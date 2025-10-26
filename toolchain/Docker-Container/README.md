# BB10 NDK Docker Container

🐳 **Pre-configured development environment for BlackBerry 10 cross-compilation**

⚠️ **Private Container**: This Docker image contains proprietary BlackBerry NDK components and is available only to developers with valid BB10 NDK licenses.

---

## ⚖️ Legal Notice

**This container includes proprietary software:**
- BlackBerry 10 NDK (proprietary, owned by BlackBerry Limited)
- QNX system files (proprietary, commercial license required)
- Open source components (GCC, OpenSSL, FLTK - properly licensed)

**Access Requirements:**
- Valid BB10 NDK license from BlackBerry
- Compliance with all BlackBerry and QNX license terms
- For legitimate development purposes only

**Disclaimer:**
- Not affiliated with or endorsed by BlackBerry Limited
- Provided "as-is" for educational and development purposes
- Users are responsible for their own license compliance
- BlackBerry®, BB10®, and QNX® are registered trademarks of BlackBerry Limited

**By requesting access, you certify that you have a legitimate BB10 NDK license and will comply with all applicable terms.**

---

## Docker Hub Repository

**Container**: [`sw7ft/bb10-ndk`](https://hub.docker.com/repository/docker/sw7ft/bb10-ndk/general) (Private)

### 🔐 How to Get Access

This container is **private** because it includes proprietary BlackBerry NDK components.

**Requirements**:
- Valid BB10 NDK license from BlackBerry
- Proof of legitimate license (developer account, etc.)

**Steps to Request Access**:
1. Open an issue on the [BerryCore GitHub repository](https://github.com/sw7ft/BerryCore/issues)
2. Use title: "Request BB10 Docker Container Access"
3. Provide proof of BB10 NDK license
4. Maintainer will provide Docker Hub credentials

**Once Approved**: You'll receive login credentials to pull the container from Docker Hub.

---

## Quick Start

### Pull the Container

```bash
docker pull sw7ft/bb10-ndk:latest
```

### Run the Container

```bash
# Interactive shell
docker run -it sw7ft/bb10-ndk

# With volume mount for your projects
docker run -it -v $(pwd):/workspace sw7ft/bb10-ndk

# With name for easy access
docker run -it --name bb10-dev sw7ft/bb10-ndk
```

---

## What's Inside

The container comes **fully configured** with:

### ✅ GCC 9.3.0 Toolchain (Pre-installed)
- ARM cross-compiler: `arm-blackberry-qnx8eabi-gcc 9.3.0`
- Complete QNX 8.0.0 target system
- BB10 NDK libraries and headers
- All environment variables configured

### ✅ Supporting Libraries
- OpenSSL 1.1.1w (HTTPS/TLS)
- FLTK 1.3.9 (GUI toolkit)
- X11 libraries

### ✅ Documentation
- Complete toolchain guides
- Extraction scripts
- Build examples

### 📂 Toolchain Location (in container)
```
/root/toolchain-gcc9-archive/
├── qnx8_toolchain_complete_20251026.tar.gz  (Master archive - 1.6 GB)
└── toolchain_transfer/                       (Individual archives)
    ├── qnx800_toolchain_20251026.tar.gz     (310 MB)
    ├── bbndk_target_20251026.tar.gz         (578 MB)
    ├── bbndk_host_20251026.tar.gz           (197 MB)
    ├── gcc9_build_20251026.tar.gz           (421 MB)
    ├── environment_and_docs_20251026.tar.gz (9.3 KB)
    ├── openssl_1.1.1w_20251026.tar.gz       (36 MB)
    └── fltk_1.3.9_20251026.tar.gz           (7.5 MB)
```

---

## Usage Examples

### 1. Activate Toolchain (Inside Container)

```bash
# Source the GCC 9.3.0 environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Verify
arm-blackberry-qnx8eabi-gcc --version
# Output: arm-blackberry-qnx8eabi-gcc (GCC) 9.3.0
```

### 2. Compile a Simple Program

```bash
# Create test program
cat > hello.c << 'EOF'
#include <stdio.h>
int main() {
    printf("Hello from BB10!\n");
    return 0;
}
EOF

# Compile for BB10
arm-blackberry-qnx8eabi-gcc hello.c -o hello

# Check binary
file hello
# Output: ELF 32-bit LSB executable, ARM, EABI5...
```

### 3. Build with OpenSSL

```bash
# Compile with OpenSSL support
arm-blackberry-qnx8eabi-gcc \
  -I/root/dillo_tls_build/openssl-1.1.1w/include \
  -L/root/dillo_tls_build/openssl-1.1.1w/lib \
  https_client.c -o https_client \
  -lssl -lcrypto
```

### 4. Build GUI Application with FLTK

```bash
# Compile FLTK GUI app
arm-blackberry-qnx8eabi-g++ \
  -I/root/dillo/fltk-1.3.9/include \
  -L/root/dillo/fltk-1.3.9/lib \
  gui_app.cpp -o gui_app \
  -lfltk -lX11
```

---

## Working with Projects

### Mount Your Project Directory

```bash
# On your host machine
cd /path/to/your/bb10-project

# Run container with mounted volume
docker run -it -v $(pwd):/workspace sw7ft/bb10-ndk

# Inside container
cd /workspace
source /root/bbndk/gcc9/bb10-gcc9/env.sh
make  # or your build commands
```

### Persistent Container

```bash
# Create named container
docker run -it --name bb10-dev sw7ft/bb10-ndk

# Exit and later return to same container
docker start -i bb10-dev

# Copy files in/out
docker cp myfile.c bb10-dev:/workspace/
docker cp bb10-dev:/workspace/myapp ./
```

---

## Container Management

### Basic Commands

```bash
# List all containers
docker ps -a

# Start existing container
docker start -i bb10-dev

# Stop container
docker stop bb10-dev

# Remove container
docker rm bb10-dev

# Remove image
docker rmi sw7ft/bb10-ndk
```

### Update to Latest

```bash
# Pull latest version
docker pull sw7ft/bb10-ndk:latest

# Remove old containers
docker rm $(docker ps -a -q -f ancestor=sw7ft/bb10-ndk)

# Run new version
docker run -it --name bb10-dev sw7ft/bb10-ndk:latest
```

---

## Environment Variables (Pre-configured)

The container automatically sets:

```bash
QNX_HOST=/root/qnx800/x86_64-linux
QNX_TARGET=/root/qnx800/arm-blackberry-qnx8eabi
QNX_CONFIGURATION=/root/bbndk/target_10_3_1_995
PATH=/root/qnx800/bin:$PATH

CC=arm-blackberry-qnx8eabi-gcc
CXX=arm-blackberry-qnx8eabi-g++
AR=arm-blackberry-qnx8eabi-ar
LD=arm-blackberry-qnx8eabi-ld
```

---

## Dockerfile (Reference)

The container is built with:

```dockerfile
FROM ubuntu:20.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    curl \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Copy and extract toolchain archives
COPY toolchain_transfer/ /root/toolchain-gcc9-archive/toolchain_transfer/
WORKDIR /root/toolchain-gcc9-archive/toolchain_transfer

# Extract GCC 9.3.0 toolchain
RUN tar xzf qnx800_toolchain_20251026.tar.gz -C /root/

# Extract build environment
RUN mkdir -p /root/bbndk/gcc9 && \
    tar xzf gcc9_build_20251026.tar.gz -C /root/bbndk/gcc9/

# Extract supporting libraries
RUN mkdir -p /root/dillo_tls_build && \
    tar xzf openssl_1.1.1w_20251026.tar.gz -C /root/dillo_tls_build/ && \
    mkdir -p /root/dillo && \
    tar xzf fltk_1.3.9_20251026.tar.gz -C /root/dillo/

# Set up environment
RUN echo 'source /root/bbndk/gcc9/bb10-gcc9/env.sh' >> /root/.bashrc

WORKDIR /root
CMD ["/bin/bash"]
```

---

## Troubleshooting

### Toolchain Not Found

**Problem**: `arm-blackberry-qnx8eabi-gcc: command not found`

**Solution**:
```bash
# Source environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Or add to .bashrc
echo 'source /root/bbndk/gcc9/bb10-gcc9/env.sh' >> ~/.bashrc
```

### Wrong GCC Version

**Problem**: Shows GCC 4.8 instead of 9.3.0

**Solution**:
```bash
# Re-source environment
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Verify
which arm-blackberry-qnx8eabi-gcc
# Should be: /root/qnx800/bin/arm-blackberry-qnx8eabi-gcc

arm-blackberry-qnx8eabi-gcc --version
# Should show: 9.3.0
```

### Permission Denied

**Problem**: Cannot write files in container

**Solution**:
```bash
# Run as root (default)
docker run -it sw7ft/bb10-ndk

# Or mount with appropriate permissions
docker run -it -v $(pwd):/workspace:rw sw7ft/bb10-ndk
```

---

## Use Cases

### ✅ Cross-Compiling BB10 Apps
Compile C/C++ applications on your x86 Linux/macOS machine for ARM BB10 devices.

### ✅ Building BerryCore Packages
Create new packages and ports for the BerryCore project.

### ✅ Porting Linux Software
Port existing Linux applications to BlackBerry 10.

### ✅ CI/CD Integration
Use in automated build pipelines for BB10 applications.

### ✅ Development Without BB10 Device
Develop and compile BB10 apps without needing the actual device during development.

---

## Related Resources

### BerryCore Project
- **GitHub**: https://github.com/sw7ft/BerryCore
- **Ports**: Pre-compiled BB10 packages
- **Package Manager**: `qpkg` for on-device package management

### Toolchain Documentation
- See parent directory (`../README.md`) for detailed toolchain documentation
- Complete extraction guides and component catalogs
- Manual setup instructions for non-Docker environments

### BlackBerry 10 Resources
- BB10 NDK documentation
- QNX Momentics IDE
- BlackBerry developer forums

---

## Container Specifications

| Property | Value |
|----------|-------|
| **Base Image** | Ubuntu 20.04 LTS |
| **GCC Version** | 9.3.0 (ARM cross-compiler) |
| **QNX Target** | 8.0.0 (BB10 compatible) |
| **Architecture** | x86_64 host → ARM target |
| **Compressed Size** | ~800 MB |
| **Extracted Size** | ~2.5 GB |
| **Maintainer** | sw7ft |

---

## Building the Container (Advanced)

If you want to build the container yourself:

```bash
# Clone BerryCore repo
git clone https://github.com/sw7ft/BerryCore.git
cd BerryCore/toolchain

# Download archives (if not using LFS)
git lfs pull

# Build Docker image
docker build -t my-bb10-ndk .

# Run your custom build
docker run -it my-bb10-ndk
```

---

## Support & Contributing

### Issues
- Report container issues on Docker Hub
- Report toolchain issues on BerryCore GitHub

### Updates
- Container is updated periodically with latest toolchain versions
- Check Docker Hub for release notes and changelogs

### Contributing
- Submit pull requests to BerryCore repository
- Share your BB10 ports and packages
- Improve documentation

---

## License

- **Container**: Packaged by sw7ft, free to use
- **GCC**: GPL v3
- **QNX**: Commercial license (BlackBerry Limited)
- **BB10 NDK**: BlackBerry Native Development Kit license
- **OpenSSL**: Apache License 2.0
- **FLTK**: LGPL with exceptions

---

**Container Version**: Latest  
**Last Updated**: October 26, 2025  
**Status**: Production Ready ✅  
**Tested**: Confirmed working for BB10 cross-compilation

---

## Quick Reference

```bash
# Pull
docker pull sw7ft/bb10-ndk

# Run
docker run -it -v $(pwd):/workspace sw7ft/bb10-ndk

# Activate toolchain (inside container)
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Compile
arm-blackberry-qnx8eabi-gcc myapp.c -o myapp

# Verify
file myapp
```

🚀 **Ready to build for BB10!**

