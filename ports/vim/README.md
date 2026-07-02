# Vim 9.1 for BlackBerry Passport (BerryCore core package)

Built with GCC 9.3 / QNX 8 (`arm-blackberry-qnx8eabi`), **huge** feature set, terminal UI via **ncursesw**, no GUI.

| | |
|---|---|
| **Version** | Vim 9.1.2148 |
| **Source tarball** | `vim-passport-9.1.2148-qnx8.tar.gz` (from xps bb10-kitchen-sink build) |
| **BerryCore package** | `berrycore/packages/vim-9.1.2148.zip` (replaces vim-8.0) |

## Rebuild BerryCore zip

```bash
./ports/vim/build-port.sh
./utilities/package.sh
```

## Rebuild from source (Docker on xps)

See `build-vim-passport.sh` — runs inside `bb10-kitchen-sink` container.
