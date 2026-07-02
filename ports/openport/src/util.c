#include "util.h"

#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t op_interrupted;

static int g_verbose;
static int g_debug;

void op_set_log_level(int verbose, int debug)
{
	g_verbose = verbose;
	g_debug = debug;
}

static void on_signal(int sig)
{
	(void)sig;
	op_interrupted = 1;
}

void op_install_signals(void)
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = on_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

void op_hex_format(char *out, size_t outsz, const uint8_t *data, size_t len)
{
	size_t pos = 0;
	for (size_t i = 0; i < len && pos + 3 < outsz; i++)
		pos += (size_t)snprintf(out + pos, outsz - pos, "%02x ", data[i]);
	if (pos > 0 && pos < outsz)
		out[pos - 1] = '\0';
	else if (outsz)
		out[0] = '\0';
}

void op_hex_format_compact(char *out, size_t outsz, const uint8_t *data, size_t len)
{
	size_t pos = 0;
	for (size_t i = 0; i < len && pos + 2 < outsz; i++)
		pos += (size_t)snprintf(out + pos, outsz - pos, "%02x", data[i]);
	if (outsz)
		out[pos < outsz ? pos : outsz - 1] = '\0';
}

uint32_t op_id_from_bytes(const uint8_t b[4])
{
	return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) |
	       ((uint32_t)b[2] << 8) | (uint32_t)b[3];
}

void op_id_to_bytes(uint32_t id, uint8_t out[4])
{
	out[0] = (uint8_t)((id >> 24) & 0xff);
	out[1] = (uint8_t)((id >> 16) & 0xff);
	out[2] = (uint8_t)((id >> 8) & 0xff);
	out[3] = (uint8_t)(id & 0xff);
}

static const char *port_candidates[] = {
	"/dev/serusb1", "/dev/serusb2", "/dev/serusb3", "/dev/serusb4",
	"/dev/ser1", "/dev/ser2", "/dev/ser3",
	"/dev/ttyACM0", "/dev/ttyACM1",
	NULL,
};

int op_port_accessible(const char *path)
{
	return path && path[0] && access(path, R_OK | W_OK) == 0;
}

const char *op_pick_port(const char *user)
{
	if (user && user[0])
		return user;
	const char *env = getenv("OPENPORT_PORT");
	if (env && env[0])
		return env;
	for (int i = 0; port_candidates[i]; i++) {
		if (op_port_accessible(port_candidates[i]))
			return port_candidates[i];
	}
	return "/dev/serusb1";
}

int op_list_ports(void)
{
	int found = 0;
	printf("Candidate serial devices:\n");
	for (int i = 0; port_candidates[i]; i++) {
		int ok = op_port_accessible(port_candidates[i]);
		printf("  %s %s\n", port_candidates[i], ok ? "[accessible]" : "[not found]");
		if (ok)
			found++;
	}
	const char *env = getenv("OPENPORT_PORT");
	if (env && env[0])
		printf("  OPENPORT_PORT=%s\n", env);
	if (!found)
		printf("\nNo accessible device yet. Plug OpenPort via OTG, then check:\n"
		       "  ls /dev/ser*\n"
		       "  usb -v   (look for 0403:cc4d Tactrix OpenPort 2.0)\n");
	return found ? 0 : 1;
}

static void vlogf(FILE *fp, const char *prefix, const char *fmt, va_list ap)
{
	fprintf(fp, "%s", prefix);
	vfprintf(fp, fmt, ap);
	fprintf(fp, "\n");
}

void op_log_info(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vlogf(stderr, "→ ", fmt, ap);
	va_end(ap);
}

void op_log_verbose(const char *fmt, ...)
{
	if (!g_verbose)
		return;
	va_list ap;
	va_start(ap, fmt);
	vlogf(stderr, "  ", fmt, ap);
	va_end(ap);
}

void op_log_warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vlogf(stderr, "[warn] ", fmt, ap);
	va_end(ap);
}

void op_log_err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vlogf(stderr, "[error] ", fmt, ap);
	va_end(ap);
}

void op_log_debug(int enabled, const char *fmt, ...)
{
	if (!enabled && !g_debug)
		return;
	va_list ap;
	va_start(ap, fmt);
	vlogf(stderr, "[debug] ", fmt, ap);
	va_end(ap);
}
