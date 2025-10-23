/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

/**
 * @file btle.h
 *
 * @brief This file contains functions and structures for using the
 *        Bluetooth low energy functionality
 *
 *
 */

#ifndef _BTLE_H_
#define _BTLE_H_

#include <stdint.h>

/**
 * Bluetooth low energy API version.
 * For example, the value @c 0x00010001 translates to 0001.00.01 or v1.0.1.
 */
#define BT_LE_VERSION         0x00010001

/**
 * A value that represents all Bluetooth addresses. This value is useful when
 * you want to receive data from any Bluetooth-enabled devices.
 */
#define BT_LE_BDADDR_ANY  "00:00:00:00:00:00"

/**
 * A value used to run advertisements for an indefinite amount of time.
 */
#define BT_LE_TIME_INFINITY      0xFFFFFFFF

/**
 * The reason why the advertising completed.
 */
typedef enum {

    /**
     * Internal stack terminated advertisements.
     */
    BT_LE_ADVERT_REASON_INTERNAL_TERMINATED        = 0x00,

    /**
     * Advertisement timed interval elapsed.
     */
    BT_LE_ADVERT_REASON_INTERVAL_TIMEOUT           = 0x01,

    /**
     * Advertisements terminated due to an incoming or outgoing connection.
     */
    BT_LE_ADVERT_REASON_CONNECTION_TERMINATED      = 0x02,

    /**
     * Reserved for future use.
     */
    BT_LE_ADVERT_REASON_RESERVED                   = 0x03,

    /**
     * Advertisements terminated due to radio shutdown
     */
    BT_LE_ADVERT_REASON_RADIO_SHUTDOWN             = 0x04,

} bt_le_advert_complete_reason_t;

/**
 * Advertising scan type.
 */
typedef enum {

    /**
     * Passive advertisement scanning - no scan request packets will be sent.
     */
    BT_LE_ADVERT_SCAN_PASSIVE                       = 0x00,

    /**
     * Active advertisement scanning - scan request packets will be sent.
     */
    BT_LE_ADVERT_SCAN_ACTIVE                        = 0x01,

} bt_le_advert_scan_type_t;

/**
 * Advertisement Event Type.
 */
typedef enum {

    /*
     * connectable undirected advertising event
     */
    BT_LE_ADVERT_TYPE_CONNECTABLE_UNDIRECTED = 0,

    /*
     * connectable directed advertising event
     */
    BT_LE_ADVERT_TYPE_CONNECTABLE_DIRECTED,

    /*
     * Discoverable Undirected advertising event
     */
    BT_LE_ADVERT_TYPE_DISCOVERABLE_UNDIRECTED,

    /*
     * non-connectable undirected advertising event
     */
    BT_LE_ADVERT_TYPE_NONCONNECTABLE_UNDIRECTED,

    /*
     * scannable undirected advertising event
     */
    BT_LE_ADVERT_TYPE_SCAN_RESPONSE,

} bt_le_advert_packet_event_t;

/**
 * @brief This definition has been deprecated
 * @deprecated BlackBerry 10.3.0. Use @c bt_le_advertisement_ext_cb instead.
 *
 * @param bdaddr The address of the Bluetooth-enabled device.
 * @param rssi The Received Signal Strength Indication (RSSI) for the
 *             advertisement.
 *             - Range: -127 dBm <= N <= 20 dBm.
               - +127 indicates the RSSI value is not available.
 * @param data The data sent in the advertisement.
 * @param len The length of data sent.
 * @param userData Pointer to the user data defined when adding the listener.
 */
typedef void (*bt_le_advertisement_cb) (const char *bdaddr, int8_t rssi, const char *data, int len, void *userData);

/**
 * The callback prototype to indicate an incoming advertisement event has occurred.
 *
 * @param bdaddr The address of the Bluetooth-enabled device.
 * @param rssi The Received Signal Strength Indication (RSSI) for the
 *             advertisement.
 *             - Range: -127 dBm <= N <= 20 dBm.
 *             - +127 indicates the RSSI value is not available.
 * @param eventType The type of advertising packet received.
 * @param data The data sent in the advertisement.
 * @param len The length of the data sent.
 * @param userData Pointer to the user data defined when adding the listener.
 */
typedef void (*bt_le_advertisement_ext_cb) (const char *bdaddr, int8_t rssi, bt_le_advert_packet_event_t eventType, const char *data, int len, void *userData);

/**
 * The callback prototype to indicate the advertisement interval has changed.
 *
 * @param intervalMin The current minimum advertisement interval. Time = N * 0.625 msec.
 * @param intervalMax The current maximum advertisement interval. Time = N * 0.625 msec.
 */
typedef void (*bt_le_advertisement_change_cb) (uint16_t intervalMin, uint16_t intervalMax);

/**
 * The callback prototype to indicate the advertisement has completed.
 *
 * @param reason The reason why the advertisements completed.
 */
typedef void (*bt_le_advertisement_complete_cb) (bt_le_advert_complete_reason_t reason);

/**
 * The structure that contains the control manager callback.
 */
typedef struct {
    /**
     * @deprecated BlackBerry 10.3.0  Use @advert_ext instead
     */
    bt_le_advertisement_cb advert;

    /**
     * Callback function to indicate a change in advertisement parameters.
     */
    bt_le_advertisement_change_cb changed;

    /**
     * Callback function to indicate advertisements have completed.
     */
    bt_le_advertisement_complete_cb complete;

    /**
     * Callback function for received advertisement data.
     */
    bt_le_advertisement_ext_cb advert_ext;

} bt_le_callbacks_t;

/**
 * Structure for parameters that applications may request for low energy advertisements.
 * Ranges of values are specified for advertisement intervals. Application-requested values must
 * fall within the specified range. If different values are requested by multiple applications,
 * the lowest value that is within the range will be used as the advertising value.
 */
typedef struct {
    /**
     * The minimum initial advertising interval used when no connection exists.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t minAdvertInterval1;

    /**
     * The maximum initial advertisement interval used when either a connection exists or
     * advertising.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t maxAdvertInterval1;

    /**
     * The time (in msec) to perform the initial advertisements. Use @c GATT_TIME_INFINITY
     * to run until the connection is created or disconnected.  If @c time1 is set to @c 0, then the initial interval
     * is disabled and the second interval is used instead for power saving when fast advertising is not required.
     */
    uint32_t time1;

    /**
     * The minimum second advertisement interval, used after @c time1 has expired or when a connection exists.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t minAdvertInterval2;
    /**
     * The maximum second advertisement interval, used after @c time1 has expired or when a connection exists.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t maxAdvertInterval2;
    /**
     * The time (in msec) to perform the second stage of the advertising process.
     * Use @c 0 to disable the second stage or @c GATT_TIME_INFINITY to run until advertisement is stopped.
     */
    uint32_t time2;

} bt_le_advert_parm_t;


__BEGIN_DECLS

/**
 * @brief Set up the desired scan interval when searching for device
 *        advertisements
 *
 * @param interval The scan interval used when no connections exist.
 *         Range (N * 0.625 msec): 0x0004 to 0x4000
 * @param window The scan window used during the scan.
 *         Range (N * 0.625 msec): 0x0004 to 0x4000
 * @param type The scan type used when listening for advertisements.
 *         Default: Passive scan.
 *
 * @return @c EOK on successful registration of scan parameters, @c -1 if an error
 *         occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EINVAL: The parameters provided are out of range.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_set_scan_params(uint16_t interval, uint16_t window, bt_le_advert_scan_type_t type);

/**
 * @brief Add the Bluetooth address of the remote device to the advertisement
 *        filter list, such as <tt>12:03:40:60:11:21</tt>
 * @details Adding the address allows your application to receive device
 *          advertisement data. The advertisement data is in binary form,
 *          which you will need to parse in your application logic.
 *          If an error is returned from the function call, the @c errno is
 *          set with reason of failure.
 *
 * @param bdaddr The address of the specific Bluetooth-enabled device. You can
 *               use the value of @c BT_LE_BDADDR_ANY to receive advertisements
 *               from all Bluetooth-enabled devices.
 * @param userData  (Optional) A pointer to user data.
 *
 * @return @c EOK on successful addition of a device to the filter list,
 *         @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c EBUSY: The requested service is already in use.
 *         - @c EINVAL: The Bluetooth MAC address provided is NULL or invalid.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_add_scan_device(const char *bdaddr, void *userData);

/**
 * @brief Remove the device from the advertisement filter list
 * @details If an error is returned from the function call, the @c errno is
 *          set with reason.
 *
 * @param bdaddr The address of the Bluetooth-enabled device to remove from the
 *               filter list.
 *
 * @return @c EOK on successful removal of a device from the filter list,
 *         @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c ENODEV: Bluetooth stack is unavailable.
 *         - @c EINVAL: The Bluetooth MAC address provided is NULL or invalid.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_remove_scan_device(const char *bdaddr);

/**
 * @brief Start low energy advertisements
 *
 * @param advertParm (Optional) The advertisement parameters. Use
 *                            this argument when you require specific
 *                            advertisement parameters; set to @c NULL otherwise
 *                            to use the following default values.
 *                              - minAdvertInterval1 = 20ms
 *                              - maxAdvertInterval1 = 30ms
 *                              - time1              = 30sec
 *                              - minAdvertInterval2 = 1sec
 *                              - maxAdvertInterval2 = 2.5sec
 *                              - time2              = 60sec
 * @param intervalMin (Optional) Returns the minimum current advertisement interval.
 * @param intervalMax (Optional) Returns the maximum current advertisement interval.
 *
 * @return @c EOK on successful start of low energy advertisements,
 *         @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c EBUSY: The stack is currently busy or there is an active
 *                     connection or connection request.
 *         - @c EINVAL: Advertisement parameters provided were invalid.
 *         - @c EMLINK: Advertising cannot be performed as there is already an
 *                      existing low energy connection.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOTSUP: Starting advertisements is not supported.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_start_advertisement(bt_le_advert_parm_t *advertParm, uint16_t *intervalMin, uint16_t *intervalMax);

/**
 * @brief Stop low energy advertisements
 *
 * @return @c EOK on successful stop of low energy advertisements, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c EBUSY: The stack is currently busy or there is an active
 *                     connection or connection request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_stop_advertisement();

/**
 * @brief This function enables the invoking of a service application when a
 *        local advertisement change or completed events occurs. The application
 *        is invoked when the first advertisement is received that meets
 *        the set scan parameters and filters after the application is
 *        terminated or @c bt_le_deinit is called.  When invoked, the invoke
 *        action is @c bb.action.bluetooth.ADVERTCHANGE or
 *        @c bb.action.bluetooth.ADVERTCOMPLETE. You can use
 *        @c bt_le_invoke_decode_advert_changed() and
 *        @c bt_le_invoke_decode_advert_complete() to retrieve the event data.
 *        You must perform this operation from the headless application.
 *        The setup values will persist until the timeout has completed or
 *        @c bt_le_stop_advertisement() is called.
 *
 * @param target The target key that is defined in the application manifest.
 *
 * @return @c EOK on successfully enabling the invoke interface, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c EPERM: The application that requests the invoke does not have
 *                     permission as it is not a headless application.
 *         - @c EACCES: The current application is not the owner of the
 *                      supplied target.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_enable_advert_invoke(const char *target);

/**
 * @brief This function disables the invoke feature for receiving local
 *        advertisement events.
 *
 * @return @c EOK on successful disabling the invoke interface, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c EPERM: The application that requests the disable the invoke
 *                     feature does not have permission as it is not a
 *                     headless application.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_disable_advert_invoke();

/**
 * @brief This function returns the reason why the local advertisement
 *        has completed when invoke is triggered with action
 *        @c "bb.action.bluetooth.ADVERTCOMPLETE".  The data that is provided
 *        must have the mime-type of
 *        @c "application/vnd.blackberry.bluetooth.advertcomplete".
 *
 * @param invoke_dat The data provided by the invoke interface.
 * @param invoke_len The length of the data provided by the invoke interface.
 * @param reason Returns the reason why the advertisements completed.
 *
 * @return @c EOK on success, @c -1 if an error occurred with the @c errno
 *         value set. These are some of the error codes that can be returned:
 *         - @c EAGAIN: @c bt_le_init() was not called.
 *         - @c EPROTO: The data provided is not properly formatted to the
 *                      required mime-type
 *         - @c EINVAL: One or more of the variables provided are invalid.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_invoke_decode_advert_complete(const char *invoke_dat, int invoke_len,
        bt_le_advert_complete_reason_t *reason);

/**
 * @brief This function is used to return the new advertisement intervals when
 *        invoke occurs with action @c "bb.action.bluetooth.ADVERTCHANGE".
 *        The data being provided must have the mime-type of
 *        "application/vnd.blackberry.bluetooth.advertchange".
 *        You must call @bt_le_init() before calling this function.
 *
 * @param invoke_dat The data that is provided by the invoke interface.
 * @param invoke_len The length of the data provided by the invoke interface.
 * @param intervalMin Returns the current minimum advertisement interval. Time = N * 0.625 msec.
 * @param intervalMax Returns current maximum advertisement interval. Time = N * 0.625 msec.
 *
 * @return @c EOK on success, @c -1 if an error occurred with the @c errno
 *         value set. These are some of the error codes that can be returned:
 *         - @c EAGAIN: @c bt_le_init() was not called.
 *         - @c EPROTO: The data provided is not properly formatted to the
 *                      required mime-type
 *         - @c EINVAL: One or more of the variables provided are invalid.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_invoke_decode_advert_changed(const char *invoke_dat, int invoke_len,
        uint16_t *intervalMin, uint16_t *intervalMax);

/**
 * @brief This function enables the invoking of a service application when a remote
 *        advertisement is received.
 * @details The application is invoked when
 *          the first advertisement is received that meets the set scan parameters
 *          and filters, and if the application has been deregistered (exited) or
 *          placed in the stop partition.  When invoked, the action
 *          is @c bb.action.bluetooth.SCANRESULT.  Upon receiving the
 *          event, you can retrieve the advertisement data by calling
 *          @c bt_le_invoke_decode_scan().  You must perform the invoke setup
 *          from the headless application. If the application is deregistered
 *          or terminated, the invoke setup will remain until the first invoke
 *          event is sent or if the application restarts and calls @c bt_le_init()
 *          prior to any invoke event.
 *
 * @param target The target key that is defined in the application manifest.
 *
 * @return @c EOK on successfully enabling the invoke interface, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c EACCES: The current application does not have permission to
 *                      invoke the supplied trigger.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_enable_scan_invoke(const char *target);

/**
 * @brief This function disables the invoke feature for receiving remote device
 *        scans.
 *
 * @return @c EOK on successfully disabling the invoke interface, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_disable_scan_invoke();

/**
 * @brief This function is used to parse the advertisement data received
 *        over the invoke interface when @c "bb.action.bluetooth.SCANRESULT"
 *        occurs.
 * @details The data that is provided must have the mime-type of
 *          "application/vnd.blackberry.bluetooth.scanresult".
 *          You must call @bt_le_init() before calling this function.
 *
 * @param invoke_dat The data provided by the invoke interface.
 * @param invoke_len The length of the data provided by the invoke interface.
 * @param bdaddr A pointer to the Bluetooth address of the advertisement from
 *               within the invoke data.   This pointer is only valid
 *               for the lifespan of the invoke data.
 * @param rssi The Remote Signal Strength Indicator (RSSI) of the advertisement.
 * @param data A pointer to the advertisement data that is received from the remote device.
 *             This pointer is only valid for the lifespan of the
 *             invoke data.
 * @param len The length of the advertisement data that is received from the remote
 *            device.
 *
 * @return @c EOK on success, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: @c bt_le_init() was not called.
 *         - @c EPROTO: The data provided is not properly formatted to the
 *                      required mime-type.
 *         - @c EINVAL: One or more of the variables provided are invalid.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_invoke_decode_scan_result(const char *invoke_dat, int invoke_len,
        const char **bdaddr, int8_t *rssi, const char **data, int *len);

/**
 * @brief Initialize the low energy functionality and allocate the required
 *        resources for the library
 * @details This function also starts a new thread for low energy functionality.
 *          The callback is invoked in the new thread and is thread safe. If an
 *          error is returned from this function call, the @c errno is set to
 *          indicate reason of failure.
 *
 * @param cb The list of callbacks to be used for low energy connection manager
 *           callbacks.
 *
 * @return @c EOK on successful initialization, @c -1 with the @c errno value
 *         set otherwise. The error codes that can be returned are as follows:
 *         - @c EACCES: Insufficient permissions to initialize the low energy
 *           functionality.
 *         - @c ENODEV: Bluetooth stack is unavailable.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOTSUP: The currently library version is not supported.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_init(bt_le_callbacks_t *cb);

/**
 * @brief Deallocate resources that were allocated to use low energy
 *        functionality
 * @details This function also stops the event loop that was created to work with
 *          the low energy functionality provided by this library.
 */
void bt_le_deinit();

/**
 * @cond
 * For internal use only. Do not use.
 *
 * The following prototypes are used as initialization functions for
 * various callbacks. The callbacks pass the version to indicate which
 * version an application is compiled against.
 */
int _bt_le_init(bt_le_callbacks_t *cb, uint32_t version);
#define bt_le_init(callbacks) _bt_le_init(callbacks, BT_LE_VERSION)
/** @endcond */


__END_DECLS

#endif /* _BTLE_H_ */


#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
