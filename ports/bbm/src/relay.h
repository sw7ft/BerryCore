#ifndef BBM_RELAY_H
#define BBM_RELAY_H

#include <stddef.h>

#define RELAY_IO_BUF 4096

typedef struct {
	int fd;
	char host[256];
	int port;
	char from[128];
	char key[256];
} relay_t;

int relay_load_config(relay_t *r);
int relay_session(relay_t *r, const char *command,
		  int (*on_line)(const char *line, void *ctx), void *ctx);

#endif
