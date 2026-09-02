## BerryCore v0.87.3

Term49 launch splash — the wordmark you see when Term49 opens.

### Added

- **TERM49 / BerryCore splash** on login (`share/term49-splash.sh`) — type `splash` to redraw
- **Berry Term49 theme** (`share/term48rc`) — Courier Bold, pale orchid on deep berry; copied to `~/.term48rc` on install if you do not already have one

### Changed

- **`sample_profile` / `install.sh`** — `BERRYCORE_QUIET=1` skips the old env.sh box and the 5s MOTD curl so the splash owns the screen
- **`env.sh`** — honors `BERRYCORE_QUIET=1`

### Update

Download `berrycore.zip` + `install.sh`, or on device after a zip refresh:

```sh
# splash is at $NATIVE_TOOLS/share/term49-splash.sh
# new shells pick it up from .profile (re-run install.sh or merge sample_profile)
splash
```

See `RELEASE_FILES_v0.87.3.txt` for checksums.
