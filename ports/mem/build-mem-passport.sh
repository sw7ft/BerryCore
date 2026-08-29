#!/usr/bin/env bash
# Cross-build mem for BlackBerry Passport inside bb10-kitchen-sink.
set -euo pipefail

SRC_ROOT="${SRC_ROOT:-/root/ports/mem}"
BUILD_DIR="${BUILD_DIR:-/root/ports/mem/build}"
STAGE_DIR="$BUILD_DIR/stage"
PREFIX="${PREFIX:-/accounts/1000/shared/misc}"

if [ -f /root/bbndk/gcc9/bb10-gcc9/env.sh ]; then
	# shellcheck source=/dev/null
	source /root/bbndk/gcc9/bb10-gcc9/env.sh
fi

mkdir -p "$BUILD_DIR" "$STAGE_DIR$PREFIX/bin"

CFLAGS="-O2 -Wall -Wextra"
OUT="$BUILD_DIR/mem"

if [ -z "${QNX_ABI:-}" ]; then
	echo "No QNX compiler found" >&2
	exit 1
fi

export CC="${QNX_ABI}-gcc"
export STRIP="${QNX_ABI}-strip"
SYSROOT="$QNX_PREBUILT"
export CFLAGS="$CFLAGS -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp"
export LDFLAGS="-L$SYSROOT/lib -L$SYSROOT/usr/lib -Wl,-rpath-link,$SYSROOT/lib -Wl,-rpath-link,$SYSROOT/usr/lib"
"$CC" $CFLAGS -o "$OUT" "$SRC_ROOT/src/mem.c" $LDFLAGS
"$STRIP" "$OUT"

install -D -m 755 "$OUT" "$STAGE_DIR$PREFIX/bin/mem"
echo "=== BUILD OK ==="
file "$STAGE_DIR$PREFIX/bin/mem" || true
ls -l "$STAGE_DIR$PREFIX/bin/mem"
