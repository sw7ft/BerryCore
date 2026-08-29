#!/bin/sh
# Build util-mem-1.0.zip for qpkg install mem
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/util-mem-1.0.zip"
BUNDLED="$REPO_ROOT/berrycore/packages/util-mem-1.0.zip"
BIN="$REPO_ROOT/berrycore/bin/mem"
PKG_ROOT="$SCRIPT_DIR/.build/pkg"

if [ ! -f "$BIN" ]; then
	echo "Error: missing $BIN (copy the XPS-built ARM binary there first)" >&2
	exit 1
fi

rm -rf "$SCRIPT_DIR/.build"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/mem" "$PKG_ROOT/share/doc/mem"
cp "$BIN" "$PKG_ROOT/bin/mem"
cp "$SCRIPT_DIR/share/mem/HELP.txt" "$PKG_ROOT/share/mem/"
cp "$SCRIPT_DIR/share/mem/HELP.txt" "$PKG_ROOT/share/doc/mem/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/mem/README.md"
chmod +x "$PKG_ROOT/bin/mem"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$REPO_ROOT/berrycore/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$SCRIPT_DIR/.build"

echo "Done: $PORT_ZIP"
ls -lh "$PORT_ZIP"
