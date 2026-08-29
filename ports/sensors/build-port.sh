#!/bin/sh
# Build util-sensors-1.1.zip for qpkg install sensors
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/util-sensors-1.1.zip"
BUNDLED="$REPO_ROOT/berrycore/packages/util-sensors-1.1.zip"
BIN="$REPO_ROOT/berrycore/bin/sensors"
PKG_ROOT="$SCRIPT_DIR/.build/pkg"

if [ ! -f "$BIN" ]; then
	echo "Error: missing $BIN (copy the XPS-built ARM binary there first)" >&2
	exit 1
fi

rm -rf "$SCRIPT_DIR/.build"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/sensors" "$PKG_ROOT/share/doc/sensors"
cp "$BIN" "$PKG_ROOT/bin/sensors"
ln -sf sensors "$PKG_ROOT/bin/sensor"
cp "$SCRIPT_DIR/share/sensors/HELP.txt" "$PKG_ROOT/share/sensors/"
cp "$SCRIPT_DIR/share/sensors/HELP.txt" "$PKG_ROOT/share/doc/sensors/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/sensors/README.md"
chmod +x "$PKG_ROOT/bin/sensors"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$REPO_ROOT/berrycore/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
rm -rf "$SCRIPT_DIR/.build"

echo "Done: $PORT_ZIP"
ls -lh "$PORT_ZIP"
