# ncdu port (ncdu 1.22)

**ncdu** — NCurses Disk Usage for BB10/QNX. Ships as a **BerryCore core package** (like wget), not a qpkg port.

## Users

```bash
qpkg update
ncdu /accounts/1000/shared/misc
```

## Build (maintainers)

```bash
cd ports/ncdu
./build-port.sh ../../ncdu-bb10-1.22.tgz
```

Output: `berrycore/packages/ncdu-1.22.zip`

## Layout (`$NATIVE_TOOLS`)

| Path | Purpose |
|------|---------|
| `bin/ncdu` | Wrapper (`TERM=xterm-256color`) |
| `bin/ncdu.bin` | ARM binary |
| `share/ncdu/HELP.txt` | Usage help |
