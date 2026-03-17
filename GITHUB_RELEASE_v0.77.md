# BerryCore v0.77 – New Ports: content-shell-term49, wifi-chat, berrybot

**Release Date:** March 17, 2026

---

## What's New

### content-shell-term49 — Chromium 120 Headless Browser

Chromium 120 headless browser for Term49/BB10. Renders web pages and dumps the DOM (after JavaScript) to stdout. Works over HTTP and HTTPS.

```bash
qpkg install content-shell-term49
content_shell http://example.com 2>/dev/null
content_shell https://example.com > page.html 2>/dev/null
```

### wifi-chat — P2P Chat over WiFi

Peer-to-peer chat over local network. Discovers devices via UDP broadcast, sends messages via TCP.

```bash
qpkg install wifi-chat
wifi-chat alice
# p = peers, s 1 msg = send, b = broadcast, h = help, q = quit
```

### berrybot — Command-Line Teaching Assistant

Non-AI teaching assistant for Linux, QNX, bash, and BerryCore. SQLite knowledge base.

```bash
qpkg install berrybot
bot grep
bot lessons
bot help
```

### Catalog Update

`qpkg catalog` now lists all port binaries: tools, node, npm, content_shell, wifi-chat, bot, tetris, qnxdesktop, voiceagent, term49-web.

---

## Install / Upgrade

**Fresh install:**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.77/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.77/install.sh
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
- `berrycore.zip` (~176 MB)
- `install.sh`
