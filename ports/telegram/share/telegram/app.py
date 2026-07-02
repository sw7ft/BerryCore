import http.server
import socketserver
import json
import urllib.parse
import os
import asyncio
import subprocess
import tempfile
import threading
import cgi
import io
import shutil

import requests  # <-- Using requests now

from telethon import TelegramClient
from telethon.errors import SessionPasswordNeededError
from telethon.sessions import SQLiteSession

# --------------------------------------------
#     FETCH TELEGRAM KEYS FROM REMOTE
# --------------------------------------------
API_ID = None
API_HASH = None

# URL to your text file containing lines like:
#   API_ID = 26728096
#   API_HASH = 'c6b92f27cd5e5882aeb9aa367e09d049'
REMOTE_KEYS_URL = "https://berrystore.sw7ft.com/keys/telegram.txt"

try:
    resp = requests.get(REMOTE_KEYS_URL)
    resp.raise_for_status()  # Raises an exception for 4xx/5xx errors
    content = resp.text
    
    for line in content.splitlines():
        line = line.strip()
        if line.startswith("API_ID"):
            # Example line:  API_ID = 26728096
            parts = line.split("=", 1)
            API_ID = int(parts[1].strip())
        elif line.startswith("API_HASH"):
            # Example line:  API_HASH = 'c6b92f27cd5e5882aeb9aa367e09d049'
            parts = line.split("=", 1)
            raw = parts[1].strip()      # "'c6b92f27cd5e5882aeb9aa367e09d049'"
            raw = raw.strip("'\"")      # remove surrounding quotes
            API_HASH = raw
except Exception as e:
    print("Failed to retrieve or parse Telegram keys from remote text file:")
    print(e)
    import sys
    sys.exit(1)

# --------------------------------------------
#     TELETHON + PATH CONFIG
# --------------------------------------------

# Use an absolute base directory reference so we can safely load files
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# Store the session file in the same directory as this script
SESSION_FILE_PATH = os.path.join(BASE_DIR, "session_name.session")

# Create a directory for downloaded media (photos, videos, etc.)
MEDIA_DIR = os.path.join(BASE_DIR, "media_cache")
if not os.path.exists(MEDIA_DIR):
    os.makedirs(MEDIA_DIR)

# Downloads directory for APK files and documents
DOWNLOADS_DIR = "/accounts/1000/shared/downloads"
if not os.path.exists(DOWNLOADS_DIR):
    try:
        os.makedirs(DOWNLOADS_DIR)
    except:
        # If we can't create it, fall back to local directory
        DOWNLOADS_DIR = os.path.join(BASE_DIR, "downloads")
        if not os.path.exists(DOWNLOADS_DIR):
            os.makedirs(DOWNLOADS_DIR)

# Initialize Telethon client with a file-based session
client = TelegramClient(
    session=SQLiteSession(SESSION_FILE_PATH),
    api_id=API_ID,
    api_hash=API_HASH
)

# Globals for phone login
phone_number = None
phone_code_hash = None
notification_thread_started = False

PORT = 8010

# Caching system (similar to RocketChat)
CACHE_DURATION = 30  # 30 seconds cache for rooms
MESSAGE_CACHE_DURATION = 15  # 15 seconds cache for messages

# Global cache to speed things up
cache = {
    'rooms': None,
    'rooms_time': 0,
    'messages': {},  # chat_id -> {messages, time, oldest_id}
    'last_message_ids': {}  # chat_id -> last_message_id (for notification tracking)
}

import time

def execute_shell_command(title, subtitle, itemid="TelegramApp"):
    """
    Executes the shell command to send a BB10 PPS notification.
    
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

async def initialize_message_tracking(notify_client):
    """
    Initialize message tracking with current latest messages - no notifications sent
    """
    global cache
    
    try:
        if not notify_client.is_connected():
            await notify_client.connect()
        
        # Only initialize if user is authorized
        if not await notify_client.is_user_authorized():
            print("[NOTIFY] User not authorized yet, skipping initialization")
            return
        
        print("[NOTIFY] Initializing message tracking...")
        
        # Get current dialogs
        async for dialog in notify_client.iter_dialogs(limit=20):
            chat_id = dialog.id
            
            try:
                # Get latest message ID (but don't send notification)
                messages = await notify_client.get_messages(chat_id, limit=1)
                if messages and len(messages) > 0:
                    latest_message = messages[0]
                    message_id = latest_message.id
                    
                    if message_id:
                        # Store this as the "last known" message (no notification)
                        cache['last_message_ids'][chat_id] = message_id
                        print(f"[NOTIFY] Initialized tracking for {dialog.name}")
            except Exception as e:
                print(f"[NOTIFY] Error initializing chat {dialog.name}: {e}")
        
        print("[NOTIFY] Message tracking initialized - will now notify for NEW messages only")
        
    except Exception as e:
        print(f"[NOTIFY] Error initializing message tracking: {e}")

def start_notification_thread():
    """Start the notification checker thread (call this after login)"""
    global notification_thread_started
    if not notification_thread_started:
        notification_thread_started = True
        threading.Thread(target=notification_checker_thread, daemon=True).start()
        print("[NOTIFY] Notification thread started")

def notification_checker_thread():
    """
    Background thread that checks for new messages and sends BB10 notifications
    """
    global cache
    
    # Create a new event loop for this thread
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    
    # Create a separate Telegram client for this thread (thread-safe approach)
    notify_client = TelegramClient(
        SQLiteSession(SESSION_FILE),
        API_ID,
        API_HASH
    )
    
    # Wait for app to initialize
    time.sleep(5)
    
    # Initialize tracking in async context
    loop.run_until_complete(initialize_message_tracking(notify_client))
    
    # Wait a bit before starting to check for new messages
    time.sleep(30)
    print("[NOTIFY] Starting new message monitoring...")
    
    initialization_complete = True  # Flag to track that initialization is done
    
    while True:
        try:
            if not notify_client.is_connected():
                loop.run_until_complete(notify_client.connect())
            
            # Check if user is authorized
            if not loop.run_until_complete(notify_client.is_user_authorized()):
                time.sleep(30)
                continue
            
            # Get my user ID
            me = loop.run_until_complete(notify_client.get_me())
            my_id = me.id if me else None
            
            async def check_dialogs():
                async for dialog in notify_client.iter_dialogs(limit=20):
                    chat_id = dialog.id
                    chat_name = dialog.name
                    
                    try:
                        # Get latest message
                        messages = await notify_client.get_messages(chat_id, limit=1)
                        
                        if messages and len(messages) > 0:
                            latest_message = messages[0]
                            message_id = latest_message.id
                            message_text = latest_message.message if latest_message.message else "[Media]"
                            sender_id = latest_message.sender_id
                            
                            # Check if this is a new message
                            last_known_id = cache['last_message_ids'].get(chat_id)
                            if last_known_id != message_id and message_id:
                                # New message detected!
                                
                                # Only send notifications AFTER initialization is complete
                                if initialization_complete and last_known_id is not None:
                                    # This is a truly NEW message - update ID and notify
                                    cache['last_message_ids'][chat_id] = message_id
                                    
                                    # Don't notify for our own messages
                                    if sender_id != my_id:
                                        # Get sender name
                                        sender_name = "Unknown"
                                        try:
                                            sender_entity = await notify_client.get_entity(sender_id)
                                            sender_name = (
                                                getattr(sender_entity, 'username', None) or
                                                getattr(sender_entity, 'first_name', 'Unknown')
                                            )
                                        except:
                                            pass
                                        
                                        # Send notification
                                        title = f"📱 {chat_name}"
                                        subtitle = f"{sender_name}: {message_text[:100]}{'...' if len(message_text) > 100 else ''}"
                                        itemid = f"Telegram-{chat_id}"
                                        
                                        execute_shell_command(title, subtitle, itemid)
                                        print(f"[NOTIFY] New message notification sent for {chat_name}")
                                else:
                                    # During initialization or first run - just store the ID
                                    cache['last_message_ids'][chat_id] = message_id
                    except Exception as e:
                        print(f"[NOTIFY] Error checking chat {chat_name}: {e}")
            
            loop.run_until_complete(check_dialogs())
            time.sleep(10)  # Check every 10 seconds
            
        except Exception as e:
            print(f"[NOTIFY] Error in notification checker: {e}")
            time.sleep(30)  # Wait longer on error

class MyHttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        """Handle all GET requests (serving HTML, checking session, listing rooms, etc.)."""
        global cache  # Declare global at the start of the method
        parsed_path = urllib.parse.urlparse(self.path)

        # Before routing, ensure we can write to the session file (or remove an unusable one).
        self._ensure_session_writable()

        # We use asyncio to check "is_user_authorized()" properly
        loop = asyncio.get_event_loop()
        is_authorized = loop.run_until_complete(self._is_user_authorized())

        # If not authorized and not hitting the auth flow endpoints, redirect to /start_auth
        auth_endpoints = ['/start_auth', '/enter_code', '/auth.html', '/auth_code.html', '/favicon.ico']
        if not is_authorized and parsed_path.path not in auth_endpoints:
            self.send_response(302)
            self.send_header('Location', '/start_auth')
            self.end_headers()
            return

        # Normal routing
        if parsed_path.path == '/':
            # Serve main index (the chat UI)
            self.serve_file('index.html', 'text/html')

        elif parsed_path.path == '/start_auth':
            # Serve the phone number input page
            self.serve_file('auth.html', 'text/html')

        elif parsed_path.path == '/enter_code':
            # Serve the code input page
            self.serve_file('auth_code.html', 'text/html')

        elif parsed_path.path == '/get_rooms':
            # Return the list of rooms/chats as JSON with caching
            now = time.time()
            
            # Use cached rooms if fresh
            if cache['rooms'] and (now - cache['rooms_time']) < CACHE_DURATION:
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(cache['rooms']).encode('utf-8'))
            else:
                loop = asyncio.get_event_loop()
                response = loop.run_until_complete(self.get_rooms())
                cache['rooms'] = response
                cache['rooms_time'] = now
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(response).encode('utf-8'))

        elif parsed_path.path == '/get_messages':
            query = urllib.parse.parse_qs(parsed_path.query)
            chat_id = query.get('chat_id', [None])[0]
            offset_id = query.get('offset_id', [None])[0]  # For loading older messages
            
            if chat_id:
                now = time.time()
                cache_key = f"msg_{chat_id}"
                
                # If offset_id is provided, we're loading older messages (bypass cache)
                if offset_id:
                    loop = asyncio.get_event_loop()
                    response = loop.run_until_complete(self.get_messages(int(chat_id), int(offset_id)))
                    self.send_response(200)
                    self.send_header('Content-type', 'application/json')
                    self.end_headers()
                    self.wfile.write(json.dumps(response).encode('utf-8'))
                # Use cached messages if fresh and no offset
                elif cache_key in cache['messages'] and (now - cache['messages'][cache_key]['time']) < MESSAGE_CACHE_DURATION:
                    self.send_response(200)
                    self.send_header('Content-type', 'application/json')
                    self.end_headers()
                    self.wfile.write(json.dumps(cache['messages'][cache_key]['data']).encode('utf-8'))
                else:
                    loop = asyncio.get_event_loop()
                    response = loop.run_until_complete(self.get_messages(int(chat_id)))
                    cache['messages'][cache_key] = {
                        'data': response,
                        'time': now
                    }
                    self.send_response(200)
                    self.send_header('Content-type', 'application/json')
                    self.end_headers()
                    self.wfile.write(json.dumps(response).encode('utf-8'))
            else:
                self.send_error(400, "chat_id is required")

        elif parsed_path.path.startswith('/media/'):
            # Serve downloaded media files (photos, videos)
            filename = parsed_path.path.replace('/media/', '')
            media_path = os.path.join(MEDIA_DIR, filename)
            
            if os.path.isfile(media_path):
                # Determine content type based on extension
                if filename.lower().endswith(('.jpg', '.jpeg')):
                    content_type = 'image/jpeg'
                elif filename.lower().endswith('.png'):
                    content_type = 'image/png'
                elif filename.lower().endswith('.gif'):
                    content_type = 'image/gif'
                elif filename.lower().endswith('.webp'):
                    content_type = 'image/webp'
                else:
                    content_type = 'application/octet-stream'
                
                try:
                    with open(media_path, 'rb') as f:
                        self.send_response(200)
                        self.send_header('Content-type', content_type)
                        self.send_header('Cache-Control', 'public, max-age=86400')  # Cache for 1 day
                        self.end_headers()
                        self.wfile.write(f.read())
                except IOError:
                    self.send_error(404, f"Media file not found: {filename}")
            else:
                self.send_error(404, f"Media file not found: {filename}")

        elif parsed_path.path == '/download_document':
            # Download a document (APK, PDF, etc.) from Telegram in background
            query = urllib.parse.parse_qs(parsed_path.query)
            chat_id = query.get('chat_id', [None])[0]
            message_id = query.get('message_id', [None])[0]
            
            if not chat_id or not message_id:
                self.send_error(400, "chat_id and message_id are required")
                return
            
            try:
                # Start download in background thread
                download_thread = threading.Thread(
                    target=self.background_download_document,
                    args=(int(chat_id), int(message_id)),
                    daemon=True
                )
                download_thread.start()
                
                # Return immediately so user can continue using the app
                result = {
                    'status': 'started',
                    'message': 'Download started in background. File will be saved to /accounts/1000/shared/downloads/'
                }
                
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(result).encode('utf-8'))
            except Exception as e:
                print(f"[ERROR] Failed to start download: {e}")
                self.send_error(500, f"Download failed: {str(e)}")

        else:
            # Attempt to serve a static file or 404
            filepath = parsed_path.path.lstrip('/')
            full_path = os.path.join(BASE_DIR, filepath)
            if os.path.isfile(full_path):
                self.serve_file(filepath, 'text/html')
            else:
                self.send_error(404, "Page not found")

    def do_POST(self):
        """Handle all POST requests (/send_code, /validate_code, /send_message, etc.)."""
        global cache  # Declare global at the start of the method
        parsed_path = urllib.parse.urlparse(self.path)

        if parsed_path.path == '/send_code':
            # Step 1: Request code from Telegram
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data)

            global phone_number, phone_code_hash
            phone_number = data.get('phone_number')
            if not phone_number:
                self.send_error(400, "phone_number is required")
                return

            loop = asyncio.get_event_loop()
            result = loop.run_until_complete(self.send_code_request(phone_number))
            if result.get('status') == 'ok':
                # Move on to enter_code page
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps({'next': '/enter_code'}).encode('utf-8'))
            else:
                # Error from Telethon or invalid phone number
                self.send_error(400, result.get('error', 'Unknown error'))

        elif parsed_path.path == '/validate_code':
            # Step 2: Validate code, sign in
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data)

            code = data.get('code')
            if not code:
                self.send_error(400, "code is required")
                return

            loop = asyncio.get_event_loop()
            result = loop.run_until_complete(self.validate_code(code))
            if result.get('status') == 'authorized':
                # Start notification thread after successful login
                start_notification_thread()
                
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps({'next': '/'}).encode('utf-8'))
            else:
                self.send_error(400, result.get('error', 'Authorization failed'))

        elif parsed_path.path == '/send_message':
            # Send a message to a specific chat
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data)

            chat_id = data.get('chat_id')
            message = data.get('message')
            if not chat_id or not message:
                self.send_error(400, "chat_id and message are required")
                return

            loop = asyncio.get_event_loop()
            response = loop.run_until_complete(self.send_message(int(chat_id), message))
            
            # Clear message cache for this room to force refresh
            cache_key = f"msg_{chat_id}"
            if cache_key in cache['messages']:
                del cache['messages'][cache_key]
            
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(response).encode('utf-8'))

        elif parsed_path.path == '/send_attachment':
            # Handle file upload with multipart/form-data
            content_type = self.headers.get('Content-Type', '')
            
            if 'multipart/form-data' not in content_type:
                self.send_error(400, "Content-Type must be multipart/form-data")
                return
            
            try:
                # Parse multipart form data
                form = cgi.FieldStorage(
                    fp=self.rfile,
                    headers=self.headers,
                    environ={
                        'REQUEST_METHOD': 'POST',
                        'CONTENT_TYPE': self.headers['Content-Type'],
                    }
                )
                
                # Extract chat_id, caption, and file
                chat_id = form.getvalue('chat_id')
                caption = form.getvalue('caption', '')
                
                if not chat_id:
                    self.send_error(400, "chat_id is required")
                    return
                
                # Get the uploaded file
                if 'file' not in form:
                    self.send_error(400, "No file uploaded")
                    return
                
                fileitem = form['file']
                
                if not fileitem.file:
                    self.send_error(400, "Invalid file")
                    return
                
                # Create a temporary file to store the upload
                temp_dir = tempfile.gettempdir()
                filename = os.path.basename(fileitem.filename)
                # Sanitize filename
                filename = "".join(c for c in filename if c.isalnum() or c in (' ', '.', '_', '-'))
                temp_path = os.path.join(temp_dir, f"telegram_upload_{os.getpid()}_{filename}")
                
                # Write uploaded file to temporary location
                with open(temp_path, 'wb') as f:
                    shutil.copyfileobj(fileitem.file, f)
                
                print(f"[ATTACHMENT] File saved temporarily: {temp_path} ({os.path.getsize(temp_path)} bytes)")
                
                # Send via Telethon
                loop = asyncio.get_event_loop()
                response = loop.run_until_complete(
                    self.send_file_attachment(int(chat_id), temp_path, caption if caption else None)
                )
                
                # Clean up temporary file
                try:
                    os.remove(temp_path)
                    print(f"[ATTACHMENT] Cleaned up temp file: {temp_path}")
                except:
                    pass
                
                # Clear message cache for this room to force refresh
                cache_key = f"msg_{chat_id}"
                if cache_key in cache['messages']:
                    del cache['messages'][cache_key]
                
                # Send success response
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(response).encode('utf-8'))
                
            except Exception as e:
                print(f"[ERROR] Attachment upload error: {e}")
                self.send_error(500, f"Upload failed: {str(e)}")

        else:
            self.send_error(404, "Unsupported POST endpoint")

    def serve_file(self, file_path, content_type):
        """Serve a file (HTML, JS, etc.) from the BASE_DIR with the specified content type."""
        full_path = os.path.join(BASE_DIR, file_path)
        try:
            with open(full_path, 'rb') as f:
                self.send_response(200)
                self.send_header('Content-type', content_type)
                self.end_headers()
                self.wfile.write(f.read())
        except IOError:
            self.send_error(404, f"File not found: {file_path}")

    # ----------------------------------------------------------------------
    #    ASYNC HELPER METHODS
    # ----------------------------------------------------------------------
    async def _is_user_authorized(self):
        """Check if Telegram client has a valid, logged-in session."""
        try:
            if not client.is_connected():
                await client.connect()
            return await client.is_user_authorized()
        except Exception as e:
            print(f"[ERROR] Authorization check failed: {e}")
            return False

    async def send_code_request(self, phone_number):
        """Ask Telegram to send a code to this phone number."""
        global phone_code_hash
        try:
            if not client.is_connected():
                await client.connect()
            # If already authorized, sign out first to re-initiate a new flow
            if await client.is_user_authorized():
                await client.log_out()

            result = await client.send_code_request(phone_number)
            phone_code_hash = result.phone_code_hash
            return {'status': 'ok'}
        except Exception as e:
            return {'status': 'error', 'error': str(e)}

    async def validate_code(self, code):
        """Validate the received code and sign into Telegram."""
        global phone_number, phone_code_hash
        try:
            if not client.is_connected():
                await client.connect()

            await client.sign_in(phone_number, code, phone_code_hash=phone_code_hash)
            return {'status': 'authorized'}
        except SessionPasswordNeededError:
            # If the account has 2FA enabled, you'd need to handle `client.sign_in(password=...)`
            return {'status': 'error', 'error': '2FA password needed (not implemented)'}
        except Exception as e:
            return {'status': 'error', 'error': str(e)}

    async def get_rooms(self):
        """Get a list of the user's chats."""
        try:
            if not client.is_connected():
                await client.connect()
            dialogs = []
            async for dialog in client.iter_dialogs():
                dialogs.append({'name': dialog.name, 'id': dialog.id})
            return dialogs
        except Exception as e:
            print(f"[ERROR] Failed to get rooms: {e}")
            return []

    async def get_messages(self, chat_id, offset_id=None):
        """Fetch messages from a chat with pagination support."""
        try:
            if not client.is_connected():
                await client.connect()

            # Fetch 50 messages instead of 10 for better experience
            # If offset_id is provided, fetch messages older than that ID
            if offset_id:
                messages = await client.get_messages(chat_id, limit=50, max_id=offset_id)
            else:
                messages = await client.get_messages(chat_id, limit=50)
            
            output = []
            me = await client.get_me()
            my_id = me.id if me else None
            
            for msg in messages:
                # Skip if neither text nor media
                if not msg.message and not msg.media:
                    continue
                    
                sender_entity = None
                sender_name = 'Unknown'
                
                if msg.sender_id:
                    try:
                        if msg.sender_id == my_id:
                            sender_name = 'You'
                        else:
                            sender_entity = await client.get_entity(msg.sender_id)
                            sender_name = (
                                getattr(sender_entity, 'username', None) or
                                getattr(sender_entity, 'first_name', 'Unknown')
                            )
                    except Exception as e:
                        print(f"[ERROR] Error getting sender entity: {e}")
                        sender_name = 'Unknown'
                
                # Check for media (photo, video, document)
                media_type = None
                media_path = None
                
                if msg.media:
                    try:
                        # Check if it's a photo
                        if hasattr(msg.media, 'photo'):
                            media_type = 'photo'
                            # Download photo to media cache
                            filename = f"photo_{chat_id}_{msg.id}.jpg"
                            media_path = os.path.join(MEDIA_DIR, filename)
                            
                            # Only download if not already cached
                            if not os.path.exists(media_path):
                                await client.download_media(msg.media, media_path)
                                print(f"[MEDIA] Downloaded photo: {filename}")
                            
                            # Return relative path for frontend
                            media_path = f"/media/{filename}"
                        
                        # Check if it's a document (could be video, file, etc.)
                        elif hasattr(msg.media, 'document'):
                            doc = msg.media.document
                            mime_type = doc.mime_type if hasattr(doc, 'mime_type') else ''
                            
                            # Get document filename from attributes
                            doc_filename = None
                            doc_size = doc.size if hasattr(doc, 'size') else 0
                            if hasattr(doc, 'attributes'):
                                for attr in doc.attributes:
                                    if hasattr(attr, 'file_name'):
                                        doc_filename = attr.file_name
                                        break
                            
                            # Handle images sent as documents
                            if mime_type.startswith('image/'):
                                media_type = 'photo'
                                ext = mime_type.split('/')[-1]
                                filename = f"photo_{chat_id}_{msg.id}.{ext}"
                                media_path = os.path.join(MEDIA_DIR, filename)
                                
                                if not os.path.exists(media_path):
                                    await client.download_media(msg.media, media_path)
                                    print(f"[MEDIA] Downloaded image document: {filename}")
                                
                                media_path = f"/media/{filename}"
                            else:
                                # Other document types (APK, PDF, ZIP, etc.)
                                media_type = 'document'
                                # Store document info for download button
                                media_path = {
                                    'filename': doc_filename or f"file_{msg.id}",
                                    'size': doc_size,
                                    'mime_type': mime_type,
                                    'message_id': msg.id,
                                    'chat_id': chat_id
                                }
                    
                    except Exception as e:
                        print(f"[ERROR] Failed to process media for message {msg.id}: {e}")
                
                output.append({
                    'id': msg.id,  # Include message ID for pagination
                    'sender_name': sender_name,
                    'message': msg.message or '',  # Empty string if no text
                    'date': str(msg.date),
                    'media_type': media_type,
                    'media_path': media_path
                })
            
            return output
            
        except Exception as e:
            print(f"[ERROR] Failed to get messages for chat {chat_id}: {e}")
            return []

    async def send_message(self, chat_id, message):
        """Send a text message to the given chat ID."""
        try:
            if not client.is_connected():
                await client.connect()
            await client.send_message(chat_id, message)
            return {'status': 'Message sent'}
        except Exception as e:
            print(f"[ERROR] Failed to send message to {chat_id}: {e}")
            return {'status': 'error', 'message': str(e)}

    async def send_file_attachment(self, chat_id, file_path, caption=None):
        """Send a file attachment to a Telegram chat."""
        try:
            if not client.is_connected():
                await client.connect()
            
            # Telethon's send_file method handles all file types automatically
            await client.send_file(
                chat_id,
                file_path,
                caption=caption,
                force_document=False  # Auto-detect if photo/video or document
            )
            
            print(f"[ATTACHMENT] Sent file to chat {chat_id}: {os.path.basename(file_path)}")
            return {'status': 'File sent successfully'}
        except Exception as e:
            print(f"[ERROR] Failed to send file to {chat_id}: {e}")
            return {'status': 'error', 'message': str(e)}

    def background_download_document(self, chat_id, message_id):
        """Run download in background thread with its own event loop."""
        # Create new event loop for this thread
        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        
        try:
            result = loop.run_until_complete(
                self.download_document_file(chat_id, message_id)
            )
            
            if result['status'] == 'success':
                print(f"[DOWNLOAD] ✓ Background download complete: {result.get('filename')}")
            else:
                print(f"[DOWNLOAD] ✗ Background download failed: {result.get('message')}")
        except Exception as e:
            print(f"[ERROR] Background download exception: {e}")
        finally:
            loop.close()
    
    async def download_document_file(self, chat_id, message_id):
        """Download a document file (APK, PDF, etc.) from Telegram to downloads folder."""
        try:
            if not client.is_connected():
                await client.connect()
            
            # Get the specific message
            msg = await client.get_messages(chat_id, ids=message_id)
            
            if not msg or not msg.media or not hasattr(msg.media, 'document'):
                return {'status': 'error', 'message': 'No document found in this message'}
            
            # Get filename from document attributes
            doc = msg.media.document
            filename = None
            if hasattr(doc, 'attributes'):
                for attr in doc.attributes:
                    if hasattr(attr, 'file_name'):
                        filename = attr.file_name
                        break
            
            if not filename:
                # Generate filename from message ID and mime type
                mime_type = doc.mime_type if hasattr(doc, 'mime_type') else 'application/octet-stream'
                ext = mime_type.split('/')[-1] if '/' in mime_type else 'bin'
                filename = f"document_{message_id}.{ext}"
            
            # Download to the downloads directory
            download_path = os.path.join(DOWNLOADS_DIR, filename)
            
            print(f"[DOWNLOAD] Downloading {filename} to {download_path}...")
            await client.download_media(msg.media, download_path)
            print(f"[DOWNLOAD] Successfully downloaded: {filename}")
            
            return {
                'status': 'success',
                'message': f'Downloaded to {download_path}',
                'filename': filename,
                'path': download_path
            }
        except Exception as e:
            print(f"[ERROR] Failed to download document: {e}")
            return {'status': 'error', 'message': str(e)}

    # ----------------------------------------------------------------------
    #    SESSION FILE / PERMISSIONS HELPER
    # ----------------------------------------------------------------------
    def _ensure_session_writable(self):
        """
        If `session_name.session` already exists but is read-only or corrupted,
        remove or rename it so Telethon can recreate properly.
        """
        session_file = SESSION_FILE_PATH
        if os.path.exists(session_file):
            # Check if we can write to the file
            if not os.access(session_file, os.W_OK):
                # Attempt to fix permissions or remove it
                try:
                    os.chmod(session_file, 0o600)  # rw-------
                except Exception:
                    # If we cannot chmod, rename or remove the file
                    try:
                        os.remove(session_file)
                    except Exception:
                        # If removing also fails, rename
                        base, ext = os.path.splitext(session_file)
                        os.rename(session_file, base + '_old' + ext)


# ----------------------------------------------------------------------
#    RUN THE SERVER
# ----------------------------------------------------------------------
if __name__ == "__main__":
    Handler = MyHttpRequestHandler
    
    # Check if user is already authorized and start notifications if so
    try:
        loop = asyncio.get_event_loop()
        
        async def check_and_start_notifications():
            if not client.is_connected():
                await client.connect()
            if await client.is_user_authorized():
                start_notification_thread()
        
        loop.run_until_complete(check_and_start_notifications())
    except Exception as e:
        print(f"[INFO] Could not check authorization at startup: {e}")
    
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print(f"Serving on port {PORT}")
        httpd.serve_forever()
