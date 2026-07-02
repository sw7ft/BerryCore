/*
 * openport — Tactrix OpenPort 2.0 tool for QNX / BlackBerry Passport
 *
 * Subcommands: identify, log, voltage, probe, scan, read-did, ports, help
 */

#include "openport.h"
#include "uds.h"
#include "util.h"

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
	const char *port;
	unsigned baud;
	int verbose;
	int debug;
} global_opts_t;

static global_opts_t g_opts;

static openport_t g_op;
static int g_op_open;

static void cleanup(void)
{
	if (g_op_open) {
		op_close(&g_op);
		g_op_open = 0;
	}
}

static int ensure_open(void)
{
	if (g_op_open)
		return 0;
	const char *port = op_pick_port(g_opts.port);
	op_log_info("Opening %s @ 115200…", port);
	if (op_open(&g_op, port, g_opts.verbose, g_opts.debug) != 0) {
		op_log_err("Cannot open %s (%s)", port, strerror(errno));
		return 1;
	}
	g_op_open = 1;
	return 0;
}

static void print_banner(void)
{
	printf("openport — Tactrix OpenPort 2.0 for QNX / BlackBerry Passport\n");
	printf("Manual: /accounts/1000/shared/misc/share/doc/openport/MANUAL.md\n\n");
}

static int cmd_identify(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (ensure_open() != 0)
		return 1;
	printf("Port:     %s\n", g_op.port_path);
	printf("Firmware: %s\n", g_op.firmware);
	printf("Status:   ready\n");
	return 0;
}

typedef struct {
	FILE *fp;
	unsigned long count;
	int show_id;
} log_ctx_t;

static void on_log_msg(uint32_t ts_us, const uint8_t *data, size_t len, log_ctx_t *ctx)
{
	char hex[512];
	double ts_ms = ts_us / 1000.0;

	if (ctx->show_id && len >= 4) {
		uint32_t id = op_id_from_bytes(data);
		op_hex_format(hex, sizeof(hex), data + 4, len - 4);
		printf("[%.3f] ID %03x  %s\n", ts_ms, id & 0x7ff, hex);
		if (ctx->fp)
			fprintf(ctx->fp, "[%.3f] ID %03x  %s\n", ts_ms, id & 0x7ff, hex);
	} else {
		op_hex_format(hex, sizeof(hex), data, len);
		printf("[%.3f] %s\n", ts_ms, hex);
		if (ctx->fp)
			fprintf(ctx->fp, "[%.3f] %s\n", ts_ms, hex);
	}
	ctx->count++;
}

static int cmd_log(int argc, char **argv)
{
	int duration = 60;
	const char *outfile = NULL;
	int iso15765 = 0;
	int show_id = 0;

	static struct option opts[] = {
		{"duration", required_argument, NULL, 'd'},
		{"output", required_argument, NULL, 'o'},
		{"iso15765", no_argument, NULL, 1000},
		{"show-id", no_argument, NULL, 1001},
		{NULL, 0, NULL, 0},
	};
	optind = 1;
	int c;
	while ((c = getopt_long(argc, argv, "d:o:", opts, NULL)) != -1) {
		switch (c) {
		case 'd': duration = atoi(optarg); break;
		case 'o': outfile = optarg; break;
		case 1000: iso15765 = 1; break;
		case 1001: show_id = 1; break;
		default: return 1;
		}
	}

	if (ensure_open() != 0)
		return 1;

	unsigned flags = OP_FLAG_SNIFF_MODE | OP_FLAG_CAN_ID_BOTH;
	int ch = iso15765 ? OP_CH_ISO15765 : OP_CH_CAN;
	const char *proto = iso15765 ? "ISO15765" : "CAN";

	op_log_info("Sniffing %s @ %u baud (%s)", proto, g_opts.baud,
		    duration > 0 ? "timed" : "continuous until Ctrl+C");

	if (op_connect(&g_op, ch, flags, g_opts.baud) != 0)
		return 1;

	if (iso15765) {
		if (op_setup_flow_filter(&g_op, 0x7e0, 0x7e8) != 0) {
			op_log_warn("Flow filter setup failed — continuing anyway");
		}
	} else {
		if (op_setup_pass_filter(&g_op) != 0) {
			op_log_warn("Pass filter setup failed — continuing anyway");
		}
	}

	log_ctx_t ctx = {0};
	ctx.show_id = show_id || !iso15765;
	if (outfile) {
		ctx.fp = fopen(outfile, "w");
		if (!ctx.fp)
			op_log_warn("Cannot write %s", outfile);
		else
			fprintf(ctx.fp, "# openport log %s %u baud\n# %s\n", proto, g_opts.baud,
				g_op.firmware);
	}

	time_t end = duration > 0 ? time(NULL) + duration : 0;
	op_log_info("Logging… (Ctrl+C to stop)");

	while (!op_interrupted && (duration <= 0 || time(NULL) < end)) {
		op_msg_t msgs[32];
		op_poll(&g_op, 500);
		size_t n = op_queue_pop(&g_op, msgs, 32);
		for (size_t i = 0; i < n; i++) {
			log_ctx_t *lctx = &ctx;
			on_log_msg(msgs[i].ts_us, msgs[i].data, msgs[i].len, lctx);
		}
	}

	printf("\nCaptured %lu messages.\n", ctx.count);
	if (ctx.fp)
		fclose(ctx.fp);
	op_disconnect(&g_op);
	return 0;
}

static int cmd_voltage(int argc, char **argv)
{
	int pin = 16;
	optind = 1;
	int c;
	while ((c = getopt(argc, argv, "p:")) != -1) {
		if (c == 'p')
			pin = atoi(optarg);
	}
	if (ensure_open() != 0)
		return 1;
	int mv = 0;
	if (op_read_voltage(&g_op, pin, &mv) != 0) {
		op_log_err("Voltage read failed (pin %d)", pin);
		return 1;
	}
	printf("Pin %2d: %d mV (%.2f V)\n", pin, mv, mv / 1000.0);
	if (pin == 16 && mv < 11000)
		op_log_warn("Battery low — many modules sleep below ~11 V");
	return 0;
}

static int cmd_probe(int argc, char **argv)
{
	uint32_t tx = 0x7e0, rx = 0x7e8;
	optind = 1;
	int c;
	while ((c = getopt(argc, argv, "t:r:")) != -1) {
		if (c == 't')
			tx = (uint32_t)strtoul(optarg, NULL, 16);
		if (c == 'r')
			rx = (uint32_t)strtoul(optarg, NULL, 16);
	}

	if (ensure_open() != 0)
		return 1;

	printf("Firmware: %s\n", g_op.firmware);

	uds_link_t link;
	if (uds_open_link(&g_op, &link, tx, rx, g_opts.baud) != 0)
		return 1;

	op_log_info("TesterPresent on TX %03x / RX %03x…", tx, rx);
	if (!uds_tester_present(&g_op, &link)) {
		op_log_err("No UDS response — check key ON, OBD fuse, module address");
		uds_close_link(&g_op);
		return 1;
	}
	printf("ECU:      alive (TesterPresent OK)\n");

	uds_resp_t vin;
	if (uds_read_did(&g_op, &link, 0xf190, &vin) == 0 && vin.ok) {
		if (vin.len >= 1 && vin.payload[0] == 0x62) {
			printf("VIN:      ");
			uds_ascii_print(vin.payload + 3, vin.len - 3);
			printf("\n");
		} else if (vin.len >= 3 && vin.payload[0] == 0x7f) {
			printf("VIN:      NRC 0x%02x (%s)\n", vin.payload[2],
			       uds_nrc_label(vin.payload[2]));
		}
	} else {
		op_log_warn("VIN read (F190) timed out");
	}

	uds_resp_t ver;
	if (uds_read_did(&g_op, &link, 0xf189, &ver) == 0 && ver.ok && ver.len >= 4 &&
	    ver.payload[0] == 0x62) {
		printf("SW ver:   ");
		uds_ascii_print(ver.payload + 3, ver.len - 3);
		printf("\n");
	}

	int mv = 0;
	if (op_read_voltage(&g_op, 16, &mv) == 0)
		printf("VBATT:    %.1f V\n", mv / 1000.0);

	uds_close_link(&g_op);
	return 0;
}

static int cmd_scan(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (ensure_open() != 0)
		return 1;

	printf("Scanning FCA module addresses @ %u baud…\n\n", g_opts.baud);
	printf("%-22s  TX     RX     Status\n", "Module");
	printf("%-22s  -----  -----  ------\n", "------");

	int found = 0;
	for (size_t i = 0; i < FCA_MODULE_COUNT && !op_interrupted; i++) {
		uds_link_t link;
		if (uds_open_link(&g_op, &link, FCA_MODULES[i].tx, FCA_MODULES[i].rx,
				  g_opts.baud) != 0) {
			printf("%-22s  %03x    %03x    open failed\n", FCA_MODULES[i].name,
			       FCA_MODULES[i].tx & 0x7ff, FCA_MODULES[i].rx & 0x7ff);
			continue;
		}
		int alive = uds_tester_present(&g_op, &link);
		printf("%-22s  %03x    %03x    %s\n", FCA_MODULES[i].name,
		       FCA_MODULES[i].tx & 0x7ff, FCA_MODULES[i].rx & 0x7ff,
		       alive ? "OK" : "—");
		if (alive)
			found++;
		uds_close_link(&g_op);
	}

	printf("\n%d module(s) responded.\n", found);
	return found ? 0 : 1;
}

static int cmd_read_did(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: openport read-did <DID> [-t tx] [-r rx]\n");
		fprintf(stderr, "Example: openport read-did F190\n");
		return 1;
	}
	uint16_t did = (uint16_t)strtoul(argv[1], NULL, 16);
	uint32_t tx = 0x7e0, rx = 0x7e8;
	optind = 2;
	int c;
	while ((c = getopt(argc, argv, "t:r:")) != -1) {
		if (c == 't')
			tx = (uint32_t)strtoul(optarg, NULL, 16);
		if (c == 'r')
			rx = (uint32_t)strtoul(optarg, NULL, 16);
	}

	if (ensure_open() != 0)
		return 1;

	uds_link_t link;
	if (uds_open_link(&g_op, &link, tx, rx, g_opts.baud) != 0)
		return 1;

	uds_resp_t resp;
	if (uds_read_did(&g_op, &link, did, &resp) != 0 || !resp.ok) {
		op_log_err("No response for DID %04X", did);
		uds_close_link(&g_op);
		return 1;
	}

	if (resp.len >= 3 && resp.payload[0] == 0x7f) {
		printf("DID %04X: NRC 0x%02x (%s)\n", did, resp.payload[2],
		       uds_nrc_label(resp.payload[2]));
	} else if (resp.len >= 4 && resp.payload[0] == 0x62) {
		char hex[512];
		op_hex_format(hex, sizeof(hex), resp.payload + 3, resp.len - 3);
		printf("DID %04X: %s\n", did, hex);
		printf("ASCII:    ");
		uds_ascii_print(resp.payload + 3, resp.len - 3);
		printf("\n");
	} else {
		char hex[512];
		op_hex_format(hex, sizeof(hex), resp.payload, resp.len);
		printf("DID %04X: unexpected %s\n", did, hex);
	}

	uds_close_link(&g_op);
	return 0;
}

static int cmd_ports(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return op_list_ports();
}

static void cmd_help(const char *topic)
{
	if (topic && strcmp(topic, "log") == 0) {
		printf("openport log — passive CAN bus capture\n\n"
		       "  openport log [-d SEC] [-o FILE] [--iso15765] [--show-id]\n\n"
		       "Writes [timestamp_ms] hex bytes, one frame per line.\n"
		       "Use --iso15765 for OBD-II formatted traffic (PCM 7E0/7E8).\n");
		return;
	}
	if (topic && strcmp(topic, "probe") == 0) {
		printf("openport probe — quick ECU health check\n\n"
		       "  openport probe [-t 7e0] [-r 7e8]\n\n"
		       "Sends UDS TesterPresent, reads VIN (F190) and software version (F189).\n");
		return;
	}

	print_banner();
	printf("Usage: openport [global opts] <command> [command opts]\n\n"
	       "Global options:\n"
	       "  -p, --port PATH    Serial device (/dev/serusb1, OPENPORT_PORT)\n"
	       "  -b, --baud RATE    Vehicle CAN baud (default: 500000)\n"
	       "  -v, --verbose      More diagnostic output\n"
	       "      --debug        Raw serial trace on stderr\n\n"
	       "Commands:\n"
	       "  identify           Cable firmware + port (no vehicle needed)\n"
	       "  log                Passive CAN / ISO15765 sniffer\n"
	       "  voltage            Read OBD pin voltage (default pin 16 = VBATT)\n"
	       "  probe              TesterPresent + VIN + SW version\n"
	       "  scan               Ping common FCA module addresses\n"
	       "  read-did <DID>     UDS read Data Identifier (hex, e.g. F190)\n"
	       "  ports              List candidate serial devices\n"
	       "  help [topic]       This help (topics: log, probe)\n\n"
	       "Quick start:\n"
	       "  openport identify\n"
	       "  openport probe          # key ON, OBD connected\n"
	       "  openport log -d 300 -o /accounts/1000/shared/misc/can.log\n\n"
	       "Full manual: share/doc/openport/MANUAL.md\n");
}

static void parse_globals(int argc, char **argv)
{
	static struct option opts[] = {
		{"port", required_argument, NULL, 'p'},
		{"baud", required_argument, NULL, 'b'},
		{"verbose", no_argument, NULL, 'v'},
		{"debug", no_argument, NULL, 1000},
		{NULL, 0, NULL, 0},
	};
	g_opts.baud = 500000;
	optind = 1;
	int c;
	while ((c = getopt_long(argc, argv, "p:b:v", opts, NULL)) != -1) {
		switch (c) {
		case 'p': g_opts.port = optarg; break;
		case 'b': g_opts.baud = (unsigned)strtoul(optarg, NULL, 10); break;
		case 'v': g_opts.verbose = 1; break;
		case 1000: g_opts.debug = 1; break;
		default: break;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		cmd_help(NULL);
		return 1;
	}

	op_set_log_level(0, 0);
	op_install_signals();
	atexit(cleanup);

	parse_globals(argc, argv);
	op_set_log_level(g_opts.verbose, g_opts.debug);

	if (optind >= argc) {
		cmd_help(NULL);
		return 1;
	}

	const char *cmd = argv[optind];
	int cmd_argc = argc - optind;
	char **cmd_argv = argv + optind;

	if (strcmp(cmd, "help") == 0 || strcmp(cmd, "--help") == 0 || strcmp(cmd, "-h") == 0) {
		cmd_help(cmd_argc > 1 ? cmd_argv[1] : NULL);
		return 0;
	}
	if (strcmp(cmd, "identify") == 0)
		return cmd_identify(cmd_argc, cmd_argv);
	if (strcmp(cmd, "log") == 0 || strcmp(cmd, "canlog") == 0)
		return cmd_log(cmd_argc, cmd_argv);
	if (strcmp(cmd, "voltage") == 0)
		return cmd_voltage(cmd_argc, cmd_argv);
	if (strcmp(cmd, "probe") == 0)
		return cmd_probe(cmd_argc, cmd_argv);
	if (strcmp(cmd, "scan") == 0)
		return cmd_scan(cmd_argc, cmd_argv);
	if (strcmp(cmd, "read-did") == 0)
		return cmd_read_did(cmd_argc, cmd_argv);
	if (strcmp(cmd, "ports") == 0)
		return cmd_ports(cmd_argc, cmd_argv);

	fprintf(stderr, "Unknown command: %s\n", cmd);
	cmd_help(NULL);
	return 1;
}
