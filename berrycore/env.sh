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
# Fetches updates from: https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt
# To disable: export BERRYCORE_MOTD_ENABLED=0 in your .profile
if [ "$BERRYCORE_MOTD_ENABLED" != "0" ]; then
    MOTD_CACHE="$HOME/.berrycore_motd"
    MOTD_AGE=3600  # Cache for 1 hour (in seconds)
    MOTD_SHOWN=0
    
    # Default MOTD URL if not set
    : ${BERRYCORE_MOTD_URL:="https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt"}
    
    # Check if cache exists and is recent
    if [ -f "$MOTD_CACHE" ]; then
        CACHE_TIME=$(stat -f %m "$MOTD_CACHE" 2>/dev/null || stat -c %Y "$MOTD_CACHE" 2>/dev/null || echo 0)
        CURRENT_TIME=$(date +%s)
        AGE=$((CURRENT_TIME - CACHE_TIME))
        
        if [ $AGE -lt $MOTD_AGE ]; then
            # Cache is fresh, use it
            if [ -s "$MOTD_CACHE" ]; then
                echo ""
                cat "$MOTD_CACHE"
                MOTD_SHOWN=1
            fi
        else
            # Cache is stale, try to fetch new (in background, non-blocking)
            # Show old cache while fetching
            if [ -s "$MOTD_CACHE" ]; then
                echo ""
                cat "$MOTD_CACHE"
                MOTD_SHOWN=1
            fi
            (curl -s -m 3 "$BERRYCORE_MOTD_URL" > "$MOTD_CACHE.tmp" 2>/dev/null && \
             [ -s "$MOTD_CACHE.tmp" ] && mv "$MOTD_CACHE.tmp" "$MOTD_CACHE") </dev/null >/dev/null 2>&1 &
        fi
    else
        # No cache exists - try quick fetch (with timeout, non-blocking)
        (curl -s -m 2 "$BERRYCORE_MOTD_URL" > "$MOTD_CACHE.tmp" 2>/dev/null && \
         [ -s "$MOTD_CACHE.tmp" ] && mv "$MOTD_CACHE.tmp" "$MOTD_CACHE") </dev/null >/dev/null 2>&1 &
        
        # Wait briefly for first fetch (max 0.5 seconds)
        sleep 0.1
        if [ -f "$MOTD_CACHE" ] && [ -s "$MOTD_CACHE" ]; then
            echo ""
            cat "$MOTD_CACHE"
            MOTD_SHOWN=1
        fi
    fi
    
    # Show default message if no MOTD was displayed (offline/first run)
    if [ $MOTD_SHOWN -eq 0 ]; then
        echo ""
        echo ">> Welcome to BerryCore! For latest updates, visit:"
        echo "   https://github.com/sw7ft/berrycore"
    fi
fi

echo ""
