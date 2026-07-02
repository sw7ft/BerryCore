#!/bin/sh
# berry-browser CLI library — sourced by bin/berry-browser

ROOT="${BB_ROOT:-$NATIVE_TOOLS/share/berry-browser}"

bb_usage() {
    cat <<EOF
BerryBrowser — CLI browser via Chromium content_shell
Works in Term49, SSH, and native shell (no display required).

Usage:
  berry-browser URL              Fetch and print readable text
  berry-browser                  Interactive mode (REPL)
  berry-browser -r URL           Raw HTML / DOM dump
  berry-browser -l URL           List links only
  berry-browser -t URL           Print page title only
  berry-browser -o file URL      Save HTML, also print text
  berry-browser -T MS URL        Timeout ms (default: 45000)
  berry-browser -w COLS URL      Wrap text width (default: 78)
  berry-browser -q URL           Quiet (no status on stderr)

Examples:
  berry-browser example.com
  berry-browser https://example.com
  berry-browser -l https://news.ycombinator.com
  berry-browser -r https://example.com | head -50

Full-screen (native QNX only):  berry-browser-screen [URL]
Low-level engine:               content_shell URL 2>/dev/null

Also: elinks URL  — classic TUI (qpkg install elinks, no JS)
EOF
}

bb_normalize_url() {
    _bb_url="$1"
    case "$_bb_url" in
        http://*|https://*|file://*) ;;
        *) _bb_url="https://$_bb_url" ;;
    esac
    printf '%s' "$_bb_url"
}

bb_fetch_html() {
    _bb_url="$1"
    _bb_out="$2"
    _bb_timeout="$3"
    _bb_quiet="$4"

    if [ ! -x "$ROOT/bin/content_shell" ]; then
        echo "berry-browser: not installed (qpkg install berry-browser)" >&2
        return 1
    fi

    export LD_LIBRARY_PATH="$ROOT/lib:${LD_LIBRARY_PATH:-}"

    # Avoid pile-up from stuck renders
    killall content_shell 2>/dev/null || true

    [ "$_bb_quiet" = 1 ] || echo "berry-browser: fetching $_bb_url ..." >&2

    _bb_err="${TMPDIR:-/accounts/1000/shared/downloads}/.bb-$$.err"
    _bb_bin="$ROOT/bin"
    _bb_kill_after=$(( _bb_timeout / 1000 + 20 ))

    # content_shell must run from bin/ (pak files, root_store.certs) with dump-dom flags
    (
        cd "$_bb_bin" || exit 1
        ./content_shell \
            --no-sandbox --no-first-run --single-process --disable-gpu \
            --disable-logging --dump-dom \
            "$_bb_url" --timeout="$_bb_timeout"
    ) >"$_bb_out" 2>"$_bb_err" &
    _bb_pid=$!

    (
        sleep "$_bb_kill_after"
        kill "$_bb_pid" 2>/dev/null
        killall content_shell 2>/dev/null || true
    ) &
    _bb_watch=$!

    if wait "$_bb_pid" 2>/dev/null; then
        _bb_rc=0
    else
        _bb_rc=$?
    fi
    kill "$_bb_watch" 2>/dev/null || true
    wait "$_bb_watch" 2>/dev/null || true

    if [ "$_bb_rc" -ne 0 ]; then
        [ "$_bb_quiet" = 1 ] || [ ! -s "$_bb_err" ] || tail -5 "$_bb_err" >&2
        rm -f "$_bb_err"
        echo "berry-browser: fetch failed for $_bb_url" >&2
        return 1
    fi
    rm -f "$_bb_err"

    if [ ! -s "$_bb_out" ]; then
        echo "berry-browser: empty response from $_bb_url" >&2
        return 1
    fi

    [ "$_bb_quiet" = 1 ] || echo "berry-browser: done" >&2
    return 0
}

bb_render_text() {
    _bb_html="$1"
    _bb_mode="$2"
    _bb_width="$3"

    if command -v python3 >/dev/null 2>&1; then
        python3 - "$_bb_html" "$_bb_mode" "$_bb_width" <<'PY'
import html.parser, html, re, sys, textwrap

path, mode, width = sys.argv[1], sys.argv[2], int(sys.argv[3])

with open(path, "rb") as f:
    raw = f.read().decode("utf-8", "replace")

class BerryParser(html.parser.HTMLParser):
    SKIP = {"script", "style", "head", "noscript", "svg", "path"}
    BLOCK = {
        "p", "div", "br", "li", "tr", "h1", "h2", "h3", "h4", "h5", "h6",
        "hr", "section", "article", "header", "footer", "main", "nav",
        "blockquote", "pre", "table", "ul", "ol", "dl", "figure"
    }
    HEADING = {"h1", "h2", "h3", "h4", "h5", "h6"}

    def __init__(self):
        super().__init__()
        self.skip = 0
        self.parts = []
        self.title = []
        self.in_title = 0
        self.links = []
        self._href = None
        self._link_text = []

    def handle_starttag(self, tag, attrs):
        t = tag.lower()
        ad = dict(attrs)
        if t == "title":
            self.in_title = 1
        if t == "a" and "href" in ad:
            self._href = ad["href"]
            self._link_text = []
        if t in self.SKIP:
            self.skip += 1
        elif t in self.HEADING:
            self.parts.append("\n\n")
        elif t in self.BLOCK:
            self.parts.append("\n")

    def handle_endtag(self, tag):
        t = tag.lower()
        if t == "title":
            self.in_title = 0
        if t == "a" and self._href:
            txt = " ".join("".join(self._link_text).split())
            if txt or self._href:
                self.links.append((txt or self._href, self._href))
            self._href = None
            self._link_text = []
        if t in self.SKIP and self.skip:
            self.skip -= 1
        elif t in self.HEADING or t in self.BLOCK:
            self.parts.append("\n")

    def handle_data(self, data):
        if self.in_title:
            self.title.append(data)
            return
        if self._href is not None:
            self._link_text.append(data)
        if self.skip:
            return
        s = data.replace("\r", " ")
        if s.strip():
            self.parts.append(s)

    def handle_entityref(self, name):
        self.handle_data(html.unescape(f"&{name};"))

    def handle_charref(self, name):
        self.handle_data(html.unescape(f"&#{name};"))

p = BerryParser()
try:
    p.feed(raw)
    p.close()
except html.parser.HTMLParserReset:
    pass

title = html.unescape("".join(p.title).strip())

if mode == "title":
    print(title or "(no title)")
    sys.exit(0)

if mode == "links":
    if title:
        print(title)
        print("=" * min(len(title), 72))
    seen = set()
    n = 0
    for txt, href in p.links:
        href = html.unescape(href.strip())
        if not href or href.startswith("javascript:"):
            continue
        key = (txt, href)
        if key in seen:
            continue
        seen.add(key)
        n += 1
        label = html.unescape(txt.strip()) if txt else href
        print(f"[{n}] {label}")
        if label != href:
            print(f"    {href}")
    if n == 0:
        print("(no links found)")
    sys.exit(0)

body = html.unescape("".join(p.parts))
body = re.sub(r"[ \t]+\n", "\n", body)
body = re.sub(r"\n[ \t]+", "\n", body)
body = re.sub(r"\n{3,}", "\n\n", body)
body = body.strip()

if title:
    bar = "=" * min(max(len(title), 20), width)
    header = f"{title}\n{bar}\n\n"
else:
    header = ""

out = header + body
if width > 0:
    lines = []
    for line in out.splitlines():
        if not line.strip():
            lines.append("")
        else:
            lines.extend(textwrap.wrap(line, width=width, break_long_words=False, break_on_hyphens=False) or [""])
    out = "\n".join(lines)

sys.stdout.write(out)
if not out.endswith("\n"):
    sys.stdout.write("\n")
PY
        return $?
    fi

    # elinks fallback for text mode only
    if [ "$_bb_mode" = "text" ] && command -v elinks >/dev/null 2>&1; then
        elinks -dump "file://$_bb_html" 2>/dev/null
        return $?
    fi

    sed 's/<script[^>]*>.*<\/script>//g; s/<style[^>]*>.*<\/style>//g; s/<[^>]*>//g; s/&nbsp;/ /g; s/&amp;/\&/g; s/&lt;/</g; s/&gt;/>/g; s/&#39;/'"'"'/g' "$_bb_html" \
        | tr -s ' \n' ' \n' | head -800
}

bb_interactive() {
    echo "BerryBrowser interactive — enter URL or :q to quit"
    while printf 'bb> '; read -r _bb_line; do
        [ -z "$_bb_line" ] && continue
        case "$_bb_line" in
            :q|:quit|exit|quit) break ;;
            help|-h|\?) bb_usage ;;
            :raw\ *) bb_main -r ${_bb_line#:raw } ;;
            :links\ *) bb_main -l ${_bb_line#:links } ;;
            *) bb_main "$_bb_line" ;;
        esac
        echo ""
    done
}

bb_main() {
    TIMEOUT=45000
    RAW=0
    MODE="text"
    OUT=
    URL=
    QUIET=0
    WIDTH=78

    while [ $# -gt 0 ]; do
        case "$1" in
            help|-h|--help) bb_usage; return 0 ;;
            -r|--raw) RAW=1; MODE="raw"; shift ;;
            -l|--links) MODE="links"; shift ;;
            -t|--title) MODE="title"; shift ;;
            -q|--quiet) QUIET=1; shift ;;
            -T|--timeout) TIMEOUT="$2"; shift 2 ;;
            -o|--output) OUT="$2"; shift 2 ;;
            -w|--width) WIDTH="$2"; shift 2 ;;
            -*) echo "berry-browser: unknown option $1" >&2; bb_usage >&2; return 1 ;;
            *) URL="$1"; shift ;;
        esac
    done

    [ -n "$URL" ] || { bb_interactive; return 0; }

    URL="$(bb_normalize_url "$URL")"
    TMP="${TMPDIR:-/accounts/1000/shared/downloads}/.berry-browser-$$.html"
    trap 'rm -f "$TMP"' 0 INT TERM HUP

    bb_fetch_html "$URL" "$TMP" "$TIMEOUT" "$QUIET" || return 1

    if [ -n "$OUT" ]; then
        cp "$TMP" "$OUT"
        [ "$QUIET" = 1 ] || echo "berry-browser: saved $OUT" >&2
    fi

    if [ "$RAW" = 1 ] || [ "$MODE" = "raw" ]; then
        cat "$TMP"
        return 0
    fi

    bb_render_text "$TMP" "$MODE" "$WIDTH"
}
