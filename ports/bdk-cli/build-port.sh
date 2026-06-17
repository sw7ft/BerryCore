#!/bin/sh
# Build crypto-bdk-cli-2.0.0.zip for qpkg install bdk-cli
# Usage: ./build-port.sh [path-to-bdk-cli-bb10-2.0.0.tgz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/bdk-cli-bb10-2.0.0.tgz}"
PORT_ZIP="$REPO_ROOT/ports/crypto-bdk-cli-2.0.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$STAGING/bdk-cli"

echo "Building bdk-cli 2.0.0 port..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$PKG_ROOT/bin/bdk-cli" ]; then
    echo "Error: expected bdk-cli/bin/bdk-cli in tarball"
    exit 1
fi

cp "$SCRIPT_DIR/setup-bdk-cli.sh" "$PKG_ROOT/setup-bdk-cli.sh"
cp "$SCRIPT_DIR/bin/berrycore-bdk-cli" "$PKG_ROOT/bin/berrycore-bdk-cli"
mkdir -p "$PKG_ROOT/share/bdk-cli" "$PKG_ROOT/data"
cp "$SCRIPT_DIR/share/bdk-cli/HELP.txt" "$PKG_ROOT/share/bdk-cli/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/bdk-cli/README-port.md" 2>/dev/null || true
touch "$PKG_ROOT/data/.keep"

chmod +x "$PKG_ROOT/setup-bdk-cli.sh" "$PKG_ROOT/bin/bdk-cli" "$PKG_ROOT/bin/berrycore-bdk-cli"

cd "$STAGING"
zip -r -q "$PORT_ZIP" bdk-cli
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
unzip -l "$PORT_ZIP" | head -20
