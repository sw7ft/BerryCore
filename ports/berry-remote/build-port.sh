#!/bin/sh
# Build web-berry-remote-1.0.zip for qpkg install berry-remote
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PORT_ZIP="$REPO_ROOT/ports/web-berry-remote-1.0.zip"
BUNDLED="$REPO_ROOT/berrycore/packages/web-berry-remote-1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
PKG_ROOT="$BUILD_DIR/pkg"

echo "Building berry-remote 1.0..."
rm -rf "$BUILD_DIR"
mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/share/berry-remote"
cp "$SCRIPT_DIR/bin/berrybrowser" "$SCRIPT_DIR/bin/berryremote" "$PKG_ROOT/bin/"
chmod +x "$PKG_ROOT/bin/"*
cp "$SCRIPT_DIR/share/berry-remote/"* "$PKG_ROOT/share/berry-remote/"
chmod +x "$PKG_ROOT/share/berry-remote/"*.sh 2>/dev/null || true
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/berry-remote/README-port.md"

cd "$PKG_ROOT"
zip -r -q "$PORT_ZIP" bin share
cd - >/dev/null
mkdir -p "$REPO_ROOT/berrycore/packages"
cp -f "$PORT_ZIP" "$BUNDLED"
# PATH wrappers in the core tree
cp -f "$SCRIPT_DIR/bin/berrybrowser" "$SCRIPT_DIR/bin/berryremote" "$REPO_ROOT/berrycore/bin/"
chmod +x "$REPO_ROOT/berrycore/bin/berrybrowser" "$REPO_ROOT/berrycore/bin/berryremote"
rm -rf "$BUILD_DIR"

echo "Done:"
ls -lh "$PORT_ZIP" "$BUNDLED"
