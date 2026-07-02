#ifndef SERDBG_UTIL_H
#define SERDBG_UTIL_H

#include <signal.h>
#include <stddef.h>
#include <stdint.h>

extern volatile sig_atomic_t serdbg_interrupted;

void serdbg_install_signals(void);
void serdbg_hex(char *out, size_t outsz, const uint8_t *data, size_t len);
void serdbg_ascii(char *out, size_t outsz, const uint8_t *data, size_t len);
int serdbg_parse_hex(const char *s, uint8_t *out, size_t cap, size_t *len);
int serdbg_unescape(const char *in, char *out, size_t outsz);
const char *serdbg_pick_port(const char *user);
int serdbg_list_ports(void);
int serdbg_port_ok(const char *path);
size_t serdbg_scan_glob_ports(char paths[][256], size_t max);

#endif
