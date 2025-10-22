# BerryCore Utilities

Development and maintenance utilities for BerryCore.

## Packaging

### package.sh
Creates berrycore.zip with detailed verification and reporting.

**Usage:**
```bash
./utilities/package.sh
```

**Features:**
- Excludes junk files (.DS_Store, __MACOSX, temp/, .bak)
- Backs up existing zip
- Verifies key files
- Shows structure and statistics
- Detailed output

### package-quick.sh
Quick packaging with minimal output.

**Usage:**
```bash
./utilities/package-quick.sh
```

**Use when:**
- Making quick test builds
- You just need the zip fast
- Don't need verification

## Package Maintenance

### scan_packages.sh
Scans all packages for macOS metadata junk (\_\_MACOSX, .DS_Store, etc.)

**Usage:**
```bash
./utilities/scan_packages.sh
```

**Output:**
- Lists all packages with issues
- Shows counts of junk files
- Reports clean vs. dirty packages

### clean_packages.sh  
Removes macOS metadata from packages and repackages them cleanly.

**Usage:**
```bash
./utilities/clean_packages.sh
```

**Features:**
- Backs up originals as `*.zip.bak`
- Shows before/after sizes
- Detailed removal statistics
- Preserves package functionality

**After cleaning:**
```bash
# Verify packages are clean
./utilities/scan_packages.sh

# Remove backups when satisfied
rm berrycore/packages/*.zip.bak
```

## Maintenance Workflow

1. **Before Release:**
   ```bash
   # Scan for issues
   ./utilities/scan_packages.sh
   
   # Clean if needed
   ./utilities/clean_packages.sh
   
   # Verify
   ./utilities/scan_packages.sh
   ```

2. **After Adding New Packages:**
   - Always scan new packages before committing
   - Clean any macOS junk
   - Test installation on device

## Notes

- Scripts use `/tmp/` for temporary extraction
- Originals are backed up (*.zip.bak)
- Safe to run multiple times
- POSIX-compliant bash scripts

