# BB10 GCC 9 Docker Container

🐳 **Development environment for BlackBerry 10 cross-compilation**

---

## Docker Hub

**Container**: [`sw7ft/bb10-gcc9`](https://hub.docker.com/repository/docker/sw7ft/bb10-gcc9/general)

---

## What's Included

- GCC 9.3.0 ARM cross-compiler
- QNX 8.0.0 target system
- OpenSSL, FLTK, and supporting libraries

---

## Quick Start

```bash
# Pull container
docker pull sw7ft/bb10-gcc9

# Run interactively
docker run -it sw7ft/bb10-gcc9

# With project directory mounted
docker run -it -v $(pwd):/workspace sw7ft/bb10-gcc9
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

## Toolchain Archive

The container includes GCC 9.3.0 toolchain components. Toolchain archives are available in the parent `toolchain/` directory for manual setup.

See `../README.md` for documentation and setup instructions.

---

🚀 **Ready to build for BB10**
