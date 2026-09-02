BerryCore **v0.82** bundles **on-device AI (bcllm 1.2.1)** in the main install and ships an updated **BerryCore Helper APK** for sideloading.

---

## On-device AI — bcllm 1.2.1 (bundled)

BerryCore AI (llama.cpp) is included in **`berrycore.zip`** as core package **`ai-bcllm-1.2.1.zip`**. After install, binaries live at:

`/accounts/1000/shared/misc/bcllm/`

`install.sh` moves the bundled tree out of the berrycore directory and links **`ai`** into `$NATIVE_TOOLS/bin`.

```bash
ai download smollm2_135m      # ~101 MB, needs wget + Wi-Fi
ai                            # interactive menu
ai "What is the capital of France?"
ai web                        # http://127.0.0.1:8080/
```

**Requires:** `wget` (core package), Wi-Fi for first model download

---

## BerryCore Helper APK

Sideload **`berrycore-helper.apk`** to install BerryCore from the BB10 Android runtime — no PC required.

1. Download `berrycore-helper.apk` from this release
2. Sideload (Sachesi, Chrome extension, etc.)
3. Open **BerryCore Helper** → run installer
4. Copy to Documents if prompted, then: `sh install.sh --upgrade -y`

---

## Install on Passport

**Option A — Helper APK:** sideload `berrycore-helper.apk` → install from app

**Option B — Manual:**
```bash
# copy berrycore.zip + install.sh to device
sh install.sh --upgrade -y --dir $NATIVE_TOOLS
. $NATIVE_TOOLS/env.sh
```

**Option C — qpkg port only** (if already on BerryCore ≥0.81):
```bash
qpkg install bcllm
ai download smollm2_135m
ai
```

Or standalone tarball:
```bash
tar xzf bcllm-passport-1.2.1.tar.gz -C /accounts/1000/shared/misc/
sh /accounts/1000/shared/misc/bcllm/setup-ai.sh
```

---

## Also included (core packages)

- **ncdu 1.22** — disk usage TUI
- **chafa 1.14.4** — terminal image viewer
- **dcron 4.5** — cron scheduler
- **wget 1.25.0** — HTTPS downloads

**Upgrade:** `qpkg update` or `sh install.sh --upgrade -y --dir $NATIVE_TOOLS`

Verify:
```bash
cat $NATIVE_TOOLS/VERSION    # 0.82
which ai
ls /accounts/1000/shared/misc/bcllm/bin/
```

---

## Release assets

| File | Purpose |
|------|---------|
| `berrycore.zip` | BerryCore v0.82 (includes ai-bcllm) |
| `berrycore-helper.apk` | Sideload installer |
| `install.sh` | Upgrade script (relocates bcllm → misc/bcllm/) |
| `bcllm-passport-1.2.1.tar.gz` | Standalone AI install |
| `ports/ai-bcllm-1.2.1.zip` | qpkg port package |

Rebuild: `./release/build-berrycore-0.82.sh`

---

BerryCore v0.82 — June 2026
