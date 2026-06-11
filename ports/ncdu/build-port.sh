#!/bin/sh
# Build berrycore/packages/ncdu-1.22.zip from ncdu-bb10-1.22.tgz
# Usage: ./build-port.sh [path-to-ncdu-bb10-1.22.tgz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/ncdu-bb10-1.22.tgz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/ncdu-1.22.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC="$STAGING/ncdu"

echo "Building ncdu 1.22 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -f "$SRC/bin/ncdu" ]; then
    echo "Error: expected ncdu/bin/ncdu in tarball"
    exit 1
fi

mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/ncdu"

cp "$SCRIPT_DIR/bin/ncdu" "$PKG_ROOT/bin/"
cp "$SRC/bin/ncdu" "$PKG_ROOT/bin/ncdu.bin"
cp "$SCRIPT_DIR/share/ncdu/HELP.txt" "$PKG_ROOT/share/ncdu/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/ncdu/" 2>/dev/null || true
cp "$SRC/docs/GUIDE.md" "$PKG_ROOT/share/ncdu/" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/ncdu" "$PKG_ROOT/bin/ncdu.bin"

cd "$PKG_ROOT"
zip -r -q "$CORE_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done: $CORE_ZIP"
ls -lh "$CORE_ZIP"
unzip -l "$CORE_ZIP"
