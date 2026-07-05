## BerryCore v0.86.0

Full **qpkg catalog** (~115 packages), **82 XPS utility ports**, messenger app upgrades, and **Phase 2** network tool fixes for fresh installs.

### Core bundle (berrycore.zip)

| Change | Details |
|--------|---------|
| **VERSION** | 0.86.0 |
| **util-ftp 1.0.0** | Rebuilt from XPS Passport build (client + bftpd server) |
| **qpkg** | Two-tier catalog, cache fix, install handlers for ftp/ping/tcpdump |

### qpkg catalog

| Command | Source | Purpose |
|---------|--------|---------|
| `qpkg ports` | `ports/FEATURED` (~22) | Showcase only |
| `qpkg search/available/show/install` | `ports/PACKAGES` (~115) | Full apt-like catalog |

### New / updated qpkg ports

| Port | Install | Notes |
|------|---------|-------|
| **openport** 1.0.0 | `qpkg install openport` | Rebuilt from XPS (25K); canlog symlink |
| **ftp** 1.0.0 | `qpkg install ftp` | netkit client + bftpd server |
| **ping** 1.0.0 | `qpkg install ping` | ICMP echo (may need root) |
| **tcpdump** 4.99.5 | `qpkg install tcpdump` | Packet capture (may need root) |
| **bbm** 1.0.0 | `qpkg install bbm` | Berry Bridge Messenger |
| **rocketchat** 3.0 | `qpkg install rocketchat` | Navigator v3 |
| **telegram** 2.1 | `qpkg install telegram` | Enhanced UI |
| **youtube** 2.0 | `qpkg install youtube` | v2 player |
| **82 XPS utilities** | `qpkg search <name>` | less, cabextract, iperf3, minicom, etc. |

### Fresh install

```sh
# Copy to device shared folder, then in Term49:
sh install.sh --fresh -y

# Browse and install ports:
qpkg ports                    # featured showcase
qpkg search cab               # full catalog search
qpkg install openport ftp ping tcpdump
```

### Upgrade from v0.85

```sh
qpkg update
# or:
sh install.sh --upgrade -y
```

### Verify

```sh
cat $NATIVE_TOOLS/VERSION    # 0.86.0
qpkg ports                   # ~22 featured
qpkg search iperf            # finds iperf3 in full catalog
openport identify            # after: qpkg install openport
```

### Assets

See `RELEASE_FILES_v0.86.txt` for SHA256 checksums.
