# BerryCore Installation System Documentation

## Overview

BerryCore uses a self-contained, non-invasive package installation system that keeps all tools and libraries in a dedicated directory structure without modifying the QNX system directories.

---

## Installation Directory Structure

```
/accounts/1000/shared/misc/berrycore/
├── bin/              # All executables from packages
├── sbin/             # System executables
├── lib/              # All shared libraries from packages
├── include/          # Development headers
├── share/            # Data files, documentation
│   ├── man/          # Manual pages
│   ├── nmap/         # nmap data files
│   └── ...           # Other package data
├── packages/         # Package zip files (69 packages)
├── env.sh            # Environment setup script
├── sample_profile    # Sample .profile snippet
├── pbpkgadd          # Package installer (moved to bin/ during install)
└── qconf-override.mk # QNX build system configuration
```

---

## Installation Process

### Step 1: Initial Setup (`install.sh`)

The `install.sh` script performs the initial installation:

```bash
#!/bin/sh

# Check for legacy Berrymuch installations
D=/accounts/1000/shared/documents/clitools
if [ -d $D ]; then
    # Warn user to remove old installation
    # (prevents conflicts and performance issues)
fi

# Create BerryCore directory
D=/accounts/1000/shared/misc/berrycore
mkdir -p $D

# Move and unpack main archive
mv berrycore.zip $D
cd $D
touch .nomedia .noindex  # Prevent media indexing
unzip berrycore.zip

# Load environment
. ./env.sh

# Install all packages
for pkg in packages/*.zip
do
    ./pbpkgadd $pkg
done

# Set up user profile
if [ ! -e "$HOME/.profile" ]; then
    cp "$PWD/sample_profile" "$HOME/.profile"
else
    echo "You already have a .profile."
    echo "You can set up your paths by sourcing $PWD/env.sh"
fi

# Create QNX SDK configuration
mkdir -p etc/qnxconf/qconfig
CONFFILE="etc/qnxconf/qconfig/qnx_blackberry_native_development_kit_2.1.0.xml"
# ... creates XML configuration ...

# Move package manager to bin
mkdir -p bin
mv pbpkgadd ./bin
```

**Key Points:**
- ✅ Creates `/accounts/1000/shared/misc/berrycore/`
- ✅ Unpacks base system
- ✅ Installs all 69 packages automatically
- ✅ Sets up user profile if needed
- ✅ Creates QNX SDK configuration

---

### Step 2: Package Installation (`pbpkgadd`)

The `pbpkgadd` script installs individual packages:

```python
#!/usr/bin/env python3.2
import sys
import os
import subprocess
from urllib.request import urlopen

# Get BerryCore installation directory
toolsdir = os.environ.get('NATIVE_TOOLS')
# toolsdir = '/accounts/1000/shared/misc/berrycore'

if toolsdir == None:
    print("No NATIVE_TOOLS in environment. Exiting")
    sys.exit(1)

# Find the package .zip
pkgname = sys.argv[1]
pkgpath = False
if os.path.isfile(pkgname):
    pkgpath = os.path.abspath(pkgname)

if not pkgpath:
    print('No package ' + pkgname + ' found. Exiting')
    sys.exit(1)

# Change to BerryCore directory
print('Unpacking ' + pkgpath + ' into ' + toolsdir)
os.chdir(toolsdir)

# Unzip directly into BerryCore directory
subprocess.call(['unzip', '-uo', pkgpath])
# -u = Update (only extract newer files)
# -o = Overwrite without prompting

print('Done')
```

**Important:** Packages are extracted **directly** into the BerryCore directory, not to system directories!

**Example:**

When installing `nano-4.0.zip` containing:
```
nano-4.0.zip
└── bin/
    └── nano
```

It extracts to:
```
/accounts/1000/shared/misc/berrycore/bin/nano
```

NOT to `/bin/nano` (system directory remains untouched)

---

### Step 3: Environment Setup (`env.sh`)

The `env.sh` script makes all packages accessible by modifying environment variables:

```bash
NATIVE_TOOLS="/accounts/1000/shared/misc/berrycore"
QNX_TARGET=$NATIVE_TOOLS/target_10_3_1_995/qnx6
export NATIVE_TOOLS QNX_TARGET

# Add BerryCore binaries to PATH (searched first!)
PATH="$NATIVE_TOOLS/bin:$NATIVE_TOOLS/sbin:$PATH"

# Add BerryCore libraries to library search path
LD_LIBRARY_PATH="$NATIVE_TOOLS/lib:$QNX_TARGET/armle-v7/usr/lib:$LD_LIBRARY_PATH"
export PATH LD_LIBRARY_PATH

# Make flags for compilation
MAKEFLAGS="-I$QNX_TARGET/usr/include"
export MAKEFLAGS

# QNX configuration
QNX_HOST="$NATIVE_TOOLS"
QCONF_OVERRIDE=$NATIVE_TOOLS/qconf-override.mk
export QNX_HOST QCONF_OVERRIDE

# Tool-specific paths
GROFF_FONT_PATH="$NATIVE_TOOLS/share/groff/1.19.2/font:..."
GROFF_TMAC_PATH="$NATIVE_TOOLS/share/groff/1.19.2/tmac:..."
export GROFF_FONT_PATH GROFF_TMAC_PATH

MAGIC="$NATIVE_TOOLS/share/misc/magic.mgc"
export MAGIC

MANPATH="$NATIVE_TOOLS/man:$NATIVE_TOOLS/share/man:$MANPATH"
export MANPATH

# nmap data directory
NMAPDIR="$NATIVE_TOOLS/share/nmap"
export NMAPDIR

# Aliases
alias man='man -C "$NATIVE_TOOLS/lib/man.conf"'
alias ls='ls --color=auto'
alias cls='printf "\033[2J\033[H"'
alias clear='printf "\033[2J\033[H"'

# Welcome Message
echo ""
echo "==========================================================="
echo "     BerryCore v0.6 - QNX Extended Userland"
echo "==========================================================="
echo ""
```

**How it works:**

1. **PATH**: BerryCore's `bin/` is prepended to PATH
   - When you type `nano`, shell finds `/accounts/1000/shared/misc/berrycore/bin/nano` first
   
2. **LD_LIBRARY_PATH**: BerryCore's `lib/` is added to library search path
   - When binaries load, they find libraries in BerryCore's lib/ directory
   
3. **Tool-specific variables**: Various tools get custom configurations
   - `NMAPDIR` tells nmap where to find its data files
   - `MAGIC` tells `file` command where to find magic database
   - `MANPATH` adds BerryCore's man pages

---

## User Profile Setup

The `sample_profile` is copied to `~/.profile` for new users:

```bash
umask 002

# BerryCore Environment
BERRYCORE_ENV="/accounts/1000/shared/misc/berrycore/env.sh"
if [ -e $BERRYCORE_ENV ];then
    . $BERRYCORE_ENV
fi

# Clear Screen Function and Aliases
clear_screen() {
    printf '\033[2J\033[H'
}

alias cls='printf "\033[2J\033[H"'
alias clear='printf "\033[2J\033[H"'

# AI CLI Integration (optional - uncomment if you have .ai_cli.sh)
# if [ -f ~/.ai_cli.sh ]; then
#     source ~/.ai_cli.sh
# fi

# Auto-Start for copyclip (optional - uncomment and adjust path if needed)
# if [ -f "/accounts/1000/appdata/com.update.Term49.gYABgHeOVx7TI8ajV86LufpS8jM/data/apps/copyclip/app.py" ]; then
#     python3 "/accounts/1000/appdata/com.update.Term49.gYABgHeOVx7TI8ajV86LufpS8jM/data/apps/copyclip/app.py" &
# fi
```

**Result:** Every new shell automatically sources `env.sh`, making all BerryCore tools available!

---

## Package Format

All BerryCore packages follow this standard structure:

```
package-name-version.zip
├── bin/              # Executables (optional)
├── sbin/             # System executables (optional)
├── lib/              # Shared libraries (optional)
├── include/          # Development headers (optional)
└── share/            # Data files (optional)
    ├── doc/
    ├── man/
    └── package-name/
```

**Example: nmap-7.95.zip**
```
nmap-7.95.zip
├── bin/
│   └── nmap
├── lib/
│   ├── libcrypto.so.1.1
│   ├── libssl.so.1.1
│   ├── libz.so.2
│   ├── libgcc_s.so.1
│   └── libstdc++.so.6
└── share/
    └── nmap/
        ├── nmap-services
        ├── nmap-protocols
        ├── nmap-os-db
        └── ... (other data files)
```

When installed via `pbpkgadd`, this becomes:
```
/accounts/1000/shared/misc/berrycore/
├── bin/nmap
├── lib/libcrypto.so.1.1
├── lib/libssl.so.1.1
├── lib/libz.so.2
├── lib/libgcc_s.so.1
├── lib/libstdc++.so.6
└── share/nmap/
    ├── nmap-services
    ├── nmap-protocols
    └── ...
```

---

## Why This Approach?

### ✅ **Safe**
- Doesn't modify QNX system directories (`/bin`, `/lib`, `/usr`)
- Can't break the system
- No risk of conflicting with system packages

### ✅ **Portable**
- Everything in one directory: `/accounts/1000/shared/misc/berrycore/`
- Easy to backup
- Easy to transfer between devices
- Can run from SD card or USB storage

### ✅ **Clean Uninstall**
```bash
rm -rf /accounts/1000/shared/misc/berrycore/
# Remove line from ~/.profile
# Done! System is back to original state
```

### ✅ **No Root Required**
- User directories only
- No system modifications
- Works on locked-down devices

### ✅ **Package Overlay**
- Multiple packages can contribute to same directories
- nmap adds to `lib/`, nano adds to `bin/`, etc.
- No conflicts as long as no filename collisions

### ✅ **Isolated Testing**
- Can have multiple BerryCore installations
- Easy to test new packages
- Rollback is just restoring a backup

---

## Directory Comparison

### System Directories (Untouched)
```bash
/bin/           # QNX system binaries (sh, ls, cat, etc.)
/lib/           # QNX system libraries
/usr/bin/       # QNX user binaries
/usr/lib/       # QNX user libraries
/sbin/          # QNX system administration
```

### BerryCore Directories (Isolated)
```bash
/accounts/1000/shared/misc/berrycore/bin/    # BerryCore binaries
/accounts/1000/shared/misc/berrycore/lib/    # BerryCore libraries
/accounts/1000/shared/misc/berrycore/sbin/   # BerryCore system tools
/accounts/1000/shared/misc/berrycore/share/  # BerryCore data
```

**Key:** Environment variables make BerryCore directories **searched first**, so BerryCore tools override system tools when both exist.

---

## Adding New Packages

To add a new package to an existing BerryCore installation:

```bash
# On device
cd /accounts/1000/shared/misc/berrycore

# Install new package
./bin/pbpkgadd packages/new-package-1.0.zip

# Binaries are immediately available (already in $PATH)
new-command --version
```

**No need to restart shell or re-source environment!** The directories are already in PATH.

---

## qconf-override.mk

Special file that configures the QNX build system to use BerryCore's custom GCC toolchain:

```makefile
CP_HOST=/bin/cp -vfpc $(CP_HOST_OPTIONS)

COMPILER_DRIVER= # qcc not yet

CC_nto_arm_gcc=gcc.pkgsrc -c    # C compiler
AS_nto_arm_gcc=gcc.pkgsrc -c    # Assembler
AR_nto_arm_gcc=ar               # Archiver
LR_nto_arm_gcc=gcc.pkgsrc -r    # Linker (relocatable)
LD_nto_arm_gcc=gcc.pkgsrc       # Linker
UM_nto_arm_gcc=true             # usemsg (disabled)
OC_nto_arm_gcc=objcopy          # Object copy
```

**Purpose:** Enables on-device compilation using BerryCore's GCC instead of requiring the full BlackBerry NDK on a desktop machine.

**Used by:** `gcc.zip` package (103 MB - the largest package in BerryCore)

---

## Current Package Count

**Total Packages:** 69

**Categories:**
- Development Tools (14)
- Shells & Core Utilities (5)
- Text Editors & Processors (4) - includes nano
- Networking & Transfer (8) - includes nmap, sshpass
- Compression & Archiving (4)
- Libraries (9)
- Data Processing & Query Tools (3)
- Multimedia (2)
- Utilities & Applications (10)
- X11 Applications (1) - xeyes with full X11 stack
- JavaScript Engines (1) - QuickJS with 5 consoles
- Miscellaneous (8)

**Total Size:** ~240 MB compressed, ~500+ MB installed

---

## Version History

- **v0.6** (Current) - BerryCore
  - Rebranded from Berrymuch
  - New installation path: `/accounts/1000/shared/misc/berrycore`
  - Added nano, nmap, sshpass, xeyes, QuickJS
  - Enhanced welcome message
  - Improved sample_profile

- **v0.5** - Berry Much OS (Legacy)
  - Last Berry Much OS version
  - Installation path: `/accounts/1000/shared/misc/clitools`
  - 64 packages

- **<0.5** - Berry Much OS (Obsolete)
  - Installation path: `/accounts/1000/shared/documents/clitools`
  - Known performance issues

---

## References

- **Berry Much OS**: Original project that BerryCore continues
- **QNX 6.5**: The operating system BlackBerry 10 is based on
- **BlackBerry 10.3.x**: Target platform
- **ARM v7**: Target architecture (armle-v7)

---

**Last Updated:** October 2025  
**BerryCore Version:** 0.6  
**Maintainer:** SW7FT QNX Initiative

