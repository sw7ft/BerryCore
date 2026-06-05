# dcron port (dcron 4.5)

Lightweight **cron** for BB10/QNX — **crond** + **crontab**, anacron-style catch-up via cronstamps. Ships as a **BerryCore core package** (like wget), not a separate qpkg port.

## Users

Installs with BerryCore upgrade or fresh install:

```bash
qpkg update
cron-start
export EDITOR=nano
crontab -e
crontab -l
```

## Build (maintainers)

```bash
cd ports/dcron
./build-port.sh ../../dcron-bb10-4.5.tgz
```

Output: `berrycore/packages/dcron-4.5.zip`

## Installed layout (`$NATIVE_TOOLS`)

| Path | Purpose |
|------|---------|
| `bin/crontab` | Wrapper (`CRON_USER`, crontabs dir) |
| `bin/crontab.bin` | ARM binary |
| `bin/cron-start` | Start crond |
| `bin/cron-stop` | Stop crond |
| `sbin/crond` | Daemon |
| `cron/` | start/stop scripts, logs, crontabs data |

Upstream docs in source tarball: `cron-pkg/docs/BB10-CRON-ASSESSMENT.md`
