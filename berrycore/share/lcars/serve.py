#!/usr/bin/env python3
"""BerryCore LCARS station — ES5 Photon-style desktop. Port 8110."""
import http.server
import json
import os
import socket
import socketserver
import subprocess
import sys
import threading
import time
import urllib.parse

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8110
VERSION = "1.7"
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
try:
    import sfx
except Exception:  # a broken sfx.py must not take the station down
    sfx = None
NATIVE = os.environ.get(
    "NATIVE_TOOLS",
    os.path.abspath(os.path.join(HERE, "..", "..")),
)
SETUP_APPS = os.path.join(HERE, "..", "setup", "apps.json")
STATE_DIR = os.path.join(NATIVE, ".tmp")
NOTES_PATH = os.path.join(STATE_DIR, "lcars-notes.json")
FILES_ROOT = os.path.join(STATE_DIR, "lcars-files")
PID_PATH = os.path.join(STATE_DIR, "lcars.pid")
VOICE_CACHE = os.path.join(STATE_DIR, "lcars-voice")
AUDIO_LOG = os.path.join(STATE_DIR, "lcars-audio.log")
BCLLM = os.environ.get("BCLLM_HOME", "/accounts/1000/shared/misc/bcllm")
DOCS = "/accounts/1000/shared/documents"
MISC = "/accounts/1000/shared/misc"
BOOKS = "/accounts/1000/shared/books"
FONT_DIR = "/usr/fonts/font_repository"
# Real LCARS is Swiss 911 Ultra Compressed. SlatePro Bold Condensed is the
# closest face already on a BB10 device; DejaVu Condensed is the fallback.
FONT_CANDIDATES = (
    os.path.join(FONT_DIR, "monotype", "SlatePro-BoldCondensed.ttf"),
    os.path.join(FONT_DIR, "monotype", "SlatePro-MediumCondensed.ttf"),
    os.path.join(FONT_DIR, "dejavu", "DejaVuSansCondensed-Bold.ttf"),
    os.path.join(FONT_DIR, "dejavu", "DejaVuSansCondensed.ttf"),
)
TEXT_EXT = (
    ".txt", ".md", ".html", ".htm", ".json", ".csv", ".log",
    ".py", ".sh", ".c", ".h", ".conf", ".css", ".js", ".xml",
)
BLOCK_NAMES = (
    "patreon.json", "id_rsa", "id_ed25519", ".env", "credentials.json",
    "authorized_keys", "berrycore-relay.env",
)
MAX_BYTES = 200000

LOCK = threading.Lock()
ASK = {"busy": False, "reply": "", "err": "", "ms": 0}


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True
    daemon_threads = True


def ensure_dirs():
    for path in (STATE_DIR, FILES_ROOT, VOICE_CACHE):
        try:
            os.makedirs(path)
        except OSError:
            pass


def lcars_font():
    # Drop a real LCARS face (Antonio, Swiss 911) at share/lcars/lcars.ttf or
    # point LCARS_FONT at one to override the on-device condensed fallback.
    for path in (os.environ.get("LCARS_FONT", ""), os.path.join(HERE, "lcars.ttf")):
        if path and os.path.isfile(path) and os.access(path, os.R_OK):
            return path
    for path in FONT_CANDIDATES:
        if os.path.isfile(path) and os.access(path, os.R_OK):
            return path
    return ""


def mime_for(path):
    ext = os.path.splitext(path)[1].lower()
    return {
        ".html": "text/html; charset=utf-8",
        ".js": "application/javascript; charset=utf-8",
        ".css": "text/css; charset=utf-8",
        ".txt": "text/plain; charset=utf-8",
        ".json": "application/json; charset=utf-8",
        ".png": "image/png",
    }.get(ext, "application/octet-stream")


def load_apps():
    path = SETUP_APPS
    if not os.path.isfile(path):
        path = os.path.join(HERE, "apps.json")
    try:
        return json.loads(open(path, "r").read())
    except Exception:
        return []


def bin_path(name):
    return os.path.join(NATIVE, "bin", name)


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


def find_app(app_id):
    for app in load_apps():
        if app.get("id") == app_id:
            return app
    return None


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
        # start_arg False means the bin is the server itself, with no start/stop
        # CLI — passing it "stop" would just try to launch a second copy.
        if os.path.isfile(path) and app.get("start_arg", True):
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


def app_status():
    rows = []
    for app in load_apps():
        item = dict(app)
        item["up"] = port_up(app["port"])
        item["has_bin"] = os.path.isfile(bin_path(app["bin"]))
        rows.append(item)
    return rows


def read_text(path, fallback=""):
    try:
        return open(path, "r").read().strip()
    except Exception:
        return fallback


def run_bin(name, args, timeout=4):
    path = bin_path(name)
    if not os.path.isfile(path):
        return ""
    try:
        out = subprocess.check_output(
            [path] + list(args),
            stderr=subprocess.STDOUT,
            timeout=timeout,
            cwd=NATIVE,
        )
        if isinstance(out, bytes):
            out = out.decode("utf-8", "replace")
        return out.strip()
    except Exception:
        return ""


def systems_snapshot():
    version = read_text(os.path.join(NATIVE, "VERSION"), "unknown")
    host = ""
    try:
        host = socket.gethostname()
    except Exception:
        host = "BLACKBERRY"
    return {
        "ok": True,
        "version": version,
        "host": host,
        "native": NATIVE,
        "port": PORT,
        "lcars": VERSION,
        "battery": run_bin("sensors", ["battery"]),
        "cpu": run_bin("sensors", ["cpu"]),
        "temp": run_bin("sensors", ["temp"]),
        "gps": run_bin("gps", ["last"]),
        "ai": bool(which_llama() and first_model()),
        "font": os.path.basename(lcars_font()) or "system",
    }


def roots():
    rows = [
        {"id": "documents", "name": "DOCUMENTS", "path": DOCS, "write": True},
        {"id": "station", "name": "STATION FILES", "path": FILES_ROOT, "write": True},
        {"id": "misc", "name": "MISC", "path": MISC, "write": False},
        {"id": "books", "name": "BOOKS", "path": BOOKS, "write": False},
        {"id": "berrycore", "name": "BERRYCORE", "path": NATIVE, "write": False},
    ]
    out = []
    for row in rows:
        row["present"] = os.path.isdir(row["path"])
        out.append(row)
    return out


LIBRARY_DIR = os.path.join(HERE, "library")


def library_items():
    """Return list of library entries from library/ dir or built-in defaults."""
    items = []
    if os.path.isdir(LIBRARY_DIR):
        for name in sorted(os.listdir(LIBRARY_DIR)):
            if name.startswith("."):
                continue
            path = os.path.join(LIBRARY_DIR, name)
            if not os.path.isfile(path):
                continue
            # Parse metadata from first lines if present (# TITLE: ..., # CAT: ...)
            title = name.rsplit(".", 1)[0].replace("-", " ").replace("_", " ").upper()
            cat = "reference"
            icon = title[:2] if len(title) >= 2 else "DC"
            color = "c-peach"
            try:
                with open(path, "r", encoding="utf-8", errors="replace") as fh:
                    for line in fh:
                        line = line.strip()
                        if not line.startswith("#"):
                            break
                        if line.upper().startswith("# TITLE:"):
                            title = line[8:].strip()
                        elif line.upper().startswith("# CAT:"):
                            cat = line[6:].strip().lower()
                        elif line.upper().startswith("# ICON:"):
                            icon = line[7:].strip()[:3]
                        elif line.upper().startswith("# COLOR:"):
                            color = line[8:].strip()
            except Exception:
                pass
            items.append({
                "title": title,
                "cat": cat,
                "icon": icon,
                "color": color,
                "file": name,
            })
    if not items:
        # Built-in sample entries
        items = [
            {"title": "FEDERATION CHARTER", "cat": "reference", "icon": "FC", "color": "c-lilac",
             "text": "We the lifeforms of the United Federation of Planets..."},
            {"title": "STARFLEET REGULATIONS", "cat": "technical", "icon": "SR", "color": "c-peach",
             "text": "GENERAL ORDER 1 (PRIME DIRECTIVE)..."},
        ]
    return items


def root_by_id(rid):
    for row in roots():
        if row["id"] == rid:
            return row
    return None


def blocked_name(name):
    low = os.path.basename(name).lower()
    for bad in BLOCK_NAMES:
        if low == bad or low.startswith("id_rsa") or low.endswith(".pem"):
            return True
    return False


def resolve_user_path(rid, rel):
    root = root_by_id(rid)
    if not root or not root["present"]:
        return None, "unknown root"
    rel = (rel or "").replace("\\", "/")
    if rel.startswith("/"):
        rel = rel[1:]
    parts = []
    for bit in rel.split("/"):
        if bit in ("", "."):
            continue
        if bit == ".." or blocked_name(bit):
            return None, "path not allowed"
        parts.append(bit)
    base = os.path.realpath(root["path"])
    target = os.path.realpath(os.path.join(base, *parts) if parts else base)
    if target != base and not target.startswith(base + os.sep):
        return None, "path not allowed"
    return {"root": root, "path": target, "rel": "/".join(parts)}, ""


def list_dir(rid, rel):
    found, err = resolve_user_path(rid, rel)
    if err:
        return {"ok": False, "error": err}
    path = found["path"]
    if not os.path.isdir(path):
        return {"ok": False, "error": "not a directory"}
    dirs = []
    files = []
    try:
        names = sorted(os.listdir(path))
    except OSError as exc:
        return {"ok": False, "error": str(exc)}
    for name in names:
        if name.startswith(".") or blocked_name(name):
            continue
        full = os.path.join(path, name)
        try:
            st = os.stat(full)
        except OSError:
            continue
        item = {
            "name": name,
            "dir": os.path.isdir(full),
            "size": st.st_size,
            "mtime": int(st.st_mtime),
        }
        if item["dir"]:
            dirs.append(item)
        else:
            files.append(item)
    return {
        "ok": True,
        "root": rid,
        "path": found["rel"],
        "write": found["root"]["write"],
        "dirs": dirs,
        "files": files,
    }


def read_user_file(rid, rel):
    found, err = resolve_user_path(rid, rel)
    if err:
        return {"ok": False, "error": err}
    path = found["path"]
    if not os.path.isfile(path):
        return {"ok": False, "error": "not a file"}
    ext = os.path.splitext(path)[1].lower()
    if ext not in TEXT_EXT:
        return {"ok": False, "error": "not a text file"}
    try:
        size = os.path.getsize(path)
    except OSError as exc:
        return {"ok": False, "error": str(exc)}
    if size > MAX_BYTES:
        return {"ok": False, "error": "file too large"}
    try:
        text = open(path, "r").read()
    except Exception as exc:
        return {"ok": False, "error": str(exc)}
    return {
        "ok": True,
        "root": rid,
        "path": found["rel"],
        "name": os.path.basename(path),
        "write": found["root"]["write"],
        "text": text,
        "size": size,
    }


def write_user_file(rid, rel, text):
    found, err = resolve_user_path(rid, rel)
    if err:
        return {"ok": False, "error": err}
    if not found["root"]["write"]:
        return {"ok": False, "error": "read only"}
    if not found["rel"] or found["rel"].endswith("/"):
        return {"ok": False, "error": "need a file name"}
    ext = os.path.splitext(found["rel"])[1].lower()
    if ext not in TEXT_EXT:
        return {"ok": False, "error": "text files only"}
    if not isinstance(text, str):
        text = str(text)
    if len(text.encode("utf-8")) > MAX_BYTES:
        return {"ok": False, "error": "too large"}
    folder = os.path.dirname(found["path"])
    try:
        if folder and not os.path.isdir(folder):
            os.makedirs(folder)
        tmp = found["path"] + ".tmp"
        open(tmp, "w").write(text)
        os.replace(tmp, found["path"])
    except Exception as exc:
        return {"ok": False, "error": str(exc)}
    return {"ok": True, "path": found["rel"]}


def safe_leaf(name):
    name = (name or "").strip().replace("\\", "/").split("/")[-1]
    if not name or name in (".", "..") or blocked_name(name):
        return ""
    if len(name) > 80:
        return ""
    for ch in name:
        if not (ch.isalnum() or ch in "._- "):
            return ""
    return name


def mkdir_user(rid, rel, name):
    leaf = safe_leaf(name)
    if not leaf:
        return {"ok": False, "error": "bad folder name"}
    found, err = resolve_user_path(rid, join_rel(rel, leaf))
    if err:
        return {"ok": False, "error": err}
    if not found["root"]["write"]:
        return {"ok": False, "error": "read only"}
    try:
        if not os.path.isdir(found["path"]):
            os.makedirs(found["path"])
    except Exception as exc:
        return {"ok": False, "error": str(exc)}
    return {"ok": True, "path": found["rel"]}


def delete_user(rid, rel):
    found, err = resolve_user_path(rid, rel)
    if err:
        return {"ok": False, "error": err}
    if not found["root"]["write"]:
        return {"ok": False, "error": "read only"}
    if not found["rel"]:
        return {"ok": False, "error": "cannot delete root"}
    path = found["path"]
    try:
        if os.path.isdir(path):
            if os.listdir(path):
                return {"ok": False, "error": "folder not empty"}
            os.rmdir(path)
        elif os.path.isfile(path):
            os.remove(path)
        else:
            return {"ok": False, "error": "missing"}
    except Exception as exc:
        return {"ok": False, "error": str(exc)}
    return {"ok": True, "path": found["rel"]}


def join_rel(base, name):
    if not base:
        return name
    return base.rstrip("/") + "/" + name


def load_notes():
    try:
        data = json.loads(open(NOTES_PATH, "r").read())
        if isinstance(data, dict) and isinstance(data.get("items"), list):
            return data
    except Exception:
        pass
    return {"items": []}


def save_notes(data):
    ensure_dirs()
    tmp = NOTES_PATH + ".tmp"
    open(tmp, "w").write(json.dumps(data))
    os.replace(tmp, NOTES_PATH)


def which_llama():
    names = [
        os.path.join(NATIVE, "bin", "llama-completion"),
        os.path.join(BCLLM, "bin", "llama-completion"),
    ]
    for path in names:
        if os.path.isfile(path) and os.access(path, os.X_OK):
            return path
    return ""


def first_model():
    models = os.path.join(BCLLM, "models")
    if not os.path.isdir(models):
        return ""
    prefer = ""
    try:
        names = sorted(os.listdir(models))
    except OSError:
        return ""
    for name in names:
        if not name.endswith(".gguf"):
            continue
        path = os.path.join(models, name)
        low = name.lower()
        if "135" in low:
            return path
        if not prefer:
            prefer = path
    return prefer


def extract_reply(raw):
    if not raw:
        return ""
    text = raw.decode("utf-8", "replace") if isinstance(raw, bytes) else raw
    keep = []
    on = False
    saw = False
    for line in text.splitlines():
        if "generate: n_ctx" in line:
            on = True
            saw = True
            continue
        if "common_perf_print" in line:
            on = False
            continue
        if on and not line.startswith("0."):
            keep.append(line)
    body = "\n".join(keep).strip() if saw else ""
    if not body:
        skip = ("Thinking", "---", "llama_", "main:", "print_info", "load_tensors", "ggml_")
        lines = []
        for line in text.splitlines():
            s = line.strip()
            if not s:
                continue
            bad = False
            for p in skip:
                if s.startswith(p) or p in s[:24]:
                    bad = True
                    break
            if not bad:
                lines.append(s)
        body = " ".join(lines).strip()
    return body.replace("[end of text]", "").strip()


def ask_llm(prompt):
    llama = which_llama()
    model = first_model()
    if not llama or not model:
        return "", "AI missing — qpkg install bcllm && ai download smollm2_135m"
    cmd = [
        llama, "-m", model, "-t", "2", "-c", "256",
        "-b", "32", "-fa", "off", "--no-warmup", "--simple-io", "-st",
        "--reasoning", "off", "--temp", "0.5", "-n", "48",
        "--no-display-prompt",
        "-sys", "You are BerryCore LCARS on a BlackBerry Passport. Be brief. No markdown.",
        "-p", prompt,
    ]
    env = os.environ.copy()
    env["LD_LIBRARY_PATH"] = "%s:%s:%s" % (
        os.path.join(BCLLM, "lib"),
        os.path.join(NATIVE, "lib"),
        env.get("LD_LIBRARY_PATH", ""),
    )
    try:
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, env=env)
        out, _ = proc.communicate(timeout=120)
    except subprocess.TimeoutExpired:
        try:
            proc.kill()
        except Exception:
            pass
        return "", "AI timed out"
    except Exception as exc:
        return "", str(exc)
    text = extract_reply(out)
    if not text:
        return "", "empty reply"
    return text, ""


def ask_worker(prompt):
    t0 = time.time()
    reply, err = ask_llm(prompt)
    with LOCK:
        ASK["busy"] = False
        ASK["reply"] = reply
        ASK["err"] = err
        ASK["ms"] = int((time.time() - t0) * 1000)


def audio_caps():
    """What the device can do, so the AUDIO panel can show it plainly."""
    if not sfx:
        return {"sfx": False, "voices": [], "fx": False, "sounds": []}
    return {
        "sfx": True,
        "voices": sfx.voices(),
        "fx": bool(sfx.ffmpeg_bin()),
        "speaker": bool(sfx.speaker_play.__doc__),
        "sounds": sorted(sfx.SOUNDS.keys()),
        "rate": sfx.RATE,
    }


def log_audio_report(report):
    """Record what the browser reported it supports.

    The BB10 browser cannot be inspected remotely, so this log is the only way
    to find out whether Web Audio actually worked on the device.
    """
    try:
        report["at"] = time.strftime("%Y-%m-%d %H:%M:%S")
        with open(AUDIO_LOG, "a") as fh:
            fh.write(json.dumps(report)[:2000] + "\n")
        return True
    except Exception:
        return False


class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        sys.stderr.write("[%s] %s\n" % (time.strftime("%H:%M:%S"), fmt % args))

    def send_json(self, obj, code=200):
        body = json.dumps(obj).encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def send_file(self, path, content_type=None):
        if not os.path.isfile(path):
            self.send_error(404)
            return
        with open(path, "rb") as fh:
            data = fh.read()
        self.send_response(200)
        self.send_header("Content-Type", content_type or mime_for(path))
        self.send_header("Content-Length", str(len(data)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(data)

    def send_audio(self, data, engine=""):
        self.send_response(200)
        self.send_header("Content-Type", "audio/wav")
        self.send_header("Content-Length", str(len(data)))
        # Beeps and repeated voice lines are identical every time, so let the
        # browser keep them instead of re-fetching on every tap.
        self.send_header("Cache-Control", "public, max-age=604800")
        if engine:
            self.send_header("X-Voice-Engine", engine)
        self.end_headers()
        self.wfile.write(data)

    def read_json(self):
        try:
            n = int(self.headers.get("Content-Length") or 0)
        except Exception:
            n = 0
        if n > MAX_BYTES:
            n = MAX_BYTES
        raw = self.rfile.read(n) if n else b""
        if not raw:
            return {}
        try:
            return json.loads(raw.decode("utf-8", "replace"))
        except Exception:
            return {}

    def do_GET(self):
        path = self.path.split("?", 1)[0]
        query = {}
        if "?" in self.path:
            for pair in self.path.split("?", 1)[1].split("&"):
                if "=" in pair:
                    k, v = pair.split("=", 1)
                    query[urllib.parse.unquote(k)] = urllib.parse.unquote(v)
        if path == "/favicon.ico":
            self.send_response(204)
            self.end_headers()
            return
        if path in ("/", "/index.html"):
            self.send_file(os.path.join(HERE, "index.html"))
            return
        if path.startswith("/static/"):
            name = os.path.basename(path)
            if name.startswith("."):
                self.send_error(404)
                return
            self.send_file(os.path.join(HERE, "static", name))
            return
        if path.startswith("/apps/"):
            name = os.path.basename(path)
            if name.startswith(".") or ".." in path:
                self.send_error(404)
                return
            app_path = os.path.join(HERE, "apps", name)
            if os.path.isfile(app_path):
                self.send_file(app_path)
            else:
                self.send_error(404)
            return
        if path == "/api/library":
            self.send_json({"ok": True, "items": library_items()})
            return
        if path.startswith("/library/"):
            name = os.path.basename(path)
            if name.startswith(".") or ".." in path:
                self.send_error(404)
                return
            lib_path = os.path.join(NATIVE, "share", "lcars", "library", name)
            if os.path.isfile(lib_path):
                self.send_file(lib_path, content_type="text/plain; charset=utf-8")
            else:
                self.send_error(404)
            return
        if path.startswith("/sound/") and path.endswith(".wav"):
            if not sfx:
                self.send_error(404)
                return
            data = sfx.sound_wav(os.path.basename(path)[:-4])
            if not data:
                self.send_error(404)
                return
            self.send_audio(data)
            return
        if path == "/api/sounds":
            if not sfx:
                self.send_json({"ok": False, "error": "sfx unavailable"})
                return
            self.send_json({"ok": True, "data": sfx.recipes()})
            return
        if path == "/api/audio":
            self.send_json({"ok": True, "data": audio_caps()})
            return
        if path == "/voice.wav":
            if not sfx:
                self.send_error(404)
                return
            data, engine = sfx.voice_wav(
                query.get("say") or "",
                query.get("v") or "auto",
                (query.get("fx") or "1") != "0",
                VOICE_CACHE,
            )
            if not data:
                self.send_response(503)
                self.send_header("Content-Type", "text/plain; charset=utf-8")
                self.send_header("X-Voice-Error", engine)
                self.end_headers()
                self.wfile.write(engine.encode("utf-8"))
                return
            sfx.trim_cache(VOICE_CACHE)
            self.send_audio(data, engine)
            return
        if path == "/font/lcars.ttf":
            font = lcars_font()
            if not font:
                self.send_error(404)
                return
            with open(font, "rb") as fh:
                data = fh.read()
            self.send_response(200)
            self.send_header("Content-Type", "font/ttf")
            self.send_header("Content-Length", str(len(data)))
            self.send_header("Cache-Control", "public, max-age=604800")
            self.end_headers()
            self.wfile.write(data)
            return
        if path == "/api/status":
            apps = app_status()
            running = 0
            for app in apps:
                if app.get("up"):
                    running += 1
            self.send_json({
                "ok": True,
                "app": "lcars",
                "version": VERSION,
                "port": PORT,
                "berrycore": read_text(os.path.join(NATIVE, "VERSION"), ""),
                "running": running,
                "apps": apps,
            })
            return
        if path == "/api/systems":
            self.send_json(systems_snapshot())
            return
        if path == "/api/notes":
            self.send_json({"ok": True, "data": load_notes()})
            return
        if path == "/api/roots":
            self.send_json({"ok": True, "roots": roots()})
            return
        if path == "/api/files":
            self.send_json(list_dir(query.get("root") or "documents", query.get("path") or ""))
            return
        if path == "/api/file":
            self.send_json(read_user_file(query.get("root") or "documents", query.get("path") or ""))
            return
        if path == "/api/ask":
            with LOCK:
                snap = dict(ASK)
            self.send_json({"ok": True, "data": snap})
            return
        self.send_error(404)

    def do_POST(self):
        path = self.path.split("?", 1)[0]
        body = self.read_json()
        if path == "/api/start":
            app = find_app(body.get("id"))
            if not app:
                self.send_json({"status": "error", "error": "unknown id"})
                return
            result = start_app(app)
            self.send_json({"status": "ok", "results": [result]})
            return
        if path == "/api/stop":
            app = find_app(body.get("id"))
            if not app:
                self.send_json({"status": "error", "error": "unknown id"})
                return
            result = stop_app(app)
            self.send_json({"status": "ok", "results": [result]})
            return
        if path == "/api/notes":
            text = (body.get("text") or "").strip()
            if not text:
                self.send_json({"ok": False, "error": "empty note"}, 400)
                return
            data = load_notes()
            data["items"].append({"text": text[:4000], "ts": int(time.time())})
            data["items"] = data["items"][-80:]
            try:
                save_notes(data)
            except Exception as exc:
                self.send_json({"ok": False, "error": str(exc)}, 500)
                return
            self.send_json({"ok": True, "data": data})
            return
        if path == "/api/file":
            self.send_json(write_user_file(
                body.get("root") or "documents",
                body.get("path") or "",
                body.get("text") or "",
            ))
            return
        if path == "/api/mkdir":
            self.send_json(mkdir_user(
                body.get("root") or "documents",
                body.get("path") or "",
                body.get("name") or "",
            ))
            return
        if path == "/api/delete":
            self.send_json(delete_user(
                body.get("root") or "documents",
                body.get("path") or "",
            ))
            return
        if path == "/api/ask":
            prompt = (body.get("text") or "").strip()
            if not prompt:
                self.send_json({"ok": False, "error": "empty"}, 400)
                return
            with LOCK:
                if ASK["busy"]:
                    self.send_json({"ok": True, "busy": True})
                    return
                ASK["busy"] = True
                ASK["reply"] = ""
                ASK["err"] = ""
                ASK["ms"] = 0
            thread = threading.Thread(target=ask_worker, args=(prompt,))
            thread.daemon = True
            thread.start()
            self.send_json({"ok": True, "busy": True})
            return
        if path == "/api/audio-report":
            report = {
                "ua": (self.headers.get("User-Agent") or "")[:300],
                "engine": str(body.get("engine"))[:40],
                "ctx": str(body.get("ctx"))[:40],
                "html": bool(body.get("html")),
                "wav": str(body.get("wav"))[:20],
                "unlocked": bool(body.get("unlocked")),
                "screen": str(body.get("screen"))[:20],
                "err": str(body.get("err"))[:200],
            }
            self.send_json({"ok": log_audio_report(report)})
            return
        if path == "/api/speak":
            if not sfx:
                self.send_json({"ok": False, "error": "sfx unavailable"})
                return
            data, engine = sfx.voice_wav(
                body.get("text") or "",
                body.get("voice") or "auto",
                body.get("fx", True) is not False,
                VOICE_CACHE,
            )
            if not data:
                self.send_json({"ok": False, "error": engine})
                return
            ok, err = sfx.speaker_play(data)
            self.send_json({"ok": ok, "error": err, "engine": engine})
            return
        if path == "/api/sfx":
            if not sfx:
                self.send_json({"ok": False, "error": "sfx unavailable"})
                return
            name = body.get("name") or ""
            if name not in sfx.SOUNDS:
                self.send_json({"ok": False, "error": "unknown sound"})
                return
            data = sfx.sound_wav(name)
            if not data:
                self.send_json({"ok": False, "error": "render failed"})
                return
            ok, err = sfx.speaker_play(data)
            self.send_json({"ok": ok, "error": err})
            return
        self.send_error(404)

    def do_HEAD(self):
        self.do_GET()


def main():
    ensure_dirs()
    try:
        open(PID_PATH, "w").write(str(os.getpid()))
    except Exception:
        pass
    httpd = ThreadedTCPServer(("127.0.0.1", PORT), Handler)
    print("LCARS v%s on http://127.0.0.1:%s" % (VERSION, PORT))
    sys.stdout.flush()
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
