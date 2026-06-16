BerryCore **v0.81.1** adds the **bcllm** on-device LLM port and ships the **BerryCore Helper** Android APK for easy sideloading. Also includes the v0.81 core packages (ncdu, chafa, dcron, wget) and the fixed **`qpkg update`** upgrade path.

---

## bcllm 1.2.1 — on-device LLM (new port)

Run **SmolLM / Gemma / Qwen** models locally on BB10 via llama.cpp — no cloud API key required.

```bash
qpkg ports                    # lists bcllm
qpkg install bcllm

ai download smollm2_135m      # ~101 MB, needs wget + Wi-Fi
ai                            # interactive menu
ai "What is the capital of France?"
ai web                        # browser chat at http://127.0.0.1:8080/
```

**Requires:** `wget` (core package), Wi-Fi for first model download  
**Install path:** `/accounts/1000/shared/misc/bcllm/`  
**Help:** `$NATIVE_TOOLS/../bcllm/share/bcllm/HELP.txt` or `cat /accounts/1000/shared/misc/bcllm/share/bcllm/HELP.txt`

Optional profile setup:

```bash
sh /accounts/1000/shared/misc/bcllm/setup-ai.sh
```

---

## BerryCore Helper APK

**BerryCore Helper** is an Android APK that bundles BerryCore for sideloading on BB10 (Android runtime). Install BerryCore without a PC — open the app and tap install.

1. Download **`berrycore-helper.apk`** from this release
2. Sideload with Sachesi, Chrome extension, or your usual tool
3. Open **BerryCore Helper** on the device and run the installer
4. After install, run **`qpkg update`** to pick up v0.81.1 (includes bcllm `qpkg` support)
5. Then: **`qpkg install bcllm`**

---

## Upgrade from v0.81

```bash
qpkg update
# or manually:
sh install.sh --upgrade -y --dir $NATIVE_TOOLS
. $NATIVE_TOOLS/env.sh
```

Verify:

```bash
cat $NATIVE_TOOLS/VERSION    # 0.81.1
grep bcllm $NATIVE_TOOLS/bin/qpkg
qpkg install bcllm
```

---

## Also in this release line (v0.81)

**Core packages** (auto-install on upgrade):
- **ncdu 1.22** — disk usage TUI
- **chafa 1.14.4** — terminal image viewer
- **dcron 4.5** — cron scheduler
- **wget 1.25.0** — HTTPS downloads

**qpkg update fix** — non-interactive upgrade with per-package install stamps.

---

BerryCore v0.81.1 — June 2026
