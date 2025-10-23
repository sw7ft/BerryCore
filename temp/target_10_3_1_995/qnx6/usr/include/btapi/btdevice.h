/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
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
 * @file btdevice.h
 *
 * @brief Functions, enumerations, and structures to work with Bluetooth-enabled
 *        devices
 *
 * Before you use functions from this file, you must call the @c
 * bt_device_init() function. You must call the @c bt_device_deinit() function
 * when Bluetooth functionality is no longer required in your application.
 *
 */

#ifndef BTDEVICE_H_
#define BTDEVICE_H_

#include <stdbool.h>    /* required to use bool declaration    */
#include <stdint.h>     /* required to use uint_t* declarations  */

/**
 * An enumeration that represents various discoverable and connectable modes
 * that can be used during the inquiry procedure. The inquiry procedure is the
 * process of discovering other Bluetooth-enabled devices that are within range.
 */
typedef enum {
    /**
     * Unknown. This value occurs when discovery fails.
     */
    BT_DISCOVERABLE_UNKNOWN = -1,
    /**
     * Not discoverable or connectable.
     */
    BT_DISCOVERABLE_NONE = 0,
    /**
     * General Inquiry Access Code (GIAC). Generally discoverable and connectable.
     */
    BT_DISCOVERABLE_GIAC = 1,
    /**
     * Limited Inquiry Access Code (LIAC). Limited discoverability but
     * connectable.
     */
    BT_DISCOVERABLE_LIAC = 2,
    /**
     * Connectable but not discoverable.
     */
    BT_DISCOVERABLE_CONNECTABLE = 3,
    /**
     * Discoverable but not connectable.
     */
    BT_DISCOVERABLE_DISCOVERABLE = 4
} bt_discoverable_t;

/**
 * An enumeration that represents access types used during the inquiry procedure
 * in applications where the remote device address is unknown.
 */
typedef enum {
    /**
     * General Inquiry Access Code (GIAC), which is always discoverable.
     */
    BT_INQUIRY_GIAC = 1,
    /**
     * Limited Inquiry Access Code (LIAC), which has limited discoverability.
     */
    BT_INQUIRY_LIAC = 2,
} bt_inquiry_access_t;

/*
 * Bluetooth local/remote API Events
 */

/**
 * Discovery mode has changed.
 */
#define BT_EVT_ACCESS_CHANGED              0x00

/**
 * The Bluetooth radio has been turned off.
 */
#define BT_EVT_RADIO_SHUTDOWN              0x01

/**
 * The Bluetooth radio has been initialized or has just started.
 */
#define BT_EVT_RADIO_INIT                  0x02

/**
 * A numeric comparison pairing has been requested.
 */
#define BT_EVT_CONFIRM_NUMERIC_REQUEST     0x03

/**
 * A Bluetooth pairing operation has been completed.
 * For low energy devices, the @c event_data field indicates whether the address
 * is public (0) or private (1).
 */
#define BT_EVT_PAIRING_COMPLETE            0x04

/**
 * A Bluetooth device has been found and added to the cached list.
 * For low energy devices, the @c event_data field indicates whether the address
 * is public (0) or private (1).
 */
#define BT_EVT_DEVICE_ADDED                0x05

/**
 * A Bluetooth device has been removed from the cached list.
 * For low energy devices, the @c event_data field indicates whether the address
 * is public (0) or private (1).
 */
#define BT_EVT_DEVICE_DELETED              0x06

/**
 * A Bluetooth device has connected to a service.
 */
#define BT_EVT_SERVICE_CONNECTED           0x07

/**
 * A Bluetooth device has disconnected from a service.
 */
#define BT_EVT_SERVICE_DISCONNECTED        0x08

/**
 * A Bluetooth stack fault has occurred, and Bluetooth must be reset to continue.
 */
#define BT_EVT_FAULT                       0x09

/**
 * A classic Bluetooth device has connected to the BlackBerry device.
 */
#define BT_EVT_DEVICE_CONNECTED            0x0A

/**
 * A classic Bluetooth device has disconnected from the BlackBerry device.
 * The @c event_data field provides the error code that indicates why the device
 * disconnected.
 */
#define BT_EVT_DEVICE_DISCONNECTED         0x0B

/**
 * A classic Bluetooth name has been retrieved for a remote device
 *(see @c bt_rdev_update_friendly_name()).
 */
#define BT_EVT_NAME_UPDATED                0x0C

/**
 * A low energy Bluetooth device has connected to the BlackBerry device.
 */
#define BT_EVT_LE_DEVICE_CONNECTED         0x0D

/**
 * A low energy Bluetooth device has disconnected from the BlackBerry device.
 * The @c event_data field provides the error code that indicates why the device
 * disconnected.
 */
#define BT_EVT_LE_DEVICE_DISCONNECTED      0x0E

/**
 * A low energy Bluetooth name has been retrieved for a remote device
 *(see @c bt_rdev_update_friendly_name()).
 */
#define BT_EVT_LE_NAME_UPDATED             0x0F

/**
 * A classic Bluetooth device has updated its service records
 * (see @c bt_rdev_get_services()).
 */
#define BT_EVT_SERVICES_UPDATED            0x10

/**
 * A classic Bluetooth device has updated its GATT services
 *(see @c bt_rdev_get_services_gatt()).
 */
#define BT_EVT_GATT_SERVICES_UPDATED       0x11

/**
 * A low energy Bluetooth device has updated its GATT services
 * (see @c bt_rdev_get_services_gatt()).
 */
#define BT_EVT_LE_GATT_SERVICES_UPDATED    0x12

/**
 * An event to indicate that the bonding/pairing information has been removed
 * For low energy devices, the @c event_data field indicates whether the address
 * is public (0) or private (1).
 */
#define BT_EVT_PAIRING_DELETED             0x13

/**
 * An event to indicate that the pairing process for the device has started.
 * For low energy devices, the @c event_data field indicates whether the address
 * is public (0) or private (1).
 */
#define BT_EVT_PAIRING_STARTED             0x14

/**
 * An event to indicate that the pairing process for the device has failed.
 * For low energy devices, the @c event_data field indicates whether the address
 * is public (0) or private (1).
 */
#define BT_EVT_PAIRING_FAILED              0x15

/**
 * An undefined value to handle unrecognized events.
 */
#define BT_EVT_UNDEFINED_EVENT             0xFF

/**
 * An event to indicate that an SDP record has been received.
 * @deprecated BlackBerry 10.3.0.  This event is internal only and is not sent to third party applications.
 */
#define BT_EVT_SDP_RECORD_RECEIVED         BT_EVT_UNDEFINED_EVENT

/**
 * Used to define all events when performing event filtering.
 */
#define BT_EVT_ALL_EVENT                   BT_EVT_UNDEFINED_EVENT

/*
 * Device list option bitmasks, which are used in '@c bt_disc_retrieve_*()'
 * calls.
 */
/**
 * Retrieve all cached devices from the last Bluetooth scan operation.
 */
#define BT_DISCOVERY_CACHED         0x01
/**
 * Retrieve all known (paired) devices.
 */
#define BT_DISCOVERY_PREKNOWN       0x02
/**
 * Retrieve all connected devices.
 */
#define BT_DISCOVERY_CONNECTED      0x04
/**
 * Retrieve all devices.
 */
#define BT_DISCOVERY_ALL            ( BT_DISCOVERY_CACHED | BT_DISCOVERY_PREKNOWN )

/*
 * Trusted flags
 */
/**
 * Connections from remote Bluetooth device are not automatically trusted.
 */
#define BT_TRUSTED_NO               0x00

/**
 * Connections from remote Bluetooth device are automatically trusted.
 */
#define BT_TRUSTED_YES              0x01

/*
 * Encrypted flags
 */
/**
 * Connections to the remote device are not encrypted.
 */
#define BT_ENCRYPTED_NO               0x00
/**
 * Connections to the remote device are encrypted.
 */
#define BT_ENCRYPTED_YES              0x01

/*
 * Device type masks (since devices can support more than one type)
 */

/**
 * Device is a regular Bluetooth-enabled device.
 */
#define BT_DEVICE_TYPE_REGULAR          0x20
/**
 * Device supports low-energy and public access.
 */
#define BT_DEVICE_TYPE_LE_PUBLIC        0x00
/**
 * Device supports low-energy and private access.
 */
#define BT_DEVICE_TYPE_LE_PRIVATE       0x01
/**
 * Device type unknown (indicating a device structure for a device which has not
 * been discovered).
 */
#define BT_DEVICE_TYPE_UNKNOWN          0xFF

/*
 * Dual mode constants that define the device's ability to work with both
 * classic and low energy Bluetooth devices.
 */

/**
 * Dual mode status unknown for this device.
 */
#define BT_DUAL_MODE_UNKNOWN        0x00

/**
 * Device supports dual mode but not simultaneous connections.
 */
#define BT_DUAL_MODE_SUPPORTED      0x01

/**
 * Device supports dual mode and allows simultaneous connections.
 */
#define BT_DUAL_MODE_SUPPORTED_SIMULTANEOUS 0x02

/**
 * Device does not support dual mode.
 */
#define BT_DUAL_MODE_NOT_SUPPORTED  0x03

/**
 * The enumeration represents the Class of Device or Class of Service request
 * mode.
 */
typedef enum {
    /**
     * Full device class value, including the next three enumerated values.
     */
    BT_COD_DEVICECLASS,
    /**
     * Major service class. For example, networking, audio, rendering, etc.
     */
    BT_COD_MAJORSERVICECLASS,
    /**
     * Major device class. For example, computer, phone, peripheral, etc.
     */
    BT_COD_MAJORDEVICECLASS,
    /**
     * Minor device class. For example, laptop, smart phone, joystick, etc.
     */
    BT_COD_MINORDEVICECLASS
} bt_deviceclassmode_t;

/**
 * Bluetooth API property identifiers. The various enumerated values represent
 * properties used for Bluetooth communication.
 */
typedef enum {
    /**
     * The API version.
     */
    BT_PROP_API_VERSION,
    /**
     * Whether a master/slave switch is allowed.
     */
    BT_PROP_MASTER_SLAVE_SWITCH,
    /**
     * The maximum number of connected devices allowed.
     */
    BT_PROP_MAX_CONNECTED_DEVICES,
    /**
     * The maximum receive MTU size supported for Logical Link Control and
     * Adaptation Protocol (L2CAP).
     */
    BT_PROP_MAX_L2CAP_RCVMTU,
    /**
     * The maximum receive MTU size supported for the RFCOMM protocol.
     */
    BT_PROP_MAX_RFCOMM_RCVMTU,
    /**
     * Whether the incoming inquiry scanning responded while connected.
     */
    BT_PROP_CONNECTED_INQUIRY_SCAN,
    /**
     * Whether incoming page scanning, for instance, a new connection, is
     * allowed while connected.
     */
    BT_PROP_CONNECTED_PAGE_SCAN,
    /**
     * Whether outgoing inquiry scanning is allowed while connected.
     */
    BT_PROP_CONNECTED_INQUIRY,
    /**
     * Whether an outgoing connection is allowed while connected.
     */
    BT_PROP_CONNECTED_PAGE
} bt_property_t;

/*
 * Bluetooth features and profiles are disabled using various bit-mask values.
 * The following list defines the reasons that features or profiles are disabled:
 */

/**
 * Feature not supported by device.
 */
#define BT_FEATURE_STATUS_NOTSUP                0x0001
/**
 * Disabled by parent feature.
 */
#define BT_FEATURE_STATUS_PARENT                0x0002
/**
 * Disabled by user selection.
 */
#define BT_FEATURE_STATUS_USER                  0x0004
/**
 * Disabled by carrier settings.
 */
#define BT_FEATURE_STATUS_CARRIER               0x0008
/**
 * Disabled by information technology (IT) policy.
 */
#define BT_FEATURE_STATUS_ITPOLICY              0x0010
/**
 * Reserved.
 */
#define BT_FEATURE_STATUS_RESERVED              0x8000

/**
 * This enumeration defines features and profiles available for Bluetooth.
 * Features and profiles can be disabled in various ways.
 * The enumerated values are used as constants for the
 * @c bt_ldev_get_feature_enabled() function to specify the feature and profiles
 * you want to test in enabled status.
 */
typedef enum
{
    /**
     * General Bluetooth.
     */
    BT_FEATURE_BLUETOOTH,
    /**
     * Message Access Profile (MAP).
     */
    BT_FEATURE_MAP,
    /**
     * Object Push Profile (OPP) server.
     */
    BT_FEATURE_OPP_SERVER,
    /**
     * Object Push Profile (OPP) client.
     */
    BT_FEATURE_OPP_CLIENT,
    /**
     * Phonebook Access Profile (PBAP).
     */
    BT_FEATURE_PBAP,
    /**
     * Advanced Audio Distribution Profile (A2DP) source.
     */
    BT_FEATURE_A2DP_SOURCE,
    /**
     * Advanced Audio Distribution Profile (A2DP) sink.
     */
    BT_FEATURE_A2DP_SINK,
    /**
     * Audio/Video Remote Control Profile (AVRCP).
     */
    BT_FEATURE_AVRCP,
    /**
     * Low Energy.
     */
    BT_FEATURE_LOW_ENERGY,
    /**
     * Handsfree Profile (HFP) gateway.
     */
    BT_FEATURE_HFPG,
    /**
     * Handsfree Profile (HFP) gateway.
     */
    BT_FEATURE_HFP,
    /**
     * Human Interface Device (HID) client.
     */
    BT_FEATURE_HID_CLIENT,
    /**
     * Human Interface Device (HID) server.
     */
    BT_FEATURE_HID_SERVER,
    /**
     * Serial Port Profile (SPP).
     */
    BT_FEATURE_SPP,
    /**
     * Personal Area Network (PAN).
     */
    BT_FEATURE_PAN,
    /**
     * Undefined (end of list placeholder).
     */
    BT_FEATURE_UNDEFINED
} bt_feature_t;

/*
 * Bluetooth out-of-band (OOB) pairing role constants for bt_rdev_set_oob_data().
 */

/**
 * The OOB role is unspecified
 */
#define BT_OOB_ROLE_UNKNOWN                 (-1)
/**
 * This side is the requester.
 */
#define BT_OOB_ROLE_REQUESTER               0
/**
 * This side is the selector.
 */
#define BT_OOB_ROLE_SELECTOR                1

/**
 * An opaque abstraction for remote device data.
 */
typedef struct {
} bt_remote_device_t;

/**
 * The structure that contains the SDP service class id.
 */
typedef struct {

   /**
    * The universal unique identifier (UUID) of the service class.
    */
   char *uuid;

} bt_sdp_class_t;

/**
 * The structure that contains the SDP protocol list.
 */
typedef struct {

   /**
    * The service protocol UUID
    */
   char *uuid;

   /**
    * The service protocol parameters.
    */
   char *parm[2];

} bt_sdp_prot_t;

/**
 * The structure that contains the SDP language base.
 */
typedef struct {

   /**
    * The language identifier.
    */
   char *code;

   /**
    * The character encoding of the language base.
    */
   char *encoding;

   /**
    * The base attribute ID for each natural language in the SDP record.
    */
   char *base_offset;

} bt_sdp_lang_t;

/**
 * The structure that contains the SDP record
 */
typedef struct {

   /**
    * The number of elements in the variable-length array of the service
    * class UUID.
    */
   int num_classId;

   /**
    * The variable-length array of the service class UUID.
    */
   bt_sdp_class_t *classId;

   /**
    * The service UUID.
    */
   char *serviceId;

   /**
    * The service name.
    */
   char *name;

   /**
    * The service description.
    */
   char *description;

   /**
    * The service provider name.
    */
   char *provider;

   /**
    * The service availability.
    */
   char *availability;

   /**
    * The handle to the service record.
    */
   char *record_handle;

   /**
    * The number of elements in the variable-length array of the service protocol.
    */
   int num_protocol;

   /**
    * The variable-length array of service protocols.
    */
   bt_sdp_prot_t *protocol;

   /**
    * The number of elements in the variable-length array of the service
    * language.
    */
   int num_language;

   /**
    * The variable-length array of the service language.
    */
   bt_sdp_lang_t *language;

} bt_sdp_record_t;

/**
 * The structure that contains the SDP record list
 */
typedef struct bt_sdp_list {

   /**
    * The number of elements in the variable-length array of pointers to the
    * SDP records.
    */
    int num_records;

   /**
    * The variable-length array of pointers to SDP records.
    */
    bt_sdp_record_t record[];

} bt_sdp_list_t;

/**
 * The callback prototype to work with Bluetooth-enabled devices.
 *
 * @param event The Bluetooth event. See the constants prefixed with @c BT_EVT.
 * @param bt_addr A pointer to an 18-byte buffer the Bluetooth MAC
 *                address is written to in NULL-terminated printable format.
 * @param event_data A string representing the event data.
 */
typedef void (*bt_device_cb)( const int event, const char *bt_addr, const char *event_data );

/**
 * The callback prototype to indicate that @c bt_ldev_set_power_async has completed.
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EAGAIN: The Bluetooth stack is already in the requested state.
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
typedef void (*bt_ldev_set_power_cb) (void *user_data, uint8_t error);

/**
 * The callback prototype to indicate that @c bt_rdev_pair_async has completed.
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *           (internal error).
 *         - @c ECANCELED: The pairing was canceled or rejected.
 */
typedef void (*bt_rdev_pair_cb) (void *user_data, uint8_t error);

/**
 * The callback prototype to indicate that @c bt_rdev_delete_async has completed.
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *           (internal error).
 */
typedef void (*bt_rdev_delete_cb) (void *user_data, uint8_t error);

/**
 * The callback prototype to indicate that @c bt_rdev_refresh_services_async has completed.
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
typedef void (*bt_rdev_refresh_services_cb) (void *user_data, uint8_t error);

/**
 * The callback prototype to indicate that @c bt_rdev_refresh_gatt_services_async has completed.
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
typedef void (*bt_rdev_refresh_gatt_services_cb) (void *user_data, uint8_t error);

/**
 * The callback prototype to indicate that @c bt_rdev_start_inquiry_async has completed.
 *
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c access_code.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 */
typedef void (*bt_disc_inquiry_complete_cb) (void *user_data, uint8_t error);

/**
 * The callback prototype to indicate that @c bt_rdev_sdp_search_async has completed.
 *
 * @param result A pointer to the resulting SDP record list. The
 *               resulting SDP record list is dynamically allocated.  This structure must
 *               not be freed within the callback.
 * @param user_data The pointer to be returned when the callback is executed.
 * @param error @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
typedef void (*bt_rdev_sdp_cb) ( bt_sdp_list_t *result, void *user_data, uint8_t error);

__BEGIN_DECLS

/*
 *
 * Device Library Initialization
 *
 */

/**
 * @brief Initialize the Bluetooth device and allocate the required resources
 *        for the library
 * @details This function also starts a new thread. The callback is invoked in
 *          the new thread and is thread safe. This function must be called
 *          before you call any other functions in this file. A corresponding
 *          call to the @c bt_device_deinit() function must be made when you
 *          have completed using functionality from this file.
 *
 * @param callback A callback function that is invoked when Bluetooth-specific
 *                 events arrive. Bluetooth events are prefixed with
 *                 @c BT_EVT_.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c EINVAL: @c bt_device_init() has already been called.
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 */
int bt_device_init( bt_device_cb callback );

/**
 * @brief Deallocate resources that were allocated to interact with the device
 * @details Call this function when you have completed using functionality
 *          from this file. It also disables functionality that was initialized
 *          when the @c bt_device_init() function was called.
 *          @b Ensure @b you @b call @b this @b function @b before @b your @b
 *          @b application @b exits.
 */
void bt_device_deinit( );

/**
 * @brief Retrieve the out-of-band (OOB) pairing data of the local device.
 * @details The OOB Hash-C and Randomizer-R values for the local Bluetooth device
 *          are copied into the provided character buffers, which can then be
 *          passed to the remote device for OOB pairing (see @c bt_rdev_set_oob_data()).
 *
 * @param hashC A pointer to a printable character array containing the Hash-C
 *              value from the local device.
 * @param randR A pointer to a printable character array containing the
 *              Randomizer-R value from the local device.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *          - @c EINVAL:  An invalid value was passed in for @c hashC or @c randR.
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT:  A required data entry was not found (internal error)
 *          - @c EPERM:  There was an error accessing required system data
 *                       (internal error).
 */
int bt_ldev_get_oob_data( const char **hashC, const char **randR );

/*
 *
 * Local Device Access
 *
 */

/**
 * @brief Retrieve the local device type
 * @details The device type for the local Bluetooth-enabled device is returned.
 *          For more information, see constants prefixed with @c BT_DEVICE_TYPE_.
 *
 * @return The local Bluetooth device type mask is returned.
 */
int bt_ldev_get_type();

/**
 * @brief Retrieve the friendly name of the local Bluetooth-enabled device
 * @details The friendly name is a string value that helps to make it easier
 *          to identify the local device. After you call the function, the name
 *          is retrieved from the @c friendly_name argument. You must allocate
 *          a buffer that is large enough to store the name including the
 *          terminating NULL character.
 *
 * @param friendly_name A string buffer where the Bluetooth friendly name is
 *                      stored.
 * @param friendly_name_len The size of the buffer. The minimum size is 2 bytes
 *                          and the maximum is 256 bytes. The buffer length must
 *                          include room for the terminating NULL character.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOENT: The friendly name of the local device could not be found.
 */
int bt_ldev_get_friendly_name( char *friendly_name, int friendly_name_len );

/**
 * @brief Retrieve the local device address
 * @details Requests the Bluetooth MAC address of the local device.
 *
 * @param bt_addr A pointer to an 18-byte buffer where the Bluetooth MAC address
 *                is written in NULL-terminated printable format.
 *                For example: <tt>00:00:00:00:00:00\0</tt>.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c ENOENT: The local device address could not be found.
 */
int bt_ldev_get_address( char *bt_addr );

/**
 * @brief Get the local device's discoverability mode
 * @details Returns the current Bluetooth discoverable status for the
 *          local device.
 *
 * @return Bluetooth discoverable setting for the local device (see
 *         @c #bt_discoverable_t).
 */
bt_discoverable_t bt_ldev_get_discoverable( );

/**
 * @brief Set the local Bluetooth-enabled device to discoverable mode
 * @details After you set the discoverable mode, you can monitor for the
 *          @c BT_EVT_ACCESS_CHANGED event to confirm that the mode has been
 *          changed. The return code for this function indicates that the
 *          function has run successfully, not that the discoverable mode
 *          has changed.
 *
 * @param new_mode The new Bluetooth discoverable mode being requested.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
int bt_ldev_set_discoverable( const bt_discoverable_t new_mode );

/**
 * @brief Retrieve the class of device information for the local
 *        Bluetooth-enabled device
 * @details This API retrieves one of a number of class of device data items
 *          (see @c #bt_deviceclassmode_t).
 *
 * @param class_type The type of CoD information that is being requested.
 * @return The device class value is returned upon success, @c -1 with the
 *         @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
int bt_ldev_get_device_class( const bt_deviceclassmode_t class_type );

/**
 * @brief Determine whether the Bluetooth radio is enabled
 * @details The current power status is retrieved and returned as a @c bool value.
 * @return @c true if the Bluetooth radio is enabled (turned on), @c false
 *         otherwise.
 */
bool bt_ldev_get_power( );

/**
 * @brief Enable or disable the Bluetooth radio
 * @details Turns the Bluetooth radio controller on or off on the local device.
 *          In your event loop, you can monitor for the @c BT_EVT_RADIO_INIT
 *          event to confirm that the Bluetooth radio has been turned on and the
 *          @c BT_EVT_RADIO_SHUTDOWN event to confirm that the radio has been
 *          turned off. The return code for this function indicates that the
 *          function has been completed successfully and not that the Bluetooth
 *          radio controller has been turned on or off.
 *
 * @param power_on Set to a value of @c true to enable (turn on) the Bluetooth
 *                 radio, @c false to disable (turn off) the Bluetooth radio.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EAGAIN: The Bluetooth stack is already in the requested state.
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
int bt_ldev_set_power(const bool power_on );

/**
 * @brief Enable or disable the Bluetooth radio asynchronously.  When completed
 *        the callback @c bt_ldev_set_power_cb will be called.
 * @details When this function completes successfully, the @c bt_ldev_set_power_cb
 *          callback is invoked and the @c BT_EVT_RADIO_INIT or
 *          @c BT_EVT_RADIO_SHUTDOWN event is sent.
 * @param power_on Set to a value of @c true to enable (turn on) the Bluetooth
 *                 radio, @c false to disable (turn off) the Bluetooth radio.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
int bt_ldev_set_power_async( const bool power_on, bt_ldev_set_power_cb cb, void *user_data );

/**
 * @brief Retrieve the value of a Bluetooth property from the local device
 * @details The value of the requested property is saved into the @c property_value
 *          argument. You are responsible for allocating a buffer size that is
 *          adequate. If the property value is longer than the @c property_value
 *          argument, it will be truncated.
 *
 * @param property_id The ID of the property to retrieve a value for.
 * @param property_value The buffer where the requested value is written in a
 *                       NULL-terminated string.
 * @param property_value_len The length of the @c property_value buffer. No more
 *                           than property_value_len characters, which includes
 *                           the terminating NULL character, is written to the
 *                           @c property_value argument.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c EINVAL: An invalid parameter was passed in.
 *          - @c ENOTSUP: The requested property_id is not currently supported.
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
int bt_ldev_get_property( const bt_property_t property_id, char *property_value,
                          int property_value_len );

/**
 * @brief Retrieve the enabled status of a feature or profile.
 * @details This function returns the current enabled status for a particular
 *          Bluetooth feature or profile.
 *          The bitmask returned indicates whether the requested item is enabled
 *          or disabled due to IT policy or some other reason (see
 *          @c BT_FEATURE_STATUS_*).
 * @param feature_id Specifies which feature or profile to check.
 * @return @c 0 if the feature is enabled, a bit-mask showing the disabled status,
 *         or @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
int bt_ldev_get_feature_enabled( const bt_feature_t feature_id );

/**
 * @brief Retrieve the list of local services
 * @details Retrieves an array of services that we support.
 *          The following example shows you how to retrieve a
 *          list of local services:
 *
 * @code
 * char **services_array;
 * if( ( services_array = bt_ldev_get_services() ) != NULL)
 * {
 *     //work with the services listing
 *     bt_ldev_free_services( services_array );
 * }
 * @endcode
 *
 * @return An allocated, NULL-terminated array of local service
 *         strings is returned upon success, @c NULL with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 */
char **bt_ldev_get_services();

/**
 * @brief Free the services array
 * @details Deallocates resources used for an array of local services.
 *
 * @param services_array A pointer to an array of local services. The array
 *                       is returned when you call the @c bt_ldev_get_services()
 *                       function.
 * @return Nothing
 */
void bt_ldev_free_services( char **services_array );

/**
 * @brief This function enables the invoking of a service application when a
 *        registered Bluetooth event occurs.
 *
 * @details The application is invoked when the first event is received that meets
 *          the filtering parameters defined with @c bt_ldev_set_filters() and the
 *          application has been deregistered (exited) or placed in the stop
 *          partition.  When invoked, the invoke action is
 *          @c bb.action.bluetooth.EVENT.  The application can use
 *          @c bt_ldev_invoke_decode_event() to retrieve the event data.
 *
 *          If the application is deregistered or terminated, the invoke setup will
 *          remain until the first invoke event is sent or until the application
 *          restarts and calls @c bt_le_init() prior to any invoke event.
 *
 *
 * @param target The target key that is defined in the application manifest.
 *
 * @return @c EOK on successful enabling the invoke interface, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c EACCES: The current application does not have permission to
 *                      invoke the supplied trigger.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_ldev_enable_invoke(const char *target);

/**
 * @brief This disables the invoke feature for receiving Bluetooth events
 *
 * @return @c EOK on successfully disabling the invoke interface, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_ldev_disable_invoke();

/**
 * @brief This function is used to parse the Bluetooth event data received
 *        over the invoke interface when @c "bb.action.bluetooth.EVENT"
 *        occurs.
 * @details The data that is provided must have the mime-type of
 *          "application/vnd.blackberry.bluetooth.event".
 *          You must call @bt_device_init() before calling this function.
 *
 * @param invoke_dat The data provided by the invoke interface.
 * @param invoke_len The length of the data provided by the invoke interface.
 * @param event Returns the event which triggered the invoke.
 * @param bdaddr A pointer to the Bluetooth address of the event from
 *               within the invoke data.   This pointer is valid only
 *               for the lifespan of the invoke data.
 * @param event_data A pointer to the event data from within the invoke data.
 *                   This pointer references is valid only for the lifespan of
 *                   the invoke data.
 *
 * @return @c EOK on success, @c -1 if an error occurred with the @c errno value
 *         set. These are some of the error codes that can be returned:
 *         - @c EAGAIN: @c bt_device_init() was not called.
 *         - @c EPROTO: The data provided is not properly formatted to the
 *                      required mime-type.
 *         - @c EINVAL: One or more of the variables provided are invalid.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */

int bt_ldev_invoke_decode_event(const char *invoke_data, int invoke_len,
        int *event, const char **bdaddr, const char **event_data);


/**
 * @brief This function allows you to enable or disable @c BT_EVT events
 *        triggering from @c bt_device_cb().
 * @details Use @c BT_EVT_ALL_EVENT to enable or disable all events.
 *          The default value is no event filtering.
 *
 * @param event The @c BT_EVT to enable or disable.  @c BT_EVT_ALL_EVENT can be used
 *              represent all events.
 * @param enable If set @c true then the event will trigger the @c bt_device_cb.
 *               If set @c false then the event will not trigget the @c bt_device_cb.
 *
 * @return @c EOK on success, @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_ldev_set_filters(int event, bool enable);

/*
 *
 *  Remote Device Access
 *
 */

/**
 * @brief Retrieve a structure representing a remote Bluetooth-enabled device
 * @details This function allocates a @c bt_remote_device_t structure and fills
 *          the address field with the one MAC address provided by the @c
 *          bt_addr.
 *          All other fields in the structure are filled with values if
 *          the specified device is either paired or cached on the system.
 *          NOTE: See @c bt_rdev_get_type() to determine whether the other
 *          fields in the structure are filled with valid, discovered data.
 *
 * @param bt_addr The Bluetooth MAC address of the remote device, including the
 *                terminating NULL character. For example,
 *                <tt>00:00:00:00:00:00\0</tt>.
 * @return An allocated device structure is returned upon success, @c NULL with
 *         the @c errno set otherwise. Any @c errno value other than the
 *         following indicates that a system error has occurred:
 *          - @c EINVAL: An invalid value was passed in for @c bt_addr.
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
bt_remote_device_t *bt_rdev_get_device( const char *bt_addr );

/**
 * @brief Retrieve a structure representing a remote Bluetooth enabled
 *        low energy device.
 * @details This function allocates a @c bt_remote_device_t structure and fills
 *          the address field with the MAC address provided by the @c
 *          bt_addr.
 *          All other fields in the structure are filled with values if
 *          the specified device is either paired or cached on the system.
 *          NOTE: See @c bt_rdev_get_type() to determine whether the other
 *          fields in the structure are filled with valid, discovered data.
 *
 * @param bt_addr The Bluetooth MAC address of the remote low energy device,
 *                including the terminating NULL character. For example,
 *                <tt>00:00:00:00:00:00\0</tt>.
 * @return An allocated device structure is returned upon success, @c NULL with
 *         the @c errno set otherwise. Any @c errno value other than the
 *         following indicates that a system error has occurred:
 *          - @c EINVAL: An invalid value was passed in for @c bt_addr.
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *          - @c ENOENT: A required data entry was not found (internal error).
 *          - @c EPERM: There was an error accessing required system data
 *            (internal error).
 */
bt_remote_device_t *bt_rdev_get_le_device( const char *bt_addr );

/**
 * @brief Release resources used by the remote device
 * @details Frees a remote device structure previously allocated by the @c
 *          bt_rdev_get_device() function.
 *
 * @param remote_device Pointer to a remote device structure.
 */
void bt_rdev_free( bt_remote_device_t *remote_device );

/**
 * @brief Deallocate the array that stores remote Bluetooth-enabled device
 *        information
 * @details The array of @c bt_remote_device_t was previously allocated by the
 *          @c bt_disc_retrieve_devices() function.
 *
 * @param remote_device_array A pointer to a NULL-terminated remote device
 *                            structure array.
 */
void bt_rdev_free_array( bt_remote_device_t **remote_device_array );

/**
 * @brief Retrieve the remote device type
 * @details Requests the Bluetooth type for the remote Bluetooth-enabled
 *          device. For more information, see constants prefixed with
 *          @c BT_DEVICE_TYPE_*.
 *          NOTE:  If the return value is @c BT_DEVICE_TYPE_UNKNOWN, this
 *          indicates that the device is not known on the system, and that
 *          other fields in the @c bt_remote_device_t object may not be valid.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return The type mask of the remote Bluetooth-enabled device is returned upon
 *         success, @c -1 with the @c errno set otherwise. Possible @c errno
 *         values include:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 */
int bt_rdev_get_type( const bt_remote_device_t *remote_device );

/**
 * @brief Retrieve the remote device name
 * @details This function retrieves the remote name of the Bluetooth-enabled device.
 *                The remote name is the name which the remote device advertises.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param device_name   A buffer where the name of the remote Bluetooth device
 *                      is written.
 * @param device_name_len The size of the buffer. The minimum size is 2 bytes
 *                        and the maximum is 256 bytes. The buffer length must
 *                        include room for the terminating @c NULL character.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_get_remote_name( const bt_remote_device_t *remote_device, char *device_name, const int device_name_len );

/**
 * @brief Retrieve the remote device friendly name
 * @details Requests the friendly name of the remote Bluetooth-enabled device.
 *                The friendly name is usually the same as the remote name,
 *                but it can be customized by the user on the BlackBerry.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param friendly_name A buffer where the Bluetooth friendly name is written.
 * @param friendly_name_len The size of the buffer. The minimum size is 2 bytes
 *                          and the maximum is 256 bytes. The buffer length must
 *                          include room for the terminating NULL character.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_get_friendly_name( const bt_remote_device_t *remote_device, char *friendly_name, const int friendly_name_len );

/**
 * @brief Update the remote device friendly name
 * @details Updates the friendly name field of the remote device data structure.
 *          This is typically done when a @c BT_EVT_NAME_UPDATED event is received
 *          and you have a @c bt_remote_device_t object for the specified device
 *          already in memory.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_update_friendly_name( bt_remote_device_t *remote_device );

/**
 * @brief Retrieve the address of the remote device
 * @details Requests the Bluetooth MAC address of the remote device.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param bt_addr A pointer to an 18-byte buffer where the Bluetooth MAC address
 *                is written in a NULL-terminated printable format.
 *                For example, <tt>00:00:00:00:00:00\0</tt>.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL:  An invalid parameter was passed in.
 */
int bt_rdev_get_address( const bt_remote_device_t *remote_device, char *bt_addr );

/**
 * @brief Deprecated
 * @details Retrieve the address of the remote device
 * @deprecated Use the @c bt_rdev_get_address() function instead.
 */
int bt_rdev_get_addr( const bt_remote_device_t *remote_device, char *bt_addr );

/**
 * @brief Retrieve the received signal strength indicator (RSSI) of the remote
 *        Bluetooth-enabled device
 * @details The RSSI value is only valid when the device was found by using the
 *          @c bt_disc_retrieve_devices() function with @c BT_DISCOVERY_CACHED
 *          as an argument.
 *
 *          The RSSI value for paired devices is always @c 0.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param rssi A pointer to a buffer where the RSSI value is to be written.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_get_rssi( const bt_remote_device_t *remote_device, int *rssi );

/**
 * @brief Retrieve the current received signal strength indicator (RSSI) of the
 *        connected remote Bluetooth-enabled device
 * @details The current RSSI value is only valid for a remote device which is
 *          currently connected to the BlackBerry. This function requests an
 *          updated RSSI value for the current connection.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param rssi A pointer to a buffer where the RSSI value is to be written.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_get_current_rssi( const bt_remote_device_t *remote_device, int *rssi );

/**
 * @brief Retrieve the current transmit (TX) power indicator of the
 *        connected remote Bluetooth-enabled device
 * @details The current TX power value is only valid for a remote device that is
 *          currently connected to the BlackBerry. This function requests an
 *          updated TX power value for the current connection.
 *          The TX power value will be in the range -30 dB to +30 dB.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param tx_power A pointer to a buffer where the TX power value is to be written.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_get_current_tx_power( const bt_remote_device_t *remote_device, int *tx_power );

/**
 * @brief Retrieve the class of device (CoD) information of the remote
 *        Bluetooth-enabled device
 * @details This function retrieves one of a number of class of device data items
 *          (see @c #bt_deviceclassmode_t).
 *
 * @param remote_device A pointer to a remote device structure.
 * @param class_type The type of CoD information that is being requested.
 * @return The device class value is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL:  An invalid parameter was passed in.
 */
int bt_rdev_get_device_class( const bt_remote_device_t *remote_device,
                              const bt_deviceclassmode_t class_type );

/**
 * @brief Retrieve the pairing state of the remote Bluetooth-enabled device
 * @details Use this function to determine if the remote device is paired.
 *          The @c paired argument indicates whether the device is paired after
 *          the function is successfully called. A value of @c true indicates
 *          that the remote device is paired.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param paired A pointer to a @c bool to indicate whether the remote device is
 *               paired.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *          Possible @c errno values include:
 *          - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_is_paired( const bt_remote_device_t *remote_device, bool *paired );

/**
 * @brief Retrieve the known state of the remote Bluetooth-enabled device
 * @details Use this function to determine if the remote device is known.
 *          The @c known argument indicates whether the device is known after
 *          the function is successfully called. A value of @c true indicates
 *          that the remote device is known.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param known A pointer to a @c bool to indicate whether the remote device is
 *               known.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *          Possible @c errno values include:
 *          - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_is_known( const bt_remote_device_t *remote_device, bool *known );

/**
 * @brief Pair with a remote Bluetooth-enabled device asynchronously.
 * @details This function sends an authentication (pairing) request to the remote
 *          device. For a Bluetooth device that does not support pairing, the device will be
 *          flagged as a known device on success.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer which will be returned during the
 *                  callback.
 * @return @c 0 is returned upon successful pairing, @c -1 with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *           (internal error).
 *         - @c ECANCELED: The pairing was canceled or rejected.
 */
int bt_rdev_pair_async( const bt_remote_device_t *remote_device, bt_rdev_pair_cb cb, void *user_data );

/**
 * @brief Pair with a remote Bluetooth-enabled device
 * @details This function sends an authentication (pairing) request to the remote
 *          device and blocks until pairing is completed successfully or fails.
 *          For Bluetooth devices that do not support pairing, the device will be
 *          flagged as a known device on success.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return @c 0 is returned upon successful pairing, @c -1 with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *           (internal error).
 *         - @c ECANCELED: The pairing was canceled or rejected.
 */
int bt_rdev_pair( const bt_remote_device_t *remote_device );

/**
 * @brief Delete a remote Bluetooth-enabled device asynchronously.
 * @details This function removes the pairing information of a remote device,
 *         essentially deleting it from the list of paired devices.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer which will be returned during the
 *                  callback.
 * @return @c 0 is returned upon successful deletion, @c -1 with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *           (internal error).
 */
int bt_rdev_delete_async( const bt_remote_device_t *remote_device, bt_rdev_delete_cb cb, void *user_data );

/**
 * @brief Delete a remote Bluetooth-enabled device
 * @details This function removes the pairing information of a remote device,
 *         essentially deleting it from the list of paired devices.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return @c 0 is returned upon successful deletion, @c -1 with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *           (internal error).
 */
int bt_rdev_delete( const bt_remote_device_t *remote_device );

/**
 * @brief Set out-of-band (OOB) pairing data for a remote Bluetooth-enabled device
 * @details Use this function to save OOB authentication (pairing) data.
 *          To initiate the OOB pairing, simply call @c bt_rdev_pair() after
 *          calling @c bt_rdev_set_oob_data().
 *
 * @param remote_device A pointer to a remote device structure.
 * @param hashC A printable character array containing the Hash-C value from the
 *              remote device.
 * @param randR A printable character array containing the Randomizer-R value
 *              from the remote device.
 * @param psi The page scan information (PSI) clock offset value (optional, use
 *            @c -1 if unspecified).
 * @param role The OOB pairing role that this side is taking (optional, see
 *             @c BT_OOB_ROLE_*).
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *          Any @c errno value other than the following indicates that a system
 *          error has occurred:
 *          - @c EINVAL:  An invalid value was passed in for @c remote_device.
 *          - @c ENOMEM: Sufficient memory is not available to perform the
 *                       request.
 *          - @c ENOENT:  A required data entry was not found (internal error).
 *          - @c EPERM:  There was an error accessing required system data
 *                       (internal error).
 */
int bt_rdev_set_oob_data( const bt_remote_device_t *remote_device, const char *hashC, const char *randR, const int psi, const int role );


/**
 * @brief Refresh remote device services
 * @details Triggers a refresh of the services advertised for a remote device.
 *          If the device is not already paired, this will trigger the first
 *          fetch of the services that the remote device advertises, provided
 *          the remote device is in the right security mode.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer which will be returned during the
 *                  callback.
 * @return @c EOK is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_refresh_services_async( const bt_remote_device_t *remote_device, bt_rdev_refresh_services_cb cb, void *user_data );

/**
 * @brief Refresh remote device services
 * @details Triggers a refresh of the services advertised for a remote device.
 *          If the device is not already paired, this will trigger the first
 *          fetch of the services that the remote device advertises, provided
 *          the remote device is in the right security mode.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return The positive trusted flag is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_refresh_services( const bt_remote_device_t *remote_device );

/**
 * @brief Refreshes the GATT services on the remote device asynchronously
 * @details Triggers a refresh of the available GATT services on the remote device.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer which is returned during the
 *                  callback.
 * @return @c EOK is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_refresh_gatt_services_async( const bt_remote_device_t *remote_device, bt_rdev_refresh_gatt_services_cb cb, void *user_data );

/**
 * @brief Refresh the available GATT services on the remote device
 * @details Triggers a refresh of the available GATT services on the remote device.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return @c EOK is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_refresh_gatt_services( const bt_remote_device_t *remote_device );

/**
 * @brief Clears the GATT service cache on a remote device
 *
 * @param remote_device A pointer to a remote device structure.
 * @return @c EOK is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_clear_gatt_cache( const bt_remote_device_t *remote_device );

/**
 * @brief Determine whether the remote device is trusted
 * @details If a non-negative value is returned, it indicates that the remote
 *          device is trusted. Trusted remote devices are prompt-free
 *          for incoming connections.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return The positive trusted flag is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_is_trusted( const bt_remote_device_t *remote_device );

/**
 * @brief Determine whether the connection with the remote Bluetooth-enabled
 *        device is encrypted
 * @details If a non-negative value is returned, it indicates that the
 *          connection is encrypted by default.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return The positive encrypted flag is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_is_encrypted( const bt_remote_device_t *remote_device );

/**
 * @brief Determine whether the remote device supports dual-mode connections
 * @details Dual-mode devices can connect to either classic or low energy
 *          devices.  If a non-negative value is returned, it indicates the
 *          modes that the remote device is capable of supporting.
 *          For more information, see constants prefixed with @c BT_DUAL_MODE_.
 *
 * @param remote_device A pointer to a remote device structure.
 * @return The positive dual mole flag is returned upon success, @c -1 with the
 *         @c errno set otherwise. Possible @c errno values include:
 *         - @c EINVAL: An invalid parameter was passed in.
 */
int bt_rdev_is_dual_mode( const bt_remote_device_t *remote_device );

/**
 * @brief Retrieve the list of remote device services
 * @details Retrieves an array of services from either the paired or the found
 *          devices list. The following example shows you how to retrieve a
 *          list of remote device services:
 *
 * @code
 * char **services_array;
 * if( ( services_array = bt_rdev_get_services( remote_device ) ) != NULL)
 * {
 *     //work with the services listing
 *     bt_rdev_free_services( services_array );
 * }
 * @endcode
 *
 * @param remote_device A pointer to a remote device structure.
 * @return An allocated, NULL-terminated array of remote device service
 *         strings is returned upon success, @c NULL with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: There are no (regular) services listed for the remote
 *                      device.
 */
char **bt_rdev_get_services( const bt_remote_device_t *remote_device );

/**
 * @brief Retrieve the list of connected services for a remote device
 * @details Retrieves an array of connected services for the specified remote
 *          device. The following example shows you how to retrieve a list of
 *          connected remote device services:
 * @code
 * char **services_array;
 * if( ( services_array = bt_rdev_get_services_connected( remote_device ) ) != NULL)
 * {
 *     //work with the services listing
 *     bt_rdev_free_services( services_array );
 * }
 * @endcode
 *
 * @param remote_device A pointer to a remote device structure.
 * @return An allocated, NULL-terminated array of connected remote device
 *         service strings is returned upon success, @c NULL with the @c errno
 *         set otherwise. Any @c errno value other than the following indicates
 *         that a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: There are no (regular) services listed for the remote
 *                      device.
 */
char **bt_rdev_get_services_connected( const bt_remote_device_t *remote_device );

/**
 * @brief Retrieve the list of remote device GATT (Generic Attributes) services
 * @details Retrieves an array of GATT services from either the paired or found
 *          devices list. The following example shows how to retrieve a list
 *          of remote device services:
 *
 * @code
 * char **services_array;
 * if( ( services_array = bt_rdev_get_services_gatt(remote_device)) != NULL) {
 *     // work with the services listing
 *     bt_rdev_free_services(services_array);
 * }
 * @endcode
 *
 * @param remote_device A pointer to a remote device structure.
 * @return An allocated, NULL-terminated array of remote device service
 *         strings is returned upon success, @c NULL with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: There are no GATT services listed for the remote
 *                      device.
 */
char **bt_rdev_get_services_gatt( const bt_remote_device_t *remote_device );

/**
 * @brief The function retrieves the list of connected Generic Attributes (GATT)
 *        services
 * @details Retrieves an array of connected GATT services for the specified remote
 *          device.  The following example demonstrates how to use this function:
 *
 * @code
 * char **services_array;
 * if( ( services_array =
 *         bt_rdev_get_services_gatt_connected(remote_device)) != NULL) {
 *     // work with the services listing
 *     bt_rdev_free_services(services_array);
 * }
 * @endcode
 *
 * @param remote_device A pointer to a remote device structure.
 * @return An allocated array of NULL-terminated strings for connected remote
 *         device services is returned upon success, @c NULL with the @c errno set
 *         otherwise. Any @c errno value other than the following indicates that
 *         a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: There are no GATT services listed for the remote
 *                      device.
 */
char **bt_rdev_get_services_gatt_connected( const bt_remote_device_t *remote_device );

/**
 * @brief Free the services array
 * @details Deallocates resources used for an array of remote device services.
 *
 * @param services_array A pointer to an array of remote services. The array
 *                       is returned when you call the @c bt_rdev_get_services()
 *                       function.
 * @return Nothing
 */
void bt_rdev_free_services( char **services_array );

/**
 * @brief Retrieve the low energy connection parameters
 * @details This function retrieves the preferred low energy connection
 *          parameters for the remote device. If these parameters are not known
 *          (invalid), the @c min_conn_ivl and @c max_conn_ivl arguments will
 *          be @c 0. In addition, if @c super_tmo is @c 0, then both @c super_tmo
 *          and @c latency arguments are considered invalid.
 *
 *          All arguments provided as part of this call are pointers to a buffer
 *          the results are written to. If you do not require a specific
 *          piece of information, provide a value of @c NULL for the argument.
 *
 * @param remote_device A pointer to a remote device structure.
 * @param min_conn_ivl The preferred minimum connection interval. These are
 *                     possible values that are returned to you:
 *                     - Range: @c 0x0006 to @c 0x0C80
 *                     - Time = N * 1.25 msec
 *                     - Time range: 7.5 msec to 4 seconds
 * @param max_conn_ivl Preferred maximum connection interval. These are
 *                     possible values that are returned to you:
 *                     - Range: @c 0x0006 to @c 0x0C80
 *                     - Time = N * 1.25 msec
 *                     - Time range: 7.5 msec to 4 seconds
 * @param latency The preferred latency value. You can use a range from @c 0x0000
 *                to @c 0x01F4.
 * @param super_tmo The preferred supervisory timeout. The timeout can be:
 *                  - Range: @c 0x000A to @c 0x0C80. A value of @c 0 is returned
 *                           if unknown.
 *                  - Time = N * 10 msec
 *                  - Time range: 100 msec to 32 seconds
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOTSUP: The remote device does not contain low energy parameters.
 */
int bt_rdev_get_le_conn_params( const bt_remote_device_t *remote_device, uint16_t *min_conn_ivl, uint16_t *max_conn_ivl, uint16_t *latency, uint16_t *super_tmo );

/**
 * @brief Retrieve the low energy information
 * @details Various low energy information can be retrieved from a Bluetooth-
 *          enabled device. All arguments provided as part of this call are
 *          pointers to a buffer results are written to. If you do
 *          not require a specific piece of information, provide a value of @c
 *          NULL for the argument.
 *
 * @param remote_device A pointer to the remove device structure.
 * @param appearance The appearance flag for the remote device.
 * @param flags A bit mask containing various low energy flags.
 * @param connectable The connectable status of the remote device.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Possible @c errno values include:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 *         - @c ENOTSUP: The remote device does not contain low energy information.
 */
int bt_rdev_get_le_info( const bt_remote_device_t *remote_device, uint16_t *appearance, uint8_t *flags, uint8_t *connectable );

/**
 * @brief Initiates an asynchronous SDP service record search
 * @details This function initiates an SDP record search with a specified search
 *          pattern on a specified remote device. It sends a non-blocking SDP
 *          search request, and calls the specified callback when the search
 *          is completed.
 *
 * @param remote_device A pointer to the remote device structure.
 * @param pattern Array of the NULL-terminated string which represents the search
 *                pattern, or NULL for Public Browse Group search.
 * @param cb Callback function that is invoked when the search is complete.
 * @param user_data A user specified pointer that is returned during the
 *                  callback.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 */
int bt_rdev_sdp_search_async( const bt_remote_device_t *remote_device, char *pattern[], bt_rdev_sdp_cb cb, void *user_data );

/**
 * @brief Initiates an SDP service record search
 * @details This function initiates an SDP record search with a specified search
 *          pattern on a specified remote device. It blocks and waits until the
 *          search request is completed.
 *
 * @param remote_device A pointer to the remote device structure.
 * @param pattern Array of the NULL-terminated string which represents the search
 *                pattern, or NULL for Public Browse Group search.
 * @return A pointer to the address of the resulting SDP record list, or @c NULL with
 *         the @c errno set. Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device.
 */
bt_sdp_list_t *bt_rdev_sdp_search( const bt_remote_device_t *remote_device, char *pattern[]);

/**
 * @brief Free the SDP service record list
 * @details This function deallocates the memory that is assigned to the
 *          specified SDP record list.
 *
 * @param list pointer to SDP record list.
 */
void bt_rdev_sdp_free( bt_sdp_list_t *list );

/*
 *
 *  DEVICE DISCOVERY ACCESS
 *
 */

/**
 * @brief Retrieve the number of Bluetooth-enabled devices within range
 * @details The number of Bluetooth-enabled devices returned are from
 *          either the paired or found devices list. You usually use this
 *          function before fetching the actual devices using the @c
 *          bt_disc_retrieve_devices() function.
 *
 * @param option Specifies whether to return a count of paired (@c
 *               BT_DISCOVERY_PREKNOWN), found (@c BT_DISCOVERY_CACHED),
 *               or connected (@c BT_DISCOVERY_CONNECTED) devices.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *          - @c EINVAL:  An invalid option was passed in.
 */
int bt_disc_retrieve_count( const int option );

/**
 * @brief Retrieve a list of Bluetooth-enabled devices that are within range
 * @details An array of devices from either the paired or found devices list.
 *          The following example shows you how to retrieve a list of devices:
 * @code
 * int device_count;
 * if( ( device_count = bt_disc_retrieve_count( BT_DISCOVERY_CACHED ) ) > 0 ) {
 *   struct bt_remote_device_t **remote_device_array;
 *   if( ( remote_device_array = bt_disc_retrieve_devices(BT_DISCOVERY_CACHED, &device_count))
 *                                                                  != NULL ) {
 *      // do work with the devices
 *      bt_rdev_free_array( remote_device_arry );
 *   }
 *  }
 * @endcode
 *
 * @param option Specifies whether to retrieve the paired
 *               (@c BT_DISCOVERY_PREKNOWN), found (@c BT_DISCOVERY_CACHED),
 *               or connected (@c BT_DISCOVERY_CONNECTED) devices.
 * @param device_count_ptr (Optional) A pointer to an integer to store the number
 *                         of retrieved devices. If you do not want to use this
 *                         value, provide a value of @c NULL.
 * @return An allocated, NULL-terminated array of remote device structures upon
 *         success, or NULL with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid option was passed in.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
bt_remote_device_t **bt_disc_retrieve_devices( const int option, int *device_count_ptr );

/**
 * @brief Retrieve a list of Bluetooth-enabled devices based on a specified service
 * @details Returns an array of devices which support the specified service.
 *          The following example shows you how to retrieve a list of devices:
 * @code
 * int device_count;
 * struct bt_remote_device_t **remote_device_array;
 * if( ( remote_device_array = bt_disc_retrieve_by_service("0x1101", &device_count))
 *                                                                != NULL ) {
 *    // do work with the devices
 *    bt_rdev_free_array( remote_device_arry );
 *  }
 * @endcode
 *
 * @param service_uuid Specifies the Bluetooth service UUID as a printable string.
 * @param device_count_ptr (Optional) A pointer to an integer to store the number
 *                         of retrieved devices. If you do not want to use this
 *                         value, provide a value of @c NULL.
 * @return An allocated, NULL-terminated array of remote device structures upon
 *         success, with the @c errno value set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid option was passed in.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
bt_remote_device_t **bt_disc_retrieve_by_service( const char *service_uuid, int *device_count_ptr );

/**
 * @brief Retrieve a list of Bluetooth-enabled devices by connected service
 * @details Returns an array of devices which are currently connected on the
 *          specified service. The following example shows you how to retrieve a
 *          list of devices:
 * @code
 * int device_count;
 * struct bt_remote_device_t **remote_device_array;
 * if( ( remote_device_array = bt_disc_retrieve_by_service_connected("0x1101", &device_count))
 *                                                                != NULL ) {
 *    // do work with the devices
 *    bt_rdev_free_array( remote_device_arry );
 *  }
 * @endcode
 *
 * @param service_uuid Specifies the Bluetooth service UUID as a printable string.
 * @param device_count_ptr (Optional) A pointer to an integer to store the number
 *                         of retrieved devices. If you do not want to use this
 *                         value, provide a value of @c NULL.
 * @return An allocated, NULL-terminated array of remote device structures upon
 *         success, with the @c errno value set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid option was passed in.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
bt_remote_device_t **bt_disc_retrieve_by_service_connected( const char *service_uuid, int *device_count_ptr );

/**
 * @brief Retrieve a list of Bluetooth-enabled devices by GATT service
 * @details Returns an array of devices which support the specified GATT service.
 *          The following example shows you how to retrieve a list of devices:
 * @code
 * int device_count;
 * struct bt_remote_device_t **remote_device_array;
 * if( ( remote_device_array = bt_disc_retrieve_by_service_gatt("0x1101", &device_count))
 *                                                                != NULL ) {
 *    // do work with the devices
 *    bt_rdev_free_array( remote_device_arry );
 *  }
 * @endcode
 *
 * @param service_uuid Specifies the Bluetooth GATT service UUID as a printable
 *                     string.
 * @param device_count_ptr (Optional) A pointer to an integer to store the number
 *                         of retrieved devices. If you do not want to use this
 *                         value, provide a value of @c NULL.
 * @return An allocated, NULL-terminated array of remote device structures upon
 *         success, with the @c errno value set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid option was passed in.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 */
bt_remote_device_t **bt_disc_retrieve_by_service_gatt( const char *service_uuid, int *device_count_ptr );


/**
 * @brief Start scanning for Bluetooth-enabled devices asynchronously.
 * @details A scan of in-range Bluetooth devices is made and the results of the
 *          scan can be found via the @c BT_EVT_DEVICE_ADDED events passed to
 *          the device library callback. For information, see the @c
 *          bt_device_init() function or one of the @c bt_disc_retrieve_*()
 *          functions with the @c BT_DISCOVERY_CACHED option.
 *          This function does not return @c BT_EVT_DEVICE_ADDED
 *          events for paired devices, even if they are in range.  The purpose
 *          is to discover new, non-paired devices only.
 *
 * @param access_code The type of inquiry to perform.
 * @param cb The callback function to be executed when the operation has
 *           completed.
 * @param user_data A user specified pointer which will be returned during the
 *                  callback.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c access_code.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *                     (internal error).
 */
int bt_disc_start_inquiry_async( const bt_inquiry_access_t access_code, bt_disc_inquiry_complete_cb cb, void *user_data );

/**
 * @brief Start scanning for Bluetooth-enabled devices
 * @details A scan of in-range Bluetooth devices is made and the results of the
 *          scan can be found via the @c BT_EVT_DEVICE_ADDED events passed to
 *          the device library callback. For information, see the @c
 *          bt_device_init() function or one of the @c bt_disc_retrieve_*()
 *          functions with the @c BT_DISCOVERY_CACHED option.
 *          This function blocks until the inquiry has completed. The
 *          Bluetooth service attempts to discover devices when this function
 *          is called. When this function unblocks, you can call
 *          @c bt_disc_retrieve_devices() to retrieve the list of devices.
 *          This function does not return @c BT_EVT_DEVICE_ADDED
 *          events for paired devices, even if they are in range.  The purpose
 *          is to discover new, non-paired devices only.
 *
 * @param access_code The type of inquiry to perform.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c access_code.
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *                     (internal error).
 */
int bt_disc_start_inquiry( const bt_inquiry_access_t access_code );

/**
 * @brief Cancel Bluetooth scan of in-range devices
 * @details This function terminates Bluetooth scans that are in progress.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c ENOMEM: Sufficient memory is not available to perform the
 *                      request.
 *         - @c ENOENT: A required data entry was not found (internal error).
 *         - @c EPERM: There was an error accessing required system data
 *                     (internal error).
 */
int bt_disc_cancel_inquiry( );

__END_DECLS

#endif /* BTDEVICE_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
