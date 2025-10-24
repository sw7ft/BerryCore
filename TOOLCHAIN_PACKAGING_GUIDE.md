# GCC 9.3.0 Toolchain Packaging Guide for BerryCore

## Mission Overview

Package the GCC 9.3.0 QNX 8 toolchain located at `~/bbndk/gcc9/bb10-gcc9/` for integration into BerryCore. This toolchain has been successfully used to compile working binaries (like git 2.50) for BlackBerry 10 devices.

## Background

- **Current BerryCore Toolchain**: GCC 4.6.3 (outdated, from 2012)
- **Target Toolchain**: GCC 9.3.0 (modern, supports C++17, better optimizations)
- **Target Platform**: arm-blackberry-qnx8eabi (QNX 8 ARM architecture)
- **Proven Compatibility**: Binaries compiled with this toolchain work on the target BB10 device

## Phase 1: Discovery & Investigation

### Step 1: Locate and Inspect the Toolchain

```bash
# Navigate to toolchain
cd ~/bbndk/gcc9/bb10-gcc9/

# Check the directory structure
echo "=== Toolchain Root Structure ==="
ls -la

# Check size (important for planning)
echo ""
echo "=== Total Size ==="
du -sh .

# Find all top-level directories
echo ""
echo "=== Top-Level Directories ==="
find . -maxdepth 1 -type d | sort
```

**Questions to Answer:**
1. What is the total size in MB/GB?
2. What directories are present? (Expected: bin, lib, libexec, include, share, arm-blackberry-qnx8eabi, etc.)
3. Is there an `env.sh` file? If so, where?

### Step 2: Examine the env.sh File

```bash
# Find and read the environment setup file
find ~/bbndk/gcc9/bb10-gcc9/ -name "env.sh" -o -name "*.env" -o -name "setenv*"

# Once found, examine it
cat ~/bbndk/gcc9/bb10-gcc9/env.sh

# Extract key environment variables
echo "=== Key Environment Variables ==="
grep -E "^export|^PATH=|^LD_LIBRARY_PATH=|CC=|CXX=|AR=|RANLIB=" ~/bbndk/gcc9/bb10-gcc9/env.sh
```

**Questions to Answer:**
1. What environment variables are set?
2. What paths are referenced?
3. Are there any absolute paths that need to be made relative?

### Step 3: Identify Compiler Binaries

```bash
cd ~/bbndk/gcc9/bb10-gcc9/

# List compiler binaries
echo "=== Compiler Binaries ==="
ls -lh bin/ | grep -E "arm-|gcc|g\+\+|ld|ar|ranlib|strip|objdump"

# Verify GCC version
echo ""
echo "=== GCC Version ==="
./bin/arm-blackberry-qnx8eabi-gcc --version

# Check for target-specific tools
echo ""
echo "=== Target Tools ==="
ls -lh arm-blackberry-qnx8eabi/bin/ 2>/dev/null || echo "No target bin directory found"
```

**Questions to Answer:**
1. What is the exact GCC version?
2. What is the full compiler prefix? (e.g., `arm-blackberry-qnx8eabi-`)
3. Are there target-specific libraries in `arm-blackberry-qnx8eabi/lib/`?

### Step 4: Check for Large Files

```bash
# Find files larger than 50MB (might need special handling)
echo "=== Large Files (>50MB) ==="
find ~/bbndk/gcc9/bb10-gcc9/ -type f -size +50M -exec ls -lh {} \;

# Count total files
echo ""
echo "=== File Count ==="
find ~/bbndk/gcc9/bb10-gcc9/ -type f | wc -l
```

**Questions to Answer:**
1. Are there any files over 100MB?
2. What is the total file count?
3. Are there unnecessary files we can exclude (docs, examples, tests)?

## Phase 2: Package Creation

### Step 1: Create Clean Workspace

```bash
# Create workspace
mkdir -p /tmp/gcc-9.3.0-berrycore
cd /tmp/gcc-9.3.0-berrycore

# Verify it's empty
ls -la
```

### Step 2: Copy Essential Directories

```bash
# Copy core directories (adjust if your structure differs)
echo "Copying toolchain directories..."

cp -r ~/bbndk/gcc9/bb10-gcc9/bin . && echo "✓ bin/"
cp -r ~/bbndk/gcc9/bb10-gcc9/lib . && echo "✓ lib/"
cp -r ~/bbndk/gcc9/bb10-gcc9/libexec . && echo "✓ libexec/"
cp -r ~/bbndk/gcc9/bb10-gcc9/include . && echo "✓ include/"
cp -r ~/bbndk/gcc9/bb10-gcc9/share . && echo "✓ share/"
cp -r ~/bbndk/gcc9/bb10-gcc9/arm-blackberry-qnx8eabi . && echo "✓ arm-blackberry-qnx8eabi/"

# Copy optional directories if they exist
cp -r ~/bbndk/gcc9/bb10-gcc9/etc . 2>/dev/null && echo "✓ etc/" || echo "⊘ etc/ (not found)"
cp -r ~/bbndk/gcc9/bb10-gcc9/sbin . 2>/dev/null && echo "✓ sbin/" || echo "⊘ sbin/ (not found)"

# Copy the environment file
cp ~/bbndk/gcc9/bb10-gcc9/env.sh . 2>/dev/null && echo "✓ env.sh" || echo "⚠ env.sh not found"
```

### Step 3: Document the Toolchain

```bash
cd /tmp/gcc-9.3.0-berrycore

cat > TOOLCHAIN_INFO.txt << 'EOF'
========================================================
  GCC 9.3.0 QNX 8 Toolchain for BerryCore Integration
========================================================

Original Location: ~/bbndk/gcc9/bb10-gcc9/
Target Platform: arm-blackberry-qnx8eabi
Packaging Date: $(date)
Packaged By: AI Agent (autonomous)

========================================================
  Directory Structure
========================================================
EOF

# Append directory tree
find . -maxdepth 2 -type d | sort >> TOOLCHAIN_INFO.txt

echo "" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
echo "  GCC Version" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
./bin/arm-blackberry-qnx8eabi-gcc --version 2>/dev/null >> TOOLCHAIN_INFO.txt || echo "GCC not found in bin/" >> TOOLCHAIN_INFO.txt

echo "" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
echo "  Key Compiler Binaries" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
ls -lh bin/ | grep -E "gcc|g\+\+|ar|ld|ranlib" >> TOOLCHAIN_INFO.txt

echo "" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
echo "  Original Environment Variables" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
if [ -f env.sh ]; then
    grep -E "^export|^PATH=|^LD_LIBRARY_PATH=" env.sh >> TOOLCHAIN_INFO.txt
else
    grep -E "^export|^PATH=|^LD_LIBRARY_PATH=" ~/bbndk/gcc9/bb10-gcc9/env.sh >> TOOLCHAIN_INFO.txt 2>/dev/null || echo "env.sh not found" >> TOOLCHAIN_INFO.txt
fi

echo "" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
echo "  Package Statistics" >> TOOLCHAIN_INFO.txt
echo "========================================================" >> TOOLCHAIN_INFO.txt
echo "Total size: $(du -sh . | cut -f1)" >> TOOLCHAIN_INFO.txt
echo "File count: $(find . -type f | wc -l)" >> TOOLCHAIN_INFO.txt
echo "Directory count: $(find . -type d | wc -l)" >> TOOLCHAIN_INFO.txt

# Display the info file
cat TOOLCHAIN_INFO.txt
```

### Step 4: Verify Package Structure

```bash
cd /tmp/gcc-9.3.0-berrycore

echo "=== Package Structure Verification ==="
echo ""
echo "Required directories:"
[ -d bin ] && echo "✓ bin/" || echo "✗ bin/ MISSING"
[ -d lib ] && echo "✓ lib/" || echo "✗ lib/ MISSING"
[ -d libexec ] && echo "✓ libexec/" || echo "✗ libexec/ MISSING"
[ -d include ] && echo "✓ include/" || echo "✗ include/ MISSING"
[ -d arm-blackberry-qnx8eabi ] && echo "✓ arm-blackberry-qnx8eabi/" || echo "✗ arm-blackberry-qnx8eabi/ MISSING"

echo ""
echo "Optional directories:"
[ -d share ] && echo "✓ share/" || echo "⊘ share/ (optional)"
[ -d etc ] && echo "✓ etc/" || echo "⊘ etc/ (optional)"

echo ""
echo "Key files:"
[ -f bin/arm-blackberry-qnx8eabi-gcc ] && echo "✓ GCC compiler" || echo "✗ GCC compiler MISSING"
[ -f bin/arm-blackberry-qnx8eabi-g++ ] && echo "✓ G++ compiler" || echo "✗ G++ compiler MISSING"
[ -f bin/arm-blackberry-qnx8eabi-ar ] && echo "✓ AR archiver" || echo "✗ AR archiver MISSING"
[ -f TOOLCHAIN_INFO.txt ] && echo "✓ TOOLCHAIN_INFO.txt" || echo "✗ TOOLCHAIN_INFO.txt MISSING"

echo ""
echo "Package size:"
du -sh .
```

### Step 5: Create ZIP Package

```bash
cd /tmp

echo "Creating ZIP package..."
echo "This may take several minutes depending on size..."

# Create the package
zip -r gcc-9.3.0-qnx8.zip gcc-9.3.0-berrycore/

echo ""
echo "=== Package Created ==="
ls -lh gcc-9.3.0-qnx8.zip

# Check if it's over GitHub's limit
SIZE_MB=$(du -m gcc-9.3.0-qnx8.zip | cut -f1)
echo ""
echo "Package size: ${SIZE_MB}MB"
if [ $SIZE_MB -gt 100 ]; then
    echo "⚠ WARNING: Package is over 100MB - will need Git LFS"
else
    echo "✓ Package is under 100MB - can be added directly to Git"
fi
```

## Phase 3: Verification

### Step 1: Test Package Integrity

```bash
cd /tmp

echo "=== Testing Package Integrity ==="
unzip -t gcc-9.3.0-qnx8.zip

# Show first and last 10 files
echo ""
echo "=== First 10 Files ==="
unzip -l gcc-9.3.0-qnx8.zip | head -15

echo ""
echo "=== Last 10 Files ==="
unzip -l gcc-9.3.0-qnx8.zip | tail -15

# Get total file count
echo ""
echo "=== Package Summary ==="
unzip -l gcc-9.3.0-qnx8.zip | tail -1
```

### Step 2: Create Checksum

```bash
cd /tmp

# Create SHA256 checksum for verification
sha256sum gcc-9.3.0-qnx8.zip > gcc-9.3.0-qnx8.zip.sha256

echo "=== Checksum Created ==="
cat gcc-9.3.0-qnx8.zip.sha256
```

### Step 3: Test Extraction

```bash
cd /tmp

# Create test extraction
mkdir -p test_extract
cd test_extract

echo "=== Testing Extraction ==="
unzip -q ../gcc-9.3.0-qnx8.zip

echo "Extracted successfully!"
echo ""
echo "Verifying GCC is present:"
if [ -f gcc-9.3.0-berrycore/bin/arm-blackberry-qnx8eabi-gcc ]; then
    echo "✓ GCC found"
    gcc-9.3.0-berrycore/bin/arm-blackberry-qnx8eabi-gcc --version
else
    echo "✗ GCC not found - package may be incomplete"
fi

# Clean up test
cd /tmp
rm -rf test_extract
```

## Phase 4: Prepare for Transfer

### Step 1: Move Package to Home Directory

```bash
# Move to convenient location
mv /tmp/gcc-9.3.0-qnx8.zip ~/
mv /tmp/gcc-9.3.0-qnx8.zip.sha256 ~/

cd ~
echo "=== Files Ready for Transfer ==="
ls -lh gcc-9.3.0-qnx8.zip*
```

### Step 2: Create Transfer Summary

```bash
cat > ~/TRANSFER_SUMMARY.txt << 'EOF'
========================================================
  GCC 9.3.0 Toolchain Package - Transfer Summary
========================================================

Files to Transfer:
1. gcc-9.3.0-qnx8.zip          - Main toolchain package
2. gcc-9.3.0-qnx8.zip.sha256   - Checksum for verification
3. TRANSFER_SUMMARY.txt        - This file

========================================================
  Package Details
========================================================
EOF

echo "Package size: $(ls -lh ~/gcc-9.3.0-qnx8.zip | awk '{print $5}')" >> ~/TRANSFER_SUMMARY.txt
echo "File count: $(unzip -l ~/gcc-9.3.0-qnx8.zip | tail -1 | awk '{print $2}')" >> ~/TRANSFER_SUMMARY.txt
echo "" >> ~/TRANSFER_SUMMARY.txt
echo "Checksum:" >> ~/TRANSFER_SUMMARY.txt
cat ~/gcc-9.3.0-qnx8.zip.sha256 >> ~/TRANSFER_SUMMARY.txt

echo "" >> ~/TRANSFER_SUMMARY.txt
echo "========================================================" >> ~/TRANSFER_SUMMARY.txt
echo "  Next Steps (on destination machine)" >> ~/TRANSFER_SUMMARY.txt
echo "========================================================" >> ~/TRANSFER_SUMMARY.txt
echo "1. Verify checksum matches" >> ~/TRANSFER_SUMMARY.txt
echo "2. Extract and inspect package structure" >> ~/TRANSFER_SUMMARY.txt
echo "3. Integrate into BerryCore packages directory" >> ~/TRANSFER_SUMMARY.txt
echo "4. Update BerryCore documentation" >> ~/TRANSFER_SUMMARY.txt
echo "5. Test compilation with new toolchain" >> ~/TRANSFER_SUMMARY.txt

cat ~/TRANSFER_SUMMARY.txt
```

## Final Checklist

Before transferring, verify you have:

- [ ] `gcc-9.3.0-qnx8.zip` - The main package
- [ ] `gcc-9.3.0-qnx8.zip.sha256` - Checksum file
- [ ] `TRANSFER_SUMMARY.txt` - Transfer summary
- [ ] Package integrity verified (unzip -t passed)
- [ ] GCC binary tested and version confirmed
- [ ] Package size documented
- [ ] All required directories present (bin, lib, libexec, include, arm-blackberry-qnx8eabi)

## Questions to Answer for Main Agent

Please provide the following information:

1. **Package Size**: __________ MB
2. **Total Files**: __________
3. **GCC Version**: __________
4. **Compiler Prefix**: __________ (e.g., arm-blackberry-qnx8eabi-)
5. **Largest Single File**: __________ (size and name)
6. **Any Issues Encountered**: __________
7. **Missing Directories**: __________ (if any)
8. **Git LFS Required**: Yes / No (if over 100MB)

## Transfer Command Examples

### Using SCP:
```bash
scp ~/gcc-9.3.0-qnx8.zip* user@destination:/path/to/BerryCore/temp/
```

### Using rsync:
```bash
rsync -avP ~/gcc-9.3.0-qnx8.zip* user@destination:/path/to/BerryCore/temp/
```

---

**End of Guide**

Once transfer is complete, the main agent will:
- Verify checksum
- Inspect package structure
- Integrate into BerryCore
- Update qconf-override.mk
- Document the upgrade

