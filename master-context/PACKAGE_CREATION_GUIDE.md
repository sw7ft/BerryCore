# BerryCore Package Creation Guide

## 🎯 Overview

This guide explains how to create and add new packages to BerryCore for BlackBerry 10/QNX devices.

## 🏗️ Prerequisites

### Build Environment

You'll need:
- **QNX SDK**: BlackBerry Native SDK 2.1.0 or compatible
- **Host System**: Linux or macOS recommended
- **Cross-compiler**: ARM v7 toolchain for QNX
- **Build tools**: make, autoconf, automake, cmake

### Target Platform Specifications

- **Architecture**: ARMv7 (armle-v7)
- **OS**: QNX 6.5 / BlackBerry 10.3.x
- **ABI**: QNX EABI
- **Endianness**: Little-endian

## 📦 Package Structure

### Standard Directory Layout

```
package-name-version/
├── bin/              # Executables (chmod 755)
├── sbin/             # System executables (chmod 755)
├── lib/              # Shared libraries (.so files)
├── share/            # Architecture-independent data
│   ├── doc/
│   │   └── package-name/
│   │       ├── README
│   │       ├── LICENSE
│   │       └── CHANGELOG
│   ├── info/         # GNU info files
│   ├── locale/       # Translations
│   └── package-name/ # Package-specific data
├── man/              # Manual pages
│   ├── man1/         # User commands
│   ├── man3/         # Library functions
│   ├── man5/         # File formats
│   └── man8/         # System administration
└── include/          # Header files (for development packages)
```

## 🔨 Compilation Steps

### Method 1: Autotools-based Projects

```bash
#!/bin/bash

# Set up environment
export QNX_TARGET=/path/to/qnx/target/qnx6
export QNX_HOST=/path/to/qnx/host
export PATH=$QNX_HOST/usr/bin:$PATH

# Set compiler
export CC=qcc
export CXX=QCC
export AR=ntoarmv7-ar
export RANLIB=ntoarmv7-ranlib
export STRIP=ntoarmv7-strip

# Configure build
./configure \
    --host=arm-unknown-nto-qnx6.5.0eabi \
    --prefix=/accounts/1000/shared/misc/clitools \
    --disable-shared \
    --enable-static \
    CFLAGS="-O2 -fstack-protector-strong" \
    LDFLAGS="-static"

# Build
make -j$(nproc)

# Install to staging directory
make DESTDIR=/tmp/package-staging install

# Create package
cd /tmp/package-staging/accounts/1000/shared/misc/clitools
zip -r package-name-version.zip .
```

### Method 2: CMake-based Projects

```bash
#!/bin/bash

# Set up environment
export QNX_TARGET=/path/to/qnx/target/qnx6
export QNX_HOST=/path/to/qnx/host

# Create build directory
mkdir build && cd build

# Configure
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../qnx-toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/accounts/1000/shared/misc/clitools \
    -DBUILD_SHARED_LIBS=OFF

# Build
make -j$(nproc)

# Install to staging
make DESTDIR=/tmp/package-staging install

# Package
cd /tmp/package-staging/accounts/1000/shared/misc/clitools
zip -r package-name-version.zip .
```

### QNX CMake Toolchain File Example

```cmake
# qnx-toolchain.cmake
set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 6.5.0)
set(CMAKE_SYSTEM_PROCESSOR armv7)

set(QNX_HOST $ENV{QNX_HOST})
set(QNX_TARGET $ENV{QNX_TARGET})

set(CMAKE_C_COMPILER ${QNX_HOST}/usr/bin/qcc)
set(CMAKE_CXX_COMPILER ${QNX_HOST}/usr/bin/QCC)
set(CMAKE_AR ${QNX_HOST}/usr/bin/ntoarmv7-ar)
set(CMAKE_RANLIB ${QNX_HOST}/usr/bin/ntoarmv7-ranlib)

set(CMAKE_C_FLAGS_INIT "-V4.4.2,gcc_ntoarmv7le")
set(CMAKE_CXX_FLAGS_INIT "-V4.4.2,gcc_ntoarmv7le")

set(CMAKE_FIND_ROOT_PATH ${QNX_TARGET})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

### Method 3: Simple Makefile Projects

```bash
#!/bin/bash

# Set compiler
export CC=qcc
export CFLAGS="-V4.4.2,gcc_ntoarmv7le -O2"
export LDFLAGS="-static"

# Build
make PREFIX=/accounts/1000/shared/misc/clitools

# Manual installation
mkdir -p /tmp/package-staging/accounts/1000/shared/misc/clitools/{bin,man/man1}
cp binary /tmp/package-staging/accounts/1000/shared/misc/clitools/bin/
cp man/binary.1 /tmp/package-staging/accounts/1000/shared/misc/clitools/man/man1/

# Strip binary
ntoarmv7-strip /tmp/package-staging/accounts/1000/shared/misc/clitools/bin/binary

# Package
cd /tmp/package-staging/accounts/1000/shared/misc/clitools
zip -r package-name-version.zip .
```

## ✅ Pre-packaging Checklist

### 1. Binary Verification

```bash
# Check binary format
file bin/your-binary
# Should show: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV)

# Check dependencies
objdump -p bin/your-binary | grep NEEDED
# Minimize dependencies or ensure they're in BerryCore

# Strip symbols (reduce size)
ntoarmv7-strip bin/your-binary
```

### 2. Library Check

```bash
# Verify library dependencies
for binary in bin/* sbin/*; do
    echo "Checking $binary"
    objdump -p "$binary" | grep NEEDED
done

# Ensure libraries are either:
# - Statically linked (preferred)
# - Available in BerryCore (lib/)
# - Part of QNX base system
```

### 3. Path Verification

```bash
# All paths should be relative or use NATIVE_TOOLS environment variable
# Check for hardcoded paths:
grep -r "/opt/" .
grep -r "/usr/local/" .
grep -r "$HOME" .

# These should be fixed before packaging
```

### 4. Permission Setting

```bash
# Set correct permissions
find bin sbin -type f -exec chmod 755 {} \;
find lib -name "*.so*" -exec chmod 755 {} \;
find man share -type f -exec chmod 644 {} \;
find . -type d -exec chmod 755 {} \;
```

### 5. Documentation

Create a minimal README:

```bash
cat > share/doc/package-name/README << EOF
Package: package-name
Version: X.Y.Z
Description: Brief description of the package
Homepage: https://project.url
License: LICENSE_TYPE

Installation:
  This package is installed via pbpkgadd

Usage:
  package-name [options] arguments

Dependencies:
  - dependency1
  - dependency2

Notes:
  - Special considerations
  - Known issues
  - Configuration tips
EOF
```

## 📦 Creating the Package

### Final Package Creation

```bash
#!/bin/bash
set -e

PACKAGE_NAME="package-name"
VERSION="1.0.0"
STAGING_DIR="/tmp/${PACKAGE_NAME}-staging"
OUTPUT_DIR="$(pwd)/packages"

# Clean staging
rm -rf "$STAGING_DIR"
mkdir -p "$STAGING_DIR"

# Copy files to staging
make DESTDIR="$STAGING_DIR/accounts/1000/shared/misc/clitools" install

# Verify structure
cd "$STAGING_DIR/accounts/1000/shared/misc/clitools"
ls -lR

# Set permissions
find . -type f -executable -exec chmod 755 {} \;
find . -type f ! -executable -exec chmod 644 {} \;
find . -type d -exec chmod 755 {} \;

# Strip binaries
find bin sbin -type f 2>/dev/null | while read f; do
    if file "$f" | grep -q ELF; then
        echo "Stripping $f"
        ntoarmv7-strip "$f" || true
    fi
done

# Create package
echo "Creating package..."
zip -r "${OUTPUT_DIR}/${PACKAGE_NAME}-${VERSION}.zip" .

# Show package info
echo "Package created: ${OUTPUT_DIR}/${PACKAGE_NAME}-${VERSION}.zip"
unzip -l "${OUTPUT_DIR}/${PACKAGE_NAME}-${VERSION}.zip"
```

## 🧪 Testing

### On-Device Testing

```bash
# Copy package to device
scp package-name-version.zip devuser@device:/tmp/

# On device:
ssh devuser@device

# Source environment
cd /accounts/1000/shared/misc/clitools
. ./env.sh

# Install package
./pbpkgadd /tmp/package-name-version.zip

# Test installation
which package-name
package-name --version
package-name --help

# Test functionality
# ... run specific tests ...

# Check for errors
ldd bin/package-name  # Verify library loading
```

### Smoke Tests

Create a test script:

```bash
#!/bin/bash
# test-package.sh

set -e

echo "Testing package-name installation..."

# Test 1: Binary exists
if [ ! -f "$NATIVE_TOOLS/bin/package-name" ]; then
    echo "ERROR: Binary not found"
    exit 1
fi

# Test 2: Binary is executable
if [ ! -x "$NATIVE_TOOLS/bin/package-name" ]; then
    echo "ERROR: Binary not executable"
    exit 1
fi

# Test 3: Version check
if ! "$NATIVE_TOOLS/bin/package-name" --version; then
    echo "ERROR: Version check failed"
    exit 1
fi

# Test 4: Basic functionality
if ! "$NATIVE_TOOLS/bin/package-name" --help > /dev/null; then
    echo "ERROR: Help command failed"
    exit 1
fi

echo "All tests passed!"
```

## 📋 Package Metadata (Optional Enhancement)

Consider creating a metadata file for package management:

```bash
cat > share/berrycore/packages/package-name.meta << EOF
{
  "name": "package-name",
  "version": "1.0.0",
  "description": "Brief description",
  "homepage": "https://example.com",
  "license": "MIT",
  "maintainer": "Your Name <email@example.com>",
  "depends": [
    "zlib-1.2.11",
    "openssl-1.0.2u"
  ],
  "conflicts": [],
  "provides": [
    "package-name"
  ],
  "files": {
    "bin": ["package-name"],
    "man": ["man1/package-name.1"]
  },
  "size": 524288,
  "checksum": "sha256:..."
}
EOF
```

## 🚀 Publishing

### Adding to BerryCore Repository

1. **Test thoroughly** on actual device
2. **Document** in ANALYSIS.md
3. **Commit package** to `clitools/packages/`
4. **Update package list** in documentation
5. **Create pull request** or push to repository

### Package Checklist

- [ ] Compiles successfully for ARM v7 QNX
- [ ] All dependencies satisfied or included
- [ ] Binaries stripped (optimized)
- [ ] Permissions set correctly
- [ ] Documentation included (README, man pages)
- [ ] Tested on actual BlackBerry 10 device
- [ ] Package follows naming convention
- [ ] No hardcoded paths
- [ ] Works with BerryCore environment (env.sh)

## 🔧 Troubleshooting

### Common Issues

**Issue**: Binary crashes with "segmentation fault"
**Solution**: Check if statically compiled or if all library dependencies are satisfied

**Issue**: "Cannot find library"
**Solution**: Add library to package or ensure it exists in BerryCore lib/

**Issue**: Wrong architecture
**Solution**: Verify compiler flags include `-V4.4.2,gcc_ntoarmv7le`

**Issue**: Path not found
**Solution**: Ensure paths are relative or use $NATIVE_TOOLS variable

**Issue**: Permission denied
**Solution**: Check file permissions (chmod 755 for binaries)

## 📚 Resources

- **BerryCore Repository**: [GitHub Link]
- **QNX Documentation**: Foundry27 / QNX Software Systems
- **Berry Much OS Forums**: [If available]
- **BlackBerry Developer Forums**: [If still active]

## 🤝 Contributing

When contributing packages:

1. Follow this guide
2. Test on actual hardware
3. Document any quirks or special requirements
4. Include source patches if modifications were needed
5. Provide build script for reproducibility

## 📝 Example: Complete Package Creation

See `examples/package-creation-example.sh` for a complete, working example of creating a package from source.

---

**Last Updated**: October 2025
**Guide Version**: 1.0
**BerryCore Version**: Based on Berry Much OS v0.5+

