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

### bb-tools — BerryCore Web Tools

Dashboard, drawing board, markdown/code editors, compass, virtual keyboard. Native C HTTP server on port 8765.

**Install:**
```bash
qpkg install bb-tools
```

**Run:**
```bash
tools
```

Then open: **http://localhost:8765/dashboard/**
