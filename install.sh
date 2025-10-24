#!/bin/sh

echo ""
echo "==========================================================="
echo "     BerryCore v0.6 Installation"
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

# versions up to 0.4 were slowing down the device (see #54)
D=/accounts/1000/shared/documents/clitools
if [ -d $D ]; then
 if [ "x$1" == "x-f" ]; then
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
    echo "if you want to bypass this check, use install -f"
    echo 
    echo
    exit 0
 fi
fi
   
D=$INSTALL_DIR
mkdir -p $D;
mv berrycore.zip $D
cd $D
touch .nomedia .noindex
unzip -o berrycore.zip
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
        # In upgrade mode, check if package is already installed
        # We check if the marker file exists (pbpkgadd creates .pkg_installed_<name>)
        # Or if key binaries/libs from the package exist
        pkg_base=$(basename "$pkg" .zip)
        
        # Simple check: if any files from this package exist, skip it
        # This is a heuristic - we assume if the package was installed before, it's still there
        SKIP_PKG=0
        
        # Check if this is a new package by looking at modification time vs env.sh
        if [ -f "env.sh" ]; then
            ENV_TIME=$(stat -f %m env.sh 2>/dev/null || stat -c %Y env.sh 2>/dev/null || echo 0)
            PKG_TIME=$(stat -f %m "$pkg" 2>/dev/null || stat -c %Y "$pkg" 2>/dev/null || echo 0)
            
            # If package is older than env.sh, it's likely already installed
            if [ $PKG_TIME -lt $ENV_TIME ]; then
                SKIP_PKG=1
            fi
        fi
        
        if [ $SKIP_PKG -eq 1 ]; then
            echo "  ⏩ $pkg_name (already installed)"
            SKIPPED_PKGS=$((SKIPPED_PKGS + 1))
        else
            echo "  📦 $pkg_name (new package)"
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

if [ ! -e "$HOME/.profile" ]; then
  # Update the path in sample_profile before copying
  sed "s|/accounts/1000/shared/misc/berrycore|$PWD|g" sample_profile > "$HOME/.profile"
  
  # Add MOTD configuration
  echo "" >> "$HOME/.profile"
  echo "# BerryCore Message of the Day" >> "$HOME/.profile"
  echo "export BERRYCORE_MOTD_URL=\"https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt\"" >> "$HOME/.profile"
  echo "export BERRYCORE_MOTD_ENABLED=1" >> "$HOME/.profile"
  
  echo "Created $HOME/.profile"
else
  echo "You already have a .profile."
  echo "You can set up your paths by sourcing $PWD/env.sh"
  echo "See $PWD/sample_profile for a snippet that does this"
  echo ""
  echo "To manually add BerryCore to your profile, add this line:"
  echo "  [ -e \"$PWD/env.sh\" ] && . \"$PWD/env.sh\""
  echo ""
  echo "To enable MOTD, add these lines:"
  echo "  export BERRYCORE_MOTD_URL=\"https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt\""
  echo "  export BERRYCORE_MOTD_ENABLED=1"
fi

# Update env.sh with actual installation path
sed -i.bak "s|NATIVE_TOOLS=\"/accounts/1000/shared/misc/berrycore\"|NATIVE_TOOLS=\"$PWD\"|g" env.sh
rm -f env.sh.bak

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
