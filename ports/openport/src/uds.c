#include "uds.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

const fca_module_t FCA_MODULES[] = {
	{"PCM (engine)",       0x7e0, 0x7e8},
	{"TCM (transmission)", 0x7e1, 0x7e9},
	{"ECU #3",             0x7e2, 0x7ea},
	{"ECU #4",             0x7e3, 0x7eb},
	{"BCM (FCA alt)",      0x620, 0x504},
	{"BCM (alt 2)",        0x740, 0x748},
	{"ABS (alt)",          0x760, 0x768},
	{"Cluster",            0x720, 0x728},
	{"Radio/AMP",          0x726, 0x72e},
};

const size_t FCA_MODULE_COUNT = sizeof(FCA_MODULES) / sizeof(FCA_MODULES[0]);

int uds_open_link(openport_t *op, uds_link_t *link, uint32_t tx_id, uint32_t rx_id,
		  unsigned baud)
{
	link->tx_id = tx_id;
	link->rx_id = rx_id;
	op_queue_clear(op);
	if (op_connect(op, OP_CH_ISO15765, OP_FLAG_CAN_ID_BOTH, baud) != 0)
		return -1;
	return op_setup_flow_filter(op, tx_id, rx_id);
}

void uds_close_link(openport_t *op)
{
	op_disconnect(op);
}

static int build_iso_frame(uint32_t tx_id, const uint8_t *payload, size_t plen,
			   uint8_t *out, size_t outsz, size_t *outlen)
{
	if (plen > 4095 || plen + 5 > outsz)
		return -1;
	uint8_t idb[4];
	op_id_to_bytes(tx_id, idb);
	out[0] = idb[0];
	out[1] = idb[1];
	out[2] = idb[2];
	out[3] = idb[3];
	out[4] = (uint8_t)plen;
	memcpy(out + 5, payload, plen);
	*outlen = plen + 5;
	return 0;
}

static int uds_collect_response(openport_t *op, const uds_link_t *link, int timeout_ms,
				uds_resp_t *resp)
{
	uint8_t parts[4096];
	size_t parts_len = 0;
	size_t expected = 0;
	int deadline = timeout_ms;

	memset(resp, 0, sizeof(*resp));

	while (deadline > 0 && !op_interrupted) {
		op_msg_t msgs[16];
		op_poll(op, deadline > 200 ? 200 : deadline);
		size_t n = op_queue_pop(op, msgs, 16);
		for (size_t i = 0; i < n; i++) {
			if (msgs[i].len < 5)
				continue;
			uint32_t rid = op_id_from_bytes(msgs[i].data);
			if (rid != link->rx_id)
				continue;

			uint8_t pci = msgs[i].data[4];
			if ((pci & 0xf0) == 0x00) {
				size_t uds_len = pci & 0x0f;
				if (5 + uds_len > msgs[i].len)
					continue;
				resp->ok = 1;
				resp->len = uds_len;
				memcpy(resp->payload, msgs[i].data + 5, uds_len);
				return 0;
			}
			if ((pci & 0xf0) == 0x10) {
				expected = ((size_t)(pci & 0x0f) << 8) | msgs[i].data[5];
				parts_len = 0;
				if (msgs[i].len > 6) {
					size_t chunk = msgs[i].len - 6;
					memcpy(parts, msgs[i].data + 6, chunk);
					parts_len = chunk;
				}
				continue;
			}
			if ((pci & 0xf0) == 0x20) {
				if (msgs[i].len > 5) {
					size_t chunk = msgs[i].len - 5;
					if (parts_len + chunk <= sizeof(parts)) {
						memcpy(parts + parts_len, msgs[i].data + 5, chunk);
						parts_len += chunk;
					}
				}
				if (expected > 0 && parts_len >= expected) {
					resp->ok = 1;
					resp->len = expected;
					memcpy(resp->payload, parts, expected);
					return 0;
				}
				if (parts_len > 32) {
					resp->ok = 1;
					resp->len = parts_len;
					memcpy(resp->payload, parts, parts_len);
					return 0;
				}
			}
		}
		deadline -= 200;
	}

	resp->ok = 0;
	return -1;
}

int uds_send(openport_t *op, const uds_link_t *link, const uint8_t *payload, size_t len,
	     int timeout_ms, uds_resp_t *resp)
{
	uint8_t frame[4120];
	size_t flen;
	if (build_iso_frame(link->tx_id, payload, len, frame, sizeof(frame), &flen) != 0)
		return -1;
	op_queue_clear(op);
	if (op_transmit(op, frame, flen, 1000000) != 0)
		return -1;
	return uds_collect_response(op, link, timeout_ms, resp);
}

int uds_tester_present(openport_t *op, const uds_link_t *link)
{
	const uint8_t tp[] = {0x3e, 0x00};
	uds_resp_t r;
	if (uds_send(op, link, tp, sizeof(tp), 800, &r) != 0 || !r.ok)
		return 0;
	return r.len >= 1 && r.payload[0] == 0x7e;
}

int uds_read_did(openport_t *op, const uds_link_t *link, uint16_t did, uds_resp_t *resp)
{
	uint8_t req[] = {0x22, (uint8_t)(did >> 8), (uint8_t)(did & 0xff)};
	return uds_send(op, link, req, sizeof(req), 2500, resp);
}

const char *uds_nrc_label(int nrc)
{
	switch (nrc) {
	case 0x10: return "general reject";
	case 0x11: return "service not supported";
	case 0x12: return "sub-function not supported";
	case 0x13: return "incorrect length";
	case 0x22: return "conditions not correct";
	case 0x31: return "request out of range";
	case 0x33: return "security access denied";
	case 0x78: return "response pending";
	default:   return "unknown NRC";
	}
}

void uds_ascii_print(const uint8_t *data, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		char c = (data[i] >= 0x20 && data[i] <= 0x7e) ? (char)data[i] : '.';
		putchar(c);
	}
}
