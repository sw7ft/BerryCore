# tmux 3.3a Port - Issue Analysis & Findings

## Problems Encountered

### Problem 1: Socket Directory
tmux fails to start with error:
```
couldn't create directory /dev/shmem/tmux-101761000 (No such file or directory)
```

**Root Cause**: The tmux binary was **compiled with hardcoded path** to `/dev/shmem/` for socket files and **does NOT respect** the `TMUX_TMPDIR` environment variable.

### Problem 2: Terminal Type
tmux fails to attach with error:
```
missing or unsuitable terminal: xterm-256color
```

**Root Cause**: QNX has limited terminfo database. The terminal type `xterm-256color` is not available on QNX/BB10.

## What We Tried

### ❌ Attempt 1: Environment Variable
```bash
export TMUX_TMPDIR=/tmp
tmux
```
**Result**: FAILED - tmux ignores the environment variable

### ❌ Attempt 2: Wrapper Script
Updated wrapper to set:
```bash
export TMUX_TMPDIR="${TMUX_TMPDIR:-/tmp}"
mkdir -p "$TMUX_TMPDIR" 2>/dev/null
```
**Result**: FAILED - tmux binary still uses hardcoded `/dev/shmem/`

### ✅ Attempt 3: Manual Socket Path
```bash
tmux -S /tmp/tmux-socket new -s mysession
```
**Result**: SUCCESS! tmux runs with custom socket location

### ✅ Attempt 4: Fix Terminal Type
```bash
export TERM=xterm
tmux -S /tmp/tmux-socket new -s mysession
```
**Result**: SUCCESS! tmux runs with proper terminal type

## QNX Terminal Support

QNX/BB10 has limited terminfo database. Available terminals found:
```bash
$ ls /usr/lib/terminfo/
a  q  v  x
```

Available terminal types on QNX:
- `xterm` - Works ✅ (in `/usr/lib/terminfo/x/`)
- `qansi`, `qansi-m` - QNX ANSI terminals (in `/usr/lib/terminfo/q/`)
- `vt100`, `vt220` - Classic VT terminals (in `/usr/lib/terminfo/v/`)
- `ansi` - Basic ANSI (in `/usr/lib/terminfo/a/`)

**NOT available:**
- `xterm-256color` ❌
- `screen-256color` ❌
- `tmux-256color` ❌

## Solution Options

### Option A: Update Wrapper (Quick Fix) - RECOMMENDED
Modify the wrapper to automatically:
1. Use custom socket location
2. Set proper terminal type

```bash
#!/bin/sh
# tmux wrapper for QNX
# Handles library path, locale, terminal type, and socket location

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
export LD_LIBRARY_PATH="$SCRIPT_DIR/../lib:$LD_LIBRARY_PATH"
export LC_ALL="${LC_ALL:-C}"
export LANG="${LANG:-C}"

# Fix terminal type for QNX (doesn't have xterm-256color)
# Use xterm if TERM is not already set to a QNX-compatible type
case "$TERM" in
    xterm|qansi|qansi-m|vt100|vt220|ansi)
        # Already compatible, keep it
        ;;
    *)
        # Set to xterm (most compatible)
        export TERM=xterm
        ;;
esac

# Use custom socket location (QNX doesn't have /dev/shmem)
SOCKET_PATH="/tmp/tmux-socket"
exec "$SCRIPT_DIR/tmux.bin" -S "$SOCKET_PATH" "$@"
```

**Pros**: 
- Works with current binary ✅
- No recompilation needed ✅
- Fixes BOTH socket and terminal issues ✅
- Users can use tmux normally ✅
- Single socket shared by all sessions ✅

**Cons**:
- Slightly non-standard socket path
- All users share same socket (but sessions are separate)

### Option B: Recompile tmux (Proper Fix)
Recompile tmux with configure options to respect `TMUX_TMPDIR`:

```bash
./configure --enable-tmpdir-env ...
# or patch the source to use /tmp by default
```

**Pros**:
- Proper fix
- Standard tmux behavior
- Respects environment variables

**Cons**:
- Requires recompilation on toolchain server
- More work

### Option C: System Workaround
Document that users need to create `/dev/shmem`:
```bash
mkdir -p /dev/shmem
chmod 1777 /dev/shmem
```

**Pros**:
- Keeps standard tmux behavior
- Simple

**Cons**:
- Requires root/admin
- Not all QNX systems have /dev/shmem
- May not persist across reboots

## Recommended Approach

**Short-term (for v0.71)**: Use Option A - Update wrapper to use `-S /tmp/tmux-socket-<pid>`

**Long-term (future)**: Use Option B - Recompile tmux with proper tmpdir support

## Commands for Toolchain Server

When recompiling tmux, check these:

```bash
# Check configure options
./configure --help | grep -i tmp
./configure --help | grep -i socket

# Look for these options:
# --with-TMUX_TMPDIR=PATH
# --enable-tmpdir-env

# Or check source code for hardcoded paths:
grep -r "/dev/shm" tmux-3.3a/
grep -r "TMUX_TMPDIR" tmux-3.3a/

# Patch if needed before compiling
```

## Immediate Workaround (Until Fix is Deployed)

Users who have already installed tmux can use this workaround:

### Add to ~/.profile:
```bash
# Fix tmux for QNX
export TERM=xterm
alias tm='tmux -S /tmp/tmux-socket'
alias tmux='tmux -S /tmp/tmux-socket'
```

### Usage:
```bash
# Reload profile
. ~/.profile

# Now tmux works normally
tmux new -s work
tmux ls
tmux attach -t work

# Or use tm alias
tm new -s work
tm ls
tm a -t work
```

## Testing Checklist

After fix, test:
- [ ] `tmux` - Start new session (no extra flags needed)
- [ ] `tmux ls` - List sessions  
- [ ] `tmux new -s test` - Named session
- [ ] `tmux attach -t test` - Attach to session
- [ ] Multiple users can run tmux simultaneously
- [ ] Socket files are created in /tmp
- [ ] Sessions persist after detach
- [ ] Terminal displays correctly (no color issues)
- [ ] Works with default TERM from user's shell

## Files to Update

1. `ports/sys-tmux-3.3a.zip` - New binary or wrapper
2. `temp/tmux-fix/bin/tmux` - Updated wrapper script
3. `temp/tmux-fix/doc/README.md` - Usage notes

---

## Summary

### Issues Found:
1. ❌ **Socket Path**: Binary hardcoded to `/dev/shmem/` (doesn't exist on QNX)
2. ❌ **Terminal Type**: Binary expects `xterm-256color` (not available on QNX)

### Solutions:
1. ✅ **Quick Fix (Wrapper)**: Use `-S /tmp/tmux-socket` and set `TERM=xterm` automatically
2. ✅ **User Workaround**: Add aliases and TERM export to ~/.profile
3. 🔄 **Long-term**: Recompile with proper QNX support

### Action Items:
- [ ] Update wrapper script with both fixes (socket + terminal)
- [ ] Test updated wrapper on BB10 device
- [ ] Update documentation with workaround
- [ ] Repackage sys-tmux-3.3a.zip
- [ ] On toolchain server: Check tmux compile options for proper /tmp support

### Current Workaround (Working):
```bash
export TERM=xterm
alias tmux='tmux -S /tmp/tmux-socket'
tmux new -s mysession
```

---

**Status**: Two workarounds available, wrapper fix ready to implement
**Priority**: HIGH - Core functionality broken without fix
**Deployment**: Ready to update wrapper and repackage
**Next Step**: Apply wrapper fix and test on device

