BerryCore **v0.81** adds **ncdu 1.22** (disk usage TUI) and **chafa 1.14.4** (terminal image viewer) as **core packages** — same install model as wget and dcron. Also includes dcron, wget 1.25.0, and qpkg fixes from earlier releases if you have not upgraded yet.

---

## ncdu 1.22 (core package)

Interactive **disk usage analyzer** — find what's eating space, drill into folders, delete from the UI.

```bash
qpkg update
ncdu /accounts/1000/shared/misc
ncdu /accounts/1000/r              # SD card
```

**Keys:** ↑↓ move, Enter enter dir, **d** delete, **n/s/C** sort, **q** quit

**Notes:**
- Needs a real TTY — use **Term49** or `ssh -t passport ncdu ~`
- Export scans: `ncdu -o /var/tmp/scan.json /path` then `ncdu -f /var/tmp/scan.json`

---

## chafa 1.14.4 (core package)

View **photos and images in the terminal** — JPEG, PNG, GIF, and more.

```bash
chafa --version
chafa-show photo.jpg
chafa-show -w 48 ~/Pictures/image.png
```

**Notes:**
- `chafa-show` is the easy wrapper; `chafa` is the low-level CLI
- Works best with `TERM=xterm-256color` (set automatically)
- SD card: `/accounts/1000/removable/sdcard/...`

---

## dcron 4.5 (core package)

If upgrading from before v0.80:

```bash
cron-start
crontab -e
crontab -l
```

---

## GNU Wget 1.25.0 (core package)

If upgrading from v0.78 or earlier:

```bash
wget --version
wget -O- https://example.com/ | head
```

---

## Upgrade

```bash
sh install.sh --upgrade
. $NATIVE_TOOLS/env.sh
```

Verify:

```bash
cat $NATIVE_TOOLS/VERSION    # 0.81
ncdu --version
chafa --version
cron-start && crontab -l
```

---

BerryCore v0.81 — June 2026
