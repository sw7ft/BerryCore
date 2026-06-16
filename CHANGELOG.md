# Changelog

All notable changes to BerryCore will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

---

## [0.82] - 2026-06-16

### Added

- **ai-bcllm 1.2.1** — On-device LLM bundled as core package (`berrycore/packages/ai-bcllm-1.2.1.zip`)
  - BerryCore AI (llama.cpp) installs to `/accounts/1000/shared/misc/bcllm/`
  - `install.sh` relocates bundled bcllm out of the berrycore tree after install
  - PATH symlinks: `ai`, `AI`, `bcllm` in `$NATIVE_TOOLS/bin`
- **BerryCore Helper APK** — Rebuilt with BerryCore v0.82 assets for sideload install

### Changed

- **bcllm qpkg port** — Renamed zip to `ports/ai-bcllm-1.2.1.zip` (category `ai`)
- **motd.txt** — Highlights on-device AI
- **VERSION** → 0.82

---

## [0.81.1] - 2026-06-15

### Added

- **bcllm 1.2.1** — On-device LLM assistant port (`qpkg install bcllm`)
  - llama.cpp binaries, interactive `ai` CLI, agent mode, web UI
  - Installs to `/accounts/1000/shared/misc/bcllm/` with PATH symlinks
  - Requires **wget** for model downloads; models not bundled
- **BerryCore Helper APK** — Android sideload app bundling BerryCore installer for BB10

### Changed

- **qpkg** — `bcllm` port install handler (misc/bcllm layout, ai symlinks)

---

## [0.81] - 2026-06-11

### Added

- **ncdu 1.22** — Interactive disk usage analyzer (ncurses TUI)
  - Core package `ncdu-1.22.zip` — wrapper sets `TERM=xterm-256color`
  - Use Term49 or `ssh -t` for interactive UI; export scans to `/var/tmp`
- **chafa 1.14.4** — Terminal image viewer (JPEG, PNG, GIF, QOI, XWD)
  - Core package `chafa-1.14.4.zip` — `chafa`, `chafa-show`, bundled `libchafa.so.9`
  - Wrapper sets `LD_LIBRARY_PATH` and `TERM` for BerryCore layout

### Fixed

- **qpkg update** — Runs `install.sh --upgrade -y` into `$NATIVE_TOOLS` (no manual prompts)
- **install.sh** — Adds `--upgrade`, `-y`, `--dir` flags; package stamps via `.berrycore_pkg_stamps/`
- **pbpkgadd** — Writes per-package install stamps for reliable upgrade detection

---

## [0.80] - 2026-06-05

### Added

- **dcron 4.5** — Lightweight cron scheduler for BB10 (crond + crontab)
  - Core package `dcron-4.5.zip` installs to `$NATIVE_TOOLS` (`bin/`, `sbin/`, `cron/`)
  - Wrappers: `crontab`, `cron-start`, `cron-stop` (BerryCore paths, `CRON_USER=berrycore`)
  - Anacron-style `cronstamps` for missed jobs after device sleep
  - Install: BerryCore upgrade / fresh install (not a qpkg port)

---

## [0.79] - 2026-06-05

### Changed

- **wget** 1.20.3 → **1.25.0** — GNU Wget with static OpenSSL 1.1.1w and Mozilla CA bundle (same SSL generation as curl 8.12.1 / git 2.47.2)
  - Wrapper sets `SSL_CERT_FILE` (BerryCore `ssl/cert.pem` or bundled `share/wget/certs/cacert.pem`)
  - Install: BerryCore upgrade / fresh install (`wget-1.25.0.zip` in core packages)
- VERSION bumped to 0.79

### Fixed

- **qpkg** — Auto-detect `NATIVE_TOOLS` when env.sh was not sourced; QNX-safe port downloads

---

## [0.78] - 2026-06-04

### New Ports: Claude Code, RocketChat, Mutt Setup

**Headline:** Claude Code AI agent for BB10, RocketChat Navigator, and interactive Mutt email setup.

### Added

#### New Ports (2)

- **claude-code** — Anthropic Claude Code 2.1.91, patched for QNX/Term49 (45 MB installed)
  - Terminal AI coding agent: edit files, run commands, interactive sessions
  - BB10 patches: Node `--jitless`, fetch polyfill (no WASM), Bash-tool freeze fix, BB10 context
  - **Requires:** `node-term49` (`qpkg install node-term49`)
  - **Setup:** `claude-setup` saves Anthropic API key to `~/claude.key`
  - Run: `claude -p "your prompt"` or `claude` for interactive mode
  - BerryCore help: `claude help` | Claude CLI help: `claude --help`
- **rocketchat** — RocketChat Navigator for BB10 (92 KB)
  - Web app for private groups and DMs on port 8026
  - **Requires:** `python3`
  - Run: `rocketchat` (background) or `rocketchat -f` (foreground)

#### Mutt

- **mutt-setup** — Interactive wizard for IMAP/SMTP; creates `~/.muttrc`

### Changed

- **rocketchat** — Runs in background with nohup by default
- **CATALOG** — Added `claude`, `claude-setup`, `rocketchat`
- VERSION bumped to 0.78

### Statistics

- **Port Count**: 17 installable ports (via `qpkg ports`)
- **Binary Count**: 100+

---

## [0.77] - 2026-03-17

### New Ports & Catalog Update

**Headline:** Three new ports — content-shell-term49 (Chromium 120 headless), wifi-chat (P2P over WiFi), berrybot (teaching assistant). Full catalog sync.

### Added

#### New Ports (3)
- **content-shell-term49** — Chromium 120 headless browser for Term49 (62 MB)
  - DOM dump to stdout, HTTP/HTTPS
  - Run: `content_shell http://example.com 2>/dev/null`
  - Replaces chromium-shell
- **wifi-chat** — P2P chat over WiFi/local network (12 KB)
  - UDP discovery, TCP messages
  - Run: `wifi-chat [name]`
- **berrybot** — Command-line teaching assistant (600 KB)
  - Non-AI help for Linux, QNX, bash, BerryCore
  - Run: `bot grep`, `bot lessons`

#### android-apps (Term49 Dashboard & Bridge)

- **term49-dashboard** — Dashboard for Term49 terminal
- **term49-bridge** (Bridge) — Bridge app for Term49
- Also includes: RDP, Kiwi Browser, Launcher, XServer, SublimeText, BB10Terminal, ExFAT
- Install: `qpkg install android-apps` → `/accounts/1000/shared/misc/android-apps/`

### Changed

- **CATALOG** — Added all port binaries: tools, node, npm, content_shell, wifi-chat, bot, tetris, qnxdesktop, voiceagent, term49-web
- VERSION bumped to 0.77

### Available Ports (Node.js, bb-tools, etc.)

- **node-term49** — Node.js v22, npm 10.5.1 (--jitless for QNX)
- **bb-tools** — Web tools: dashboard, drawing-board, editors, compass, virtual-keyboard (port 8765)

### Statistics

- **Port Count**: 14 installable ports
- **Core Packages**: 77 (includes berrybot)
- **Binary Count**: 100+

---

## [0.76] - 2026-02-22

### Updated git & curl with Modern SSL

**Headline:** Upgraded **git** (2.26→2.47.2) and **curl** (7.76→8.12.1) to work with modern HTTPS and SSL/TLS.

### Added

- **pass-1.0** (util-pass) – Password manager (gpg-encrypted store). Requires gpg for full use; git included in BerryCore.

### Changed

- **git** 2.26.0 → **2.47.2** – Wrapper sets GIT_EXEC_PATH, GIT_TEMPLATE_DIR, CA certs for HTTPS clone
- **curl** 7.76.0 → **8.12.1** – Wrapper sets CURL_CA_BUNDLE for HTTPS; includes gcal, tcal
- Both use BerryCore's `ssl/cert.pem` for modern SSL verification
- VERSION bumped to 0.76

### Added

#### New Ports (4)
- **qnxdesktop** - Windows 98 style web desktop (753 KB)
  - File Explorer for QNX Shared and SD Card
  - Mail client (IMAP/SMTP) with folders, send/receive
  - AI Chat (Claude API integration)
  - Notes and code editor
  - System information panel
  - Auto-installs Flask + requests on first run
- **voiceagent** - AI voice assistant (23 KB)
  - Push-to-talk with OpenAI Whisper, GPT-4o, TTS
  - Web UI on port 8085
- **chromium-shell** - Headless Chromium Content Shell (21 MB)
  - DOM dump to stdout, HTTP proxy for external sites
  - Terminal-only browser engine for QNX
- **tetris** - Classic Tetris in pure bash (6 KB)

### Statistics

- **Port Count**: 11 installable ports
- **Core Packages**: 73
- **Binary Count**: 100+

---

## [0.75] - 2026-02-22

### QNX Desktop Release

**Headline: QNX Desktop** – A full Windows 98 style desktop environment for BlackBerry 10.

### Added

#### New Ports (4)
- **qnxdesktop** - Windows 98 style web desktop (753 KB)
- **voiceagent** - AI voice assistant (23 KB)
- **chromium-shell** - Headless Chromium Content Shell (21 MB)
- **tetris** - Classic Tetris in pure bash (6 KB)

### Changed

- Port count: 11 total (up from 7)
- VERSION bumped to 0.75

---

## [0.6.0] - 2025-10-21

### 🎉 Major Release - BerryCore Rebranding

This is the first official release under the **BerryCore** name, continuing the legacy of Berry Much OS v0.5.

### Added

#### New Packages (5)
- **nano-4.0** - User-friendly text editor (731 KB)
- **nmap-7.95** - Network exploration and security scanner (3.0 MB)
  - Includes full nmap data files (nmap-services, nmap-protocols, nmap-os-db)
  - All required libraries bundled
- **sshpass-1.06** - Non-interactive SSH password provider
- **xeyes-1.1.0** - Classic X11 demo application (~8 MB)
  - Full X11 client library stack included
  - Complete development headers for building X11 apps
- **quickjs-2024.06** - JavaScript engine and REPL (~19 MB)
  - 5 console variants: simple, shell, web, web-es5, compiler (qjsc)
  - Static libraries for development

#### New Features
- **Binary Catalog System** - Browse and discover installed binaries
  - `bclist` - List binaries by category
  - `bclist -c CATEGORY` - Filter by category (dev, net, editor, etc.)
  - `bclist -s TERM` - Search for specific tools
  - `bcinfo BINARY` - Get detailed info about a binary
  - `bcbins` - Quick list of all installed binaries
  - `CATALOG` file with ~100 documented binaries

- **Message of the Day (MOTD)** - Stay updated with latest news
  - Automatic fetching from GitHub
  - Smart caching (1-hour intervals)
  - Non-blocking, works offline
  - `bcmotd` utility for management
  - Endpoint: https://raw.githubusercontent.com/sw7ft/berrycore/main/motd.txt

- **Interactive Installation** - Choose custom installation directory
  - Default: `/accounts/1000/shared/misc/berrycore`
  - Custom: `/accounts/1000/shared/misc/YOUR_NAME`
  - Allows multiple BerryCore installations

- **Enhanced Welcome Screen** - Informative startup message
  - Shows package count
  - Quick discovery commands
  - MOTD integration

- **Improved Profile Setup** - Better first-run experience
  - Auto-configured `.profile` for new users
  - MOTD enabled by default
  - Clear instructions for existing users

### Changed

- **Rebranded** from Berry Much OS to **BerryCore**
- **Installation Path** changed from `/accounts/1000/shared/misc/clitools` to `/accounts/1000/shared/misc/berrycore`
- **Environment Variable** renamed: `CLITOOLS_ENV` → `BERRYCORE_ENV`
- **Welcome Message** now includes usage tips and discovery commands
- **Version Bumped** to 0.6 to mark new era

### Fixed

- **nmap** now includes proper data files and `NMAPDIR` environment variable
- **nano** binary permissions corrected
- **install.sh** prompt now uses POSIX-compliant `echo -n` instead of `printf`
- Legacy version detection improved

### Infrastructure

- **Documentation** greatly expanded
  - `INSTALLATION_SYSTEM.md` - Complete installation system documentation
  - `PACKAGE_CREATION_GUIDE.md` - How to create packages
  - `PRIORITY_PACKAGES.md` - Roadmap for future packages
  - `ANALYSIS.md` - Complete package inventory and analysis

- **Utility Scripts** added
  - `scan_packages.sh` - Detect macOS metadata in packages
  - `clean_packages.sh` - Remove macOS junk from packages
  - `check_sizes.py` - Analyze package sizes

### Statistics

- **Total Packages**: 69 (was 64 in Berry Much OS v0.5)
- **Total Size**: ~241 MB compressed
- **New Binary Count**: 100+ binaries available
- **Categories**: 12 (dev, shell, editor, net, vcs, sys, archive, media, data, x11, js, doc)

---

## [0.5.0] - Berry Much OS (Legacy)

Last official Berry Much OS release. Included 64 packages with core development tools, shells, networking utilities, and system tools.

### Known Issues (Resolved in 0.6)
- Installation at `/accounts/1000/shared/documents/clitools` could cause slowdowns
- No binary discovery system
- Limited documentation

---

## Legend

- 🎉 Major release
- ✨ New feature
- 🐛 Bug fix
- 📝 Documentation
- ⚡ Performance improvement
- 🔒 Security fix
- 🗑️ Deprecation
- 💥 Breaking change

---

## Future Releases

See [PRIORITY_PACKAGES.md](master-context/PRIORITY_PACKAGES.md) for planned additions.

### Tentatively Planned for 0.7
- htop - Interactive process viewer
- CMake - Modern build system
- pkg-config - Build system essential
- sed/gawk - Text processing (if missing)
- Python 3 improvements (if applicable)

