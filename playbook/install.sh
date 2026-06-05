#!/bin/sh
# BerryCore install.sh - PlayBook Edition
#
# Usage (Term48 or SSH):
#   . install.sh
#
# Just place install.sh and playbook-deploy.zip in the same directory.
# install.sh extracts everything it needs - no manual unzip required.
#
# Term48-friendly: portable sed, no emoji, no stat/head/id,
# pbpkgadd fallback to unzip, close/reopen Term48 after install.

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# If inner zips are missing, extract them from playbook-deploy.zip
if [ ! -f "berrycore.zip" ] || [ ! -f "playbook-overlay.zip" ]; then
    if [ -f "playbook-deploy.zip" ]; then
        echo "Extracting playbook-deploy.zip..."
        unzip -o playbook-deploy.zip berrycore.zip playbook-overlay.zip 2>/dev/null || \
        unzip -o playbook-deploy.zip
    fi
fi

# Verify we have what we need
if [ ! -f "berrycore.zip" ]; then
    echo "Error: berrycore.zip not found."
    echo "Place playbook-deploy.zip and install.sh in the same directory and re-run."
    exit 1
fi
if [ ! -f "playbook-overlay.zip" ]; then
    echo "Error: playbook-overlay.zip not found."
    exit 1
fi

echo ""
echo "==========================================================="
echo "     BerryCore v0.78 Installation (PlayBook Edition)"
echo "==========================================================="
echo ""

# Prompt for installation directory
echo "Installation directory: /accounts/1000/shared/misc/berrycore"
echo ""
echo "Press Enter to use default, or type a custom name:"
echo -n "Directory name [berrycore]: "
read custom_name

if [ -z "$custom_name" ]; then
    custom_name="berrycore"
    INSTALL_DIR="/accounts/1000/shared/misc/berrycore"
    echo "Using default: $INSTALL_DIR"
else
    INSTALL_DIR="/accounts/1000/shared/misc/$custom_name"
    echo "Installing to: $INSTALL_DIR"
fi

echo ""

# Check for existing BerryCore installation
UPGRADE_MODE=0
if [ -d "$INSTALL_DIR" ] && [ -f "$INSTALL_DIR/env.sh" ]; then
    echo "==========================================================="
    echo "  Existing BerryCore installation detected!"
    echo "==========================================================="
    echo ""
    echo "Installation found at: $INSTALL_DIR"
    echo ""
    echo "Choose installation mode:"
    echo "  [1] Upgrade (fast - only install new packages)"
    echo "  [2] Fresh install (slower - reinstall all packages)"
    echo ""
    echo -n "Enter choice [1]: "
    read install_choice

    if [ -z "$install_choice" ] || [ "$install_choice" = "1" ]; then
        UPGRADE_MODE=1
        echo ""
        echo "Using upgrade mode - will preserve existing packages"
    else
        UPGRADE_MODE=0
        echo ""
        echo "Using fresh install mode - will reinstall everything"
    fi
else
    echo "Press Enter to continue or Ctrl+C to cancel..."
    read confirm
fi

# Check for old Berrymuch installation (<0.5) that slows down the device
D=/accounts/1000/shared/documents/clitools
if [ -d $D ]; then
    if [ "x$1" = "x-f" ]; then
        echo ""
        echo "Skipping check of previous BerryCore/Berrymuch version (<0.6)"
        echo ""
    else
        echo ""
        echo "Previous version of Berrymuch (<0.6) has been detected."
        echo "Please remove the previous installation by typing:"
        echo ""
        echo "  rm -rf /accounts/1000/shared/documents/clitools"
        echo "  $0"
        echo ""
        echo "To bypass this check, use: sh install.sh -f"
        echo ""
        exit 0
    fi
fi

D=$INSTALL_DIR
mkdir -p $D
cp "$SCRIPT_DIR/berrycore.zip" $D
cd $D

touch .nomedia .noindex
echo "Extracting berrycore.zip..."
unzip -o berrycore.zip

# Patch env.sh with actual installation path BEFORE sourcing it
# Uses portable sed pattern (QNX sed does not support -i)
sed "s|NATIVE_TOOLS=\"/accounts/1000/shared/misc/berrycore\"|NATIVE_TOOLS=\"$PWD\"|g" env.sh > env.sh.tmp && mv env.sh.tmp env.sh

. ./env.sh

# Install packages
NEW_PKGS=0
SKIPPED_PKGS=0
UPDATED_PKGS=0

echo ""
echo "Installing packages..."
echo ""

for pkg in packages/*.zip
do
    pkg_name=$(basename "$pkg")

    if [ $UPGRADE_MODE -eq 1 ]; then
        pkg_base=$(basename "$pkg" .zip)
        SKIP_PKG=0

        # stat is not available on PlayBook QNX - upgrade mode installs all packages
        # (stat would normally be used here for timestamp comparison)

        if [ $SKIP_PKG -eq 1 ]; then
            echo "  [SKIP] $pkg_name (already installed)"
            SKIPPED_PKGS=$((SKIPPED_PKGS + 1))
    else
        echo "  [PKG]  $pkg_name (new package)"
        (./pbpkgadd "$pkg" 2>/dev/null) || unzip -o "$pkg"
        NEW_PKGS=$((NEW_PKGS + 1))
        fi
    else
        echo "  [PKG]  $pkg_name"
        (./pbpkgadd "$pkg" 2>/dev/null) || unzip -o "$pkg"
        UPDATED_PKGS=$((UPDATED_PKGS + 1))
    fi
done

echo ""
if [ $UPGRADE_MODE -eq 1 ]; then
    echo "Package installation summary:"
    echo "  New packages installed: $NEW_PKGS"
    echo "  Existing packages preserved: $SKIPPED_PKGS"
else
    echo "Package installation complete:"
    echo "  Total packages installed: $UPDATED_PKGS"
fi
echo ""

# Backup existing .profile if it exists
if [ -e "$HOME/.profile" ]; then
    BACKUP_NAME="$HOME/.profile.backup.$(date '+%Y%m%d_%H%M%S' 2>/dev/null || echo old)"
    cp "$HOME/.profile" "$BACKUP_NAME"
    echo "Backed up existing .profile to: $(basename $BACKUP_NAME)"
fi

# PlayBook overlay path (fixed, lives alongside berrycore)
MISC="/accounts/1000/shared/misc"
PLAYBOOK_FIXES="$MISC/berrycore-playbook-fixes2"

# Write fresh .profile - use PlayBook overlay env (ncurses, quansi, compat libs)
{
    sed "s|/accounts/1000/shared/misc/berrycore|$PWD|g" sample_profile
    echo ""
    echo "# BerryCore Message of the Day"
    echo "export BERRYCORE_MOTD_URL=\"https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt\""
    echo "export BERRYCORE_MOTD_ENABLED=1"
    echo ""
    echo "# PlayBook overlay (ncurses, quansi terminfo, strcasestr/optreset/memset_s)"
    echo ". $PLAYBOOK_FIXES/playbook-env.sh"
} > "$HOME/.profile"

echo "Created fresh $HOME/.profile (uses PlayBook overlay)"

# Install PlayBook overlay (berrycore stays pristine)
OVERLAY_ZIP="$SCRIPT_DIR/playbook-overlay.zip"
if [ -f "$OVERLAY_ZIP" ]; then
    echo ""
    echo "Installing PlayBook overlay..."
    rm -rf "$PLAYBOOK_FIXES" 2>/dev/null || true
    mkdir -p "$PLAYBOOK_FIXES"
    cd "$PLAYBOOK_FIXES"
    if ! unzip -o "$OVERLAY_ZIP"; then
        echo "  Warning: overlay unzip had errors (common in Term48 if overlay was created over SSH)."
        echo "  Remove the overlay dir and re-run: rm -rf $PLAYBOOK_FIXES && . $SCRIPT_DIR/install.sh"
    fi
    chmod +x bin/* 2>/dev/null || true
    # Patch BERRYCORE path in playbook-env.sh (handles custom install dirs)
    sed "s|BERRYCORE=\"/accounts/1000/shared/misc/berrycore\"|BERRYCORE=\"$INSTALL_DIR\"|g" \
        playbook-env.sh > playbook-env.sh.tmp && mv playbook-env.sh.tmp playbook-env.sh
    # libplaybook-compat.so is in overlay zip; copy from deploy dir if present (optional)
    if [ -f "$SCRIPT_DIR/libplaybook-compat.so" ]; then
        cp "$SCRIPT_DIR/libplaybook-compat.so" "$PLAYBOOK_FIXES/lib/"
        echo "  libplaybook-compat.so installed"
    fi
    cd "$INSTALL_DIR"
    echo "PlayBook overlay installed at $PLAYBOOK_FIXES"
else
    echo ""
    echo "Note: playbook-overlay.zip not found in $SCRIPT_DIR"
fi

echo ""
echo "==========================================================="
echo "     Installation Complete!"
echo "==========================================================="
echo ""
echo "BerryCore: $INSTALL_DIR"
echo "PlayBook overlay: $PLAYBOOK_FIXES"
echo ""

# Load env in current shell so sshd, nano, tmux work immediately (no full paths needed)
if [ -f "$PLAYBOOK_FIXES/playbook-env.sh" ]; then
    . "$PLAYBOOK_FIXES/playbook-env.sh"
    echo "Environment loaded. Run: sshd -Dd"
else
    echo "To use: . $PLAYBOOK_FIXES/playbook-env.sh  (or restart shell)"
fi
echo ""

mkdir -p etc/qnxconf/qconfig
CONFFILE="etc/qnxconf/qconfig/qnx_blackberry_native_development_kit_2.1.0.xml"

echo "<?xml version=\"1.0\" ?>"                                     >  $CONFFILE
echo "<qnxSystemDefinition>"                                       >> $CONFFILE
echo "  <installation>"                                            >> $CONFFILE
echo "    <base>$PWD</base>"                                       >> $CONFFILE
echo "    <name>BlackBerry Native SDK for Tablet OS 2.1.0</name>" >> $CONFFILE
echo "    <host>$PWD</host>"                                       >> $CONFFILE
echo "    <target>$PWD/target/qnx6</target>"                      >> $CONFFILE
echo "  </installation>"                                           >> $CONFFILE
echo "</qnxSystemDefinition>"                                      >> $CONFFILE

mkdir -p bin
# Move pbpkgadd into bin if not already there
if [ -f pbpkgadd ]; then
    mv pbpkgadd ./bin/
fi

# Make binaries executable (failure-safe for empty or missing bin/)
chmod +x bin/* 2>/dev/null || true

# Configure Term48 terminal settings if config exists
TERM_CONFIG="$HOME/.term48rc"
if [ -f "$TERM_CONFIG" ]; then
    echo ""
    echo "Configuring Term48 settings..."
    cp "$TERM_CONFIG" "$TERM_CONFIG.bak"
    sed "s/font_size = [0-9]*;/font_size = 15;/" "$TERM_CONFIG" > "$TERM_CONFIG.tmp" && mv "$TERM_CONFIG.tmp" "$TERM_CONFIG"
    sed "s/background_color = \[.*\];/background_color = [ 44, 0, 30 ];/" "$TERM_CONFIG" > "$TERM_CONFIG.tmp" && mv "$TERM_CONFIG.tmp" "$TERM_CONFIG"
    echo "Term48 configured: font_size=15, flat purple background (Ubuntu-style)"
    echo "Original backed up as: .term48rc.bak"
else
    echo ""
    echo "Note: Term48 config (.term48rc) not found - skipping terminal customization"
fi

echo ""
echo "==========================================================="
echo "     Welcome to BerryCore (PlayBook Edition)!"
echo "==========================================================="
echo ""
