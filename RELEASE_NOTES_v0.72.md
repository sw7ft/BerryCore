# BerryCore v0.72 Release Notes

**Release Date**: October 27, 2025  
**Type**: Quality of Life Update

---

## 🎯 Overview

BerryCore v0.72 brings convenient navigation shortcuts and an updated tmux port with critical QNX fixes.

---

## ✨ New Features

### Quick Navigation Aliases

Navigate instantly to common BB10 directories:

```bash
misc        # /accounts/1000/shared/misc
docs        # /accounts/1000/shared/documents
downloads   # /accounts/1000/shared/downloads
sdcard      # /accounts/1000/removable/sdcard
bc          # BerryCore installation directory
```

Type the alias and hit enter - no more long path typing!

---

## 🔧 Port Updates

### tmux 3.3a (Updated)

**Fixed critical QNX compatibility issues:**

- ✅ **TERM Support**: Automatically sets `TERM=ansi` for QNX
- ✅ **Shell Integration**: Uses BerryCore bash instead of system shell
- ✅ **Socket Path Fix**: Uses `~/t/` to avoid Unix socket path limits
- ✅ **Better Documentation**: Comprehensive guide with QNX-specific notes

**Install/Update:**
```bash
qpkg install tmux
```

**Quick Start:**
```bash
tmux              # Start tmux
# Ctrl+b, "       Split horizontally
# Ctrl+b, %       Split vertically
# Ctrl+b, d       Detach (session keeps running!)
```

---

## 📊 Package Statistics

- **Total Packages**: 70
- **Total Binaries**: 100+
- **Available Ports**: 5 (hydra, gcc-arm, apache-php, tmux, gcc9-docs)

---

## 🛠️ Technical Changes

### Environment Improvements
- Added 5 directory navigation aliases to `env.sh`
- Updated welcome message to show shortcuts
- Improved user experience for first-time users

### Port Fixes
- Fixed tmux wrapper for QNX terminal compatibility
- Resolved BSD-style PTY socket path issues
- Added comprehensive tmux documentation

---

## 📥 Installation

### New Installation
```bash
# Transfer berrycore.zip and install.sh to your device
cd /accounts/1000/shared/documents
sh install.sh
```

### Upgrade from v0.71
```bash
# The installer will detect your existing installation
sh install.sh
# Choose "Upgrade" to install only new packages
```

---

## 🗂️ Documentation Updates

- Organized documentation into `docs/` directory
- Updated Docker container to `sw7ft/bb10-gcc9`
- Added toolchain archive location instructions
- Improved legal disclaimers and licensing information

---

## 🐛 Known Issues

### tmux
- Mouse support is limited on QNX
- Some complex key combinations may not work in Term49
- Use `tmux -S /tmp/custom-socket` if you need custom socket locations

---

## 🔮 Coming Soon

- Additional networking tools
- Python 3 port
- More system utilities
- Performance optimizations

---

## 📝 Upgrade Notes

**From v0.71:**
- New navigation aliases available immediately after upgrade
- Run `qpkg install tmux` to update to fixed version
- No breaking changes

**From v0.6:**
- Upgrade through v0.71 first for best results
- Or do fresh install and restore your data

---

## 🙏 Credits

Thanks to the BB10 community for:
- Reporting tmux terminal issues
- Testing socket path fixes
- Feedback on navigation shortcuts

---

## 📦 Release Files

- `berrycore.zip` (279 MB) - Main package
- `install.sh` - Installation script
- See GitHub Releases for download links

---

## 🔗 Resources

- **GitHub**: https://github.com/sw7ft/BerryCore
- **Documentation**: See `docs/` directory
- **Docker**: https://hub.docker.com/repository/docker/sw7ft/bb10-gcc9
- **Support**: Open an issue on GitHub

---

**Enjoy the smoother BerryCore experience!** 🚀

