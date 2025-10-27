# Installing BerryCore on BlackBerry 10

## Prerequisites
- BlackBerry 10 device (OS 10.3.1 or later recommended)
- Terminal app (Term48 or Term49)
- Internet connection for downloading files

## Installation Steps

### 1. Download Files
Download both files to your device:
- **berrycore.zip** - Main package (268 MB)
- **install.sh** - Installation script

Save them to: `/accounts/1000/shared/documents/`

**Option A: Using wget (if available):**
```bash
cd /accounts/1000/shared/documents
wget https://github.com/sw7ft/BerryCore/releases/download/v0.6/berrycore.zip
wget https://github.com/sw7ft/BerryCore/releases/download/v0.6/install.sh
```

**Option B: Download via browser:**
- Visit: https://github.com/sw7ft/BerryCore/releases/latest
- Download both files to your device
- Move them to Documents folder

### 2. Run Installation
Open your Terminal app (Term48/Term49) and run:

```bash
cd /accounts/1000/shared/documents
sh install.sh
```

### 3. Follow Prompts
- Choose installation directory (default: `berrycore`) or enter custom name
- Wait for extraction and setup to complete (~1-2 minutes)
- Installation will configure your shell profile automatically

### 4. Restart Terminal
Close and reopen your Terminal app to load BerryCore environment.

## Verification

After reopening Terminal, you should see:
```
===========================================================
     BerryCore v0.6 - QNX Extended Userland
===========================================================
```

Test it works:
```bash
bclist          # Browse available tools
nano --version  # Test nano editor
git --version   # Test git
```

## What Gets Installed

- **Location:** `/accounts/1000/shared/misc/berrycore` (or your custom path)
- **69 packages** with 100+ command-line tools
- **Profile configuration** automatically added to `~/.profile`
- **Terminal customization** (font size and dark theme)

## Troubleshooting

**If commands aren't found after install:**
```bash
source ~/.profile
```

**To manually check environment:**
```bash
echo $NATIVE_TOOLS
# Should show: /accounts/1000/shared/misc/berrycore
```

**For help:**
- Visit: https://github.com/sw7ft/BerryCore/issues
- Check: `bclist` for available tools
- Run: `bcinfo <command>` for specific tool info

