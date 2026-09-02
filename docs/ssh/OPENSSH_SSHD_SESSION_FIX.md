# sshd-session Fix

## Problem

sshd fails with: `/accounts/1000/shared/misc/libexec/sshd-session does not exist or is not executable`

The OpenSSH 10.2 binary was built with a SessionProgram that expects this path (parent of berrycore install).

## Solution

1. **Added `libexec/sshd-session`** to openssh-10.2p1.zip – minimal script that exec's the user's shell or command.

2. **Updated `install.sh`** – After package install, copies `libexec/sshd-session` to `$(dirname $INSTALL_DIR)/libexec/` so the binary finds it.

## For existing installs (manual fix)

The sshd binary expects **both** sshd-session and sshd-auth in `/accounts/1000/shared/misc/libexec/` (parent of berrycore – path is baked into the binary).

Run on device:

```bash
mkdir -p /accounts/1000/shared/misc/libexec

# sshd-session
cat > /accounts/1000/shared/misc/libexec/sshd-session << 'EOF'
#!/bin/sh
if [ $# -gt 0 ]; then exec "$@"; else exec ${SHELL:-/bin/sh} -l; fi
EOF

# sshd-auth
cat > /accounts/1000/shared/misc/libexec/sshd-auth << 'EOF'
#!/bin/sh
if [ $# -gt 0 ]; then exec "$@"; else exec ${SHELL:-/bin/sh} -l; fi
EOF

chmod +x /accounts/1000/shared/misc/libexec/sshd-session /accounts/1000/shared/misc/libexec/sshd-auth
```

Or re-run install.sh with the updated berrycore.zip.
