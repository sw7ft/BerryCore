# Changelog

All notable changes to BerryCore will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

---

## [gps-1.0] - 2026-08-29

### Added

- **gps** qpkg — Term49 CLI for BB10 geolocation (BPS). Last-known and live GNSS/hybrid fixes, satellite list, PPS dump. `qpkg install gps`.

---

## [sensors-1.0] - 2026-08-29

### Added

- **sensors** qpkg — Term49 CLI for BB10 motion sensors (BPS). Accel, gyro, mag, gravity, linaccel, APR, compass, orientation, light, proximity, holster. `qpkg install sensors`. Alias: `sensor`. PPS dump: `sensors pps`.

---

## [0.88.0] - 2026-08-22

### Added

- **Setup hub** — branded on-device guide at `http://127.0.0.1:8098/` (Home, Apps, Packages, Core, Manual, Settings). Ubuntu aubergine, orchid accents, BB10 Browser safe.
- **Packages** — searchable qpkg table; Install / Reinstall from the hub (`QPKG_YES` for non-interactive install).
- **Core** — default userland inventory (`qpkg catalog` / `qpkg bins`) with present/missing marks.
- **Settings** — hub themes (Aubergine, Midnight, Ember, Paper) plus SW7FT / Patreon / GitHub. Term49 colors follow the theme.
- **talkbutton** qpkg — play/pause dictation (QSA mic, warm Vosk, system clipboard + Hub). `qpkg install talkbutton`. Requires `qpkg install vosk`.
- Apps catalog: QNX Desktop, Term49 Web, BerryPy, Voice Agent, BerrySnip.

### Changed

- **Term49 splash** — short hub line: `Running locally at 127.0.0.1:8098`. Setup still auto-starts on login (`setup boot`) and posts that address on the Hub banner.
- **Apps** — Start/Stop show Starting/Stopping immediately, then a green lamp when the port is up.
- **Manual** — same hub chrome as the rest of the guide.
- **VERSION** → 0.88.0

---

## [0.87.9] - 2026-08-22

### Changed

- **Term49 splash** — official launch screen: white 3-wide BERRYCORE, 7-dot blackberry mark, Ubuntu aubergine (`#300A24`), paper text, orange cursor (`share/term49-splash.sh`, `share/term48rc`).
- **VERSION** → 0.87.9

---

## [0.87.8] - 2026-08-18

### Added

- **stocks** / **ticker** — ES5 ticker and research on port **8096** (`The Tape`)
- **Custom lists**, per-symbol up-tick hub banners, price above/below alerts
- **PPS notify** — same `/pps/services/notify/control` path as Rocket.Chat
- **waterwaymap** / **waterway** qpkg — OSM river-basin map on port **8095**
- Bundled `packages/web-stocks-1.0.zip` and `packages/web-waterwaymap-1.0.zip`

### Changed

- **VERSION** → 0.87.8
- **CATALOG / FEATURED / PACKAGES / env.sh** — `stocks`, `ticker`, `waterwaymap`, `waterway`

---

## [0.87.7] - 2026-08-18

### Added

- **library** / **books** — on-device EPUB/HTML shelf and reader on port **8094**
- **Formats** — EPUB, FB2, HTML/XHTML, Markdown, plain text
- **Categories** — expandable user-editable shelves (file, rename, reorder)
- **Archive / import / delete** — zip the shelf to Documents; import from Documents; remove a title
- **Bell Labs UNIX + xv6** — bundled under `share/books/classics/` (V7 Volume 2 papers, Ritchie essays, MIT xv6 book)

### Changed

- **VERSION** → 0.87.7
- **CATALOG / env.sh** — `library` and `books` listed with `games`

---

## [0.87.6] - 2026-08-16

### Added

- **sttlabs** — Term49 text UI (`sttlabs` / `sttlab term` / `sttlabs demo`)
- **`qpkg install sttlabs`** — alias for `sttlab` (`web-sttlab-1.1.zip`)
- **STT Drop APK** — bundled at `share/sttlab/STT-Drop.apk` (file-drop, no HTTP)
- **Android inbox** — lab watches `/sdcard/sttmic` for WAV + `.req`

### Changed

- **sttlab 1.1** — ice/black web UI, `/term` no-JS page, Python fallback like games
- **VERSION** → 0.87.6
- **CATALOG / FEATURED / PACKAGES / env.sh** — `sttlabs` listed with `sttlab`

---

## [0.87.5] - 2026-08-15

### Added

- **sttlab** — STT compare lab on port **8093** (`sttlab` / `sttlab stop` / `sttlab status`). Bundled in core and as `qpkg install sttlab`
- **vosk** qpkg port — QNX ARM `libvosk.so` + `vosk.bin` + small English model (`qpkg install vosk`). Not bundled in `berrycore.zip`
- **vosk** wrapper in core PATH — prints `qpkg install vosk` until the engine is installed

### Changed

- **VERSION** → 0.87.5
- **CATALOG / FEATURED / PACKAGES / env.sh** — `sttlab` and `vosk` listed with `games`

---

## [0.87.4] - 2026-08-15

### Added

- **games** — BerryCore Games menu on port **8766** (`games` / `games stop` / `settings games-on`). ES5 splash + BerryCraft, BerryFly, BerryBoat, BerryDig, BerryMoto, BerryMX
- **bb-games** qpkg port — bundled `packages/games-bb-games-1.0.zip` and `ports/games-bb-games-1.0.zip` (`qpkg install bb-games`)

### Changed

- **VERSION** → 0.87.4
- **CATALOG / FEATURED / env.sh** — `games` listed next to `tools`

---

## [0.87.3] - 2026-08-14

### Added

- **Term49 launch splash** — 256-color TERM49 / BerryCore wordmark on login (`share/term49-splash.sh`, `splash` to redraw)
- **Berry Term49 theme** — Courier Bold, pale orchid on deep berry (`share/term48rc`, installed to `~/.term48rc` if missing)

### Changed

- **sample_profile / install.sh** — `BERRYCORE_QUIET=1` skips the plain env.sh banner and remote MOTD wait so the splash owns the launch screen
- **env.sh** — honors `BERRYCORE_QUIET=1` to suppress the ASCII welcome box
- **VERSION** → 0.87.3

---

## [0.87.2] - 2026-07-05

### Added

- **berrycore.html in Documents** — `install.sh` copies the catalog guide to `/accounts/1000/shared/documents/berrycore.html` on fresh install and upgrade
- **Bundled catalog** — `berrycore/doc/berrycore.html` included inside `berrycore.zip` (regenerate via `utilities/build-catalog-html.sh`)

---

## [0.87.1] - 2026-07-05

### Fixed

- **qpkg custom install dirs** — Ports like openport/telnet/dropbear now install under the active `NATIVE_TOOLS` tree (e.g. `berrycore4/`) instead of always writing to shared `misc/` when the install dir is not named `berrycore`
- **qpkg port extract** — Staging extract (`unzip` → `cp`) avoids QNX "cannot delete old share/doc/…" errors when reinstalling from a second Term49 session

---

## [0.87.0] - 2026-07-05

### Added

- **berrycore.html** — Self-contained ES5 dark-themed catalog: intro, install guides, copy-pastable commands, searchable featured + full qpkg catalog (~116 packages)
- **utilities/build-catalog-html.sh** — Regenerates `berrycore.html` from `ports/PACKAGES` and `ports/FEATURED`

### Removed

- **berrycore-helper.apk** — Dropped from GitHub releases; use `berrycore.html` + `install.sh` instead

### Changed

- **VERSION** → 0.87.0 — Consolidated release bundling Phase 2 ports, two-tier qpkg catalog, XPS utilities, and HTML catalog guide

---

## [0.86.0] - 2026-07-05

### Added

- **qpkg two-tier catalog** — `qpkg ports` shows featured ports; full catalog via `qpkg search`, `qpkg available`, `qpkg show`, `qpkg install` reads `ports/PACKAGES`
- **82 XPS utility ports** — individual `util-*` zips (less, lha, cabextract, minicom, cpmtools, iperf3, etc.) in full PACKAGES catalog
- **bbm 1.0.0** — Berry Bridge Messenger native relay client (`qpkg install bbm`)
- **ftp, ping, tcpdump qpkg ports** — `qpkg install ftp ping tcpdump` (ftp was core-only before; ping/tcpdump now installable)
- **ports/ping/** and **ports/tcpdump/** — build scripts for util-ping and util-tcpdump port zips

### Changed

- **openport 1.0.0** — Rebuilt from XPS Passport tarball (25,672 bytes); `openport-canlog` preserved as symlink
- **util-ftp 1.0.0** — Rebuilt from XPS tarball; dual output to `ports/` and `berrycore/packages/`
- **rocketchat 3.0** — RocketChat Navigator v3 from Passport upgrade
- **telegram 2.1** — Telegram v2.1 with enhanced UI
- **youtube 2.0** — YouTube Navigator v2 with bundled static UI

### Fixed

- **qpkg catalog cache** — Prefer local cache when GitHub raw CDN is stale or QNX `stat` mtime unavailable

- **VERSION** → 0.86.0

---

## [0.85.0] - 2026-07-01

### Added

- **openport 1.0.0** — OpenPort 2.0 OBD diagnostic CLI port (`qpkg install openport`)
  - Built on Passport (armle-v7 / QNX 8) via bb10-kitchen-sink
  - Installs to `misc/bin/`; symlinks in `$NATIVE_TOOLS/bin/`
- **util-ftp 1.0.0** — Bundled FTP client (`ftp`) + server (`bftpd`) for Passport
  - netkit-ftp 0.17 client, bftpd 5.4 server with QNX patches
  - Sample config: `$NATIVE_TOOLS/etc/bftpd.conf.example`, share dir `ftp-root/`
- **berry-browser 1.0.27** — Full Chromium browser for Passport (replaces content-shell-term49)
  - **`berry-browser`** — primary CLI browser via content_shell (Term49/SSH): readable text, links, title, interactive REPL
  - **`browse`** — alias for berry-browser
  - **`berry-browser-screen`** — full-screen on native QNX only (upstream launcher renamed)
  - **`content_shell`** — low-level headless engine
  - Port: `web-berry-browser-1.0.27.zip`; legacy `qpkg install content-shell-term49` aliases to berry-browser
- **telnet 0.17** — Classic netkit TELNET client (`qpkg install telnet`)
- **usbdbg 1.0.0** — Generic USB serial debugger (`qpkg install usbdbg`)
- **dropbear 2026.91** — Lightweight SSH client (`dbclient`/`ssh`) and server (`qpkg install dropbear`)
- **maps 1.0** — OpenStreetMap navigation from BerryPy/BerryStore (`qpkg install maps`, port 8090)
- **youtube 1.0** — YouTube search and streaming from BerryPy/BerryStore (`qpkg install youtube`, port 8070)
- **telegram 1.0** — Telegram Messenger from BerryPy/BerryStore (`qpkg install telegram`, port 8010)

### Changed

- **vim 8.0 → 9.1.2148** — Major upgrade (huge features, terminal + ncursesw, QNX os_qnx fix)
  - Replaces `vim-8.0.zip` with `vim-9.1.2148.zip` in core bundle
  - `VIMRUNTIME` set in `env.sh` → `share/vim/vim91`
- **VERSION** → 0.85.0

---

## [0.84.0] - 2026-06-24

### Added

- **berrybridge-agent 0.1.0** — Bundled core package for Berry Bridge desktop app
  - Installs to `/accounts/1000/shared/misc/berrybridge-agent/`
  - Watches `documents/berrybridge/inbox/` for JSON jobs (install BerryCore, SSH keys, ping)
  - `install.sh` relocates agent and runs post-install (inbox setup, watcher, sshd helpers)
  - Commands in `$NATIVE_TOOLS/bin/`: `berrybridge-run-job`, `berrybridge-ensure-sshd`, `berrybridge-agent`

### Changed

- **VERSION** → 0.84.0

---

## [0.83.0] - 2026-06-17

### Added

- **util-ping 1.0.0** — ICMP ping for network reachability tests
- **util-tcpdump 4.99.5** — Network packet capture and analysis
- **util-nixtla-audio 1.0.0** — BB10 audio playback/recording (`play-audio`, `demoPlayWav`, `demoCaptureEco`)

### Changed

- **ffmpeg 4.2.2 → 6.1.2** — Major upgrade; adds `ffprobe`, better codec support for `play-audio`
- **tig 2.5.0 → 2.6.1** — Git TUI upgrade with bundled `etc/tigrc` (`TIGRC` set in env.sh)
- **VERSION** → 0.83.0

---

## [0.82.0] - 2026-06-XX

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

