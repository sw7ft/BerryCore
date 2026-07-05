## BerryCore v0.87.2

Installs the **berrycore.html** catalog guide to Documents automatically.

### Added

- **`install.sh`** copies `berrycore.html` → `/accounts/1000/shared/documents/berrycore.html` on every fresh install and upgrade
- Catalog is **bundled inside `berrycore.zip`** at `doc/berrycore.html` — no separate download required

### On device after install

```sh
docs                    # cd to Documents
# Open berrycore.html in BB10 browser, or transfer via USB
```

Or from PC: `scp passport:/accounts/1000/shared/documents/berrycore.html .`

### Includes v0.87.1 fixes

- Custom install dirs (`berrycore4`, etc.) — ports stay in your tree
- QNX staging extract — no more unzip delete errors

### Update

```sh
qpkg update
```

See `RELEASE_FILES_v0.87.2.txt` for checksums.
