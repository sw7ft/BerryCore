# FTP for BerryCore (netkit client + bftpd server)

Classic **`ftp`** client (netkit 0.17) + **`bftpd`** 5.4 server, cross-built for Passport/QNX 8.

Bundled as core package `util-ftp-1.0.0.zip` — installs with BerryCore upgrade/fresh install.

## Binaries

| Command | Role |
|---------|------|
| `ftp` / `pftp` | Interactive FTP client |
| `bftpd` | Lightweight FTP server |

## Server quick start

```sh
cp $NATIVE_TOOLS/etc/bftpd.conf.example $NATIVE_TOOLS/etc/bftpd.conf
bftpd -c $NATIVE_TOOLS/etc/bftpd.conf -D
# From LAN: ftp <passport-ip>
```

Share folder: `$NATIVE_TOOLS/ftp-root/`

## Rebuild

```bash
./ports/ftp/build-port.sh ftp-passport-qnx8.tar.gz
./utilities/package.sh
```

Source build: `build-ftp-passport.sh` (bb10-kitchen-sink Docker on xps).
