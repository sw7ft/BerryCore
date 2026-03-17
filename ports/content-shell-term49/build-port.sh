#!/bin/sh
# Build web-content-shell-term49-1.0.zip from content-shell-term49.zip
# Usage: ./build-port.sh [path-to-content-shell-term49.zip]
# Default: ../../content-shell-term49.zip (from repo root)

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_ZIP="${1:-$REPO_ROOT/content-shell-term49.zip}"
OUTPUT_ZIP="$SCRIPT_DIR/../web-content-shell-term49-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PORT_ROOT="$BUILD_DIR/port"

echo "Building content-shell-term49 port..."
echo "  Input:  $INPUT_ZIP"
echo "  Output: $OUTPUT_ZIP"

if [ ! -f "$INPUT_ZIP" ]; then
    echo "Error: $INPUT_ZIP not found"
    echo "Place content-shell-term49.zip at repo root or pass path as argument"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PORT_ROOT/bin" "$PORT_ROOT/share/content-shell-term49"

# Extract source zip
echo "Extracting..."
TMP_EXTRACT="$BUILD_DIR/extract"
mkdir -p "$TMP_EXTRACT"
unzip -q -o "$INPUT_ZIP" -d "$TMP_EXTRACT"

# Find the content shell files (may be in term49-content-shell/ or at root)
SRC_DIR="$TMP_EXTRACT"
if [ -d "$TMP_EXTRACT/term49-content-shell" ]; then
    SRC_DIR="$TMP_EXTRACT/term49-content-shell"
elif [ -d "$TMP_EXTRACT/content-shell-term49" ]; then
    SRC_DIR="$TMP_EXTRACT/content-shell-term49"
fi

# Copy Chromium binary + libs to share
echo "Copying content-shell files..."
cp -R "$SRC_DIR"/* "$PORT_ROOT/share/content-shell-term49/" 2>/dev/null || true

# Ensure binary is executable
for exe in content_shell content-shell; do
    [ -f "$PORT_ROOT/share/content-shell-term49/$exe" ] && chmod +x "$PORT_ROOT/share/content-shell-term49/$exe"
done

# Copy our wrapper and HELP
cp "$SCRIPT_DIR/bin/content_shell" "$PORT_ROOT/bin/"
cp "$SCRIPT_DIR/share/content-shell-term49/HELP.txt" "$PORT_ROOT/share/content-shell-term49/"
chmod +x "$PORT_ROOT/bin/content_shell"

# Copy README to share
cp "$SCRIPT_DIR/README.md" "$PORT_ROOT/share/content-shell-term49/" 2>/dev/null || true

# Create zip (from port root, so paths are bin/ and share/)
echo "Packaging..."
cd "$PORT_ROOT"
zip -r -q "$OUTPUT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done: $OUTPUT_ZIP"
ls -la "$OUTPUT_ZIP"
