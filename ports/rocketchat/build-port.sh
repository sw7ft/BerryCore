#!/bin/sh
# Build web-rocketchat-3.0.zip for qpkg install rocketchat
# Usage: ./build-port.sh

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/web-rocketchat-3.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"
SRC="$SCRIPT_DIR/share/rocketchat"

echo "Building rocketchat 3.0 port..."
echo "  Output: $PORT_ZIP"

if [ ! -f "$SRC/app.py" ] || [ ! -f "$SRC/index.html" ]; then
    echo "Error: share/rocketchat/ app bundle incomplete"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/rocketchat"

cp "$SCRIPT_DIR/bin/rocketchat" "$PKG_ROOT/bin/"
cp -R "$SRC/"* "$PKG_ROOT/share/rocketchat/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/rocketchat/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/rocketchat"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
