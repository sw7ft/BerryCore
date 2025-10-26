# BB10 NDK Docker Container

🐳 **Development environment for BlackBerry 10 cross-compilation**

---

## Docker Hub

**Container**: [`sw7ft/bb10-ndk`](https://hub.docker.com/repository/docker/sw7ft/bb10-ndk/general)

---

## What's Included

- GCC 9.3.0 ARM cross-compiler
- QNX 8.0.0 target system
- OpenSSL, FLTK, and supporting libraries

---

## Quick Start

```bash
# Pull container
docker pull sw7ft/bb10-ndk

# Run interactively
docker run -it sw7ft/bb10-ndk

# With project directory mounted
docker run -it -v $(pwd):/workspace sw7ft/bb10-ndk
```

---

## Usage

Inside the container:

```bash
# Activate toolchain
source /root/bbndk/gcc9/bb10-gcc9/env.sh

# Compile
arm-blackberry-qnx8eabi-gcc myapp.c -o myapp
```

---

## Toolchain Files

The GCC 9.3.0 toolchain and related files are located in the parent `toolchain/` directory of this repository.

See `../README.md` for toolchain documentation and setup instructions.

---

🚀 **Ready to build for BB10**
