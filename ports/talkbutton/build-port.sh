#!/bin/sh
# Build util-talkbutton-1.0.zip for qpkg install talkbutton
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/util-talkbutton-1.0.zip"
BUNDLED="$REPO_ROOT/berrycore/packages/util-talkbutton-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"
SRC="$SCRIPT_DIR/share/talkbutton"
V2T="$REPO_ROOT/ports/voice2text/share/voice2text"

echo "Building talkbutton 1.0..."
echo "  Output: $PORT_ZIP"

if [ ! -f "$SRC/talkbutton.py" ] || [ ! -f "$SCRIPT_DIR/bin/talkbutton" ]; then
    echo "Error: talkbutton port incomplete"
    exit 1
fi
for f in qsa_capture.py vosk_engine.py button_watch.py bb_clipboard.py; do
    if [ ! -f "$V2T/$f" ]; then
        echo "Error: missing $V2T/$f (voice2text helpers)"
        exit 1
    fi
done

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/talkbutton"
cp "$SCRIPT_DIR/bin/talkbutton" "$PKG_ROOT/bin/"
chmod +x "$PKG_ROOT/bin/talkbutton"
cp "$SRC/talkbutton.py" "$SRC/HELP.txt" "$SCRIPT_DIR/context.md" \
    "$PKG_ROOT/share/talkbutton/"
cp "$V2T/qsa_capture.py" "$V2T/vosk_engine.py" \
    "$V2T/button_watch.py" "$V2T/bb_clipboard.py" \
    "$PKG_ROOT/share/talkbutton/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/talkbutton/README-port.md" 2>/dev/null || true

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$REPO_ROOT/berrycore/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
echo "qpkg install talkbutton  →  ports/util-talkbutton-1.0.zip"
