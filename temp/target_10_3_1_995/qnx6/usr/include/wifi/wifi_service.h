/*
 * Research In Motion Limited. Copyright (C) 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file wifi_service.h
 *
 * @brief The BlackBerry Wi-Fi service library
 *
 * The Wi-Fi service APIs provide functions to determine Wi-Fi status and
 * receive events for Wi-Fi activities.
 *
 * To use the Wi-Fi service API functions, the application must have
 * the @c access_wifi_public capability. To grant an application
 * the @c access_wifi_public capability, the bar-descriptor.xml file
 * in the application's project must contain the line
 * "<permission>access_wifi_public</permission>".
 *
 * The APIs support hotspot aggregator applications that can configure
 * Wi-Fi profiles and receive aggregator specific event notifications to allow
 * connection at Wi-Fi hotspots on the user's behalf.
 *
 */
#ifndef _WIFI_SERVICE_H_
#define _WIFI_SERVICE_H_

#include <stdbool.h>
#include <stdint.h>

__BEGIN_DECLS

/**
 * Wi-Fi service API identifier.
 */
#ifndef WIFI_API
#define WIFI_API
#endif

/**
 * A return code that indicates that a function did not complete successfully.
 * When the @c errno value is set, it indicates the reason for the failure.
 */
#define WIFI_FAILURE (-1)

/**
 * Maximum length of the buffer where Wi-Fi Service Set Identifier (SSID) name will
 * be copied. The SSID should be NULL terminated.
 */
#define WIFI_MAX_SSID_BUFFER_LEN        (32+1)

/**
 * The length of a Wi-Fi Basic Service Set Identifier (BSSID) address.
 * The BSSID is the MAC address of the access point (AP).
 */
#define WIFI_BSSID_ADDR_LEN             (6)

/**
 * Maximum length of the Wi-Fi aggregator name
 */
#define WIFI_MAX_AGGREGATOR_NAME_LEN    (32+1)

/**
 * Maximum length of the Wired Equivalent Privacy (WEP) security key
 */
#define WIFI_MAX_WEP_KEY_LEN            (16)

/**
 * @brief Contains Wi-Fi service context information
 *
 * An opaque structure used for Wi-Fi service events.
 */
typedef struct _wifi_service_t wifi_service_t;

/**
 * @brief Contains Wi-Fi event information
 *
 * An opaque structure of a Wi-Fi service event which contains event type
 * and any applicable event data that can be queried using the appropriate
 * functions.
 */
typedef struct _wifi_service_event_t wifi_service_event_t;

/**
 * @brief Contains Wi-Fi scan result list information
 *
 * An opaque structure of the Wi-Fi scan results.
 */
typedef struct _wifi_scan_results_t wifi_scan_results_t;

/**
 * @brief Contains Wi-Fi user profile list information
 *
 * An opaque structure of a Wi-Fi user profile list
 * that can be used to query details of the user profiles.
 */
typedef struct _wifi_user_profile_list_t wifi_user_profile_list_t;

/**
 * @brief Contains Wi-Fi aggregator context information
 *
 * An opaque structure of a Wi-Fi aggregator
 * that must be used for aggregator function calls.
 */
typedef struct _wifi_aggregator_t wifi_aggregator_t;

/**
 * @brief Wi-Fi return codes
 *
 * This enumeration defines the return codes for Wi-Fi APIs.
 */
typedef enum {
    /**
     * No error, operation is successful.
     */
    WIFI_SUCCESS                         = 0x00,

    /**
     * Error due to invalid input.
     */
    WIFI_ERROR_INVALID_PARAMETERS           = 0x01,

    /**
     * Error due to insufficient memory.
     */
    WIFI_ERROR_NOT_ENOUGH_MEMORY            = 0x02,

    /**
     * Error - aggregator profile already exists.
     */
    WIFI_ERROR_AGGREGATOR_DUPLICATE         = 0x03,

    /**
     * Error - aggregator profile is in use.
     */
    WIFI_ERROR_AGGREGATOR_PROFILE_BUSY      = 0x04,

    /**
     * Error - aggregator profile is not configured.
     */
    WIFI_ERROR_AGGREGATOR_PROFILE_NOT_READY = 0x05,

    /**
     * Error - request is refused at this time.
     */
    WIFI_ERROR_REQUEST_REFUSED              = 0x06,

    /**
     * Error - the requested command and parameters are not supported.
     */
    WIFI_ERROR_REQUEST_UNSUPPORTED          = 0x07,

    /**
     * Error - the requested information is not available.
     */
    WIFI_ERROR_INFO_NOT_AVAILABLE           = 0x08,

    /**
     * General error.
     */
    WIFI_ERROR                              = 0xFF
} wifi_result_t;

/**
 * @brief Event types for Wi-Fi service events
 *
 * This enum defines the event codes for Wi-Fi service events that are
 * generated if @c wifi_service_initialize() was called.
 */
typedef enum {
    /**
     * The Wi-Fi station connection state has changed.  It can be queried using
     * the @c wifi_station_connection_get_state() function.
     */
    WIFI_EVENT_STATION_CONNECTION_STATE          = 0,

    /**
     * New scan results are available.  They can be queried using
     * the @c wifi_get_scan_results() function.
     */
    WIFI_EVENT_SCAN_RESULTS                     = 1,

    /**
     * A change in the aggregator profile's enable status has occurred.
     * The event reason and the new enable state can be queried using the
     * @c wifi_service_event_get_aggregator_profile_enable_state() function.
     */
    WIFI_EVENT_AGGREGATOR_PROFILE_ENABLE_CHANGE = 2,

    /**
     * The aggregator login wait period has timed out.  This occurs if the
     * @c wifi_aggregator_login_complete() function is not called to confirm
     * hotspot login result after the Wi-Fi connection is established.
     */
    WIFI_EVENT_AGGREGATOR_LOGIN_TIMEOUT         = 3,

    /**
     * The aggregator has been deregistered.
     */
    WIFI_EVENT_AGGREGATOR_DEREGISTERED          = 4,

    /**
     * The event can be ignored by the application. This event type may be
     * returned if the file descriptor changes but the event is applicable
     * only to another registered application.
     */
    WIFI_EVENT_IGNORE                           = 0xFE,

    /**
     * The event type is unknown.
     */
    WIFI_EVENT_UNKNOWN                          = 0xFF
} wifi_event_t;

/**
 * @brief Wi-Fi status
 *
 * This enumeration defines the values of Wi-Fi status.
 */
typedef enum {
    /**
     * The WLAN radio power is off. Calling @c wifi_set_sta_power(true) will
     * start the device in client STA mode.
     */
    WIFI_STATUS_RADIO_OFF = 0,

    /**
     * The device is in client STA mode and the WLAN radio is on.
     * Calling @c wifi_set_sta_power(false) will turn off WLAN radio power.
     */
    WIFI_STATUS_RADIO_ON = 1,

    /**
     * The device is not in client STA mode and cannot be controlled using this
     * API.
     */
    WIFI_STATUS_BUSY = 2,
} wifi_status_t;

/**
 * @brief Station role connection states.
 *
 * This enum defines the Wi-Fi connection states for the station.
 */
typedef enum {
    /**
     * The Wi-Fi radio is turned off.
     */
    WIFI_STATION_RADIO_OFF          = 0,

    /**
     * The Wi-Fi radio is on and station is disconnected.
     */
    WIFI_STATION_DISCONNECTED       = 1,

    /**
     * The station has started association to an Access Point (AP).
     */
    WIFI_STATION_ASSOCIATING        = 2,

    /**
     * The station has started authentication to an AP.
     */
    WIFI_STATION_AUTHENTICATING     = 3,

    /**
     * The station is authenticated and is acquiring an IP address.
     */
    WIFI_STATION_ACQUIRING_IP       = 4,

    /**
     * The station is connected to an AP with an IP address.
     */
    WIFI_STATION_CONNECTED          = 5,

    /**
     * The station is disconnecting from the AP.
     */
    WIFI_STATION_DISCONNECTING      = 6
} wifi_station_connection_state_t;

/**
 * @brief Station disconnect reasons.
 *
 * This enum defines the reason codes that explain why a station is in disconnected
 * state.
 */
typedef enum {
    /**
     * Internal reasons.
     */
    WIFI_STATION_DISCONNECT_REASON_INTERNAL     = 0,

    /**
     * User requested disconnect.
     */
    WIFI_STATION_DISCONNECT_REASON_USER_ACTION  = 1,

    /**
     * Authentication failures on previous connection attempt.
     */
    WIFI_STATION_DISCONNECT_REASON_AUTH_FAILURE = 2,

    /**
     * Deauthentication of the last connection.
     */
    WIFI_STATION_DISCONNECT_REASON_DEAUTH       = 3,

    /**
     * The Aggregator application login timed out.
     */
    WIFI_STATION_DISCONNECT_REASON_AGGREGATOR_LOGIN_TIMEOUT = 4,

    /**
     * The disconnect reason is unknown.
     */
    WIFI_STATION_DISCONNECT_REASON_UNKNOWN      = 5,
} wifi_station_disconnect_reason_t;

/**
 * @brief Wi-Fi scan report types
 *
 * This enum defines the type of report for the scan results available.
 * Depending on the requester of the scan, this value may differ and
 * an application may not be interested in certain types of scan report
 * updates.
 */
typedef enum {
    /**
     * The scan requester type could not be identified.
     */
    WIFI_SCAN_REPORT_UNKOWN                     = 0,

    /**
     * The scan requester was the internal connection manager
     * requesting scans for connection and network selection.
     */
    WIFI_SCAN_REPORT_CONNECTION                 = 1
} wifi_scan_report_t;

/**
 * @brief Wi-Fi network scan result flags
 *
 * This enum defines the flags bitmask of Wi-Fi network capabilities
 * reported in scan results.  Multiple capabilities may be advertised in
 * a scan result entry.
 */
typedef enum {
    /**
     * The network supports Wi-Fi Protected Access (WPA) Personal security.
     */
    WIFI_NETWORK_FLAGS_WPA_PERSONAL             = 0x00000001,

    /**
     * The network supports WPA2 Personal security.
     */
    WIFI_NETWORK_FLAGS_WPA2_PERSONAL            = 0x00000002,

    /**
     * The network supports WPA Enterprise security.
     */
    WIFI_NETWORK_FLAGS_WPA_ENTERPRISE           = 0x00000004,

    /**
     * The network supports WPA2 Enterprise security.
     */
    WIFI_NETWORK_FLAGS_WPA2_ENTERPRISE          = 0x00000008,

    /**
     * The network is an Extended Service Set (ESS).
     */
    WIFI_NETWORK_FLAGS_ESS                      = 0x00000010,

    /**
     * The network supports Peer-to-peer (P2P).
     */
    WIFI_NETWORK_FLAGS_P2P                      = 0x00000020,

    /**
     * The network supports Hotspot 2.0.
     */
    WIFI_NETWORK_FLAGS_HS20                     = 0x00000040,

    /**
     * The network supports Wi-Fi Protected Setup (WPS)
     */
    WIFI_NETWORK_FLAGS_WPS                      = 0x00000080
} wifi_scan_network_flags_t;

/**
 * @brief Wi-Fi key management types
 *
 * This enum defines security key management types reported in scan
 * result entries.
 */
typedef enum {
    /**
     * Open security.
     */
    WIFI_KEY_MANAGEMENT_NONE                          = 0,

    /**
     * Wired Equivalent Privacy (WEP) security.
     */
    WIFI_KEY_MANAGEMENT_WEP                           = 1,

    /**
     * Wi-Fi Protected Access (WPA) security.
     */
    WIFI_KEY_MANAGEMENT_WPA                           = 2
} wifi_key_management_t;

/**
 * @brief Wi-Fi security types
 *
 * This enum defines security types supported for configuring profiles.
 */
typedef enum {
    /**
     * No security, open network.
     */
    WIFI_SECURITY_TYPE_OPEN                     = 0,

    /**
     * Wired Equivalent Privacy (WEP) security. WEP key must be configured.
     */
    WIFI_SECURITY_TYPE_WEP                      = 1,

    /**
     * Pre-shared key (PSK) security.  Passphrase must also be configured.
     */
    WIFI_SECURITY_TYPE_PSK                      = 2,

    /**
     * Protected Extensible Authentication Protocol (PEAP) security.
     * Username and password must be configured.
     */
    WIFI_SECURITY_TYPE_PEAP                     = 3,

    /**
     * Extensible Authentication Protocol Transport Layer Security (EAP-TLS).
     * Security, username and password must be configured.
     */
    WIFI_SECUFITY_TYPE_EAP_TLS                  = 4,

    /**
     * EAP Tunnelled Transport Layer Security (EAP-TTLS) security.
     * Username and password must be configured.
     */
    WIFI_SECURITY_TYPE_EAP_TTLS                 = 5,

    /**
     * EAP - Flexible Authentication via Secure Tunnelling (EAP-FAST) security.
     */
    WIFI_SECURITY_TYPE_EAP_FAST                 = 6,

    /**
     * EAP for GSM Subscriber Identity Module (EAP-SIM) security.
     */
    WIFI_SECURITY_TYPE_EAP_SIM                  = 7,

    /**
     * EAP for UMTS Authentication and Key Agreement (EAP-AKA) security.
     */
    WIFI_SECURITY_TYPE_EAP_AKA                  = 8,

    /**
     * EAP-SIM or EAP-AKA security.
     */
    WIFI_SECURITY_TYPE_EAP_SIMAKA               = 9
} wifi_security_type_t;

/**
 * @brief Wi-Fi security phase 2 authentication methods
 *
 * This enum defines types for phase 2 or inner authentication methods.
 */
typedef enum {
    /**
     * Auto select Microsoft Challenge Handshake Authentication Protocol 
	 * version 2 (MS-CHAPv2) or Generic Token Card (GTC).
     */
    WIFI_SECURITY_PHASE2_AUTO                   = 0,

    /**
     * Use Extensible Authentication Protocol (EAP)-MS-CHAPv2 for inner authentication.
     */
    WIFI_SECURITY_PHASE2_EAP_MSCHAPV2           = 1,

    /**
     * Use EAP-GTC for inner authentication.
     */
    WIFI_SECURITY_PHASE2_EAP_GTC                = 2,

    /**
     * Use Password Authentication Protocol (PAP) for inner authentication.
     */
    WIFI_SECURITY_PHASE2_PAP                    = 3,

    /**
     * Use MS-CHAPv2 for inner authentication.
     */
    WIFI_SECURITY_PHASE2_MSCHAPV2               = 4
} wifi_security_phase2_auth_t;

/**
 * @brief Wi-Fi profile band types
 *
 * This enum defines supported band selection types for profiles.
 */
typedef enum {
    /**
     * Connect on either 2.4 GHz or 5 GHz channels.
     */
    WIFI_PROFILE_DUAL_BAND                  = 0,

    /**
     * Connect only on 2.4 GHz channels.
     */
    WIFI_PROFILE_2_4_GHZ_BAND_ONLY          = 1,

    /**
     * Connect only on 5 GHz channels.
     */
    WIFI_PROFILE_5_GHZ_BAND_ONLY            = 2
} wifi_profile_band_select_t;

/**
 * @brief Event reason codes for aggregator events
 *
 * This enum defines the event codes for aggregator specific Wi-Fi service
 * events.
 */
typedef enum {
    /**
     * The event was generated for unspecified internal reasons.
     */
    WIFI_AGGREGATOR_EVENT_REASON_INTERNAL               = 0,

    /**
     * The event was generated due to user action.
     */
    WIFI_AGGREGATOR_EVENT_REASON_USER_ACTION            = 1,

    /**
     * The aggregator has been blacklisted.
     */
    WIFI_AGGREGATOR_EVENT_REASON_BLACKLISTED            = 2
} wifi_aggregator_event_reason_t;

/**
 * @brief Aggregator hotspot login status types
 *
 * This enum defines the status types for an aggregator application login.
 */
typedef enum {
    /**
     * The login was not successful.
     */
    WIFI_AGGREGATOR_LOGIN_FAILURE               = 0,

    /**
     * The login was successful.
     */
    WIFI_AGGREGATOR_LOGIN_SUCCESS               = 1,

    /**
     * The application requests more time for login
     */
    WIFI_AGGREGATOR_LOGIN_NEED_MORE_TIME        = 2
} wifi_aggregator_login_status_t;


/**
 * @brief Initialize the Wi-Fi service system and start receiving Wi-Fi events
 *
 * This function connects the application to the Wi-Fi service system and lets
 * it start receiving events.  It creates and initializes the handle that is
 * used for receiving events.  An application may only call this function once.
 *
 * The application must call @c wifi_service_shutdown() to clean up and
 * release the handle.
 *
 * @param[out] wifi_service The service handle that will be created and
 * initialized by this function.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_initialize(wifi_service_t **wifi_service);

/**
 * @brief Shutdown the Wi-Fi service and stop receiving Wi-Fi events
 *
 * This function releases the application from the Wi-Fi service and stops
 * it from receiving events.  Applications must always call this function
 * as part of their teardown process.
 *
 * @param[in,out] wifi_service The service handle that will be closed and
 * released by this function.

 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_shutdown(wifi_service_t *wifi_service);

/**
 * @brief Retrieve the file descriptor for Wi-Fi service events
 *
 * This function retrieves the file descriptor that the application uses to
 * receive event information from the Wi-Fi service.
 *
 * The ownership of the file descriptor is not passed to the application.
 * The application must not close the file descriptors manually, but should
 * call @c wifi_service_shutdown() to close the file descriptor.
 *
 * The application can use the file descriptor with ionotify(), select(),
 * poll(), or bps_add_fd() to receive event notification triggers, and then
 * call @c wifi_service_read_event() to retrieve the event and
 * @c wifi_service_get_event_type() to get the event type details.
 *
 * @param[in] wifi_service The Wi-Fi service handle.
 *
 * @param[out] fd The Wi-Fi service file descriptor.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_get_fd(wifi_service_t *wifi_service, int *fd);

/**
 * @brief Read a Wi-Fi service event
 *
 * This function reads the Wi-Fi service event and returns a handle to the
 * event to the application.  If this function returns without error, the
 * application must release the event using @c wifi_service_free_event()
 * when it is done processing it.
 *
 * @param[in] wifi_service The Wi-Fi service handle.
 *
 * @param[out] event The Wi-Fi service event.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_read_event(wifi_service_t *wifi_service, wifi_service_event_t **event);

/**
 * @brief Free the Wi-Fi service event
 *
 * This function must be called to release the event resources after the
 * event is processed by the application.
 *
 * @param[in] wifi_service The Wi-Fi service handle.
 *
 * @param[in,out] event The Wi-Fi service event.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_free_event(wifi_service_t *wifi_service, wifi_service_event_t *event);

/**
 * @brief Get the event type for a Wi-Fi service event
 *
 * This function retrieves the event type for the given event.
 *
 * @param[in] event The Wi-Fi service event.
 *
 * @param[out] event_type The Wi-Fi service event type.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_get_event_type(wifi_service_event_t *event, wifi_event_t *event_type);

/**
 * @brief Get the details of a Wi-Fi station connection event
 *
 * This function retrieves the new connection state that triggered the event.
 *
 * @param[out] state The Wi-Fi station connection state.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_event_get_station_connection_state(wifi_service_event_t *event,
                            wifi_station_connection_state_t *state);

/**
 * @brief Get the details of a Wi-Fi aggregator profile change event
 *
 * This function retrieves the aggregator profile enable state and the reason
 * for this event.
 *
 * @param[in] event The Wi-Fi service event.
 *
 * @param[out] enable The Wi-Fi aggregator profile enable value.
 *
 * @param[out] reason The Wi-Fi aggregator profile enable change event reason.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_service_event_get_aggregator_profile_enable_state(wifi_service_event_t *event,
                            int *enable, wifi_aggregator_event_reason_t *reason);

/**
 * @brief Get the current Wi-Fi station connection state
 *
 * This function queries the current Wi-Fi connection state.
 *
 * @param[out] state The Wi-Fi station connection state.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_station_connection_get_state(wifi_station_connection_state_t *state);

/**
 * @brief Get the Wi-Fi station connected Service Set Identifier (SSID)
 *
 * This function queries the SSID if applicable to the current state.
 *
 * @param[out] ssid A buffer of length @c WIFI_MAX_SSID_BUFFER_LEN where the
 *                  SSID will be copied.  The SSID will be NULL terminated.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_station_connection_get_ssid(char *ssid);

/**
 * @brief Get the Wi-Fi station connected Basic Service Set Identifier (BSSID)
 *
 * This function queries the BSSID if applicable to the current state.
 *
 * @param[out] bssid A buffer of length @c WIFI_BSSID_ADDR_LEN where the BSSID
 *                   will be copied.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_station_connection_get_bssid(uint8_t *bssid);

/**
 * @brief Get the Wi-Fi station connected channel
 *
 * This function queries the channel if applicable to the current state.
 *
 * @param[out] channel The channel number.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_station_connection_get_channel(int *channel);

/**
 * @brief Get the Wi-Fi station disconnect reason
 *
 * This function queries the last disconnect reason.
 *
 * @param[out] reason The reason code for Wi-Fi disconnection.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_station_connection_get_disconnect_reason(wifi_station_disconnect_reason_t *reason);

/**
 * @brief Get the Wi-Fi scan results
 *
 * This function queries the latest available scan results list as well as the
 * size of the list.  It should be called after a scan result event
 * notification is received to retrieve the scan result list.  The
 * @c wifi_free_scan_results() function must be called to free the scan
 * results when scan results processing is complete.
 *
 * The scan result entries can be decoded by looping from 1 to
 * @c num_scan_entries and calling @c wifi_get_scan_result_*()
 * functions to extract the details of each scan result entry.
 *
 * @param[out] scan_results Pointer that will be set to the scan result list.
 *
 * @param[out] report_type  The report type for these results.
 *
 * @param[out] num_scan_entries The number of list entries.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_scan_results(wifi_scan_results_t **scan_results,
                                            wifi_scan_report_t *report_type,
                                            int *num_scan_entries);

/**
 * @brief Free the Wi-Fi scan results
 *
 * This function must be called to free the scan results that are returned
 * by @c wifi_get_scan_results() when processing of the scan results is
 * complete.
 *
 * @param[in,out] scan_results Pointer to the scan results that will be freed.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_free_scan_results(wifi_scan_results_t *scan_results);

/**
 * @brief Get the Service Set Identifier (SSID) for a Wi-Fi scan result entry
 *
 * This function queries the SSID for the scan result entry provided.
 *
 * @param[in] scan_results The scan result list.
 *
 * @param[in] entry_number Scan result entry to query. The index range is between
 *                         @c 1 and @c num_scan_entries, which can be queried by
 *                         calling @c wifi_get_scan_results().
 *
 * @param[out] ssid A buffer of length @c WIFI_MAX_SSID_BUFFER_LEN where the
 *                  SSID will be copied.  The SSID will be NULL terminated.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_scan_result_ssid(wifi_scan_results_t *scan_results,
                                            int entry_number, char *ssid);

/**
 * @brief Get the Basic Service Set Identifier (BSSID) for a Wi-Fi scan
 * result entry
 *
 * This function queries the BSSID for the scan result entry provided.
 *
 * @param[in] scan_results The scan result list.
 *
 * @param[in] entry_number Scan result entry to query. The index range is between
 *                         @c 1 and @c num_scan_entries, which can be queried by
 *                         calling @c wifi_get_scan_results().
 *
 * @param[out] bssid A buffer of length @c WIFI_BSSID_ADDR_LEN where the
 *                   BSSID will be copied.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_scan_result_bssid(wifi_scan_results_t *scan_results,
                                            int entry_number, uint8_t *bssid);

/**
 * @brief Get the frequency of a Wi-Fi scan result entry
 *
 * This function queries the frequency of the scan result entry provided.
 *
 * @param[in] scan_results The scan result list.
 *
 * @param[in] entry_number Scan result entry to query. The index range is between
 *                         @c 1 and @c num_scan_entries, which can be queried by
 *                         calling @c wifi_get_scan_results().
 *
 * @param[out] freq The frequency of the scan entry in MHz.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_scan_result_freq(wifi_scan_results_t *scan_results,
                                            int entry_number, int *freq);

/**
 * @brief Get the received signal strength indicator (RSSI) for a Wi-Fi
 * scan result entry
 *
 * This function queries the signal level for the scan result entry provided.
 *
 * @param[in] scan_results The scan result list.
 *
 * @param[in] entry_number Scan result entry to query. The index range is between
 *                         @c 1 and @c num_scan_entries, which can be queried by
 *                         calling @c wifi_get_scan_results().
 *
 * @param[out] signal_level The RSSI in dBm of the entry.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_scan_result_signal_level(wifi_scan_results_t *scan_results,
                                            int entry_number, int *signal_level);

/**
 * @brief Get the security and capabilities flags for a Wi-Fi scan result entry
 *
 * This function queries the security type capabilities and other network
 * capabilities for the scan entry provided.
 *
 * @param[in] scan_results The scan result list.
 *
 * @param[in] entry_number Scan result entry to query. The index range is between
 *                         @c 1 and @c num_scan_entries, which can be queried by
 *                         calling @c wifi_get_scan_results().
 *
 * @param[out] key_management The key management advertised for the network.
 *
 * @param[out] flags Bitmask of the Wi-Fi flags.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_scan_result_flags(wifi_scan_results_t *scan_results,
                        int entry_number, wifi_key_management_t *key_management, uint32_t *flags);

/**
 * @brief Get the current user-saved Wi-Fi profile list
 *
 * This function queries the user profile list.  The
 * @c wifi_free_user_profiles() function must be called to free the user
 * profiles list when processing is complete.
 *
 * The user profiles can be decoded by looping from 1 to
 * @c num_user_profiles and calling @c wifi_get_user_profile_*()
 * functions to extract the details of each user profile entry.
 *
 * @param[out] profiles  Pointer that will be set to the user profile list.
 *
 * @param[out] num_user_profiles The number of user profiles in the list.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_user_profiles(wifi_user_profile_list_t **profiles,
                                             int *num_user_profiles);

/**
 * @brief Free the Wi-Fi user profile list
 *
 * This function must be called to free the user profiles list returned
 * by @c wifi_get_user_profiles() when processing of the uesr profiles is
 * complete.
 *
 * @param[in,out] profiles  Pointer to the user profiles list that will be freed and
 *                          set to NULL on return.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_free_user_profiles(wifi_user_profile_list_t **profiles);

/**
 * @brief Get the Service Set Identifier (SSID) for a user profile entry
 *
 * This function queries the SSID for a user profile.
 *
 * @param[in] profiles The user profiles list.
 *
 * @param[in] entry_number The user profile entry to query. The index range is between
 *                         @c 1 and @c num_user_profiles, which can be queried by
 *                         calling @c wifi_get_user_profiles().
 *
 * @param[out] ssid A buffer of length @c WIFI_MAX_SSID_BUFFER_LEN where the
 *                  SSID will be copied.  The SSID will be NULL terminated.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_user_profile_ssid(wifi_user_profile_list_t *profiles,
                                int entry_number, char *ssid);

/**
 * @brief Get the security type for a user profile entry
 *
 * This function queries the security type for a user profile.
 *
 * @param[in] profiles The user profiles list.
 *
 * @param[in] entry_number The user profile entry to query. The index range is between
 *                         @c 1 and @c num_user_profiles, which can be queried by
 *                         calling @c wifi_get_user_profiles().
 *
 * @param[out] security The security type.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_user_profile_security(wifi_user_profile_list_t *profiles,
                                int entry_number, wifi_security_type_t *security);

/**
 * @brief Get the enable status of a user profile entry
 *
 * This function queries the enable status of a user profile.
 *
 * @param[in] profiles The user profiles list.
 *
 * @param[in] entry_number The user profile entry to query. The index range is between
 *                         @c 1 and @c num_user_profiles, which can be queried by
 *                         calling @c wifi_get_user_profiles().
 *
 * @param[out] enable The profile internal enable status.
 *
 * @param[out] user_enable The user selected enable status of the profile.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_get_user_profile_enable(wifi_user_profile_list_t *profiles,
                                int entry_number, bool *enable, bool *user_enable);

/**
 * @brief Retrieve the current Wi-Fi status
 *
 * The @c wifi_get_status() function returns the current Wi-Fi status.
 *
 * @param[out] status This will be set to the current status.
 *
 * @return @c WIFI_SUCCESS upon success, @c WIFI_FAILURE with @c errno set
 * otherwise.
 */
WIFI_API int wifi_get_status(wifi_status_t *status);

/**
 * @brief Turn the Wi-Fi radio power on or off while the device is in
 * client STA operational mode.
 *
 * The @c wifi_set_sta_power() function attempts to set the Wi-Fi radio power.
 * When the device is in an operational mode other than client STA this function
 * fails, @c errno is set to EBUSY, and the Wi-Fi power remains unchanged.
 * Additional restrictions apply to power off requests if, for example, Wi-Fi is
 * the default route for one of the perimeters, or if an application is
 * explicitly bound to the Wi-Fi interface. In such cases the power off request
 * fails and errno is set to EBUSY.
 *
 * When the function returns successfully in response to a power-on request
 * the device will operate in the client STA mode.
 *
 * @param[in] on_off If @c true the power will be turned on, if @c false the power
 * will be turned off.
 *
 * @return @c WIFI_SUCCESS upon success, @c WIFI_FAILURE with @c errno set
 * otherwise.
 */
WIFI_API int wifi_set_sta_power(bool on_off);

/**
 * @brief Register the application as a hotspot aggregator
 *
 * This function registers the calling application with the Wi-Fi service
 * library as an aggregator application.  Certain events and APIs are
 * only applicable to aggregator applications that configure profiles for
 * the purpose of connecting on behalf of the user.
 *
 * Applications must be registered prior to calling any other aggregator
 * APIs.
 *
 * If the BlackBerry device is not connected as a station to an access point
 * (AP), scans are triggered internally by the Wi-Fi connection manager at
 * regular intervals. When scan results are available, they will be passed
 * to applications that receive events from the Wi-Fi service library.
 *
 * The @c refresh parameter indicates if this is the first time the application
 * has tried to register.  If so, set @c refresh to @c false.  A new empty profile
 * is created and saved.  This profile is displayed to the user as disabled
 * and uneditable.  When the application determines based on scan results
 * received that there is a network it wishes to connect to, it can use one
 * of the functions below to populate the profile:
 *     - @c wifi_aggregator_set_profile_ssid()
 *     - @c wifi_aggregator_set_profile_ap_handover()
 *     - @c wifi_aggregator_set_profile_band_select()
 *     - @c wifi_aggregator_set_profile_user_deletable()
 *     - @c wifi_aggregator_set_profile_security_type()
 *     - @c wifi_aggregator_set_profile_security_wep_key()
 *     - @c wifi_aggregator_set_profile_security_wep_key_str()
 *     - @c wifi_aggregator_set_profile_security_psk_passphrase()
 *     - @c wifi_aggregator_set_profile_security_user_name_password()
 *
 * The @c aggregator_name parameter is used as the UI display name for the
 * aggregator profile, indicating to the user that an aggregator application
 * is registered.  If the name is a duplicate of an existing saved profile and
 * @c refresh is @c false, @c #WIFI_ERROR_AGGREGATOR_DUPLICATE is returned.
 * If @c refresh is @c true, a check for a matching @c aggregator_name profile
 * is performed.  If not found, @c #WIFI_ERROR_INVALID_PARAMETERS
 * is returned.  Otherwise, the aggregator recovers its prior profile,
 * which is disabled at registration but can be queried or enabled
 * by the application.
 *
 * An application may register only once and must use the same
 * @c aggregator_name on refresh of its registration.  The Wi-Fi connection
 * manager maintains only a single Wi-Fi profile for this aggregator
 * at any one time, and the aggregator can use the above functions to
 * change the profile if needed.
 *
 * @param[in] wifi_service The Wi-Fi service handle.
 *
 * @param[out] aggregator Pointer that will be set to an aggregator struct.
 *
 * @param[in] aggregator_name The aggregator name to be used also as the
 *                            profile name.
 *
 * @param[in] refresh Flag indicating if this is the first registration attempt.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_register(wifi_service_t *wifi_service,
                                                wifi_aggregator_t **aggregator,
                                                const char *aggregator_name, bool refresh );

/**
 * @brief Configure the Service Set Identifier (SSID) of a Wi-Fi aggregator profile
 *
 * This function configures the SSID.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] ssid A null-terminated Wi-Fi SSID name.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_ssid(wifi_aggregator_t *aggregator, const char *ssid);

/**
 * @brief Configure the access point (AP) handover attribute of a
 * Wi-Fi aggregator profile
 *
 * This function configures the AP handover attribute to enable or disable
 * inter-AP roaming using this profile.
 *
 * The default value is @c false.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] ap_handover_enabled The new attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_ap_handover(wifi_aggregator_t *aggregator, bool ap_handover_enabled);

/**
 * @brief Configure the band-select attribute of a Wi-Fi aggregator profile
 *
 * This function configures the band-select attribute to support dual bands or
 * a single band for connections.
 *
 * The default value is @c WIFI_PROFILE_DUAL_BAND.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] band_select A new attribute value defined in @c #wifi_profile_band_select_t.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_band_select(wifi_aggregator_t *aggregator, wifi_profile_band_select_t band_select);

/**
 * @brief Configure the user-deletable attribute of a Wi-Fi aggregator profile
 *
 * This function configures the user-deletable attribute to indicate
 * if the profile can be deleted and the application deregistered.
 *
 * The default value is @c true.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] user_deletable The new attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_user_deletable(wifi_aggregator_t *aggregator, bool user_deletable);

/**
 * @brief Configure the security type of a Wi-Fi aggregator profile
 *
 * This function configures the security type attribute and removes the pre-configured
 * security credentials for the profile. The security type must be configured using
 * this function before any other security credentials are configured. This attribute
 * is mandatory and must be specified by the application for the profile to be
 * considered complete.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed.
 *
 * If a security type is not supported @c WIFI_ERROR_REQUEST_UNSUPPORTED
 * will be returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] security An attribute value defined in @c wifi_security_type_t.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_security_type(wifi_aggregator_t *aggregator, wifi_security_type_t security);

/**
 * @brief Configure the Wired Equivalent Privacy (WEP) key attribute of the
 * Wi-Fi aggregator profile
 *
 * This function configures the WEP key.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed. If the security type is unmatched, @c #WIFI_ERROR_INVALID_PARAMETERS
 * is returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] wep_key A WEP key of maximum length @c WIFI_MAX_WEP_KEY_LEN. Both the ASCII and
 * the hexadecimal keys are supported.
 *
 * @param[in] wep_key_byte_len The length of the WEP key in bytes. An ASCII WEP key needs to be
 * either 5 or 13 ASCII characters. And a hexadecimal WEP key needs to be either 10 or 26 hexadecimal
 * characters.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_security_wep_key(wifi_aggregator_t *aggregator,
                const uint8_t *wep_key, int wep_key_byte_len);

/**
 * @brief Configure the Wired Equivalent Privacy (WEP) key attribute of the
 * Wi-Fi aggregator profile
 *
 * This function configures the WEP key using a null-terminated string.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed. If the security type is unmatched, @c #WIFI_ERROR_INVALID_PARAMETERS
 * is returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] wep_key A null-terminated WEP key. Both the ASCII and the hexadecimal keys are supported.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_security_wep_key_str(wifi_aggregator_t *aggregator,
									const char *wep_key);

/**
 * @brief Configure the pre-shared key (PSK) passphrase of a Wi-Fi aggregator
 * profile
 *
 * This function configures the PSK passphrase.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed. If the security type is unmatched, @c #WIFI_ERROR_INVALID_PARAMETERS
 * is returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] passphrase A null-terminated Wi-Fi Protected Access (WPA)
 * ASCII passphrase between 8 and 63 characters in length.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_security_psk_passphrase(wifi_aggregator_t *aggregator, const char *passphrase);

/**
 * @brief Configure the username and password of a Wi-Fi aggregator profile
 *
 * This function configures the username and password.
 *
 * If the existing aggregator profile corresponds to the currently connected
 * network, @c #WIFI_ERROR_AGGREGATOR_PROFILE_BUSY is returned and the
 * profile is not changed. If the security type is unmatched, @c #WIFI_ERROR_INVALID_PARAMETERS
 * is returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] username The new attribute value for username.
 *
 * @param[in] password The new attribute value for password.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_set_profile_security_user_name_password(wifi_aggregator_t *aggregator,
                    const char *username, const char *password);

/**
 * @brief Query the Service Set Identifier (SSID) of the Wi-Fi aggregator profile
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] ssid A pointer for the returned attribute value. The maximum length
 * of the SSID is @c WIFI_MAX_SSID_BUFFER_LEN-1.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_ssid(wifi_aggregator_t *aggregator, char *ssid);

/**
 * @brief Query the the access point (AP) handover attribute of the Wi-Fi
 * aggregator profile
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] ap_handover_enabled A pointer for the returned attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_ap_handover(wifi_aggregator_t *aggregator, bool *ap_handover_enabled);

/**
 * @brief Query the band select attribute of the Wi-Fi aggregator profile
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] band_select A pointer for the returned attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_band_select(wifi_aggregator_t *aggregator, wifi_profile_band_select_t *band_select);

/**
 * @brief Query the user deletable attribute of the Wi-Fi aggregator profile
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] user_deletable A pointer for the returned attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_user_deletable(wifi_aggregator_t *aggregator, bool *user_deletable);

/**
 * @brief Query the security type attribute of the Wi-Fi aggregator profile
 *
 * If the attribute has not been configured yet
 * @c #WIFI_ERROR_AGGREGATOR_PROFILE_NOT_READY will be returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] security A pointer for the returned attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_security_type(wifi_aggregator_t *aggregator, wifi_security_type_t *security);

/**
 * @brief Query the enable status attribute of the Wi-Fi aggregator profile
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] enable A pointer for the enable status for the profile.
 *
 * @param[out] user_enable A pointer for the user configured enable status for the profile.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_enable_status(wifi_aggregator_t *aggregator, bool *enable, bool *user_enable);

/**
 * @brief Queries the Wi-Fi aggregator priority attribute
 *
 * This function queries the priority of the aggregator profile.  The priority
 * is a value from 0 to the maximum number of saved Wi-Fi profiles, where a
 * smaller number represents a lower priority.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[out] priority A pointer for the returned attribute value.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_get_profile_priority(wifi_aggregator_t *aggregator, int *priority);

/**
 * @brief Modify the enable status of a Wi-Fi aggregator profile.
 *
 * This function enables or disables the Wi-Fi aggregator profile according to
 * the @c enable flag provided. Enabled profiles may be used for connection
 * by the internal Wi-Fi connection manager.
 *
 * This function may be used to disconnect from the aggregator network.
 * If @c enable is set to @c false and the currently connected network corresponds
 * to the Wi-Fi aggregator profile, the network will be disconnected and the
 * profile disabled.
 *
 * If the profile is not properly configured yet it cannot be enabled and
 * @c #WIFI_ERROR_AGGREGATOR_PROFILE_NOT_READY will be returned.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] enable @c true to enable the profile, @c false to disable it.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_enable_profile(wifi_aggregator_t *aggregator, bool enable);

/**
 * @brief Report that a network is found for connection from the last scan
 * results
 *
 * Call this function when the aggregator has completed network selection
 * against received scan results. If a network was found, first configure the
 * profile by calling the funtions to set profile parameters and then call
 * this function to signal a match is found and that the profile is configured.
 * If no network is found for connection, call this function with @c match set
 * to @c false to allow the Wi-Fi connection manager to continue network
 * selection without waiting. If the application does not call this function
 * it may be deregistered and the profile deleted.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] match  @c true if a match was found, @c false otherwise.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_network_match(wifi_aggregator_t *aggregator, bool match);

/**
 * @brief Report completion of hotspot/network login process
 *
 * Call this function when the hotspot/network login is completed and when the
 * interface is expected to have Internet connectivity.  If this function is
 * not called within 60 seconds after Wi-Fi has connected, the Wi-Fi
 * network will be disconnected and an event sent to the application.
 * If the application needs more time to complete a login, it can send
 * @c WIFI_AGGREGATOR_LOGIN_NEED_MORE_TIME.  The application is allowed
 * a maximum of 5 minutes from the time of the Wi-Fi connected event to
 * login completion.  After the maximum time has expired, further requests for
 * more time will be rejected with return code @c #WIFI_ERROR_REQUEST_REFUSED.
 *
 * @param[in] aggregator The aggregator returned in @c wifi_aggregator_register().
 *
 * @param[in] status The login status.
 *
 * @return A return code from @c #wifi_result_t.
 */
WIFI_API wifi_result_t wifi_aggregator_login_complete(wifi_aggregator_t *aggregator,
                    wifi_aggregator_login_status_t status);

/**
 * @brief Deregister the application as an aggregator application.
 *
 * This function deregisters the specified aggregator application from
 * receiving aggregator events and from calling any other aggregator APIs.
 * The saved profile for the aggregator application will be removed.
 * Applications should call this function on termination to ensure proper
 * cleanup.
 *
 * @param[in] wifi_service The Wi-Fi service handle.
 *
 * @param[in] aggregator The aggregator returned in
 *                           @c wifi_aggregator_register().
 *
 * @return A return code from @c #wifi_result_t
 */
WIFI_API wifi_result_t wifi_aggregator_deregister(wifi_service_t *wifi_service,
                                                  wifi_aggregator_t *aggregator);


__END_DECLS

#endif /* _WIFI_SERVICE_H_ */

