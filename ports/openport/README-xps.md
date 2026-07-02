# BlackBerry 10 Ports — Agent Start Here

> **Directory:** `~/Desktop/BlackBerry 10/ports/`  
> **Target device:** BlackBerry Passport (ARM `armle-v7`, QNX 8)  
> **Build environment:** Docker container `bb10-kitchen-sink`

Everything built for Passport lives **in this folder** — tarballs, source, build scripts, and manuals.

---

## What's in this folder

| Item | Purpose |
|------|---------|
| **`README.md`** | This file — agent entry point |
| **`openport-passport-qnx8.tar.gz`** | Install on Passport: `openport` diagnostic CLI |
| **`vim-passport-9.1.2148-qnx8.tar.gz`** | Install on Passport: Vim 9.1.2148 |
| **`openport/`** | OpenPort source + `MANUAL.md` |
| **`build-openport-canlog.sh`** | Rebuild OpenPort in container |
| **`build-vim-passport.sh`** | Rebuild Vim in container |
| **`README-vim.md`** | Vim install notes |

Parent context: `~/Desktop/BlackBerry 10/context.md`  
Linux OpenPort tools (full scan/UDS): `~/openport-tools/` and `~/Desktop/OpenPort/`

---

## Install on Passport

Both packages use BerryCore prefix `/accounts/1000/shared/misc`:

```bash
# Copy tarballs to device, then:
cd /accounts/1000/shared/misc
tar xzf openport-passport-qnx8.tar.gz
tar xzf vim-passport-9.1.2148-qnx8.tar.gz

export PATH="/accounts/1000/shared/misc/bin:$PATH"
export VIMRUNTIME="/accounts/1000/shared/misc/share/vim/vim91"
```

---

## OpenPort — which serial port? (two devices)

OpenPort USB exposes **two serial nodes**. Only one is the **command/data** interface.

| Host | Try first | Alternate |
|------|-----------|-----------|
| **Passport (QNX)** | `/dev/serusb1` | `/dev/serusb2` |
| **Linux PC** | `/dev/ttyACM0` | `/dev/ttyACM1` |

**Pick the one that works:**

```bash
openport -p /dev/serusb1 identify    # must print firmware version
openport -p /dev/serusb2 identify    # try if first fails
```

Set permanently:

```bash
export OPENPORT_PORT=/dev/serusb1   # use whichever passed identify
```

**Not the same as CAN “ports”:**
- USB serial to cable: **115200** baud
- Vehicle CAN (Jeep/FCA): **500000** baud (`-b 500000`, default)
- PCM ECU addresses: TX **7E0** → RX **7E8** (`openport probe`)

Full manual: **`openport/MANUAL.md`**

### OpenPort quick commands

```bash
openport identify          # cable only — no car
openport ports             # list /dev/ser* candidates
openport voltage           # OBD battery (pin 16)
openport probe             # VIN + PCM check (key ON)
openport scan              # ping FCA modules
openport log -d 120 -o /accounts/1000/shared/misc/can.log --show-id
openport help
```

---

## Vim

| | |
|---|---|
| Version | **9.1.2148** (tag `v9.1.2148`) |
| Features | `huge`, terminal + ncursesw, no GUI |

See **`README-vim.md`**.

---

## Rebuild (inside `bb10-kitchen-sink`)

```bash
# OpenPort
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/openport bb10-kitchen-sink:/root/ports/openport-log'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/build-openport-canlog.sh bb10-kitchen-sink:/root/ports/'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-openport-canlog.sh"'
sg docker -c 'docker cp bb10-kitchen-sink:/root/ports/openport-log/build/openport-passport-qnx8.tar.gz ~/Desktop/BlackBerry\ 10/ports/'

# Vim
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/build-vim-passport.sh bb10-kitchen-sink:/root/ports/'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-vim-passport.sh"'
sg docker -c 'docker cp bb10-kitchen-sink:/root/ports/vim-build/vim-passport-9.1.2148-qnx8.tar.gz ~/Desktop/BlackBerry\ 10/ports/'
```

---

## Hardware reminder

```
Vehicle OBD  ←→  OpenPort 2.0 (0403:cc4d)  ←→  USB OTG  ←→  Passport
```

- Remove microSD from OpenPort when using USB host
- Key **ON** for vehicle diagnostics
- OpenPort firmware is **on the cable** — these packages are host-side only
