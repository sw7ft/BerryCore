#!/bin/sh
# Build berrycore/packages/vim-9.1.2148.zip from vim-passport-9.1.2148-qnx8.tar.gz
# Usage: ./build-port.sh [path-to-vim-passport-9.1.2148-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/vim-passport-9.1.2148-qnx8.tar.gz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/vim-9.1.2148.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"

echo "Building vim 9.1.2148 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$STAGING/$SRC_PREFIX/bin/vim" ]; then
    echo "Error: expected $SRC_PREFIX/bin/vim in tarball"
    exit 1
fi

cp -R "$STAGING/$SRC_PREFIX/bin" "$PKG_ROOT/"
mkdir -p "$PKG_ROOT/share"
cp -R "$STAGING/$SRC_PREFIX/share/vim" "$PKG_ROOT/share/"

chmod +x "$PKG_ROOT/bin/"* 2>/dev/null || true

cd "$PKG_ROOT"
zip -r -q "$CORE_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$CORE_ZIP"
unzip -l "$CORE_ZIP" | head -20
