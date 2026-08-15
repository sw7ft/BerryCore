#!/usr/bin/env python3
"""BerryCore Games static server. Default port 8766."""
import os
import sys
from http.server import HTTPServer, SimpleHTTPRequestHandler

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8766
ROOT = os.path.dirname(os.path.abspath(__file__))


class GamesHandler(SimpleHTTPRequestHandler):
    def log_message(self, fmt, *args):
        sys.stderr.write("%s - %s\n" % (self.address_string(), fmt % args))


if __name__ == "__main__":
    os.chdir(ROOT)
    httpd = HTTPServer(("0.0.0.0", PORT), GamesHandler)
    sys.stderr.write("BerryCore Games at http://0.0.0.0:%d/\n" % PORT)
    httpd.serve_forever()
