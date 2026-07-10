#!/bin/sh
# QNX Doom — run from share/qnx-doom (BerryCore port layout)
# Requires DISPLAY (XSDL / X server). Run on device, not over SSH.

DOOM_DIR=$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)
export LD_LIBRARY_PATH="$DOOM_DIR/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

if [ -z "$DISPLAY" ]; then
    echo "ERROR: DISPLAY is not set."
    echo "Start XSDL (see share/qnx-doom/apks/) and run:"
    echo "  export DISPLAY=192.168.1.113:0"
    exit 1
fi

echo "QNX Doom — X display: $DISPLAY"
echo "(Requires XSDL/X server — run on device, not SSH)"
cd "$DOOM_DIR"
exec ./bin/doomgeneric_qnx "$@"
