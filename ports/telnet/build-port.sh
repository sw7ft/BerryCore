#!/bin/sh
# Build net-telnet-0.17.zip for qpkg install telnet
# Usage: ./build-port.sh [path-to-telnet-passport-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/telnet-passport-qnx8.tar.gz}"
PORT_ZIP="$REPO_ROOT/ports/net-telnet-0.17.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"

echo "Building telnet 0.17 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/telnet"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$STAGING/$SRC_PREFIX/bin/telnet" ]; then
    echo "Error: expected $SRC_PREFIX/bin/telnet in tarball"
    exit 1
fi

cp "$STAGING/$SRC_PREFIX/bin/telnet" "$PKG_ROOT/bin/"
cp "$STAGING/$SRC_PREFIX/share/doc/telnet/MANUAL.md" "$PKG_ROOT/share/doc/telnet/" 2>/dev/null || \
    cp "$SCRIPT_DIR/MANUAL.md" "$PKG_ROOT/share/doc/telnet/"
cp "$SCRIPT_DIR/share/telnet/HELP.txt" "$PKG_ROOT/share/doc/telnet/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/telnet/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/telnet"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
