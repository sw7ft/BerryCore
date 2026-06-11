# chafa port (chafa 1.14.4)

**chafa** — terminal image viewer for BB10/QNX. Ships as a **BerryCore core package** (like wget), not a qpkg port.

## Users

```bash
qpkg update
chafa --version
chafa-show photo.jpg
```

## Build (maintainers)

```bash
cd ports/chafa
./build-port.sh ../../chafa-bb10-1.14.4.tgz
```

Output: `berrycore/packages/chafa-1.14.4.zip`

## Layout (`$NATIVE_TOOLS`)

| Path | Purpose |
|------|---------|
| `bin/chafa` | Wrapper (LD_LIBRARY_PATH, TERM) |
| `bin/chafa.bin` | ARM binary |
| `bin/chafa-show` | User-friendly image viewer |
| `lib/libchafa.so.9` | Bundled library |
| `share/chafa/` | HELP, examples |
