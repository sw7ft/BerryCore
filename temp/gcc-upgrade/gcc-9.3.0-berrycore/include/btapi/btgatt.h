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
 * @file btgatt.h
 *
 * @brief Functions and structures that provide Bluetooth Generic Attribute
 *        Profile (GATT) functions to communicate with a GATT server.
 *
 * This file defines functions to work with Bluetooth capabilities on classic
 * and low-energy devices. Before you use functions from this file, you must
 * call the @c bt_gatt_init() function. You must call the @c bt_gatt_deinit()
 * function when GATT functionality is no longer required in your application.
 *
 */



#ifndef _BTGATT_H_
#define _BTGATT_H_

#include <stdint.h>

/**
 * The Bluetooth Generic Attribute (GATT) API version
 * For example, the value @c 0x00000900 translates to 0000.09.00 or v0.9.0.
 */
#define BT_GATT_VERSION         0x00000900
/**
 * The time frame used to run a scan indefinitely for a connection.
 */
#define BT_GATT_TIME_INFINITY      0xFFFFFFFF

/** @deprecated This definition is deprecated.  Use @c BT_GATT_TIME_INFINITY instead.
 */
#define GATT_TIME_INFINITY         BT_GATT_TIME_INFINITY

/**
 * Possible Attribute Protocol (ATT) error codes that may be used in read/write responses.
 */
typedef enum {

    /**
     * No errors
     */
    BT_GATT_ATT_ERROR_NONE                           = 0x00,

    /**
     * The attribute handle given is not valid on this server.
     */
    BT_GATT_ATT_ERROR_INVALID_HANDLE                 = 0x01,

    /**
     * The attribute cannot be read.
     */
    BT_GATT_ATT_ERROR_READ_NOT_PERMITTED             = 0x02,

    /**
     * The attribute cannot be written to.
     */
    BT_GATT_ATT_ERROR_WRITE_NOT_PERMITTED            = 0x03,

    /**
     * The attribute Protocol Data Unit (PDU) was invalid.
     */
    BT_GATT_ATT_ERROR_INVALID_PDU                    = 0x04,

    /**
     * The attribute requires authentication before it can be read from or
     * written to.
     */
    BT_GATT_ATT_ERROR_INSUFFICIENT_AUTHENTICATION    = 0x05,

    /**
     * The attribute server does not support the request received from the client.
     */
    BT_GATT_ATT_ERROR_REQUEST_NOT_SUPPORTED          = 0x06,

    /**
     * Offset specified was past the end of the attribute.
     */
    BT_GATT_ATT_ERROR_INVALID_OFFSET                 = 0x07,

    /**
     * The attribute requires authorization before it can be read from or
     * written to.
     */
    BT_GATT_ATT_ERROR_INSUFFICIENT_AUTHORIZATION     = 0x08,

    /**
     * Too many prepare writes have been queued.
     */
    BT_GATT_ATT_ERROR_PREPARE_QUEUE_FULL             = 0x09,

    /**
     * No attribute found within the given attribute handle range.
     */
    BT_GATT_ATT_ERROR_ATTRIBUTE_NOT_FOUND            = 0x0A,

    /**
     * The attribute cannot be read or written to using the Read Blob Request.
     */
    BT_GATT_ATT_ERROR_ATTRIBUTE_NOT_LONG             = 0x0B,

    /**
     * The encryption key size used for encrypting this link is insufficient.
     */
    BT_GATT_ATT_ERROR_INSUFFICIENT_ENCRYPT_KEY_SIZE  = 0x0C,

    /**
     * The attribute value length is invalid for the operation.
     */
    BT_GATT_ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH = 0x0D,

    /**
     * The attribute request that was requested has encountered an unlikely
     * error, and could not be completed as requested.
     */
    BT_GATT_ATT_ERROR_UNLIKELY_ERROR                 = 0x0E,

    /**
     * The attribute requires encryption before it can be read from or
     * written to.
     */
    BT_GATT_ATT_ERROR_INSUFFICIENT_ENCRYPTION        = 0x0F,

    /**
     * The attribute type is not a supported grouping attribute as defined by a
     * higher layer specification.
     */
    BT_GATT_ATT_ERROR_UNSUPPORTED_GROUP_TYPE         = 0x10,

    /**
     * Insufficient resources to complete the request.
     */
    BT_GATT_ATT_ERROR_INSUFFICIENT_RESOURCES         = 0x11,

    /**
     * Generic application error. Specific application error codes defined by an
     * application should be in the range of 0x80 - 0xFF.
     */
    BT_GATT_ATT_ERROR_GENERIC_APPLICATION_ERROR      = 0x80,
} bt_gatt_att_error_t;

/**
 * The maximum string length for a universally unique identifier (UUID).
 */
#define BT_GATT_UUID_STRING_LENGTH   39

/** @deprecated This definition is deprecated. Use @c BT_GATT_UUID_STRING_LENGTH instead.
 */
#define GATT_UUID_STRING_LENGTH            BT_GATT_UUID_STRING_LENGTH


/**
 * Client characteristic configuration UUID
 */
#define BT_GATT_CLIENT_CHAR_CFG_UUID "0x2902"

/** @deprecated This definition is deprecated. Use @c BT_GATT_CHARACTERISTIC_PROP_BROADCAST instead.
 */
#define GATT_CLIENT_CHAR_CFG_UUID          BT_GATT_CLIENT_CHAR_CFG_UUID


/**
 * The mask to show supported properties of the characteristic.
 */
typedef uint8_t bt_gatt_char_prop_mask;

/**
 * Allow for the broadcasting of Generic Attributes (GATT) characteristic values.
 */
#define BT_GATT_CHARACTERISTIC_PROP_BROADCAST 0x01

/** @deprecated This definition is deprecated. Use @c BT_GATT_CHARACTERISTIC_PROP_BROADCAST instead.
 */
#define GATT_CHARACTERISTIC_PROP_BROADCAST         BT_GATT_CHARACTERISTIC_PROP_BROADCAST

/**
 * Allow the characteristic values to be read.
 */
#define BT_GATT_CHARACTERISTIC_PROP_READ 0x02

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_READ instead.
 */
#define GATT_CHARACTERISTIC_PROP_READ              BT_GATT_CHARACTERISTIC_PROP_READ

/**
 * Allow characteristic values without responses to be written.
 */
#define BT_GATT_CHARACTERISTIC_PROP_WRITE_NORESP 0x04

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_WRITE_NORESP instead.
 */
#define GATT_CHARACTERISTIC_PROP_WRITE_NORESP     BT_GATT_CHARACTERISTIC_PROP_WRITE_NORESP

/**
 * Allow for characteristic values to be written.
 */
#define BT_GATT_CHARACTERISTIC_PROP_WRITE 0x08

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_WRITE_NORESP instead.
 */
#define GATT_CHARACTERISTIC_PROP_WRITE            BT_GATT_CHARACTERISTIC_PROP_WRITE


/**
 * Permits notification of characteristic values.
 */
#define BT_GATT_CHARACTERISTIC_PROP_NOTIFY 0x10

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_NOTIFY instead.
 */
#define GATT_CHARACTERISTIC_PROP_NOTIFY          BT_GATT_CHARACTERISTIC_PROP_NOTIFY

/**
 * Permits indications of characteristic values.
 */
#define BT_GATT_CHARACTERISTIC_PROP_INDICATE 0x20

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_INDICATE instead.
 */
#define GATT_CHARACTERISTIC_PROP_INDICATE        BT_GATT_CHARACTERISTIC_PROP_INDICATE


/**
 * Permits signed writes of the GATT characteristic values.
 */
#define BT_GATT_CHARACTERISTIC_PROP_WRITE_SIGNED 0x40

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_WRITE_SIGNED instead.
 */
#define GATT_CHARACTERISTIC_PROP_WRITE_SIGNED    BT_GATT_CHARACTERISTIC_PROP_WRITE_SIGNED

/**
 * Additional characteristic properties are defined in the characteristic
 * extended properties descriptor.
 */
#define BT_GATT_CHARACTERISTIC_PROP_EXT_PROP 0x80

/** @deprecated This definition is deprecated.  Use @c BT_GATT_CHARACTERISTIC_PROP_EXT_PROP instead.
 */
#define GATT_CHARACTERISTIC_PROP_EXT_PROP     BT_GATT_CHARACTERISTIC_PROP_EXT_PROP


/**
 * Structure representing a single GATT service.
 */
typedef struct {
    /**
     * The universally unique identifier (UUID) for the included Bluetooth
     * service.
     */
    char                    uuid[BT_GATT_UUID_STRING_LENGTH];
    /**
     * The handle of the included service.
     */
    uint16_t                handle;
    /**
     * The included service's starting attribute handle.
     */
    uint16_t                start_handle;
    /**
     * The end group handle of the included service.
     */
    uint16_t                end_handle;
} bt_gatt_included_service_t;

/**
 * Structure representing a single Generic Attribute (GATT) characteristic.
 */
typedef struct {
    /**
     * The string universally unique identifier (UUID) for the given
     * characteristic.
     */
    char                    uuid[BT_GATT_UUID_STRING_LENGTH];
    /**
     * The handle of the characteristic.
     */
    uint16_t                handle;
    /**
     * The properties for the characteristic
     */
    bt_gatt_char_prop_mask  properties;
    /**
     * The handle containing the data
     */
    uint16_t                value_handle;
} bt_gatt_characteristic_t;

/**
 * Structure representing a single Generic Attribute (GATT) descriptor.
 */
typedef struct {
    /**
     * The string UUID for the given descriptor.
     */
    char                    uuid[BT_GATT_UUID_STRING_LENGTH];
    /**
     * The handle for the descriptor.
     */
    uint16_t                handle;
} bt_gatt_descriptor_t;

/**
 * Structure that contains the connection scan parameters for a low energy
 * connection.
 */
typedef struct {
    /**
     * The initial scan interval, used if no connection exists and the
     * device is not advertising.
     * - Range: 0x0004 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 2.5 msec to 10.24 seconds
     */
    uint16_t interval1;

    /**
     * The initial scan interval used when either a connection exists or
     * the device is advertising.
     * - Range: 0x0004 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 2.5 msec to 10.24 seconds
     */
    uint16_t interval12;

    /**
     * The initial scan window.
     * - Range: 0x0004 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 2.5 msec to 10240 msec
     */
    uint16_t window1;

    /**
     * The time (in msec) to perform the initial scan. Use @c GATT_TIME_INFINITY
     * to run until the connection is created or disconnected.
     */
    uint32_t time1;

    /**
     * The second scan interval, used after @c time1 has expired.
     * - Range: 0x0004 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 2.5 msec to 10.24 seconds
     */
    uint16_t interval2;
    /**
     * The second scan window, used after @c time1 has expired.
     * - Range: 0x0004 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 2.5 msec to 10240 msec
     */
    uint16_t window2;
    /**
     * The time (in msec) to perform the second stage of the window or interval
     * scan. Use @c 0 to disable the second stage of window/interval scanning,
     * or @c GATT_TIME_INFINITY to run until a connection is created or
     * disconnected.
     */
    uint32_t time2;

} bt_gatt_scan_parm_t;

/**
 * Structure to represent the connection parameters for a low energy (LE) link.
 */
typedef struct {
    /**
     * Minimum value for the connection interval.
     * - Range: 0x0006 to 0x0C80
     * - Time = N * 1.25 msec
     * - Time Range: 7.5 msec to 4 seconds
     */
    uint16_t minConn;
    /**
     * Maximum value for the connection interval.
     * - Range: 0x0006 to 0x0C80
     * - Time = N * 1.25 msec
     * - Time Range: 7.5 msec to 4 seconds
     */
    uint16_t maxConn;
    /**
     * Slave latency for the connection.
     * - Range: 0x0000 to 0x01F4
     */
    uint16_t latency;
    /**
     * Supervision timeout for the LE Link, value must satisfy
     * the following condition: (superTimout > (1 + latency ) * maxConn);
     * - Range: 0x000A to 0x0C80
     * - Time = N * 10 msec
     * - Time Range: 100 msec to 32 seconds
     */
    uint16_t superTimeout;

} bt_gatt_conn_parm_t;


/**
 * The callback prototype to indicate a service has been connected or a
 * connection attempt has failed.
 *
 * The @c connInt, @c latency, and @c superTimeout parameters are only required
 * for low-energy devices.
 *
 * @param bdaddr The address of the Bluetooth-enabled device.
 * @param service The service that has been connected. This can be either
 *                a 128-bit or a 16-bit Universally Unique Identifier (UUID).
 *                The UUID is represented as a string value.
 * @param instance An identifier used to reference the service connection.
 * @param err @c EOK indicates a successful service connection, otherwise an
 *            error code indicates reason for the connection failure. The
 *            following error codes can be returned:
 *            - @c EACCES: An authentication or pairing failure occurred.
 *            - @c EBUSY: The stack was busy and could not complete the request.
 *            - @c ECONNREFUSED: The connection was refused due to incorrect
 *                               connection parameters provided.
 *            - @c ECONNRESET: The remote party terminated the connection.
 *            - @c EINVAL: Invalid stack parameters, or connection to the remote
 *                         Bluetooth-enabled device is not available.
 *            - @c EMLINK: There were too many active connections.
 *            - @c ENETUNREACH: A page timeout occurred.
 *            - @c ENOENT: The service was not available on the remote device.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ENOSYS: The operation failed at the stack level.
 *            - @c EPROTO: The operation failed because the response from the
 *                         remote Bluetooth-enabled device had a protocol error.
 *            - @c ETIMEOUT: The connection attempt timed out.
 * @param connInt The negotiated connection interval for the service. Only use
 *                this argument for low-energy devices.  For BR/EDR devices this
 *                value must be zero.
 * @param latency The negotiated latency for the service. Only use
 *                this argument for low-energy devices.  For BR/EDR devices this
 *                value must be zero.
 * @param superTimeout The negotiated supervisor timeout for the connection.
 *                     Use this argument only for low-energy devices.  For BR/EDR
 *                     devices this value must be zero.
 * @param userData Pointer to the user data that is passed in during the
 *                 connection request.
 */
typedef void (*bt_gatt_service_connected_cb) (const char *bdaddr, const char *service, int instance, int err, uint16_t connInt, uint16_t latency, uint16_t superTimeout, void *userData);

/**
 * The callback prototype to indicate that the service has been disconnected.
 * This callback is not triggered if the request to disconnect comes from the user.
 *
 * @param bdaddr The address of the Bluetooth-enabled device.
 * @param service The service that has been disconnected. This can be either
 *                a 128-bit or a 16-bit Universally Unique Identifier (UUID).
 *                The UUID is represented as a string value. The string
 *                representation for GATT services is @c 0x1435.
 * @param instance The identifier used to reference the service connection.
 * @param reason @c EOK indicates a successful service connection, otherwise an
 *               error code indicates the reason for the connection failure.
 *               The following error codes can be returned:
 *               - @c EACCES: An authentication or pairing failure occurred.
 *               - @c ENOTCONN: There is no connection.
 *               - @c ECONNREFUSED: The connection was refused due to invalid
 *                                  connection parameters.
 *               - @c ECONNRESET: The remote party terminated the connection.
 *               - @c ENETUNREACH: A page timeout occurred.
 *               - @c EPROTO: The operation failed because the response from
 *                            the remote Bluetooth-enabled device had a
 *                            protocol error.
 *               - @c ETIMEOUT: The connection attempt timed out.
 * @param userData Pointer to the user data that is passed in during the
 *                 connection request.
 */
typedef void (*bt_gatt_service_disconnected_cb) (const char *bdaddr, const char *service, int instance, int reason, void *userData);

/**
 * The callback prototype to indicate that the service connection parameters have
 * changed. The prototype is only valid for low-energy devices.
 *
 * @param bdaddr The address of the Bluetooth-enabled device.
 * @param instance The identifier used to reference the service connection.
 * @param connInt The negotiated connection interval for the service.
 * @param latency The negotiated latency for the service.
 * @param superTimeout The negotiated supervisor timeout for the connection.
 * @param userData Pointer to the user data that is passed in during the
 *                 connection request.
 */
typedef void (*bt_gatt_service_updated_cb) (const char *bdaddr, int instance,
        uint16_t connInt, uint16_t latency,
        uint16_t superTimeout, void *userData);

/**
 * The callback prototype to indicate a notification or indication event has
 * occurred.
 *
 * @param instance The identifier used to reference the service connection.
 * @param handle The valueHandle of the characteristic which caused the event.
 * @param val A pointer to the data sent in the notification.
 * @param len The length of data sent.
 * @param userData Pointer to user data defined in connection request.
 */
typedef void (*bt_gatt_notifications_cb) (int instance, uint16_t handle, const uint8_t *val, uint16_t len, void *userData);

/**
 * The callback prototype to indicate that @c bt_gatt_included_service_async has completed.
 *
 * @param instance The identifier used to reference the service.
 * @param services An array of included services when operation
 *                 completes successfully.
 * @param size The size of the included services array. The size
 *             indicates the number of structures in the array and not the
 *             memory size required for the structures.
 * @param error The ATT result of the operation.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_included_services_cb) (int instance, bt_gatt_included_service_t *services, uint16_t size, bt_gatt_att_error_t error, void *user_data);


/**
 * The callback prototype to indicate that @c bt_gatt_descriptors_async has completed.
 *
 * @param instance The identifier used to reference the service.
 * @param characteristic the characteristic to discover descriptors of.
 * @param descriptor An array of descriptors provided when operation
 *                   completes successfully.
 * @param size The size of the descriptor array. The size
 *             indicates the number of structures in the array and not the
 *             memory size required for the structures.
 * @param error The ATT result of the operation.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_descriptors_cb) (int instance, bt_gatt_characteristic_t *characteristic,
        bt_gatt_descriptor_t *descriptor, uint16_t size, bt_gatt_att_error_t error, void *user_data);


/**
 * The callback prototype to indicate that @c bt_gatt_characteristc_async has completed.
 *
 * @param instance The identifier used to reference the service.
 * @param characteristics An array of characteristics when operation
 *                        completes successfully.
 * @param size The size of the characteristic array. The size
 *             indicates the number of structures in the array and not the
 *             memory size required for the structures.
 * @param error The ATT result of the operation.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_characteristics_cb) (int instance, bt_gatt_characteristic_t *characteristics, uint16_t size, bt_gatt_att_error_t error, void *user_data);

/**
 * The callback prototype to indicate that @c bt_gatt_read_value_async has completed.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The handle of the value to be read.
 * @param offset The offset to begin reading from.
 * @param data A pointer to the data that was read.
 * @param size The size of the data array.
 * @param more Flag to indicate if there is more data to be read.
 * @param error The ATT result of the operation.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_read_value_cb) (int instance, uint16_t handle, uint16_t offset, uint8_t *data, uint16_t size, uint8_t more, bt_gatt_att_error_t error, void *user_data);

/**
 * The callback prototype to indicate that @c bt_gatt_write_value_async has completed.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The handle where the value was written.
 * @param error The ATT result of the operation.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_write_value_cb) (int instance, uint16_t handle, bt_gatt_att_error_t error, void *user_data);


/**
 * A structure that contains the list of callbacks to be used for GATT connections
 */
typedef struct {
    /**
     * The callback that indicates that a service has been connected.
     */
    bt_gatt_service_connected_cb connected;
    /**
     * The callback that indicates that a service has been disconnected.
     */
    bt_gatt_service_disconnected_cb disconnected;
    /**
     * The callback that indicates that connection parameters have changed.
     */
    bt_gatt_service_updated_cb updated;
} bt_gatt_callbacks_t;


__BEGIN_DECLS
/**
 * @brief Request for a asynchronous connection to a single service.
 * @details After a connection attempt has completed, the @c
 *         bt_gatt_service_connected_cb function is called.
 *
 * @param bdaddr The Bluetooth MAC address of the remote device.
 * @param service The single service to be connected. This can be either
 *                a 128-bit or a 16-bit universally unique identifier (UUID).
 *                The UUID is represented as a NULL-terminated string value. An
 *                example of the string representation for GATT services is
 *                @c 0x1435. The 128-bit UUID is traditionally represented as
 *                @c 0xF0000000-0451-4000-B000-000000000000.
 * @param scanParm (Optional) The requested link connection scan parameters.
 *                 Use this argument only when specific scan parameters are
 *                 required for the service, otherwise set to NULL to use
 *                 default values. Use this argument only for low energy
 *                 devices.
 *                 These are the default values:
 *                 - interval1  = 30ms
 *                 - interval12 = 60ms
 *                 - window1    = 30ms
 *                 - time1      = 30sec
 *                 - interval2  = 1.28sec
 *                 - window2    = 11.25ms
 *                 - time2      = 30sec
 * @param connParm (Optional) The requested link connection parameters. Use
 *                 this argument when you require specific connection parameters
 *                 for the service, set it to @c NULL to use default values
 *                 otherwise. Use this argument only for low-energy devices.
 *                 These are the default values:
 *                 - minConn = 30ms
 *                 - maxConn = 50ms
 *                 - superTimeout = 100ms
 *                 - latency = 0
 * @param userData (Optional) A pointer to user data that will be passed back
 *                 during connection/disconnection callbacks.
 *
 * @return @c EOK on successful registration of the service connection requestor,
 *         @c -1 with the @c errno set otherwise. Some of the possible error
 *         codes that can be returned are as follows:
 *        - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                     can try again.
 *        - @c EBUSY: The requested service is already in use.
 *        - @c EDEADLK: A potential deadlock has been avoided.
 *        - @c EINVAL: Invalid stack parameters or connection to the remote
 *                     Bluetooth-enabled device is not available.
 *        - @c ENODEV: The requested Bluetooth-enabled device could not be
 *                     found in the paired/known device list.
 *        - @c ENOMEM: Sufficient memory is not available to perform the
 *                     request.
 *        - @c ENOTSUP: The requested service is not supported by the device.
 *        - @c ENOSYS: Could not create a connection to the device.
 *        - @c ESRVRFAULT: An internal error has occurred.
 *        - @c ETIMEOUT: The connection attempt timed out.
 */
int bt_gatt_connect_service(const char *bdaddr, const char *service, bt_gatt_scan_parm_t *scanParm, bt_gatt_conn_parm_t *connParm, void *userData);

/**
 * @brief Request for an asynchronous connection to the remote device.
 * @brief When the connection completes, the @c bt_gatt_service_connected_cb
 *        is called.
 *
 * @param bdaddr The MAC address of the remote Bluetooth-enabled device.
 * @param services A NULL-terminated string list of services to be connected to.
 *                 This can be represented as 128-bit or 16-bit Universally
 *                 Unique Identifiers (UUIDs). The UUID is represented as a
 *                 string value. An example of the string representation for
 *                 GATT services is @c 0x1435. The 128-bit UUID is traditionally
 *                 represented as @c 0xF0000000-0451-4000-B000-000000000000.
 * @param scanParm (Optional) The requested link connection scan parameters.
 *                 Use this argument when you require specific connection
 *                 parameters for the service, set to NULL to use default values
 *                 otherwise. Use this argument only for low-energy devices.
 *                 These are the default values.
 *                 - interval1  = 30ms
 *                 - interval12 = 60ms
 *                 - window1    = 30ms
 *                 - time1      = 30sec
 *                 - interval2  = 1.28sec
 *                 - window2    = 11.25ms
 *                 - time2      = 30sec
 * @param connParm (Optional) The requested link connection parameters. Use
 *                            this argument when you require specific
 *                            connection parameters for the service,
 *                            set to NULL to use default values otherwise. Only
 *                            use this argument for low-energy devices. These
 *                            are the default values.
 *                             - connMin       = 30ms
 *                             - connMax       = 60ms
 *                             - interval      = 30ms
 *                             - superTimeout  = 30sec
 * @param userData  (Optional) A pointer to user data that will be passed back
 *                             during connection/disconnection callbacks.
 *
 * @return @c EOK on successful registration of a service connection request, @c
 *         -1 with the @c errno set otherwise. Some of the possible error codes
 *         that can be returned are as follows:
 *            - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                         can try again.
 *            - @c EDEADLK: A potential deadlock has been avoided.
 *            - @c EBUSY: One of the requested services is currently in use.
 *            - @c EINVAL: The passed arguments are invalid.
 *            - @c ENODEV: The requested Bluetooth-enabled device could not be
 *                         found in the paired/known device list.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ENOSYS: Could not create a connection to the device.
 *            - @c ENOTSUP: The requested service is not supported by the device.
 *            - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_connect_services(const char *bdaddr, const char **services, bt_gatt_scan_parm_t *scanParm, bt_gatt_conn_parm_t *connParm, void *userData);

/**
 * @brief Disconnect a list of active services or cancel pending service
 *        connections
 *
 * @param bdaddr The MAC address of the remote Bluetooth-enabled device.
 * @param services A list of services to be disconnected or cancelled. These can
 *                 be either 128-bit or 16-bit universally unique identifiers
 *                 (UUIDs). The list is NULL-terminated. An example of the
 *                 string representation for GATT services is @c 0x1435. The
 *                 128-bit UUID is traditionally represented as
 *                 @c 0xF0000000-0451-4000-B000-000000000000.
 * @return @c EOK on successful disconnection of service, or @c -1 with the
 *         @c errno set otherwise. Some of the possible error codes that can be
 *         returned are as follows:
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The passed arguments are invalid.
 *         - @c ENODEV: A connection to the specified device could not be
 *                      found.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_disconnect_services(const char *bdaddr, const char **services);

/**
 * @brief Disconnect a single active service.
 * @details You can also use this function to cancel a pending service
 *          connection.
 *
 * @param bdaddr The MAC address of the remote Bluetooth-enabled device.
 * @param service The name of the service. An example of the string
 *                representation for GATT services is @c 0x1435. The 128-bit
 *                UUID is traditionally represented as
 *                @c 0xF0000000-0451-4000-B000-000000000000.
 * @return @c EOK on successful disconnection of the service, @c -1 with the @c
 *         errno set otherwise. Error codes that can be returned are as follows:
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The passed arguments are invalid.
 *         - @c ENODEV: A connection to the specified device could not be
 *                      found.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_disconnect_service(const char *bdaddr, const char *service);

/**
 * @brief Disconnect an active service
 * @param instance The identifier used to reference the active connection.
 * @return @c EOK on successful disconnection of the active service, -1 with the
 *         @c errno set otherwise. The error code that can be returned are as
 *         follows:
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The passed arguments are invalid.
 *         - @c ENODEV: A connection to the specified device could not be
 *                      found.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_disconnect_instance(int instance);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve a list of
 *        included services of the given primary service
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param services An array of services that is populated when the function
 *                 completes successfully. The string representation for GATT
 *                 services is 0x1435.
 * @param size The size of the array that is passed to the function. The size
 *             indicates the number of structures in the array and not the
 *             memory size required for the structures.
 * @return The number of included services that were retrieved when the function
 *         is successfully completed, @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *            - @c EACCESS: Insufficient authentication or authorization.
 *            - @c EBUSY: The stack was busy and could not complete the request.
 *            - @c EDEADLK: A potential deadlock has been avoided.
 *            - @c EINVAL: Invalid stack parameters or connection to the remote
 *                         Bluetooth-enabled device is not available.
 *            - @c ENODEV: The requested Bluetooth-enabled device could not be
 *                         found.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ENOSYS: The operation failed at the stack level.
 *            - @c EPROTO: The operation failed because the response from remote
 *                         Bluetooth-enabled device had a protocol error.
 *            - @c ESRCH: The service connection was not available.
 *            - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_included_services(int instance, bt_gatt_included_service_t *services, uint16_t size);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve a list of
 *        included services asynchronously for a given primary service
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c EOK when the function has successfully requested the included services,
 *         @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *            - @c EACCESS: Insufficient authentication or authorization.
 *            - @c EINVAL: Invalid stack parameters or the connection to the remote
 *                         Bluetooth-enabled device is not available.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ESRCH: The service connection was not available.
 *            - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_included_services_async(int instance, bt_gatt_included_services_cb cb, void *user_data);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve the number of
 *        included services within the primary service
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @return The number of included services that are available when the function
 *         is successfully completed, @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *            - @c EACCESS: Insufficient authentication or authorization.
 *            - @c EBUSY: The stack was busy performing another operation. You
 *                        can try again later.
 *            - @c EDEADLK: A potential deadlock has been avoided.
 *            - @c EINVAL: Invalid stack parameters or connection to the remote
 *                         Bluetooth-enabled device is not available.
 *            - @c ENODEV: Unable to find the service connection defined by the
 *                         @c instance argument.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ENOSYS: The operation failed at the stack level.
 *            - @c EPROTO: The operation failed because the response from remote
 *                         Bluetooth-enabled device had a protocol error.
 *            - @c ESRCH: The service connection was not available.
 *            - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_included_services_count(int instance);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve a list of
 *        characteristics for a provided primary service
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param characteristics An array of characteristics that is populated when the
 *                        function completes successfully.
 * @param size The size of the array passed to the function.
 * @return The number of characteristics retrieved when the function is
 *         successfully completed, @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_characteristics(int instance, bt_gatt_characteristic_t *characteristics, uint16_t size);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve a list of
 *        characteristics asynchronously for a provided primary service
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c EOK when the function has successfully requested the characteristics,
 *         @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *            - @c EACCESS: Insufficient authentication or authorization.
 *            - @c EINVAL: Invalid stack parameters or the connection to the remote
 *                         Bluetooth-enabled device is not available.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ESRCH: The service connection was not available.
 *            - @c ESRVRFAULT: An internal error has occurred.
 */
 int bt_gatt_characteristics_async(int instance, bt_gatt_characteristics_cb cb, void *user_data);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve the number of
 *        characteristics within a primary service
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @return The number of characteristics that are available, @c -1 with the @c
 *         errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_characteristics_count(int instance);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve the list of
 *        descriptors for a provided characteristic
 * @details The descriptor provides a list of services. For the @c
 *          characteristic argument, if you provide a handle of 0x0000, then the
 *          first characteristic that matches the universally unique identifier
 *          (UUID) will be discovered.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param characteristic Characteristic to discover descriptors of.
 * @param descriptors An array of descriptors to be populated if the function
 *                    completes successfully.
 * @param size The size of the array passed to the function.
 * @return The number of descriptors retrieved when the function is successfully
 *         completed, @c -1 with the @c errno set otherwise. The error codes
 *         that can be returned are as follows:
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_descriptors(int instance, const bt_gatt_characteristic_t *characteristic, bt_gatt_descriptor_t *descriptors, uint16_t size);

/**
 * @brief Perform a Generic Attribute (GATT) call to asynchronously retrieve
 *        the list of descriptors for a provided characteristic
 * @details For the @c characteristic argument, if you provide a handle of 0x0000, then the
 *          first characteristic that matches the universally unique identifier
 *          (UUID) will be retrieved.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param characteristic The characteristic for which this function retrieves
 *        the descriptors.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c EOK when the function has successfully requested the descriptors,
 *         @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *            - @c EACCESS: Insufficient authentication or authorization.
 *            - @c EINVAL: Invalid stack parameters or the connection to the remote
 *                         Bluetooth-enabled device is not available.
 *            - @c ENOMEM: Sufficient memory is not available to perform the
 *                         request.
 *            - @c ESRCH: The service connection was not available.
 *            - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_descriptors_async(int instance, const bt_gatt_characteristic_t *characteristic, bt_gatt_descriptors_cb cb, void *user_data);

/**
 * @brief Perform a Generic Attribute (GATT) call to retrieve the number of
 *        descriptors for a provided characteristic
 * @details You must provide the characteristic using the @c
 *          characteristic argument. You can retrieve information about the
 *          characteristic from the @c bt_gatt_characteristic_t structure.
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param characteristic The characteristic to retrieve a count on.
 * @return The number of descriptors that are available, @c -1 with the @c errno
 *         set otherwise. The error codes that can be returned are as follows:
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_descriptors_count(int instance, const bt_gatt_characteristic_t *characteristic);

/**
 * @brief Perform a Generic Attribute (GATT) call to read a value from
 *        a provided handle
 * @details You can use the optional @c more argument to indicate there is more
 *          data to read. If you do not provide the value, the function does
 *          indicate whether there is more data to be read. The reason being
 *          that in most cases, the size of the data is defined by the
 *          specifications of the protocol.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The handle of the value to be read.
 * @param offset The offset to begin reading from.
 * @param data A pointer to the array to be populated with the data that
 *             is read.
 * @param size The size of the array passed that is passed to the function.
 * @param more (Optional) Use a value of 1 to indicate that there is more
 *             data to read and a value of 0 to explicitly indicate that there
 *             is no more data to be read.
 * @return The number of bytes that have been read when the function is
 *         successfully completed, @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOENT: An invalid handle was provided for the GATT server.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c ENXIO: An unknown handle value was provided for a service.
 *         - @c EPERM: An attribute could not be read.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_read_value(int instance, uint16_t handle, uint16_t offset, uint8_t *data, uint16_t size, uint8_t *more);

/**
 * @brief Perform a Generic Attribute (GATT) call to read a value asynchronously from
 *        a provided handle
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The handle of the value to be read.
 * @param offset The offset to begin reading from.
 * @param size The size of data to be read.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return The number of bytes that have been read when the function is
 *         successfully completed, @c -1 with the @c errno set otherwise.
 *         The error codes that can be returned are as follows:
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EINVAL: The arguments passed in are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOENT: An invalid handle was provided for the GATT server.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_read_value_async(int instance, uint16_t handle, uint16_t offset, bt_gatt_read_value_cb cb, void *user_data);

/**
 * @brief Perform a Generic Attribute (GATT) call to write a value from a
 *        provided handle
 * @details This function writes values and expects a response from the remote
 *          Bluetooth-enabled device. The size of the value to be written cannot
 *          be larger than @c ATT_MTU - 3 bytes.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The to the value to be written.
 * @param offset The offset to begin writing from.
 * @param data An array of data to be written.
 * @param size The size of the array to be written.
 * @return @c EOK when data writing is successfully completed, @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c E2BIG: The requested write size is larger than @c ATT_MTU - 3
 *                     bytes.
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOENT: An invalid handle was provided for the GATT server.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c ENXIO: An unknown handle value was provided for a service.
 *         - @c EPERM: An attribute could not be written to.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_write_value(int instance, uint16_t handle, uint16_t offset, const uint8_t *data, int size);

/**
 * @brief Perform a Generic Attribute (GATT) call to asynchronously write a
 *        value from a provided handle
 * @details The size of the value to be written cannot be larger than
 *          @c ATT_MTU - 3 bytes.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The to the value to be written.
 * @param offset The offset to begin writing from.
 * @param data   An array of data to be written.
 * @param size   The size of the array to be written.
 * @param cb     The callback function to be executed when the operation has
 *               completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c EOK when data writing is successfully completed, @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c EINVAL: The arguments passed in are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_write_value_async(int instance, uint16_t handle, uint16_t offset, const uint8_t *data, int size,
        bt_gatt_write_value_cb cb, void *user_data);

/**
 * @brief Perform a Generic Attribute (GATT) call to write a value from a
 *        provided handle
 * @details This function specifically writes values with no response from the
 *          remote Bluetooth-enabled device.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param handle The handle to the value to be written.
 * @param offset The offset to begin writing from.
 * @param data An array of data to be written.
 * @param size The size of the array to be written.
 * @return @c EOK when data writing is successfully completed, @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c E2BIG: The requested write size is larger than ATT_MTU - 3 bytes.
 *         - @c EACCESS: Insufficient authentication or authorization.
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOENT: An invalid handle was provided for the GATT server.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c ENXIO: An unknown handle value was provided for a service.
 *         - @c EPERM: An attribute could not be written to.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_write_value_noresp(int instance, uint16_t handle, uint16_t offset, const uint8_t *data, int size);

/**
 * @brief Retrieve the Attribute Protocol Maximum Transmit Unit (ATT_MTU) for
 *        a provided handle
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @return The MTU value for the given instance when the function is completed
 *         successfully, @c -1 with the @c errno set otherwise. The error codes
 *         that can be returned are as follows:
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_get_mtu(int instance);

/**
 * @brief Register a callback to notify of Generic Attribute (GATT) events that
 *        occur.
 * @details This function notifies you when both notification and indication
 *          events occur. You must pass in the handle to the primary service.
 *          You can pass a value of @c NULL to the @c notify argument to clear a
 *          callback that you previously registered.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param notify The callback to call when an event occurs. Use a value of @c
 *               NULL to clear a callback that is registered to a primary
 *               service.
 * @return @c EOK when a notification has been successfully registered or
 *         cleared, @c -1 with the @c errno set otherwise. The error codes that
 *         can be returned are as follows:
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c EINVAL: An invalid argument was passed to the function.
 *         - @c ENOENT: An invalid handle was provided for the GATT server.
 *         - @c ESRCH: The service connection was not available.
 */
int bt_gatt_reg_notifications(int instance, bt_gatt_notifications_cb notify);

/**
 * @brief Enable notifications for a given Generic Attribute (GATT) characteristic.
 * @details You can also use this function to disable notifications for the
 *          specified characteristic.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param characteristic The GATT characteristic.
 * @param enable Enable or disable notifications for the specified
 *               @c characteristic. Use a value of 1 to enable notifications
 *               or a value of 0 to disable them.
 * @return @c EOK when notifications have been successfully enabled or disabled,
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_enable_notify(int instance, const bt_gatt_characteristic_t *characteristic, uint8_t enable);


/**
 * @brief Enable indications for a given Generic Attribute (GATT) characteristic.
 * @details You can also use this function to disable indications for the
 *          specified characteristic.
 *
 * @param instance The identifier used to reference the connected primary
 *                 service.
 * @param characteristic The GATT characteristic.
 * @param enable Enable or disable indications for the specified @c
 *               characteristic. Use a value of 1 to enable indications or
 *               a value of 0 to disable them.
 * @return @c EOK when indications have been successfully enabled or disabled,
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY: The stack was busy performing another operation. You
 *                     can try again later.
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: The arguments passed are invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOSYS: The operation failed at the stack level.
 *         - @c EPROTO: The operation failed because the response from remote
 *                      Bluetooth-enabled device had a protocol error.
 *         - @c ESRCH: The service connection was not available.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_enable_indicate(int instance, const bt_gatt_characteristic_t *characteristic, uint8_t enable);

/**
 * @brief Initialize resources required for Generic Attribute (GATT)
 * @details The function also starts a new thread. Most callbacks invoked in
 *          the new thread are thread safe unless otherwise specified. You must
 *          call this function before calling any other functions in this file.
 *
 * @param cb The list of callbacks to be used for GATT Connection Manager
 *           callbacks.
 * @return @c EOK when the initialization is successful, @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c EACCESS:  Insufficient permissions to initialize functionality.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOTSUP: The current library version is not supported.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_init(bt_gatt_callbacks_t *cb);

/**
 * @brief Clean up resources that were initialized for Generic Attribute
 *        (GATT)
 * @details This function also stops the event loop that was started by the
 *          the @c bt_gatt_init() function. You should call this function when
 *          GATT functionality is no longer required in your application.
 */
void bt_gatt_deinit();

/**
 * @cond
 * For internal use only. Do not use.
 * The following are prototypes that are used for the initialization function.
 * This function passes the version information as an argument so that it is
 * possible to determine the version an application was compiled with.
 */
int _bt_gatt_init(bt_gatt_callbacks_t *cb, uint32_t version);
#define bt_gatt_init(callbacks) _bt_gatt_init(callbacks, BT_GATT_VERSION)
/** @endcond */



__END_DECLS
#endif /* _BTGATT_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
