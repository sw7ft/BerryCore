## BerryCore v0.84.0

Bundles **Berry Bridge agent 0.1.0** — the on-device executor for the Berry Bridge desktop app.

### Berry Bridge agent (bundled core package)

Not a qpkg port — installs automatically with BerryCore upgrade or fresh install.

| Path | Purpose |
|------|---------|
| `/accounts/1000/shared/misc/berrybridge-agent/` | Agent binaries and libs |
| `documents/berrybridge/inbox/` | Bridge drops JSON jobs via SMB |
| `documents/berrybridge/status.json` | Status for desktop app |
| `documents/berrybridge/agent.log` | Agent log |

**Commands** (linked into `$NATIVE_TOOLS/bin/`):

```sh
berrybridge-run-job ping          # health check
berrybridge-run-job --once        # process inbox once
berrybridge-ensure-sshd           # start BerryCore sshd on port 2022
```

**Job types:** `ping`, `install_berrycore`, `install_ssh_key`, `ensure_sshd`

### Upgrade

```sh
qpkg update
# or manual:
# copy berrycore.zip + install.sh to device, then:
sh install.sh --upgrade
```

### Verify

```sh
cat $NATIVE_TOOLS/VERSION          # 0.84.0
ls /accounts/1000/shared/misc/berrybridge-agent/bin/
berrybridge-run-job ping
```

### Assets

| File | SHA256 |
|------|--------|
| `berrycore.zip` | `6de55706dcdb2cfb020a1ca3f70f8704c35d2046cc7c308b87aac51d536d990d` |
| `install.sh` | `0d1c7139d9892f74c8ecc55bdf12b586de1ac7ca0a22b500a9539dfc94b9886b` |
