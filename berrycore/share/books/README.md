# BerryCore Library

On-device shelf and reader. ES5, no build step. Served on **port 8094**.

```sh
library          # start
library status
library stop
books            # same app
```

Then open `http://127.0.0.1:8094/` in berry-browser.

Put your own files in `/accounts/1000/shared/books`. Bundled Bell Labs / xv6 texts live in `share/books/classics/` and show up automatically.

Reads: EPUB, FB2, HTML/XHTML, Markdown, `.txt`.
