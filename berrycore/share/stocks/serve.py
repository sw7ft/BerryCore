#!/usr/bin/env python3
"""Stocks — ticker, research, lists, upticks, PPS alerts. Port 8096."""
import http.server
import json
import os
import socketserver
import ssl
import sys
import threading
import time
import urllib.parse
import urllib.request
import uuid

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8096
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
STATIC_DIR = os.path.join(BASE_DIR, "static")
STATE_PATH = os.environ.get(
    "BERRYCORE_STOCKS_STATE",
    os.path.join(BASE_DIR, "..", "..", ".tmp", "stocks-state.json"),
)
PPS_PATH = "/pps/services/notify/control"
UA = "BerryCoreStocks/1.0 (https://github.com/sw7ft/BerryCore)"
SPARK = "https://query1.finance.yahoo.com/v8/finance/spark?%s"
CHART = "https://query1.finance.yahoo.com/v8/finance/chart/%s?%s"
SEARCH = "https://query2.finance.yahoo.com/v1/finance/search?%s"
YAHOO2 = "https://query2.finance.yahoo.com/v8/finance/spark?%s"

LOCK = threading.Lock()
CACHE = {"quotes": {}, "ts": 0}
STATE = None


def create_ssl_context():
    try:
        return ssl._create_unverified_context()
    except Exception:
        ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
        ctx.verify_mode = ssl.CERT_NONE
        ctx.check_hostname = False
        return ctx


SSL_CTX = create_ssl_context()


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True
    daemon_threads = True


def default_state():
    return {
        "lists": [
            {
                "id": "watch",
                "name": "Watch",
                "symbols": ["AAPL", "MSFT", "GOOG", "AMZN", "NVDA", "SPY"],
            }
        ],
        "active": "watch",
        "ticks": {"AAPL": True, "MSFT": True, "SPY": True},
        "alerts": [],
        "poll": 30,
        "pps": True,
        "fired": {},
    }


def load_state():
    global STATE
    try:
        raw = open(STATE_PATH, "r").read()
        data = json.loads(raw)
        if not isinstance(data, dict) or not data.get("lists"):
            data = default_state()
    except Exception:
        data = default_state()
    if "ticks" not in data:
        data["ticks"] = {}
    if "alerts" not in data:
        data["alerts"] = []
    if "fired" not in data:
        data["fired"] = {}
    if "poll" not in data:
        data["poll"] = 30
    if "pps" not in data:
        data["pps"] = True
    STATE = data
    return data


def save_state():
    path = os.path.abspath(STATE_PATH)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    tmp = path + ".tmp"
    open(tmp, "w").write(json.dumps(STATE, indent=2))
    os.rename(tmp, path)


def http_get(url, timeout=14):
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, context=SSL_CTX, timeout=timeout) as resp:
        return resp.read()


def pps_notify(title, subtitle):
    payload = json.dumps({
        "itemid": "BerryStocks",
        "title": title,
        "subtitle": subtitle,
        "target": "",
        "targetAction": "",
        "payload": "http://localhost:%d/" % PORT,
        "payloadType": "url",
        "payloadURI": "http://localhost:%d/" % PORT,
    })
    msg = "msg::notify\ndat:json:%s\n" % payload
    try:
        fd = os.open(PPS_PATH, os.O_WRONLY | os.O_APPEND)
        try:
            os.write(fd, msg.encode("utf-8"))
        finally:
            os.close(fd)
        sys.stderr.write("[NOTIFY] %s — %s\n" % (title, subtitle))
        return True
    except Exception as exc:
        sys.stderr.write("[NOTIFY] skip: %s\n" % exc)
        return False


def last_close(closes):
    if not closes:
        return None
    i = len(closes) - 1
    while i >= 0:
        if closes[i] is not None:
            return float(closes[i])
        i -= 1
    return None


def parse_spark(data):
    out = []
    if not isinstance(data, dict):
        return out
    inner = data.get("spark", {}).get("result") if "spark" in data else None
    items = {}
    if isinstance(inner, list):
        for row in inner:
            if isinstance(row, dict) and row.get("symbol"):
                items[row["symbol"]] = row
    elif isinstance(data, dict):
        for key, row in data.items():
            if key in ("spark", "finance"):
                continue
            if isinstance(row, dict) and (row.get("symbol") or row.get("close")):
                items[row.get("symbol") or key] = row
    for sym, row in items.items():
        price = last_close(row.get("close") or [])
        prev = row.get("previousClose") or row.get("chartPreviousClose")
        if price is None:
            continue
        prev = float(prev) if prev else price
        chg = price - prev
        pct = (chg / prev * 100.0) if prev else 0.0
        spark = []
        for v in (row.get("close") or [])[-24:]:
            if v is not None:
                spark.append(round(float(v), 4))
        out.append({
            "symbol": sym,
            "price": round(price, 4),
            "prev": round(prev, 4),
            "change": round(chg, 4),
            "pct": round(pct, 3),
            "spark": spark,
        })
    return out


def fetch_spark(symbols):
    if not symbols:
        return []
    chunk = []
    seen = set()
    for s in symbols:
        s = (s or "").strip().upper()
        if s and s not in seen:
            seen.add(s)
            chunk.append(s)
    results = []
    i = 0
    while i < len(chunk):
        part = chunk[i:i + 12]
        qs = urllib.parse.urlencode({
            "symbols": ",".join(part),
            "range": "1d",
            "interval": "5m",
        })
        raw = None
        for url in (SPARK % qs, YAHOO2 % qs):
            try:
                raw = http_get(url, timeout=12)
                if raw and raw[:1] == b"{":
                    break
            except Exception:
                raw = None
        if raw:
            try:
                results.extend(parse_spark(json.loads(raw.decode("utf-8"))))
            except Exception:
                pass
        i += 12
    return results


def fetch_chart(symbol, rng="1d", interval="5m"):
    symbol = urllib.parse.quote((symbol or "").strip().upper())
    qs = urllib.parse.urlencode({"range": rng, "interval": interval})
    raw = http_get(CHART % (symbol, qs), timeout=14)
    data = json.loads(raw.decode("utf-8"))
    res = (data.get("chart") or {}).get("result") or []
    if not res:
        raise RuntimeError("no chart")
    row = res[0]
    meta = row.get("meta") or {}
    ts = row.get("timestamp") or []
    closes = (((row.get("indicators") or {}).get("quote") or [{}])[0].get("close") or [])
    spark = []
    i = 0
    while i < len(closes):
        if closes[i] is not None:
            spark.append({
                "t": ts[i] if i < len(ts) else 0,
                "p": round(float(closes[i]), 4),
            })
        i += 1
    price = meta.get("regularMarketPrice")
    prev = meta.get("chartPreviousClose") or meta.get("previousClose")
    if price is None and spark:
        price = spark[-1]["p"]
    prev = float(prev) if prev else (float(price) if price else 0)
    price = float(price) if price else prev
    chg = price - prev
    pct = (chg / prev * 100.0) if prev else 0.0
    return {
        "symbol": meta.get("symbol") or symbol,
        "name": meta.get("shortName") or meta.get("longName") or symbol,
        "long_name": meta.get("longName") or meta.get("shortName") or symbol,
        "price": round(price, 4),
        "prev": round(prev, 4),
        "change": round(chg, 4),
        "pct": round(pct, 3),
        "currency": meta.get("currency") or "USD",
        "exchange": meta.get("fullExchangeName") or meta.get("exchangeName") or "",
        "kind": meta.get("instrumentType") or "",
        "day_high": meta.get("regularMarketDayHigh"),
        "day_low": meta.get("regularMarketDayLow"),
        "volume": meta.get("regularMarketVolume"),
        "year_high": meta.get("fiftyTwoWeekHigh"),
        "year_low": meta.get("fiftyTwoWeekLow"),
        "spark": spark[-48:],
    }


def search_symbols(query, limit=8):
    qs = urllib.parse.urlencode({
        "q": query,
        "quotesCount": str(limit),
        "newsCount": "6",
    })
    raw = http_get(SEARCH % qs, timeout=12)
    data = json.loads(raw.decode("utf-8"))
    quotes = []
    for item in data.get("quotes") or []:
        quotes.append({
            "symbol": item.get("symbol") or "",
            "name": item.get("shortname") or item.get("longname") or "",
            "long_name": item.get("longname") or item.get("shortname") or "",
            "type": item.get("typeDisp") or item.get("quoteType") or "",
            "exchange": item.get("exchDisp") or item.get("exchange") or "",
            "sector": item.get("sectorDisp") or item.get("sector") or "",
            "industry": item.get("industryDisp") or item.get("industry") or "",
        })
        if len(quotes) >= limit:
            break
    news = []
    for item in data.get("news") or []:
        news.append({
            "title": item.get("title") or "",
            "link": item.get("link") or item.get("url") or "",
            "publisher": item.get("publisher") or "",
        })
        if len(news) >= 6:
            break
    return quotes, news


def all_symbols():
    seen = []
    have = set()
    for lst in STATE.get("lists") or []:
        for s in lst.get("symbols") or []:
            s = (s or "").strip().upper()
            if s and s not in have:
                have.add(s)
                seen.append(s)
    for a in STATE.get("alerts") or []:
        s = (a.get("symbol") or "").strip().upper()
        if s and s not in have:
            have.add(s)
            seen.append(s)
    return seen


def apply_quotes(rows):
    now = time.time()
    events = []
    with LOCK:
        prev = CACHE["quotes"]
        nxt = dict(prev)
        for row in rows:
            sym = row["symbol"]
            old = prev.get(sym)
            row["tick"] = 0
            if old and old.get("price") is not None:
                if row["price"] > old["price"]:
                    row["tick"] = 1
                elif row["price"] < old["price"]:
                    row["tick"] = -1
            nxt[sym] = row
            if row["tick"] == 1 and STATE.get("ticks", {}).get(sym):
                events.append(("up", row))
            for alert in STATE.get("alerts") or []:
                if not alert.get("enabled", True):
                    continue
                if (alert.get("symbol") or "").upper() != sym:
                    continue
                kind = alert.get("kind") or "above"
                aid = alert.get("id") or ""
                last_fire = float((STATE.get("fired") or {}).get(aid) or 0)
                if now - last_fire < 900:
                    continue
                hit = False
                if kind == "above" and alert.get("price") is not None and row["price"] >= float(alert["price"]):
                    hit = True
                elif kind == "below" and alert.get("price") is not None and row["price"] <= float(alert["price"]):
                    hit = True
                elif kind == "uptick" and row["tick"] == 1:
                    hit = True
                elif kind == "downtick" and row["tick"] == -1:
                    hit = True
                if hit:
                    events.append(("alert", row, alert))
                    STATE.setdefault("fired", {})[aid] = now
        CACHE["quotes"] = nxt
        CACHE["ts"] = now
    if events and STATE.get("pps"):
        for ev in events:
            if ev[0] == "up":
                row = ev[1]
                pps_notify(
                    "%s ↑ %.2f" % (row["symbol"], row["price"]),
                    "%+.2f (%+.2f%%)" % (row["change"], row["pct"]),
                )
            else:
                row, alert = ev[1], ev[2]
                pps_notify(
                    "%s %s" % (row["symbol"], alert.get("kind") or "alert"),
                    "%.2f  %s" % (row["price"], alert.get("note") or ""),
                )
        try:
            save_state()
        except Exception:
            pass
    return [CACHE["quotes"].get(s) for s in [r["symbol"] for r in rows] if CACHE["quotes"].get(s)]


def refresh_quotes(symbols=None):
    symbols = symbols or all_symbols()
    rows = fetch_spark(symbols)
    return apply_quotes(rows)


def poller():
    while True:
        try:
            load_state()
            secs = int(STATE.get("poll") or 30)
            if secs < 15:
                secs = 15
            if all_symbols():
                refresh_quotes()
        except Exception as exc:
            sys.stderr.write("[POLL] %s\n" % exc)
        time.sleep(max(15, int((STATE or {}).get("poll") or 30)))


def json_bytes(obj):
    return json.dumps(obj).encode("utf-8")


def mime_for(path):
    if path.endswith(".js"):
        return "application/javascript"
    if path.endswith(".css"):
        return "text/css"
    return "text/html; charset=utf-8"


def read_json_body(handler):
    n = int(handler.headers.get("Content-Length") or 0)
    raw = handler.rfile.read(n) if n else b"{}"
    try:
        return json.loads(raw.decode("utf-8"))
    except Exception:
        return {}


class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        sys.stderr.write("%s - %s\n" % (self.address_string(), fmt % args))

    def send_json(self, code, obj):
        body = json_bytes(obj)
        self.send_response(code)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Cache-Control", "no-store")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def send_file(self, path):
        if not os.path.isfile(path):
            self.send_error(404)
            return
        data = open(path, "rb").read()
        self.send_response(200)
        self.send_header("Content-Type", mime_for(path))
        self.send_header("Cache-Control", "no-cache")
        self.end_headers()
        self.wfile.write(data)

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path
        q = dict(urllib.parse.parse_qsl(parsed.query))
        if path in ("/", "/index.html"):
            self.send_file(os.path.join(BASE_DIR, "index.html"))
            return
        if path.startswith("/static/"):
            self.send_file(os.path.join(STATIC_DIR, os.path.basename(path)))
            return
        try:
            if path == "/api/state":
                load_state()
                with LOCK:
                    quotes = dict(CACHE["quotes"])
                    ts = CACHE["ts"]
                self.send_json(200, {
                    "status": "ok",
                    "state": STATE,
                    "quotes": quotes,
                    "asof": ts,
                })
                return
            if path == "/api/quotes":
                load_state()
                symbols = [s.strip().upper() for s in (q.get("symbols") or "").split(",") if s.strip()]
                if not symbols:
                    symbols = all_symbols()
                rows = refresh_quotes(symbols)
                self.send_json(200, {"status": "ok", "count": len(rows), "quotes": rows})
                return
            if path == "/api/search":
                quotes, news = search_symbols(q.get("q", ""), int(q.get("limit", 8) or 8))
                self.send_json(200, {"status": "ok", "results": quotes, "news": news})
                return
            if path == "/api/research":
                sym = (q.get("symbol") or "").strip().upper()
                if not sym:
                    self.send_json(400, {"status": "error", "error": "symbol required"})
                    return
                info = fetch_chart(sym, q.get("range") or "5d", q.get("interval") or "1d")
                extra, news = search_symbols(sym, 4)
                match = extra[0] if extra and extra[0]["symbol"] == sym else (extra[0] if extra else {})
                info["sector"] = match.get("sector") or ""
                info["industry"] = match.get("industry") or ""
                info["type"] = match.get("type") or info.get("kind") or ""
                info["news"] = news
                apply_quotes([{
                    "symbol": info["symbol"],
                    "price": info["price"],
                    "prev": info["prev"],
                    "change": info["change"],
                    "pct": info["pct"],
                    "spark": [p["p"] for p in info["spark"]],
                }])
                self.send_json(200, {"status": "ok", "research": info})
                return
            if path == "/api/config":
                self.send_json(200, {"status": "ok", "port": PORT, "pps": os.path.exists(PPS_PATH)})
                return
        except Exception as exc:
            self.send_json(500, {"status": "error", "error": str(exc)})
            return
        self.send_error(404)

    def do_POST(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path
        body = read_json_body(self)
        try:
            load_state()
            if path == "/api/state":
                if "lists" in body:
                    STATE["lists"] = body["lists"]
                if "active" in body:
                    STATE["active"] = body["active"]
                if "ticks" in body:
                    STATE["ticks"] = body["ticks"]
                if "alerts" in body:
                    STATE["alerts"] = body["alerts"]
                if "poll" in body:
                    STATE["poll"] = max(15, int(body["poll"] or 30))
                if "pps" in body:
                    STATE["pps"] = bool(body["pps"])
                save_state()
                self.send_json(200, {"status": "ok", "state": STATE})
                return
            if path == "/api/list":
                name = (body.get("name") or "List").strip() or "List"
                lid = (body.get("id") or uuid.uuid4().hex[:8])
                STATE["lists"].append({"id": lid, "name": name, "symbols": []})
                STATE["active"] = lid
                save_state()
                self.send_json(200, {"status": "ok", "state": STATE})
                return
            if path == "/api/notify-test":
                ok = pps_notify("Stocks", body.get("msg") or "PPS test from BerryCore Stocks")
                self.send_json(200, {"status": "ok" if ok else "skip", "pps": ok})
                return
        except Exception as exc:
            self.send_json(500, {"status": "error", "error": str(exc)})
            return
        self.send_error(404)


def main():
    load_state()
    save_state()
    t = threading.Thread(target=poller)
    t.daemon = True
    t.start()
    httpd = ThreadedTCPServer(("0.0.0.0", PORT), Handler)
    print("Stocks http://0.0.0.0:%d/" % PORT)
    httpd.serve_forever()


if __name__ == "__main__":
    main()
