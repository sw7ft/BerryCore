## BerryCore v0.82.1

Fixes **`ai "prompt"` not working** after `qpkg install bcllm`.

### What was wrong
- The port zip accidentally shipped the full 25KB `AI` script instead of the small **`ai` wrapper** (macOS case-insensitive filesystem merged `ai` and `AI` during build).
- Invoking `ai` via a symlink broke `AI_HOME`, so quick prompts failed even when bcllm was installed.

### What's fixed
- **`ports/ai-bcllm-1.2.1.zip`** — ships `bin/ai` as the wrapper script (571 bytes), `bin/bcllm-ai` as the real assistant.
- **`qpkg install bcllm`** — always installs a real `ai` script into `berrycore/bin/` and runs `setup-ai.sh`.
- **`install.sh`** — no longer symlinks `ai` → `bcllm-ai` during relocation.

### After upgrading
```sh
qpkg update          # gets fixed qpkg from berrycore.zip
qpkg install bcllm   # reinstall / refresh ai wrapper
. ~/.profile
ai "What is QNX?"
```

Or fresh install: download **berrycore.zip** + **install.sh** from this release.

### Assets
- `berrycore.zip` — BerryCore 0.82.1 with bundled bcllm + fixed qpkg
- `install.sh`
- `berrycore-helper.apk` — sideload installer (optional)
- `ports/ai-bcllm-1.2.1.zip` — qpkg port (also via `qpkg install bcllm`)
- `bcllm-passport-1.2.1.tar.gz` — upstream source tarball
