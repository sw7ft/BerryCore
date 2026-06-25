# Berry Bridge Agent (bundled in BerryCore)

On-device executor for the Berry Bridge desktop app: watches JSON jobs dropped via SMB at `documents/berrybridge/inbox/`, installs BerryCore, bootstraps SSH on port 2022, writes `status.json`.

## Install path (after BerryCore install)

```
/accounts/1000/shared/misc/berrybridge-agent/
/accounts/1000/shared/documents/berrybridge/inbox/   ← Bridge drops jobs
/accounts/1000/shared/documents/berrybridge/status.json
```

Commands are linked into `$NATIVE_TOOLS/bin/` during install.

## Rebuild core zip

```bash
./ports/berrybridge-agent/build-port.sh berrybridge-agent-bb10-0.1.0.tgz
```

Output: `berrycore/packages/berrybridge-agent-0.1.0.zip`

## Manual test

```sh
berrybridge-run-job ping
berrybridge-run-job --once
berrybridge-ensure-sshd
```

Docs in `$NATIVE_TOOLS/../berrybridge-agent/docs/` or `misc/berrybridge-agent/docs/`.
