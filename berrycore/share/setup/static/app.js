/* BerryCore setup — ES5 */
(function () {
    "use strict";
    function $(id) { return document.getElementById(id); }
    function esc(s) {
        return String(s || "").replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
    }
    function xhr(method, url, body, cb) {
        var req = new XMLHttpRequest();
        req.open(method, url, true);
        req.timeout = 25000;
        if (body) req.setRequestHeader("Content-Type", "application/json");
        req.onreadystatechange = function () {
            if (req.readyState !== 4) return;
            var data = null;
            try { data = JSON.parse(req.responseText); } catch (e) {}
            if (cb) cb(req.status, data);
        };
        req.send(body || null);
    }

    var ALL = [];
    var query = "";
    var cat = "";
    var runFilter = "";
    var watch = null;

    function hay(a) {
        return [
            a.name, a.blurb, a.cmd, a.bin, a.qpkg, a.also, a.cat,
            String(a.port), a.id
        ].join(" ").toLowerCase();
    }

    function cats() {
        var seen = {}, out = [], i, c;
        for (i = 0; i < ALL.length; i++) {
            c = ALL[i].cat || "Other";
            if (!seen[c]) {
                seen[c] = 1;
                out.push(c);
            }
        }
        out.sort();
        return out;
    }

    function filtered() {
        var q = query.toLowerCase();
        var out = [], i, a;
        for (i = 0; i < ALL.length; i++) {
            a = ALL[i];
            if (cat && (a.cat || "Other") !== cat) continue;
            if (runFilter === "up" && !a.up) continue;
            if (runFilter === "down" && a.up) continue;
            if (q && hay(a).indexOf(q) === -1) continue;
            out.push(a);
        }
        out.sort(function (x, y) {
            if (x.up !== y.up) return x.up ? -1 : 1;
            return String(x.name).localeCompare(String(y.name));
        });
        return out;
    }

    function renderChips() {
        var el = $("cats");
        if (!el) return;
        var list = cats();
        var html = '<span class="chip' + (cat ? "" : " on") + '" data-cat="">All</span>';
        var i;
        for (i = 0; i < list.length; i++) {
                html += '<span class="chip' + (cat === list[i] ? " on" : "") + '" data-cat="' + esc(list[i]) + '">' + esc(list[i]) + "</span>";
        }
        html += '<span class="chip' + (runFilter === "up" ? " on" : "") + '" data-run="up">Running</span>';
        html += '<span class="chip' + (runFilter === "down" ? " on" : "") + '" data-run="down">Stopped</span>';
        el.innerHTML = html;
        var nodes = el.getElementsByClassName("chip");
        for (i = 0; i < nodes.length; i++) {
            nodes[i].onclick = function () {
                if (this.getAttribute("data-run") !== null) {
                    runFilter = this.getAttribute("data-run") || "";
                    if (this.className.indexOf(" on") !== -1 && runFilter) runFilter = "";
                } else {
                    cat = this.getAttribute("data-cat") || "";
                }
                paint();
            };
        }
    }

    function render(apps) {
        var html = "", i, a, letters, running = 0, kind, label;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].up) running += 1;
        }
        if ($("count")) {
            $("count").textContent = running + " running · " + (ALL.length - running) + " stopped · " + apps.length + " shown";
        }
        for (i = 0; i < apps.length; i++) {
            a = apps[i];
            letters = a.letters || (a.name || "?").substring(0, 2).toUpperCase();
            if (a.pending === "start") {
                kind = "busy";
                label = "Starting";
            } else if (a.pending === "stop") {
                kind = "busy";
                label = "Stopping";
            } else if (a.up) {
                kind = "run";
                label = "Running";
            } else if (a.has_bin) {
                kind = "off";
                label = "Stopped";
            } else {
                kind = "miss";
                label = "Not installed";
            }
            html += '<div class="app' + (a.up && !a.pending ? " up" : "") + (a.pending ? " wait" : "") + '">';
            html += '<div class="status ' + kind + '"><span class="lamp"></span>' + label + "</div>";
            html += '<img src="/icon/' + esc(a.id) + '.png" alt="" onerror="this.style.display=\'none\';this.nextSibling.style.display=\'block\'">';
            html += '<div class="mark-fallback" style="display:none">' + esc(letters) + "</div>";
            html += '<div class="meta">';
            html += '<p class="cat">' + esc(a.cat || "App") + "</p>";
            html += "<h3>" + (a.up && !a.pending ? '<span class="live-dot"></span>' : "") + esc(a.name) + "</h3>";
            html += '<div class="sub">:' + a.port;
            if (a.cmd) html += " · <code>" + esc(a.cmd) + "</code>";
            html += "</div></div>";
            if (a.blurb) html += '<p class="blurb">' + esc(a.blurb) + "</p>";
            html += '<div class="row">';
            if (a.pending) {
                html += '<span class="muted">Working…</span>';
            } else if (a.up) {
                html += '<button type="button" class="btn ghost tiny wide stop-one" data-id="' + esc(a.id) + '">Stop</button>';
                html += '<a class="btn primary tiny wide" href="http://127.0.0.1:' + a.port + '/">Open</a>';
            } else if (a.has_bin) {
                html += '<button type="button" class="btn primary tiny wide start-one" data-id="' + esc(a.id) + '">Start</button>';
            } else if (a.qpkg) {
                html += '<a class="btn ghost tiny wide" href="/packages">Packages</a>';
            }
            html += '<a class="btn ghost tiny" href="/pin/' + esc(a.id) + '">Pin</a>';
            html += "</div></div>";
        }
        if (!apps.length) html = '<p class="muted">No apps match.</p>';
        $("grid").innerHTML = html;
        bindToggles();
    }

    function findApp(id) {
        var i;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].id === id) return ALL[i];
        }
        return null;
    }

    function merge(apps) {
        var keep = {}, i, id, a;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].pending) keep[ALL[i].id] = ALL[i].pending;
        }
        ALL = apps;
        for (i = 0; i < ALL.length; i++) {
            a = ALL[i];
            id = a.id;
            if (!keep[id]) continue;
            if (keep[id] === "start" && a.up) continue;
            if (keep[id] === "stop" && !a.up) continue;
            a.pending = keep[id];
        }
    }

    function stopWatch() {
        if (watch) {
            clearInterval(watch);
            watch = null;
        }
    }

    function finish(id, kind, result) {
        var a = findApp(id);
        var up = result && typeof result.up === "boolean" ? result.up : (a && a.up);
        if (a) {
            if (typeof up === "boolean") a.up = up;
            if ((kind === "start" && a.up) || (kind === "stop" && !a.up)) {
                a.pending = "";
                stopWatch();
                if ($("note")) {
                    $("note").textContent = kind === "start" ? a.name + " is running." : a.name + " stopped.";
                }
                paint();
                return;
            }
        }
        watchUntil(id, kind);
    }

    function watchUntil(id, kind) {
        var n = 0;
        stopWatch();
        watch = setInterval(function () {
            n += 1;
            xhr("GET", "/api/status", null, function (status, data) {
                var a;
                if (status === 200 && data && data.apps) merge(data.apps);
                a = findApp(id);
                if (!a) return;
                if (kind === "start" && a.up) {
                    a.pending = "";
                    stopWatch();
                    if ($("note")) $("note").textContent = a.name + " is running.";
                } else if (kind === "stop" && !a.up) {
                    a.pending = "";
                    stopWatch();
                    if ($("note")) $("note").textContent = a.name + " stopped.";
                } else if (n >= 10) {
                    a.pending = "";
                    stopWatch();
                    if ($("note")) {
                        $("note").textContent = kind === "start"
                            ? a.name + " is still coming up — tap Start again if needed."
                            : a.name + " is still stopping.";
                    }
                }
                paint();
            });
        }, 700);
    }

    function toggle(id, kind) {
        var a = findApp(id);
        var url = kind === "start" ? "/api/start" : "/api/stop";
        if (a) a.pending = kind;
        if ($("note")) $("note").textContent = (kind === "start" ? "Starting " : "Stopping ") + (a ? a.name : id) + "…";
        paint();
        xhr("POST", url, '{"id":"' + id + '"}', function (status, data) {
            var result = data && data.results && data.results[0] ? data.results[0] : data;
            if (!data || data.status !== "ok" || (result && result.error)) {
                if (a) a.pending = "";
                if ($("note")) $("note").textContent = (result && result.error) ? result.error : (kind === "start" ? "Start failed" : "Stop failed");
                paint();
                return;
            }
            finish(id, kind, result);
        });
    }

    function bindToggles() {
        var starts = document.getElementsByClassName("start-one");
        var stops = document.getElementsByClassName("stop-one");
        var i;
        for (i = 0; i < starts.length; i++) {
            starts[i].onclick = function () { toggle(this.getAttribute("data-id"), "start"); };
        }
        for (i = 0; i < stops.length; i++) {
            stops[i].onclick = function () { toggle(this.getAttribute("data-id"), "stop"); };
        }
    }

    function paint() {
        renderChips();
        render(filtered());
    }

    function load() {
        xhr("GET", "/api/status", null, function (status, data) {
            if (status === 200 && data && data.apps) {
                merge(data.apps);
                paint();
            }
        });
    }

    if (!$("grid")) return;
    if ($("q")) {
        $("q").oninput = function () {
            query = this.value || "";
            paint();
        };
        $("q").onkeyup = function () {
            query = this.value || "";
            paint();
        };
    }
    load();
    setInterval(load, 8000);
})();
