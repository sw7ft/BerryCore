# WiFi Chat Port

P2P chat over WiFi/local network. Discovers devices via UDP broadcast, sends messages via TCP.

## Install

```bash
qpkg install wifi-chat
```

## Quick start

```bash
wifi-chat                    # Use hostname as display name
wifi-chat alice              # Use "alice" as display name
wifi-chat -p 9999 bob        # Custom port (discovery = 9998)
```

## Commands (at prompt)

| Key | Action |
|-----|--------|
| `p` | List peers |
| `s 1 msg` | Send to peer 1 |
| `b msg` | Broadcast to all |
| `h` | Help |
| `q` | Quit |

## Requirements

- Devices on same LAN
- Ports 9876 (UDP) and 9877 (TCP) free (or use `-p` for alternate)

Full docs: `$NATIVE_TOOLS/share/wifi-chat/README.md`
