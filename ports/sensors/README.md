# sensors — Term49 motion-sensor CLI

Native BPS client for the Passport accelerometer, gyro, magnetometer, and related nodes. Falls back to readable PPS fusion (`sensors pps`).

Built on xps (`bb10-kitchen-sink` / BB10 NDK) for **armle-v7**.

## Install

```sh
qpkg install sensors
```

## Usage

```sh
sensors
sensors accel
sensors -n 10 all
sensors pps
```

## Rebuild

Inside `bb10-kitchen-sink`:

```bash
bash /root/ports/sensors/build-sensors-passport.sh
```

Then:

```bash
./ports/sensors/build-port.sh
```
