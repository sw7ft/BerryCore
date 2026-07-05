# bbm — Berry Bridge Messenger

Native QNX/BB10 client for the BerryCore device relay at **berrycore.sw7ft.com**.

No `nc` or `telnet` required — single ARM binary using TCP port **37193**.

## Setup

```bash
export BERRYRELAY_KEY="<relay_key from server ~/public_html/.bc-relay/config.json>"
export BERRYRELAY_FROM="$(hostname)"   # optional; defaults to hostname
export BERRYRELAY_HOST="berrycore.sw7ft.com"
export BERRYRELAY_PORT="37193"
```

Add to BerryCore `env.sh`:

```sh
export BERRYRELAY_HOST="berrycore.sw7ft.com"
export BERRYRELAY_PORT="37193"
# export BERRYRELAY_KEY="..."  # per-site secret
```

## Commands

```bash
bbm send @all "online"
bbm send other-hostname "ping"
bbm poll
bbm group 20
bbm who
```

`berrymsg` symlink is installed for compatibility with the server-side shell CLI.

## Install

```bash
tar xzf bbm-passport-qnx8.tar.gz -C /
source /accounts/1000/shared/misc/berrycore/env.sh
bbm who
```

## Protocol

Line-oriented BerryRelay 1.0: `AUTH`, `SEND`, `POLL`, `GROUP`, `WHO`, `QUIT`.
