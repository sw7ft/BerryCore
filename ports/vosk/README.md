# Vosk (offline STT)

QNX ARM build of alphacep Vosk / Kaldi plus the small English model
`vosk-model-small-en-us-0.15`.

## Install

```sh
qpkg install vosk
qpkg install sttlab
```

## Usage

```sh
vosk clip.wav
sttlab
berry-browser http://127.0.0.1:8093/
```

`libvosk.so` lands in `berrycore/lib/`. The model is
`berrycore/share/stt/model/vosk-en/`.
