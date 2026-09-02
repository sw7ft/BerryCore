# BerryCore

**QNX extended userland for BlackBerry 10.** First beta of **Berry Browser — Chromium** ships in [v0.90.0](https://github.com/sw7ft/BerryCore/releases/tag/v0.90.0).

Years of work restoring a real browser to BB10. This is the first public beta.

## Berry Browser — Chromium (first beta)

A Chromium `content_shell` on the Passport. Not the frozen stock WebKit. Modern sites can render. You need a **rooted device** — the app is a `.bar`.

| | |
|---|---|
| **BAR** | [BerryBrowserV3-3.0.2-build83.bar](https://github.com/sw7ft/BerryCore/releases/tag/v0.90.0) — install on a rooted BB10 device |
| **Also in the BAR** | `content_shell` and a Term49 bin to play with (that part will get better) |
| **qpkg :8080 viewer** | `qpkg install berry-remote` then `berryremote` — open `http://127.0.0.1:8080/` |

```sh
qpkg install berry-remote
berryremote
# http://127.0.0.1:8080/
```

The :8080 view is the Chromium remote we built (screenshot + tap/keys). Engine comes from the BAR or `qpkg install berry-browser`.

## Install BerryCore

Download `berrycore.zip` and `install.sh` from [Releases](https://github.com/sw7ft/BerryCore/releases). How-to videos:

1. [Transfer files](https://www.youtube.com/shorts/j-kRBxrv4XI)
2. [Install](https://www.youtube.com/shorts/6paUBxsP2yU)
3. [SSH](https://youtube.com/shorts/pKX2x4o4w1I)

Site: [berrycore.sw7ft.com](https://berrycore.sw7ft.com/)

## What this is

BerryCore is a modernized continuation of **Berry Much OS** — extra binaries, `env.sh`, and `qpkg` so BB10/QNX can be a development box again. Not affiliated with BlackBerry Limited.

Support: [Patreon – Sw7ft](https://www.patreon.com/c/Sw7ft)
