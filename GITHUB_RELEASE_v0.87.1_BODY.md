## BerryCore v0.87.1

Patch release — fixes **custom install directory** port installs (e.g. `berrycore4`) and QNX unzip errors.

### Fixed

- **`qpkg install openport`** (and telnet, dropbear, ftp, bbm, usbdbg) on custom-named installs now extracts to your BerryCore tree, not shared `misc/share/doc/`
- **Second Term49 session** — no more "cannot delete old MANUAL.md" warnings; staging extract replaces in-place unzip

### Default `berrycore` install

Unchanged — misc-bin ports still go to `/accounts/1000/shared/misc/bin/` with symlinks into `berrycore/bin/`.

### Update

```sh
qpkg update
# or copy new berrycore.zip + install.sh:
sh install.sh --upgrade -y
```

### Custom install (e.g. berrycore4)

After upgrade, or copy the new qpkg:

```sh
cp /accounts/1000/shared/misc/berrycore/bin/qpkg /accounts/1000/shared/misc/berrycore4/bin/qpkg
. /accounts/1000/shared/misc/berrycore4/env.sh
qpkg install openport
# Expect: Installing to .../berrycore4
```

### Assets

See `RELEASE_FILES_v0.87.1.txt` for SHA256 checksums.
