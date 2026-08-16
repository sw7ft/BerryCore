#!/usr/bin/env python3
"""STT lab text UI for Term49 — no browser, no JS.

Talks to the local lab on :8093 (start it with `sttlab` first).
Usage:  sttlabs            interactive menu
        sttlabs demo       official goforward clip (both engines)
        sttlabs vosk       goforward, Vosk only
        sttlabs rec [SEC]  device mic, default 3 seconds
        sttlabs file PATH  decode a wav/raw/m4a
"""
from __future__ import print_function

import json
import os
import sys
import time
import urllib.error
import urllib.request

PORT = int(os.environ.get("BERRYCORE_STTLAB_PORT", "8093"))
BASE = os.environ.get("STTLAB_URL", "http://127.0.0.1:%d" % PORT)

RST = "\033[0m"
DIM = "\033[38;5;60m"
PNK = "\033[1;38;5;213m"
CYN = "\033[1;38;5;51m"
ORG = "\033[1;38;5;215m"
WHT = "\033[1;38;5;231m"
MUT = "\033[38;5;146m"
OK = "\033[1;38;5;84m"
ERR = "\033[1;38;5;209m"


def get(path, timeout=180):
    url = BASE + path
    req = urllib.request.Request(url)
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            return r.getcode(), json.loads(r.read().decode("utf-8", "replace"))
    except urllib.error.HTTPError as e:
        body = e.read().decode("utf-8", "replace")
        try:
            return e.code, json.loads(body)
        except Exception:
            return e.code, {"error": body or str(e)}
    except Exception as e:
        return 0, {"error": str(e)}


def post(path, data=b"{}", timeout=180, ctype="application/json"):
    url = BASE + path
    req = urllib.request.Request(url, data=data, method="POST")
    req.add_header("Content-Type", ctype)
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            return r.getcode(), json.loads(r.read().decode("utf-8", "replace"))
    except urllib.error.HTTPError as e:
        body = e.read().decode("utf-8", "replace")
        try:
            return e.code, json.loads(body)
        except Exception:
            return e.code, {"error": body or str(e)}
    except Exception as e:
        return 0, {"error": str(e)}


def wait_engine(jid, engine):
    st, obj = get("/api/job?id=%s&engine=%s" % (jid, engine), timeout=180)
    if st != 200:
        return {"ok": False, "text": "", "err": (obj or {}).get("error") or "job failed", "ms": 0}
    return (obj or {}).get(engine) or obj or {"ok": False, "text": "", "err": "empty", "ms": 0}


def show_one(name, r):
    r = r or {}
    text = r.get("text") or ""
    err = r.get("err") or r.get("error") or ""
    ms = r.get("ms")
    if r.get("ok") and text:
        print("  %s%-12s%s  %s%s%s" % (CYN, name, RST, WHT, text, RST))
        if ms is not None:
            print("  %s%12s  %s ms%s" % (DIM, "", ms, RST))
    else:
        print("  %s%-12s%s  %s%s%s" % (ORG, name, RST, ERR, text or err or "no text", RST))
        if ms is not None:
            print("  %s%12s  %s ms%s" % (DIM, "", ms, RST))


def run_job(path):
    print("%sdecoding…%s" % (MUT, RST))
    st, obj = get(path, timeout=30)
    if st != 200 or not obj or not obj.get("job"):
        print("%sfailed:%s %s" % (ERR, RST, (obj or {}).get("error") or ("HTTP %s" % st)))
        return 1
    jid = obj["job"]
    vosk = wait_engine(jid, "vosk")
    show_one("vosk", vosk)
    sphinx = wait_engine(jid, "sphinx")
    show_one("sphinx", sphinx)
    return 0


def cmd_status():
    st, obj = get("/api/status", timeout=8)
    if st != 200:
        print("%slab not reachable%s  %s" % (ERR, RST, (obj or {}).get("error") or "start with: sttlab"))
        print("  %s%s%s" % (DIM, BASE, RST))
        return 1
    def flag(ok):
        return ("%sready%s" % (OK, RST)) if ok else ("%smissing%s" % (ERR, RST))
    print("%sSTT LAB%s  %sTerm49 test%s  %s%s%s" % (PNK, RST, WHT, RST, DIM, BASE, RST))
    print("  sphinx %s  vosk %s%s  mic %s" % (
        flag(obj.get("sphinx")),
        flag(obj.get("vosk")),
        (" %swarm%s" % (OK, RST)) if obj.get("vosk_warm") else "",
        (obj.get("record_method") or "none") if obj.get("record") else "none",
    ))
    return 0


def cmd_demo(engine="both"):
    q = "?engine=vosk" if engine == "vosk" else ""
    return run_job("/api/demo" + q)


def cmd_rec(sec=3):
    try:
        sec = max(1, min(int(sec), 20))
    except Exception:
        sec = 3
    print("%srecording %ds — speak now%s" % (ORG, sec, RST))
    st, obj = post("/api/record/start", timeout=8)
    if st != 200 or not (obj or {}).get("ok"):
        print("%smic failed:%s %s" % (ERR, RST, (obj or {}).get("error") or ("HTTP %s" % st)))
        return 1
    time.sleep(sec)
    print("%sstopping…%s" % (MUT, RST))
    st, obj = post("/api/record/stop", timeout=30)
    if st != 200 or not obj or not obj.get("job"):
        print("%sstop failed:%s %s" % (ERR, RST, (obj or {}).get("error") or ("HTTP %s" % st)))
        return 1
    jid = obj["job"]
    vosk = wait_engine(jid, "vosk")
    show_one("vosk", vosk)
    sphinx = wait_engine(jid, "sphinx")
    show_one("sphinx", sphinx)
    return 0


def cmd_file(path):
    if not path or not os.path.isfile(path):
        print("%sfile not found:%s %s" % (ERR, RST, path or "(none)"))
        return 1
    data = open(path, "rb").read()
    print("%suploading %s (%d bytes)%s" % (MUT, path, len(data), RST))
    low = path.lower()
    ctype = "application/octet-stream"
    if low.endswith(".wav"):
        ctype = "audio/wav"
    elif low.endswith(".m4a"):
        ctype = "audio/mp4"
    elif low.endswith(".raw") or low.endswith(".pcm"):
        ctype = "application/octet-stream"
    st, obj = post("/api/decode", data=data, ctype=ctype, timeout=30)
    if st != 200 or not obj or not obj.get("job"):
        print("%sdecode failed:%s %s" % (ERR, RST, (obj or {}).get("error") or ("HTTP %s" % st)))
        return 1
    jid = obj["job"]
    vosk = wait_engine(jid, "vosk")
    show_one("vosk", vosk)
    sphinx = wait_engine(jid, "sphinx")
    show_one("sphinx", sphinx)
    return 0


def menu():
    if cmd_status() != 0:
        return 1
    print()
    print("  %s1%s  demo     official goforward clip" % (PNK, RST))
    print("  %s2%s  vosk     goforward, Vosk only" % (PNK, RST))
    print("  %s3%s  rec      device mic 3 seconds" % (PNK, RST))
    print("  %s4%s  rec 6    device mic 6 seconds" % (PNK, RST))
    print("  %sq%s  quit     lab stays running" % (PNK, RST))
    print()
    while True:
        try:
            line = input("%s>%s " % (PNK, RST))
        except (EOFError, KeyboardInterrupt):
            print()
            return 0
        line = (line or "").strip()
        if not line:
            continue
        if line in ("q", "quit", "exit"):
            return 0
        if line in ("1", "demo"):
            cmd_demo("both")
        elif line in ("2", "vosk"):
            cmd_demo("vosk")
        elif line in ("3", "rec"):
            cmd_rec(3)
        elif line in ("4", "rec6"):
            cmd_rec(6)
        elif line.startswith("rec "):
            cmd_rec(line.split()[1])
        elif line.startswith("file "):
            cmd_file(line.split(" ", 1)[1].strip())
        elif line in ("s", "status"):
            cmd_status()
        else:
            print("%s1 demo  2 vosk  3 rec  4 rec6  q quit%s" % (DIM, RST))
        print()


def main(argv):
    args = list(argv[1:])
    if not args or args[0] in ("term", "menu", "tui"):
        return menu()
    cmd = args[0]
    if cmd in ("demo", "goforward"):
        return cmd_demo("both")
    if cmd in ("vosk", "voskonly"):
        return cmd_demo("vosk")
    if cmd in ("rec", "record"):
        return cmd_rec(args[1] if len(args) > 1 else 3)
    if cmd in ("file", "decode"):
        return cmd_file(args[1] if len(args) > 1 else "")
    if cmd in ("status", "-s"):
        return cmd_status()
    if cmd in ("-h", "--help", "help"):
        print(__doc__)
        return 0
    print("Usage: sttlabs [demo|vosk|rec [SEC]|file PATH|status]")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv) or 0)
