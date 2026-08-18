/* Stocks — ES5 ticker / research / lists / alerts for berry-browser */
(function() {
  var state = null;
  var quotes = {};
  var hits = [];
  var timer = null;
  var lastFlash = {};

  function $(id) { return document.getElementById(id); }

  function esc(t) {
    return String(t || "")
      .replace(/&/g, "&amp;").replace(/</g, "&lt;")
      .replace(/>/g, "&gt;").replace(/"/g, "&quot;");
  }

  function xhr(method, url, body, cb) {
    var req = new XMLHttpRequest();
    req.open(method, url, true);
    try { req.timeout = 28000; } catch (e) {}
    if (body) req.setRequestHeader("Content-Type", "application/json");
    req.onreadystatechange = function() {
      if (req.readyState !== 4) return;
      var data = null;
      try { data = JSON.parse(req.responseText); } catch (err) {}
      cb(req.status, data);
    };
    req.onerror = function() { cb(0, null); };
    req.ontimeout = function() { cb(0, null); };
    req.send(body ? JSON.stringify(body) : null);
  }

  function activeList() {
    var i, lst, id = state ? state.active : "watch";
    if (!state) return null;
    for (i = 0; i < state.lists.length; i++) {
      if (state.lists[i].id === id) return state.lists[i];
    }
    lst = state.lists[0];
    if (lst) state.active = lst.id;
    return lst || null;
  }

  function setChip(msg) {
    $("chip").innerHTML = '<span class="muted">' + esc(msg) + "</span>";
  }

  function cls(pct, tick) {
    if (tick === 1 || pct > 0) return "up";
    if (tick === -1 || pct < 0) return "dn";
    return "flat";
  }

  function arrow(tick, pct) {
    if (tick === 1) return "▲";
    if (tick === -1) return "▼";
    if (pct > 0) return "▲";
    if (pct < 0) return "▼";
    return "·";
  }

  function hideHits() {
    $("hits").style.display = "none";
    $("hits").innerHTML = "";
  }

  function hideSheets() {
    $("scrim").className = "scrim";
    $("sheet").className = "sheet";
    $("research").className = "sheet";
  }

  function showSheet(html) {
    $("research").className = "sheet";
    $("sheet").innerHTML = html;
    $("sheet").className = "sheet on";
    $("scrim").className = "scrim on";
  }

  function showResearch(html) {
    $("sheet").className = "sheet";
    $("research").innerHTML = html;
    $("research").className = "sheet on wide";
    $("scrim").className = "scrim on";
  }

  function save(extra) {
    var body = extra || {};
    body.lists = state.lists;
    body.active = state.active;
    body.ticks = state.ticks;
    body.alerts = state.alerts;
    body.poll = state.poll;
    body.pps = state.pps;
    xhr("POST", "/api/state", body, function(st, obj) {
      if (st === 200 && obj && obj.state) state = obj.state;
    });
  }

  function renderLists() {
    var html = "";
    var i, lst, on;
    if (!state) return;
    for (i = 0; i < state.lists.length; i++) {
      lst = state.lists[i];
      on = lst.id === state.active ? " on" : "";
      html += '<button type="button" data-list="' + esc(lst.id) + '" class="' + on + '">' +
        esc(lst.name) + "</button>";
    }
    html += '<button type="button" data-list="__new">+ List</button>';
    $("lists").innerHTML = html;
  }

  function sparkId(sym) {
    return "sk_" + String(sym).replace(/[^A-Za-z0-9]/g, "_");
  }

  function drawMini(id, values, up) {
    var c = $(id);
    if (!c || !c.getContext || !values || values.length < 2) return;
    var ctx = c.getContext("2d");
    var w = c.width = 68;
    var h = c.height = 30;
    var i, min = values[0], max = values[0], x, y;
    for (i = 0; i < values.length; i++) {
      if (values[i] < min) min = values[i];
      if (values[i] > max) max = values[i];
    }
    if (max === min) max = min + 1;
    ctx.clearRect(0, 0, w, h);
    ctx.beginPath();
    for (i = 0; i < values.length; i++) {
      x = i / (values.length - 1) * (w - 4) + 2;
      y = h - 3 - (values[i] - min) / (max - min) * (h - 6);
      if (i === 0) ctx.moveTo(x, y);
      else ctx.lineTo(x, y);
    }
    ctx.strokeStyle = up ? "#7dce6a" : "#e15b4f";
    ctx.lineWidth = 1.6;
    ctx.stroke();
  }

  function drawBoardSparks() {
    var lst = activeList();
    var i, sym, q;
    if (!lst) return;
    for (i = 0; i < lst.symbols.length; i++) {
      sym = lst.symbols[i];
      q = quotes[sym] || {};
      if (q.spark && q.spark.length > 1) {
        drawMini(sparkId(sym), q.spark, (q.pct || 0) >= 0);
      }
    }
  }

  function renderBoard() {
    var lst = activeList();
    var html = "";
    var i, sym, q, pct, tick, flash, dir, chg;
    if (!lst) {
      $("board").innerHTML = '<div class="empty-board">No list yet</div>';
      return;
    }
    for (i = 0; i < lst.symbols.length; i++) {
      sym = lst.symbols[i];
      q = quotes[sym] || {};
      pct = q.pct || 0;
      tick = q.tick || 0;
      dir = cls(pct, tick);
      flash = "";
      if (lastFlash[sym] !== tick && tick) {
        flash = tick === 1 ? " flash-up" : " flash-dn";
        lastFlash[sym] = tick;
      }
      chg = "";
      if (q.change != null) {
        chg = (q.change > 0 ? "+" : "") + Number(q.change).toFixed(2);
      }
      html += '<a class="row' + flash + '" href="#" data-sym="' + esc(sym) + '">';
      html += '<span class="rail ' + dir + '"></span>';
      html += '<div class="who"><div class="sym">' + esc(sym);
      if (state.ticks && state.ticks[sym]) html += ' <span class="bell">▲</span>';
      html += '</div><div class="nm">' + (chg ? chg + " today" : "waiting on tape") + "</div></div>";
      html += '<div class="fig"><div class="px">' +
        (q.price != null ? Number(q.price).toFixed(2) : "—") + "</div>";
      html += '<div class="pill ' + dir + '">' + arrow(tick, pct) + " ";
      html += (q.pct != null ? (q.pct > 0 ? "+" : "") + Number(q.pct).toFixed(2) + "%" : "—");
      html += "</div></div>";
      html += '<canvas class="mini" id="' + sparkId(sym) + '" width="68" height="30"></canvas>';
      html += "</a>";
    }
    if (!lst.symbols.length) {
      html = '<div class="empty-board">Add a symbol to this list</div>';
    }
    $("board").innerHTML = html;
    drawBoardSparks();
  }

  function loadState(thenQuotes) {
    xhr("GET", "/api/state", null, function(st, obj) {
      if (st !== 200 || !obj || !obj.state) {
        setChip("Could not load lists");
        return;
      }
      state = obj.state;
      quotes = obj.quotes || {};
      renderLists();
      renderBoard();
      if (thenQuotes) refreshQuotes();
      else setChip(Object.keys(quotes).length + " quotes cached");
    });
  }

  function refreshQuotes() {
    var lst = activeList();
    var symbols = lst ? lst.symbols.join(",") : "";
    setChip("Refreshing…");
    xhr("GET", "/api/quotes?symbols=" + encodeURIComponent(symbols), null, function(st, obj) {
      var i, row, n = 0;
      if (st !== 200 || !obj || obj.status !== "ok") {
        setChip((obj && obj.error) ? obj.error : "Quote fetch failed");
        return;
      }
      for (i = 0; i < (obj.quotes || []).length; i++) {
        row = obj.quotes[i];
        quotes[row.symbol] = row;
        n++;
      }
      renderBoard();
      $("asof").innerHTML = n + " names · " + (state.poll || 30) + "s";
      setChip(n ? (n + " names on the tape") : "No quotes yet");
    });
  }

  function addSymbol(sym) {
    var lst = activeList();
    if (!lst || !sym) return;
    sym = String(sym).toUpperCase();
    if (lst.symbols.indexOf(sym) < 0) lst.symbols.push(sym);
    hideHits();
    $("q").value = "";
    save();
    renderBoard();
    refreshQuotes();
  }

  function search() {
    var q = ($("q").value || "").replace(/^\s+|\s+$/g, "");
    if (!q) { setChip("Type a symbol or name"); return false; }
    if (/^[A-Za-z][A-Za-z0-9.-]{0,9}$/.test(q) && q.indexOf(" ") < 0) {
      addSymbol(q);
      return false;
    }
    $("hits").style.display = "block";
    $("hits").innerHTML = '<div class="empty">Searching…</div>';
    xhr("GET", "/api/search?q=" + encodeURIComponent(q), null, function(st, obj) {
      var html = "", i, r;
      hits = (obj && obj.results) || [];
      if (st !== 200 || !hits.length) {
        $("hits").innerHTML = '<div class="empty">No match — try the ticker</div>';
        return;
      }
      for (i = 0; i < hits.length; i++) {
        r = hits[i];
        html += '<div class="item" data-idx="' + i + '"><div class="t">' +
          esc(r.symbol) + "</div><div class=\"m\">" +
          esc(r.name) + (r.exchange ? " · " + esc(r.exchange) : "") +
          "</div></div>";
      }
      $("hits").innerHTML = html;
    });
    return false;
  }

  function drawSpark(points) {
    var c = $("spark");
    if (!c || !c.getContext || !points || points.length < 2) return;
    var ctx = c.getContext("2d");
    var w = c.width = c.clientWidth || 300;
    var h = c.height = 90;
    var i, min = points[0].p, max = points[0].p, x, y;
    for (i = 0; i < points.length; i++) {
      if (points[i].p < min) min = points[i].p;
      if (points[i].p > max) max = points[i].p;
    }
    if (max === min) max = min + 1;
    ctx.clearRect(0, 0, w, h);
    ctx.beginPath();
    for (i = 0; i < points.length; i++) {
      x = i / (points.length - 1) * (w - 8) + 4;
      y = h - 8 - (points[i].p - min) / (max - min) * (h - 16);
      if (i === 0) ctx.moveTo(x, y);
      else ctx.lineTo(x, y);
    }
    ctx.strokeStyle = points[points.length - 1].p >= points[0].p ? "#7dce6a" : "#e15b4f";
    ctx.lineWidth = 2;
    ctx.stroke();
  }

  function openResearch(sym) {
    showResearch("<h2>" + esc(sym) + "</h2><p class=\"note\">Loading research…</p>");
    xhr("GET", "/api/research?symbol=" + encodeURIComponent(sym) + "&range=5d&interval=1d", null, function(st, obj) {
      var r, html, i, n, q, onTick;
      if (st !== 200 || !obj || !obj.research) {
        showResearch("<h2>" + esc(sym) + "</h2><p class=\"note\">Research failed</p>");
        return;
      }
      r = obj.research;
      q = quotes[sym] || r;
      onTick = !!(state.ticks && state.ticks[sym]);
      html = "<h2>" + esc(r.symbol) + "</h2>";
      html += "<h3>" + esc(r.long_name || r.name) + "</h3>";
      html += '<div class="hero-px">' + Number(r.price).toFixed(2) +
        ' <span style="font-size:14px;color:#8a8070">' + esc(r.currency) + "</span></div>";
      html += '<div class="hero-ch ' + cls(r.pct, 0) + '">' +
        (r.change > 0 ? "+" : "") + Number(r.change).toFixed(2) + "  (" +
        (r.pct > 0 ? "+" : "") + Number(r.pct).toFixed(2) + "%)</div>";
      html += '<canvas id="spark"></canvas>';
      html += '<div class="grid">';
      html += '<div class="cell"><span class="l">Day</span><span class="v">' +
        (r.day_low || "—") + " – " + (r.day_high || "—") + "</span></div>";
      html += '<div class="cell"><span class="l">52 week</span><span class="v">' +
        (r.year_low || "—") + " – " + (r.year_high || "—") + "</span></div>";
      html += '<div class="cell"><span class="l">Volume</span><span class="v">' +
        (r.volume || "—") + "</span></div>";
      html += '<div class="cell"><span class="l">Exchange</span><span class="v">' +
        esc(r.exchange) + "</span></div>";
      if (r.sector) {
        html += '<div class="cell"><span class="l">Sector</span><span class="v">' +
          esc(r.sector) + "</span></div>";
      }
      if (r.industry) {
        html += '<div class="cell"><span class="l">Industry</span><span class="v">' +
          esc(r.industry) + "</span></div>";
      }
      html += "</div>";
      html += '<label><input type="checkbox" id="tickOn"' + (onTick ? " checked" : "") + "> Price up-tick notify</label>";
      html += '<button type="button" class="go" id="btnAlert">Add price alert</button>';
      html += '<button type="button" class="danger" id="btnDrop">Remove from list</button>';
      html += "<h2>Headlines</h2>";
      if (r.news && r.news.length) {
        for (i = 0; i < r.news.length; i++) {
          n = r.news[i];
          html += '<a class="news" href="' + esc(n.link) + '">' + esc(n.title) +
            '<div class="m">' + esc(n.publisher) + "</div></a>";
        }
      } else {
        html += '<p class="note">No headlines</p>';
      }
      html += '<button type="button" id="btnCloseR">Close</button>';
      showResearch(html);
      drawSpark(r.spark || []);
      $("tickOn").onchange = function() {
        if (!state.ticks) state.ticks = {};
        if ($("tickOn").checked) state.ticks[sym] = true;
        else delete state.ticks[sym];
        save();
        renderBoard();
      };
      $("btnAlert").onclick = function() { addAlertForm(sym, r.price); };
      $("btnDrop").onclick = function() { dropSymbol(sym); hideSheets(); };
      $("btnCloseR").onclick = hideSheets;
    });
  }

  function dropSymbol(sym) {
    var lst = activeList();
    var next = [], i;
    if (!lst) return;
    for (i = 0; i < lst.symbols.length; i++) {
      if (lst.symbols[i] !== sym) next.push(lst.symbols[i]);
    }
    lst.symbols = next;
    save();
    renderBoard();
  }

  function addAlertForm(sym, price) {
    var html = "<h2>Alert</h2><h3>" + esc(sym) + "</h3>";
    html += "<label>When</label><select id=\"akind\">";
    html += '<option value="above">Price goes above</option>';
    html += '<option value="below">Price goes below</option>';
    html += '<option value="uptick">Any up-tick</option>';
    html += '<option value="downtick">Any down-tick</option></select>';
    html += '<label>Price</label><input type="number" id="aprice" step="0.01" value="' +
      (price ? Number(price).toFixed(2) : "") + '">';
    html += '<label>Note</label><input type="text" id="anote" placeholder="optional">';
    html += '<button type="button" class="go" id="asave">Save alert</button>';
    html += '<button type="button" id="acancel">Cancel</button>';
    showSheet(html);
    $("asave").onclick = function() {
      state.alerts.push({
        id: String(new Date().getTime()),
        symbol: sym,
        kind: $("akind").value,
        price: parseFloat($("aprice").value),
        note: $("anote").value,
        enabled: true
      });
      save();
      hideSheets();
      setChip("Alert saved for " + sym);
    };
    $("acancel").onclick = hideSheets;
  }

  function openMenu() {
    var html = "<h2>The Tape</h2><h3>Desk</h3>";
    html += '<button type="button" class="go" id="mRefresh">Refresh quotes</button>';
    html += '<button type="button" id="mAlerts">Alerts</button>';
    html += '<button type="button" id="mLists">Manage lists</button>';
    html += '<button type="button" id="mPps">Test hub notify</button>';
    html += "<label>Poll seconds</label>";
    html += '<input type="number" id="mPoll" min="15" step="5" value="' + (state.poll || 30) + '">';
    html += '<label><input type="checkbox" id="mPpsOn"' + (state.pps ? " checked" : "") + "> Hub notifications (PPS)</label>";
    html += '<p class="note">Quotes from Yahoo spark/chart. Alerts append to /pps/services/notify/control — same path Rocket.Chat uses. Turn on the gold ▲ on a symbol for up-tick banners.</p>';
    html += '<button type="button" id="mClose">Close</button>';
    showSheet(html);
    $("mRefresh").onclick = function() { hideSheets(); refreshQuotes(); };
    $("mAlerts").onclick = openAlerts;
    $("mLists").onclick = openLists;
    $("mPps").onclick = function() {
      xhr("POST", "/api/notify-test", { msg: "Stocks PPS test" }, function(st, obj) {
        setChip((obj && obj.pps) ? "PPS sent" : "PPS skipped (no /pps here)");
      });
    };
    $("mPoll").onchange = function() {
      state.poll = parseInt($("mPoll").value, 10) || 30;
      save();
    };
    $("mPpsOn").onchange = function() {
      state.pps = $("mPpsOn").checked;
      save();
    };
    $("mClose").onclick = hideSheets;
  }

  function openAlerts() {
    var html = "<h2>Alerts</h2>", i, a;
    if (!state.alerts.length) html += '<p class="note">None yet. Open a symbol.</p>';
    for (i = 0; i < state.alerts.length; i++) {
      a = state.alerts[i];
      html += '<button type="button" data-adel="' + i + '">' + esc(a.symbol) + " · " +
        esc(a.kind) + (a.price ? " " + a.price : "") + "  ×</button>";
    }
    html += '<button type="button" id="aBack">Back</button>';
    showSheet(html);
    $("sheet").onclick = function(e) {
      e = e || window.event;
      var t = e.target || e.srcElement;
      if (t && t.getAttribute && t.getAttribute("data-adel") != null) {
        state.alerts.splice(parseInt(t.getAttribute("data-adel"), 10), 1);
        save();
        openAlerts();
      }
    };
    $("aBack").onclick = openMenu;
  }

  function openLists() {
    var html = "<h2>Lists</h2>", i, lst;
    html += '<label>New list</label><input type="text" id="lname" placeholder="Energy, Banks…">';
    html += '<button type="button" class="go" id="ladd">Create list</button>';
    for (i = 0; i < state.lists.length; i++) {
      lst = state.lists[i];
      html += '<button type="button" data-ldel="' + i + '"' +
        (state.lists.length < 2 ? " disabled" : "") + ">" +
        esc(lst.name) + " (" + lst.symbols.length + ")  ×</button>";
    }
    html += '<button type="button" id="lBack">Back</button>';
    showSheet(html);
    $("ladd").onclick = function() {
      var name = ($("lname").value || "").replace(/^\s+|\s+$/g, "") || "List";
      xhr("POST", "/api/list", { name: name }, function(st, obj) {
        if (obj && obj.state) state = obj.state;
        renderLists();
        renderBoard();
        hideSheets();
      });
    };
    $("sheet").onclick = function(e) {
      e = e || window.event;
      var t = e.target || e.srcElement, idx;
      if (t && t.getAttribute && t.getAttribute("data-ldel") != null && state.lists.length > 1) {
        idx = parseInt(t.getAttribute("data-ldel"), 10);
        if (state.lists[idx].id === state.active) {
          state.active = state.lists[idx ? 0 : 1].id;
        }
        state.lists.splice(idx, 1);
        save();
        renderLists();
        openLists();
      }
    };
    $("lBack").onclick = openMenu;
  }

  function boot() {
    $("btnMenu").onclick = openMenu;
    $("scrim").onclick = hideSheets;
    $("btnSearch").onclick = function() { search(); return false; };
    $("addForm").onsubmit = function(e) {
      e = e || window.event;
      if (e.preventDefault) e.preventDefault();
      search();
      return false;
    };
    $("lists").onclick = function(e) {
      e = e || window.event;
      var t = e.target || e.srcElement, id;
      if (!t || !t.getAttribute) return;
      id = t.getAttribute("data-list");
      if (!id) return;
      if (id === "__new") { openLists(); return; }
      state.active = id;
      save();
      renderLists();
      renderBoard();
      refreshQuotes();
    };
    $("hits").onclick = function(e) {
      e = e || window.event;
      var t = e.target || e.srcElement, idx;
      while (t && t !== $("hits")) {
        if (t.getAttribute && t.getAttribute("data-idx") != null) {
          idx = parseInt(t.getAttribute("data-idx"), 10);
          if (hits[idx]) addSymbol(hits[idx].symbol);
          return;
        }
        t = t.parentNode;
      }
    };
    $("board").onclick = function(e) {
      e = e || window.event;
      var t = e.target || e.srcElement;
      if (e.preventDefault) e.preventDefault();
      while (t && t !== $("board")) {
        if (t.getAttribute && t.getAttribute("data-sym")) {
          openResearch(t.getAttribute("data-sym"));
          return false;
        }
        t = t.parentNode;
      }
    };
    loadState(true);
    timer = setInterval(function() { refreshQuotes(); }, 35000);
  }

  if (document.readyState === "complete" || document.readyState === "interactive") boot();
  else if (document.addEventListener) document.addEventListener("DOMContentLoaded", boot, false);
  else window.onload = boot;
})();
