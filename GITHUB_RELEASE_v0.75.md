# BerryCore v0.75 – QNX Desktop & Git/curl Upgrades

**Release Date:** February 22, 2026

---

## QNX Desktop – Full Windows 98 Desktop Environment

A complete retro desktop experience for BlackBerry 10. Browse files, manage email, chat with AI, edit documents, and more — all through a familiar Windows 98–style web interface.

```bash
qpkg install qnxdesktop
qnxdesktop start
```

Open `http://127.0.0.1:8029` in the BB10 browser. Login: `qnx-user` / `desktop`

**Features:** File Explorer | Mail Client (IMAP/SMTP) | AI Chat (Claude API) | Notes & Code Editor | System Information

---

## Core Upgrades: Git 2.47.2 & curl 8.12.1

| Package | Previous | New |
|---------|----------|-----|
| **git** | 2.26.0 | **2.47.2** |
| **curl** | 7.76.0 | **8.12.1** |

Both include wrappers that configure CA certs for HTTPS (`git clone`, `curl`). Uses BerryCore's `ssl/cert.pem` when available.

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

**From v0.74 or earlier:**

```bash
qpkg update
```

**Manual install:**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.75/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.75/install.sh
chmod +x install.sh
./install.sh
```

---

## Assets

Attach these to the release:
- `berrycore.zip` (~170 MB)
- `install.sh`
