## gps 1.0 — GNSS from Term49

Read the Passport location manager from the shell. Native BPS client, ~12K. Live test: GNSS MS-based fix, ~25 m, 8/24 satellites.

```
qpkg install gps
gps
gps last
gps sats
gps watch
gps pps
gps -p gnss
```

Same pattern as `sensors` — subscribe to a service that was already running.

Zip: `util-gps-1.0.zip`.
