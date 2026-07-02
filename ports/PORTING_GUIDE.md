# BerryCore Porting Guide

This guide explains how to create, package, and submit ports for BerryCore.

## Prerequisites

- BerryCore v0.7 or later installed
- Access to QNX/BB10 development environment
- Basic understanding of package structure
- Tested binaries compiled for ARM QNX

## Port Package Structure

All ports must follow the standard BerryCore structure:

```
your-package/
├── bin/                 # Executables
│   └── yourprogram
├── lib/                 # Libraries (if needed)
│   └── libyour.so.1
├── include/            # Headers (if needed)
│   └── your/
├── share/              # Data files
│   └── yourprogram/
└── doc/                # Documentation (optional)
    └── README.md
```

## Step 1: Compile for QNX ARM

Ensure your binaries are compiled for:
- **Architecture**: ARM (armle-v7)
- **OS**: QNX 6.5+ / BB10
- **ABI**: Compatible with system libraries

Test with:
```bash
file bin/yourprogram
# Should show: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV)
```

## Step 2: Organize Package

Create directory structure:
```bash
mkdir -p myport/bin myport/lib myport/share/myport
cp compiled_binary myport/bin/
cp *.so* myport/lib/ 2>/dev/null || true
cp data_files myport/share/myport/
chmod +x myport/bin/*
```

## Step 3: Test Installation

Test manually first:
```bash
cd myport
zip -r ../category-name-version.zip .
cd $NATIVE_TOOLS
unzip -o /path/to/category-name-version.zip
# Test the binary
```

## Step 4: Create Package

Package with proper naming:
```bash
# Format: category-name-version.zip
# Examples:
cd your-package
zip -r ../lang-python-3.11.zip .
zip -r ../db-postgresql-15.zip .
zip -r ../util-htop-3.3.zip .
```

**Important**: Package from WITHIN the directory, not the parent!

### Converting tar/tar.gz to port zip

If you have a `.tar` or `.tar.gz` (e.g. from a pre-built binary):

```bash
# Extract
tar xf your-package.tar   # or: tar xzf your-package.tar.gz

# Restructure: remove wrapper dir, use bin/lib/share at root
cd your-package-dir
mkdir -p ../port-pkg/bin ../port-pkg/lib ../port-pkg/doc
cp node node.bin npm *.so* ../port-pkg/bin/   # example
cp -r lib/node_modules ../port-pkg/bin/lib/   # if paths are relative to bin
cp README.md ../port-pkg/doc/

# Package
cd ../port-pkg
zip -r ../lang-yourname-version.zip .
```

Ensure wrapper scripts use `$(dirname "$0")` for paths so they work when installed to `berrycore/bin/`.

## Step 5: Add to INDEX

Add an entry to `ports/INDEX`:

```
# Format: name|category|version|size|description
python|lang|3.11|45M|Python programming language with pip and standard library
postgresql|database|15.0|25M|Advanced open source relational database
htop|util|3.3|500K|Interactive process viewer for Unix systems
```

Fields:
- **name**: Package name (without category prefix)
- **category**: Category (lang, database, dev, net, util, media, sys)
- **version**: Version number
- **size**: Approximate size (K/M/G)
- **description**: One-line description

## Custom Install Paths

Most ports extract to `berrycore/` (NATIVE_TOOLS). For ports that need a different location, add a case in qpkg's `cmd_install`:

```bash
# Example: android-apps installs to misc/android-apps/
case "$PORT_NAME" in
    android-apps)
        INSTALL_DIR="/accounts/1000/shared/misc"
        ;;
esac
```

The zip should have the target directory at root (e.g. `android-apps/`) so extraction produces the correct path.

## Step 6: Update CATALOG (Optional)

If your port includes major binaries, add them to `berrycore/CATALOG`:

```
# Programming Languages
python3|lang|Python 3.11 interpreter
pip3|lang|Python package installer

# Databases  
psql|database|PostgreSQL interactive terminal
```

## Step 7: Test with qpkg

Test installation via qpkg:
```bash
# Copy to ports directory
cp category-name-version.zip ~/path/to/BerryCore/ports/

# Test install (local)
qpkg install name

# Verify
which yourprogram
yourprogram --version
```

## Step 8: Submit to Repository

1. Fork the BerryCore repository
2. Add your port to `ports/` directory
3. Update `ports/INDEX` with your entry
4. Create a pull request with:
   - Port package (.zip)
   - INDEX entry
   - Brief description
   - Testing notes

## Best Practices

### ✅ DO:
- Test thoroughly on BB10 device
- Include all dependencies in package
- Use standard directory structure
- Add helpful documentation
- Check for library conflicts
- Verify executable permissions

### ❌ DON'T:
- Include macOS metadata (`__MACOSX`, `.DS_Store`)
- Use absolute paths in scripts
- Assume specific BerryCore installation location
- Package with wrapper directories
- Include compiled debug symbols (strip binaries)

## Dependency Management

If your port requires other ports:
```bash
# Add to package README or description
Requires: openssl-3.3.2, zlib-1.2.11
```

## Library Considerations

If providing libraries:
- Use versioned symlinks (`libfoo.so.1 -> libfoo.so.1.2.3`)
- Don't conflict with system libraries
- Document ABI requirements

## Environment Variables

If your port needs environment variables, document them:
```bash
# Example in package README
export PYTHON_HOME=$NATIVE_TOOLS
export PYTHONPATH=$NATIVE_TOOLS/lib/python3.11
```

## Example: Creating a Simple Port

```bash
# 1. Prepare files
mkdir -p htop-package/bin
cp /path/to/compiled/htop htop-package/bin/
chmod +x htop-package/bin/htop

# 2. Package it
cd htop-package
zip -r ../util-htop-3.3.zip .
cd ..

# 3. Verify structure
unzip -l util-htop-3.3.zip
# Should show: bin/htop (no wrapper directory)

# 4. Add to INDEX
echo "htop|util|3.3|500K|Interactive process viewer" >> ports/INDEX

# 5. Test
qpkg install htop
```

## Troubleshooting

### Package won't install
- Check structure: `unzip -l your-package.zip`
- Verify no wrapper directory
- Check file permissions

### Binary won't run
- Test with `file bin/yourprogram`
- Check `ldd bin/yourprogram` for missing libs
- Verify architecture matches ARM

### Library conflicts
- Use `ldd` to check dependencies
- Don't replace system libraries
- Use versioned library names

## Port Dependencies

Some ports require others. Check before installing:

| Port | Requires |
|------|----------|
| berrypy | python3 |
| berrysnip | python3 |
| voiceagent | python3 |
| qnxdesktop | python3 |
| rocketchat | python3 |
| maps | python3, `requests` (`python3 -m pip install requests`) |
| youtube | python3, `pytube` (`python3 -m pip install pytube`; optional: `youtube-search-python`) |
| telegram | python3, `telethon`, `requests` (`python3 -m pip install telethon requests`) |

## BB10 Tools Deployment

BerryCore includes a native C HTTP server for the web tools (dashboard, drawing board, QNX Chat, etc.). These are deployed with the base package:

| Path | Contents |
|------|----------|
| `misc/bin/tools` | ARM ELF32 HTTP server (port 8765) |
| `misc/share/tools/` | dashboard, drawing-board, markdown-editor, code-editor, compass, linux-chat, virtual-keyboard |

**Run on device:** (starts in background)
```sh
tools
# or: /accounts/1000/shared/misc/berrycore/bin/tools
```

Then open: `http://localhost:8765/dashboard/`

**Note:** The tools binary expects `/accounts/1000/shared/misc/share/tools`. When installed via `qpkg install bb-tools`, the port includes a wrapper that copies the files to that path on first run.

The server has no Python dependency. Source tools live in repo `tools/`; the bb10-root deploy uses `bb10-root/include/accounts/1000/shared/misc/share/tools/`.

## Questions?

- Open an issue: https://github.com/sw7ft/BerryCore/issues
- Join the discussion: https://github.com/sw7ft/BerryCore/discussions

---

**Happy Porting!** 🚀

