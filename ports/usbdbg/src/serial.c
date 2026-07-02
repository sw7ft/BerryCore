#include "serial.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static speed_t baud_to_speed(int baud)
{
	switch (baud) {
	case 9600: return B9600;
	case 19200: return B19200;
	case 38400: return B38400;
	case 57600: return B57600;
	case 115200: return B115200;
#ifdef B230400
	case 230400: return B230400;
#endif
#ifdef B460800
	case 460800: return B460800;
#endif
#ifdef B921600
	case 921600: return B921600;
#endif
	default:
		return B115200;
	}
}

int serial_open(serial_port_t *sp, const char *path, int baud)
{
	memset(sp, 0, sizeof(*sp));
	sp->fd = -1;
	sp->baud = baud;
	snprintf(sp->path, sizeof(sp->path), "%s", path);

	int fd = open(path, O_RDWR | O_NOCTTY);
	if (fd < 0)
		return -1;

	struct termios tio;
	if (tcgetattr(fd, &tio) != 0) {
		close(fd);
		return -1;
	}

	cfmakeraw(&tio);
	tio.c_cflag |= (CLOCAL | CREAD);
	tio.c_cflag &= ~CSIZE;
	tio.c_cflag |= CS8;
	tio.c_cflag &= ~PARENB;
	tio.c_cflag &= ~CSTOPB;
#ifdef CRTSCTS
	tio.c_cflag &= ~CRTSCTS;
#endif
	tio.c_cc[VMIN] = 0;
	tio.c_cc[VTIME] = 0;

	speed_t speed = baud_to_speed(baud);
	cfsetispeed(&tio, speed);
	cfsetospeed(&tio, speed);

	if (tcsetattr(fd, TCSANOW, &tio) != 0) {
		close(fd);
		return -1;
	}

	tcflush(fd, TCIOFLUSH);
	sp->fd = fd;
	return 0;
}

void serial_close(serial_port_t *sp)
{
	if (sp->fd >= 0) {
		close(sp->fd);
		sp->fd = -1;
	}
}

void serial_flush(serial_port_t *sp)
{
	if (sp->fd >= 0)
		tcflush(sp->fd, TCIOFLUSH);
}

int serial_write(serial_port_t *sp, const uint8_t *data, size_t len)
{
	size_t off = 0;
	while (off < len) {
		ssize_t n = write(sp->fd, data + off, len - off);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		off += (size_t)n;
	}
	return (int)len;
}

int serial_read(serial_port_t *sp, uint8_t *buf, size_t cap, int timeout_ms)
{
	fd_set rfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_SET(sp->fd, &rfds);
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;

	int sel = select(sp->fd + 1, &rfds, NULL, NULL, &tv);
	if (sel <= 0)
		return sel;

	ssize_t n = read(sp->fd, buf, cap);
	if (n < 0)
		return -1;
	return (int)n;
}
