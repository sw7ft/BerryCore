#!/bin/sh
# QNX Doom — run from share/qnx-doom (BerryCore port layout)

DOOM_DIR=$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)
export LD_LIBRARY_PATH="$DOOM_DIR/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

if [ -z "$DISPLAY" ]; then
    DISPLAY="127.0.0.1:0"
    export DISPLAY
fi

echo "QNX Doom — DISPLAY=$DISPLAY"
echo "(Start XSDL first. Run on device for keyboard — not SSH.)"
cd "$DOOM_DIR"
exec ./bin/doomgeneric_qnx "$@"
