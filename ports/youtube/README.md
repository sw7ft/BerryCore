# YouTube Port

YouTube search and streaming for BB10 — same app as **youtube** in BerryPy / BerryStore.

## Install

```bash
qpkg install python3
python3 -m ensurepip
python3 -m pip install pytube youtube-search-python

qpkg install youtube
```

## Quick start

```bash
youtube
# Open http://localhost:8070 in BB10 browser

youtube -f   # foreground / debug
```

## Requires

- **python3** — `qpkg install python3`
- **pytube** — `python3 -m pip install pytube` (required for streaming)
- **youtube-search-python** — optional; app falls back to direct HTTP search

## Port

**8070** (matches BerryPy / BerryStore catalog)

## Source

BerryStore: `http://berrystore.sw7ft.com/apps/youtube.zip`

## Rebuild

```bash
./ports/youtube/build-port.sh
```
