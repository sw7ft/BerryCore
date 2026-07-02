#!/usr/bin/env bash
# Cross-build Vim 9.1 for BlackBerry Passport (armle-v7 / QNX 8) inside bb10-kitchen-sink.
set -euo pipefail

VIM_VERSION="${VIM_VERSION:-v9.1.2148}"
PREFIX="${PREFIX:-/accounts/1000/shared/misc}"
BUILD_DIR="${BUILD_DIR:-/root/ports/vim-build}"
SRC_DIR="$BUILD_DIR/vim-src"
STAGE_DIR="$BUILD_DIR/stage"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"

source /root/bbndk/gcc9/bb10-gcc9/env.sh

export CC="${QNX_ABI}-gcc"
export CXX="${QNX_ABI}-g++"
export AR="${QNX_ABI}-ar"
export RANLIB="${QNX_ABI}-ranlib"
export STRIP="${QNX_ABI}-strip"

SYSROOT="$QNX_PREBUILT"
NCURSES_INC="$QNX_TARGET/include"
NCURSES_LIB="$SYSROOT/usr/lib"

export CFLAGS="-O2 -pipe -mcpu=cortex-a9 -mthumb -mfpu=neon-vfpv3 -mfloat-abi=softfp"
export CPPFLAGS="-I$NCURSES_INC -D__QNXNTO__ -D__QNX__"
export LDFLAGS="-L$NCURSES_LIB -Wl,-rpath-link,$NCURSES_LIB"

mkdir -p "$BUILD_DIR" "$STAGE_DIR"
cd "$BUILD_DIR"

if [ ! -d "$SRC_DIR/.git" ]; then
  rm -rf "$SRC_DIR"
  git clone --depth 1 --branch "$VIM_VERSION" https://github.com/vim/vim.git "$SRC_DIR"
fi

cd "$SRC_DIR/src"

make distclean 2>/dev/null || true

# Cross-compile cache vars — see src/INSTALLx.txt
export ac_cv_sizeof_int=4
export vim_cv_getcwd_broken=no
export vim_cv_memmove_handles_overlap=yes
export vim_cv_stat_ignores_slash=yes
export vim_cv_tgetent=zero
export vim_cv_terminfo=yes
export vim_cv_toupper_broken=no

./configure \
  --build="$(uname -m)-linux-gnu" \
  --host="$QNX_ABI" \
  --target="$QNX_ABI" \
  --prefix="$PREFIX" \
  --with-features=huge \
  --enable-multibyte \
  --enable-terminal \
  --disable-gui \
  --disable-gtk \
  --disable-gtk2 \
  --disable-gnome \
  --disable-motif \
  --disable-athena \
  --disable-cscope \
  --disable-netbeans \
  --disable-channel \
  --without-x \
  --with-wayland=no \
  --with-compiledby="BerryCore-GCC9.3-Passport" \
  --with-tlib=ncursesw

# QNX: main.c calls qnx_init() when __QNXNTO__ is set; configure does not add os_qnx.o.
sed -i 's/^OS_EXTRA_OBJ.*/OS_EXTRA_OBJ\t= objects\/os_qnx.o/' auto/config.mk

make -j"$JOBS"
make DESTDIR="$STAGE_DIR" install

"$STRIP" "$STAGE_DIR$PREFIX/bin/vim" || true
[ -f "$STAGE_DIR$PREFIX/bin/xxd" ] && "$STRIP" "$STAGE_DIR$PREFIX/bin/xxd" || true

PKG="$BUILD_DIR/vim-passport-${VIM_VERSION#v}-qnx8.tar.gz"
tar -C "$STAGE_DIR" -czf "$PKG" accounts

echo ""
echo "=== BUILD OK ==="
echo "Binary:  $STAGE_DIR$PREFIX/bin/vim"
echo "Package: $PKG"
file "$STAGE_DIR$PREFIX/bin/vim"
"$STAGE_DIR$PREFIX/bin/vim" --version | head -3 || true
