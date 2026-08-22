# talkbutton — play/pause dictation (Passport)

Background daemon by default. Play/pause starts listening, play/pause stops.
Transcript goes to the **system clipboard** (paste in any app), the Hub, and
`last.txt`. No web server. We cannot inject into the focused field from this
process — BB10 has no world-writable “paste into whoever has focus” API —
so clipboard is the everywhere path.

```sh
. /accounts/1000/shared/misc/berrycore/env.sh
talkbutton          # background
talkbutton -f       # Term49 foreground
talkbutton stop
```

Canonical tree: `repo/ports/talkbutton/`  
On device: `$BC/bin/talkbutton` + `$BC/share/talkbutton/`  
`qpkg install talkbutton` → `util-talkbutton-1.0.zip` (helpers bundled).  
Also finds `share/voice2text/` if the zip helpers are missing.

Do not run at the same time as webrtc-mic (`mic` :8028) or voice2text (`talk`
:8029) — the QSA mic is exclusive. voice2text was replaced by this tool; leave
:8029 stopped unless someone asks for the web UI again.

---

## Mic (QSA)

Raw `os.read('/dev/snd/...')` returns **0 bytes**. Capture has to go through
QNX Sound Architecture:

1. `libasound` + `libaudio_manager`
2. `audio_manager_snd_pcm_open_name("voice")` (also try `pcmPreferredc`)
3. `snd_pcm_plugin_params` / `plugin_prepare` / **`snd_pcm_plugin_read`**
4. S16_LE, 16 kHz, mono. `Params` struct is **752** bytes.

If a browser tab still holds getUserMedia, native capture gets nothing — release
the WebKit mic first.

Play/pause is `bid_playpause` on `/pps/system/buttons/status` (`b_up` / `b_down`).
`cat` does not block; poll ~50 ms and toggle on the **down** edge. Same PPS object
the `player` script talks to, opposite direction.

---

## Vosk

Warm the model **once at startup** (~12–17 s), then decode in-process.

- `libvosk.so` + `model/vosk-en` under `/accounts/1000/shared/misc/stt/`
- ctypes: pass PCM with `from_buffer_copy` — **not** `c_char_p` (audio has NULs)
- Demo wav that must work: `/accounts/1000/shared/misc/stt/tmp/goforward16.wav`
  (16 kHz) → `"go forward ten meters"`. Do **not** use `share/goforward.wav`
  (8 kHz; garbled).
- `qpkg install vosk` if the lib/model are missing.

Last transcript is also written to `share/talkbutton/last.txt` and copied with
`bb_clipboard.copy_text` (`libclipboard.so.1`, `text/plain`, store
`/accounts/1000/clipboard/text.plain`). Same path voice2text used. Paste in
Term49 with metamode `v`, or the usual paste in any other app.

---

## Hub notification

Writes `/pps/services/notify/control` the **same way RocketChat2 posts chat
alerts** (`share/rocketchat2/app.py` `execute_shell_command`, called from
`check_for_new_messages`).

```
msg::notify
dat:json:{"itemid":"RocketChat-<id>","title":"🚀 Transcribed","subtitle":"Talkbutton: …","target":"","targetAction":"","payload":"http://localhost:8027","payloadType":"url","payloadURI":"http://localhost:8027"}
```

What actually shows in Hub (do not “improve” these):

| Field | Working value |
|-------|----------------|
| `msg` | `notify` (lowercase) |
| `itemid` | `RocketChat-<unique>` — same prefix the chat loop uses (`RocketChat-%s % rid`) |
| `title` | `🚀 %s` % name (rocket + space). Plain `Transcribed` does not appear. |
| `payloadType` | `url` |
| `payload` / `payloadURI` | `http://localhost:8027` (RocketChat2’s port) |

`itemid=RocketChat` with no suffix is only the scheduled-job default and does
**not** show. PascalCase `ItemId` / `msg::Notify` (libbps names) also does not
show. Append with `os.open(..., O_WRONLY|O_APPEND)` + one `os.write` of the
two-line message, same as RocketChat2.

LED `/pps/services/led/control` is unusable without impersonation (`led_control`
group). Vibrator `/pps/services/vibrator` works but is not needed for Hub.
