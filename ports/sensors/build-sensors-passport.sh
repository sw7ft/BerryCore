#!/usr/bin/env bash
# Cross-build sensors for BlackBerry Passport (BPS) inside bb10-kitchen-sink.
set -euo pipefail

SRC_ROOT="${SRC_ROOT:-/root/ports/sensors}"
BUILD_DIR="${BUILD_DIR:-/root/ports/sensors/build}"
STAGE_DIR="$BUILD_DIR/stage"
PREFIX="${PREFIX:-/accounts/1000/shared/misc}"

if [ -f /root/bbndk/gcc9/bb10-gcc9/env.sh ]; then
	# shellcheck source=/dev/null
	source /root/bbndk/gcc9/bb10-gcc9/env.sh
fi

# Prefer official BB10 NDK qcc if BPS lives there (kitchen-sink gcc9 may lack libbps).
QCC=""
for c in \
	"${QNX_HOST:-}/usr/bin/qcc" \
	/root/bbndk/host_10_3_1_12/linux/x86/usr/bin/qcc \
	/opt/bbndk/host_10_3_1_995/linux/x86/usr/bin/qcc
do
	if [ -x "$c" ]; then
		QCC="$c"
		break
	fi
done

mkdir -p "$BUILD_DIR" "$STAGE_DIR$PREFIX/bin" "$STAGE_DIR$PREFIX/share/doc/sensors"

CFLAGS="-O2 -Wall -Wextra"
OUT="$BUILD_DIR/sensors"

if [ -n "$QCC" ]; then
	echo "Using qcc: $QCC"
	"$QCC" -Vgcc_ntoarmv7le $CFLAGS -o "$OUT" "$SRC_ROOT/src/sensors.c" -lbps
elif [ -n "${QNX_ABI:-}" ]; then
	echo "Using ${QNX_ABI}-gcc + -lbps"
	export CC="${QNX_ABI}-gcc"
	export STRIP="${QNX_ABI}-strip"
	SYSROOT="$QNX_PREBUILT"
	export CFLAGS="$CFLAGS -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp"
	export LDFLAGS="-L$SYSROOT/usr/lib -Wl,-rpath-link,$SYSROOT/usr/lib"
	"$CC" $CFLAGS -o "$OUT" "$SRC_ROOT/src/sensors.c" $LDFLAGS -lbps
	"$STRIP" "$OUT"
else
	echo "No QNX compiler found" >&2
	exit 1
fi

if command -v "${QNX_ABI:-ntoarmv7-}-strip" >/dev/null 2>&1; then
	"${QNX_ABI}-strip" "$OUT" || true
fi

install -D -m 755 "$OUT" "$STAGE_DIR$PREFIX/bin/sensors"
ln -sf sensors "$STAGE_DIR$PREFIX/bin/sensor"
if [ -f "$SRC_ROOT/share/sensors/HELP.txt" ]; then
	install -D -m 644 "$SRC_ROOT/share/sensors/HELP.txt" "$STAGE_DIR$PREFIX/share/doc/sensors/HELP.txt"
fi

PKG="$BUILD_DIR/sensors-passport-qnx8.tar.gz"
tar -C "$STAGE_DIR" -czf "$PKG" accounts

echo ""
echo "=== BUILD OK ==="
echo "Binary:  $STAGE_DIR$PREFIX/bin/sensors"
echo "Package: $PKG"
file "$STAGE_DIR$PREFIX/bin/sensors" || true
