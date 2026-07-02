#ifndef OPENPORT_UTIL_H
#define OPENPORT_UTIL_H

#include <signal.h>
#include <stddef.h>
#include <stdint.h>

#define OP_ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

extern volatile sig_atomic_t op_interrupted;

void op_set_log_level(int verbose, int debug);
void op_install_signals(void);
void op_hex_format(char *out, size_t outsz, const uint8_t *data, size_t len);
void op_hex_format_compact(char *out, size_t outsz, const uint8_t *data, size_t len);
uint32_t op_id_from_bytes(const uint8_t b[4]);
void op_id_to_bytes(uint32_t id, uint8_t out[4]);
const char *op_pick_port(const char *user);
int op_list_ports(void);
int op_port_accessible(const char *path);
void op_log_info(const char *fmt, ...);
void op_log_verbose(const char *fmt, ...);
void op_log_warn(const char *fmt, ...);
void op_log_err(const char *fmt, ...);
void op_log_debug(int enabled, const char *fmt, ...);

#endif
