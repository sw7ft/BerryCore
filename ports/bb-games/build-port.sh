#!/bin/sh
# Build games-bb-games-1.0.zip for qpkg install bb-games
# Canonical files live in berrycore/bin/games + berrycore/share/games/
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC="$REPO_ROOT/berrycore"
PORT_ZIP="$REPO_ROOT/ports/games-bb-games-1.0.zip"
BUNDLED="$SRC/packages/games-bb-games-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building bb-games 1.0..."
if [ ! -f "$SRC/bin/games" ] || [ ! -f "$SRC/share/games/index.html" ]; then
    echo "Error: berrycore/bin/games or share/games/index.html missing"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/games"
cp "$SRC/bin/games" "$PKG_ROOT/bin/"
cp "$SRC/share/games/"* "$PKG_ROOT/share/games/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/games/README-port.md" 2>/dev/null || true
chmod +x "$PKG_ROOT/bin/games" "$PKG_ROOT/share/games/serve.py"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$SRC/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
echo "qpkg install bb-games  →  ports/games-bb-games-1.0.zip"
