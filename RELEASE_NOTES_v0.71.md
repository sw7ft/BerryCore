# BerryCore v0.71 - Package Manager & Ports Repository

**The Software Expansion Update** 🚀

Transform your BlackBerry 10 into a complete development workstation with on-device compilation, web hosting, and a full package management system!

---

## 🎯 HEADLINE FEATURES

### 📦 **qpkg Package Manager**
A complete package management system for BerryCore!

```bash
qpkg update              # Update BerryCore to latest version
qpkg ports               # Browse available ports
qpkg install apache-php  # Install ports with one command
qpkg catalog             # Browse all installed binaries
qpkg bins                # List all available tools
qpkg info nano           # Get detailed info about any binary
```

**Features:**
- ✅ One-command updates from GitHub releases
- ✅ Automatic package discovery and installation
- ✅ Smart pagination for large lists
- ✅ Category filtering and search
- ✅ Backward compatible (bclist, bcinfo, bcbins still work)

---

### 🔧 **Ports Repository System**
Install additional software on-demand!

**Available Ports:**

#### 1️⃣ **GCC 9.3.0 ARM-Native Compiler** (`gcc-arm` - 33 MB)
**Revolutionary on-device compilation!**

- **Full GCC 9.3.0** toolchain running natively on BB10
- **C++17 support** (vs C++98 in the old 4.6.3)
- **Modern optimizations** and ARM code generation
- **Complete toolchain**: gcc, g++, gcov, gcc-ar, gcc-nm, gcc-ranlib
- **Headers & libraries** included

```bash
qpkg install gcc-arm
gcc --version  # GCC 9.3.0
g++ -std=c++17 myapp.cpp -o myapp
```

**Compile directly on your BlackBerry - no cross-compiler needed!**

---

#### 2️⃣ **Apache HTTP Server 2.4.58 + PHP 7.4.33** (`apache-php` - 43 MB)
**Complete web server stack on your BlackBerry!**

**Apache 2.4.58 Features:**
- Full-featured HTTP/1.1 and HTTP/2 server
- SSL/TLS support (mod_ssl)
- Virtual hosts, .htaccess, CGI/FastCGI
- Reverse proxy capabilities
- All standard modules included

**PHP 7.4.33 Features:**
- CLI and CGI support
- Full standard library
- Extensions: mysqli, pdo, sqlite3, curl, json, xml, openssl, zlib, gd
- Perfect for web development and APIs

```bash
qpkg install apache-php
apachectl start
# Access at http://[your-bb10-ip]/
php -v  # PHP 7.4.33
```

**Use Cases:**
- 🌐 Local web development and testing
- 📱 Personal website or blog hosting
- 🔌 REST API endpoints for automation
- 📊 Data dashboards and visualizations
- 📸 Photo gallery or file sharing server
- 🎓 Learn web development on-device

---

#### 3️⃣ **Hydra Network Auditor** (`hydra` - 165 KB)
**Fast and flexible password auditing tool**

- Supports 50+ protocols (SSH, FTP, HTTP, HTTPS, SMB, and more)
- Parallel connection engine
- Password list and brute-force attacks
- Perfect for security testing

```bash
qpkg install hydra
hydra -l admin -P passwords.txt ssh://192.168.1.1
```

**Optimized package** - Redundant OpenSSL libs removed, uses BerryCore's OpenSSL 3.3.2

---

## 🎨 NEW FEATURES

### Enhanced Binary Catalog
- ✅ **New "Web Development" category** - apache, httpd, apachectl, php, php-cgi
- ✅ **137 binaries** now cataloged and searchable
- ✅ **Smart pagination** - No more overwhelming lists
- ✅ **Category filtering** - Find tools by type: `qpkg catalog -c web`
- ✅ **Text search** - Search descriptions: `qpkg catalog -s compiler`

### Improved Binary Discovery
```bash
# Old way
bclist              # List major binaries
bcinfo nano         # Get info about nano
bcbins              # See all binaries

# New way (backward compatible!)
qpkg catalog        # Same as bclist, but paginated
qpkg info nano      # Same as bcinfo
qpkg bins           # Same as bcbins, but paginated

# Plus new features:
qpkg catalog -s git           # Search for git-related tools
qpkg catalog -c net           # Show only networking tools
qpkg ports                    # Browse installable ports
qpkg install gcc-arm          # Install with one command
```

### Welcome Message Updates
- Updated to show `qpkg` commands
- Quick start now includes: `nano, vim, git, nmap, curl, linux, hydra`
- "Install additional software" section points to ports

---

## 📊 PACKAGE STATISTICS

### Core Distribution
- **Total Packages**: 70 (in berrycore.zip)
- **Total Size**: 279 MB
- **Total Binaries**: 100+
- **Cataloged Tools**: 137

### Ports Repository
- **Available Ports**: 4
- **Total Port Size**: 78.5 MB (compressed)
- **Installation**: On-demand via `qpkg install`

### New Categories in CATALOG
- **Web Development** - 5 binaries (apache, httpd, apachectl, php, php-cgi)
- **Updated Dev Tools** - gcc-arm and g++ listings

---

## 🔧 IMPROVEMENTS & FIXES

### Installer Enhancements
- ✅ **Faster upgrade mode** - Fixed package timestamp detection
- ✅ **Preserves berrycore.zip** - Now uses `cp` instead of `mv`
- ✅ **Better package verification** - More accurate "already installed" detection

### MOTD System
- ✅ **Simplified logic** - Single non-blocking request
- ✅ **Defaults to enabled** - Uses `${BERRYCORE_MOTD_ENABLED:-1}`
- ✅ **Silent failure** - No error messages when offline
- ✅ **Faster startup** - 2-second timeout, no caching overhead

### Environment Setup
- ✅ **Updated welcome message** - Now mentions qpkg and ports
- ✅ **Quick start includes hydra** - Added to tool suggestions
- ✅ **Backward compatibility** - Old commands (bclist, bcinfo) still work as aliases

---

## 🎓 WHAT YOU CAN DO NOW

### On-Device Development
```bash
# Install modern GCC
qpkg install gcc-arm

# Write a C++ program
cat > hello.cpp << 'EOF'
#include <iostream>
int main() {
    std::cout << "Compiled on BB10!" << std::endl;
}
EOF

# Compile with C++17 support
g++ -std=c++17 hello.cpp -o hello
./hello
```

### Web Development
```bash
# Install Apache + PHP
qpkg install apache-php

# Create a PHP app
cat > $NATIVE_TOOLS/share/apache2/htdocs/index.php << 'EOF'
<?php
echo "<h1>Hello from BlackBerry 10!</h1>";
echo "<p>PHP Version: " . PHP_VERSION . "</p>";
?>
EOF

# Start server
apachectl start
# Visit: http://[your-bb10-ip]/
```

### Security Testing
```bash
# Install Hydra
qpkg install hydra

# Test SSH passwords
hydra -l admin -P wordlist.txt ssh://target.example.com
```

### Stay Updated
```bash
# Check for BerryCore updates
qpkg update

# Browse new ports
qpkg ports

# Find tools
qpkg catalog -s network
```

---

## 📦 INSTALLATION

### New Installation
```bash
# Download berrycore.zip and install.sh
cd /accounts/1000/shared/documents
sh install.sh
```

### Upgrading from v0.7
```bash
# Just run qpkg update!
qpkg update

# Or manually:
cd /accounts/1000/shared/documents
# Download new berrycore.zip and install.sh
sh install.sh  # Choose "Upgrade" when prompted
```

---

## 🌟 TECHNICAL HIGHLIGHTS

### Package Manager Architecture
- **GitHub Integration** - Uses GitHub Releases API for updates
- **Raw Content Fetching** - Downloads ports directly from repository
- **Smart Installation** - Automatic extraction, permission setting, path configuration
- **INDEX-based Discovery** - Simple text format for port metadata
- **Modular Design** - Easy to add new ports

### Port Packaging Standards
- **Standardized Structure** - bin/, lib/, share/, doc/ directories
- **Wrapper Scripts** - Smart launchers that respect $NATIVE_TOOLS
- **Documentation** - Every port includes comprehensive README.md
- **Size Optimized** - Removed redundant libraries, macOS metadata cleaned

### Build Quality
- ✅ **ARM-native binaries** - ELF 32-bit LSB for ARMv7 QNX
- ✅ **Clean packages** - No __MACOSX, .DS_Store, or metadata junk
- ✅ **Version tracking** - VERSION file in berrycore/
- ✅ **Comprehensive CATALOG** - 137 tools documented

---

## 📚 DOCUMENTATION

### New Guides
- **`ports/README.md`** - How to use ports system
- **`ports/PORTING_GUIDE.md`** - How to create and submit ports
- **`ports/QPKG-INFO.md`** - Complete qpkg documentation
- **Port READMEs** - Each port includes detailed usage guide

### Command Reference
```bash
# Package Management
qpkg update                    # Update BerryCore
qpkg ports                     # List available ports
qpkg install <package>         # Install a port
qpkg list                      # List installed packages

# Binary Discovery
qpkg catalog                   # Browse all binaries
qpkg catalog -c <category>     # Filter by category
qpkg catalog -s <keyword>      # Search binaries
qpkg bins                      # List all installed binaries
qpkg info <binary>             # Get binary information

# Help
qpkg help                      # Show all commands
```

---

## 🎯 WHAT'S NEXT?

### Future Ports (Community Requested)
- Python 3.11 with pip
- Node.js JavaScript runtime
- PostgreSQL database
- Nginx web server
- Redis cache
- Git 2.50+ (latest)

**Want to contribute a port?** See `ports/PORTING_GUIDE.md`!

---

## 🙏 ACKNOWLEDGMENTS

This release represents a major milestone in making BlackBerry 10 a viable development platform. Special thanks to:

- The original Berrymuch project maintainers
- QNX and ARM toolchain developers
- Apache Software Foundation
- PHP development team
- GCC compiler team
- The BB10 community

---

## 📞 SUPPORT

- **GitHub**: https://github.com/sw7ft/BerryCore
- **Issues**: https://github.com/sw7ft/BerryCore/issues
- **Wiki**: https://github.com/sw7ft/BerryCore/wiki
- **Releases**: https://github.com/sw7ft/BerryCore/releases

---

## 🎉 SUMMARY

**BerryCore v0.71 is the biggest update yet!**

✅ **Complete package manager** (qpkg)  
✅ **Ports repository** with 3 major packages  
✅ **GCC 9.3.0** for on-device compilation  
✅ **Apache + PHP** web server stack  
✅ **Hydra** security tool  
✅ **Enhanced binary discovery** with pagination  
✅ **137 tools cataloged** and searchable  
✅ **Faster installer** and simplified MOTD  
✅ **Comprehensive documentation**  

**Transform your BlackBerry 10 into a complete development workstation!** 🚀

---

*Built with ❤️ for the BlackBerry 10 community*

