# BerryCore Toolchain Components

**GCC 9.3.0 Cross-Compiler for BB10/QNX Development**

---

## ⚖️ Legal Disclaimer

**READ BEFORE USE**

This repository provides documentation and open-source tools for BlackBerry 10 development. However, please note:

### Proprietary Software Notice
- **BlackBerry 10 NDK** and **QNX** are proprietary software owned by BlackBerry Limited
- You **MUST** obtain a legitimate license from BlackBerry to use these components
- This repository does **NOT** include or distribute proprietary BlackBerry/QNX files
- Users are responsible for complying with all BlackBerry and QNX license agreements

### Educational & Development Purpose
- This project is for **educational purposes** and **legitimate development** only
- Intended for developers who already have valid BB10 NDK licenses
- Not affiliated with, endorsed by, or supported by BlackBerry Limited

### No Warranty
- Provided "as-is" without warranty of any kind
- Use at your own risk
- Not responsible for any license violations by users
- Not responsible for any damage to devices or data

### Respect Intellectual Property
- Respect all trademarks, copyrights, and licenses
- BlackBerry®, BB10®, and QNX® are registered trademarks of BlackBerry Limited
- Do not redistribute proprietary components without proper authorization

**By using these tools and documentation, you agree to comply with all applicable laws and license agreements.**

---

## Overview

This directory contains documentation and open-source components for setting up a GCC 9.3.0 toolchain for cross-compiling applications for BlackBerry 10 devices running on ARM QNX 8.

⚠️ **Important**: The BB10 NDK and QNX system files are **proprietary** and require a license from BlackBerry. This repository provides instructions on how to set up the toolchain if you already have legitimate access to these components.

### Pre-configured Development Environment

🐳 **Docker Container Available (Recommended)**

A fully configured Docker container with all components pre-installed is available:

**Repository**: [`sw7ft/bb10-ndk` on Docker Hub](https://hub.docker.com/repository/docker/sw7ft/bb10-ndk/general)

**Status**: Private (requires access credentials)

**How to Get Access**:
1. Ensure you have a valid BB10 NDK license from BlackBerry
2. Contact the maintainer via GitHub issues or Docker Hub
3. Provide proof of legitimate BB10 NDK license
4. Receive Docker Hub credentials for pull access

**Why Use Docker**: Skip the complex setup - everything is ready to compile BB10 apps immediately!

See the [`Docker-Container/` directory](./Docker-Container/) for complete usage documentation.

---

## What's Included in This Repository

### ✅ Open Source Components (Included)

| File | Size | License | Purpose |
|------|------|---------|---------|
| `gcc-9.3.0-qnx8.tar.gz` | 316 MB | GPL v3 | **GCC 9.3.0 x86→ARM cross-compiler** |
| `berrycore-gcc-9.3.0-arm.tar.gz` | 31 MB | GPL v3 | **ARM-native GCC 9.3.0** (runs on device) |
| `openssl_1.1.1w_20251026.tar.gz` | 36 MB | Apache 2.0 | OpenSSL for HTTPS/TLS |
| `fltk_1.3.9_20251026.tar.gz` | 7.5 MB | LGPL | FLTK GUI toolkit |
| `environment_and_docs_20251026.tar.gz` | 9.3 KB | Free | Setup scripts and docs |

### ⚠️ Proprietary Components (You Must Obtain)

These files are **NOT included** due to licensing restrictions. You need to obtain them from BlackBerry:

| Required File | Size | Where to Get |
|---------------|------|--------------|
| BB10 NDK Target Libraries | ~578 MB | [BlackBerry Developer Portal](https://developer.blackberry.com) |
| BB10 NDK Host Tools | ~197 MB | Same as above |
| QNX 8.0.0 System Files | ~310 MB | QNX Software Center (with license) |
| GCC 9 Build Environment | ~421 MB | Contact maintainer (if you have NDK license) |

---

## Quick Start

### Using Docker (Recommended)

```bash
# Pull the pre-configured environment
docker pull sw7ft/bb10-ndk

# Run the container
docker run -it sw7ft/bb10-ndk

# Inside container, toolchain is ready at:
# /root/toolchain-gcc9-archive/
```

### Manual Setup on Linux

#### 1. Extract Core Toolchain
```bash
# Create workspace
mkdir -p ~/bb10-toolchain
cd ~/bb10-toolchain

# Extract main GCC 9.3.0 toolchain
tar xzf gcc-9.3.0-qnx8.tar.gz -C ~/

# This creates: ~/qnx800/ with GCC 9.3.0 binaries
```

#### 2. Extract Build Environment
```bash
# Extract GCC 9 build files and environment
mkdir -p ~/bbndk/gcc9
tar xzf gcc9_build_20251026.tar.gz -C ~/bbndk/gcc9/

# Extract QNX system files
tar xzf qnx800_toolchain_20251026.tar.gz -C ~/
```

#### 3. Activate Toolchain
```bash
# Source the GCC 9.3.0 environment
source ~/bbndk/gcc9/bb10-gcc9/env.sh

# Add to your ~/.bashrc for persistence
echo 'source ~/bbndk/gcc9/bb10-gcc9/env.sh' >> ~/.bashrc
```

#### 4. Verify Installation
```bash
# Check GCC version (should show 9.3.0)
arm-blackberry-qnx8eabi-gcc --version
# Expected: arm-blackberry-qnx8eabi-gcc (GCC) 9.3.0

# Check compiler path
which arm-blackberry-qnx8eabi-gcc
# Expected: ~/qnx800/bin/arm-blackberry-qnx8eabi-gcc

# Test compilation
echo 'int main() { return 0; }' > test.c
arm-blackberry-qnx8eabi-gcc test.c -o test
file test
# Expected: ELF 32-bit LSB executable, ARM, EABI5...

# Clean up
rm test.c test
```

---

## Docker Container Details

### Toolchain Location (in container)
```
/root/toolchain-gcc9-archive/
├── qnx8_toolchain_complete_20251026.tar.gz  (Master archive - 1.6 GB)
└── toolchain_transfer/                       (Individual archives)
    ├── qnx800_toolchain_20251026.tar.gz
    ├── bbndk_target_20251026.tar.gz
    ├── bbndk_host_20251026.tar.gz
    ├── gcc9_build_20251026.tar.gz
    ├── environment_and_docs_20251026.tar.gz
    ├── openssl_1.1.1w_20251026.tar.gz
    └── fltk_1.3.9_20251026.tar.gz
```

### Directory Structure After Extraction
```
/root/
├── qnx800/                          ← GCC 9.3.0 toolchain
│   ├── bin/
│   │   ├── arm-blackberry-qnx8eabi-gcc
│   │   ├── arm-blackberry-qnx8eabi-g++
│   │   ├── arm-blackberry-qnx8eabi-ld
│   │   └── ... (compiler tools)
│   ├── arm-blackberry-qnx8eabi/    ← Target libraries
│   ├── x86_64-linux/                ← Host tools
│   └── include/                     ← Headers
│
├── bbndk/
│   ├── target_10_3_1_995/          ← BB10 target libraries
│   ├── host_10_3_1_12/             ← BB10 host tools
│   └── gcc9/
│       └── bb10-gcc9/
│           ├── env.sh               ← SOURCE THIS!
│           ├── bin/
│           └── include/
│
├── dillo_tls_build/
│   └── openssl-1.1.1w/             ← OpenSSL libraries
│
└── dillo/
    └── fltk-1.3.9/                 ← FLTK GUI toolkit
```

---

## Detailed Deployment Steps

### Step 1: Choose Deployment Method

**Option A - Using Master Archive (Easiest):**
```bash
cd /root/toolchain-gcc9-archive
tar xzf qnx8_toolchain_complete_20251026.tar.gz
cd toolchain_transfer/
```

**Option B - Using Individual Archives:**
```bash
cd /root/toolchain-gcc9-archive/toolchain_transfer/
# Archives are already separated
```

### Step 2: Deploy GCC 9.3.0 Toolchain (CRITICAL)
```bash
# Extract the new GCC 9.3.0 cross-compiler
tar xzf qnx800_toolchain_20251026.tar.gz -C /root/

# This creates /root/qnx800/ with:
# - arm-blackberry-qnx8eabi-gcc 9.3.0
# - Complete ARM QNX 8 target system
```

### Step 3: Deploy Build Environment (ESSENTIAL)
```bash
# Create GCC 9 workspace
mkdir -p /root/bbndk/gcc9

# Extract GCC 9 build files and env.sh
tar xzf gcc9_build_20251026.tar.gz -C /root/bbndk/gcc9/

# Extract documentation
tar xzf environment_and_docs_20251026.tar.gz -C /root/bbndk/
```

### Step 4: Update Target/Host Libraries (Optional)
```bash
# If you already have these, you can skip
# Otherwise, extract:
tar xzf bbndk_target_20251026.tar.gz -C /root/bbndk/
tar xzf bbndk_host_20251026.tar.gz -C /root/bbndk/
```

### Step 5: Extract Supporting Libraries (Recommended)
```bash
# OpenSSL for HTTPS/TLS
mkdir -p /root/dillo_tls_build
tar xzf openssl_1.1.1w_20251026.tar.gz -C /root/dillo_tls_build/

# FLTK for GUI applications
mkdir -p /root/dillo
tar xzf fltk_1.3.9_20251026.tar.gz -C /root/dillo/
```

### Step 6: Activate Toolchain
```bash
# Source the environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Make permanent
echo 'source /root/bbndk/gcc9/bb10-gcc9/env.sh' >> ~/.bashrc
```

---

## Environment Variables

After sourcing `env.sh`, these key variables are set:

```bash
QNX_HOST=/root/qnx800/x86_64-linux
QNX_TARGET=/root/qnx800/arm-blackberry-qnx8eabi
QNX_CONFIGURATION=/root/bbndk/target_10_3_1_995
PATH=/root/qnx800/bin:...
CC=arm-blackberry-qnx8eabi-gcc
CXX=arm-blackberry-qnx8eabi-g++
AR=arm-blackberry-qnx8eabi-ar
LD=arm-blackberry-qnx8eabi-ld
```

---

## Compiling for BB10

### Basic Compilation
```bash
# Compile C program
arm-blackberry-qnx8eabi-gcc hello.c -o hello

# Compile C++ program
arm-blackberry-qnx8eabi-g++ hello.cpp -o hello

# With optimization
arm-blackberry-qnx8eabi-gcc -O2 program.c -o program

# Static linking
arm-blackberry-qnx8eabi-gcc -static program.c -o program
```

### Using OpenSSL
```bash
# Link against OpenSSL
arm-blackberry-qnx8eabi-gcc \
  -I/root/dillo_tls_build/openssl-1.1.1w/include \
  -L/root/dillo_tls_build/openssl-1.1.1w/lib \
  program.c -o program -lssl -lcrypto
```

### Using FLTK (GUI)
```bash
# Compile FLTK application
arm-blackberry-qnx8eabi-g++ \
  -I/root/dillo/fltk-1.3.9/include \
  -L/root/dillo/fltk-1.3.9/lib \
  gui_app.cpp -o gui_app -lfltk -lX11
```

---

## Troubleshooting

### Problem: Old Compiler Still Shows Up
```bash
# Check version
arm-blackberry-qnx8eabi-gcc --version
# Shows: GCC 4.8

# Solution: Source environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Verify
arm-blackberry-qnx8eabi-gcc --version
# Should show: GCC 9.3.0
```

### Problem: Compiler Not Found
```bash
# Check if toolchain extracted
ls -la /root/qnx800/bin/arm-blackberry-qnx8eabi-gcc

# If missing, re-extract
tar xzf qnx800_toolchain_20251026.tar.gz -C /root/

# Source environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh
```

### Problem: Wrong PATH
```bash
# Check PATH
echo $PATH
# Should contain: /root/qnx800/bin

# Check compiler location
which arm-blackberry-qnx8eabi-gcc
# Should be: /root/qnx800/bin/arm-blackberry-qnx8eabi-gcc

# If wrong, re-source environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh
```

### Problem: Missing Libraries
```bash
# Check library paths
echo $QNX_TARGET
# Should be: /root/qnx800/arm-blackberry-qnx8eabi

# List available libraries
ls $QNX_TARGET/lib/
ls $QNX_TARGET/usr/lib/

# If missing, extract bbndk_target
tar xzf bbndk_target_20251026.tar.gz -C /root/bbndk/
```

---

## Verification Checklist

After setup, verify:

- ✅ **GCC Version**: `arm-blackberry-qnx8eabi-gcc --version` shows 9.3.0 (not 4.8)
- ✅ **Compiler Path**: `which arm-blackberry-qnx8eabi-gcc` points to `/root/qnx800/bin/`
- ✅ **Test Compile**: Can compile simple C program
- ✅ **Binary Check**: `file` shows ARM EABI5 executable
- ✅ **Environment**: `env.sh` sources without errors
- ✅ **QNX Variables**: `$QNX_HOST` and `$QNX_TARGET` are set

---

## Upgrade Notes

### From GCC 4.8 to GCC 9.3.0

**Major Improvements:**
- **C++17 Support**: Full C++17 standard library
- **Better Optimization**: Improved `-O2` and `-O3` optimization
- **Modern Standards**: C11, C++11, C++14, C++17
- **Better Diagnostics**: More helpful error messages
- **Link-Time Optimization**: LTO support (`-flto`)
- **Security**: Stack protector improvements

**Breaking Changes:**
- Some old C++ code may need updates for stricter standards
- ABI changes mean you cannot mix GCC 4.8 and 9.3.0 binaries
- Must recompile all libraries with GCC 9.3.0

**Compatibility:**
- ✅ Binaries compiled with GCC 9.3.0 **DO** run on BB10 devices
- ✅ QNX 8 target system is compatible with BB10 OS 10.3.1
- ✅ Can still use BB10 NDK target libraries

---

## ARM-Native Compiler

The `berrycore-gcc-9.3.0-arm.tar.gz` file contains an **ARM-native GCC 9.3.0** that runs directly on BB10 devices.

**Use case:** On-device compilation (compiling C/C++ code directly on your BlackBerry)

**Deployment:** This is packaged as a BerryCore "port" and can be installed via:
```bash
qpkg install gcc-arm
```

See BerryCore's `ports/` directory for more information.

---

## Additional Resources

### Documentation Files
- `TOOLCHAIN_CATALOG.md` - Complete component catalog
- `TRANSFER_MANIFEST.txt` - File checksums and sizes
- `EXTRACTION_GUIDE.md` - Detailed extraction instructions
- `TRANSFER_SUMMARY.md` - Quick reference guide
- `create_toolchain_archives.sh` - Script used to create archives

### Docker Hub
- **Repository**: https://hub.docker.com/repository/docker/sw7ft/bb10-ndk/general
- **Container Tag**: `sw7ft/bb10-ndk:latest`
- **Pre-configured**: Toolchain ready to use out-of-the-box

### BerryCore Project
- **GitHub**: https://github.com/sw7ft/BerryCore
- **Ports**: Additional pre-compiled packages for BB10
- **Install**: Native BerryCore includes package manager (`qpkg`)

---

## Quick Command Reference

```bash
# Extract all components (one-liner)
tar xzf qnx800_toolchain_20251026.tar.gz -C /root/ && \
mkdir -p /root/bbndk/gcc9 && \
tar xzf gcc9_build_20251026.tar.gz -C /root/bbndk/gcc9/ && \
tar xzf environment_and_docs_20251026.tar.gz -C /root/bbndk/ && \
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Verify toolchain
arm-blackberry-qnx8eabi-gcc --version

# Compile test program
echo 'int main() { return 0; }' > test.c && \
arm-blackberry-qnx8eabi-gcc test.c -o test && \
file test && \
rm test.c test
```

---

## File Sizes Summary

| Component | Size | LFS Tracked |
|-----------|------|-------------|
| GCC 9.3.0 Cross-Compiler | 316 MB | ✅ Yes |
| QNX 8.0.0 Toolchain | 310 MB | ✅ Yes |
| BB10 NDK Target | 578 MB | ✅ Yes |
| BB10 NDK Host | 197 MB | ✅ Yes |
| GCC 9 Build Files | 421 MB | ✅ Yes |
| OpenSSL 1.1.1w | 36 MB | ✅ Yes |
| FLTK 1.3.9 | 7.5 MB | ✅ Yes |
| Environment & Docs | 9.3 KB | ✅ Yes |
| ARM-Native GCC 9.3.0 | 31 MB | ✅ Yes |
| **Total** | **~1.9 GB** | |

All files are tracked with Git LFS for efficient repository management.

---

## License & Credits

**GCC 9.3.0**: GPL v3 - https://gcc.gnu.org/  
**QNX**: Commercial - BlackBerry Limited  
**BB10 NDK**: BlackBerry Native Development Kit  
**OpenSSL**: Apache License 2.0  
**FLTK**: LGPL with exceptions  

**Packaged by**: sw7ft  
**Date**: October 26, 2025  
**Purpose**: Modern GCC toolchain for BB10/QNX development

---

**Status**: Production Ready ✅  
**Tested**: Compiles binaries that run on BB10 devices  
**Upgrade**: GCC 4.8 → GCC 9.3.0

