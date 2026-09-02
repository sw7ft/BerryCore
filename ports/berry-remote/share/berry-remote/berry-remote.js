#!/usr/bin/env node
/*
 * berry-remote.js -- browser-accessible remote view + control of a
 * Chromium content_shell running on the BB10/QNX device.
 *
 * CDP over --remote-debugging-pipe (fds 3/4). Page.captureScreenshot loop → JPEG.
 * Input / nav / back / forward / reload over HTTP → CDP Input.* / Page.*.
 *
 * Run from a dir containing content_shell + paks + libs:
 *   PORT=8080 URL=https://duckduckgo.com/ node --jitless berry-remote.js
 */
'use strict';

var http = require('http');
var spawn = require('child_process').spawn;
var path = require('path');
var fs = require('fs');

var DIR = process.cwd();
var BIN = path.join(DIR, 'content_shell');
var PORT = parseInt(process.env.PORT || '8080', 10);
var HOST = process.env.HOST || '0.0.0.0';
var START_URL = process.env.URL || 'https://html.duckduckgo.com/html/';
var RENDER = parseInt(process.env.RENDER || '360', 10);
var RENDER_H = parseInt(process.env.RENDER_H || String(RENDER), 10);
var JPEG_QUALITY = parseInt(process.env.QUALITY || '40', 10);
var GRAB_MS = parseInt(process.env.GRAB || '400', 10);
var TOKEN = process.env.TOKEN || '';
var STARTED = Date.now();
var VERSION = '72-bc16';
var IDLE_MS = 8000;
var BOOKMARKS_FILE = path.join(DIR, 'bookmarks.json');
var SETTINGS_FILE = path.join(DIR, 'settings.json');
var BROWSE_HOME = process.env.BROWSE_HOME || 'http://127.0.0.1:8040/';
var PROFILE = path.join(DIR, 'profile');
try { fs.mkdirSync(PROFILE); } catch (e) {}

function clamp(n, lo, hi, fallback) {
  n = parseInt(n, 10);
  if (isNaN(n)) return fallback;
  if (n < lo) return lo;
  if (n > hi) return hi;
  return n;
}
function loadSettings() {
  try {
    var s = JSON.parse(fs.readFileSync(SETTINGS_FILE, 'utf8'));
    if (s.width) RENDER = clamp(s.width, 240, 1280, RENDER);
    if (s.height) RENDER_H = clamp(s.height, 240, 1280, RENDER_H);
    if (s.quality) JPEG_QUALITY = clamp(s.quality, 20, 90, JPEG_QUALITY);
    if (s.grab) GRAB_MS = clamp(s.grab, 200, 2000, GRAB_MS);
    if (s.url && /^https?:\/\//.test(s.url)) START_URL = s.url;
  } catch (e) {}
}
function saveSettings() {
  fs.writeFileSync(SETTINGS_FILE, JSON.stringify({
    width: RENDER, height: RENDER_H, quality: JPEG_QUALITY, grab: GRAB_MS,
    url: lastUrl || START_URL
  }));
}
function settingsPublic() {
  return {
    width: RENDER, height: RENDER_H, quality: JPEG_QUALITY, grab: GRAB_MS,
    presets: [
      { name: '360', w: 360, h: 360 },
      { name: '480', w: 480, h: 480 },
      { name: '640', w: 640, h: 640 },
      { name: '720', w: 720, h: 720 },
      { name: '360×640', w: 360, h: 640 },
      { name: '640×360', w: 640, h: 360 }
    ]
  };
}
loadSettings();

function log() {
  process.stdout.write('[remote] ' +
    Array.prototype.slice.call(arguments).join(' ') + '\n');
}

try { fs.writeFileSync(path.join(DIR, '.service.pid'), String(process.pid)); } catch (e) {}

// ---------------------------------------------------------------------------
// Launch content_shell — flag set is the proven WhatsApp/QNX combination.
// ---------------------------------------------------------------------------
var env = {};
var ek;
for (ek in process.env) {
  if (Object.prototype.hasOwnProperty.call(process.env, ek)) env[ek] = process.env[ek];
}
env.QNX_DEVTOOLS = '1';
env.LD_LIBRARY_PATH = DIR + ':' + (process.env.LD_LIBRARY_PATH || '');
env.QNX_SCREEN_WIDTH = String(RENDER);
env.QNX_SCREEN_HEIGHT = String(RENDER_H);
env.QNX_SCREEN_OUTPUT_WIDTH = String(RENDER);
env.QNX_SCREEN_OUTPUT_HEIGHT = String(RENDER_H);
env.QNX_SCREEN_ROTATION = process.env.QNX_SCREEN_ROTATION || '90';
var ca = path.join(DIR, 'root_store.certs');
if (fs.existsSync(ca)) env.QNX_CA_BUNDLE = ca;

var args = [
  '--no-sandbox', '--no-zygote', '--single-process',
  '--disable-gpu', '--disable-gpu-compositing',
  '--ozone-platform=qnx_screen',
  '--disable-renderer-accessibility',
  '--ignore-certificate-errors',
  '--use-fake-ui-for-media-stream',
  '--disable-quic',
  '--enable-low-end-device-mode',
  '--disable-background-networking',
  '--disable-hang-monitor',
  '--disable-component-update',
  '--disable-remote-fonts',
  '--disable-sync',
  '--disable-breakpad',
  '--disable-smooth-scrolling',
  '--disable-renderer-backgrounding',
  '--disable-backgrounding-occluded-windows',
  '--disable-ipc-flooding-protection',
  '--num-raster-threads=1',
  '--js-flags=--max-old-space-size=64',
  '--user-data-dir=' + PROFILE,
  '--disk-cache-dir=' + path.join(PROFILE, 'Cache'),
  '--disk-cache-size=83886080',
  '--disable-features=NetworkServiceDedicatedThread,MojoIpcz,Translate,' +
    'OptimizationHints,MediaRouter,PreconnectToSearch,' +
    'InterestFeedContentSuggestions,PaintHolding,LazyImageLoading',
  '--force-device-scale-factor=1',
  '--remote-debugging-pipe', '--remote-allow-origins=*',
  'about:blank'
];

log('engine:', BIN);
log('url:', START_URL, 'render:', RENDER + 'x' + RENDER_H, 'q=' + JPEG_QUALITY);

var child = spawn(BIN, args, {
  cwd: DIR, env: env, stdio: ['ignore', 'ignore', 'pipe', 'pipe', 'pipe']
});
try { fs.writeFileSync(path.join(DIR, '.engine.pid'), String(child.pid)); } catch (e) {}
child.on('error', function (e) { log('spawn error', e.message); process.exit(1); });
child.on('exit', function (c, s) {
  log('engine exited code=' + c + ' sig=' + s);
  try { fs.unlinkSync(path.join(DIR, '.engine.pid')); } catch (e) {}
  process.exit(1);
});

var elog = fs.openSync(path.join(DIR, 'berry-remote-engine.log'), 'w');
child.stdio[2].on('data', function (d) { try { fs.writeSync(elog, d); } catch (e) {} });

// ---------------------------------------------------------------------------
// Minimal CDP-over-pipe client (NUL-delimited JSON on fds 3=write, 4=read).
// ---------------------------------------------------------------------------
var pipeWrite = child.stdio[3];
var pipeRead = child.stdio[4];
var nextId = 0, pending = {}, listeners = [], rbuf = Buffer.alloc(0);

pipeRead.on('data', function (chunk) {
  rbuf = Buffer.concat([rbuf, chunk]);
  var start = 0;
  for (var i = 0; i < rbuf.length; i++) {
    if (rbuf[i] === 0) {
      var s = rbuf.slice(start, i); start = i + 1;
      if (s.length) dispatch(s.toString('utf8'));
    }
  }
  rbuf = rbuf.slice(start);
});
function dispatch(text) {
  var msg; try { msg = JSON.parse(text); } catch (e) { return; }
  if (msg.id && pending[msg.id]) {
    var p = pending[msg.id]; delete pending[msg.id];
    if (msg.error) p.reject(new Error(JSON.stringify(msg.error)));
    else p.resolve(msg.result || {});
  } else if (msg.method) {
    for (var k = 0; k < listeners.length; k++) listeners[k](msg);
  }
}
function send(method, params, sid, timeoutMs) {
  return new Promise(function (resolve, reject) {
    var id = ++nextId; pending[id] = { resolve: resolve, reject: reject };
    var e = { id: id, method: method, params: params || {} };
    if (sid) e.sessionId = sid;
    pipeWrite.write(JSON.stringify(e) + '\0');
    setTimeout(function () {
      if (pending[id]) { delete pending[id]; reject(new Error('timeout: ' + method)); }
    }, timeoutMs || 12000);
  });
}
function sendRaw(o) { pipeWrite.write(JSON.stringify(o) + '\0'); }
function sleep(ms) { return new Promise(function (r) { setTimeout(r, ms); }); }

// ---------------------------------------------------------------------------
// Screenshot grab + MJPEG (startScreencast SIGSEGVs this QNX content_shell)
// ---------------------------------------------------------------------------
var session = null, attachResolve = null, loadResolve = null;
var lastFrame = null;
var lastFrameAt = 0;
var lastUrl = START_URL;
var lastTitle = '';
var lastText = '';
var lastFocus = { edit: false, tag: '', type: '' };
var lastMeta = { deviceWidth: RENDER, deviceHeight: RENDER_H,
                 pageScaleFactor: 1, offsetTop: 0,
                 scrollOffsetX: 0, scrollOffsetY: 0 };
var mjpegClients = [];
var frameCount = 0;
var lastViewerAt = 0;
var lastB64 = '';
var navigating = false;
var navGen = 0;
var hotUntil = 0;

function hasViewer() {
  return mjpegClients.length > 0 || (lastViewerAt && Date.now() - lastViewerAt < IDLE_MS);
}
function bumpHot() {
  hotUntil = Date.now() + 1600;
}
function grabDelay() {
  if (!hasViewer()) return 1400;
  if (Date.now() < hotUntil) return 140;
  return GRAB_MS;
}
function touchViewer() {
  var woke = !hasViewer();
  lastViewerAt = Date.now();
  if (woke) { bumpHot(); scheduleGrab(40); }
}

listeners.push(function (msg) {
  if (msg.method === 'Target.attachedToTarget') {
    var ti = msg.params.targetInfo || {};
    if (ti.type === 'page') {
      session = msg.params.sessionId;
      if (attachResolve) { var r = attachResolve; attachResolve = null; r(); }
    }
  } else if (msg.method === 'Page.screencastFrame') {
    frameCount++;
    lastFrameAt = Date.now();
    if (msg.params.metadata) lastMeta = msg.params.metadata;
    var buf = Buffer.from(msg.params.data, 'base64');
    lastFrame = buf;
    sendRaw({ id: 900000 + frameCount, method: 'Page.screencastFrameAck',
              params: { sessionId: msg.params.sessionId }, sessionId: session });
    pushFrameToClients(buf);
  } else if (msg.method === 'Page.loadEventFired' ||
             msg.method === 'Page.domContentEventFired') {
    if (loadResolve) { var lr = loadResolve; loadResolve = null; lr(); }
  } else if (msg.method === 'Page.javascriptDialogOpening') {
    send('Page.handleJavaScriptDialog', { accept: false }, session, 4000).catch(function () {});
  } else if (msg.method === 'Page.frameNavigated') {
    var fr = (msg.params && msg.params.frame) || {};
    if (fr.url && !fr.parentId) {
      lastUrl = fr.url;
      if (!navigating) refreshPageInfo();
    }
  }
});

function pushFrameToClients(buf) {
  for (var i = mjpegClients.length - 1; i >= 0; i--) {
    var res = mjpegClients[i];
    try {
      res.write('--frame\r\nContent-Type: image/jpeg\r\nContent-Length: ' +
                buf.length + '\r\n\r\n');
      res.write(buf);
      res.write('\r\n');
    } catch (e) {
      mjpegClients.splice(i, 1);
    }
  }
}

function waitForSession() {
  return new Promise(function (resolve, reject) {
    if (session) return resolve();
    attachResolve = resolve;
    setTimeout(function () {
      if (attachResolve) { attachResolve = null; reject(new Error('no page session')); }
    }, 20000);
  });
}

var grabBusy = false;
var grabTimer = null;
function scheduleGrab(ms) {
  if (grabTimer) clearTimeout(grabTimer);
  grabTimer = setTimeout(grabFrame, ms || GRAB_MS);
}
function waitLoad(ms) {
  return new Promise(function (resolve) {
    var done = false;
    loadResolve = function () { if (!done) { done = true; resolve(); } };
    setTimeout(function () {
      if (!done) { done = true; loadResolve = null; resolve(); }
    }, ms || 8000);
  });
}
function beginNav() {
  navigating = true;
  navGen++;
  lastB64 = '';
  if (grabTimer) { clearTimeout(grabTimer); grabTimer = null; }
}
function endNav() {
  navigating = false;
  refreshPageInfo();
  scheduleGrab(40);
  setTimeout(function () { if (!navigating) scheduleGrab(280); }, 320);
  setTimeout(function () { if (!navigating) scheduleGrab(800); }, 850);
}
function afterNavigate() {
  var g = navGen;
  return waitLoad(9000).then(function () {
    if (g !== navGen) return;
    return sleep(80);
  }).then(function () {
    if (g !== navGen) return;
    endNav();
  });
}
function grabFrame() {
  grabTimer = null;
  if (!session) { scheduleGrab(500); return; }
  if (navigating) { scheduleGrab(500); return; }
  if (grabBusy) return;
  if (lastFrame && !hasViewer()) {
    scheduleGrab(1400);
    return;
  }
  grabBusy = true;
  send('Page.captureScreenshot', {
    format: 'jpeg', quality: JPEG_QUALITY,
    captureBeyondViewport: false
  }, session, 20000).then(function (r) {
    grabBusy = false;
    if (navigating) { scheduleGrab(400); return; }
    if (r && r.data && r.data !== lastB64) {
      lastB64 = r.data;
      lastFrame = Buffer.from(r.data, 'base64');
      lastFrameAt = Date.now();
      frameCount++;
      lastMeta.deviceWidth = RENDER;
      lastMeta.deviceHeight = RENDER_H;
      pushFrameToClients(lastFrame);
      if (frameCount % 10 === 0) refreshPageInfo();
    }
    scheduleGrab(grabDelay());
  }, function (e) {
    grabBusy = false;
    if (navigating) { scheduleGrab(600); return; }
    log('grab', e.message);
    scheduleGrab(1800);
  });
}

function refreshPageInfo() {
  if (!session || navigating) return;
  send('Runtime.evaluate', {
    expression: '(function(){var t=document.title||"";var u=location.href||"";' +
      'var el=document.activeElement,tag="",ty="",edit=false;' +
      'if(el){tag=(el.tagName||"").toLowerCase();ty=el.type||"";' +
      'edit=tag==="input"||tag==="textarea"||!!el.isContentEditable;' +
      'if(tag==="input"&&(ty==="button"||ty==="submit"||ty==="checkbox"||ty==="radio"))edit=false;}' +
      'return {url:u,title:t,edit:edit,tag:tag,type:ty};})()',
    returnByValue: true
  }, session, 5000).then(function (r) {
    var v = r && r.result && r.result.value;
    if (!v) return;
    if (v.url) lastUrl = v.url;
    if (v.title !== undefined) lastTitle = v.title;
    lastFocus = { edit: !!v.edit, tag: v.tag || '', type: v.type || '' };
  }, function () {});
}
function dumpPageText() {
  if (!session || navigating) {
    return Promise.resolve((lastTitle ? lastTitle + '\n\n' : '') + (lastText || ''));
  }
  return send('Runtime.evaluate', {
    expression: '(function(){var x="";try{x=(document.body&&document.body.innerText)||"";}catch(e){}' +
      'if(x.length>200000)x=x.slice(0,200000);return x;})()',
    returnByValue: true
  }, session, 8000).then(function (r) {
    var v = r && r.result && r.result.value;
    if (typeof v === 'string') lastText = v;
    return (lastTitle ? lastTitle + '\n\n' : '') + (lastText || '');
  }, function () {
    return (lastTitle ? lastTitle + '\n\n' : '') + (lastText || '');
  });
}

function cssX(fx) { return Math.round(fx * (lastMeta.deviceWidth || RENDER)); }
function cssY(fy) { return Math.round(fy * (lastMeta.deviceHeight || RENDER_H)); }

function mouse(type, fx, fy, buttons, button, clickCount) {
  sendRaw({
    id: ++nextId, method: 'Input.dispatchMouseEvent', sessionId: session,
    params: {
      type: type, x: cssX(fx), y: cssY(fy),
      button: button || (buttons ? 'left' : 'none'),
      buttons: buttons || 0,
      clickCount: clickCount || 0
    }
  });
}
function wheel(fx, fy, dx, dy) {
  sendRaw({
    id: ++nextId, method: 'Input.dispatchMouseEvent', sessionId: session,
    params: {
      type: 'mouseWheel', x: cssX(fx), y: cssY(fy),
      deltaX: dx || 0, deltaY: dy || 0
    }
  });
}
function releaseModifiers() {
  if (!session) return;
  var names = [
    { key: 'Shift', code: 'ShiftLeft', keyCode: 16 },
    { key: 'Control', code: 'ControlLeft', keyCode: 17 },
    { key: 'Alt', code: 'AltLeft', keyCode: 18 },
    { key: 'Meta', code: 'MetaLeft', keyCode: 91 }
  ];
  var i;
  for (i = 0; i < names.length; i++) {
    sendRaw({
      id: ++nextId, method: 'Input.dispatchKeyEvent', sessionId: session,
      params: {
        type: 'keyUp', key: names[i].key, code: names[i].code,
        windowsVirtualKeyCode: names[i].keyCode,
        nativeVirtualKeyCode: names[i].keyCode
      }
    });
  }
}

function keyEvent(ev) {
  if (!session || !ev) return;
  var key = ev.key || '';
  if (key === 'Shift' || key === 'Control' || key === 'Alt' || key === 'Meta') {
    if (ev.type === 'keyUp' || ev.type === 'release') releaseModifiers();
    return;
  }
  if (ev.type === 'release') { releaseModifiers(); return; }
  if ((ev.type === 'insert' || ev.type === 'insertText' || ev.type === 'char') && ev.text) {
    releaseModifiers();
    sendRaw({
      id: ++nextId, method: 'Input.insertText',
      params: { text: String(ev.text) }, sessionId: session
    });
    return;
  }
  var p = { type: ev.type || 'keyDown' };
  if (ev.text !== undefined) p.text = ev.text;
  if (ev.unmodifiedText !== undefined) p.unmodifiedText = ev.unmodifiedText;
  if (ev.key !== undefined) p.key = ev.key;
  if (ev.code !== undefined) p.code = ev.code;
  if (ev.keyCode !== undefined) {
    p.windowsVirtualKeyCode = ev.keyCode;
    p.nativeVirtualKeyCode = ev.keyCode;
  }
  sendRaw({ id: ++nextId, method: 'Input.dispatchKeyEvent', params: p, sessionId: session });
}

function historyStep(delta) {
  return send('Page.getNavigationHistory', {}, session).then(function (h) {
    var entries = h.entries || [];
    var idx = (h.currentIndex || 0) + delta;
    if (idx < 0 || idx >= entries.length) return null;
    var id = entries[idx].id;
    lastUrl = entries[idx].url || lastUrl;
    return send('Page.navigateToHistoryEntry', { entryId: id }, session);
  });
}

function authorized(req) {
  if (!TOKEN) return true;
  var h = req.headers || {};
  if (h['x-berry-remote'] === TOKEN) return true;
  var q = (req.url.split('?')[1] || '');
  return q.indexOf('token=' + TOKEN) >= 0;
}

function readBody(req) {
  return new Promise(function (resolve) {
    var b = '';
    req.on('data', function (d) { b += d; if (b.length > 1e6) b = b.slice(0, 1e6); });
    req.on('end', function () { resolve(b); });
  });
}

function deny(res) { res.writeHead(401); res.end('unauthorized'); }

function loadBookmarks() {
  try {
    var raw = fs.readFileSync(BOOKMARKS_FILE, 'utf8');
    var list = JSON.parse(raw);
    return Array.isArray(list) ? list : [];
  } catch (e) { return []; }
}
function writeBookmarks(list) {
  fs.writeFileSync(BOOKMARKS_FILE, JSON.stringify(list));
}
function loadPageHtml() {
  try {
    return fs.readFileSync(path.join(__dirname, 'berry-viewer.html'), 'utf8')
      .split('%%START_URL%%').join(START_URL);
  } catch (e) {
    return '<!doctype html><html><body style="background:#300A24;color:#ddd">' +
      '<p>berry-viewer.html missing</p><img src="/stream"></body></html>';
  }
}

var server = http.createServer(function (req, res) {
  var u = req.url.split('?')[0];

  if (u === '/' || u === '/index.html') {
    touchViewer();
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    res.end(loadPageHtml());
    return;
  }

  if (u === '/stream') {
    touchViewer();
    res.writeHead(200, {
      'Content-Type': 'multipart/x-mixed-replace; boundary=frame',
      'Cache-Control': 'no-cache, no-store, must-revalidate',
      'Pragma': 'no-cache', 'Connection': 'close'
    });
    mjpegClients.push(res);
    if (lastFrame) pushFrameToClients(lastFrame);
    req.on('close', function () {
      var i = mjpegClients.indexOf(res);
      if (i >= 0) mjpegClients.splice(i, 1);
    });
    return;
  }

  if (u === '/input' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    readBody(req).then(function (b) {
      var ev; try { ev = JSON.parse(b); } catch (e) { ev = null; }
      if (ev && session) {
        try {
          touchViewer();
          if (ev.kind === 'down') mouse('mousePressed', ev.fx, ev.fy, 1, 'left', 1);
          else if (ev.kind === 'up') mouse('mouseReleased', ev.fx, ev.fy, 0, 'left', 1);
          else if (ev.kind === 'move') mouse('mouseMoved', ev.fx, ev.fy, ev.buttons ? 1 : 0);
          else if (ev.kind === 'wheel') wheel(ev.fx, ev.fy, ev.dx, ev.dy);
          bumpHot();
          if (ev.kind !== 'move' && !navigating) scheduleGrab(50);
        } catch (e) {}
      }
      res.writeHead(204); res.end();
    });
    return;
  }

  if (u === '/key' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    readBody(req).then(function (b) {
      var ev; try { ev = JSON.parse(b); } catch (e) { ev = null; }
      if (ev && session) {
        try {
          touchViewer();
          keyEvent(ev);
          bumpHot();
          if (ev.type !== 'keyUp' && !navigating) scheduleGrab(50);
        } catch (e) {}
      }
      res.writeHead(204); res.end();
    });
    return;
  }

  if (u === '/nav' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    readBody(req).then(function (b) {
      var o; try { o = JSON.parse(b); } catch (e) { o = null; }
      if (o && o.url && session) {
        lastUrl = o.url;
        beginNav();
        send('Page.navigate', { url: o.url }, session, 20000)
          .then(function () { return afterNavigate(); })
          .catch(function () { endNav(); });
      }
      res.writeHead(204); res.end();
    });
    return;
  }

  if (u === '/reload' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    if (session) {
      beginNav();
      send('Page.reload', { ignoreCache: false }, session, 20000)
        .then(function () { return afterNavigate(); })
        .catch(function () { endNav(); });
    }
    res.writeHead(204); res.end();
    return;
  }

  if (u === '/back' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    if (session) {
      beginNav();
      historyStep(-1).then(function () { return afterNavigate(); })
        .catch(function () { endNav(); });
    }
    res.writeHead(204); res.end();
    return;
  }

  if (u === '/forward' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    if (session) {
      beginNav();
      historyStep(1).then(function () { return afterNavigate(); })
        .catch(function () { endNav(); });
    }
    res.writeHead(204); res.end();
    return;
  }

  if (u === '/settings' && req.method === 'GET') {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify(settingsPublic()));
    return;
  }

  if (u === '/settings' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    readBody(req).then(function (b) {
      var o; try { o = JSON.parse(b); } catch (e) { o = {}; }
      if (o.width) RENDER = clamp(o.width, 240, 1280, RENDER);
      if (o.height) RENDER_H = clamp(o.height, 240, 1280, RENDER_H);
      if (o.quality) JPEG_QUALITY = clamp(o.quality, 20, 90, JPEG_QUALITY);
      if (o.grab) GRAB_MS = clamp(o.grab, 200, 2000, GRAB_MS);
      try { saveSettings(); } catch (e) { log('settings save', e.message); }
      function reply() {
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ ok: true, restart: true, settings: settingsPublic() }));
        setTimeout(function () { process.exit(1); }, 250);
      }
      if (session) {
        send('Emulation.setDeviceMetricsOverride', {
          width: RENDER, height: RENDER_H, deviceScaleFactor: 1, mobile: false
        }, session, 5000).then(reply, reply);
      } else {
        reply();
      }
    });
    return;
  }

  if (u === '/text') {
    touchViewer();
    dumpPageText().then(function (t) {
      res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
      res.end(t);
    });
    return;
  }

  if (u === '/frame.seq') {
    touchViewer();
    res.writeHead(200, {
      'Content-Type': 'text/plain',
      'Cache-Control': 'no-cache',
      'Access-Control-Allow-Origin': '*'
    });
    res.end(String(frameCount));
    return;
  }

  if (u === '/frame.jpg') {
    touchViewer();
    if (!lastFrame) { res.writeHead(503); res.end(); return; }
    var etag = '"' + frameCount + '-' + lastFrame.length + '"';
    if ((req.headers['if-none-match'] || '') === etag) {
      res.writeHead(304, { 'ETag': etag, 'Cache-Control': 'no-cache' });
      res.end();
      return;
    }
    res.writeHead(200, {
      'Content-Type': 'image/jpeg', 'Content-Length': lastFrame.length,
      'ETag': etag,
      'Cache-Control': 'no-cache',
      'Connection': 'keep-alive'
    });
    res.end(lastFrame);
    return;
  }

  if (u === '/bookmarks' && req.method === 'GET') {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify({ bookmarks: loadBookmarks() }));
    return;
  }

  if (u === '/bookmark' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    readBody(req).then(function (b) {
      var o; try { o = JSON.parse(b); } catch (e) { o = null; }
      var url = (o && o.url) ? String(o.url).replace(/^\s+|\s+$/g, '') : lastUrl;
      if (!url) { res.writeHead(400); res.end('no url'); return; }
      var list = loadBookmarks();
      var i;
      for (i = 0; i < list.length; i++) {
        if (list[i].url === url) {
          res.writeHead(200, { 'Content-Type': 'application/json' });
          res.end(JSON.stringify({ ok: true, already: true, bookmarks: list }));
          return;
        }
      }
      list.unshift({
        id: Date.now(),
        url: url,
        title: (o && o.title) ? String(o.title) : url,
        ts: Date.now()
      });
      if (list.length > 80) list = list.slice(0, 80);
      writeBookmarks(list);
      res.writeHead(200, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify({ ok: true, bookmarks: list }));
    });
    return;
  }

  if (u === '/bookmark/delete' && req.method === 'POST') {
    if (!authorized(req)) return deny(res);
    readBody(req).then(function (b) {
      var o; try { o = JSON.parse(b); } catch (e) { o = {}; }
      var list = loadBookmarks();
      var next = [];
      var i;
      for (i = 0; i < list.length; i++) {
        if (o.id && list[i].id === o.id) continue;
        if (o.url && list[i].url === o.url) continue;
        next.push(list[i]);
      }
      writeBookmarks(next);
      res.writeHead(200, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify({ ok: true, bookmarks: next }));
    });
    return;
  }

  if (u === '/status') {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify({
      ok: true,
      version: VERSION,
      session: !!session,
      frames: frameCount,
      clients: mjpegClients.length,
      watching: hasViewer(),
      meta: lastMeta,
      url: lastUrl,
      title: lastTitle,
      focus: lastFocus,
      browseHome: BROWSE_HOME,
      port: PORT,
      host: HOST,
      render: RENDER,
      width: RENDER,
      height: RENDER_H,
      quality: JPEG_QUALITY,
      grab: GRAB_MS,
      navigating: navigating,
      capture: 'screenshot',
      enginePid: child.pid || null,
      servicePid: process.pid,
      uptimeSec: Math.round((Date.now() - STARTED) / 1000)
    }));
    return;
  }

  res.writeHead(404); res.end('not found');
});

function boot() {
  send('Target.setAutoAttach',
       { autoAttach: true, waitForDebuggerOnStart: false, flatten: true }, null, 12000)
    .then(function () { log('autoAttach ok; waiting for page session'); return waitForSession(); })
    .then(function () {
      log('page session', session, '-> viewport', RENDER + 'x' + RENDER_H, 'nav', START_URL);
      return send('Page.enable', {}, session, 8000);
    })
    .then(function () {
      return send('Runtime.enable', {}, session, 8000);
    })
    .then(function () {
      return send('Emulation.setDeviceMetricsOverride', {
        width: RENDER, height: RENDER_H, deviceScaleFactor: 1, mobile: false
      }, session, 8000);
    })
    .then(function () {
      return send('Page.addScriptToEvaluateOnNewDocument', {
        source: 'try{var s=document.createElement("style");s.textContent=' +
          '"*{animation:none!important;transition:none!important;scroll-behavior:auto!important}";' +
          'document.documentElement.appendChild(s);}catch(e){}'
      }, session, 8000);
    })
    .then(function () {
      sendRaw({ id: ++nextId, method: 'Network.enable', params: {}, sessionId: session });
      sendRaw({
        id: ++nextId, method: 'Network.setCacheDisabled',
        params: { cacheDisabled: false }, sessionId: session
      });
      sendRaw({
        id: ++nextId, method: 'Network.setBlockedURLs', sessionId: session,
        params: { urls: [
          '*google-analytics.com*', '*googletagmanager.com*', '*doubleclick.net*',
          '*adservice.google.com*', '*scorecardresearch.com*',
          '*googlesyndication.com*', '*amazon-adsystem.com*'
        ] }
      });
    })
    .then(function () {
      beginNav();
      return send('Page.navigate', { url: START_URL }, session, 20000)
        .then(function () { return afterNavigate(); })
        .catch(function () { endNav(); });
    })
    .then(function () {
      log('capture loop', GRAB_MS + 'ms');
      releaseModifiers();
    })
    .catch(function (e) {
      log('BOOT FAIL', e.message, '(http stays up)');
    });
}

function listenHttp() {
  if (server.listening) return;
  server.listen(PORT, HOST, function () {
    log('LISTENING http://' + HOST + ':' + PORT + '  (open in a browser)');
  });
}
listenHttp();
setTimeout(boot, 1500);

process.on('unhandledRejection', function (e) {
  log('unhandled', e && e.message ? e.message : e);
});
