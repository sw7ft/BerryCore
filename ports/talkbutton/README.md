# talkbutton

Play/pause push-to-talk on the Passport: QSA mic, warm Vosk, Hub notify.

See [context.md](context.md) for the working mic / Vosk / notification recipe.

```sh
. /accounts/1000/shared/misc/berrycore/env.sh
talkbutton          # background — play/pause from any app
talkbutton -f       # foreground
talkbutton stop
```

Each transcript is written to the BB10 system clipboard (`libclipboard`,
`text/plain`) so you can paste in Hub, browser, Term49 (metamode `v`), etc.

Requires `qpkg install vosk`.

## Rebuild

```sh
./ports/talkbutton/build-port.sh
```

Install: `qpkg install talkbutton`
