BerryCore **v0.79** upgrades **GNU Wget to 1.25.0** with modern HTTPS (same OpenSSL generation as curl 8.12.1 / git 2.47.2), and fixes **qpkg port installs** when the shell environment was not loaded.

---

## GNU Wget 1.25.0 (core package)

Wget ships **inside BerryCore** — no separate port install. Upgrades automatically with this release.

**What's new vs wget 1.20.3:**

- GNU Wget **1.25.0** (Nov 2024 upstream)
- Static **OpenSSL 1.1.1w** (modern TLS)
- Wrapper sets **`SSL_CERT_FILE`** to BerryCore `ssl/cert.pem` (or bundled Mozilla CA fallback)

**After upgrade:**

```bash
wget --version
# GNU Wget 1.25.0 built on qnx.  +https +ssl/openssl

wget -O- https://example.com/ | head
wget -O file.zip https://example.com/file.zip
```

Run **`wget`** (the wrapper), not `wget.bin` directly, unless you set `SSL_CERT_FILE` yourself.

---

## qpkg fixes

- **Auto-detect `NATIVE_TOOLS`** from the `qpkg` script path when `env.sh` was not sourced — fixes port install failures (`/.tmp/` permission errors) and `command not found` after upgrade
- **QNX-safe downloads** — removed broken `grep -o` progress parsing on port installs

If port installs failed after a previous upgrade, try again after updating:

```bash
qpkg update
# open a new shell, or:
. $NATIVE_TOOLS/env.sh
qpkg install python3
qpkg install qnxdesktop
```

---

## Ports (via qpkg — not in this zip)

These install separately with `qpkg install <name>` after upgrading BerryCore:

| Port | Notes |
|------|--------|
| **claude-code** | Claude Code AI agent — requires `node-term49`, run `claude-setup` |
| **rocketchat** | RocketChat web app — requires `python3`, port 8026 |
| **node-term49** | Node.js v22 (--jitless) |

```bash
qpkg ports
qpkg install node-term49
qpkg install claude-code
claude-setup
```

Claude docs: [GITHUB_RELEASE_ports-claude-code.md](https://github.com/sw7ft/BerryCore/blob/main/GITHUB_RELEASE_ports-claude-code.md)

---

## Install / upgrade

**Fresh install**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.79/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.79/install.sh
chmod +x install.sh
./install.sh
```

**Upgrade from v0.78, v0.77, or earlier**

```bash
qpkg update
```

Or re-run `install.sh` from the release assets (upgrade mode preserves existing packages).

**Verify**

```bash
cat $NATIVE_TOOLS/VERSION
# 0.79

wget --version
```

---

## Release assets

| File | Size | SHA256 |
|------|------|--------|
| `berrycore.zip` | 177 MB | `9bb3cf16e446a45f917cc45951ca47bf4fb401d4b1fcb25e8a7e1ad453d9844c` |
| `install.sh` | ~8 KB | `cc1bf28722bb447fd98d252ad0ef76e72690fcfad82cb4442dabcc630f2d51f9` |

Ports (claude-code, rocketchat, python3, etc.) are **not** attached to this release — install with `qpkg install` after upgrading.

---

## Full changelog

[CHANGELOG.md](https://github.com/sw7ft/BerryCore/blob/main/CHANGELOG.md)
