# BDK CLI Port

Bitcoin Dev Kit wallet CLI for BB10 — Electrum sync over TLS (testnet-first).

## Install

```bash
qpkg install bdk-cli
. ~/.profile
```

Installs to `/accounts/1000/shared/misc/bdk-cli/` and adds `bdk-cli` to `berrycore/bin/`.

## Quick start

```bash
bdk-cli key generate

bdk-cli -n testnet wallet -w mywallet -e "wpkh(tpub.../*)" \
  --client-type electrum --database-type sqlite \
  --url "ssl://electrum.blockstream.info:60002" sync
```

## Environment

`setup-bdk-cli.sh` configures:

- `DATADIR` → `misc/bdk-cli/data` (wallet SQLite DB)
- `SSL_CERT_FILE` → `$NATIVE_TOOLS/certs/cacert.pem`

The `berrycore/bin/bdk-cli` wrapper sets these on every run.

## Rebuild port zip

```bash
./ports/bdk-cli/build-port.sh bdk-cli-bb10-2.0.0.tgz
```

## Warning

Experimental — testnet only. Do not store mainnet funds on-device.
