/* Waterway Map — ES5 UI for berry-browser */
(function() {
  var map = null;
  var timer = null;
  var hashTimer = null;
  var allWays = [];
  var minKm = 0;
  var writingHash = false;
  var lastResults = [];
  var lastFetch = null;
  var fetchGen = 0;

  function $(id) { return document.getElementById(id); }

  function escapeHtml(t) {
    if (!t) return "";
    return String(t)
      .replace(/&/g, "&amp;")
      .replace(/</g, "&lt;")
      .replace(/>/g, "&gt;")
      .replace(/"/g, "&quot;");
  }

  function xhrGet(url, cb) {
    var req = new XMLHttpRequest();
    req.open("GET", url, true);
    try { req.timeout = 28000; } catch (e) {}
    req.onreadystatechange = function() {
      if (req.readyState !== 4) return;
      var data = null;
      try { data = JSON.parse(req.responseText); } catch (err) {}
      cb(req.status, data);
    };
    req.onerror = function() { cb(0, null); };
    req.ontimeout = function() { cb(0, null); };
    req.send();
  }

  function parseHash() {
    var h = (location.hash || "").replace(/^#/, "");
    var m = h.match(/^map=([\d.]+)\/(-?[\d.]+)\/(-?[\d.]+)/);
    if (!m) return null;
    return { zoom: parseFloat(m[1]), lat: parseFloat(m[2]), lon: parseFloat(m[3]) };
  }

  function saveView(lat, lon, z, label) {
    try {
      if (window.localStorage) {
        localStorage.setItem("ww_view", JSON.stringify({
          lat: lat, lon: lon, zoom: z, label: label || ""
        }));
      }
    } catch (e) {}
  }

  function loadView() {
    try {
      if (!window.localStorage) return null;
      var raw = localStorage.getItem("ww_view");
      if (!raw) return null;
      var o = JSON.parse(raw);
      if (typeof o.lat !== "number" || typeof o.lon !== "number") return null;
      return o;
    } catch (e) { return null; }
  }

  function writeHash() {
    if (!map) return;
    var c = map.getCenter();
    saveView(c.lat, c.lon, c.zoom);
    var next = "map=" + c.zoom + "/" + c.lat.toFixed(4) + "/" + c.lon.toFixed(4);
    if (location.hash.replace(/^#/, "") === next) return;
    writingHash = true;
    try {
      if (window.history && history.replaceState) {
        history.replaceState(null, "", "#" + next);
      }
    } catch (e) {}
    setTimeout(function() { writingHash = false; }, 200);
  }

  function types() {
    var out = [];
    if ($("tRiver").checked) out.push("river");
    if ($("tCanal").checked) out.push("canal");
    if ($("tStream").checked) out.push("stream");
    if ($("tDrain").checked) out.push("drain");
    return out.join(",") || "river";
  }

  function applyFilter() {
    var km = parseFloat($("minKm").value);
    if (isNaN(km) || km < 0) km = 0;
    minKm = km;
    var shown = [];
    var i;
    for (i = 0; i < allWays.length; i++) {
      if ((allWays[i].km || 0) >= minKm) shown.push(allWays[i]);
    }
    map.setWaterways(shown);
    setChip(shown.length ? (shown.length + " waterways") : "No waterways in view");
  }

  function setChip(msg, name) {
    var el = $("chip");
    if (!el) return;
    if (name) el.innerHTML = "<b>" + escapeHtml(name) + "</b> · " + escapeHtml(msg);
    else el.innerHTML = '<span class="muted">' + escapeHtml(msg) + "</span>";
  }

  function hideHits() {
    $("hits").style.display = "none";
    $("hits").innerHTML = "";
  }

  function markHit(idx) {
    var box = $("hits");
    var nodes = box.childNodes;
    var i;
    for (i = 0; i < nodes.length; i++) {
      if (!nodes[i].className) continue;
      nodes[i].className = (i === idx) ? "item on" : "item";
    }
  }

  function covers(prev, next) {
    if (!prev) return false;
    return prev.south <= next.south && prev.west <= next.west &&
      prev.north >= next.north && prev.east >= next.east;
  }

  function padBounds(b, pad) {
    var dh = (b.north - b.south) * pad;
    var dw = (b.east - b.west) * pad;
    return {
      south: b.south - dh, west: b.west - dw,
      north: b.north + dh, east: b.east + dw
    };
  }

  function loadWays(force) {
    if (!map) return;
    var c = map.getCenter();
    if (c.zoom < 8) {
      allWays = [];
      map.setWaterways([]);
      lastFetch = null;
      setChip("Zoom in to load OSM waterways");
      return;
    }
    var b = map.getBounds();
    var t = types();
    if (!force && lastFetch && lastFetch.zoom === c.zoom && lastFetch.types === t && covers(lastFetch.b, b)) {
      return;
    }
    var q = padBounds(b, 0.2);
    var url = "/api/waterways?south=" + q.south + "&west=" + q.west +
      "&north=" + q.north + "&east=" + q.east +
      "&zoom=" + c.zoom + "&types=" + encodeURIComponent(t);
    var gen = ++fetchGen;
    if (!allWays.length) setChip("Loading waterways...");
    xhrGet(url, function(st, obj) {
      if (gen !== fetchGen) return;
      if (st !== 200 || !obj || obj.status !== "ok") {
        if (!allWays.length) {
          setChip((obj && obj.error) ? obj.error : "Overpass failed — try again");
        }
        return;
      }
      lastFetch = { zoom: c.zoom, types: t, b: q };
      allWays = obj.waterways || [];
      applyFilter();
    });
  }

  function applyPrefetch(obj, t, z) {
    if (!obj || obj.status !== "ok" || !obj.waterways) return false;
    lastFetch = {
      zoom: obj.zoom || z,
      types: t,
      b: obj.bounds || { south: -90, west: -180, north: 90, east: 180 }
    };
    allWays = obj.waterways;
    applyFilter();
    return true;
  }

  function prefetch(lat, lon, z) {
    var t = types();
    xhrGet(
      "/api/prefetch?lat=" + lat + "&lon=" + lon + "&zoom=" + z +
        "&types=" + encodeURIComponent(t),
      function(st, obj) {
        if (st === 200) applyPrefetch(obj, t, z);
      }
    );
  }

  function scheduleLoad() {
    hideHits();
    if (hashTimer) clearTimeout(hashTimer);
    hashTimer = setTimeout(writeHash, 400);
    if (timer) clearTimeout(timer);
    timer = setTimeout(function() { loadWays(false); }, 280);
  }

  function goTo(lat, lon, z, label, keepHits) {
    lat = parseFloat(lat);
    lon = parseFloat(lon);
    z = parseInt(z, 10);
    if (isNaN(lat) || isNaN(lon)) return;
    if (isNaN(z)) z = 11;
    if (!keepHits) hideHits();
    hideSheet();
    if (map.setPin) map.setPin(lat, lon);
    map.setCenter(lat, lon, z);
    saveView(lat, lon, z, label);
    writeHash();
    if (label) setChip("Showing " + label);
    lastFetch = null;
    prefetch(lat, lon, z);
    if (timer) clearTimeout(timer);
    timer = setTimeout(function() { loadWays(false); }, 500);
  }

  function pickResult(idx, keepHits) {
    var r = lastResults[idx];
    if (!r) return;
    if (keepHits && lastResults.length > 1) {
      markHit(idx);
      goTo(r.lat, r.lon, 12, r.short_name || r.name, true);
    } else {
      goTo(r.lat, r.lon, 12, r.short_name || r.name, false);
    }
  }

  function showResults(results) {
    var box = $("hits");
    lastResults = results || [];
    if (!lastResults.length) {
      box.innerHTML = '<div class="empty">No place found</div>';
      box.style.display = "block";
      setChip("No place found");
      return;
    }
    var html = "";
    var i, r;
    for (i = 0; i < lastResults.length; i++) {
      r = lastResults[i];
      html += '<div class="item" data-idx="' + i + '">';
      html += '<div class="t">' + escapeHtml(r.short_name || r.name) + "</div>";
      html += '<div class="m">' + escapeHtml(r.name) + "</div></div>";
    }
    box.innerHTML = html;
    box.style.display = "block";
    setChip(lastResults.length + " places — tap one");
  }

  function search() {
    var q = ($("q").value || "").replace(/^\s+|\s+$/g, "");
    if (!q) {
      setChip("Type a place or river");
      return false;
    }
    setChip("Searching...");
    $("hits").style.display = "block";
    $("hits").innerHTML = '<div class="empty">Searching...</div>';
    xhrGet("/api/geocode?q=" + encodeURIComponent(q) + "&limit=8", function(st, obj) {
      if (st !== 200 || !obj || obj.status !== "ok") {
        showResults([]);
        setChip("Search failed — try again");
        return;
      }
      var list = obj.results || [];
      showResults(list);
      if (list.length) pickResult(0, true);
    });
    return false;
  }

  function showSheet() {
    $("scrim").className = "scrim on";
    $("sheet").className = "sheet on";
  }
  function hideSheet() {
    $("scrim").className = "scrim";
    $("sheet").className = "sheet";
  }

  function boot() {
    map = window.MapView;
    map.init({
      container: $("map"),
      tiles: $("tiles"),
      overlay: $("overlay")
    });
    var start = parseHash() || loadView() || { zoom: 3, lat: 40, lon: 15 };
    map.setCenter(start.lat, start.lon, start.zoom);
    if (start.label) setChip("Showing " + start.label);
    map.onIdle(scheduleLoad);
    map.onPick(function(way) {
      setChip((way.kind || "waterway") + " · " + (way.km || 0) + " km", way.name);
    });

    $("btnMenu").onclick = function() {
      if ($("sheet").className.indexOf("on") >= 0) hideSheet();
      else showSheet();
    };
    $("scrim").onclick = hideSheet;
    $("zoomIn").onclick = function() { map.zoomIn(); scheduleLoad(); };
    $("zoomOut").onclick = function() { map.zoomOut(); scheduleLoad(); };
    $("searchForm").onsubmit = function(e) {
      e = e || window.event;
      if (e.preventDefault) e.preventDefault();
      if (e.stopPropagation) e.stopPropagation();
      search();
      return false;
    };
    $("btnSearch").onclick = function(e) {
      e = e || window.event;
      if (e.preventDefault) e.preventDefault();
      search();
      return false;
    };
    $("btnClear").onclick = function() {
      $("q").value = "";
      hideHits();
      if (map.setPin) map.setPin(null);
      setChip("Search a place, then zoom in for rivers");
    };
    $("btnPin").onclick = function() {
      var p = map.getPin ? map.getPin() : null;
      if (!p) {
        setChip("Search a place first");
        return;
      }
      map.setCenter(p.lat, p.lon);
      writeHash();
      loadWays(false);
    };
    function hitTap(e) {
      e = e || window.event;
      var t = e.target || e.srcElement;
      while (t && t !== $("hits")) {
        if (t.getAttribute && t.getAttribute("data-idx")) {
          if (e.preventDefault) e.preventDefault();
          pickResult(parseInt(t.getAttribute("data-idx"), 10));
          return false;
        }
        t = t.parentNode;
      }
    }
    $("hits").onclick = hitTap;
    if ($("hits").addEventListener) $("hits").addEventListener("touchend", hitTap, false);
    $("minKm").onchange = applyFilter;
    $("tRiver").onchange = function() { lastFetch = null; loadWays(true); };
    $("tCanal").onchange = function() { lastFetch = null; loadWays(true); };
    $("tStream").onchange = function() { lastFetch = null; loadWays(true); };
    $("tDrain").onchange = function() { lastFetch = null; loadWays(true); };
    $("jumpWorld").onclick = function() { goTo(40, 15, 3); hideSheet(); };
    $("jumpSask").onclick = function() { goTo(53.5461, -113.4938, 10); hideSheet(); };
    $("jumpNile").onclick = function() { goTo(15.6, 32.5, 6); hideSheet(); };
    $("jumpAmazon").onclick = function() { goTo(-3.1, -60.0, 6); hideSheet(); };

    if (window.addEventListener) {
      window.addEventListener("resize", function() { map.refresh(); }, false);
      window.addEventListener("hashchange", function() {
        if (writingHash) return;
        var h = parseHash();
        if (!h) return;
        var c = map.getCenter();
        if (Math.abs(c.lat - h.lat) > 0.01 || Math.abs(c.lon - h.lon) > 0.01 || c.zoom !== Math.round(h.zoom)) {
          map.setCenter(h.lat, h.lon, h.zoom);
          loadWays();
        }
      }, false);
    }
    writeHash();
    loadWays();
  }

  if (document.readyState === "complete" || document.readyState === "interactive") boot();
  else if (document.addEventListener) document.addEventListener("DOMContentLoaded", boot, false);
  else window.onload = boot;
})();
