# usbdbg — USB Serial Debugger

Generic USB serial probe/sniff tool for Passport. Raw read/write on `/dev/serusb*` — no vendor protocol.

For **OpenPort + CAN/UDS**, use `openport` instead.

Built on xps (bb10-kitchen-sink Docker) for **armle-v7 / QNX 8**.

## Install

```sh
qpkg install usbdbg
```

## Usage

```sh
usbdbg ports
usbdbg -p /dev/serusb1 probe
usbdbg -p /dev/serusb1 sniff -d 60 -a
usbdbg send "AT\r\n"
usbdbg line
```

Full manual: `share/doc/usbdbg/MANUAL.md`

## Rebuild

```bash
./ports/usbdbg/build-port.sh usbdbg-passport-qnx8.tar.gz
```

Source: `ports/usbdbg/src/main.c`
