# Maps Port

OpenStreetMap navigation for BB10 — search locations, view maps, and get driving directions.

Same app as **Maps** in BerryPy / BerryStore, packaged as a standalone qpkg port.

## Install

```bash
qpkg install python3
python3 -m ensurepip
python3 -m pip install requests

qpkg install maps
```

## Quick start

```bash
maps
# Starts in background. Open http://localhost:8090 in BB10 browser

maps -f   # Run in foreground (for debugging)
```

## Requires

- **python3** — `qpkg install python3`
- **requests** — `python3 -m pip install requests`
- Network access (map tiles, Nominatim, OSRM)

## Features

- Interactive Leaflet map
- Search places
- Driving directions
- Touch-optimized BB10 UI

## Port

Default: **8090** (matches BerryPy / BerryStore catalog)

## Source

Downloaded from BerryStore: `http://berrystore.sw7ft.com/apps/Maps.zip`

## Rebuild

```bash
./ports/maps/build-port.sh
```
