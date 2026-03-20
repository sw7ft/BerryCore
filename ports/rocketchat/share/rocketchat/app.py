#!/usr/bin/env python3
"""
BB10 RocketChat Navigator
A BlackBerry 10 optimized web application for navigating RocketChat private groups and direct messages.
Follows BB10 development standards and conventions.
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

PORT = 8026
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CONFIG_FILE_PATH = os.path.join(BASE_DIR, '.env')

# Performance optimization: Caching (following BB10 standards)
CACHE_DURATION = 30  # 30 seconds cache for rooms
MESSAGE_CACHE_DURATION = 15  # 15 seconds cache for messages
CONFIG_CACHE_DURATION = 60  # 60 seconds cache for config
REQUEST_TIMEOUT = 10  # 10 seconds timeout for requests

# Global cache to speed things up
cache = {
    'config': None,
    'config_time': 0,
    'rooms': None,
    'rooms_time': 0,
    'messages': {},  # room_id -> {messages, time}
    'user_info': None,
    'user_time': 0,
    'last_message_ids': {}  # room_id -> last_message_id (for notification tracking)
}

def execute_shell_command(title, subtitle, itemid="RocketChat"):
    """
    Executes the shell command to send a notification - EXACT copy from reminders.py
    
    Args:
        title (str): The title of the notification.
        subtitle (str): The subtitle/content of the notification.
        itemid (str): Identifier for the notification item.
    """
    payload = {
        "itemid": itemid,
        "title": title,
        "subtitle": subtitle,
        "target": "YourTarget",
        "targetAction": "YourTargetAction",
        "payload": "YourPayload",
        "payloadType": "YourPayloadType",
        "payloadURI": "YourPayloadURI"
    }
    json_payload = json.dumps(payload)

    try:
        with tempfile.NamedTemporaryFile(delete=False, mode="w", encoding="utf-8") as temp_file:
            temp_file.write(f"msg::notify\ndat:json:{json_payload}")
            temp_file_path = temp_file.name

        command = f"cat {temp_file_path} >> /pps/services/notify/control"
        subprocess.run(command, shell=True, check=True)
        print(f"[NOTIFY] Notification sent: {title}")
    except subprocess.CalledProcessError as e:
        print(f"[NOTIFY] Error sending notification '{title}': {e}")
    except Exception as e:
        print(f"[NOTIFY] General error sending notification '{title}': {e}")

def initialize_message_tracking():
    """
    Initialize message tracking with current latest messages - no notifications sent
    """
    global cache
    
    try:
        config = load_config()
        if not config.get('RCSERVER') or not config.get('RCTOKEN') or not config.get('RCID'):
            print("[NOTIFY] Not configured yet, skipping initialization")
            return
        
        print("[NOTIFY] Initializing message tracking...")
        
        # Get current rooms
        rooms_result = get_rooms_data(config)
        if rooms_result.get('status') == 'success':
            all_rooms = []
            all_rooms.extend(rooms_result.get('private_groups', []))
            all_rooms.extend(rooms_result.get('direct_messages', []))
            
            for room in all_rooms:
                room_id = room.get('id')
                room_type = 'd' if room.get('type') == 'dm' else 'p'
                
                if room_id:
                    # Get latest message ID (but don't send notification)
                    endpoint = f'im.messages?roomId={room_id}&count=1' if room_type == 'd' else f'groups.messages?roomId={room_id}&count=1'
                    messages_result = make_rocketchat_request(endpoint, config)
                    
                    if messages_result.get('success') and messages_result.get('messages'):
                        latest_message = messages_result['messages'][0]
                        message_id = latest_message.get('_id')
                        
                        if message_id:
                            # Store this as the "last known" message (no notification)
                            cache['last_message_ids'][room_id] = message_id
                            print(f"[NOTIFY] Initialized tracking for room {room.get('display', room_id)}")
        
        print("[NOTIFY] Message tracking initialized - will now notify for NEW messages only")
        
    except Exception as e:
        print(f"[NOTIFY] Error initializing message tracking: {e}")

def check_for_new_messages():
    """
    Check for new messages and send notifications - runs in background thread
    """
    global cache
    
    # Initialize tracking first (no notifications for existing messages)
    initialize_message_tracking()
    
    # Wait a bit before starting to check for new messages
    time.sleep(45)
    print("[NOTIFY] Starting new message monitoring...")
    
    initialization_complete = True  # Flag to track that initialization is done
    
    while True:
        try:
            config = load_config()
            if not config.get('RCSERVER') or not config.get('RCTOKEN') or not config.get('RCID'):
                time.sleep(30)  # Wait 30 seconds if not configured
                continue
            
            # Get rooms (use cached if available)
            now = time.time()
            if not cache['rooms'] or (now - cache['rooms_time']) > CACHE_DURATION:
                # Refresh rooms cache
                rooms_result = get_rooms_data(config)
                if rooms_result.get('status') == 'success':
                    cache['rooms'] = rooms_result
                    cache['rooms_time'] = now
            
            if cache['rooms'] and cache['rooms'].get('status') == 'success':
                all_rooms = []
                all_rooms.extend(cache['rooms'].get('private_groups', []))
                all_rooms.extend(cache['rooms'].get('direct_messages', []))
                
                for room in all_rooms:
                    room_id = room.get('id')
                    room_name = room.get('display', room.get('name', 'Unknown'))
                    room_type = 'd' if room.get('type') == 'dm' else 'p'
                    
                    if room_id:
                        # Get latest message
                        endpoint = f'im.messages?roomId={room_id}&count=1' if room_type == 'd' else f'groups.messages?roomId={room_id}&count=1'
                        messages_result = make_rocketchat_request(endpoint, config)
                        
                        if messages_result.get('success') and messages_result.get('messages'):
                            latest_message = messages_result['messages'][0]
                            message_id = latest_message.get('_id')
                            message_text = latest_message.get('msg', '')
                            sender = latest_message.get('u', {}).get('username', 'Unknown')
                            
                            # Check if this is a new message
                            last_known_id = cache['last_message_ids'].get(room_id)
                            if last_known_id != message_id and message_id:
                                # New message detected!
                                
                                # Only send notifications AFTER initialization is complete
                                if initialization_complete and last_known_id is not None:
                                    # This is a truly NEW message - update ID and notify
                                    cache['last_message_ids'][room_id] = message_id
                                    
                                    # Don't notify for our own messages
                                    my_username = get_user_info(config).get('username', '')
                                    if sender != my_username:
                                        # Send notification
                                        title = f"🚀 {room_name}"
                                        subtitle = f"{sender}: {message_text[:100]}{'...' if len(message_text) > 100 else ''}"
                                        itemid = f"RocketChat-{room_id}"
                                        
                                        execute_shell_command(title, subtitle, itemid)
                                        print(f"[NOTIFY] New message notification sent for {room_name}")
                                else:
                                    # During initialization or first run - just store the ID
                                    cache['last_message_ids'][room_id] = message_id
            
            time.sleep(10)  # Check every 10 seconds
            
        except Exception as e:
            print(f"[NOTIFY] Error in notification checker: {e}")
            time.sleep(30)  # Wait longer on error

# Start notification checker thread
threading.Thread(target=check_for_new_messages, daemon=True).start()

def get_cached_or_fetch_config():
    """Load configuration with caching (following BB10 standards)"""
    global cache
    now = time.time()
    
    # Use cached config if fresh
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
            print(f"Error loading config: {e}")
    
    # Cache it
    cache['config'] = config
    cache['config_time'] = now
    return config

def load_config():
    """Backward compatibility wrapper"""
    return get_cached_or_fetch_config()

def get_rooms_data(config):
    """Get rooms data for notifications - helper function"""
    if not config.get('RCSERVER') or not config.get('RCTOKEN'):
        return {'status': 'error', 'message': 'Missing config'}
    
    private_groups = []
    direct_messages = []
    
    # Get user info once
    user_info = get_user_info(config)
    my_username = user_info.get('username', '')
    
    # Get private groups
    groups_result = make_rocketchat_request('groups.list?count=20&sort={"lm":-1}', config)
    if groups_result.get('success'):
        for group in groups_result.get('groups', []):
            last_message = group.get('lm', group.get('_updatedAt', ''))
            private_groups.append({
                'id': group.get('_id'),
                'name': group.get('name'),
                'display': f"🔒{group.get('name')}",
                'type': 'private_group',
                'last_activity': last_message
            })
    
    # Get direct messages
    ims_result = make_rocketchat_request('im.list?count=20&sort={"lm":-1}', config)
    if ims_result.get('success'):
        for im in ims_result.get('ims', []):
            room_id = im.get('_id', '')
            username = 'Unknown'
            other_person = 'Unknown'
            
            # Get the other person's name
            usernames = im.get('usernames', [])
            if usernames and len(usernames) >= 2:
                for uname in usernames:
                    if uname != my_username and uname:
                        other_person = uname
                        break
            
            # Get username of who sent the LAST message
            if room_id:
                messages_result = make_rocketchat_request(f'im.messages?roomId={room_id}&count=1', config)
                if messages_result.get('success'):
                    messages = messages_result.get('messages', [])
                    if messages:
                        last_msg = messages[0]
                        last_sender = last_msg.get('u', {}).get('username', '')
                        username = last_sender if last_sender else other_person
                    else:
                        username = other_person
                else:
                    username = other_person
            else:
                username = other_person
            
            # Fallback if still unknown
            if username == 'Unknown' and usernames:
                username = usernames[0] if usernames[0] != my_username else (usernames[1] if len(usernames) > 1 else usernames[0])
            
            last_message = im.get('lm', im.get('_updatedAt', ''))
            display_name = f"@{username}" if username != 'Unknown' else f"@{other_person}"
            
            direct_messages.append({
                'id': im.get('_id'),
                'name': other_person,
                'display': display_name,
                'type': 'dm',
                'last_activity': last_message,
                'last_sender': username
            })
    
    return {
        'status': 'success',
        'private_groups': private_groups,
        'direct_messages': direct_messages,
        'total_private': len(private_groups),
        'total_dms': len(direct_messages)
    }

def make_rocketchat_request(endpoint, config, method='GET', data=None):
    """Make RocketChat API request with proper error handling (BB10 standards)"""
    try:
        print(f"[API] Making request to endpoint: {endpoint}")
        if not config.get('RCSERVER') or not config.get('RCTOKEN') or not config.get('RCID'):
            print(f"[API] Missing config - Server: {bool(config.get('RCSERVER'))}, Token: {bool(config.get('RCTOKEN'))}, ID: {bool(config.get('RCID'))}")
            return {'success': False, 'error': 'Missing configuration'}
        
        url = f"{config['RCSERVER']}/api/v1/{endpoint}"
        headers = {
            'X-Auth-Token': config['RCTOKEN'],
            'X-User-Id': config['RCID'],
            'Content-Type': 'application/json',
            'User-Agent': 'BB10RocketChatNavigator/1.0'
        }
        
        if method == 'POST' and data:
            data = json.dumps(data).encode('utf-8')
        
        req = urllib.request.Request(url, data=data, headers=headers)
        req.get_method = lambda: method
        
        # Optimized SSL context for BB10 performance
        ssl_context = ssl.create_default_context()
        ssl_context.check_hostname = False
        ssl_context.verify_mode = ssl.CERT_NONE
        
        response = urllib.request.urlopen(req, timeout=REQUEST_TIMEOUT, context=ssl_context)
        result = response.read().decode('utf-8')
        json_result = json.loads(result)
        print(f"[API] Success: {endpoint} -> {json_result.get('success', 'unknown')}")
        return json_result
        
    except urllib.error.HTTPError as e:
        print(f"[API] HTTP Error: {endpoint} -> {e.code}: {e.reason}")
        return {'success': False, 'error': f'HTTP {e.code}: {e.reason}'}
    except urllib.error.URLError as e:
        print(f"[API] URL Error: {endpoint} -> {e.reason}")
        return {'success': False, 'error': f'Connection error: {e.reason}'}
    except socket.timeout:
        print(f"[API] Timeout: {endpoint}")
        return {'success': False, 'error': 'Request timeout'}
    except json.JSONDecodeError as e:
        print(f"[API] JSON Error: {endpoint} -> {e}")
        return {'success': False, 'error': f'Invalid JSON response: {e}'}
    except Exception as e:
        print(f"[API] General Error: {endpoint} -> {e}")
        return {'success': False, 'error': str(e)}

def get_user_info(config):
    """Get user information with caching (BB10 standards)"""
    global cache
    now = time.time()
    
    # Use cached user info (cache longer for user info)
    if cache['user_info'] and (now - cache['user_time']) < CONFIG_CACHE_DURATION:
        return cache['user_info']
    
    result = make_rocketchat_request('me', config)
    if result.get('success'):
        user_info = result.get('user', {})
        cache['user_info'] = user_info
        cache['user_time'] = now
        return user_info
    else:
        print(f"Failed to get user info: {result.get('error', 'Unknown error')}")
        return {}

class RocketChatHandler(http.server.BaseHTTPRequestHandler):
    """BB10 RocketChat Navigator HTTP Handler (following BB10 standards)"""
    
    def log_message(self, format, *args):
        """Enable request logging for debugging"""
        print(f"[{time.strftime('%H:%M:%S')}] {format % args}")
    
    def do_GET(self):
        """Handle GET requests with proper routing (BB10 standards)"""
        try:
            parsed_path = urllib.parse.urlparse(self.path)
            config = load_config()
            
            # Check if user is authorized (has config)
            is_authorized = config.get('RCSERVER') and config.get('RCTOKEN') and config.get('RCID')
            
            # Auth flow endpoints
            auth_endpoints = ['/start_auth', '/auth.html', '/favicon.ico']
            
            # If not authorized and not hitting auth endpoints, redirect
            if not is_authorized and parsed_path.path not in auth_endpoints:
                self.send_response(302)
                self.send_header('Location', '/start_auth')
                self.end_headers()
                return
            
            # Route handling following BB10 patterns
            if parsed_path.path == '/':
                self.serve_file('index.html', 'text/html')
            elif parsed_path.path == '/start_auth':
                self.serve_file('auth.html', 'text/html')
            elif parsed_path.path == '/api/status':
                self.handle_status_api(config)
            elif parsed_path.path == '/get_rooms':
                self.handle_rooms_api(config)
            elif parsed_path.path == '/get_messages':
                self.handle_messages_api(config)
            elif parsed_path.path == '/api/config':
                self.handle_config_api(config)
            elif parsed_path.path == '/api/refresh_messages':
                self.handle_refresh_messages_api(config)
            else:
                # Try to serve static file
                filepath = parsed_path.path.lstrip('/')
                full_path = os.path.join(BASE_DIR, filepath)
                if os.path.isfile(full_path):
                    content_type = 'text/html'
                    if filepath.endswith('.css'):
                        content_type = 'text/css'
                    elif filepath.endswith('.js'):
                        content_type = 'application/javascript'
                    self.serve_file(filepath, content_type)
                else:
                    self.send_error(404, 'Not Found')
                
        except Exception as e:
            print(f"GET request error: {e}")
            self.send_error(500, 'Internal Server Error')
    
    def do_POST(self):
        """Handle POST requests with proper routing (BB10 standards)"""
        try:
            parsed_path = urllib.parse.urlparse(self.path)
            config = load_config()
            
            # Route handling following BB10 patterns
            if parsed_path.path == '/send_message':
                self.handle_send_message_api(config)
            elif parsed_path.path == '/api/save_config':
                self.handle_save_config_api(config)
            elif parsed_path.path == '/api/login':
                self.handle_login_api()
            else:
                self.send_error(404, 'Not Found')
                
        except Exception as e:
            print(f"POST request error: {e}")
            self.send_error(500, 'Internal Server Error')
    
    def serve_file(self, file_path, content_type):
        """Serve a file from BASE_DIR"""
        full_path = os.path.join(BASE_DIR, file_path)
        try:
            with open(full_path, 'rb') as f:
                self.send_response(200)
                self.send_header('Content-type', content_type)
                self.end_headers()
                self.wfile.write(f.read())
        except IOError:
            self.send_error(404, f"File not found: {file_path}")
    
    def send_json(self, data, status_code=200):
        """Send JSON response with proper headers (BB10 standards)"""
        try:
            self.send_response(status_code)
            self.send_header('Content-Type', 'application/json; charset=utf-8')
            self.send_header('Cache-Control', 'no-cache, no-store, must-revalidate')
            self.send_header('Pragma', 'no-cache')
            self.send_header('Expires', '0')
            self.send_header('X-Content-Type-Options', 'nosniff')
            self.end_headers()
            
            # Compact JSON for performance (BB10 standard)
            json_str = json.dumps(data, separators=(',', ':'), ensure_ascii=False)
            self.wfile.write(json_str.encode('utf-8'))
            
        except Exception as e:
            print(f"Error sending JSON: {e}")
            try:
                self.send_error(500, 'JSON encoding error')
            except:
                pass
    
    def handle_status_api(self, config):
        """Handle status API request (BB10 standards)"""
        try:
            if not config.get('RCSERVER') or not config.get('RCTOKEN') or not config.get('RCID'):
                self.send_json({
                    'status': 'error', 
                    'connected': False, 
                    'message': 'Configuration incomplete'
                })
                return
            
            # Test connection with a quick API call
            result = make_rocketchat_request('me', config)
            if result.get('success'):
                self.send_json({
                    'status': 'success',
                    'connected': True,
                    'message': 'Connected to RocketChat',
                    'server': config['RCSERVER'],
                    'user': result.get('user', {}).get('username', 'Unknown')
                })
            else:
                self.send_json({
                    'status': 'error',
                    'connected': False,
                    'message': f"Connection failed: {result.get('error', 'Unknown error')}",
                    'server': config['RCSERVER']
                })
                
        except Exception as e:
            print(f"Status API error: {e}")
            self.send_json({
                'status': 'error',
                'connected': False,
                'message': f'Status check failed: {str(e)}'
            })
    
    def handle_rooms_api(self, config):
        """Handle rooms API request with caching (BB10 standards)"""
        global cache
        now = time.time()
        
        # Use cached rooms if fresh
        if cache['rooms'] and (now - cache['rooms_time']) < CACHE_DURATION:
            # Convert to format expected by UI
            rooms = []
            for group in cache['rooms'].get('private_groups', []):
                rooms.append({
                    'id': group['id'],
                    'name': group['display'],
                    'type': 'group'
                })
            for dm in cache['rooms'].get('direct_messages', []):
                rooms.append({
                    'id': dm['id'],
                    'name': dm['display'],
                    'type': 'dm'
                })
            self.send_json(rooms)
            return
        
        if not config.get('RCSERVER') or not config.get('RCTOKEN'):
            self.send_json([])
            return
        
        # Get fresh rooms data
        rooms_result = get_rooms_data(config)
        if rooms_result.get('status') == 'success':
            cache['rooms'] = rooms_result
            cache['rooms_time'] = now
            
            # Convert to format expected by UI
            rooms = []
            for group in rooms_result.get('private_groups', []):
                rooms.append({
                    'id': group['id'],
                    'name': group['display'],
                    'type': 'group'
                })
            for dm in rooms_result.get('direct_messages', []):
                rooms.append({
                    'id': dm['id'],
                    'name': dm['display'],
                    'type': 'dm'
                })
            self.send_json(rooms)
        else:
            self.send_json([])
    
    def handle_messages_api(self, config):
        """Handle messages API request with caching (BB10 standards)"""
        global cache
        
        if not config.get('RCSERVER') or not config.get('RCTOKEN'):
            self.send_json([])
            return
        
        # Parse query parameters
        query = urllib.parse.urlparse(self.path).query
        params = urllib.parse.parse_qs(query)
        chat_id = params.get('chat_id', [''])[0]
        
        if not chat_id:
            self.send_json([])
            return
        
        now = time.time()
        cache_key = f"msg_{chat_id}"
        
        # Use cached messages if fresh
        if (cache_key in cache['messages'] and 
            (now - cache['messages'][cache_key]['time']) < MESSAGE_CACHE_DURATION):
            self.send_json(cache['messages'][cache_key]['data'])
            return
        
        # Determine room type (try both DM and group endpoints)
        # Try DM first
        endpoint = f'im.messages?roomId={chat_id}&count=20'
        messages_result = make_rocketchat_request(endpoint, config)
        
        if not messages_result.get('success'):
            # Try group endpoint
            endpoint = f'groups.messages?roomId={chat_id}&count=20'
            messages_result = make_rocketchat_request(endpoint, config)
        
        if not messages_result.get('success'):
            self.send_json([])
            return
        
        # Get user info for comparison
        user_info = get_user_info(config)
        my_username = user_info.get('username', '')
        
        # Format messages for UI
        formatted_messages = []
        for msg in messages_result.get('messages', []):
            user = msg.get('u', {})
            sender_name = user.get('username', 'Unknown')
            
            # Mark own messages
            if sender_name == my_username:
                sender_name = 'You'
            
            # Format timestamp
            ts = msg.get('ts', {})
            formatted_time = 'Now'
            if isinstance(ts, dict) and '$date' in ts:
                try:
                    timestamp = ts['$date']
                    if isinstance(timestamp, (int, float)):
                        import datetime
                        dt = datetime.datetime.fromtimestamp(timestamp / 1000)
                        formatted_time = dt.strftime('%Y-%m-%d %H:%M:%S')
                except:
                    pass
            
            formatted_messages.append({
                'sender_name': sender_name,
                'message': msg.get('msg', ''),
                'date': formatted_time
            })
        
        # Cache the result
        cache['messages'][cache_key] = {
            'data': formatted_messages,
            'time': now
        }
        
        self.send_json(formatted_messages)
    
    def handle_send_message_api(self, config):
        """Handle send message API request (BB10 standards)"""
        if not config.get('RCSERVER') or not config.get('RCTOKEN'):
            self.send_json({'status': 'error', 'message': 'Missing config'})
            return
        
        try:
            content_length = int(self.headers.get('Content-Length', 0))
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode('utf-8'))
            
            chat_id = data.get('chat_id')
            message_text = data.get('message')
            
            if not chat_id or not message_text:
                self.send_json({'status': 'error', 'message': 'Missing chat_id or message'})
                return
            
            # Use the unified chat.postMessage endpoint (works for all room types)
            send_data = {'roomId': chat_id, 'text': message_text}
            result = make_rocketchat_request('chat.postMessage', config, method='POST', data=send_data)
            
            print(f"[SEND] Message send result: {result}")
            
            if result.get('success'):
                # Clear message cache for this room to force refresh
                cache_key = f"msg_{chat_id}"
                if cache_key in cache['messages']:
                    del cache['messages'][cache_key]
                
                self.send_json({'status': 'Message sent'})
            else:
                error_msg = result.get('error', 'Unknown error')
                print(f"[SEND] Failed to send message: {error_msg}")
                self.send_json({'status': 'error', 'message': error_msg})
                
        except Exception as e:
            print(f"[SEND] Exception in send message: {e}")
            import traceback
            traceback.print_exc()
            self.send_json({'status': 'error', 'message': str(e)})
    
    def handle_config_api(self, config):
        """API: Get current configuration (non-sensitive data only)"""
        try:
            safe_config = {}
            # Only return non-sensitive config
            if config.get('RCSERVER'):
                safe_config['RCSERVER'] = config['RCSERVER']
            
            self.send_json(safe_config)
        except Exception as e:
            self.send_json({'status': 'error', 'message': str(e)})
    
    def handle_refresh_messages_api(self, config):
        """API: Force refresh messages for a specific room (bypasses cache)"""
        global cache
        
        if not config.get('RCSERVER') or not config.get('RCTOKEN'):
            self.send_json({'status': 'error', 'message': 'Missing config'})
            return
        
        # Parse query parameters
        query = urllib.parse.urlparse(self.path).query
        params = urllib.parse.parse_qs(query)
        chat_id = params.get('chat_id', [''])[0]
        
        if not chat_id:
            self.send_json({'status': 'error', 'message': 'Missing chat_id'})
            return
        
        try:
            # Clear cache for this specific room to force fresh data
            cache_key = f"msg_{chat_id}"
            if cache_key in cache['messages']:
                del cache['messages'][cache_key]
            
            # Try DM endpoint first
            endpoint = f'im.messages?roomId={chat_id}&count=20'
            messages_result = make_rocketchat_request(endpoint, config)
            
            if not messages_result.get('success'):
                # Try group endpoint
                endpoint = f'groups.messages?roomId={chat_id}&count=20'
                messages_result = make_rocketchat_request(endpoint, config)
            
            if not messages_result.get('success'):
                self.send_json({'status': 'error', 'message': 'Failed to fetch messages'})
                return
            
            # Get user info for comparison
            user_info = get_user_info(config)
            my_username = user_info.get('username', '')
            
            # Format messages for UI (same as handle_messages_api)
            formatted_messages = []
            for msg in messages_result.get('messages', []):
                user = msg.get('u', {})
                sender_name = user.get('username', 'Unknown')
                
                if sender_name == my_username:
                    sender_name = 'You'
                
                # Format timestamp
                ts = msg.get('ts', {})
                formatted_time = 'Now'
                if isinstance(ts, dict) and '$date' in ts:
                    try:
                        timestamp = ts['$date']
                        if isinstance(timestamp, (int, float)):
                            import datetime
                            dt = datetime.datetime.fromtimestamp(timestamp / 1000)
                            formatted_time = dt.strftime('%Y-%m-%d %H:%M:%S')
                    except:
                        pass
                
                formatted_messages.append({
                    'sender_name': sender_name,
                    'message': msg.get('msg', ''),
                    'date': formatted_time
                })
            
            # Cache the fresh result
            now = time.time()
            cache['messages'][cache_key] = {
                'data': formatted_messages,
                'time': now
            }
            
            self.send_json({
                'status': 'success',
                'message_count': len(formatted_messages),
                'messages': formatted_messages
            })
            
        except Exception as e:
            print(f"Refresh messages error: {e}")
            self.send_json({'status': 'error', 'message': str(e)})
    
    def handle_save_config_api(self, config):
        """API: Save configuration to .env file"""
        try:
            content_length = int(self.headers.get('Content-Length', 0))
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode('utf-8'))
            
            # Update config
            allowed_keys = ['RCSERVER', 'RCTOKEN', 'RCID']
            updated = False
            
            existing_config = load_config()
            
            for key, value in data.items():
                if key in allowed_keys:
                    clean_value = str(value).strip()
                    if clean_value:
                        existing_config[key] = clean_value
                        updated = True
            
            if not updated:
                self.send_json({
                    'status': 'error',
                    'message': 'No valid configuration provided'
                })
                return
            
            # Write configuration to .env file
            try:
                with open(CONFIG_FILE_PATH, 'w') as f:
                    f.write("# RocketChat Configuration for BB10 Navigator\n")
                    f.write(f"# Generated: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
                    f.write("\n")
                    
                    for key in ['RCSERVER', 'RCTOKEN', 'RCID']:
                        if key in existing_config:
                            f.write(f"{key}={existing_config[key]}\n")
                
                print(f"Configuration saved to {CONFIG_FILE_PATH}")
                
            except Exception as e:
                self.send_json({
                    'status': 'error',
                    'message': f'Failed to write config file: {str(e)}'
                })
                return
            
            # Clear all caches
            global cache
            cache['config'] = None
            cache['config_time'] = 0
            cache['rooms'] = None
            cache['rooms_time'] = 0
            cache['user_info'] = None
            cache['user_time'] = 0
            cache['messages'] = {}
            
            self.send_json({
                'status': 'success',
                'message': 'Configuration saved successfully!'
            })
            
        except json.JSONDecodeError:
            self.send_json({
                'status': 'error',
                'message': 'Invalid JSON data received'
            })
        except Exception as e:
            print(f"Save config error: {e}")
            self.send_json({
                'status': 'error',
                'message': f'Configuration save failed: {str(e)}'
            })
    
    def handle_login_api(self):
        """API: Login with username/password and automatically save tokens"""
        try:
            content_length = int(self.headers.get('Content-Length', 0))
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode('utf-8'))
            
            server_url = data.get('server_url', '').strip()
            username = data.get('username', '').strip()
            password = data.get('password', '').strip()
            
            if not server_url or not username or not password:
                self.send_json({
                    'status': 'error',
                    'message': 'Server URL, username, and password are required'
                })
                return
            
            # Ensure server URL has proper format
            if not server_url.startswith('http'):
                server_url = 'https://' + server_url
            
            print(f"[LOGIN] Attempting login to {server_url} with username: {username}")
            
            # Perform RocketChat login
            login_result = self.rocketchat_login(server_url, username, password)
            
            if login_result.get('success'):
                # Extract tokens from login response
                auth_token = login_result.get('data', {}).get('authToken')
                user_id = login_result.get('data', {}).get('userId')
                
                if not auth_token or not user_id:
                    self.send_json({
                        'status': 'error',
                        'message': 'Login succeeded but failed to get tokens from response'
                    })
                    return
                
                print(f"[LOGIN] Login successful!")
                
                # Save configuration automatically
                config_data = {
                    'RCSERVER': server_url,
                    'RCTOKEN': auth_token,
                    'RCID': user_id
                }
                
                # Save to .env file
                try:
                    with open(CONFIG_FILE_PATH, 'w') as f:
                        f.write("# RocketChat Configuration - Auto-generated from login\n")
                        f.write(f"# Generated: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
                        f.write("\n")
                        f.write(f"RCSERVER={server_url}\n")
                        f.write(f"RCTOKEN={auth_token}\n")
                        f.write(f"RCID={user_id}\n")
                    
                    print(f"[LOGIN] Configuration saved to {CONFIG_FILE_PATH}")
                    
                    # Clear caches
                    global cache
                    cache['config'] = None
                    cache['config_time'] = 0
                    cache['rooms'] = None
                    cache['rooms_time'] = 0
                    cache['user_info'] = None
                    cache['user_time'] = 0
                    cache['messages'] = {}
                    
                    self.send_json({
                        'next': '/'
                    })
                    
                except Exception as e:
                    print(f"[LOGIN] Error saving config: {e}")
                    self.send_json({
                        'status': 'error',
                        'message': f'Login successful but failed to save configuration: {str(e)}'
                    })
            else:
                error_msg = login_result.get('error', 'Unknown login error')
                print(f"[LOGIN] Login failed: {error_msg}")
                self.send_json({
                    'status': 'error',
                    'message': f'Login failed: {error_msg}'
                })
                
        except json.JSONDecodeError:
            self.send_json({
                'status': 'error',
                'message': 'Invalid JSON data received'
            })
        except Exception as e:
            print(f"[LOGIN] Login API error: {e}")
            self.send_json({
                'status': 'error',
                'message': f'Login request failed: {str(e)}'
            })
    
    def rocketchat_login(self, server_url, username, password):
        """Perform RocketChat login and return auth tokens"""
        try:
            login_url = f"{server_url}/api/v1/login"
            
            # Prepare login data
            login_data = {
                'user': username,
                'password': password
            }
            
            # Create request
            data = json.dumps(login_data).encode('utf-8')
            headers = {
                'Content-Type': 'application/json',
                'User-Agent': 'BB10RocketChatNavigator/1.0'
            }
            
            req = urllib.request.Request(login_url, data=data, headers=headers)
            req.get_method = lambda: 'POST'
            
            # SSL context for BB10 compatibility
            ssl_context = ssl.create_default_context()
            ssl_context.check_hostname = False
            ssl_context.verify_mode = ssl.CERT_NONE
            
            # Make request
            response = urllib.request.urlopen(req, timeout=REQUEST_TIMEOUT, context=ssl_context)
            result = response.read().decode('utf-8')
            json_result = json.loads(result)
            
            print(f"[LOGIN] RocketChat login response: success={json_result.get('success')}")
            return json_result
            
        except urllib.error.HTTPError as e:
            error_body = e.read().decode('utf-8') if e.fp else 'No error details'
            try:
                error_json = json.loads(error_body)
                error_msg = error_json.get('error', error_json.get('message', f'HTTP {e.code}'))
            except:
                error_msg = f'HTTP {e.code}: {e.reason}'
            
            print(f"[LOGIN] HTTP Error: {e.code} - {error_msg}")
            return {'success': False, 'error': error_msg}
            
        except urllib.error.URLError as e:
            print(f"[LOGIN] URL Error: {e.reason}")
            return {'success': False, 'error': f'Connection error: {e.reason}'}
            
        except socket.timeout:
            print(f"[LOGIN] Timeout during login")
            return {'success': False, 'error': 'Login request timeout'}
            
        except json.JSONDecodeError as e:
            print(f"[LOGIN] JSON decode error: {e}")
            return {'success': False, 'error': 'Invalid response from server'}
            
        except Exception as e:
            print(f"[LOGIN] General error: {e}")
            return {'success': False, 'error': str(e)}

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    """Threaded TCP Server for BB10 applications (following BB10 standards)"""
    allow_reuse_address = True
    daemon_threads = True
    timeout = 30

def run_server(port=PORT):
    """Run the BB10 RocketChat Navigator server (BB10 standards)"""
    try:
        config = load_config()
        
        print("=" * 60)
        print("BB10 RocketChat Navigator")
        print("=" * 60)
        print(f"Port: {port}")
        print(f"Server: {config.get('RCSERVER', 'Not configured')}")
        print(f"Base Directory: {BASE_DIR}")
        print("")
        print("Features:")
        print("- Optimized caching system")
        print("- BB10 compatible UI/UX")
        print("- Real-time messaging")
        print("- Private groups & DMs")
        print("")
        print(f"🚀 Starting server on http://localhost:{port}")
        print("📱 Optimized for BlackBerry Passport")
        print("⏹️  Press Ctrl+C to stop")
        print("=" * 60)
        
        with ThreadedTCPServer(("", port), RocketChatHandler) as httpd:
            httpd.serve_forever()
            
    except KeyboardInterrupt:
        print("\n" + "=" * 60)
        print("👋 Shutting down BB10 RocketChat Navigator")
        print("=" * 60)
    except Exception as e:
        print(f"❌ Server error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    run_server()
