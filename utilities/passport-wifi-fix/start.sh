#!/bin/sh
# BB10 Wi-Fi RAM patch launcher, called by getroot v4's root-stage addon.
# Disable by creating /var/rootdata/wifi-fix/disabled.
FIX=/var/rootdata/wifi-fix
[ -f "$FIX/disabled" ] && exit 0
MODE=
case "$1" in
    --verify|--reapply) MODE="$1" ;;
    "") ;;
    *) exit 2 ;;
esac
umask 077
[ -f "$FIX/disabled" ] && exit 0
(set -C; : > /tmp/passport-wifi-fix.lock) 2>/dev/null || exit 0
trap 'rm -f /tmp/passport-wifi-fix.lock' EXIT
on -ePYTHONHOME=/usr:/usr -u 100:0 -A nonroot,allow,setuid,inherit /usr/bin/python3.2 -u "$FIX/boot_patch.py" $MODE >> "$FIX/boot.log" 2>&1
