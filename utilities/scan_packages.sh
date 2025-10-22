#!/bin/bash
# Scan BerryCore packages for macOS metadata junk

echo "Scanning BerryCore packages for macOS metadata..."
echo "==========================================================="
echo ""

packages_dir="/Users/mp/Documents/GitHub/BerryCore/berrycore/packages"
found_issues=0
clean_packages=0

# Check if packages directory exists
if [ ! -d "$packages_dir" ]; then
    echo "Error: Packages directory not found: $packages_dir"
    exit 1
fi

cd "$packages_dir"

# Scan each package
for pkg in *.zip; do
    if [ ! -f "$pkg" ]; then
        continue
    fi
    
    # Check for macOS junk in the package
    issues=""
    macosx_count=0
    ds_store_count=0
    resource_fork_count=0
    localized_count=0
    
    # Check for __MACOSX directory
    macosx_count=$(unzip -l "$pkg" 2>/dev/null | grep -c "__MACOSX/" || echo 0)
    if [ "$macosx_count" -gt 0 ]; then
        issues="${issues}__MACOSX/($macosx_count) "
    fi
    
    # Check for .DS_Store files
    ds_store_count=$(unzip -l "$pkg" 2>/dev/null | grep -c "\.DS_Store" || echo 0)
    if [ "$ds_store_count" -gt 0 ]; then
        issues="${issues}.DS_Store($ds_store_count) "
    fi
    
    # Check for ._* resource fork files
    resource_fork_count=$(unzip -l "$pkg" 2>/dev/null | grep -c "/\._" || echo 0)
    if [ "$resource_fork_count" -gt 0 ]; then
        issues="${issues}._*($resource_fork_count) "
    fi
    
    # Check for .localized files
    localized_count=$(unzip -l "$pkg" 2>/dev/null | grep -c "\.localized" || echo 0)
    if [ "$localized_count" -gt 0 ]; then
        issues="${issues}.localized($localized_count) "
    fi
    
    # Report findings
    if [ -n "$issues" ]; then
        echo "❌ $pkg"
        echo "   Contains: $issues"
        found_issues=$((found_issues + 1))
    else
        echo "✅ $pkg"
        clean_packages=$((clean_packages + 1))
    fi
done

echo ""
echo "==========================================================="
echo "Scan Complete"
echo "==========================================================="
echo "Clean packages: $clean_packages"
echo "Packages with issues: $found_issues"
echo ""

if [ $found_issues -gt 0 ]; then
    echo "Run './clean_packages.sh' to clean all packages"
fi

