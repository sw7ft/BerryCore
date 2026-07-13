# QNX Doom (qpkg install qnx-doom)

Classic **Doom** via `doomgeneric` on QNX 8 / BlackBerry Passport, rendered through an **Android X11 server**.

> **TEST ONLY — BlackBerry Passport — NO AUDIO**

Source: [sw7ft/qnx-packages `qnx_doom_deploy`](https://github.com/sw7ft/qnx-packages/tree/main/qnx_doom_deploy)

---

## Requirements (read this first)

| Requirement | Details |
|-------------|---------|
| **XSDL / XServer** | **Required.** Doom draws to X11; BB10 has no native framebuffer for this build. |
| **DISPLAY** | Must be set to your X server address, e.g. `192.168.1.113:0` |
| **Run location** | **On the device** (Term49). Do **not** run over SSH — keyboard/input will not work correctly. |
| **Device** | Tested on Passport only |
| **Audio** | None |
| **Game data** | **Freedoom Phase 1** (`freedoom1.wad`) is bundled — no extra download needed |

Without XSDL running and `DISPLAY` set, `qnx-doom` will exit with setup instructions.

---

## Install

```sh
qpkg install qnx-doom
```

Installs to `$NATIVE_TOOLS/share/qnx-doom/` with launcher `qnx-doom` in `$NATIVE_TOOLS/bin/`.

---

## Step 1 — Install XSDL (X server)

An XSDL utility APK is bundled with this port:

```
$NATIVE_TOOLS/share/qnx-doom/apks/xserver-xsdl-1-11-40-(Utility).apk
```

**Option A — Sideload the bundled APK**

Copy to the device and install via BB10 Android runtime, or use the `android-apps` port if xSDL is listed there.

**Option B — Use an existing X server**

Any X11 server on BB10 that exposes `IP:0` works (XSDL, XServer, etc.).

1. Launch the X server app on the phone
2. Note the **IP address and display number** shown (e.g. `192.168.1.113:0`)

---

## Step 2 — Run (easy mode)

In **Term49 on the Passport**:

```sh
. $NATIVE_TOOLS/env.sh
qnx-doom
```

When prompted for **Display**, just press **Enter** to use `127.0.0.1:0` (XSDL on the same device).

The launcher auto-selects **freedoom1.wad** from `share/qnx-doom/wads/`.

Or type the IP XSDL shows if different (e.g. `192.168.1.113:0`).

You can still preset it: `export DISPLAY=127.0.0.1:0` before running.

**Tip:** Run on the device — keyboard input may not work over SSH.

---

## Game data (IWAD)

Bundled in `share/qnx-doom/wads/`:

- **freedoom1.wad** — Freedoom Phase 1 (free, GPL/BSD)

Optional — copy your own WADs into the same folder:

- `freedoom2.wad`, `doom.wad`, `doom2.wad`

Force a specific file:

```sh
qnx-doom -iwad /path/to/doom2.wad
```

---

## Controls

| Key | Action |
|-----|--------|
| Arrow keys | Move |
| Ctrl | Fire |
| Space | Use / open doors |
| Shift | Run |
| Esc | Menu |

---

## Troubleshooting

| Problem | Fix |
|---------|-----|
| `No IWAD file found` | Reinstall: `qpkg install qnx-doom` (includes freedoom1.wad) |
| `DISPLAY not set` | Start XSDL, export `DISPLAY=ip:0` |
| Black screen | Wrong DISPLAY IP — check XSDL status screen |
| No keyboard | You are on SSH — run in Term49 on device |
| `cannot open display` | X server not running or firewall blocked |
| Missing libs | Re-run `qpkg install qnx-doom`; check `share/qnx-doom/lib/` |

---

## Files

```
share/qnx-doom/
├── bin/doomgeneric_qnx
├── lib/libX11.so* …
├── wads/freedoom1.wad
├── scripts/doom_run.sh
├── apks/xserver-xsdl-1-11-40-(Utility).apk
└── README.txt
bin/qnx-doom          ← launcher (IWAD + DISPLAY)
```

---

## Credits

Built with QNX 8 ARM toolchain and X11 forwarding. Package maintained in BerryCore ports.
