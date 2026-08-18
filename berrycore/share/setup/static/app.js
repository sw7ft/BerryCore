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

    function hay(a) {
        return [
            a.name, a.blurb, a.cmd, a.bin, a.qpkg, a.also, a.cat,
            String(a.port), a.id
        ].join(" ").toLowerCase();
    }

    function filtered() {
        var q = query.toLowerCase();
        var out = [], i, a;
        if (!q) return ALL;
        for (i = 0; i < ALL.length; i++) {
            a = ALL[i];
            if (hay(a).indexOf(q) !== -1) out.push(a);
        }
        return out;
    }

    function render(apps) {
        var html = "", i, a, cls, state, cmd;
        for (i = 0; i < apps.length; i++) {
            a = apps[i];
            cls = a.up ? "on" : "";
            state = a.up ? "running" : (a.has_bin ? "stopped" : "not installed");
            cmd = a.cmd || a.bin;
            html += '<div class="app">';
            html += '<img src="/icon/' + esc(a.id) + '.png" alt="">';
            html += '<div class="meta"><h3>' + esc(a.name) + '</h3>';
            html += '<div class="sub"><span class="dot ' + cls + '"></span>' + state;
            html += " · :" + a.port;
            if (cmd) html += " · <code>" + esc(cmd) + "</code>";
            if (a.qpkg) html += " · qpkg " + esc(a.qpkg);
            if (a.also) html += " · also " + esc(a.also);
            html += "</div></div>";
            if (a.blurb) html += '<p class="blurb">' + esc(a.blurb) + "</p>";
            html += '<div class="row">';
            html += '<button type="button" class="btn ghost tiny start-one" data-id="' + esc(a.id) + '">Start</button>';
            html += '<a class="btn ghost tiny" href="/pin/' + esc(a.id) + '">Pin</a>';
            html += '<a class="btn primary tiny" href="http://127.0.0.1:' + a.port + '/">Open</a>';
            html += "</div></div>";
        }
        if (!apps.length) html = '<p class="muted">No apps match.</p>';
        $("grid").innerHTML = html;
        bindStarts();
    }

    function bindStarts() {
        var nodes = document.getElementsByClassName("start-one");
        var i;
        for (i = 0; i < nodes.length; i++) {
            nodes[i].onclick = function () {
                var id = this.getAttribute("data-id");
                $("note").textContent = "Starting " + id + "…";
                xhr("POST", "/api/start", '{"id":"' + id + '"}', function (status, data) {
                    $("note").textContent = (data && data.status === "ok") ? "Started." : "Start failed";
                    setTimeout(load, 900);
                });
            };
        }
    }

    function paint() {
        render(filtered());
    }

    function load() {
        xhr("GET", "/api/status", null, function (status, data) {
            if (status === 200 && data && data.apps) {
                ALL = data.apps;
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
