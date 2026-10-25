#!/bin/sh
# getroot v4 addon. Real/effective IDs may differ here; normalize with __root.
FIX=/var/rootdata/wifi-fix
[ -f "$FIX/disabled" ] && exit 0
umask 077
{
    echo "$(date) wifi addon v2 entered"
    pidin -p $$ user
} >> "$FIX/boot.log" 2>&1
/base/bin/__root <<'WIFI_ROOT' >> /var/rootdata/wifi-fix/boot.log 2>&1
echo "$(date) wifi addon credentials normalized"
pidin -p $$ user
# Do not restart Wi-Fi while getroot is still completing its own startup work.
n=0
while ! grep -q 'Script finished successfully' /tmp/root_install_x.log; do
    [ -f /var/rootdata/wifi-fix/disabled ] && exit 0
    n=$((n + 1))
    if [ "$n" -ge 90 ]; then
        echo "$(date) wifi addon aborted: getroot completion timeout"
        exit 1
    fi
    sleep 1
done
/bin/sh < /var/rootdata/wifi-fix/start.sh
WIFI_ROOT
