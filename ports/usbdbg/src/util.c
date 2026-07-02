#include "util.h"

#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t serdbg_interrupted;

static const char *defaults[] = {
	"/dev/serusb1", "/dev/serusb2", "/dev/serusb3", "/dev/serusb4",
	"/dev/ser1", "/dev/ser2", "/dev/ser3", "/dev/ser4",
	"/dev/ttyACM0", "/dev/ttyACM1", "/dev/ttyUSB0", "/dev/ttyUSB1",
	NULL,
};

static void on_sig(int sig)
{
	(void)sig;
	serdbg_interrupted = 1;
}

void serdbg_install_signals(void)
{
	signal(SIGINT, on_sig);
	signal(SIGTERM, on_sig);
}

void serdbg_hex(char *out, size_t outsz, const uint8_t *data, size_t len)
{
	size_t pos = 0;
	for (size_t i = 0; i < len && pos + 3 < outsz; i++)
		pos += (size_t)snprintf(out + pos, outsz - pos, "%02x ", data[i]);
	if (pos > 0 && pos < outsz)
		out[pos - 1] = '\0';
	else if (outsz)
		out[0] = '\0';
}

void serdbg_ascii(char *out, size_t outsz, const uint8_t *data, size_t len)
{
	size_t pos = 0;
	for (size_t i = 0; i < len && pos + 1 < outsz; i++) {
		char c = (data[i] >= 0x20 && data[i] <= 0x7e) ? (char)data[i] : '.';
		out[pos++] = c;
	}
	if (outsz)
		out[pos < outsz ? pos : outsz - 1] = '\0';
}

int serdbg_parse_hex(const char *s, uint8_t *out, size_t cap, size_t *len)
{
	size_t n = 0;
	const char *p = s;
	while (*p && n < cap) {
		while (*p == ' ' || *p == '\t' || *p == ',' || *p == ':')
			p++;
		if (!*p)
			break;
		unsigned v;
		if (sscanf(p, "%2x", &v) != 1)
			return -1;
		out[n++] = (uint8_t)v;
		while (*p && *p != ' ' && *p != '\t' && *p != ',')
			p++;
	}
	*len = n;
	return 0;
}

int serdbg_unescape(const char *in, char *out, size_t outsz)
{
	size_t j = 0;
	for (size_t i = 0; in[i] && j + 1 < outsz; i++) {
		if (in[i] == '\\' && in[i + 1]) {
			i++;
			switch (in[i]) {
			case 'n': out[j++] = '\n'; break;
			case 'r': out[j++] = '\r'; break;
			case 't': out[j++] = '\t'; break;
			case '\\': out[j++] = '\\'; break;
			default: out[j++] = in[i]; break;
			}
		} else {
			out[j++] = in[i];
		}
	}
	out[j] = '\0';
	return (int)j;
}

int serdbg_port_ok(const char *path)
{
	return path && path[0] && access(path, R_OK | W_OK) == 0;
}

size_t serdbg_scan_glob_ports(char paths[][256], size_t max)
{
	size_t n = 0;
	for (int i = 0; defaults[i] && n < max; i++) {
		if (serdbg_port_ok(defaults[i])) {
			snprintf(paths[n], 256, "%s", defaults[i]);
			n++;
		}
	}
	DIR *d = opendir("/dev");
	if (d) {
		struct dirent *e;
		while ((e = readdir(d)) && n < max) {
			if (strncmp(e->d_name, "serusb", 6) != 0 &&
			    strncmp(e->d_name, "ser", 3) != 0)
				continue;
			char path[256];
			snprintf(path, sizeof(path), "/dev/%s", e->d_name);
			int dup = 0;
			for (size_t k = 0; k < n; k++) {
				if (strcmp(paths[k], path) == 0) {
					dup = 1;
					break;
				}
			}
			if (!dup && serdbg_port_ok(path)) {
				snprintf(paths[n], 256, "%s", path);
				n++;
			}
		}
		closedir(d);
	}
	return n;
}

const char *serdbg_pick_port(const char *user)
{
	if (user && user[0])
		return user;
	const char *env = getenv("SERDBG_PORT");
	if (env && env[0])
		return env;
	env = getenv("USB_SERIAL_PORT");
	if (env && env[0])
		return env;
	static char first[256];
	char paths[32][256];
	if (serdbg_scan_glob_ports(paths, 32) > 0) {
		snprintf(first, sizeof(first), "%s", paths[0]);
		return first;
	}
	return "/dev/serusb1";
}

int serdbg_list_ports(void)
{
	printf("USB / serial devices (readable+writable):\n\n");
	char paths[32][256];
	size_t n = serdbg_scan_glob_ports(paths, 32);
	for (size_t i = 0; i < n; i++)
		printf("  %s\n", paths[i]);

	printf("\nCommon defaults (may not exist until device plugged in):\n");
	for (int i = 0; defaults[i]; i++)
		printf("  %s %s\n", defaults[i], serdbg_port_ok(defaults[i]) ? "[ok]" : "[--]");

	const char *env = getenv("SERDBG_PORT");
	if (env && env[0])
		printf("\nSERDBG_PORT=%s\n", env);

	if (n == 0) {
		printf("\nNo device yet. Plug USB OTG gadget, then:\n");
		printf("  ls /dev/ser*\n");
		printf("  usb -v   (look for CDC ACM, FTDI, etc.)\n");
		return 1;
	}
	return 0;
}
