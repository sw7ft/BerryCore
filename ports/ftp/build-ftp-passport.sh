#!/usr/bin/env bash
# Cross-build classic netkit-ftp + bftpd for BlackBerry Passport (QNX 8).
set -euo pipefail

PREFIX="${PREFIX:-/accounts/1000/shared/misc}"
BUILD_DIR="${BUILD_DIR:-/root/ports/ftp-build}"
STAGE_DIR="${BUILD_DIR}/stage"
NETKIT_VER="0.17"
BFTPD_VER="5.4"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"

source /root/bbndk/gcc9/bb10-gcc9/env.sh

export CC="${QNX_ABI}-gcc"
export STRIP="${QNX_ABI}-strip"
SYSROOT="$QNX_PREBUILT"

export CFLAGS="-O2 -pipe -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp -D__QNXNTO__ -D__QNX__"
export CPPFLAGS="-I$QNX_TARGET/include"
export LDFLAGS="-L$SYSROOT/usr/lib -Wl,-rpath-link,$SYSROOT/usr/lib"

mkdir -p "$BUILD_DIR" "$STAGE_DIR$PREFIX/bin" "$STAGE_DIR$PREFIX/etc" \
  "$STAGE_DIR$PREFIX/share/doc/ftp" "$STAGE_DIR$PREFIX/var/log"

cd "$BUILD_DIR"

# --- netkit-ftp (classic ftp client) ---
if [ ! -d "netkit-ftp-${NETKIT_VER}" ]; then
  curl -fsSL -o netkit-ftp.tgz \
    "http://ftp.debian.org/debian/pool/main/n/netkit-ftp/netkit-ftp_${NETKIT_VER}.orig.tar.gz"
  tar xzf netkit-ftp.tgz
fi

cd "netkit-ftp-${NETKIT_VER}"
./configure --prefix="$PREFIX" --without-readline 2>/dev/null || \
  ./configure --prefix="$PREFIX" --without-readline
sed -i "s|^CC=.*|CC=${QNX_ABI}-gcc|" MCONFIG
sed -i "s|^CFLAGS=.*|CFLAGS=${CFLAGS} -DL_SET=0 -DL_INCR=1 -DL_XTND=2|" MCONFIG
sed -i "s|^LDFLAGS=.*|LDFLAGS=${LDFLAGS}|" MCONFIG
make -C ftp clean
make -C ftp
"$STRIP" ftp/ftp
install -D -m755 ftp/ftp "$STAGE_DIR$PREFIX/bin/ftp"
ln -sf ftp "$STAGE_DIR$PREFIX/bin/pftp"
cd "$BUILD_DIR"

# --- bftpd (FTP server) ---
if [ ! -d "bftpd" ]; then
  curl -fsSL -L -o bftpd.tgz \
    "https://downloads.sourceforge.net/project/bftpd/bftpd/bftpd-${BFTPD_VER}/bftpd-${BFTPD_VER}.tar.gz"
  tar xzf bftpd.tgz
  mv "bftpd-${BFTPD_VER}" bftpd 2>/dev/null || true
fi

cd bftpd
# Apply QNX patches if present
PATCH_DIR="/root/ports/ftp-patches"
if [ -d "$PATCH_DIR" ]; then
  for p in "$PATCH_DIR"/*.patch; do
    [ -f "$p" ] && patch -p1 -N < "$p" || true
  done
fi
# Inline patches (idempotent sed)
sed -i 's/sig_t save_quit, save_int, save_chld;/void (*save_quit)(int), (*save_int)(int), (*save_chld)(int);/' commands.c
sed -i 's/#if !defined(__minix) && !defined(__NetBSD__)/#if !defined(__minix) \&\& !defined(__NetBSD__) \&\& !defined(__QNXNTO__)/' login.c
sed -i 's/#ifndef __minix/#if !defined(__minix) \&\& !defined(__QNXNTO__)/' dirlist.c

make distclean 2>/dev/null || rm -f config.cache config.status
export ac_cv_func_setpgrp_void=yes
export ac_cv_lib_crypt_crypt=no
export ac_cv_header_asm_socket_h=no
export ac_cv_header_crypt_h=no
./configure --host="$QNX_ABI" --prefix="$PREFIX"
sed -i "s|^CFLAGS = .*|CFLAGS = ${CFLAGS} -DHAVE_CONFIG_H -Wall -I. -DVERSION=\\\\\"${BFTPD_VER}\\\\\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DPREFIX=\\\\\"${PREFIX}\\\\\\\"|" Makefile
sed -i "s|^LDFLAGS = .*|LDFLAGS = ${LDFLAGS}|" Makefile
make CC="$CC" -j"$JOBS"
"$STRIP" bftpd
install -D -m755 bftpd "$STAGE_DIR$PREFIX/bin/bftpd"
cd "$BUILD_DIR"

# Docs + sample config
install -D -m644 /root/ports/ftp-docs/bftpd.conf.example "$STAGE_DIR$PREFIX/etc/bftpd.conf.example" 2>/dev/null || \
  install -D -m644 "$BUILD_DIR/../ftp/bftpd.conf.example" "$STAGE_DIR$PREFIX/etc/bftpd.conf.example" 2>/dev/null || true
install -D -m644 /root/ports/ftp-docs/MANUAL.md "$STAGE_DIR$PREFIX/share/doc/ftp/MANUAL.md" 2>/dev/null || true

PKG="$BUILD_DIR/ftp-passport-qnx8.tar.gz"
tar -C "$STAGE_DIR" -czf "$PKG" accounts

echo ""
echo "=== BUILD OK ==="
echo "ftp:   $STAGE_DIR$PREFIX/bin/ftp"
echo "bftpd: $STAGE_DIR$PREFIX/bin/bftpd"
echo "Package: $PKG"
"${QNX_ABI}-readelf" -h "$STAGE_DIR$PREFIX/bin/ftp" | grep -E 'Machine|Flags'
"${QNX_ABI}-readelf" -h "$STAGE_DIR$PREFIX/bin/bftpd" | grep -E 'Machine|Flags'
