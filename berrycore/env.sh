NATIVE_TOOLS="/accounts/1000/shared/misc/berrycore"
QNX_TARGET=$NATIVE_TOOLS/target_10_3_1_995/qnx6
export NATIVE_TOOLS QNX_TARGET

PATH="$NATIVE_TOOLS/bin:$NATIVE_TOOLS/sbin:$PATH"
# Put BerryCore libs AFTER system libs to avoid conflicts with system binaries
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$QNX_TARGET/armle-v7/usr/lib:$NATIVE_TOOLS/lib"
export PATH LD_LIBRARY_PATH

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

# BerryCore utility aliases
alias bchelp='bclist -h'
alias bccat='bclist -c'        # Usage: bccat net
alias bcsearch='bclist -s'     # Usage: bcsearch compress
alias bcbins='ls -1 $NATIVE_TOOLS/bin'

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

# Welcome Message
echo ""
echo "==========================================================="
echo "     BerryCore v0.6 - QNX Extended Userland"
echo "==========================================================="
echo ""
echo "69 packages installed with 100+ binaries available"
echo ""
echo "Browse available tools:"
echo "  bclist              List major binaries by category"
echo "  bclist -s TERM      Search for specific tools"
echo "  bcinfo BINARY       Get info about a binary"
echo "  bcbins              See all installed binaries"
echo ""
echo "Quick start: nano, vim, git, nmap, curl, tmux, quickjs"
echo "==========================================================="

# Message of the Day (MOTD) - Enabled by default
# To disable: export BERRYCORE_MOTD_ENABLED=0 in your .profile
if [ "$BERRYCORE_MOTD_ENABLED" != "0" ]; then
    # Default MOTD URL if not set
    : ${BERRYCORE_MOTD_URL:="https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt"}
    
    # Fetch and display MOTD (single request, 2 second timeout)
    MOTD_TEXT=$(curl -s -m 2 "$BERRYCORE_MOTD_URL" 2>/dev/null)
    
    if [ -n "$MOTD_TEXT" ]; then
        echo ""
        echo "$MOTD_TEXT"
    fi
fi

echo ""
