# BerryCore v0.74 Release Notes

**Release Date:** November 23, 2025
**Type:** Port Updates & Android Bridge Release

---

## Highlights

- **New App:** Term49Bridge-API - Android Runtime Access for BB10
- **New Port:** ELinks 0.17.0 - Text Browser with SSL/TLS + JavaScript
- **Port Update:** BerryPy 2.1.0
- **Enhanced Ecosystem:** Android API integration for advanced permissions

---

## New Features

### Term49Bridge-API - Android Runtime Bridge

The Term49Bridge-API enables Term49 (and other apps) to access the Android runtime layer on BB10, unlocking permissions and capabilities previously unavailable to native apps.

**What It Enables:**
- Background Audio Recording
- Advanced Notifications (rich notification API access)
- Enhanced Location Services (full GPS/location API)
- Phone State Access (call monitoring and management)
- System State Information (battery, network, device info)
- Advanced Permissions (Android-level permissions)

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

**Technical Details:**
- Exposes Android APIs through JNI integration
- Permission delegation and runtime API access
- Compatible with the Android app model on BB10

---

### ELinks 0.17.0 - Modern Text Browser

Full-featured text-based web browser with complete HTTPS support, JavaScript execution, and CSS rendering.

**Key Features:**
- SSL/TLS Support with bundled Mozilla CA certificates (150+ root CAs)
- JavaScript Engine powered by QuickJS (ES2020+)
- CSS Rendering via libcss + libdom
- Wildcard SSL certificate handling
- App Sandbox Compatible
- UTF-8 Support
- Protocols: HTTP, HTTPS, FTP, File

**Browser Features:**
- Cookies, bookmarks, history
- HTML5 parsing, form submission
- Download manager, tabbed browsing, search in page

**Installation:**
```bash
qpkg install elinks

# Run with launcher (recommended - sets up SSL)
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
The launcher script (`elinks_run.sh`) automatically:
1. Sets `LD_LIBRARY_PATH` to use BerryCore's OpenSSL 1.0.0 libraries (wildcard SSL support)
2. Configures `CURL_CA_BUNDLE` and `SSL_CERT_FILE` to use bundled Mozilla CA certificates
3. Handles app sandbox restrictions (HOME in read-only appdata, falls back to `/tmp`)

**Technical Specs:**
- Version: 0.17.0
- Binary Size: 2.2 MB | Port Size: 1.3 MB
- SSL: OpenSSL 1.0.1i + Mozilla CA bundle (225KB)
- JavaScript: QuickJS (static linked)
- CSS: libcss 0.9.2 | DOM: libdom (NetSurf)
- Build: GCC 9.3.0, ARMv7-A EABI5

---

## Available Ports (7 total)

| Port | Category | Size | Description |
|------|----------|------|-------------|
| **elinks** (NEW) | web | 1.1 MB | Text browser with SSL/TLS + JavaScript |
| **python3** | lang | 25 MB | Python 3.11.10 + pip |
| **apache-php** | web | 43 MB | Apache 2.4.58 + PHP 7.4.33 |
| **berrypy** | web | 75 KB | App platform manager (v2.1.0) |
| **berrysnip** | util | 24 KB | Snippet & notes manager |
| **hydra** | net | 165 KB | Password auditing tool |
| **tmux** | sys | 2.5 MB | Terminal multiplexer 3.3a |

---

## Updates & Changes

### Port System
- Added ELinks 0.17.0 port
- Updated BerryPy 2.0 to 2.1.0 (smart requirements)
- INDEX updated with ELinks entry
- CATALOG updated with ELinks binaries

### Bar Files
- Added Term49Bridge-API.apk (Android runtime integration)
- Location: `bar-files/Term49Bridge-API.apk`

---

## Statistics

- **Core Packages:** 73
- **Binary Count:** 100+
- **Port Count:** 7 installable ports
- **Total Size:** ~270 MB (core) + ~72 MB (all ports)

---

## Upgrade Instructions

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
qpkg install elinks
elinks_run.sh https://news.ycombinator.com

# Update BerryPy (if already installed)
qpkg install berrypy
berrypy start
```

### Install Term49Bridge-API:

1. Transfer `bar-files/Term49Bridge-API.apk` to your device
2. Install via Android APK installer on BB10
3. No additional configuration needed
4. Compatible apps will automatically detect and use it

---

## Testing

### Tested On:
- BlackBerry Passport (QNX 8)
- BlackBerry Q10 (QNX 8)

### Results:

**ELinks:** HTTPS loads correctly, wildcard SSL works, JavaScript functional, CSS rendering operational, app sandbox compatible, downloads and bookmarks working.

**Term49Bridge-API:** APK installs, Android runtime exposure working, permission delegation functional, compatible with Term49.

---

## Known Issues

### ELinks
- Some modern sites may have compatibility issues with older SSL (OpenSSL 1.0.1i)
- JavaScript engine is ES2020+ but some complex sites may not render perfectly
- CSS rendering is basic (not full modern CSS3)

### Term49Bridge-API
- Requires proper installation via APK installer
- Only works with compatible apps
- Android permissions model on BB10 has limitations

### Core
None reported for v0.74. All core functionality tested and working.

---

## Links

- **Repository:** https://github.com/sw7ft/BerryCore
- **Releases:** https://github.com/sw7ft/BerryCore/releases
- **Issues:** https://github.com/sw7ft/BerryCore/issues
