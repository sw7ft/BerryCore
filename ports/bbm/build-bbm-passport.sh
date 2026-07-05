#!/usr/bin/env bash
# Cross-build bbm (Berry Bridge Messenger) for BlackBerry Passport (QNX 8).
set -euo pipefail

SRC_ROOT="${SRC_ROOT:-/root/ports/bbm}"
BUILD_DIR="${BUILD_DIR:-/root/ports/bbm/build}"
STAGE_DIR="${BUILD_DIR}/stage"
PREFIX="${PREFIX:-/accounts/1000/shared/misc}"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"

source /root/bbndk/gcc9/bb10-gcc9/env.sh

export CC="${QNX_ABI}-gcc"
export STRIP="${QNX_ABI}-strip"

SYSROOT="$QNX_PREBUILT"
export CFLAGS="-O2 -pipe -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp -Wall -Wextra"
export LDFLAGS="-L$SYSROOT/usr/lib -Wl,-rpath-link,$SYSROOT/usr/lib"

mkdir -p "$BUILD_DIR" "$STAGE_DIR$PREFIX/bin" "$STAGE_DIR$PREFIX/share/doc/bbm"

cd "$SRC_ROOT/src"
"$CC" $CFLAGS -o "$BUILD_DIR/bbm" main.c relay.c util.c $LDFLAGS
"$STRIP" "$BUILD_DIR/bbm"

install -D -m 755 "$BUILD_DIR/bbm" "$STAGE_DIR$PREFIX/bin/bbm"
ln -sf bbm "$STAGE_DIR$PREFIX/bin/berrymsg"

if [ -f "$SRC_ROOT/MANUAL.md" ]; then
  install -D -m 644 "$SRC_ROOT/MANUAL.md" "$STAGE_DIR$PREFIX/share/doc/bbm/MANUAL.md"
fi
if [ -f "$SRC_ROOT/env.example" ]; then
  install -D -m 644 "$SRC_ROOT/env.example" "$STAGE_DIR$PREFIX/share/doc/bbm/env.example"
fi

PKG="$BUILD_DIR/bbm-passport-qnx8.tar.gz"
tar -C "$STAGE_DIR" -czf "$PKG" accounts

echo ""
echo "=== BUILD OK ==="
echo "Binary:  $STAGE_DIR$PREFIX/bin/bbm"
echo "Package: $PKG"
"${QNX_ABI}-readelf" -h "$STAGE_DIR$PREFIX/bin/bbm" | grep -E 'Class|Machine|Flags'
