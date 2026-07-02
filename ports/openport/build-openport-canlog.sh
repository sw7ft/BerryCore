#!/usr/bin/env bash
# Cross-build openport for BlackBerry Passport (QNX 8 / armle-v7).
set -euo pipefail

SRC_ROOT="${SRC_ROOT:-/root/ports/openport-log}"
BUILD_DIR="${BUILD_DIR:-/root/ports/openport-log/build}"
STAGE_DIR="${BUILD_DIR}/stage"
PREFIX="${PREFIX:-/accounts/1000/shared/misc}"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"
# Host source: ~/Desktop/BlackBerry 10/ports/openport/ → container /root/ports/openport-log/

source /root/bbndk/gcc9/bb10-gcc9/env.sh

export CC="${QNX_ABI}-gcc"
export STRIP="${QNX_ABI}-strip"

SYSROOT="$QNX_PREBUILT"
export CFLAGS="-O2 -pipe -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp -Wall -Wextra"
export LDFLAGS="-L$SYSROOT/usr/lib -Wl,-rpath-link,$SYSROOT/usr/lib"

mkdir -p "$BUILD_DIR" "$STAGE_DIR/bin" "$STAGE_DIR$PREFIX/share/doc/openport"

cd "$SRC_ROOT/src"
"$CC" $CFLAGS -o "$BUILD_DIR/openport" \
  serial.c util.c openport.c uds.c main.c $LDFLAGS

"$STRIP" "$BUILD_DIR/openport"

install -D -m 755 "$BUILD_DIR/openport" "$STAGE_DIR$PREFIX/bin/openport"
ln -sf openport "$STAGE_DIR$PREFIX/bin/openport-canlog"

if [ -f "$SRC_ROOT/MANUAL.md" ]; then
  install -D -m 644 "$SRC_ROOT/MANUAL.md" "$STAGE_DIR$PREFIX/share/doc/openport/MANUAL.md"
fi
if [ -f "$SRC_ROOT/README.md" ]; then
  install -D -m 644 "$SRC_ROOT/README.md" "$STAGE_DIR$PREFIX/share/doc/openport/README.md"
fi

PKG="$BUILD_DIR/openport-passport-qnx8.tar.gz"
tar -C "$STAGE_DIR" -czf "$PKG" accounts

echo ""
echo "=== BUILD OK ==="
echo "Binary:  $STAGE_DIR$PREFIX/bin/openport"
echo "Manual:  $STAGE_DIR$PREFIX/share/doc/openport/MANUAL.md"
echo "Package: $PKG"
"${QNX_ABI}-readelf" -h "$STAGE_DIR$PREFIX/bin/openport" | grep -E 'Class|Machine|Flags'
