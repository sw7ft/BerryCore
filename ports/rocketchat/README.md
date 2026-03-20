# RocketChat Port

RocketChat Navigator for BB10 — web app for RocketChat private groups and direct messages.

## Install

```bash
qpkg install rocketchat
```

## Requires

- **python3** — `qpkg install python3`

## Quick start

```bash
rocketchat
# Starts in background. Open http://localhost:8026 in BB10 browser

rocketchat -f   # Run in foreground (for debugging)
```

## First-time setup

1. Run `rocketchat`
2. Open **http://localhost:8026** in your BB10 browser
3. Enter your RocketChat server URL (e.g. `https://your-server.com`)
4. Enter username and password
5. Click Login — credentials are saved automatically

## Features

- Private groups and direct messages
- Room search
- Send messages
- Real-time message refresh
- BB10 notifications (when configured)

## Port

Default: **8026**

## Config

Stored in `$NATIVE_TOOLS/share/rocketchat/.env` (RCSERVER, RCTOKEN, RCID)
