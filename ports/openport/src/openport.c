#include "openport.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint16_t op_next_seq(openport_t *op)
{
	op->seq = (uint16_t)((op->seq + 1) & 0xffff);
	if (op->seq == 0)
		op->seq = 1;
	return op->seq;
}

static int op_send_cmd(openport_t *op, const char *cmd)
{
	size_t len = strlen(cmd);
	uint8_t buf[256];
	if (len + 2 > sizeof(buf))
		return -1;
	memcpy(buf, cmd, len);
	buf[len++] = '\r';
	buf[len++] = '\n';
	op_log_debug(op->debug, "TX cmd: %s", cmd);
	return serial_write(&op->serial, buf, len);
}

static int op_send_binary(openport_t *op, const char *header, const uint8_t *payload, size_t plen)
{
	size_t hlen = strlen(header);
	uint8_t buf[512];
	if (hlen + plen > sizeof(buf))
		return -1;
	memcpy(buf, header, hlen);
	if (payload && plen)
		memcpy(buf + hlen, payload, plen);
	op_log_debug(op->debug, "TX binary header: %s (%zu payload bytes)", header, plen);
	return serial_write(&op->serial, buf, hlen + plen);
}

static int buf_has_text(const uint8_t *buf, size_t len, const char *needle)
{
	size_t nlen = strlen(needle);
	if (len < nlen)
		return 0;
	for (size_t i = 0; i + nlen <= len; i++) {
		if (memcmp(buf + i, needle, nlen) == 0)
			return 1;
	}
	return 0;
}

int op_wait_text(openport_t *op, const char *token, int timeout_ms)
{
	uint8_t acc[512];
	size_t acc_len = 0;

	for (int elapsed = 0; elapsed < timeout_ms; elapsed += 50) {
		uint8_t chunk[256];
		int n = serial_read(&op->serial, chunk, sizeof(chunk), 50);
		if (n <= 0)
			continue;
		if (acc_len + (size_t)n > sizeof(acc))
			acc_len = 0;
		memcpy(acc + acc_len, chunk, (size_t)n);
		acc_len += (size_t)n;
		if (buf_has_text(acc, acc_len, token))
			return 0;
	}
	return -1;
}

static int op_parse_version(const uint8_t *buf, size_t len, char *out, size_t outsz)
{
	const char *tag = "ari";
	for (size_t i = 0; i + 3 < len; i++) {
		if (memcmp(buf + i, tag, 3) != 0)
			continue;
		size_t start = i + 3;
		while (start < len && (buf[start] == ' ' || buf[start] == '\r' || buf[start] == '\n'))
			start++;
		size_t end = start;
		while (end < len && buf[end] != '\r' && buf[end] != '\n')
			end++;
		size_t n = end - start;
		if (n >= outsz)
			n = outsz - 1;
		memcpy(out, buf + start, n);
		out[n] = '\0';
		return 0;
	}
	return -1;
}

static int op_parse_voltage(const uint8_t *buf, size_t len, int *mv)
{
	const char *tag = "arr";
	for (size_t i = 0; i + 3 < len; i++) {
		if (memcmp(buf + i, tag, 3) != 0)
			continue;
		size_t start = i + 3;
		while (start < len && (buf[start] == ' ' || buf[start] == '\r'))
			start++;
		char tmp[32];
		size_t j = 0;
		while (start < len && buf[start] != '\r' && buf[start] != '\n' && j + 1 < sizeof(tmp)) {
			tmp[j++] = (char)buf[start++];
		}
		tmp[j] = '\0';
		char *endp = NULL;
		long v = strtol(tmp, &endp, 10);
		if (endp == tmp)
			return -1;
		*mv = (int)v;
		return 0;
	}
	return -1;
}

static uint32_t parse_ts_be(const uint8_t *p)
{
	return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
	       ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

static void op_queue_push(openport_t *op, const op_msg_t *msg)
{
	size_t next = (op->q_tail + 1) % OP_MSG_QUEUE;
	if (next == op->q_head)
		op->q_head = (op->q_head + 1) % OP_MSG_QUEUE;
	op->queue[op->q_tail] = *msg;
	op->q_tail = next;
}

static void op_feed_rx(openport_t *op, const uint8_t *data, size_t len)
{
	if (op->rx_acc_len + len > OP_RX_ACC_SIZE) {
		op_log_warn("RX buffer overflow — discarding partial data");
		op->rx_acc_len = 0;
	}
	memcpy(op->rx_acc + op->rx_acc_len, data, len);
	op->rx_acc_len += len;
}

static void op_parse_rx_buffer(openport_t *op)
{
	size_t off = 0;

	while (off < op->rx_acc_len) {
		if (op->rx_acc[off] != 0x61 || off + 1 >= op->rx_acc_len ||
		    op->rx_acc[off + 1] != 0x72) {
			if (buf_has_text(op->rx_acc + off, op->rx_acc_len - off, "ari") ||
			    buf_has_text(op->rx_acc + off, op->rx_acc_len - off, "aro") ||
			    buf_has_text(op->rx_acc + off, op->rx_acc_len - off, "arf") ||
			    buf_has_text(op->rx_acc + off, op->rx_acc_len - off, "arr")) {
				off++;
				continue;
			}
			off++;
			continue;
		}

		if (op->rx_acc[off + 2] == 0x6f) {
			off += 4;
			continue;
		}

		if (off + 5 > op->rx_acc_len)
			break;

		uint8_t pkt_len = op->rx_acc[off + 3];
		size_t total = (size_t)pkt_len + 4;
		if (off + total > op->rx_acc_len)
			break;

		uint8_t ptype = op->rx_acc[off + 4];
		const uint8_t *payload = op->rx_acc + off + 5;
		size_t plen = pkt_len > 0 ? (size_t)pkt_len - 1 : 0;

		if (ptype == 0x00 || ptype == 0x20 || ptype == 0x40) {
			if (plen >= 4) {
				op_msg_t msg;
				msg.ts_us = parse_ts_be(payload);
				size_t dlen = plen - 4;
				if (dlen > OP_MSG_MAX)
					dlen = OP_MSG_MAX;
				memcpy(msg.data, payload + 4, dlen);
				msg.len = dlen;
				if (dlen > 0)
					op_queue_push(op, &msg);
			}
		}

		off += total;
	}

	if (off > 0) {
		memmove(op->rx_acc, op->rx_acc + off, op->rx_acc_len - off);
		op->rx_acc_len -= off;
	}
}

int op_poll(openport_t *op, int timeout_ms)
{
	uint8_t chunk[2048];
	int n = serial_read(&op->serial, chunk, sizeof(chunk), timeout_ms);
	if (n <= 0)
		return n;
	if (op->debug) {
		char hex[128];
		size_t show = (size_t)n > 32 ? 32 : (size_t)n;
		op_hex_format(hex, sizeof(hex), chunk, show);
		op_log_debug(1, "RX %d bytes: %s%s", n, hex, n > 32 ? " …" : "");
	}
	op_feed_rx(op, chunk, (size_t)n);
	op_parse_rx_buffer(op);
	return n;
}

size_t op_queue_count(const openport_t *op)
{
	if (op->q_tail >= op->q_head)
		return op->q_tail - op->q_head;
	return OP_MSG_QUEUE - op->q_head + op->q_tail;
}

size_t op_queue_pop(openport_t *op, op_msg_t *out, size_t max)
{
	size_t n = 0;
	while (n < max && op->q_head != op->q_tail) {
		out[n++] = op->queue[op->q_head];
		op->q_head = (op->q_head + 1) % OP_MSG_QUEUE;
	}
	return n;
}

void op_queue_clear(openport_t *op)
{
	op->q_head = op->q_tail = 0;
}

int op_open(openport_t *op, const char *path, int verbose, int debug)
{
	memset(op, 0, sizeof(*op));
	op->serial.fd = -1;
	op->verbose = verbose;
	op->debug = debug;
	snprintf(op->port_path, sizeof(op->port_path), "%s", path);

	for (int attempt = 1; attempt <= 3; attempt++) {
		if (serial_open(&op->serial, path, 115200) == 0)
			break;
		if (attempt == 3)
			return -1;
		op_log_warn("Serial open failed (attempt %d/3), retrying…", attempt);
		usleep(300000);
	}

	const char *ident = "\r\n\r\nati\r\n";
	if (serial_write(&op->serial, (const uint8_t *)ident, strlen(ident)) < 0)
		return -1;

	uint8_t acc[512];
	size_t acc_len = 0;
	for (int t = 0; t < 60; t++) {
		uint8_t chunk[128];
		int n = serial_read(&op->serial, chunk, sizeof(chunk), 50);
		if (n <= 0)
			continue;
		if (acc_len + (size_t)n > sizeof(acc))
			acc_len = 0;
		memcpy(acc + acc_len, chunk, (size_t)n);
		acc_len += (size_t)n;
		if (op_parse_version(acc, acc_len, op->firmware, sizeof(op->firmware)) == 0)
			break;
	}

	if (op->firmware[0] == '\0') {
		op_log_err("No firmware response on %s", path);
		op_log_err("Hints: check OTG cable, try `openport ports`, confirm 0403:cc4d USB device");
		return -1;
	}

	if (op_send_cmd(op, "ata") != 0)
		return -1;
	if (op_wait_text(op, "aro", 3000) != 0) {
		op_log_err("Attach (ata) failed — cable may be busy or wrong device");
		return -1;
	}

	op_log_verbose("Firmware: %s", op->firmware);
	return 0;
}

void op_close(openport_t *op)
{
	if (op->channel_byte) {
		char cmd[32];
		snprintf(cmd, sizeof(cmd), "atc%c", op->channel_byte);
		op_send_cmd(op, cmd);
		op->channel_byte = 0;
	}
	op_send_cmd(op, "atz");
	serial_close(&op->serial);
}

int op_connect(openport_t *op, int channel_byte, unsigned flags, unsigned baud)
{
	char cmd[96];
	snprintf(cmd, sizeof(cmd), "ato%c %u %u 0 %u", channel_byte, flags, baud,
		 op_next_seq(op));
	if (op_send_cmd(op, cmd) != 0)
		return -1;
	if (op_wait_text(op, "aro", 3000) != 0) {
		op_log_err("Channel open failed (ato) — check vehicle key ON and OBD connection");
		return -1;
	}
	op->channel_byte = channel_byte;
	op_queue_clear(op);
	op->rx_acc_len = 0;
	return 0;
}

int op_disconnect(openport_t *op)
{
	if (!op->channel_byte)
		return 0;
	char cmd[32];
	snprintf(cmd, sizeof(cmd), "atc%c", op->channel_byte);
	op_send_cmd(op, cmd);
	op->channel_byte = 0;
	op_queue_clear(op);
	return 0;
}

int op_setup_pass_filter(openport_t *op)
{
	uint8_t z[4] = {0, 0, 0, 0};
	char header[64];
	snprintf(header, sizeof(header), "atf%c %d 0 4\r\n", op->channel_byte, OP_FILTER_PASS);
	uint8_t payload[8];
	memcpy(payload, z, 4);
	memcpy(payload + 4, z, 4);
	if (op_send_binary(op, header, payload, 8) != 0)
		return -1;
	return op_wait_text(op, "arf", 2000);
}

int op_setup_flow_filter(openport_t *op, uint32_t tx_id, uint32_t rx_id)
{
	uint8_t mask[4] = {0xff, 0xff, 0xff, 0xff};
	uint8_t txb[4], rxb[4];
	op_id_to_bytes(tx_id, txb);
	op_id_to_bytes(rx_id, rxb);
	char header[64];
	snprintf(header, sizeof(header), "atf%c %d 0 4\r\n", op->channel_byte,
		 OP_FILTER_FLOW_CTRL);
	uint8_t payload[12];
	memcpy(payload, mask, 4);
	memcpy(payload + 4, txb, 4);
	memcpy(payload + 8, rxb, 4);
	if (op_send_binary(op, header, payload, 12) != 0)
		return -1;
	return op_wait_text(op, "arf", 2000);
}

int op_transmit(openport_t *op, const uint8_t *frame, size_t len, unsigned timeout_us)
{
	char header[96];
	snprintf(header, sizeof(header), "att%c %zu 0 %u %u\r\n", op->channel_byte, len,
		 timeout_us, op_next_seq(op));
	return op_send_binary(op, header, frame, len);
}

int op_read_voltage(openport_t *op, int pin, int *millivolts)
{
	char cmd[32];
	snprintf(cmd, sizeof(cmd), "atr %d", pin);
	if (op_send_cmd(op, cmd) != 0)
		return -1;

	uint8_t acc[128];
	size_t acc_len = 0;
	for (int t = 0; t < 40; t++) {
		uint8_t chunk[64];
		int n = serial_read(&op->serial, chunk, sizeof(chunk), 50);
		if (n <= 0)
			continue;
		if (acc_len + (size_t)n > sizeof(acc))
			acc_len = 0;
		memcpy(acc + acc_len, chunk, (size_t)n);
		acc_len += (size_t)n;
		if (op_parse_voltage(acc, acc_len, millivolts) == 0)
			return 0;
	}
	return -1;
}
