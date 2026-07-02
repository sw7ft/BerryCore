#!/bin/sh
# Build web-berry-browser-1.0.27.zip from browser-chromium-terminal-build27.zip
# Usage: ./build-port.sh [path-to-browser-chromium-terminal-build27.zip]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_ZIP="${1:-$SCRIPT_DIR/browser-chromium-terminal-build27.zip}"
[ -f "$INPUT_ZIP" ] || INPUT_ZIP="${REPO_ROOT}/browser-chromium-terminal-build27.zip"
PORT_ZIP="$REPO_ROOT/ports/web-berry-browser-1.0.27.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
APP_ROOT="$PKG_ROOT/share/berry-browser"

echo "Building berry-browser 1.0.27 port..."
echo "  Input:  $INPUT_ZIP"
echo "  Output: $PORT_ZIP"

if [ ! -f "$INPUT_ZIP" ]; then
    echo "Error: $INPUT_ZIP not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT/bin"
unzip -q "$INPUT_ZIP" -d "$STAGING"

if [ ! -x "$STAGING/bin/content_shell" ] || [ ! -x "$STAGING/bin/berry-browser" ]; then
    echo "Error: expected bin/content_shell and bin/berry-browser in zip"
    exit 1
fi

mkdir -p "$APP_ROOT/lib"
cp -R "$STAGING/bin" "$APP_ROOT/"
cp -R "$STAGING/lib" "$APP_ROOT/"
[ -d "$STAGING/share" ] && cp -R "$STAGING/share" "$APP_ROOT/"
[ -d "$STAGING/doc" ] && cp -R "$STAGING/doc" "$APP_ROOT/"
[ -f "$STAGING/VERSION" ] && cp "$STAGING/VERSION" "$APP_ROOT/"

# Upstream full-screen launcher → berry-browser-screen (CLI uses bin/berry-browser)
mv "$APP_ROOT/bin/berry-browser" "$APP_ROOT/bin/berry-browser-screen"

cp "$SCRIPT_DIR/share/berry-browser/HELP.txt" "$APP_ROOT/HELP.txt"
cp "$SCRIPT_DIR/share/berry-browser/lib/berry-browser-cli.sh" "$APP_ROOT/lib/"
cp "$SCRIPT_DIR/README.md" "$APP_ROOT/doc/README-port.md" 2>/dev/null || true

chmod +x "$APP_ROOT/bin/"* "$APP_ROOT/lib/"*.sh 2>/dev/null || true

for w in berry-browser browse content_shell berry-browser-screen; do
    cp "$SCRIPT_DIR/bin/$w" "$PKG_ROOT/bin/"
    chmod +x "$PKG_ROOT/bin/$w"
done

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$PORT_ZIP"
