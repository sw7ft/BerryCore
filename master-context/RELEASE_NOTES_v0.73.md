# BerryCore v0.73 Release Notes

**Release Date:** November 12, 2025  
**Type:** Port Updates & Maintenance Release

---

## 🎯 Highlights

- **New Port:** BerrySnip 1.0 - Snippet & Notes Manager
- **Port Removed:** gcc-arm 9.3.0 (incompatible with QNX8)
- **Port System:** Updated catalog and index
- **Repository:** Improved gitignore for cleaner repo

---

## ✨ New Features

### BerrySnip 1.0 - Snippet Manager

A dual-interface snippet and notes manager designed for BlackBerry 10.

**Features:**
- **Web Interface** (Port 8018)
  - ES5 compliant for BlackBerry browser
  - Dark theme with gradient design
  - Full CRUD operations for snippets
  - Real-time search across titles, content, and tags
  - Tag-based organization
  - Language syntax reference

- **TUI Interface** (ncurses)
  - Full keyboard navigation
  - **Yank clipboard integration** (press 'y' to copy)
  - Quick search with '/'
  - Add/edit/delete from terminal
  - Color-coded interface

- **Storage**
  - SQLite database (`~/.berrysnip/snippets.db`)
  - Indexed for fast search
  - Portable and easy to backup

**Installation:**
```bash
qpkg install berrysnip

# Start web interface
berrysnip web
# Browse to: http://127.0.0.1:8018

# Or use TUI
berrysnip tui
```

**Use Cases:**
- Code snippets storage
- Configuration file templates
- Command references
- Quick notes and documentation
- Script library

---

## 🔧 Changes

### Ports Repository

**Added:**
- `util-berrysnip-1.0.zip` (24KB) - Snippet manager with web UI and TUI

**Removed:**
- `dev-gcc-arm-9.3.0.zip` - Removed due to QNX8 compatibility issues

**Updated:**
- `ports/INDEX` - Added BerrySnip, removed gcc-arm
- `berrycore/CATALOG` - Updated compiler references to GCC 4.6.3

### Documentation

**Added:**
- `ports/GCC-ARM-TODO.md` - Documents gcc-arm issues and rebuild requirements

**Details gcc-arm removal:**
- Process spawning failures ("No child processes")
- Missing QNX compiler defines (`__LITTLEENDIAN__`, etc.)
- Corrupted specs file
- Incompatible with QNX8/BB10 runtime

**Alternative:** GCC 4.6.3 (included in base BerryCore) works perfectly for C/C++ compilation.

### Repository Improvements

**Updated `.gitignore`:**
- Added `temp/` directory to gitignore
- Keeps work-in-progress files local only
- Maintains clean distributable repository

---

## 📦 Available Ports (6 total)

1. **apache-php** (web, 43MB) - Apache 2.4.58 + PHP 7.4.33
2. **berrypy** (web, 79KB) - BlackBerry app platform manager
3. **berrysnip** (util, 24KB) - Snippet & notes manager ⭐ NEW
4. **hydra** (net, 165KB) - Network password auditing tool
5. **python3** (lang, 25MB) - Python 3.11.10 with pip
6. **tmux** (sys, 2.5MB) - Terminal multiplexer 3.3a

---

## 🐛 Bug Fixes & Improvements

### gcc-arm Port Issues Documented

Comprehensive analysis of gcc-arm 9.3.0 failures:

**Issues Found:**
1. ❌ Process spawning failure - gcc cannot execute cc1/as/ld
2. ❌ Missing QNX defines - endian detection fails
3. ❌ Specs file corruption
4. ❌ Header path misconfiguration

**Testing Done:**
- Created diagnostic tools
- Attempted fixes via wrapper scripts
- Documented requirements for future rebuild

**Recommendation:**
Use GCC 4.6.3 (base system) which works perfectly.

**Future Work:**
gcc-arm will be rebuilt with proper QNX8 configuration when time permits.

---

## 📊 Statistics

**Package Count:** 69 core packages  
**Binary Count:** 100+ binaries  
**Port Count:** 6 installable ports  
**Repository Size:** Clean and optimized  

---

## 🔄 Upgrade Instructions

### From v0.72 or earlier:

```bash
# Update BerryCore
qpkg update

# Or manual installation
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.73/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.73/install.sh
chmod +x install.sh
./install.sh
```

### Post-Upgrade:

```bash
# Check version
cat $NATIVE_TOOLS/VERSION
# Should show: 0.73

# Try new BerrySnip port
qpkg install berrysnip
berrysnip web
```

### If you had gcc-arm installed:

```bash
# The broken gcc-arm will still be on your system
# Remove it manually:
cd $NATIVE_TOOLS
rm -f bin/gcc.real bin/g++.real
rm -rf lib/gcc/arm-blackberry-qnx8eabi/9.3.0
rm -rf libexec/gcc/arm-blackberry-qnx8eabi/9.3.0

# System will revert to working GCC 4.6.3
source $NATIVE_TOOLS/env.sh
gcc --version
```

---

## 🧪 Testing

### Tested On:
- BlackBerry Passport (QNX 8)
- BlackBerry Q10 (QNX 8)

### Test Results:

**BerrySnip:**
- ✅ Web interface loads on BB10 browser
- ✅ ES5 JavaScript compatibility verified
- ✅ TUI navigation with keyboard
- ✅ Yank clipboard integration works
- ✅ SQLite database operations
- ✅ Search and tagging functional

**gcc-arm Removal:**
- ✅ Removed from ports catalog
- ✅ GCC 4.6.3 remains functional
- ✅ C/C++ compilation tested
- ✅ No regressions in base system

---

## 📝 Known Issues

### gcc-arm 9.3.0
- Not compatible with QNX8 on BB10
- Removed from distribution
- Use GCC 4.6.3 (included) for compilation
- See `ports/GCC-ARM-TODO.md` for details

### None reported for v0.73 core
All core functionality tested and working.

---

## 🔮 Coming Soon

- **gcc-arm rebuild:** Properly configured for QNX8
- **Additional ports:** Community requests
- **Documentation updates:** Enhanced guides
- **Port improvements:** Based on user feedback

---

## 👥 Contributors

- BerryCore Team
- Community testers
- Port contributors

---

## 📄 License

BerryCore is provided as-is for BlackBerry 10 enthusiasts.  
Individual packages retain their original licenses.

---

## 🔗 Links

- **Repository:** https://github.com/sw7ft/BerryCore
- **Releases:** https://github.com/sw7ft/BerryCore/releases
- **Documentation:** https://github.com/sw7ft/BerryCore/tree/main/docs
- **Issues:** https://github.com/sw7ft/BerryCore/issues

---

## 💬 Feedback

Found a bug? Have a feature request? Want to contribute a port?

Open an issue or discussion on GitHub!

---

**Thank you for using BerryCore!** 🍇

*Keeping BlackBerry 10 alive, one release at a time.*

