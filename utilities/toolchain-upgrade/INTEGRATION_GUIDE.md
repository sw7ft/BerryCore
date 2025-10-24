# GCC 9.3.0 Toolchain Integration Guide

## Overview

This guide explains how to integrate and use the GCC 9.3.0 QNX 8 toolchain with BerryCore for compiling modern packages with improved performance and C++17 support.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Installation](#installation)
3. [Environment Setup](#environment-setup)
4. [Building Packages](#building-packages)
5. [Troubleshooting](#troubleshooting)
6. [Migration Strategy](#migration-strategy)

---

## Prerequisites

### On Your Development Machine (Linux)

- **Operating System**: Linux (Ubuntu 20.04+ recommended)
- **Disk Space**: ~1 GB free space
- **Existing Tools**: tar, make, bash

### On Your BlackBerry 10 Device

- **BerryCore**: v0.6 or later installed
- **Disk Space**: Packages you compile will need space
- **SSH Access**: For transferring compiled binaries

---

## Installation

### Step 1: Extract the Toolchain

On your Linux development machine:

```bash
# Navigate to your working directory
cd ~/development

# Extract the toolchain
tar -xzf /path/to/gcc-9.3.0-qnx8.tar.gz

# This creates: gcc-9.3.0-berrycore/
```

### Step 2: Set Up Environment Variables

Create or edit `~/qnx-env.sh`:

```bash
#!/bin/bash

# GCC 9.3.0 Toolchain for BerryCore
export TOOLCHAIN_ROOT="$HOME/development/gcc-9.3.0-berrycore"

# QNX Configuration
export QNX_TARGET="$TOOLCHAIN_ROOT"
export QNX_HOST="$TOOLCHAIN_ROOT"
export QNX_ABI="arm-blackberry-qnx8eabi"

# Compiler Paths
export PATH="$TOOLCHAIN_ROOT/bin:$PATH"
export LD_LIBRARY_PATH="$TOOLCHAIN_ROOT/lib:$LD_LIBRARY_PATH"

# Build Configuration
export CC="arm-blackberry-qnx8eabi-gcc"
export CXX="arm-blackberry-qnx8eabi-g++"
export AR="arm-blackberry-qnx8eabi-ar"
export RANLIB="arm-blackberry-qnx8eabi-ranlib"
export LD="arm-blackberry-qnx8eabi-ld"
export STRIP="arm-blackberry-qnx8eabi-strip"
export OBJDUMP="arm-blackberry-qnx8eabi-objdump"
export OBJCOPY="arm-blackberry-qnx8eabi-objcopy"
export AS="arm-blackberry-qnx8eabi-as"

# Compilation Flags
export CFLAGS="-march=armv7-a -mfpu=neon -O2"
export CXXFLAGS="-march=armv7-a -mfpu=neon -O2 -std=c++17"
export LDFLAGS="-L$TOOLCHAIN_ROOT/lib"

# pkg-config
export PKG_CONFIG_PATH="$TOOLCHAIN_ROOT/lib/pkgconfig:$PKG_CONFIG_PATH"

echo "✓ GCC 9.3.0 Toolchain environment loaded"
echo "  Compiler: $(arm-blackberry-qnx8eabi-gcc --version | head -1)"
echo "  Target: $QNX_ABI"
```

### Step 3: Activate the Environment

```bash
# Source the environment
source ~/qnx-env.sh

# Verify it works
arm-blackberry-qnx8eabi-gcc --version
# Should output: arm-blackberry-qnx8eabi-gcc (GCC) 9.3.0
```

---

## Environment Setup

### Permanent Setup

Add to your `~/.bashrc` or `~/.bash_profile`:

```bash
# BerryCore GCC 9.3.0 Toolchain
if [ -f ~/qnx-env.sh ]; then
    source ~/qnx-env.sh
fi
```

### Per-Session Setup

For one-time use:

```bash
source ~/qnx-env.sh
```

### Verification Checklist

```bash
# Check compiler
which arm-blackberry-qnx8eabi-gcc
# Should output: /home/user/development/gcc-9.3.0-berrycore/bin/arm-blackberry-qnx8eabi-gcc

# Check version
arm-blackberry-qnx8eabi-gcc --version

# Check target
arm-blackberry-qnx8eabi-gcc -dumpmachine
# Should output: arm-unknown-nto-qnx8.0.0eabi

# Test compilation
echo 'int main() { return 0; }' > test.c
arm-blackberry-qnx8eabi-gcc test.c -o test
file test
rm test test.c
```

---

## Building Packages

### Basic Build Process

#### Step 1: Download Source

```bash
# Example: Building nano 5.9
wget https://www.nano-editor.org/dist/v5/nano-5.9.tar.gz
tar -xzf nano-5.9.tar.gz
cd nano-5.9
```

#### Step 2: Configure

```bash
# Source the toolchain environment
source ~/qnx-env.sh

# Configure with cross-compilation settings
./configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=/accounts/1000/shared/misc/berrycore \
    --disable-nls \
    --enable-tiny
```

**Common Configure Options:**
- `--host=arm-blackberry-qnx8eabi` - Cross-compile target
- `--prefix=...` - Installation path on device
- `--disable-nls` - Disable translations (smaller binary)
- `--enable-static` - Static linking (if needed)

#### Step 3: Build

```bash
# Compile with verbose output
make V=1

# Check for errors
echo $?  # Should be 0
```

#### Step 4: Package for BerryCore

```bash
# Install to staging directory
make DESTDIR=$PWD/deploy install

# Create BerryCore package structure
cd deploy/accounts/1000/shared/misc/berrycore

# Verify structure
ls -la
# Should have: bin/, lib/, share/, etc.

# Create package
cd ..
zip -r nano-5.9.zip berrycore/

# Move to packages directory
# This will go into berrycore/packages/
```

---

## Building Examples

### Example 1: Simple Binary (Hello World)

```bash
# Create source
cat > hello.c << 'EOF'
#include <stdio.h>
int main() {
    printf("Hello from GCC 9.3.0!\n");
    return 0;
}
EOF

# Compile
source ~/qnx-env.sh
arm-blackberry-qnx8eabi-gcc hello.c -o hello

# Check binary
file hello
# Output: hello: ELF 32-bit LSB executable, ARM, ...

# Strip to reduce size
arm-blackberry-qnx8eabi-strip hello

# Transfer to device
scp hello root@192.168.1.108:/tmp/
```

### Example 2: Autotools Project (e.g., wget)

```bash
source ~/qnx-env.sh

./configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=/accounts/1000/shared/misc/berrycore \
    --with-ssl=openssl \
    --with-openssl=$TOOLCHAIN_ROOT \
    --disable-nls

make -j$(nproc)
make DESTDIR=$PWD/deploy install
```

### Example 3: CMake Project

```bash
source ~/qnx-env.sh

# Create toolchain file
cat > qnx-toolchain.cmake << 'EOF'
set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-blackberry-qnx8eabi-gcc)
set(CMAKE_CXX_COMPILER arm-blackberry-qnx8eabi-g++)
set(CMAKE_AR arm-blackberry-qnx8eabi-ar)
set(CMAKE_RANLIB arm-blackberry-qnx8eabi-ranlib)

set(CMAKE_FIND_ROOT_PATH $ENV{TOOLCHAIN_ROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
EOF

# Configure with CMake
mkdir build && cd build
cmake \
    -DCMAKE_TOOLCHAIN_FILE=../qnx-toolchain.cmake \
    -DCMAKE_INSTALL_PREFIX=/accounts/1000/shared/misc/berrycore \
    ..

make -j$(nproc)
make DESTDIR=$PWD/deploy install
```

---

## Troubleshooting

### Issue: "cannot find -lc" or "cannot find crt0.o"

**Cause**: Toolchain paths not correctly set

**Solution**:
```bash
# Verify QNX_TARGET is set
echo $QNX_TARGET

# Check for libraries
ls $QNX_TARGET/arm-blackberry-qnx8eabi/lib/

# Re-source environment
source ~/qnx-env.sh
```

### Issue: "undefined reference" errors

**Cause**: Missing libraries or incorrect link order

**Solution**:
```bash
# Add libraries explicitly
arm-blackberry-qnx8eabi-gcc myfile.c -o myapp -lm -lpthread

# Check what's being linked
arm-blackberry-qnx8eabi-gcc -v myfile.c -o myapp
```

### Issue: Binary crashes on device

**Possible Causes**:
1. **Library incompatibility**: Using wrong OpenSSL version
2. **ABI mismatch**: Wrong compiler flags
3. **Missing libraries**: Check with `ldd`

**Solution**:
```bash
# On device, check dependencies
ldd /path/to/binary

# Check BerryCore library paths
echo $LD_LIBRARY_PATH

# Verify libraries are present
ls -la $NATIVE_TOOLS/lib/libssl*
```

### Issue: configure script fails

**Common Problems**:

1. **"checking for arm-blackberry-qnx8eabi-gcc... no"**
   ```bash
   # Ensure PATH includes toolchain
   export PATH="$TOOLCHAIN_ROOT/bin:$PATH"
   which arm-blackberry-qnx8eabi-gcc
   ```

2. **"C compiler cannot create executables"**
   ```bash
   # Check config.log for actual error
   tail -50 config.log
   
   # Verify basic compilation works
   echo 'int main() { return 0; }' > test.c
   arm-blackberry-qnx8eabi-gcc test.c -o test
   ```

---

## Migration Strategy

### Option 1: Gradual Migration (Recommended)

**Approach**: Keep both toolchains, migrate packages one at a time

**Benefits**:
- Lower risk
- Test each package individually
- Fallback to old toolchain if needed

**Process**:
1. Start with simple packages (nano, curl, wget)
2. Test thoroughly on device
3. Move to complex packages (git, ffmpeg)
4. Eventually retire GCC 4.6.3

### Option 2: Complete Migration

**Approach**: Recompile all packages with GCC 9.3.0

**Benefits**:
- Consistent toolchain
- Better optimization across all packages
- Modern C++ features everywhere

**Process**:
1. List all packages that need recompilation
2. Create build scripts for each
3. Build and test systematically
4. Replace old GCC package

### Recommended Package Priority

**Phase 1 - Critical Tools** (Test First):
1. ✓ nano (already working)
2. ✓ git (already working - version 2.50)
3. curl
4. wget
5. openssh

**Phase 2 - Core Utilities**:
1. coreutils
2. findutils
3. grep
4. sed

**Phase 3 - Development Tools**:
1. make
2. autoconf
3. automake
4. pkg-config

**Phase 4 - Complex Packages**:
1. vim
2. tmux
3. ffmpeg
4. OpenSSL (if upgrading binaries)

---

## Build Optimization Tips

### Compiler Flags for Performance

```bash
# Maximum optimization (may be unstable)
export CFLAGS="-march=armv7-a -mfpu=neon -O3 -flto"

# Balanced (recommended)
export CFLAGS="-march=armv7-a -mfpu=neon -O2"

# Debug build
export CFLAGS="-march=armv7-a -mfpu=neon -O0 -g"

# Size optimization
export CFLAGS="-march=armv7-a -mfpu=neon -Os"
```

### Reducing Binary Size

```bash
# Strip symbols after compilation
arm-blackberry-qnx8eabi-strip --strip-unneeded binary

# Use size optimization
CFLAGS="-Os" ./configure ...

# Enable LTO (Link Time Optimization)
CFLAGS="-O2 -flto" LDFLAGS="-flto" ./configure ...
```

### Parallel Compilation

```bash
# Use all CPU cores
make -j$(nproc)

# Limit to 4 cores
make -j4
```

---

## Testing Compiled Binaries

### On Development Machine

```bash
# Check binary type
file mybinary

# Check dependencies
arm-blackberry-qnx8eabi-readelf -d mybinary | grep NEEDED

# Check size
ls -lh mybinary
du -h mybinary
```

### On BlackBerry 10 Device

```bash
# Transfer binary
scp mybinary root@192.168.1.108:/tmp/

# SSH to device
ssh root@192.168.1.108

# Test execution
cd /tmp
chmod +x mybinary
./mybinary --version

# Check runtime dependencies
ldd mybinary

# Check which libraries are loaded
LD_DEBUG=libs ./mybinary
```

---

## Integration with BerryCore Packages

### Creating a BerryCore Package

After building, create a package that follows BerryCore conventions:

```bash
# Navigate to DESTDIR
cd $PWD/deploy/accounts/1000/shared/misc/berrycore

# Verify structure
tree -L 2
# Should show:
# .
# ├── bin/
# ├── lib/
# ├── share/
# └── include/

# Clean up unnecessary files
rm -rf share/doc share/man  # If needed
find . -name "*.la" -delete  # Remove libtool files

# Create package
cd ..
zip -r mypackage-1.0.zip berrycore/

# Test package integrity
unzip -t mypackage-1.0.zip

# Add to BerryCore
mv mypackage-1.0.zip /path/to/BerryCore/berrycore/packages/
```

### Package Naming Convention

Follow BerryCore's naming: `packagename-version.zip`

Examples:
- `nano-5.9.zip`
- `git-2.50.zip`
- `curl-8.0.1.zip`

---

## Advanced Topics

### Cross-Compiling with Dependencies

When a package depends on other libraries:

```bash
# Example: Building curl with OpenSSL

# 1. Ensure OpenSSL is in the toolchain
export PKG_CONFIG_PATH="$TOOLCHAIN_ROOT/lib/pkgconfig"

# 2. Configure with dependency paths
./configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=/accounts/1000/shared/misc/berrycore \
    --with-ssl=$TOOLCHAIN_ROOT \
    PKG_CONFIG="pkg-config"

# 3. Verify dependencies were found
grep "SSL support" config.log
```

### Creating Reusable Build Scripts

```bash
#!/bin/bash
# build-for-berrycore.sh

set -e  # Exit on error

# Load toolchain
source ~/qnx-env.sh

# Configuration
PACKAGE_NAME="$1"
PACKAGE_VERSION="$2"
SOURCE_DIR="$PWD"
BUILD_DIR="$SOURCE_DIR/build-qnx"
DEPLOY_DIR="$SOURCE_DIR/deploy"

# Clean previous builds
rm -rf "$BUILD_DIR" "$DEPLOY_DIR"
mkdir -p "$BUILD_DIR" "$DEPLOY_DIR"

# Configure
cd "$BUILD_DIR"
../configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=/accounts/1000/shared/misc/berrycore \
    --disable-nls

# Build
make -j$(nproc)

# Install to staging
make DESTDIR="$DEPLOY_DIR" install

# Package
cd "$DEPLOY_DIR/accounts/1000/shared/misc"
zip -r "${PACKAGE_NAME}-${PACKAGE_VERSION}.zip" berrycore/

echo "✓ Package created: ${PACKAGE_NAME}-${PACKAGE_VERSION}.zip"
```

---

## Reference

### Toolchain Specifications

- **GCC Version**: 9.3.0
- **Target**: arm-blackberry-qnx8eabi
- **Architecture**: ARMv7-A
- **FPU**: NEON
- **C++ Standard**: Up to C++17
- **Total Size**: 676 MB (uncompressed)
- **Compressed Size**: 316 MB

### Compiler Prefix

All tools use the prefix: `arm-blackberry-qnx8eabi-`

Examples:
- `arm-blackberry-qnx8eabi-gcc`
- `arm-blackberry-qnx8eabi-g++`
- `arm-blackberry-qnx8eabi-ar`
- `arm-blackberry-qnx8eabi-ld`
- `arm-blackberry-qnx8eabi-strip`

### Key Directories

```
gcc-9.3.0-berrycore/
├── bin/                              # Compiler binaries
├── include/                          # System headers
├── arm-blackberry-qnx8eabi/          # Target-specific files
│   ├── bin/                          # Target binutils
│   ├── lib/                          # Target libraries
│   └── include/                      # Target headers
├── x86_64-linux/                     # Host-specific GCC internals
│   └── libexec/gcc/                  # Compiler components
└── share/                            # Documentation
```

---

## Additional Resources

### Documentation

- [GCC 9 Manual](https://gcc.gnu.org/onlinedocs/gcc-9.3.0/)
- [QNX Documentation](https://www.qnx.com/developers/docs/)
- [BerryCore Wiki](https://github.com/sw7ft/BerryCore/wiki)

### Community

- **BerryCore Issues**: https://github.com/sw7ft/BerryCore/issues
- **CrackBerry Forums**: https://forums.crackberry.com

### Related Guides

- `TRANSFER_SUMMARY.txt` - Package transfer details
- `PACKAGING_COMPLETE.txt` - Packaging completion report
- `QUICK_REFERENCE.txt` - Quick command reference

---

## Version History

- **v1.0** (2025-10-24): Initial integration guide for GCC 9.3.0
- **Toolchain**: GCC 9.3.0 from qnx800 build

---

**Questions or Issues?**

Open an issue on the [BerryCore GitHub repository](https://github.com/sw7ft/BerryCore).

**End of Integration Guide**

