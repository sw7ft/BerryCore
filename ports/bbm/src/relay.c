#include "relay.h"
#include "util.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int relay_load_config(relay_t *r)
{
	memset(r, 0, sizeof(*r));
	r->fd = -1;
	r->port = 37193;

	env_or("BERRYRELAY_HOST", r->host, sizeof(r->host), "berrycore.sw7ft.com");
	const char *port_env = getenv("BERRYRELAY_PORT");
	if (port_env && *port_env)
		r->port = atoi(port_env);
	if (r->port <= 0 || r->port > 65535)
		die("invalid BERRYRELAY_PORT");

	pick_hostname(r->from, sizeof(r->from));
	if (env_or("BERRYRELAY_KEY", r->key, sizeof(r->key), NULL) != 0 || !r->key[0])
		die("BERRYRELAY_KEY is not set");
	return 0;
}

static int relay_read_line(int fd, char *buf, size_t buflen)
{
	size_t n = 0;
	while (n + 1 < buflen) {
		char c;
		ssize_t rc = read(fd, &c, 1);
		if (rc == 0)
			return -1;
		if (rc < 0) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		if (c == '\r')
			continue;
		if (c == '\n') {
			buf[n] = '\0';
			return 0;
		}
		buf[n++] = c;
	}
	buf[buflen - 1] = '\0';
	return 0;
}

static int relay_write_all(int fd, const char *data)
{
	size_t left = strlen(data);
	while (left > 0) {
		ssize_t n = write(fd, data, left);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		data += n;
		left -= (size_t)n;
	}
	return 0;
}

static int relay_connect_tcp(relay_t *r)
{
	struct hostent *he = gethostbyname(r->host);
	if (!he || !he->h_addr_list[0])
		die("cannot resolve %s", r->host);

	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons((uint16_t)r->port);
	memcpy(&sa.sin_addr, he->h_addr_list[0], (size_t)he->h_length);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		die("socket failed (%s)", strerror(errno));
	if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
		close(fd);
		die("cannot connect to %s:%d (%s)", r->host, r->port, strerror(errno));
	}
	r->fd = fd;
	return 0;
}

static int relay_handle_line(const char *line, int (*on_line)(const char *, void *), void *ctx)
{
	if (strncmp(line, "ERR ", 4) == 0)
		die("%s", line + 4);
	if (strcmp(line, "END") == 0)
		return 1;
	if (on_line && on_line(line, ctx) != 0)
		return 1;
	return 0;
}

int relay_session(relay_t *r, const char *command,
		  int (*on_line)(const char *line, void *ctx), void *ctx)
{
	char line[RELAY_IO_BUF];
	char auth[512];

	if (relay_connect_tcp(r) != 0)
		return -1;

	if (relay_read_line(r->fd, line, sizeof(line)) != 0)
		die("relay closed before greeting");
	if (strncmp(line, "BerryRelay", 10) != 0)
		warnx("unexpected greeting: %s", line);

	snprintf(auth, sizeof(auth), "AUTH %s %s\n", r->from, r->key);
	if (relay_write_all(r->fd, auth) != 0)
		die("write failed (%s)", strerror(errno));

	if (relay_read_line(r->fd, line, sizeof(line)) != 0)
		die("relay closed during auth");
	if (strncmp(line, "ERR ", 4) == 0)
		die("%s", line + 4);
	if (strncmp(line, "OK ", 3) != 0)
		die("unexpected auth response: %s", line);

	char cmdbuf[RELAY_IO_BUF];
	snprintf(cmdbuf, sizeof(cmdbuf), "%s\nQUIT\n", command);
	if (relay_write_all(r->fd, cmdbuf) != 0)
		die("write failed (%s)", strerror(errno));

	for (;;) {
		if (relay_read_line(r->fd, line, sizeof(line)) != 0)
			break;
		if (relay_handle_line(line, on_line, ctx))
			break;
	}

	close(r->fd);
	r->fd = -1;
	return 0;
}
