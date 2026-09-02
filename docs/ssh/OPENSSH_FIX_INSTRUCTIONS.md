# OpenSSH 10.2p1 BerryCore Fix – Instructions for Other Agent

## Problem Summary

1. **`sshd -Dd`** – Error: `unable to load host key /accounts/1000/shared/mic/etc/ssh_host key`  
   - Path is truncated (`mic` not `misc`, `ssh_host key` incomplete)  
   - The OpenSSH binary has a broken compile-time default path  
   - Fix: Always pass `-o HostKey=` from the wrapper to override

2. **`sshd-berrycore -Dd`** – Hangs on "Generating SSH host keys"  
   - Generating separate host keys via ssh-keygen blocks (likely slow entropy on BB10)  
   - Fix: Switch back to the **old working approach** – use the user key as the host key, no separate host key generation

## Old Working Approach (from openssh-7.1p2)

The old `bin/sshd` script:

- Used `-f /dev/null` (no config file)
- Used `-o HostKey=$HOME/.ssh/id_rsa` (user key as host key)
- Generated only the user key if missing (one ssh-keygen call)
- Passed all options via `-o` to avoid path issues

## Required Changes

### 1. Update `berrycore/packages/openssh-10.2p1.zip`

Extract, fix, repack.

### 2. Modify `bin/sshd` (wrapper)

Must pass `-o HostKey=` so the binary’s default path is not used.

```sh
#!/bin/sh
DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$DIR/.." && pwd)"

# Binary has broken default path – must pass HostKey
HOSTKEY=""
if [ -f "$HOME/.ssh/id_rsa" ]; then
  HOSTKEY="-o HostKey=$HOME/.ssh/id_rsa"
elif [ -f "$ROOT/etc/ssh_host_ed25519_key" ]; then
  HOSTKEY="-o HostKey=$ROOT/etc/ssh_host_ed25519_key"
elif [ -f "$ROOT/etc/ssh_host_rsa_key" ]; then
  HOSTKEY="-o HostKey=$ROOT/etc/ssh_host_rsa_key"
else
  echo "No host key found. Run: sshd-berrycore  (to generate ~/.ssh/id_rsa)"
  exit 1
fi

exec "$DIR/sshd.bin" -f "$ROOT/etc/sshd_config" $HOSTKEY "$@"
```

### 3. Modify `bin/sshd-berrycore` (old-style quick-start)

- Use the user key as host key (no separate host key generation)
- Use `-f /dev/null` and pass everything via `-o`
- Single ssh-keygen for the user key if missing
- Use ROOT from script path for the Subsystem path

```sh
#!/bin/sh
DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$DIR/.." && pwd)"
VAR="$ROOT/var"
mkdir -p "$VAR/run" "$VAR/empty"

# Only generate user key if missing (one ssh-keygen – matches old working behaviour)
if [ ! -f "$HOME/.ssh/id_rsa" ]; then
  echo "Generating SSH key (may take a minute on first run)..."
  mkdir -p "$HOME/.ssh"
  "$DIR/ssh-keygen" -f "$HOME/.ssh/id_rsa" -t rsa -b 2048 -N '' -q
  cp "$HOME/.ssh/id_rsa.pub" "$HOME/.ssh/authorized_keys" 2>/dev/null
  echo "Transfer ~/.ssh/id_rsa to the computer you connect from."
fi

# Old approach: use user key as host key, -f /dev/null, all options via -o
exec "$DIR/sshd.bin" -f /dev/null \
  -o "HostKey=$HOME/.ssh/id_rsa" \
  -o "Subsystem=sftp $ROOT/bin/sftp-server" \
  -o "Port=2022" \
  -o "PidFile=$VAR/run/sshd.pid" \
  -o "PasswordAuthentication=no" \
  -o "StrictModes=no" \
  "$@"
```

### 4. Repack and rebuild

```bash
cd /tmp/openssh-fix   # or wherever you extracted
zip -r /path/to/BerryCore/berrycore/packages/openssh-10.2p1.zip bin etc var README.txt -x "*.DS_Store"

cd /path/to/BerryCore
./utilities/package.sh
```

## Notes

- If ssh-keygen still hangs on the device, the user can generate `~/.ssh/id_rsa` on another machine and copy it to the device.
- OpenSSH 10.2 does not support `UsePrivilegeSeparation=no`; omit it.
- `sftp-server` lives in `bin/` in this package (old package used `libexec/`).
