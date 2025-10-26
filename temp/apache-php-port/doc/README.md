# Apache HTTP Server 2.4.58 + PHP 7.4.33 for BerryCore

A complete web server stack for BlackBerry 10! Run a full-featured Apache web server with PHP support directly on your device.

## What This Is

- **Apache HTTP Server 2.4.58** - Industry-standard web server
- **PHP 7.4.33** - Server-side scripting language with full CLI and CGI support
- **Complete Stack** - Everything needed to host websites, APIs, and web applications on BB10

## Installation

```bash
# Install via qpkg
qpkg install apache-php

# Run setup (creates required symlinks)
apache-setup

# Verify installation
httpd -v
# Should show: Server version: Apache/2.4.58 (Unix)

php -v
# Should show: PHP 7.4.33 (cli)
```

### Why Setup is Needed

Apache was compiled with hardcoded paths expecting to be installed at:
- `/accounts/1000/shared/misc/apache2/`
- `/accounts/1000/shared/misc/php/`

But BerryCore installs to `$NATIVE_TOOLS/share/`. The `apache-setup` command creates symlinks so Apache can find its files.

**Manual Setup (if needed):**
```bash
ln -s $NATIVE_TOOLS/share/apache2 /accounts/1000/shared/misc/apache2
ln -s $NATIVE_TOOLS/share/php /accounts/1000/shared/misc/php
```

## Quick Start

### 1. Start Apache

```bash
# Start the server
apachectl start

# Check if running
apachectl status

# Your server is now running!
# Access it at: http://[your-bb10-ip]:8080/
```

**Note**: Apache runs on port **8080** (not 80) because port 80 requires root privileges on QNX/BB10.

### 2. Test PHP

Create a test PHP file:

```bash
# Create a PHP info page
cat > $NATIVE_TOOLS/share/apache2/htdocs/info.php << 'EOF'
<?php
phpinfo();
?>
EOF

# Access it at: http://[your-bb10-ip]:8080/info.php
```

### 3. Stop Apache

```bash
# Stop the server
apachectl stop
```

## What's Included

### Apache 2.4.58
- Full-featured HTTP server
- All standard modules
- SSL/TLS support (mod_ssl)
- CGI/FastCGI support
- Reverse proxy capabilities
- Virtual hosts support
- .htaccess support

### PHP 7.4.33
- CLI (Command Line Interface)
- CGI (Common Gateway Interface)
- Full standard library
- Extensions included:
  - Database: mysqli, pdo, sqlite3
  - Web: curl, json, xml
  - Compression: zlib, bzip2
  - Encryption: openssl, hash
  - Graphics: gd (if available)
  - And many more!

## Configuration

### Apache Configuration

Main config file:
```
$NATIVE_TOOLS/share/apache2/conf/httpd.conf
```

Document root (web files):
```
$NATIVE_TOOLS/share/apache2/htdocs/
```

### PHP Configuration

PHP config file:
```
$NATIVE_TOOLS/share/php/lib/php.ini
```

Or use the CLI php.ini:
```
$NATIVE_TOOLS/share/php/etc/php.ini
```

## Common Tasks

### Change Apache Port

By default, BerryCore's Apache uses port **8080** (configured by `apache-setup`). To change it to a different port:

```bash
# Edit httpd.conf
nano /accounts/1000/shared/misc/apache2/conf/httpd.conf

# Find and change:
# Listen 8080
# To:
# Listen 3000  (or any other port)

# Also update ServerName:
# ServerName localhost:8080
# To:
# ServerName localhost:3000

# Restart Apache
apachectl restart
```

**Note**: Ports below 1024 (like 80) require root privileges on QNX/BB10.

### Enable PHP in Apache

PHP should be enabled by default. Verify by checking httpd.conf:

```bash
grep -i php $NATIVE_TOOLS/share/apache2/conf/httpd.conf
```

You should see lines like:
```apache
LoadModule php7_module modules/libphp7.so
AddHandler php7-script .php
```

### Create a Simple Website

```bash
# Go to document root
cd $NATIVE_TOOLS/share/apache2/htdocs

# Create index.php
cat > index.php << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>BB10 Web Server</title>
</head>
<body>
    <h1>Welcome to BlackBerry 10 Web Server!</h1>
    <p>Powered by Apache <?php echo $_SERVER['SERVER_SOFTWARE']; ?></p>
    <p>PHP Version: <?php echo PHP_VERSION; ?></p>
    <p>Current time: <?php echo date('Y-m-d H:i:s'); ?></p>
</body>
</html>
EOF

# View it at http://[your-bb10-ip]:8080/
```

### View Apache Logs

```bash
# Access log
tail -f $NATIVE_TOOLS/share/apache2/logs/access_log

# Error log
tail -f $NATIVE_TOOLS/share/apache2/logs/error_log
```

### Test PHP CLI

```bash
# Run PHP interactively
php -a

# Execute PHP code directly
php -r "echo 'Hello from BB10!';"

# Run a PHP script
echo '<?php echo "Hello World\n"; ?>' > test.php
php test.php
```

## Advanced Usage

### Virtual Hosts

Edit `$NATIVE_TOOLS/share/apache2/conf/extra/httpd-vhosts.conf`:

```apache
<VirtualHost *:80>
    ServerName mysite.local
    DocumentRoot "$NATIVE_TOOLS/share/apache2/htdocs/mysite"
    <Directory "$NATIVE_TOOLS/share/apache2/htdocs/mysite">
        AllowOverride All
        Require all granted
    </Directory>
</VirtualHost>
```

### Enable .htaccess

In httpd.conf, find your DocumentRoot section and set:
```apache
AllowOverride All
```

### Run a Database-Driven App

PHP includes SQLite support out of the box:

```php
<?php
// Connect to SQLite database
$db = new PDO('sqlite:/path/to/database.db');

// Create table
$db->exec("CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY,
    name TEXT
)");

// Insert data
$stmt = $db->prepare("INSERT INTO users (name) VALUES (?)");
$stmt->execute(['John Doe']);

// Query data
$result = $db->query("SELECT * FROM users");
foreach($result as $row) {
    echo "User: " . $row['name'] . "\n";
}
?>
```

### API Endpoint Example

Create `$NATIVE_TOOLS/share/apache2/htdocs/api.php`:

```php
<?php
header('Content-Type: application/json');

$data = [
    'message' => 'Hello from BB10!',
    'device' => 'BlackBerry 10',
    'timestamp' => time(),
    'php_version' => PHP_VERSION
];

echo json_encode($data, JSON_PRETTY_PRINT);
?>
```

Access at: `http://[your-bb10-ip]:8080/api.php`

## Apache Control Commands

```bash
# Start
apachectl start

# Stop
apachectl stop

# Restart
apachectl restart

# Graceful restart (no downtime)
apachectl graceful

# Check config syntax
apachectl configtest

# Show loaded modules
apachectl -M

# Show compile settings
httpd -V
```

## PHP Command Line Tools

```bash
php           # PHP CLI
php-cgi       # PHP CGI
php-config    # Configuration info
phpize        # Prepare PHP extensions
phpdbg        # PHP debugger
```

## Troubleshooting

### Apache won't start

**First, make sure you ran the setup:**
```bash
apache-setup
```

Check logs:
```bash
cat /accounts/1000/shared/misc/apache2/logs/error_log
```

Common issues:
- **Symlinks not created** - Run `apache-setup` to create them
- **User 'daemon' not found** - Setup script fixes this (uses 'nobody')
- **Port 80 permission denied** - Setup script changes to port 8080
- **Log permission issues** - Setup script fixes this automatically
- **Config syntax error** - Run `apachectl configtest`

### PHP not working

1. Check if PHP module is loaded:
```bash
httpd -M | grep php
```

2. Check file permissions:
```bash
ls -l $NATIVE_TOOLS/share/apache2/modules/libphp7.so
```

3. Verify PHP files have .php extension

### Can't access from network

1. Find your BB10 IP address:
```bash
ifconfig
```

2. Check firewall settings on BB10

3. Make sure Apache is listening on all interfaces (not just 127.0.0.1)

### "Permission denied" errors

```bash
# Make sure log directory is writable
chmod 755 $NATIVE_TOOLS/share/apache2/logs

# Make sure htdocs is readable
chmod 755 $NATIVE_TOOLS/share/apache2/htdocs
chmod 644 $NATIVE_TOOLS/share/apache2/htdocs/*
```

## Performance Tips

1. **Limit Apache modules**: Disable unused modules in httpd.conf
2. **Tune MaxClients**: Lower it for devices with limited RAM
3. **Enable compression**: mod_deflate for smaller transfers
4. **Use FastCGI**: For better PHP performance (php-fpm)
5. **Keep logs small**: Regularly rotate or truncate logs

## Use Cases

### Local Development
- Test PHP applications on-device
- Develop mobile-optimized web apps
- Local API testing

### Personal Server
- Host a personal website or blog
- Photo gallery
- File sharing server
- RSS feed reader

### IoT/Automation
- REST API for device control
- Webhook receiver
- Data logger/dashboard
- Network monitoring

### Education
- Learn web development
- Practice PHP programming
- Understand server administration

## File Locations

```
$NATIVE_TOOLS/share/apache2/          # Apache root
  ├── bin/                            # Apache binaries
  ├── conf/                           # Configuration files
  ├── htdocs/                         # Document root (your web files)
  ├── logs/                           # Access/error logs
  ├── modules/                        # Apache modules
  └── manual/                         # Apache documentation

$NATIVE_TOOLS/share/php/              # PHP root
  ├── bin/                            # PHP binaries
  ├── include/                        # PHP headers
  ├── lib/                            # PHP libraries
  └── var/                            # PHP data
```

## Binaries Installed

### Apache
- `httpd` - Apache HTTP Server
- `apachectl` - Apache control script
- `ab` - Apache Benchmark tool
- `htpasswd` - Password file management
- `htdigest` - Digest authentication management

### PHP
- `php` - PHP CLI
- `php-cgi` - PHP CGI
- `php-config` - PHP configuration tool
- `phpize` - Extension tool
- `phpdbg` - PHP debugger

## Version Information

- **Apache**: 2.4.58 (Unix)
- **PHP**: 7.4.33 (cli) + CGI
- **APR**: 1.7.4 (Apache Portable Runtime)
- **Architecture**: ARM EABI5 (QNX 8 / BB10)

## Size Information

- **Apache**: ~50 MB
- **PHP**: ~68 MB
- **Total**: ~118 MB uncompressed
- **Compressed**: ~41 MB

## Security Notes

⚠️ **Important Security Considerations:**

1. **Not for production**: This is for development/personal use
2. **Change default passwords**: If using htpasswd
3. **Keep PHP updated**: Security patches are important
4. **Disable directory listing**: Set `Options -Indexes`
5. **Restrict access**: Use firewall rules to limit access
6. **Use HTTPS**: Enable mod_ssl for encrypted connections
7. **Hide PHP version**: Set `expose_php = Off` in php.ini

## Related Packages

You might also want:
- `git` - Version control (already in BerryCore)
- `curl` - HTTP client (already in BerryCore)
- `vim`/`nano` - Text editors (already in BerryCore)
- `sqlite` - Database (included with PHP)

## Documentation

- Apache Docs: https://httpd.apache.org/docs/2.4/
- PHP Manual: https://www.php.net/manual/en/
- PHP 7.4 Docs: https://www.php.net/manual/en/migration74.php

## Examples Repository

Check out example scripts and configurations at:
https://github.com/sw7ft/berrycore/wiki/Apache-PHP-Examples

---

**Build amazing things on your BlackBerry 10!** 🚀🌐

