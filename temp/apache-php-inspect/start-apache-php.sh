#!/bin/sh
# Startup script for Apache with PHP on QNX 8 BlackBerry Passport

# Set paths
APACHE_HOME=/accounts/1000/shared/misc/apache2
PHP_HOME=/accounts/1000/shared/misc/php
export PATH=$APACHE_HOME/bin:$PHP_HOME/bin:$PATH

# Start Apache
echo "Starting Apache HTTP Server with PHP support..."
$APACHE_HOME/bin/httpd -k start

# Check status
if [ $? -eq 0 ]; then
    echo "Apache started successfully!"
    echo "Access your server at http://[device-ip]"
    echo "Test PHP at http://[device-ip]/info.php"
else
    echo "Failed to start Apache"
    exit 1
fi
