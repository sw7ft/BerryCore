#!/bin/sh
# Stop Berry Remote. Never `slay -f node` — that kills PM2 and any other node.
DIR="$(cd "$(dirname "$0")" && pwd)"

rm -f "$DIR/.remote-run"

kill_pidfile() {
    f="$1"
    if [ -f "$f" ]; then
        p=$(cat "$f" 2>/dev/null)
        if [ -n "$p" ]; then
            kill "$p" 2>/dev/null
            sleep 0
            kill -9 "$p" 2>/dev/null
        fi
        rm -f "$f"
    fi
}

kill_pidfile "$DIR/.supervisor.pid"
kill_pidfile "$DIR/.service.pid"
kill_pidfile "$DIR/.engine.pid"
# Engine binary name is ours; safe. Do not slay node.
slay -f content_shell 2>/dev/null
echo "berry-remote stopped"
