/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

#ifndef BTHID_H_
#define BTHID_H_

/**
 * @file bthid.h
 *
 * @brief Functions to implement the Bluetooth Human Interface Device (HID)
 *        Profile in the device role.  Can be used to remote control HID hosts
 *        such as a PC.
 *
 * This module allows an application to behave as a HID device to control a
 * remote HID Host, such as a PC.  The HID descriptor is fixed and cannot be changed.
 * Currently 3 types of HID reports are included: mouse, keyboard and enhanced
 * keyboard controls.
 *
 * The details of the descriptor are as follows:
 *
 * @code
 *       Mouse Descriptor
 *
 *       0x05, 0x01,              USAGE_PAGE (Generic Desktop)
 *       0x09, 0x02,              USAGE (Mouse)
 *       0xa1, 0x01,              COLLECTION (Application)
 *       0x85, 0x02,                  REPORT ID (Mouse)
 *       0xa1, 0x02,                  COLLECTION (Logical)
 *       0x09, 0x01,                      USAGE (Pointer)
 *       0xa1, 0x00,                      COLLECTION (Physical)
 *       0x05, 0x09,                          USAGE_PAGE (Button)
 *       0x19, 0x01,                          USAGE_MINIMUM (Button 1)
 *       0x29, 0x03,                          USAGE_MAXIMUM (Button 3)
 *       0x15, 0x00,                          LOGICAL_MINIMUM (0)
 *       0x25, 0x01,                          LOGICAL_MAXIMUM (1)
 *       0x95, 0x03,                          REPORT_COUNT (3)
 *       0x75, 0x01,                          REPORT_SIZE (1)
 *       0x81, 0x02,                          INPUT (Data,Var,Abs)
 *       0x95, 0x01,                          REPORT_COUNT (1)
 *       0x75, 0x05,                          REPORT_SIZE (5)
 *       0x81, 0x03,                          INPUT (Cnst,Var,Abs)
 *       0x05, 0x01,                          USAGE_PAGE (Generic Desktop)
 *       0x09, 0x30,                          USAGE (X)
 *       0x09, 0x31,                          USAGE (Y)
 *       0x15, 0x81,                          LOGICAL_MINIMUM (-127)
 *       0x25, 0x7f,                          LOGICAL_MAXIMUM (127)
 *       0x75, 0x08,                          REPORT_SIZE (8)
 *       0x95, 0x02,                          REPORT_COUNT (2)
 *       0x81, 0x06,                          INPUT (Data,Var,Rel)
 *       0x05, 0x01,                          Usage Page (Generic Desktop)
 *       0x09, 0x38,                          Usage (Wheel)
 *       0x15, 0x81,                          Logical Minimum (-127)
 *       0x25, 0x7F,                          Logical Minimum (127)
 *       0x75, 0x08,                          Report Size (8)
 *       0x95, 0x01,                          Report Count (1)
 *       0x81, 0x06,                          INPUT (Data,Var,Rel)
 *       0x05, 0x0c,                          USAGE_PAGE (Consumer Devices)
 *       0x0a, 0x38, 0x02,                    USAGE (AC Pan)
 *       0x15, 0x81,                          LOGICAL_MINIMUM (-127)
 *       0x25, 0x7f,                          LOGICAL_MAXIMUM (127)
 *       0x75, 0x08,                          Report Size (8)
 *       0x95, 0x01,                          Report Count (1)
 *       0x81, 0x06,                          INPUT (Data,Var,Rel)
 *       0xc0,                            END_COLLECTION
 *       0xc0,                        END_COLLECTION
 *       0xc0,                    END_COLLECTION
 *
 *       Keyboard Descriptor
 *
 *       0x05, 0x01,              USAGE_PAGE (Generic Desktop)
 *       0x09, 0x06,              USAGE (Keyboard)
 *       0xa1, 0x01,              COLLECTION (Application)
 *       0x85, 0x01,                  REPORT ID (Keyboard)
 *       0x05, 0x07,                  USAGE_PAGE (Keyboard)
 *       0x19, 0xe0,                  USAGE_MINIMUM (Keyboard Left Control)
 *       0x29, 0xe7,                  USAGE_MAXIMUM (Keyboard Right GUI)
 *       0x15, 0x00,                  LOGICAL_MINIMUM (0)
 *       0x25, 0x01,                  LOGICAL_MAXIMUM (1)
 *       0x75, 0x01,                  Report Size (1)
 *       0x95, 0x08,                  Report Count (8)
 *       0x81, 0x02,                  Input (Data, Var, Abs)
 *       0x95, 0x01,                  Report Count (1)
 *       0x75, 0x08,                  Report Size (8)
 *       0x81, 0x03,                  Input (Cnst, Var, Abs)
 *       0x95, 0x05,                  Report Count (5)
 *       0x75, 0x01,                  Report Size  (1)
 *       0x05, 0x08,                  USAGE_PAGE (LEDs)
 *       0x19, 0x01,                  USAGE_MINIMUM (NumLock)
 *       0x29, 0x05,                  USAGE_MAXIMUM (Kana)
 *       0x91, 0x02,                  Output (Data, Var, Abs)
 *       0x95, 0x01,                  Report Count (1)
 *       0x75, 0x03,                  Report Size  (3)
 *       0x91, 0x03,                  Output (Cnst, Var, Abs)
 *       0x95, 0x06,                  Report Count (6)
 *       0x75, 0x08,                  Report Size  (8)
 *       0x15, 0x00,                  LOGICAL_MINIMUM (0)
 *       0x25, 0x65,                  LOGICAL_MAXIMUM (101)
 *       0x05, 0x07,                  USAGE PAGE (KEYBOARD)
 *       0x19, 0x00,                  USAGE_MINIMUM (Reserved (no event indicated))
 *       0x29, 0x65,                  USAGE_MAXIMUM (Keyboard Application)
 *       0x81, 0x00,                  Input (Data, Ary, Abs)
 *       0xc0,                    END_COLLECTION
 *
 *       Enhanced Keys Descriptor
 *
 *       0x05, 0x0c,              USAGE_PAGE (Consumer)
 *       0x09, 0x01,              USAGE (Consumer Control)
 *       0xa1, 0x01,              COLLECTION (Application)
 *       0x85, 0x03,                  REPORT ID (Enhanced Keys)
 *       0x09, 0xE2,                  USAGE (Mute)
 *       0x15, 0x00,                  LOGICAL_MINIMUM (0)
 *       0x25, 0x01,                  LOGICAL_MAXIMUM (1)
 *       0x75, 0x01,                  REPORT_SIZE (1)
 *       0x95, 0x01,                  REPORT_COUNT (1)
 *       0x81, 0x06,                  INPUT (Data,Var,Rel)
 *       0x09, 0xE9,                  USAGE (Volume Up)
 *       0x09, 0xEA,                  USAGE (Volume Down)
 *       0x09, 0xCD,                  USAGE (Play/Pause)
 *       0x09, 0xB7,                  USAGE (Stop)
 *       0x09, 0xB5,                  USAGE (Scan Next Track)
 *       0x09, 0xB6,                  USAGE (Scan Previous Track)
 *       0x09, 0xB4,                  USAGE (Rewind)
 *       0x09, 0xB3,                  USAGE (Fast Forward)
 *       0x15, 0x00,                  LOGICAL_MINIMUM (0)
 *       0x25, 0x01,                  LOGICAL_MAXIMUM (1)
 *       0x75, 0x01,                  REPORT_SIZE (1)
 *       0x95, 0x08,                  REPORT_COUNT (8)
 *       0x81, 0x02,                  Input (Data, Var, Abs)
 *       0x75, 0x01,                  REPORT_SIZE (1)
 *       0x95, 0x07,                  REPORT_COUNT (7)
 *       0x81, 0x03,                  INPUT (Cnst,Var,Abs)
 *       0xc0                     END_COLLECTION
 * @endcode
 */

#include <unistd.h>

__BEGIN_DECLS

/**
 * Bluetooth HID device API version.
 * For example, the value @c 0x00010000 translates to 0001.00.00 or v1.0.0.
 */
#define BT_HID_VERSION  0x00010001

/**
 * HID protocol selection.
 */
typedef enum {

    /**
     * You can set the HID protocol to Boot Protocol.
     */
    BT_HID_PROTOCOL_BOOT = 0,

    /**
     * Default is Report Protocol.
     */
    BT_HID_PROTOCOL_REPORT = 1,

} bt_hid_protocol_t;


/**
 * HID idle rate value.
 */
typedef uint16_t bt_hid_idle_rate_t;


/**
 * HID report type selection.
*/
typedef enum {

    /**
     * Other report type
     */
    BT_HID_REPORT_OTHER = 0,

    /**
     * Input report type
     */
    BT_HID_REPORT_INPUT = 1,

    /**
     * Output report type
     */
    BT_HID_REPORT_OUTPUT = 2,

    /**
     * Feature report type
     */
    BT_HID_REPORT_FEATURE = 3,

} bt_hid_report_type_t;

/**
 *  HID result type.
 */
typedef enum {

    /**
     * Result indicating success.
     */
    BT_HID_RESULT_SUCCESS = 0,

    /**
     * Result indicating failure because the application was not ready.
     */
    BT_HID_RESULT_NOT_READY = 1,

    /**
     * Result indicating failure because report ID was not valid.
     */
    BT_HID_RESULT_INVALID_REPORT_ID = 2,

    /**
     * Result indicating failure because request is not supported.
     */
    BT_HID_RESULT_UNSUPPORTED_REQUEST = 3,

    /**
     * Result indicating failure because request contained an invalid parameter.
     */
    BT_HID_RESULT_INVALID_PARAMETER = 4,

    /**
     * Result indicating failure because of an unknown reason.
     */
    BT_HID_RESULT_UNKNOWN = 5,

    /**
     * Result indicating a fatal failure.
     */
    BT_HID_RESULT_FATAL = 6,

} bt_hid_result_t;

/**
 * HID report.
 */
typedef struct bt_hid_report {
    /**
     * Report type (input, output, or feature).
     */
	bt_hid_report_type_t  reportType;
    /**
     * Length of the report data.
     */
    uint16_t                dataLen;
    /**
     * Pointer to the report data.
     */
    uint8_t                 *data;
} bt_hid_report_t;

/**
 * HID report request.
 */
typedef struct bt_hid_report_req {
    /**
     * Report type (input, output, or feature).
     */
	bt_hid_report_type_t reportType;
    /**
     * Set to TRUE if reportId should be used.
     */
	uint8_t useId;
    /**
     * The report ID.
     */
    uint8_t reportId;
    /**
     * The maximum buffer size for returning events.
     */
    uint16_t bufferSize;
} bt_hid_report_req_t;

/**
 * The callback prototype to indicate the completion of @c bt_hid_connect_async().
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *        - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                     can try again.
 *        - @c ENOMEM: Sufficient memory is not available to perform the
 *             request.
 *        - @c ENOTSUP: The requested service is not supported by the device.
 *        - @c ENOSYS: Cannot create a connection to the device.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
typedef void (*bt_hid_service_connected_async_cb) (void *user_data, int error );
/**
 * The callback prototype to indicate a service has been connected.  This is
 * used for incoming connections only.
 *
 * @param bdaddr The address of the remote Bluetooth-enabled device.
 */
typedef void (*bt_hid_service_connected_cb) ( const char *bdaddr );

/**
 * The callback prototype to indicate the service has been disconnected.
 *
 * @param reason @c EOK indicates a successful service connection; otherwise an
 *               error code indicates the reason for the connection failure.
 *               The following error codes can be returned:
 *               - @c EACCES: An authentication or pairing failure has occurred.
 *               - @c ENOTCONN: There is no connection.
 *               - @c ECONNREFUSED: The connection was refused because the
 *                            connection parameters provided are invalid.
 *               - @c ECONNRESET: The remote party has terminated the connection.
 *               - @c ENETUNREACH: A page timeout has occurred.
 *               - @c EPROTO: The operation has failed because the response from the
 *                            remote Bluetooth-enabled device had a protocol error.
 *               - @c ETIMEOUT: The connection attempt has timed out.
 */
typedef void (*bt_hid_service_disconnected_cb) (int reason);

/**
 * The callback prototype to indicate a report has been requested.  The application
 * must respond to this event by calling @c bt_hid_get_report_res().
 *
 * @param req Information about the report request.
 */
typedef void (*bt_hid_report_req_cb) (const bt_hid_report_req_t *req);

/**
 * The callback prototype to indicate a report has been received.  The application
 * must respond to this event by calling @c bt_hid_set_report_res().
 *
 * @param report The report that has been received.
 */
typedef void (*bt_hid_report_set_cb) (const bt_hid_report_t *report);

/**
 * The callback prototype to indicate the protocol has been requested.  The application
 * must respond to this event by calling @c bt_hid_get_protocol_res().
 *
 */
typedef void (*bt_hid_protocol_req_cb) (void);

/**
 * The callback prototype to indicate a protocol has been set.  The application
 * must respond to this event by calling @c bt_hid_set_protocol_res().
 *
 * @param protocol The protocol being set.
 */
typedef void (*bt_hid_protocol_set_cb) (bt_hid_protocol_t protocol);

/**
 * The callback prototype to indicate the idle rate has been requested.  The application
 * must respond to this event by calling @c bt_hid_get_idle_res().
 *
 */
typedef void (*bt_hid_idle_req_cb) (void);

/**
 * The callback prototype to indicate the idle rate has been set.  The application
 * must respond to this event by calling @c bt_hid_set_idle_res().
 *
 * @param idle The idle rate being set.
 */
typedef void (*bt_hid_idle_set_cb) (bt_hid_idle_rate_t idle);

/**
 * The callback prototype to indicate that the interrupt message has been sent.
 */
typedef void (*bt_hid_interrupt_sent_cb) (void);

/**
 * A structure that contains the list of callbacks to be used for a HID Device
 */
typedef struct {
    /**
     * A callback that indicates that service has been connected.
     */
    bt_hid_service_connected_cb connected;
    /**
     * A callback that indicates that service has been disconnected.
     */
    bt_hid_service_disconnected_cb disconnected;
    /**
     * A callback that requests a report.
     */
    bt_hid_report_req_cb report_req;
    /**
     * A callback that contains a report.
     */
    bt_hid_report_set_cb report_set;
    /**
     * A callback that requests the protocol.
     */
    bt_hid_protocol_req_cb protocol_req;
    /**
     * A callback that sets the protocol.
     */
    bt_hid_protocol_set_cb protocol_set;
    /**
     * A callback that requests the idle rate.
     */
    bt_hid_idle_req_cb idle_req;
    /**
     * A callback that sets the idle rate.
     */
    bt_hid_idle_set_cb idle_set;
    /**
     * A callback to indicate that an interrupt has been sent.
     */
    bt_hid_interrupt_sent_cb interrupt_sent;

} bt_hid_callbacks_t;


/**
 * @brief Initialize the resources required for the HID module
 * @details You must call this function before using any other
 *          functions in the library. If you call this function successfully,
 *          call the @c bt_hid_deinit() function when your application has
 *          finished using the HID module.
 * @param cb The list of callbacks to be used for HID Device callbacks.
 *
 * @return @c 0 is returned when initialization is successful, @c -1 with the @c errno
 *         set.  The error codes that can be returned are as follows:
 *        - @c EBUSY: The HID module has already been initialized.
 *        - @c EINVAL: Callbacks are not provided.
 *        - @c EACCESS: Insufficient permissions to initialize functionality.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_init(bt_hid_callbacks_t *cb);

/**
 * @brief Clean up resources used at initialization
 * @details This function cleans up resources initialized by the @c
 *          bt_hid_init() function after all connections are closed by the user.
 *
 *          Call this function after you have previously called the @c bt_hid_init()
 *          function successfully and after your application has finished using
 *          the HID module.
 *
 *          You do not need to call @c bt_hid_deinit() if a call to the @c
 *          bt_hid_init() function fails.
 *
 * @return @c 0 is returned when deinitialization is successful, @c -1 with the @c errno
 *         set.
 */
int bt_hid_deinit();

/**
 * @brief Create a HID Device connection to a service on a remote Bluetooth
 *        device (HID Host)
 * @details This function attempts to open a HID Device connection to a Host
 *          device at the address specified.  The function blocks after making a
 *          connection request and returns EOK when the connection has been
 *          successfully established.
 *
 * @param addr  The remote Bluetooth device (Host) address.
 * @return @c 0 if the service connection is successful, or @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c EBUSY: The requested service is already in use.
 *        - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                     can try again.
 *        - @c EINVAL: Invalid stack parameters or connection to the remote
 *                     Bluetooth-enabled device is not available.
 *        - @c ENODEV: The requested Bluetooth-enabled device could not be
 *                     found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ENOTSUP: The requested service is not supported by the device.
 *        - @c ENOSYS: Cannot create a connection to the device.
 *        - @c ESRVRFAULT: An internal error has occurred.
 *        - @c ETIMEOUT: The connection attempt has timed out.
 */
int bt_hid_connect(const char *addr);

/**
 * @brief Asynchronously create a HID Device connection to a service on a remote
 *        Bluetooth device (HID Host).
 * @details This function attempts to open a HID connection to a Host
 *          device at the address specified.  Once completed, the specified
 *          @c bt_hid_service_connected_async_cb() callback function is
 *          executed.
 *
 * @param addr  The remote Bluetooth device (Host) address.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c 0 if the service connection is successful, or @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c EBUSY: The requested service is already in use.
 *        - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                     can try again.
 *        - @c EINVAL: Invalid stack parameters or connection to the remote
 *                     Bluetooth-enabled device is not available.
 *        - @c ENODEV: The requested Bluetooth-enabled device could not be
 *                     found.
 *        - @c ENOMEM: Sufficient memory is not available to perform the
 *             request.
 *        - @c ENOTSUP: The requested service is not supported by the device.
 *        - @c ENOSYS: Cannot create a connection to the device.
 *        - @c ESRVRFAULT: An internal error has occurred.
 *        - @c ETIMEOUT: The connection attempt has timed out.
 */
int bt_hid_connect_async( const char *addr, bt_hid_service_connected_async_cb cb, void *user_data );

/**
 * @brief Disconnect the HID Device service
 * @details If your HID Device application is still connected, this function closes the service.
 *
 * @return  @c 0 is returned when the service is successfully disconnected, @c -1 with the @c errno
 *          set otherwise. The @c errno can be set to one of the following values:
 *          - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *          - @c ENODEV: A connection cannot be found.
 */
int bt_hid_disconnect();

/**
 * @brief Register for incoming connections
 * @details An application calls this function to register for incoming HID device connection
 *          notification. If the application successfully registers and an incoming connection
 *          from a remote Bluetooth device (HID Host) occurs, the application will be notified
 *          by the @c bt_hid_service_connected_cb callback.
 *
 * @return @c 0 if the registration is successful, or @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c EBUSY: The requested service is already in use.
 *        - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                     can try again.
 *        - @c EINVAL: Invalid stack parameters.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_register();

/**
 * @brief Deregister to disallow incoming connections
 * @details An application calls this function to disallow incoming HID device connections
 *          from a remote Bluetooth device (Host).
 *
 * @return @c 0 if the service is deregistered, or @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_deregister();

/**
 * @brief Send a response to a received report
 * @details An application must call this function in response to the @c bt_hid_report_set_cb
 *          callback.
 * @param result Use @c BT_HID_RESULT_SUCCESS to successfully acknowledge the report, or else
 *               indicate an error.
 *
 * @return @c 0 if the response is successfully sent, or @c -1
 *         with the @c errno set otherwise. The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_set_report_res(bt_hid_result_t result);

/**
 * @brief Sends a report as a response to the @c bt_hid_report_req_cb callback
 * @details An application must call this function in response to the @c bt_hid_report_req_cb
 *          callback.
 * @param result Use @c BT_HID_RESULT_SUCCESS to respond to the request with a report, or else
 *               indicate an error.
 * @param report The requested report to send.
 *
 * @return @c 0 if the response has been successfully sent, or @c -1
 *         with the @c errno set otherwise. The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_get_report_res(bt_hid_result_t result, const bt_hid_report_t *report);

/**
 * @brief Send a response to a received protocol
 * @details An application must call this function in response to the @c bt_hid_protocol_set_cb
 *          callback.
 * @param result Use @c BT_HID_RESULT_SUCCESS to successfully acknowledge the protocol, or else
 *               indicate an error.
 *
 * @return @c 0 if the response has been successfully sent, or @c -1
 *         with the @c errno set otherwise.  The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_set_protocol_res(bt_hid_result_t result);

/**
 * @brief Send the current protocol as a response to the bt_hid_protocol_req_cb callback
 * @details An application must call this function in response to the @c bt_hid_protocol_req_cb
 *          callback.
 * @param result Use @c BT_HID_RESULT_SUCCESS to respond to the request with a protocol,
 *               or else indicate an error.
 * @param protocol The current protocol.
 *
 * @return @c 0 if the response has been successfully sent, or @c -1
 *         with the @c errno set otherwise.  The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_get_protocol_res(bt_hid_result_t result, bt_hid_protocol_t protocol);

/**
 * @brief Send a response to a received idle rate
 * @details An application must call this function in response to the @c bt_hid_idle_set_cb
 *          callback.
 * @param result Use @c BT_HID_RESULT_SUCCESS to successfully acknowledge the idle rate, or else
 *               indicate an error.
 *
 * @return @c 0 if the response has been successfully sent, or @c -1
 *         with the @c errno set otherwise.  The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_set_idle_res(bt_hid_result_t result);

/**
 * @brief Send the current idle rate as a response to the @c bt_hid_idle_req_cb callback
 * @details An application must call this function in response to the @c bt_hid_idle_req_cb
 *          callback.
 * @param result Use @c BT_HID_RESULT_SUCCESS to respond to the request with an idle rate,
 *               or else indicate an error.
 * @param idlerate The current idle rate.
 *
 * @return @c 0 if the response has been successfully sent, or @c -1
 *         with the @c errno set otherwise.  The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_get_idle_res(bt_hid_result_t result, bt_hid_idle_rate_t idlerate);

/**
 * @brief Send a report to the remote device
 * @details This function is used to send a report to the remote device.  An application can
 *          call this function as a response to human input, such as a mouse movement or a
 *          key press.
 * @param report The requested report to send.
 *
 * @return @c 0 if the report has been successfully sent, or @c -1
 *         with the @c errno set otherwise.  The error codes that can be returned are as follows:
 *        - @c EPERM: The @c bt_hid_init() function was not called or did not complete successfully.
 *        - @c ENODEV: A connection cannot be found.
 *        - @c ENOMEM: Insufficient memory is available to perform the
 *             request.
 *        - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_hid_send_interrupt(bt_hid_report_t const *report );

/**
 * @cond
 * For internal use only. Do not use.
 * The following are prototypes that are used for the initialization function.
 * This function passes the version information as an argument so that it is
 * possible to determine the version an application was compiled with.
 */
int _bt_hid_init(bt_hid_callbacks_t *cb, uint32_t version);
#define bt_hid_init(callbacks) _bt_hid_init((callbacks), BT_HID_VERSION)

/** @endcond */
__END_DECLS

#endif /* BTHID_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
