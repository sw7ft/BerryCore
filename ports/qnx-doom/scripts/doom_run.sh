#!/bin/sh
# QNX Doom — run from share/qnx-doom (BerryCore port layout)

DOOM_DIR=$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)
WAD_DIR="$DOOM_DIR/wads"
export LD_LIBRARY_PATH="$DOOM_DIR/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
export DOOMWADDIR="$WAD_DIR"

if [ -z "$DISPLAY" ]; then
    DISPLAY="127.0.0.1:0"
    export DISPLAY
fi

echo "QNX Doom — DISPLAY=$DISPLAY"
echo "(Start XSDL first. Run on device for keyboard — not SSH.)"
echo "Colors wrong? XSDL → Change device config → Video → enable 24 bit color depth"
cd "$DOOM_DIR"
exec ./bin/doomgeneric_qnx "$@"
