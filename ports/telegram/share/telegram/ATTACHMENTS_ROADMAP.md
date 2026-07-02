# Telegram App: Attachments Feature Roadmap

## Overview
This document outlines what would be needed to add file/attachment sending capabilities to the Telegram app.

---

## 📋 Feature Scope

### What We Want to Support:
1. **Photos/Images** (.jpg, .png, .gif, .webp)
2. **Documents** (.pdf, .txt, .doc, .zip, etc.)
3. **Videos** (.mp4, .avi, .mov)
4. **Audio** (.mp3, .wav, .ogg)
5. **Optional: Voice messages** (if BB10 has mic access)

### File Size Limits:
- **Photos**: Up to 10 MB (Telegram limit)
- **Other files**: Up to 2 GB (Telegram limit)
- **Practical limit on BB10**: Suggest 50 MB max for performance

---

## 🔧 Technical Implementation

### 1. Backend Changes (app.py)

#### A. Add File Upload Endpoint
```python
elif parsed_path.path == '/send_attachment':
    # Handle multipart/form-data file upload
    content_type = self.headers.get('Content-Type', '')
    
    if 'multipart/form-data' in content_type:
        # Parse multipart form data
        boundary = content_type.split('boundary=')[1]
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        
        # Extract file data, chat_id, caption, file_type
        # Save to temporary file
        # Call send_file_to_telegram()
```

#### B. Add Telethon File Sending Method
```python
async def send_file_to_telegram(self, chat_id, file_path, caption=None):
    """Send a file attachment to a Telegram chat."""
    try:
        if not client.is_connected():
            await client.connect()
        
        # Telethon's send_file method (very powerful!)
        await client.send_file(
            chat_id,
            file_path,
            caption=caption,
            force_document=False  # Auto-detect if photo/video
        )
        
        return {'status': 'success'}
    except Exception as e:
        print(f"[ERROR] Failed to send file: {e}")
        return {'status': 'error', 'message': str(e)}
```

#### C. Handle Multipart Form Data
- Need to parse `multipart/form-data` (Python's `cgi` module or custom parser)
- Save uploaded file to temporary directory
- Send via Telethon
- Clean up temporary file

**Estimated Lines of Code**: ~150-200 lines

---

### 2. Frontend Changes (index.html)

#### A. Add File Input Button
```html
<!-- In the message input area -->
<div class="input-area">
    <button id="attach-button" class="attach-button" onclick="triggerFileInput()">📎</button>
    <input type="file" id="file-input" style="display:none;" onchange="handleFileSelect(event)" multiple>
    <textarea id="messageInput" placeholder="Type a message..."></textarea>
    <button id="sendButton" onclick="sendMessage()">Send</button>
</div>
```

#### B. Add File Preview Area
```html
<div id="file-preview" class="file-preview" style="display:none;">
    <div class="preview-content">
        <span id="file-name"></span>
        <span id="file-size"></span>
        <button onclick="clearFile()">✕</button>
    </div>
</div>
```

#### C. Add JavaScript Functions
```javascript
var selectedFile = null;

function triggerFileInput() {
    document.getElementById('file-input').click();
}

function handleFileSelect(event) {
    var file = event.target.files[0];
    if (file) {
        // Check file size (50 MB limit for BB10)
        if (file.size > 50 * 1024 * 1024) {
            alert('File too large. Max 50 MB.');
            return;
        }
        
        selectedFile = file;
        showFilePreview(file);
    }
}

function showFilePreview(file) {
    var preview = document.getElementById('file-preview');
    var fileName = document.getElementById('file-name');
    var fileSize = document.getElementById('file-size');
    
    fileName.textContent = file.name;
    fileSize.textContent = formatFileSize(file.size);
    preview.style.display = 'block';
}

function sendMessageWithAttachment() {
    if (!selectedFile) {
        sendMessage(); // Regular text message
        return;
    }
    
    var formData = new FormData();
    formData.append('file', selectedFile);
    formData.append('chat_id', selectedChatId);
    formData.append('caption', document.getElementById('messageInput').value);
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/send_attachment', true);
    
    xhr.upload.onprogress = function(e) {
        if (e.lengthComputable) {
            var percentComplete = (e.loaded / e.total) * 100;
            updateUploadProgress(percentComplete);
        }
    };
    
    xhr.onload = function() {
        if (xhr.status === 200) {
            clearFile();
            fetchMessages(selectedChatId);
        } else {
            alert('Upload failed');
        }
    };
    
    xhr.send(formData);
}

function formatFileSize(bytes) {
    if (bytes < 1024) return bytes + ' B';
    if (bytes < 1024 * 1024) return (bytes / 1024).toFixed(1) + ' KB';
    return (bytes / (1024 * 1024)).toFixed(1) + ' MB';
}
```

**Estimated Lines of Code**: ~200-250 lines

---

### 3. CSS Styling
```css
.attach-button {
    background: transparent;
    border: none;
    color: #0088cc;
    font-size: 20px;
    cursor: pointer;
    padding: 8px;
}

.file-preview {
    background: #2a2a2a;
    padding: 10px;
    border-radius: 8px;
    margin-bottom: 10px;
}

.upload-progress {
    width: 100%;
    height: 4px;
    background: #1a1a1a;
    border-radius: 2px;
    overflow: hidden;
}

.upload-progress-bar {
    height: 100%;
    background: #0088cc;
    transition: width 0.3s;
}
```

**Estimated Lines of Code**: ~50-75 lines

---

## 🚧 BB10 Browser Compatibility Concerns

### Potential Issues:
1. **File Input Support**: BB10 browser may have limited file picker support
   - May only work for photos from camera/gallery
   - May not support multiple file selection
   - Document selection might be limited

2. **FormData API**: Need to verify BB10 supports `FormData` for file uploads
   - May need fallback to base64 encoding if FormData doesn't work

3. **File Size**: Large files may cause memory issues on BB10
   - Should enforce stricter limits (10-20 MB suggested)

4. **Upload Progress**: `xhr.upload.onprogress` may not work on BB10
   - May need to show indeterminate progress instead

### Testing Required:
- Test file input on actual BB10 device
- Test FormData upload
- Test with various file sizes
- Test image preview functionality

---

## ⏱️ Time Estimate

### Development Time:
- **Backend (Python)**: 3-4 hours
  - Multipart form parsing
  - Telethon integration
  - File handling and cleanup
  - Error handling

- **Frontend (HTML/JS/CSS)**: 4-5 hours
  - File input UI
  - Preview system
  - Upload progress
  - BB10 compatibility fixes

- **Testing & Debugging**: 3-4 hours
  - BB10 device testing
  - Various file types
  - Edge cases (large files, errors)
  - Network interruptions

- **Documentation**: 1 hour

**Total Estimated Time**: 11-14 hours

---

## 📦 Required Dependencies

### Python:
- No new dependencies needed! ✅
  - `cgi` module (built-in) for multipart form parsing
  - Telethon already installed and has `send_file()` method

### JavaScript:
- No new dependencies needed! ✅
  - FormData API (should be available on BB10)
  - XMLHttpRequest (already using)

---

## 🎯 Simplified MVP (Minimum Viable Product)

If you want to start smaller, here's a quick MVP:

### Phase 1: Photo Upload Only (4-6 hours)
- Single file input (photos only)
- No preview, just upload
- Basic error handling
- Test on BB10

### Phase 2: Add Document Support (2-3 hours)
- Support any file type
- File size validation
- File type detection

### Phase 3: Polish (3-4 hours)
- File preview
- Upload progress
- Better UI/UX
- Multiple file selection

---

## 🔑 Key Telethon API Methods

```python
# Basic file send
await client.send_file(chat_id, 'photo.jpg')

# With caption
await client.send_file(chat_id, 'document.pdf', caption='Here is the file')

# Force as document (not inline photo)
await client.send_file(chat_id, 'photo.jpg', force_document=True)

# With attributes (for voice messages, etc.)
from telethon.tl.types import DocumentAttributeAudio
await client.send_file(
    chat_id, 
    'audio.mp3',
    attributes=[DocumentAttributeAudio(duration=120, voice=True)]
)
```

---

## ✅ Pros of Adding This Feature

1. **Complete Telegram Experience**: Users can share photos, documents, etc.
2. **Telethon Makes It Easy**: `send_file()` handles all the complexity
3. **No New Dependencies**: Everything we need is already available
4. **Incremental Development**: Can start with photos only

## ⚠️ Cons / Challenges

1. **BB10 Browser Limitations**: File input may be limited or buggy
2. **Testing Required**: Need real device to verify functionality
3. **File Size Management**: Need careful handling to avoid crashes
4. **Storage Space**: Temporary files need to be managed properly

---

## 🎨 UI Mockup (Text-Based)

```
┌─────────────────────────────────────┐
│  Telegram - Chat with John          │
├─────────────────────────────────────┤
│                                      │
│  ┌──────────────────────────┐      │
│  │ You: Here's the photo!   │      │
│  │ [📷 image.jpg 2.3 MB]    │      │
│  │ 3:45 PM                  │      │
│  └──────────────────────────┘      │
│                                      │
│  ┌──────────────────────────────┐  │
│  │ John: Thanks!                │  │
│  │ 3:46 PM                      │  │
│  └──────────────────────────────┘  │
│                                      │
├─────────────────────────────────────┤
│ [📎] [Type a message...      ] [▶] │
│                                      │
│ ┌─ Selected: photo.jpg (2.3 MB) ─┐ │
│ │ [Cancel]                    [✓] │ │
│ └─────────────────────────────────┘ │
└─────────────────────────────────────┘
```

---

## 🚀 Recommendation

**Start with Phase 1 (Photo Upload MVP)** - 4-6 hours of work

This will let you:
1. Test if file uploads work on BB10
2. Validate the Telethon integration
3. Get core functionality working
4. Decide if you want to expand to full attachment support

**Is it worth it?**
- If photos are important → YES, definitely worth 4-6 hours
- If full attachments needed → Plan for 11-14 hours
- If BB10 file input is broken → May need alternative approach (upload from URL, etc.)

Would you like me to implement the Phase 1 MVP (photo upload only) to test the waters?

