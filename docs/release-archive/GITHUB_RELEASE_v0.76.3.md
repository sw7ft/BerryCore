# BerryCore v0.76.3 – Mutt Email Client, Nano 7.2, Installer Fix

**Release Date:** March 1, 2026

---

## What's New

### Mutt 2.2.16 — Terminal Email Client

BerryCore now includes **mutt**, a powerful terminal-based email client with full IMAP/SMTP support over TLS. This is a statically linked build with OpenSSL 1.1.1w and LMDB header caching — no additional shared libraries required.

On first run, mutt automatically:
- Creates `~/.muttrc` with BB10-compatible defaults
- Sets up `~/Mail/` for local mail storage
- Creates `~/.cache/mutt/headers/` for IMAP header caching
- Configures SSL using BerryCore's CA certificate bundle

To connect to your mail server, edit `~/.muttrc` or copy the included example config:

```bash
cp $NATIVE_TOOLS/doc/mutt/muttrc.swiftmedia.example ~/.muttrc
nano ~/.muttrc
```

| Component | Details |
|-----------|---------|
| **mutt 2.2.16** | Full-featured email client (IMAP, SMTP, POP3, TLS) |
| **mutt-nossl** | No-TLS build included for debugging |
| **etc/Muttrc** | Default config — auto-copied to `~/.muttrc` on first run |

### Nano 7.2

Nano upgraded from 4.0 to 7.2.

### Installer Fix for Custom Directories

`install.sh` now updates `env.sh` with the correct install path **before** sourcing it. Previously, installing BerryCore to a non-default directory (anything other than `/accounts/1000/shared/misc/berrycore`) would cause packages to extract to the wrong location.

### Housekeeping

- Removed `bb10-root` auto-launch from `~/.profile` template

---

## Install / Upgrade

**Fresh install:**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76.3/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76.3/install.sh
chmod +x install.sh
./install.sh
```

**Upgrade from v0.76.x:**

```bash
qpkg update
```

---

## Assets

Attach these to the release:
- `berrycore.zip` (~170 MB)
- `install.sh`
