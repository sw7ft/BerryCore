/*
 * (C) 2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * wdmcapi_ext.h
 *
 * This header defines all the function declarations that comprise the public interface of the
 * SLS library.
 *  Created on: July 18, 2012
 *      Author: haili/msobhani
 */

#ifndef WDMCAPI_EXT_H_
#define WDMCAPI_EXT_H_
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__)
#   define SWUPDATE_PUBLIC  __attribute__ ((visibility ("default")))
#else
#   define SWUPDATE_PUBLIC
#endif

#include "wdmc_state_ext.h"
#include "wdmctypes_ext.h"

enum requestType {
	REQUEST_CHECK_FOR_UPDATE,
	REQUEST_DOWNLOAD_UPDATE,
	REQUEST_EULA_DOCUMENT,
	REQUEST_EULA_CONTENT,
	REQUEST_DOWNLOAD_PAUSE,
	REQUEST_DOWNLOAD_CANCEL,
	REQUEST_REBOOT,
	REQUEST_EULA_ACCEPTANCE,
	REQUEST_CHECK_FOR_DC,
	REQUEST_ACTIVATE_DEVICE,
	REQUEST_DEFER_UPDATE,
	REQUEST_CHECK_STORAGE,
	REQUEST_UPDATE_OPTIONS
};

enum requestSubType{
	SW_UPDATE_TYPE_MANUAL = 0x1000,
	SW_UPDATE_TYPE_AUTO = 0x1001,
	SW_UPDATE_TYPE_CURRENT = 0x1002,
	SW_UPDATE_TYPE_CR_APP = 0x2000,
	SW_UPDATE_TYPE_ACT = 0x3000,
	SW_UPDATE_TYPE_BRAND = 0x4000,
	SW_UPDATE_TYPE_EDID = 0x5000,
	SW_UPDATE_TYPE_CD = 0x6000,
	SW_UPDATE_TYPE_BARS = 0x7000,
	SW_UPDATE_TYPE_DI = 0x8000,
	SW_UPDATE_TYPE_CONFIG_BAR = 0x9000,
	SW_UPDATE_TYPE_DEVICE_CONFIGURATION_OS_BARS = 0xA000,
	SW_UPDATE_TYPE_EXFAT_BAR = 0xB000
};

enum grantType{
	DWNLD_GRANT_NONE = 0,
	DWNLD_GRANT_WAN = 1,
	DWNLD_GRANT_WAN_ROAM = 2,
	DWNLD_GRANT_WAN_ROAMINT = 3    // International Roaming
};

enum statusRequestOperation{
    CURRENT_VALUE = 0x10,          // just return the current value (sync)
    REGISTER_FOR_UPDATES,          // send updates when the status changes (sync for current value, and async afterwards)
    DEREGISTER                     // don't send updates any longer for the status (no response)
};

enum requestOperationStatus{
	PROCESSING = 0x20,             // just return the current value (sync)
	UNABLE_TO_PROCESS              // send updates when the status changes (sync for current value, and async afterwards)
};

enum requestOperationSubStatus{
	PPS_NOT_AVAILABLE = 0x30
};

enum responseStatus{
	REQUEST_RESULT = 0x40,         // indicates the request completed successfully
	REQUEST_FAILED,                // processing the request ended in a failure condition
	STATUS_UPDATE                  // indicates a status previously registered for has updated data
};

enum mandatoryType{
	MANDATORY_UNKNOWN = -1,
	MANDATORY_NO = 0,
	MANDATORY_YES = 1,
	MANDATORY_SERVER = 2
};

typedef struct {
	 int status;
	 int operation;
	 int reserved_for_future_use1;
	 int reserved_for_future_use2;
} wdmcStatusReq_t;

typedef struct {
	int requestType;
	int requestTypeVer;
	int requestSubType;
	int reserved_for_future_use2;
} wdmcCommon_t;

typedef struct {
	bool is2ndCFU;
	bool limitCFU;
} data_cfu_t;

typedef struct {
	int mandatory;
	int grant;
} data_dwnld_t;

typedef struct {
	const char * locale;
} data_eula_content_t;

typedef struct {
	int num_parts;
	long long unsigned int *timestamp_array;
	const char * eula_ver;
} data_eula_acceptance_t;

typedef struct {
	bool autoUpdate;
} data_options_t;

typedef union {
	data_cfu_t data_cfu;
	data_dwnld_t data_dwnld;
	data_req_detail_cr_t data_cr;
	data_eula_content_t data_eula_content;
	data_eula_acceptance_t data_eula_acceptance;
	data_options_t data_options;
} request_data_t;

typedef struct {
	const char * versionOsCurrent;
	const char * versionSoftwareReleaseCurrent;
	const char * versionRadioCurrent;
	int64_t mandatoryRebootTime;
} wdmcstatus_device_info_t;

typedef struct {
	int stateBack;
	int stateCurrent;
	int statePrevious;
} wdmcstatus_state_t;

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
} wdmcstatus_network_transport_t;

typedef struct {
	bool                              connected;
	bool                              roaming;
	bool                              route_available;
	bool                              tethered;
	bool                              wifi_allowed;
	const char *                      carrier_name;
	wdmcstatus_network_transport_t    transport;
} wdmcstatus_network_t;

typedef struct {
	bool capLimitReached;
	bool downloadCancelled;
	bool hasOSInBundle;
	bool hasRadioInBundle;
	bool needReboot;
	bool retrying;
	const char * description;
	const char * downloadResumeTime;
	const char * eulaResult;
	const char * friendlyMessage;
	const char * version_tgt;
	const char * version_tgt_os;
	const char * version_tgt_radio;
	const char * version_tgt_software_release;
	int cancelReason;
	int downloadGrant;
	int errorCode;
	int gracePeriod;
	int mandatory;
	int pauseReason;
	int state;
	int swuAllowed;
	int64_t bytes;
	int64_t currentGlobalProgress;
	int64_t getOSSize;
	int64_t getRadioSize;
	int64_t getTotalSize;
	int64_t progress;
	int64_t size;
	int64_t sizeCurrentBar;
	int64_t spaceNeeded;
	int64_t totalGlobalProgress;
} wdmcstatus_swStatus_t;

typedef struct {
	int64_t nextCfuTimeUser;
} wdmcstatus_polling_sw_t;

typedef struct {
	wdmcstatus_polling_sw_t sw;
} wdmcstatus_polling_t;

typedef struct {
	bool autoUpdate;
} wdmcstatus_options_t;

typedef struct {
	wdmcstatus_device_info_t          device_info;
	wdmcstatus_state_t                state;
	wdmcstatus_swStatus_t             swStatus;
	wdmcstatus_network_t              network;
	wdmcstatus_polling_t              polling;
	wdmcstatus_options_t              options;
} otastatus_t;

typedef union {
	swu_detail_t swu_detail;
	otastatus_t status_detail;
} response_data_t;

typedef struct {
	wdmcCommon_t request;

	request_data_t data;
} wdmcRequestData_t;

typedef struct {
	 int responseType;
	 int status;
	 char * statusString;
	 int reserved_for_future_use1;
	 int reserved_for_future_use2;
	 response_data_t data_detail;
} wdmcResponse_t;

typedef struct {
	 int status;
	 int subStatus;
} wdmcRequestDisposition_t;

typedef void(*CallbackFunc)(wdmcResponse_t* response);

typedef struct {
	int id;
	CallbackFunc cb;
} wdmcContext_t;

wdmcContext_t* wdmcContextCreate(CallbackFunc cb);
void wdmcContextDispose(wdmcContext_t *context);

wdmcResponse_t wdmcStatusQuery(wdmcStatusReq_t status, wdmcContext_t *context);

wdmcRequestData_t* vendRequestData(int requestType);

wdmcRequestDisposition_t wdmcRequest(void *requestData);

#ifdef __cplusplus
}
#endif
#endif /* WDMCAPI_EXT_H_ */
