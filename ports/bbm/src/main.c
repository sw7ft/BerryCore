/*
 * bbm — BerryCore Berry Bridge Messenger (QNX / BB10 native client)
 *
 * Talks to berrycore.sw7ft.com BerryRelay on TCP 37193.
 * No nc/telnet dependency — ships as a single ARM binary.
 */

#include "relay.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int print_msg_line(const char *line, void *ctx)
{
	(void)ctx;
	if (strncmp(line, "MSG ", 4) != 0) {
		if (strncmp(line, "OK ", 3) == 0)
			return 0;
		return 0;
	}
	puts(line + 4);
	return 0;
}

static int print_ok_line(const char *line, void *ctx)
{
	(void)ctx;
	if (strncmp(line, "OK ", 3) == 0) {
		puts(line + 3);
		return 0;
	}
	return print_msg_line(line, ctx);
}

static int print_dev_line(const char *line, void *ctx)
{
	(void)ctx;
	if (strncmp(line, "DEV ", 4) == 0) {
		puts(line + 4);
		return 0;
	}
	return print_msg_line(line, ctx);
}

static void usage(void)
{
	fputs(
	    "bbm — BerryCore device relay (Berry Bridge Messenger)\n\n"
	    "Usage:\n"
	    "  bbm send <to|@all> <message...>\n"
	    "  bbm poll\n"
	    "  bbm group [count]\n"
	    "  bbm who\n\n"
	    "Environment:\n"
	    "  BERRYRELAY_HOST   relay host (default: berrycore.sw7ft.com)\n"
	    "  BERRYRELAY_PORT   TCP port (default: 37193)\n"
	    "  BERRYRELAY_KEY    shared relay key (required)\n"
	    "  BERRYRELAY_FROM   sender hostname (default: hostname)\n\n"
	    "Examples:\n"
	    "  bbm send @all \"online\"\n"
	    "  bbm send BLACKBERRY-3F7B ping\n"
	    "  bbm poll\n",
	    stderr);
}

int main(int argc, char **argv)
{
	if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 ||
	    strcmp(argv[1], "help") == 0) {
		usage();
		return argc < 2 ? 1 : 0;
	}

	relay_t relay;
	relay_load_config(&relay);

	const char *cmd = argv[1];
	char command[4096];

	if (strcmp(cmd, "send") == 0) {
		if (argc < 4)
			die("usage: bbm send <to|@all> <message...>");
		char msgbuf[4096];
		size_t pos = 0;
		for (int i = 3; i < argc; i++) {
			if (i > 3 && pos + 1 < sizeof(msgbuf))
				msgbuf[pos++] = ' ';
			size_t n = strlen(argv[i]);
			if (pos + n >= sizeof(msgbuf))
				die("message too long");
			memcpy(msgbuf + pos, argv[i], n);
			pos += n;
		}
		msgbuf[pos] = '\0';
		snprintf(command, sizeof(command), "SEND %s %s", argv[2], msgbuf);
		return relay_session(&relay, command, print_ok_line, NULL) == 0 ? 0 : 1;
	}

	if (strcmp(cmd, "poll") == 0)
		return relay_session(&relay, "POLL", print_msg_line, NULL) == 0 ? 0 : 1;

	if (strcmp(cmd, "group") == 0) {
		int count = 50;
		if (argc >= 3)
			count = atoi(argv[2]);
		if (count < 1)
			count = 1;
		if (count > 200)
			count = 200;
		snprintf(command, sizeof(command), "GROUP %d", count);
		return relay_session(&relay, command, print_msg_line, NULL) == 0 ? 0 : 1;
	}

	if (strcmp(cmd, "who") == 0)
		return relay_session(&relay, "WHO", print_dev_line, NULL) == 0 ? 0 : 1;

	die("unknown command: %s (try --help)", cmd);
	return 1;
}
