# Content Shell Term49 Port

Chromium 120 headless browser for BB10 via Term49. Renders web pages and dumps the DOM (after JavaScript) to stdout. Works over HTTP and HTTPS.

## Install

```bash
qpkg install content-shell-term49
```

## Quick test

```bash
content_shell                          # Hello world
content_shell help                     # Show help
content_shell http://example.com       # HTTP (use 2>/dev/null to quiet stderr)
content_shell https://example.com      # HTTPS
```

## Save to file

```bash
content_shell http://example.com > page.html 2>/dev/null
```

## JS-heavy pages (Google, etc.)

```bash
content_shell https://www.google.com --timeout=15000 2>/dev/null
```

## Help

```bash
content_shell help
```

Or: `cat $NATIVE_TOOLS/share/content-shell-term49/HELP.txt`

---

## For maintainers: build the port

Requires `content-shell-term49.zip` at repo root (or pass path):

```bash
cd ports/content-shell-term49
./build-port.sh
# Output: ../web-content-shell-term49-1.0.zip
```

Then commit the zip to `ports/` and ensure `ports/INDEX` has the entry.
