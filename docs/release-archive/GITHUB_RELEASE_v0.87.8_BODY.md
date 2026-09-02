## BerryCore v0.87.8

**The Tape** is a stock desk for berry-browser, and Waterway Map is installable with qpkg.

### Added

- **`stocks`** / **`ticker`** — ticker + research on port **8096**
  - Custom lists
  - Per-symbol up-tick hub banners
  - Price above / below / up-tick / down-tick alerts
  - Research: range, sector, spark, headlines
  - Hub notify via `/pps/services/notify/control` (same path Rocket.Chat uses)
- **`qpkg install stocks`** — `web-stocks-1.0.zip` (alias: `ticker`)
- **`qpkg install waterwaymap`** — OSM river-basin map on port **8095** (`web-waterwaymap-1.0.zip`, alias: `waterway`)

### Use

```sh
qpkg install stocks
stocks
berry-browser http://127.0.0.1:8096/

qpkg install waterwaymap
waterwaymap
berry-browser http://127.0.0.1:8095/
```

See `RELEASE_FILES_v0.87.8.txt` for checksums.
