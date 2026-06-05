'use strict';
/**
 * Minimal fetch/Headers/Response for Node 22 --jitless + --no-experimental-fetch
 * (no global fetch; undici needs WASM which jitless disables).
 * Uses only node:http / node:https — no WebAssembly.
 */
const http = require('http');
const https = require('https');
const { URL } = require('url');

class BB10Headers {
  constructor(init) {
    this._m = new Map();
    if (init == null) return;
    if (typeof init.forEach === 'function' && typeof init.append === 'function') {
      init.forEach((v, k) => this.append(k, v));
    } else if (Array.isArray(init)) {
      for (const pair of init) {
        if (pair && pair.length >= 2) this.append(pair[0], pair[1]);
      }
    } else if (typeof init === 'object') {
      for (const k of Object.keys(init)) this.append(k, init[k]);
    }
  }
  append(name, value) {
    const k = String(name).toLowerCase();
    const v = String(value);
    if (this._m.has(k)) this._m.set(k, this._m.get(k) + ', ' + v);
    else this._m.set(k, v);
  }
  get(name) {
    const v = this._m.get(String(name).toLowerCase());
    return v === undefined ? null : v;
  }
  has(name) {
    return this._m.has(String(name).toLowerCase());
  }
  forEach(fn, thisArg) {
    for (const [k, v] of this._m) fn.call(thisArg, v, k, this);
  }
  set(name, value) {
    this._m.set(String(name).toLowerCase(), String(value));
  }
  delete(name) {
    return this._m.delete(String(name).toLowerCase());
  }
  *entries() {
    for (const [k, v] of this._m) yield [k, v];
  }
  *keys() {
    for (const k of this._m.keys()) yield k;
  }
  *values() {
    for (const v of this._m.values()) yield v;
  }
  [Symbol.iterator]() {
    return this.entries();
  }
}

class BB10Response {
  constructor(status, statusText, rawHeaders, bodyBuf) {
    this.status = status;
    this.statusText = statusText || '';
    this.ok = status >= 200 && status < 300;
    const flat = {};
    if (rawHeaders) {
      for (let i = 0; i < rawHeaders.length; i += 2) {
        const key = rawHeaders[i];
        const val = rawHeaders[i + 1];
        const lk = String(key).toLowerCase();
        flat[lk] = flat[lk] ? flat[lk] + ', ' + val : String(val);
      }
    }
    this.headers = new BB10Headers(flat);
    this._body = bodyBuf;
  }
  async text() {
    return this._body.toString('utf8');
  }
  async json() {
    return JSON.parse(this._body.toString('utf8'));
  }
  async arrayBuffer() {
    const b = this._body;
    const ab = b.buffer.slice(b.byteOffset, b.byteOffset + b.byteLength);
    return ab;
  }
}

function normalizeHeaders(h) {
  const o = {};
  if (!h) return o;
  if (typeof h.forEach === 'function') {
    h.forEach((v, k) => {
      o[String(k).toLowerCase()] = String(v);
    });
    return o;
  }
  for (const k of Object.keys(h)) o[String(k).toLowerCase()] = String(h[k]);
  return o;
}

function normalizeBody(body) {
  if (body == null || body === undefined) return null;
  if (typeof body === 'string') return Buffer.from(body, 'utf8');
  if (Buffer.isBuffer(body)) return body;
  if (body instanceof Uint8Array) return Buffer.from(body);
  if (typeof body.toString === 'function' && body.constructor && body.constructor.name === 'URLSearchParams')
    return Buffer.from(body.toString(), 'utf8');
  return null;
}

function bb10Fetch(input, init) {
  init = init || {};
  const urlStr = typeof input === 'string' ? input : input && input.url;
  if (!urlStr) return Promise.reject(new TypeError('fetch: invalid url'));

  const u = new URL(urlStr);
  const mod = u.protocol === 'https:' ? https : u.protocol === 'http:' ? http : null;
  if (!mod) return Promise.reject(new TypeError('fetch: unsupported URL scheme'));

  const method = String(init.method || 'GET').toUpperCase();
  const headers = normalizeHeaders(init.headers);
  const bodyBuf = normalizeBody(init.body);

  if (bodyBuf && !headers['content-length']) headers['content-length'] = String(bodyBuf.length);

  const opts = {
    method,
    hostname: u.hostname,
    port: u.port || (u.protocol === 'https:' ? 443 : 80),
    path: u.pathname + u.search,
    headers,
    rejectUnauthorized: process.env.NODE_TLS_REJECT_UNAUTHORIZED !== '0',
  };

  return new Promise((resolve, reject) => {
    const req = mod.request(opts, (res) => {
      const chunks = [];
      res.on('data', (c) => chunks.push(c));
      res.on('end', () => {
        const buf = Buffer.concat(chunks);
        resolve(new BB10Response(res.statusCode, res.statusMessage, res.rawHeaders, buf));
      });
    });
    req.on('error', reject);
    if (bodyBuf) req.write(bodyBuf);
    req.end();
  });
}

/** Enough for SDK checks / light usage; multipart not fully WHATWG. */
class BB10FormData {
  constructor() {
    this._m = new Map();
  }
  append(name, value, filename) {
    const k = String(name);
    const entry = { value, filename };
    if (!this._m.has(k)) this._m.set(k, []);
    this._m.get(k).push(entry);
  }
  delete(name) {
    return this._m.delete(String(name));
  }
  get(name) {
    const a = this._m.get(String(name));
    return a && a.length ? a[0].value : null;
  }
  getAll(name) {
    const a = this._m.get(String(name));
    return a ? a.map((e) => e.value) : [];
  }
  has(name) {
    return this._m.has(String(name));
  }
  set(name, value, filename) {
    const k = String(name);
    this._m.set(k, [{ value, filename }]);
  }
  forEach(fn, thisArg) {
    for (const [k, arr] of this._m) {
      for (const e of arr) fn.call(thisArg, e.value, k, this);
    }
  }
  *entries() {
    for (const [k, arr] of this._m) {
      for (const e of arr) yield [k, e.value];
    }
  }
  *keys() {
    for (const [k, arr] of this._m) {
      for (let i = 0; i < arr.length; i++) yield k;
    }
  }
  *values() {
    for (const [, arr] of this._m) {
      for (const e of arr) yield e.value;
    }
  }
  [Symbol.iterator]() {
    return this.entries();
  }
}

if (typeof globalThis.fetch !== 'function') {
  globalThis.fetch = bb10Fetch;
  globalThis.Headers = BB10Headers;
  globalThis.Response = BB10Response;
}
if (typeof globalThis.FormData !== 'function') {
  globalThis.FormData = BB10FormData;
}
