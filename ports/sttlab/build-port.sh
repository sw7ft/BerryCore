#!/bin/sh
# Build web-sttlab-1.1.zip for qpkg install sttlab / sttlabs
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC="$REPO_ROOT/berrycore"
PORT_ZIP="$REPO_ROOT/ports/web-sttlab-1.1.zip"
BUNDLED="$SRC/packages/web-sttlab-1.1.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building sttlab 1.1..."
for f in "$SRC/bin/sttlab" "$SRC/bin/sttlabs" \
         "$SRC/share/sttlab/index.html" "$SRC/share/sttlab/serve.py" \
         "$SRC/share/sttlab/term.html" "$SRC/share/sttlab/term49.py"; do
    if [ ! -f "$f" ]; then
        echo "Error: missing $f"
        exit 1
    fi
done

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/sttlab"
cp "$SRC/bin/sttlab" "$SRC/bin/sttlabs" "$PKG_ROOT/bin/"
cp "$SRC/share/sttlab/index.html" "$SRC/share/sttlab/serve.py" \
   "$SRC/share/sttlab/term.html" "$SRC/share/sttlab/term49.py" \
   "$PKG_ROOT/share/sttlab/"
if [ -f "$SRC/share/sttlab/STT-Drop.apk" ]; then
    cp "$SRC/share/sttlab/STT-Drop.apk" "$PKG_ROOT/share/sttlab/"
fi
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/sttlab/README-port.md"
chmod +x "$PKG_ROOT/bin/sttlab" "$PKG_ROOT/bin/sttlabs" \
    "$PKG_ROOT/share/sttlab/serve.py" "$PKG_ROOT/share/sttlab/term49.py"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$SRC/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
echo "qpkg install sttlabs  →  ports/web-sttlab-1.1.zip"
