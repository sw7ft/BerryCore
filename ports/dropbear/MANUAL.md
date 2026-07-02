# Dropbear SSH for BlackBerry Passport — Manual

**Dropbear 2026.91** — lightweight SSH server and client for QNX 8 / BerryCore.

| Binary | Role |
|--------|------|
| `dbclient` | SSH client (connect, port forward, scp-style use via other tools) |
| `ssh` | Symlink to `dbclient` |
| `dropbear` | SSH server (listen on Passport) |
| `dropbearkey` | Generate host/user keys |

Install prefix: `/accounts/1000/shared/misc`

Static binaries with bundled **libtomcrypt** / **libtommath** (no external crypto libs).

---

## Install

```bash
tar xzf dropbear-passport-qnx8.tar.gz -C /
export PATH="/accounts/1000/shared/misc/bin:$PATH"
mkdir -p /accounts/1000/shared/misc/etc/dropbear
```

---

## SSH client (`dbclient` / `ssh`)

Connect to your PC or LAN host:

```bash
dbclient mp@192.168.1.179
ssh mp@192.168.1.179          # same binary

# With key
dbclient -i ~/.ssh/id_ed25519 mp@192.168.1.179

# Local port forward (PC service → Passport localhost)
dbclient -L 8080:127.0.0.1:3000 mp@192.168.1.179

# Remote port forward
dbclient -R 8022:127.0.0.1:22 mp@192.168.1.179
```

Generate a client key on Passport:

```bash
dropbearkey -t ed25519 -f /accounts/1000/shared/misc/etc/dropbear/id_ed25519
# Public half: id_ed25519.pub — add to PC ~/.ssh/authorized_keys
```

Copy public key to PC:

```bash
cat /accounts/1000/shared/misc/etc/dropbear/id_ed25519.pub
# paste into ~/.ssh/authorized_keys on 192.168.1.179
```

---

## SSH server (`dropbear`)

Generate host key (once):

```bash
dropbearkey -t ed25519 -f /accounts/1000/shared/misc/etc/dropbear/dropbear_ed25519_host_key
```

Run in foreground (test):

```bash
dropbear -F -E -p 2222 \
  -r /accounts/1000/shared/misc/etc/dropbear/dropbear_ed25519_host_key
```

From PC:

```bash
ssh -p 2222 user@192.168.1.xxx   # Passport LAN IP
# or
dbclient -p 2222 user@192.168.1.xxx
```

### QNX notes

- Built with **single-user** mode (`DROPBEAR_SVR_MULTIUSER=0`) — no `setresgid()` on QNX.
- **Password auth** works if `/etc/passwd` + `crypt` are available on BerryCore.
- **Pubkey auth** recommended.
- No PAM, no utmp/wtmp.

---

## Typical workflows

**SSH from Passport → PC** (Gitea, files, build):

```bash
ssh mp@192.168.1.179
```

**Reverse tunnel** (expose Passport SSH via PC):

```bash
dbclient -R 8022:127.0.0.1:2222 mp@192.168.1.179
# then from elsewhere: ssh -p 8022 mp@192.168.1.179
```

**Tunnel for HTTP API** (until WireGuard/proxy is up):

```bash
dbclient -L 3000:127.0.0.1:3000 mp@192.168.1.179
curl http://127.0.0.1:3000/api/v1/version
```

---

## Rebuild

```bash
sg docker -c 'docker exec bb10-kitchen-sink mkdir -p /root/ports/dropbear-opts /root/ports/dropbear-docs'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/dropbear/localoptions.h bb10-kitchen-sink:/root/ports/dropbear-opts/'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/dropbear/MANUAL.md bb10-kitchen-sink:/root/ports/dropbear-docs/'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/build-dropbear-passport.sh bb10-kitchen-sink:/root/ports/'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-dropbear-passport.sh"'
sg docker -c 'docker cp bb10-kitchen-sink:/root/ports/dropbear-build/dropbear-passport-qnx8.tar.gz ~/Desktop/BlackBerry\ 10/ports/'
```

QNX overrides: `dropbear/localoptions.h`.
