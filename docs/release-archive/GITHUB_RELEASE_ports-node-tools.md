# BerryCore Ports: Node.js & BB10 Tools

**Date:** March 2026

## New Ports

### node-term49 — Node.js v22 for Term49/QNX

JavaScript runtime with npm, **--jitless by default** (required for QNX).

**Install:**
```bash
qpkg install node-term49
```

**Use:**
```bash
node -e "console.log('Hello!')"
npm init
npm install <package>
```

### claude-code — Claude Code AI Agent (requires node-term49)

Anthropic Claude Code in the terminal, patched for QNX/Term49. Bring your own API key.

**Install:**
```bash
qpkg install node-term49    # required first
qpkg install claude-code
claude-setup
```

**Use:**
```bash
claude -p "explain this script"
claude                        # interactive
```

See [GITHUB_RELEASE_ports-claude-code.md](GITHUB_RELEASE_ports-claude-code.md) for full details.

### bb-tools — BerryCore Web Tools

Dashboard, drawing board, markdown/code editors, compass, virtual keyboard. Native C HTTP server on port 8765.

**Install:**
```bash
qpkg install bb-tools
```

**Run:** (starts in background)
```bash
tools
```

Then open: **http://localhost:8765/dashboard/**
