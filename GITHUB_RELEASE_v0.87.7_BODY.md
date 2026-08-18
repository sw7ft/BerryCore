## BerryCore v0.87.7

The Library ships in the core zip: an on-device shelf and reader for EPUB and other text, plus the Bell Labs UNIX papers and MIT’s xv6 book.

### Added

- **`library`** / **`books`** — shelf + reader on port **8094**
- **Formats** — EPUB (preferred), FB2, HTML/XHTML, Markdown, plain text
- **Categories** — expandable shelves you can add, rename, reorder; tap a gold chip to file or delete a title
- **Archive / import** — zip the shelf (and progress) to Documents; import from Documents / Downloads
- **Back** — Library control and the Passport back key return to the shelf
- **Bundled texts** in `share/books/classics/`
  - Ritchie & Thompson, *The UNIX Time-Sharing System*
  - Thompson, *UNIX Implementation*
  - Ritchie, *The UNIX I/O System*, *On the Security of UNIX*, *Evolution of Unix*, *Development of C*, Streams
  - *Setting Up UNIX — Seventh Edition*
  - MIT xv6 book (RISC-V)

HTML papers have no cover art (letter tiles). Gutenberg EPUBs you add yourself still show covers. K&R, Kernighan & Pike, and Bach are still in copyright and are not bundled.

### Use

```sh
library
berry-browser http://127.0.0.1:8094/
library stop
```

Put your own books in `/accounts/1000/shared/books`.

See `RELEASE_FILES_v0.87.7.txt` for checksums.
