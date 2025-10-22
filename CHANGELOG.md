# Changelog

All notable changes to BerryCore will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.6.0] - 2025-10-21

### 🎉 Major Release - BerryCore Rebranding

This is the first official release under the **BerryCore** name, continuing the legacy of Berry Much OS v0.5.

### Added

#### New Packages (5)
- **nano-4.0** - User-friendly text editor (731 KB)
- **nmap-7.95** - Network exploration and security scanner (3.0 MB)
  - Includes full nmap data files (nmap-services, nmap-protocols, nmap-os-db)
  - All required libraries bundled
- **sshpass-1.06** - Non-interactive SSH password provider
- **xeyes-1.1.0** - Classic X11 demo application (~8 MB)
  - Full X11 client library stack included
  - Complete development headers for building X11 apps
- **quickjs-2024.06** - JavaScript engine and REPL (~19 MB)
  - 5 console variants: simple, shell, web, web-es5, compiler (qjsc)
  - Static libraries for development

#### New Features
- **Binary Catalog System** - Browse and discover installed binaries
  - `bclist` - List binaries by category
  - `bclist -c CATEGORY` - Filter by category (dev, net, editor, etc.)
  - `bclist -s TERM` - Search for specific tools
  - `bcinfo BINARY` - Get detailed info about a binary
  - `bcbins` - Quick list of all installed binaries
  - `CATALOG` file with ~100 documented binaries

- **Message of the Day (MOTD)** - Stay updated with latest news
  - Automatic fetching from GitHub
  - Smart caching (1-hour intervals)
  - Non-blocking, works offline
  - `bcmotd` utility for management
  - Endpoint: https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt

- **Interactive Installation** - Choose custom installation directory
  - Default: `/accounts/1000/shared/misc/berrycore`
  - Custom: `/accounts/1000/shared/misc/YOUR_NAME`
  - Allows multiple BerryCore installations

- **Enhanced Welcome Screen** - Informative startup message
  - Shows package count
  - Quick discovery commands
  - MOTD integration

- **Improved Profile Setup** - Better first-run experience
  - Auto-configured `.profile` for new users
  - MOTD enabled by default
  - Clear instructions for existing users

### Changed

- **Rebranded** from Berry Much OS to **BerryCore**
- **Installation Path** changed from `/accounts/1000/shared/misc/clitools` to `/accounts/1000/shared/misc/berrycore`
- **Environment Variable** renamed: `CLITOOLS_ENV` → `BERRYCORE_ENV`
- **Welcome Message** now includes usage tips and discovery commands
- **Version Bumped** to 0.6 to mark new era

### Fixed

- **nmap** now includes proper data files and `NMAPDIR` environment variable
- **nano** binary permissions corrected
- **install.sh** prompt now uses POSIX-compliant `echo -n` instead of `printf`
- Legacy version detection improved

### Infrastructure

- **Documentation** greatly expanded
  - `INSTALLATION_SYSTEM.md` - Complete installation system documentation
  - `PACKAGE_CREATION_GUIDE.md` - How to create packages
  - `PRIORITY_PACKAGES.md` - Roadmap for future packages
  - `ANALYSIS.md` - Complete package inventory and analysis

- **Utility Scripts** added
  - `scan_packages.sh` - Detect macOS metadata in packages
  - `clean_packages.sh` - Remove macOS junk from packages
  - `check_sizes.py` - Analyze package sizes

### Statistics

- **Total Packages**: 69 (was 64 in Berry Much OS v0.5)
- **Total Size**: ~241 MB compressed
- **New Binary Count**: 100+ binaries available
- **Categories**: 12 (dev, shell, editor, net, vcs, sys, archive, media, data, x11, js, doc)

---

## [0.5.0] - Berry Much OS (Legacy)

Last official Berry Much OS release. Included 64 packages with core development tools, shells, networking utilities, and system tools.

### Known Issues (Resolved in 0.6)
- Installation at `/accounts/1000/shared/documents/clitools` could cause slowdowns
- No binary discovery system
- Limited documentation

---

## Legend

- 🎉 Major release
- ✨ New feature
- 🐛 Bug fix
- 📝 Documentation
- ⚡ Performance improvement
- 🔒 Security fix
- 🗑️ Deprecation
- 💥 Breaking change

---

## Future Releases

See [PRIORITY_PACKAGES.md](master-context/PRIORITY_PACKAGES.md) for planned additions.

### Tentatively Planned for 0.7
- htop - Interactive process viewer
- CMake - Modern build system
- pkg-config - Build system essential
- sed/gawk - Text processing (if missing)
- Python 3 improvements (if applicable)

