#!/bin/sh
# Build util-openport-1.0.0.zip for qpkg install openport
# Usage: ./build-port.sh [path-to-openport-passport-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/openport-passport-qnx8.tar.gz}"
PORT_ZIP="$REPO_ROOT/ports/util-openport-1.0.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"

echo "Building openport 1.0.0 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$STAGING/$SRC_PREFIX/bin/openport" ]; then
    echo "Error: expected $SRC_PREFIX/bin/openport in tarball"
    exit 1
fi

mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/openport"
cp "$STAGING/$SRC_PREFIX/bin/openport" "$PKG_ROOT/bin/openport"
cp "$STAGING/$SRC_PREFIX/bin/openport" "$PKG_ROOT/bin/openport-canlog"
cp "$STAGING/$SRC_PREFIX/share/doc/openport/"* "$PKG_ROOT/share/doc/openport/" 2>/dev/null || true
cp "$SCRIPT_DIR/share/openport/HELP.txt" "$PKG_ROOT/share/doc/openport/" 2>/dev/null || true
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/openport/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/openport" "$PKG_ROOT/bin/openport-canlog"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
unzip -l "$PORT_ZIP"
