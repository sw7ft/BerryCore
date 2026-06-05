#!/bin/sh
# Build net-wget-1.25.0.zip and berrycore/packages/wget-1.25.0.zip
# Usage: ./build-port.sh [path-to-wget-bb10-1.25.0.tgz]
# Default: ../../wget-bb10-1.25.0.tgz

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/wget-bb10-1.25.0.tgz}"
PORT_ZIP="$SCRIPT_DIR/../net-wget-1.25.0.zip"
CORE_ZIP="$REPO_ROOT/berrycore/packages/wget-1.25.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PORT_ROOT="$BUILD_DIR/port"

echo "Building wget 1.25.0 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Port:   $PORT_ZIP"
echo "  Core:   $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

if [ ! -f "$STAGING/wget/bin/wget.bin" ]; then
    rm -rf "$BUILD_DIR"
    mkdir -p "$STAGING"
    tar xzf "$INPUT_TGZ" -C "$STAGING"
fi

if [ ! -f "$STAGING/wget/bin/wget.bin" ]; then
    echo "Error: expected wget/bin/wget.bin inside tarball"
    exit 1
fi

rm -rf "$PORT_ROOT"
mkdir -p "$PORT_ROOT/bin" "$PORT_ROOT/share/wget/certs"

cp "$SCRIPT_DIR/bin/wget" "$PORT_ROOT/bin/"
cp "$STAGING/wget/bin/wget.bin" "$PORT_ROOT/bin/"
cp "$STAGING/wget/certs/cacert.pem" "$PORT_ROOT/share/wget/certs/"
cp "$SCRIPT_DIR/share/wget/HELP.txt" "$PORT_ROOT/share/wget/"
cp "$SCRIPT_DIR/README.md" "$PORT_ROOT/share/wget/" 2>/dev/null || true
chmod +x "$PORT_ROOT/bin/wget" "$PORT_ROOT/bin/wget.bin"

echo "Packaging..."
cd "$PORT_ROOT"
zip -r -q "$PORT_ZIP" bin share
zip -r -q "$CORE_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP" "$CORE_ZIP"
