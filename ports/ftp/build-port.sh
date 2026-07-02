#!/bin/sh
# Build berrycore/packages/util-ftp-1.0.0.zip from ftp-passport-qnx8.tar.gz
# Usage: ./build-port.sh [path-to-ftp-passport-qnx8.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$SCRIPT_DIR/ftp-passport-qnx8.tar.gz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/util-ftp-1.0.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$BUILD_DIR/pkg"
SRC_PREFIX="accounts/1000/shared/misc"
NT="/accounts/1000/shared/misc/berrycore"

echo "Building util-ftp 1.0.0 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING" "$PKG_ROOT"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$STAGING/$SRC_PREFIX/bin/ftp" ] || [ ! -x "$STAGING/$SRC_PREFIX/bin/bftpd" ]; then
    echo "Error: expected ftp and bftpd in tarball"
    exit 1
fi

mkdir -p "$PKG_ROOT/bin" "$PKG_ROOT/etc" "$PKG_ROOT/share/doc/ftp" \
    "$PKG_ROOT/var/log" "$PKG_ROOT/ftp-root"

cp "$STAGING/$SRC_PREFIX/bin/ftp" "$PKG_ROOT/bin/"
cp "$STAGING/$SRC_PREFIX/bin/ftp" "$PKG_ROOT/bin/pftp"
cp "$STAGING/$SRC_PREFIX/bin/bftpd" "$PKG_ROOT/bin/"
cp "$STAGING/$SRC_PREFIX/share/doc/ftp/MANUAL.md" "$PKG_ROOT/share/doc/ftp/" 2>/dev/null || \
    cp "$SCRIPT_DIR/MANUAL.md" "$PKG_ROOT/share/doc/ftp/"

# BerryCore paths in sample config
cat > "$PKG_ROOT/etc/bftpd.conf.example" << EOF
# bftpd.conf — BerryCore / Passport
# Copy: cp \$NATIVE_TOOLS/etc/bftpd.conf.example \$NATIVE_TOOLS/etc/bftpd.conf

USER="ftp"
GROUP="ftp"
PATH="${NT}/ftp-root"
PORT="8021"
ALLOW_ANONYMOUS="YES"
LOGFILE="${NT}/var/log/bftpd.log"
# Start: bftpd -c ${NT}/etc/bftpd.conf -D
# Note: on BB10, binding may require elevated privileges; use port 8021+ on LAN.
# Client always works: ftp other-host
EOF

cp "$SCRIPT_DIR/share/ftp/HELP.txt" "$PKG_ROOT/share/doc/ftp/" 2>/dev/null || true
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/doc/ftp/README-port.md" 2>/dev/null || true
touch "$PKG_ROOT/var/log/.keep" "$PKG_ROOT/ftp-root/.keep"

chmod +x "$PKG_ROOT/bin/ftp" "$PKG_ROOT/bin/pftp" "$PKG_ROOT/bin/bftpd"

cd "$PKG_ROOT"
zip -r -q "$CORE_ZIP" bin etc share var ftp-root
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$CORE_ZIP"
unzip -l "$CORE_ZIP"
