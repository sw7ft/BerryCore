#!/bin/sh
# Build BerryCore v0.82 release artifacts
# Usage: ./release/build-berrycore-0.82.sh
#
# Outputs in release/berrycore-0.82/:
#   berrycore.zip, install.sh, berrycore-helper.apk
#   bcllm-passport-1.2.1.tar.gz, ports/ai-bcllm-1.2.1.zip, ports/INDEX
#   RELEASE_NOTES.md, SHA256SUMS

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
RELEASE_DIR="$SCRIPT_DIR/berrycore-0.82"
HELPER_APK_IN="${HELPER_APK_IN:-$REPO_ROOT/berrycore-helper.apk}"
if [ ! -f "$HELPER_APK_IN" ] && [ -f "$HOME/Desktop/berrycore-helper.apk" ]; then
    HELPER_APK_IN="$HOME/Desktop/berrycore-helper.apk"
fi

echo "==========================================================="
echo "     BerryCore v0.82 Release Build"
echo "==========================================================="
echo ""

# 1. Build ai-bcllm core + port zip
echo ">>> Building ai-bcllm-1.2.1.zip..."
"$REPO_ROOT/ports/bcllm/build-port.sh"

# 2. Build berrycore.zip
echo ""
echo ">>> Building berrycore.zip..."
"$REPO_ROOT/utilities/package.sh"

# 3. Rebuild helper APK assets (replace bundled zip + install.sh)
mkdir -p "$RELEASE_DIR"
HELPER_APK_OUT="$RELEASE_DIR/berrycore-helper.apk"
if [ -f "$HELPER_APK_IN" ]; then
    echo ""
    echo ">>> Rebuilding berrycore-helper.apk assets..."
    APK_WORK="$SCRIPT_DIR/.apk-work"
    rm -rf "$APK_WORK"
    mkdir -p "$APK_WORK"
    unzip -q "$HELPER_APK_IN" -d "$APK_WORK"
    cp "$REPO_ROOT/berrycore.zip" "$APK_WORK/assets/berrycore.zip"
    cp "$REPO_ROOT/install.sh" "$APK_WORK/assets/install.sh"
    echo "0.82" > "$APK_WORK/assets/VERSION"
    rm -rf "$APK_WORK/META-INF"
    (cd "$APK_WORK" && zip -qr -0 "$HELPER_APK_OUT" .)
    echo "Helper APK written (unsigned — re-sign before sideload if required): $HELPER_APK_OUT"
    cp "$HELPER_APK_OUT" "$REPO_ROOT/berrycore-helper.apk" 2>/dev/null || true
else
    echo ""
    echo ">>> Skipping helper APK (set HELPER_APK_IN=path/to/berrycore-helper.apk)"
fi

# 4. Assemble release folder
echo ""
echo ">>> Assembling $RELEASE_DIR..."
mkdir -p "$RELEASE_DIR/ports"
cp "$REPO_ROOT/berrycore.zip" "$RELEASE_DIR/"
cp "$REPO_ROOT/install.sh" "$RELEASE_DIR/"
cp "$REPO_ROOT/bcllm-passport-1.2.1.tar.gz" "$RELEASE_DIR/" 2>/dev/null || true
cp "$REPO_ROOT/ports/ai-bcllm-1.2.1.zip" "$RELEASE_DIR/ports/"
cp "$REPO_ROOT/ports/INDEX" "$RELEASE_DIR/ports/"
cp "$SCRIPT_DIR/RELEASE_NOTES_v0.82.md" "$RELEASE_DIR/RELEASE_NOTES.md" 2>/dev/null || \
    cp "$REPO_ROOT/GITHUB_RELEASE_v0.82_BODY.md" "$RELEASE_DIR/RELEASE_NOTES.md" 2>/dev/null || true

# 5. SHA256SUMS
echo ""
echo ">>> SHA256SUMS..."
(
    cd "$RELEASE_DIR"
    shasum -a 256 berrycore.zip install.sh 2>/dev/null
    [ -f berrycore-helper.apk ] && shasum -a 256 berrycore-helper.apk
    [ -f bcllm-passport-1.2.1.tar.gz ] && shasum -a 256 bcllm-passport-1.2.1.tar.gz
    [ -f ports/ai-bcllm-1.2.1.zip ] && shasum -a 256 ports/ai-bcllm-1.2.1.zip
) > "$RELEASE_DIR/SHA256SUMS"

echo ""
echo "==========================================================="
echo "     Release folder ready: $RELEASE_DIR"
echo "==========================================================="
ls -lh "$RELEASE_DIR"
echo ""
cat "$RELEASE_DIR/SHA256SUMS"
