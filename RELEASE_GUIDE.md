# BerryCore Release Guide

This guide explains how to create and publish new BerryCore releases.

---

## Release Workflow

### 1. Prepare the Release

#### Update Version Numbers
- [ ] Update version in `README.md`
- [ ] Update version in `berrycore/env.sh` (welcome message)
- [ ] Update version in `CHANGELOG.md`
- [ ] Update version in `PACKAGES.md`

#### Update Documentation
- [ ] Add entry to `CHANGELOG.md` following Keep a Changelog format
- [ ] Update `PACKAGES.md` with new packages
- [ ] Mark new packages with ✨ NEW
- [ ] Update statistics (package count, total size)

#### Test Everything
- [ ] Run `./scan_packages.sh` - ensure no macOS junk
- [ ] Run `./clean_packages.sh` if needed
- [ ] Test installation on BlackBerry 10 device
- [ ] Verify all new packages work
- [ ] Test `bclist`, `bcinfo`, `bcmotd`
- [ ] Check MOTD fetching works

### 2. Create Release Package

```bash
# Navigate to project root
cd /Users/mp/Documents/GitHub/BerryCore

# Create berrycore.zip (the main package)
cd berrycore
zip -r ../berrycore.zip . -x "*.DS_Store" -x "__MACOSX/*" -x "temp/*"
cd ..

# Verify the package
unzip -l berrycore.zip | head -50

# Check size
ls -lh berrycore.zip
```

### 3. Git Commit and Tag

```bash
# Stage changes
git add .

# Commit with version message
git commit -m "Release v0.6.0 - BerryCore Launch

- Added 5 new packages (nano, nmap, sshpass, xeyes, quickjs)
- New binary catalog system
- MOTD integration
- Interactive installation
- Total: 69 packages
"

# Create annotated tag
git tag -a v0.6.0 -m "BerryCore v0.6.0

Major rebranding release with 5 new packages and enhanced user experience.

See CHANGELOG.md for full details.
"

# Push to GitHub
git push origin main
git push origin v0.6.0
```

### 4. Create GitHub Release

1. **Go to GitHub** → Repository → **Releases** → **Draft a new release**

2. **Choose tag**: Select `v0.6.0` (or create new)

3. **Release title**: `BerryCore v0.6.0 - QNX Extended Userland`

4. **Description**: Use this template:

```markdown
# 🍇 BerryCore v0.6.0

**First Official BerryCore Release!** 

This release marks the rebranding of Berry Much OS to BerryCore, with significant improvements and new packages.

## ✨ What's New

### New Packages (5)
- 📝 **nano 4.0** - User-friendly text editor
- 🔍 **nmap 7.95** - Network exploration and security scanner
- 🔐 **sshpass 1.06** - Non-interactive SSH authentication
- 👀 **xeyes 1.1.0** - X11 application with full X11 library stack
- ⚡ **QuickJS 2024.06** - Modern JavaScript engine (ES2023)

### New Features
- 📚 **Binary Catalog System** - Discover tools with `bclist`, `bcinfo`, `bcbins`
- 📢 **Message of the Day** - Stay updated with latest news
- 🎯 **Interactive Installation** - Choose custom installation directory
- 💬 **Enhanced Welcome Screen** - Better first-run experience

### Improvements
- Rebranded to **BerryCore**
- New installation path: `/accounts/1000/shared/misc/berrycore`
- Better documentation (4 new comprehensive guides)
- Fixed nmap data files location
- Improved POSIX compliance

## 📊 Statistics

- **Total Packages**: 69 (up from 64)
- **Total Size**: ~241 MB compressed
- **Binary Count**: 100+ commands available
- **Categories**: 13 different categories

## 📥 Installation

### Quick Start

1. Download `berrycore.zip` and `install.sh`
2. Transfer to your BlackBerry 10 device
3. Run: `sh install.sh`
4. Follow the prompts

### Requirements

- BlackBerry 10.3.x (QNX 6.5)
- ~500 MB free storage
- Terminal access

## 📖 Documentation

- [CHANGELOG.md](CHANGELOG.md) - Full version history
- [PACKAGES.md](PACKAGES.md) - Complete package list
- [INSTALLATION_SYSTEM.md](master-context/INSTALLATION_SYSTEM.md) - How it works
- [README.md](README.md) - Project overview

## 🆘 Support

- Issues: https://github.com/sw7ft/berrycore/issues
- Discussions: https://github.com/sw7ft/berrycore/discussions

## 🙏 Acknowledgments

This project continues the legacy of **Berry Much OS** and honors the incredible work of its developers and community.

## 📝 Full Changelog

See [CHANGELOG.md](CHANGELOG.md) for complete details.

---

**Previous Version**: Berry Much OS v0.5  
**Migration**: Automatic legacy detection during installation
```

5. **Attach Files**:
   - Upload `berrycore.zip` (main package)
   - Upload `install.sh`
   - (Optional) Upload `README.md`, `CHANGELOG.md`

6. **Set as latest release** ✅

7. **Publish release** 🚀

### 5. Update MOTD

Update the message of the day to announce the release:

```bash
# Update motd.txt in your repo
cat > motd.txt << 'EOF'
📢 BerryCore v0.6.0 Released! (Oct 21, 2025)
   🎉 First official BerryCore release
   ✨ 5 new packages: nano, nmap, sshpass, xeyes, quickjs
   📚 New catalog system - try 'bclist'
   📖 Full changelog: github.com/sw7ft/berrycore
EOF

git add motd.txt
git commit -m "Update MOTD for v0.6.0 release"
git push
```

### 6. Announce

- Post on relevant forums/communities
- Update project website (if any)
- Social media announcement
- Update Patreon supporters

---

## Version Numbering

BerryCore follows [Semantic Versioning](https://semver.org/):

- **MAJOR.MINOR.PATCH** (e.g., 0.6.0)
- **MAJOR**: Breaking changes, complete overhauls
- **MINOR**: New features, new packages, backwards-compatible
- **PATCH**: Bug fixes, documentation updates

### Examples:
- `0.6.0` → `0.6.1`: Bug fixes only
- `0.6.0` → `0.7.0`: New packages added
- `0.6.0` → `1.0.0`: Major milestone (e.g., 100 packages, major rewrite)

---

## Release Checklist

### Pre-Release
- [ ] All new packages tested on device
- [ ] No macOS junk in packages (`./scan_packages.sh`)
- [ ] Documentation updated
- [ ] CHANGELOG.md complete
- [ ] PACKAGES.md updated
- [ ] Version numbers bumped everywhere

### Release
- [ ] berrycore.zip created and tested
- [ ] Git committed and tagged
- [ ] GitHub release created
- [ ] Files uploaded
- [ ] Release published
- [ ] MOTD updated

### Post-Release
- [ ] Installation tested from GitHub
- [ ] Community announcement
- [ ] Monitor for issues
- [ ] Respond to user feedback

---

## Hotfix Process

For urgent bug fixes:

1. Create hotfix branch: `git checkout -b hotfix/0.6.1`
2. Make minimal fixes
3. Test thoroughly
4. Update CHANGELOG (add `[0.6.1] - YYYY-MM-DD` section)
5. Commit: `git commit -m "Hotfix v0.6.1 - Fix critical bug"`
6. Tag: `git tag -a v0.6.1 -m "Hotfix release"`
7. Push: `git push origin main && git push origin v0.6.1`
8. Create GitHub release (mark as "pre-release" if still testing)

---

## Tips

- **Test on actual hardware** before releasing
- **Keep releases focused** - don't add too much at once
- **Document everything** - users appreciate detailed changelogs
- **Respond to feedback** quickly after release
- **Be conservative** with version numbers (better to under-promise)

---

**Last Updated**: October 21, 2025  
**Next Release**: TBD (see PRIORITY_PACKAGES.md for roadmap)

