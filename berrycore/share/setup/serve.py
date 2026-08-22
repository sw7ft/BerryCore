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
import time
import urllib.parse
import zlib

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8098
BASE = os.path.dirname(os.path.abspath(__file__))
NATIVE = os.environ.get("NATIVE_TOOLS", os.path.normpath(os.path.join(BASE, "..", "..")))
ICON_DIR = os.path.join(BASE, "icons")
VERSION = "2.2"
BC_VERSION = "0.88.0"
_PKG_JOBS = {}
_PKG_FAIL = {}


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


def wait_port(port, want, tries=6, delay=0.16):
    i = 0
    while i < tries:
        if port_up(port) == want:
            return True
        time.sleep(delay)
        i += 1
    return port_up(port) == want


def start_app(app):
    path = bin_path(app["bin"])
    if not os.path.isfile(path):
        return {"id": app["id"], "started": False, "up": False, "error": "bin missing"}
    if port_up(app["port"]):
        return {"id": app["id"], "started": True, "up": True, "already": True}
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
        up = wait_port(app["port"], True)
        return {"id": app["id"], "started": True, "up": up, "already": False}
    except Exception as exc:
        return {"id": app["id"], "started": False, "up": False, "error": str(exc)}


def stop_app(app):
    path = bin_path(app["bin"])
    if not port_up(app["port"]):
        return {"id": app["id"], "stopped": True, "up": False, "already": True}
    try:
        if os.path.isfile(path):
            subprocess.call(
                [path, "stop"],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                cwd=NATIVE,
            )
        if port_up(app["port"]):
            subprocess.call(
                ["slay", "-f", app.get("slay") or app["bin"]],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
            )
        down = wait_port(app["port"], False)
        return {"id": app["id"], "stopped": down, "up": not down}
    except Exception as exc:
        return {"id": app["id"], "stopped": False, "up": port_up(app["port"]), "error": str(exc)}


def pkg_root():
    return os.environ.get("NATIVE_TOOLS") or os.path.dirname(os.path.dirname(BASE))


def pkg_catalog_path():
    native = pkg_root()
    for path in (
        os.path.join(native, ".cache", "qpkg", "PACKAGES"),
        os.path.join(BASE, "PACKAGES"),
        os.path.join(native, "share", "setup", "PACKAGES"),
        os.path.join(native, "ports", "PACKAGES"),
    ):
        if os.path.isfile(path):
            return path
    return ""


def pkg_installed_map():
    found = {}
    native = pkg_root()
    log = os.path.join(native, ".qpkg", "installed")
    if os.path.isfile(log):
        try:
            with open(log) as fh:
                for line in fh:
                    line = line.strip()
                    if not line or line.startswith("#") or "|" not in line:
                        continue
                    parts = line.split("|")
                    name = parts[0].strip()
                    if name:
                        found[name] = {
                            "ver": parts[1].strip() if len(parts) > 1 else "",
                            "date": parts[2].strip() if len(parts) > 2 else "",
                            "zip": parts[3].strip() if len(parts) > 3 else "",
                        }
        except OSError:
            pass
    bindir = os.path.join(native, "bin")
    if os.path.isdir(bindir):
        try:
            for name in os.listdir(bindir):
                path = os.path.join(bindir, name)
                if os.path.isfile(path) and os.access(path, os.X_OK):
                    found.setdefault(name, {"ver": "", "date": "", "zip": ""})
        except OSError:
            pass
    return found


def bundled_zips():
    names = set()
    pkgdir = os.path.join(pkg_root(), "packages")
    if os.path.isdir(pkgdir):
        try:
            for name in os.listdir(pkgdir):
                if name.endswith(".zip"):
                    names.add(name)
        except OSError:
            pass
    return names


def parse_packages():
    path = pkg_catalog_path()
    rows = []
    installed = pkg_installed_map()
    zips = bundled_zips()
    if path:
        try:
            with open(path) as fh:
                for line in fh:
                    line = line.strip()
                    if not line or line.startswith("#") or "|" not in line:
                        continue
                    parts = line.split("|")
                    while len(parts) < 7:
                        parts.append("")
                    name = parts[0].strip()
                    if not name:
                        continue
                    zipname = parts[5].strip()
                    rows.append({
                        "name": name,
                        "cat": parts[1].strip() or "other",
                        "ver": parts[2].strip(),
                        "size": parts[3].strip(),
                        "desc": parts[4].strip(),
                        "zip": zipname,
                        "replaces": parts[6].strip(),
                        "installed": name in installed,
                        "bundled": zipname in zips,
                        "busy": name in _PKG_JOBS and _PKG_JOBS[name].poll() is None,
                        "fail": _PKG_FAIL.get(name, ""),
                    })
        except OSError:
            pass
    return rows, path


def valid_pkg_name(name):
    if not name or len(name) > 64:
        return False
    for ch in name:
        if not (ch.isalnum() or ch in "._-"):
            return False
    return True


def prune_pkg_jobs():
    done = []
    for name, proc in list(_PKG_JOBS.items()):
        code = proc.poll()
        if code is None:
            continue
        done.append(name)
        if code != 0:
            _PKG_FAIL[name] = "install failed (exit %s)" % code
        else:
            _PKG_FAIL.pop(name, None)
    for name in done:
        _PKG_JOBS.pop(name, None)


def start_pkg_install(name):
    prune_pkg_jobs()
    if not valid_pkg_name(name):
        return {"error": "bad package name"}
    if name in _PKG_JOBS and _PKG_JOBS[name].poll() is None:
        return {"status": "ok", "already": True, "busy": True}
    rows, _path = parse_packages()
    catalog = {row["name"]: row for row in rows}
    if name not in catalog:
        return {"error": "unknown package"}
    qpkg = os.path.join(pkg_root(), "bin", "qpkg")
    if not os.path.isfile(qpkg):
        return {"error": "qpkg not found"}
    env = os.environ.copy()
    env["NATIVE_TOOLS"] = pkg_root()
    env["QPKG_YES"] = "1"
    tmp = os.path.join(pkg_root(), ".tmp")
    try:
        os.makedirs(tmp, exist_ok=True)
    except OSError:
        pass
    log = os.path.join(tmp, "qpkg-install-%s.log" % name)
    try:
        logf = open(log, "wb")
        proc = subprocess.Popen(
            [qpkg, "install", name],
            stdin=subprocess.PIPE,
            stdout=logf,
            stderr=subprocess.STDOUT,
            env=env,
        )
        logf.close()
        try:
            proc.stdin.write(b"y\n")
            proc.stdin.close()
        except Exception:
            pass
        _PKG_JOBS[name] = proc
        _PKG_FAIL.pop(name, None)
        return {"status": "ok", "name": name}
    except Exception as exc:
        return {"error": str(exc)}


HUB_THEMES = {
    "aubergine": {"bg": [48, 10, 36], "fg": [238, 238, 238]},
    "midnight": {"bg": [11, 11, 16], "fg": [232, 232, 238]},
    "ember": {"bg": [44, 0, 30], "fg": [238, 238, 238]},
    "paper": {"bg": [244, 239, 230], "fg": [42, 31, 24]},
}


def hub_theme_path():
    return os.path.join(pkg_root(), ".tmp", "hub-theme")


def read_hub_theme():
    path = hub_theme_path()
    if os.path.isfile(path):
        try:
            name = open(path).read().strip()
            if name in HUB_THEMES:
                return name
        except OSError:
            pass
    return "aubergine"


def write_term48_colors(theme):
    colors = HUB_THEMES.get(theme)
    if not colors:
        return False
    bg = colors["bg"]
    fg = colors["fg"]
    written = 0
    homes = [
        os.path.join(pkg_root(), "share", "term48rc"),
        os.path.join(os.path.expanduser("~"), ".term48rc"),
    ]
    for path in homes:
        if not os.path.isfile(path):
            continue
        try:
            text = open(path).read()
            lines = []
            for line in text.splitlines():
                if line.startswith("background_color"):
                    lines.append("background_color = [ %d, %d, %d ];" % (bg[0], bg[1], bg[2]))
                elif line.startswith("text_color"):
                    lines.append("text_color = [ %d, %d, %d ];" % (fg[0], fg[1], fg[2]))
                else:
                    lines.append(line)
            open(path, "w").write("\n".join(lines) + "\n")
            written += 1
        except OSError:
            pass
    return written > 0


def set_hub_theme(name):
    if name not in HUB_THEMES:
        return {"error": "unknown theme"}
    tmp = os.path.join(pkg_root(), ".tmp")
    try:
        os.makedirs(tmp, exist_ok=True)
        open(hub_theme_path(), "w").write(name + "\n")
    except OSError as exc:
        return {"error": str(exc)}
    term = write_term48_colors(name)
    return {"status": "ok", "theme": name, "term48": term}


def core_catalog_path():
    for path in (
        os.path.join(pkg_root(), "CATALOG"),
        os.path.join(NATIVE, "CATALOG"),
        os.path.join(BASE, "CATALOG"),
    ):
        if os.path.isfile(path):
            return path
    return ""


def installed_bin_names():
    names = set()
    bindir = os.path.join(pkg_root(), "bin")
    if not os.path.isdir(bindir):
        return names
    try:
        for name in os.listdir(bindir):
            if name.startswith("."):
                continue
            path = os.path.join(bindir, name)
            if os.path.isfile(path) or os.path.islink(path):
                names.add(name)
    except OSError:
        pass
    return names


def parse_core():
    present = installed_bin_names()
    rows = []
    seen = set()
    path = core_catalog_path()
    if path:
        try:
            with open(path) as fh:
                for line in fh:
                    line = line.strip()
                    if not line or line.startswith("#") or "|" not in line:
                        continue
                    parts = line.split("|")
                    while len(parts) < 3:
                        parts.append("")
                    name = parts[0].strip()
                    if not name or name in seen:
                        continue
                    desc = parts[2].strip()
                    port = "qpkg install" in desc.lower()
                    seen.add(name)
                    rows.append({
                        "name": name,
                        "cat": parts[1].strip() or "util",
                        "desc": desc,
                        "present": name in present,
                        "port": port,
                        "core": not port,
                        "extra": False,
                    })
        except OSError:
            pass
    extras = sorted(present - seen)
    for name in extras:
        rows.append({
            "name": name,
            "cat": "extra",
            "desc": "On this device — not in the core catalog",
            "present": True,
            "port": False,
            "core": False,
            "extra": True,
        })
    return rows, path


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
        if path in ("/packages", "/packages.html", "/pkg", "/qpkg"):
            self.send_bytes(200, "text/html; charset=utf-8", open(os.path.join(BASE, "packages.html"), "rb").read())
            return
        if path in ("/core", "/core.html", "/bins", "/installed"):
            self.send_bytes(200, "text/html; charset=utf-8", open(os.path.join(BASE, "core.html"), "rb").read())
            return
        if path in ("/settings", "/settings.html"):
            self.send_bytes(200, "text/html; charset=utf-8", open(os.path.join(BASE, "settings.html"), "rb").read())
            return
        if path in ("/manual", "/manual.html", "/docs"):
            self.send_bytes(200, "text/html; charset=utf-8", open(os.path.join(BASE, "manual.html"), "rb").read())
            return
        if path in ("/berrycore.html", "/classic"):
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
        if path == "/static/packages.js":
            self.send_bytes(200, "application/javascript", open(os.path.join(BASE, "static", "packages.js"), "rb").read())
            return
        if path == "/static/core.js":
            self.send_bytes(200, "application/javascript", open(os.path.join(BASE, "static", "core.js"), "rb").read())
            return
        if path == "/static/manual.js":
            self.send_bytes(200, "application/javascript", open(os.path.join(BASE, "static", "manual.js"), "rb").read())
            return
        if path == "/static/theme.js":
            self.send_bytes(200, "application/javascript", open(os.path.join(BASE, "static", "theme.js"), "rb").read())
            return
        if path == "/static/settings.js":
            self.send_bytes(200, "application/javascript", open(os.path.join(BASE, "static", "settings.js"), "rb").read())
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
        if path == "/api/packages":
            prune_pkg_jobs()
            rows, src = parse_packages()
            self.send_json({
                "status": "ok",
                "source": src,
                "packages": rows,
            })
            return
        if path == "/api/core":
            rows, src = parse_core()
            self.send_json({
                "status": "ok",
                "source": src,
                "bins": rows,
            })
            return
        if path == "/api/theme":
            self.send_json({"status": "ok", "theme": read_hub_theme()})
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
        if parsed.path == "/api/stop":
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
                results.append(stop_app(app))
            if not results:
                self.send_json({"status": "error", "error": "unknown id"})
                return
            self.send_json({"status": "ok", "results": results})
            return
        if parsed.path == "/api/pkg/install":
            length = int(self.headers.get("Content-Length", 0) or 0)
            body = self.rfile.read(length).decode("utf-8") if length else "{}"
            try:
                data = json.loads(body or "{}")
            except Exception:
                data = {}
            name = (data.get("name") or "").strip()
            if not name:
                self.send_json({"status": "error", "error": "name required"})
                return
            result = start_pkg_install(name)
            if result.get("error"):
                self.send_json({"status": "error", "error": result["error"]})
                return
            self.send_json(result)
            return
        if parsed.path == "/api/theme":
            length = int(self.headers.get("Content-Length", 0) or 0)
            body = self.rfile.read(length).decode("utf-8") if length else "{}"
            try:
                data = json.loads(body or "{}")
            except Exception:
                data = {}
            result = set_hub_theme((data.get("theme") or "").strip())
            if result.get("error"):
                self.send_json({"status": "error", "error": result["error"]})
                return
            self.send_json(result)
            return
        self.send_error(404)


def main():
    os.makedirs(ICON_DIR, exist_ok=True)
    httpd = ThreadedTCPServer(("0.0.0.0", PORT), Handler)
    print("BerryCore setup http://0.0.0.0:%d/" % PORT)
    httpd.serve_forever()


if __name__ == "__main__":
    main()
