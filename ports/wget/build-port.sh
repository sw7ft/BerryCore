#!/bin/sh
# Build berrycore/packages/wget-1.25.0.zip from wget-bb10-1.25.0.tgz
# Usage: ./build-port.sh [path-to-wget-bb10-1.25.0.tgz]
# Default: ../../wget-bb10-1.25.0.tgz

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/wget-bb10-1.25.0.tgz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/wget-1.25.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building wget 1.25.0 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -f "$STAGING/wget/bin/wget.bin" ]; then
    echo "Error: expected wget/bin/wget.bin inside tarball"
    exit 1
fi

mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/wget/certs"

cp "$SCRIPT_DIR/bin/wget" "$PKG_ROOT/bin/"
cp "$STAGING/wget/bin/wget.bin" "$PKG_ROOT/bin/"
cp "$STAGING/wget/certs/cacert.pem" "$PKG_ROOT/share/wget/certs/"
cp "$SCRIPT_DIR/share/wget/HELP.txt" "$PKG_ROOT/share/wget/"
chmod +x "$PKG_ROOT/bin/wget" "$PKG_ROOT/bin/wget.bin"

cd "$PKG_ROOT"
zip -r -q "$CORE_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done: $CORE_ZIP"
ls -lh "$CORE_ZIP"
