## BerryCore v0.85.0

Passport tools batch: **Vim 9.1**, **FTP**, **BerryBrowser CLI**, **OpenPort**, network utilities, and BerryPy apps as standalone qpkg ports.

### Core bundle (berrycore.zip)

| Change | Details |
|--------|---------|
| **Vim 9.1.2148** | Replaces vim 8.0 — huge features, terminal + ncursesw |
| **util-ftp 1.0.0** | `ftp` client + `bftpd` server bundled in core packages |
| **VIMRUNTIME** | `env.sh` → `share/vim/vim91` |

### New qpkg ports

| Port | Install | Notes |
|------|---------|-------|
| **berry-browser** 1.0.27 | `qpkg install berry-browser` | CLI browser (`berry-browser URL`) + full-screen (`berry-browser-screen`) |
| **openport** 1.0.0 | `qpkg install openport` | OpenPort 2.0 OBD diagnostics |
| **telnet** 0.17 | `qpkg install telnet` | Classic netkit telnet client |
| **usbdbg** 1.0.0 | `qpkg install usbdbg` | USB serial probe/sniff |
| **dropbear** 2026.91 | `qpkg install dropbear` | SSH client (`ssh`/`dbclient`) + server |
| **maps** 1.0 | `qpkg install maps` | OpenStreetMap — port **8090**, needs `requests` |
| **youtube** 1.0 | `qpkg install youtube` | YouTube search/stream — port **8070**, needs `pytube` |
| **telegram** 1.0 | `qpkg install telegram` | Telegram via Telethon — port **8010** |

Legacy: `qpkg install content-shell-term49` → aliases to **berry-browser**.

### Quick start after upgrade

```sh
qpkg update
# or:
sh install.sh --upgrade

qpkg install berry-browser openport telnet usbdbg dropbear maps youtube telegram
```

**BerryBrowser (Term49 / SSH):**
```sh
berry-browser example.com
berry-browser -l example.com
```

**BerryPy-style apps (need pip deps first):**
```sh
python3 -m pip install requests          # maps
python3 -m pip install pytube            # youtube
python3 -m pip install telethon requests # telegram
maps && youtube && telegram
```

### Verify

```sh
cat $NATIVE_TOOLS/VERSION    # 0.85.0
vim --version                # 9.1.2148
berry-browser help
qpkg ports
```

### Assets

See `RELEASE_FILES_v0.85.txt` for SHA256 checksums.
