/* BerryCore packages — ES5 table */
(function () {
    "use strict";
    function $(id) { return document.getElementById(id); }
    function esc(s) {
        return String(s || "").replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
    }
    function xhr(method, url, body, cb) {
        var req = new XMLHttpRequest();
        req.open(method, url, true);
        req.timeout = 120000;
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
    var state = "";
    var sortKey = "name";
    var sortDir = 1;

    function hay(p) {
        return [p.name, p.desc, p.cat, p.zip, p.replaces, p.ver, p.size].join(" ").toLowerCase();
    }

    function sortVal(p, key) {
        if (key === "cat") return String(p.cat || "").toLowerCase();
        if (key === "ver") return String(p.ver || "").toLowerCase();
        if (key === "st") {
            if (p.busy) return 0;
            if (p.installed) return 1;
            return 2;
        }
        return String(p.name || "").toLowerCase();
    }

    function cats() {
        var seen = {}, out = [], i, c;
        for (i = 0; i < ALL.length; i++) {
            c = ALL[i].cat || "other";
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
            if (cat && (p.cat || "other") !== cat) continue;
            if (state === "in" && !p.installed) continue;
            if (state === "out" && p.installed) continue;
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
        var html = '<span class="chip' + (cat || state ? "" : " on") + '" data-cat="" data-state="">All</span>';
        html += '<span class="chip' + (state === "in" ? " on" : "") + '" data-state="in">Installed</span>';
        html += '<span class="chip' + (state === "out" ? " on" : "") + '" data-state="out">Available</span>';
        var i;
        for (i = 0; i < list.length; i++) {
            html += '<span class="chip' + (cat === list[i] ? " on" : "") + '" data-cat="' + esc(list[i]) + '">' + esc(list[i]) + "</span>";
        }
        el.innerHTML = html;
        var nodes = el.getElementsByClassName("chip");
        for (i = 0; i < nodes.length; i++) {
            nodes[i].onclick = function () {
                if (this.getAttribute("data-state") !== null && !this.getAttribute("data-cat")) {
                    state = this.getAttribute("data-state") || "";
                    if (this.className.indexOf(" on") !== -1 && state) state = "";
                    cat = "";
                } else {
                    cat = this.getAttribute("data-cat") || "";
                    if (!cat) state = "";
                }
                paint();
            };
        }
    }

    function render(list) {
        var inst = 0, busy = 0, i, p, st, label, row, act;
        for (i = 0; i < ALL.length; i++) {
            if (ALL[i].installed) inst += 1;
            if (ALL[i].busy) busy += 1;
        }
        if ($("count")) {
            $("count").textContent = inst + " installed · " + (ALL.length - inst) + " available · " + list.length + " shown";
            if (busy) $("count").textContent += " · " + busy + " installing";
        }
        if (!list.length) {
            $("grid").innerHTML = '<p class="muted">No packages match.</p>';
            return;
        }
        var html = '<div class="pkg-wrap"><table class="pkg-table"><thead><tr>';
        html += th("name", "Package", "c-name");
        html += th("cat", "Cat", "c-cat");
        html += th("ver", "Ver", "c-ver");
        html += th("st", "Status", "c-st");
        html += '<th class="c-act"></th></tr></thead><tbody>';
        for (i = 0; i < list.length; i++) {
            p = list[i];
            if (p.busy) {
                st = "busy";
                label = "Busy";
                act = '<span class="muted">…</span>';
                row = "busy";
            } else if (p.installed) {
                st = "in";
                label = "In";
                act = '<button type="button" class="btn ghost tiny inst-one" data-name="' + esc(p.name) + '">Re</button>';
                row = "in";
            } else {
                st = "out";
                label = "—";
                act = '<button type="button" class="btn primary tiny inst-one" data-name="' + esc(p.name) + '">Install</button>';
                row = "";
            }
            if (p.fail) row = (row ? row + " " : "") + "fail";
            html += '<tr class="' + row + '">';
            html += '<td class="c-name"><span class="pkg-name">' + esc(p.name);
            if (p.bundled) html += " ·";
            html += '</span><span class="pkg-desc">' + esc(p.desc || "");
            if (p.fail) html += " — " + esc(p.fail);
            html += "</span></td>";
            html += '<td class="c-cat">' + esc(p.cat || "") + "</td>";
            html += '<td class="c-ver">' + esc(p.ver || "") + "</td>";
            html += '<td class="c-st"><span class="pkg-st ' + st + '"><span class="dot"></span>' + label + "</span></td>";
            html += '<td class="c-act">' + act + "</td>";
            html += "</tr>";
        }
        html += "</tbody></table></div>";
        $("grid").innerHTML = html;
        bindSort();
        bindInstall();
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

    function bindInstall() {
        var nodes = document.getElementsByClassName("inst-one");
        var i;
        for (i = 0; i < nodes.length; i++) {
            nodes[i].onclick = function () {
                var name = this.getAttribute("data-name");
                this.disabled = true;
                $("note").textContent = "Installing " + name + "…";
                xhr("POST", "/api/pkg/install", '{"name":"' + name + '"}', function (status, data) {
                    if (data && data.status === "ok") {
                        $("note").textContent = data.already ? "Already installed." : "Install started for " + name + ".";
                    } else {
                        $("note").textContent = (data && data.error) ? data.error : "Install failed";
                    }
                    setTimeout(load, 800);
                });
            };
        }
    }

    function paint() {
        renderChips();
        render(filtered());
    }

    function load() {
        xhr("GET", "/api/packages", null, function (status, data) {
            if (status === 200 && data && data.packages) {
                ALL = data.packages;
                paint();
            } else if ($("note") && !ALL.length) {
                $("note").textContent = "Could not load package catalog.";
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
    setInterval(load, 4000);
})();
