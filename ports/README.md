# BerryCore Ports Repository

Additional packages and ports that extend BerryCore functionality.

## What Are Ports?

Ports are additional software packages that can be installed on top of BerryCore. Unlike the core 73 packages that come with BerryCore, ports are optional and can be installed individually based on your needs.

## Installing Ports

```bash
# Browse available ports
qpkg ports

# Install a specific port
qpkg install <package-name>

# Examples:
qpkg install gcc-arm       # Install GCC 9.3.0 compiler
qpkg install apache-php    # Install Apache + PHP web stack
qpkg install hydra         # Install network security tool
```

### Post-Installation Steps

Some ports require additional setup after installation:

**Apache + PHP:**
```bash
qpkg install apache-php
apache-setup              # REQUIRED - configures Apache for BB10
apachectl start           # Start the web server
# Access at: http://[your-bb10-ip]:8080/
```

**Other ports:**
Most ports work immediately after installation. Check `qpkg info <binary>` for details.

## Available Ports

See the [INDEX](INDEX) file for a complete list of available ports with descriptions and versions.

## Port Categories

- **lang** - Programming languages (Python, Node.js, Ruby, etc.)
- **database** - Database systems (PostgreSQL, MySQL, Redis, etc.)
- **dev** - Development tools (CMake, Docker CLI, etc.)
- **net** - Networking tools (Wireshark, tcpdump, etc.)
- **util** - Utility programs
- **media** - Media processing tools
- **sys** - System utilities

## Creating Your Own Ports

See [PORTING_GUIDE.md](PORTING_GUIDE.md) for instructions on creating and submitting your own ports to the repository.

## Port Naming Convention

Ports follow this naming pattern:
```
category-name-version.zip
```

Examples:
- `lang-python-3.11.zip`
- `db-postgresql-15.zip`
- `net-wireshark-4.2.zip`

## Repository Structure

Ports are hosted on GitHub and installed via raw URLs:
```
https://github.com/sw7ft/BerryCore/raw/main/ports/lang-python-3.11.zip
```

## Contributing

To contribute a port:
1. Create your package following the [PORTING_GUIDE.md](PORTING_GUIDE.md)
2. Test it on your BB10 device
3. Submit a pull request with your port and INDEX entry
4. Include a brief description and any dependencies

---

**BerryCore Ports** - Extending BlackBerry 10 Capabilities

