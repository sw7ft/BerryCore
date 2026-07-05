#!/bin/sh
# Generate berrycore.html from VERSION, ports/FEATURED, ports/PACKAGES
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"
VERSION="$(cat "$REPO_ROOT/berrycore/VERSION" 2>/dev/null || echo "unknown")"
OUT="$REPO_ROOT/berrycore.html"
TAG="v${VERSION}"
RELEASE_BASE="https://github.com/sw7ft/BerryCore/releases/download/${TAG}"
RAW_BASE="https://raw.githubusercontent.com/sw7ft/BerryCore/main"

parse_tsv_to_json() {
    _file="$1"
    _kind="$2"
    _first=1
    printf '['
    while IFS='|' read -r f1 f2 f3 f4 f5 f6 f7; do
        if [ "$_kind" = "featured" ]; then
            _name="$f1"; _cat="$f2"; _ver="$f3"; _size="$f4"; _desc="$f5"
        else
            _name="$f1"; _cat="$f2"; _ver="$f3"; _size="$f4"; _desc="$f5"
        fi
        _esc() { printf '%s' "$1" | sed 's/\\/\\\\/g; s/"/\\"/g'; }
        _n=$(_esc "$_name"); _c=$(_esc "$_cat"); _v=$(_esc "$_ver")
        _s=$(_esc "$_size"); _d=$(_esc "$_desc")
        if [ "$_first" -eq 1 ]; then _first=0; else printf ','; fi
        if [ "$_kind" = "featured" ]; then
            printf '{"name":"%s","category":"%s","version":"%s","size":"%s","description":"%s"}' "$_n" "$_c" "$_v" "$_s" "$_d"
        else
            _z=$(_esc "$f6"); _r=$(_esc "$f7")
            printf '{"name":"%s","category":"%s","version":"%s","size":"%s","description":"%s","zip":"%s","replaces":"%s"}' "$_n" "$_c" "$_v" "$_s" "$_d" "$_z" "$_r"
        fi
    done <<EOF
$(grep -v '^#' "$_file" | grep -v '^$')
EOF
    printf ']'
}

# Build JSON in temp files (while loop runs in subshell otherwise)
FEATURED_JSON="$(parse_tsv_to_json "$REPO_ROOT/ports/FEATURED" featured)"
PACKAGES_JSON="$(parse_tsv_to_json "$REPO_ROOT/ports/PACKAGES" packages)"
FEATURED_COUNT="$(grep -v '^#' "$REPO_ROOT/ports/FEATURED" | grep -vc '^$' || echo 0)"
PACKAGES_COUNT="$(grep -v '^#' "$REPO_ROOT/ports/PACKAGES" | grep -vc '^$' || echo 0)"

cat > "$OUT" << HTMLEOF
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>BerryCore ${VERSION} — Catalog &amp; Install Guide</title>
<style>
*{box-sizing:border-box;margin:0;padding:0}
html{scroll-behavior:smooth}
body{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,Helvetica,Arial,sans-serif;background:#0d1117;color:#c9d1d9;line-height:1.6;font-size:15px}
a{color:#58a6ff;text-decoration:none}
a:hover{text-decoration:underline}
code,kbd{font-family:ui-monospace,SFMono-Regular,"SF Mono",Menlo,Consolas,monospace;font-size:.9em}
.wrap{max-width:1100px;margin:0 auto;padding:0 20px 60px}
header{background:linear-gradient(135deg,#161b22 0%,#1a1225 50%,#161b22 100%);border-bottom:1px solid #30363d;padding:28px 0 22px;margin-bottom:28px}
header .wrap{display:flex;flex-wrap:wrap;align-items:center;gap:16px}
.logo{font-size:1.75rem;font-weight:700;color:#f0f6fc;letter-spacing:-.02em}
.logo span{color:#bc8cff}
.badge{display:inline-block;background:#21262d;border:1px solid #30363d;color:#8b949e;padding:4px 10px;border-radius:999px;font-size:.8rem}
nav.sticky{position:sticky;top:0;z-index:50;background:rgba(13,17,23,.92);backdrop-filter:blur(8px);border-bottom:1px solid #30363d;margin:0 -20px 24px;padding:0 20px}
nav.sticky ul{display:flex;flex-wrap:wrap;gap:4px 0;list-style:none;padding:10px 0}
nav.sticky a{display:block;padding:8px 14px;border-radius:6px;color:#8b949e;font-size:.875rem;font-weight:500}
nav.sticky a:hover{background:#21262d;color:#f0f6fc;text-decoration:none}
section{margin-bottom:40px}
h2{font-size:1.35rem;color:#f0f6fc;margin-bottom:14px;padding-bottom:8px;border-bottom:1px solid #21262d}
h3{font-size:1.05rem;color:#e6edf3;margin:18px 0 10px}
p,li{color:#8b949e;margin-bottom:.6em}
.lead{font-size:1.05rem;color:#8b949e;max-width:720px}
.grid2{display:flex;flex-wrap:wrap;gap:16px}
.card{flex:1 1 280px;background:#161b22;border:1px solid #30363d;border-radius:10px;padding:18px 20px}
.card h3{margin-top:0;color:#bc8cff;font-size:.95rem;text-transform:uppercase;letter-spacing:.04em}
.copywrap{position:relative;margin:10px 0}
.copyblock{background:#0d1117;border:1px solid #30363d;border-radius:8px;padding:14px 48px 14px 16px;font-size:.85rem;color:#e6edf3;white-space:pre-wrap;word-break:break-all;overflow-x:auto}
.copywrap .copybtn{position:absolute;top:10px;right:10px}
.copybtn{background:#21262d;border:1px solid #30363d;color:#8b949e;padding:5px 10px;border-radius:6px;cursor:pointer;font-size:.75rem}
.copybtn:hover{background:#30363d;color:#f0f6fc}
.copybtn.ok{border-color:#238636;color:#3fb950}
.searchbar{width:100%;max-width:420px;padding:10px 14px;background:#0d1117;border:1px solid #30363d;border-radius:8px;color:#f0f6fc;font-size:.95rem;margin-bottom:14px}
.searchbar:focus{outline:none;border-color:#bc8cff}
.filters{display:flex;flex-wrap:wrap;gap:8px;margin-bottom:16px}
.filterbtn{background:#21262d;border:1px solid #30363d;color:#8b949e;padding:6px 12px;border-radius:999px;cursor:pointer;font-size:.8rem}
.filterbtn.on{background:#388bfd22;border-color:#388bfd;color:#58a6ff}
table{width:100%;border-collapse:collapse;font-size:.875rem}
th,td{text-align:left;padding:10px 12px;border-bottom:1px solid #21262d;vertical-align:top}
th{color:#8b949e;font-weight:600;font-size:.75rem;text-transform:uppercase;letter-spacing:.05em}
tr:hover td{background:#161b22}
.tag{display:inline-block;padding:2px 8px;border-radius:999px;font-size:.7rem;font-weight:600;text-transform:uppercase;letter-spacing:.03em}
.cat-web{background:#388bfd22;color:#58a6ff}
.cat-net{background:#23863622;color:#3fb950}
.cat-util{background:#bc8cff22;color:#bc8cff}
.cat-dev{background:#d1861622;color:#f0883e}
.cat-lang{background:#f8514922;color:#ff7b72}
.cat-ai{background:#8957e522;color:#bc8cff}
.cat-crypto{background:#db6d2822;color:#ffa657}
.cat-sys{background:#388bfd22;color:#79c0ff}
.cat-archive{background:#388bfd18;color:#a5d6ff}
.cat-security{background:#f8514922;color:#f85149}
.cat-games{background:#23863622;color:#56d364}
.cmd{color:#bc8cff}
.install-step{display:flex;gap:14px;margin-bottom:16px}
.step-num{flex:0 0 32px;height:32px;background:#21262d;border:1px solid #30363d;border-radius:50%;display:flex;align-items:center;justify-content:center;font-weight:700;color:#bc8cff;font-size:.85rem}
.flow{display:flex;flex-wrap:wrap;gap:10px;margin:16px 0}
.flow-item{flex:1 1 140px;background:#161b22;border:1px solid #30363d;border-radius:8px;padding:14px;text-align:center;font-size:.85rem}
.flow-item strong{display:block;color:#f0f6fc;margin-bottom:4px}
.flow-arrow{color:#484f58;align-self:center;font-size:1.2rem}
footer{margin-top:48px;padding-top:24px;border-top:1px solid #21262d;color:#484f58;font-size:.8rem;text-align:center}
@media(max-width:640px){.logo{font-size:1.4rem}th:nth-child(3),td:nth-child(3),th:nth-child(4),td:nth-child(4){display:none}}
</style>
</head>
<body>
<header><div class="wrap">
  <div class="logo">🍇 <span>BerryCore</span></div>
  <span class="badge">v${VERSION}</span>
  <span class="badge">QNX Extended Userland</span>
  <span class="badge">${PACKAGES_COUNT} qpkg ports</span>
</div></header>

<div class="wrap">
<nav class="sticky"><ul>
  <li><a href="#intro">Intro</a></li>
  <li><a href="#links">Download</a></li>
  <li><a href="#install">Install</a></li>
  <li><a href="#how">How it works</a></li>
  <li><a href="#qpkg">qpkg</a></li>
  <li><a href="#featured">Featured</a></li>
  <li><a href="#catalog">Full catalog</a></li>
</ul></nav>

<section id="intro">
  <h2>Introduction</h2>
  <p class="lead">BerryCore is the <strong style="color:#e6edf3">QNX Extended Userland</strong> for BlackBerry 10 and QNX devices — a modern continuation of Berry Much OS. It bundles hundreds of CLI tools, a two-tier package manager (<code>qpkg</code>), and optional ports for browsers, AI, crypto, retro utilities, and more.</p>
  <div class="grid2" style="margin-top:20px">
    <div class="card"><h3>Core bundle</h3><p>~210 MB <code>berrycore.zip</code> — bash, vim 9.1, git, gcc, python-ready env, 86 bundled packages. Installs to <code>/accounts/1000/shared/misc/berrycore/</code>.</p></div>
    <div class="card"><h3>Optional ports</h3><p><code>qpkg install NAME</code> downloads individual port zips from GitHub — browsers, node, dropbear, XPS retro tools, BerryPy apps, and more.</p></div>
    <div class="card"><h3>Featured vs full</h3><p><code>qpkg ports</code> shows ${FEATURED_COUNT} curated highlights. <code>qpkg search</code> / <code>qpkg available</code> search all ${PACKAGES_COUNT} installable packages.</p></div>
  </div>
</section>

<section id="links">
  <h2>Download links</h2>
  <p>Copy these URLs or commands. Replace <code>passport</code> with your SSH host alias or IP.</p>
  <h3>Release assets (${TAG})</h3>
  <div class="copyblock" data-copy="${RELEASE_BASE}/berrycore.zip">berrycore.zip (core install)
${RELEASE_BASE}/berrycore.zip</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <div class="copyblock" data-copy="${RELEASE_BASE}/install.sh">install.sh
${RELEASE_BASE}/install.sh</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <div class="copyblock" data-copy="${RELEASE_BASE}/berrycore.html">berrycore.html (this catalog, offline-friendly)
${RELEASE_BASE}/berrycore.html</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <h3>Transfer to device (from your PC)</h3>
  <div class="copyblock" data-copy="scp ${RELEASE_BASE}/berrycore.zip ${RELEASE_BASE}/install.sh passport:/accounts/1000/shared/misc/">scp ${RELEASE_BASE}/berrycore.zip ${RELEASE_BASE}/install.sh passport:/accounts/1000/shared/misc/</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <h3>GitHub</h3>
  <p><a href="https://github.com/sw7ft/BerryCore/releases/tag/${TAG}">Release page</a> · <a href="https://github.com/sw7ft/BerryCore">Repository</a> · <a href="${RAW_BASE}/ports/PACKAGES">ports/PACKAGES</a> (raw catalog)</p>
</section>

<section id="install">
  <h2>Install guides</h2>
  <h3>Fresh install (new device)</h3>
  <div class="install-step"><div class="step-num">1</div><div><p>Copy <code>berrycore.zip</code> and <code>install.sh</code> to <code>/accounts/1000/shared/misc/</code> (USB, SCP, or shared folder).</p></div></div>
  <div class="install-step"><div class="step-num">2</div><div><p>Open <strong>Term49</strong> (or SSH terminal) and run:</p>
  <div class="copyblock" data-copy="cd /accounts/1000/shared/misc
sh install.sh --fresh -y
. berrycore/env.sh">cd /accounts/1000/shared/misc
sh install.sh --fresh -y
. berrycore/env.sh</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button></div></div>
  <div class="install-step"><div class="step-num">3</div><div><p>Verify:</p>
  <div class="copyblock" data-copy="cat \$NATIVE_TOOLS/VERSION
qpkg ports
vim --version">cat \$NATIVE_TOOLS/VERSION
qpkg ports
vim --version</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button></div></div>
  <h3>Upgrade existing install</h3>
  <div class="copyblock" data-copy="cd /accounts/1000/shared/misc
# copy new berrycore.zip here, then:
sh install.sh --upgrade -y
# or from inside berrycore:
qpkg update">cd /accounts/1000/shared/misc
# copy new berrycore.zip here, then:
sh install.sh --upgrade -y
# or from inside berrycore:
qpkg update</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <h3>Install a port</h3>
  <div class="copyblock" data-copy="qpkg search cab
qpkg show cabextract
qpkg install cabextract
qpkg install openport dropbear python3">qpkg search cab
qpkg show cabextract
qpkg install cabextract
qpkg install openport dropbear python3</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <h3>Auto-start helpers</h3>
  <div class="copyblock" data-copy="settings sshd-on    # SSH server on login
settings tools-on   # BerryCore web tools on port 8765
settings status">settings sshd-on    # SSH server on login
settings tools-on   # BerryCore web tools on port 8765
settings status</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
</section>

<section id="how">
  <h2>How it works</h2>
  <div class="flow">
    <div class="flow-item"><strong>berrycore.zip</strong>Core userland: bin/, lib/, packages/*.zip</div>
    <div class="flow-arrow">→</div>
    <div class="flow-item"><strong>install.sh</strong>Extracts to NATIVE_TOOLS, sets up env.sh</div>
    <div class="flow-arrow">→</div>
    <div class="flow-item"><strong>env.sh</strong>PATH, VIMRUNTIME, welcome MOTD</div>
    <div class="flow-arrow">→</div>
    <div class="flow-item"><strong>qpkg</strong>Install optional ports from GitHub</div>
  </div>
  <h3>Directory layout</h3>
  <div class="copyblock" data-copy="/accounts/1000/shared/misc/
├── berrycore/          ← NATIVE_TOOLS (core install)
│   ├── bin/            ← qpkg, vim, git, curl, …
│   ├── packages/       ← bundled core packages
│   ├── env.sh          ← source this every session
│   └── CATALOG         ← installed binary index (local)
├── bin/                ← misc tools (openport, telnet, …)
└── share/              ← port docs, tools UI">/accounts/1000/shared/misc/
├── berrycore/          ← NATIVE_TOOLS (core install)
│   ├── bin/            ← qpkg, vim, git, curl, …
│   ├── packages/       ← bundled core packages
│   ├── env.sh          ← source this every session
│   └── CATALOG         ← installed binary index (local)
├── bin/                ← misc tools (openport, telnet, …)
└── share/              ← port docs, tools UI</div>
  <button type="button" class="copybtn" onclick="copyFromPrev(this)">Copy</button>
  <h3>Two-tier catalog</h3>
  <table>
    <tr><th>Command</th><th>Source</th><th>Purpose</th></tr>
    <tr><td><code>qpkg ports</code></td><td>ports/FEATURED</td><td>Showcase (~${FEATURED_COUNT} curated ports)</td></tr>
    <tr><td><code>qpkg search</code></td><td>ports/PACKAGES</td><td>Search full catalog (~${PACKAGES_COUNT})</td></tr>
    <tr><td><code>qpkg available</code></td><td>ports/PACKAGES</td><td>List all installable packages</td></tr>
    <tr><td><code>qpkg install</code></td><td>ports/PACKAGES</td><td>Download zip from GitHub, extract, post-install hooks</td></tr>
    <tr><td><code>qpkg catalog</code></td><td>local CATALOG</td><td>Browse binaries already on device</td></tr>
  </table>
</section>

<section id="qpkg">
  <h2>qpkg command reference</h2>
  <table>
    <tr><th>Command</th><th>Description</th></tr>
    <tr><td><code>qpkg ports</code></td><td>Featured port showcase</td></tr>
    <tr><td><code>qpkg search &lt;term&gt;</code></td><td>Search full PACKAGES catalog</td></tr>
    <tr><td><code>qpkg available [cat]</code></td><td>List all packages, optional category filter</td></tr>
    <tr><td><code>qpkg show &lt;name&gt;</code></td><td>Package details before install</td></tr>
    <tr><td><code>qpkg install &lt;name&gt;</code></td><td>Download and install a port</td></tr>
    <tr><td><code>qpkg update</code></td><td>Upgrade BerryCore from latest release</td></tr>
    <tr><td><code>qpkg catalog</code></td><td>Local installed binary catalog</td></tr>
    <tr><td><code>qpkg catalog -s &lt;term&gt;</code></td><td>Search installed binaries</td></tr>
    <tr><td><code>qpkg info &lt;binary&gt;</code></td><td>Info about an installed binary</td></tr>
  </table>
</section>

<section id="featured">
  <h2>Featured ports</h2>
  <p>Shown by <code>qpkg ports</code> — curated highlights for new users.</p>
  <table id="featured-table"><thead><tr><th>Port</th><th>Category</th><th>Version</th><th>Size</th><th>Description</th><th></th></tr></thead><tbody></tbody></table>
</section>

<section id="catalog">
  <h2>Full package catalog</h2>
  <p>All installable ports from <code>ports/PACKAGES</code>. Filter by name or category.</p>
  <input type="search" class="searchbar" id="search" placeholder="Search packages…" autocomplete="off">
  <div class="filters" id="cat-filters"></div>
  <p id="result-count" style="font-size:.85rem;margin-bottom:10px"></p>
  <table id="catalog-table"><thead><tr><th>Port</th><th>Category</th><th>Version</th><th>Size</th><th>Description</th><th></th></tr></thead><tbody></tbody></table>
</section>

<footer>
  BerryCore v${VERSION} · <a href="https://github.com/sw7ft/BerryCore">github.com/sw7ft/BerryCore</a> · Generated catalog page
</footer>
</div>

<script>
var VERSION = "${VERSION}";
var FEATURED = ${FEATURED_JSON};
var PACKAGES = ${PACKAGES_JSON};

function catClass(c) {
  return 'tag cat-' + (c || 'util');
}

function esc(s) {
  if (!s) return '';
  return String(s).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;');
}

function installCmd(name) {
  return 'qpkg install ' + name;
}

function copyText(text, btn) {
  var ta = document.createElement('textarea');
  ta.value = text;
  ta.style.position = 'fixed';
  ta.style.left = '-9999px';
  document.body.appendChild(ta);
  ta.select();
  var ok = false;
  try { ok = document.execCommand('copy'); } catch (e) {}
  document.body.removeChild(ta);
  if (btn) {
    var label = btn.textContent;
    btn.textContent = ok ? 'Copied!' : label;
    btn.className = ok ? 'copybtn ok' : 'copybtn';
    setTimeout(function() { btn.textContent = label; btn.className = 'copybtn'; }, 1500);
  }
}

function copyFromPrev(btn) {
  var block = btn.previousElementSibling;
  if (block && block.className && block.className.indexOf('copyblock') === -1) {
    block = btn.parentNode ? btn.parentNode.querySelector('.copyblock') : null;
  }
  if (block && block.getAttribute('data-copy')) {
    copyText(block.getAttribute('data-copy'), btn);
  }
}

function copyFromData(btn) {
  copyText(btn.getAttribute('data-copy') || '', btn);
}

function attrEsc(s) {
  return String(s).replace(/&/g,'&amp;').replace(/"/g,'&quot;');
}

function rowHtml(p, showInstall) {
  var html = '<tr>';
  html += '<td><strong>' + esc(p.name) + '</strong></td>';
  html += '<td><span class="' + catClass(p.category) + '">' + esc(p.category) + '</span></td>';
  html += '<td>' + esc(p.version) + '</td>';
  html += '<td>' + esc(p.size) + '</td>';
  html += '<td>' + esc(p.description) + '</td>';
  html += '<td>';
  if (showInstall) {
    html += '<button type="button" class="copybtn" style="position:static" data-copy="' + attrEsc(installCmd(p.name)) + '" onclick="copyFromData(this)">install</button>';
  }
  html += '</td></tr>';
  return html;
}

function renderFeatured() {
  var tb = document.getElementById('featured-table').getElementsByTagName('tbody')[0];
  var html = '';
  var i;
  for (i = 0; i < FEATURED.length; i++) {
    html += rowHtml(FEATURED[i], true);
  }
  tb.innerHTML = html;
}

var activeCat = '';

function getCategories() {
  var cats = {}, i, c;
  for (i = 0; i < PACKAGES.length; i++) {
    c = PACKAGES[i].category;
    cats[c] = (cats[c] || 0) + 1;
  }
  return cats;
}

function renderFilters() {
  var cats = getCategories();
  var el = document.getElementById('cat-filters');
  var names = [], k;
  for (k in cats) { if (cats.hasOwnProperty(k)) names.push(k); }
  names.sort();
  var html = '<button type="button" class="filterbtn on" data-cat="">All</button>';
  var i;
  for (i = 0; i < names.length; i++) {
    html += '<button type="button" class="filterbtn" data-cat="' + esc(names[i]) + '">' + esc(names[i]) + ' (' + cats[names[i]] + ')</button>';
  }
  el.innerHTML = html;
  var btns = el.getElementsByTagName('button');
  for (i = 0; i < btns.length; i++) {
    btns[i].onclick = (function(b) {
      return function() {
        var j, all = el.getElementsByTagName('button');
        for (j = 0; j < all.length; j++) { all[j].className = 'filterbtn'; }
        b.className = 'filterbtn on';
        activeCat = b.getAttribute('data-cat') || '';
        renderCatalog();
      };
    })(btns[i]);
  }
}

function renderCatalog() {
  var q = (document.getElementById('search').value || '').toLowerCase();
  var tb = document.getElementById('catalog-table').getElementsByTagName('tbody')[0];
  var html = '', n = 0, i, p, hay;
  for (i = 0; i < PACKAGES.length; i++) {
    p = PACKAGES[i];
    if (activeCat && p.category !== activeCat) continue;
    hay = (p.name + ' ' + p.category + ' ' + p.description).toLowerCase();
    if (q && hay.indexOf(q) === -1) continue;
    html += rowHtml(p, true);
    n++;
  }
  tb.innerHTML = html;
  document.getElementById('result-count').textContent = n + ' of ' + PACKAGES.length + ' packages';
}

document.getElementById('search').oninput = renderCatalog;
renderFeatured();
renderFilters();
renderCatalog();
</script>
</body>
</html>
HTMLEOF

DOC_OUT="$REPO_ROOT/berrycore/doc/berrycore.html"
mkdir -p "$(dirname "$DOC_OUT")"
cp "$OUT" "$DOC_OUT"
echo "Generated $OUT (${PACKAGES_COUNT} packages, ${FEATURED_COUNT} featured, v${VERSION})"
echo "Also: $DOC_OUT (bundled in berrycore.zip)"
