## sensors 1.0 — motion sensors in Term49

Read the Passport accelerometer, gyro, magnetometer, and related nodes from the shell. Native BPS client, ~10K.

```
qpkg install sensors
sensors
sensors accel
sensors -n 20 all
sensors pps
```

### What reports on Passport

| Name | Meaning |
|------|---------|
| accel | accelerometer (m/s²) |
| gyro | gyroscope (rad/s) |
| mag | magnetometer |
| gravity | gravity vector |
| linaccel | accel minus gravity |
| apr | azimuth / pitch / roll |
| compass | heading (degrees) |
| orient | screen pose |
| light | illuminance (lux) |
| prox | proximity |
| holster | holstered yes/no |
| pressure | not on this hardware |

`sensors pps` dumps fused state (in_hand, step count, stationary).

Alias: `sensor`. Zip: `util-sensors-1.0.zip`.
