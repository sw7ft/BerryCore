#!/bin/sh
# BerryCore BDK CLI — setup after qpkg install bdk-cli
BDK_HOME="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
BDK_BIN="${BDK_HOME}/bin"
BDK_DATA="${BDK_HOME}/data"
MARK="# BerryCore BDK CLI"
PROFILE="${HOME}/.profile"
NT="${NATIVE_TOOLS:-/accounts/1000/shared/misc/berrycore}"

printf 'BerryCore BDK CLI setup\n'
printf '  home: %s\n' "$BDK_HOME"

if [ ! -x "$BDK_BIN/bdk-cli" ]; then
	printf 'ERROR: bdk-cli not found at %s/bdk-cli\n' "$BDK_BIN"
	exit 1
fi

chmod +x "$BDK_BIN/bdk-cli" 2>/dev/null
mkdir -p "$BDK_DATA"

# Wrapper in berrycore/bin — sets DATADIR + SSL_CERT_FILE automatically
mkdir -p "$NT/bin"
if [ -f "$BDK_BIN/berrycore-bdk-cli" ]; then
	cp "$BDK_BIN/berrycore-bdk-cli" "$NT/bin/bdk-cli"
else
	cat > "$NT/bin/bdk-cli" << 'EOF'
#!/bin/sh
BDK_HOME="/accounts/1000/shared/misc/bdk-cli"
NT="${NATIVE_TOOLS:-/accounts/1000/shared/misc/berrycore}"
export DATADIR="${DATADIR:-$BDK_HOME/data}"
export SSL_CERT_FILE="${SSL_CERT_FILE:-$NT/certs/cacert.pem}"
mkdir -p "$DATADIR"
exec "$BDK_HOME/bin/bdk-cli" "$@"
EOF
fi
chmod +x "$NT/bin/bdk-cli"
printf '  Installed bdk-cli in %s/bin\n' "$NT"

if [ -f "$PROFILE" ] && grep -q "$MARK" "$PROFILE" 2>/dev/null; then
	printf '  Env already in %s\n' "$PROFILE"
else
	printf '\n%s\n' "$MARK" >> "$PROFILE"
	printf 'export DATADIR=%s\n' "$BDK_DATA" >> "$PROFILE"
	printf 'export SSL_CERT_FILE=%s/certs/cacert.pem\n' "$NT" >> "$PROFILE"
	printf '  Added DATADIR + SSL_CERT_FILE to %s\n' "$PROFILE"
fi

printf '\nDone. Try (testnet only):\n\n'
printf '  . ~/.profile\n'
printf '  bdk-cli key generate\n'
printf '  bdk-cli -n testnet wallet -w mywallet -e "wpkh(tpub.../*)" \\\n'
printf '    --client-type electrum --database-type sqlite \\\n'
printf '    --url "ssl://electrum.blockstream.info:60002" sync\n\n'
printf 'Help: %s/share/bdk-cli/HELP.txt\n\n' "$BDK_HOME"
