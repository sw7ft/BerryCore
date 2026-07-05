#include "util.h"

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void die(const char *fmt, ...)
{
	va_list ap;
	fprintf(stderr, "bbm: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	exit(1);
}

void warnx(const char *fmt, ...)
{
	va_list ap;
	fprintf(stderr, "bbm: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
}

char *trim(char *s)
{
	while (*s && isspace((unsigned char)*s))
		s++;
	if (!*s)
		return s;
	char *end = s + strlen(s) - 1;
	while (end > s && isspace((unsigned char)*end))
		*end-- = '\0';
	return s;
}

int env_or(const char *name, char *buf, size_t buflen, const char *fallback)
{
	const char *v = getenv(name);
	if (v && *v) {
		snprintf(buf, buflen, "%s", v);
		return 0;
	}
	if (fallback) {
		snprintf(buf, buflen, "%s", fallback);
		return 0;
	}
	buf[0] = '\0';
	return -1;
}

const char *pick_hostname(char *buf, size_t buflen)
{
	if (env_or("BERRYRELAY_FROM", buf, buflen, NULL) == 0 && buf[0])
		return buf;
	if (gethostname(buf, buflen) == 0 && buf[0])
		return buf;
	snprintf(buf, buflen, "unknown");
	return buf;
}
