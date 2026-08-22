/* BerryCore settings — ES5 */
(function () {
    "use strict";
    var THEMES = [
        { id: "aubergine", name: "Aubergine", blurb: "Official — Ubuntu dark + orchid" },
        { id: "midnight", name: "Midnight", blurb: "Near-black desk, cool lamp" },
        { id: "ember", name: "Ember", blurb: "Aubergine with Ubuntu orange" },
        { id: "paper", name: "Paper", blurb: "Light page for daytime" }
    ];

    function $(id) { return document.getElementById(id); }
    function esc(s) {
        return String(s || "").replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
    }

    function paint() {
        var cur = (window.bcTheme && window.bcTheme.current()) || "aubergine";
        var html = "", i, t;
        for (i = 0; i < THEMES.length; i++) {
            t = THEMES[i];
            html += '<button type="button" class="theme-card' + (cur === t.id ? " on" : "") + '" data-id="' + t.id + '">';
            html += '<span class="swatch sw-' + t.id + '"></span>';
            html += '<span class="theme-name">' + esc(t.name) + "</span>";
            html += '<span class="theme-blurb">' + esc(t.blurb) + "</span>";
            html += "</button>";
        }
        $("themes").innerHTML = html;
        var nodes = $("themes").getElementsByTagName("button");
        for (i = 0; i < nodes.length; i++) {
            nodes[i].onclick = function () { pick(this.getAttribute("data-id")); };
        }
    }

    function pick(id) {
        if (window.bcTheme) window.bcTheme.apply(id);
        paint();
        if ($("note")) $("note").textContent = "Applying " + id + "…";
        var req = new XMLHttpRequest();
        req.open("POST", "/api/theme", true);
        req.setRequestHeader("Content-Type", "application/json");
        req.timeout = 8000;
        req.onreadystatechange = function () {
            if (req.readyState !== 4) return;
            var data = null;
            try { data = JSON.parse(req.responseText); } catch (e) {}
            if ($("note")) {
                if (data && data.status === "ok") {
                    $("note").textContent = "Theme saved. Reopen Term49 for the terminal colors.";
                } else {
                    $("note").textContent = "Hub theme applied. Term49 file was not written.";
                }
            }
        };
        req.send('{"theme":"' + id + '"}');
    }

    if ($("themes")) paint();
})();
