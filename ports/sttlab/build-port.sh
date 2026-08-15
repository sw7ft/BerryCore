#!/bin/sh
# Build web-sttlab-1.0.zip for qpkg install sttlab
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC="$REPO_ROOT/berrycore"
PORT_ZIP="$REPO_ROOT/ports/web-sttlab-1.0.zip"
BUNDLED="$SRC/packages/web-sttlab-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building sttlab 1.0..."
if [ ! -f "$SRC/bin/sttlab" ] || [ ! -f "$SRC/share/sttlab/index.html" ]; then
    echo "Error: berrycore/bin/sttlab or share/sttlab missing"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/sttlab"
cp "$SRC/bin/sttlab" "$PKG_ROOT/bin/"
cp "$SRC/share/sttlab/index.html" "$SRC/share/sttlab/serve.py" "$PKG_ROOT/share/sttlab/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/sttlab/README-port.md"
chmod +x "$PKG_ROOT/bin/sttlab" "$PKG_ROOT/share/sttlab/serve.py"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$SRC/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
echo "qpkg install sttlab  →  ports/web-sttlab-1.0.zip"
