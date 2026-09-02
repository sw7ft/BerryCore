# BerryCore v0.76.1 – Git SSL Fix

**Release Date:** February 26, 2026

---

## Bug Fix: Git HTTPS Now Works

`git clone`, `git pull`, and `git push` over HTTPS were failing with SSL errors because `GIT_SSL_CAINFO` was not being set in the git wrapper. This is now fixed — git correctly uses BerryCore's `ssl/cert.pem` CA bundle for all HTTPS operations.

| Tool | What was fixed |
|------|---------------|
| **git 2.47.2** | Added `GIT_SSL_CAINFO` to wrapper so HTTPS works |
| **curl 8.12.1** | No change — was already working |

---

## Install / Upgrade

**Upgrade from v0.76:**

```bash
qpkg update
```

**Manual install:**

```bash
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76.1/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.76.1/install.sh
chmod +x install.sh
./install.sh
```

---

## Assets

Attach these to the release:
- `berrycore.zip` (~170 MB)
- `install.sh`
