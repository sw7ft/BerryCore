#!/usr/bin/env python3
"""STT lab — compare PocketSphinx and Vosk on the same clip. Port 8093."""
import json
import os
import shutil
import struct
import subprocess
import sys
import threading
import time
import tempfile
from http.server import BaseHTTPRequestHandler, HTTPServer

try:
    from socketserver import ThreadingMixIn
except ImportError:
    class ThreadingMixIn(object):
        pass

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8093
ROOT = os.path.dirname(os.path.abspath(__file__))


def resolve_stt_root():
    env = os.environ.get("STT_ROOT")
    if env:
        return env
    native = os.path.abspath(os.path.join(ROOT, "..", ".."))
    legacy = "/accounts/1000/shared/misc/stt"
    if os.path.isfile(os.path.join(native, "lib", "libvosk.so")) or os.path.isdir(
        os.path.join(native, "share", "stt", "model", "vosk-en")
    ):
        return native
    if os.path.isdir(legacy):
        return legacy
    return native


STT_ROOT = resolve_stt_root()


def vosk_lib_path():
    for p in (
        os.path.join(STT_ROOT, "lib", "libvosk.so"),
        os.path.join(STT_ROOT, "share", "stt", "lib", "libvosk.so"),
        "/accounts/1000/shared/misc/stt/lib/libvosk.so",
    ):
        if os.path.isfile(p):
            return p
    return os.path.join(STT_ROOT, "lib", "libvosk.so")


def vosk_model_path():
    for p in (
        os.path.join(STT_ROOT, "share", "stt", "model", "vosk-en"),
        os.path.join(STT_ROOT, "model", "vosk-en"),
        "/accounts/1000/shared/misc/stt/model/vosk-en",
    ):
        if os.path.isdir(p):
            return p
    return os.path.join(STT_ROOT, "share", "stt", "model", "vosk-en")

FFMPEG = os.environ.get("FFMPEG", "ffmpeg")
for p in (
    "/accounts/1000/shared/misc/clitools/bin/ffmpeg",
    "/accounts/1000/shared/misc/berrycore/bin/ffmpeg",
):
    if os.path.isfile(p):
        FFMPEG = p
        break


RECORD = {"proc": None, "path": None, "method": None, "dev": None}


def find_pcm_capture():
    snd = "/dev/snd"
    if not os.path.isdir(snd):
        return None
    for name in ("defaultc", "handsetc"):
        p = os.path.join(snd, name)
        if os.path.exists(p):
            return p
    try:
        for entry in os.listdir(snd):
            if entry.startswith("pcm") and entry.endswith("c"):
                return os.path.join(snd, entry)
    except Exception:
        pass
    return None


def detect_record():
    if RECORD["method"]:
        return RECORD["method"], RECORD["dev"]
    dev = find_pcm_capture()
    if dev:
        try:
            fd = os.open(dev, os.O_RDONLY | os.O_NONBLOCK)
            os.close(fd)
            RECORD["method"] = "pcm"
            RECORD["dev"] = dev
            return "pcm", dev
        except Exception:
            pass
    return None, None


def which_engines():
    method, _dev = detect_record()
    return {
        "sphinx": os.path.isfile(os.path.join(STT_ROOT, "bin", "pocketsphinx_batch")),
        "vosk": os.path.isfile(vosk_lib_path()),
        "vosk_warm": VOSK.ready,
        "stt_root": STT_ROOT,
        "record": method is not None,
        "record_method": method or "",
        "stream": VOSK.streaming,
    }


def upload_name(content_type):
    ct = (content_type or "").split(";")[0].strip().lower()
    if "m4a" in ct or ct in ("audio/mp4", "audio/x-m4a", "audio/aac"):
        return "upload.m4a"
    if "wav" in ct:
        return "upload.wav"
    if "webm" in ct:
        return "upload.webm"
    if "mpeg" in ct or "mp3" in ct:
        return "upload.mp3"
    if "ogg" in ct:
        return "upload.ogg"
    return "upload.bin"


def run_cmd(cmd, timeout=180, env=None):
    t0 = time.time()
    try:
        p = subprocess.Popen(
            cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env
        )
        out, err = p.communicate(timeout=timeout)
        return {
            "ok": p.returncode == 0,
            "text": (out or b"").decode("utf-8", "replace").strip(),
            "err": (err or b"").decode("utf-8", "replace")[-800:],
            "ms": int((time.time() - t0) * 1000),
            "rc": p.returncode,
        }
    except Exception as e:
        return {"ok": False, "text": "", "err": str(e), "ms": int((time.time() - t0) * 1000), "rc": -1}


def ffmpeg_in(src_path):
    """Prefix args so raw PCM is not guessed as an image."""
    low = src_path.lower()
    if low.endswith(".raw") or low.endswith(".pcm"):
        return ["-f", "s16le", "-ar", "16000", "-ac", "1", "-i", src_path]
    return ["-i", src_path]


def to_wavs(src_path, work, want_8=True, want_16=True):
    """Make 8 kHz (Sphinx) and/or 16 kHz (Vosk) mono WAVs in parallel."""
    wav8 = os.path.join(work, "clip8.wav")
    wav16 = os.path.join(work, "clip16.wav")
    box = {}
    threads = []

    def _8():
        box["r8"] = run_cmd(
            [FFMPEG, "-y"] + ffmpeg_in(src_path) + ["-ar", "8000", "-ac", "1", wav8],
            timeout=60,
        )

    def _16():
        box["r16"] = run_cmd(
            [FFMPEG, "-y"] + ffmpeg_in(src_path) + ["-ar", "16000", "-ac", "1", wav16],
            timeout=60,
        )

    if want_8:
        t1 = threading.Thread(target=_8)
        threads.append(t1)
        t1.start()
    if want_16:
        t2 = threading.Thread(target=_16)
        threads.append(t2)
        t2.start()
    for t in threads:
        t.join()
    r8 = box.get("r8") or {"ok": False, "err": ""}
    r16 = box.get("r16") or {"ok": False, "err": ""}
    return wav8 if r8.get("ok") else None, wav16 if r16.get("ok") else None, r8, r16


def decode_sphinx(wav8):
    stt = os.path.join(STT_ROOT, "bin", "stt")
    if os.path.isfile(stt):
        r = run_cmd([stt, wav8], timeout=180)
        if r["ok"] and r["text"]:
            return r
    # fallback: pocketsphinx_batch directly
    batch = os.path.join(STT_ROOT, "bin", "pocketsphinx_batch")
    hmm = os.path.join(STT_ROOT, "model", "hmm-en_US", "hub4wsj_sc_8k")
    lm = os.path.join(STT_ROOT, "model", "lm-en_US", "hub4.5000.DMP")
    dic = os.path.join(STT_ROOT, "model", "lm-en_US", "cmu07a.dic")
    work = os.path.dirname(wav8)
    ctl = os.path.join(work, "clip8.ctl")
    hyp = os.path.join(work, "clip8.hyp")
    with open(ctl, "w") as f:
        f.write("clip8\n")
    env = os.environ.copy()
    env["LD_LIBRARY_PATH"] = os.path.join(STT_ROOT, "lib") + ":" + env.get("LD_LIBRARY_PATH", "")
    t0 = time.time()
    try:
        p = subprocess.Popen(
            [batch, "-hmm", hmm, "-lm", lm, "-dict", dic,
             "-cepdir", work, "-cepext", ".wav", "-ctl", ctl,
             "-adcin", "yes", "-adchdr", "44", "-samprate", "8000", "-hyp", hyp],
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env,
        )
        _, err = p.communicate(timeout=180)
        text = ""
        if os.path.isfile(hyp):
            line = open(hyp).read().strip()
            if " (" in line:
                line = line.rsplit(" (", 1)[0]
            text = line
        return {
            "ok": bool(text),
            "text": text,
            "err": (err or b"").decode("utf-8", "replace")[-400:],
            "ms": int((time.time() - t0) * 1000),
            "rc": p.returncode,
        }
    except Exception as e:
        return {"ok": False, "text": "", "err": str(e), "ms": int((time.time() - t0) * 1000), "rc": -1}


class VoskEngine(object):
    """Keep libvosk + model loaded. Reloading is ~12s on the Passport."""

    def __init__(self):
        self.lib = None
        self.model = None
        self.rec = None
        self.rate = 16000
        self.lock = threading.Lock()
        self.err = ""
        self.ready = False
        self.streaming = False
        self.partial = ""
        self.committed = ""
        self.stream_bytes = 0
        self.stream_t0 = 0.0

    def load(self):
        if self.ready:
            return True
        import ctypes
        libpath = vosk_lib_path()
        model_dir = vosk_model_path()
        if not os.path.isfile(libpath):
            self.err = "libvosk.so missing"
            return False
        if not os.path.isdir(model_dir):
            self.err = "vosk model missing"
            return False
        env = os.environ
        extra = (
            os.path.dirname(libpath)
            + ":"
            + os.path.join(STT_ROOT, "lib")
            + ":/accounts/1000/shared/misc/berrycore/lib"
        )
        env["LD_LIBRARY_PATH"] = extra + ":" + env.get("LD_LIBRARY_PATH", "")
        try:
            lib = ctypes.CDLL(libpath)
            lib.vosk_set_log_level.argtypes = [ctypes.c_int]
            lib.vosk_model_new.argtypes = [ctypes.c_char_p]
            lib.vosk_model_new.restype = ctypes.c_void_p
            lib.vosk_model_free.argtypes = [ctypes.c_void_p]
            lib.vosk_recognizer_new.argtypes = [ctypes.c_void_p, ctypes.c_float]
            lib.vosk_recognizer_new.restype = ctypes.c_void_p
            lib.vosk_recognizer_accept_waveform.argtypes = [
                ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int
            ]
            lib.vosk_recognizer_accept_waveform.restype = ctypes.c_int
            lib.vosk_recognizer_result.argtypes = [ctypes.c_void_p]
            lib.vosk_recognizer_result.restype = ctypes.c_char_p
            lib.vosk_recognizer_partial_result.argtypes = [ctypes.c_void_p]
            lib.vosk_recognizer_partial_result.restype = ctypes.c_char_p
            lib.vosk_recognizer_final_result.argtypes = [ctypes.c_void_p]
            lib.vosk_recognizer_final_result.restype = ctypes.c_char_p
            lib.vosk_recognizer_reset.argtypes = [ctypes.c_void_p]
            lib.vosk_recognizer_free.argtypes = [ctypes.c_void_p]
            lib.vosk_set_log_level(-1)
            t0 = time.time()
            model = lib.vosk_model_new(model_dir.encode("utf-8"))
            if not model:
                self.err = "vosk_model_new failed"
                return False
            rec = lib.vosk_recognizer_new(model, float(self.rate))
            if not rec:
                lib.vosk_model_free(model)
                self.err = "vosk_recognizer_new failed"
                return False
            self.lib = lib
            self.model = model
            self.rec = rec
            self.ready = True
            sys.stderr.write("vosk model warm in %dms\n" % int((time.time() - t0) * 1000))
            return True
        except Exception as e:
            self.err = str(e)
            return False

    def decode_wav(self, wav16):
        t0 = time.time()
        if not self.load():
            return {"ok": False, "text": "", "err": self.err, "ms": 0, "rc": -1, "warm": False}
        pcm, rate = read_wav_pcm(wav16)
        if pcm is None:
            return {"ok": False, "text": "", "err": "bad wav", "ms": 0, "rc": -1, "warm": True}
        with self.lock:
            try:
                if rate and rate != self.rate:
                    # resample already done by ffmpeg to 16k; still accept header rate
                    pass
                self.lib.vosk_recognizer_reset(self.rec)
                self.lib.vosk_recognizer_accept_waveform(self.rec, pcm, len(pcm))
                raw = self.lib.vosk_recognizer_final_result(self.rec)
                text = parse_vosk_text(raw)
                return {
                    "ok": bool(text),
                    "text": text,
                    "err": "",
                    "ms": int((time.time() - t0) * 1000),
                    "rc": 0,
                    "warm": True,
                }
            except Exception as e:
                return {
                    "ok": False,
                    "text": "",
                    "err": str(e),
                    "ms": int((time.time() - t0) * 1000),
                    "rc": -1,
                    "warm": True,
                }

    def stream_state(self):
        with self.lock:
            live = self.committed
            if self.partial:
                live = (live + " " + self.partial).strip() if live else self.partial
            return {
                "listening": self.streaming,
                "partial": self.partial,
                "text": self.committed,
                "live": live,
                "bytes": self.stream_bytes,
                "ms": int((time.time() - self.stream_t0) * 1000) if self.stream_t0 else 0,
                "warm": self.ready,
                "err": self.err,
            }

    def stream_start(self):
        if not self.load():
            return False, self.err
        with self.lock:
            try:
                self.lib.vosk_recognizer_reset(self.rec)
            except Exception as e:
                return False, str(e)
            self.streaming = True
            self.partial = ""
            self.committed = ""
            self.stream_bytes = 0
            self.stream_t0 = time.time()
            self.err = ""
            return True, ""

    def stream_feed(self, pcm):
        if not pcm:
            return True, ""
        with self.lock:
            if not self.streaming or not self.rec:
                return False, "not streaming"
            try:
                self.stream_bytes += len(pcm)
                rc = self.lib.vosk_recognizer_accept_waveform(self.rec, pcm, len(pcm))
                if rc == 1:
                    text = parse_vosk_text(self.lib.vosk_recognizer_result(self.rec))
                    if text:
                        self.committed = (self.committed + " " + text).strip() if self.committed else text
                    self.partial = ""
                else:
                    self.partial = parse_vosk_partial(self.lib.vosk_recognizer_partial_result(self.rec))
                return True, ""
            except Exception as e:
                self.err = str(e)
                return False, str(e)

    def stream_stop(self):
        with self.lock:
            if not self.streaming:
                live = self.committed
                return {
                    "ok": bool(live),
                    "text": live,
                    "err": "not streaming",
                    "ms": int((time.time() - self.stream_t0) * 1000) if self.stream_t0 else 0,
                    "bytes": self.stream_bytes,
                }
            try:
                text = parse_vosk_text(self.lib.vosk_recognizer_final_result(self.rec))
                if text:
                    self.committed = (self.committed + " " + text).strip() if self.committed else text
            except Exception as e:
                self.err = str(e)
            self.partial = ""
            self.streaming = False
            return {
                "ok": True,
                "text": self.committed,
                "err": self.err,
                "ms": int((time.time() - self.stream_t0) * 1000) if self.stream_t0 else 0,
                "bytes": self.stream_bytes,
            }


VOSK = VoskEngine()


def read_wav_pcm(path):
    try:
        data = open(path, "rb").read()
    except IOError:
        return None, 0
    if len(data) < 44 or data[:4] != b"RIFF":
        return None, 0
    rate = data[24] | (data[25] << 8) | (data[26] << 16) | (data[27] << 24)
    return data[44:], rate


def parse_vosk_text(raw):
    if not raw:
        return ""
    if isinstance(raw, bytes):
        s = raw.decode("utf-8", "replace")
    else:
        s = str(raw)
    try:
        obj = json.loads(s)
        return (obj.get("text") or "").strip()
    except Exception:
        pass
    i = s.find('"text"')
    if i < 0:
        return s.strip()
    i = s.find('"', i + 6)
    if i < 0:
        return s.strip()
    j = s.find('"', i + 1)
    if j < 0:
        return s.strip()
    return s[i + 1:j]


def parse_vosk_partial(raw):
    if not raw:
        return ""
    if isinstance(raw, bytes):
        s = raw.decode("utf-8", "replace")
    else:
        s = str(raw)
    try:
        obj = json.loads(s)
        return (obj.get("partial") or "").strip()
    except Exception:
        pass
    i = s.find('"partial"')
    if i < 0:
        return ""
    i = s.find('"', i + 9)
    if i < 0:
        return ""
    j = s.find('"', i + 1)
    if j < 0:
        return ""
    return s[i + 1:j]


def decode_vosk(wav16):
    if VOSK.ready or os.path.isfile(os.path.join(STT_ROOT, "lib", "libvosk.so")):
        r = VOSK.decode_wav(wav16)
        if r.get("ok") or r.get("warm"):
            return r
    vosk = os.path.join(STT_ROOT, "bin", "vosk")
    if not os.path.isfile(vosk):
        return {"ok": False, "text": "", "err": VOSK.err or "vosk binary not on device yet", "ms": 0, "rc": -1}
    env = os.environ.copy()
    env["LD_LIBRARY_PATH"] = (
        os.path.join(STT_ROOT, "lib")
        + ":/accounts/1000/shared/misc/berrycore/lib:"
        + env.get("LD_LIBRARY_PATH", "")
    )
    return run_cmd([vosk, wav16], timeout=180, env=env)


def decode_both(wav8, wav16):
    box = {}

    def _s():
        box["sphinx"] = decode_sphinx(wav8) if wav8 else {
            "ok": False, "text": "", "err": "no 8k wav", "ms": 0
        }

    def _v():
        box["vosk"] = decode_vosk(wav16) if wav16 else {
            "ok": False, "text": "", "err": "no 16k wav", "ms": 0
        }

    t1 = threading.Thread(target=_s)
    t2 = threading.Thread(target=_v)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    return box.get("sphinx"), box.get("vosk")


JOBS = {}
JOB_LOCK = threading.Lock()
_JOB_N = [0]


def _job_id():
    _JOB_N[0] += 1
    return "j%d" % _JOB_N[0]


def _job_set(jid, engine, value):
    with JOB_LOCK:
        job = JOBS.get(jid)
        if job is not None:
            job[engine] = value


def start_job(src, engines="both", work=None, own_work=False):
    """Convert + decode in the background. Each engine is published as it finishes."""
    jid = _job_id()
    skipped = {"ok": False, "text": "", "err": "skipped", "ms": 0}
    with JOB_LOCK:
        JOBS[jid] = {"sphinx": None, "vosk": None, "t0": time.time()}

    def run():
        try:
            want_s = engines in ("both", "sphinx")
            want_v = engines in ("both", "vosk")
            if work is None:
                base = os.path.join(STT_ROOT, "tmp")
                try:
                    os.makedirs(base, exist_ok=True)
                    w = tempfile.mkdtemp(prefix="sttlab-", dir=base)
                    own = True
                except Exception:
                    w = tempfile.mkdtemp(prefix="sttlab-")
                    own = True
            else:
                w = work
                own = own_work
            wav8, wav16, r8, r16 = to_wavs(src, w, want_8=want_s, want_16=want_v)
            threads = []
            if want_v:
                def _v():
                    if wav16:
                        _job_set(jid, "vosk", decode_vosk(wav16))
                    else:
                        _job_set(jid, "vosk", {
                            "ok": False, "text": "",
                            "err": "ffmpeg 16k failed: " + r16.get("err", ""), "ms": 0,
                        })
                t = threading.Thread(target=_v)
                threads.append(t)
                t.start()
            else:
                _job_set(jid, "vosk", skipped)
            if want_s:
                def _s():
                    if wav8:
                        _job_set(jid, "sphinx", decode_sphinx(wav8))
                    else:
                        _job_set(jid, "sphinx", {
                            "ok": False, "text": "",
                            "err": "ffmpeg 8k failed: " + r8.get("err", ""), "ms": 0,
                        })
                t = threading.Thread(target=_s)
                threads.append(t)
                t.start()
            else:
                _job_set(jid, "sphinx", skipped)
            for t in threads:
                t.join()
            if own:
                shutil.rmtree(w, ignore_errors=True)
        except Exception as e:
            err = {"ok": False, "text": "", "err": str(e), "ms": 0}
            _job_set(jid, "vosk", err)
            _job_set(jid, "sphinx", err)

    threading.Thread(target=run, daemon=True).start()
    return jid


def wait_job(jid, engine, timeout=180):
    t0 = time.time()
    while time.time() - t0 < timeout:
        with JOB_LOCK:
            job = JOBS.get(jid)
            val = job.get(engine) if job else "missing"
        if val == "missing":
            return None, "unknown job"
        if val is not None:
            return val, ""
        time.sleep(0.05)
    return None, "timeout"


def prune_jobs():
    now = time.time()
    with JOB_LOCK:
        dead = [k for k, j in JOBS.items() if now - j.get("t0", now) > 300]
        for k in dead:
            JOBS.pop(k, None)


def write_wav16(path, pcm, rate=16000):
    data_size = len(pcm)
    with open(path, "wb") as f:
        f.write(b"RIFF")
        f.write(struct.pack("<I", 36 + data_size))
        f.write(b"WAVE")
        f.write(b"fmt ")
        f.write(struct.pack("<I", 16))
        f.write(struct.pack("<H", 1))
        f.write(struct.pack("<H", 1))
        f.write(struct.pack("<I", rate))
        f.write(struct.pack("<I", rate * 2))
        f.write(struct.pack("<H", 2))
        f.write(struct.pack("<H", 16))
        f.write(b"data")
        f.write(struct.pack("<I", data_size))
        f.write(pcm)


def start_record():
    if RECORD["proc"] is not None:
        return False, "already recording"
    method, dev = detect_record()
    if method != "pcm" or not dev:
        return False, "no device mic — use the BB10 voice recorder"
    tmp = os.path.join(STT_ROOT, "tmp")
    os.makedirs(tmp, exist_ok=True)
    out = os.path.join(tmp, "live.wav")
    stop = {"on": True}

    def _run():
        raw = bytearray()
        fd = None
        try:
            fd = os.open(dev, os.O_RDONLY)
            t0 = time.time()
            while stop["on"] and (time.time() - t0) < 30:
                try:
                    chunk = os.read(fd, 4096)
                    if chunk:
                        raw.extend(chunk)
                    else:
                        time.sleep(0.01)
                except Exception:
                    time.sleep(0.01)
        finally:
            if fd is not None:
                try:
                    os.close(fd)
                except Exception:
                    pass
        write_wav16(out, bytes(raw), 16000)

    th = threading.Thread(target=_run)
    th.daemon = True
    RECORD["proc"] = (th, stop)
    RECORD["path"] = out
    th.start()
    return True, "recording"


def stop_record():
    proc = RECORD.get("proc")
    path = RECORD.get("path")
    RECORD["proc"] = None
    RECORD["path"] = None
    if not proc:
        return None, "not recording"
    th, stop = proc
    stop["on"] = False
    th.join(timeout=8)
    if not path or not os.path.isfile(path) or os.path.getsize(path) < 80:
        return None, "no audio captured"
    return path, ""


class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    daemon_threads = True
    allow_reuse_address = True


class Handler(BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        sys.stderr.write("%s - %s\n" % (self.address_string(), fmt % args))

    def _json(self, code, obj):
        body = json.dumps(obj).encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def _file(self, path, ctype):
        try:
            data = open(path, "rb").read()
        except IOError:
            self.send_error(404)
            return
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def do_GET(self):
        path = self.path.split("?", 1)[0]
        if path == "/" or path == "/index.html":
            self._file(os.path.join(ROOT, "index.html"), "text/html; charset=utf-8")
        elif path == "/api/status":
            self._json(200, which_engines())
        elif path == "/api/demo":
            demo = os.path.join(STT_ROOT, "share", "goforward.raw")
            if not os.path.isfile(demo):
                self._json(404, {"error": "goforward.raw missing"})
                return
            prune_jobs()
            jid = start_job(demo, engines=self._engines_q())
            self._json(200, {"job": jid})
        elif path == "/api/job":
            q = self.path.split("?", 1)[1] if "?" in self.path else ""
            jid = ""
            engine = "vosk"
            for part in q.split("&"):
                if part.startswith("id="):
                    jid = part[3:]
                elif part.startswith("engine="):
                    engine = part[7:]
            if engine not in ("vosk", "sphinx"):
                self._json(400, {"error": "engine must be vosk or sphinx"})
                return
            val, err = wait_job(jid, engine)
            if err:
                self._json(404, {"error": err})
                return
            self._json(200, {engine: val})
        elif path == "/api/partial":
            self._json(200, VOSK.stream_state())
        elif path == "/api/stream/start":
            self._stream_start()
        elif path == "/api/stream/stop":
            self._stream_stop()
        else:
            self.send_error(404)

    def _stream_start(self):
        ok, err = VOSK.stream_start()
        st = VOSK.stream_state()
        st["ok"] = ok
        if err:
            st["error"] = err
        self._json(200 if ok else 503, st)

    def _stream_stop(self):
        self._json(200, VOSK.stream_stop())

    def do_POST(self):
        path = self.path.split("?", 1)[0]
        if path == "/api/stream/start":
            n = int(self.headers.get("Content-Length", "0") or 0)
            if n:
                self.rfile.read(n)
            self._stream_start()
            return
        if path == "/api/stream/chunk":
            n = int(self.headers.get("Content-Length", "0") or 0)
            if n <= 0 or n > 512 * 1024:
                self._json(400, {"ok": False, "error": "empty or huge chunk"})
                return
            pcm = self.rfile.read(n)
            ok, err = VOSK.stream_feed(pcm)
            st = VOSK.stream_state()
            st["ok"] = ok or err == "not streaming"
            if err and err != "not streaming":
                st["error"] = err
            elif err == "not streaming":
                st["ignored"] = True
            self._json(200, st)
            return
        if path == "/api/stream/stop":
            n = int(self.headers.get("Content-Length", "0") or 0)
            if n:
                self.rfile.read(n)
            self._stream_stop()
            return
        if path == "/api/record/start":
            n = int(self.headers.get("Content-Length", "0") or 0)
            if n:
                self.rfile.read(n)
            ok, msg = start_record()
            self._json(200 if ok else 400, {"ok": ok, "error": "" if ok else msg})
            return
        if path == "/api/record/stop":
            n = int(self.headers.get("Content-Length", "0") or 0)
            if n:
                self.rfile.read(n)
            src, err = stop_record()
            if not src:
                self._json(400, {"error": err or "record stop failed"})
                return
            prune_jobs()
            jid = start_job(src, engines=self._engines_q())
            self._json(200, {"job": jid})
            return
        if path != "/api/decode":
            self.send_error(404)
            return
        n = int(self.headers.get("Content-Length", "0") or 0)
        if n <= 0 or n > 12 * 1024 * 1024:
            self._json(400, {"error": "audio too large or empty"})
            return
        data = self.rfile.read(n)
        base = os.path.join(STT_ROOT, "tmp")
        try:
            os.makedirs(base, exist_ok=True)
            work = tempfile.mkdtemp(prefix="sttlab-", dir=base)
        except Exception:
            work = tempfile.mkdtemp(prefix="sttlab-")
        src = os.path.join(work, upload_name(self.headers.get("Content-Type", "")))
        open(src, "wb").write(data)
        prune_jobs()
        jid = start_job(src, engines=self._engines_q(), work=work, own_work=True)
        self._json(200, {"job": jid})

    def _engines_q(self):
        q = ""
        if "?" in self.path:
            q = self.path.split("?", 1)[1]
        if "engine=vosk" in q:
            return "vosk"
        if "engine=sphinx" in q:
            return "sphinx"
        return "both"

    def _decode_path(self, src, work=None, engines="both"):
        own = work is None
        if work is None:
            base = os.path.join(STT_ROOT, "tmp")
            try:
                os.makedirs(base, exist_ok=True)
                work = tempfile.mkdtemp(prefix="sttlab-", dir=base)
            except Exception:
                work = tempfile.mkdtemp(prefix="sttlab-")
        try:
            want_s = engines in ("both", "sphinx")
            want_v = engines in ("both", "vosk")
            wav8, wav16, r8, r16 = to_wavs(src, work, want_8=want_s, want_16=want_v)
            sphinx = {"ok": False, "text": "", "err": "", "ms": 0}
            vosk = {"ok": False, "text": "", "err": "", "ms": 0}
            if want_s and not wav8:
                sphinx = {"ok": False, "text": "", "err": "ffmpeg 8k failed: " + r8.get("err", ""), "ms": 0}
            if want_v and not wav16:
                vosk = {"ok": False, "text": "", "err": "ffmpeg 16k failed: " + r16.get("err", ""), "ms": 0}
            if want_s and want_v and (wav8 or wav16):
                sphinx, vosk = decode_both(wav8, wav16)
            elif want_s and wav8:
                sphinx = decode_sphinx(wav8)
            elif want_v and wav16:
                vosk = decode_vosk(wav16)
            self._json(200, {"sphinx": sphinx, "vosk": vosk, "engines": which_engines()})
        finally:
            if own:
                shutil.rmtree(work, ignore_errors=True)


if __name__ == "__main__":
    os.makedirs(os.path.join(STT_ROOT, "tmp"), exist_ok=True)

    def _warm():
        VOSK.load()

    threading.Thread(target=_warm, daemon=True).start()
    httpd = ThreadedHTTPServer(("0.0.0.0", PORT), Handler)
    sys.stderr.write("STT lab http://0.0.0.0:%d/  root=%s\n" % (PORT, STT_ROOT))
    httpd.serve_forever()
