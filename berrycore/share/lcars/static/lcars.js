/* BerryCore LCARS 1.7 — ES5, BB10 browser (Passport reports 504x462) */
(function () {
    "use strict";

    var ALL = [];
    var PANEL = "access";
    var FILE_ROOT = "documents";
    var FILE_PATH = "";
    var OPEN_FILE = "";
    var SELECTED = "";
    var OPEN_APP = null;
    var CAT = "";
    var toastT = null;
    var askT = null;
    var holdT = null;
    var held = false;
    var COLORS = ["c-orange", "c-peach", "c-lilac", "c-peri", "c-apricot", "c-dust"];
    /* The shelf itself is orange, so orange chips would vanish into it. */
    var SHELF_COLORS = ["c-peach", "c-lilac", "c-peri", "c-apricot", "c-dust"];
    var SHELF_H = 70;   /* keep in step with .row-bot in lcars.css */
    /* Apps that must take over the page instead of loading into the workspace
       frame. The terminal is deliberately not one of them — it runs inside the
       LCARS frame, and FULL in the band is there if you want the whole screen. */
    var FULL_PAGE = {};
    /* label, LCARS code, accent — the accent matches the panel's rail button. */
    var TITLES = {
        "access": ["STATION DESK", "01-4470", "c-orange"],
        "programs": ["PROGRAM DIRECTORY", "02-1108", "c-peach"],
        "files": ["FILE ACCESS", "03-1977", "c-lilac"],
        "notes": ["STATION NOTES", "04-2711", "c-peri"],
        "systems": ["SYSTEMS MONITOR", "05-3604", "c-apricot"],
        "ai": ["COMPUTER", "06-4701", "c-dust"],
        "audio": ["AUDIO SYSTEMS", "07-8812", "c-rose"],
        "workspace": ["WORKSPACE", "08-5512", "c-peach"]
    };
    var PINS = [
        { kind: "panel", id: "files", name: "Files", sub: "DOCS" },
        { kind: "panel", id: "programs", name: "Programs", sub: "START" },
        { kind: "panel", id: "notes", name: "Notes", sub: "LOG" },
        { kind: "panel", id: "systems", name: "Systems", sub: "SCAN" },
        { kind: "app", id: "term49", name: "Terminal", sub: "SHELL" },
        { kind: "lcars", id: "library", name: "Library", sub: "DATA", url: "/apps/library.html" }
    ];
    /* LCARS internal apps — served from this same port, no separate server needed */
    var LCARS_APPS = {
        "library": { id: "library", name: "Library", url: "/apps/library.html" }
    };

    function $(id) { return document.getElementById(id); }

    var AUD = window.LCARSAudio || null;

    /* Every interface sound goes through here, so a missing audio engine is
       never fatal — the station just runs silent. */
    function sfx(name) {
        if (AUD) AUD.play(name);
    }

    function speak(text) {
        if (AUD) AUD.speak(text);
    }

    function esc(s) {
        return String(s || "").replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
    }

    function xhr(method, url, body, cb) {
        var req = new XMLHttpRequest();
        req.open(method, url, true);
        req.timeout = 30000;
        if (body) req.setRequestHeader("Content-Type", "application/json");
        req.onreadystatechange = function () {
            if (req.readyState !== 4) return;
            var data = null;
            try { data = JSON.parse(req.responseText); } catch (e) {}
            if (cb) cb(req.status, data);
        };
        req.send(body || null);
    }

    function pad(n) { return n < 10 ? "0" + n : String(n); }

    function stardate(d) {
        var start = new Date(d.getFullYear(), 0, 0);
        var day = Math.floor((d - start) / 86400000);
        var frac = (d.getHours() * 60 + d.getMinutes()) / 1440;
        return ((d.getFullYear() - 2000) * 1000 + day + frac).toFixed(1);
    }

    function tickClock() {
        var d = new Date();
        var sd = stardate(d);
        if ($("clock")) $("clock").textContent = pad(d.getHours()) + ":" + pad(d.getMinutes());
        if ($("stardate")) $("stardate").textContent = "SD " + sd;
        if ($("sd-big")) $("sd-big").textContent = sd;
    }

    function toast(msg, kind) {
        var el = $("toast");
        if (kind !== "quiet") sfx(kind === "bad" ? "deny" : "toast");
        if (!el) return;
        el.textContent = msg;
        el.className = "toast on";
        if (toastT) clearTimeout(toastT);
        toastT = setTimeout(function () { el.className = "toast"; }, 2200);
    }

    function colorAt(i) {
        return COLORS[i % COLORS.length];
    }

    /* Space between an element's top edge and the shelf. A table cell grows to
       fit its content, so measuring the cell is circular — measure the real
       viewport position instead. Returns 0 while the panel is hidden. */
    /* Anything after the element (a query field, a button row) still needs its
       space, so subtract the siblings that follow it. */
    function tailHeight(el) {
        var h = 0, n = el.nextSibling;
        while (n) {
            if (n.nodeType === 1 && n.offsetHeight) h += n.offsetHeight + 6;
            n = n.nextSibling;
        }
        return h;
    }

    function roomBelow(el) {
        var top;
        if (!el || !el.offsetParent) return 0;
        top = el.getBoundingClientRect().top;
        return Math.max(0, (window.innerHeight || 720) - SHELF_H - top - 6 - tailHeight(el));
    }

    function fitToBottom(el, min) {
        var room = roomBelow(el);
        var h;
        if (!room) return 0;
        h = Math.floor(Math.max(min, room));
        el.style.height = h + "px";
        return h;
    }

    /* Grow a tile grid so its rows fill the panel instead of leaving a black
       band above the shelf. Returns the row height it settled on. */
    function fillGrid(el, cols, cls, minH, room) {
        var kids = el ? el.getElementsByTagName("div") : [];
        var tiles = [], i, rows, h;
        if (!el || !room) return 0;
        for (i = 0; i < kids.length; i++) {
            if (kids[i].className.indexOf(cls) === 0) tiles.push(kids[i]);
        }
        if (!tiles.length) return 0;
        rows = Math.ceil(tiles.length / cols);
        h = Math.floor((room - rows * 6) / rows);   /* each row carries a 6px gap */
        if (h < minH) h = minH;
        for (i = 0; i < tiles.length; i++) {
            tiles[i].style.height = h + "px";
        }
        return h;
    }

    function sizeDesk() {
        var el = $("desk");
        var h = fillGrid(el, 3, "desk-icon", 66, roomBelow(el));
        var tiles = el ? el.getElementsByTagName("div") : [];
        var i;
        if (!h) return;
        for (i = 0; i < tiles.length; i++) {
            /* Push the status tag onto the bottom edge of the tile. */
            if (tiles[i].className.indexOf("desk-icon") === 0) {
                tiles[i].getElementsByTagName("span")[0].style.marginTop = (h - 52) + "px";
            }
        }
    }

    /* End the chip area on a chip boundary. Left to itself it stops mid-row,
       which reads as a clipped chip rather than something you can scroll. Rows
       are not a fixed pitch here (the VOICE divider sits between them), so this
       measures where the chips actually end. */
    function sizeAud() {
        var el = $("aud-tests");
        var chips, room, top, i, bottom, best;
        if (!el) return;
        room = fitToBottom(el, 60);
        if (!room) return;
        chips = el.getElementsByTagName("span");
        if (!chips.length) return;
        top = el.getBoundingClientRect().top - el.scrollTop;
        best = 0;
        for (i = 0; i < chips.length; i++) {
            bottom = Math.ceil(chips[i].getBoundingClientRect().bottom - top) + 5;
            if (bottom <= room && bottom > best) best = bottom;
        }
        if (best) el.style.height = best + "px";
    }

    function sizeSys() {
        var el = $("sys-box");
        /* sys-box is already fitted to the shelf, so fill it, not the panel. */
        if (el) fillGrid(el, 2, "sys", 92, el.clientHeight);
    }

    /* Run the rail colour block down to the elbow, like a real LCARS frame. */
    function sizeRail() {
        var fill = document.getElementById("rail-fill");
        if (fill) fitToBottom(fill, 40);
    }

    /* Right frame: a column of varied blocks, like the data columns on a real
       LCARS panel. Built to the measured height so it always closes the frame. */
    var R_PATTERN = [46, 22, 64, 22, 40, 78, 22, 52];
    var rframeH = -1;

    function paintRFrame() {
        var el = document.getElementById("rframe");
        var room = el ? roomBelow(el) : 0;
        var html = "", used = 0, i = 0, h;
        if (!el || !room || room === rframeH) return;
        rframeH = room;
        while (used < room && i < 40) {
            h = R_PATTERN[i % R_PATTERN.length];
            if (used + h + 4 > room) {
                h = room - used - 4;      /* last block takes what is left */
                if (h < 14) break;
            }
            html += '<div class="rblk ' + COLORS[i % COLORS.length] + '" style="height:' + h + 'px"></div>';
            used += h + 4;
            i += 1;
        }
        el.innerHTML = html;
    }

    /* Every scrolling region runs to the shelf; nothing is hardcoded. */
    function sizeFill() {
        var fills = ["prog-list", "file-list", "notes", "ai-log", "sys-box", "file-text"];
        var i, el;
        for (i = 0; i < fills.length; i++) {
            el = $(fills[i]);
            if (el) fitToBottom(el, 140);
        }
        el = $("ws");
        if (el) fitToBottom(el, 220);
        sizeDesk();
        sizeSys();
        sizeAud();
        sizeRail();
        paintRFrame();
        fitShelf();
    }

    function showFileEdit(on) {
        if ($("file-browse")) $("file-browse").className = on ? "off" : "";
        if ($("file-edit")) $("file-edit").className = on ? "" : "off";
        sizeFill();
    }

    /* The elbow band is shared, so it re-labels itself on every panel switch. */
    function paintBand(name) {
        var t = TITLES[name] || TITLES.access;
        var ws = name === "workspace";
        if ($("panel-title")) {
            $("panel-title").textContent = (ws && OPEN_APP) ? OPEN_APP.name : t[0];
        }
        if ($("band-num")) $("band-num").textContent = t[1];
        if ($("band-bar")) $("band-bar").className = "band-bar " + t[2];
        if ($("btn-full")) $("btn-full").className = "pill tiny c-lilac" + (ws ? "" : " off");
        if ($("btn-close-ws")) $("btn-close-ws").className = "pill tiny c-dust" + (ws ? "" : " off");
    }

    function showPanel(name) {
        var panels = document.getElementsByClassName("panel");
        var navs = document.getElementsByClassName("nav");
        var i;
        if (name !== PANEL) sfx(name === "workspace" ? "open" : "nav");
        PANEL = name;
        for (i = 0; i < panels.length; i++) {
            panels[i].className = panels[i].id === "panel-" + name ? "panel on" : "panel";
        }
        for (i = 0; i < navs.length; i++) {
            navs[i].className = navs[i].className.replace(" on", "");
            if (navs[i].getAttribute("data-panel") === name) {
                navs[i].className += " on";
            }
        }
        paintBand(name);
        if (name === "files") {
            showFileEdit(false);
            loadRoots();
        }
        if (name === "notes") loadNotes();
        if (name === "systems") loadSystems();
        if (name === "audio") { if (AUDCAPS) paintAudio(); else loadAudio(); }
        if (name === "programs" || name === "access") paintPrograms();
        sizeFill();
    }

    function findApp(id) {
        var i;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].id === id) return ALL[i];
        }
        return null;
    }

    function running() {
        var out = [], i;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].up && ALL[i].id !== "lcars") out.push(ALL[i]);
        }
        return out;
    }

    function cats() {
        var seen = {}, out = [], i, c;
        for (i = 0; i < ALL.length; i++) {
            c = ALL[i].cat || "APP";
            if (ALL[i].id === "lcars" || seen[c]) continue;
            seen[c] = true;
            out.push(c);
        }
        out.sort();
        return out;
    }

    function launchables() {
        var q = ($("q") && $("q").value || "").toLowerCase();
        var out = [], i, a, hay;
        for (i = 0; i < ALL.length; i++) {
            a = ALL[i];
            if (a.id === "lcars") continue;
            if (CAT && (a.cat || "") !== CAT) continue;
            hay = (a.name + " " + (a.cat || "") + " " + a.id).toLowerCase();
            if (q && hay.indexOf(q) === -1) continue;
            out.push(a);
        }
        out.sort(function (x, y) {
            if (x.up !== y.up) return x.up ? -1 : 1;
            return String(x.name).localeCompare(String(y.name));
        });
        return out;
    }

    function paintDesk() {
        var el = $("desk");
        var html = "", i, pin, a, mark;
        if (!el) return;
        for (i = 0; i < PINS.length; i++) {
            pin = PINS[i];
            mark = pin.sub;
            if (pin.kind === "app") {
                a = findApp(pin.id);
                if (a && a.up) mark = "LIVE";
                else if (a && !a.has_bin) mark = "MISS";
            }
            html += '<div class="desk-icon ' + colorAt(i);
            if (i % 3 === 2) html += " last";
            html += '"';
            if (pin.kind === "panel") html += ' data-panel="' + esc(pin.id) + '"';
            else html += ' data-open="' + esc(pin.id) + '"';
            html += '>' + esc(pin.name) + '<span class="sub">' + esc(mark) + "</span></div>";
        }
        el.innerHTML = html;
        sizeDesk();
    }

    function paintCats() {
        var el = $("cats");
        var list = cats();
        var html = '<span class="cat c-peach' + (CAT ? "" : " on") + '" data-cat="">ALL</span>';
        var i;
        if (!el) return;
        for (i = 0; i < list.length; i++) {
            html += '<span class="cat ' + colorAt(i) + (CAT === list[i] ? " on" : "") + '" data-cat="' + esc(list[i]) + '">' + esc(list[i]) + "</span>";
        }
        el.innerHTML = html;
    }

    function paintShelf() {
        var el = $("shelf");
        var list = running();
        var html = "", i, a, cls;
        if (!el) return;
        if (!list.length) {
            el.innerHTML = '<span class="chip c-peach">NONE</span>';
            fitShelf();
            return;
        }
        for (i = 0; i < list.length; i++) {
            a = list[i];
            cls = "chip " + SHELF_COLORS[i % SHELF_COLORS.length];
            if (OPEN_APP && OPEN_APP.id === a.id) cls += " cur";
            html += '<span class="' + cls + '" data-open="' + esc(a.id) + '">' + esc(a.name) + "</span>";
        }
        el.innerHTML = html;
        fitShelf();
    }

    /* The shelf is one row beside START. Give it exactly the room that is left,
       and if the chips still do not fit, fold the remainder into a "+n" chip, so
       a name is never sliced through the middle. */
    var MORE_W = 58;

    function fitShelf() {
        var row = $("shelf");
        var shelf = document.getElementsByClassName("shelf")[0];
        var more = $("shelf-more");
        var chips = [], widths = [], avail, limit, fits, i;

        function countFits(cap) {
            var n = 0, w = 0, j;
            for (j = 0; j < widths.length; j++) {
                if (w + widths[j] > cap) break;
                w += widths[j];
                n += 1;
            }
            return n;
        }

        if (!row || !shelf || !row.offsetParent) return;
        if (more && more.parentNode) more.parentNode.removeChild(more);
        row.style.width = "auto";
        for (i = 0; i < row.childNodes.length; i++) {
            if (row.childNodes[i].nodeType === 1) chips.push(row.childNodes[i]);
        }
        for (i = 0; i < chips.length; i++) {
            chips[i].style.display = "";
        }
        avail = Math.floor(shelf.getBoundingClientRect().right - 8 - row.getBoundingClientRect().left);
        if (avail < 80) return;
        row.style.width = avail + "px";
        for (i = 0; i < chips.length; i++) {
            widths.push(chips[i].offsetWidth + 4);
        }
        fits = countFits(avail);
        if (fits < chips.length) {
            limit = avail - MORE_W;
            fits = countFits(limit > 0 ? limit : 0);
        }
        for (i = fits; i < chips.length; i++) {
            chips[i].style.display = "none";
        }
        if (fits < chips.length) {
            more = document.createElement("span");
            more.id = "shelf-more";
            more.className = "chip c-peach";
            more.setAttribute("data-panel", "programs");
            more.textContent = "+" + (chips.length - fits);
            row.appendChild(more);
        }
    }

    function paintAccess() {
        if ($("live-n")) $("live-n").textContent = String(running().length);
        paintDesk();
    }

    function paintPrograms() {
        var el = $("prog-list");
        var list = launchables();
        var html = "", i, a, cls, mark;
        paintAccess();
        paintShelf();
        paintCats();
        if (!el) return;
        if (!list.length) {
            el.innerHTML = '<div class="brief">NO MATCHING PROGRAMS</div>';
            return;
        }
        for (i = 0; i < list.length; i++) {
            a = list[i];
            cls = "prog " + colorAt(i);
            if (!a.has_bin && !a.up) cls += " miss";
            mark = a.up ? "LIVE" : (a.has_bin ? a.cat || "APP" : "MISSING");
            html += '<div class="' + cls + '" data-open="' + esc(a.id) + '">';
            html += esc(a.name);
            html += '<span class="meta">' + esc(mark) + "</span></div>";
        }
        el.innerHTML = html;
        sizeFill();
    }

    function openWorkspace(a) {
        var frame = $("ws");
        if (FULL_PAGE[a.id]) {
            window.location.href = "http://127.0.0.1:" + a.port + "/";
            return;
        }
        OPEN_APP = a;
        if (frame) frame.src = "http://127.0.0.1:" + a.port + "/";
        showPanel("workspace");
        paintShelf();
    }

    function startThenOpen(a) {
        sfx("work");
        toast("Starting " + a.name, "quiet");
        xhr("POST", "/api/start", '{"id":"' + a.id + '"}', function (status, data) {
            var result = data && data.results && data.results[0] ? data.results[0] : data;
            if (!data || data.status !== "ok" || (result && result.error)) {
                toast((result && result.error) ? result.error : "Start failed", "bad");
                speak("Unable to comply.");
                return;
            }
            watchStart(a.id);
        });
    }

    function watchStart(id) {
        var n = 0;
        var t = setInterval(function () {
            n += 1;
            xhr("GET", "/api/status", null, function (status, data) {
                var a;
                if (status === 200 && data && data.apps) merge(data.apps);
                a = findApp(id);
                paintPrograms();
                if (a && a.up) {
                    clearInterval(t);
                    openWorkspace(a);
                    return;
                }
                if (n >= 12) {
                    clearInterval(t);
                    toast(a ? a.name + " still coming up" : "Still starting", "bad");
                }
            });
        }, 700);
    }

    function tapApp(id) {
        /* Check for LCARS internal apps first */
        var la = LCARS_APPS[id];
        if (la) {
            openLcarsApp(la);
            return;
        }
        var a = findApp(id);
        if (!a) {
            toast((id || "app") + " is not installed", "bad");
            speak("Unable to comply.");
            return;
        }
        if (a.up) {
            openWorkspace(a);
            return;
        }
        if (a.has_bin) {
            startThenOpen(a);
            return;
        }
        toast((a.name || id) + " is not installed", "bad");
        speak("Unable to comply.");
    }

    function openLcarsApp(la) {
        var frame = $("ws");
        OPEN_APP = { id: la.id, name: la.name, port: 0, lcars: true };
        if (frame) frame.src = la.url;
        showPanel("workspace");
        paintShelf();
    }

    function stopApp(id) {
        var a = findApp(id);
        sfx("close");
        toast("Stopping " + (a ? a.name : id), "quiet");
        xhr("POST", "/api/stop", '{"id":"' + id + '"}', function () {
            loadStatus();
        });
    }

    function merge(apps) {
        ALL = apps || [];
    }

    function loadStatus() {
        xhr("GET", "/api/status", null, function (status, data) {
            if (status !== 200 || !data) return;
            if (data.apps) merge(data.apps);
            if ($("bc-ver")) $("bc-ver").textContent = data.berrycore || "—";
            paintPrograms();
        });
    }

    var sysN = 0;

    function sysTile(k, v) {
        var cls = "sys" + (sysN % 2 === 1 ? " last" : "");
        sysN += 1;
        return '<div class="' + cls + '"><div class="k">' + esc(k) + '</div><div class="v">' + esc(v || "—") + "</div></div>";
    }

    function loadSystems() {
        xhr("GET", "/api/systems", null, function (status, data) {
            var box = $("sys-box");
            if (!box) return;
            sysN = 0;
            if (status !== 200 || !data) {
                box.innerHTML = sysTile("SCAN", "FAILED");
                return;
            }
            if ($("ai-ready")) $("ai-ready").textContent = data.ai ? "ONLINE" : "STANDBY";
            box.innerHTML = sysTile("HOST", data.host) +
                sysTile("BERRYCORE", data.version) +
                sysTile("LCARS", (data.lcars || "") + " :" + (data.port || "")) +
                sysTile("TYPEFACE", data.font || "system") +
                sysTile("BATTERY", data.battery || "sensors missing") +
                sysTile("CPU", data.cpu || "—") +
                sysTile("THERMAL", data.temp || "—") +
                sysTile("LOCATION", data.gps || "gps missing");
            sizeSys();
        });
    }

    function loadNotes() {
        xhr("GET", "/api/notes", null, function (status, data) {
            var el = $("notes");
            var items, html = "", i, it, d;
            if (!el) return;
            items = data && data.data && data.data.items ? data.data.items : [];
            if (!items.length) {
                el.innerHTML = '<div class="brief">NO STATION NOTES</div>';
                return;
            }
            for (i = items.length - 1; i >= 0; i--) {
                it = items[i];
                d = new Date((it.ts || 0) * 1000);
                html += '<div class="note"><div class="when">' + esc(d.toLocaleString()) + "</div>";
                html += esc(it.text) + "</div>";
            }
            el.innerHTML = html;
            sizeFill();
        });
    }

    function addNote() {
        var box = $("note-text");
        var text = box ? box.value : "";
        if (!text) {
            toast("Empty note", "bad");
            return;
        }
        xhr("POST", "/api/notes", JSON.stringify({ text: text }), function (status, data) {
            if (!data || !data.ok) {
                toast((data && data.error) || "Note failed", "bad");
                return;
            }
            sfx("confirm");
            if (box) box.value = "";
            loadNotes();
        });
    }

    function loadRoots() {
        xhr("GET", "/api/roots", null, function (status, data) {
            var el = $("roots");
            var html = "", i, r, rows;
            if (!el) return;
            rows = data && data.roots ? data.roots : [];
            for (i = 0; i < rows.length; i++) {
                r = rows[i];
                if (!r.present) continue;
                html += '<span class="root-btn ' + colorAt(i) + (FILE_ROOT === r.id ? " on" : "") + '" data-root="' + esc(r.id) + '">' + esc(r.name) + "</span>";
            }
            el.innerHTML = html;
            sizeFill();   /* the roots row shifts the list down */
            loadFiles();
        });
    }

    function loadFiles() {
        var url = "/api/files?root=" + encodeURIComponent(FILE_ROOT) + "&path=" + encodeURIComponent(FILE_PATH);
        if ($("pathline")) {
            $("pathline").textContent = FILE_ROOT.toUpperCase() + " / " + (FILE_PATH || "");
        }
        xhr("GET", url, null, function (status, data) {
            var el = $("file-list");
            var html = "", i, it, cls;
            if (!el) return;
            if (!data || !data.ok) {
                el.innerHTML = '<div class="brief">' + esc((data && data.error) || "NO ACCESS") + "</div>";
                return;
            }
            if (FILE_PATH) {
                html += '<div class="frow dir" data-up="1">.. PARENT</div>';
            }
            for (i = 0; i < data.dirs.length; i++) {
                it = data.dirs[i];
                cls = "frow dir" + (SELECTED === it.name ? " sel" : "");
                html += '<div class="' + cls + '" data-dir="' + esc(it.name) + '">' + esc(it.name) + " /</div>";
            }
            for (i = 0; i < data.files.length; i++) {
                it = data.files[i];
                cls = "frow" + (SELECTED === it.name ? " sel" : "");
                html += '<div class="' + cls + '" data-file="' + esc(it.name) + '">' + esc(it.name) + "</div>";
            }
            if (!data.dirs.length && !data.files.length) {
                html += '<div class="brief">EMPTY</div>';
            }
            el.innerHTML = html;
            sizeFill();
        });
    }

    function joinPath(base, name) {
        if (!base) return name;
        return base + "/" + name;
    }

    function parentPath(path) {
        var i = path.lastIndexOf("/");
        if (i < 0) return "";
        return path.substring(0, i);
    }

    function newName() {
        var box = $("file-newname");
        return box ? String(box.value || "").replace(/^\s+|\s+$/g, "") : "";
    }

    function openFile(name) {
        var rel = joinPath(FILE_PATH, name);
        OPEN_FILE = rel;
        SELECTED = name;
        xhr("GET", "/api/file?root=" + encodeURIComponent(FILE_ROOT) + "&path=" + encodeURIComponent(rel), null, function (status, data) {
            if (!data || !data.ok) {
                toast((data && data.error) || "Cannot open");
                return;
            }
            if ($("file-name")) $("file-name").textContent = data.name;
            if ($("file-text")) $("file-text").value = data.text || "";
            showFileEdit(true);
        });
    }

    function saveFile() {
        var text = $("file-text") ? $("file-text").value : "";
        var path = OPEN_FILE;
        if (!path) {
            toast("No file open", "bad");
            return;
        }
        xhr("POST", "/api/file", JSON.stringify({
            root: FILE_ROOT,
            path: path,
            text: text
        }), function (status, data) {
            if (!data || !data.ok) {
                toast((data && data.error) || "Save failed", "bad");
                return;
            }
            sfx("confirm");
            toast("Saved", "quiet");
        });
    }

    function newFile() {
        var name = newName() || ("note-" + String(new Date().getTime()) + ".txt");
        if (name.indexOf(".") < 0) name += ".txt";
        OPEN_FILE = joinPath(FILE_PATH, name);
        SELECTED = name;
        if ($("file-name")) $("file-name").textContent = name;
        if ($("file-text")) $("file-text").value = "";
        showFileEdit(true);
        toast("New " + name);
    }

    function mkdir() {
        var name = newName();
        if (!name) {
            toast("Type a folder name");
            return;
        }
        xhr("POST", "/api/mkdir", JSON.stringify({
            root: FILE_ROOT,
            path: FILE_PATH,
            name: name
        }), function (status, data) {
            if (!data || !data.ok) {
                toast((data && data.error) || "Folder failed");
                return;
            }
            if ($("file-newname")) $("file-newname").value = "";
            toast("Folder " + name);
            loadFiles();
        });
    }

    function deleteSelected() {
        var rel;
        if (!SELECTED) {
            toast("Tap a file first", "bad");
            return;
        }
        rel = joinPath(FILE_PATH, SELECTED);
        xhr("POST", "/api/delete", JSON.stringify({
            root: FILE_ROOT,
            path: rel
        }), function (status, data) {
            if (!data || !data.ok) {
                toast((data && data.error) || "Delete failed", "bad");
                return;
            }
            toast("Deleted " + SELECTED, "quiet");
            SELECTED = "";
            OPEN_FILE = "";
            showFileEdit(false);
            loadFiles();
        });
    }

    function aiLine(who, text) {
        var el = $("ai-log");
        var div;
        if (!el) return;
        div = document.createElement("div");
        div.className = "line";
        div.innerHTML = '<div class="who">' + esc(who) + '</div><div class="txt">' + esc(text) + "</div>";
        el.appendChild(div);
        el.scrollTop = el.scrollHeight;
    }

    function askComputer() {
        var box = $("ai-q");
        var text = box ? box.value : "";
        if (!text) {
            toast("Enter a query", "bad");
            return;
        }
        aiLine("YOU", text);
        sfx("work");
        if (box) box.value = "";
        xhr("POST", "/api/ask", JSON.stringify({ text: text }), function (status, data) {
            if (!data || !data.ok) {
                toast((data && data.error) || "Computer offline", "bad");
                return;
            }
            pollAsk();
        });
    }

    function pollAsk() {
        if (askT) clearInterval(askT);
        askT = setInterval(function () {
            xhr("GET", "/api/ask", null, function (status, data) {
                var st = data && data.data ? data.data : null;
                if (!st) return;
                if (st.busy) return;
                clearInterval(askT);
                askT = null;
                if (st.err && !st.reply) {
                    aiLine("COMPUTER", st.err);
                    sfx("deny");
                    speak("Unable to comply.");
                    return;
                }
                aiLine("COMPUTER", st.reply || "NO RESPONSE");
                if (AUD) AUD.announce(st.reply || "No response.");
            });
        }, 1200);
    }

    /* ── audio panel ─────────────────────────────────────────────── */

    var AUDCAPS = null;
    /* Short computer lines, the kind the ship actually says. Chip label first,
       spoken text second — the full sentence would not fit on a chip. */
    var LINES = [
        ["WORKING", "Working."],
        ["ACK", "Acknowledged."],
        ["AFFIRM", "Affirmative."],
        ["NO COMPLY", "Unable to comply."],
        ["DENIED", "Access denied."],
        ["WARNING", "Warning."],
        ["COMPLETE", "Program complete."],
        ["STANDBY", "Standing by."],
        ["ONLINE", "LCARS online. All systems nominal."]
    ];

    function audTile(k, v) {
        return sysTile(k, v);
    }

    /* PASS/FAIL straight on the chip, so a silent phone shows why. */
    function testMark(test, name) {
        var i;
        if (!test || !test.results) return "";
        for (i = 0; i < test.results.length; i++) {
            if (test.results[i].name !== name) continue;
            return test.results[i].ok ? " \u2713" : " \u2717";
        }
        return "";
    }

    function paintAudio() {
        var box = $("aud-box");
        var tests = $("aud-tests");
        var st = AUD ? AUD.state() : null;
        var names = AUD ? AUD.names() : [];
        var caps = AUDCAPS || {};
        var voices = caps.voices || [];
        var html = "", i, n, cols, wide, mark;

        if (box) {
            sysN = 0;
            html += audTile("ENGINE", st ? st.engine : "none");
            html += audTile("CONTEXT", st ? st.ctx : "none");
            html += audTile("TONES", String(names.length));
            html += audTile("VOICE", voices.length ? voices.join(" + ") : "none");
            html += audTile("VOICE FX", caps.fx ? "ffmpeg" : "unavailable");
            if (st && st.test) {
                html += audTile("SELF TEST", st.test.pass + "/" + st.test.total +
                                (st.test.fail ? " · " + st.test.fail : " tones playing"));
            } else {
                html += audTile("UNLOCKED", st && st.unlocked ? "yes" : "waiting for tap");
            }
            box.innerHTML = html;
        }

        if (tests) {
            /* The Passport browser reports a 504px-wide viewport, where three
               chips per row clip their labels. Column count follows the width. */
            cols = tests.clientWidth >= 460 ? 3 : 2;
            wide = cols === 3 ? "30%" : "47%";
            html = "";
            for (i = 0; i < names.length; i++) {
                n = names[i];
                mark = st && st.test ? testMark(st.test, n) : "";
                html += '<span class="chip ' + colorAt(i) +
                        (i % cols === cols - 1 ? " last" : "") +
                        '" style="width:' + wide + '" data-tone="' + esc(n) + '">' +
                        esc(n) + mark + "</span>";
            }
            html += '<span class="said">COMPUTER VOICE</span>';
            for (i = 0; i < LINES.length; i++) {
                html += '<span class="chip ' + SHELF_COLORS[i % SHELF_COLORS.length] +
                        (i % cols === cols - 1 ? " last" : "") +
                        '" style="width:' + wide + '" data-say="' + esc(LINES[i][1]) + '">' +
                        esc(LINES[i][0]) + "</span>";
            }
            tests.innerHTML = html;
        }

        if (st) {
            if ($("aud-mute")) $("aud-mute").textContent = st.mute ? "SOUND OFF" : "SOUND ON";
            if ($("aud-voice")) $("aud-voice").textContent = st.voice ? "VOICE ON" : "VOICE OFF";
            if ($("aud-fx")) $("aud-fx").textContent = st.fx ? "FX ON" : "FX OFF";
            if ($("aud-route")) $("aud-route").textContent = st.route === "speaker" ? "SPEAKER" : "BROWSER";
            if ($("aud-vsel")) $("aud-vsel").textContent = "VOICE: " + String(st.voiceEngine).toUpperCase();
        }
        paintAudBadge();
        sizeFill();
    }

    function paintAudBadge() {
        var el = $("aud-toggle");
        var st = AUD ? AUD.state() : null;
        if (!el) return;
        if (!st || st.engine === "none") {
            el.className = "stamp aud off";
            el.textContent = "\u266b N/A";
            return;
        }
        el.className = st.mute ? "stamp aud off" : "stamp aud";
        el.textContent = st.mute ? "\u266b OFF" : "\u266b ON";
    }

    function loadAudio() {
        xhr("GET", "/api/audio", null, function (status, data) {
            AUDCAPS = (status === 200 && data && data.data) ? data.data : {};
            paintAudio();
        });
    }

    function cycleVoice() {
        var voices = (AUDCAPS && AUDCAPS.voices) ? AUDCAPS.voices : [];
        var order = ["auto"].concat(voices);
        var cur = AUD ? AUD.state().voiceEngine : "auto";
        var i = order.indexOf(cur);
        if (i < 0) i = 0;
        return order[(i + 1) % order.length];
    }

    function bindAudio() {
        if ($("aud-toggle")) {
            $("aud-toggle").onclick = function () {
                if (!AUD) return;
                AUD.setPref("mute", !AUD.state().mute);
                if (!AUD.state().mute) sfx("confirm");
                paintAudBadge();
                if (PANEL === "audio") paintAudio();
            };
        }
        if ($("aud-mute")) {
            $("aud-mute").onclick = function () {
                if (!AUD) return;
                AUD.setPref("mute", !AUD.state().mute);
                if (!AUD.state().mute) sfx("confirm");
                paintAudio();
            };
        }
        if ($("aud-voice")) {
            $("aud-voice").onclick = function () {
                if (!AUD) return;
                AUD.setPref("voice", !AUD.state().voice);
                paintAudio();
                if (AUD.state().voice) speak("Voice enabled.");
            };
        }
        if ($("aud-fx")) {
            $("aud-fx").onclick = function () {
                if (!AUD) return;
                AUD.setPref("fx", !AUD.state().fx);
                paintAudio();
                speak("Filter " + (AUD.state().fx ? "engaged." : "disengaged."));
            };
        }
        if ($("aud-route")) {
            $("aud-route").onclick = function () {
                if (!AUD) return;
                AUD.setPref("route", AUD.state().route === "speaker" ? "browser" : "speaker");
                paintAudio();
                speak("Audio routed.");
            };
        }
        if ($("aud-vsel")) {
            $("aud-vsel").onclick = function () {
                if (!AUD) return;
                AUD.setPref("engine_voice", cycleVoice());
                paintAudio();
                speak("Voice selected.");
            };
        }
        if ($("aud-test")) {
            $("aud-test").onclick = function () {
                if (!AUD) return;
                $("aud-test").textContent = "TESTING…";
                toast("Playing every tone", "quiet");
                AUD.selftest(function (res) {
                    $("aud-test").textContent = "SELF TEST";
                    paintAudio();
                    toast(res.pass + "/" + res.total + " tones played", "quiet");
                    if (res.pass === res.total) speak("Audio systems nominal.");
                });
            };
        }
        if ($("aud-speak")) {
            $("aud-speak").onclick = function () {
                var box = $("aud-say");
                var text = box ? box.value : "";
                if (!text) {
                    toast("Enter a line", "bad");
                    return;
                }
                sfx("ack");
                speak(text);
            };
        }
        if ($("aud-say")) {
            $("aud-say").onkeydown = function (e) {
                var ev = e || window.event;
                if ((ev.keyCode || ev.which) === 13) {
                    if ($("aud-speak")) $("aud-speak").onclick();
                    if (ev.preventDefault) ev.preventDefault();
                    return false;
                }
            };
        }
    }

    function closest(el, attr) {
        while (el && el !== document) {
            if (el.getAttribute && el.getAttribute(attr) !== null) return el;
            el = el.parentNode;
        }
        return null;
    }

    function onClick(e) {
        var t = e.target || e.srcElement;
        var node;
        if (held) {
            held = false;
            return;
        }
        node = closest(t, "data-tone");
        if (node) {
            if (AUD) AUD.play(node.getAttribute("data-tone"));
            return;
        }
        node = closest(t, "data-say");
        if (node) {
            sfx("ack");
            speak(node.getAttribute("data-say"));
            return;
        }
        node = closest(t, "data-cat");
        if (node) {
            sfx("tap");
            CAT = node.getAttribute("data-cat") || "";
            paintPrograms();
            return;
        }
        node = closest(t, "data-panel");
        if (node && !node.getAttribute("data-open")) {
            showPanel(node.getAttribute("data-panel"));
            return;
        }
        node = closest(t, "data-open");
        if (node) {
            tapApp(node.getAttribute("data-open"));
            return;
        }
        node = closest(t, "data-root");
        if (node) {
            sfx("tap");
            FILE_ROOT = node.getAttribute("data-root");
            FILE_PATH = "";
            OPEN_FILE = "";
            SELECTED = "";
            loadRoots();
            return;
        }
        node = closest(t, "data-up");
        if (node) {
            sfx("tap");
            FILE_PATH = parentPath(FILE_PATH);
            SELECTED = "";
            loadFiles();
            return;
        }
        node = closest(t, "data-dir");
        if (node) {
            sfx("tap");
            SELECTED = node.getAttribute("data-dir");
            FILE_PATH = joinPath(FILE_PATH, SELECTED);
            SELECTED = "";
            loadFiles();
            return;
        }
        node = closest(t, "data-file");
        if (node) {
            sfx("tap");
            SELECTED = node.getAttribute("data-file");
            openFile(SELECTED);
        }
    }

    function bindHold() {
        document.ontouchstart = function (e) {
            var node = closest(e.target || e.srcElement, "data-open");
            held = false;
            if (holdT) clearTimeout(holdT);
            if (!node) return;
            holdT = setTimeout(function () {
                held = true;
                stopApp(node.getAttribute("data-open"));
            }, 520);
        };
        document.ontouchend = function () {
            if (holdT) clearTimeout(holdT);
            holdT = null;
        };
        document.ontouchmove = function () {
            if (holdT) clearTimeout(holdT);
            holdT = null;
        };
    }

    function bind() {
        document.onclick = onClick;
        bindHold();
        if ($("q")) $("q").onkeyup = function () { paintPrograms(); };
        if ($("btn-save")) $("btn-save").onclick = saveFile;
        if ($("btn-new")) $("btn-new").onclick = newFile;
        if ($("btn-mkdir")) $("btn-mkdir").onclick = mkdir;
        if ($("btn-delete")) $("btn-delete").onclick = deleteSelected;
        if ($("btn-back")) $("btn-back").onclick = function () { showFileEdit(false); loadFiles(); };
        if ($("btn-note")) $("btn-note").onclick = addNote;
        if ($("btn-ask")) $("btn-ask").onclick = askComputer;
        if ($("ai-q")) {
            $("ai-q").onkeydown = function (e) {
                var ev = e || window.event;
                if ((ev.keyCode || ev.which) === 13) {
                    askComputer();
                    if (ev.preventDefault) ev.preventDefault();
                    return false;
                }
            };
        }
        if ($("btn-full")) {
            $("btn-full").onclick = function () {
                if (OPEN_APP) window.location.href = "http://127.0.0.1:" + OPEN_APP.port + "/";
            };
        }
        if ($("btn-close-ws")) {
            $("btn-close-ws").onclick = function () {
                var frame = $("ws");
                if (frame) frame.src = "about:blank";
                OPEN_APP = null;
                showPanel("access");
            };
        }
        window.onresize = sizeFill;
    }

    /* Star Trek 60th Anniversary splash dismissal */
    function dismissTrek60() {
        var overlay = $("trek60");
        if (overlay && !overlay.classList.contains("hidden")) {
            overlay.classList.add("hidden");
            if (AUD) {
                AUD.init(function () {
                    paintAudBadge();
                    sfx("boot");
                    speak("LCARS online. Live long and prosper.");
                    if (PANEL === "audio") paintAudio();
                });
            }
        }
    }

    tickClock();
    setInterval(tickClock, 15000);
    bind();
    bindAudio();
    sizeFill();
    loadStatus();
    loadSystems();
    setInterval(loadStatus, 8000);

    /* If no splash overlay, init audio immediately */
    if (!$("trek60")) {
        if (AUD) {
            AUD.init(function () {
                paintAudBadge();
                sfx("boot");
                if (PANEL === "audio") paintAudio();
            });
        }
    } else {
        /* Splash present — wait for tap to init audio (WebKit requirement) */
        $("trek60").onclick = dismissTrek60;
    }
})();
