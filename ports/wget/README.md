# wget port (GNU Wget 1.25.0)

Modern **GNU Wget** for BB10/QNX, cross-built with static **OpenSSL 1.1.1w** (same SSL generation as curl 8.12.1 and git 2.47.2). Replaces BerryCore **wget 1.20.3**.

## Users

```bash
qpkg install wget
wget --version
wget -O- https://example.com/ | head
```

## Build (maintainers)

From repo root (requires `wget-bb10-1.25.0.tgz`):

```bash
cd ports/wget
./build-port.sh
```

Produces:

- `ports/net-wget-1.25.0.zip` — qpkg port
- `berrycore/packages/wget-1.25.0.zip` — core BerryCore package (replaces wget-1.20.3.zip)

## Layout (installed to `$NATIVE_TOOLS`)

| Path | Purpose |
|------|---------|
| `bin/wget` | Wrapper (SSL_CERT_FILE) |
| `bin/wget.bin` | ARM binary (~3.2 MB) |
| `share/wget/certs/cacert.pem` | Mozilla CA bundle (fallback) |

Upstream build docs are in the source tarball under `wget/docs/`.
