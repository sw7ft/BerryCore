# Telnet for BlackBerry Passport

Classic **netkit telnet 0.17** client — interactive TELNET sessions to LAN hosts, routers, debug ports.

Built on xps (bb10-kitchen-sink Docker) for **armle-v7 / QNX 8**.

## Install

```sh
qpkg install telnet
```

Installs to `/accounts/1000/shared/misc/bin/` with symlink in `$NATIVE_TOOLS/bin/`.

## Usage

```sh
telnet 192.168.1.179
telnet 192.168.1.179 8080
```

Escape: **Ctrl+]`** then `quit`

Full manual: `share/doc/telnet/MANUAL.md`

## Rebuild

```bash
./ports/telnet/build-port.sh telnet-passport-qnx8.tar.gz
```

QNX patches: `ports/telnet/patches/`
