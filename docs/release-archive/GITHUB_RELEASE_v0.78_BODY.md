BerryCore **v0.78** adds **Claude Code** on BB10, plus **RocketChat** and **Mutt setup**. Ports install via `qpkg` — no extra zips needed for Claude or RocketChat.

---

## Claude Code on BB10

Run [Anthropic Claude Code](https://github.com/anthropics/claude-code) in your terminal: edit files, run commands, ask about your codebase. **Bring your own API key** from [console.anthropic.com](https://console.anthropic.com/).

### 1. Install Node.js (required)

```bash
qpkg install node-term49
node -e "console.log('Node OK')"
```

### 2. Install Claude Code

```bash
qpkg install claude-code
claude-setup
```

`claude-setup` saves your key to `~/claude.key` (mode 600).

### 3. Use Claude

```bash
claude help                 # BerryCore install / key / env docs
claude --help               # Claude Code CLI options
claude -p "hello from BB10"
claude -p "explain the files in my home directory"
claude                      # interactive session
```

### API key options

| Method | Command |
|--------|---------|
| **Recommended** | `claude-setup` |
| Manual file | `echo 'sk-ant-...' > ~/claude.key && chmod 600 ~/claude.key` |
| One session | `export ANTHROPIC_API_KEY=sk-ant-...` |

### BB10 tips

- Requires **node-term49** first
- Uses BerryCore **bash** for the Bash tool (QNX `/bin/sh` is ksh)
- Temp files go to **`~/tmp`** (not `/tmp`)
- Tool use is auto-approved by default on personal devices; disable with `CLAUDE_BB10_SKIP_PERMISSION_BYPASS=1`

More detail: [Claude Code port docs](https://github.com/sw7ft/BerryCore/blob/main/GITHUB_RELEASE_ports-claude-code.md)

---

## RocketChat Navigator

Web app for RocketChat private groups and DMs. Port **8026**.

```bash
qpkg install python3
qpkg install rocketchat
rocketchat
# Open http://localhost:8026 in your BB10 browser

rocketchat -f    # foreground (debugging)
```

First run: enter server URL, username, and password in the browser.

---

## Mutt email setup

Interactive wizard for IMAP/SMTP — creates `~/.muttrc`:

```bash
mutt-setup
mutt
```

---

## Install / upgrade

**Fresh install**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.78/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.78/install.sh
chmod +x install.sh
./install.sh
```

**Upgrade from v0.77 or earlier**

```bash
qpkg update
```

**Verify**

```bash
cat $NATIVE_TOOLS/VERSION
# 0.78
```

---

## Release assets

| File | Size | SHA256 |
|------|------|--------|
| `berrycore.zip` | 176 MB | `33e7e590c2f4279396a44e26962e3981b9b0cf5690913da7ad944e712508de7a` |
| `install.sh` | ~8 KB | `8721a4a6d33a770f3a992d6c13223601cd2bc35f9aad30b9ec58232460bc291e` |

Ports (`claude-code`, `rocketchat`, etc.) are installed separately:

```bash
qpkg ports
qpkg install claude-code
```

---

## Also in this release

| Port | Description |
|------|-------------|
| **claude-code** | Claude Code AI agent (requires node-term49) |
| **rocketchat** | RocketChat web navigator (requires python3) |
| **node-term49** | Node.js v22, npm 10.5.1 (--jitless) |
| **content-shell-term49** | Chromium 120 headless browser |
| **wifi-chat** | P2P chat over WiFi |
| **berrybot** | Command-line teaching assistant |
| **bb-tools** | Web tools dashboard (port 8765) |

Full changelog: [CHANGELOG.md](https://github.com/sw7ft/BerryCore/blob/main/CHANGELOG.md)
