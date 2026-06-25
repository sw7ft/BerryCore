#!/bin/sh
# Build berrycore/packages/berrybridge-agent-0.1.0.zip
# Usage: ./build-port.sh [path-to-berrybridge-agent-bb10-0.1.0.tgz]

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
INPUT_TGZ="${1:-$REPO_ROOT/berrybridge-agent-bb10-0.1.0.tgz}"
CORE_ZIP="$REPO_ROOT/berrycore/packages/berrybridge-agent-0.1.0.zip"
BUILD_DIR="$SCRIPT_DIR/.build"
STAGING="$BUILD_DIR/staging"
PKG_ROOT="$STAGING/berrybridge-agent"

echo "Building berrybridge-agent 0.1.0 core package..."
echo "  Input:  $INPUT_TGZ"
echo "  Output: $CORE_ZIP"

if [ ! -f "$INPUT_TGZ" ]; then
    echo "Error: $INPUT_TGZ not found"
    exit 1
fi

rm -rf "$BUILD_DIR"
mkdir -p "$STAGING"
tar xzf "$INPUT_TGZ" -C "$STAGING"

if [ ! -x "$PKG_ROOT/bin/berrybridge-run-job" ]; then
    echo "Error: expected berrybridge-agent/bin/berrybridge-run-job in tarball"
    exit 1
fi

chmod +x "$PKG_ROOT/bin/"* "$PKG_ROOT/berrybridge-postinstall.sh" \
    "$PKG_ROOT/setup-berrybridge.sh" 2>/dev/null || true

# BerryCore install.sh relocates to misc/ — postinstall must find agent there
cat > "$PKG_ROOT/berrybridge-postinstall.sh" << 'EOF'
#!/bin/sh
# Berry Bridge agent — post-install hook (called from BerryCore install.sh)
set -eu

INSTALL_ROOT="${1:-${NATIVE_TOOLS:-}}"
if [ -z "$INSTALL_ROOT" ] || [ ! -f "$INSTALL_ROOT/env.sh" ]; then
	printf 'berrybridge-postinstall: skip (no BerryCore root)\n'
	exit 0
fi

AGENT_HOME=""
for _d in \
	"/accounts/1000/shared/misc/berrybridge-agent" \
	"$INSTALL_ROOT/berrybridge-agent"; do
	if [ -x "$_d/bin/berrybridge-run-job" ]; then
		AGENT_HOME="$_d"
		break
	fi
done

if [ -z "$AGENT_HOME" ]; then
	printf 'berrybridge-postinstall: skip (agent not installed)\n'
	exit 0
fi

# shellcheck disable=SC1090
. "$INSTALL_ROOT/env.sh"
export NATIVE_TOOLS BERRYCORE_PATH="$NATIVE_TOOLS"

_conf="${AGENT_HOME}/etc/berrybridge/agent.conf"
if [ -f "$_conf" ]; then
	sed "s|^BERRYCORE_PATH=.*|BERRYCORE_PATH=${NATIVE_TOOLS}|" "$_conf" >"${_conf}.tmp" \
		&& mv "${_conf}.tmp" "$_conf"
fi

printf 'Berry Bridge agent post-install\n'
printf '  BerryCore: %s\n' "$NATIVE_TOOLS"
printf '  Agent:     %s\n' "$AGENT_HOME"

export BB_AGENT_HOME="$AGENT_HOME"
sh "${AGENT_HOME}/setup-berrybridge.sh"

# shellcheck source=/dev/null
. "${AGENT_HOME}/lib/berrybridge/common.sh"
bb_load_conf
# shellcheck source=/dev/null
. "${AGENT_HOME}/lib/berrybridge/start-watcher.sh"

mkdir -p "$NATIVE_TOOLS/bin" 2>/dev/null
for _cmd in berrybridge-agent berrybridge-run-job berrybridge-ensure-sshd; do
	ln -sf "${AGENT_HOME}/bin/${_cmd}" "${NATIVE_TOOLS}/bin/${_cmd}" 2>/dev/null || \
		cp "${AGENT_HOME}/bin/${_cmd}" "${NATIVE_TOOLS}/bin/${_cmd}" 2>/dev/null
	chmod +x "${NATIVE_TOOLS}/bin/${_cmd}" 2>/dev/null || true
done

bb_start_watcher || true
bb_install_cron_fallback || true

printf 'berrybridge-postinstall: done (inbox=%s)\n' "$INBOX"
EOF
chmod +x "$PKG_ROOT/berrybridge-postinstall.sh"

cd "$STAGING"
zip -r -q "$CORE_ZIP" berrybridge-agent
cd - >/dev/null

rm -rf "$BUILD_DIR"
echo "Done:"
ls -lh "$CORE_ZIP"
unzip -l "$CORE_ZIP" | head -25
