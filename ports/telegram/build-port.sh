#!/bin/sh
# Build web-telegram-1.0.zip for qpkg install telegram
# Usage: ./build-port.sh

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/web-telegram-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"
SRC="$SCRIPT_DIR/share/telegram"

echo "Building telegram 1.0 port..."
echo "  Output: $PORT_ZIP"

if [ ! -f "$SRC/app.py" ] || [ ! -f "$SRC/index.html" ]; then
    echo "Error: share/telegram/ app bundle incomplete (need app.py, index.html)"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/telegram"

cp "$SCRIPT_DIR/bin/telegram" "$PKG_ROOT/bin/"
cp -R "$SRC/"* "$PKG_ROOT/share/telegram/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/telegram/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/telegram"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
