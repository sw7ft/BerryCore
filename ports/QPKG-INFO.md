# qpkg - QNX Package Manager

Complete guide to using qpkg, BerryCore's unified package management system.

## Overview

`qpkg` is the all-in-one package manager for BerryCore that handles:
- **Updates**: Automatically update BerryCore to the latest release
- **Ports**: Install additional software packages from the repository
- **Discovery**: Browse and search available binaries
- **Information**: Get details about installed tools

## Quick Start

```bash
qpkg help          # Show all commands
qpkg update        # Update BerryCore
qpkg ports         # List available ports
qpkg install hydra # Install a port
qpkg catalog       # Browse binaries
```

---

## Commands

### Core Commands

#### `qpkg update`
Check for and install BerryCore updates from GitHub releases.

```bash
$ qpkg update
Current version: v0.7
Checking for updates...
✨ New version available: v0.8!

Download and install v0.8? [Y/n]: y
```

**How it works:**
1. Reads local version from `$NATIVE_TOOLS/VERSION`
2. Fetches latest release from GitHub API
3. Downloads `berrycore.zip` and `install.sh` to `/accounts/1000/shared/documents/`
4. Runs installer with upgrade mode (preserves existing packages)
5. Updates VERSION file

**Requirements:**
- Internet connection
- Write access to `/accounts/1000/shared/documents/`

---

#### `qpkg ports`
List all available ports from the GitHub repository.

```bash
$ qpkg ports
Available ports to install:
===========================================================

  hydra                [net] v9.5    2.3M   Fast network logon cracker
  python               [lang] v3.11   45M   Python programming language
  postgresql           [database] v15.0   25M   Advanced relational database

Install with: qpkg install <port-name>
```

**How it works:**
1. Fetches `ports/INDEX` from GitHub raw content
2. Parses and displays available ports
3. Shows name, category, version, size, and description

**Source:**
- URL: `https://raw.githubusercontent.com/sw7ft/BerryCore/main/ports/INDEX`

---

#### `qpkg install <package>`
Download and install a port from the repository.

```bash
$ qpkg install hydra
Installing Port: hydra
Port: hydra v9.5
Category: net
Size: 2.3M
Description: Fast network logon cracker - password auditing tool

Install this port? [Y/n]: y

Downloading net-hydra-9.5.zip...
Progress: 100%
✓ Downloaded net-hydra-9.5.zip

Installing to /accounts/1000/shared/misc/berrycore...
✓ Port 'hydra' installed successfully!

Binaries installed:
  bin/hydra
  bin/pw-inspector
```

**How it works:**
1. Fetches `ports/INDEX` to find the port
2. Constructs download URL: `ports/{category}-{name}-{version}.zip`
3. Downloads to `/tmp/qpkg-{name}-$$`
4. Extracts to `$NATIVE_TOOLS`
5. Sets executable permissions on `bin/*`
6. Cleans up temporary files

**Port Naming Convention:**
```
Format: {category}-{name}-{version}.zip
Examples:
  net-hydra-9.5.zip
  lang-python-3.11.zip
  database-postgresql-15.0.zip
```

**Requirements:**
- Internet connection
- Space in `$NATIVE_TOOLS`
- Write access to `/tmp`

---

#### `qpkg catalog [options]`
Browse and search installed binaries.

```bash
# List all binaries by category
$ qpkg catalog

# Search for specific tools
$ qpkg catalog -s ssh
  ssh                       [net] Secure shell client
  sshpass                   [net] Non-interactive SSH password provider
  openssh                   [net] Secure Shell server

# Show specific category
$ qpkg catalog -c net
  curl                      Transfer data from/to servers
  wget                      Download files from the web
  nmap                      Network exploration and security scanner
  hydra                     Fast network logon cracker
```

**Options:**
- `(none)` - List all binaries organized by category
- `-c CATEGORY` - Show binaries in specific category
- `-s TERM` - Search for binaries matching term

**Features:**
- Auto-pagination with `less` (quits if fits on one screen)
- Color-coded output
- Searches names and descriptions

---

#### `qpkg bins`
List all installed binaries from `$NATIVE_TOOLS/bin`.

```bash
$ qpkg bins
Installed Binaries
===========================================================

  nano                      Simple, user-friendly text editor
  vim                       Vi IMproved text editor
  git                       Distributed version control system
  hydra                     Fast network logon cracker
  ...
```

**How it works:**
- Lists files from `$NATIVE_TOOLS/bin`
- Looks up descriptions from CATALOG
- Auto-paginates output

---

#### `qpkg info <binary>`
Show detailed information about a binary or package.

```bash
$ qpkg info hydra
Binary Info: hydra
Location: /accounts/1000/shared/misc/berrycore/bin/hydra
Category: net
Description: Fast network logon cracker (password auditing)

Size: 288K  Permissions: -rwxr-xr-x

Hydra v9.5

Manual: Not available
```

**Shows:**
- Location on disk
- Category and description
- File size and permissions
- Version (if available)
- Manual page availability

---

### Legacy Commands

#### `qpkg list`
List installed package files (`.zip` files in `packages/`).

```bash
$ qpkg list
Installed Packages
===========================================================
  1  ansiweather-1.15.0
  2  autoconf-2.69
  3  bash-5.0
  ...
```

---

#### `qpkg search <keyword>`
**Coming soon** - Will search available ports from repository.

---

## Port Repository Structure

### INDEX File Format

The `ports/INDEX` file tracks all available ports:

```
# Format: name|category|version|size|description
hydra|net|9.5|2.3M|Fast network logon cracker - password auditing tool
python|lang|3.11|45M|Python programming language with pip
postgresql|database|15.0|25M|Advanced relational database
```

**Fields:**
1. `name` - Package name (without category prefix)
2. `category` - Category (lang, database, dev, net, util, media, sys)
3. `version` - Version number
4. `size` - Approximate size (K/M/G)
5. `description` - One-line description

### Package Structure

All ports must follow the BerryCore structure:

```
port-package.zip
├── bin/           # Executables (required)
│   └── binary
├── lib/           # Libraries (if needed)
│   └── libname.so
├── share/         # Data files (if needed)
│   └── appdata/
├── include/       # Headers (if needed)
│   └── headers.h
└── doc/           # Documentation (optional)
    └── README.md
```

**Critical Rules:**
- ✅ No wrapper directories (extract directly to bin/, lib/, etc.)
- ✅ All binaries must be ARM QNX-compatible
- ✅ Set executable permissions on binaries
- ✅ Include required libraries (if not in BerryCore)
- ❌ No macOS metadata (`__MACOSX`, `.DS_Store`)

---

## CATALOG System

The CATALOG file (`berrycore/CATALOG`) provides metadata for `qpkg catalog` and `qpkg info`:

```
# Format: binary_name|category|description
hydra|net|Fast network logon cracker (password auditing)
nano|editor|Simple, user-friendly text editor
git|vcs|Distributed version control system
```

**When to add entries:**
- For major binaries in ports
- For tools users should discover
- When providing helpful descriptions

---

## Environment Integration

### Auto-configuration

When BerryCore loads, it sets up qpkg:

```bash
# In env.sh
PATH="$NATIVE_TOOLS/bin:$PATH"
export NATIVE_TOOLS

# Legacy aliases (backward compatibility)
alias bclist='qpkg catalog'
alias bcinfo='qpkg info'
alias bcbins='qpkg bins'
```

### Welcome Message

Users see qpkg commands on startup:

```
===========================================================
     BerryCore v0.7 - QNX Extended Userland
===========================================================

69 packages installed with 100+ binaries available

Browse available tools:
  qpkg catalog        List all binaries by category
  qpkg catalog -s     Search for specific tools
  qpkg info BINARY    Get info about a binary
  qpkg bins           See all installed binaries

Quick start: nano, vim, git, nmap, curl, linux, hydra
===========================================================
```

---

## Advanced Usage

### Installing Multiple Ports

```bash
# Install several ports
for port in hydra python postgresql; do
    qpkg install $port
done
```

### Checking Port Availability

```bash
# Check if a port exists before installing
qpkg ports | grep python
```

### Verifying Installation

```bash
# After installing, verify binaries
qpkg info hydra
which hydra
hydra -h
```

### Updating Port Metadata

When adding new ports to the repository:

1. Create port package: `category-name-version.zip`
2. Update `ports/INDEX` with entry
3. Optionally add to `berrycore/CATALOG`
4. Commit and push to GitHub
5. Users can immediately `qpkg install name`

---

## Troubleshooting

### Port not found

```bash
$ qpkg install myport
✗ Port 'myport' not found in repository

Available ports:
  hydra
  python
```

**Solution**: Check available ports with `qpkg ports`

---

### Download failed

```bash
✗ Download failed
```

**Common causes:**
1. No internet connection - check connectivity
2. GitHub is down - wait and retry
3. Port file doesn't exist - verify URL manually

**Manual workaround:**
```bash
# Download directly
cd $NATIVE_TOOLS
curl -L -O https://github.com/sw7ft/BerryCore/raw/main/ports/net-hydra-9.5.zip
unzip -o net-hydra-9.5.zip
chmod +x bin/*
```

---

### Binary doesn't run

```bash
$ hydra
sh: hydra: not found
```

**Solutions:**
1. Source environment: `. $NATIVE_TOOLS/env.sh`
2. Check permissions: `ls -la $NATIVE_TOOLS/bin/hydra`
3. Verify architecture: `file $NATIVE_TOOLS/bin/hydra`

---

### Missing libraries

```bash
$ hydra
error: libssl.so.3: cannot open shared object
```

**Solution**: Port should include required libraries in `lib/`
- Check if libraries exist: `ls $NATIVE_TOOLS/lib/libssl.so.3`
- Reinstall port: `qpkg install hydra`

---

## Development

### Creating a Port

See [PORTING_GUIDE.md](PORTING_GUIDE.md) for detailed instructions.

**Quick checklist:**
1. ✅ Compile for ARM QNX
2. ✅ Package with correct structure (no wrapper dir)
3. ✅ Add to `ports/INDEX`
4. ✅ Test installation: `qpkg install myport`
5. ✅ Verify binary runs
6. ✅ Submit pull request

### Testing Ports Locally

Before submitting:

```bash
# Test package structure
unzip -l category-name-version.zip
# Should show: bin/, lib/, etc. (no wrapper directory)

# Test installation
cd $NATIVE_TOOLS
unzip -o /path/to/category-name-version.zip
which myprogram
myprogram --version
```

---

## API Reference

### GitHub Raw URLs

Ports are accessed via GitHub raw content:

```
Base: https://raw.githubusercontent.com/sw7ft/BerryCore/main/

Files:
  ports/INDEX                        - Port list
  ports/net-hydra-9.5.zip           - Port package
  motd.txt                          - Message of the Day
```

### GitHub API

Updates use GitHub Releases API:

```
https://api.github.com/repos/sw7ft/BerryCore/releases/latest

Returns:
  {
    "tag_name": "v0.8",
    "body": "Release notes...",
    "assets": [...]
  }
```

---

## Version History

- **v0.1.0** - Initial qpkg implementation
  - `update` - BerryCore updates
  - `catalog` - Binary browser
  - `bins` - Binary lister
  - `info` - Binary information
  
- **v0.2.0** - Ports system
  - `ports` - List available ports
  - `install` - Install ports from repository
  - INDEX file format
  - Auto-pagination

---

## Resources

- **Repository**: https://github.com/sw7ft/BerryCore
- **Ports**: https://github.com/sw7ft/BerryCore/tree/main/ports
- **Releases**: https://github.com/sw7ft/BerryCore/releases
- **Wiki**: https://github.com/sw7ft/BerryCore/wiki

---

## Contributing

Want to contribute a port?

1. Fork the repository
2. Create your port following [PORTING_GUIDE.md](PORTING_GUIDE.md)
3. Add entry to `ports/INDEX`
4. Test thoroughly on BB10
5. Submit pull request

**Questions?**
- Open an issue: https://github.com/sw7ft/BerryCore/issues
- Discussion: https://github.com/sw7ft/BerryCore/discussions

---

**qpkg** - Making BlackBerry 10 More Capable, One Port at a Time 🚀

