/* Waterway Map — ES5 tile engine. Reuses imgs; no innerHTML on pan. */
window.MapView = (function() {
  var TILE = 256;
  var container, tilesEl, overlay;
  var centerLat = 40;
  var centerLon = 15;
  var zoom = 3;
  var minZoom = 2;
  var maxZoom = 18;
  var waterways = [];
  var pin = null;
  var dragging = false;
  var lastX = 0;
  var lastY = 0;
  var lastTap = 0;
  var dragDist = 0;
  var size = { w: 320, h: 240 };
  var onIdleCb = null;
  var onPickCb = null;
  var pool = {};
  var overlayDirty = true;
  var overlayShiftX = 0;
  var overlayShiftY = 0;

  function clamp(v, lo, hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
  }

  function latLonToWorld(lat, lon) {
    var scale = TILE * Math.pow(2, zoom);
    var x = (lon + 180) / 360 * scale;
    var sinLat = Math.sin(lat * Math.PI / 180);
    if (sinLat > 0.9999) sinLat = 0.9999;
    if (sinLat < -0.9999) sinLat = -0.9999;
    var y = (0.5 - Math.log((1 + sinLat) / (1 - sinLat)) / (4 * Math.PI)) * scale;
    return { x: x, y: y };
  }

  function worldToLatLon(x, y) {
    var scale = TILE * Math.pow(2, zoom);
    var lon = x / scale * 360 - 180;
    var n = Math.PI - 2 * Math.PI * y / scale;
    var lat = 180 / Math.PI * Math.atan(0.5 * (Math.exp(n) - Math.exp(-n)));
    return { lat: lat, lon: lon };
  }

  function latLonToPixel(lat, lon) {
    var w = latLonToWorld(lat, lon);
    var c = latLonToWorld(centerLat, centerLon);
    return { x: size.w / 2 + (w.x - c.x), y: size.h / 2 + (w.y - c.y) };
  }

  function pixelToLatLon(px, py) {
    var c = latLonToWorld(centerLat, centerLon);
    return worldToLatLon(c.x + (px - size.w / 2), c.y + (py - size.h / 2));
  }

  function tileUrl(z, x, y) {
    return "/api/tile/" + z + "/" + x + "/" + y + ".png";
  }

  function renderTiles(draw) {
    if (!tilesEl) return;
    var c = latLonToWorld(centerLat, centerLon);
    var tileX = Math.floor(c.x / TILE);
    var tileY = Math.floor(c.y / TILE);
    var offX = size.w / 2 - (c.x - tileX * TILE);
    var offY = size.h / 2 - (c.y - tileY * TILE);
    var cols = Math.ceil(size.w / TILE) + 2;
    var rows = Math.ceil(size.h / TILE) + 2;
    var maxTile = Math.pow(2, zoom);
    var keep = {};
    var row, col, tx, ty, key, img, left, top;
    for (row = 0; row < rows; row++) {
      for (col = 0; col < cols; col++) {
        tx = ((tileX + col - 1) % maxTile + maxTile) % maxTile;
        ty = tileY + row - 1;
        if (ty < 0 || ty >= maxTile) continue;
        key = zoom + "/" + tx + "/" + ty;
        keep[key] = 1;
        img = pool[key];
        if (!img) {
          img = document.createElement("img");
          img.className = "tile";
          img.width = TILE;
          img.height = TILE;
          img.src = tileUrl(zoom, tx, ty);
          tilesEl.appendChild(img);
          pool[key] = img;
        }
        left = Math.round(offX + col * TILE - TILE);
        top = Math.round(offY + row * TILE - TILE);
        img.style.left = left + "px";
        img.style.top = top + "px";
        img.style.display = "block";
      }
    }
    var k, n = 0, extra = [];
    for (k in pool) {
      if (!pool.hasOwnProperty(k)) continue;
      n++;
      if (!keep[k]) extra.push(k);
    }
    for (k = 0; k < extra.length; k++) {
      if (n > 64) {
        if (pool[extra[k]].parentNode) {
          pool[extra[k]].parentNode.removeChild(pool[extra[k]]);
        }
        delete pool[extra[k]];
        n--;
      } else {
        pool[extra[k]].style.display = "none";
      }
    }
    if (draw !== false) {
      resetOverlayShift();
      drawOverlay();
    }
  }

  function resetOverlayShift() {
    overlayShiftX = 0;
    overlayShiftY = 0;
    if (overlay) {
      overlay.style.left = "0px";
      overlay.style.top = "0px";
    }
  }

  function shiftOverlay(dx, dy) {
    overlayShiftX += dx;
    overlayShiftY += dy;
    if (overlay) {
      overlay.style.left = overlayShiftX + "px";
      overlay.style.top = overlayShiftY + "px";
    }
  }

  function lineWidth(kind) {
    if (kind === "river") return zoom >= 12 ? 3.5 : 2.5;
    if (kind === "canal") return 2.5;
    return 1.5;
  }

  function drawOverlay() {
    if (!overlay) return;
    var ctx = overlay.getContext("2d");
    if (!ctx) return;
    if (overlay.width !== size.w) overlay.width = size.w;
    if (overlay.height !== size.h) overlay.height = size.h;
    ctx.clearRect(0, 0, size.w, size.h);
    var i, j, p, way, coords, w, lastX, lastY;
    for (i = 0; i < waterways.length; i++) {
      way = waterways[i];
      coords = way.coords;
      if (!coords || coords.length < 2) continue;
      w = lineWidth(way.kind);
      ctx.beginPath();
      lastX = lastY = -9999;
      for (j = 0; j < coords.length; j++) {
        p = latLonToPixel(coords[j][1], coords[j][0]);
        if (j > 0 && j < coords.length - 1 && Math.abs(p.x - lastX) < 1.4 && Math.abs(p.y - lastY) < 1.4) {
          continue;
        }
        if (lastX === -9999) ctx.moveTo(p.x, p.y);
        else ctx.lineTo(p.x, p.y);
        lastX = p.x;
        lastY = p.y;
      }
      ctx.lineJoin = "round";
      ctx.lineCap = "round";
      ctx.strokeStyle = "rgba(20,40,55,0.35)";
      ctx.lineWidth = w + 1.6;
      ctx.stroke();
      ctx.strokeStyle = way.color || "#1d6fd8";
      ctx.lineWidth = w;
      ctx.stroke();
    }
    if (pin) {
      p = latLonToPixel(pin.lat, pin.lon);
      ctx.beginPath();
      ctx.arc(p.x, p.y, 7, 0, Math.PI * 2);
      ctx.fillStyle = "#ffd93d";
      ctx.fill();
      ctx.strokeStyle = "#041018";
      ctx.lineWidth = 2;
      ctx.stroke();
    }
    overlayDirty = false;
  }

  function distToSeg(px, py, ax, ay, bx, by) {
    var dx = bx - ax, dy = by - ay;
    var len2 = dx * dx + dy * dy;
    var t = 0;
    if (len2 > 0) t = ((px - ax) * dx + (py - ay) * dy) / len2;
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    dx = px - (ax + t * dx);
    dy = py - (ay + t * dy);
    return Math.sqrt(dx * dx + dy * dy);
  }

  function pickAt(px, py) {
    var best = null, bestD = 14, i, j, a, b, d, coords;
    for (i = 0; i < waterways.length; i++) {
      coords = waterways[i].coords;
      if (!coords) continue;
      for (j = 1; j < coords.length; j++) {
        a = latLonToPixel(coords[j - 1][1], coords[j - 1][0]);
        b = latLonToPixel(coords[j][1], coords[j][0]);
        d = distToSeg(px, py, a.x, a.y, b.x, b.y);
        if (d < bestD) {
          bestD = d;
          best = waterways[i];
        }
      }
    }
    return best;
  }

  function resize() {
    if (!container) return;
    size.w = container.clientWidth || 320;
    size.h = container.clientHeight || 240;
    if (size.w < 50) size.w = 320;
    if (size.h < 50) size.h = 240;
    renderTiles(true);
  }

  function panByPixels(dx, dy) {
    var c = latLonToWorld(centerLat, centerLon);
    var ll = worldToLatLon(c.x - dx, c.y - dy);
    centerLon = ll.lon;
    centerLat = clamp(ll.lat, -85, 85);
    renderTiles(false);
  }

  function finishMove() {
    resetOverlayShift();
    drawOverlay();
    if (onIdleCb) onIdleCb();
  }

  function onStart(e) {
    dragging = true;
    dragDist = 0;
    var t = e.touches ? e.touches[0] : e;
    lastX = t.clientX;
    lastY = t.clientY;
    if (e.preventDefault) e.preventDefault();
  }

  function onMove(e) {
    if (!dragging) return;
    var t = e.touches ? e.touches[0] : e;
    var dx = t.clientX - lastX;
    var dy = t.clientY - lastY;
    dragDist += Math.abs(dx) + Math.abs(dy);
    panByPixels(dx, dy);
    shiftOverlay(dx, dy);
    lastX = t.clientX;
    lastY = t.clientY;
    if (e.preventDefault) e.preventDefault();
  }

  function onEnd(e) {
    var now = new Date().getTime();
    var t = (e && e.changedTouches && e.changedTouches[0]) ? e.changedTouches[0] : e;
    if (t && now - lastTap < 280) {
      zoom = clamp(zoom + 1, minZoom, maxZoom);
      lastTap = 0;
      dragging = false;
      renderTiles(true);
      finishMove();
      return;
    }
    lastTap = now;
    if (t && onPickCb && container && dragDist < 12) {
      var r = container.getBoundingClientRect ? container.getBoundingClientRect() : { left: 0, top: 0 };
      var hit = pickAt(t.clientX - r.left, t.clientY - r.top);
      if (hit) onPickCb(hit);
    }
    dragging = false;
    if (dragDist >= 12) finishMove();
    else drawOverlay();
  }

  function bindEvents() {
    if (!container || !container.addEventListener) return;
    container.addEventListener("mousedown", onStart, false);
    container.addEventListener("mousemove", onMove, false);
    container.addEventListener("mouseup", onEnd, false);
    container.addEventListener("mouseleave", function() {
      if (dragging) {
        dragging = false;
        finishMove();
      }
    }, false);
    container.addEventListener("touchstart", onStart, false);
    container.addEventListener("touchmove", onMove, false);
    container.addEventListener("touchend", onEnd, false);
  }

  return {
    init: function(opts) {
      container = opts.container;
      tilesEl = opts.tiles;
      overlay = opts.overlay;
      if (opts.minZoom) minZoom = opts.minZoom;
      if (opts.maxZoom) maxZoom = opts.maxZoom;
      bindEvents();
      resize();
    },
    setCenter: function(lat, lon, z) {
      centerLat = lat;
      centerLon = lon;
      if (z !== undefined && z !== null) zoom = clamp(Math.round(z), minZoom, maxZoom);
      renderTiles(true);
    },
    getCenter: function() {
      return { lat: centerLat, lon: centerLon, zoom: zoom };
    },
    getBounds: function() {
      var sw = pixelToLatLon(0, size.h);
      var ne = pixelToLatLon(size.w, 0);
      return { south: sw.lat, west: sw.lon, north: ne.lat, east: ne.lon };
    },
    zoomIn: function() {
      zoom = clamp(zoom + 1, minZoom, maxZoom);
      renderTiles(true);
    },
    zoomOut: function() {
      zoom = clamp(zoom - 1, minZoom, maxZoom);
      renderTiles(true);
    },
    setWaterways: function(list) {
      waterways = list || [];
      drawOverlay();
    },
    setPin: function(lat, lon) {
      pin = (lat === null || lat === undefined) ? null : { lat: lat, lon: lon };
      drawOverlay();
    },
    getPin: function() {
      return pin;
    },
    refresh: function() { resize(); },
    onIdle: function(cb) { onIdleCb = cb; },
    onPick: function(cb) { onPickCb = cb; }
  };
})();
