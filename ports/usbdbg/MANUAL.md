# usbdbg — Generic USB Serial Debugger (Passport / QNX)

**usbdbg** is a small CLI for raw USB CDC/serial work on the BlackBerry Passport. It does **not** speak OpenPort, J2534, or any vendor protocol — it opens the port, sends bytes, and logs what comes back.

Use it for:

- Probing unknown USB gadgets (FTDI, CDC ACM, GPS, modems, Arduino)
- Sniffing traffic before writing a dedicated tool
- Quick AT-style tests (`send`, `line`, `probe`)
- Debugging when you are not sure which `/dev/serusb*` node is active

For **OpenPort + CAN/UDS** on a vehicle, use **`openport`** instead.

---

## Install

```bash
tar xzf usbdbg-passport-qnx8.tar.gz -C /
export PATH="/accounts/1000/shared/misc/bin:$PATH"
```

---

## Serial port (Passport)

USB OTG adapters usually show up as **`/dev/serusb1`** and **`/dev/serusb2`**. Only one is the data interface.

```bash
usbdbg ports
usbdbg -p /dev/serusb1 probe
usbdbg -p /dev/serusb2 probe
```

Set a default:

```bash
export SERDBG_PORT=/dev/serusb1
# or
export USB_SERIAL_PORT=/dev/serusb1
```

Default baud is **115200**. Many GPS units use **9600**:

```bash
usbdbg -b 9600 probe
```

---

## Commands

| Command | Description |
|---------|-------------|
| `ports` | List readable/writable serial nodes |
| `sniff [-d SEC] [-o FILE] [-a]` | Log RX as hex (optional ASCII, duration, file) |
| `send [-x] DATA` | Send string or hex bytes; print quick RX |
| `probe [-b BANNER]` | Open port, optional wake string, listen 3s |
| `cat` | Raw RX to stdout |
| `line` | Interactive line mode (type to send, echo RX) |
| `help` | Usage |

Global flags (before command): **`-p PORT`**, **`-b BAUD`**, **`-v`**.

---

## Examples

```bash
# List devices
usbdbg ports

# Sniff for 60 seconds with ASCII column
usbdbg -p /dev/serusb1 sniff -d 60 -a -o /accounts/1000/shared/misc/usb.log

# Send AT command (escaped CR/LF)
usbdbg send "AT\r\n"

# Send raw hex
usbdbg send -x "61 74 69 0d 0a"

# Probe with wake banner (OpenPort AT identify — generic, not full openport stack)
usbdbg probe -b "\r\nati\r\n"

# Interactive session
usbdbg -p /dev/serusb1 line
```

---

## vs OpenPort

| | **usbdbg** | **openport** |
|---|------------|--------------|
| Purpose | Raw serial transport | OpenPort 2.0 + CAN/UDS |
| Protocol | None | AT + ISO-TP + UDS |
| Vehicle scan | No | `scan`, `probe`, `read-did` |
| CAN logging | No | `log` |

Both can share the same USB cable; pick the right `/dev/serusb*` with `ports` / `probe`.

---

## Rebuild

From the host (see `ports/README.md`):

```bash
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/usbdbg bb10-kitchen-sink:/root/ports/usbdbg'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/build-usbdbg-passport.sh bb10-kitchen-sink:/root/ports/'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-usbdbg-passport.sh"'
sg docker -c 'docker cp bb10-kitchen-sink:/root/ports/usbdbg-build/usbdbg-passport-qnx8.tar.gz ~/Desktop/BlackBerry\ 10/ports/'
```
