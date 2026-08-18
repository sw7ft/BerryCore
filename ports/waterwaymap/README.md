# Waterway Map

ES5 OSM river-basin viewer for berry-browser. Port **8095**.

## Install

Bundled in current BerryCore, or:

```sh
qpkg install waterwaymap
```

`qpkg install waterway` is the same package.

## Usage

```sh
waterwaymap              # start
waterwaymap status
waterwaymap stop
waterway                 # same app
berry-browser http://127.0.0.1:8095/
```

Search a place, zoom 8+ for OSM waterways. Tiles and waterway JSON cache under `share/waterwaymap/offline/`.
