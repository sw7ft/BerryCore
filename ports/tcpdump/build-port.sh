#!/bin/sh
# Build util-tcpdump-4.99.5.zip for qpkg install tcpdump
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/util-tcpdump-4.99.5.zip"
PKG_ROOT="$SCRIPT_DIR/.build/pkg"
rm -rf "$SCRIPT_DIR/.build"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/tcpdump"

if [ -f "$REPO_ROOT/util-tcpdump-4.99.5.zip" ]; then
    unzip -p "$REPO_ROOT/util-tcpdump-4.99.5.zip" bin/tcpdump > "$PKG_ROOT/bin/tcpdump"
elif [ -f "$PORT_ZIP" ]; then
    unzip -p "$PORT_ZIP" bin/tcpdump > "$PKG_ROOT/bin/tcpdump"
else
    echo "Error: need bin/tcpdump source"; exit 1
fi

cat > "$PKG_ROOT/share/doc/tcpdump/HELP.txt" << 'EOF'
tcpdump — network packet capture (v4.99.5)

Install:  qpkg install tcpdump
Note:      may require root on BB10

Usage:
  tcpdump -i bptp0 -c 20
  tcpdump -n port 443
EOF

chmod +x "$PKG_ROOT/bin/tcpdump"
cd "$PKG_ROOT" && zip -r -q "$PORT_ZIP" bin share
echo "Done: $PORT_ZIP"
