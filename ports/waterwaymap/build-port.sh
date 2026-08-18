#!/bin/sh
# Build web-waterwaymap-1.0.zip for qpkg install waterwaymap / waterway
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC="$REPO_ROOT/berrycore"
PORT_ZIP="$REPO_ROOT/ports/web-waterwaymap-1.0.zip"
BUNDLED="$SRC/packages/web-waterwaymap-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building waterwaymap 1.0..."
for f in "$SRC/bin/waterwaymap" "$SRC/bin/waterway" \
         "$SRC/share/waterwaymap/serve.py" "$SRC/share/waterwaymap/index.html"; do
    if [ ! -f "$f" ]; then
        echo "Error: missing $f"
        exit 1
    fi
done

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/waterwaymap/static"
cp "$SRC/bin/waterwaymap" "$SRC/bin/waterway" "$PKG_ROOT/bin/"
cp "$SRC/share/waterwaymap/serve.py" "$SRC/share/waterwaymap/index.html" "$PKG_ROOT/share/waterwaymap/"
if [ -f "$SRC/share/waterwaymap/README.md" ]; then
    cp "$SRC/share/waterwaymap/README.md" "$PKG_ROOT/share/waterwaymap/"
fi
cp "$SRC/share/waterwaymap/static/"* "$PKG_ROOT/share/waterwaymap/static/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/waterwaymap/README-port.md"
chmod +x "$PKG_ROOT/bin/waterwaymap" "$PKG_ROOT/bin/waterway" \
    "$PKG_ROOT/share/waterwaymap/serve.py"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$SRC/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
echo "qpkg install waterwaymap  →  ports/web-waterwaymap-1.0.zip"
