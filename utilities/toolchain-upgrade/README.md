# GCC 9.3.0 Toolchain for BerryCore

Modern cross-compilation toolchain for building BlackBerry 10 / QNX applications with GCC 9.3.0.

## 📦 What's Included

- **GCC 9.3.0** - Modern C/C++ compiler with C++17 support
- **Binutils** - Complete set of binary utilities
- **QNX 8 Headers & Libraries** - System headers and runtime libraries
- **Target**: `arm-blackberry-qnx8eabi`
- **Size**: 316 MB (compressed), 676 MB (extracted)

## 🚀 Quick Start

### For Developers (Linux)

```bash
# 1. Run the setup script
bash setup-toolchain.sh

# 2. Activate the toolchain
source ~/berrycore-toolchain/qnx-env.sh

# 3. Test it works
arm-blackberry-qnx8eabi-gcc --version

# 4. Compile something
echo 'int main() { return 0; }' > test.c
arm-blackberry-qnx8eabi-gcc test.c -o test
file test
```

### For End Users

This toolchain is for **developers** who want to compile packages for BerryCore.

If you just want to **use** BerryCore packages, you don't need this toolchain - just install BerryCore using `install.sh`.

## 📚 Documentation

| File | Description |
|------|-------------|
| **setup-toolchain.sh** | Automated setup script (START HERE) |
| **INTEGRATION_GUIDE.md** | Complete integration and usage guide |
| **TRANSFER_SUMMARY.txt** | Package details and transfer info |
| **PACKAGING_COMPLETE.txt** | Packaging verification report |
| **QUICK_REFERENCE.txt** | At-a-glance command reference |
| **gcc-9.3.0-qnx8.tar.gz** | The toolchain archive (Git LFS) |

## 🎯 Why Upgrade?

### From GCC 4.6.3 (2012) to GCC 9.3.0 (2019)

**Benefits:**
- ✅ **C++17 Support** - Modern C++ features
- ✅ **Better Optimization** - 7 years of compiler improvements
- ✅ **ARM Improvements** - Better code generation for ARM
- ✅ **Bug Fixes** - Hundreds of bug fixes
- ✅ **Standards Compliance** - Better C/C++ standards support

**Proven Track Record:**
- ✅ git 2.50
- ✅ nano 5.9
- ✅ Dillo Browser
- ✅ OpenSSL 1.1.1w
- ✅ FLTK 1.3.9
- ✅ Many more packages

## 🛠️ Usage Workflow

### 1. Setup (One Time)

```bash
bash setup-toolchain.sh
```

### 2. Activate Environment

```bash
source ~/berrycore-toolchain/qnx-env.sh
```

### 3. Build a Package

```bash
# Download source
wget https://example.com/package-1.0.tar.gz
tar -xzf package-1.0.tar.gz
cd package-1.0

# Configure for cross-compilation
./configure \
    --host=arm-blackberry-qnx8eabi \
    --prefix=/accounts/1000/shared/misc/berrycore

# Build
make -j$(nproc)

# Install to staging directory
make DESTDIR=$PWD/deploy install

# Package for BerryCore
cd deploy/accounts/1000/shared/misc
zip -r package-1.0.zip berrycore/
```

### 4. Deploy to Device

```bash
# Transfer to your BerryCore packages directory
# Then follow BerryCore's installation process
```

## 📋 Requirements

### Development Machine (Linux)

- **OS**: Linux (Ubuntu 20.04+ recommended)
- **Disk**: ~1 GB free space
- **Tools**: tar, make, gcc (for build tools)
- **Memory**: 2 GB RAM minimum

### Target Device (BlackBerry 10)

- **BerryCore**: v0.6 or later
- **Disk**: Varies by package
- **OS**: BlackBerry 10 with QNX compatibility

## ❓ FAQ

### Do I need this to use BerryCore?

**No.** This is for developers who want to compile new packages. Regular users just need to install BerryCore normally.

### Can I use this on macOS or Windows?

**Not directly.** You need a Linux machine or VM. WSL2 on Windows might work but is untested.

### Will binaries compiled with this work on my device?

Yes! This toolchain produces binaries compatible with BlackBerry 10 devices that have BerryCore installed.

### Can I replace the old GCC 4.6.3 toolchain?

You can keep both. The old toolchain is still in `berrycore/packages/gcc.zip`. This new toolchain is for development machines only.

### How do I report issues?

Open an issue on the [BerryCore GitHub repository](https://github.com/sw7ft/BerryCore/issues).

## 🔗 Related Resources

- **BerryCore Main Repository**: https://github.com/sw7ft/BerryCore
- **Installation Wiki**: https://github.com/sw7ft/BerryCore/wiki
- **Integration Guide**: [INTEGRATION_GUIDE.md](INTEGRATION_GUIDE.md)

## 📊 Toolchain Specifications

| Property | Value |
|----------|-------|
| **GCC Version** | 9.3.0 |
| **Target** | arm-blackberry-qnx8eabi |
| **Architecture** | ARMv7-A |
| **FPU** | NEON |
| **C++ Standard** | Up to C++17 |
| **Compressed Size** | 316 MB |
| **Extracted Size** | 676 MB |
| **Total Files** | 9,406 |

## 🏗️ Build History

- **Built**: October 24, 2025
- **Source**: QNX 800 toolchain
- **Packaged By**: Autonomous AI agent
- **Tested On**: BlackBerry Passport
- **Status**: Production ready

## 📝 Version History

- **v1.0** (2025-10-24): Initial release
  - GCC 9.3.0
  - Complete QNX 8 headers and libraries
  - Automated setup script
  - Comprehensive documentation

## 💡 Tips

### Make Setup Permanent

Add to your `~/.bashrc`:

```bash
# BerryCore GCC 9.3.0 Toolchain
if [ -f ~/berrycore-toolchain/qnx-env.sh ]; then
    source ~/berrycore-toolchain/qnx-env.sh
fi
```

### Check if Toolchain is Active

```bash
which arm-blackberry-qnx8eabi-gcc
arm-blackberry-qnx8eabi-gcc --version
```

### Build with Maximum Optimization

```bash
export CFLAGS="-march=armv7-a -mfpu=neon -O3 -flto"
export CXXFLAGS="-march=armv7-a -mfpu=neon -O3 -flto -std=c++17"
```

### Reduce Binary Size

```bash
# After compilation
arm-blackberry-qnx8eabi-strip --strip-unneeded mybinary
```

## 🤝 Contributing

Found a bug? Have a suggestion? Want to add documentation?

1. Fork the repository
2. Create a feature branch
3. Submit a pull request

## 📄 License

This toolchain package includes:
- **GCC**: GPL v3
- **QNX Libraries**: QNX Software Systems license
- **Documentation**: MIT License (BerryCore project)

---

**Questions?** Open an issue on GitHub or check the [Integration Guide](INTEGRATION_GUIDE.md).

**Happy Building!** 🎉

