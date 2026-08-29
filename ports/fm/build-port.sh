#!/bin/sh
# Build util-fm-1.0.zip for qpkg install fm
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/util-fm-1.0.zip"
BUNDLED="$REPO_ROOT/berrycore/packages/util-fm-1.0.zip"
BIN="$REPO_ROOT/berrycore/bin/fm"
PKG_ROOT="$SCRIPT_DIR/.build/pkg"

if [ ! -f "$BIN" ]; then
	echo "Error: missing $BIN (copy the XPS-built ARM binary there first)" >&2
	exit 1
fi

rm -rf "$SCRIPT_DIR/.build"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/fm" "$PKG_ROOT/share/doc/fm"
cp "$BIN" "$PKG_ROOT/bin/fm"
cp "$SCRIPT_DIR/share/fm/HELP.txt" "$PKG_ROOT/share/fm/"
cp "$SCRIPT_DIR/share/fm/HELP.txt" "$PKG_ROOT/share/doc/fm/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/fm/README.md"
chmod +x "$PKG_ROOT/bin/fm"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$REPO_ROOT/berrycore/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$SCRIPT_DIR/.build"

echo "Done: $PORT_ZIP"
ls -lh "$PORT_ZIP"
