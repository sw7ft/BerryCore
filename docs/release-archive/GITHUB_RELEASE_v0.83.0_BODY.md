## BerryCore v0.83.0

Core package update — networking, media, and Git tools.

### New packages

| Package | Version | Binaries |
|---------|---------|----------|
| util-ping | 1.0.0 | `ping` |
| util-tcpdump | 4.99.5 | `tcpdump` |
| util-nixtla-audio | 1.0.0 | `play-audio`, `demoPlayWav`, `demoCaptureEco` |

### Upgrades

| Package | Was | Now |
|---------|-----|-----|
| ffmpeg | 4.2.2 | **6.1.2** (`ffmpeg`, `ffprobe`) |
| tig | 2.5.0 | **2.6.1** (includes `etc/tigrc`) |

### Usage

```sh
qpkg update                    # or manual install.sh --upgrade
ping 8.8.8.8
tcpdump -i bpe0 -c 10
tig                            # Git log browser
ffmpeg -i video.mp4 -vn out.wav
play-audio song.mp3            # BB10 speaker via nixtla + ffmpeg
```

### Notes

- `play-audio` decodes MP3/video with ffmpeg 6.1, plays WAV via OpenAL on Passport
- `TIGRC` is exported in `env.sh` for tig 2.6.1 config
- Upgrade installs new package zips; old `ffmpeg-4.2.2` and `tig-2.5.0` removed from bundle

### Assets

- `berrycore.zip` — BerryCore 0.83.0
- `install.sh`
