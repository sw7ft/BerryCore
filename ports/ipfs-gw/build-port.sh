#!/bin/sh
# Build util-ipfs-gw-0.1.0.zip for qpkg install ipfs-gw
# Usage: ./build-port.sh [path-to-util-ipfs-gw-0.1.0.zip]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_ZIP="${1:-$REPO_ROOT/util-ipfs-gw-0.1.0.zip}"
PORT_ZIP="$REPO_ROOT/ports/util-ipfs-gw-0.1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"

echo "Building ipfs-gw 0.1.0 port..."
echo "  Input:  $INPUT_ZIP"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_ZIP" ]; then
    echo "Error: $INPUT_ZIP not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
unzip -q "$INPUT_ZIP" -d "$STAGING"

if [ ! -x "$STAGING/bin/ipfs-gw" ]; then
    echo "Error: expected bin/ipfs-gw in zip"
    exit 1
fi

mkdir -p "$STAGING/share/ipfs-gw"
cp "$SCRIPT_DIR/share/ipfs-gw/HELP.txt" "$STAGING/share/ipfs-gw/"
cp "$SCRIPT_DIR/README.md" "$STAGING/share/ipfs-gw/README-port.md" 2>/dev/null || true
chmod +x "$STAGING/bin/ipfs-gw"

cd "$STAGING"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
unzip -l "$PORT_ZIP"
