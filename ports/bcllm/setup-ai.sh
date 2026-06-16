#!/bin/sh
# BerryCore AI — setup after qpkg install bcllm or BerryCore upgrade
AI_HOME="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
AI_BIN="${AI_HOME}/bin"
MARK="# BerryCore AI"
PROFILE="${HOME}/.profile"
NT="${NATIVE_TOOLS:-/accounts/1000/shared/misc/berrycore}"

printf 'BerryCore AI setup\n'
printf '  home: %s\n' "$AI_HOME"

if [ ! -x "$AI_BIN/bcllm-ai" ]; then
	printf 'ERROR: ai not found at %s/bcllm-ai\n' "$AI_BIN"
	exit 1
fi

# Ensure bin/ai is the wrapper (fixes broken symlinks and ai/AI zip collisions)
if [ -f "$AI_BIN/berrycore-ai" ]; then
	cp "$AI_BIN/berrycore-ai" "$AI_BIN/ai"
	chmod +x "$AI_BIN/ai"
elif [ -L "$AI_BIN/ai" ] || [ ! -f "$AI_BIN/ai" ]; then
	cat > "$AI_BIN/ai" << 'EOF'
#!/bin/sh
exec /accounts/1000/shared/misc/bcllm/bin/bcllm-ai "$@"
EOF
	chmod +x "$AI_BIN/ai"
fi
ln -sf ai "$AI_BIN/AI" 2>/dev/null || true

# $NATIVE_TOOLS/bin/ai — real wrapper script (symlink breaks ai "prompt")
mkdir -p "$NT/bin"
rm -f "$NT/bin/ai" "$NT/bin/AI" "$NT/bin/bcllm"
if [ -f "$AI_BIN/ai" ] && [ ! -L "$AI_BIN/ai" ]; then
	cp "$AI_BIN/ai" "$NT/bin/ai"
elif [ -f "$AI_BIN/berrycore-ai" ]; then
	cp "$AI_BIN/berrycore-ai" "$NT/bin/ai"
else
	cat > "$NT/bin/ai" << 'EOF'
#!/bin/sh
exec /accounts/1000/shared/misc/bcllm/bin/bcllm-ai "$@"
EOF
fi
chmod +x "$NT/bin/ai"
ln -sf ai "$NT/bin/AI" 2>/dev/null || true
[ -x "$AI_BIN/bcllm" ] && ln -sf "$AI_BIN/bcllm" "$NT/bin/bcllm" 2>/dev/null || true
printf '  Installed ai in %s/bin\n' "$NT"

if [ -f "$PROFILE" ] && grep -q "$MARK" "$PROFILE" 2>/dev/null; then
	printf '  PATH already in %s\n' "$PROFILE"
else
	printf '\n%s\n' "$MARK" >> "$PROFILE"
	printf 'export PATH=%s:$PATH\n' "$AI_BIN" >> "$PROFILE"
	printf '  Added PATH to %s\n' "$PROFILE"
fi

mkdir -p "$AI_HOME/models" "$AI_HOME/var" 2>/dev/null

printf '\nDone. Try:\n\n'
printf '  . ~/.profile\n'
printf '  ai download smollm2_135m\n'
printf '  ai "What is the capital of France?"\n\n'
