# IPFS Gateway Client Port

Read-only IPFS client for BB10 — fetch CIDs via HTTPS gateways (`ipfs.io`, `dweb.link`, etc.).

## Install

```bash
qpkg install ipfs-gw
```

## Quick start

```bash
# Fetch a CID to stdout
ipfs-gw cat QmYwAPJzv5CZsnA625s3Xf2nemtYgPUp66jiT1MV8b2w3

# Save to file
ipfs-gw cat Qm... > file.bin

# Use alternate gateway
ipfs-gw cat Qm... --gateway dweb.link > file.bin

# Verify local file matches CIDv0
ipfs-gw verify myfile.bin Qm...
```

## Requirements

- Wi-Fi / network access
- No local IPFS daemon needed (gateway-only client)

Full docs: `$NATIVE_TOOLS/share/ipfs-gw/HELP.txt`

## Rebuild port zip

```bash
./ports/ipfs-gw/build-port.sh util-ipfs-gw-0.1.0.zip
```
