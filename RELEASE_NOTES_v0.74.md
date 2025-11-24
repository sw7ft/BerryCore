# BerryCore v0.74 Release Notes

**Release Date:** November 23, 2025  
**Type:** Port Updates & Android Bridge Release

---

## 🎯 Highlights

- **New App:** Term49Bridge-API - Android Runtime Access for BB10
- **New Port:** ELinks 0.17.0 - Text Browser with SSL/TLS + JavaScript
- **Port Updates:** BerryPy 2.1.0, Telegram V7, RocketChat V3
- **Enhanced Ecosystem:** Android API integration for advanced permissions

---

## ✨ New Features

### 🌉 Term49Bridge-API - Android Runtime Bridge

**Revolutionary Android Integration for BB10!**

The Term49Bridge-API enables Term49 (and other apps) to access the Android runtime layer on BB10, unlocking permissions and capabilities previously unavailable to native apps.

**What It Enables:**
- 🎤 **Background Audio Recording** - Record audio even when app is backgrounded
- 🔔 **Advanced Notifications** - Rich notification API access
- 📍 **Enhanced Location Services** - Full GPS/location API access
- 📞 **Phone State Access** - Call monitoring and management
- 📱 **System State Information** - Battery, network, device info
- 🔐 **Advanced Permissions** - Access to Android-level permissions

**Why This Matters:**
BlackBerry 10's native API is limited. Many advanced features require Android permissions. Term49Bridge-API exposes the Android runtime, allowing developers to create BB10 apps with Android-level capabilities.

**Use Cases:**
- Voice recording apps that work in background
- Advanced automation tools
- System monitoring applications
- Enhanced terminal features
- Custom notification systems

**Installation:**
- Located in: `bar-files/Term49Bridge-API.apk`
- Install via Android APK installer on BB10
- Integrates with Term49 and compatible apps
- No additional configuration needed

**Developer Info:**
- Exposes Android API to BlackBerry runtime
- Bridge layer for permission escalation
- Compatible with Term49 and future apps
- Documentation for developers coming soon

---

### 🌐 ELinks 0.17.0 - Modern Text Browser

**Full-Featured Text-Based Web Browser with SSL/TLS Support!**

ELinks brings modern web browsing to the terminal with complete HTTPS support, JavaScript execution, and CSS rendering.

**Key Features:**
- ✅ **SSL/TLS Support** - Browse HTTPS sites securely with bundled Mozilla CA certificates
- ✅ **JavaScript Engine** - Powered by QuickJS (ES2020+)
- ✅ **CSS Rendering** - libcss + libdom for proper styling
- ✅ **Wildcard SSL Fixed** - Handles *.example.com certificates
- ✅ **App Sandbox Compatible** - Works in restricted environments
- ✅ **UTF-8 Support** - International character support

**Protocols Supported:**
- HTTP/HTTPS
- FTP
- File://

**Browser Features:**
- Cookies, bookmarks, history
- HTML5 parsing
- Form submission
- Download manager
- Tabbed browsing
- Search in page

**Installation:**
```bash
qpkg install elinks

# Run with launcher (recommended)
elinks_run.sh https://example.com

# Or run directly
elinks https://github.com
```

**Keyboard Commands:**
```
g        - Go to URL
/        - Search in page
n        - Next search result
ESC      - Main menu
s        - Save page
d        - Download link
Backspace - Go back
q        - Quit
?        - Help
```

**SSL/TLS Configuration:**
The launcher script automatically configures SSL certificates using the bundled Mozilla CA certificate bundle (225KB), ensuring compatibility with modern HTTPS sites including those using wildcard certificates. No additional configuration required!

**Technical Details:**
- Version: 0.17.0
- Binary Size: 2.2 MB
- Port Size: 1.3 MB (with SSL certificates)
- SSL: OpenSSL 1.0.1i (QNX system) + Mozilla CA bundle (225KB, 150+ root certificates)
- JavaScript: QuickJS (static linked)
- CSS: libcss 0.9.2
- DOM: libdom (NetSurf)
- Build: GCC 9.3.0, ARMv7-A EABI5

---

### 📱 BerryPy 2.1.0 - Smart App Requirements

**Updated:** Enhanced app installation experience with intelligent requirement detection.

**What's New:**
- ⚠️ **Pre-Install Requirements** - See prerequisites before installing
- 📋 **Setup Instructions** - Step-by-step guidance for each app
- ✅ **Post-Install Notifications** - Setup reminders after installation
- 🔗 **Resource Links** - Direct links to API documentation
- 📚 **Enhanced Catalog** - Rich metadata for better discovery

**New Apps Available via BerryPy:**
- **Telegram V7** - Full-featured Telegram client
  - Default API credentials included (no registration needed!)
  - Photo attachments with inline viewing
  - Document downloads
  - Chat search
  - Background notifications
  - Infinite scroll
  - Port: 8010

- **RocketChat V3** - Team messaging platform
  - BB10-compatible JavaScript (forEach/includes fixed)
  - Manual refresh for new messages
  - Real-time notifications via PPS
  - Search conversations
  - Improved message sending
  - Port: 8020

**Developer Benefits:**
App creators can now specify:
- Required API keys
- Account prerequisites
- Phone number requirements
- Setup steps
- Configuration instructions
- Resource links

This dramatically improves the user installation experience!

---

## 📦 Available Ports (7 total)

| Port | Category | Size | Description |
|------|----------|------|-------------|
| **elinks** ⭐ NEW | web | 1.1 MB | Text browser with SSL/TLS + JavaScript |
| **python3** | lang | 25 MB | Python 3.11.10 + pip |
| **apache-php** | web | 43 MB | Apache 2.4.58 + PHP 7.4.33 |
| **berrypy** | web | 75 KB | App platform manager (v2.1.0) |
| **berrysnip** | util | 24 KB | Snippet & notes manager |
| **hydra** | net | 165 KB | Password auditing tool |
| **tmux** | sys | 2.5 MB | Terminal multiplexer 3.3a |

---

## 🛠️ Updates & Changes

### Port System
- **Added:** ELinks 0.17.0 port (web browser)
- **Updated:** BerryPy 2.0 → 2.1.0 (smart requirements)
- **Enhanced:** INDEX with ELinks entry
- **Maintained:** 7 total ports available

### Documentation
- **Added:** ELinks usage documentation
- **Updated:** CATALOG with ELinks binaries
- **Enhanced:** Port descriptions

### Bar Files
- **Added:** Term49Bridge-API.apk (newest version)
- **Purpose:** Android runtime integration
- **Location:** `bar-files/Term49Bridge-API.apk`

---

## 🔧 Technical Details

### ELinks SSL/TLS Configuration

ELinks uses a launcher script (`elinks_run.sh`) that:
1. Sets `LD_LIBRARY_PATH` to use BerryCore's OpenSSL 1.0.0 libraries (wildcard SSL support)
2. Configures `CURL_CA_BUNDLE` to use bundled Mozilla CA certificates (150+ root CAs)
3. Sets `SSL_CERT_FILE` to the bundled certificate bundle
4. Handles app sandbox restrictions (HOME in read-only appdata)
5. Falls back to `/tmp` for config if needed

**SSL Certificate Bundle:**
- **Source:** Mozilla CA Certificate Store (latest)
- **Location:** `$NATIVE_TOOLS/share/elinks/ssl/cacert.pem`
- **Size:** 225 KB (uncompressed)
- **Root CAs:** 150+ trusted certificate authorities
- **Coverage:** Works with all major HTTPS sites including wildcard certificates

This ensures ELinks can securely browse modern HTTPS websites without manual certificate configuration.

### BerryPy Catalog Format

New catalog format includes:
```json
{
  "requirements": {
    "api_keys": ["Telegram API ID", "Telegram API Hash"],
    "accounts": ["Telegram account"],
    "other": ["Phone number for verification"]
  },
  "setup_steps": [
    "Step 1: Visit my.telegram.org/apps",
    "Step 2: Register your application",
    ...
  ],
  "resources": {
    "api_docs": "https://...",
    "support": "https://...",
    "documentation": "https://..."
  }
}
```

See `docs/CATALOG_FORMAT.md` in BerryPy for full specification.

### Term49Bridge-API

The bridge exposes Android APIs through:
- JNI (Java Native Interface) integration
- Permission delegation
- Runtime API access
- Compatible with Android app model on BB10

---

## 📊 Statistics

**Core Packages:** 73 packages  
**Binary Count:** 100+  
**Port Count:** 7 installable ports  
**Total Size:** ~270 MB (core) + ~72 MB (all ports)

---

## 🔄 Upgrade Instructions

### From v0.73 or earlier:

```bash
# Update BerryCore
qpkg update

# Or manual installation
cd /accounts/1000/shared/documents
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.74/berrycore.zip
curl -L -O https://github.com/sw7ft/BerryCore/releases/download/v0.74/install.sh
chmod +x install.sh
./install.sh
```

### Install New Ports:

```bash
# Install ELinks browser
qpkg install elinks
elinks_run.sh https://news.ycombinator.com

# Update BerryPy (if already installed)
qpkg install berrypy

# Try Telegram via BerryPy
berrypy start
# Browse to http://127.0.0.1:8001
```

### Install Term49Bridge-API:

1. Transfer `bar-files/Term49Bridge-API.apk` to your device
2. Install via Android APK installer on BB10
3. No additional configuration needed
4. Compatible apps will automatically detect and use it

---

## 🧪 Testing

### Tested On:
- BlackBerry Passport (QNX 8)
- BlackBerry Q10 (QNX 8)

### Test Results:

**ELinks:**
- ✅ HTTPS sites load correctly
- ✅ Wildcard SSL certificates work
- ✅ JavaScript execution functional
- ✅ CSS rendering operational
- ✅ App sandbox compatibility verified
- ✅ Downloads working
- ✅ Bookmarks and history functional

**BerryPy 2.1.0:**
- ✅ Smart requirements display working
- ✅ Pre-install checks functional
- ✅ Post-install notifications working
- ✅ Telegram V7 app installs correctly
- ✅ RocketChat V3 app installs correctly
- ✅ Setup instructions display properly

**Term49Bridge-API:**
- ✅ APK installs on BB10
- ✅ Android runtime exposure working
- ✅ Permission delegation functional
- ✅ Compatible with Term49

---

## 📝 Known Issues

### ELinks
- Some modern sites may have compatibility issues with older SSL (OpenSSL 1.0.1i)
- JavaScript engine is ES2020+ but some sites may not work perfectly
- CSS rendering is basic (not full modern CSS3)

### Term49Bridge-API
- Requires proper installation via APK installer
- Only works with compatible apps
- Android permissions model on BB10 has limitations

### None reported for v0.74 core
All core functionality tested and working.

---

## 🔮 Coming Soon

- **ELinks 0.18+:** Newer version when available
- **More Android Bridge Apps:** Applications leveraging Term49Bridge-API
- **Additional Ports:** Community requests
- **Documentation:** Developer guide for Term49Bridge-API
- **Enhanced BerryPy:** More apps with smart requirements

---

## 💡 Usage Examples

### ELinks Web Browsing:
```bash
# Browse Hacker News
elinks_run.sh https://news.ycombinator.com

# Check GitHub
elinks_run.sh https://github.com/sw7ft/BerryCore

# Dump page to text
elinks -dump https://example.com > page.txt

# Offline mode
elinks -no-connect
```

### BerryPy App Management:
```bash
# Start BerryPy
berrypy start

# Access web interface
# Browse to: http://127.0.0.1:8001

# Install Telegram V7
# (via web interface - see requirements before installing)

# View logs
berrypy logs
```

### Term49Bridge-API:
```bash
# Install APK first
# Then compatible apps will automatically use it

# Example: Record audio in background (with compatible app)
# Example: Enhanced notifications (with compatible app)
```

---

## 👥 Contributors

- BerryCore Team
- ELinks Project
- QuickJS Project
- NetSurf Libraries Team
- Community testers
- Port contributors

---

## 📄 License

BerryCore is provided as-is for BlackBerry 10 enthusiasts.  
Individual packages retain their original licenses.

---

## 🔗 Links

- **Repository:** https://github.com/sw7ft/BerryCore
- **Releases:** https://github.com/sw7ft/BerryCore/releases
- **Documentation:** https://github.com/sw7ft/BerryCore/tree/main/docs
- **Issues:** https://github.com/sw7ft/BerryCore/issues

---

## 💬 Feedback

Found a bug? Have a feature request? Want to contribute a port?

Open an issue or discussion on GitHub!

---

**Thank you for using BerryCore!** 🍇

*Keeping BlackBerry 10 alive with modern capabilities.*

---

## 🎉 Special Thanks

Special thanks to the developers who made this release possible:
- The ELinks team for creating an amazing text browser
- The QuickJS team for a powerful JavaScript engine
- The NetSurf project for CSS/DOM libraries
- The BerryPy app developers for creating Telegram and RocketChat clients
- The BlackBerry 10 community for continued support

This release represents hundreds of hours of compilation, testing, and debugging to bring these modern tools to BB10!


