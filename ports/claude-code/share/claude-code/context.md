# BlackBerry 10 + BerryCore — AI context (Term49 shell)

This file is installed at `$NATIVE_TOOLS/share/claude-code/context.md` (BerryCore port `claude-code`). The `claude` launcher injects it with `--append-system-prompt-file` and also passes `--dangerously-skip-permissions` so tools run without interactive approval (personal device only).

---

## 0. Launcher defaults (read this first)

When started via `claude` (qpkg install claude-code), the process already receives:

- `--dangerously-skip-permissions` — do not re-ask for Bash/edit permissions; execute requested commands.
- `--append-system-prompt-file` pointing at this file (unless disabled).
- **`TMPDIR`**, **`TMP`**, **`TEMP`**, and **`TEMPDIR`** set to **`$HOME/tmp`** (created if missing) so libraries and subprocesses avoid `/tmp`.
- **`CLAUDE_CODE_TMPDIR`** matches **`$TMPDIR`** so Claude’s Bash tool sandbox markers stay under home, not system `/tmp`.
- **`PATH`** is prefixed with **`…/berrycore/bin`** so spawned shells resolve core utilities predictably.
- **`CLAUDE_CODE_SHELL`** and **`SHELL`** point at **BerryCore’s GNU `bash`** (`…/berrycore/bin/bash`). On BB10, **`/bin/sh` is `ksh`** (QNX Korn shell), not bash — if Claude inherits `SHELL=/bin/sh` or a minimal `PATH`, the Bash tool can mis-detect the shell or appear stuck while it snapshots temp/cwd under the wrong directory. The launcher fixes **`CLAUDE_CODE_SHELL`**, **`SHELL`**, **`CLAUDE_CODE_TMPDIR`**, and **`PATH`** for every `node` process. If Bash still misbehaves, run once with **`claude --debug bash`** and inspect logs ([env vars](https://code.claude.com/docs/en/env-vars)).
- **Bash tool “runs forever” (Read/Write still work)** — Claude Code normally builds a **login-shell snapshot** (`d$K` in the bundle) before each Bash invocation. On **QNX / Term49** that snapshot can block indefinitely (PTY / controlling-terminal behavior), while file tools never hit that path. Apply the one-line patch after every **`cli.js` upgrade**:  
  `python3 $NATIVE_TOOLS/share/claude-code/build/patch-cli-bb10-bash-freeze.py $NATIVE_TOOLS/share/claude-code/package/cli.js`  
  (Script is in the port under `share/claude-code/build/`; it replaces the snapshot call with `Promise.resolve(void 0)`.) **Sandbox** is only supported on macOS/Linux in upstream Claude Code (`__4()` is false for `process.platform === "qnx"`); leave sandbox off in settings so `wrapWithSandbox` is not used.

To disable for one run: `CLAUDE_BB10_SKIP_PERMISSION_BYPASS=1` and/or `CLAUDE_BB10_SKIP_CONTEXT=1`. Override the shell with `CLAUDE_CODE_SHELL=/path/to/bash` if needed.

---

## 1. Filesystem policy for the agent (mandatory)

**Treat `$HOME` (`~`) as your only durable read/write workspace.**

| Rule | Detail |
|------|--------|
| **Primary workspace** | `cd` to `$HOME` at the start of substantive work. Create projects, scripts, logs, and artifacts **under `$HOME`** (e.g. `$HOME/src`, `$HOME/work`, `$HOME/logs`). |
| **Read/write scope** | Assume **reliable read/write is limited to `~`**. Do not depend on writing outside `$HOME` unless the user explicitly asks and you have verified permissions. |
| **Never use `/tmp` (including `cat /tmp/text`)** | Do **not** use paths like `/tmp/text`, `/tmp/foo`, or `cat /tmp/...` for scratch files, pipelines, or “quick tests.” On BB10 / Term49, `/tmp` is wrong for this shell. **Always** use **`$HOME/tmp/...`** or **`~/tmp/...`** (same thing after `cd ~`), or a file directly under **`$HOME`** (e.g. `$HOME/text`). The launcher sets `TMPDIR`, `TMP`, `TEMP`, and `TEMPDIR` to **`$HOME/tmp`** — prefer those variables when generating paths. |
| **PPS notify** | Do **not** stage payloads under `/tmp`. Append **directly** to `/pps/services/notify/control` (see §9). |
| **Volatile files** | Use `$TMPDIR`, `$HOME/tmp`, or a subdirectory of `$HOME` you create. |
| **Reading the OS** | You may **read** BerryCore paths (e.g. `/accounts/1000/shared/misc/berrycore/...`) for documentation or tracing behavior, but **default artifact output to `~`**. |

**Anti-patterns (do not do this):** `cat /tmp/text`, `echo … > /tmp/text`, `tee /tmp/…`, `mktemp -p /tmp`, `ls /tmp` as part of normal workflows. **Instead:** `cat "$HOME/tmp/text"`, `printf … > "$HOME/tmp/text"`, or `cat ~/text` if you stored the file in home.

---

## 2. What this environment is

- **OS**: BlackBerry 10 is built on **QNX Neutrino**. Paths resemble Linux; the kernel and ABI are QNX-specific.
- **Shell access**: Usually **Term49** (terminal BAR). `$HOME` is the app’s sandboxed **data** directory, not `/home/username`.
- **Extended userland**: **BerryCore** (sw7ft) under `/accounts/1000/shared/misc/berrycore` — `qpkg`, Python 3, Node, utilities, packaged apps (e.g. `rocketchat`).

---

## 3. Home directory (`~` / `$HOME`)

Typical Term49 `$HOME`:

```
/accounts/1000/appdata/com.update.Term49.gYABgHeOVx7TI8ajV86LufpS8jM/data
```

| Path | Role |
|------|------|
| `.profile` | Sources BerryCore `env.sh`, MOTD, optional `sshd` autostart |
| `.berrysnip/` | BerrySnip DB (`snippets.db`) |
| `.claude/`, `.claude.json` | Claude Code state when run from this home |
| `.npm`, `.cache`, `node_modules` | Node/npm when used from HOME |
| `.terminfo` | Symlink → `../app/native/terminfo` |
| `../app/native/` | Term app bundle (read-only) |
| `tmp/` | Preferred temp directory (launcher sets `TMPDIR` here) |

**BerryCore**: Non-login automation must **source** `/accounts/1000/shared/misc/berrycore/env.sh` for `PATH` and `LD_LIBRARY_PATH`.

**Claude launcher**: If `HOME` is unset, `claude` sets `HOME` to `/accounts/1000/shared/misc`; know which home you are writing to.

---

## 4. Shared storage layout

| Path | Purpose |
|------|---------|
| `/accounts/1000/shared/misc` | **misc** — Claude package, BerryCore, polyfills, this `context.md` |
| `/accounts/1000/shared/documents` | User documents |
| `/accounts/1000/shared/downloads` | Downloads |
| `/accounts/1000/removable/sdcard` | SD card |
| `/accounts/1000/shared/misc/berrycore` | BerryCore root (`$NATIVE_TOOLS`) |

Some `/accounts/1000/appdata/...` trees are not listable from every UID; prefer paths you know work.

---

## 5. BerryCore and `.profile`

`.profile` sources `berrycore/env.sh`, which sets `NATIVE_TOOLS`, `QNX_TARGET`, `PATH`, `LD_LIBRARY_PATH`, `MANPATH`, etc., and defines navigation helpers:

| Command | No args | With args |
|---------|---------|-----------|
| `misc` | `cd /accounts/1000/shared/misc` | `cp` from misc |
| `docs` | `cd` shared documents | `cp` helper |
| `downloads` | `cd` downloads | `cp` helper |
| `sdcard` | `cd` SD root | `cp` helper |
| `bc` | `cd` `$NATIVE_TOOLS` | `cp` helper |

---

## 6. Runtimes: Node and Python 3

| Tool | Typical path | Notes |
|------|----------------|------|
| **Python 3** | `.../berrycore/bin/python3` | Often **3.11.x** |
| **Node** (wrapper) | `.../berrycore/bin/node` | Runs `node.bin --jitless` |
| **Node binary** | `.../berrycore/bin/node.bin` | **v22.x** |

**Claude Code** uses `node.bin --jitless --no-experimental-fetch` plus `bb10-fetch-polyfill.cjs` (no WASM fetch under jitless).

---

## 7. BerrySnip (`berrysnip`)

- **Binary**: `/accounts/1000/shared/misc/berrycore/bin/berrysnip`
- **Help**: `berrysnip help`
- **Subcommands**: `web` (default), `tui`, `add`, `list`
- **Web**: `http://127.0.0.1:8018` (ES5-friendly for BB10 browser)
- **Storage**: `$HOME/.berrysnip/snippets.db`

---

## 8. `qpkg`

- `qpkg catalog`, `qpkg catalog -s`, `qpkg info`, `qpkg bins`, `qpkg ports`, `qpkg install`

---

## 9. Notifications (PPS) — write to the control object, not `/tmp`

Hub notifications are driven by **appending a two-line PPS message** to:

`/pps/services/notify/control`

**Preferred (no temp files):** one `echo` with an embedded newline, appended to the control path. Do **not** create `/tmp/notify_test` (or anything under `/tmp`) and `cat` it; that fails or misleads on this platform and violates the workspace rules in §1.

**Canonical shell example** (replace placeholder JSON fields as needed):

```sh
echo "msg::notify
dat:json:{\"itemid\":\"yourItemIdHere\",\"title\":\"YourTitle\",\"subtitle\":\"YourSubtitle\",\"target\":\"YourTarget\",\"targetAction\":\"YourTargetAction\",\"payload\":\"YourPayload\",\"payloadType\":\"YourPayloadType\",\"payloadURI\":\"YourPayloadURI\"}" >> /pps/services/notify/control
```

In a single line (equivalent, `\n` between the two PPS fields):

```sh
echo "msg::notify\ndat:json:{\"itemid\":\"yourItemIdHere\",\"title\":\"YourTitle\",\"subtitle\":\"YourSubtitle\",\"target\":\"YourTarget\",\"targetAction\":\"YourTargetAction\",\"payload\":\"YourPayload\",\"payloadType\":\"YourPayloadType\",\"payloadURI\":\"YourPayloadURI\"}" >> /pps/services/notify/control
```

**Notes**

- Use **`>>`** (append) on the control object; PPS expects streamed commands.
- Escape double quotes inside the JSON for the shell, or build the string in Python/Node and **still** append to `/pps/services/notify/control` via a single write — if a file is unavoidable, use **`$HOME/tmp/`**, never `/tmp`.
- Some older code (e.g. RocketChat’s `app.py`) used `NamedTemporaryFile` + `cat`; treat that as **legacy**. For new commands and for Claude-generated scripts, use the **direct echo** (or `printf ‘%s\n’ "msg::notify" "dat:json:..."`) pattern above.
- **Claude Bash tool workaround**: Escape sequences (`\n`) may not interpolate correctly in the Bash tool environment. For reliable PPS writes from Claude, use `printf ‘%s\n’` with separate arguments for each line:
  ```sh
  printf ‘%s\n’ ‘msg::notify’ ‘dat:json:{...json...}’ >> /pps/services/notify/control
  ```
  This creates literal newlines naturally instead of relying on escape interpretation.
- Fill `target` / `payload*` fields meaningfully when you need a tap action; placeholders are fine for a simple banner test.

---

## 10. Build order (“inside out”)

1. `echo $HOME`, `cd` to `$HOME` for work.
2. `. /accounts/1000/shared/misc/berrycore/env.sh`
3. `python3 --version`, `node --version`
4. Durable deliverables under `$HOME`; scratch under **`$HOME/tmp`** (never `/tmp` or `cat /tmp/text`).
5. `qpkg` when binaries are missing.
6. PPS notify for headless user alerts.

---

## 11. Quick reference

| Item | Path |
|------|------|
| This file | `$NATIVE_TOOLS/share/claude-code/context.md` |
| Launcher | `$NATIVE_TOOLS/bin/claude` |
| Setup | `$NATIVE_TOOLS/bin/claude-setup` |
| Claude CLI | `$NATIVE_TOOLS/share/claude-code/package/cli.js` |
| Polyfill | `$NATIVE_TOOLS/share/claude-code/bb10-fetch-polyfill.cjs` |
| API key (user) | `$HOME/claude.key` |
| BerryCore env | `$NATIVE_TOOLS/env.sh` |
| RocketChat app | `$NATIVE_TOOLS/share/rocketchat/app.py` |
| PPS notify | `/pps/services/notify/control` |
| Bash snapshot patch | `$NATIVE_TOOLS/share/claude-code/build/patch-cli-bb10-bash-freeze.py` (re-run after `cli.js` upgrades) |

---

*Device-local sandbox. Re-check versions after BerryCore upgrades.*
