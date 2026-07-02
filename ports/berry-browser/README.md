# BerryBrowser — CLI browser for Term49 / SSH

**`berry-browser`** is the main command — a polished CLI wrapper around headless
`content_shell`. Chromium renders JavaScript; you get clean readable text in the
terminal. Works in **Term49** (no display needed).

Full-screen UI is separate: **`berry-browser-screen`** (native QNX only).

## Install

```sh
qpkg install berry-browser
```

## Usage

```sh
berry-browser example.com
berry-browser https://news.ycombinator.com
berry-browser -l https://example.com      # links only
berry-browser -t https://example.com      # title
berry-browser -r https://example.com      # raw HTML
berry-browser -o page.html https://example.com
berry-browser                             # interactive REPL
```

Alias: `browse` = `berry-browser`

## vs elinks

| | elinks | berry-browser |
|---|--------|---------------|
| JS | Limited | Full Chromium |
| Speed | Fast | Slower (headless render) |
| Term49 | Yes | Yes |

## Rebuild

```bash
./ports/berry-browser/build-port.sh browser-chromium-terminal-build27.zip
```
