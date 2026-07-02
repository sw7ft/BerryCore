#ifndef OPENPORT_H
#define OPENPORT_H

#include "serial.h"

#include <stddef.h>
#include <stdint.h>

#define OP_CH_CAN       0x35
#define OP_CH_ISO15765  0x36

#define OP_FLAG_CAN_ID_BOTH  0x0800U
#define OP_FLAG_SNIFF_MODE   0x10000000U

#define OP_FILTER_PASS       1
#define OP_FILTER_FLOW_CTRL  3

#define OP_RX_ACC_SIZE  8192
#define OP_MSG_MAX      4120
#define OP_MSG_QUEUE    128

typedef struct {
	uint32_t ts_us;
	uint8_t data[OP_MSG_MAX];
	size_t len;
} op_msg_t;

typedef struct {
	serial_port_t serial;
	char firmware[160];
	char port_path[256];
	uint16_t seq;
	int channel_byte;
	int verbose;
	int debug;
	uint8_t rx_acc[OP_RX_ACC_SIZE];
	size_t rx_acc_len;
	op_msg_t queue[OP_MSG_QUEUE];
	size_t q_head;
	size_t q_tail;
} openport_t;

int op_open(openport_t *op, const char *path, int verbose, int debug);
void op_close(openport_t *op);
int op_connect(openport_t *op, int channel_byte, unsigned flags, unsigned baud);
int op_disconnect(openport_t *op);
int op_setup_pass_filter(openport_t *op);
int op_setup_flow_filter(openport_t *op, uint32_t tx_id, uint32_t rx_id);
int op_transmit(openport_t *op, const uint8_t *frame, size_t len, unsigned timeout_us);
int op_poll(openport_t *op, int timeout_ms);
size_t op_queue_count(const openport_t *op);
size_t op_queue_pop(openport_t *op, op_msg_t *out, size_t max);
void op_queue_clear(openport_t *op);
int op_read_voltage(openport_t *op, int pin, int *millivolts);
int op_wait_text(openport_t *op, const char *token, int timeout_ms);

#endif
