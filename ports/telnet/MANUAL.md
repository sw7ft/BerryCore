# Telnet for BlackBerry Passport — Manual

Classic **netkit `telnet`** client, cross-built for QNX 8 / BerryCore.

| Binary | Version | Role |
|--------|---------|------|
| `telnet` | netkit 0.17 | Interactive TELNET client |

Install prefix: `/accounts/1000/shared/misc`

---

## Install

```bash
tar xzf telnet-passport-qnx8.tar.gz -C /
export PATH="/accounts/1000/shared/misc/bin:$PATH"
```

---

## Basic use

Connect to a host on the LAN (PC, router, embedded device):

```bash
telnet 192.168.1.179
telnet 192.168.1.179 23
telnet example.com 8023
```

Escape to the telnet command prompt: **`Ctrl+]`** (control + right bracket), then type `help`.

Common commands at the `telnet>` prompt:

| Command | Action |
|---------|--------|
| `close` | Drop connection |
| `quit` | Exit telnet |
| `status` | Show link state |
| `set localecho` | Echo locally (useful on some servers) |

Exit the session: **`Ctrl+]`** then `quit`, or close the remote side.

---

## Options

```bash
telnet -8 192.168.1.179          # 8-bit mode
telnet -E 192.168.1.179          # disable escape char
telnet -l myuser 192.168.1.179   # send USER env (server-dependent)
telnet -d 192.168.1.179          # debug trace on stderr
```

---

## Typical workflows

**Debug a TCP service** (banner grab):

```bash
telnet 192.168.1.179 8080
```

**Router / switch admin** (if telnet enabled — prefer SSH when available):

```bash
telnet 192.168.1.1
```

**From Passport to PC** while Gitea/FTP run on the LAN:

```bash
telnet 192.168.1.179 3000   # raw TCP — not HTTP-aware; use curl for HTTP
```

For HTTP/API work, **`curl`** (if on device) or the **gitea** client is usually better. Telnet is for plain TCP text sessions.

---

## Notes

- This package is the **client only** (no `telnetd` server).
- Uses **ncursesw** from the QNX sysroot for terminal handling.
- Plain telnet is **not encrypted**. Use SSH when the remote supports it.

---

## Rebuild

See `ports/README.md`:

```bash
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/telnet bb10-kitchen-sink:/root/ports/telnet-docs'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/telnet/patches bb10-kitchen-sink:/root/ports/telnet-patches'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/build-telnet-passport.sh bb10-kitchen-sink:/root/ports/'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-telnet-passport.sh"'
sg docker -c 'docker cp bb10-kitchen-sink:/root/ports/telnet-build/telnet-passport-qnx8.tar.gz ~/Desktop/BlackBerry\ 10/ports/'
```

Patches live in `telnet/patches/` (QNX `externs.h`, `commands.cc`, `main.cc`).
