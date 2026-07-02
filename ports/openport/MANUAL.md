# OpenPort for BlackBerry Passport — User Manual

> **Version:** QNX native port (GCC 9.3 / armle-v7)  
> **Hardware:** Tactrix OpenPort 2.0 (`0403:cc4d`)  
> **Host:** BlackBerry Passport with USB OTG  
> **Vehicles documented:** FCA Jeep/Dodge (2017+), 500 kbit/s CAN

---

## Table of contents

1. [What this tool does](#1-what-this-tool-does)
2. [How the hardware connects](#2-how-the-hardware-connects)
3. [How the software stack works](#3-how-the-software-stack-works)
4. [Installation](#4-installation)
5. [Command reference](#5-command-reference)
6. [Typical workflows](#6-typical-workflows)
7. [Understanding CAN logs](#7-understanding-can-logs)
8. [Understanding UDS and DIDs](#8-understanding-uds-and-dids)
9. [FCA module address table](#9-fca-module-address-table)
10. [Troubleshooting](#10-troubleshooting)
11. [Linux PC vs Passport](#11-linux-pc-vs-passport)
12. [Protocol reference (for developers)](#12-protocol-reference-for-developers)
13. [Safety notes](#13-safety-notes)

---

## 1. What this tool does

**`openport`** is a native diagnostic companion for your Passport. It talks to a **Tactrix OpenPort 2.0** cable over USB serial and lets you:

| Capability | Command | Needs vehicle? |
|------------|---------|----------------|
| Verify cable + firmware | `identify` | No |
| Find serial device path | `ports` | No |
| Read OBD battery voltage | `voltage` | Key ON recommended |
| Quick ECU check + VIN | `probe` | Key ON |
| Discover which modules respond | `scan` | Key ON |
| Read a specific register (DID) | `read-did` | Key ON |
| **Passive CAN bus logging** | `log` | Key ON (engine optional) |

The OpenPort **firmware is already on the cable** (e.g. 1.17.x). This package does not update firmware — it is the **host-side explorer** that makes USB-connected diagnostics possible on the Passport.

---

## 2. How the hardware connects

```
┌─────────────┐   OBD-II    ┌──────────────┐   USB mini   ┌─────────┐   OTG    ┌───────────┐
│  Your Jeep  │◄───────────►│  OpenPort 2  │◄────────────►│ USB-A   │◄──────►│ Passport  │
│  (or Dodge) │   16-pin    │  (0403:cc4d) │              │ adapter │        │ (QNX host)│
└─────────────┘             └──────────────┘              └─────────┘        └───────────┘
```

### Important rules

| Rule | Why |
|------|-----|
| Passport is **USB host** (OTG cable) | OpenPort is a USB **device**, like a serial modem |
| **Remove microSD** from OpenPort when using USB | SD slot is for standalone logging without a host |
| **Key ON** (RUN position) for vehicle commands | Many modules sleep with key off |
| Engine **may be off** for logging and reads | PCM often responds with key ON alone |
| Do not flash/recalibrate PCM from this tool | Read/log only — flashing needs dedicated tools |

### USB identification

| Field | Value |
|-------|-------|
| Vendor ID | `0403` (FTDI) |
| Product ID | `cc4d` |
| Product name | Tactrix OpenPort 2.0 |
| USB class | CDC ACM (serial) |
| Command port speed | **115200 8N1** |
| Vehicle CAN speed (FCA) | **500000** (set by software after open) |

### Serial device path on QNX

After plugging in via OTG, look for:

```bash
ls /dev/ser*
# Common: /dev/serusb1
export OPENPORT_PORT=/dev/serusb1
```

Use `openport ports` to list candidates.

---

## 3. How the software stack works

You do **not** need the Windows J2534 DLL. The Passport app speaks directly to OpenPort firmware:

```
┌─────────────────────────────────────────────┐
│  openport CLI  (log / probe / scan / …)     │
├─────────────────────────────────────────────┤
│  UDS layer       ISO-TP reassembly, DIDs    │
├─────────────────────────────────────────────┤
│  OpenPort layer  AT commands (ati, ato, …)  │
├─────────────────────────────────────────────┤
│  Serial layer    115200 on /dev/serusb*     │
├─────────────────────────────────────────────┤
│  OpenPort firmware  (already on cable)      │
├─────────────────────────────────────────────┤
│  Vehicle CAN  @ 500 kbit/s  →  ECUs        │
└─────────────────────────────────────────────┘
```

### Two speeds — do not confuse them

| Link | Speed | Meaning |
|------|-------|---------|
| USB serial (Passport ↔ OpenPort) | **115200** | Command channel to firmware |
| CAN bus (OpenPort ↔ car) | **500000** (typical) | Actual vehicle network |

---

## 4. Installation

### From tarball (on Passport)

```bash
cd /accounts/1000/shared/misc
tar xzf openport-passport-qnx8.tar.gz
export PATH="/accounts/1000/shared/misc/bin:$PATH"
```

Add to `~/.profile` or BerryCore shell init:

```bash
export PATH="/accounts/1000/shared/misc/bin:$PATH"
export OPENPORT_PORT=/dev/serusb1   # adjust after first plug-in
```

### Verify install

```bash
openport help
openport identify
```

### Rebuild from source (on Linux dev host)

```bash
sg docker -c 'docker cp ~/Desktop/OpenPort/qnx-port bb10-kitchen-sink:/root/ports/openport-log'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-openport-canlog.sh"'
```

---

## 5. Command reference

Global options (before subcommand):

| Option | Description |
|--------|-------------|
| `-p, --port PATH` | Serial device (default: `$OPENPORT_PORT` or auto) |
| `-b, --baud RATE` | Vehicle CAN baud (default: **500000**) |
| `-v, --verbose` | Extra status messages |
| `--debug` | Raw serial hex dump on stderr |

### `openport identify`

Opens the cable, prints firmware version. **No vehicle required.**

```bash
openport identify
openport -p /dev/serusb1 identify
```

Expected output includes a line like `main code version : 1.17.4877`.

---

### `openport ports`

Lists common serial paths and whether they are accessible.

```bash
openport ports
```

---

### `openport voltage`

Reads pin voltage via OpenPort. Default pin **16** = OBD battery (VBATT).

```bash
openport voltage
openport voltage -p 6    # CAN-H pin (diagnostic)
```

---

### `openport probe`

Quick health check on one ECU pair (default PCM **7E0 → 7E8**):

1. UDS TesterPresent (`3E 00`)
2. Read DID **F190** (VIN)
3. Read DID **F189** (software version)
4. VBATT

```bash
openport probe
openport probe -t 7e1 -r 7e9    # transmission module
```

---

### `openport scan`

Pings common FCA module addresses with TesterPresent.

```bash
openport scan
```

Use this before deep logging to see which modules are awake.

---

### `openport read-did <DID>`

UDS ReadDataByIdentifier (`0x22`) for one DID (hex, no `0x` required):

```bash
openport read-did F190          # VIN
openport read-did F189          # SW version
openport read-did F191 -t 620 -r 504   # BCM alt address
```

---

### `openport log`

**Passive CAN sniffer** — captures frames without transmitting (sniff mode).

```bash
# 60 seconds to stdout
openport log

# 5 minutes to file, show CAN IDs
openport log -d 300 -o /accounts/1000/shared/misc/can.log --show-id

# ISO15765 mode (OBD-II framing, PCM 7E0/7E8)
openport log --iso15765 -d 120

# Run until Ctrl+C
openport log -d 0
```

Log line format:

```text
[1234.567] ID 7e8  06 41 0d 00 00 00 00
 │          │     └── payload bytes (hex)
 │          └── CAN ID (11-bit display)
 └── timestamp ms from OpenPort
```

---

### `openport help [topic]`

```bash
openport help
openport help log
openport help probe
```

---

## 6. Typical workflows

### A. First time — bench test (no car)

```bash
openport ports
openport identify
```

You should see firmware text. If not, fix OTG/serial before connecting the car.

---

### B. Connected to vehicle — quick sanity check

```bash
# Key ON, OBD plugged in
openport voltage          # expect ~12–14 V on pin 16
openport probe            # VIN + alive PCM
openport scan             # which modules respond
```

---

### C. Road logging session

```bash
openport log -d 0 -o /accounts/1000/shared/misc/logs/trip-$(date +%Y%m%d).log --show-id
# Drive. Ctrl+C when done.
```

Copy log off the Passport later via SSH/SCP for analysis on your Linux PC.

---

### D. Investigate one register

```bash
openport read-did F190
openport read-did F18C    # ECU serial
```

Cross-reference DID list in §8 and your Linux scan JSON (`~/openport-tools/scans/`).

---

## 7. Understanding CAN logs

Each line is one **CAN frame** as seen by OpenPort:

| Bytes | Meaning |
|-------|---------|
| First 4 (in `--show-id` mode) | CAN arbitration ID (big-endian) |
| Remaining | Payload (0–8 bytes typical) |

### Common IDs (FCA OBD)

| ID | Direction | Typical content |
|----|-----------|-----------------|
| `7E0` | Tester → PCM | UDS/OBD requests |
| `7E8` | PCM → tester | Responses |
| `7DF` | Broadcast | OBD-II functional |

### Tips

- **High traffic at idle is normal** — modules broadcast status continuously.
- Compare captures **key ON vs key OFF** to see what wakes up.
- Use Linux `openport-canlog` or Wireshark for deeper analysis of saved logs.

---

## 8. Understanding UDS and DIDs

**UDS** (Unified Diagnostic Services) is the protocol most 2017+ FCA modules speak over CAN.

| Service | Hex | Purpose |
|---------|-----|---------|
| TesterPresent | `3E 00` | Keep session alive / ping |
| ReadDataByIdentifier | `22 xx xx` | Read register (DID) |
| WriteDataByIdentifier | `2E …` | Write (not exposed in this tool) |

### Useful identification DIDs

| DID | Content |
|-----|---------|
| **F190** | VIN |
| **F189** | ECU software version |
| **F188** | ECU software number |
| **F191** | ECU hardware number |
| **F18C** | ECU serial number |
| **F195** | Supplier software version |

### Negative response codes (NRC)

If `read-did` returns `NRC 0x33` (*security access denied*) on a 2020+ vehicle, the **Security Gateway** may block writes — reads often still work. Writes require additional hardware (12+8 bypass cable) and are outside this tool.

---

## 9. FCA module address table

Used by `openport scan`:

| Module | TX | RX |
|--------|----|----|
| PCM (engine) | 7E0 | 7E8 |
| TCM (transmission) | 7E1 | 7E9 |
| ECU #3 | 7E2 | 7EA |
| ECU #4 | 7E3 | 7EB |
| BCM (FCA alt) | 620 | 504 |
| BCM (alt 2) | 740 | 748 |
| ABS (alt) | 760 | 768 |
| Cluster | 720 | 728 |
| Radio/AMP | 726 | 72E |

Use `-t` / `-r` with `probe` and `read-did` for non-PCM modules.

---

## 10. Troubleshooting

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| `No firmware response` | Wrong `/dev` path, no OTG power | `openport ports`, replug, try `-p` |
| `Attach (ata) failed` | Wrong device, cable busy | Close other apps; only one host at a time |
| `Channel open failed` | Key off, bad OBD, blown fuse | Key ON; wiggle OBD connector |
| `No UDS response` | Wrong TX/RX, module asleep | `openport scan`; try engine running |
| `0 modules` on scan | Low battery, SGW, wiring | `openport voltage` ≥ 11 V |
| Permission denied on `/dev/ser*` | QNX permissions | Run as appropriate user / dev permissions |
| Log shows nothing | Wrong baud, not sniffing bus | Confirm `-b 500000`; try `--iso15765` |
| Works on Linux, not Passport | Serial driver not started | Check `io-usb`, `devc-serusb` on QNX |

### Debug mode

```bash
openport --debug -v identify
openport --debug probe
```

Shows raw serial traffic on stderr.

---

## 11. Linux PC vs Passport

| Task | Best platform |
|------|----------------|
| Passive CAN logging in the car | **Passport** (`openport log`) |
| Full ECU/DID brute-force scan | **Linux** (`openport-scan`) |
| UDS write / security unlock | **Linux** (`openport-fca uds`) |
| Standalone logging (no host) | **OpenPort SD** + `logcfg.txt` |
| Interactive bus inspector | **Linux** (`openport-inspector`) |

This Passport port is intentionally focused on **reliable read-only exploration** — identify, probe, scan, log.

Source reference on Linux: `~/openport-tools/` (TypeScript j2534 stack).

---

## 12. Protocol reference (for developers)

### Open sequence

1. Open serial @ 115200  
2. `\r\n\r\nati\r\n` → response `ari …` (firmware)  
3. `ata\r\n` → `aro` (attach)  
4. `ato6 2684357120 500000 0 1\r\n` → open ISO15765 @ 500k with flags (example)  
5. `atf6 3 0 4\r\n` + mask/pattern/flow → flow control filter  
6. `att6 …` → transmit frame  
7. Read binary `ar` packets from serial  

Channel bytes: `5` = CAN (`0x35`), `6` = ISO15765 (`0x36`).

### Source layout

```text
qnx-port/src/
  serial.c      POSIX termios transport
  openport.c    AT commands, RX reassembly, message queue
  uds.c         ISO-TP + UDS helpers
  util.c        logging, port detection
  main.c        CLI commands
```

Ported from `@emdzej/j2534` TypeScript (`packages/core`, `packages/driver`).

---

## 13. Safety notes

- This tool performs **read-only** diagnostics and passive logging by default.
- Do not attempt PCM **flashing** or **calibration writes** with this binary.
- Only connect and test on vehicles you own or have permission to diagnose.
- Logging while driving: mount the Passport securely — distraction kills.

---

## Quick reference card

```bash
openport identify                    # cable OK?
openport voltage                     # ~12V?
openport probe                       # VIN + PCM alive?
openport scan                        # all modules
openport log -d 300 -o can.log --show-id
openport read-did F190
openport help
```

**Manual path on device:**  
`/accounts/1000/shared/misc/share/doc/openport/MANUAL.md`
