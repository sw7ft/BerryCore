# YouTube Search App - Installation Guide

A fast, YouTube-themed search and streaming app with ES5 compatibility for QNX and embedded systems.

## 📋 Requirements

### System Requirements
- **Python 3.11** or higher
- **SW7FT Task Manager** (for automatic app detection) https://www.patreon.com/posts/139192725/edit
- Internet connection for YouTube search and streaming

### Python Dependencies
- `pytube` - YouTube video downloading and streaming
- `youtube-search-python` - YouTube search functionality (optional, has direct HTTP fallback)

## 🚀 Quick Installation

### 1. Install Python Dependencies
```bash
pip install pytube youtube-search-python
```

### 2. Download the App
Save `app.py` to your desired directory.

### 3. Run the Application
```bash
python3 app.py
```

### 4. Access the Interface
Open your browser and go to:
```
http://localhost:8033
```

## 🔧 SW7FT Task Manager Integration

The app is designed to work with **SW7FT Task Manager** which automatically detects running applications by scanning for the `PORT = 8033` pattern in the source code.

### SW7FT Features:
- **Auto-discovery** of the YouTube app
- **Process management** and monitoring
- **System integration** for QNX environments

## 🎯 Features

- **Fast YouTube search** with thumbnail previews
- **Built-in video streaming** with quality selection
- **YouTube-themed interface** (red and white design)
- **ES5 compatible** JavaScript (works on older browsers)
- **QNX SSL compatible** (handles certificate issues)
- **Progressive loading** (shows 8 results initially, load more on demand)
- **Loading animations** with spinning circles

## 🔍 Usage

1. **Search**: Type keywords in the search box and press Enter
2. **Watch**: Click "▶ Watch" on any video to stream it directly
3. **Quality**: Use the quality selector to change video resolution
4. **External**: Click "Open in YouTube" to view on YouTube.com

## 🛠️ Troubleshooting

### Common Issues:

**Port already in use:**
```bash
# Kill any existing process on port 8033
lsof -ti:8033 | xargs kill -9
```

**SSL certificate errors:**
- The app automatically handles SSL issues with fallback contexts
- No manual SSL configuration needed

**Search not working:**
- App has built-in fallback from `youtube-search-python` to direct HTTP scraping
- Works even if the Python library has issues

**Streaming not working:**
- Ensure `pytube` is installed: `pip install pytube`
- Some videos may be region-restricted or have streaming limitations

## 📱 Compatibility

- **Browsers**: Works on ES5-compatible browsers (IE9+, all modern browsers)
- **Systems**: Linux, macOS, Windows, QNX, embedded systems
- **Python**: Requires Python 3.11+
- **Network**: Handles SSL certificate issues automatically

## 🎨 Customization

The app uses YouTube's official color scheme:
- **Primary Red**: `#ff0000` (YouTube red)
- **Background**: `#f9f9f9` (light gray)
- **Cards**: White with subtle shadows
- **Text**: Dark gray (`#030303`, `#606060`)

---

**Note**: This app is designed for personal use and educational purposes. Respect YouTube's terms of service when using this application.
