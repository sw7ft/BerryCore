/*
 * usbdbg — generic USB serial debugger for QNX / BlackBerry Passport
 *
 * Raw read/write/sniff on CDC ACM / serusb devices. No vendor protocol required.
 * Use for OpenPort, FTDI adapters, Arduino, GPS, modems, etc.
 */

#include "serial.h"
#include "util.h"

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

typedef struct {
	const char *port;
	int baud;
	int verbose;
} globals_t;

static globals_t g;

static int open_port(serial_port_t *sp)
{
	const char *path = serdbg_pick_port(g.port);
	if (serial_open(sp, path, g.baud) != 0) {
		fprintf(stderr, "usbdbg: cannot open %s (%s)\n", path, strerror(errno));
		fprintf(stderr, "Try: usbdbg ports\n");
		return -1;
	}
	if (g.verbose)
		fprintf(stderr, "→ open %s @ %d baud\n", path, g.baud);
	return 0;
}

static void print_rx_line(const uint8_t *data, size_t len, int show_ascii, FILE *fp)
{
	char hex[512], asc[128];
	serdbg_hex(hex, sizeof(hex), data, len);
	if (show_ascii)
		serdbg_ascii(asc, sizeof(asc), data, len);
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	double ms = ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
	if (show_ascii)
		fprintf(fp, "[%.0f] RX %zu  %s  |%s|\n", ms, len, hex, asc);
	else
		fprintf(fp, "[%.0f] RX %zu  %s\n", ms, len, hex);
}

static int cmd_sniff(int argc, char **argv)
{
	int duration = 0;
	const char *outfile = NULL;
	int show_ascii = 0;

	static struct option opts[] = {
		{"duration", required_argument, NULL, 'd'},
		{"output", required_argument, NULL, 'o'},
		{"ascii", no_argument, NULL, 'a'},
		{NULL, 0, NULL, 0},
	};
	optind = 1;
	int c;
	while ((c = getopt_long(argc, argv, "d:o:a", opts, NULL)) != -1) {
		switch (c) {
		case 'd': duration = atoi(optarg); break;
		case 'o': outfile = optarg; break;
		case 'a': show_ascii = 1; break;
		default: return 1;
		}
	}

	serial_port_t sp;
	if (open_port(&sp) != 0)
		return 1;

	FILE *log = stdout;
	if (outfile) {
		log = fopen(outfile, "w");
		if (!log) {
			perror(outfile);
			serial_close(&sp);
			return 1;
		}
		fprintf(log, "# usbdbg sniff %s %d baud\n", sp.path, sp.baud);
	}

	fprintf(stderr, "Sniffing %s (Ctrl+C to stop)…\n", sp.path);
	time_t end = duration > 0 ? time(NULL) + duration : 0;
	uint8_t buf[4096];
	unsigned long total = 0;

	while (!serdbg_interrupted && (duration <= 0 || time(NULL) < end)) {
		int n = serial_read(&sp, buf, sizeof(buf), 200);
		if (n <= 0)
			continue;
		print_rx_line(buf, (size_t)n, show_ascii, log);
		total += (unsigned long)n;
	}

	fprintf(stderr, "\n%lu bytes captured.\n", total);
	if (log != stdout)
		fclose(log);
	serial_close(&sp);
	return 0;
}

static int cmd_send(int argc, char **argv)
{
	int hex_mode = 0;
	const char *payload = NULL;

	static struct option opts[] = {
		{"hex", no_argument, NULL, 'x'},
		{NULL, 0, NULL, 0},
	};
	optind = 1;
	int c;
	while ((c = getopt_long(argc, argv, "x", opts, NULL)) != -1) {
		if (c == 'x')
			hex_mode = 1;
	}

	if (optind >= argc) {
		fprintf(stderr, "Usage: usbdbg send [-x] \"string\" | aa bb cc\n");
		return 1;
	}
	payload = argv[optind];

	serial_port_t sp;
	if (open_port(&sp) != 0)
		return 1;

	uint8_t data[4096];
	size_t len = 0;
	if (hex_mode || strchr(payload, ' ')) {
		if (serdbg_parse_hex(payload, data, sizeof(data), &len) != 0) {
			fprintf(stderr, "Bad hex payload\n");
			serial_close(&sp);
			return 1;
		}
	} else {
		char tmp[4096];
		serdbg_unescape(payload, tmp, sizeof(tmp));
		len = strlen(tmp);
		memcpy(data, tmp, len);
	}

	if (serial_write(&sp, data, len) != (int)len) {
		fprintf(stderr, "Write failed\n");
		serial_close(&sp);
		return 1;
	}

	if (g.verbose) {
		char hex[512];
		serdbg_hex(hex, sizeof(hex), data, len);
		fprintf(stderr, "→ TX %zu  %s\n", len, hex);
	}

	/* Brief read for response */
	uint8_t rx[4096];
	int n = serial_read(&sp, rx, sizeof(rx), 500);
	if (n > 0)
		print_rx_line(rx, (size_t)n, 1, stdout);

	serial_close(&sp);
	return 0;
}

static int cmd_probe(int argc, char **argv)
{
	const char *banner = NULL;
	optind = 1;
	int c;
	while ((c = getopt(argc, argv, "b:")) != -1) {
		if (c == 'b')
			banner = optarg;
	}

	serial_port_t sp;
	if (open_port(&sp) != 0)
		return 1;

	printf("Port: %s\n", sp.path);
	printf("Baud: %d\n", sp.baud);

	if (banner) {
		char tmp[512];
		int blen = serdbg_unescape(banner, tmp, sizeof(tmp));
		serial_write(&sp, (uint8_t *)tmp, (size_t)blen);
		if (g.verbose)
			fprintf(stderr, "→ sent banner (%d bytes)\n", blen);
	}

	fprintf(stderr, "Listening 3s for any data…\n");
	uint8_t buf[4096];
	int got = 0;
	for (int t = 0; t < 15 && !serdbg_interrupted; t++) {
		int n = serial_read(&sp, buf, sizeof(buf), 200);
		if (n > 0) {
			print_rx_line(buf, (size_t)n, 1, stdout);
			got = 1;
		}
	}

	if (!got)
		printf("(no data — try different baud or send a wake string with -b)\n");

	serial_close(&sp);
	return got ? 0 : 1;
}

static int cmd_line(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	serial_port_t sp;
	if (open_port(&sp) != 0)
		return 1;

	printf("Line mode on %s @ %d. Type lines to send; Ctrl+C exit.\n", sp.path, sp.baud);
	char line[512];
	uint8_t rx[4096];

	while (!serdbg_interrupted) {
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(sp.fd, &rfds);
		FD_SET(STDIN_FILENO, &rfds);
		int mx = sp.fd > STDIN_FILENO ? sp.fd : STDIN_FILENO;
		struct timeval tv = { .tv_sec = 0, .tv_usec = 200000 };

		int sel = select(mx + 1, &rfds, NULL, NULL, &tv);
		if (sel < 0 && errno == EINTR)
			break;
		if (sel > 0 && FD_ISSET(sp.fd, &rfds)) {
			int n = read(sp.fd, rx, sizeof(rx));
			if (n > 0)
				fwrite(rx, 1, (size_t)n, stdout);
		}
		if (sel > 0 && FD_ISSET(STDIN_FILENO, &rfds)) {
			if (!fgets(line, sizeof(line), stdin))
				break;
			size_t l = strlen(line);
			if (l > 0 && line[l - 1] == '\n')
				line[--l] = '\0';
			serdbg_unescape(line, line, sizeof(line));
			l = strlen(line);
			serial_write(&sp, (uint8_t *)line, l);
			serial_write(&sp, (const uint8_t *)"\r\n", 2);
		}
	}
	serial_close(&sp);
	putchar('\n');
	return 0;
}

static int cmd_cat(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	serial_port_t sp;
	if (open_port(&sp) != 0)
		return 1;

	fprintf(stderr, "Reading %s (Ctrl+C)…\n", sp.path);
	uint8_t buf[4096];
	while (!serdbg_interrupted) {
		int n = serial_read(&sp, buf, sizeof(buf), 500);
		if (n > 0)
			fwrite(buf, 1, (size_t)n, stdout);
	}
	serial_close(&sp);
	return 0;
}

static void help(void)
{
	printf(
		"usbdbg — generic USB serial debugger (QNX / Passport)\n\n"
		"Global: -p PORT  -b BAUD  -v\n"
		"  SERDBG_PORT or USB_SERIAL_PORT env overrides default path\n\n"
		"Commands:\n"
		"  ports              List /dev/ser* and common serial nodes\n"
		"  sniff [-d SEC] [-o FILE] [-a]   Log raw RX (hex + optional ASCII)\n"
		"  send [-x] DATA     Send string or hex (spaces); print quick RX\n"
		"  send -x \"61 74 69 0d 0a\"          Send raw bytes\n"
		"  probe [-b \"\\r\\nati\\r\\n\"]       Open, optional TX, listen\n"
		"  cat                Raw RX to stdout\n"
		"  line               Interactive line sender + echo\n"
		"  help\n\n"
		"Examples:\n"
		"  usbdbg ports\n"
		"  usbdbg -p /dev/serusb1 probe -b \"\\\\r\\\\nati\\\\r\\\\n\"   # any AT device\n"
		"  usbdbg sniff -d 60 -a -o /tmp/usb.log\n"
		"  usbdbg send \"AT\\r\\n\"\n"
		"  usbdbg -b 9600 probe              # GPS / older gear\n\n"
		"OpenPort-specific CAN/UDS: use `openport` instead.\n"
	);
}

static void parse_globals(int argc, char **argv)
{
	g.baud = 115200;
	optind = 1;
	int c;
	while ((c = getopt(argc, argv, "+p:b:v")) != -1) {
		switch (c) {
		case 'p': g.port = optarg; break;
		case 'b': g.baud = atoi(optarg); break;
		case 'v': g.verbose = 1; break;
		default: break;
		}
	}
}

int main(int argc, char **argv)
{
	serdbg_install_signals();

	if (argc < 2) {
		help();
		return 1;
	}

	parse_globals(argc, argv);
	if (optind >= argc) {
		help();
		return 1;
	}

	const char *cmd = argv[optind];
	int cmd_argc = argc - optind;
	char **cmd_argv = argv + optind;

	if (strcmp(cmd, "help") == 0 || strcmp(cmd, "-h") == 0) {
		help();
		return 0;
	}
	if (strcmp(cmd, "ports") == 0)
		return serdbg_list_ports();
	if (strcmp(cmd, "sniff") == 0)
		return cmd_sniff(cmd_argc, cmd_argv);
	if (strcmp(cmd, "send") == 0)
		return cmd_send(cmd_argc, cmd_argv);
	if (strcmp(cmd, "probe") == 0)
		return cmd_probe(cmd_argc, cmd_argv);
	if (strcmp(cmd, "line") == 0)
		return cmd_line(cmd_argc, cmd_argv);
	if (strcmp(cmd, "cat") == 0)
		return cmd_cat(cmd_argc, cmd_argv);

	fprintf(stderr, "Unknown command: %s\n", cmd);
	help();
	return 1;
}
