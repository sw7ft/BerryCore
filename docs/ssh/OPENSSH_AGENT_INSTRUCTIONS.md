# OpenSSH 10.2 BB10 – Instructions for Build Agent

## Goal

BerryCore needs OpenSSH to work **like it did with 7.1p2**: plain `sshd -Dd` should run and accept connections. Prefer `sshd -Dd` over custom helpers like `sshd-berrycore`.

## Current Problem

The OpenSSH 10.2 binary (`openssh-10.2p1-bb10-deploy-static`) was built with external program dependencies that fail on BerryCore:

1. **`/accounts/1000/shared/misc/libexec/sshd-session`** – binary reports "does not exist or is not executable"
2. **`/accounts/1000/shared/misc/libexec/sshd-auth`** – same error

The path `/accounts/1000/shared/misc/libexec/` is **hardcoded in the binary** (parent of berrycore install). BerryCore installs to `/accounts/1000/shared/misc/berrycore/`.

We added minimal stub scripts (exec shell or pass args) for both, but issues persist. The user reports the files are present on the device but it still fails.

## Questions for Build Agent

1. **Do you have the intended `sshd-session` and `sshd-auth`** from your build environment? Please share their contents or source.

2. **Can you rebuild sshd without these dependencies?** Standard OpenSSH does not require external sshd-session/sshd-auth. If the BB10/QNX build added these for sandboxing or Term49, can we have a build that uses internal session handling instead?

3. **What exactly do these programs do?** Are they:
   - Session starters (spawn user shell)?
   - Auth helpers (PAM/sandbox integration)?
   - Term49-specific wrappers?

4. **Path flexibility:** Can the binary be rebuilt to look for these in `$NATIVE_TOOLS/libexec/` (e.g. via runtime config or a different compile-time prefix) so they live inside the berrycore install dir?

## New: "Invalid user blackberry" (Regression from 7.1)

After upgrading, clients get **Permission denied** with server logs: `Invalid user blackberry from ... [preauth]`.

The **old 7.1** setup used `UsePrivilegeSeparation=no`, which changed the user-validation flow. The new 10.2 always uses privilege separation and does a strict `getpwnam(username)` lookup. On BB10/Term49, `blackberry` may not exist in the system user database, so the lookup fails before any auth method runs.

**Fix needed:** The pwfallback (for Term49 UID) must accept `blackberry` (or the username Term49 reports) and map it to the correct UID, even when `getpwnam("blackberry")` returns NULL. Alternatively, document the actual username the device uses so clients can connect with the right User.

**Workaround for users (until fixed):** Run `whoami` on the device in Term49; use that username in `~/.ssh/config` instead of `blackberry`.

## Fallback

If the 10.2 binary cannot be made to work reliably, BerryCore may need to stay on OpenSSH 7.1p2, which worked with the old setup (script wrapper + sbin/sshd, no external helpers).

## BerryCore Context

- Install dir: `/accounts/1000/shared/misc/berrycore` (or user-chosen name under misc)
- We can place files in berrycore/libexec/ and copy to misc/libexec/ during install
- Old 7.1 used: user key as host key, `-f /dev/null`, everything via `-o`, no config file
- BB10/Term49: pwfallback for UID, static OpenSSL/zlib – keep these fixes
