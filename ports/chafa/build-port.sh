#!/bin/sh
# Build berrycore/packages/chafa-1.14.4.zip from chafa-bb10-1.14.4.tgz
# Usage: ./build-port.sh [path-to-chafa-bb10-1.14.4.tgz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/chafa-bb10-1.14.4.tgz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/chafa-1.14.4.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC="$STAGING/chafa"

echo "Building chafa 1.14.4 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -f "$SRC/bin/chafa.bin" ] || [ ! -f "$SRC/lib/libchafa.so.9" ]; then
    echo "Error: expected chafa/bin/chafa.bin and lib/libchafa.so.9 in tarball"
    exit 1
fi

mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/lib" "$PKG_ROOT/share/chafa/examples"

cp "$SCRIPT_DIR/bin/chafa" "$SCRIPT_DIR/bin/chafa-show" "$PKG_ROOT/bin/"
cp "$SRC/bin/chafa.bin" "$PKG_ROOT/bin/"
cp "$SRC/lib/libchafa.so.9" "$PKG_ROOT/lib/"
ln -sf libchafa.so.9 "$PKG_ROOT/lib/libchafa.so"
cp "$SCRIPT_DIR/share/chafa/HELP.txt" "$PKG_ROOT/share/chafa/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/chafa/" 2>/dev/null || true
cp "$SRC/docs/GUIDE.md" "$PKG_ROOT/share/chafa/" 2>/dev/null || true
cp "$SRC/examples/show-sdcard-photo.sh" "$PKG_ROOT/share/chafa/examples/" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/chafa" "$PKG_ROOT/bin/chafa-show" "$PKG_ROOT/bin/chafa.bin"
chmod +x "$PKG_ROOT/share/chafa/examples/"*.sh 2>/dev/null || true

cd "$PKG_ROOT"
zip -r -q "$CORE_ZIP" bin lib share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done: $CORE_ZIP"
ls -lh "$CORE_ZIP"
unzip -l "$CORE_ZIP"
