# term49-web Port Analysis

## Overview

**term49-web** is a browser-based terminal for QNX/BB10. Access your shell from any browser using xterm.js over WebSocket.

## Package Contents

| Path | Purpose |
|------|---------|
| `bin/term49-web` | C binary – WebSocket server + PTY bridge (ELF ARM, ~12KB) |
| `www/index.html` | Web UI with xterm.js |
| `www/css/xterm.css` | Terminal styling |
| `www/js/xterm.js` | xterm.js v3.14.5 (ES5-compatible) |
| `www/js/fit.js` | Terminal resize fit addon |
| `share/term49-web/README.md` | Full documentation |

## Technical Notes

- **Binary**: ARM EABI5, dynamically linked (ldqnx.so.2) – BB10 compatible
- **Port**: 7681 (configurable via `-p`)
- **Dependencies**: BerryCore bash, tmux PTY (both in core)
- **Web root**: Server expects `www/` as sibling of `bin/` – extraction to `$NATIVE_TOOLS` preserves this layout

## Security

- No authentication – localhost use recommended
- HTTP only – no TLS
- Block external access if on shared network

## Install / Usage

```bash
qpkg install term49-web
term49-web                    # Default port 7681
# Open http://localhost:7681/ in BB10 browser
term49-web -p 8080            # Custom port
```

## Verification Checklist

- [x] Binary is ARM QNX ELF
- [x] Package layout matches server expectations (bin/ + www/ siblings)
- [x] Added to ports/INDEX
- [x] Added to berrycore/CATALOG
- [x] env.sh quick start updated
