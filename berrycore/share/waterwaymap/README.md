# Waterway Map

ES5 OpenStreetMap river-basin viewer for berry-browser. Inspired by [waterwaymap.org](https://waterwaymap.org/#map=2.5/40/15).

```sh
qpkg install waterwaymap
waterwaymap              # start on port 8095
waterwaymap stop
berry-browser http://127.0.0.1:8095/#map=3/40/15
```

Also: `qpkg install waterway` / `waterway`.

- Standard OSM tiles (Voyager fallback), cached under `share/waterwaymap/offline/tiles-osm`
- Waterways from Overpass, coloured by connected group in the current view
- Hash `#map=zoom/lat/lon` like waterwaymap.org
- Filters: river / canal / stream / drain, minimum length
- Zoom 8+ to load ways
