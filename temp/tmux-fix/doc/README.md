# tmux - Terminal Multiplexer for QNX

**Version:** 3.3a  
**Category:** System Utilities  
**Built for:** BlackBerry QNX 8 (ARM)

## Description

tmux is a terminal multiplexer that allows multiple terminal sessions to be accessed simultaneously in a single window. It's extremely useful for remote SSH sessions where you need to run multiple programs or maintain long-running processes.

## Features

- **Multiple Windows**: Create and switch between multiple terminal windows
- **Split Panes**: Split your screen horizontally and vertically
- **Session Persistence**: Detach from sessions and reattach later (survives SSH disconnections!)
- **Customizable**: Extensive configuration via `~/.tmux.conf`
- **Scriptable**: Automate session creation and management

## Quick Start

```bash
# Start tmux
tmux

# Create a new named session
tmux new -s mysession

# List sessions
tmux ls

# Attach to existing session
tmux attach -t mysession

# Detach from session (inside tmux)
Ctrl-b d
```

## Essential Key Bindings

All tmux commands start with the **prefix**: `Ctrl-b`

### Windows
- `Ctrl-b c` - Create new window
- `Ctrl-b n` - Next window
- `Ctrl-b p` - Previous window
- `Ctrl-b w` - List windows

### Panes
- `Ctrl-b %` - Split vertically
- `Ctrl-b "` - Split horizontally
- `Ctrl-b arrow` - Move between panes
- `Ctrl-b x` - Kill pane

### Sessions
- `Ctrl-b d` - Detach from session
- `Ctrl-b s` - List sessions
- `Ctrl-b $` - Rename session

### Help
- `Ctrl-b ?` - Show all key bindings

## Common Use Case: Persistent SSH Sessions

```bash
# Connect to your QNX device
ssh user@device

# Start tmux
tmux new -s work

# Do your work...
# If SSH disconnects or you need to logout:
Ctrl-b d

# Later, reconnect and reattach
ssh user@device
tmux attach -t work
# Your session is exactly as you left it!
```

## Configuration

Create `~/.tmux.conf` for custom settings:

```bash
# Example configuration
# Enable mouse support
set -g mouse on

# Start window numbering at 1
set -g base-index 1

# Increase scrollback history
set -g history-limit 10000

# Status bar colors
set -g status-bg black
set -g status-fg green
```

## Technical Details

- **tmux version**: 3.3a
- **libevent version**: 2.1.12 (bundled)
- **Dependencies**: libncursesw, libm, libsocket, libc (QNX system libraries)
- **Architecture**: ARM EABI5
- **Wrapper script**: Automatically sets `LD_LIBRARY_PATH` and locale settings

## Notes

- The wrapper script sets `LC_ALL=C` by default (QNX has limited locale support)
- libevent libraries are bundled in the package
- Session files are stored in `/tmp/tmux-<uid>/`

## Troubleshooting

**Problem**: "couldn't create directory /dev/shm/tmux-... no such file or directory"  
**Solution**: The wrapper handles this automatically (sets `TMUX_TMPDIR=/tmp`). QNX doesn't have `/dev/shm`, so tmux uses `/tmp` instead.

**Problem**: "invalid LC_ALL, LC_CTYPE or LANG"  
**Solution**: The wrapper handles this automatically. If running tmux.bin directly, set:
```bash
export LC_ALL=C
export LANG=C
```

**Problem**: "Could not load library libevent"  
**Solution**: The wrapper handles this automatically. If running tmux.bin directly, set:
```bash
export LD_LIBRARY_PATH=/path/to/tmux/../lib:$LD_LIBRARY_PATH
```

**Manual Setup** (if needed):
```bash
export TMUX_TMPDIR=/tmp
export LC_ALL=C
export LANG=C
export LD_LIBRARY_PATH=/path/to/lib:$LD_LIBRARY_PATH
```

## Resources

- Official tmux site: https://github.com/tmux/tmux
- Cheat sheet: https://tmuxcheatsheet.com/
- Man page: https://man.openbsd.org/tmux

---

**Built for BerryCore on BlackBerry QNX 8 ARM**

