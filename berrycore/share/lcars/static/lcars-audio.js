/* LCARS 1.7 — sound engine. ES5 only, no libraries.
 *
 * Two paths, picked by what the browser has:
 *   webaudio — recipes fetched from /api/sounds are built out of oscillators
 *              here, so a tap costs no network and fires instantly
 *   html5    — the same recipes rendered server-side, played as /sound/x.wav
 *
 * The BB10 browser cannot be inspected remotely, so which path is live gets
 * reported to /api/audio-report and shown in the AUDIO panel.
 */
window.LCARSAudio = (function () {
    "use strict";

    var PREF_KEY = "lcars.audio";
    var TAPS = ["tap", "tap2", "tap3"];

    var ctx = null;
    var master = null;
    var recipes = null;
    var pool = {};
    var mediaErr = {};
    var voiceEl = null;
    var lastTest = null;
    var engine = "none";
    var ctxKind = "none";
    var unlocked = false;
    var pending = null;
    var lastErr = "";
    var reported = false;

    var pref = {
        mute: false,
        vol: 0.7,
        voice: true,
        engine_voice: "auto",
        fx: true,
        route: "browser"
    };

    function loadPref() {
        var raw, k;
        try {
            raw = window.localStorage ? window.localStorage.getItem(PREF_KEY) : null;
            if (!raw) return;
            raw = JSON.parse(raw);
            for (k in pref) {
                if (pref.hasOwnProperty(k) && raw[k] !== undefined) pref[k] = raw[k];
            }
        } catch (e) { /* private browsing */ }
    }

    function savePref() {
        try {
            if (window.localStorage) {
                window.localStorage.setItem(PREF_KEY, JSON.stringify(pref));
            }
        } catch (e) { /* ignore */ }
    }

    function get(url, cb) {
        var req = new XMLHttpRequest();
        req.open("GET", url, true);
        req.onreadystatechange = function () {
            if (req.readyState !== 4) return;
            var data = null;
            try { data = JSON.parse(req.responseText); } catch (e) { data = null; }
            cb(req.status, data);
        };
        req.send(null);
    }

    function post(url, obj) {
        var req = new XMLHttpRequest();
        req.open("POST", url, true);
        req.setRequestHeader("Content-Type", "application/json");
        req.send(JSON.stringify(obj));
    }

    function makeCtx() {
        var Ctor = window.AudioContext || window.webkitAudioContext || null;
        if (!Ctor) return false;
        try {
            ctx = new Ctor();
            ctxKind = window.AudioContext ? "AudioContext" : "webkitAudioContext";
            master = ctx.createGain();
            master.gain.value = pref.mute ? 0 : pref.vol;
            master.connect(ctx.destination);
            return true;
        } catch (e) {
            lastErr = "ctx: " + (e.message || e);
            ctx = null;
            return false;
        }
    }

    function canPlayWav() {
        var probe;
        try {
            probe = document.createElement("audio");
            if (!probe || !probe.canPlayType) return "";
            return probe.canPlayType("audio/wav") || probe.canPlayType("audio/wav; codecs=1") || "no";
        } catch (e) {
            return "";
        }
    }

    /* html5 path: a few elements per sound so rapid taps do not cut each other
       off waiting for one element to rewind. They are parked in a hidden bin in
       the document because older WebKit is unreliable about playing media
       elements that were never attached. */
    function bin() {
        var el = document.getElementById("lcars-audio-bin");
        if (el) return el;
        el = document.createElement("div");
        el.id = "lcars-audio-bin";
        el.style.position = "absolute";
        el.style.left = "-9999px";
        el.style.width = "1px";
        el.style.height = "1px";
        el.style.overflow = "hidden";
        document.body.appendChild(el);
        return el;
    }

    /* One element per sound. The BB10 browser gives each element its own
       gesture permission, so every element is played once during the unlocking
       tap; a pool of three per sound would triple that work for no gain, since
       the phone plays one channel at a time anyway. */
    function elFor(name) {
        var el, host;
        if (pool[name]) return pool[name];
        host = bin();
        el = document.createElement("audio");
        el.src = "/sound/" + name + ".wav";
        el.preload = "auto";
        el.onerror = function () {
            mediaErr[name] = el.error ? el.error.code : -1;
            lastErr = "media " + name + " code " + mediaErr[name];
        };
        host.appendChild(el);
        try { el.load(); } catch (e) { /* ignore */ }
        pool[name] = el;
        return el;
    }

    function playHtml5(name) {
        var el = elFor(name);
        if (!el) return;
        try { el.volume = pref.mute ? 0 : pref.vol; } catch (e) { /* ignore */ }
        /* Rewinding before the metadata exists throws InvalidStateError on BB10,
           and when that sat ahead of play() it skipped playback entirely. The
           rewind is best-effort and must never block the play call. */
        if (el.readyState > 0 && el.currentTime > 0) {
            try { el.currentTime = 0; } catch (e) { lastErr = "rewind: " + (e.message || e); }
        }
        try {
            el.play();
        } catch (e) {
            lastErr = "play: " + (e.message || e);
        }
    }

    /* Play-then-pause inside the unlocking gesture. Old WebKit grants playback
       permission per element, so an element first touched from an XHR callback
       (a launch finishing, the computer answering) would otherwise stay silent. */
    function bless() {
        var names = recipes && recipes.sounds ? recipes.sounds : {};
        var n, el;
        for (n in names) {
            if (!names.hasOwnProperty(n)) continue;
            el = elFor(n);
            try {
                el.volume = 0;
                el.play();
                el.pause();
                el.volume = pref.mute ? 0 : pref.vol;
            } catch (e) { /* ignore */ }
        }
        el = voiceElement();
        try {
            el.volume = 0;
            el.play();
            el.pause();
            el.volume = pref.vol;
        } catch (e) { /* ignore */ }
    }

    function playBlip(b, when) {
        var i, partial, osc, gain, mult, peak, f0, f1, dur;
        dur = b.dur;
        for (i = 0; i < b.p.length; i++) {
            partial = b.p[i];
            mult = partial[0];
            peak = b.g * partial[1];
            f0 = b.f0 * mult;
            f1 = b.f1 * mult;
            osc = ctx.createOscillator();
            osc.type = b.w === "tri" ? "triangle" : (b.w === "saw" ? "sawtooth" : b.w);
            osc.frequency.setValueAtTime(f0, when);
            if (f1 !== f0) osc.frequency.linearRampToValueAtTime(f1, when + dur);
            gain = ctx.createGain();
            gain.gain.setValueAtTime(0.0001, when);
            gain.gain.linearRampToValueAtTime(peak, when + 0.004);
            /* exponential ramps cannot reach zero, so land just above it */
            gain.gain.exponentialRampToValueAtTime(0.0008, when + dur);
            osc.connect(gain);
            gain.connect(master);
            osc.start(when);
            osc.stop(when + dur + 0.02);
        }
    }

    function playSynth(name) {
        var blips = recipes && recipes.sounds ? recipes.sounds[name] : null;
        var now, i;
        if (!blips) return;
        try {
            now = ctx.currentTime + 0.005;
            for (i = 0; i < blips.length; i++) {
                playBlip(blips[i], now + blips[i].at);
            }
        } catch (e) {
            lastErr = "synth: " + (e.message || e);
        }
    }

    function playSpeaker(name) {
        post("/api/sfx", { name: name });
    }

    /* exact skips the tap randomiser, so the self test and the panel's tone
       chips play the sound they name rather than a sibling variant. */
    function play(name, exact) {
        if (pref.mute) return;
        if (!exact && name === "tap") name = TAPS[Math.floor(Math.random() * TAPS.length)];
        /* Speaker route bypasses the browser audio entirely */
        if (pref.route === "speaker") {
            playSpeaker(name);
            return;
        }
        if (engine === "none") return;
        if (!unlocked) {
            /* WebKit wants a gesture first; hold the newest sound for it */
            pending = name;
            return;
        }
        if (engine === "webaudio" && recipes) playSynth(name);
        else playHtml5(name);
    }

    /* One reused element rather than a fresh Audio() per line: a brand new
       element has no gesture permission, so spoken answers arriving from an XHR
       callback were never going to play on BB10. */
    function voiceElement() {
        if (voiceEl) return voiceEl;
        voiceEl = document.createElement("audio");
        voiceEl.preload = "auto";
        voiceEl.onerror = function () {
            lastErr = "voice media code " + (voiceEl.error ? voiceEl.error.code : -1);
        };
        bin().appendChild(voiceEl);
        return voiceEl;
    }

    function speak(text) {
        var url, el;
        if (!pref.voice || pref.mute || !text) return;
        text = String(text).replace(/\s+/g, " ").substring(0, 400);
        if (pref.route === "speaker") {
            post("/api/speak", { text: text, voice: pref.engine_voice, fx: pref.fx });
            return;
        }
        url = "/voice.wav?say=" + encodeURIComponent(text) +
              "&v=" + encodeURIComponent(pref.engine_voice) +
              "&fx=" + (pref.fx ? "1" : "0");
        el = voiceElement();
        try {
            el.pause();
            el.volume = pref.vol;
            el.src = url;
            try { el.load(); } catch (e2) { /* ignore */ }
            el.play();
        } catch (e) {
            lastErr = "voice: " + (e.message || e);
        }
    }

    /* The computer chirps, then answers. */
    function announce(text) {
        play("ack");
        if (!pref.voice) return;
        window.setTimeout(function () { speak(text); }, 210);
    }

    function unlock() {
        if (unlocked) return;
        unlocked = true;
        if (ctx && ctx.resume) {
            try { ctx.resume(); } catch (e) { /* ignore */ }
        }
        if (engine === "html5") bless();
        if (pending) {
            var name = pending;
            pending = null;
            play(name);
        }
        report();
    }

    function canPlay(type) {
        var probe;
        try {
            probe = document.createElement("audio");
            return (probe.canPlayType && probe.canPlayType(type)) || "no";
        } catch (e) {
            return "";
        }
    }

    function report(extra) {
        var body = {
            engine: engine,
            ctx: ctxKind,
            html: !!canPlayWav(),
            wav: canPlayWav(),
            fmt: "mp3=" + canPlay("audio/mpeg") + " aac=" + canPlay("audio/mp4"),
            unlocked: unlocked,
            screen: window.innerWidth + "x" + window.innerHeight,
            err: lastErr
        };
        if (extra) {
            body.test = extra;
            reported = true;
        } else {
            if (reported) return;
            reported = true;
        }
        post("/api/audio-report", body);
    }

    /* Plays every tone in turn and checks each one actually started. Nobody can
       inspect the BB10 browser remotely, so this is how a silent phone gets
       diagnosed: the result shows on the panel and goes to the server log. */
    function selftest(cb) {
        var names = nameList();
        var results = [];
        var i = 0;

        function done() {
            var pass = 0, k, codes = [];
            for (k = 0; k < results.length; k++) {
                if (results[k].ok) pass += 1;
                else codes.push(results[k].name + "=" + results[k].code + "/r" + results[k].ready);
            }
            lastTest = {
                pass: pass,
                total: results.length,
                results: results,
                fail: codes.join(" ")
            };
            report(pass + "/" + results.length + " " + codes.join(" "));
            if (cb) cb(lastTest);
        }

        function step() {
            var name, el;
            if (i >= names.length) {
                done();
                return;
            }
            name = names[i];
            i += 1;
            el = engine === "html5" ? elFor(name) : null;
            if (el && el.readyState > 0) {
                try { el.currentTime = 0; } catch (e) { /* ignore */ }
            }
            play(name);
            window.setTimeout(function () {
                var ok;
                if (engine === "html5") {
                    ok = !!(el && !el.error && (el.currentTime > 0 || !el.paused));
                    results.push({
                        name: name,
                        ok: ok,
                        code: el && el.error ? el.error.code : 0,
                        ready: el ? el.readyState : -1
                    });
                } else {
                    ok = !!ctx && ctx.state !== "suspended";
                    results.push({ name: name, ok: ok, code: 0, ready: -1 });
                }
                step();
            }, 330);
        }

        if (!names.length) {
            done();
            return;
        }
        step();
    }

    function nameList() {
        var out = [], n;
        if (!recipes || !recipes.sounds) return out;
        for (n in recipes.sounds) {
            if (recipes.sounds.hasOwnProperty(n)) out.push(n);
        }
        out.sort();
        return out;
    }

    function state() {
        return {
            engine: engine,
            ctx: ctxKind,
            test: lastTest,
            unlocked: unlocked,
            mute: pref.mute,
            vol: pref.vol,
            voice: pref.voice,
            voiceEngine: pref.engine_voice,
            fx: pref.fx,
            route: pref.route,
            sounds: recipes && recipes.sounds ? recipes.sounds : {},
            err: lastErr
        };
    }

    function setPref(key, value) {
        pref[key] = value;
        if (key === "mute" && master) master.gain.value = value ? 0 : pref.vol;
        if (key === "vol" && master && !pref.mute) master.gain.value = value;
        savePref();
    }

    function init(cb) {
        loadPref();
        /* ?html5 forces the WAV path, which is the only way to exercise the
           fallback on a browser that does have Web Audio. */
        if (window.location.search.indexOf("html5") >= 0) engine = "html5";
        else if (makeCtx()) engine = "webaudio";
        else if (canPlayWav() && canPlayWav() !== "no") engine = "html5";
        else { engine = "none"; lastErr = lastErr || "no audio support"; }

        get("/api/sounds", function (status, data) {
            if (status === 200 && data && data.ok) recipes = data.data;
            else if (engine === "webaudio") {
                /* no recipes means nothing to synthesize; the WAVs still work */
                engine = canPlayWav() ? "html5" : "none";
                lastErr = "recipes unavailable";
            }
            if (cb) cb(state());
        });

        /* Any first touch or click counts as the unlocking gesture. */
        if (document.addEventListener) {
            document.addEventListener("touchstart", unlock, true);
            document.addEventListener("mousedown", unlock, true);
            document.addEventListener("click", unlock, true);
            document.addEventListener("keydown", unlock, true);
        }
        window.setTimeout(report, 6000);
    }

    return {
        init: init,
        play: play,
        speak: speak,
        announce: announce,
        unlock: unlock,
        state: state,
        setPref: setPref,
        selftest: selftest,
        names: nameList
    };
})();
