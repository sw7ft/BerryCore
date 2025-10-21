# 🍇 **Introducing BerryCore for BlackBerry 10 Devices**

### **A Project of the SW7FT Initiative**  
### **BerryCore – QNX Extended Userland**

---

## 🧭 **Overview**

**BerryCore** is the **QNX Extended Userland** — a modernized continuation of the open-source legacy started by **Berry Much OS**.  
It’s designed to breathe new life into **BlackBerry 10 and QNX devices**, transforming them into capable development and experimentation environments once again.  

BerryCore provides an expanded runtime layer, updated binaries, and streamlined environment scripts (`env.sh`) that make adding and using modern software on QNX simple and consistent.

---

## 🕰️ **Honoring the Legacy**

This project is built as a **continuation and tribute** to the incredible work done by the developers of **Berry Much OS**.  
Their dedication to keeping the **BlackBerry 10 and QNX platform alive** laid the foundation for everything that follows here.  

Without their ingenuity — rebuilding toolchains, porting compilers, and proving that these devices could still be productive, programmable, and free — this project would simply **not be possible**.  

Berry Much OS didn’t just keep QNX breathing; it **redefined what persistence in open-source looks like**.  
BerryCore exists as a **homage** to that spirit — to extend their work, modernize it, and continue making BlackBerry hardware relevant in a new era.

---

## 🎯 **Purpose**

The goal of BerryCore is to **carry the torch forward** — refining, expanding, and repackaging the Berry Much ecosystem into a modern, modular, and extensible runtime environment for QNX devices.  

This new effort focuses on **streamlining the process of adding and maintaining modern binaries** (Python, Git, GCC, SSH, etc.) while expanding the **system layer** with new libraries, command-line tools, and utilities that make QNX more capable for developers and experimenters.

---

## ⚙️ **Core Objectives**

- 🧱 **Streamline Binary Integration**  
  Simplify the process of compiling and adding modern binaries to QNX, ensuring compatibility, stability, and clean system paths.  

- ⚙️ **Expand the System Environment**  
  Add more tools, libraries, and utilities to bring the QNX userland closer to a modern UNIX-like experience — while retaining its reliability and small footprint.  

- 💻 **Enable Modern App Development**  
  Support application development using **Python**, **C**, **X servers**, and any other frameworks that can be adapted to QNX.  
  The goal is to create a flexible environment where both graphical and command-line applications can coexist and evolve.  

- 🐍 **Modern Scripting and APIs**  
  Continue support for Python, JavaScript, and REST-based control layers, allowing automation and local system scripting.  

- 🔄 **Cross-Platform Portability**  
  Maintain compatibility with **legacy BB10 devices**, while expanding to **QNX 8.x**, **ARM**, and **RISC-V** embedded builds.  

- 🤝 **Community Collaboration**  
  Build an open developer ecosystem for sharing precompiled binaries, system extensions, and QNX development tools.

---

## 🙏 **Acknowledgements**

To the **Berry Much OS developers**, contributors, testers, and community — **thank you**.  
Your work has preserved a piece of computing history and inspired a generation of hobbyists, engineers, and educators.  

This project is dedicated to you, and to the enduring legacy of the **BlackBerry and QNX development community** — those who believed these devices still had something to give.

---

## 🚀 **Moving Forward**

Our mission is simple:  
To **extend**, **modernize**, and **streamline** the vision of Berry Much OS.  

By uniting QNX’s real-time reliability with modern open-source tooling, we aim to make these devices **usable, hackable, and developer-friendly again** — both as daily drivers and as educational systems for embedded computing.

---

## 🧩 **Project Information**

**Project Name:** BerryCore – QNX Extended Userland  
**Parent Initiative:** SW7FT QNX Development Stack  
**Inspired by:** [Berry Much OS](https://github.com/BerryFarm/BerryMuch)  
**Platform:** QNX / BlackBerry 10  
**Focus:** Modern Binaries, System Expansion, Developer Tools  
**Status:** In Active Development  
**License:** Open Source (TBD)

---

### 🧰 Example Structure

```bash
/berrycore/
├── bin/             # Modern binaries (python3, git, curl, etc.)
├── lib/             # Supporting shared libraries
├── include/         # Headers for SDK integration
├── env.sh           # Environment setup for PATH and LD_LIBRARY_PATH
└── docs/            # Technical notes and build guides
