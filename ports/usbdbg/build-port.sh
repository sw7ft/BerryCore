#!/bin/sh
# Build util-usbdbg-1.0.0.zip for qpkg install usbdbg
# Usage: ./build-port.sh [path-to-usbdbg-passport-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/usbdbg-passport-qnx8.tar.gz}"
PORT_ZIP="$REPO_ROOT/ports/util-usbdbg-1.0.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"

echo "Building usbdbg 1.0.0 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/usbdbg"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$STAGING/$SRC_PREFIX/bin/usbdbg" ]; then
    echo "Error: expected $SRC_PREFIX/bin/usbdbg in tarball"
    exit 1
fi

cp "$STAGING/$SRC_PREFIX/bin/usbdbg" "$PKG_ROOT/bin/"
cp "$STAGING/$SRC_PREFIX/share/doc/usbdbg/MANUAL.md" "$PKG_ROOT/share/doc/usbdbg/" 2>/dev/null || \
    cp "$SCRIPT_DIR/MANUAL.md" "$PKG_ROOT/share/doc/usbdbg/"
cp "$SCRIPT_DIR/share/usbdbg/HELP.txt" "$PKG_ROOT/share/doc/usbdbg/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/usbdbg/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/usbdbg"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
