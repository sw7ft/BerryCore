# BerryCore v0.76 Release Notes

**Release Date:** February 22, 2026  
**Type:** Updated git & curl with Modern SSL

---

## Updated git & curl – Working with Modern SSL

This release upgrades **git** and **curl** to work reliably with modern HTTPS and SSL/TLS:

| Package | Previous | New |
|---------|----------|-----|
| **git** | 2.26.0 | **2.47.2** |
| **curl** | 7.76.0 | **8.12.1** |

Both include wrappers that configure CA certs for HTTPS. `git clone https://...` and `curl https://...` work with modern SSL verification using BerryCore's `ssl/cert.pem`.

---

## QNX Desktop – Full Windows 98 Desktop Environment

A complete retro desktop experience for BlackBerry 10. Browse files, manage email, chat with AI, edit documents, and more — all through a familiar Windows 98–style web interface.

**Install:**
```bash
qpkg install qnxdesktop
qnxdesktop start
```

Then open `http://127.0.0.1:8029` in the BB10 browser. Login: `qnx-user` / `desktop`

**Features:**
- **File Explorer** – Browse `/accounts/1000/shared` and SD card. Upload, download, delete, create folders
- **Mail Client** – IMAP/SMTP with full inbox, folders, send/receive, mark read/unread
- **AI Chat** – Claude API integration for conversations from the desktop
- **Notes & Code Editor** – Built-in text editor with syntax awareness
- **System Information** – Storage usage, accessible paths, device info
- **Auto-Dependencies** – Checks for Python 3 and Flask on first run; installs what's needed via pip

**Technical:**
- Flask-based web app, port 8029
- Requires Python 3 (qpkg install python3)
- Auto-installs Flask + requests on first start if missing

---

## New Ports (4)

### QNX Desktop
- **Category:** web | **Size:** 753 KB  
- Windows 98–style desktop with file explorer, mail client, AI chat

### VoiceAgent
- **Category:** web | **Size:** 23 KB  
- Push-to-talk AI voice assistant. OpenAI Whisper → GPT-4o → TTS. Port 8085

### Chromium Shell
- **Category:** web | **Size:** 21 MB  
- Headless Chromium Content Shell for DOM dump. HTTP proxy for external sites. Terminal-only

### Tetris
- **Category:** games | **Size:** 6 KB  
- Classic Tetris in pure bash. Play in the terminal

---

## Available Ports (11 total)

| Port | Category | Size | Description |
|------|----------|------|-------------|
| **qnxdesktop** (NEW) | web | 753 KB | Windows 98 desktop – file explorer, mail, AI chat |
| **voiceagent** (NEW) | web | 23 KB | AI voice assistant with OpenAI APIs |
| **chromium-shell** (NEW) | web | 21 MB | Headless Chromium, DOM dump, HTTP proxy |
| **tetris** (NEW) | games | 6 KB | Classic Tetris in bash |
| apache-php | web | 43 MB | Apache + PHP 7.4 |
| berrypy | web | 75 KB | App platform manager |
| berrysnip | util | 24 KB | Snippet & notes manager |
| elinks | web | 1.3 MB | Text browser with SSL/TLS |
| hydra | net | 165 KB | Password auditing |
| python3 | lang | 25 MB | Python 3.11 + pip |
| tmux | sys | 2.5 MB | Terminal multiplexer |

---

## Statistics

- **Core Packages:** 73  
- **Port Count:** 11 installable ports (up from 7)  
- **Binary Count:** 100+  
- **Total Size:** ~270 MB (core) + ports on demand  

---

## Upgrade Instructions

### From v0.75 or earlier:

```bash
qpkg update
```

Or manual:
```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76/install.sh
chmod +x install.sh
./install.sh
```

### Install New Ports:

```bash
qpkg install qnxdesktop
qnxdesktop start

qpkg install voiceagent
voiceagent start

qpkg install chromium-shell
chromium-shell http://127.0.0.1:8001/page.html

qpkg install tetris
tetris
```

---

## Links

- **Repository:** https://github.com/sw7ft/BerryCore  
- **Releases:** https://github.com/sw7ft/BerryCore/releases  
- **Issues:** https://github.com/sw7ft/BerryCore/issues  
