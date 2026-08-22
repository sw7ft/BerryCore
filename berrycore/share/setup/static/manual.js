/* BerryCore manual — ES5 copy helper */
(function () {
    "use strict";
    function copyText(text, btn) {
        var ta = document.createElement("textarea");
        ta.value = text;
        ta.style.position = "fixed";
        ta.style.left = "-9999px";
        document.body.appendChild(ta);
        ta.select();
        var ok = false;
        try { ok = document.execCommand("copy"); } catch (e) {}
        document.body.removeChild(ta);
        if (btn) {
            var label = btn.textContent;
            btn.textContent = ok ? "Copied" : label;
            setTimeout(function () { btn.textContent = label; }, 1400);
        }
    }
    var nodes = document.getElementsByClassName("copy-btn");
    var i;
    for (i = 0; i < nodes.length; i++) {
        nodes[i].onclick = function () {
            copyText(this.getAttribute("data-copy") || "", this);
        };
    }
})();
