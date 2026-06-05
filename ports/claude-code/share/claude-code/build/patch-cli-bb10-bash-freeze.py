#!/usr/bin/env python3
"""
Patch Claude Code cli.js on BB10 / QNX so the Bash tool does not hang.

Upstream assumes Linux/macOS PTY + optional bubblewrap + a login-shell snapshot.
On QNX (process.platform === "qnx") several of those steps can block forever while
Read/Write keep working.

This script is idempotent: safe to run after every cli.js upgrade.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path


def default_cli_path() -> str:
    return str(Path(__file__).resolve().parent.parent / "package" / "cli.js")


def main() -> int:
    path = sys.argv[1] if len(sys.argv) > 1 else default_cli_path()
    with open(path, "rb") as f:
        data = f.read()

    orig = data
    changes: list[str] = []

    # 1) Skip login-shell snapshot before Bash (variable + d$K name minify differently per build).
    snap_re = re.compile(
        rb"[A-Za-z$_][A-Za-z$_0-9]*\?\.skipSnapshot\?Promise\.resolve\(void 0\):d[A-Za-z$_][A-Za-z$_0-9]*\(q\)"
    )
    m = snap_re.search(data)
    if m:
        data = data[: m.start()] + b"Promise.resolve(void 0)" + data[m.end() :]
        changes.append("bash-snapshot-skip")
    elif b"Promise.resolve(void 0).catch" in data and snap_re.pattern not in data:
        # Heuristic: already patched older way
        changes.append("bash-snapshot-skip(already)")

    # 2) Do not spawn bash detached (can confuse QNX session / waitpid handling with stdio pipes).
    det_old = b'type:"bash",shellPath:q,detached:!0'
    det_new = b'type:"bash",shellPath:q,detached:!1'
    if det_old in data:
        data = data.replace(det_old, det_new, 1)
        changes.append("bash-detached-off")

    # 3) Never enter Linux/macOS sandbox wrapper for bash (bwrap / seatbelt not available on qnx).
    wrap_old = rb"if(A){D=await W7.wrapWithSandbox(D,v,void 0,K);"
    wrap_new = rb"if(0&&A){D=await W7.wrapWithSandbox(D,v,void 0,K);"
    if wrap_old in data:
        n = data.count(wrap_old)
        data = data.replace(wrap_old, wrap_new)
        changes.append(f"sandbox-wrap-neutralize({n}x)")

    if data == orig:
        print("patch-bb10-bash-freeze: no changes applied (patterns missing or already patched).", file=sys.stderr)
        print("  If Bash still hangs, re-copy a fresh cli.js from the .tgz and run this again.", file=sys.stderr)
        return 1

    with open(path, "wb") as f:
        f.write(data)

    print("patched:", path)
    for c in changes:
        print(" -", c)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
