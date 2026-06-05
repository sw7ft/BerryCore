# Claude Code Port (BB10)

Anthropic [Claude Code](https://github.com/anthropics/claude-code) packaged for BlackBerry 10 / QNX Term49 via BerryCore.

## Install (users)

```bash
qpkg install node-term49      # required
qpkg install claude-code
claude-setup                  # paste your Anthropic API key
claude --help
claude -p "hello from BB10"
```

## API key

Users bring their own key from [Anthropic Console](https://console.anthropic.com/).

- **Recommended:** `claude-setup` writes `~/claude.key` with mode `600`
- **Manual:** `echo 'sk-ant-...' > ~/claude.key && chmod 600 ~/claude.key`
- **Session:** `export ANTHROPIC_API_KEY=sk-ant-...`

Never commit real keys. See `share/claude-code/claude.key.example`.

## License

Claude Code is © Anthropic. See `share/claude-code/package/LICENSE.md` in the installed port. This BerryCore port ships a BB10-patched bundle; users must provide their own Anthropic API key and comply with [Anthropic's terms](https://www.anthropic.com/legal/consumer-terms).

## What’s included

| Path | Purpose |
|------|---------|
| `bin/claude` | Launcher (Node --jitless, fetch polyfill, BB10 env) |
| `bin/claude-setup` | Interactive API key setup |
| `share/claude-code/package/` | Patched Claude Code 2.1.91 bundle |
| `share/claude-code/bb10-fetch-polyfill.cjs` | fetch without WASM |
| `share/claude-code/context.md` | BB10 system prompt append |

## Requires

- **node-term49** — Node.js v22 with `--jitless` (QNX V8 requirement)
- BerryCore **bash** (for Claude Code Bash tool)

## Build port zip (maintainers)

The patched `package/` tree (~45MB) is built on a BB10 device or copied from a working install, then packaged:

```bash
cd ports/claude-code
./build-port.sh /path/to/package    # directory containing cli.js + vendor/
```

Output: `ports/dev-claude-code-2.1.91.zip`

Host-side rebuild flow (on device in `misc/`):

1. `prepare-bb10-package.sh` / `fetch-on-host.sh` — download upstream tarball
2. `patch-cli-for-bb10.py`, `patch_cli_ucd_payload.py` — Unicode/Intl
3. `patch-cli-bb10-bash-freeze.py` — QNX Bash-tool hang fix (included in `share/claude-code/build/`)

Re-run the bash-freeze patch after every `cli.js` upgrade.

## Port metadata

- **qpkg name:** `claude-code`
- **Category:** `dev`
- **Version:** `2.1.91`
- **Zip:** `dev-claude-code-2.1.91.zip`
