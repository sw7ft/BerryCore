## BerryCore v0.89.0

Sensors and GPS now ship in the base install. Fresh `berrycore.zip` has the binaries on PATH after `install.sh` — no extra `qpkg install` required.

### sensors (base)

Motion, battery, CPU, and `/dev/thermal` from Term49.

```
sensors
sensors battery
sensors cpu
sensors temp
sensors accel
```

Alias: `sensor`.

### gps (valuable default)

GNSS / hybrid location. Same pattern as sensors.

```
gps
gps last
gps sats
gps watch
```

### Hub

Same aubergine setup hub at `127.0.0.1:8098`. Core inventory lists `sensors` and `gps` as default present.

`qpkg update` pulls this Latest zip. v0.88.0 is no longer Latest.
