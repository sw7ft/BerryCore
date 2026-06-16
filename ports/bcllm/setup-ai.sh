#!/bin/sh
# BerryCore AI — one-time setup (run after qpkg install bcllm)
AI_HOME="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
AI_BIN="${AI_HOME}/bin"
MARK="# BerryCore AI"
PROFILE="${HOME}/.profile"

printf 'BerryCore AI setup\n'
printf '  home: %s\n' "$AI_HOME"

if [ ! -x "$AI_BIN/bcllm-ai" ] && [ ! -x "$AI_BIN/ai" ]; then
	printf 'ERROR: ai not found at %s/bcllm-ai\n' "$AI_BIN"
	exit 1
fi
[ -x "$AI_BIN/bcllm-ai" ] && ln -sf bcllm-ai "$AI_BIN/ai" 2>/dev/null

if [ -f "$PROFILE" ] && grep -q "$MARK" "$PROFILE" 2>/dev/null; then
	printf '  PATH already in %s\n' "$PROFILE"
else
	printf '\n%s\n' "$MARK" >> "$PROFILE"
	printf 'export PATH=%s:$PATH\n' "$AI_BIN" >> "$PROFILE"
	printf '  Added PATH to %s\n' "$PROFILE"
fi

ln -sf "$AI_BIN/ai" "$AI_BIN/AI" 2>/dev/null || true

if [ -f "$PROFILE" ] && grep -q 'alias AI=' "$PROFILE" 2>/dev/null; then
	printf '  alias AI already set\n'
else
	printf "alias AI='ai'\n" >> "$PROFILE"
	printf '  Added alias AI=ai\n'
fi

mkdir -p "$AI_HOME/models" "$AI_HOME/var" 2>/dev/null

printf '\nDone. Open a new shell or run:\n\n'
printf '  export PATH=%s:$PATH\n' "$AI_BIN"
printf '  ai\n'
printf '  ai download smollm2_135m\n\n'
