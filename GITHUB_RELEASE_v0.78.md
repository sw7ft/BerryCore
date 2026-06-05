# BerryCore v0.78 – Claude Code, RocketChat, Mutt Setup

**Release Date:** June 4, 2026

---

## What's New

### claude-code — Claude Code AI Agent for BB10

Run [Anthropic Claude Code](https://github.com/anthropics/claude-code) on BlackBerry 10 / QNX Term49. Terminal AI coding agent: edit files, run shell commands, answer questions about your codebase. **You bring your own API key** from [console.anthropic.com](https://console.anthropic.com/).

**Prerequisite — Node.js (required):**

```bash
qpkg install node-term49
node -e "console.log('Node OK')"
```

**Install Claude Code:**

```bash
qpkg install claude-code
claude-setup                # paste your Anthropic API key → ~/claude.key
```

**Use Claude:**

```bash
claude help                 # BerryCore install / key / env docs
claude --help               # Claude Code CLI options
claude -p "hello from BB10"
claude -p "explain the files in my home directory"
claude                      # interactive session
```

**API key options:**

| Method | Command |
|--------|---------|
| Recommended | `claude-setup` |
| Manual file | `echo 'sk-ant-...' > ~/claude.key && chmod 600 ~/claude.key` |
| One session | `export ANTHROPIC_API_KEY=sk-ant-...` |

**Tips for BB10:**

- Requires **node-term49** first (`qpkg install node-term49`)
- Uses BerryCore **bash** for the Bash tool (QNX `/bin/sh` is ksh)
- Temp files go to **`~/tmp`** (not `/tmp`)
- Personal devices: tool use is auto-approved by default; disable with `CLAUDE_BB10_SKIP_PERMISSION_BYPASS=1`
- Full port docs: [GITHUB_RELEASE_ports-claude-code.md](GITHUB_RELEASE_ports-claude-code.md)

---

### rocketchat — RocketChat Navigator for BB10

Web app for RocketChat private groups and direct messages. Runs on port **8026**.

```bash
qpkg install python3        # required
qpkg install rocketchat
rocketchat                  # starts in background
# Open http://localhost:8026 in BB10 browser

rocketchat -f               # foreground (debugging)
```

First run: enter server URL, username, and password in the browser.

---

### mutt-setup — Interactive Email Config

One-time setup wizard for Mutt (IMAP/SMTP). Creates `~/.muttrc`.

```bash
mutt-setup
mutt
```

Included with the mutt package; also documented in `berrycore/packages/mutt-setup`.

---

## All ports since v0.77

Install any time with `qpkg install <name>` (ports download from GitHub):

| Port | Description |
|------|-------------|
| **claude-code** | Claude Code AI agent (requires node-term49) |
| **rocketchat** | RocketChat web navigator (requires python3) |
| **node-term49** | Node.js v22, npm 10.5.1 (--jitless) |
| **content-shell-term49** | Chromium 120 headless browser |
| **wifi-chat** | P2P chat over WiFi |
| **berrybot** | Command-line teaching assistant |
| **bb-tools** | Web tools dashboard (port 8765) |

Run `qpkg ports` for the full list.

---

## Install / Upgrade

**Fresh install:**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.78/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.78/install.sh
chmod +x install.sh
./install.sh
```

**Upgrade from v0.77 or earlier:**

```bash
qpkg update
```

Or re-run `install.sh` from the release assets (upgrade mode preserves packages).

**Verify version:**

```bash
cat $NATIVE_TOOLS/VERSION
# 0.78
```

---

## Assets

Attach these to the GitHub release:

- `berrycore.zip` — main package (see `RELEASE_FILES_v0.78.txt` for size/checksum)
- `install.sh`

Ports (claude-code, rocketchat, etc.) are installed separately via `qpkg install` — no need to attach port zips to the release.

---

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for full details.
