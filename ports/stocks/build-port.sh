#!/bin/sh
# Build web-stocks-1.0.zip for qpkg install stocks / ticker
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC="$REPO_ROOT/berrycore"
PORT_ZIP="$REPO_ROOT/ports/web-stocks-1.0.zip"
BUNDLED="$SRC/packages/web-stocks-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building stocks 1.0..."
for f in "$SRC/bin/stocks" "$SRC/bin/ticker" \
         "$SRC/share/stocks/serve.py" "$SRC/share/stocks/index.html"; do
    if [ ! -f "$f" ]; then
        echo "Error: missing $f"
        exit 1
    fi
done

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/stocks/static"
cp "$SRC/bin/stocks" "$SRC/bin/ticker" "$PKG_ROOT/bin/"
cp "$SRC/share/stocks/serve.py" "$SRC/share/stocks/index.html" "$PKG_ROOT/share/stocks/"
if [ -f "$SRC/share/stocks/README.md" ]; then
    cp "$SRC/share/stocks/README.md" "$PKG_ROOT/share/stocks/"
fi
cp "$SRC/share/stocks/static/"* "$PKG_ROOT/share/stocks/static/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/stocks/README-port.md"
chmod +x "$PKG_ROOT/bin/stocks" "$PKG_ROOT/bin/ticker" "$PKG_ROOT/share/stocks/serve.py"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$SRC/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
echo "qpkg install stocks  →  ports/web-stocks-1.0.zip"
