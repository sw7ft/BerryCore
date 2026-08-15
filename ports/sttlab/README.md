# STT lab (sttlab)

Compare PocketSphinx and Vosk on the same clip. Port **8093**.

## Install

Bundled in BerryCore, or:

```sh
qpkg install sttlab
qpkg install vosk
```

`sttlab` is the web UI. `vosk` is the offline engine + small English model.

## Usage

```sh
sttlab
berry-browser http://127.0.0.1:8093/
```
