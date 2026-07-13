#!/bin/sh
# Build games-qnx-doom-1.1.zip for qpkg install qnx-doom
# Usage: ./build-port.sh [path-to-qnx_doom_deploy]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_DIR="${1:-$SCRIPT_DIR/qnx_doom_deploy}"
PORT_ZIP="$REPO_ROOT/ports/games-qnx-doom-1.1.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"
DOOM_ROOT="$PKG_ROOT/share/qnx-doom"
FREEDOOM_CACHE="$SCRIPT_DIR/.cache/freedoom-0.13.0.zip"
FREEDOOM_URL="https://github.com/freedoom/freedoom/releases/download/v0.13.0/freedoom-0.13.0.zip"

echo "Building qnx-doom 1.1 port..."
echo "  Input:  $INPUT_DIR"
echo "  Output: $PORT_ZIP"

if [ ! -x "$INPUT_DIR/bin/doomgeneric_qnx" ]; then
    echo "Error: $INPUT_DIR/bin/doomgeneric_qnx not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$DOOM_ROOT/bin" "$DOOM_ROOT/lib" "$DOOM_ROOT/scripts" "$DOOM_ROOT/apks" \
    "$DOOM_ROOT/wads" "$PKG_ROOT/bin" "$PKG_ROOT/share/doc/qnx-doom" "$SCRIPT_DIR/.cache"

# Fetch Freedoom IWAD (free game data — required to play)
if [ ! -f "$SCRIPT_DIR/.cache/freedoom1.wad" ]; then
    echo "  Downloading Freedoom 0.13.0 (freedoom1.wad)..."
    if [ ! -f "$FREEDOOM_CACHE" ]; then
        curl -sL -o "$FREEDOOM_CACHE" "$FREEDOOM_URL"
    fi
    unzip -p "$FREEDOOM_CACHE" freedoom-0.13.0/freedoom1.wad > "$SCRIPT_DIR/.cache/freedoom1.wad"
fi
cp "$SCRIPT_DIR/.cache/freedoom1.wad" "$DOOM_ROOT/wads/freedoom1.wad"
cp "$SCRIPT_DIR/wads/README.txt" "$DOOM_ROOT/wads/README.txt"

cp "$INPUT_DIR/bin/doomgeneric_qnx" "$DOOM_ROOT/bin/"
cp "$INPUT_DIR/lib/"*.so* "$DOOM_ROOT/lib/" 2>/dev/null || cp "$INPUT_DIR/lib/"* "$DOOM_ROOT/lib/"
cp "$SCRIPT_DIR/scripts/doom_run.sh" "$DOOM_ROOT/scripts/doom_run.sh"
cp "$INPUT_DIR/README.txt" "$DOOM_ROOT/README.txt"
if [ -f "$INPUT_DIR/xserver-xsdl-1-11-40-(Utility).apk" ]; then
    cp "$INPUT_DIR/xserver-xsdl-1-11-40-(Utility).apk" "$DOOM_ROOT/apks/"
fi

cp "$SCRIPT_DIR/bin/qnx-doom" "$PKG_ROOT/bin/qnx-doom"
cp "$SCRIPT_DIR/share/doc/qnx-doom/"* "$PKG_ROOT/share/doc/qnx-doom/"

chmod +x "$PKG_ROOT/bin/qnx-doom" "$DOOM_ROOT/bin/doomgeneric_qnx" "$DOOM_ROOT/scripts/doom_run.sh"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
ls -lh "$DOOM_ROOT/wads/freedoom1.wad" 2>/dev/null || ls -lh "$SCRIPT_DIR/.cache/freedoom1.wad"
