#!/bin/sh
# Build web-maps-1.0.zip for qpkg install maps
# Usage: ./build-port.sh

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/web-maps-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building maps 1.0 port..."
echo "  Output: $PORT_ZIP"

if [ ! -f "$SCRIPT_DIR/share/maps/app.py" ]; then
    echo "Error: share/maps/app.py not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/maps"

cp "$SCRIPT_DIR/bin/maps" "$PKG_ROOT/bin/"
cp "$SCRIPT_DIR/share/maps/app.py" "$PKG_ROOT/share/maps/"
cp "$SCRIPT_DIR/share/maps/HELP.txt" "$PKG_ROOT/share/maps/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/maps/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/maps"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
