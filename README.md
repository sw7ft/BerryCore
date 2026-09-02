# BerryCore

QNX extended userland for BlackBerry 10.

I have been working on restoring browser functionality for BB10 for years and I am happy to release the first beta of Berry Browser (Chromium). Yes it is a .bar so you will need a rooted device. Good news: content_shell and a Term49 bin are also included to play with. I will make that better.

Latest: [v0.90.1](https://github.com/sw7ft/BerryCore/releases/tag/v0.90.1) (qpkg remove). Browser beta: [v0.90.0](https://github.com/sw7ft/BerryCore/releases/tag/v0.90.0).

## Berry Browser Chromium (first beta)

| | |
|---|---|
| **BAR** | [BerryBrowserV3-3.0.2-build83.bar](https://github.com/sw7ft/BerryCore/releases/tag/v0.90.0) on a rooted BB10 device |
| **Also in the BAR** | `content_shell` and a Term49 bin to play with |
| **qpkg :8080 viewer** | `qpkg install berry-remote` then `berryremote`. Open `http://127.0.0.1:8080/` |

```sh
qpkg install berry-remote
berryremote
# http://127.0.0.1:8080/
qpkg remove berry-remote
```

Engine comes from the BAR or `qpkg install berry-browser`.

## Install BerryCore

Download `berrycore.zip` and `install.sh` from [Releases](https://github.com/sw7ft/BerryCore/releases). How-to videos:

1. [Transfer files](https://www.youtube.com/shorts/j-kRBxrv4XI)
2. [Install](https://www.youtube.com/shorts/6paUBxsP2yU)
3. [SSH](https://youtube.com/shorts/pKX2x4o4w1I)

Site: [berrycore.sw7ft.com](https://berrycore.sw7ft.com/)

## What this is

BerryCore is a modernized continuation of Berry Much OS. Extra binaries, `env.sh`, and `qpkg` so BB10/QNX can be a development box again. Not affiliated with BlackBerry Limited.

Support: [Patreon - Sw7ft](https://www.patreon.com/c/Sw7ft)
