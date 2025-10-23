/*
 * (C) 2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 * otasl_state_ext.h
 *
 *  Created on: July 18, 2012
 *      Author: haili/msobhani
 */

#ifndef OTASL_STATE_EXT_H_
#define OTASL_STATE_EXT_H_

enum otasl_status{
    OTA_STATE_NOT_INIT = 0x0000,                               // 0
    OTA_STATE_IDLE = 0x1000,                                   // 4096
    //back state
    OTA_STATE_BACK = 0x1001,                                   // 4097
    //device config sub-states
    OTA_STATE_DC = 0x2000,                                     // 8192
    OTA_STATE_DC_checking_for_update = 0x2001,                 // 8193
    OTA_STATE_DC_ready_for_download = 0x2002,                  // 8194
    OTA_STATE_DC_downloading = 0x2003,                         // 8195
    OTA_STATE_DC_download_paused = 0x2004,                     // 8196
    OTA_STATE_DC_download_failure = 0x2005,                    // 8197
    OTA_STATE_DC_download_retrying = 0x2006,                   // 8198
    OTA_STATE_DC_ready_for_install = 0x2007,                   // 8199
    OTA_STATE_DC_installing = 0x2008,                          // 8200
    OTA_STATE_DC_install_failure = 0x2009,                     // 8201
    OTA_STATE_DC_edid_ready_for_install = 0x200C,              // 8204
    OTA_STATE_DC_conf_ready_for_install = 0x200D,              // 8205
    OTA_STATE_DC_installing_edid = 0x200E,                     // 8206
    OTA_STATE_DC_installing_conf = 0x200F,                     // 8207
    OTA_STATE_DC_edid_install_finished = 0x2010,               // 8208
    OTA_STATE_DC_conf_install_finished = 0x2011,               // 8209
    OTA_STATE_DC_edid_install_failed = 0x2012,                 // 8210
    OTA_STATE_DC_conf_install_failed = 0x2013,                 // 8211
    OTA_STATE_DC_max = 0x2014,                                 // 8212

    //software updat sub-states
    OTA_STATE_UPDATE = 0x3000,                                 // 12288
    OTA_STATE_UPDATE_checking_for_udpate = 0x3002,             // 12290
    OTA_STATE_UPDATE_list_available = 0x3003,                  // 12291
    OTA_STATE_UPDATE_ready_for_download = 0x3007,              // 12295
    OTA_STATE_UPDATE_downloading = 0x3008,                     // 12296
    OTA_STATE_UPDATE_download_paused = 0x3009,                 // 12297
    OTA_STATE_UPDATE_download_failure = 0x300A,                // 12298
    OTA_STATE_UPDATE_download_retrying_connection = 0x300B,    // 12299
    OTA_STATE_UPDATE_download_retry_waiting = 0x300C,          // 12300
    OTA_STATE_UPDATE_ready_for_install = 0x300D,               // 12301
    OTA_STATE_UPDATE_installing = 0x300E,                      // 12302
    OTA_STATE_UPDATE_install_failure = 0x300F,                 // 12303
    OTA_STATE_UPDATE_update_complete = 0x3010,                 // 12304
    OTA_STATE_UPDATE_rebooting = 0x3011,                       // 12305
    OTA_STATE_UPDATE_reporting_post_update_status = 0x3012,    // 12306
    OTA_STATE_UPDATE_max = 0x3013,                             // 12307

    //software activation sub-states
    OTA_STATE_ACTIVATE = 0x4000,                               // 16384
    OTA_STATE_UPDATE_activating_device = 0x4001,               // 16385
    OTA_STATE_ACTIVATE_max = 0x4002,                           // 16386

    //software eula sub-states
    OTA_STATE_EULA = 0x5000,                                   // 20480
    OTA_STATE_UPDATE_checking_for_eula = 0x5001,               // 20481
    OTA_STATE_UPDATE_eula_available = 0x5002,                  // 20482
    OTA_STATE_EULA_max = 0x5003,                               // 20483

    OTA_STATE_ALL_STATES,
    OTA_STATE_max,

    OTA_EVENT_NULL,
	// DC Events
	OTA_EVENT_DCS_CAN_NOT_PROCESS,
	OTA_EVENT_DCS_CHECKING_FOR_UPDATE,
	OTA_EVENT_DCS_CONF_INSTALL_FAILED,
	OTA_EVENT_DCS_CONF_INSTALL_FINISHED,
	OTA_EVENT_DCS_CONF_READY_FOR_INSTALL,
	OTA_EVENT_DCS_CONNECTION_TIMEOUT,
	OTA_EVENT_DCS_DOWNLOADING,
	OTA_EVENT_DCS_DOWNLOAD_FAILED,
	OTA_EVENT_DCS_DOWNLOAD_PAUSED,
	OTA_EVENT_DCS_DOWNLOAD_RETRY,
	OTA_EVENT_DCS_DOWNLOAD_START,
	OTA_EVENT_DCS_DOWNLOAD_TXN_BEGIN,
	OTA_EVENT_DCS_DOWNLOAD_TXN_CANCELLED,
	OTA_EVENT_DCS_DOWNLOAD_TXN_FAILED,
	OTA_EVENT_DCS_DOWNLOAD_TXN_PROGRESS,
	OTA_EVENT_DCS_DOWNLOAD_TXN_PROGRESS_BYTES,
	OTA_EVENT_DCS_DOWNLOAD_TXN_SUCCESS,
	OTA_EVENT_DCS_EDID_INSTALL_FAILED,
	OTA_EVENT_DCS_EDID_INSTALL_FINISHED,
	OTA_EVENT_DCS_EDID_READY_FOR_INSTALL,
	OTA_EVENT_DCS_ERROR_CONNECTION,
	OTA_EVENT_DCS_ERROR_RESULT,
	OTA_EVENT_DCS_INSTALLATION_COMPLETE,
	OTA_EVENT_DCS_INSTALLATION_FAILED,
	OTA_EVENT_DCS_INSTALLATION_READY,
	OTA_EVENT_DCS_INSTALLATION_START,
	OTA_EVENT_DCS_INSTALLING,
	OTA_EVENT_DCS_INSTALL_FAILED,
	OTA_EVENT_DCS_INSTALL_TXN_BEGIN,
	OTA_EVENT_DCS_INSTALL_TXN_CANCELLED,
	OTA_EVENT_DCS_INSTALL_TXN_FAILED,
	OTA_EVENT_DCS_INSTALL_TXN_SUCCESS,
	OTA_EVENT_DCS_NOUPDATE_AVAILABLE,
	OTA_EVENT_DCS_READY_FOR_DOWNLOAD,

	//cfu related
	OTA_EVENT_CHECKING_FOR_UPDATE,
	OTA_EVENT_NO_UPDATE_AVAILABLE,
	OTA_EVENT_UPDATE_BUNDLE_LIST,
	OTA_EVENT_UPDATE_READY_FOR_DOWNLOAD,
	OTA_EVENT_DEFER_UPDATE,

	//overall download events
	OTA_EVENT_DOWNLOAD_START,

	OTA_EVENT_SWOOP_START,
	OTA_EVENT_SWOOP_STOP,

	//each transaction download events
	OTA_EVENT_DOWNLOAD_TXN_BEGIN,
	OTA_EVENT_DOWNLOAD_TXN_SUCCESS,
	OTA_EVENT_DOWNLOAD_TXN_FAILED,
	OTA_EVENT_DOWNLOAD_TXN_PAUSED,
	OTA_EVENT_DOWNLOAD_TXN_CANCELLED,
	OTA_EVENT_DOWNLOAD_TXN_PROGRESS_BYTES,
	OTA_EVENT_DOWNLOAD_BLACKOUT_LIFTED,

	//each transaction install events
	OTA_EVENT_INSTALLATION_TXN_BEGIN,
	OTA_EVENT_INSTALLATION_TXN_SUCCESS,
	OTA_EVENT_INSTALLATION_TXN_FAILED,
	OTA_EVENT_INSTALLATION_TXN_CANCELLED,
	OTA_EVENT_INSTALLATION_TXN_PROGRESS,

	//overall install events
	OTA_EVENT_INSTALLATION_READY,
	OTA_EVENT_INSTALLATION_START,
	OTA_EVENT_INSTALLATION_COMPLETE,
	OTA_EVENT_INSTALLATION_FAILED,

	//error events
	OTA_EVENT_OTASL_ERROR,
	OTA_EVENT_ERROR_RESULT,
	OTA_EVENT_ERROR_CONNECTION,
	OTA_EVENT_CONNECTION_TIMEDOUT,
	OTA_EVENT_INTERNET_CONNECTION_LOST,
	OTA_EVENT_INTERNET_CONNECTION_RETRY,

	//general swupdate events
	OTA_EVENT_UPGRADE_STATUS,
	OTA_EVENT_UPGRADE_SUMMARY,
	OTA_EVENT_DEVICE_ACTIVATION,
	OTA_EVENT_DATA_READY,

	// eula related
	OTA_EVENT_EULA_URL,
	OTA_EVENT_EULA_AVAILABLE,
	OTA_EVENT_EULA_NOT_AVAILABLE,

	//rebooting
	OTA_EVENT_REBOOTING,

	//network event
	OTA_EVENT_NETWORK_UPDATE,

	//IT Policy change
	OTA_EVENT_IT_POLICY_CHANGED,

	//Device Info
	OTA_EVENT_DEVICE_INFO,

	// client cancelled
	OTA_EVENT_CLIENT_CANCELLED,

	OTA_EVENT_MAX,

	API_EVENT_UNKNOWN,
	API_EVENT_CONTEXT_NOT_SET,
	API_EVENT_CANNOT_PROCESS_PPS,
	API_STATE_RETURNED
};



#endif /* OTASL_STATE_EXT_H_ */
