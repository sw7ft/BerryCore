#!/bin/sh
# Build ai-vosk-1.0.zip for qpkg install vosk
# Payload: ports/vosk/.payload/{libvosk.so,vosk.bin,model/}
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC="$REPO_ROOT/berrycore"
PAYLOAD="$SCRIPT_DIR/.payload"
PORT_ZIP="$REPO_ROOT/ports/ai-vosk-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building vosk 1.0..."
if [ ! -f "$PAYLOAD/libvosk.so" ] || [ ! -x "$PAYLOAD/vosk.bin" ] || [ ! -d "$PAYLOAD/model" ]; then
    echo "Error: missing $PAYLOAD (libvosk.so, vosk.bin, model/)"
    echo "Copy from Passport: /accounts/1000/shared/misc/stt/{lib,bin,model/vosk-en}"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/lib" "$PKG_ROOT/share/stt/model" "$PKG_ROOT/share/doc/vosk"
cp "$SRC/bin/vosk" "$PKG_ROOT/bin/vosk"
cp "$PAYLOAD/vosk.bin" "$PKG_ROOT/bin/vosk.bin"
cp "$PAYLOAD/libvosk.so" "$PKG_ROOT/lib/libvosk.so"
cp -R "$PAYLOAD/model" "$PKG_ROOT/share/stt/model/vosk-en"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/vosk/README.md"
chmod +x "$PKG_ROOT/bin/vosk" "$PKG_ROOT/bin/vosk.bin" "$PKG_ROOT/lib/libvosk.so"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin lib share
cd - >/dev/null
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP"
echo "qpkg install vosk  →  ports/ai-vosk-1.0.zip"
