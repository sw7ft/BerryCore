#ifndef SERDBG_SERIAL_H
#define SERDBG_SERIAL_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
	int fd;
	char path[256];
	int baud;
} serial_port_t;

int serial_open(serial_port_t *sp, const char *path, int baud);
void serial_close(serial_port_t *sp);
int serial_write(serial_port_t *sp, const uint8_t *data, size_t len);
int serial_read(serial_port_t *sp, uint8_t *buf, size_t cap, int timeout_ms);
void serial_flush(serial_port_t *sp);

#endif
