#!/bin/sh
# Split XPS Passport tarballs into individual qpkg port zips.
# Usage: ./split-xps-bundle.sh [--from-passport user@host]
#
# Inputs (ports/.xps-src/):
#   berrycore-ports-passport-qnx8.tar.gz
#   dos-retro-passport-qnx8.tar.gz
#   retro-interop-passport-qnx8.tar.gz
#
# Optional: --from-passport pulls missing binaries via scp
#
# Outputs:
#   ports/util-<name>-<version>.zip
#   ports/scripts/xps-generated-packages.tsv (append to PACKAGES)

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SRC_DIR="$REPO_ROOT/ports/.xps-src"
STAGING="$SCRIPT_DIR/.xps-staging"
BIN_SRC="$STAGING/accounts/1000/shared/misc/bin"
MANIFEST="$SCRIPT_DIR/xps-manifest.tsv"
GENERATED="$SCRIPT_DIR/xps-generated-packages.tsv"
PASSPORT_SSH=""

while [ $# -gt 0 ]; do
    case "$1" in
        --from-passport)
            PASSPORT_SSH="${2:-passport}"
            shift 2
            ;;
        *)
            echo "Unknown option: $1" >&2
            exit 1
            ;;
    esac
done

echo "=== XPS bundle splitter ==="
rm -rf "$STAGING"
mkdir -p "$BIN_SRC"

for tgz in berrycore-ports-passport-qnx8.tar.gz \
           dos-retro-passport-qnx8.tar.gz \
           retro-interop-passport-qnx8.tar.gz; do
    if [ -f "$SRC_DIR/$tgz" ]; then
        echo "Extracting $tgz..."
        tar -xzf "$SRC_DIR/$tgz" -C "$STAGING" 2>/dev/null || true
    fi
done

# Pull binaries listed in manifest but missing from tarballs
if [ -n "$PASSPORT_SSH" ]; then
    echo "Checking Passport for missing binaries..."
    while IFS='|' read -r name _rest; do
        [ -z "$name" ] && continue
        echo "$name" | grep -q '^#' && continue
        if [ ! -f "$BIN_SRC/$name" ]; then
            echo "  scp $name from $PASSPORT_SSH"
            scp "$PASSPORT_SSH:/accounts/1000/shared/misc/berrycore/bin/$name" "$BIN_SRC/" 2>/dev/null || \
                scp "$PASSPORT_SSH:/accounts/1000/shared/misc/bin/$name" "$BIN_SRC/" 2>/dev/null || \
                echo "  warning: could not fetch $name"
        fi
    done < "$MANIFEST"
fi

# libgcc for 7za/unrar if present
if [ -f "$BIN_SRC/libgcc_s.so.1" ]; then
    HAS_LIBGCC=1
else
    HAS_LIBGCC=0
fi

: > "$GENERATED"
_built=0
_skipped=0

while IFS='|' read -r name category version size desc replaces; do
    [ -z "$name" ] && continue
    echo "$name" | grep -q '^#' && continue

    bin="$BIN_SRC/$name"
    if [ ! -f "$bin" ]; then
        echo "SKIP (no binary): $name"
        _skipped=$((_skipped + 1))
        continue
    fi

    zipname="util-${name}-${version}.zip"
    # Sanitize zip name for dots in binary names (mkfs.fat -> mkfs.fat)
    zipname=$(echo "$zipname" | sed 's/\.\././g')

    pkg_root="$SCRIPT_DIR/.pkg-$name"
    rm -rf "$pkg_root"
    mkdir -p "$pkg_root/bin" "$pkg_root/share/doc/$name"

    cp "$bin" "$pkg_root/bin/"
    chmod +x "$pkg_root/bin/$name"

    # 7z symlink
    if [ "$name" = "7za" ] && [ ! -f "$pkg_root/bin/7z" ]; then
        ln -sf 7za "$pkg_root/bin/7z"
    fi

    # Bundle libgcc with 7za/unrar
    if [ "$HAS_LIBGCC" = 1 ] && { [ "$name" = "7za" ] || [ "$name" = "unrar" ]; }; then
        cp "$BIN_SRC/libgcc_s.so.1" "$pkg_root/bin/" 2>/dev/null || true
    fi

    cat > "$pkg_root/share/doc/$name/HELP.txt" <<EOF
$name — $desc

Install:  qpkg install $name
Binary:   /accounts/1000/shared/misc/bin/$name
Version:  $version (XPS QNX8 build)

Category: $category
Replaces: $replaces
EOF

    outzip="$REPO_ROOT/ports/$zipname"
    cd "$pkg_root"
    zip -r -q "$outzip" bin share
    cd - >/dev/null
    rm -rf "$pkg_root"

    _size=$(ls -lh "$outzip" | awk '{print $5}')
    echo "${name}|${category}|${version}|${_size}|${desc}|${zipname}|${replaces}" >> "$GENERATED"
    echo "OK $zipname"
    _built=$((_built + 1))
done < "$MANIFEST"

echo ""
echo "=== Done: $_built built, $_skipped skipped ==="
echo "Generated rows: $GENERATED"
