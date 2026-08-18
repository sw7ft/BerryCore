#!/usr/bin/env python3
"""BerryCore Books — EPUB library + reader. Port 8094."""
import hashlib
import json
import os
import posixpath
import re
import shutil
import sys
import time
import zipfile
import xml.etree.ElementTree as ET
from urllib.parse import parse_qs, quote, unquote
from http.server import BaseHTTPRequestHandler, HTTPServer

try:
    from socketserver import ThreadingMixIn
except ImportError:
    class ThreadingMixIn(object):
        pass

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8094
ROOT = os.path.dirname(os.path.abspath(__file__))
BOOKS_DIR = os.environ.get("BERRYCORE_BOOKS", "/accounts/1000/shared/books")
EXTRA_DIRS = [
    "/accounts/1000/shared/documents",
    "/accounts/1000/shared/downloads",
]
DOCS_DIR = os.environ.get("BERRYCORE_DOCS", "/accounts/1000/shared/documents")
CLASSICS_DIR = os.path.join(ROOT, "classics")
FILE_EXTS = (".epub", ".txt", ".text", ".html", ".htm", ".xhtml", ".md", ".markdown", ".fb2")
ARCHIVE_EXTS = FILE_EXTS + (".zip",)
PROGRESS_PATH = os.environ.get(
    "BERRYCORE_BOOKS_PROGRESS",
    "/accounts/1000/shared/misc/berrycore/.tmp/books-progress.json",
)
BOOKMARKS_PATH = os.environ.get(
    "BERRYCORE_BOOKS_BOOKMARKS",
    "/accounts/1000/shared/misc/berrycore/.tmp/books-bookmarks.json",
)
CATEGORIES_PATH = os.environ.get(
    "BERRYCORE_BOOKS_CATEGORIES",
    "/accounts/1000/shared/misc/berrycore/.tmp/books-categories.json",
)

DEFAULT_CATS = [
    {"id": "bell-labs", "name": "Bell Labs UNIX", "open": True},
    {"id": "os", "name": "Operating Systems", "open": True},
    {"id": "fiction", "name": "Fiction", "open": False},
    {"id": "unfiled", "name": "Unfiled", "open": False},
]

CACHE = {"books": None, "t": 0}
TEXT_TYPES = (
    "application/xhtml+xml",
    "text/html",
    "application/x-dtbncx+xml",
    "text/css",
)


def local(tag):
    if tag and "}" in tag:
        return tag.rsplit("}", 1)[1]
    return tag or ""


def text_of(el):
    if el is None:
        return ""
    parts = []
    if el.text:
        parts.append(el.text)
    for c in list(el):
        parts.append(text_of(c))
        if c.tail:
            parts.append(c.tail)
    return "".join(parts).strip()


def find_child(el, name):
    if el is None:
        return None
    for c in list(el):
        if local(c.tag) == name:
            return c
    return None


def find_all(el, name):
    out = []
    if el is None:
        return out
    for c in el.iter():
        if local(c.tag) == name:
            out.append(c)
    return out


def parse_xml(data):
    if isinstance(data, bytes):
        data = data.decode("utf-8", "replace")
    data = data.lstrip("\ufeff")
    return ET.fromstring(data.encode("utf-8"))


class Store(object):
    def __init__(self, kind, path):
        self.kind = kind
        self.path = path
        self._zip = None

    def names(self):
        if self.kind == "dir":
            out = []
            for root, _dirs, files in os.walk(self.path):
                for fn in files:
                    rel = os.path.relpath(os.path.join(root, fn), self.path)
                    out.append(rel.replace(os.sep, "/"))
            return out
        z = self._open()
        return z.namelist()

    def read(self, rel):
        rel = (rel or "").replace("\\", "/").lstrip("/")
        if self.kind == "file":
            try:
                return open(self.path, "rb").read()
            except IOError:
                return None
        if self.kind == "fb2":
            try:
                i = int(re.sub(r"[^0-9]", "", rel) or "0")
            except ValueError:
                i = 0
            parts = getattr(self, "_parts", []) or [""]
            if i < 0 or i >= len(parts):
                return None
            return parts[i].encode("utf-8")
        if self.kind == "dir":
            full = os.path.normpath(os.path.join(self.path, rel))
            if not full.startswith(os.path.normpath(self.path) + os.sep) and full != os.path.normpath(self.path):
                return None
            try:
                return open(full, "rb").read()
            except IOError:
                return None
        z = self._open()
        try:
            return z.read(rel)
        except KeyError:
            for n in z.namelist():
                if n.replace("\\", "/") == rel:
                    return z.read(n)
            return None

    def _open(self):
        if self._zip is None:
            self._zip = zipfile.ZipFile(self.path, "r")
        return self._zip


def is_epub_zip(path):
    try:
        z = zipfile.ZipFile(path, "r")
        names = [n.replace("\\", "/") for n in z.namelist()]
        if "META-INF/container.xml" in names:
            return True
        if "mimetype" in names:
            return z.read("mimetype").strip() == b"application/epub+zip"
    except Exception:
        return False
    return False


def container_opf(store):
    raw = store.read("META-INF/container.xml")
    if not raw:
        return None
    try:
        root = parse_xml(raw)
    except Exception:
        return None
    for el in find_all(root, "rootfile"):
        href = el.get("full-path")
        if href:
            return href.replace("\\", "/")
    return None


def join_href(base, href):
    href = (href or "").split("#", 1)[0]
    if not href:
        return ""
    if href.startswith("/"):
        return href.lstrip("/")
    return posixpath.normpath(posixpath.join(posixpath.dirname(base), href))


def parse_book(store, bid, src):
    opf_path = container_opf(store)
    if not opf_path:
        return None
    raw = store.read(opf_path)
    if not raw:
        return None
    try:
        opf = parse_xml(raw)
    except Exception:
        return None
    title = os.path.basename(src)
    author = ""
    cover_id = ""
    for el in find_all(opf, "title"):
        t = text_of(el)
        if t:
            title = t
            break
    for el in find_all(opf, "creator"):
        t = text_of(el)
        if t:
            author = t
            break
    for el in find_all(opf, "meta"):
        if (el.get("name") or "").lower() == "cover":
            cover_id = el.get("content") or ""
    manifest = {}
    for el in find_all(opf, "item"):
        iid = el.get("id")
        href = el.get("href") or ""
        if iid and href:
            manifest[iid] = {
                "href": join_href(opf_path, href),
                "type": el.get("media-type") or "",
                "props": el.get("properties") or "",
            }
    cover = ""
    if cover_id and cover_id in manifest:
        cover = manifest[cover_id]["href"]
    if not cover:
        for item in manifest.values():
            if "cover-image" in (item.get("props") or ""):
                cover = item["href"]
                break
    if not cover:
        for item in manifest.values():
            if (item.get("type") or "").startswith("image/"):
                href = item["href"].lower()
                if "cover" in href:
                    cover = item["href"]
                    break
    spine = []
    for el in find_all(opf, "itemref"):
        iid = el.get("idref")
        if iid and iid in manifest:
            mt = manifest[iid].get("type") or ""
            if mt in TEXT_TYPES or mt.endswith("xml") or mt.endswith("html"):
                spine.append(manifest[iid]["href"])
    labels = parse_ncx(store, manifest, opf_path)
    chapters = []
    for i, href in enumerate(spine):
        chapters.append({
            "i": i,
            "href": href,
            "title": labels.get(href) or ("Part %d" % (i + 1)),
        })
    return {
        "id": bid,
        "title": title,
        "author": author,
        "cover": bool(cover),
        "cover_path": cover,
        "chapters": len(chapters),
        "spine": chapters,
        "src": src,
        "kind": store.kind,
        "fmt": "epub",
    }


def parse_ncx(store, manifest, opf_path):
    ncx = ""
    for item in manifest.values():
        if item.get("type") == "application/x-dtbncx+xml":
            ncx = item["href"]
            break
    if not ncx:
        return {}
    raw = store.read(ncx)
    if not raw:
        return {}
    try:
        root = parse_xml(raw)
    except Exception:
        return {}
    labels = {}
    for np in find_all(root, "navPoint"):
        label = ""
        src = ""
        for c in list(np):
            if local(c.tag) == "navLabel":
                label = text_of(find_child(c, "text") or c)
            elif local(c.tag) == "content":
                src = c.get("src") or ""
        href = join_href(ncx, src)
        if href and label and href not in labels:
            labels[href] = label
    return labels


HEAD_RE = re.compile(r"<h[1-3][^>]*>([\s\S]*?)</h[1-3]>", re.I)


def polish_titles(store, chapters):
    for ch in chapters:
        t = ch.get("title") or ""
        if t and not t.startswith("Part "):
            continue
        raw = store.read(ch["href"])
        if not raw:
            continue
        if isinstance(raw, bytes):
            raw = raw.decode("utf-8", "replace")
        m = HEAD_RE.search(raw[:12000])
        if not m:
            continue
        label = re.sub(r"<[^>]+>", "", m.group(1))
        label = re.sub(r"\s+", " ", label).strip()
        if label:
            ch["title"] = label[:90]


def pretty_title(path):
    base = os.path.splitext(os.path.basename(path.rstrip("/")))[0]
    base = re.sub(r"[-_]+", " ", base).strip()
    return base or "Untitled"


def file_fmt(name):
    low = name.lower()
    if low.endswith(".epub"):
        return "epub"
    if low.endswith(".fb2"):
        return "fb2"
    if low.endswith(".md") or low.endswith(".markdown"):
        return "md"
    if low.endswith(".html") or low.endswith(".htm") or low.endswith(".xhtml"):
        return "html"
    if low.endswith(".txt") or low.endswith(".text"):
        return "txt"
    return ""


def txt_to_html(text):
    text = (text or "").replace("\r\n", "\n").replace("\r", "\n")
    text = text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    parts = re.split(r"\n\s*\n", text)
    out = []
    for p in parts:
        p = p.strip()
        if p:
            out.append("<p>" + p.replace("\n", "<br>") + "</p>")
    return "\n".join(out) or "<p>(empty)</p>"


def md_to_html(text):
    text = (text or "").replace("\r\n", "\n")
    text = text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    out = []
    buf = []

    def flush():
        if buf:
            out.append("<p>" + " ".join(buf) + "</p>")
            buf[:] = []

    for line in text.split("\n"):
        if line.startswith("# "):
            flush()
            out.append("<h1>" + line[2:].strip() + "</h1>")
        elif line.startswith("## "):
            flush()
            out.append("<h2>" + line[3:].strip() + "</h2>")
        elif line.startswith("### "):
            flush()
            out.append("<h3>" + line[4:].strip() + "</h3>")
        elif not line.strip():
            flush()
        else:
            buf.append(line.strip())
    flush()
    return "\n".join(out) or "<p>(empty)</p>"


def html_to_body(raw):
    if isinstance(raw, bytes):
        raw = raw.decode("utf-8", "replace")
    raw = SCRIPT_RE.sub("", raw)
    raw = STYLE_RE.sub("", raw)
    m = BODY_RE.search(raw)
    return m.group(1) if m else raw


def fb2_inline(el):
    if el is None:
        return ""
    parts = []
    if el.text:
        parts.append(el.text.replace("&", "&amp;").replace("<", "&lt;"))
    for c in list(el):
        name = local(c.tag)
        inner = fb2_inline(c)
        if name in ("strong", "emphasis", "em"):
            parts.append("<em>" + inner + "</em>")
        elif name == "a":
            parts.append(inner)
        else:
            parts.append(inner)
        if c.tail:
            parts.append(c.tail.replace("&", "&amp;").replace("<", "&lt;"))
    return "".join(parts)


def fb2_section_html(el):
    bits = []
    for c in list(el):
        name = local(c.tag)
        if name == "title":
            bits.append("<h2>" + fb2_inline(c) + "</h2>")
        elif name == "subtitle":
            bits.append("<h3>" + fb2_inline(c) + "</h3>")
        elif name == "p":
            bits.append("<p>" + fb2_inline(c) + "</p>")
        elif name == "empty-line":
            bits.append("<p></p>")
        elif name == "section":
            bits.append(fb2_section_html(c))
        elif name == "epigraph":
            bits.append("<blockquote>" + fb2_section_html(c) + "</blockquote>")
        elif name == "cite":
            bits.append("<blockquote>" + fb2_inline(c) + "</blockquote>")
    return "\n".join(bits) or "<p>(empty)</p>"


def parse_file_book(path, fmt):
    title = pretty_title(path)
    author = ""
    if fmt == "html":
        try:
            head = open(path, "rb").read(12000).decode("utf-8", "replace")
        except Exception:
            head = ""
        m = re.search(r"<title>([^<]+)</title>", head, re.I)
        if m:
            title = re.sub(r"\s+", " ", m.group(1)).strip() or title
        m = re.search(
            r'<meta\s+name=["\']author["\']\s+content=["\']([^"\']+)',
            head,
            re.I,
        )
        if m:
            author = m.group(1).strip()
    store = Store("file", path)
    return {
        "id": make_id(path),
        "title": title,
        "author": author,
        "cover": False,
        "cover_path": "",
        "chapters": 1,
        "spine": [{"i": 0, "href": os.path.basename(path), "title": title}],
        "src": path,
        "kind": "file",
        "fmt": fmt,
        "_store": store,
    }


def parse_fb2_book(path):
    try:
        raw = open(path, "rb").read()
        root = parse_xml(raw)
    except Exception:
        return None
    title = pretty_title(path)
    author = ""
    for el in find_all(root, "book-title"):
        t = text_of(el)
        if t:
            title = t
            break
    first = last = ""
    for el in find_all(root, "first-name"):
        first = text_of(el)
        if first:
            break
    for el in find_all(root, "last-name"):
        last = text_of(el)
        if last:
            break
    author = (first + " " + last).strip()
    sections = []
    for body in find_all(root, "body"):
        if (body.get("name") or "").lower() == "notes":
            continue
        secs = [c for c in list(body) if local(c.tag) == "section"]
        if secs:
            sections.extend(secs)
        else:
            sections.append(body)
    if not sections:
        return None
    spine = []
    parts = []
    for i, sec in enumerate(sections):
        label = ""
        tit = find_child(sec, "title")
        if tit:
            label = re.sub(r"\s+", " ", fb2_inline(tit)).strip()
        if not label:
            label = "Part %d" % (i + 1)
        spine.append({"i": i, "href": "s%d" % i, "title": label[:90]})
        parts.append(fb2_section_html(sec))
    store = Store("fb2", path)
    store._parts = parts
    return {
        "id": make_id(path),
        "title": title,
        "author": author,
        "cover": False,
        "cover_path": "",
        "chapters": len(spine),
        "spine": spine,
        "src": path,
        "kind": "fb2",
        "fmt": "fb2",
        "_store": store,
    }


def chapter_html(b, idx, reader=False):
    href = b["spine"][idx]["href"]
    raw = b["_store"].read(href)
    if raw is None:
        return None
    kind = b.get("kind") or "zip"
    fmt = b.get("fmt") or ""
    if kind == "file":
        if isinstance(raw, bytes):
            text = raw.decode("utf-8", "replace")
        else:
            text = raw
        if fmt == "md":
            return md_to_html(text)
        if fmt == "html":
            return html_to_body(text)
        return txt_to_html(text)
    if kind == "fb2":
        if isinstance(raw, bytes):
            return raw.decode("utf-8", "replace")
        return raw
    return rewrite_chapter(raw, b["id"], href, spine=b["spine"], reader=reader)


def make_id(path):
    base = os.path.basename(path.rstrip("/"))
    slug = re.sub(r"[^a-zA-Z0-9._-]+", "-", base).strip("-").lower()
    if not slug:
        slug = "book"
    h = hashlib.md5(os.path.abspath(path).encode("utf-8")).hexdigest()[:6]
    return slug[:40] + "-" + h


def skip_name(name):
    low = name.lower()
    for bad in ("key", "secret", "password", "credential", "token"):
        if bad in low:
            return True
    return False


def scan_dir(folder, books, seen, extra=False):
    if not os.path.isdir(folder):
        return
    try:
        names = os.listdir(folder)
    except OSError:
        return
    for name in names:
        if name.startswith(".") or skip_name(name):
            continue
        path = os.path.join(folder, name)
        ap = os.path.abspath(path)
        if ap in seen:
            continue
        if os.path.isdir(path) and os.path.isfile(os.path.join(path, "META-INF", "container.xml")):
            seen.add(ap)
            store = Store("dir", path)
            bid = make_id(path)
            info = parse_book(store, bid, path)
            if info:
                info["_store"] = store
                books.append(info)
        elif name.lower().endswith(".epub") and os.path.isfile(path) and is_epub_zip(path):
            unpacked = os.path.splitext(path)[0]
            if os.path.isdir(os.path.join(unpacked, "META-INF")):
                continue
            seen.add(ap)
            store = Store("zip", path)
            bid = make_id(path)
            info = parse_book(store, bid, path)
            if info:
                info["_store"] = store
                books.append(info)
        elif os.path.isfile(path):
            fmt = file_fmt(name)
            if not fmt or fmt == "epub":
                continue
            if extra and fmt in ("txt", "html", "md"):
                continue
            seen.add(ap)
            if fmt == "fb2":
                info = parse_fb2_book(path)
            else:
                info = parse_file_book(path, fmt)
            if info:
                books.append(info)


def bust_cache():
    CACHE["books"] = None
    CACHE["t"] = ""


def safe_dest(folder, name):
    base = os.path.basename(name).replace("\\", "/").split("/")[-1]
    if not base or base.startswith("."):
        return None
    return os.path.join(folder, base)


def import_shared():
    copied = []
    try:
        os.makedirs(BOOKS_DIR, exist_ok=True)
    except Exception:
        pass
    for folder in EXTRA_DIRS:
        if not os.path.isdir(folder):
            continue
        if os.path.abspath(folder) == os.path.abspath(BOOKS_DIR):
            continue
        try:
            names = os.listdir(folder)
        except OSError:
            continue
        for name in names:
            low = name.lower()
            src = os.path.join(folder, name)
            if not os.path.isfile(src):
                continue
            if low.endswith(".zip") and "library" in low:
                n = import_zip(src)
                copied.append("%s (%d files)" % (name, n))
                continue
            if not file_fmt(name):
                continue
            dest = safe_dest(BOOKS_DIR, name)
            if not dest or os.path.exists(dest):
                continue
            try:
                shutil.copy2(src, dest)
                copied.append(name)
            except Exception:
                pass
    bust_cache()
    return copied


def import_zip(src):
    n = 0
    try:
        z = zipfile.ZipFile(src, "r")
    except Exception:
        return 0
    try:
        os.makedirs(BOOKS_DIR, exist_ok=True)
    except Exception:
        pass
    for info in z.infolist():
        name = os.path.basename(info.filename)
        if info.is_dir() or name.startswith("."):
            continue
        if name in ("books-progress.json", "books-bookmarks.json", "books-categories.json"):
            if "progress" in name:
                dest = PROGRESS_PATH
            elif "bookmark" in name:
                dest = BOOKMARKS_PATH
            else:
                dest = CATEGORIES_PATH
            try:
                open(dest, "wb").write(z.read(info.filename))
            except Exception:
                pass
            continue
        if not file_fmt(name):
            continue
        dest = safe_dest(BOOKS_DIR, name)
        if not dest or os.path.exists(dest):
            continue
        try:
            open(dest, "wb").write(z.read(info.filename))
            n += 1
        except Exception:
            pass
    return n


def save_upload(name, data):
    try:
        os.makedirs(BOOKS_DIR, exist_ok=True)
    except Exception:
        pass
    base = os.path.basename(name or "upload.bin")
    if base.lower().endswith(".zip"):
        tmp = os.path.join(BOOKS_DIR, ".import.zip")
        open(tmp, "wb").write(data)
        n = import_zip(tmp)
        try:
            os.remove(tmp)
        except Exception:
            pass
        bust_cache()
        return {"ok": True, "imported": n, "name": base}
    if not file_fmt(base):
        return {"ok": False, "error": "unsupported file"}
    dest = safe_dest(BOOKS_DIR, base)
    if not dest:
        return {"ok": False, "error": "bad name"}
    open(dest, "wb").write(data)
    bust_cache()
    return {"ok": True, "imported": 1, "name": base}


def make_archive():
    try:
        os.makedirs(DOCS_DIR, exist_ok=True)
    except Exception:
        pass
    name = "berrycore-library-%s.zip" % time.strftime("%Y%m%d-%H%M")
    dest = os.path.join(DOCS_DIR, name)
    try:
        z = zipfile.ZipFile(dest, "w", zipfile.ZIP_DEFLATED)
    except Exception:
        z = zipfile.ZipFile(dest, "w", zipfile.ZIP_STORED)
    n = 0
    if os.path.isdir(BOOKS_DIR):
        for root, _dirs, files in os.walk(BOOKS_DIR):
            for fn in files:
                if fn.startswith("."):
                    continue
                full = os.path.join(root, fn)
                arc = os.path.join("books", os.path.relpath(full, BOOKS_DIR))
                try:
                    z.write(full, arc)
                    n += 1
                except Exception:
                    pass
    if os.path.isfile(PROGRESS_PATH):
        z.write(PROGRESS_PATH, "books-progress.json")
    if os.path.isfile(BOOKMARKS_PATH):
        z.write(BOOKMARKS_PATH, "books-bookmarks.json")
    if os.path.isfile(CATEGORIES_PATH):
        z.write(CATEGORIES_PATH, "books-categories.json")
    z.close()
    return {"ok": True, "path": dest, "name": name, "files": n}


def library():
    books = []
    seen = set()
    scan_dir(BOOKS_DIR, books, seen)
    if os.path.isdir(CLASSICS_DIR):
        scan_dir(CLASSICS_DIR, books, seen)
    for extra in EXTRA_DIRS:
        if os.path.abspath(extra) != os.path.abspath(BOOKS_DIR):
            scan_dir(extra, books, seen, extra=True)
    books.sort(key=lambda b: (b.get("title") or "").lower())
    return books


def dir_stamp():
    parts = []
    for folder in [BOOKS_DIR, CLASSICS_DIR] + EXTRA_DIRS:
        if not os.path.isdir(folder):
            continue
        try:
            for name in os.listdir(folder):
                path = os.path.join(folder, name)
                try:
                    parts.append(name + ":" + str(int(os.path.getmtime(path))))
                except OSError:
                    pass
        except OSError:
            pass
    return "|".join(parts)


def get_lib():
    stamp = dir_stamp()
    if CACHE["books"] is None or CACHE["t"] != stamp:
        CACHE["books"] = library()
        CACHE["t"] = stamp
    return CACHE["books"]


def find_book(bid):
    for b in get_lib():
        if b["id"] == bid:
            return b
    return None


def under_dir(path, root):
    ap = os.path.abspath(path)
    ar = os.path.abspath(root)
    return ap == ar or ap.startswith(ar + os.sep)


def delete_book(bid):
    b = find_book(bid)
    if not b:
        return {"ok": False, "error": "not found"}
    src = b.get("src") or ""
    if not src or not under_dir(src, BOOKS_DIR):
        return {"ok": False, "error": "only files in the library folder can be deleted"}
    try:
        if os.path.isdir(src):
            shutil.rmtree(src)
        elif os.path.isfile(src):
            os.remove(src)
        else:
            return {"ok": False, "error": "missing file"}
    except Exception:
        return {"ok": False, "error": "could not delete"}
    prog = load_progress()
    if bid in prog:
        del prog[bid]
        save_progress(prog)
    save_bookmarks([m for m in load_bookmarks() if m.get("id") != bid])
    cats = load_categories()
    if bid in (cats.get("assign") or {}):
        del cats["assign"][bid]
        save_categories(cats)
    bust_cache()
    return {"ok": True, "id": bid, "title": b.get("title") or ""}


def load_progress():
    try:
        return json.loads(open(PROGRESS_PATH).read())
    except Exception:
        return {}


def _write_json(path, obj):
    folder = os.path.dirname(path)
    try:
        os.makedirs(folder, exist_ok=True)
    except Exception:
        pass
    tmp = path + ".tmp"
    open(tmp, "w").write(json.dumps(obj))
    try:
        os.replace(tmp, path)
    except Exception:
        try:
            os.remove(path)
        except Exception:
            pass
        os.rename(tmp, path)


def save_progress(obj):
    _write_json(PROGRESS_PATH, obj)


def load_bookmarks():
    try:
        data = json.loads(open(BOOKMARKS_PATH).read())
        if isinstance(data, list):
            return data
    except Exception:
        pass
    return []


def save_bookmarks(items):
    _write_json(BOOKMARKS_PATH, items)


def cat_slug(name):
    slug = re.sub(r"[^a-zA-Z0-9]+", "-", (name or "").strip().lower()).strip("-")
    return (slug or "cat")[:32]


def guess_category(b):
    blob = " ".join([
        b.get("title") or "",
        b.get("author") or "",
        os.path.basename(b.get("src") or ""),
    ]).lower()
    fiction = (
        "alice", "wonderland", "dracula", "dorian", "frankenstein",
        "pride", "prejudice", "sherlock", "holmes", "christmas carol",
        "moby", "gatsby", "jekyll",
    )
    bell = (
        "unix", "bell labs", "ritchie", "thompson", "kernighan",
        "pike", "lions", "bstj", "seventh edition", "7th edition",
        "system iii", "v7", "programmer's manual", "time-sharing",
        "time sharing",
    )
    osish = (
        "xv6", "ostep", "operating system", "kernel", "minix",
        "qnx", "freebsd", "scheduler", "virtual memory", "inode",
    )
    for w in fiction:
        if w in blob:
            return "fiction"
    for w in osish:
        if w in blob:
            return "os"
    for w in bell:
        if w in blob:
            return "bell-labs"
    return "unfiled"


def empty_categories():
    return {
        "categories": [dict(c) for c in DEFAULT_CATS],
        "assign": {},
    }


def load_categories():
    data = empty_categories()
    try:
        raw = json.loads(open(CATEGORIES_PATH).read())
    except Exception:
        raw = None
    if isinstance(raw, dict):
        cats = raw.get("categories")
        if isinstance(cats, list) and cats:
            clean = []
            seen = set()
            for c in cats:
                if not isinstance(c, dict):
                    continue
                cid = cat_slug(c.get("id") or c.get("name") or "")
                if not cid or cid in seen:
                    continue
                seen.add(cid)
                clean.append({
                    "id": cid,
                    "name": (c.get("name") or cid)[:48],
                    "open": bool(c.get("open", True)),
                })
            if clean:
                data["categories"] = clean
        assign = raw.get("assign")
        if isinstance(assign, dict):
            data["assign"] = dict((str(k), str(v)) for k, v in assign.items() if k and v)
    have = [c["id"] for c in data["categories"]]
    for c in DEFAULT_CATS:
        if c["id"] not in have:
            data["categories"].append(dict(c))
            have.append(c["id"])
    if "unfiled" not in have:
        data["categories"].append({"id": "unfiled", "name": "Unfiled", "open": False})
    return data


def save_categories(data):
    _write_json(CATEGORIES_PATH, {
        "categories": data.get("categories") or [],
        "assign": data.get("assign") or {},
    })


def known_cat_ids(data):
    return [c["id"] for c in data.get("categories") or []]


def book_category(b, data):
    cid = (data.get("assign") or {}).get(b["id"])
    if cid and cid in known_cat_ids(data):
        return cid
    return guess_category(b)


def apply_categories(obj):
    data = load_categories()
    op = (obj.get("op") or "").strip()
    if op == "assign":
        bid = obj.get("id") or ""
        cid = cat_slug(obj.get("cat") or "")
        if not bid or cid not in known_cat_ids(data):
            return None
        data["assign"][bid] = cid
    elif op == "add":
        name = (obj.get("name") or "").strip()[:48]
        if not name:
            return None
        cid = cat_slug(obj.get("id") or name)
        ids = known_cat_ids(data)
        base = cid
        n = 2
        while cid in ids:
            cid = "%s-%d" % (base[:28], n)
            n += 1
        data["categories"].append({"id": cid, "name": name, "open": True})
    elif op == "rename":
        cid = cat_slug(obj.get("cat") or "")
        name = (obj.get("name") or "").strip()[:48]
        if not cid or not name:
            return None
        for c in data["categories"]:
            if c["id"] == cid:
                c["name"] = name
                break
        else:
            return None
    elif op == "delete":
        cid = cat_slug(obj.get("cat") or "")
        if cid in ("", "unfiled") or cid not in known_cat_ids(data):
            return None
        data["categories"] = [c for c in data["categories"] if c["id"] != cid]
        for bid, cur in list(data["assign"].items()):
            if cur == cid:
                data["assign"][bid] = "unfiled"
    elif op == "toggle":
        cid = cat_slug(obj.get("cat") or "")
        for c in data["categories"]:
            if c["id"] == cid:
                c["open"] = not c.get("open", True)
                break
        else:
            return None
    elif op == "open":
        cid = cat_slug(obj.get("cat") or "")
        want = bool(obj.get("open"))
        for c in data["categories"]:
            if c["id"] == cid:
                c["open"] = want
                break
        else:
            return None
    elif op == "order":
        ids = obj.get("ids") or []
        if not isinstance(ids, list):
            return None
        by_id = dict((c["id"], c) for c in data["categories"])
        ordered = []
        seen = set()
        for cid in ids:
            cid = cat_slug(cid)
            if cid in by_id and cid not in seen:
                ordered.append(by_id[cid])
                seen.add(cid)
        for c in data["categories"]:
            if c["id"] not in seen:
                ordered.append(c)
        data["categories"] = ordered
    else:
        return None
    save_categories(data)
    return data


def esc_html(s):
    return (
        str(s or "")
        .replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
        .replace('"', "&quot;")
    )


def reader_page(b, idx, html, title):
    bid = quote(b["id"])
    n = len(b["spine"])
    prev_l = "/reader?id=%s&amp;i=%d" % (bid, idx - 1) if idx > 0 else ""
    next_l = "/reader?id=%s&amp;i=%d" % (bid, idx + 1) if idx < n - 1 else ""
    lib = "/?b=%s&amp;c=%d" % (bid, idx)
    nav = []
    if prev_l:
        nav.append('<a href="%s">Previous chapter</a>' % prev_l)
    nav.append('<a href="%s">Library reader</a>' % lib)
    if next_l:
        nav.append('<a href="%s">Next chapter</a>' % next_l)
    return """<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>%s — %s</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="author" content="%s">
<meta name="description" content="%s">
<style>
  body { margin: 0; background: #f4ead4; color: #2c2118;
    font-family: Georgia, "Times New Roman", serif; }
  article { max-width: 680px; margin: 0 auto; padding: 28px 22px 48px;
    font-size: 20px; line-height: 1.7; }
  h1 { font-weight: normal; font-size: 1.6em; color: #5c3d1e; }
  .by { color: #7a6548; font-style: italic; margin: 0 0 1.4em; font-size: 0.92em; }
  p { margin: 0 0 0.95em; }
  img { max-width: 100%%; }
  .foot { margin-top: 2em; padding-top: 1em; border-top: 1px solid #c4a574;
    font-size: 15px; }
  .foot a { color: #5c3d1e; }
</style>
</head>
<body>
<article>
  <h1>%s</h1>
  <p class="by">%s · %s · %d of %d</p>
  %s
  <p class="foot">%s</p>
</article>
</body>
</html>
""" % (
        esc_html(title),
        esc_html(b.get("title")),
        esc_html(b.get("author")),
        esc_html(b.get("title") + " — " + title),
        esc_html(title),
        esc_html(b.get("title")),
        esc_html(b.get("author") or "Unknown"),
        idx + 1,
        n,
        html,
        " · ".join(nav),
    )


SCRIPT_RE = re.compile(r"<script\b[^>]*>[\s\S]*?</script>", re.I)
STYLE_RE = re.compile(r"<style\b[^>]*>[\s\S]*?</style>", re.I)
ONATTR_RE = re.compile(r"\son[a-z]+\s*=\s*(\"[^\"]*\"|'[^']*'|[^\s>]+)", re.I)
BODY_RE = re.compile(r"<body\b[^>]*>([\s\S]*)</body>", re.I)
SRC_RE = re.compile(
    r"""(?i)(\b(?:src|href|xlink:href)\s*=\s*)(['"])([^'"]+)\2"""
)


def norm_href(p):
    p = (p or "").replace("\\", "/").split("#", 1)[0]
    p = posixpath.normpath(p).lstrip("./")
    if p == ".":
        return ""
    return p


def spine_index(spine, rel):
    rel = norm_href(rel)
    if not rel:
        return -1
    for i, ch in enumerate(spine or []):
        if norm_href(ch.get("href")) == rel:
            return i
    for i, ch in enumerate(spine or []):
        h = norm_href(ch.get("href"))
        if h.endswith("/" + rel) or rel.endswith("/" + h):
            return i
    return -1


def rewrite_chapter(html, bid, href, spine=None, reader=False):
    if isinstance(html, bytes):
        html = html.decode("utf-8", "replace")
    html = SCRIPT_RE.sub("", html)
    html = STYLE_RE.sub("", html)
    html = ONATTR_RE.sub("", html)
    m = BODY_RE.search(html)
    if m:
        html = m.group(1)
    base = posixpath.dirname(href)
    here = norm_href(href)

    def repl(match):
        attr, q, url = match.group(1), match.group(2), match.group(3)
        low = url.lower()
        if low.startswith("http://") or low.startswith("https://") or low.startswith("data:") or low.startswith("mailto:"):
            if "href" in attr.lower() and not low.startswith("data:"):
                return attr + q + "#" + q
            return match.group(0)
        if url.startswith("#"):
            return match.group(0)
        path, frag = url.split("#", 1) if "#" in url else (url, "")
        rel = posixpath.normpath(posixpath.join(base, path))
        if rel.startswith("../"):
            rel = rel.replace("../", "")
        rel = norm_href(rel)
        api = "/api/file?id=%s&p=%s" % (quote(bid), quote(rel))
        if "href" in attr.lower() and not re.search(r"\.(png|jpe?g|gif|svg|webp)$", rel, re.I):
            if rel == here or not rel:
                return attr + q + ("#" + frag if frag else "#") + q
            i = spine_index(spine, rel)
            if i >= 0:
                if reader:
                    dest = "/reader?id=%s&i=%d" % (quote(bid), i)
                    if frag:
                        dest += "#" + frag
                    return attr + q + dest + q
                extra = (' data-bc-frag="%s"' % frag.replace('"', "")) if frag else ""
                return '%s%s#bc-ch-%d%s%s' % (attr, q, i, q, extra)
            return attr + q + "#" + q
        return attr + q + api + q

    return SRC_RE.sub(repl, html)


def guess_type(path):
    low = path.lower()
    if low.endswith(".jpg") or low.endswith(".jpeg"):
        return "image/jpeg"
    if low.endswith(".png"):
        return "image/png"
    if low.endswith(".gif"):
        return "image/gif"
    if low.endswith(".svg"):
        return "image/svg+xml"
    if low.endswith(".css"):
        return "text/css"
    if low.endswith(".html") or low.endswith(".htm") or low.endswith(".xhtml"):
        return "text/html; charset=utf-8"
    return "application/octet-stream"


class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    daemon_threads = True
    allow_reuse_address = True


class Handler(BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        sys.stderr.write("%s - %s\n" % (self.address_string(), fmt % args))

    def _json(self, code, obj):
        body = json.dumps(obj).encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def _bytes(self, data, ctype):
        if data is None:
            self.send_error(404)
            return
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(data)))
        self.send_header("Cache-Control", "max-age=120")
        self.end_headers()
        self.wfile.write(data)

    def _file(self, path, ctype):
        try:
            data = open(path, "rb").read()
        except IOError:
            self.send_error(404)
            return
        self._bytes(data, ctype)

    def _qs(self):
        if "?" not in self.path:
            return {}
        return parse_qs(self.path.split("?", 1)[1])

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def do_GET(self):
        path = self.path.split("?", 1)[0]
        if path == "/" or path == "/index.html":
            self._file(os.path.join(ROOT, "index.html"), "text/html; charset=utf-8")
            return
        if path == "/api/library":
            prog = load_progress()
            cats = load_categories()
            items = []
            for b in get_lib():
                p = prog.get(b["id"]) or {}
                items.append({
                    "id": b["id"],
                    "title": b["title"],
                    "author": b["author"],
                    "cover": b["cover"],
                    "chapters": b["chapters"],
                    "fmt": b.get("fmt") or ("epub" if b.get("kind") in ("zip", "dir") else ""),
                    "category": book_category(b, cats),
                    "chapter": int(p.get("chapter") or 0),
                    "scroll": int(p.get("scroll") or 0),
                })
            self._json(200, {
                "books": items,
                "root": BOOKS_DIR,
                "count": len(items),
                "categories": cats["categories"],
            })
            return
        if path == "/api/categories":
            self._json(200, load_categories())
            return
        if path == "/api/book":
            bid = (self._qs().get("id") or [""])[0]
            b = find_book(bid)
            if not b:
                self._json(404, {"error": "book not found"})
                return
            if not b.get("_titled"):
                polish_titles(b["_store"], b["spine"])
                b["_titled"] = True
            prog = load_progress().get(bid) or {}
            self._json(200, {
                "id": b["id"],
                "title": b["title"],
                "author": b["author"],
                "cover": b["cover"],
                "chapters": b["spine"],
                "chapter": int(prog.get("chapter") or 0),
                "scroll": int(prog.get("scroll") or 0),
            })
            return
        if path == "/api/chapter":
            q = self._qs()
            bid = (q.get("id") or [""])[0]
            try:
                idx = int((q.get("i") or ["0"])[0])
            except ValueError:
                idx = 0
            b = find_book(bid)
            if not b or idx < 0 or idx >= len(b["spine"]):
                self._json(404, {"error": "chapter not found"})
                return
            html = chapter_html(b, idx)
            if html is None:
                self._json(404, {"error": "missing chapter"})
                return
            self._json(200, {
                "i": idx,
                "title": b["spine"][idx]["title"],
                "html": html,
                "n": len(b["spine"]),
            })
            return
        if path == "/api/cover":
            bid = (self._qs().get("id") or [""])[0]
            b = find_book(bid)
            if not b or not b.get("cover_path"):
                self.send_error(404)
                return
            data = b["_store"].read(b["cover_path"])
            self._bytes(data, guess_type(b["cover_path"]))
            return
        if path == "/api/file":
            q = self._qs()
            bid = (q.get("id") or [""])[0]
            rel = unquote((q.get("p") or [""])[0])
            if ".." in rel.split("/"):
                self.send_error(400)
                return
            b = find_book(bid)
            if not b:
                self.send_error(404)
                return
            data = b["_store"].read(rel)
            self._bytes(data, guess_type(rel))
            return
        if path == "/api/progress":
            self._json(200, load_progress())
            return
        if path == "/api/bookmarks":
            self._json(200, {"bookmarks": load_bookmarks()})
            return
        if path == "/reader":
            q = self._qs()
            bid = (q.get("id") or [""])[0]
            try:
                idx = int((q.get("i") or ["0"])[0])
            except ValueError:
                idx = 0
            b = find_book(bid)
            if not b or idx < 0 or idx >= len(b["spine"]):
                self.send_error(404)
                return
            html = chapter_html(b, idx, reader=True)
            if html is None:
                self.send_error(404)
                return
            title = b["spine"][idx]["title"]
            page = reader_page(b, idx, html, title).encode("utf-8")
            self._bytes(page, "text/html; charset=utf-8")
            return
        self.send_error(404)

    def do_POST(self):
        path = self.path.split("?", 1)[0]
        n = int(self.headers.get("Content-Length", "0") or 0)
        raw = self.rfile.read(n) if n > 0 else b""
        if path == "/api/archive":
            self._json(200, make_archive())
            return
        if path == "/api/import":
            copied = import_shared()
            self._json(200, {"ok": True, "copied": copied, "count": len(copied)})
            return
        if path == "/api/upload":
            name = unquote((self._qs().get("name") or ["upload.bin"])[0])
            self._json(200, save_upload(name, raw))
            return
        try:
            obj = json.loads(raw.decode("utf-8") if raw else "{}")
        except Exception:
            self._json(400, {"error": "bad json"})
            return
        if path == "/api/delete":
            bid = obj.get("id") or ""
            if not bid:
                self._json(400, {"error": "missing id"})
                return
            self._json(200, delete_book(bid))
            return
        if path == "/api/progress":
            bid = obj.get("id") or ""
            if not bid:
                self._json(400, {"error": "missing id"})
                return
            prog = load_progress()
            prog[bid] = {
                "chapter": int(obj.get("chapter") or 0),
                "scroll": int(obj.get("scroll") or 0),
            }
            save_progress(prog)
            self._json(200, {"ok": True})
            return
        if path == "/api/categories":
            data = apply_categories(obj)
            if not data:
                self._json(400, {"error": "bad category request"})
                return
            self._json(200, data)
            return
        if path == "/api/bookmarks":
            marks = load_bookmarks()
            op = obj.get("op") or "add"
            if op == "del":
                tid = obj.get("t")
                marks = [m for m in marks if m.get("t") != tid]
                save_bookmarks(marks)
                self._json(200, {"ok": True, "bookmarks": marks})
                return
            bid = obj.get("id") or ""
            if not bid:
                self._json(400, {"error": "missing id"})
                return
            mark = {
                "t": int(time.time() * 1000),
                "id": bid,
                "chapter": int(obj.get("chapter") or 0),
                "scroll": int(obj.get("scroll") or 0),
                "book": obj.get("book") or "",
                "label": obj.get("label") or "",
            }
            marks.insert(0, mark)
            marks = marks[:80]
            save_bookmarks(marks)
            self._json(200, {"ok": True, "bookmark": mark, "bookmarks": marks})
            return
        self.send_error(404)


if __name__ == "__main__":
    httpd = ThreadedHTTPServer(("0.0.0.0", PORT), Handler)
    sys.stderr.write("Books http://0.0.0.0:%d/  dir=%s\n" % (PORT, BOOKS_DIR))
    httpd.serve_forever()
