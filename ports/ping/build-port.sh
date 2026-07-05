#!/bin/sh
# Build util-ping-1.0.0.zip for qpkg install ping
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/util-ping-1.0.0.zip"
PKG_ROOT="$SCRIPT_DIR/.build/pkg"
rm -rf "$SCRIPT_DIR/.build"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/ping"

# Binary from existing port zip or repo-root copy
if [ -f "$REPO_ROOT/util-ping-1.0.0.zip" ]; then
    unzip -p "$REPO_ROOT/util-ping-1.0.0.zip" bin/ping > "$PKG_ROOT/bin/ping"
elif [ -f "$PORT_ZIP" ]; then
    unzip -p "$PORT_ZIP" bin/ping > "$PKG_ROOT/bin/ping"
else
    echo "Error: need bin/ping source"; exit 1
fi

cat > "$PKG_ROOT/share/doc/ping/HELP.txt" << 'EOF'
ping — ICMP echo (BerryCore / QNX)

Install:  qpkg install ping
Note:      may require root / privileged user on BB10

Usage:
  ping -c 4 192.168.1.1
  ping berrycore.sw7ft.com
EOF

chmod +x "$PKG_ROOT/bin/ping"
cd "$PKG_ROOT" && zip -r -q "$PORT_ZIP" bin share
echo "Done: $PORT_ZIP"
