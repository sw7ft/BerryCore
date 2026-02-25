# BerryCore v0.76 – Updated Git & curl with Modern SSL

**Release Date:** February 22, 2026

---

## Updated git & curl – Working with Modern SSL

This release upgrades **git** and **curl** to work reliably with modern HTTPS and SSL/TLS:

| Package | Previous | New |
|---------|----------|-----|
| **git** | 2.26.0 | **2.47.2** |
| **curl** | 7.76.0 | **8.12.1** |

Both include wrappers that configure CA certs for HTTPS. `git clone https://...` and `curl https://...` work with modern SSL verification using BerryCore's `ssl/cert.pem`.

---

## QNX Desktop – Windows 98 Style Web UI

```bash
qpkg install qnxdesktop
qnxdesktop start
```

Open `http://127.0.0.1:8029` in the BB10 browser. Login: `qnx-user` / `desktop`

**Features:** File Explorer | Mail Client (IMAP/SMTP) | AI Chat (Claude API) | Notes & Code Editor

---

## New Ports

| Port | Category | Size |
|------|----------|------|
| **qnxdesktop** | web | 753 KB |
| **voiceagent** | web | 23 KB |
| **chromium-shell** | web | 21 MB |
| **tetris** | games | 6 KB |

---

## Install / Upgrade

**From v0.75 or earlier:**

```bash
qpkg update
```

**Manual install:**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76/install.sh
chmod +x install.sh
./install.sh
```

---

## Assets

Attach these to the release:
- `berrycore.zip` (~170 MB)
- `install.sh`
