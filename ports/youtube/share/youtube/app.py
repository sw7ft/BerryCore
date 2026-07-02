#!/usr/bin/env python3
"""
YouTube Search App - Dedicated Search Interface
- YouTube-themed colors and design
- Search and stream YouTube videos
- ES5-compatible frontend
- QNX SSL compatible
- No download functionality (pure search/stream)
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

# ---- App identity & TaskApp2 integration ----
PORT = 8070  # BerryPy / BerryStore catalog port
APP_NAME = "YouTube Search"

# ---- QNX/Embedded system optimizations ----
QNX_MODE = True  # Set to True for QNX/embedded systems (prioritizes embed)
EMBED_FIRST = QNX_MODE  # Use embed-first strategy for better compatibility

# ---- SSL Context (QNX compatible) ----
def create_permissive_ssl_context():
    """Create a permissive SSL context that works on QNX"""
    try:
        ctx = ssl._create_unverified_context()
        print("SSL: Using unverified context (no certificate verification)")
        return ctx
    except Exception as e1:
        print(f"SSL: Unverified context failed ({e1}), trying manual setup...")
        try:
            ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
            ctx.verify_mode = ssl.CERT_NONE
            ctx.check_hostname = False
            print("SSL: Using manual permissive context")
            return ctx
        except Exception as e2:
            print(f"SSL: Manual context failed ({e2}), using default...")
            return ssl.create_default_context()

ssl_context = create_permissive_ssl_context()

def create_qnx_ssl_context(*args, **kwargs):
    return ssl_context

ssl._create_default_https_context = create_qnx_ssl_context
ssl.create_default_context = create_qnx_ssl_context
ssl._create_unverified_context = create_qnx_ssl_context

# ---- YouTube search imports ----
try:
    from youtubesearchpython import VideosSearch
    SEARCH_METHOD = "direct-http"  # Use direct HTTP by default for speed
    print("Note: Using direct HTTP search for better performance")
except Exception as e:
    SEARCH_METHOD = "direct-http"

try:
    from pytube import YouTube
    from pytube.exceptions import VideoUnavailable, RegexMatchError, PytubeError
    PYTUBE_AVAILABLE = True
except Exception as e:
    PYTUBE_AVAILABLE = False

# Enhanced streaming with multiple fallback methods
import threading
import time
from urllib.parse import parse_qs, urlparse

# ---- Cache for search results ----
search_cache = {}
cache_timeout = 300  # 5 minutes

def get_cached_search(query, limit):
    """Get cached search results if available and not expired"""
    cache_key = f"{query}:{limit}"
    if cache_key in search_cache:
        cached_data, timestamp = search_cache[cache_key]
        if time.time() - timestamp < cache_timeout:
            print(f"Using cached results for: {query}")
            return cached_data
    return None

def cache_search_results(query, limit, results):
    """Cache search results"""
    cache_key = f"{query}:{limit}"
    search_cache[cache_key] = (results, time.time())
    # Keep cache size reasonable
    if len(search_cache) > 50:
        oldest_key = min(search_cache.keys(), key=lambda k: search_cache[k][1])
        del search_cache[oldest_key]

# ---- Enhanced YouTube streaming methods ----
def extract_video_urls_advanced(video_id):
    """Advanced method to extract direct video URLs"""
    try:
        # Method 1: Try YouTube's player API
        player_url = f"https://www.youtube.com/youtubei/v1/player"
        player_data = {
            "videoId": video_id,
            "context": {
                "client": {
                    "clientName": "WEB",
                    "clientVersion": "2.20231201.00.00"
                }
            }
        }
        
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
            'Content-Type': 'application/json'
        }
        
        req = urllib.request.Request(
            player_url, 
            data=json.dumps(player_data).encode('utf-8'),
            headers=headers
        )
        
        with urllib.request.urlopen(req, context=ssl_context, timeout=10) as response:
            player_response = json.loads(response.read().decode('utf-8'))
            
        if 'streamingData' in player_response:
            streaming_data = player_response['streamingData']
            formats = streaming_data.get('formats', []) + streaming_data.get('adaptiveFormats', [])
            
            # Find best compatible stream for web playback
            best_stream = None
            progressive_streams = []
            
            # First, collect all progressive (video+audio) streams
            for fmt in formats:
                if 'url' in fmt:
                    mime_type = fmt.get('mimeType', '')
                    quality_label = fmt.get('qualityLabel', '')
                    
                    # Look for progressive MP4 streams (video + audio combined)
                    if ('video/mp4' in mime_type and 
                        'codecs="avc1' in mime_type and 
                        quality_label and 
                        'p' in quality_label):
                        
                        quality = quality_label.replace('p', '')
                        if quality.isdigit():
                            progressive_streams.append({
                                'url': fmt['url'],
                                'quality': int(quality),
                                'quality_label': quality_label,
                                'mime_type': mime_type,
                                'has_audio': fmt.get('audioQuality') is not None or 'mp4a' in mime_type
                            })
            
            # Sort by quality and prefer streams with audio
            progressive_streams.sort(key=lambda x: (x['has_audio'], x['quality']), reverse=True)
            
            # Find best stream for requested quality
            target_quality = quality.replace('p', '') if quality != 'best' and quality != 'audio' else None
            
            if target_quality and target_quality.isdigit():
                target_q = int(target_quality)
                # Find closest quality match
                for stream in progressive_streams:
                    if stream['quality'] <= target_q:
                        best_stream = stream
                        break
            
            # If no specific quality match, use best available
            if not best_stream and progressive_streams:
                best_stream = progressive_streams[0]
            
            if best_stream:
                return {
                    'url': best_stream['url'],
                    'quality': str(best_stream['quality']),
                    'mime_type': best_stream['mime_type']
                }
                
    except Exception as e:
        print(f"Advanced URL extraction failed: {e}")
    
    return None

def get_youtube_info_fast(video_id):
    """Fast method to get basic video info"""
    try:
        # Use YouTube's oEmbed API for basic info
        oembed_url = f"https://www.youtube.com/oembed?url=https://www.youtube.com/watch?v={video_id}&format=json"
        
        req = urllib.request.Request(oembed_url, headers={
            'User-Agent': 'Mozilla/5.0 (compatible; YouTube Search App)'
        })
        
        with urllib.request.urlopen(req, context=ssl_context, timeout=5) as response:
            data = json.loads(response.read().decode('utf-8'))
            
        return {
            'title': data.get('title', f'YouTube Video {video_id}'),
            'author': data.get('author_name', 'Unknown Channel'),
            'thumbnail': data.get('thumbnail_url', f'https://i.ytimg.com/vi/{video_id}/mqdefault.jpg')
        }
        
    except Exception as e:
        print(f"Fast info extraction failed: {e}")
        return {
            'title': f'YouTube Video {video_id}',
            'author': 'Unknown Channel',
            'thumbnail': f'https://i.ytimg.com/vi/{video_id}/mqdefault.jpg'
        }

# ---- Direct YouTube search fallback ----
def search_youtube_direct(query, limit=20):
    """Direct YouTube search using HTTP requests - QNX compatible"""
    try:
        search_url = f"https://www.youtube.com/results?search_query={urllib.parse.quote(query)}"
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
        }
        
        req = urllib.request.Request(search_url, headers=headers)
        
        with urllib.request.urlopen(req, context=ssl_context) as response:
            html = response.read().decode('utf-8')
        
        pattern = r'var ytInitialData = ({.*?});'
        match = re.search(pattern, html)
        
        if not match:
            pattern = r'window\["ytInitialData"\] = ({.*?});'
            match = re.search(pattern, html)
        
        if not match:
            return []
        
        try:
            data = json.loads(match.group(1))
            return parse_youtube_data(data, limit)
        except json.JSONDecodeError:
            return []
            
    except Exception as e:
        print(f"Direct search error: {e}")
        return []

def parse_youtube_data(data, limit):
    """Parse YouTube search results from ytInitialData"""
    results = []
    
    try:
        contents = data.get('contents', {}).get('twoColumnSearchResultsRenderer', {}).get('primaryContents', {}).get('sectionListRenderer', {}).get('contents', [])
        
        for section in contents:
            items = section.get('itemSectionRenderer', {}).get('contents', [])
            
            for item in items:
                if 'videoRenderer' in item:
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
                            'url': f'https://www.youtube.com/watch?v={video_id}',
                            'duration': duration,
                            'channel': channel,
                            'views': views,
                            'thumbnail': f'https://i.ytimg.com/vi/{video_id}/mqdefault.jpg',
                            'published': published,
                            'video_id': video_id
                        })
                        
                        if len(results) >= limit:
                            break
            
            if len(results) >= limit:
                break
                
    except Exception as e:
        print(f"Parse error: {e}")
    
    return results[:limit]

# ---- Utility functions ----
def send_json(handler, status_code, payload):
    body = json.dumps(payload).encode("utf-8")
    handler.send_response(status_code)
    handler.send_header("Content-Type", "application/json")
    handler.send_header("Cache-Control", "no-store")
    handler.send_header("Content-Length", str(len(body)))
    handler.send_header("Access-Control-Allow-Origin", "*")
    handler.end_headers()
    handler.wfile.write(body)

# ---- HTTP Handler ----
class SearchHandler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        # Suppress logging for common misrouted requests to reduce noise
        message = fmt % args
        if "/api/game" in message or "/api/input" in message:
            return  # Don't log these misrouted requests
        
        sys.stdout.write("%s - - [%s] %s\n" % (self.address_string(),
                                               self.log_date_time_string(),
                                               message))

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path

        if path == "/" or path == "/index.html":
            self.serve_html()
            return

        if path == "/api/search":
            self.handle_search(parsed.query)
            return

        if path == "/api/stream":
            self.handle_stream(parsed.query)
            return

        if path == "/api/status":
            self.handle_status()
            return

        if path == "/api/cache-stats":
            self.handle_cache_stats()
            return

        if path == "/favicon.ico":
            self.send_favicon()
            return

        # Handle common misrouted requests quietly
        if path.startswith("/api/game") or path.startswith("/api/input"):
            send_json(self, 404, {"status": "error", "error": "This is a YouTube Search app, not a game server"})
            return

        self.send_error(404, "Not Found")

    def do_POST(self):
        """Handle POST requests (return appropriate error)"""
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path
        
        # Handle common misrouted POST requests
        if path.startswith("/api/"):
            send_json(self, 405, {"status": "error", "error": "This YouTube Search app only supports GET requests"})
            return
            
        self.send_error(405, "Method Not Allowed")

    def handle_status(self):
        """Status endpoint"""
        status = {
            "app": APP_NAME,
            "port": PORT,
            "search_method": SEARCH_METHOD,
            "pytube_available": PYTUBE_AVAILABLE,
            "cache_entries": len(search_cache),
            "ssl_context": "permissive",
            "qnx_mode": QNX_MODE,
            "embed_first": EMBED_FIRST,
            "streaming_strategy": "embed-first" if EMBED_FIRST else "direct-first"
        }
        send_json(self, 200, {"status": "ok", "info": status})

    def handle_cache_stats(self):
        """Cache statistics endpoint"""
        stats = {
            "cache_entries": len(search_cache),
            "cache_timeout": cache_timeout,
            "cache_keys": list(search_cache.keys())[:10]  # Show first 10 keys
        }
        send_json(self, 200, {"status": "ok", "cache_stats": stats})

    def send_favicon(self):
        """Send a simple favicon to prevent 404 errors"""
        # Simple 16x16 red square favicon (YouTube red)
        favicon_data = b'\x00\x00\x01\x00\x01\x00\x10\x10\x00\x00\x01\x00\x18\x00h\x00\x00\x00\x16\x00\x00\x00(\x00\x00\x00\x10\x00\x00\x00 \x00\x00\x00\x01\x00\x18\x00\x00\x00\x00\x00@\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00\xff\x00\x00'
        
        self.send_response(200)
        self.send_header("Content-Type", "image/x-icon")
        self.send_header("Content-Length", str(len(favicon_data)))
        self.send_header("Cache-Control", "public, max-age=86400")  # Cache for 1 day
        self.end_headers()
        self.wfile.write(favicon_data)

    def handle_search(self, query_string):
        """Search YouTube videos with caching"""
        params = urllib.parse.parse_qs(query_string)
        query = params.get("q", [""])[0].strip()
        limit = int(params.get("limit", ["12"])[0])  # Reduced default from 20 to 12

        if not query:
            send_json(self, 400, {"status": "error", "error": "Missing 'q' parameter"})
            return

        if limit > 24:  # Reduced max from 50 to 24
            limit = 24

        print(f"Searching YouTube for: {query} (limit: {limit}) using {SEARCH_METHOD}")
        
        # Check cache first
        cached_results = get_cached_search(query, limit)
        if cached_results:
            send_json(self, 200, {
                "status": "ok",
                "query": query,
                "results": cached_results,
                "count": len(cached_results),
                "method": f"{SEARCH_METHOD} (cached)",
                "cached": True
            })
            return
        
        # Use direct HTTP method for speed (skip youtube-search-python)
        try:
            formatted_results = search_youtube_direct(query, limit)
            print(f"Search completed via direct HTTP: {len(formatted_results)} results")
            
            # Cache the results
            cache_search_results(query, limit, formatted_results)
            
        except Exception as e:
            print(f"Direct search failed: {e}")
            send_json(self, 500, {"status": "error", "error": f"Search failed: {str(e)}"})
            return
        
        send_json(self, 200, {
            "status": "ok",
            "query": query,
            "results": formatted_results,
            "count": len(formatted_results),
            "method": SEARCH_METHOD,
            "cached": False
        })

    def handle_stream(self, query_string):
        """Get streaming URL for a YouTube video with enhanced methods"""
        params = urllib.parse.parse_qs(query_string)
        url = params.get("url", [""])[0].strip()
        quality = params.get("quality", ["360p"])[0]

        if not url:
            send_json(self, 400, {"status": "error", "error": "Missing 'url' parameter"})
            return

        # Extract video ID from URL for fallback
        video_id = None
        if "watch?v=" in url:
            video_id = url.split("watch?v=")[1].split("&")[0]
        elif "youtu.be/" in url:
            video_id = url.split("youtu.be/")[1].split("?")[0]
        
        if not video_id:
            send_json(self, 400, {"status": "error", "error": "Invalid YouTube URL"})
            return

        # Get the origin for YouTube embed (dynamic IP support)
        origin = f"http://{self.headers.get('Host', 'localhost:8034')}"
        print(f"Getting stream info for: {url} (quality: {quality}) [QNX_MODE: {QNX_MODE}] [Origin: {origin}]")

        # Strategy selection based on system type
        if EMBED_FIRST:
            # Method 1: Try YouTube embed first (most reliable on QNX/embedded)
            try:
                video_info = get_youtube_info_fast(video_id)
                
                # Create embed-based response (always works on QNX)
                # Optimized parameters for QNX/embedded systems
                embed_url = f"https://www.youtube.com/embed/{video_id}?autoplay=1&controls=1&rel=0&modestbranding=1&iv_load_policy=3&disablekb=1&fs=1&origin={origin}"
                
                response_data = {
                    "status": "ok",
                    "title": video_info['title'],
                    "author": video_info['author'],
                    "length_seconds": 0,
                    "description": "Playing via YouTube embed (QNX optimized)",
                    "thumbnail": video_info['thumbnail'],
                    "stream_url": embed_url,
                    "stream_quality": "embed",
                    "stream_type": "text/html",
                    "is_embed": True,
                    "method": "embed_priority"
                }
                
                send_json(self, 200, response_data)
                print(f"Stream ready via embed (QNX priority): {video_info['title']}")
                return
                
            except Exception as e:
                print(f"Embed method failed: {e}")

        # Method 2: Try advanced direct URL extraction (fallback)
        try:
            direct_stream = extract_video_urls_advanced(video_id)
            if direct_stream:
                video_info = get_youtube_info_fast(video_id)
                
                response_data = {
                    "status": "ok",
                    "title": video_info['title'],
                    "author": video_info['author'],
                    "length_seconds": 0,
                    "description": "Direct stream via YouTube API",
                    "thumbnail": video_info['thumbnail'],
                    "stream_url": direct_stream['url'],
                    "stream_quality": f"{direct_stream['quality']}p",
                    "stream_type": direct_stream['mime_type'],
                    "method": "direct_api",
                    "requires_headers": True
                }
                
                send_json(self, 200, response_data)
                print(f"Stream ready via direct API: {direct_stream['quality']}p (fallback)")
                return
                
        except Exception as e:
            print(f"Direct API method failed: {e}")

        # Method 3: Try pytube (if available)
        if PYTUBE_AVAILABLE:
            try:
                yt = YouTube(url)
                
                # Find best stream for requested quality
                best_stream = None
                if quality == "best":
                    best_stream = yt.streams.filter(progressive=True).order_by("resolution").desc().first()
                elif quality == "audio":
                    best_stream = yt.streams.filter(only_audio=True).order_by("abr").desc().first()
                else:
                    best_stream = yt.streams.filter(progressive=True, res=quality).first()
                    if not best_stream:
                        best_stream = yt.streams.filter(progressive=True).order_by("resolution").desc().first()
                
                if best_stream:
                    response_data = {
                        "status": "ok",
                        "title": yt.title,
                        "author": yt.author,
                        "length_seconds": yt.length,
                        "description": yt.description[:500] if yt.description else "",
                        "thumbnail": f"https://i.ytimg.com/vi/{yt.video_id}/mqdefault.jpg",
                        "stream_url": best_stream.url,
                        "stream_quality": getattr(best_stream, 'resolution', 'audio'),
                        "stream_type": best_stream.mime_type,
                        "method": "pytube"
                    }
                    
                    send_json(self, 200, response_data)
                    print(f"Stream info retrieved via pytube: {best_stream.mime_type}, {getattr(best_stream, 'resolution', 'audio')}")
                    return
                    
            except Exception as e:
                print(f"Pytube failed ({str(e)}), trying fallback method...")

        # Method 4: Final fallback to YouTube embed
        try:
            video_info = get_youtube_info_fast(video_id)
            
            # Create embed-based response (always works)
            embed_url = f"https://www.youtube.com/embed/{video_id}?autoplay=1&controls=1&rel=0&modestbranding=1&iv_load_policy=3&disablekb=1&fs=1&origin={origin}"
            
            response_data = {
                "status": "ok",
                "title": video_info['title'],
                "author": video_info['author'],
                "length_seconds": 0,
                "description": "Playing via YouTube embed",
                "thumbnail": video_info['thumbnail'],
                "stream_url": embed_url,
                "stream_quality": "embed",
                "stream_type": "text/html",
                "is_embed": True,  # Flag to handle differently in frontend
                "method": "embed"
            }
            
            send_json(self, 200, response_data)
            print(f"Stream ready via embed: {video_info['title']}")
            
        except Exception as e:
            print(f"All streaming methods failed: {e}")
            send_json(self, 500, {"status": "error", "error": "Video temporarily unavailable"})

    def serve_html(self):
        html = """<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>YouTube</title>
    
    <!-- Home Screen Icon Support -->
    <link rel="icon" href="https://berrystore.sw7ft.com/apps/app-icons/youtube.png" type="image/png">
    <link rel="apple-touch-icon" href="https://berrystore.sw7ft.com/apps/app-icons/youtube.png">
    <link rel="apple-touch-icon-precomposed" href="https://berrystore.sw7ft.com/apps/app-icons/youtube.png">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black">
    <meta name="apple-mobile-web-app-title" content="YouTube">
    <meta name="application-name" content="YouTube">
    <meta name="theme-color" content="#FF0000">
<style>
  /* YouTube-inspired color scheme */
  body { 
    font-family: 'Roboto', Arial, sans-serif; 
    background: #f9f9f9; 
    color: #030303; 
    margin: 0; 
    padding: 20px; 
  }
  
  .header {
    background: #fff;
    border-bottom: 1px solid #e5e5e5;
    padding: 16px 20px;
    margin: -20px -20px 20px -20px;
    display: flex;
    align-items: center;
    box-shadow: 0 1px 2px rgba(0,0,0,0.1);
  }
  
  .logo {
    font-size: 24px;
    font-weight: bold;
    color: #ff0000;
    margin-right: 20px;
  }
  
  .search-container {
    flex: 1;
    max-width: 600px;
    display: flex;
    align-items: center;
  }
  
  .search-box {
    flex: 1;
    padding: 12px 16px;
    border: 1px solid #ccc;
    border-radius: 2px 0 0 2px;
    font-size: 16px;
    outline: none;
  }
  
  .search-box:focus {
    border-color: #1c62b9;
    box-shadow: inset 0 1px 2px rgba(0,0,0,0.1);
  }
  
  .search-btn {
    padding: 12px 20px;
    background: #f8f8f8;
    border: 1px solid #ccc;
    border-left: none;
    border-radius: 0 2px 2px 0;
    cursor: pointer;
    font-size: 16px;
  }
  
  .search-btn:hover {
    background: #f0f0f0;
  }
  
  .search-btn:disabled {
    background: #f8f8f8;
    cursor: not-allowed;
  }
  
  .container {
    max-width: 1200px;
    margin: 0 auto;
  }
  
  .results-header {
    padding: 16px 0;
    border-bottom: 1px solid #e5e5e5;
    margin-bottom: 16px;
    color: #606060;
    font-size: 14px;
  }
  
  .video-grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));  /* Smaller cards */
    gap: 12px;  /* Reduced gap */
    margin-bottom: 20px;
    /* Performance optimizations */
    will-change: contents;
    contain: layout style;
  }
  
  .video-card {
    background: #fff;
    border-radius: 6px;
    overflow: hidden;
    box-shadow: 0 1px 2px rgba(0,0,0,0.1);
    cursor: pointer;
    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    will-change: transform, box-shadow;
    animation: fadeIn 0.4s ease-out;
  }
  
  .video-card:hover {
    box-shadow: 0 4px 12px rgba(0,0,0,0.15);
    transform: translateY(-2px);
  }
  
  .video-card:active {
    transform: translateY(0);
    transition: transform 0.1s;
  }
  
  .video-thumbnail {
    position: relative;
    width: 100%;
    height: 160px;  /* Reduced from 180px to 160px */
    background: #000;
    overflow: hidden;
  }
  
  .video-thumbnail img {
    width: 100%;
    height: 100%;
    object-fit: cover;
    loading: lazy;  /* Lazy load images for faster initial render */
  }
  
  .video-duration {
    position: absolute;
    bottom: 8px;
    right: 8px;
    background: rgba(0,0,0,0.8);
    color: white;
    padding: 2px 6px;
    border-radius: 2px;
    font-size: 12px;
    font-weight: 500;
  }
  
  .video-info {
    padding: 12px;
  }
  
  .video-title {
    font-size: 14px;
    font-weight: 500;
    line-height: 1.3;
    margin-bottom: 8px;
    color: #030303;
    display: -webkit-box;
    -webkit-line-clamp: 2;
    -webkit-box-orient: vertical;
    overflow: hidden;
  }
  
  .video-channel {
    font-size: 13px;
    color: #606060;
    margin-bottom: 4px;
  }
  
  .video-meta {
    font-size: 13px;
    color: #606060;
  }
  
  .video-actions {
    padding: 0 12px 12px;
    display: flex;
    gap: 8px;
  }
  
  .btn {
    padding: 8px 16px;
    border: none;
    border-radius: 18px;
    cursor: pointer;
    font-size: 13px;
    font-weight: 500;
    transition: all 0.25s cubic-bezier(0.4, 0, 0.2, 1);
    will-change: transform, background-color;
  }
  
  .btn:hover {
    transform: translateY(-1px);
  }
  
  .btn:active {
    transform: translateY(0);
    transition: transform 0.1s;
  }
  
  .btn-primary {
    background: #ff0000;
    color: white;
  }
  
  .btn-primary:hover {
    background: #cc0000;
  }
  
  .btn-secondary {
    background: #f2f2f2;
    color: #030303;
  }
  
  .btn-secondary:hover {
    background: #e5e5e5;
  }
  
  .status {
    background: #fff;
    padding: 16px;
    border-radius: 8px;
    margin-bottom: 20px;
    box-shadow: 0 1px 2px rgba(0,0,0,0.1);
  }
  
  .status.error {
    background: #fef7f7;
    border-left: 4px solid #ff0000;
    color: #d93025;
  }
  
  .status.success {
    background: #f7fef7;
    border-left: 4px solid #00aa00;
    color: #137333;
  }
  
  .player-section {
    background: #fff;
    border-radius: 8px;
    padding: 20px;
    margin-bottom: 20px;
    box-shadow: 0 1px 2px rgba(0,0,0,0.1);
    display: none;
    animation: slideIn 0.4s cubic-bezier(0.4, 0, 0.2, 1);
  }
  
  .video-player {
    width: 100%;
    max-width: 854px;
    height: 0;
    padding-bottom: 56.25%; /* 16:9 aspect ratio (9/16 = 0.5625) */
    background: #000;
    border-radius: 8px;
    position: relative;
  }
  
  .video-player iframe,
  .video-player video {
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    border-radius: 8px;
  }
  
  .player-info {
    margin-top: 16px;
  }
  
  .player-title {
    font-size: 18px;
    font-weight: 500;
    margin-bottom: 8px;
    color: #030303;
  }
  
  .player-meta {
    color: #606060;
    font-size: 14px;
    margin-bottom: 12px;
  }
  
  .player-description {
    color: #030303;
    font-size: 14px;
    line-height: 1.4;
    max-height: 60px;
    overflow: hidden;
  }
  
  .player-controls {
    margin-top: 16px;
    display: flex;
    gap: 12px;
    align-items: center;
  }
  
  .quality-select {
    padding: 8px 12px;
    border: 1px solid #ccc;
    border-radius: 2px;
    font-size: 13px;
  }
  
  .loading {
    text-align: center;
    padding: 40px;
    color: #606060;
  }
  
  .empty-state {
    text-align: center;
    padding: 60px 20px;
    color: #606060;
  }
  
  .empty-state h3 {
    margin-bottom: 8px;
    color: #030303;
  }
  
  /* Enhanced loading spinners with smooth animations */
  .loading-spinner {
    display: inline-block;
    width: 20px;
    height: 20px;
    border: 3px solid rgba(255, 0, 0, 0.1);
    border-top: 3px solid #ff0000;
    border-radius: 50%;
    animation: smoothSpin 0.8s cubic-bezier(0.4, 0, 0.2, 1) infinite;
    margin-right: 8px;
  }
  
  .loading-spinner-large {
    width: 48px;
    height: 48px;
    border-width: 4px;
    margin: 20px auto;
    border: 4px solid rgba(255, 255, 255, 0.1);
    border-top: 4px solid #ff0000;
    animation: smoothSpin 1s cubic-bezier(0.4, 0, 0.2, 1) infinite;
  }
  
  @keyframes smoothSpin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
  }
  
  /* Smooth fade-in animation */
  @keyframes fadeIn {
    from { opacity: 0; transform: translateY(10px); }
    to { opacity: 1; transform: translateY(0); }
  }
  
  /* Smooth slide-in animation */
  @keyframes slideIn {
    from { opacity: 0; transform: translateX(-20px); }
    to { opacity: 1; transform: translateX(0); }
  }
  
  /* Pulse animation for loading states */
  @keyframes pulse {
    0%, 100% { opacity: 1; }
    50% { opacity: 0.6; }
  }
  
  .btn-loading {
    opacity: 0.7;
    cursor: not-allowed;
  }
  
  /* Responsive video player */
  @media (max-width: 768px) {
    .video-player {
      max-width: 100%;
      border-radius: 4px; /* Smaller radius on mobile */
    }
    
    .video-player iframe,
    .video-player video {
      border-radius: 4px;
    }
  }
  
  @media (min-width: 1200px) {
    .video-player {
      max-width: 1024px; /* Larger on big screens */
    }
  }
  
  /* Fullscreen styles with smooth transitions */
  .fullscreen-player {
    position: fixed !important;
    top: 0 !important;
    left: 0 !important;
    width: 100vw !important;
    height: 100vh !important;
    max-width: none !important;
    padding-bottom: 0 !important;
    z-index: 9999 !important;
    background: #000 !important;
    border-radius: 0 !important;
    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1) !important;
  }
  
  .fullscreen-player iframe,
  .fullscreen-player video {
    width: 100% !important;
    height: 100% !important;
    border-radius: 0 !important;
  }
  
  .fullscreen-overlay {
    position: fixed;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    background: #000;
    z-index: 9998;
    display: none;
    opacity: 0;
    transition: opacity 0.3s cubic-bezier(0.4, 0, 0.2, 1);
  }
  
  .fullscreen-overlay.show {
    opacity: 1;
  }
  
  .fullscreen-controls {
    position: fixed;
    bottom: 20px;
    right: 20px;
    z-index: 10000;
    display: none;
    opacity: 0;
    transform: translateY(20px);
    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
  }
  
  .fullscreen-controls.show {
    opacity: 1;
    transform: translateY(0);
  }
  
  .fullscreen-controls button {
    background: rgba(0,0,0,0.8);
    color: white;
    border: 1px solid rgba(255,255,255,0.3);
    padding: 10px 15px;
    border-radius: 4px;
    cursor: pointer;
    font-size: 14px;
  }
  
  .fullscreen-controls button:hover {
    background: rgba(0,0,0,0.9);
  }
</style>
</head>
<body>
  <div class="header">
    <div class="logo">📺 YouTube </div>
    <div class="search-container">
      <input type="text" id="searchInput" class="search-box" placeholder="Search YouTube videos..." value="">
      <button id="searchButton" class="search-btn" onclick="performSearch()">🔍</button>
    </div>
  </div>

  <div class="container">
    <div id="status" class="status" style="display:none;"></div>
    
    <div id="playerSection" class="player-section">
      <div id="videoPlayerContainer" class="video-player">
        <video id="videoPlayer" controls>
          Your browser does not support the video tag.
        </video>
      </div>
      <div class="player-info">
        <div id="playerTitle" class="player-title"></div>
        <div id="playerMeta" class="player-meta"></div>
        <div id="playerDescription" class="player-description"></div>
      </div>
      <div class="player-controls">
        <button class="btn btn-secondary" onclick="closePlayer()">Close Player</button>
        <button id="fullscreenBtn" class="btn btn-secondary" onclick="toggleFullscreen()">⛶ Fullscreen</button>
        <button id="retryStreamBtn" class="btn btn-secondary" onclick="retryStream()" style="display:none;">Retry Stream</button>
        <select id="qualitySelect" class="quality-select" onchange="changeQuality()">
          <option value="360p">360p</option>
          <option value="480p">480p</option>
          <option value="720p">720p</option>
          <option value="best">Best Quality</option>
          <option value="audio">Audio Only</option>
        </select>
      </div>
    </div>

    <div id="resultsHeader" class="results-header" style="display:none;"></div>
    
    <div id="results" class="video-grid"></div>
    
    <div id="loadMoreSection" style="text-align:center; margin:20px 0; display:none;">
      <button id="loadMoreBtn" class="btn btn-secondary" onclick="loadMoreResults()">Load More Videos</button>
    </div>
    
    <div id="emptyState" class="empty-state">
      <h3>Search YouTube</h3>
      <p>Enter a search term above to find videos</p>
    </div>
  </div>

  <!-- Fullscreen overlay and controls -->
  <div id="fullscreenOverlay" class="fullscreen-overlay"></div>
  <div id="fullscreenControls" class="fullscreen-controls">
    <button onclick="exitFullscreen()">✕ Exit Fullscreen</button>
  </div>

<script>
  // ES5 compatible JavaScript
  var isSearching = false;
  var isStreaming = false;
  var currentStreamUrl = '';
  var currentQuery = '';
  var currentResults = [];
  var displayedCount = 0;
  var isFullscreen = false;

  function setStatus(message, type) {
    var statusEl = document.getElementById('status');
    statusEl.textContent = message;
    statusEl.className = 'status ' + (type || '');
    statusEl.style.display = 'block';
    
    // Auto-hide success messages
    if (type === 'success') {
      setTimeout(function() {
        statusEl.style.display = 'none';
      }, 3000);
    }
  }

  function performSearch() {
    if (isSearching) return;

    var query = document.getElementById('searchInput').value.trim();
    if (!query) {
      setStatus('Please enter a search term', 'error');
      return;
    }

    isSearching = true;
    document.getElementById('searchButton').disabled = true;
    document.getElementById('searchButton').textContent = '⏳';
    
    setStatus('Searching YouTube...', '');
    document.getElementById('emptyState').style.display = 'none';
    document.getElementById('results').innerHTML = '<div class="loading" style="text-align:center; padding:40px; animation:fadeIn 0.3s ease;"><div class="loading-spinner loading-spinner-large"></div><div style="margin-top:15px; animation:pulse 2s infinite;">Searching for videos...</div></div>';

    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/api/search?q=' + encodeURIComponent(query) + '&limit=12', true);
    xhr.timeout = 10000;  // Reduced to 10s for faster feedback

    xhr.onreadystatechange = function() {
      if (xhr.readyState === 4) {
        isSearching = false;
        document.getElementById('searchButton').disabled = false;
        document.getElementById('searchButton').textContent = '🔍';
        
        try {
          var res = JSON.parse(xhr.responseText);
          if (xhr.status === 200 && res && res.status === 'ok') {
            currentQuery = res.query;
            currentResults = res.results;
            displayedCount = 0;
            displayResults(res.results.slice(0, 8), res.query, res.count);  // Show first 8 results
            var cacheMsg = res.cached ? ' (cached)' : '';
            setStatus('Found ' + res.count + ' videos' + cacheMsg, 'success');
            
            // Show load more button if there are more results
            if (res.results.length > 8) {
              document.getElementById('loadMoreSection').style.display = 'block';
            }
          } else {
            var err = (res && res.error) ? res.error : ('HTTP ' + xhr.status + ' error');
            setStatus('Search failed: ' + err, 'error');
            document.getElementById('results').innerHTML = '';
          }
        } catch (e) {
          setStatus('Error parsing search response', 'error');
          document.getElementById('results').innerHTML = '';
        }
      }
    };

    xhr.ontimeout = function() {
      isSearching = false;
      document.getElementById('searchButton').disabled = false;
      document.getElementById('searchButton').textContent = '🔍';
      setStatus('Search timeout - please try again', 'error');
    };

    xhr.onerror = function() {
      isSearching = false;
      document.getElementById('searchButton').disabled = false;
      document.getElementById('searchButton').textContent = '🔍';
      setStatus('Network error - please check connection', 'error');
    };

    xhr.send();
  }

  function displayResults(results, query, count, append) {
    var container = document.getElementById('results');
    var header = document.getElementById('resultsHeader');
    
    if (!results || results.length === 0) {
      if (!append) {
        container.innerHTML = '<div class="empty-state"><h3>No results found</h3><p>Try different search terms</p></div>';
        header.style.display = 'none';
      }
      return;
    }

    if (!append) {
      header.textContent = 'About ' + count + ' results for "' + query + '"';
      header.style.display = 'block';
    }

    var html = append ? container.innerHTML : '';
    for (var i = 0; i < results.length; i++) {
      var video = results[i];
      html += '<div class="video-card">';
      html += '<div class="video-thumbnail">';
      if (video.thumbnail) {
        // Use smaller thumbnail for faster loading (mqdefault instead of maxresdefault)
        var thumbUrl = video.thumbnail.replace('maxresdefault', 'mqdefault');
        html += '<img src="' + thumbUrl + '" alt="' + video.title.replace(/"/g, '&quot;') + '" loading="lazy">';
      }
      html += '<div class="video-duration">' + video.duration + '</div>';
      html += '</div>';
      html += '<div class="video-info">';
      html += '<div class="video-title">' + video.title + '</div>';
      html += '<div class="video-channel">' + video.channel + '</div>';
      html += '<div class="video-meta">' + video.views + ' • ' + video.published + '</div>';
      html += '</div>';
      html += '<div class="video-actions">';
      html += '<button class="btn btn-primary" data-url="' + video.url.replace(/"/g, '&quot;') + '" data-title="' + video.title.replace(/"/g, '&quot;') + '" onclick="streamVideoFromData(this)">▶ Watch</button>';
      html += '<button class="btn btn-secondary" data-url="' + video.url.replace(/"/g, '&quot;') + '" onclick="openYouTubeFromData(this)">Open in YouTube</button>';
      html += '</div>';
      html += '</div>';
    }
    
    container.innerHTML = html;
    displayedCount += results.length;
  }

  function loadMoreResults() {
    if (displayedCount >= currentResults.length) {
      document.getElementById('loadMoreSection').style.display = 'none';
      return;
    }
    
    var nextBatch = currentResults.slice(displayedCount, displayedCount + 4);  // Load 4 more
    displayResults(nextBatch, currentQuery, currentResults.length, true);
    
    // Hide load more button if no more results
    if (displayedCount >= currentResults.length) {
      document.getElementById('loadMoreSection').style.display = 'none';
    }
  }

  function streamVideoFromData(button) {
    var url = button.getAttribute('data-url');
    var title = button.getAttribute('data-title');
    
    // Add loading spinner to button
    setButtonLoading(button, true);
    
    streamVideo(url, title, button);
  }

  function openYouTubeFromData(button) {
    var url = button.getAttribute('data-url');
    openYouTube(url);
  }

  function setButtonLoading(button, loading) {
    if (loading) {
      button.disabled = true;
      button.className += ' btn-loading';
      button.style.transform = 'scale(0.95)';
      button.innerHTML = '<span class="loading-spinner"></span>Loading...';
    } else {
      button.disabled = false;
      button.className = button.className.replace(' btn-loading', '');
      button.style.transform = '';
      button.innerHTML = '▶ Watch';
    }
  }

  function clearAllButtonLoading() {
    var buttons = document.querySelectorAll('.btn-primary');
    for (var i = 0; i < buttons.length; i++) {
      setButtonLoading(buttons[i], false);
    }
  }

  function streamVideo(url, title, button) {
    if (isStreaming) {
      setStatus('Loading stream, please wait...', '');
      return;
    }

    isStreaming = true;
    currentStreamUrl = url;
    setStatus('Loading stream for: ' + title, '');
    
    // Clear any previous button loading states
    clearAllButtonLoading();
    
    // Show loading in player section
    showPlayerLoading(title);

    var quality = document.getElementById('qualitySelect').value;
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/api/stream?url=' + encodeURIComponent(url) + '&quality=' + quality, true);
    xhr.timeout = 20000;  // Reduced from 30s to 20s

    xhr.onreadystatechange = function() {
      if (xhr.readyState === 4) {
        isStreaming = false;
        clearAllButtonLoading();
        
        try {
          var res = JSON.parse(xhr.responseText);
          if (xhr.status === 200 && res && res.status === 'ok') {
            showPlayer(res);
            var methodMsg = res.method ? ' (' + res.method + ')' : '';
            setStatus('Now playing: ' + res.title + methodMsg, 'success');
          } else {
            var err = (res && res.error) ? res.error : ('HTTP ' + xhr.status + ' error');
            setStatus('Stream failed: ' + err, 'error');
            document.getElementById('retryStreamBtn').style.display = 'inline-block';
            hidePlayerLoading();
          }
        } catch (e) {
          setStatus('Error loading stream', 'error');
          hidePlayerLoading();
        }
      }
    };

    xhr.ontimeout = function() {
      isStreaming = false;
      clearAllButtonLoading();
      hidePlayerLoading();
      document.getElementById('retryStreamBtn').style.display = 'inline-block';
      setStatus('Stream timeout - video may be too long', 'error');
    };

    xhr.onerror = function() {
      isStreaming = false;
      clearAllButtonLoading();
      hidePlayerLoading();
      document.getElementById('retryStreamBtn').style.display = 'inline-block';
      setStatus('Stream error - please try again', 'error');
    };

    xhr.send();
  }

  function showPlayerLoading(title) {
    var section = document.getElementById('playerSection');
    var playerContainer = document.getElementById('videoPlayerContainer');
    
    // Show the player section with smooth animation
    section.style.display = 'block';
    
    // Create or update loading content in the responsive container
    var loadingDiv = document.getElementById('playerLoading');
    if (!loadingDiv) {
      loadingDiv = document.createElement('div');
      loadingDiv.id = 'playerLoading';
      loadingDiv.style.cssText = 'position:absolute; top:0; left:0; width:100%; height:100%; display:flex; flex-direction:column; justify-content:center; align-items:center; background:#000; border-radius:8px; color:#fff; opacity:0; transition:opacity 0.3s ease;';
      playerContainer.appendChild(loadingDiv);
    }
    
    loadingDiv.innerHTML = '<div class="loading-spinner loading-spinner-large"></div><div style="margin-top:15px; font-size:14px; animation:pulse 2s infinite;">Loading video: ' + title + '</div>';
    loadingDiv.style.display = 'flex';
    
    // Fade in loading screen
    setTimeout(function() {
      loadingDiv.style.opacity = '1';
    }, 10);
    
    // Clear player info with smooth updates
    document.getElementById('playerTitle').textContent = title;
    document.getElementById('playerMeta').textContent = 'Loading...';
    document.getElementById('playerDescription').textContent = 'Please wait while the video loads...';
    
    // Smooth scroll to player
    section.scrollIntoView({ behavior: 'smooth', block: 'start' });
  }

  function hidePlayerLoading() {
    var loadingDiv = document.getElementById('playerLoading');
    if (loadingDiv) {
      // Fade out loading screen
      loadingDiv.style.opacity = '0';
      setTimeout(function() {
        loadingDiv.style.display = 'none';
      }, 300);
    }
  }

  function showPlayer(streamData) {
    var playerContainer = document.getElementById('videoPlayerContainer');
    var section = document.getElementById('playerSection');
    
    // Hide loading
    hidePlayerLoading();
    
    // Clear existing player
    playerContainer.innerHTML = '';
    
    if (streamData.is_embed) {
      // Create iframe for YouTube embed with QNX-optimized attributes
      var iframe = document.createElement('iframe');
      iframe.src = streamData.stream_url;
      iframe.setAttribute('frameborder', '0');
      iframe.setAttribute('allowfullscreen', '');
      iframe.setAttribute('allow', 'autoplay; encrypted-media; fullscreen');
      iframe.setAttribute('sandbox', 'allow-scripts allow-same-origin allow-presentation');
      iframe.setAttribute('loading', 'lazy');
      iframe.setAttribute('title', streamData.title || 'YouTube Video');
      
      // Add double-click to fullscreen
      iframe.ondblclick = function() {
        if (!isFullscreen) {
          enterFullscreen();
        }
      };
      
      playerContainer.appendChild(iframe);
    } else {
      // Create video element for direct stream
      var video = document.createElement('video');
      video.src = streamData.stream_url;
      video.setAttribute('controls', '');
      video.setAttribute('preload', 'metadata');
      video.id = 'videoPlayer';
      
      // Add error handling for media playback
      video.onerror = function(e) {
        console.log('Video error:', e);
        console.log('Error code:', video.error ? video.error.code : 'unknown');
        
        // If this was a direct API stream, try embed immediately
        if (streamData.method === 'direct_api') {
          setStatus('Direct stream blocked, switching to embed...', 'error');
        } else {
          setStatus('Media playback failed, trying embed fallback...', 'error');
        }
        
        // Fallback to embed if direct stream fails
        setTimeout(function() {
          var embedUrl = 'https://www.youtube.com/embed/' + getVideoIdFromUrl(currentStreamUrl) + '?autoplay=1&controls=1&rel=0&modestbranding=1&iv_load_policy=3&disablekb=1&fs=1&origin=' + encodeURIComponent(getCurrentOrigin());
          var iframe = document.createElement('iframe');
          iframe.src = embedUrl;
          iframe.setAttribute('frameborder', '0');
          iframe.setAttribute('allowfullscreen', '');
          iframe.setAttribute('allow', 'autoplay; encrypted-media; fullscreen');
          iframe.setAttribute('sandbox', 'allow-scripts allow-same-origin allow-presentation');
          iframe.setAttribute('loading', 'lazy');
          
          playerContainer.innerHTML = '';
          playerContainer.appendChild(iframe);
          setStatus('Playing via YouTube embed (auto-fallback)', 'success');
        }, 500);  // Faster fallback
      };
      
      video.onloadstart = function() {
        setStatus('Loading video stream...', '');
      };
      
      video.oncanplay = function() {
        setStatus('Video ready to play', 'success');
      };
      
      // Add double-click to fullscreen for direct video
      video.ondblclick = function() {
        if (!isFullscreen) {
          enterFullscreen();
        }
      };
      
      playerContainer.appendChild(video);
    }
    
    document.getElementById('playerTitle').textContent = streamData.title;
    var duration = streamData.length_seconds > 0 ? 
      Math.floor(streamData.length_seconds / 60) + 'm ' + (streamData.length_seconds % 60) + 's' : 
      'Duration unknown';
    document.getElementById('playerMeta').textContent = 
      'By ' + streamData.author + ' • ' + duration + ' • ' + streamData.stream_quality;
    document.getElementById('playerDescription').textContent = streamData.description || 'No description available.';
    
    section.style.display = 'block';
  }

  function changeQuality() {
    if (currentStreamUrl) {
      var title = document.getElementById('playerTitle').textContent;
      streamVideo(currentStreamUrl, title);
    }
  }

  function retryStream() {
    if (currentStreamUrl) {
      var title = document.getElementById('playerTitle').textContent;
      document.getElementById('retryStreamBtn').style.display = 'none';
      streamVideo(currentStreamUrl, title);
    }
  }

  function closePlayer() {
    var playerContainer = document.getElementById('videoPlayerContainer');
    var section = document.getElementById('playerSection');
    
    // Exit fullscreen if active
    if (isFullscreen) {
      exitFullscreen();
    }
    
    // Stop any playing video
    var video = playerContainer.querySelector('video');
    var iframe = playerContainer.querySelector('iframe');
    
    if (video) {
      video.pause();
      video.src = '';
    }
    
    if (iframe) {
      iframe.src = '';
    }
    
    // Clear the player container and restore default video element
    playerContainer.innerHTML = '<video id="videoPlayer" controls>Your browser does not support the video tag.</video>';
    
    section.style.display = 'none';
    currentStreamUrl = '';
    
    setStatus('Player closed', 'success');
  }

  function getVideoIdFromUrl(url) {
    if (!url) return '';
    if (url.includes('watch?v=')) {
      return url.split('watch?v=')[1].split('&')[0];
    } else if (url.includes('youtu.be/')) {
      return url.split('youtu.be/')[1].split('?')[0];
    }
    return '';
  }

  function getCurrentOrigin() {
    return window.location.protocol + '//' + window.location.host;
  }

  function toggleFullscreen() {
    if (isFullscreen) {
      exitFullscreen();
    } else {
      enterFullscreen();
    }
  }

  function enterFullscreen() {
    var playerContainer = document.getElementById('videoPlayerContainer');
    var overlay = document.getElementById('fullscreenOverlay');
    var controls = document.getElementById('fullscreenControls');
    var fullscreenBtn = document.getElementById('fullscreenBtn');
    
    if (!playerContainer.querySelector('iframe') && !playerContainer.querySelector('video')) {
      setStatus('No video is currently playing', 'error');
      return;
    }
    
    // Show overlay and controls with smooth animation
    overlay.style.display = 'block';
    controls.style.display = 'block';
    
    // Trigger animations after display is set
    setTimeout(function() {
      overlay.classList.add('show');
      controls.classList.add('show');
    }, 10);
    
    // Add fullscreen class to player
    playerContainer.classList.add('fullscreen-player');
    
    // Update button text
    fullscreenBtn.innerHTML = '⛶ Exit Fullscreen';
    
    isFullscreen = true;
    
    // Hide scrollbars
    document.body.style.overflow = 'hidden';
    
    setStatus('Entered fullscreen mode', 'success');
    
    // ESC key listener
    document.addEventListener('keydown', handleFullscreenEscape);
  }

  function exitFullscreen() {
    var playerContainer = document.getElementById('videoPlayerContainer');
    var overlay = document.getElementById('fullscreenOverlay');
    var controls = document.getElementById('fullscreenControls');
    var fullscreenBtn = document.getElementById('fullscreenBtn');
    
    // Hide overlay and controls with smooth animation
    overlay.classList.remove('show');
    controls.classList.remove('show');
    
    // Hide elements after animation completes
    setTimeout(function() {
      overlay.style.display = 'none';
      controls.style.display = 'none';
    }, 300);
    
    // Remove fullscreen class
    playerContainer.classList.remove('fullscreen-player');
    
    // Update button text
    fullscreenBtn.innerHTML = '⛶ Fullscreen';
    
    isFullscreen = false;
    
    // Restore scrollbars
    document.body.style.overflow = '';
    
    setStatus('Exited fullscreen mode', 'success');
    
    // Remove ESC key listener
    document.removeEventListener('keydown', handleFullscreenEscape);
  }

  function handleFullscreenEscape(e) {
    if (e.keyCode === 27 && isFullscreen) { // ESC key
      exitFullscreen();
    }
  }

  function openYouTube(url) {
    window.open(url, '_blank');
  }

  // Enter key support
  document.getElementById('searchInput').onkeypress = function(e) {
    if (e.keyCode === 13) {
      performSearch();
    }
  };

  // Auto-focus search box
  window.onload = function() {
    document.getElementById('searchInput').focus();
  };
</script>
</body>
</html>"""
        body = html.encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

# ---- Server setup ----
def _signal_handler(sig, frame):
    print(f"Shutting down {APP_NAME}...")
    sys.exit(0)

signal.signal(signal.SIGTERM, _signal_handler)
signal.signal(signal.SIGINT, _signal_handler)

class ThreadingTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    daemon_threads = True
    allow_reuse_address = True

def run_server(port=PORT):
    try:
        with ThreadingTCPServer(("", port), SearchHandler) as httpd:
            print(f"Starting {APP_NAME} on port {port}...")
            print(f"Access at: http://localhost:{port}")
            print(f"Search method: {SEARCH_METHOD}")
            print(f"Streaming available: {PYTUBE_AVAILABLE}")
            print(f"QNX mode: {QNX_MODE} (embed-first: {EMBED_FIRST})")
            try:
                httpd.serve_forever()
            except KeyboardInterrupt:
                print(f"\nShutting down {APP_NAME}...")
    except OSError as e:
        if e.errno == 48:
            print(f"Error: Port {port} is already in use.")
        else:
            print(f"Error starting server: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if not PYTUBE_AVAILABLE:
        print("WARNING: pytube not available - streaming will be disabled")
    run_server()
