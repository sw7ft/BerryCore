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

/**
 * @file btgattsrv.h
 *
 * @brief Functions and structures that provide Bluetooth Generic Attribute
 *        Profile (GATT) server functions to communicate with a GATT server.
 *
 * This file defines functions to work with Bluetooth capabilities on classic
 * and low-energy devices. Before you use functions from this file, you must
 * call the @c bt_gatt_srv_init() function. You must call the
 * @c bt_gatt_srv_deinit() function when GATT functionality is no longer
 * required in your application.
 *
 */



#ifndef _BTGATTSRV_H_
#define _BTGATTSRV_H_

#include <stdint.h>
#include <stdbool.h>
/**
 * The Bluetooth Generic Attribute (GATT) server API version.
 * For example, the value @c 0x00000900 translates to 0000.09.00 or v0.9.0.
 */
#define BT_GATT_SRV_VERSION         0x00010000

/** Bluetooth low energy server attribute type */
typedef enum {

    /**
     * GATT service entry.
     */
    BT_GATT_SRV_ATT_SERVICE          = 0x01,

    /**
     * GATT characteristic entry.
     */
    BT_GATT_SRV_ATT_CHARACTERISTICS  = 0x02,

    /**
     * GATT descriptor entry.
     */
    BT_GATT_SRV_ATT_DESCRIPTOR       = 0x03,

    /**
     * GATT included service entry.
     */
    BT_GATT_SRV_ATT_INCLUDE_SERVICE  = 0x04,
} bt_gatt_srv_att_type_t;

/**
 * GATT attribute data type.
 */
typedef enum {

    /**
     * A value indicating that neither readable nor writeable value is used. This value
     * is used for services that do not have associated data.
     */
    BT_GATT_SRV_ATT_VALUE_NONE       = 0x00,

    /**
     * Static value.  The data must be populated at the time that the service is created.
     */
    BT_GATT_SRV_ATT_VALUE_STATIC     = 0x01,

    /**
     * Dynamic value.  Callbacks will be triggered for all read/write operations.
     */
    BT_GATT_SRV_ATT_VALUE_DYNAMIC    = 0x02,

    /**
     * Volatile value. The data is only populated at the time that the service is
     * created. The remote device is allowed to read or write to this value if
     * permission allows.  The @c bt_gatt_srv_write_alert_cb or
     * @c bt_gatt_srv_read_alert_cb callback is invoked when the remote device
     * performs a read or write operation.
     */
    BT_GATT_SRV_ATT_VALUE_VOLATILE   = 0x03,
} bt_gatt_srv_att_value_t;

/**
 * GATT service type.
 */
typedef enum {

    /**
     * Secondary service type.
     */
    BT_GATT_SRV_ATT_SECONDARY_SERVICE  = 0x00,

    /**
     * Primary service type.
     */
    BT_GATT_SRV_ATT_PRIMARY_SERVICE    = 0x01,
} bt_gatt_srv_att_service_t;

/**
 * The bitmask to indicate properties of a characteristic.
 */
typedef uint8_t bt_gatt_srv_att_properties_t;

/**
 * Allow for the broadcasting of Generic Attributes(GATT) characteristic values.
 */
#define BT_GATT_SRV_ATT_PROPERTY_BROADCAST 0x01

/**
 * Allow the characteristic values to be read.
 */
#define BT_GATT_SRV_ATT_PROPERTY_READ 0x02

/**
 * Allow characteristic values without responses to be written.
 */
#define BT_GATT_SRV_ATT_PROPERTY_WRITE_NORESP 0x04

/**
 * Allow for characteristic values to be written.
 */
#define BT_GATT_SRV_ATT_PROPERTY_WRITE 0x08

/**
 * Permit notification of characteristic values.
 */
#define BT_GATT_SRV_ATT_PROPERTY_NOTIFY 0x10

/**
 * Permit indications of characteristic values.
 */
#define BT_GATT_SRV_ATT_PROPERTY_INDICATE 0x20

/**
 * Permit signed writes of the GATT characteristic values.
 */
#define BT_GATT_SRV_ATT_PROPERTY_WRITE_SIGNED 0x40

/**
 * Additional characteristic properties are defined in the characteristic
 * extended properties descriptor.
 */
#define BT_GATT_SRV_ATT_PROPERTY_EXT_PROP 0x80

/**
 * The bitmask to indicate required permissions for attributes.
 */
typedef uint16_t bt_gatt_srv_att_permissions_t;

/**
 * Flag that when set, indicates that no permission is required.
 */
#define BT_GATT_SRV_ATT_PERMISSION_NONE                0x0000

/**
 * Flag that indicates whether the client is allowed to write to an attribute on the server.
 */
#define BT_GATT_SRV_ATT_PERMISSION_WRITEABLE           0x0001

/**
 * Flag that indicates whether the client is allowed to read an attribute from the server.
 */
#define BT_GATT_SRV_ATT_PERMISSION_READABLE            0x0002

/**
 * Flag that indicates whether authentication is required to write to the attribute on the server.
 * If this flag is set, @c GATT_SRV_ATT_PERMISSION_WRITEABLE must also be set.
 */
#define BT_GATT_SRV_ATT_PERMISSION_AUTHEN_REQ_WRITE    0x0004

/**
 * Flag that indicates whether authentication is required to read an attribute from the server or
 * to receive notification or indication events from the server. If this flag is set,
 * @c GATT_SRV_ATT_PERMISSION_READABLE must also be set.
 */
#define BT_GATT_SRV_ATT_PERMISSION_AUTHEN_REQ_READ     0x0008

/**
 * Flag that indicates whether Man In The Middle (MITM) protection is required to write to an
 * attribute on the server. If this value is not set, then no MITM protection is required and
 * the Just Works security model is used. If this value is set, @c GATT_SRV_ATT_PERMISSION_WRITEABLE
 * and @c GATT_SRV_ATT_PERMISSION_AUTHEN_REQ_WRITE must also be set.
 */
#define BT_GATT_SRV_ATT_PERMISSION_MITM_WRITE          0x0010

/**
 * Flag that indicates whether Man In The Middle (MITM) protection is required to read from
 * an attribute on the server or to receive notification or indication events about an attribute
 * from the server. If this flag is not set, then no MITM protection is required and the
 * Just Works security model is used. If this flag is set, @c GATT_SRV_ATT_PERMISSION_READABLE and
 * @c GATT_SRV_ATT_PERMISSION_AUTHEN_REQ_READ must also be set.
 */
#define BT_GATT_SRV_ATT_PERMISSION_MITM_READ           0x0020

/**
 * Flag reserved for future use
 */
#define BT_GATT_SRV_ATT_PERMISSION_RESERVED_1          0x0040

/**
 * Flag reserved for future use
 */
#define BT_GATT_SRV_ATT_PERMISSION_RESERVED_2          0x0080

/**
 * Possible Attribute Protocol (ATT) error codes that may be used in read/write responses.
 */
typedef enum {

    /**
     * No errors
     */
    BT_ATT_ERROR_NONE                           = 0x00,

    /**
     * The attribute handle given is not valid on this server.
     */
    BT_ATT_ERROR_INVALID_HANDLE                 = 0x01,

    /**
     * The attribute cannot be read.
     */
    BT_ATT_ERROR_READ_NOT_PERMITTED             = 0x02,

    /**
     * The attribute cannot be written to.
     */
    BT_ATT_ERROR_WRITE_NOT_PERMITTED            = 0x03,

    /**
     * The attribute Protocol Data Unit (PDU) was invalid.
     */
    BT_ATT_ERROR_INVALID_PDU                    = 0x04,

    /**
     * The attribute requires authentication before it can be read or written to.
     */
    BT_ATT_ERROR_INSUFFICIENT_AUTHENTICATION    = 0x05,

    /**
     * The attribute server does not support the request received from the client.
     */
    BT_ATT_ERROR_REQUEST_NOT_SUPPORTED          = 0x06,

    /**
     * Offset specified was past the end of the attribute.
     */
    BT_ATT_ERROR_INVALID_OFFSET                 = 0x07,

    /**
     * The attribute requires authorization before it can be read or written to.
     */
    BT_ATT_ERROR_INSUFFICIENT_AUTHORIZATION     = 0x08,

    /**
     * Too many prepare writes have been queued.
     */
    BT_ATT_ERROR_PREPARE_QUEUE_FULL             = 0x09,

    /**
     * No attribute found within the given attribute handle range.
     */
    BT_ATT_ERROR_ATTRIBUTE_NOT_FOUND            = 0x0A,

    /**
     * The attribute cannot be read or written to using the Read Blob Request.
     */
    BT_ATT_ERROR_ATTRIBUTE_NOT_LONG             = 0x0B,

    /**
     * The encryption key size used for encrypting this link is insufficient.
     */
    BT_ATT_ERROR_INSUFFICIENT_ENCRYPT_KEY_SIZE  = 0x0C,

    /**
     * The attribute value length is invalid for the operation.
     */
    BT_ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH = 0x0D,

    /**
     * The attribute request that was requested has encountered an error that
     * was unlikely, and therefore could not be completed as requested.
     */
    BT_ATT_ERROR_UNLIKELY_ERROR                 = 0x0E,

    /**
     * The attribute requires encryption before it can be read or written to.
     */
    BT_ATT_ERROR_INSUFFICIENT_ENCRYPTION        = 0x0F,

    /**
     * The attribute type is not a supported grouping attribute as defined by a
     * higher layer specification.
     */
    BT_ATT_ERROR_UNSUPPORTED_GROUP_TYPE         = 0x10,

    /**
     * Insufficient resources to complete the request.
     */
    BT_ATT_ERROR_INSUFFICIENT_RESOURCES         = 0x11,

    /**
     * Generic application error. Specific application error codes defined by an
     * application should be in the range of 0x80 - 0xFF.
     */
    BT_ATT_ERROR_GENERIC_APPLICATION_ERROR      = 0x80,
} bt_gatt_srv_att_error_t;

/**
 * The callback prototype to indicate that @c bt_gatt_srv_send_notification_async has completed.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute for which the notification was sent.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_srv_send_notification_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, void *user_data);

/**
 * The callback prototype to indicate that @c bt_gatt_srv_send_indication_async has completed.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute for which the notification was sent.
 * @param error Set to @c #BT_ATT_ERROR_NONE if indication was successful, otherwise indicate
 *              the error that has occurred.
 * @param user_data The pointer to be returned when the callback is executed.
 */
typedef void (*bt_gatt_srv_send_indication_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, bt_gatt_srv_att_error_t error, void *user_data);

/**
 * The callback prototype to indicate a device has connected to the GATT server.
 *
 * @param instance The identifier used to reference the service connection.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param connInt The negotiated connection interval for the service. Only use
 *                this argument for low-energy devices.  For BR/EDR devices this
 *                value will be zero.
 * @param latency The negotiated latency for the service. Only use
 *                this argument for low-energy devices.  For BR/EDR devices this
 *                value will be zero.
 * @param superTimeout The negotiated supervisor timeout for the connection.
 *                     Use this argument only for low-energy devices.  For BR/EDR
 *                     devices this value will be zero.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_connected_cb) (int instance, const char *bdaddr,
        uint8_t type, uint16_t connInt, uint16_t latency, uint16_t superTimeout, void *userData);

/**
 * The callback prototype to indicate that link parameters have been updated for the
 * specific connection to the GATT server.  This callback will only occur on
 * low-energy links.
 *
 * @param instance The identifier used to reference the service connection.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param connInt The new negotiated connection interval for the service.
 * @param latency The new negotiated latency for the service.
 * @param superTimeout The new negotiated supervisor timeout for the connection.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_updated_cb) (int instance, const char *bdaddr,
        uint8_t type, uint16_t connInt, uint16_t latency, uint16_t superTimeout, void *userData);

/**
 * The callback prototype to indicate a device has disconnected from the GATT server.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_disconnected_cb) (int instance, const char *bdaddr, uint8_t type, void *userData);

/**
 * The callback prototype to indicate that a remote device has performed a write operation on the given handle
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute which is being written to.
 * @param val A pointer to the data sent in the notification.
 * @param len The length of data sent.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_write_alert_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, uint8_t *val, uint16_t len, void *userData);

/**
 * @brief This definition has been deprecated
 * @deprecated BlackBerry 10.3.0. Use @c bt_gatt_srv_write_request_cb instead.
 * @details A call to @c bt_gatt_srv_send_write_rsp() must be made to accept/reject the request.
 *          This can either be done from within or outside the callback.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute which is being written to.
 * @param val A pointer to the data sent in the request.
 * @param len The length of data sent.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_write_req_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, uint8_t *val, uint16_t len, void *userData);

/**
 * @brief The callback prototype to indicate that a remote device has requested to write data
 *        to the given handle
 * @details If the write requires a response indicated by @c needRsp, then you must call
 *          @c bt_gatt_srv_send_write_rsp() to accept or reject the request.
 *          This can be done from either within or outside the callback.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute which is being written to.
 * @param offset The offset where the write should be performed.
 * @param needRsp If @c true, a response is needed.  Call @c bt_gatt_srv_send_write_rsp().
 * @param val A pointer to the data sent in the request.
 * @param len The length of data sent.
 * @param userData A pointer to the user data that was passed in during the connection request.
 */
typedef void (*bt_gatt_srv_write_request_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, uint8_t offset, bool needRsp, uint8_t *val, uint16_t len, void *userData);

/**
 * The callback prototype to indicate that a remote device has performed a read operation on the given handle.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute which is being read from.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_read_alert_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, void *userData);

/**
 * @brief This definition has been deprecated.
 * @deprecated BlackBerry 10.3.0.  Use @c bt_gatt_srv_read_request_cb instead.
 * @details A call to @c bt_gatt_srv_send_read_rsp() must be made to accept/reject the request.
 *          This can either be done from within or outside the callback.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute which is being read from.
 * @param len The length of data that is being requested.
 * @param userData Pointer to user data passed in during the connection request.
 */
typedef void (*bt_gatt_srv_read_req_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, uint16_t len, void *userData);

/**
 * @brief The callback prototype to indicate that a remote device has requested to read data
 *        from the given handle
 * @details You must call @c bt_gatt_srv_send_read_rsp() to accept or reject the request.
 *          This can be done from either within or outside the callback.
 *
 * @param instance The identifier used to reference the service.
 * @param bdaddr  The address of the remote Bluetooth device.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute which is being read from.
 * @param offset The offset where the read should be performed.
 * @param len The length of data that is being requested.
 * @param userData A pointer to the user data that was passed in during the connection request.
 */
typedef void (*bt_gatt_srv_read_request_cb) (int instance, const char *bdaddr, uint8_t type, uint16_t handle, uint16_t offset, uint16_t len, void *userData);


/**
 * A structure that contains the list of callbacks to be used for service
 * read/write operations.
 */
typedef struct {
    /**
     * The callback that indicates that a remote device has connected to the server.
     */
    bt_gatt_srv_connected_cb connected;
    /**
     * The callback that indicates that the link parameters of the remote device
     * have been updated to the server.
     */
    bt_gatt_srv_updated_cb updated;
    /**
     * The callback that indicates that a remote device has disconnected from the server.
     */
    bt_gatt_srv_disconnected_cb disconnected;
    /**
     * The callback that indicates that a remote device has written to an attribute.
     */
    bt_gatt_srv_write_alert_cb write_alert;
    /**
     * @deprecated BlackBerry 10.3.0  Use @write_request instead
.     */
    bt_gatt_srv_write_req_cb write_req;
    /**
     * The callback that indicates that a remote device has read an attribute.
     */
    bt_gatt_srv_read_alert_cb read_alert;
    /**
     * @deprecated BlackBerry 10.3.0. Use @read_request instead.
     */
    bt_gatt_srv_read_req_cb read_req;

    /**
     * The callback that indicates that a remote device is requesting to write to an attribute.
     */
    bt_gatt_srv_write_request_cb write_request;
    /**
     * The callback that indicates that a remote device is requesting to read an attribute.
     */
    bt_gatt_srv_read_request_cb read_request;

} bt_gatt_srv_service_cb;

/**
 * A generic structure used to create the GATT service
 */
typedef struct {

    /**
     * The UUID is represented as a NULL-terminated string value. An example of the string
     * representation for GATT services is 0x1435. The 128-bit UUID is traditionally represented
     * as 0xF0000000-0451-4000-B000-000000000000.
     */
    char service[39];

    /**
     * The handle value for this attribute.  This value should start
     * at zero for the primary service and increment for each attribute.
     * @note Characteristics use an extra handle for the valueHandle.
     */
    uint16_t handle;

    /**
     * Attribute entry type stored in @c dcl.
     */
    bt_gatt_srv_att_type_t attrType;

    /**
     * Details of the attribute.
     */
    union{
        /**
         * Used to hold data for a @c GATT_SRV_ATTRIB_SERVICE entry type.
         */
        struct {

            /**
             * The total number of attributes in the service (including the service).
             */
            uint16_t cnt;

            /**
             * The desired starting handle for the given service.  If set to
             * zero then the starting handle will be automatically assigned.
             */
            uint16_t startHandle;

            /**
             * The number of handles to allocate for this service.
             */
            uint16_t numHandles;

            /**
             * The type of service.
             */
            bt_gatt_srv_att_service_t type;

            /**
             * Set to 1 to include the service in SDP record for classic links.  This should
             * be set only if the type of service is set to @c GATT_SRV_ATTRIB_PRIMARY_SERVICE.
             * @note If a name is provided for the SDP record, it must be provided in the
             * @c value structure with the @c valueType set to @c GATT_SRV_ATTRIB_VALUE_STATIC.
             * The maximum size of the name is 255 bytes.
             */
            uint8_t useSDP;
        } service;

        /**
         * Used to hold data for a @c GATT_SRV_ATTRIB_INCLUDE_SERVICE entry type.
         */
        struct {

            /**
             * The UUID of the included service represented as a
             * NULL-terminated string value. An example of the string
             * representation for GATT services is 0x1435. The 128-bit UUID is
             * traditionally represented as
             * 0xF0000000-0451-4000-B000-000000000000.
             */
            char service[39];

            /**
             * The handle of the service to be included in the current service.
             */
            uint16_t incServiceHandle;

            /**
             * The handle of the last attribute of the included service.
             */
            uint16_t endGroupHandle;

        } include;

        /**
         * Used to hold data for a @c GATT_SRV_ATTRIB_CHARACTERISTIC entry type.
         */
        struct {
            /**
             * Bitmask representing the properties of the characteristic.
             */
            bt_gatt_srv_att_properties_t properties;

            /**
             * The permissions to access this characteristic.
             */
            bt_gatt_srv_att_permissions_t permission;

            /**
             * Encryption key size for the attribute. Valid range is 7 to 16 bytes;
             * 0 indicates no key is required.
             */
            uint8_t encryptKeySize;

            /**
             * The value handle of the data for the characteristic.  This handle will be passed in
             * the callback if the data type for this attribute is @c GATT_SRV_ATTRIB_DATA_DYNAMIC.
             */
            uint16_t valueHandle;
        } characteristic;

        /**
         * Used to hold data for a @c GATT_SRV_ATTRIB_DESCRIPTOR entry type.
         */
        struct {
            /**
             * The permissions to access this descriptor.
             */
            bt_gatt_srv_att_permissions_t permission;

            /**
             * Encryption key size for the attribute. Valid range is 7 to 16 bytes;
             * 0 indicates no key is required.
             */
            uint8_t encryptKeySize;

        } descriptor;
    } dcl;

    /**
     * The type of data stored in @c value.  For @c GATT_SRV_ATTRIB_SERVICE types, this is set to
     * @c GATT_SRV_ATTRIB_DATA_NONE.
     */
    bt_gatt_srv_att_value_t valueType;

    /**
     * Details of dynamic, static, or volatile data stored.
     */
    union {
        /**
         * Used to represent dynamic value when @c dataType is set to @c GATT_SRV_ATTRIB_DATA_DYNAMIC.
         * Callbacks are invoked to retrieve the data from the application on read/write operations.
         */
        struct {
            /**
             * The current length of the value.  This must be less than or equal to @c maxValueLen.
             */
            uint16_t valueLen;
            /**
             * The maximum allowable size of the data to be retrieved.
             */
            uint16_t maxValueLen;
        } dyn;

        /**
         * Used to represent the static value when @c dataType is set to @c GATT_SRV_ATTRIB_DATA_STATIC.  This is the
         * value that is returned when read/write operations are performed.
         */
        struct {
            /**
             * The size of the static value to be included.
             */
            uint16_t valueLen;
            /**
             * Pointer to the static value.
             */
            uint8_t *value;
        } sta;

        /**
         * Used to represent the volatile value when @c dataType is set to
         * @c GATT_SRV_ATTRIB_DATA_VOLATILE.  This is the initial value that
         * will be returned when a read operation is performed.
         */
        struct {
            /**
             * The size of the volatile value to be included.
             */
            uint16_t valueLen;
            /**
             * The maximum allowable size of the data to be retrieved.
             */
            uint16_t maxValueLen;
            /**
             * Pointer to the volatile value.
             */
            uint8_t *value;
        } vol;
    }value;
} bt_gatt_srv_attrvalue_t;

/**
 * Structure to represent the update connection parameters for a low energy (LE) link.
 */
typedef struct {
    /**
     * Minimum value for the connection interval.
     * - Range: 0x0006 to 0x0C80
     * - Time = N * 1.25 msec
     * - Time range: 7.5 msec to 4 seconds
     */
    uint16_t minConn;

    /**
     * Maximum value for the connection interval.
     * - Range: 0x0006 to 0x0C80
     * - Time = N * 1.25 msec
     * - Time range: 7.5 msec to 4 seconds
     */
    uint16_t maxConn;
    /**
     * Slave latency for the connection.
     * - Range: 0x0000 to 0x01F4
     */
    uint16_t latency;
    /**
     * Supervision timeout for the LE link. Value must satisfy
     * the following condition: (superTimout > (1 + latency ) * maxConn).
     * - Range: 0x000A to 0x0C80
     * - Time = N * 10 msec
     * - Time range: 100 msec to 32 seconds
     */
    uint16_t superTimeout;

} bt_gatt_srv_update_parm_t;

__BEGIN_DECLS

/**
 * @brief Send the response to a read request
 * @details This can be performed within the @c bt_gatt_srv_read_request_cb()
 *          callback function or from another thread.
 *
 * @param instance The instance number representing the local GATT service.
 * @param addr The address of the remote device which the response is to be sent to.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute that the response is for.
 * @param error Set to @c #BT_ATT_ERROR_NONE if value is valid, otherwise indicate
 *              the error that has occurred.
 * @param value The binary data to be sent back to the remote device.
 * @param len The length of data to be sent back to the remote device.
 *
 * @return @c EOK on a successful response to the remote device, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_send_read_rsp (int instance, const char *addr, uint8_t type, uint16_t handle, bt_gatt_srv_att_error_t error, const uint8_t *value, uint16_t len);

/**
 * @brief Send the response to a write request
 * @details This can be performed within the @c bt_gatt_srv_write_request_cb()
 *          callback function or from another thread.
 *
 * @param instance The instance number representing the local GATT service.
 * @param addr The address of the remote device which the response is to be sent to.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute that the response is for.
 * @param error Set to @c #BT_ATT_ERROR_NONE if the write was successful, otherwise
 *              indicate the error that has occurred.
 *
 * @return @c EOK on a successful response to the remote device, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_send_write_rsp (int instance, const char *addr, uint8_t type, uint16_t handle, bt_gatt_srv_att_error_t error);

/**
 * @brief Send a notification to the remote device.
 * @details If you are using a software version before BlackBerry 10.3.0, you must call
 *          @c bt_gatt_srv_set_keepalive() prior to calling this function.
 *
 * @param instance The instance number representing the local GATT service.
 * @param addr The address of the remote device which the notification is to be sent to.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute that the notification belongs to.
 * @param val The binary data being sent in the notification.
 * @param len The length of the data to be sent in the notification.
 *
 * @return @c EOK on a successful notification to the remote device, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EDEADLK:    A potential deadlock has been avoided.
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ENOTCONN:   The keep-alive is required prior to calling this function.
 *                          See @c bt_gatt_srv_set_keepalive().
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_send_notification(int instance, const char *addr, uint8_t type, uint16_t handle, const uint8_t *val, uint16_t len);

/**
 * @brief Send a notification asynchronously to the remote device.
 *
 * @param instance The instance number representing the local GATT service.
 * @param addr The address of the remote device which the notification is to be sent to.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute that the notification belongs to.
 * @param val The binary data being sent in the notification.
 * @param len The length of the data to be sent in the notification.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 *
 * @return @c EOK on a successful notification to the remote device, otherwise,
 *         @c -1 with the @c errno set. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EDEADLK:    A potential deadlock has been avoided.
 *         - @c EINVAL:     An argument is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Sufficient memory was not available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_send_notification_async(int instance, const char *addr,
        uint8_t type, uint16_t handle, const uint8_t *val, uint16_t len,
        bt_gatt_srv_send_notification_cb cb, void *user_data);

/**
 * @brief Send an indication to the remote device.
 * @details If you are using a software version before BlackBerry 10.3.0, you must call
 *          @c bt_gatt_srv_set_keepalive() prior to calling this function.
 *
 * @param instance The instance number representing the local GATT service.
 * @param addr The address of the remote device which the indication is to be sent to.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute that the indication belongs to.
 * @param val The binary data being sent in the indication.
 * @param len The length of the data to be sent in the indication.
 *
 * @return @c EOK on a successful indication to the remote device, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EDEADLK:    A potential deadlock has been avoided.
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ENOTCONN:   The keep-alive is required prior to calling this function.
 *                          See @c bt_gatt_srv_set_keepalive().
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_send_indication(int instance, const char *addr, uint8_t type, uint16_t handle, const uint8_t *val, uint16_t len);

/**
 * @brief Send an indication asynchronously to the remote device.
 *
 * @param instance The instance number representing the local GATT service.
 * @param addr The address of the remote device which the indication is to be sent to.
 * @param type The device type identifier.  Refer to constants prefixed with
 *             @c BT_DEVICE_TYPE_.
 * @param handle The handle of the attribute that the indication belongs to.
 * @param val The binary data being sent in the indication.
 * @param len The length of the data to be sent in the indication.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 *
 * @return @c EOK on a successful indication to the remote device, otherwise,
 *         @c -1 with the @c errno set. The error codes that can be
 *         returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EINVAL:     An argument is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Sufficient memory was not available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_send_indication_async(int instance, const char *addr, uint8_t type,
        uint16_t handle, const uint8_t *val, uint16_t len,
        bt_gatt_srv_send_indication_cb cb, void *user_data);

/**
 * @brief Retrieve the service's starting and ending handles in the GATT server.
 *
 * @param instance    The instance number representing the local GATT service
 * @param startHandle A pointer to a buffer where the starting handle in the
 *                    GATT server is to be written.
 * @param endHandle   A pointer to a buffer where the ending handle in the GATT
 *                    server is to be written.
 *
 * @return @c EOK when the handles are successfully retrieved, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */

int bt_gatt_srv_get_service_handles( int instance, uint16_t *startHandle, uint16_t *endHandle);

/**
 * @brief Request to enable or disable a connection keep-alive to the remote device
 * @details This function should only be used when the service that enables it knows
 *        that the connection to the remote device must remain active. If the
 *        keep-alive is enabled, the GATT connection will remain open until either
 *        the keep-alive is disabled or the remote device closes the connection.
 *        Caution should be used to ensure that the keep-alive is used for services
 *        that are actively used by the remote device; otherwise the connection may
 *        remain open and never disconnect.
 *
 * @param instance    The instance number representing the local GATT service.
 * @param addr        The address of the remote device to which the connection
 *                    update request is to be sent.
 * @param type        The device type identifier.  Refer to constants prefixed with
 *                    @c BT_DEVICE_TYPE_.
 * @param enabled     A value of @c 1 will enable notification support.  A value
 *                    of @c 0 will disable notification support.
 *
 * @return @c EOK when notification support is successfully enabled, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENOTSUP:    The request is being made on a BR/EDR connection,
 *                          which is not supported.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ENOTCONN:   The keep-alive is currently disabled.
 *         - @c EBUSY:      The keep-alive is already enabled.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_set_keepalive( int instance, const char *addr, uint8_t type, uint8_t enabled);

/**
 * @brief Retrieve the Attribute Protocol Maximum Transmit Unit (ATT_MTU) for
 *        the given connection
 *
 * @param instance The identifier used to reference the local service
 * @param addr     The address of the remote device to which the connection
 *                 update request is to be sent.
 * @param type     The device type identifier.  Refer to constants prefixed with
 *                 @c BT_DEVICE_TYPE_.
 * @return The MTU value for the given instance when the function is completed
 *         successfully, @c -1 with the @c errno set otherwise. The error codes
 *         that can be returned are as follows:
 *         - @c EDEADLK: A potential deadlock has been avoided.
 *         - @c EINVAL: An argument passed is invalid or the connection to
 *                      the remote Bluetooth-enabled device is unavailable.
 *         - @c ENODEV: Unable to find the service connection defined by the
 *                      @c instance argument.
 *         - @c ENOMEM: Insufficient memory was available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_get_mtu(int instance, const char *addr, uint8_t type);

/**
 * @brief Request an update to the low-energy connection parameters
 * @details The @c bt_gatt_srv_updated_cb() callback is invoked if the connection
 *          parameters change.
 *
 *          This function should be used with care.  Modifying the link connection
 *          parameters will affect all GATT servers and clients using the low-energy
 *          link.  Use this function only to obtain a faster response time, or
 *          only when you know that changing the connection interval will not
 *          impact another application.
 *
 * @param instance    The instance number representing the local GATT service.
 * @param addr        The address of the remote device to which the connection
 *                    update request is to be sent.
 * @param type        The device type identifier. Refer to constants prefixed with
 *                    @c BT_DEVICE_TYPE_.
 * @param parms       The desired connection parameters for the low-energy link.
 *
 * @return @c EOK when the handles are successfully retrieved, otherwise
 *         @c -1 with the @c errno set otherwise. The error codes that can be
 *         returned are as follows:
 *         - @c EINVAL:     An argument passed is invalid or the connection to
 *                          the remote Bluetooth-enabled device is unavailable.
 *         - @c ENOTSUP:    The request is being made on a BR/EDR connection,
 *                          which is not supported.
 *         - @c ENODEV:     Unable to find the service connection defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_update_connection( int instance, const char *addr, uint8_t type, bt_gatt_srv_update_parm_t *parms);

/**
 * @brief Helper function to validate the service record being passed to @c bt_gatt_srv_register_service.
 *
 * @details This function can be used prior to calling @c bt_gatt_srv_register_service()
 *          to verify that the information in the @c #bt_gatt_srv_attrvalue_t
 *          structure is populated correctly. The @c errstr will be populated with a
 *          descriptive string if @c EINVAL is returned.
 *
 * @param service The GATT service to be validated.
 * @param errstr (Optional) String to provide details on failure.
 * @param len Length of @c errstr.  Set to 0 if @c errstr is not used.
 *
 * @return @c EOK if service validation passes, @c -1 with the @c errno
 *         set otherwise. The error codes that can be returned are as follows:
 *         - @c EINVAL: The service provided has errors.  The @c errstr
 *                      argument will contain a description of the error if
 *                      provided.
 */
int bt_gatt_srv_validate_service(bt_gatt_srv_attrvalue_t *service, char *errstr, uint16_t len);

/**
 * @brief Register a local service with the Generic Attribute (GATT) server
 *
 * @param service An array of @c bt_gatt_attrvalue_t objects representing the
 *                GATT services to register.
 *                For example, you may want to define a service with a private
 *                UUID that mimics an Immediate Alert Service. In this case by
 *                setting the @c cnt attribute of the first array element to a
 *                value of @c 3 you tell @c bt_gatt_srv_register_service() that
 *                there are three instances of bt_gatt_srv_attrvalue_t in the
 *                registration, one for the primary service and one for each
 *                attribute. The following code sample illustrates this example:
 * @code
 * bt_gatt_srv_attrvalue_t _myService[3];
 * strlcpy(_myService[0].service,
 *      "0x3759E92B-4E2C-4EFD-97B5-BEDF474A1C56", sizeof(_myService[0].service));
 * _myService[0].handle = 0;
 * _myService[0].attrType = BT_GATT_SRV_ATT_SERVICE;
 * _myService[0].dcl.service.cnt = 3;
 * _myService[0].dcl.service.startHandle = 0;
 * _myService[0].dcl.service.numHandles = 4;
 * _myService[0].dcl.service.type = BT_GATT_SRV_ATT_PRIMARY_SERVICE;
 * _myService[0].dcl.service.useSDP = 1;
 * _myService[0].valueType = BT_GATT_SRV_ATT_VALUE_STATIC;
 * _myService[0].value.sta.valueLen = 19;
 * _myService[0].value.sta.value = (uint8_t *)"My Immediate Alert";
 *
 * strlcpy(_myService[1].service, "0x2A06", sizeof(_myService[0].service));
 * _myService[1].handle = 1;
 * _myService[1].attrType = BT_GATT_SRV_ATT_CHARACTERISTICS;
 * _myService[1].dcl.characteristic.properties = BT_GATT_SRV_ATT_PROPERTY_WRITE_NORESP;
 * _myService[1].dcl.characteristic.permission = BT_GATT_SRV_ATT_PERMISSION_WRITEABLE;
 * _myService[1].dcl.characteristic.encryptKeySize = 0;
 * _myService[1].dcl.characteristic.valueHandle = 2;
 * _myService[1].valueType = BT_GATT_SRV_ATT_VALUE_DYNAMIC;
 * _myService[1].value.dyn.valueLen = 1;
 * _myService[1].value.dyn.maxValueLen = 1;
 *
 * strlcpy(_myService[2].service, "0x2901", sizeof(_myService[0].service));
 * _myService[2].handle = 3;
 * _myService[2].attrType = BT_GATT_SRV_ATT_DESCRIPTOR;
 * _myService[2].dcl.descriptor.permission = BT_GATT_SRV_ATT_PERMISSION_READABLE;
 * _myService[2].dcl.descriptor.encryptKeySize = 0;
 * _myService[2].valueType = BT_GATT_SRV_ATT_VALUE_STATIC;
 * _myService[2].value.sta.valueLen = 12;
 * _myService[2].value.sta.value = (uint8_t *)"Alert Level";
 * @endcode
 *
 * @param cb The callbacks to call when read/write operations are performed on
 *           this service.
 * @param userData (Optional) Pointer to user data that will be passed back
 *                 during event callbacks.
 *
 * @return The @c instance representing the service, @c -1 with the @c errno
 *         set otherwise. The error codes that can be returned are as follows:
 *         - @c EBUSY:      The stack was busy performing another operation. You
 *                          can try again later.
 *         - @c EDEADLK:    A potential deadlock has been avoided.
 *         - @c EINVAL:     An argument passed is invalid.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_register_service(bt_gatt_srv_attrvalue_t *service, bt_gatt_srv_service_cb *cb, void *userData);

/**
 * @brief Deregister the local service from the Generic Attribute (GATT) server
 *
 * @param instance The identifier used to reference the service.
 *
 * @return @c EOK when the service is successfully deregistered, @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c EDEADLK:    A potential deadlock has been avoided.
 *         - @c ENODEV:     Unable to find the local service defined by the
 *                          @c instance argument.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_deregister_service(int instance);

/**
 * @brief Initialize resources required for the Generic Attribute (GATT) server
 * @details The function also starts a new thread. Most callbacks invoked in
 *          the new thread are thread safe unless otherwise specified. You must
 *          call this function before calling any other functions in this file.
 *
 * @return @c EOK when the initialization is successful, @c -1 with the
 *         @c errno set otherwise. The error codes that can be returned are as
 *         follows:
 *         - @c EACCESS:    Insufficient permissions to initialize functionality.
 *         - @c ENOMEM:     Insufficient memory was available to perform the
 *                          request.
 *         - @c ENOTSUP:    The current library version is not supported.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_gatt_srv_init( void );

/**
 * @brief Clean up resources that were initialized for Generic Attribute (GATT)
 *        server
 * @details This function also stops the event loop that was started by the
 *          the @c bt_gatt_srv_init() function. You should call this function when
 *          GATT functionality is no longer required in your application.
 */
void bt_gatt_srv_deinit( void );

/**
 * @cond
 * For internal use only. Do not use.
 * The following are prototypes that are used for the initialization function.
 * This function passes the version information as an argument so that it is
 * possible to determine the version an application was compiled with.
 */
int _bt_gatt_srv_init( uint32_t version);
#define bt_gatt_srv_init() _bt_gatt_srv_init( BT_GATT_SRV_VERSION )
/** @endcond */



__END_DECLS
#endif /* _BTGATT_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
