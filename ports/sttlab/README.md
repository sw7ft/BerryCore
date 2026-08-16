# STT lab (sttlab / sttlabs)

Compare PocketSphinx and Vosk on the same clip. Port **8093**.
Ice/black UI, Term49 text front-end, Android file-drop inbox.

## Install

```sh
qpkg install sttlabs
qpkg install vosk
```

`qpkg install sttlab` is the same package.

## Usage

```sh
sttlab                          # web lab on :8093
sttlabs                         # Term49 text menu
sttlabs demo                    # official goforward clip
berry-browser http://127.0.0.1:8093/
berry-browser http://127.0.0.1:8093/term
```

Android: copy `$NATIVE_TOOLS/share/sttlab/STT-Drop.apk` to Documents and install **STT Drop** (not the old pink STT Mic). The APK writes WAV to `/sdcard/sttmic`; the lab watches that folder.

`sttlab` is the daemon + web UI. `vosk` is the offline engine + small English model.
