# wget package (GNU Wget 1.25.0)

Modern **GNU Wget** for BB10/QNX, shipped as a **BerryCore core package** (same as the old wget 1.20.3 zip). Not a separate `qpkg ports` entry.

Cross-built with static **OpenSSL 1.1.1w** (same SSL generation as curl 8.12.1 and git 2.47.2).

## Users

Wget installs automatically with BerryCore upgrade or fresh install:

```bash
qpkg update          # or fresh install.sh
wget --version
wget -O- https://example.com/ | head
```

## Build (maintainers)

From repo root (requires `wget-bb10-1.25.0.tgz`):

```bash
cd ports/wget
./build-port.sh
```

Output: `berrycore/packages/wget-1.25.0.zip`

## Layout (installed to `$NATIVE_TOOLS` via pbpkgadd)

| Path | Purpose |
|------|---------|
| `bin/wget` | Wrapper (SSL_CERT_FILE) |
| `bin/wget.bin` | ARM binary (~3.2 MB) |
| `share/wget/certs/cacert.pem` | Mozilla CA bundle (fallback) |
