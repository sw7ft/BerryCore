#!/bin/bash
# BerryCore Packaging Script
# Creates berrycore.zip from the berrycore directory

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BERRYCORE_DIR="$PROJECT_ROOT/berrycore"
OUTPUT_ZIP="$PROJECT_ROOT/berrycore.zip"

echo "==========================================================="
echo "     BerryCore Packaging Script"
echo "==========================================================="
echo ""

# Check if berrycore directory exists
if [ ! -d "$BERRYCORE_DIR" ]; then
    echo "Error: berrycore directory not found at: $BERRYCORE_DIR"
    exit 1
fi

# Backup old zip if it exists
if [ -f "$OUTPUT_ZIP" ]; then
    echo "Backing up existing berrycore.zip..."
    mv "$OUTPUT_ZIP" "$OUTPUT_ZIP.old"
fi

# Navigate to berrycore directory
cd "$BERRYCORE_DIR"

echo "Creating berrycore.zip..."
echo "Source: $BERRYCORE_DIR"
echo "Output: $OUTPUT_ZIP"
echo ""

# Create the zip, excluding junk files
zip -r "$OUTPUT_ZIP" . \
    -x "*.DS_Store" \
    -x "__MACOSX/*" \
    -x "temp/*" \
    -x "*.bak" \
    -x ".git/*" \
    -x ".gitignore" \
    -q

if [ $? -eq 0 ]; then
    echo "✅ Package created successfully!"
    echo ""
    
    # Show package info
    echo "Package details:"
    echo "-----------------------------------------------------------"
    ls -lh "$OUTPUT_ZIP" | awk '{print "Size: " $5}'
    echo ""
    
    # Count files
    file_count=$(unzip -l "$OUTPUT_ZIP" | tail -1 | awk '{print $2}')
    echo "Files: $file_count"
    echo ""
    
    # Show structure
    echo "Structure preview:"
    unzip -l "$OUTPUT_ZIP" | head -20
    echo "..."
    echo ""
    
    # Verify key files
    echo "Verifying key files..."
    missing=0
    
    for file in env.sh pbpkgadd sample_profile CATALOG qconf-override.mk; do
        if unzip -l "$OUTPUT_ZIP" | grep -q "$file"; then
            echo "  ✓ $file"
        else
            echo "  ✗ $file (MISSING!)"
            missing=1
        fi
    done
    
    # Check packages directory
    pkg_count=$(unzip -l "$OUTPUT_ZIP" | grep "packages/.*\.zip" | wc -l | tr -d ' ')
    echo "  ✓ packages/ ($pkg_count packages)"
    
    # Check bin directory
    bin_count=$(unzip -l "$OUTPUT_ZIP" | grep "^.*bin/" | wc -l | tr -d ' ')
    echo "  ✓ bin/ ($bin_count items)"
    
    echo ""
    
    if [ $missing -eq 0 ]; then
        echo "==========================================================="
        echo "✅ Package ready for distribution!"
        echo "==========================================================="
        echo ""
        echo "Location: $OUTPUT_ZIP"
        echo ""
        echo "Next steps:"
        echo "  1. Test installation on device"
        echo "  2. Upload to GitHub releases"
        echo "  3. Update CHANGELOG.md if needed"
        echo ""
    else
        echo "⚠️  Warning: Some key files are missing!"
        echo "Review the package before distribution."
        echo ""
    fi
    
    # Clean up old backup if successful
    if [ -f "$OUTPUT_ZIP.old" ]; then
        rm "$OUTPUT_ZIP.old"
    fi
else
    echo "❌ Error: Failed to create package"
    
    # Restore old backup if it exists
    if [ -f "$OUTPUT_ZIP.old" ]; then
        mv "$OUTPUT_ZIP.old" "$OUTPUT_ZIP"
        echo "Restored previous berrycore.zip"
    fi
    exit 1
fi

