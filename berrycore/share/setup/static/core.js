/* BerryCore core inventory — ES5 table */
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
    var state = "core";
    var sortKey = "name";
    var sortDir = 1;

    function hay(p) {
        return [p.name, p.desc, p.cat].join(" ").toLowerCase();
    }

    function sortVal(p, key) {
        if (key === "cat") return String(p.cat || "").toLowerCase();
        if (key === "st") {
            if (p.present) return 0;
            return 1;
        }
        return String(p.name || "").toLowerCase();
    }

    function cats() {
        var seen = {}, out = [], i, c;
        for (i = 0; i < ALL.length; i++) {
            if (state === "core" && !ALL[i].core) continue;
            if (state === "port" && !ALL[i].port) continue;
            if (state === "extra" && !ALL[i].extra) continue;
            c = ALL[i].cat || "util";
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
        var out = [], i, p;
        for (i = 0; i < ALL.length; i++) {
            p = ALL[i];
            if (state === "core" && !p.core) continue;
            if (state === "port" && !p.port) continue;
            if (state === "extra" && !p.extra) continue;
            if (state === "in" && !p.present) continue;
            if (state === "out" && p.present) continue;
            if (cat && (p.cat || "util") !== cat) continue;
            if (q && hay(p).indexOf(q) === -1) continue;
            out.push(p);
        }
        out.sort(function (a, b) {
            var av = sortVal(a, sortKey);
            var bv = sortVal(b, sortKey);
            if (av < bv) return -1 * sortDir;
            if (av > bv) return 1 * sortDir;
            return String(a.name).localeCompare(String(b.name));
        });
        return out;
    }

    function mark(key) {
        if (sortKey !== key) return "";
        return sortDir > 0 ? " ▲" : " ▼";
    }

    function th(key, label, cls) {
        return '<th class="' + cls + (sortKey === key ? " sort" : "") + '" data-sort="' + key + '">' + label + mark(key) + "</th>";
    }

    function renderChips() {
        var el = $("cats");
        if (!el) return;
        var list = cats();
        var html = "";
        function chip(val, label, attr) {
            var on = state === val && !cat;
            if (attr === "cat") on = cat === val;
            html += '<span class="chip' + (on ? " on" : "") + '" data-state="' + (attr === "cat" ? "" : esc(val)) + '" data-cat="' + (attr === "cat" ? esc(val) : "") + '">' + esc(label) + "</span>";
        }
        chip("core", "Default");
        chip("in", "Present");
        chip("out", "Missing");
        chip("port", "Ports");
        chip("extra", "Extra");
        chip("", "All");
        var i;
        for (i = 0; i < list.length; i++) {
            chip(list[i], list[i], "cat");
        }
        el.innerHTML = html;
        var nodes = el.getElementsByClassName("chip");
        for (i = 0; i < nodes.length; i++) {
            nodes[i].onclick = function () {
                var nextCat = this.getAttribute("data-cat") || "";
                var nextState = this.getAttribute("data-state");
                if (nextCat) {
                    cat = (cat === nextCat) ? "" : nextCat;
                } else {
                    state = nextState || "";
                    cat = "";
                }
                paint();
            };
        }
    }

    function render(list) {
        var core = 0, coreIn = 0, i, p, st, label, row, act;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].core) {
                core += 1;
                if (ALL[i].present) coreIn += 1;
            }
        }
        if ($("count")) {
            $("count").textContent = coreIn + " / " + core + " default present · " + list.length + " shown";
        }
        if (!list.length) {
            $("grid").innerHTML = '<p class="muted">No tools match.</p>';
            return;
        }
        var html = '<div class="pkg-wrap"><table class="pkg-table core-table"><thead><tr>';
        html += th("name", "Binary", "c-name");
        html += th("cat", "Cat", "c-cat");
        html += th("st", "Status", "c-st");
        html += '<th class="c-act"></th></tr></thead><tbody>';
        for (i = 0; i < list.length; i++) {
            p = list[i];
            if (p.present) {
                st = "in";
                label = "In";
                row = "in";
                act = "";
            } else {
                st = "out";
                label = "—";
                row = "";
                act = p.port ? '<a class="btn ghost tiny" href="/packages">Get</a>' : "";
            }
            html += '<tr class="' + row + '">';
            html += '<td class="c-name"><span class="pkg-name">' + esc(p.name) + "</span>";
            html += '<span class="pkg-desc">' + esc(p.desc || "") + "</span></td>";
            html += '<td class="c-cat">' + esc(p.cat || "") + "</td>";
            html += '<td class="c-st"><span class="pkg-st ' + st + '"><span class="dot"></span>' + label + "</span></td>";
            html += '<td class="c-act">' + act + "</td>";
            html += "</tr>";
        }
        html += "</tbody></table></div>";
        $("grid").innerHTML = html;
        bindSort();
    }

    function bindSort() {
        var nodes = document.getElementsByTagName("th");
        var i;
        for (i = 0; i < nodes.length; i++) {
            if (!nodes[i].getAttribute("data-sort")) continue;
            nodes[i].onclick = function () {
                var key = this.getAttribute("data-sort");
                if (sortKey === key) sortDir = -sortDir;
                else {
                    sortKey = key;
                    sortDir = 1;
                }
                paint();
            };
        }
    }

    function paint() {
        renderChips();
        render(filtered());
    }

    function load() {
        xhr("GET", "/api/core", null, function (status, data) {
            if (status === 200 && data && data.bins) {
                ALL = data.bins;
                paint();
            } else if ($("note") && !ALL.length) {
                $("note").textContent = "Could not load the core catalog.";
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
})();
