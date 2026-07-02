# Dropbear SSH for BlackBerry Passport

**Dropbear 2026.91** — lightweight SSH client (`dbclient`/`ssh`) and server for QNX 8 / BerryCore.

Built on xps (bb10-kitchen-sink Docker) for **armle-v7 / QNX 8**.

## Install

```sh
qpkg install dropbear
```

Binaries in `/accounts/1000/shared/misc/bin/`; keys dir `/accounts/1000/shared/misc/etc/dropbear/`.

## Usage

```sh
ssh mp@192.168.1.179
dbclient -L 8080:127.0.0.1:3000 mp@192.168.1.179

dropbearkey -t ed25519 -f /accounts/1000/shared/misc/etc/dropbear/id_ed25519
dropbear -F -E -p 2222 -r /accounts/1000/shared/misc/etc/dropbear/dropbear_ed25519_host_key
```

Full manual: `share/doc/dropbear/MANUAL.md`

## Rebuild

```bash
./ports/dropbear/build-port.sh dropbear-passport-qnx8.tar.gz
```

QNX options: `ports/dropbear/localoptions.h`
