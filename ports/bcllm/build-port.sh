#!/bin/sh
# Build ai-bcllm-1.2.1.zip from bcllm-passport-1.2.1.tar.gz
# Outputs:
#   berrycore/packages/ai-bcllm-1.2.1.zip  (core package, bundled in berrycore.zip)
#   ports/ai-bcllm-1.2.1.zip               (qpkg port — category ai → ai-bcllm-1.2.1.zip)
# Usage: ./build-port.sh [path-to-bcllm-passport-1.2.1.tar.gz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/bcllm-passport-1.2.1.tar.gz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/ai-bcllm-1.2.1.zip"
PORT_ZIP="$REPO_ROOT/ports/ai-bcllm-1.2.1.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$STAGING/bcllm"

echo "Building bcllm 1.2.1 (ai-bcllm-1.2.1.zip)..."
echo "  Input:      $INPUT_TGZ"
echo "  Core zip:   $CORE_ZIP"
echo "  Port zip:   $PORT_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -f "$PKG_ROOT/bin/llama-completion" ]; then
    echo "Error: expected bcllm/bin/llama-completion in tarball"
    exit 1
fi

cp "$SCRIPT_DIR/setup-ai.sh" "$PKG_ROOT/setup-ai.sh"
cp "$SCRIPT_DIR/bin/ai-install" "$PKG_ROOT/bin/ai-install"
cp "$SCRIPT_DIR/bin/berrycore-ai" "$PKG_ROOT/bin/berrycore-ai"
cp "$SCRIPT_DIR/share/bcllm/HELP.txt" "$PKG_ROOT/share/bcllm/" 2>/dev/null || {
    mkdir -p "$PKG_ROOT/share/bcllm"
    cp "$SCRIPT_DIR/share/bcllm/HELP.txt" "$PKG_ROOT/share/bcllm/"
}
cp "$SCRIPT_DIR/README.md" "$PKG_ROOT/share/bcllm/README-port.md" 2>/dev/null || true

mkdir -p "$PKG_ROOT/models" "$PKG_ROOT/var"
chmod +x "$PKG_ROOT/setup-ai.sh" "$PKG_ROOT/bin/"*.sh 2>/dev/null || true
chmod +x "$PKG_ROOT/bin/"*.bin 2>/dev/null || true
for _f in bcllm bcllm-krait bcllm-universal llama-bench llama-completion llama-server ai-install; do
    chmod +x "$PKG_ROOT/bin/$_f" 2>/dev/null || true
done

if [ ! -f "$SCRIPT_DIR/vendor/bin/ai" ]; then
    echo "Error: $SCRIPT_DIR/vendor/bin/ai not found"
    exit 1
fi
rm -f "$PKG_ROOT/bin/ai" "$PKG_ROOT/bin/AI" "$PKG_ROOT/bin/bcllm-ai"
cat "$SCRIPT_DIR/vendor/bin/ai" > "$PKG_ROOT/bin/bcllm-ai"
chmod +x "$PKG_ROOT/bin/bcllm-ai"
# bin/ai = wrapper script only (never symlink; never AI — macOS HFS+ merges ai/AI in zip)
cp "$SCRIPT_DIR/bin/berrycore-ai" "$PKG_ROOT/bin/ai"
chmod +x "$PKG_ROOT/bin/ai"
# Do not create bin/AI here (case-insensitive build hosts collapse ai+AI). setup-ai.sh adds AI on device.

cd "$STAGING"
if [ ! -f "bcllm/bin/bcllm-ai" ]; then
    echo "Error: bcllm/bin/bcllm-ai missing before zip"
    ls -la bcllm/bin/
    exit 1
fi
zip -r -q "$CORE_ZIP" bcllm
cp "$CORE_ZIP" "$PORT_ZIP"
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$CORE_ZIP" "$PORT_ZIP"
unzip -l "$CORE_ZIP" | head -20
