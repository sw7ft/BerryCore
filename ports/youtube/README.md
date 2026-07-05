# YouTube Port

YouTube Navigator **v2** for BB10 — search and embed playback with bundled static UI.

## Install

```bash
qpkg install python3
qpkg install youtube
```

## Quick start

```bash
youtube
# Open http://localhost:8070 in BB10 browser

youtube -f   # foreground / debug
```

## Requires

- **python3** — `qpkg install python3` (BerryCore bundled python preferred)
- **pytube** — optional; embed playback works without it

## Port

**8070** (matches BerryPy / BerryStore catalog)

## Rebuild

```bash
./ports/youtube/build-port.sh
```
