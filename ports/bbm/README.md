# BBM — Berry Bridge Messenger

Native QNX/BB10 client for the BerryCore device relay at **berrycore.sw7ft.com** (TCP **37193**).

Single ARM binary — no `nc` or `telnet` required. Installs `bbm` and `berrymsg` (symlink).

## Install

```sh
qpkg install bbm
```

Installs to `/accounts/1000/shared/misc/bin/` with symlinks in `$NATIVE_TOOLS/bin/`.

## Setup

Add to BerryCore `env.sh` (see `share/doc/bbm/env.example`):

```sh
export BERRYRELAY_HOST="berrycore.sw7ft.com"
export BERRYRELAY_PORT="37193"
export BERRYRELAY_KEY="<relay key>"
```

## Usage

```sh
bbm who
bbm send @all "online"
bbm send other-hostname "ping"
bbm poll
bbm group 20
```

Full manual: `share/doc/bbm/MANUAL.md`

## Rebuild

Cross-build on xps (bb10-kitchen-sink Docker):

```bash
./ports/bbm/build-bbm-passport.sh
./ports/bbm/build-port.sh bbm-passport-qnx8.tar.gz
```
