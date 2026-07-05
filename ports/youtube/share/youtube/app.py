#!/usr/bin/env python3
"""
YouTube Navigator v2 — BB10 ES5 web client
Search and stream YouTube via local proxy on port 8070.
"""
import http.server
import socketserver
import urllib.parse
import urllib.request
import json
import os
import ssl
import sys
import signal
import re
import time

PORT = 8070
VERSION = '2.3.3'
APP_NAME = 'YouTube Search'
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
STATIC_DIR = os.path.join(BASE_DIR, 'static')

# Ensure berrycore Python can find bundled site-packages (pytube, etc.)
_BERRYCORE = os.path.dirname(os.path.dirname(BASE_DIR))
_BC_HOME = os.path.join(_BERRYCORE, 'lib', 'python3_ntoarmv7-qnx-static')
if os.path.isdir(_BC_HOME) and not os.environ.get('PYTHONHOME'):
    os.environ['PYTHONHOME'] = _BC_HOME

QNX_MODE = True
EMBED_FIRST = QNX_MODE

cache_timeout = 300
search_cache = {}
stream_cache = {}
stream_cache_timeout = 600


def create_permissive_ssl_context():
    try:
        ctx = ssl._create_unverified_context()
        return ctx
    except Exception:
        try:
            ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
            ctx.verify_mode = ssl.CERT_NONE
            ctx.check_hostname = False
            return ctx
        except Exception:
            return ssl.create_default_context()


ssl_context = create_permissive_ssl_context()


def create_qnx_ssl_context(*args, **kwargs):
    return ssl_context


ssl._create_default_https_context = create_qnx_ssl_context
ssl.create_default_context = create_qnx_ssl_context
ssl._create_unverified_context = create_qnx_ssl_context

try:
    from youtubesearchpython import VideosSearch  # noqa: F401
    SEARCH_METHOD = 'direct-http'
except Exception:
    SEARCH_METHOD = 'direct-http'

try:
    from pytube import YouTube
    from pytube.exceptions import VideoUnavailable, RegexMatchError, PytubeError  # noqa: F401
    PYTUBE_AVAILABLE = True
except Exception:
    PYTUBE_AVAILABLE = False


def get_cached_search(cache_key):
    if cache_key in search_cache:
        cached_data, timestamp = search_cache[cache_key]
        if time.time() - timestamp < cache_timeout:
            return cached_data
    return None


def cache_search_results(cache_key, results):
    search_cache[cache_key] = (results, time.time())
    if len(search_cache) > 50:
        oldest_key = min(search_cache.keys(), key=lambda k: search_cache[k][1])
        del search_cache[oldest_key]


def extract_video_id(url):
    if not url:
        return None
    if 'watch?v=' in url:
        return url.split('watch?v=')[1].split('&')[0]
    if 'youtu.be/' in url:
        return url.split('youtu.be/')[1].split('?')[0]
    if '/embed/' in url:
        return url.split('/embed/')[1].split('?')[0]
    return None


PLAYER_CLIENTS = [
    {'clientName': 'ANDROID', 'clientVersion': '19.08.35'},
    {'clientName': 'IOS', 'clientVersion': '19.08.35'},
    {'clientName': 'WEB', 'clientVersion': '2.20231201.00.00'},
]


def build_embed_url(video_id, origin, nocookie=False, autoplay=False):
    base = 'https://www.youtube-nocookie.com' if nocookie else 'https://www.youtube.com'
    params = [
        'controls=1', 'rel=0', 'modestbranding=1', 'iv_load_policy=3',
        'fs=1', 'playsinline=1', 'enablejsapi=1',
    ]
    if autoplay:
        params.insert(0, 'autoplay=1')
    if origin:
        params.append('origin=' + urllib.parse.quote(origin, safe=''))
    return '%s/embed/%s?%s' % (base, video_id, '&'.join(params))


def pick_progressive_stream(formats, quality='360p'):
    progressive_streams = []
    for fmt in formats:
        if 'url' not in fmt:
            continue
        mime_type = fmt.get('mimeType', '')
        quality_label = fmt.get('qualityLabel', '')
        if (
            'video/mp4' in mime_type
            and 'codecs="avc1' in mime_type
            and quality_label
            and 'p' in quality_label
        ):
            q = quality_label.replace('p', '')
            if q.isdigit():
                progressive_streams.append({
                    'url': fmt['url'],
                    'quality': int(q),
                    'quality_label': quality_label,
                    'mime_type': mime_type,
                    'has_audio': fmt.get('audioQuality') is not None or 'mp4a' in mime_type,
                })

    progressive_streams.sort(key=lambda x: (x['has_audio'], x['quality']), reverse=True)
    target_quality = quality.replace('p', '') if quality not in ('best', 'audio') else None
    best_stream = None

    if target_quality and target_quality.isdigit():
        target_q = int(target_quality)
        for stream in progressive_streams:
            if stream['quality'] <= target_q:
                best_stream = stream
                break

    if not best_stream and progressive_streams:
        best_stream = progressive_streams[0]

    if best_stream:
        return {
            'url': best_stream['url'],
            'quality': str(best_stream['quality']),
            'mime_type': best_stream['mime_type'],
        }
    return None


def extract_video_urls_advanced(video_id, quality='360p'):
    player_url = 'https://www.youtube.com/youtubei/v1/player'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Linux; Android 11) AppleWebKit/537.36',
        'Content-Type': 'application/json',
    }
    for client in PLAYER_CLIENTS:
        try:
            player_data = {
                'videoId': video_id,
                'context': {'client': client},
            }
            req = urllib.request.Request(
                player_url,
                data=json.dumps(player_data).encode('utf-8'),
                headers=headers,
            )
            with urllib.request.urlopen(req, context=ssl_context, timeout=12) as response:
                player_response = json.loads(response.read().decode('utf-8'))

            if 'streamingData' not in player_response:
                continue

            streaming_data = player_response['streamingData']
            formats = streaming_data.get('formats', []) + streaming_data.get('adaptiveFormats', [])
            picked = pick_progressive_stream(formats, quality)
            if picked:
                picked['client'] = client['clientName']
                return picked
        except Exception as e:
            print('Player API (%s) failed: %s' % (client['clientName'], e))
    return None


def get_pytube_stream(url, quality='360p'):
    if not PYTUBE_AVAILABLE:
        return None
    try:
        yt = YouTube(url)
        best_stream = None
        if quality == 'best':
            best_stream = yt.streams.filter(progressive=True).order_by('resolution').desc().first()
        elif quality == 'audio':
            best_stream = yt.streams.filter(only_audio=True).order_by('abr').desc().first()
        else:
            best_stream = yt.streams.filter(progressive=True, res=quality).first()
            if not best_stream:
                best_stream = yt.streams.filter(progressive=True).order_by('resolution').desc().first()
        if not best_stream:
            return None
        return {
            'title': yt.title,
            'author': yt.author,
            'length_seconds': yt.length,
            'description': (yt.description[:500] if yt.description else ''),
            'thumbnail': 'https://i.ytimg.com/vi/%s/hqdefault.jpg' % yt.video_id,
            'stream_url': best_stream.url,
            'stream_quality': getattr(best_stream, 'resolution', 'audio'),
            'stream_type': best_stream.mime_type,
        }
    except Exception as e:
        print('Pytube failed: %s' % e)
        return None


def collect_stream_sources(video_id, url, quality, origin, mode='auto'):
    """Build ordered playback sources for client-side fallback chain."""
    if mode == 'fast':
        info = get_youtube_info_instant(video_id)
        sources = []
        sources.append({
            'method': 'embed',
            'stream_url': build_embed_url(video_id, origin, False, False),
            'is_embed': True,
            'label': 'YouTube embed',
            'stream_quality': 'embed',
            'stream_type': 'text/html',
        })
        sources.append({
            'method': 'embed_nocookie',
            'stream_url': build_embed_url(video_id, origin, True, False),
            'is_embed': True,
            'label': 'Privacy embed',
            'stream_quality': 'embed',
            'stream_type': 'text/html',
        })
        sources.append({
            'method': 'embed_autoplay',
            'stream_url': build_embed_url(video_id, origin, False, True),
            'is_embed': True,
            'label': 'YouTube embed (autoplay)',
            'stream_quality': 'embed',
            'stream_type': 'text/html',
        })
        return info, sources

    info = get_youtube_info_fast(video_id)
    sources = []

    def add_embed(method, nocookie, autoplay, label):
        sources.append({
            'method': method,
            'stream_url': build_embed_url(video_id, origin, nocookie, autoplay),
            'is_embed': True,
            'label': label,
            'stream_quality': 'embed',
            'stream_type': 'text/html',
        })

    def add_direct(direct):
        sources.append({
            'method': 'direct_api',
            'stream_url': direct['url'],
            'is_embed': False,
            'label': 'Direct stream (%sp)' % direct['quality'],
            'stream_quality': '%sp' % direct['quality'],
            'stream_type': direct['mime_type'],
        })

    if mode in ('auto', 'embed'):
        add_embed('embed', False, False, 'YouTube embed')
        add_embed('embed_nocookie', True, False, 'Privacy embed')
        add_embed('embed_autoplay', False, True, 'YouTube embed (autoplay)')

    if mode in ('auto', 'direct', 'expand'):
        direct = extract_video_urls_advanced(video_id, quality)
        if direct:
            add_direct(direct)

    if mode in ('auto', 'pytube', 'direct', 'expand'):
        pytube_data = get_pytube_stream(url, quality)
        if pytube_data:
            sources.append({
                'method': 'pytube',
                'stream_url': pytube_data['stream_url'],
                'is_embed': False,
                'label': 'Pytube stream (%s)' % pytube_data['stream_quality'],
                'stream_quality': pytube_data['stream_quality'],
                'stream_type': pytube_data['stream_type'],
            })
            if pytube_data.get('title'):
                info['title'] = pytube_data['title']
            if pytube_data.get('author'):
                info['author'] = pytube_data['author']
            if pytube_data.get('length_seconds'):
                info['length_seconds'] = pytube_data['length_seconds']
            if pytube_data.get('description'):
                info['description'] = pytube_data['description']

    if mode == 'embed' and not sources:
        add_embed('embed', False, False, 'YouTube embed')

    if mode in ('auto', 'embed') and len(sources) < 2:
        add_embed('embed_nocookie', True, True, 'Privacy embed (autoplay)')

    return info, sources


def collect_expand_sources(video_id, url, quality):
    """Slow direct/pytube sources — fetched in background after fast embed start."""
    info = get_youtube_info_fast(video_id)
    _, sources = collect_stream_sources(video_id, url, quality, '', 'expand')
    return info, sources


def get_cached_stream(cache_key):
    if cache_key in stream_cache:
        cached_data, timestamp = stream_cache[cache_key]
        if time.time() - timestamp < stream_cache_timeout:
            return cached_data
    return None


def cache_stream_result(cache_key, payload):
    stream_cache[cache_key] = (payload, time.time())
    if len(stream_cache) > 40:
        oldest_key = min(stream_cache.keys(), key=lambda k: stream_cache[k][1])
        del stream_cache[oldest_key]


def get_youtube_info_instant(video_id):
    return {
        'title': 'YouTube Video',
        'author': '',
        'length_seconds': 0,
        'description': '',
        'thumbnail': 'https://i.ytimg.com/vi/%s/hqdefault.jpg' % video_id,
    }
def get_youtube_info_fast(video_id):
    cached = get_cached_stream('info:%s' % video_id)
    if cached:
        return cached
    try:
        oembed_url = (
            'https://www.youtube.com/oembed?url=https://www.youtube.com/watch?v=%s&format=json'
            % video_id
        )
        req = urllib.request.Request(oembed_url, headers={
            'User-Agent': 'Mozilla/5.0 (compatible; YouTube Search App)',
        })
        with urllib.request.urlopen(req, context=ssl_context, timeout=3) as response:
            data = json.loads(response.read().decode('utf-8'))
        info = {
            'title': data.get('title', 'YouTube Video %s' % video_id),
            'author': data.get('author_name', 'Unknown Channel'),
            'length_seconds': 0,
            'description': '',
            'thumbnail': data.get('thumbnail_url', 'https://i.ytimg.com/vi/%s/hqdefault.jpg' % video_id),
        }
        cache_stream_result('info:%s' % video_id, info)
        return info
    except Exception as e:
        print('Fast info extraction failed: %s' % e)
        return get_youtube_info_instant(video_id)


def search_youtube_direct(query, limit=20):
    try:
        search_url = 'https://www.youtube.com/results?search_query=%s' % urllib.parse.quote(query)
        headers = {
            'User-Agent': (
                'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 '
                '(KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
            ),
        }
        req = urllib.request.Request(search_url, headers=headers)
        with urllib.request.urlopen(req, context=ssl_context, timeout=15) as response:
            html = response.read().decode('utf-8')

        match = re.search(r'var ytInitialData = ({.*?});', html)
        if not match:
            match = re.search(r'window\["ytInitialData"\] = ({.*?});', html)
        if not match:
            return []

        data = json.loads(match.group(1))
        return parse_youtube_data(data, limit)
    except Exception as e:
        print('Direct search error: %s' % e)
        return []


def parse_youtube_data(data, limit):
    results = []
    try:
        contents = (
            data.get('contents', {})
            .get('twoColumnSearchResultsRenderer', {})
            .get('primaryContents', {})
            .get('sectionListRenderer', {})
            .get('contents', [])
        )
        for section in contents:
            items = section.get('itemSectionRenderer', {}).get('contents', [])
            for item in items:
                if 'videoRenderer' not in item:
                    continue
                video = item['videoRenderer']
                video_id = video.get('videoId', '')
                title = ''
                duration = 'Unknown'
                channel = 'Unknown Channel'
                views = 'Unknown views'
                published = 'Unknown'

                if 'title' in video and 'runs' in video['title']:
                    title = ''.join([run.get('text', '') for run in video['title']['runs']])
                elif 'title' in video and 'simpleText' in video['title']:
                    title = video['title']['simpleText']

                if 'lengthText' in video and 'simpleText' in video['lengthText']:
                    duration = video['lengthText']['simpleText']

                if 'ownerText' in video and 'runs' in video['ownerText']:
                    channel = video['ownerText']['runs'][0].get('text', 'Unknown Channel')

                if 'viewCountText' in video and 'simpleText' in video['viewCountText']:
                    views = video['viewCountText']['simpleText']

                if 'publishedTimeText' in video and 'simpleText' in video['publishedTimeText']:
                    published = video['publishedTimeText']['simpleText']

                if video_id and title:
                    results.append({
                        'title': title,
                        'url': 'https://www.youtube.com/watch?v=%s' % video_id,
                        'duration': duration,
                        'channel': channel,
                        'views': views,
                        'thumbnail': 'https://i.ytimg.com/vi/%s/hqdefault.jpg' % video_id,
                        'published': published,
                        'video_id': video_id,
                    })
                    if len(results) >= limit:
                        break
            if len(results) >= limit:
                break
    except Exception as e:
        print('Parse error: %s' % e)
    return results[:limit]


def send_json(handler, status_code, payload):
    body = json.dumps(payload).encode('utf-8')
    handler.send_response(status_code)
    handler.send_header('Content-Type', 'application/json')
    handler.send_header('Cache-Control', 'no-store')
    handler.send_header('Content-Length', str(len(body)))
    handler.send_header('Access-Control-Allow-Origin', '*')
    handler.end_headers()
    handler.wfile.write(body)


class SearchHandler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        message = fmt % args
        if '/api/game' in message or '/api/input' in message:
            return
        sys.stdout.write('%s - - [%s] %s\n' % (
            self.address_string(), self.log_date_time_string(), message))

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path

        if path in ('/', '/index.html'):
            self.serve_file('index.html', 'text/html; charset=utf-8')
            return

        if path.startswith('/static/'):
            rel = path.lstrip('/')
            if rel.endswith('.css'):
                ctype = 'text/css'
            elif rel.endswith('.js'):
                ctype = 'application/javascript'
            else:
                ctype = 'application/octet-stream'
            self.serve_static(rel, ctype)
            return

        if path == '/api/search':
            self.handle_search(parsed.query)
            return

        if path == '/api/stream':
            self.handle_stream(parsed.query)
            return

        if path == '/api/status':
            self.handle_status()
            return

        if path == '/api/cache-stats':
            self.handle_cache_stats()
            return

        if path == '/favicon.ico':
            self.send_favicon()
            return

        if path.startswith('/api/game') or path.startswith('/api/input'):
            send_json(self, 404, {'status': 'error', 'error': 'YouTube Search app, not a game server'})
            return

        self.send_error(404, 'Not Found')

    def do_POST(self):
        parsed = urllib.parse.urlparse(self.path)
        if parsed.path.startswith('/api/'):
            send_json(self, 405, {'status': 'error', 'error': 'GET only'})
            return
        self.send_error(405, 'Method Not Allowed')

    def serve_file(self, rel, content_type):
        full = os.path.join(BASE_DIR, rel)
        try:
            with open(full, 'rb') as f:
                data = f.read()
            self.send_response(200)
            self.send_header('Content-Type', content_type)
            self.send_header('Cache-Control', 'no-cache')
            self.end_headers()
            self.wfile.write(data)
        except IOError:
            self.send_error(404)

    def serve_static(self, rel, content_type):
        full = os.path.join(BASE_DIR, rel)
        try:
            with open(full, 'rb') as f:
                data = f.read()
            self.send_response(200)
            self.send_header('Content-Type', content_type)
            self.send_header('Cache-Control', 'public, max-age=3600')
            self.end_headers()
            self.wfile.write(data)
        except IOError:
            self.send_error(404)

    def handle_status(self):
        status = {
            'app': APP_NAME,
            'version': VERSION,
            'port': PORT,
            'search_method': SEARCH_METHOD,
            'pytube_available': PYTUBE_AVAILABLE,
            'cache_entries': len(search_cache),
            'qnx_mode': QNX_MODE,
            'embed_first': EMBED_FIRST,
        }
        send_json(self, 200, {'status': 'ok', 'info': status})

    def handle_cache_stats(self):
        send_json(self, 200, {
            'status': 'ok',
            'cache_stats': {
                'cache_entries': len(search_cache),
                'cache_timeout': cache_timeout,
                'cache_keys': list(search_cache.keys())[:10],
            },
        })

    def send_favicon(self):
        favicon_data = (
            b'\x00\x00\x01\x00\x01\x00\x10\x10\x00\x00\x01\x00\x18\x00h\x00\x00\x00'
            b'\x16\x00\x00\x00(\x00\x00\x00\x10\x00\x00\x00 \x00\x00\x00\x01\x00\x18'
            b'\x00\x00\x00\x00\x00@\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
            b'\x00\x00\x00\x00\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00'
        )
        self.send_response(200)
        self.send_header('Content-Type', 'image/x-icon')
        self.send_header('Content-Length', str(len(favicon_data)))
        self.end_headers()
        self.wfile.write(favicon_data)

    def handle_search(self, query_string):
        params = urllib.parse.parse_qs(query_string)
        query = params.get('q', [''])[0].strip()
        limit = int(params.get('limit', ['12'])[0])
        offset = int(params.get('offset', ['0'])[0])
        channel = params.get('channel', [''])[0].strip()

        if not query:
            send_json(self, 400, {'status': 'error', 'error': "Missing 'q' parameter"})
            return

        if limit > 24:
            limit = 24
        if offset < 0:
            offset = 0
        if offset > 100:
            offset = 100

        fetch_limit = min(limit + offset + 12, 48)
        cache_key = '%s:%s:%s' % (query, fetch_limit, channel.lower())

        cached_results = get_cached_search(cache_key)
        if cached_results is not None:
            page = cached_results[offset:offset + limit]
            send_json(self, 200, {
                'status': 'ok',
                'query': query,
                'results': page,
                'count': len(cached_results),
                'offset': offset,
                'limit': limit,
                'has_more': (offset + limit) < len(cached_results),
                'method': '%s (cached)' % SEARCH_METHOD,
                'cached': True,
            })
            return

        try:
            results = search_youtube_direct(query, fetch_limit)
            if channel:
                needle = channel.lower()
                results = [r for r in results if needle in r.get('channel', '').lower()]
            cache_search_results(cache_key, results)
            page = results[offset:offset + limit]
            send_json(self, 200, {
                'status': 'ok',
                'query': query,
                'results': page,
                'count': len(results),
                'offset': offset,
                'limit': limit,
                'has_more': (offset + limit) < len(results),
                'method': SEARCH_METHOD,
                'cached': False,
            })
        except Exception as e:
            send_json(self, 500, {'status': 'error', 'error': 'Search failed: %s' % str(e)})

    def handle_stream(self, query_string):
        params = urllib.parse.parse_qs(query_string)
        url = params.get('url', [''])[0].strip()
        quality = params.get('quality', ['360p'])[0]
        mode = params.get('method', ['fast'])[0].strip().lower()
        source_index = int(params.get('source', ['0'])[0])

        if not url:
            send_json(self, 400, {'status': 'error', 'error': "Missing 'url' parameter"})
            return

        video_id = extract_video_id(url)
        if not video_id:
            send_json(self, 400, {'status': 'error', 'error': 'Invalid YouTube URL'})
            return

        if mode == 'auto':
            mode = 'fast'
        if mode not in ('fast', 'auto', 'embed', 'direct', 'pytube', 'expand'):
            mode = 'fast'

        origin = 'http://%s' % self.headers.get('Host', 'localhost:%s' % PORT)
        print('Stream: %s quality=%s mode=%s origin=%s' % (url, quality, mode, origin))

        if mode == 'expand':
            try:
                info, sources = collect_expand_sources(video_id, url, quality)
            except Exception as e:
                print('collect_expand_sources failed: %s' % e)
                send_json(self, 500, {'status': 'error', 'error': 'Expand failed: %s' % str(e)})
                return
            send_json(self, 200, {
                'status': 'ok',
                'title': info.get('title', 'YouTube Video'),
                'author': info.get('author', 'Unknown Channel'),
                'thumbnail': info.get('thumbnail', 'https://i.ytimg.com/vi/%s/hqdefault.jpg' % video_id),
                'sources': sources,
                'video_id': video_id,
            })
            return

        cache_key = 'stream:%s:%s:%s' % (video_id, quality, mode)
        cached_payload = get_cached_stream(cache_key)
        if cached_payload is not None:
            cached_payload = dict(cached_payload)
            if source_index < len(cached_payload.get('sources', [])):
                primary = cached_payload['sources'][source_index]
                cached_payload['stream_url'] = primary['stream_url']
                cached_payload['stream_quality'] = primary.get('stream_quality', 'unknown')
                cached_payload['stream_type'] = primary.get('stream_type', 'video/mp4')
                cached_payload['is_embed'] = primary.get('is_embed', False)
                cached_payload['method'] = primary.get('method', 'unknown')
                cached_payload['label'] = primary.get('label', '')
                cached_payload['source_index'] = source_index
                cached_payload['has_more_sources'] = source_index < (len(cached_payload['sources']) - 1)
            send_json(self, 200, cached_payload)
            return

        try:
            info, sources = collect_stream_sources(video_id, url, quality, origin, mode)
        except Exception as e:
            print('collect_stream_sources failed: %s' % e)
            send_json(self, 500, {'status': 'error', 'error': 'Stream lookup failed: %s' % str(e)})
            return

        if not sources:
            send_json(self, 500, {'status': 'error', 'error': 'No playback sources available for this video'})
            return

        if source_index < 0 or source_index >= len(sources):
            source_index = 0

        primary = sources[source_index]
        payload = {
            'status': 'ok',
            'title': info.get('title', 'YouTube Video'),
            'author': info.get('author', 'Unknown Channel'),
            'length_seconds': info.get('length_seconds', 0),
            'description': info.get('description', ''),
            'thumbnail': info.get('thumbnail', 'https://i.ytimg.com/vi/%s/hqdefault.jpg' % video_id),
            'stream_url': primary['stream_url'],
            'stream_quality': primary.get('stream_quality', 'unknown'),
            'stream_type': primary.get('stream_type', 'video/mp4'),
            'is_embed': primary.get('is_embed', False),
            'method': primary.get('method', 'unknown'),
            'label': primary.get('label', ''),
            'source_index': source_index,
            'source_count': len(sources),
            'sources': sources,
            'video_id': video_id,
            'has_more_sources': source_index < (len(sources) - 1),
            'fast': mode == 'fast',
        }
        cache_stream_result(cache_key, payload)
        send_json(self, 200, payload)


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True
    daemon_threads = True


def _signal_handler(sig, frame):
    print('Shutting down %s...' % APP_NAME)
    sys.exit(0)


signal.signal(signal.SIGTERM, _signal_handler)
signal.signal(signal.SIGINT, _signal_handler)


def run_server(port=PORT):
    print('=' * 60)
    print('%s v%s' % (APP_NAME, VERSION))
    print('Port: %s' % port)
    print('Search: %s | pytube: %s | QNX embed-first: %s' % (
        SEARCH_METHOD, PYTUBE_AVAILABLE, EMBED_FIRST))
    print('Open http://localhost:%s' % port)
    print('=' * 60)
    httpd = ThreadedTCPServer(('', port), SearchHandler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print('Shutting down')
    finally:
        httpd.server_close()


if __name__ == '__main__':
    run_server()
