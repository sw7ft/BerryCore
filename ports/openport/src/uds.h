#ifndef OPENPORT_UDS_H
#define OPENPORT_UDS_H

#include "openport.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint32_t tx_id;
	uint32_t rx_id;
} uds_link_t;

typedef struct {
	int ok;
	uint8_t payload[4096];
	size_t len;
	int nrc;
} uds_resp_t;

int uds_open_link(openport_t *op, uds_link_t *link, uint32_t tx_id, uint32_t rx_id,
		  unsigned baud);
void uds_close_link(openport_t *op);
int uds_send(openport_t *op, const uds_link_t *link, const uint8_t *payload, size_t len,
	     int timeout_ms, uds_resp_t *resp);
int uds_tester_present(openport_t *op, const uds_link_t *link);
int uds_read_did(openport_t *op, const uds_link_t *link, uint16_t did, uds_resp_t *resp);
const char *uds_nrc_label(int nrc);
void uds_ascii_print(const uint8_t *data, size_t len);

typedef struct {
	const char *name;
	uint32_t tx;
	uint32_t rx;
} fca_module_t;

extern const fca_module_t FCA_MODULES[];
extern const size_t FCA_MODULE_COUNT;

#endif
