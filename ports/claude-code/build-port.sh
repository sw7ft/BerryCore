#!/bin/sh
# Build dev-claude-code-2.1.91.zip for qpkg install claude-code
# Usage: ./build-port.sh [path-to-package-dir]
#   package-dir must contain cli.js and vendor/ (patched Claude Code bundle)
# Default: ./staging/package (create with: scp -r passport:.../misc/package staging/)

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
OUTPUT_ZIP="$SCRIPT_DIR/../dev-claude-code-2.1.91.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PORT_ROOT="$BUILD_DIR/port"
PACKAGE_DIR="${1:-$SCRIPT_DIR/staging/package}"

echo "Building claude-code port..."
echo "  Package: $PACKAGE_DIR"
echo "  Output:  $OUTPUT_ZIP"

if [ ! -f "$PACKAGE_DIR/cli.js" ]; then
    echo "Error: $PACKAGE_DIR/cli.js not found"
    echo ""
    echo "Copy the patched bundle from a working BB10 install:"
    echo "  mkdir -p staging && scp -r passport:/accounts/1000/shared/misc/package staging/"
    echo "  ./build-port.sh staging/package"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PORT_ROOT/bin" "$PORT_ROOT/share/claude-code/package"

cp "$SCRIPT_DIR/bin/claude" "$PORT_ROOT/bin/"
cp "$SCRIPT_DIR/bin/claude-setup" "$PORT_ROOT/bin/"
chmod +x "$PORT_ROOT/bin/claude" "$PORT_ROOT/bin/claude-setup"

cp "$SCRIPT_DIR/share/claude-code/bb10-fetch-polyfill.cjs" "$PORT_ROOT/share/claude-code/"
cp "$SCRIPT_DIR/share/claude-code/context.md" "$PORT_ROOT/share/claude-code/"
cp "$SCRIPT_DIR/share/claude-code/HELP.txt" "$PORT_ROOT/share/claude-code/"
cp "$SCRIPT_DIR/share/claude-code/claude.key.example" "$PORT_ROOT/share/claude-code/"
cp "$SCRIPT_DIR/README.md" "$PORT_ROOT/share/claude-code/" 2>/dev/null || true
mkdir -p "$PORT_ROOT/share/claude-code/build"
cp "$SCRIPT_DIR/share/claude-code/build/"*.py "$PORT_ROOT/share/claude-code/build/" 2>/dev/null || true

echo "Copying Claude Code bundle (this may take a moment)..."
cp -R "$PACKAGE_DIR/"* "$PORT_ROOT/share/claude-code/package/"
chmod +x "$PORT_ROOT/share/claude-code/package/cli.js" 2>/dev/null || true

echo "Packaging..."
cd "$PORT_ROOT"
zip -r -q "$OUTPUT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done: $OUTPUT_ZIP"
ls -lh "$OUTPUT_ZIP"
