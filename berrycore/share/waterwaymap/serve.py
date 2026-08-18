#!/usr/bin/env python3
"""Waterway Map — OSM river basins for berry-browser. Port 8095."""
import http.server
import json
import math
import os
import socketserver
import ssl
import struct
import sys
import threading
import urllib.parse
import urllib.request
import zlib

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8095
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
STATIC_DIR = os.path.join(BASE_DIR, "static")
CACHE_DIR = os.path.join(BASE_DIR, "offline", "tiles-osm")
WAY_DIR = os.path.join(BASE_DIR, "offline", "waterways")
MIN_TILE_BYTES = 400
UA = "BerryCoreWaterway/1.0 (https://github.com/sw7ft/BerryCore)"
TILE_OSM = "https://tile.openstreetmap.org/%d/%d/%d.png"
TILE_LIGHT = "https://basemaps.cartocdn.com/rastertiles/voyager/%d/%d/%d.png"
OVERPASS_URLS = (
    "https://overpass.kumi.systems/api/interpreter",
    "https://overpass-api.de/api/interpreter",
    "https://overpass.osm.ch/api/interpreter",
)
NOMINATIM = "https://nominatim.openstreetmap.org"
WAY_CACHE = {}
WAY_CACHE_KEYS = []
WAY_INFLIGHT = {}
WAY_GUARD = threading.Lock()
PALETTE = (
    "#ff6b6b", "#ffd93d", "#6bcb77", "#4d96ff", "#ff922b",
    "#cc5de8", "#20c997", "#f06595", "#74c0fc", "#ffc078",
    "#63e6be", "#b197fc", "#ffa8a8", "#8ce99a", "#66d9e8",
)


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


def http_get(url, timeout=20):
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, context=SSL_CTX, timeout=timeout) as resp:
        return resp.read()


def http_post(url, data, timeout=16):
    body = data.encode("utf-8")
    req = urllib.request.Request(
        url, data=body,
        headers={"User-Agent": UA, "Content-Type": "application/x-www-form-urlencoded"},
    )
    with urllib.request.urlopen(req, context=SSL_CTX, timeout=timeout) as resp:
        return resp.read()


def tile_path(z, x, y):
    os.makedirs(CACHE_DIR, exist_ok=True)
    return os.path.join(CACHE_DIR, "%d_%d_%d.png" % (z, x, y))


def is_png(data):
    return bool(data) and data[:8] == b"\x89PNG\r\n\x1a\n"


def empty_png():
    def chunk(tag, data):
        crc = zlib.crc32(tag + data) & 0xFFFFFFFF
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", crc)
    raw = b"\x00\xf2\xef\xe9"
    return (
        b"\x89PNG\r\n\x1a\n"
        + chunk(b"IHDR", struct.pack(">IIBBBBB", 1, 1, 8, 2, 0, 0, 0))
        + chunk(b"IDAT", zlib.compress(raw))
        + chunk(b"IEND", b"")
    )


EMPTY_TILE = empty_png()


def fetch_tile(z, x, y):
    path = tile_path(z, x, y)
    if os.path.exists(path):
        cached = open(path, "rb").read()
        if is_png(cached) and len(cached) > MIN_TILE_BYTES:
            return cached
    data = None
    for url in (TILE_OSM % (z, x, y), TILE_LIGHT % (z, x, y)):
        try:
            data = http_get(url, timeout=12)
        except Exception:
            data = None
        if is_png(data) and len(data) > MIN_TILE_BYTES:
            open(path, "wb").write(data)
            return data
    return EMPTY_TILE


def haversine_m(lat1, lon1, lat2, lon2):
    r = 6371000.0
    p1, p2 = math.radians(lat1), math.radians(lat2)
    dphi = math.radians(lat2 - lat1)
    dl = math.radians(lon2 - lon1)
    a = math.sin(dphi / 2) ** 2 + math.cos(p1) * math.cos(p2) * math.sin(dl / 2) ** 2
    return 2 * r * math.asin(min(1.0, math.sqrt(a)))


def path_length_m(coords):
    total = 0.0
    i = 0
    while i < len(coords) - 1:
        total += haversine_m(coords[i][1], coords[i][0], coords[i + 1][1], coords[i + 1][0])
        i += 1
    return total


def simplify(coords, zoom):
    if len(coords) < 4:
        return coords
    if zoom < 10:
        step = 8
    elif zoom < 12:
        step = 5
    elif zoom < 14:
        step = 3
    else:
        step = 2
    out = [coords[0]]
    i = step
    while i < len(coords) - 1:
        out.append(coords[i])
        i += step
    out.append(coords[-1])
    if len(out) > 72:
        slim = [out[0]]
        hop = max(1, len(out) // 70)
        i = hop
        while i < len(out) - 1:
            slim.append(out[i])
            i += hop
        slim.append(out[-1])
        return slim
    return out


def lonlat_to_tile(lon, lat, zoom):
    lat_rad = math.radians(max(-85.0, min(85.0, lat)))
    n = 2.0 ** zoom
    x = int((lon + 180.0) / 360.0 * n)
    y = int((1.0 - math.log(math.tan(lat_rad) + 1.0 / math.cos(lat_rad)) / math.pi) / 2.0 * n)
    return x, y


def prefetch_around(lat, lon, zoom):
    z = max(3, min(16, int(zoom)))
    n = 0
    jobs = ((z, 1), (min(16, z + 1), 0))
    for zz, rad in jobs:
        cx, cy = lonlat_to_tile(lon, lat, zz)
        dx = -rad
        while dx <= rad:
            dy = -rad
            while dy <= rad:
                try:
                    fetch_tile(zz, cx + dx, cy + dy)
                    n += 1
                except Exception:
                    pass
                dy += 1
            dx += 1
    return n


def view_bbox(lat, lon, zoom):
    tile_deg = 360.0 / (2 ** max(1, int(zoom)))
    half_lon = tile_deg * 1.15
    half_lat = tile_deg * 0.95
    return (
        lat - half_lat,
        lon - half_lon,
        lat + half_lat,
        lon + half_lon,
    )


def snap_bbox(south, west, north, east, zoom):
    if zoom < 11:
        step = 0.05
    elif zoom < 13:
        step = 0.02
    else:
        step = 0.01
    south = math.floor(south / step) * step
    west = math.floor(west / step) * step
    north = math.ceil(north / step) * step
    east = math.ceil(east / step) * step
    return (
        round(south, 4), round(west, 4),
        round(north, 4), round(east, 4),
    )


def way_disk_name(key):
    kinds = "-".join(key[5])
    return "s%s_w%s_n%s_e%s_z%s_%s.json" % (
        key[0], key[1], key[2], key[3], key[4], kinds,
    )


def way_cache_get(key):
    hit = WAY_CACHE.get(key)
    if hit is not None:
        return hit
    path = os.path.join(WAY_DIR, way_disk_name(key))
    if not os.path.isfile(path):
        return None
    try:
        data = json.loads(open(path, "r").read())
    except Exception:
        return None
    if isinstance(data, list):
        WAY_CACHE[key] = data
        return data
    return None


def way_cache_put(key, val):
    WAY_CACHE[key] = val
    if key not in WAY_CACHE_KEYS:
        WAY_CACHE_KEYS.append(key)
    while len(WAY_CACHE_KEYS) > 24:
        old = WAY_CACHE_KEYS.pop(0)
        if old != key:
            WAY_CACHE.pop(old, None)
    os.makedirs(WAY_DIR, exist_ok=True)
    try:
        open(os.path.join(WAY_DIR, way_disk_name(key)), "w").write(json.dumps(val))
    except Exception:
        pass


def kinds_for_zoom(zoom, want):
    allowed = []
    if "river" in want:
        allowed.append("river")
    if "canal" in want and zoom >= 9:
        allowed.append("canal")
    if "stream" in want and zoom >= 12:
        allowed.append("stream")
        allowed.append("rapids")
    if "drain" in want and zoom >= 14:
        allowed.append("drain")
        allowed.append("ditch")
    if not allowed:
        allowed = ["river"]
    return allowed


def group_ways(ways):
    n = len(ways)
    parent = list(range(n))

    def find(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i

    def union(a, b):
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[rb] = ra

    buckets = {}
    i = 0
    while i < n:
        seen = set()
        for pt in ways[i]["coords"]:
            k = (round(pt[0], 4), round(pt[1], 4))
            if k in seen:
                continue
            seen.add(k)
            if k in buckets:
                union(i, buckets[k])
            else:
                buckets[k] = i
        i += 1

    groups = {}
    gid = 0
    i = 0
    while i < n:
        root = find(i)
        if root not in groups:
            groups[root] = gid
            gid += 1
        ways[i]["group"] = groups[root]
        ways[i]["color"] = PALETTE[groups[root] % len(PALETTE)]
        i += 1
    return ways


def overpass_query(kinds, south, west, north, east):
    parts = []
    for kind in kinds:
        parts.append('way["waterway"="%s"](%s,%s,%s,%s);' % (
            kind, south, west, north, east,
        ))
    return (
        "[out:json][timeout:10];(%s);out geom qt;" % "".join(parts)
    )


def overpass_fetch(payload):
    last = None
    for url in OVERPASS_URLS:
        try:
            raw = http_post(url, payload, timeout=14)
            if raw and len(raw) > 400 and raw.lstrip()[:1] == b"{":
                return raw, None
        except Exception as exc:
            last = exc
    return None, last


def parse_overpass(raw, zoom):
    data = json.loads(raw.decode("utf-8"))
    ways = []
    cap = 60 if zoom < 11 else 90
    for el in data.get("elements", []):
        geom = el.get("geometry") or []
        if len(geom) < 2:
            continue
        coords = []
        for pt in geom:
            coords.append([round(float(pt["lon"]), 5), round(float(pt["lat"]), 5)])
        coords = simplify(coords, zoom)
        tags = el.get("tags") or {}
        kind = tags.get("waterway") or "river"
        ways.append({
            "id": el.get("id"),
            "name": tags.get("name") or kind,
            "kind": kind,
            "km": round(path_length_m(coords) / 1000.0, 2),
            "coords": coords,
        })
        if len(ways) >= cap:
            break
    return group_ways(ways)


def overpass_waterways(south, west, north, east, zoom, types):
    area = abs(north - south) * abs(east - west)
    if area > 6:
        return []
    kinds = kinds_for_zoom(zoom, types)
    south, west, north, east = snap_bbox(south, west, north, east, zoom)
    key = (south, west, north, east, int(zoom), tuple(kinds))
    hit = way_cache_get(key)
    if hit is not None:
        return hit
    mine = False
    with WAY_GUARD:
        ev = WAY_INFLIGHT.get(key)
        if ev is None:
            ev = threading.Event()
            WAY_INFLIGHT[key] = ev
            mine = True
    if not mine:
        ev.wait(14)
        return way_cache_get(key) or []
    try:
        payload = "data=" + urllib.parse.quote(overpass_query(kinds, south, west, north, east))
        raw, last = overpass_fetch(payload)
        if not raw:
            raise last or RuntimeError("overpass failed")
        ways = parse_overpass(raw, zoom)
        way_cache_put(key, ways)
        return ways
    finally:
        ev.set()
        with WAY_GUARD:
            WAY_INFLIGHT.pop(key, None)


def nominatim_search(query, limit=8):
    query = (query or "").strip()
    if not query:
        return []
    attempts = [query]
    low = query.lower()
    if not any(w in low for w in ("river", "creek", "lake", "canal")):
        attempts.append(query + " river")
    results = []
    seen = set()
    for q in attempts:
        params = urllib.parse.urlencode({
            "format": "json",
            "q": q,
            "limit": str(limit + 2),
            "addressdetails": "0",
        })
        try:
            raw = http_get("%s/search?%s" % (NOMINATIM, params), timeout=16)
            data = json.loads(raw.decode("utf-8"))
        except Exception:
            data = []
        if not isinstance(data, list):
            continue
        for item in data:
            try:
                lat = float(item["lat"])
                lon = float(item["lon"])
            except Exception:
                continue
            name = item.get("display_name") or item.get("name") or q
            key = (round(lat, 4), round(lon, 4), name)
            if key in seen:
                continue
            seen.add(key)
            results.append({
                "name": name,
                "short_name": item.get("name") or name.split(",")[0],
                "lat": lat,
                "lon": lon,
            })
            if len(results) >= limit:
                return results
        if results:
            break
    return results


def json_bytes(obj):
    return json.dumps(obj).encode("utf-8")


def mime_for(path):
    if path.endswith(".js"):
        return "application/javascript"
    if path.endswith(".css"):
        return "text/css"
    if path.endswith(".png"):
        return "image/png"
    if path.endswith(".json"):
        return "application/json"
    return "text/html; charset=utf-8"


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
            if path == "/api/config":
                self.send_json(200, {
                    "status": "ok",
                    "default_lat": 40.0,
                    "default_lon": 15.0,
                    "default_zoom": 3,
                    "port": PORT,
                })
                return
            if path.startswith("/api/tile/"):
                parts = path.strip("/").split("/")
                z, x, y = int(parts[2]), int(parts[3]), int(parts[4].split(".")[0])
                data = fetch_tile(z, x, y) or EMPTY_TILE
                self.send_response(200)
                self.send_header("Content-Type", "image/png")
                self.send_header("Cache-Control", "public, max-age=86400")
                self.end_headers()
                self.wfile.write(data)
                return
            if path == "/api/prefetch":
                lat = float(q["lat"])
                lon = float(q["lon"])
                zoom = int(q.get("zoom", 12) or 12)
                types = (q.get("types") or "river,canal").split(",")
                types = [t.strip() for t in types if t.strip()]
                ways = []
                bounds = None
                if zoom >= 8:
                    south, west, north, east = view_bbox(lat, lon, zoom)
                    ways = overpass_waterways(south, west, north, east, zoom, types)
                    south, west, north, east = snap_bbox(south, west, north, east, zoom)
                    bounds = {
                        "south": south, "west": west,
                        "north": north, "east": east,
                    }
                n = prefetch_around(lat, lon, zoom)
                self.send_json(200, {
                    "status": "ok", "tiles": n,
                    "count": len(ways), "waterways": ways,
                    "bounds": bounds, "zoom": zoom,
                })
                return
            if path == "/api/geocode":
                results = nominatim_search(q.get("q", ""), int(q.get("limit", 8) or 8))
                self.send_json(200, {"status": "ok", "count": len(results), "results": results})
                return
            if path == "/api/waterways":
                zoom = int(q.get("zoom", 10) or 10)
                if zoom < 8:
                    self.send_json(200, {
                        "status": "ok", "count": 0, "waterways": [],
                        "note": "Zoom in to load waterways",
                    })
                    return
                types = (q.get("types") or "river,canal").split(",")
                types = [t.strip() for t in types if t.strip()]
                ways = overpass_waterways(
                    float(q["south"]), float(q["west"]),
                    float(q["north"]), float(q["east"]),
                    zoom, types,
                )
                self.send_json(200, {"status": "ok", "count": len(ways), "waterways": ways})
                return
        except KeyError:
            self.send_json(400, {"status": "error", "error": "missing parameter"})
            return
        except Exception as exc:
            self.send_json(500, {"status": "error", "error": str(exc)})
            return
        self.send_error(404)


def main():
    os.makedirs(CACHE_DIR, exist_ok=True)
    os.makedirs(WAY_DIR, exist_ok=True)
    httpd = ThreadedTCPServer(("0.0.0.0", PORT), Handler)
    print("Waterway Map http://0.0.0.0:%d/" % PORT)
    httpd.serve_forever()


if __name__ == "__main__":
    main()
