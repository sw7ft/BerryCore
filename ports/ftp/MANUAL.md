# FTP for BlackBerry Passport — Manual

Classic **netkit `ftp`** client + **bftpd** server, cross-built for QNX 8 / BerryCore.

| Binary | Version | Role |
|--------|---------|------|
| `ftp` | netkit 0.17 | Old-school interactive FTP client |
| `pftp` | symlink | Same as `ftp` |
| `bftpd` | 5.4 | Lightweight FTP server |

Install prefix: `/accounts/1000/shared/misc`

---

## Install

```bash
tar xzf ftp-passport-qnx8.tar.gz -C /
export PATH="/accounts/1000/shared/misc/bin:$PATH"
mkdir -p /accounts/1000/shared/misc/ftp-root
mkdir -p /accounts/1000/shared/misc/var/log
```

---

## Classic `ftp` client

Interactive — just like the old days:

```bash
ftp 192.168.1.179
# Name: youruser
# Password: ****

ftp> ls
ftp> cd pub
ftp> get file.txt
ftp> put local.bin
ftp> binary
ftp> quit
```

One-liner (non-interactive):

```bash
ftp -n 192.168.1.179 <<EOF
user myuser mypass
binary
get remote.txt
quit
EOF
```

`.netrc` in home directory works (same as Linux):

```text
machine 192.168.1.179 login myuser password mypass
```

Then: `ftp 192.168.1.179` logs in automatically.

**Note:** Plain FTP sends passwords unencrypted. Use only on trusted home LAN, or prefer SFTP/SSH when available.

---

## `bftpd` server (share files from Passport)

### First-time setup

```bash
cp /accounts/1000/shared/misc/etc/bftpd.conf.example \
   /accounts/1000/shared/misc/etc/bftpd.conf

# Edit PATH= to your shared folder
mkdir -p /accounts/1000/shared/misc/ftp-root
```

### Start server (standalone)

```bash
bftpd -c /accounts/1000/shared/misc/etc/bftpd.conf -D
```

From another machine on LAN:

```bash
ftp <passport-ip>
# anonymous or configured user
```

### Stop server

Find PID and kill, or from Term49: `killall bftpd`

---

## Connect to your PC

Your Pop!_OS PC can run an FTP server too, or use the existing web upload at port 8080.

From Passport:

```bash
ftp 192.168.1.179
```

Or upload to PC Gitea / SCP as alternatives.

---

## Troubleshooting

| Problem | Fix |
|---------|-----|
| `ftp: connect: Connection refused` | Server not running or wrong IP/port |
| `ftp: Login incorrect` | Check user/pass; bftpd may need anonymous YES in conf |
| Passive mode hangs | Set `PASSIVE_PORTS` in bftpd.conf; open ports on firewall |
| `bftpd: permission denied` | Run as user with access to PATH directory |
| Port 21 blocked | BB10 firewall — test on same Wi‑Fi first |

---

## Security notes

- FTP is **plaintext** — OK on home LAN only
- Prefer **SSH/SFTP** for sensitive files
- Do not expose bftpd to the public internet
- Anonymous upload should stay disabled unless you know why you need it

---

## Rebuild

```bash
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/ftp bb10-kitchen-sink:/root/ports/ftp-docs'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/ftp/patches bb10-kitchen-sink:/root/ports/ftp-patches'
sg docker -c 'docker cp ~/Desktop/BlackBerry\ 10/ports/build-ftp-passport.sh bb10-kitchen-sink:/root/ports/'
sg docker -c 'docker exec bb10-kitchen-sink bash -lc "bash /root/ports/build-ftp-passport.sh"'
sg docker -c 'docker cp bb10-kitchen-sink:/root/ports/ftp-build/ftp-passport-qnx8.tar.gz ~/Desktop/BlackBerry\ 10/ports/'
```

Patches: `ftp/patches/bftpd-qnx-*.patch`
