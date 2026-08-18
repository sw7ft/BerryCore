#!/usr/bin/env python3
"""BerryCore setup guide. Port 8098."""
import http.server
import json
import os
import socket
import socketserver
import struct
import subprocess
import sys
import urllib.parse
import zlib

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8098
BASE = os.path.dirname(os.path.abspath(__file__))
NATIVE = os.environ.get("NATIVE_TOOLS", os.path.normpath(os.path.join(BASE, "..", "..")))
ICON_DIR = os.path.join(BASE, "icons")
VERSION = "2.0"
BC_VERSION = "0.87.8"


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True
    daemon_threads = True


def load_apps():
    return json.loads(open(os.path.join(BASE, "apps.json"), "r").read())


def bin_path(name):
    return os.path.join(NATIVE, "bin", name)


def catalog_path():
    names = (
        os.path.join(BASE, "berrycore.html"),
        os.path.join(NATIVE, "doc", "berrycore.html"),
        os.path.join(NATIVE, "berrycore.html"),
    )
    for path in names:
        if os.path.isfile(path):
            return path
    return ""


def port_up(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(0.35)
    try:
        sock.connect(("127.0.0.1", int(port)))
        sock.close()
        return True
    except Exception:
        try:
            sock.close()
        except Exception:
            pass
        return False


def start_app(app):
    path = bin_path(app["bin"])
    if not os.path.isfile(path):
        return {"id": app["id"], "started": False, "error": "bin missing"}
    if port_up(app["port"]):
        return {"id": app["id"], "started": True, "already": True}
    try:
        argv = [path]
        if app.get("start_arg", True):
            argv.append("start")
        subprocess.Popen(
            argv,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            cwd=NATIVE,
        )
        return {"id": app["id"], "started": True, "already": False}
    except Exception as exc:
        return {"id": app["id"], "started": False, "error": str(exc)}


def png_chunk(tag, data):
    crc = zlib.crc32(tag + data) & 0xFFFFFFFF
    return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", crc)


FONT = {
    "A": "0111010001111111000110001",
    "B": "1111010001111101000111110",
    "C": "0111110000100001000001111",
    "D": "1111010001100011000111110",
    "E": "1111110000111101000011111",
    "F": "1111110000111101000010000",
    "G": "0111110000101111000101111",
    "H": "1000110001111111000110001",
    "L": "1000010000100001000011111",
    "M": "1000111011101011000110001",
    "O": "0111010001100011000101110",
    "P": "1111010001111101000010000",
    "R": "1111010001111101001010001",
    "S": "0111110000011100000111110",
    "T": "1111100100001000010000100",
    "W": "1000110001101011101110001",
    "Y": "1000110001011100010000100",
    "4": "1000110001111110000100001",
}


def make_icon(r, g, b, letters):
    size = 114
    pixels = []
    y = 0
    while y < size:
        row = []
        x = 0
        while x < size:
            edge = x < 4 or y < 4 or x >= size - 4 or y >= size - 4
            if edge:
                row.append((max(0, r - 40), max(0, g - 40), max(0, b - 40)))
            else:
                row.append((r, g, b))
            x += 1
        pixels.append(row)
        y += 1
    glyphs = []
    i = 0
    while i < len(letters) and i < 2:
        ch = letters[i].upper()
        glyphs.append(FONT.get(ch, FONT["O"]))
        i += 1
    if not glyphs:
        glyphs = [FONT["O"]]
    rows = 5
    scale = 8
    gap = 8
    total_w = len(glyphs) * 5 * scale + (len(glyphs) - 1) * gap
    ox = (size - total_w) // 2
    oy = (size - rows * scale) // 2
    gi = 0
    while gi < len(glyphs):
        bits = glyphs[gi]
        by = 0
        while by < rows:
            bx = 0
            while bx < 5:
                if bits[by * 5 + bx] == "1":
                    py = 0
                    while py < scale:
                        px = 0
                        while px < scale:
                            yy = oy + by * scale + py
                            xx = ox + gi * (5 * scale + gap) + bx * scale + px
                            if 0 <= yy < size and 0 <= xx < size:
                                pixels[yy][xx] = (255, 255, 255)
                            px += 1
                        py += 1
                bx += 1
            by += 1
        gi += 1
    raw = b""
    y = 0
    while y < size:
        raw += b"\x00"
        x = 0
        while x < size:
            raw += bytes(pixels[y][x])
            x += 1
        y += 1
    return (
        b"\x89PNG\r\n\x1a\n"
        + png_chunk(b"IHDR", struct.pack(">IIBBBBB", size, size, 8, 2, 0, 0, 0))
        + png_chunk(b"IDAT", zlib.compress(raw, 9))
        + png_chunk(b"IEND", b"")
    )


def icon_bytes(app):
    os.makedirs(ICON_DIR, exist_ok=True)
    path = os.path.join(ICON_DIR, app["id"] + ".png")
    if os.path.isfile(path) and os.path.getsize(path) > 80:
        return open(path, "rb").read()
    parts = [int(x) for x in app["color"].split(",")]
    data = make_icon(parts[0], parts[1], parts[2], app.get("letters") or app["name"][:2])
    open(path, "wb").write(data)
    return data


def find_app(app_id):
    for app in load_apps():
        if app["id"] == app_id:
            return app
    return None


def pin_html(app):
    url = "http://127.0.0.1:%d/" % app["port"]
    icon = "/icon/%s.png" % app["id"]
    return """<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
<title>%(name)s</title>
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-title" content="%(name)s">
<meta name="apple-mobile-web-app-status-bar-style" content="black">
<link rel="apple-touch-icon" href="%(icon)s">
<link rel="apple-touch-icon-precomposed" href="%(icon)s">
<style>
html,body{margin:0;height:100%%;background:#08080b;color:#f4f4f8;
font-family:-apple-system,Helvetica,Arial,sans-serif;text-align:center}
.wrap{padding:16%% 22px 0}
img{width:96px;height:96px;border-radius:22px;
-webkit-box-shadow:0 0 24px rgba(139,92,246,.45)}
.kicker{color:#22d3ee;letter-spacing:.16em;text-transform:uppercase;
font-size:11px;font-weight:600;margin-bottom:10px}
h1{font-weight:700;letter-spacing:-.03em;margin:12px 0 10px}
p{color:#9ca3af;font-size:14px;line-height:1.5}
a{display:inline-block;margin-top:16px;padding:10px 16px;border-radius:10px;
background:#8b5cf6;color:#fff;text-decoration:none;font-weight:600}
</style>
</head>
<body>
<div class="wrap">
<div class="kicker">BerryCore</div>
<img src="%(icon)s" alt="%(name)s">
<h1>%(name)s</h1>
<p>Overflow menu → Add to Home Screen → Save.<br>Title and icon are already set.</p>
<p><a href="%(url)s">Open %(name)s</a></p>
</div>
<script>
if (window.navigator && window.navigator.standalone) {
    window.location.replace(%(url_js)s);
}
</script>
</body>
</html>
""" % {
        "name": app["name"],
        "icon": icon,
        "url": url,
        "url_js": json.dumps(url),
    }


class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        sys.stderr.write("%s - %s\n" % (self.address_string(), fmt % args))

    def send_bytes(self, code, ctype, data, cache="no-cache"):
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Cache-Control", cache)
        self.end_headers()
        self.wfile.write(data)

    def send_json(self, obj):
        self.send_bytes(200, "application/json; charset=utf-8", json.dumps(obj).encode("utf-8"))

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path
        if path in ("/", "/index.html", "/setup"):
            self.send_bytes(200, "text/html; charset=utf-8", open(os.path.join(BASE, "index.html"), "rb").read())
            return
        if path in ("/apps", "/apps.html", "/catalog", "/catalog.html"):
            self.send_bytes(200, "text/html; charset=utf-8", open(os.path.join(BASE, "apps.html"), "rb").read())
            return
        if path in ("/manual", "/manual.html", "/docs", "/berrycore.html"):
            cat = catalog_path()
            if not cat:
                self.send_error(404)
                return
            self.send_bytes(200, "text/html; charset=utf-8", open(cat, "rb").read())
            return
        if path == "/static/style.css":
            self.send_bytes(200, "text/css", open(os.path.join(BASE, "static", "style.css"), "rb").read())
            return
        if path == "/static/app.js":
            self.send_bytes(200, "application/javascript", open(os.path.join(BASE, "static", "app.js"), "rb").read())
            return
        if path == "/icon.png":
            hub = {"id": "hub", "name": "BerryCore", "color": "139,92,246", "letters": "BC"}
            self.send_bytes(200, "image/png", icon_bytes(hub), "public, max-age=86400")
            return
        if path.startswith("/icon/") and path.endswith(".png"):
            app = find_app(path[6:-4])
            if not app:
                self.send_error(404)
                return
            self.send_bytes(200, "image/png", icon_bytes(app), "public, max-age=86400")
            return
        if path.startswith("/pin/"):
            app = find_app(path.split("/")[2])
            if not app:
                self.send_error(404)
                return
            self.send_bytes(200, "text/html; charset=utf-8", pin_html(app).encode("utf-8"))
            return
        if path == "/api/status":
            apps = []
            for app in load_apps():
                item = dict(app)
                item["up"] = port_up(app["port"])
                item["has_bin"] = os.path.isfile(bin_path(app["bin"]))
                apps.append(item)
            self.send_json({
                "status": "ok",
                "version": VERSION,
                "berrycore": BC_VERSION,
                "port": PORT,
                "catalog": bool(catalog_path()),
                "apps": apps,
            })
            return
        self.send_error(404)

    def do_POST(self):
        parsed = urllib.parse.urlparse(self.path)
        if parsed.path == "/api/start":
            length = int(self.headers.get("Content-Length", 0) or 0)
            body = self.rfile.read(length).decode("utf-8") if length else "{}"
            try:
                data = json.loads(body or "{}")
            except Exception:
                data = {}
            want = data.get("id")
            if not want:
                self.send_json({"status": "error", "error": "id required"})
                return
            results = []
            for app in load_apps():
                if app["id"] != want:
                    continue
                results.append(start_app(app))
            if not results:
                self.send_json({"status": "error", "error": "unknown id"})
                return
            self.send_json({"status": "ok", "results": results})
            return
        self.send_error(404)


def main():
    os.makedirs(ICON_DIR, exist_ok=True)
    httpd = ThreadedTCPServer(("0.0.0.0", PORT), Handler)
    print("BerryCore setup http://0.0.0.0:%d/" % PORT)
    httpd.serve_forever()


if __name__ == "__main__":
    main()
