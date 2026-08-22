/* BerryCore hub theme — ES5 */
(function () {
    "use strict";
    var KEY = "bc-theme";
    function current() {
        try { return localStorage.getItem(KEY) || ""; } catch (e) { return ""; }
    }
    function remember(name) {
        try { localStorage.setItem(KEY, name); } catch (e) {}
    }
    function apply(name) {
        var b = document.body;
        if (!b) return;
        b.className = String(b.className || "").replace(/\s*th-\w+/g, "");
        if (name && name !== "aubergine") b.className += (b.className ? " " : "") + "th-" + name;
        remember(name || "aubergine");
    }
    window.bcTheme = { apply: apply, current: current, remember: remember };
    apply(current() || "aubergine");
    try {
        var req = new XMLHttpRequest();
        req.open("GET", "/api/theme", true);
        req.timeout = 4000;
        req.onreadystatechange = function () {
            if (req.readyState !== 4 || req.status !== 200) return;
            var data = null;
            try { data = JSON.parse(req.responseText); } catch (e) {}
            if (data && data.theme && data.theme !== current()) apply(data.theme);
        };
        req.send(null);
    } catch (e) {}
})();
