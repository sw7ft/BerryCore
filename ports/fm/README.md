# fm — Term49 analog FM tuner

OpenMAX AL `XA_IID_RADIO` + RDS from the shell. Headset wire is usually the antenna.

```sh
qpkg install fm
fm avail
fm 95.1
fm now
fm seek
```

Built on xps (`bb10-kitchen-sink`) for **armle-v7**. Rebuild: `bash /root/ports/fm/build-fm-passport.sh`

Do not leave a tune running on the Wi-Fi hop — FM shares the BCM4339 combo with Wi-Fi.
