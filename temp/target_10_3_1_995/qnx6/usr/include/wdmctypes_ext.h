/*
 * (C) 2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * otasltypes_ext.h
 *
 *  Created on: July 18, 2012
 *      Author: haili/msobhani
 */
#ifndef OTASLTYPES_EXT_H_
#define OTASLTYPES_EXT_H_

#include <stdbool.h>
#include <stdint.h>

////////////////////////////
// request related types
////////////////////////////


// EVENTS

// Device Configuration Events
#define EVENT_DCS_CAN_NOT_PROCESS                "dcs_can_not_process"
#define EVENT_DCS_CHECKING_FOR_UPDATE            "dcs_checking_for_update"
#define EVENT_DCS_CONF_INSTALL_FAILED            "dcs_conf_install_failed"
#define EVENT_DCS_CONF_INSTALL_FINISHED          "dcs_conf_install_finished"
#define EVENT_DCS_CONF_READY_FOR_INSTALL         "dcs_conf_ready_for_install"
#define EVENT_DCS_CONNECTION_TIMEOUT             "dcs_connection_timeout"
#define EVENT_DCS_DOWNLOADING                    "dcs_downloading"
#define EVENT_DCS_DOWNLOAD_FAILED                "dcs_download_failed"
#define EVENT_DCS_DOWNLOAD_PAUSED                "dcs_download_paused"
#define EVENT_DCS_DOWNLOAD_RETRY                 "dcs_download_retry"
#define EVENT_DCS_DOWNLOAD_START                 "dcs_download_start"
#define EVENT_DCS_DOWNLOAD_TXN_BEGIN             "dcs_download_txn_begin"
#define EVENT_DCS_DOWNLOAD_TXN_CANCELLED         "dcs_download_txn_cancelled"
#define EVENT_DCS_DOWNLOAD_TXN_FAILED            "dcs_download_txn_failed"
#define EVENT_DCS_DOWNLOAD_TXN_PROGRESS          "dcs_download_txn_progress"
#define EVENT_DCS_DOWNLOAD_TXN_PROGRESS_BYTES    "dcs_download_txn_progress_bytes"
#define EVENT_DCS_DOWNLOAD_TXN_SUCCESS           "dcs_download_txn_success"
#define EVENT_DCS_EDID_INSTALL_FAILED            "dcs_edid_install_failed"
#define EVENT_DCS_EDID_INSTALL_FINISHED          "dcs_edid_install_finished"
#define EVENT_DCS_EDID_READY_FOR_INSTALL         "dcs_edid_ready_for_install"
#define EVENT_DCS_ERROR_CONNECTION               "dcs_error_connection"
#define EVENT_DCS_ERROR_RESULT                   "dcs_error_result"
#define EVENT_DCS_INSTALLATION_COMPLETE          "dcs_installation_complete"
#define EVENT_DCS_INSTALLATION_FAILED            "dcs_installation_failed"
#define EVENT_DCS_INSTALLATION_READY             "dcs_installation_ready"
#define EVENT_DCS_INSTALLATION_START             "dcs_installation_start"
#define EVENT_DCS_INSTALLING                     "dcs_installing"
#define EVENT_DCS_INSTALL_FAILED                 "dcs_install_failed"
#define EVENT_DCS_INSTALL_TXN_BEGIN              "dcs_install_txn_begin"
#define EVENT_DCS_INSTALL_TXN_CANCELLED          "dcs_install_txn_cancelled"
#define EVENT_DCS_INSTALL_TXN_FAILED             "dcs_install_txn_failed"
#define EVENT_DCS_INSTALL_TXN_SUCCESS            "dcs_install_txn_success"
#define EVENT_DCS_NOUPDATE_AVAILABLE             "dcs_noupdate_available"
#define EVENT_DCS_READY_FOR_DOWNLOAD             "dcs_ready_for_download"

// Shared Events
#define EVENT_ERROR_RESULT                       "error_result"
#define EVENT_NO_UPDATE_AVAILABLE                "noupdate_available"
#define EVENT_CONNECTION_TIMEOUT                 "connection_timedout"
#define EVENT_ERROR_CONNECTION                   "error_connection"
#define EVENT_DEVICE_INFO                        "device_info"
#define EVENT_CLIENT_CANCELLED                   "client_cancelled"

// ?
#define EVENT_NETWORK_UPDATE                           "network_update"

// Software Update Events
#define EVENT_UPDATE_READY_FOR_DOWNLOAD          "update_ready_for_download"

#define EVENT_DOWNLOAD_TXN_FAILED                "download_txn_failed"
#define EVENT_DOWNLOAD_TXN_CANCELLED             "download_txn_cancelled"
#define EVENT_DOWNLOAD_TXN_PROGRESS              "download_txn_progress"
#define EVENT_DOWNLOAD_TXN_PROGRESS_BYTES        "download_txn_progress_bytes"
#define EVENT_DOWNLOAD_TXN_BEGIN                 "download_txn_begin"
#define EVENT_DOWNLOAD_TXN_SUCCESS               "download_txn_success"
#define EVENT_DOWNLOAD_START                     "download_start"

#define EVENT_INSTALLATION_FAILED                "installation_failed"
#define EVENT_INSTALLATION_COMPLETE              "installation_complete"
#define EVENT_INSTALLATION_START                 "installation_start"
#define EVENT_INSTALL_TXN_BEGIN                  "install_txn_begin"
#define EVENT_INSTALL_TXN_SUCCESS                "install_txn_success"
#define EVENT_INSTALL_TXN_CANCELLED              "install_txn_cancelled"
#define EVENT_INSTALL_TXN_FAILED                 "install_txn_failed"
#define EVENT_INSTALL_TXN_PROGRESS               "install_txn_progress"

#define EVENT_EULA_URL                           "eula_url"
#define EVENT_EULA_AVAILABLE                     "eula_available"
#define EVENT_EULA_NOT_AVAILABLE                 "eula_not_available"

#define EVENT_DEVICE_ACTIVATION                  "device_activation"

enum otasl_states{
	STATE_NOT_INIT = 0x0000,
	STATE_IDLE = 0x1000,
	//back state
	STATE_BACK = 0x1001,
	//device config sub-states
	STATE_DC = 0x2000,
	STATE_DC_checking_for_update = 0x2001,
	STATE_DC_ready_for_download = 0x2002,
	STATE_DC_downloading = 0x2003,
	STATE_DC_download_paused = 0x2004,
	STATE_DC_download_failure = 0x2005,
	STATE_DC_download_retrying = 0x2006,
	STATE_DC_ready_for_install = 0x2007,
	STATE_DC_installing = 0x2008,
	STATE_DC_install_failure = 0x2009,
	STATE_DC_edid_ready_for_install = 0x200C,
	STATE_DC_conf_ready_for_install = 0x200D,
	STATE_DC_installing_edid = 0x200E,
	STATE_DC_installing_conf = 0x200F,
	STATE_DC_edid_install_finished = 0x2010,
	STATE_DC_conf_install_finished = 0x2011,
	STATE_DC_edid_install_failed = 0x2012,
	STATE_DC_conf_install_failed = 0x2013,
	STATE_DC_max = 0x2014,

	//software activation sub-states
	STATE_ACTIVATE = 0x4000,
	STATE_UPDATE_activating_device = 0x4001,
	STATE_ACTIVATE_max = 0x4002,

	//software eula sub-states
	STATE_EULA = 0x5000,
	STATE_UPDATE_checking_for_eula = 0x5001,
	STATE_UPDATE_eula_available = 0x5002,
	STATE_EULA_max = 0x5003,

	//software update sub-states
	STATE_UPDATE = 0x3000,
	STATE_UPDATE_checking_for_udpate = 0x3002,
	STATE_UPDATE_list_available = 0x3003,
	STATE_UPDATE_ready_for_download = 0x3007,
	STATE_UPDATE_downloading = 0x3008,
	STATE_UPDATE_download_paused = 0x3009,
	STATE_UPDATE_download_failure = 0x300A,
	STATE_UPDATE_download_retrying_connection = 0x300B,
	STATE_UPDATE_download_retry_waiting = 0x300C,
	STATE_UPDATE_ready_for_install = 0x300D,
	STATE_UPDATE_installing = 0x300E,
	STATE_UPDATE_install_failure = 0x300F,
	STATE_UPDATE_update_complete = 0x3010,
	STATE_UPDATE_rebooting = 0x3011,
	STATE_UPDATE_reporting_post_update_status = 0x3012,
	STATE_UPDATE_max = 0x3013
};

//*****************************
// pause reason codes
//*****************************
enum _pause_reasons_t
{
        USER_PAUSED = 0,
        NEW_NETWORK_PAUSED = 1,
        BLACKOUT_PAUSED = 2,
        DOWNLOAD_CONTROL_PAUSED = 3,
        TETHERED_PAUSED = 4,
        CAP_LIMIT_PAUSED = 5,
        LOW_BATTERY_PAUSED = 6,
        LOW_MEMORY_PAUSED = 7,
        //This is for NETWORK_CAPACITY_REACHED case
        DOWNLOAD_CONTROL_DEFERRED = 8,
        USER_NOT_GRANTED  = 9
};

typedef struct {
	char * objectName;  //objectName
	char * tag; 		//tag - this cannot be null or empty string
} data_cr_config_item_t;

typedef struct {
	int config_length;
	data_cr_config_item_t data_config[];

} data_req_detail_cr_t;


typedef union {
	data_req_detail_cr_t data_cr;
	//add other types in the future
	//
} data_req_t;



////////////////////////////
// response related types
////////////////////////////

typedef struct {
	const char *displayText;
	const char *locale;
} urlitem_t;

typedef struct {
	int num_urlitems;
	urlitem_t *urlitem_array;
} urlmap_t;

typedef struct {
	int numParts;
	const char *path;
	bool isnew;
	urlmap_t urlmap;
} eulaResult_t;

typedef struct {
	bool                              zero_rated;
	const char *                      apn;
	const char *                      name;
	const char *                      network_name;
	const char *                      network_type;
	const char *                      npc;
	const char *                      password;
	const char *                      username;
	int                               profile_id;
} transport_t;

typedef struct {
	bool firstPkg;
	bool reboot;
	bool refetch;
	bool retrying;
	bool vplOnly;
	const char *bundles;
	const char *description;
	const char *downloadResumeTime;
	const char *message;
	const char *versionSoftwareReleaseCurrent;
	const char *version_src;
	const char *version_tgt;
	const char *version_tgt_os;
	const char *version_tgt_radio;
	const char *version_tgt_software_release;
	int cancelReason;
	int error;
	int pauseReason;
	int postReasonCode;
	int postResultCode;
	int swuAllowed;
	int64_t bytes;
	int64_t currentGlobalProgress;
	int64_t progress;
	int64_t size;
	int64_t sizeCurrentBar;
	int64_t sizeOS;
	int64_t sizeRadio;
	int64_t totalGlobalProgress;
	eulaResult_t eulaResult;
	transport_t transport;
} swu_detail_t;

typedef union {
	swu_detail_t swu_detail;
	//add other types in the future
	//
} data_detail_t;

typedef struct {
	char * evt_id;
	int id;
	int type;
	bool complete;
	data_detail_t data_detail;
} data_resp_t;

#endif /* OTASLTYPES_EXT_H_ */
