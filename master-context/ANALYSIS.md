# BerryCore CLI Tools Analysis

## 📋 Project Overview

**BerryCore** is a QNX Extended Userland for BlackBerry 10 devices - a modern continuation of Berry Much OS. It provides a comprehensive development environment for QNX devices through a modular package system.

## 🏗️ Architecture

### Directory Structure

```
clitools/
├── env.sh                    # Environment setup script
├── pbpkgadd                  # Package installer (Python 3.2)
├── qconf-override.mk         # QNX compiler configuration overrides
├── sample_profile            # Profile snippet for user's ~/.profile
├── packages/                 # Pre-compiled binary packages (64 packages)
└── temp/                     # Working directory for package testing
```

### Installation Process

The `install.sh` script performs the following:

1. **Checks for legacy versions** (< 0.5) that could slow down the device
2. **Creates installation directory**: `/accounts/1000/shared/misc/clitools`
3. **Unpacks clitools.zip** to the installation directory
4. **Sources env.sh** to set up the environment
5. **Installs all packages** using `pbpkgadd`
6. **Sets up user profile** (creates ~/.profile if it doesn't exist)
7. **Creates QNX configuration** for the BlackBerry Native SDK

### Environment Setup (env.sh)

Key environment variables configured:

- **NATIVE_TOOLS**: `/accounts/1000/shared/misc/clitools`
- **QNX_TARGET**: Points to QNX 10.3.1.995 target system
- **PATH**: Prepends clitools bin and sbin directories
- **LD_LIBRARY_PATH**: Adds clitools libraries and ARM libraries
- **MANPATH**: Adds clitools man pages
- **Various tool-specific paths**: GROFF, MAGIC (file), locales

### Package System

**Package Format**: Simple ZIP archives containing standard Unix directory structure:
- `bin/` - Executables
- `sbin/` - System executables
- `lib/` - Shared libraries
- `share/` - Data files, documentation
- `man/` - Manual pages
- `include/` - Header files (for development packages)

**Package Installer (pbpkgadd)**: 
- Python 3.2 script
- Extracts packages into the NATIVE_TOOLS directory
- Overlays files (allows package layering)

## 📦 Current Package Inventory (65 packages)

### Development Tools (14)
- **autoconf-2.69** (942K) - Build system generator
- **automake-1.16.2** (1.7M) - Makefile generator
- **bison-2.5.1** (816K) - Parser generator
- **cflow-1.5** (208K) - C call graph analyzer
- **fakeroot** (144K) - Fake root environment
- **flex-2.6.4** (363K) - Lexical analyzer generator
- **gcc** (103M) - GNU Compiler Collection
- **gettext-0.18.1.1** (7.3M) - Internationalization library
- **git-2.26.0** (15M) - Version control
- **libtool** (likely in contrib)
- **m4-1.4.18** (1.0M) - Macro processor
- **make-3.82** - Build automation
- **patch-2.7.1** - File patching utility

### Shells & Core Utilities (5)
- **bash-5.0** (3.5M) - Bourne Again Shell
- **zsh-5.0.2** - Z Shell
- **coreutils-8.29** (15M) - GNU core utilities
- **diffutils-3.2** (550K) - File comparison
- **findutils-4.7.0** (1.4M) - File search utilities

### Text Editors & Processors (4)
- **ed-1.15** (64K) - Line editor
- **nano** (731K) - User-friendly text editor ✨ NEW
- **vim-8.0** - Vi improved editor
- **groff-1.22.3** (5.8M) - Document formatting system

### Networking & Transfer (7)
- **autossh-1.4g** (1.8M) - Auto-restarting SSH
- **curl-7.76.0** (2.5M) - Data transfer tool
- **dropbear-2019.78** (366K) - Lightweight SSH server/client
- **openssh-7.1p2** - OpenSSH suite
- **rsync-3.1.3** - File synchronization
- **wget-1.20.3** - File downloader
- **zeromq-4.2.3** - Message queue library

### Compression & Archiving (4)
- **bzip2-1.0.6** (4.0M)
- **gzip-1.5**
- **tar-1.32**
- **xz-5.2.3**
- **libarchive-3.4.1**

### Libraries (9)
- **cacert** (4.1M) - CA certificates
- **gdbm-1.9.1** (140K) - Database library
- **jansson-2.11** - JSON library
- **libevent-2.0.22-stable** - Event notification library
- **libmpg123-bb10** - MP3 decoder library
- **libuuid-1.0.3** - UUID generation library
- **nettle-3.5** - Cryptographic library
- **onig-6.9.4** - Regular expression library
- **openssl-1.0.2u** - Cryptography library
- **readline-8.0** - Command-line editing
- **yaml-0.1.4** - YAML parser
- **zlib-1.2.11** - Compression library

### Data Processing & Query Tools (3)
- **bc-1.07** (3.6M) - Arbitrary precision calculator
- **grep-3.4** (375K) - Pattern matching
- **jq-1.6** - JSON processor
- **sqlite-autoconf-3240000** - SQL database engine

### Multimedia (2)
- **ffmpeg-4.2.2** (10M) - Video/audio processing
- **youtube-dl** - Video downloader

### Utilities & Applications (10)
- **ansiweather-1.15.0** (3.4K) - Weather in terminal
- **calcurse-4.5.1** (4.6M) - Calendar & scheduling
- **file-5.11** (505K) - File type identification
- **gcal-4.1** (1.0M) - Calendar calculator
- **hexedit** - Binary file editor
- **ircii-20190117** - IRC client
- **lynx2.8.9rel.1** - Text-based web browser
- **man-1.6g** - Manual page viewer
- **nbsdgames** - BSD games collection
- **sc-7.16_1.1.2** - Spreadsheet calculator
- **task-2.4.2** - Task management
- **tig-2.5.0** - Text-mode interface for Git
- **tmux-2.0** - Terminal multiplexer
- **yank** - Copy to clipboard utility

### Miscellaneous
- **contrib** (875B) - Contributed scripts/tools

## 🎯 Suggested Package Additions

### High Priority - Essential Development Tools

1. **Python 3.x** (if not already in gcc/contrib)
   - Critical for modern scripting
   - Package manager: pip3
   - Size: ~15-25M

2. **Perl 5.x** 
   - Many build systems depend on it
   - CPAN module support
   - Size: ~10-15M

3. **Ruby** 
   - Scripting and automation
   - Package manager: gem
   - Size: ~8-12M

4. **Node.js / npm**
   - JavaScript runtime
   - Modern web development
   - Size: ~15-25M

5. **CMake**
   - Modern build system
   - Essential for many C/C++ projects
   - Size: ~5-10M

6. **Ninja**
   - Fast build system (pairs with CMake)
   - Size: ~500K

7. **pkg-config**
   - Library dependency management
   - Essential for compilation
   - Size: ~100K

### High Priority - Enhanced Utilities

8. **htop** / **top**
   - Process viewer/monitor
   - Essential for system monitoring
   - Size: ~200K

9. **ncurses-apps** (ncdu, iftop, etc.)
   - Disk usage analyzer
   - Network monitoring
   - Size: ~1-2M

10. **tree**
    - Directory structure viewer
    - Size: ~50K

11. **less** / **more**
    - File pagers
    - Size: ~200K

12. **nano** / **micro**
    - Simple text editors
    - More user-friendly than vi
    - Size: ~500K-1M

13. **ack** / **ag** (the_silver_searcher)
    - Fast code search
    - Better than grep for codebases
    - Size: ~500K-1M

14. **sed**
    - Stream editor
    - Essential for text processing
    - Size: ~300K

15. **awk** / **gawk**
    - Text processing language
    - Size: ~500K

### Medium Priority - Network Tools

16. **nmap**
    - Network scanning
    - Security auditing
    - Size: ~5-8M

17. **netcat** (nc)
    - Network Swiss Army knife
    - Size: ~100K

18. **tcpdump** / **wireshark-cli** (tshark)
    - Packet capture
    - Network debugging
    - Size: ~2-5M

19. **telnet**
    - Remote connection
    - Protocol debugging
    - Size: ~100K

20. **socat**
    - Socket relay
    - Advanced networking
    - Size: ~300K

### Medium Priority - Development Enhancements

21. **gdb**
    - GNU debugger
    - Essential for C/C++ debugging
    - Size: ~3-5M

22. **strace** / **ltrace**
    - System call tracer
    - Debugging tool
    - Size: ~500K-1M

23. **valgrind** (if ARM compatible)
    - Memory debugging
    - Profiling
    - Size: ~10-15M

24. **ctags** / **universal-ctags**
    - Code navigation
    - Editor integration
    - Size: ~500K

25. **doxygen**
    - Documentation generator
    - Size: ~5-8M

### Medium Priority - Data & Text Processing

26. **xmllint** / **libxml2-utils**
    - XML processing
    - Size: ~2M

27. **jshon** / **json-c**
    - Additional JSON tools
    - Size: ~500K

28. **csvkit** / **csvtool**
    - CSV processing
    - Size: ~1-2M

29. **pandoc** (if feasible)
    - Document converter
    - Markdown, PDF, etc.
    - Size: ~20-30M

30. **imagemagick** / **graphicsmagick**
    - Image processing
    - Size: ~10-20M

### Lower Priority - Enhanced User Experience

31. **tmux plugins** / **tmux-resurrect**
    - Enhanced tmux experience
    - Size: ~100K

32. **zsh plugins** (oh-my-zsh subset)
    - Enhanced shell experience
    - Size: ~1-2M

33. **fzf**
    - Fuzzy finder
    - Command-line enhancement
    - Size: ~1M

34. **ripgrep** (rg)
    - Ultra-fast search
    - Modern grep replacement
    - Size: ~1-2M

35. **bat**
    - Better cat with syntax highlighting
    - Size: ~2M

36. **exa**
    - Modern ls replacement
    - Size: ~500K

37. **fd**
    - Fast file finder
    - Better than find
    - Size: ~1M

### Lower Priority - Specialized Tools

38. **socat**
    - Network utility
    - Size: ~300K

39. **screen**
    - Terminal multiplexer alternative
    - Size: ~500K

40. **minicom** / **picocom**
    - Serial terminal
    - Embedded development
    - Size: ~300K

41. **i2c-tools** / **spi-tools**
    - Hardware interface tools
    - Size: ~500K

42. **stress** / **stress-ng**
    - System stress testing
    - Size: ~500K

### Security & Cryptography

43. **gnupg** (gpg)
    - Encryption
    - Key management
    - Size: ~5-8M

44. **openssl-tools**
    - Additional crypto utilities
    - Size: ~1M

45. **pass**
    - Password manager
    - Size: ~100K

### Version Control Extensions

46. **mercurial** (hg)
    - Distributed VCS
    - Size: ~3-5M

47. **subversion** (svn)
    - Centralized VCS
    - Size: ~5-8M

48. **git-extras**
    - Git utilities
    - Size: ~500K

### Scripting & Automation

49. **expect**
    - Automation tool
    - Size: ~500K

50. **dialog** / **whiptail**
    - Shell UI builder
    - Size: ~300K

## 🔧 Package Creation Guidelines

Based on the existing package structure:

### Package Structure Requirements

```
package-name-version.zip
├── bin/           # Executables
├── sbin/          # System binaries
├── lib/           # Shared libraries (.so files)
├── share/         # Data files, documentation
│   ├── doc/
│   ├── info/
│   └── locale/
├── man/           # Manual pages
│   └── man1/
└── include/       # Headers (for development packages)
```

### Compilation Targets

- **Architecture**: ARM v7 (armle-v7)
- **OS**: QNX 6.x / BlackBerry 10
- **SDK**: BlackBerry Native SDK 2.1.0
- **Compiler**: gcc.pkgsrc (from qconf-override.mk)

### Best Practices

1. **Static linking preferred** where possible to reduce library dependencies
2. **Strip binaries** to reduce size (use `strip` or compile with appropriate flags)
3. **Include minimal documentation** (README, man pages only)
4. **Test on actual device** before packaging
5. **List dependencies** in a metadata file (consider creating `PKGINFO` file)
6. **Version naming**: Use `package-version.zip` format
7. **Maintainer info**: Add to package documentation

## 📊 Statistics Summary

- **Total Packages**: 65
- **Total Size**: ~241 MB (estimated)
- **Largest Package**: gcc (103 MB)
- **Smallest Package**: ansiweather (3.4 KB)
- **Categories**: 
  - Development: 22%
  - System Utilities: 31%
  - Networking: 11%
  - Libraries: 19%
  - Applications: 17%

## 🚀 Next Steps

1. **Prioritize packages** based on user needs and dependencies
2. **Set up cross-compilation environment** for QNX ARM
3. **Create package build scripts** for automation
4. **Test packages** on BlackBerry 10 devices
5. **Document package creation process**
6. **Set up package repository** for community contributions
7. **Create dependency resolver** for pbpkgadd
8. **Add package metadata system** (version, deps, description)

## 🎯 Immediate Action Items

### Quick Wins (Easy to add, high value)

1. **tree** - Simple, single binary
2. **less** - Essential pager
3. **nano** - User-friendly editor
4. **htop** - System monitoring
5. **ack** / **ag** - Fast search
6. **netcat** - Network utility
7. **sed** - Text processing
8. **gawk** - Text processing
9. **pkg-config** - Build essential
10. **ctags** - Code navigation

### Strategic Additions (Requires effort, high impact)

1. **Python 3** with pip (if not present)
2. **CMake** - Modern build system
3. **gdb** - Debugger
4. **Perl** - Many tools depend on it
5. **Node.js** - Modern development

### Community Wishlist

Consider creating a survey or GitHub issues to gather user feedback on most wanted packages.

## 📝 Notes

- Berry Much OS v0.5 was the last official version
- BerryCore aims to modernize and extend this foundation
- Focus on developer experience and modern tooling
- Maintain compatibility with BlackBerry 10 platform
- Consider future QNX 8.x and RISC-V targets

