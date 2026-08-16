## BerryCore v0.87.6

STT lab is now a complete `qpkg` port: Term49 text UI, ice/black web, Android file-drop.

### Added

- **`qpkg install sttlabs`** — same package as `sttlab` (`web-sttlab-1.1.zip`)
- **`sttlabs`** — Term49 text menu (`sttlabs demo`, `sttlabs rec`, `sttlab term`)
- **`/term`** — no-JS page for berry-browser
- **STT Drop 1.2.1** — `share/sttlab/STT-Drop.apk` (writes WAV to `/sdcard/sttmic`; no HTTP)

### Use

```sh
qpkg install vosk
qpkg install sttlabs
sttlabs
sttlabs demo
berry-browser http://127.0.0.1:8093/
berry-browser http://127.0.0.1:8093/term
```

Copy `$NATIVE_TOOLS/share/sttlab/STT-Drop.apk` to Documents and install **STT Drop** (not the old pink STT Mic). The lab watches `/sdcard/sttmic`.

`qpkg install sttlab` and `qpkg install sttlabs` install the same zip. Engine is still `qpkg install vosk`.

See `RELEASE_FILES_v0.87.6.txt` for checksums.
