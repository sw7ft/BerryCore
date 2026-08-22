NATIVE_TOOLS="/accounts/1000/shared/misc/berrycore"
QNX_TARGET=$NATIVE_TOOLS/target_10_3_1_995/qnx6
export NATIVE_TOOLS QNX_TARGET

PATH="$NATIVE_TOOLS/bin:$NATIVE_TOOLS/sbin:$PATH"
# Put BerryCore libs AFTER system libs to avoid conflicts with system binaries
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$QNX_TARGET/armle-v7/usr/lib:$NATIVE_TOOLS/lib"
export PATH LD_LIBRARY_PATH
export TIGRC="$NATIVE_TOOLS/etc/tigrc"
export VIMRUNTIME="$NATIVE_TOOLS/share/vim/vim91"

#MAKEFLAGS="-I$NATIVE_TOOLS/include"
MAKEFLAGS="-I$QNX_TARGET/usr/include"
export MAKEFLAGS

QNX_HOST="$NATIVE_TOOLS"
#QNX_CONFIGURATION="$NATIVE_TOOLS/etc/qnxconf"
QCONF_OVERRIDE=$NATIVE_TOOLS/qconf-override.mk
export QNX_HOST QCONF_OVERRIDE

GROFF_FONT_PATH="$NATIVE_TOOLS/share/groff/1.19.2/font:$NATIVE_TOOLS/share/groff/site-font"
GROFF_TMAC_PATH="$NATIVE_TOOLS/share/groff/1.19.2/tmac:$NATIVE_TOOLS/share/groff/site-tmac"
export GROFF_FONT_PATH GROFF_TMAC_PATH

MAGIC="$NATIVE_TOOLS/share/misc/magic.mgc"
export MAGIC

MANPATH="$NATIVE_TOOLS/man:$NATIVE_TOOLS/share/man:$MANPATH"
export MANPATH
alias man='man -C "$NATIVE_TOOLS/lib/man.conf"'

# nmap data directory
NMAPDIR="$NATIVE_TOOLS/share/nmap"
export NMAPDIR

# coreutils
alias ls='ls --color=auto'

# BerryCore utility aliases (legacy - use qpkg commands)
alias bchelp='qpkg catalog -h'
alias bccat='qpkg catalog -c'        # Usage: bccat net
alias bcsearch='qpkg catalog -s'     # Usage: bcsearch compress
alias bcbins='qpkg bins'

# fakeroot
#export FAKEROOTUID=100
#export FAKEROOTGID=100
#export FAKEROOTEUID=100
#export FAKEROOTEGID=100
#export FAKEROOTSUID=100
#export FAKEROOTSGID=100
#export FAKEROOTFUID=100
#export FAKEROOTFGID=100

# locale
export LC_CTYPE=en_US.UTF-8

# Term49 / login: start the web-app catalog (port 8098) and notify once.
# Disable: export BERRYCORE_SETUP_AUTO=0 in .profile before sourcing env.sh
if [ -t 1 ] && [ "${BERRYCORE_SETUP_AUTO:-1}" = "1" ] && [ -x "$NATIVE_TOOLS/bin/setup" ]; then
    "$NATIVE_TOOLS/bin/setup" boot >/dev/null 2>&1 &
fi

# Welcome Message
# Set BERRYCORE_QUIET=1 in .profile BEFORE sourcing env.sh to skip this
# banner (Term49 fancy splash owns the launch screen).
if [ "${BERRYCORE_QUIET:-0}" != "1" ]; then
echo ""
echo "==========================================================="
echo "     BerryCore v0.88.0 - QNX Extended Userland"
echo "==========================================================="
echo ""
echo "Browse available tools:"
echo "  qpkg catalog        List all binaries by category"
echo "  qpkg catalog -s     Search for specific tools"
echo "  qpkg info BINARY    Get info about a binary"
echo "  qpkg bins           See all installed binaries"
echo ""
echo "Install additional software:"
echo "  qpkg ports          Browse available ports"
echo "  qpkg install NAME   Install a port package"
echo ""
echo "Quick navigation shortcuts:"
echo "  misc, docs, downloads, sdcard, bc"
echo ""
echo "Quick start: setup, talkbutton, nano, vim, git, nmap, curl, linux, games, library, waterwaymap, stocks, solarsystem, sttlab, term49-web"
echo ""
echo "Auto-start: settings sshd-on, settings tools-on, settings games-on, settings homescreen-on, settings status"
echo "==========================================================="
fi

# Message of the Day (MOTD) - Enabled by default
# To disable: export BERRYCORE_MOTD_ENABLED=0 in your .profile BEFORE sourcing env.sh
if [ "${BERRYCORE_MOTD_ENABLED:-1}" = "1" ]; then
    # Default MOTD URL
    MOTD_URL="${BERRYCORE_MOTD_URL:-https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt}"
    
    # Try to fetch from internet first (with SSL verification bypass for QNX)
    MOTD_TEXT=$(curl -k -s -m 5 "$MOTD_URL" 2>/dev/null)
    
    if [ -n "$MOTD_TEXT" ]; then
        echo ""
        echo "$MOTD_TEXT"
    else
        # Fallback to local MOTD file if internet fetch fails
        if [ -f "$NATIVE_TOOLS/motd.txt" ]; then
            echo ""
            cat "$NATIVE_TOOLS/motd.txt"
        fi
    fi
fi

# Quick navigation shortcuts for common BB10 directories
# Smart functions: cd to directory OR copy files from it

misc() {
    if [ $# -eq 0 ]; then
        cd /accounts/1000/shared/misc
    elif [ $# -eq 1 ]; then
        cp "/accounts/1000/shared/misc/$1" .
    else
        cp "/accounts/1000/shared/misc/$1" "$2"
    fi
}

docs() {
    if [ $# -eq 0 ]; then
        cd /accounts/1000/shared/documents
    elif [ $# -eq 1 ]; then
        cp "/accounts/1000/shared/documents/$1" .
    else
        cp "/accounts/1000/shared/documents/$1" "$2"
    fi
}

downloads() {
    if [ $# -eq 0 ]; then
        cd /accounts/1000/shared/downloads
    elif [ $# -eq 1 ]; then
        cp "/accounts/1000/shared/downloads/$1" .
    else
        cp "/accounts/1000/shared/downloads/$1" "$2"
    fi
}

sdcard() {
    if [ $# -eq 0 ]; then
        cd /accounts/1000/removable/sdcard
    elif [ $# -eq 1 ]; then
        cp "/accounts/1000/removable/sdcard/$1" .
    else
        cp "/accounts/1000/removable/sdcard/$1" "$2"
    fi
}

bc() {
    if [ $# -eq 0 ]; then
        cd $NATIVE_TOOLS
    elif [ $# -eq 1 ]; then
        cp "$NATIVE_TOOLS/$1" .
    else
        cp "$NATIVE_TOOLS/$1" "$2"
    fi
}

echo ""
