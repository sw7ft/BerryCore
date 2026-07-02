# Telegram Port

Telegram Messenger client for BB10 — same app as **Telegram** in BerryPy / BerryStore (v7.0.0).

## Install

```bash
qpkg install python3
python3 -m ensurepip
python3 -m pip install telethon requests

qpkg install telegram
```

## Quick start

```bash
telegram
# Open http://localhost:8010 in BB10 browser

telegram -f   # foreground / debug
```

## Requires

- **python3** — `qpkg install python3`
- **telethon** — `python3 -m pip install telethon`
- **requests** — `python3 -m pip install requests`
- Telegram account (free at telegram.org)
- Phone number with country code for login

## Port

**8010** (matches BerryPy / BerryStore catalog)

## Files

- `share/telegram/app.py` — backend + Telethon
- `share/telegram/index.html`, `auth.html`, `auth_code.html` — UI
- `share/telegram/session_name.session` — created on first login

## Source

BerryStore: `http://berrystore.sw7ft.com/apps/Telegram.zip`

## Rebuild

```bash
./ports/telegram/build-port.sh
```
