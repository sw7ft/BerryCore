#!/bin/sh
# Build berrycore/packages/dcron-4.5.zip from dcron-bb10-4.5.tgz
# Usage: ./build-port.sh [path-to-dcron-bb10-4.5.tgz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/dcron-bb10-4.5.tgz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/dcron-4.5.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC="$STAGING/cron-pkg"

echo "Building dcron 4.5 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -f "$SRC/sbin/crond" ] || [ ! -f "$SRC/bin/crontab.bin" ]; then
    echo "Error: expected cron-pkg/sbin/crond and bin/crontab.bin in tarball"
    exit 1
fi

mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/sbin" "$PKG_ROOT/cron" \
    "$PKG_ROOT/cron/crontabs" "$PKG_ROOT/cron/cronstamps" "$PKG_ROOT/cron/cron.d" \
    "$PKG_ROOT/share/dcron" "$PKG_ROOT/share/man/man1" "$PKG_ROOT/share/man/man8"

cp "$SCRIPT_DIR/bin/crontab" "$SCRIPT_DIR/bin/cron-start" "$SCRIPT_DIR/bin/cron-stop" "$PKG_ROOT/bin/"
cp "$SRC/bin/crontab.bin" "$PKG_ROOT/bin/"
cp "$SRC/sbin/crond" "$PKG_ROOT/sbin/"
cp "$SRC/cron/start-crond.sh" "$SRC/cron/stop-crond.sh" "$PKG_ROOT/cron/"
cp "$SCRIPT_DIR/cron/example.crontab" "$PKG_ROOT/cron/"
cp "$SCRIPT_DIR/share/dcron/HELP.txt" "$PKG_ROOT/share/dcron/"
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/dcron/" 2>/dev/null || true
cp "$SRC/share/man/man1/crontab.1" "$PKG_ROOT/share/man/man1/" 2>/dev/null || true
cp "$SRC/share/man/man8/crond.8" "$PKG_ROOT/share/man/man8/" 2>/dev/null || true

chmod +x "$PKG_ROOT/bin/crontab" "$PKG_ROOT/bin/cron-start" "$PKG_ROOT/bin/cron-stop" \
    "$PKG_ROOT/bin/crontab.bin" "$PKG_ROOT/sbin/crond" \
    "$PKG_ROOT/cron/start-crond.sh" "$PKG_ROOT/cron/stop-crond.sh"

touch "$PKG_ROOT/cron/crontabs/.keep" "$PKG_ROOT/cron/cronstamps/.keep" "$PKG_ROOT/cron/cron.d/.keep"

cd "$PKG_ROOT"
zip -r -q "$CORE_ZIP" bin sbin cron share
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done: $CORE_ZIP"
ls -lh "$CORE_ZIP"
unzip -l "$CORE_ZIP"
