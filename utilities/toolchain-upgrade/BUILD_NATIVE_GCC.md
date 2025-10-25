# Building ARM-Native GCC 9.3.0 for BlackBerry 10

## Overview

This guide explains how to use the GCC 9.3.0 cross-compiler to build an ARM-native GCC 9.3.0 that runs directly on BlackBerry 10 devices.

## What We're Doing

**Current State:**
- GCC 9.3.0 cross-compiler (runs on Linux x86, outputs ARM binaries)

**Goal:**
- GCC 9.3.0 native compiler (runs on BB10 ARM, outputs ARM binaries)

**Method:**
- Use cross-compiler to compile GCC source code for ARM target
- Package the resulting ARM binaries
- Install on BlackBerry 10 device

## Prerequisites

### On Linux Development Machine

- **GCC 9.3.0 Cross-Compiler**: Already extracted from tar.gz
- **Disk Space**: ~3 GB free
- **RAM**: 4 GB minimum
- **Time**: 2-4 hours for full build
- **Tools**: make, wget, tar, bzip2

### Dependencies

GCC requires several libraries. We'll build them in order:

1. **GMP** (GNU Multiple Precision Arithmetic Library)
2. **MPFR** (Multiple Precision Floating-Point Reliable Library)
3. **MPC** (Multiple Precision Complex Library)
4. **ISL** (Integer Set Library) - Optional but recommended
5. **GCC** itself

## Step-by-Step Build Process

### Phase 1: Environment Setup

```bash
# Set up build environment
export BUILD_ROOT="$HOME/berrycore-gcc-build"
export TOOLCHAIN_ROOT="$HOME/berrycore-toolchain/gcc-9.3.0-berrycore"
export INSTALL_PREFIX="/accounts/1000/shared/misc/berrycore"

# Create build directories
mkdir -p $BUILD_ROOT/{sources,build,staging}
cd $BUILD_ROOT

# Load cross-compiler environment
source ~/berrycore-toolchain/qnx-env.sh

# Verify cross-compiler works
arm-blackberry-qnx8eabi-gcc --version
```

### Phase 2: Download Source Code

```bash
cd $BUILD_ROOT/sources

# GCC 9.3.0
wget https://ftp.gnu.org/gnu/gcc/gcc-9.3.0/gcc-9.3.0.tar.xz
tar -xf gcc-9.3.0.tar.xz

# GMP 6.2.0 (required by GCC)
wget https://ftp.gnu.org/gnu/gmp/gmp-6.2.0.tar.xz
tar -xf gmp-6.2.0.tar.xz

# MPFR 4.0.2 (required by GCC)
wget https://ftp.gnu.org/gnu/mpfr/mpfr-4.0.2.tar.xz
tar -xf mpfr-4.0.2.tar.xz

# MPC 1.1.0 (required by GCC)
wget https://ftp.gnu.org/gnu/mpc/mpc-1.1.0.tar.gz
tar -xf mpc-1.1.0.tar.gz

# ISL 0.18 (optional, for better optimization)
wget http://isl.gforge.inria.fr/isl-0.18.tar.bz2
tar -xf isl-0.18.tar.bz2
```

### Phase 3: Build Dependencies

#### Build GMP

```bash
cd $BUILD_ROOT/build
mkdir gmp && cd gmp

../../sources/gmp-6.2.0/configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=$BUILD_ROOT/staging \
    --enable-static \
    --disable-shared

make -j$(nproc)
make install

# Verify
ls $BUILD_ROOT/staging/lib/libgmp.a
```

#### Build MPFR

```bash
cd $BUILD_ROOT/build
mkdir mpfr && cd mpfr

../../sources/mpfr-4.0.2/configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=$BUILD_ROOT/staging \
    --with-gmp=$BUILD_ROOT/staging \
    --enable-static \
    --disable-shared

make -j$(nproc)
make install

# Verify
ls $BUILD_ROOT/staging/lib/libmpfr.a
```

#### Build MPC

```bash
cd $BUILD_ROOT/build
mkdir mpc && cd mpc

../../sources/mpc-1.1.0/configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=$BUILD_ROOT/staging \
    --with-gmp=$BUILD_ROOT/staging \
    --with-mpfr=$BUILD_ROOT/staging \
    --enable-static \
    --disable-shared

make -j$(nproc)
make install

# Verify
ls $BUILD_ROOT/staging/lib/libmpc.a
```

#### Build ISL (Optional)

```bash
cd $BUILD_ROOT/build
mkdir isl && cd isl

../../sources/isl-0.18/configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=$BUILD_ROOT/staging \
    --with-gmp-prefix=$BUILD_ROOT/staging \
    --enable-static \
    --disable-shared

make -j$(nproc)
make install

# Verify
ls $BUILD_ROOT/staging/lib/libisl.a
```

### Phase 4: Configure GCC

```bash
cd $BUILD_ROOT/build
mkdir gcc && cd gcc

# Configure GCC for ARM-native build
../../sources/gcc-9.3.0/configure \
    --target=arm-blackberry-qnx8eabi \
    --host=arm-blackberry-qnx8eabi \
    --build=x86_64-linux-gnu \
    --prefix=$INSTALL_PREFIX \
    --with-sysroot=$TOOLCHAIN_ROOT/arm-blackberry-qnx8eabi \
    --with-gmp=$BUILD_ROOT/staging \
    --with-mpfr=$BUILD_ROOT/staging \
    --with-mpc=$BUILD_ROOT/staging \
    --with-isl=$BUILD_ROOT/staging \
    --enable-languages=c,c++ \
    --disable-multilib \
    --disable-nls \
    --disable-libssp \
    --disable-libgomp \
    --disable-libmudflap \
    --disable-libquadmath \
    --with-gnu-as \
    --with-gnu-ld \
    --enable-threads=posix \
    --enable-shared \
    --enable-static \
    --with-arch=armv7-a \
    --with-float=hard \
    --with-fpu=neon

# Note: This might show warnings about missing system headers
# That's normal for a cross-compiled native compiler
```

### Phase 5: Build GCC

```bash
cd $BUILD_ROOT/build/gcc

# Build GCC (this takes 2-4 hours)
make -j$(nproc) all-gcc all-target-libgcc

# If building full GCC with libstdc++:
# make -j$(nproc)

# Check for errors
echo "Build exit code: $?"
```

### Phase 6: Install to Staging

```bash
cd $BUILD_ROOT/build/gcc

# Install to deployment directory
mkdir -p $BUILD_ROOT/deploy
make DESTDIR=$BUILD_ROOT/deploy install-gcc install-target-libgcc

# If built full GCC:
# make DESTDIR=$BUILD_ROOT/deploy install

# Navigate to installed files
cd $BUILD_ROOT/deploy/$INSTALL_PREFIX
```

### Phase 7: Verify ARM Binaries

```bash
cd $BUILD_ROOT/deploy/$INSTALL_PREFIX

# Check that binaries are ARM
file bin/gcc
# Should output: ELF 32-bit LSB executable, ARM, EABI5

file bin/g++
# Should output: ELF 32-bit LSB executable, ARM, EABI5

# Check libraries
ls -lh lib/
ls -lh lib/gcc/
```

### Phase 8: Package for BerryCore

```bash
cd $BUILD_ROOT/deploy/$INSTALL_PREFIX

# Clean up unnecessary files
rm -rf share/man share/info share/doc

# Strip binaries to save space
find . -type f -executable -exec arm-blackberry-qnx8eabi-strip --strip-unneeded {} \; 2>/dev/null

# Check size
du -sh .

# Create package
cd $BUILD_ROOT/deploy/accounts/1000/shared/misc
zip -r gcc-9.3.0-arm-native.zip berrycore/

# Move to BerryCore packages
mv gcc-9.3.0-arm-native.zip /path/to/BerryCore/berrycore/packages/

# Verify package
unzip -t gcc-9.3.0-arm-native.zip
```

## Simplified Build Script

Save this as `build-native-gcc.sh`:

```bash
#!/bin/bash
# build-native-gcc.sh - Build ARM-native GCC 9.3.0

set -e

# Configuration
BUILD_ROOT="$HOME/berrycore-gcc-build"
TOOLCHAIN_ROOT="$HOME/berrycore-toolchain/gcc-9.3.0-berrycore"
INSTALL_PREFIX="/accounts/1000/shared/misc/berrycore"
CORES=$(nproc)

echo "==========================================================="
echo "  Building ARM-Native GCC 9.3.0 for BlackBerry 10"
echo "==========================================================="
echo ""
echo "Build root: $BUILD_ROOT"
echo "Using $(nproc) CPU cores"
echo "Estimated time: 2-4 hours"
echo ""
read -p "Press Enter to start or Ctrl+C to cancel..."

# Setup environment
source ~/berrycore-toolchain/qnx-env.sh

# Create directories
mkdir -p $BUILD_ROOT/{sources,build,staging,deploy}

# Function to build a library
build_lib() {
    local NAME=$1
    local VERSION=$2
    local URL=$3
    local EXTRA_OPTS=$4
    
    echo ""
    echo "=========================================="
    echo "Building $NAME $VERSION"
    echo "=========================================="
    
    cd $BUILD_ROOT/sources
    if [ ! -f "$NAME-$VERSION.tar.xz" ] && [ ! -f "$NAME-$VERSION.tar.gz" ] && [ ! -f "$NAME-$VERSION.tar.bz2" ]; then
        wget $URL
    fi
    
    # Extract
    tar -xf $NAME-$VERSION.tar.* || true
    
    # Build
    cd $BUILD_ROOT/build
    rm -rf $NAME && mkdir $NAME && cd $NAME
    
    ../../sources/$NAME-$VERSION/configure \
        --host=arm-blackberry-qnx8eabi \
        --prefix=$BUILD_ROOT/staging \
        --enable-static \
        --disable-shared \
        $EXTRA_OPTS
    
    make -j$CORES
    make install
    
    echo "✓ $NAME built successfully"
}

# Build dependencies
build_lib "gmp" "6.2.0" "https://ftp.gnu.org/gnu/gmp/gmp-6.2.0.tar.xz"
build_lib "mpfr" "4.0.2" "https://ftp.gnu.org/gnu/mpfr/mpfr-4.0.2.tar.xz" "--with-gmp=$BUILD_ROOT/staging"
build_lib "mpc" "1.1.0" "https://ftp.gnu.org/gnu/mpc/mpc-1.1.0.tar.gz" "--with-gmp=$BUILD_ROOT/staging --with-mpfr=$BUILD_ROOT/staging"

# Download GCC if needed
cd $BUILD_ROOT/sources
if [ ! -f "gcc-9.3.0.tar.xz" ]; then
    echo "Downloading GCC 9.3.0..."
    wget https://ftp.gnu.org/gnu/gcc/gcc-9.3.0/gcc-9.3.0.tar.xz
fi
tar -xf gcc-9.3.0.tar.xz

# Build GCC
echo ""
echo "=========================================="
echo "Building GCC 9.3.0 (this will take a while)"
echo "=========================================="

cd $BUILD_ROOT/build
rm -rf gcc && mkdir gcc && cd gcc

../../sources/gcc-9.3.0/configure \
    --target=arm-blackberry-qnx8eabi \
    --host=arm-blackberry-qnx8eabi \
    --build=x86_64-linux-gnu \
    --prefix=$INSTALL_PREFIX \
    --with-sysroot=$TOOLCHAIN_ROOT/arm-blackberry-qnx8eabi \
    --with-gmp=$BUILD_ROOT/staging \
    --with-mpfr=$BUILD_ROOT/staging \
    --with-mpc=$BUILD_ROOT/staging \
    --enable-languages=c,c++ \
    --disable-multilib \
    --disable-nls \
    --disable-libssp \
    --disable-libgomp \
    --with-gnu-as \
    --with-gnu-ld \
    --enable-threads=posix \
    --with-arch=armv7-a \
    --with-float=hard \
    --with-fpu=neon

make -j$CORES all-gcc all-target-libgcc

echo "✓ GCC compilation complete"

# Install
echo ""
echo "Installing to staging directory..."
make DESTDIR=$BUILD_ROOT/deploy install-gcc install-target-libgcc

# Package
echo ""
echo "Creating BerryCore package..."
cd $BUILD_ROOT/deploy/$INSTALL_PREFIX

# Strip binaries
find . -type f -executable -exec arm-blackberry-qnx8eabi-strip --strip-unneeded {} \; 2>/dev/null

# Create package
cd $BUILD_ROOT/deploy/accounts/1000/shared/misc
zip -r $BUILD_ROOT/gcc-9.3.0-arm-native.zip berrycore/

echo ""
echo "==========================================================="
echo "  Build Complete!"
echo "==========================================================="
echo ""
echo "Package created: $BUILD_ROOT/gcc-9.3.0-arm-native.zip"
echo "Package size: $(du -h $BUILD_ROOT/gcc-9.3.0-arm-native.zip | cut -f1)"
echo ""
echo "Next steps:"
echo "  1. Test the package on your BB10 device"
echo "  2. Move to: berrycore/packages/gcc-9.3.0.zip"
echo "  3. Update BerryCore package list"
echo ""
```

## Troubleshooting

### Issue: "configure: error: C compiler cannot create executables"

**Solution:**
```bash
# Verify cross-compiler is in PATH
which arm-blackberry-qnx8eabi-gcc

# Check config.log for actual error
tail -100 config.log

# Ensure CC is set
export CC=arm-blackberry-qnx8eabi-gcc
export CXX=arm-blackberry-qnx8eabi-g++
```

### Issue: Build fails with missing headers

**Solution:**
```bash
# Ensure sysroot is set
export CFLAGS="-I$TOOLCHAIN_ROOT/include -I$TOOLCHAIN_ROOT/arm-blackberry-qnx8eabi/include"
export LDFLAGS="-L$TOOLCHAIN_ROOT/lib -L$TOOLCHAIN_ROOT/arm-blackberry-qnx8eabi/lib"
```

### Issue: Out of memory during build

**Solution:**
```bash
# Reduce parallel jobs
make -j2  # Instead of -j$(nproc)

# Or add swap space
sudo dd if=/dev/zero of=/swapfile bs=1G count=4
sudo mkswap /swapfile
sudo swapon /swapfile
```

## Testing on Device

After building, test on your BlackBerry device:

```bash
# Transfer to device
scp gcc-9.3.0-arm-native.zip root@192.168.1.108:/tmp/

# SSH to device
ssh root@192.168.1.108

# Extract
cd /tmp
unzip gcc-9.3.0-arm-native.zip

# Test basic compilation
echo 'int main() { return 0; }' > test.c
./berrycore/bin/gcc test.c -o test
./test
echo $?  # Should output 0

# Check version
./berrycore/bin/gcc --version
```

## Size Considerations

### Minimal GCC Package

For a smaller package (compilers only):
```bash
make install-gcc install-target-libgcc
```

### Full GCC Package

For full functionality (includes libstdc++):
```bash
make install
```

### Size Comparison

- **Minimal**: ~40-60 MB
- **Full**: ~100-150 MB
- **Current (4.6.3)**: 103 MB

## Alternative: Quick Test Build

For testing, you can build just the C compiler:

```bash
../../sources/gcc-9.3.0/configure \
    --target=arm-blackberry-qnx8eabi \
    --host=arm-blackberry-qnx8eabi \
    --build=x86_64-linux-gnu \
    --prefix=$INSTALL_PREFIX \
    --enable-languages=c \
    --disable-multilib \
    --disable-bootstrap

make -j$(nproc) all-gcc
```

This is much faster (~30 minutes) and good for testing the build process.

## Expected Build Time

- **GMP**: 5-10 minutes
- **MPFR**: 5-10 minutes  
- **MPC**: 2-5 minutes
- **GCC (minimal)**: 30-60 minutes
- **GCC (full)**: 2-4 hours

**Total**: 3-5 hours for full build

## Next Steps

After successful build:

1. **Test thoroughly on device**
2. **Update PACKAGES.md**
3. **Update CATALOG**
4. **Create installation instructions**
5. **Document any device-specific notes**

---

**Questions or Issues?**

This is an advanced build process. If you encounter problems:
1. Check the troubleshooting section
2. Review build logs carefully
3. Open an issue on GitHub with details

Good luck with your build! 🚀

