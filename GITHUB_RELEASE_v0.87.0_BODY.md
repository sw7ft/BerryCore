## BerryCore v0.87.0

Consolidated fresh-install release: **core bundle**, **116 qpkg ports**, **HTML catalog guide**, no helper APK.

### Download

| File | Purpose |
|------|---------|
| **berrycore.zip** | Core userland (~210 MB) — bash, vim 9.1, git, gcc, 86 bundled packages |
| **install.sh** | Installer — fresh or upgrade |
| **berrycore.html** | Interactive catalog & install guide (open in any browser) |
| **RELEASE_FILES_v0.87.0.txt** | SHA256 checksums |

### What's included

- **Two-tier qpkg catalog** — `qpkg ports` (21 featured) + `qpkg search` (116 full catalog)
- **82 XPS utility ports** — cabextract, iperf3, minicom, cpmtools, 7za, retro interop tools
- **Phase 2 network ports** — openport (XPS rebuild), ftp, ping, tcpdump
- **Messenger upgrades** — RocketChat v3, Telegram v2.1, YouTube v2, BBM
- **berrycore.html** — copy-pastable install commands, category filters, port search

### Fresh install

```sh
# 1. Copy to device (from PC):
scp berrycore.zip install.sh berrycore.html passport:/accounts/1000/shared/misc/

# 2. On device (Term49 or SSH):
cd /accounts/1000/shared/misc
sh install.sh --fresh -y
. berrycore/env.sh

# 3. Verify:
cat $NATIVE_TOOLS/VERSION    # 0.87.0
qpkg ports
qpkg search cab
```

### Install ports

```sh
qpkg install openport dropbear python3 berry-browser
qpkg install cabextract iperf3 nomarch
```

### Upgrade from older BerryCore

```sh
qpkg update
# or copy new berrycore.zip + install.sh, then:
sh install.sh --upgrade -y
```

### Catalog page

Open **berrycore.html** on your PC or BB10 browser for the full port list, install snippets, and qpkg command reference.

### Assets

See `RELEASE_FILES_v0.87.0.txt` for SHA256 checksums.
