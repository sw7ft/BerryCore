# bcllm port (BerryCore AI 1.2.1)

On-device **LLM assistant** for BB10 Passport — interactive chat, agent mode, and web UI via llama.cpp.

## Users

```bash
qpkg install bcllm
sh /accounts/1000/shared/misc/bcllm/setup-ai.sh   # optional: add to ~/.profile
ai download smollm2_135m
ai
```

`qpkg install` also symlinks **`ai`** into `$NATIVE_TOOLS/bin`.

## Requirements

- **wget** — model downloads (BerryCore core package)
- **Wi-Fi** — first-time model download from Hugging Face
- **~100–400 MB** free per model (not bundled in port)

## Install location

```
/accounts/1000/shared/misc/bcllm/
  bin/ai              Main program (~25 KB shell + llama binaries)
  bin/llama-completion
  bin/llama-server    Web chat backend
  etc/ai.conf         User settings
  etc/models.conf     Model catalog + URLs
  models/             Downloaded .gguf weights
  web/index.html      BB10-friendly browser chat UI
```

## Build (maintainers)

```bash
cd ports/bcllm
./build-port.sh ../../bcllm-passport-1.2.1.tar.gz
```

Output: `ports/ai-bcllm-1.2.1.zip` and `berrycore/packages/ai-bcllm-1.2.1.zip`

## Models

| ID | Size | Notes |
|----|------|-------|
| `smollm2_135m` | 101 MB | Default, fastest |
| `smollm2_360m` | 259 MB | Balanced |
| `gemma3_270m` | 241 MB | Google Gemma 3 |
| `qwen25_0_5b` | 352 MB | Completion mode |

See `docs/USAGE.md` in the installed tree for full list.
