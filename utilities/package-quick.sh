#!/bin/bash
# Quick packaging script - minimal output

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT/berrycore"

# Backup old
[ -f "$PROJECT_ROOT/berrycore.zip" ] && mv "$PROJECT_ROOT/berrycore.zip" "$PROJECT_ROOT/berrycore.zip.old"

# Create zip
zip -r "$PROJECT_ROOT/berrycore.zip" . \
    -x "*.DS_Store" \
    -x "__MACOSX/*" \
    -x "temp/*" \
    -x "*.bak" \
    -q

if [ $? -eq 0 ]; then
    rm -f "$PROJECT_ROOT/berrycore.zip.old"
    echo "✅ berrycore.zip created ($(ls -lh "$PROJECT_ROOT/berrycore.zip" | awk '{print $5}'))"
else
    [ -f "$PROJECT_ROOT/berrycore.zip.old" ] && mv "$PROJECT_ROOT/berrycore.zip.old" "$PROJECT_ROOT/berrycore.zip"
    echo "❌ Failed"
    exit 1
fi

