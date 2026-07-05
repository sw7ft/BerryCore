#!/usr/bin/env python3
"""
RocketChat Navigator v3 — BB10 ES5 web client
Local proxy on port 8026 for Rocket.Chat private groups, channels, and DMs.
"""
import http.server
import socketserver
import json
import os
import sys
import urllib.request
import urllib.parse
import ssl
import time
import threading
import socket
import subprocess
import tempfile
import datetime

PORT = 8026
VERSION = '3.2'
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CONFIG_FILE_PATH = os.path.join(BASE_DIR, '.env')
DISMISSED_ALERTS_PATH = os.path.join(BASE_DIR, '.dismissed_alerts')
STATIC_DIR = os.path.join(BASE_DIR, 'static')

CACHE_DURATION = 30
MESSAGE_CACHE_DURATION = 12
CONFIG_CACHE_DURATION = 60
REQUEST_TIMEOUT = 12
DEFAULT_MSG_COUNT = 40

cache = {
    'config': None,
    'config_time': 0,
    'rooms': None,
    'rooms_time': 0,
    'messages': {},
    'user_info': None,
    'user_time': 0,
    'last_message_ids': {},
    'room_types': {},
    'read_message_ids': {},
    'unread_counts': {},
    'active_room_id': '',
    'last_in_app_alert': None,
    'dismissed_alert_ids': set(),
}


def load_dismissed_alerts():
    ids = set()
    if os.path.exists(DISMISSED_ALERTS_PATH):
        try:
            with open(DISMISSED_ALERTS_PATH, 'r') as f:
                for line in f:
                    key = line.strip()
                    if key:
                        ids.add(key)
        except Exception as e:
            print('[ALERT] load dismissed error: %s' % e)
    cache['dismissed_alert_ids'] = ids


def save_dismissed_alert(alert_id):
    if not alert_id:
        return
    cache['dismissed_alert_ids'].add(alert_id)
    try:
        with open(DISMISSED_ALERTS_PATH, 'a') as f:
            f.write('%s\n' % alert_id)
    except Exception as e:
        print('[ALERT] save dismissed error: %s' % e)


def alert_is_dismissed(alert):
    if not alert:
        return True
    aid = alert.get('id', '')
    if aid and aid in cache.get('dismissed_alert_ids', set()):
        return True
    return False


def dismiss_alert(alert_id=None, room_id=None):
    alert = cache.get('last_in_app_alert')
    if alert_id:
        save_dismissed_alert(alert_id)
    elif alert and alert.get('id'):
        save_dismissed_alert(alert['id'])
    elif room_id and alert and alert.get('room_id') == room_id:
        save_dismissed_alert(alert.get('id', '%s:%s' % (room_id, alert.get('time', ''))))
    if alert and (not room_id or alert.get('room_id') == room_id or alert_id == alert.get('id')):
        cache['last_in_app_alert'] = None


load_dismissed_alerts()


def execute_shell_command(title, subtitle, itemid='RocketChat'):
    payload = {
        'itemid': itemid,
        'title': title,
        'subtitle': subtitle,
        'target': 'YourTarget',
        'targetAction': 'YourTargetAction',
        'payload': 'YourPayload',
        'payloadType': 'YourPayloadType',
        'payloadURI': 'YourPayloadURI',
    }
    json_payload = json.dumps(payload)
    try:
        with tempfile.NamedTemporaryFile(delete=False, mode='w', encoding='utf-8') as temp_file:
            temp_file.write('msg::notify\ndat:json:%s' % json_payload)
            temp_file_path = temp_file.name
        subprocess.run('cat %s >> /pps/services/notify/control' % temp_file_path, shell=True, check=True)
        print('[NOTIFY] %s' % title)
    except Exception as e:
        print('[NOTIFY] error: %s' % e)


def parse_rc_timestamp(ts):
    if isinstance(ts, dict) and '$date' in ts:
        try:
            ms = ts['$date']
            if isinstance(ms, (int, float)):
                return datetime.datetime.fromtimestamp(ms / 1000.0)
        except Exception:
            pass
    if isinstance(ts, str):
        try:
            return datetime.datetime.fromisoformat(ts.replace('Z', '+00:00').split('+')[0])
        except Exception:
            pass
    return None


def format_time_short(dt):
    if not dt:
        return ''
    try:
        now = datetime.datetime.now()
        if dt.date() == now.date():
            h = dt.hour % 12 or 12
            m = dt.minute
            ampm = 'PM' if dt.hour >= 12 else 'AM'
            return '%d:%02d %s' % (h, m, ampm)
        if dt.year == now.year:
            return dt.strftime('%b %d')
        return dt.strftime('%Y-%m-%d')
    except Exception:
        return ''


def format_time_full(dt):
    if not dt:
        return 'Now'
    try:
        return dt.strftime('%Y-%m-%d %H:%M:%S')
    except Exception:
        return 'Now'


def get_cached_or_fetch_config():
    global cache
    now = time.time()
    if cache['config'] and (now - cache['config_time']) < CONFIG_CACHE_DURATION:
        return cache['config']
    config = {}
    if os.path.exists(CONFIG_FILE_PATH):
        try:
            with open(CONFIG_FILE_PATH, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line and not line.startswith('#') and '=' in line:
                        key, value = line.split('=', 1)
                        config[key.strip()] = value.strip()
        except Exception as e:
            print('config load error: %s' % e)
    cache['config'] = config
    cache['config_time'] = now
    return config


def load_config():
    return get_cached_or_fetch_config()


def get_ssl_context():
    try:
        ctx = ssl.create_default_context()
    except AttributeError:
        try:
            ctx = ssl.SSLContext(getattr(ssl, 'PROTOCOL_TLS', ssl.PROTOCOL_SSLv23))
        except Exception:
            return None
    try:
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE
    except Exception:
        pass
    return ctx


def urlopen_with_ssl(req, timeout):
    ctx = get_ssl_context()
    try:
        if ctx is not None:
            return urllib.request.urlopen(req, timeout=timeout, context=ctx)
    except TypeError:
        pass
    return urllib.request.urlopen(req, timeout=timeout)


def make_rocketchat_request(endpoint, config, method='GET', data=None):
    try:
        if not config.get('RCSERVER') or not config.get('RCTOKEN') or not config.get('RCID'):
            return {'success': False, 'error': 'Missing configuration'}
        url = '%s/api/v1/%s' % (config['RCSERVER'], endpoint)
        headers = {
            'X-Auth-Token': config['RCTOKEN'],
            'X-User-Id': config['RCID'],
            'Content-Type': 'application/json',
            'User-Agent': 'BB10RocketChatNavigator/%s' % VERSION,
        }
        body = None
        if method == 'POST' and data is not None:
            body = json.dumps(data).encode('utf-8')
        req = urllib.request.Request(url, data=body, headers=headers)
        req.get_method = lambda: method
        response = urlopen_with_ssl(req, REQUEST_TIMEOUT)
        return json.loads(response.read().decode('utf-8'))
    except urllib.error.HTTPError as e:
        return {'success': False, 'error': 'HTTP %s: %s' % (e.code, e.reason)}
    except urllib.error.URLError as e:
        return {'success': False, 'error': 'Connection error: %s' % e.reason}
    except socket.timeout:
        return {'success': False, 'error': 'Request timeout'}
    except Exception as e:
        return {'success': False, 'error': str(e)}


def is_own_message(msg, config):
    """True if message was sent by the logged-in user (ID + username)."""
    if not msg:
        return False
    user = msg.get('u', {}) or {}
    my_id = config.get('RCID', '')
    if my_id and user.get('_id') == my_id:
        return True
    my_username = get_user_info(config).get('username', '')
    sender = user.get('username', '')
    if my_username and sender and sender == my_username:
        return True
    return False


def record_message_seen(room_id, message_id):
    if not room_id:
        return
    if message_id:
        cache['last_message_ids'][room_id] = message_id
        cache['read_message_ids'][room_id] = message_id
    cache['unread_counts'][room_id] = 0


def bump_unread(room_id):
    cache['unread_counts'][room_id] = cache['unread_counts'].get(room_id, 0) + 1


def unread_total():
    total = 0
    for count in cache['unread_counts'].values():
        if count > 0:
            total += count
    return total


def attach_unread_to_rooms(rooms_data):
    for key in ('channels', 'groups', 'direct_messages'):
        for room in rooms_data.get(key, []):
            rid = room.get('id')
            room['unread'] = cache['unread_counts'].get(rid, 0)
    rooms_data['unread_total'] = unread_total()
    return rooms_data


def get_user_info(config):
    global cache
    now = time.time()
    if cache['user_info'] and (now - cache['user_time']) < CONFIG_CACHE_DURATION:
        return cache['user_info']
    result = make_rocketchat_request('me', config)
    if result.get('success'):
        cache['user_info'] = result.get('user', {})
        cache['user_time'] = now
        return cache['user_info']
    return {}


def room_last_preview(config, room_id, room_type):
    if room_type == 'dm':
        endpoint = 'im.messages?roomId=%s&count=1' % room_id
    elif room_type == 'group':
        endpoint = 'groups.messages?roomId=%s&count=1' % room_id
    else:
        endpoint = 'channels.messages?roomId=%s&count=1' % room_id
    result = make_rocketchat_request(endpoint, config)
    if result.get('success') and result.get('messages'):
        msg = result['messages'][0]
        text = msg.get('msg', '')
        if len(text) > 80:
            text = text[:77] + '...'
        sender = msg.get('u', {}).get('username', '')
        dt = parse_rc_timestamp(msg.get('ts'))
        return text, sender, dt
    return '', '', None


def preview_from_room(room_obj, my_username):
    text = ''
    sender = ''
    dt = None
    last = room_obj.get('lastMessage')
    if last and isinstance(last, dict):
        text = last.get('msg', '')
        sender = last.get('u', {}).get('username', '')
        dt = parse_rc_timestamp(last.get('ts'))
    if not text:
        dt = parse_rc_timestamp(room_obj.get('lm'))
    if len(text) > 80:
        text = text[:77] + '...'
    if sender and sender != my_username and text:
        text = '%s: %s' % (sender, text)
    return text, format_time_short(dt)


def get_rooms_data(config):
    if not config.get('RCSERVER') or not config.get('RCTOKEN'):
        return {'status': 'error', 'message': 'Missing config'}

    user_info = get_user_info(config)
    my_username = user_info.get('username', '')
    channels = []
    groups = []
    direct_messages = []

    ch_result = make_rocketchat_request('channels.list?count=50&sort={"lm":-1}', config)
    if ch_result.get('success'):
        for ch in ch_result.get('channels', []):
            rid = ch.get('_id')
            name = ch.get('name', 'unknown')
            preview, time_str = preview_from_room(ch, my_username)
            cache['room_types'][rid] = 'channel'
            channels.append({
                'id': rid,
                'name': name,
                'display': '#%s' % name,
                'type': 'channel',
                'preview': preview,
                'time': time_str,
                'last_activity': ch.get('lm', ''),
            })

    gr_result = make_rocketchat_request('groups.list?count=50&sort={"lm":-1}', config)
    if gr_result.get('success'):
        for group in gr_result.get('groups', []):
            rid = group.get('_id')
            name = group.get('name', 'unknown')
            preview, time_str = preview_from_room(group, my_username)
            cache['room_types'][rid] = 'group'
            groups.append({
                'id': rid,
                'name': name,
                'display': '🔒%s' % name,
                'type': 'group',
                'preview': preview,
                'time': time_str,
                'last_activity': group.get('lm', ''),
            })

    im_result = make_rocketchat_request('im.list?count=50&sort={"lm":-1}', config)
    if im_result.get('success'):
        for im in im_result.get('ims', []):
            rid = im.get('_id', '')
            other = 'Unknown'
            usernames = im.get('usernames', [])
            for uname in usernames:
                if uname and uname != my_username:
                    other = uname
                    break
            preview, time_str = preview_from_room(im, my_username)
            cache['room_types'][rid] = 'dm'
            direct_messages.append({
                'id': rid,
                'name': other,
                'display': '@%s' % other,
                'type': 'dm',
                'preview': preview,
                'time': time_str,
                'last_activity': im.get('lm', ''),
            })

    return {
        'status': 'success',
        'channels': channels,
        'groups': groups,
        'direct_messages': direct_messages,
        'user': my_username,
        'total': len(channels) + len(groups) + len(direct_messages),
    }


def fetch_messages_for_room(config, chat_id, count=DEFAULT_MSG_COUNT, before=None):
    room_type = cache['room_types'].get(chat_id)
    endpoints = []
    if room_type == 'dm':
        endpoints = ['im.messages?roomId=%s&count=%d' % (chat_id, count)]
    elif room_type == 'group':
        endpoints = ['groups.messages?roomId=%s&count=%d' % (chat_id, count)]
    elif room_type == 'channel':
        endpoints = ['channels.messages?roomId=%s&count=%d' % (chat_id, count)]
    else:
        endpoints = [
            'im.messages?roomId=%s&count=%d' % (chat_id, count),
            'groups.messages?roomId=%s&count=%d' % (chat_id, count),
            'channels.messages?roomId=%s&count=%d' % (chat_id, count),
        ]

    if before:
        for i, ep in enumerate(endpoints):
            endpoints[i] = ep + '&sort={"ts":-1}&offset=0'
            # RocketChat uses oldest param in some versions; try timestamp filter
            endpoints[i] = ep.replace('&count=%d' % count, '&count=%d&latest=%s' % (count, urllib.parse.quote(before)))

    messages_result = None
    for endpoint in endpoints:
        messages_result = make_rocketchat_request(endpoint, config)
        if messages_result.get('success') and messages_result.get('messages') is not None:
            if room_type is None:
                if 'im.messages' in endpoint:
                    cache['room_types'][chat_id] = 'dm'
                elif 'groups.messages' in endpoint:
                    cache['room_types'][chat_id] = 'group'
                else:
                    cache['room_types'][chat_id] = 'channel'
            break

    if not messages_result or not messages_result.get('success'):
        return []

    user_info = get_user_info(config)
    formatted = []
    for msg in messages_result.get('messages', []):
        is_mine = is_own_message(msg, config)
        sender_name = msg.get('u', {}).get('username', 'Unknown')
        if is_mine:
            sender_name = 'You'
        dt = parse_rc_timestamp(msg.get('ts'))
        formatted.append({
            'id': msg.get('_id', ''),
            'sender_name': sender_name,
            'message': msg.get('msg', ''),
            'date': format_time_full(dt),
            'day': dt.strftime('%A, %B %d, %Y') if dt else '',
            'time_short': format_time_short(dt),
            'is_mine': is_mine,
            'ts': dt.isoformat() if dt else '',
        })
    return formatted


def initialize_message_tracking():
    global cache
    try:
        config = load_config()
        if not config.get('RCSERVER'):
            return
        rooms_result = get_rooms_data(config)
        if rooms_result.get('status') != 'success':
            return
        all_rooms = []
        all_rooms.extend(rooms_result.get('channels', []))
        all_rooms.extend(rooms_result.get('groups', []))
        all_rooms.extend(rooms_result.get('direct_messages', []))
        for room in all_rooms:
            rid = room.get('id')
            if not rid:
                continue
            rtype = room.get('type', 'group')
            if rtype == 'dm':
                ep = 'im.messages?roomId=%s&count=1' % rid
            elif rtype == 'channel':
                ep = 'channels.messages?roomId=%s&count=1' % rid
            else:
                ep = 'groups.messages?roomId=%s&count=1' % rid
            res = make_rocketchat_request(ep, config)
            if res.get('success') and res.get('messages'):
                mid = res['messages'][0].get('_id')
                if mid:
                    cache['last_message_ids'][rid] = mid
                    cache['read_message_ids'].setdefault(rid, mid)
    except Exception as e:
        print('[NOTIFY] init error: %s' % e)


def check_for_new_messages():
    initialize_message_tracking()
    time.sleep(45)
    while True:
        try:
            config = load_config()
            if not config.get('RCSERVER'):
                time.sleep(30)
                continue
            now = time.time()
            if not cache['rooms'] or (now - cache['rooms_time']) > CACHE_DURATION:
                rooms_result = get_rooms_data(config)
                if rooms_result.get('status') == 'success':
                    cache['rooms'] = rooms_result
                    cache['rooms_time'] = now
            if not cache['rooms']:
                time.sleep(15)
                continue
            all_rooms = []
            all_rooms.extend(cache['rooms'].get('channels', []))
            all_rooms.extend(cache['rooms'].get('groups', []))
            all_rooms.extend(cache['rooms'].get('direct_messages', []))
            active_room = cache.get('active_room_id', '')
            for room in all_rooms:
                rid = room.get('id')
                rtype = room.get('type', 'group')
                if rtype == 'dm':
                    ep = 'im.messages?roomId=%s&count=1' % rid
                elif rtype == 'channel':
                    ep = 'channels.messages?roomId=%s&count=1' % rid
                else:
                    ep = 'groups.messages?roomId=%s&count=1' % rid
                res = make_rocketchat_request(ep, config)
                if not res.get('success') or not res.get('messages'):
                    continue
                latest = res['messages'][0]
                mid = latest.get('_id')
                last_known = cache['last_message_ids'].get(rid)
                if last_known and mid and last_known != mid:
                    if is_own_message(latest, config):
                        record_message_seen(rid, mid)
                    else:
                        bump_unread(rid)
                        sender = latest.get('u', {}).get('username', 'Someone')
                        text = latest.get('msg', '')
                        if len(text) > 100:
                            text = text[:97] + '...'
                        cache['last_in_app_alert'] = {
                            'id': '%s:%s' % (rid, mid),
                            'room_id': rid,
                            'room': room.get('display', room.get('name', 'Chat')),
                            'from': sender,
                            'text': text,
                            'time': int(time.time()),
                        }
                        # Hub notify only if user is not viewing this room
                        if rid != active_room:
                            title = '🚀 %s' % room.get('display', room.get('name', 'Chat'))
                            execute_shell_command(
                                title,
                                '%s: %s' % (sender, text),
                                'RocketChat-%s' % rid,
                            )
                        elif rid == active_room:
                            record_message_seen(rid, mid)
                if mid:
                    cache['last_message_ids'][rid] = mid
            time.sleep(12)
        except Exception as e:
            print('[NOTIFY] loop error: %s' % e)
            time.sleep(30)


_notify_thread = threading.Thread(target=check_for_new_messages)
try:
    _notify_thread.daemon = True
except Exception:
    pass
_notify_thread.start()


class RocketChatHandler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        print('[%s] %s' % (time.strftime('%H:%M:%S'), fmt % args))

    def do_GET(self):
        try:
            parsed = urllib.parse.urlparse(self.path)
            path = parsed.path
            config = load_config()
            authorized = config.get('RCSERVER') and config.get('RCTOKEN') and config.get('RCID')
            auth_paths = ['/start_auth', '/auth.html', '/static/style.css', '/static/app.js', '/favicon.ico']
            if not authorized and path not in auth_paths:
                self.redirect('/start_auth')
                return
            if path == '/':
                self.serve_file('index.html', 'text/html')
            elif path == '/start_auth':
                self.serve_file('auth.html', 'text/html')
            elif path == '/api/status':
                self.handle_status(config)
            elif path == '/get_rooms':
                self.handle_rooms(config)
            elif path == '/get_messages':
                self.handle_messages(config, parsed.query)
            elif path == '/api/refresh_messages':
                self.handle_refresh_messages(config, parsed.query)
            elif path == '/api/unread':
                self.handle_unread_api()
            elif path == '/api/config':
                self.send_json({'RCSERVER': config.get('RCSERVER', '')})
            elif path.startswith('/static/'):
                rel = path.lstrip('/')
                ctype = 'text/css' if rel.endswith('.css') else 'application/javascript'
                self.serve_static(rel, ctype)
            else:
                rel = path.lstrip('/')
                full = os.path.join(BASE_DIR, rel)
                if os.path.isfile(full):
                    self.serve_file(rel, 'text/html')
                else:
                    self.send_error(404)
        except Exception as e:
            print('GET error: %s' % e)
            self.send_error(500)

    def do_POST(self):
        try:
            parsed = urllib.parse.urlparse(self.path)
            config = load_config()
            if parsed.path == '/send_message':
                self.handle_send_message(config)
            elif parsed.path == '/api/login':
                self.handle_login()
            elif parsed.path == '/api/logout':
                self.handle_logout()
            elif parsed.path == '/api/save_config':
                self.handle_save_config()
            elif parsed.path == '/api/mark_read':
                self.handle_mark_read()
            elif parsed.path == '/api/active_room':
                self.handle_active_room()
            elif parsed.path == '/api/dismiss_alert':
                self.handle_dismiss_alert()
            else:
                self.send_error(404)
        except Exception as e:
            print('POST error: %s' % e)
            self.send_error(500)

    def redirect(self, location):
        self.send_response(302)
        self.send_header('Location', location)
        self.end_headers()

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
            self.end_headers()
            self.wfile.write(data)
        except IOError:
            self.send_error(404)

    def send_json(self, data, status=200):
        self.send_response(status)
        self.send_header('Content-Type', 'application/json; charset=utf-8')
        self.send_header('Cache-Control', 'no-cache')
        self.end_headers()
        self.wfile.write(json.dumps(data, separators=(',', ':'), ensure_ascii=False).encode('utf-8'))

    def read_json_body(self):
        length = int(self.headers.get('Content-Length', 0))
        raw = self.rfile.read(length).decode('utf-8')
        return json.loads(raw)

    def handle_status(self, config):
        if not config.get('RCSERVER'):
            self.send_json({'status': 'error', 'connected': False, 'message': 'Not configured'})
            return
        result = make_rocketchat_request('me', config)
        if result.get('success'):
            user = result.get('user', {})
            self.send_json({
                'status': 'success',
                'connected': True,
                'server': config['RCSERVER'],
                'user': user.get('username', 'Unknown'),
                'name': user.get('name', ''),
                'version': VERSION,
            })
        else:
            self.send_json({
                'status': 'error',
                'connected': False,
                'message': result.get('error', 'Connection failed'),
                'server': config.get('RCSERVER', ''),
            })

    def handle_rooms(self, config):
        global cache
        now = time.time()
        if cache['rooms'] and (now - cache['rooms_time']) < CACHE_DURATION:
            self.send_json(attach_unread_to_rooms(dict(cache['rooms'])))
            return
        rooms = get_rooms_data(config)
        if rooms.get('status') == 'success':
            cache['rooms'] = rooms
            cache['rooms_time'] = now
        self.send_json(attach_unread_to_rooms(rooms))

    def handle_messages(self, config, query_string):
        global cache
        params = urllib.parse.parse_qs(query_string)
        chat_id = params.get('chat_id', [''])[0]
        count = int(params.get('count', [str(DEFAULT_MSG_COUNT)])[0] or DEFAULT_MSG_COUNT)
        if not chat_id:
            self.send_json([])
            return
        cache_key = 'msg_%s_%d' % (chat_id, count)
        now = time.time()
        if cache_key in cache['messages'] and (now - cache['messages'][cache_key]['time']) < MESSAGE_CACHE_DURATION:
            self.send_json(cache['messages'][cache_key]['data'])
            return
        formatted = fetch_messages_for_room(config, chat_id, count=count)
        cache['messages'][cache_key] = {'data': formatted, 'time': now}
        if formatted:
            record_message_seen(chat_id, formatted[0].get('id', ''))
        self.send_json(formatted)

    def handle_refresh_messages(self, config, query_string):
        global cache
        params = urllib.parse.parse_qs(query_string)
        chat_id = params.get('chat_id', [''])[0]
        count = int(params.get('count', [str(DEFAULT_MSG_COUNT)])[0] or DEFAULT_MSG_COUNT)
        if not chat_id:
            self.send_json({'status': 'error', 'message': 'Missing chat_id'})
            return
        for key in list(cache['messages'].keys()):
            if key.startswith('msg_%s_' % chat_id):
                del cache['messages'][key]
        formatted = fetch_messages_for_room(config, chat_id, count=count)
        cache_key = 'msg_%s_%d' % (chat_id, count)
        cache['messages'][cache_key] = {'data': formatted, 'time': time.time()}
        if formatted:
            record_message_seen(chat_id, formatted[0].get('id', ''))
        self.send_json({'status': 'success', 'messages': formatted, 'message_count': len(formatted)})

    def handle_send_message(self, config):
        try:
            data = self.read_json_body()
            chat_id = data.get('chat_id')
            message_text = data.get('message')
            if not chat_id or not message_text:
                self.send_json({'status': 'error', 'message': 'Missing chat_id or message'})
                return
            result = make_rocketchat_request('chat.postMessage', config, method='POST', data={
                'roomId': chat_id,
                'text': message_text,
            })
            if result.get('success'):
                for key in list(cache['messages'].keys()):
                    if key.startswith('msg_%s_' % chat_id):
                        del cache['messages'][key]
                cache['rooms_time'] = 0
                sent = result.get('message') or {}
                mid = sent.get('_id')
                if mid:
                    record_message_seen(chat_id, mid)
                else:
                    cache['last_message_ids'][chat_id] = 'sent-%d' % int(time.time())
                self.send_json({'status': 'success', 'message': 'Message sent', 'message_id': mid or ''})
            else:
                self.send_json({'status': 'error', 'message': result.get('error', 'Send failed')})
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})

    def handle_logout(self):
        global cache
        try:
            if os.path.exists(CONFIG_FILE_PATH):
                os.remove(CONFIG_FILE_PATH)
        except Exception:
            pass
        cache['config'] = None
        cache['config_time'] = 0
        cache['rooms'] = None
        cache['rooms_time'] = 0
        cache['user_info'] = None
        cache['user_time'] = 0
        cache['messages'] = {}
        cache['room_types'] = {}
        cache['last_message_ids'] = {}
        cache['read_message_ids'] = {}
        cache['unread_counts'] = {}
        cache['active_room_id'] = ''
        cache['last_in_app_alert'] = None
        self.send_json({'status': 'success', 'next': '/start_auth'})

    def handle_unread_api(self):
        alert = cache.get('last_in_app_alert')
        if alert_is_dismissed(alert):
            alert = None
        payload = {
            'status': 'success',
            'unread_total': unread_total(),
            'unread': dict(cache.get('unread_counts', {})),
            'alert': alert,
        }
        self.send_json(payload)

    def handle_dismiss_alert(self):
        try:
            data = self.read_json_body()
            dismiss_alert(
                alert_id=data.get('alert_id', ''),
                room_id=data.get('room_id', ''),
            )
            self.send_json({'status': 'success'})
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})

    def handle_mark_read(self):
        try:
            data = self.read_json_body()
            chat_id = data.get('chat_id', '')
            message_id = data.get('message_id', '')
            if chat_id:
                cache['active_room_id'] = chat_id
                dismiss_alert(room_id=chat_id)
                if message_id:
                    record_message_seen(chat_id, message_id)
                else:
                    cache['unread_counts'][chat_id] = 0
            self.send_json({'status': 'success'})
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})

    def handle_active_room(self):
        try:
            data = self.read_json_body()
            chat_id = data.get('chat_id', '')
            cache['active_room_id'] = chat_id or ''
            if chat_id:
                dismiss_alert(room_id=chat_id)
                cache['unread_counts'][chat_id] = 0
            self.send_json({'status': 'success'})
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})

    def handle_save_config(self):
        try:
            data = self.read_json_body()
            allowed = ['RCSERVER', 'RCTOKEN', 'RCID']
            existing = load_config()
            updated = False
            for key, value in data.items():
                if key in allowed and str(value).strip():
                    existing[key] = str(value).strip()
                    updated = True
            if not updated:
                self.send_json({'status': 'error', 'message': 'No valid configuration'})
                return
            with open(CONFIG_FILE_PATH, 'w') as f:
                for key in allowed:
                    if key in existing:
                        f.write('%s=%s\n' % (key, existing[key]))
            global cache
            cache['config'] = None
            cache['rooms'] = None
            cache['messages'] = {}
            self.send_json({'status': 'success'})
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})

    def handle_login(self):
        global cache
        try:
            data = self.read_json_body()
            server_url = data.get('server_url', '').strip()
            username = data.get('username', '').strip()
            password = data.get('password', '').strip()
            if not server_url or not username or not password:
                self.send_json({'status': 'error', 'message': 'Server URL, username, and password required'})
                return
            if not server_url.startswith('http'):
                server_url = 'https://' + server_url
            login_result = self.rocketchat_login(server_url, username, password)
            if not login_result.get('success'):
                self.send_json({'status': 'error', 'message': login_result.get('error', 'Login failed')})
                return
            auth_token = login_result.get('data', {}).get('authToken')
            user_id = login_result.get('data', {}).get('userId')
            if not auth_token or not user_id:
                self.send_json({'status': 'error', 'message': 'Login OK but no tokens returned'})
                return
            with open(CONFIG_FILE_PATH, 'w') as f:
                f.write('# RocketChat Navigator v3\n')
                f.write('RCSERVER=%s\n' % server_url)
                f.write('RCTOKEN=%s\n' % auth_token)
                f.write('RCID=%s\n' % user_id)
            cache['config'] = None
            cache['rooms'] = None
            cache['messages'] = {}
            self.send_json({'status': 'success', 'next': '/'})
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})

    def rocketchat_login(self, server_url, username, password):
        try:
            login_url = '%s/api/v1/login' % server_url
            body = json.dumps({'user': username, 'password': password}).encode('utf-8')
            req = urllib.request.Request(login_url, data=body, headers={
                'Content-Type': 'application/json',
                'User-Agent': 'BB10RocketChatNavigator/%s' % VERSION,
            })
            req.get_method = lambda: 'POST'
            response = urlopen_with_ssl(req, REQUEST_TIMEOUT)
            return json.loads(response.read().decode('utf-8'))
        except urllib.error.HTTPError as e:
            try:
                err = json.loads(e.read().decode('utf-8'))
                return {'success': False, 'error': err.get('error', err.get('message', 'HTTP %s' % e.code))}
            except Exception:
                return {'success': False, 'error': 'HTTP %s' % e.code}
        except Exception as e:
            return {'success': False, 'error': str(e)}


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True
    daemon_threads = True


def run_server(port=PORT):
    config = load_config()
    print('=' * 60)
    print('RocketChat Navigator v%s' % VERSION)
    print('Port: %s' % port)
    print('Server: %s' % config.get('RCSERVER', 'not configured'))
    print('Open http://localhost:%s' % port)
    print('=' * 60)
    httpd = ThreadedTCPServer(('', port), RocketChatHandler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print('Shutting down')
    finally:
        httpd.server_close()


if __name__ == '__main__':
    run_server()
