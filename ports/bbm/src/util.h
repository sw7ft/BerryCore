#ifndef BBM_UTIL_H
#define BBM_UTIL_H

#include <stddef.h>

void die(const char *fmt, ...);
void warnx(const char *fmt, ...);
char *trim(char *s);
int env_or(const char *name, char *buf, size_t buflen, const char *fallback);
const char *pick_hostname(char *buf, size_t buflen);

#endif
