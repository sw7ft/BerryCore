#!/usr/bin/env bash
# Cross-build Dropbear 2026.91 (dropbear + dbclient + dropbearkey) for Passport.
set -euo pipefail

PREFIX="${PREFIX:-/accounts/1000/shared/misc}"
BUILD_DIR="${BUILD_DIR:-/root/ports/dropbear-build}"
STAGE_DIR="${BUILD_DIR}/stage"
DROPBEAR_VER="2026.91"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"
OPTS_DIR="${OPTS_DIR:-/root/ports/dropbear-opts}"
DOC_DIR="${DOC_DIR:-/root/ports/dropbear-docs}"

source /root/bbndk/gcc9/bb10-gcc9/env.sh

export CC="${QNX_ABI}-gcc"
export AR="${QNX_ABI}-ar"
export RANLIB="${QNX_ABI}-ranlib"
export STRIP="${QNX_ABI}-strip"
SYSROOT="$QNX_PREBUILT"
QINC="/root/qnx800/include"

export CFLAGS="-O2 -pipe -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp -D__QNXNTO__ -D__QNX__ -I${QINC}"
export LDFLAGS="-L${SYSROOT}/usr/lib -Wl,-rpath-link,${SYSROOT}/usr/lib"

mkdir -p "$BUILD_DIR" "$STAGE_DIR${PREFIX}/bin" "$STAGE_DIR${PREFIX}/etc/dropbear" \
	"$STAGE_DIR${PREFIX}/share/doc/dropbear"

cd "$BUILD_DIR"

if [ ! -d "dropbear-${DROPBEAR_VER}" ]; then
	curl -fsSL -o dropbear.tar.bz2 \
		"https://matt.ucc.asn.au/dropbear/releases/dropbear-${DROPBEAR_VER}.tar.bz2"
	tar xjf dropbear.tar.bz2
fi

cd "dropbear-${DROPBEAR_VER}"

install -D -m644 "${OPTS_DIR}/localoptions.h" ./localoptions.h

# Issue #6: single-user getgroups() check runs in dbclient too.
# IS_DROPBEAR_SERVER is a runtime macro (ses.isserver), so it cannot be
# used in #if. Skip the check on QNX (CFLAGS already pass -D__QNX__).
SESS="src/common-session.c"
if [ -f "$SESS" ]; then
	sed -i 's/#if !DROPBEAR_SVR_MULTIUSER\( && IS_DROPBEAR_SERVER\)\?$/#if !DROPBEAR_SVR_MULTIUSER \&\& !defined(__QNX__)/' "$SESS"
fi
if ! grep -q 'DROPBEAR_SVR_MULTIUSER && !defined(__QNX__)' "$SESS"; then
	echo "ERROR: common-session.c QNX patch did not apply" >&2
	exit 1
fi

./configure --host="${QNX_ABI}" --prefix="${PREFIX}" \
	--enable-static --disable-pam --disable-lastlog --disable-utmp --disable-wtmp \
	--disable-shadow --enable-bundled-libtom

make PROGRAMS="dropbear dbclient dropbearkey" -j"${JOBS}"

for bin in dropbear dbclient dropbearkey; do
	"${STRIP}" "$bin"
	install -D -m755 "$bin" "$STAGE_DIR${PREFIX}/bin/${bin}"
done

ln -sf dbclient "$STAGE_DIR${PREFIX}/bin/ssh"

if [ -f "${DOC_DIR}/MANUAL.md" ]; then
	install -D -m644 "${DOC_DIR}/MANUAL.md" "$STAGE_DIR${PREFIX}/share/doc/dropbear/MANUAL.md"
fi
if [ -f "${DOC_DIR}/dropbear.conf.example" ]; then
	install -D -m644 "${DOC_DIR}/dropbear.conf.example" "$STAGE_DIR${PREFIX}/etc/dropbear/dropbear.conf.example"
fi

PKG="$BUILD_DIR/dropbear-passport-qnx8.tar.gz"
tar -C "$STAGE_DIR" -czf "$PKG" accounts

echo ""
echo "=== BUILD OK ==="
echo "dropbear:    $STAGE_DIR${PREFIX}/bin/dropbear"
echo "dbclient:    $STAGE_DIR${PREFIX}/bin/dbclient  (ssh -> dbclient)"
echo "dropbearkey: $STAGE_DIR${PREFIX}/bin/dropbearkey"
echo "Package:     $PKG"
"${QNX_ABI}-readelf" -h "$STAGE_DIR${PREFIX}/bin/dbclient" | grep -E 'Machine|Flags'
ls -lh "$STAGE_DIR${PREFIX}/bin"/{dropbear,dbclient,dropbearkey,ssh}
