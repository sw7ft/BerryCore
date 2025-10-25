# OpenSSL 3.3.2 for BlackBerry QNX 8 ARM

## What's Included
- OpenSSL 3.3.2 compiled for BlackBerry QNX 8 ARM architecture
- Both shared libraries (.so) and static libraries (.a)
- Complete development headers for building applications
- pkg-config files for easy integration
- CMake configuration files

## Package Contents
```
accounts/1000/shared/misc/openssl332/
├── lib/
│   ├── libcrypto.so.3     # Main crypto library (3.4MB)
│   ├── libcrypto.so       # Symlink to libcrypto.so.3
│   ├── libcrypto.a        # Static crypto library (5.6MB)
│   ├── libssl.so.3        # SSL/TLS library (802KB)
│   ├── libssl.so          # Symlink to libssl.so.3
│   ├── libssl.a           # Static SSL library (1.1MB)
│   ├── pkgconfig/         # pkg-config files
│   └── cmake/             # CMake configuration
└── include/
    └── openssl/           # Complete OpenSSL headers
```

## Installation Instructions

### 1. Extract to QNX Device
```bash
# Transfer this package to your QNX device
scp openssl332_qnx8_deploy.tar.gz user@qnx-device:/accounts/1000/appdata/

# On the QNX device, extract:
cd /accounts/1000/appdata/
tar -xzf openssl332_qnx8_deploy.tar.gz
```

### 2. Set Environment Variables
```bash
# Add to your shell profile or run before using:
export LD_LIBRARY_PATH="/accounts/1000/shared/misc/openssl332/lib:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="/accounts/1000/shared/misc/openssl332/lib/pkgconfig:$PKG_CONFIG_PATH"
export OPENSSL_ROOT_DIR="/accounts/1000/shared/misc/openssl332"
```

## Version Information
- **OpenSSL Version**: 3.3.2 (September 3, 2024)
- **Target Architecture**: ARM (arm-blackberry-qnx8eabi)
- **Build Configuration**: Shared libraries, no applications, no async, no tests
- **Compiled With**: GCC 9.3.0 (BlackBerry QNX toolchain)

## Key Features
- **Modern OpenSSL**: Latest stable 3.3.2 release with all security updates
- **Full Compatibility**: Works with existing OpenSSL 3.x applications
- **QNX Optimized**: Cross-compiled specifically for BlackBerry QNX 8 ARM
- **Complete Package**: Libraries, headers, and configuration files included

## Usage Examples

### Linking with Applications
```bash
# Using pkg-config (recommended):
gcc myapp.c $(pkg-config --cflags --libs openssl)

# Manual linking:
gcc myapp.c -I/accounts/1000/shared/misc/openssl332/include \
            -L/accounts/1000/shared/misc/openssl332/lib \
            -lssl -lcrypto
```

### Python Integration
This OpenSSL version is compatible with Python applications that need SSL/TLS support.
Make sure your Python environment can find these libraries via `LD_LIBRARY_PATH`.

## Compatibility Notes
- **Replaces**: OpenSSL 1.0.x and 1.1.x versions
- **Compatible With**: Applications built for OpenSSL 3.x
- **Python Support**: Works with Python 3.x SSL modules
- **QNX Version**: Tested on BlackBerry QNX 8

## Build Information
- **Build Date**: October 23, 2025
- **Compiler**: arm-blackberry-qnx8eabi-gcc 9.3.0
- **Configure Options**: linux-armv4 --cross-compile-prefix=arm-blackberry-qnx8eabi- shared no-async no-tests no-apps
- **Dependencies**: libatomic (included in QNX toolchain)

## Support
This is a cross-compiled version of the official OpenSSL 3.3.2 release.
For OpenSSL documentation and support, visit: https://www.openssl.org/

## License
OpenSSL is licensed under the Apache License 2.0.
See the OpenSSL project for full license details.
