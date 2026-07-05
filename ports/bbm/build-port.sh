#!/bin/sh
# Build net-bbm-1.0.0.zip for qpkg install bbm
# Usage: ./build-port.sh [path-to-bbm-passport-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/bbm-passport-qnx8.tar.gz}"
PORT_ZIP="$REPO_ROOT/ports/net-bbm-1.0.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"

echo "Building bbm 1.0.0 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/bbm"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$STAGING/$SRC_PREFIX/bin/bbm" ]; then
    echo "Error: expected $SRC_PREFIX/bin/bbm in tarball"
    exit 1
fi

cp "$STAGING/$SRC_PREFIX/bin/bbm" "$PKG_ROOT/bin/"
ln -sf bbm "$PKG_ROOT/bin/berrymsg"
cp "$STAGING/$SRC_PREFIX/share/doc/bbm/MANUAL.md" "$PKG_ROOT/share/doc/bbm/" 2>/dev/null || \
    cp "$SCRIPT_DIR/MANUAL.md" "$PKG_ROOT/share/doc/bbm/"
cp "$STAGING/$SRC_PREFIX/share/doc/bbm/env.example" "$PKG_ROOT/share/doc/bbm/" 2>/dev/null || \
    cp "$SCRIPT_DIR/env.example" "$PKG_ROOT/share/doc/bbm/"
cp "$SCRIPT_DIR/share/bbm/HELP.txt" "$PKG_ROOT/share/doc/bbm/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/bbm/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/bbm"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
