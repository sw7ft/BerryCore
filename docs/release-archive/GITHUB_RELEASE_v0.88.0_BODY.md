## BerryCore v0.88.0

The on-device hub is a product now — same aubergine brand as Term49, and it comes up when you open the terminal.

Type `setup` or wait for login. The splash says **Running locally at 127.0.0.1:8098**. The Hub banner says the same. Tap it to open Apps.

### Hub

- **Home** — BERRYCORE wordmark, slogan, v0.88.0
- **Apps** — start / stop with a live Starting state and a green lamp when the port is up. Includes QNX Desktop, Term49 Web, BerryPy, Voice Agent, BerrySnip, Library, Orrery, The Tape, and the rest of the local web UIs
- **Packages** — compact qpkg table. Search, sort, Install or Reinstall
- **Core** — what ships with BerryCore by default (`qpkg catalog` / `qpkg bins`)
- **Manual** — same chrome as the hub
- **Settings** — Aubergine / Midnight / Ember / Paper. SW7FT, [Patreon](https://www.patreon.com/Sw7ft), [berrycore.sw7ft.com](https://berrycore.sw7ft.com/), GitHub

### Talkbutton

Play/pause dictation on the Passport. QSA mic, warm Vosk, transcript to the system clipboard and the Hub.

```
qpkg install vosk
qpkg install talkbutton
talkbutton
```

### Term49

Official splash stays: white BERRYCORE, 7-dot berry, `#300A24`. New hub line on every launch. `setup boot` starts the catalog if it is down and notifies `Running locally at 127.0.0.1:8098`.

Disable hub autostart with `export BERRYCORE_SETUP_AUTO=0` in `.profile` before `env.sh`.
