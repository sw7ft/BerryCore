# GCC 9.3.0 ARM-Native Toolchain for BerryCore

ARM-native GCC 9.3.0 compiler that runs directly on BlackBerry 10 devices.

## What This Is

This is an **on-device compiler** - GCC 9.3.0 compiled to run natively on ARM QNX (BlackBerry 10). It allows you to compile C/C++ code directly on your BlackBerry device without needing a separate development machine.

## What's Included

- **GCC 9.3.0** - GNU Compiler Collection
- **G++ 9.3.0** - C++ compiler
- **GCov** - Code coverage tool
- **GCC-AR**, **GCC-NM**, **GCC-Ranlib** - Build tools
- **Complete toolchain** - Headers, libraries, and runtime support

## Installation

```bash
# Install via qpkg
qpkg install gcc-arm

# Verify installation
gcc --version
# Should show: gcc (GCC) 9.3.0

g++ --version
# Should show: g++ (GCC) 9.3.0
```

## Usage

### Compile a C program

```bash
# Create a simple C program
cat > hello.c << 'EOF'
#include <stdio.h>
int main() {
    printf("Hello from BB10!\n");
    return 0;
}
EOF

# Compile it
gcc -o hello hello.c

# Run it
./hello
# Output: Hello from BB10!
```

### Compile a C++ program

```bash
# Create a C++ program
cat > hello.cpp << 'EOF'
#include <iostream>
int main() {
    std::cout << "Hello C++ on BB10!" << std::endl;
    return 0;
}
EOF

# Compile it
g++ -o hello_cpp hello.cpp

# Run it
./hello_cpp
# Output: Hello C++ on BB10!
```

### Compile with optimization

```bash
# Optimize for size
gcc -Os -o hello_small hello.c

# Optimize for speed
gcc -O3 -o hello_fast hello.c

# With debugging symbols
gcc -g -o hello_debug hello.c
```

## Binaries Provided

- `gcc` - C compiler
- `g++` / `c++` - C++ compiler
- `cpp` - C preprocessor
- `gcov` - Coverage testing tool
- `gcov-tool` - Coverage data manipulation
- `gcov-dump` - Coverage data dumper
- `gcc-ar` - Archive tool
- `gcc-nm` - Symbol table tool
- `gcc-ranlib` - Archive index generator
- Plus ARM-specific variants: `arm-blackberry-qnx8eabi-*`

## Target Platform

- **Architecture**: ARM (armle-v7)
- **OS**: QNX 8 / BlackBerry 10
- **ABI**: EABI5
- **Toolchain triplet**: `arm-blackberry-qnx8eabi`

## Using with BerryCore Build System

If you want to build software using BerryCore's toolchain:

```bash
# BerryCore provides qconf-override.mk for QNX builds
export QCONF_OVERRIDE=$NATIVE_TOOLS/qconf-override.mk

# Now you can build QNX/BB10 software using standard make
```

## Differences from Old GCC 4.6.3

### Improvements in GCC 9.3.0:
- **C++17 support** (vs C++98 in 4.6.3)
- **Better optimization** - Faster code generation
- **Modern warnings** - Catch more bugs at compile time
- **ARM improvements** - Better ARM code generation
- **Standards compliance** - More ISO C/C++ compliant

### Compatibility

Most code that compiled with GCC 4.6.3 will compile with 9.3.0, but you may need to:
- Fix warnings that are now errors
- Update deprecated features
- Adjust optimization flags

## Examples

### Check compiler capabilities

```bash
# Show supported C++ standards
g++ -dM -E -x c++ /dev/null | grep __cplusplus

# Show all built-in defines
gcc -dM -E - < /dev/null

# Show include search paths
gcc -E -v - < /dev/null
```

### Compile with QNX specifics

```bash
# Link against QNX libraries
gcc -o myapp myapp.c -lscreen

# Use QNX-specific features
gcc -o myapp myapp.c -DQNX -D__BLACKBERRY10__
```

## Troubleshooting

### "command not found"

Make sure BerryCore is in your PATH:
```bash
. $NATIVE_TOOLS/env.sh
```

### "cannot find -lstdc++"

The toolchain includes libstdc++. If you get linking errors:
```bash
# Check library location
ls $NATIVE_TOOLS/lib/gcc/arm-blackberry-qnx8eabi/9.3.0/
```

### Compilation is slow

This is normal - compiling on device is slower than cross-compiling. For large projects, consider:
- Cross-compiling on a faster machine
- Using optimization level `-O1` instead of `-O3` for faster builds
- Compiling with `-pipe` to reduce I/O

## Size Information

- **Binaries**: ~3.8 MB
- **Libraries**: ~812 KB
- **Compiler internals**: ~46 MB
- **Headers & docs**: ~19 MB
- **Total installed**: ~70 MB

## Version Information

- **GCC Version**: 9.3.0
- **Target**: arm-blackberry-qnx8eabi
- **Configured for**: ARM QNX 8 / BlackBerry 10
- **Thread model**: posix
- **Supported languages**: C, C++

## Related Tools

After installing gcc-arm, you might also want:
- `make` - Build automation (already in BerryCore)
- `autoconf` / `automake` - Configure scripts (already in BerryCore)
- `git` - Version control (already in BerryCore)
- `patch` - Apply patches (already in BerryCore)

## Documentation

For full GCC 9.3.0 documentation:
- GCC Manual: https://gcc.gnu.org/onlinedocs/gcc-9.3.0/
- C++ Features: https://gcc.gnu.org/projects/cxx-status.html

## Notes

- This is a **native compiler** - it runs on BB10 ARM, not a cross-compiler
- For cross-compilation (building on x86 Linux for BB10), use the x86 toolchain
- Binaries compiled with this will work on BB10 and QNX 8 ARM devices
- Size of compiler suite: ~31 MB compressed, ~70 MB installed

---

**Enjoy native compilation on your BlackBerry 10!** 🛠️

