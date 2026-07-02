# OpenPort for BlackBerry Passport

OpenPort 2.0 OBD diagnostic CLI — identify cable, read voltage, probe PCM, scan FCA modules, log CAN traffic.

Built on xps (bb10-kitchen-sink Docker) for **armle-v7 / QNX 8**.

## Install

```sh
qpkg install openport
```

Installs to `/accounts/1000/shared/misc/bin/` with symlinks in `$NATIVE_TOOLS/bin/`.

## Usage

```sh
openport identify              # cable firmware (no vehicle)
openport -p /dev/serusb1 identify   # try serusb1 or serusb2
openport voltage
openport probe                 # VIN + PCM (key ON)
openport scan
openport log -d 120 -o /accounts/1000/shared/misc/can.log --show-id
export OPENPORT_PORT=/dev/serusb1
```

Full manual: `$NATIVE_TOOLS/share/doc/openport/MANUAL.md` or `misc/share/doc/openport/MANUAL.md`

## Rebuild

```bash
./ports/openport/build-port.sh openport-passport-qnx8.tar.gz
```

Source + Docker build script: `ports/openport/build-openport-canlog.sh`
