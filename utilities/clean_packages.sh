#!/bin/bash
# Clean macOS metadata from BerryCore packages

echo "Cleaning BerryCore packages from macOS metadata..."
echo "==========================================================="
echo ""

packages_dir="/Users/mp/Documents/GitHub/BerryCore/berrycore/packages"
temp_dir="/tmp/berrycore_clean_$$"
cleaned=0
skipped=0
total_removed=0

# Create temp directory
mkdir -p "$temp_dir"

cd "$packages_dir"

# Process each package
for pkg in *.zip; do
    if [ ! -f "$pkg" ]; then
        continue
    fi
    
    pkg_name="${pkg%.zip}"
    
    # Check if package has issues
    has_issues=0
    if unzip -l "$pkg" 2>/dev/null | grep -qE "__MACOSX/|\.DS_Store|/\._|\.localized"; then
        has_issues=1
    fi
    
    if [ $has_issues -eq 1 ]; then
        echo "🧹 Cleaning: $pkg"
        
        # Create temp extraction directory
        extract_dir="$temp_dir/$pkg_name"
        mkdir -p "$extract_dir"
        
        # Extract package
        unzip -q "$pkg" -d "$extract_dir" 2>/dev/null
        
        # Count what we're removing
        macosx_dirs=$(find "$extract_dir" -name "__MACOSX" -type d 2>/dev/null | wc -l | tr -d ' ')
        ds_files=$(find "$extract_dir" -name ".DS_Store" -type f 2>/dev/null | wc -l | tr -d ' ')
        rf_files=$(find "$extract_dir" -name "._*" -type f 2>/dev/null | wc -l | tr -d ' ')
        loc_files=$(find "$extract_dir" -name ".localized" -type f 2>/dev/null | wc -l | tr -d ' ')
        
        removed_count=$((macosx_dirs + ds_files + rf_files + loc_files))
        total_removed=$((total_removed + removed_count))
        
        # Remove macOS junk
        find "$extract_dir" -name "__MACOSX" -type d -exec rm -rf {} + 2>/dev/null
        find "$extract_dir" -name ".DS_Store" -type f -delete 2>/dev/null
        find "$extract_dir" -name "._*" -type f -delete 2>/dev/null
        find "$extract_dir" -name ".localized" -type f -delete 2>/dev/null
        
        # Show what was removed
        if [ $removed_count -gt 0 ]; then
            echo "   Removed: __MACOSX($macosx_dirs) .DS_Store($ds_files) ._*($rf_files) .localized($loc_files)"
        fi
        
        # Backup original
        mv "$pkg" "$pkg.bak"
        
        # Repackage
        cd "$extract_dir"
        zip -r "$packages_dir/$pkg" . -q
        cd "$packages_dir"
        
        # Compare sizes
        old_size=$(du -h "$pkg.bak" | cut -f1)
        new_size=$(du -h "$pkg" | cut -f1)
        echo "   Size: $old_size → $new_size"
        echo "   ✅ Cleaned and repackaged"
        
        # Clean up extraction directory
        rm -rf "$extract_dir"
        
        cleaned=$((cleaned + 1))
    else
        echo "✅ $pkg (already clean)"
        skipped=$((skipped + 1))
    fi
done

# Clean up temp directory
rm -rf "$temp_dir"

echo ""
echo "==========================================================="
echo "Cleaning Complete"
echo "==========================================================="
echo "Cleaned packages: $cleaned"
echo "Already clean: $skipped"
echo "Total junk files removed: $total_removed"
echo ""
echo "Original packages backed up as: *.zip.bak"
echo ""
echo "To verify packages are good:"
echo "  ./scan_packages.sh"
echo ""
echo "To remove backups:"
echo "  rm berrycore/packages/*.zip.bak"

