# BerryCore Priority Package List

## 🎯 Immediate Priorities (Quick Wins)

These packages are essential, relatively easy to compile, and provide immediate value.

### Tier 1: Critical Missing Utilities

| Package | Version | Size Est. | Priority | Difficulty | Reason |
|---------|---------|-----------|----------|------------|---------|
| **sed** | 4.8 | ~300KB | 🔴 Critical | Easy | Essential for text processing, many scripts depend on it |
| **gawk** | 5.1 | ~1MB | 🔴 Critical | Easy | Text processing, scripting essential |
| **less** | 590 | ~200KB | 🔴 Critical | Easy | File pager, essential for reading files |
| **pkg-config** | 0.29 | ~100KB | 🔴 Critical | Easy | Build system essential, many packages need it |
| **nano** | 6.0 | ~500KB | 🟠 High | Easy | User-friendly editor alternative to vi |
| **tree** | 2.0 | ~50KB | 🟠 High | Easy | Directory visualization |
| **htop** | 3.2 | ~200KB | 🟠 High | Medium | System monitoring (may need ncurses) |
| **netcat** | 1.10 | ~100KB | 🟠 High | Easy | Network debugging essential |
| **which** | 2.21 | ~50KB | 🔴 Critical | Easy | Find executables in PATH |
| **lsof** | 4.94 | ~300KB | 🟠 High | Medium | List open files, debugging |

**Estimated Total**: ~2.8 MB  
**Time to Complete**: 1-2 days

### Tier 2: Development Essentials

| Package | Version | Size Est. | Priority | Difficulty | Reason |
|---------|---------|-----------|----------|------------|---------|
| **CMake** | 3.25 | ~8MB | 🔴 Critical | Medium | Modern build system, many projects use it |
| **gdb** | 12.1 | ~5MB | 🔴 Critical | Hard | Debugger essential for development |
| **Perl** | 5.36 | ~12MB | 🔴 Critical | Hard | Many build systems depend on it |
| **Python3** | 3.11 | ~20MB | 🔴 Critical | Hard | Modern scripting essential (if not present) |
| **ninja** | 1.11 | ~500KB | 🟠 High | Easy | Fast build system, pairs with CMake |
| **ctags** | 5.9 | ~500KB | 🟠 High | Easy | Code navigation |
| **cscope** | 15.9 | ~300KB | 🟢 Medium | Easy | C code browser |

**Estimated Total**: ~46 MB  
**Time to Complete**: 1-2 weeks

### Tier 3: Enhanced User Experience

| Package | Version | Size Est. | Priority | Difficulty | Reason |
|---------|---------|-----------|----------|------------|---------|
| **ack** / **ag** | 3.5 / 2.2 | ~500KB | 🟠 High | Easy | Fast code search |
| **ripgrep** | 13.0 | ~1.5MB | 🟢 Medium | Medium | Ultra-fast search (Rust) |
| **fzf** | 0.38 | ~1MB | 🟢 Medium | Medium | Fuzzy finder |
| **screen** | 4.9 | ~500KB | 🟢 Medium | Easy | Terminal multiplexer alternative |
| **ncdu** | 1.18 | ~100KB | 🟠 High | Easy | Disk usage analyzer |
| **iftop** | 1.0 | ~100KB | 🟢 Medium | Medium | Network bandwidth monitor |

**Estimated Total**: ~3.7 MB  
**Time to Complete**: 3-5 days

## 🔧 Medium Priority Additions

### Development Tools

| Package | Version | Size Est. | Priority | Difficulty | Dependencies |
|---------|---------|-----------|----------|------------|-------------|
| **strace** | 5.19 | ~1MB | 🟠 High | Hard | Low-level QNX compat issues |
| **ltrace** | 0.7.3 | ~500KB | 🟢 Medium | Hard | Binary instrumentation |
| **valgrind** | 3.20 | ~15MB | 🟢 Medium | Very Hard | ARM/QNX compat uncertain |
| **doxygen** | 1.9.6 | ~8MB | 🟢 Medium | Medium | Requires Perl |
| **ccache** | 4.7 | ~500KB | 🟢 Medium | Easy | Compiler cache |
| **distcc** | 3.4 | ~500KB | 🟢 Medium | Medium | Distributed compilation |

### Scripting Languages

| Package | Version | Size Est. | Priority | Difficulty | Dependencies |
|---------|---------|-----------|----------|------------|-------------|
| **Ruby** | 3.1 | ~10MB | 🟢 Medium | Hard | Build toolchain |
| **Node.js** | 18.x LTS | ~20MB | 🟠 High | Very Hard | Complex build, may need older version |
| **Lua** | 5.4 | ~300KB | 🟢 Medium | Easy | Lightweight scripting |
| **Tcl** | 8.6 | ~2MB | 🟢 Medium | Easy | Scripting, Expect dependency |
| **expect** | 5.45 | ~500KB | 🟢 Medium | Easy | Automation (needs Tcl) |

### Network Tools

| Package | Version | Size Est. | Priority | Difficulty | Dependencies |
|---------|---------|-----------|----------|------------|-------------|
| **nmap** | 7.93 | ~8MB | 🟢 Medium | Medium | OpenSSL, pcap |
| **tcpdump** | 4.99 | ~1MB | 🟠 High | Medium | libpcap |
| **socat** | 1.7.4 | ~300KB | 🟠 High | Easy | Network utility |
| **telnet** | 0.17 | ~100KB | 🟠 High | Easy | Remote access |
| **whois** | 5.5 | ~100KB | 🟢 Medium | Easy | Domain lookup |
| **traceroute** | 2.1 | ~100KB | 🟢 Medium | Easy | Network diagnostic |
| **mtr** | 0.95 | ~200KB | 🟢 Medium | Medium | Network diagnostic |

## 📦 Lower Priority / Nice to Have

### Data Processing

| Package | Size Est. | Priority | Notes |
|---------|-----------|----------|-------|
| **xmllint** (libxml2) | ~2MB | 🟢 Medium | XML processing |
| **csvtool** | ~500KB | 🟡 Low | CSV processing |
| **pandoc** | ~30MB | 🟡 Low | Document converter (large) |
| **imagemagick** | ~20MB | 🟡 Low | Image processing |
| **graphicsmagick** | ~10MB | 🟢 Medium | Lighter ImageMagick alternative |

### Modern CLI Tools (Rust-based, may be challenging)

| Package | Size Est. | Priority | Notes |
|---------|-----------|----------|-------|
| **bat** | ~2MB | 🟡 Low | Better cat (Rust) |
| **exa** | ~500KB | 🟡 Low | Modern ls (Rust) |
| **fd** | ~1MB | 🟡 Low | Better find (Rust) |
| **dust** | ~1MB | 🟡 Low | Better du (Rust) |
| **procs** | ~1MB | 🟡 Low | Better ps (Rust) |

### Version Control

| Package | Size Est. | Priority | Notes |
|---------|-----------|----------|-------|
| **mercurial** (hg) | ~5MB | 🟡 Low | Requires Python |
| **subversion** (svn) | ~8MB | 🟡 Low | Older VCS |
| **cvs** | ~1MB | 🟡 Low | Very old VCS |

### Security Tools

| Package | Size Est. | Priority | Notes |
|---------|-----------|----------|-------|
| **gnupg** (gpg) | ~8MB | 🟢 Medium | Encryption |
| **pass** | ~100KB | 🟡 Low | Password manager (needs gpg, git) |
| **hashcat** | ~5MB | 🟡 Low | Password recovery |
| **john** | ~3MB | 🟡 Low | Password cracker |

### Specialized Tools

| Package | Size Est. | Priority | Notes |
|---------|-----------|----------|-------|
| **minicom** | ~300KB | 🟢 Medium | Serial terminal |
| **picocom** | ~100KB | 🟢 Medium | Minimal serial terminal |
| **dialog** | ~300KB | 🟢 Medium | Shell UI |
| **pv** | ~100KB | 🟢 Medium | Pipe viewer |
| **watch** | ~50KB | 🟠 High | Command repeater |
| **parallel** | ~500KB | 🟢 Medium | Parallel execution (GNU) |

## 📊 Development Roadmap

### Phase 1: Foundation (Week 1-2)
**Goal**: Add critical missing utilities that scripts depend on

- [ ] sed
- [ ] gawk  
- [ ] less
- [ ] which
- [ ] pkg-config
- [ ] nano
- [ ] tree
- [ ] netcat

**Deliverable**: Basic scripting and text processing capability

### Phase 2: Development Core (Week 3-5)
**Goal**: Enable modern C/C++ development

- [ ] CMake
- [ ] ninja
- [ ] Perl (for build systems)
- [ ] ctags
- [ ] gdb
- [ ] strace (if possible)

**Deliverable**: Modern build and debug environment

### Phase 3: Enhanced Experience (Week 6-7)
**Goal**: Improve user experience and monitoring

- [ ] htop
- [ ] ncdu
- [ ] screen
- [ ] ack/ag
- [ ] watch
- [ ] lsof

**Deliverable**: Better system visibility and usability

### Phase 4: Scripting & Automation (Week 8-10)
**Goal**: Add scripting language support

- [ ] Python 3.x (if not present)
- [ ] Lua
- [ ] Tcl + expect
- [ ] Ruby (optional)

**Deliverable**: Rich scripting environment

### Phase 5: Network & Security (Week 11-12)
**Goal**: Network debugging and security tools

- [ ] tcpdump
- [ ] socat
- [ ] telnet
- [ ] gnupg
- [ ] nmap (optional)

**Deliverable**: Network troubleshooting capability

### Phase 6: Quality of Life (Week 13-14)
**Goal**: Modern CLI enhancements

- [ ] fzf
- [ ] ripgrep (if feasible)
- [ ] pv
- [ ] parallel

**Deliverable**: Modern, efficient CLI experience

## 🎯 Success Metrics

### Phase 1 Success Criteria
- ✅ All Tier 1 packages installed
- ✅ Can run common shell scripts
- ✅ Text processing works (sed/awk)
- ✅ File navigation improved (less, tree)

### Phase 2 Success Criteria
- ✅ Can build C/C++ projects with CMake
- ✅ Can debug with gdb
- ✅ Perl scripts work
- ✅ Code navigation available

### Overall Success Criteria
- ✅ 90% of common development workflows supported
- ✅ User experience comparable to modern Linux
- ✅ All packages stable on BlackBerry 10
- ✅ Total package size < 100 MB additional

## 📝 Notes

### Compilation Complexity Ratings

- **Easy**: Single binary, minimal dependencies, straightforward configure/make
- **Medium**: Multiple binaries, some library dependencies, standard build
- **Hard**: Complex dependencies, requires patching, non-standard build
- **Very Hard**: Extensive porting needed, may not be feasible

### Priority Ratings

- 🔴 **Critical**: Essential for basic functionality
- 🟠 **High**: Important for good user experience
- 🟢 **Medium**: Nice to have, improves specific workflows
- 🟡 **Low**: Optional, for specialized use cases

## 🤝 Community Input

Please provide feedback on priorities via:
- GitHub Issues
- Pull Requests
- Community Forums

Your input helps shape the roadmap!

---

**Last Updated**: October 2025  
**Next Review**: After Phase 1 completion

