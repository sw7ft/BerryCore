#!/bin/sh
# Start Berry Remote on BB10/QNX.
# Persists after SSH close via ignored SIGHUP (no nohup/setsid on this busybox).
# Does NOT slay every `node` on the device (PM2 / other node must survive).
#
#   PORT=8080 URL=https://html.duckduckgo.com/html/ sh remote-start.sh
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR" || exit 1

PORT="${PORT:-8080}"
URL="${URL:-https://html.duckduckgo.com/html/}"
RENDER="${RENDER:-360}"
LOG="$DIR/berry-remote.log"

find_node() {
    if [ -n "$NODE" ] && [ -x "$NODE" ]; then
        echo "$NODE"
        return 0
    fi
    for c in \
        "$DIR/../node/node" \
        "$DIR/node/node.bin" \
        "$DIR/node/node" \
        "/accounts/devuser/berry-deploy/node/node"
    do
        if [ -x "$c" ]; then
            echo "$c"
            return 0
        fi
    done
    return 1
}

NODE="$(find_node)" || {
    echo "berry-remote: node not found (expected ../node/node)"
    exit 1
}

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

# Drop the run marker first so a previous supervisor exits instead of respawning.
rm -f "$DIR/.remote-run"
kill_pidfile "$DIR/.supervisor.pid"
kill_pidfile "$DIR/.service.pid"
kill_pidfile "$DIR/.engine.pid"
# Leftover engine from a crash (name is unique enough; do not slay node).
slay -f content_shell 2>/dev/null
sleep 1
: > "$LOG"

LAN_IP=""
if [ -x /sbin/ifconfig ] || command -v ifconfig >/dev/null 2>&1; then
    LAN_IP=$(ifconfig bcm0 2>/dev/null | awk '/inet /{print $2; exit}')
fi
[ -z "$LAN_IP" ] && LAN_IP="<device-ip>"

trap '' HUP
# --jitless is REQUIRED: QNX ARM32 node JIT SIGBUS once anything tiers up.
NODE_DIR="$(dirname "$NODE")"
# QNX date has no +%s — do not use it for the nonce.
NONCE="$$.$PORT.$RENDER"
echo "$NONCE" > "$DIR/.remote-run"
(
  while [ "$(cat "$DIR/.remote-run" 2>/dev/null)" = "$NONCE" ]; do
    PORT="$PORT" URL="$URL" RENDER="$RENDER" \
      LD_LIBRARY_PATH="$NODE_DIR:$DIR:$LD_LIBRARY_PATH" \
      "$NODE" --jitless "$DIR/berry-remote.js" >> "$LOG" 2>&1
    echo "[supervisor] service exited rc=$? — respawning in 8s" >> "$LOG"
    sleep 8
  done
  echo "[supervisor] run marker removed, stopping" >> "$LOG"
) < /dev/null > /dev/null 2>&1 &
echo $! > "$DIR/.supervisor.pid"

echo "berry-remote started port=$PORT url=$URL render=$RENDER"
echo "node: $NODE"
echo "log: $LOG"
echo "open: http://$LAN_IP:$PORT"
echo "hop:  ssh -L $PORT:127.0.0.1:$PORT passport   then http://localhost:$PORT"
echo "stop: berryremote stop"
