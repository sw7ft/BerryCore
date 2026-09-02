# Port Overlap Audit (Phase 0)

Audit date: 2026-07-05  
Source: XPS `portupdate.md` vs BerryCore core bundle vs existing qpkg ports.

## Summary

| Zone | Count | Action |
|------|-------|--------|
| Existing qpkg ports (PACKAGES) | 31 | Keep; verify zip names match |
| XPS wave 1–5 utilities | ~25 | Add to PACKAGES in Phase 3; check `replaces=core` |
| XPS wave 6 DOS retro | ~33 | Add in Phase 4 |
| XPS wave 7 retro interop | ~30 | Add in Phase 4; not yet on Passport |
| Blocked (rlwrap, mc, etc.) | 7 | Omit from PACKAGES |

## Existing qpkg vs XPS-built (same tool, different path)

| Tool | BerryCore port / core | XPS build | Decision |
|------|----------------------|-----------|----------|
| telnet | `net-telnet-0.17.zip` | XPS tarball | Compare builds in Phase 2; bump if XPS newer |
| dropbear | `net-dropbear-2026.91.1.zip` | XPS tarball | Same |
| ftp/bftpd | core util-ftp | XPS `build-ftp-passport.sh` | Phase 2 compare |
| vim | core package | XPS vim 9.1.2148 | Core v0.85 already aligned |
| pv | core binary? | XPS pv 1.8.14 on Passport | PACKAGES entry `replaces=core` |
| ping/tcpdump | release zips v0.83 | — | No XPS overlap |
| less, zstd, socat, tree, etc. | not in qpkg ports | XPS on Passport | New individual ports Phase 3 |

## Passport status (2026-07-05)

- Wave 1–6 binaries: deployed via `deploy-berrycore-bin.sh` to `misc/bin/` + symlinks
- Wave 7: **not deployed** (cabextract, nomarch, cpmtools, hfsutils, macutils missing)

## Reconciliation rules

1. Featured list (`FEATURED`) — showcase only (~22 ports)
2. Full catalog (`PACKAGES`) — all installable packages
3. `replaces=core` — warn on install if binary exists in `$NATIVE_TOOLS/bin/`
4. C++ ports (`7za`, `unrar`) — require `LD_LIBRARY_PATH` includes berrycore/bin
5. Symlinks (`7z`→`7za`) — one zip, multiple PACKAGES rows (Phase 3)

## Phase 2 complete (2026-07-05)

Compared XPS tarballs vs existing BerryCore ports:

| Tool | Result | Action taken |
|------|--------|--------------|
| telnet | SAME (66976 bytes) | No change |
| dropbear | SAME | No change |
| ftp/bftpd | SAME | Rebuilt `util-ftp-1.0.0.zip`; added qpkg install |
| vim | SAME | No change (core v9.1.2148) |
| usbdbg | SAME | No change |
| openport | **DIFF** (25672 vs 18948) | Rebuilt from XPS tarball; upgraded on Passport |
| ping | — | Added `util-ping-1.0.0.zip` + qpkg install |
| tcpdump | — | Added `util-tcpdump-4.99.5.zip` + qpkg install |

Passport tests: `qpkg install openport ftp ping tcpdump` — all OK.

## Next phases

- ~~Phase 2: Rebuild/compare telnet, dropbear, ftp against XPS tarballs~~ **Done**
- ~~Phase 3: Split XPS bundles → individual `util-*` zips + PACKAGES rows~~ **Done (82 ports, commit 0b39634)**
- Phase 4: Passport verification batch — in progress (nomarch, cabextract, iperf3 install OK via qpkg)
- Phase 5: Featured port regression + remaining smoke tests

## qpkg notes (2026-07-05)

- GitHub raw CDN may lag on `main` after push; qpkg keeps local cache if remote has fewer entries
- QNX lacks reliable `stat` mtime — cache prefers local copy when mtime unavailable
