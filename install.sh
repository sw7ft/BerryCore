#!/bin/sh

# Parse options (used by qpkg update: install.sh --upgrade -y --dir "$NATIVE_TOOLS")
UPGRADE_MODE=0
YES_MODE=0
FORCE_CLITOOLS=0
INSTALL_DIR=""
custom_name=""

while [ $# -gt 0 ]; do
    case "$1" in
        --upgrade|-u)
            UPGRADE_MODE=1
            shift
            ;;
        --fresh)
            UPGRADE_MODE=0
            shift
            ;;
        -y|--yes)
            YES_MODE=1
            shift
            ;;
        -f)
            FORCE_CLITOOLS=1
            shift
            ;;
        --dir)
            INSTALL_DIR="$2"
            shift 2
            ;;
        *)
            shift
            ;;
    esac
done

if [ -z "$INSTALL_DIR" ] && [ -n "$BERRYCORE_INSTALL_DIR" ]; then
    INSTALL_DIR="$BERRYCORE_INSTALL_DIR"
fi
if [ -z "$INSTALL_DIR" ] && [ -n "$NATIVE_TOOLS" ] && [ "$UPGRADE_MODE" -eq 1 ]; then
    INSTALL_DIR="$NATIVE_TOOLS"
fi

BC_VERSION=$(unzip -p berrycore.zip VERSION 2>/dev/null || echo "unknown")

echo ""
echo "==========================================================="
echo "     BerryCore v${BC_VERSION} Installation"
echo "==========================================================="
echo ""

if [ -z "$INSTALL_DIR" ]; then
    echo "Installation directory: /accounts/1000/shared/misc/berrycore"
    echo ""
    if [ "$YES_MODE" -eq 1 ]; then
        custom_name="berrycore"
        INSTALL_DIR="/accounts/1000/shared/misc/berrycore"
        echo "Using default: $INSTALL_DIR"
    else
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
    fi
else
    echo "Installation directory: $INSTALL_DIR"
fi

echo ""

# Check for existing BerryCore installation
if [ -d "$INSTALL_DIR" ] && [ -f "$INSTALL_DIR/env.sh" ]; then
    if [ "$UPGRADE_MODE" -eq 0 ] && [ "$YES_MODE" -eq 0 ]; then
        echo "==========================================================="
        echo "  Existing BerryCore installation detected!"
        echo "==========================================================="
        echo ""
        echo "Installation found at: $INSTALL_DIR"
        echo ""
        echo "Choose installation mode:"
        echo "  [1] Upgrade (fast - only install new/changed packages)"
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
    elif [ "$UPGRADE_MODE" -eq 1 ]; then
        echo "Upgrade mode — updating $INSTALL_DIR"
    fi
else
    if [ "$YES_MODE" -eq 0 ]; then
        echo "Press Enter to continue or Ctrl+C to cancel..."
        read confirm
    fi
fi

# versions up to 0.4 were slowing down the device (see #54)
D=/accounts/1000/shared/documents/clitools
if [ -d $D ]; then
 if [ "$FORCE_CLITOOLS" -eq 1 ]; then
    echo 
    echo "skipping check of previous BerryCore/Berrymuch version (<0.6)"
    echo 
 else
    echo
    echo "previous version of Berrymuch (<0.6) has been detected"
    echo "please remove the previous installation by typing"
    echo
    echo "  rm -rf /accounts/1000/shared/documents/clitools"
    echo "  $0"
    echo 
    echo "if you want to bypass this check, use install.sh -f"
    echo 
    echo
    exit 0
 fi
fi
   
D=$INSTALL_DIR
mkdir -p $D;
cp berrycore.zip $D
cd $D

# Save old env.sh timestamp for upgrade detection (fallback)
OLD_ENV_TIME=0
if [ -f "env.sh" ]; then
    OLD_ENV_TIME=$(stat -f %m env.sh 2>/dev/null || stat -c %Y env.sh 2>/dev/null || echo 0)
fi

STAMP_DIR=".berrycore_pkg_stamps"
mkdir -p "$STAMP_DIR" 2>/dev/null

package_mtime() {
    _pkg="$1"
    _mtime=$(stat -f %m "$_pkg" 2>/dev/null || stat -c %Y "$_pkg" 2>/dev/null || echo 0)
    if [ "$_mtime" = "0" ] && command -v python3 >/dev/null 2>&1; then
        _mtime=$(python3 -c "import os; print(int(os.path.getmtime('$_pkg')))" 2>/dev/null || echo 0)
    fi
    echo "$_mtime"
}

should_skip_package() {
    _pkg="$1"
    _base="$2"
    _stamp="$STAMP_DIR/$_base"

    if [ ! -f "$_stamp" ]; then
        return 1
    fi

    _installed=$(cat "$_stamp" 2>/dev/null)
    _pkgtime=$(package_mtime "$_pkg")

    if [ -n "$_installed" ] && [ -n "$_pkgtime" ] && [ "$_pkgtime" -le "$_installed" ]; then
        return 0
    fi

    if [ -n "$_installed" ] && [ "$_pkgtime" = "0" ] && [ $OLD_ENV_TIME -gt 0 ]; then
        if [ $OLD_ENV_TIME -gt "$_installed" ]; then
            return 1
        fi
        return 0
    fi

    return 1
}

touch .nomedia .noindex
unzip -o berrycore.zip
# Update env.sh with actual installation path BEFORE sourcing it
# so pbpkgadd installs packages to the correct directory
sed -i.bak "s|NATIVE_TOOLS=\"/accounts/1000/shared/misc/berrycore\"|NATIVE_TOOLS=\"$PWD\"|g" env.sh
rm -f env.sh.bak
# Note: berrycore.zip is kept in both locations (original and installation directory)
. ./env.sh

# zsh and other tools have hardcoded /accounts/1000/shared/misc/clitools paths
# Create symlink so they find the actual install directory
if [ -d /accounts/1000/shared/misc ] && { [ ! -e /accounts/1000/shared/misc/clitools ] || [ -L /accounts/1000/shared/misc/clitools ]; }; then
    ln -sf "$PWD" /accounts/1000/shared/misc/clitools
    echo "Created clitools -> $PWD symlink (for zsh and legacy tools)"
fi

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

        if should_skip_package "$pkg" "$pkg_base"; then
            SKIP_PKG=1
        fi

        if [ $SKIP_PKG -eq 1 ]; then
            echo "  ⏩ $pkg_name (already installed)"
            SKIPPED_PKGS=$((SKIPPED_PKGS + 1))
        else
            echo "  📦 $pkg_name (new or updated)"
            ./pbpkgadd "$pkg"
            NEW_PKGS=$((NEW_PKGS + 1))
        fi
    else
        # Fresh install mode - install everything
        echo "  📦 $pkg_name"
        ./pbpkgadd "$pkg"
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

# Move bundled bcllm from berrycore tree to misc/bcllm (same layout as qpkg install)
relocate_bcllm() {
    MISC_ROOT="/accounts/1000/shared/misc"
    MISC_BCLLM="$MISC_ROOT/bcllm"
    NT="$PWD"

    if [ -d "$NT/bcllm" ] && [ "$NT/bcllm" != "$MISC_BCLLM" ]; then
        mkdir -p "$MISC_ROOT"
        rm -rf "$MISC_BCLLM"
        mv "$NT/bcllm" "$MISC_BCLLM"
        echo "BerryCore AI moved to $MISC_BCLLM"
    fi

    if [ ! -d "$MISC_BCLLM/bin" ]; then
        return 0
    fi

    chmod +x "$MISC_BCLLM/bin/"* 2>/dev/null
    mkdir -p "$MISC_BCLLM/models" "$MISC_BCLLM/var" 2>/dev/null
    ln -sf bcllm-ai "$MISC_BCLLM/bin/ai" 2>/dev/null
    ln -sf bcllm-ai "$MISC_BCLLM/bin/AI" 2>/dev/null

    if [ -x "$MISC_BCLLM/setup-ai.sh" ]; then
        export NATIVE_TOOLS="$NT"
        sh "$MISC_BCLLM/setup-ai.sh"
    else
        mkdir -p "$NT/bin"
        if [ -f "$MISC_BCLLM/bin/berrycore-ai" ]; then
            cp "$MISC_BCLLM/bin/berrycore-ai" "$NT/bin/ai"
            chmod +x "$NT/bin/ai"
            ln -sf ai "$NT/bin/AI" 2>/dev/null
            ln -sf "$MISC_BCLLM/bin/bcllm" "$NT/bin/bcllm" 2>/dev/null
        fi
        echo "Linked ai into $NT/bin (run setup-ai.sh for .profile PATH)"
    fi
}

relocate_bcllm

# Backup existing .profile if it exists
if [ -e "$HOME/.profile" ]; then
  BACKUP_NAME="$HOME/.profile.backup.$(date +%Y%m%d_%H%M%S)"
  cp "$HOME/.profile" "$BACKUP_NAME"
  echo "Backed up existing .profile to: $(basename $BACKUP_NAME)"
fi

# Always create fresh .profile to prevent errors from old configs
sed "s|/accounts/1000/shared/misc/berrycore|$PWD|g" sample_profile > "$HOME/.profile"

# Add MOTD configuration
echo "" >> "$HOME/.profile"
echo "# BerryCore Message of the Day" >> "$HOME/.profile"
echo "export BERRYCORE_MOTD_URL=\"https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt\"" >> "$HOME/.profile"
echo "export BERRYCORE_MOTD_ENABLED=1" >> "$HOME/.profile"

echo "Created fresh $HOME/.profile"

echo ""
echo "==========================================================="
echo "     Installation Complete!"
echo "==========================================================="
echo ""
echo "Installation directory: $PWD"
echo ""
echo "To use BerryCore, either:"
echo "  1. Start a new shell (if .profile was created/updated)"
echo "  2. Run: source $PWD/env.sh"
echo ""

mkdir -p etc/qnxconf/qconfig
CONFFILE="etc/qnxconf/qconfig/qnx_blackberry_native_development_kit_2.1.0.xml"

echo "<?xml version="1.0" ?>"                                     >  $CONFFILE
echo "<qnxSystemDefinition>"                                      >> $CONFFILE
echo "  <installation>"                                           >> $CONFFILE
echo "    <base>$PWD</base>"                                      >> $CONFFILE
echo "    <name>BlackBerry Native SDK for Tablet OS 2.1.0</name>" >> $CONFFILE
echo "    <host>$PWD</host>"                                      >> $CONFFILE
echo "    <target>$PWD/target/qnx6</target>"                      >> $CONFFILE
echo "  </installation>"                                          >> $CONFFILE
echo "</qnxSystemDefinition>"                                     >> $CONFFILE

mkdir -p bin
mv pbpkgadd ./bin

# Ensure all binaries have executable permissions
chmod +x bin/*

# Configure Terminal settings for better visibility
TERM_CONFIG="$HOME/.term48rc"
if [ -f "$TERM_CONFIG" ]; then
    echo ""
    echo "Configuring Terminal settings..."
    
    # Backup original config
    cp "$TERM_CONFIG" "$TERM_CONFIG.bak"
    
    # Update font size to 40
    sed -i "s/font_size = [0-9]*;/font_size = 40;/" "$TERM_CONFIG"
    
    # Update background color to dark purple [30, 0, 30]
    sed -i "s/background_color = \[.*\];/background_color = [ 30, 0, 30 ];/" "$TERM_CONFIG"
    
    echo "Terminal configured: font_size=40, dark background"
    echo "Original backed up as: .term48rc.bak"
else
    echo ""
    echo "Note: Terminal config (.term48rc) not found, skipping terminal customization"
fi

echo ""
echo "==========================================================="
echo "     Welcome to BerryCore!"
echo "==========================================================="
echo ""
