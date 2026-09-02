BerryCore **v0.80** adds **dcron 4.5** — a lightweight cron scheduler for BB10 — as a **core package** (same model as wget 1.25.0). Also includes **wget 1.25.0** and **qpkg fixes** from the v0.79 line if you have not upgraded yet.

---

## dcron 4.5 (core package)

Scheduled jobs on BB10 — no separate port install. Ships in `berrycore.zip` and installs with upgrade or fresh install.

**Binaries:**

| Command | Role |
|---------|------|
| `cron-start` | Start **crond** in background |
| `cron-stop` | Stop **crond** |
| `crontab` | Edit/list jobs (`CRON_USER=berrycore` by default) |

**Data under `$NATIVE_TOOLS/cron/`:**

- `crontabs/` — per-user crontab files
- `cronstamps/` — anacron-style catch-up after sleep
- `cron.d/` — drop-in system jobs
- `crond.log` — daemon log

**Quick start:**

```bash
qpkg update
cron-start
export EDITOR=nano
crontab -e
crontab -l
```

**Notes:**

- dcron does **not** load `~/.profile` — use full paths in job commands
- Jobs run via `/bin/sh -c`; BerryCore tools are on PATH after `env.sh`
- Keep **crond running** (`cron-start`); BB10 may miss ticks while asleep — `cronstamps` help catch up

Example: `crontab $NATIVE_TOOLS/cron/example.crontab`

---

## GNU Wget 1.25.0 (core package)

If upgrading from v0.78 or earlier:

- GNU Wget **1.25.0** with OpenSSL 1.1.1w
- Wrapper sets `SSL_CERT_FILE` for HTTPS

```bash
wget --version
wget -O- https://example.com/ | head
```

---

## qpkg fixes

- Auto-detect `NATIVE_TOOLS` when `env.sh` was not sourced
- QNX-safe port downloads

```bash
. $NATIVE_TOOLS/env.sh
qpkg install python3
```

---

## Ports (via qpkg — not in berrycore.zip)

| Port | Notes |
|------|-------|
| `claude-code` | Claude Code CLI (BYO API key) |
| `rocketchat` | Rocket.Chat client |
| `node-term49` | Node.js for Term49 (dependency for some ports) |

---

## Upgrade

```bash
# Download berrycore.zip + install.sh from this release, then:
sh install.sh --upgrade
. $NATIVE_TOOLS/env.sh
```

Verify:

```bash
cat $NATIVE_TOOLS/VERSION    # 0.80
cron-start && crontab -l
wget --version               # 1.25.0
```

---

BerryCore v0.80 — June 2026
