#!/bin/sh
# Build net-dropbear-2026.91.1.zip for qpkg install dropbear
# Usage: ./build-port.sh [path-to-dropbear-passport-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/dropbear-passport-qnx8.tar.gz}"
PORT_ZIP="$REPO_ROOT/ports/net-dropbear-2026.91.1.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"

echo "Building dropbear 2026.91.1 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT/bin" "$PKG_ROOT/etc/dropbear" "$PKG_ROOT/share/doc/dropbear"
tar xzf "$INPUT_TGZ" -C "$STAGING"

for b in dbclient dropbear dropbearkey; do
    if [ ! -x "$STAGING/$SRC_PREFIX/bin/$b" ]; then
        echo "Error: expected $SRC_PREFIX/bin/$b in tarball"
        exit 1
    fi
    cp "$STAGING/$SRC_PREFIX/bin/$b" "$PKG_ROOT/bin/"
done

ln -sf dbclient "$PKG_ROOT/bin/ssh"
touch "$PKG_ROOT/etc/dropbear/.keep"

cp "$STAGING/$SRC_PREFIX/share/doc/dropbear/MANUAL.md" "$PKG_ROOT/share/doc/dropbear/" 2>/dev/null || \
    cp "$SCRIPT_DIR/MANUAL.md" "$PKG_ROOT/share/doc/dropbear/"
cp "$SCRIPT_DIR/share/dropbear/HELP.txt" "$PKG_ROOT/share/doc/dropbear/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/dropbear/README-port.md" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/"*

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin etc share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
