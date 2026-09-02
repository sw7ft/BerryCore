# BerryCore Port: Claude Code for BB10

**Date:** June 2026

## claude-code — Anthropic Claude Code (BB10-patched)

Run [Claude Code](https://github.com/anthropics/claude-code) on BlackBerry 10 / QNX Term49. Users bring their own Anthropic API key.

### Prerequisites

```bash
qpkg install node-term49    # Node.js v22 --jitless (required)
```

### Install

```bash
qpkg install claude-code
claude-setup                # paste API key from console.anthropic.com
```

### Quick start

```bash
claude help                 # BerryCore install / key docs
claude --help               # Claude Code CLI help
claude -p "hello from BB10"
claude                      # interactive session
```

### API key

- **Recommended:** `claude-setup` → writes `~/claude.key` (mode 600)
- **Manual:** `echo 'sk-ant-...' > ~/claude.key && chmod 600 ~/claude.key`
- **Session:** `export ANTHROPIC_API_KEY=sk-ant-...`

Never commit or share your API key.

### What's included

| Component | Purpose |
|-----------|---------|
| `bin/claude` | Launcher (jitless Node, fetch polyfill, BB10 env) |
| `bin/claude-setup` | Interactive API key setup |
| `share/claude-code/package/` | Claude Code 2.1.91 (BB10-patched bundle) |
| `share/claude-code/bb10-fetch-polyfill.cjs` | HTTP fetch without WebAssembly |
| `share/claude-code/context.md` | BB10 system prompt for the agent |

### Notes

- Uses BerryCore **bash** for the Bash tool (QNX `/bin/sh` is ksh)
- Temp files under `~/tmp` (not `/tmp`)
- Auto-approves tool use by default on personal devices (`--dangerously-skip-permissions`)
- Disable with `CLAUDE_BB10_SKIP_PERMISSION_BYPASS=1`
- License: Anthropic — see installed `share/claude-code/package/LICENSE.md`

### Port metadata

- **qpkg name:** `claude-code`
- **Category:** `dev`
- **Version:** `2.1.91`
- **Zip:** `dev-claude-code-2.1.91.zip` (~15 MB download)
