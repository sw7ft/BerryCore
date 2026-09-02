## BerryCore v0.87.5

Offline speech-to-text: STT lab in core, Vosk as a real `qpkg` port.

### Added

- **`sttlab`** on port **8093** — `sttlab` / `sttlab stop` / `sttlab status`
- **`qpkg install sttlab`** — `web-sttlab-1.0.zip` (also bundled in `berrycore.zip` under `packages/`)
- **`qpkg install vosk`** — `ai-vosk-1.0.zip` (engine + small English model; not in the core zip)

### Use

```sh
qpkg install vosk
sttlab
berry-browser http://127.0.0.1:8093/
vosk clip.wav
```

`qpkg install vosk` pulls `ai-vosk-1.0.zip` from the ports catalog and extracts `bin/`, `lib/`, and `share/` into `$NATIVE_TOOLS` (usually `/accounts/1000/shared/misc/berrycore`).

See `RELEASE_FILES_v0.87.5.txt` for checksums.
