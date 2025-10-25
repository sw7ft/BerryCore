/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc_types.h
 * This file contains various enumerations, typedefs, and structures
 * used to work with the Near Field Communication (NFC) library.
 *
 */

#ifndef NFC_TYPES_H_
#define NFC_TYPES_H_

/**
 * @brief NFC status code
 * @details This enumeration defines the Near Field Communication (NFC) status
 *          codes supported.
 */
typedef enum {
    /**
     * The NFC call returned successfully.
     */
    NFC_RESULT_SUCCESS                          = 0x00,
    /**
     * An error occurred because an invalid parameter was provided
     * or the parameter is invalid in the feature set used.
     */
    NFC_RESULT_INVALID_PARAMETER                = 0x01,
    /**
     * An error occurred because a non-existent or unimplemented function was
     * called.
     */
    NFC_RESULT_FEATURE_NOT_IMPLEMENTED          = 0x02,
    /**
     * An error occurred because an unsupported or deprecated function was
     * called.
     */
    NFC_RESULT_UNSUPPORTED_API                  = 0x03,
    /**
     * An error occurred because an attempt was made to access a locked
     * resource, such as a locked tag/SE.
     */
    NFC_RESULT_LOCKED                           = 0x04,
    /**
     * An error occurred because an attempt to exceed a defined resource
     * limitation was made. See the specific function description for more
     * information about the error.
     */
    NFC_RESULT_LIMITATION_EXCEEDED              = 0x05,
    /**
     * An error occurred because a user operation is not supported by the remote
     * connection.
     */
    NFC_RESULT_OPERATION_NOT_SUPPORTED          = 0x06,
    /**
     * An error occurred because a user operation is not possible in the current
     * state.
     */
    NFC_RESULT_OPERATION_REJECTED               = 0x07,
    /**
     * An error occurred because the NFC client is unable to communicate with
     * NFC service.
     */
    NFC_RESULT_SERVICE_CONNECTION_ERROR         = 0x08,
    /**
     * An error occurred because the remote peer does not support user-requested
     * services.
     */
    NFC_RESULT_P2P_REJECTED                     = 0x09,
    /**
     * An error occurred because an NFC stack timeout occurred.
     */
    NFC_RESULT_TIMEOUT                          = 0x0A,
    /**
     * An error occurred because the NFC stack is busy and cannot execute the
     * user request.
     */
    NFC_RESULT_RESOURCE_BUSY                    = 0x0B,
    /**
     * An error occurred because there are not enough memory resources. See the
     * specific function description for more information about the error.
     */
    NFC_RESULT_NOT_ENOUGH_SPACE                 = 0x0C,
    /**
     * An error has occurred because the NFC service is not able to allocate enough
     * memory for the operation.
     * This status code can be returned by any function in the NFC API, even if it
     * is not listed in the documentation of the function.
     */
    NFC_RESULT_OUT_OF_MEMORY                    = 0x0D,
    /**
     * An error when accessing NFC FDs. Application is likely out of sync with
     * NFC service.
     */
    NFC_RESULT_FD_ACCESS_ERROR                  = 0x0E,

    /**
     * NFC Tag Errors
     */
    /**
     * An error occurred because the remote tag is not lockable.
     */
    NFC_RESULT_LOCK_FAILED                      = 0x30,
    /**
     * An error occurred while writing to a tag or during a Logical Link Control
     * Protocol (LLCP) write. The contents of the tag are likely corrupt or
     * invalid.
     */
    NFC_RESULT_WRITE_FAILED                     = 0x31,
    /**
     * An error occurred while trying to read a tag or during a LLCP read.
     */
    NFC_RESULT_READ_FAILED                      = 0x32,
    /**
     * An error occurred because the remote tag isn't NFC compliant, however,
     * the remote tag can be formatted.
     */
    NFC_RESULT_NOT_NFC_TAG_BUT_CAPABLE          = 0x33,
    /**
     * An error occurred because the remote tag isn't supported.
     */
    NFC_RESULT_TAG_NOT_SUPPORTED                = 0x34,
    /**
     * An error occurred because the NDEF message could not be built.
     * The NDEF message could not be built because the provided data isn't in a
     * valid NDEF format.
     */
    NFC_RESULT_BAD_NDEF_FORMAT                  = 0x35,

    /**
     * NFC SE Errors
     */

    /**
     * An NFC Security error occurred because the input buffer was too short.
     */
    NFC_RESULT_SE_INPUT_TOO_SHORT               = 0x60,

    /**
     * An NFC Security error occurred because the handle provided wasn't valid.
     */
    NFC_RESULT_SE_INVALID_HANDLE                = 0x61,

    /**
     * An NFC Security error occurred; the Secure element service was not
     * initialized.
     */
    NFC_RESULT_SE_SERVICE_NOT_READY             = 0x62,

    /**
     * An NFC Security error occurred because no logical channels were
     * available. No channels were available because they were all in use.
     */
    NFC_RESULT_SE_OUT_OF_LOGICAL_CHANNELS       = 0x63,

    /**
     * The applet with the specified Application ID (AID) cannot be found.
     */
    NFC_RESULT_SE_AID_NOT_FOUND                 = 0x64,

     /**
     * The Application Data Unit (APDU) that was provided is malformed or
     * invalid.
     */
    NFC_RESULT_SE_INVALID_APDU                  = 0x65,

    /**
     * The secure element for a specified reader is not available.
     */
    NFC_RESULT_SE_NOT_PRESENT                   = 0x66,

    /**
     * The request was rejected by the Access Control files (ACF), or some other
     * security mechanism.
     */
    NFC_RESULT_SE_REQUEST_REJECTED              = 0x67,

    /**
     * An operation was attempted against a service that does not exist.
     */
    NFC_RESULT_SE_INVALID_SERVICE               = 0x68,

    /**
     * An operation was attempted while the SE Services Manager was not
     * initialized.
     */
    NFC_RESULT_SE_SERVICES_MANAGER_NOT_INITIALIZED = 0x69,

    /**
     * An operation was attempted against a service for which the platform does
     * not have enough information about to perform.
     */
    NFC_RESULT_SE_MISSING_SERVICE_INFORMATION   = 0x6A,

    /**
     * Internal errors
     */
    /**
     * An unhandled internal error occurred.
     */
    NFC_RESULT_UNHANDLED_ERROR                  = 0xFE,
    /**
     * An unexpected error occurred.
     */
    NFC_RESULT_ERROR                            = 0xFF
} nfc_result_t;

/**
 * @brief This enumeration defines event codes for the various NFC events
 *
 * The event codes can be associated with the following values:
 * - a target
 *   You can retrieve the target by calling @c nfc_get_target().
 * - a notification value
 *   You can retrieve the notification value by calling @c nfc_get_notification_value().
 *
 * The @c nfc_get_target() function and the @c nfc_get_notification_value() function
 * will return @c NFC_RESULT_INVALID_PARAMETER if called with an event code that is
 * not associated with a corresponding value.
 */
typedef enum {
    /** @internal
     *  For internal use only. Reserved Event Enum Value
     */
    // RESERVED                                 = 0,

    /**
     * A SNEP connection is detected and ready for sending an NDEF message
     * to NFC-enabled device.
     *
     * You can retrieve the target by calling @c nfc_get_target().
     */
    NFC_SNEP_CONNECTION_EVENT                   = 1,

    /**
     * An NFC tag target is detected and ready to read from or write to.
     *
     * You can retrieve the target by calling @c nfc_get_target().
     */
    NFC_TAG_READWRITE_EVENT                     = 2,

    /**
     * An NFC connection handover target is detected and ready for the handover
     * negotiation process to start.
     *
     * The application retrieves the target by calling @c nfc_get_target()
     * and informs the NFC system whether the application wants to
     * proceed with the handover or ignore the target.
     */
    NFC_HANDOVER_DETECTED_EVENT                 = 3,

    /**
     * An NFC connection handover negotiation was completed.
     *
     * You can call the @c nfc_get_target() function to retrieve handover
     * details from the target containing connection handover details.
     */
    NFC_HANDOVER_COMPLETE_EVENT                 = 4,

    /**
     * An Logical Link Control Protocol (LLCP) connection has been detected and
     * is ready for communication.
     *
     * You can call the @c nfc_get_target() function to retrieve the LLCP connection.
     */
    NFC_LLCP_CONNECTION_EVENT                   = 5,

    /**
     * The NFC system is off. No further NFC events will be delivered.
     *
     * No value is returned as part of this event.
     */
    NFC_OFF_EVENT                               = 6,

    /**
     * The NFC system is on.
     *
     * No value is returned as part of this event.
     */
    NFC_ON_EVENT                                = 7,

    /**
     * An external field was lost.
     *
     * No value is returned as part of this event.
     */
    NFC_FIELD_LOST_EVENT                        = 8,

    /**
     * An external field was detected.
     *
     * No value is returned as part of this event.
     */
    NFC_FIELD_DETECTED_EVENT                    = 9,

    /**
     * The emulated NDEF tag has been selected by a remote reader device.
     *
     * No value is returned as part of this event.
     */
    NFC_VIRTUAL_TAG_SELECTION_EVENT             = 10,

    /**
     * The NDEF tag emulation detects that the remote reader device has
     * left the field.
     *
     * No value is returned as part of this event.
     */
    NFC_VIRTUAL_TAG_LEFT_EVENT                  = 11,

    /**
     * A remote reader device has read from the emulated NDEF tag.
     * Feature set 2 does not support this event.
     *
     * No value is returned as part of this event.
     */
    NFC_VIRTUAL_TAG_READ_EVENT                  = 12,

    /**
     * The emulated NDEF tag has been written to by a remote reader device.
     *
     * No value is returned as part of this event.
     *
     * This event has been defined for the sake of completeness. Since
     * NDEF tags are emulated only in read-only mode, it is not possible
     * to write to an emulated NDEF tag and hence this event will never be sent
     * to the client.
     */
    NFC_VIRTUAL_TAG_WRITE_EVENT                 = 13,

    /**
     * The NDEF message has been successfully pushed to the remote device.
     *
     * No value is returned as part of this event.
      */
    NFC_NDEF_PUSH_SUCCEED_EVENT                 = 20,

    /**
     * The remote device has rejected the NDEF push message because the message
     * is too large.
     *
     * No value is returned as part of this event.
     */
    NFC_NDEF_PUSH_FAILURE_MSG_OVER_SIZE_EVENT   = 21,

    /**
     * The remote device has rejected the NDEF push message.
     *
     * No value is returned as part of this event.
     */
    NFC_NDEF_PUSH_FAILURE_REJECTED_EVENT        = 22,

    /**
     * The NDEF message push failed because of the I/O error.
     *
     * No value is returned as part of this event.
     */
    NFC_NDEF_PUSH_FAILURE_IO_ERROR_EVENT        = 23,

    /**
     * The NDEF message push failed because of version mismatch.
     *
     * No value is returned as part of this event.
     */
    NFC_NDEF_PUSH_FAILURE_VERSION_MISMATCH_EVENT = 24,

    /**
     * The NFC connection handover negotiation failed because the transport is
     * not supported.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #nfc_handover_failure_reason_t values as part of this event code:
     * - @c #NFC_TRANSPORTS_UNAVAILABLE: Handover failed because transports
     *   on the local device are not available to participate in the negotiation.
     * - @c #NFC_TRANSPORTS_NOT_SUPPORTED_BY_LOCAL: Handover failed because
     *   requested transports are not supported by the local device.
     * - @c #NFC_TRANSPORTS_NOT_SUPPORTED_BY_REMOTE: Handover failed because
     *   requested transports are not supported by the remote device.
     *
    */
    NFC_HANDOVER_FAILURE_NO_TRANSPORT_EVENT     = 30,

    /**
     * The NFC connection handover negotiation failed because the handover
     * version used is not supported.
     *
     * No value is returned as part of this event.
    */
    NFC_HANDOVER_FAILURE_VERSION_MISMATCH_EVENT = 31,

#ifndef OMIT_FROM_DOXYGEN
    /**
     * @internal
     * The NFC connection handover requests for the NDEF record from the local transport.
     * This is an internal only event.
     *
     * You can call the @c nfc_get_target() function to retrieve handover
     * details from the target that contains connection handover details.
     */
    NFC_REQUEST_LOCAL_RECORD_EVENT              = 32,
#endif

    /**
     * The NFC connection handover negotiation failed due to an error
     * during version negotiation. This means that the request message
     * was either not received or not valid.
     *
     * No value is returned as part of this event.
    */
    NFC_HANDOVER_FAILURE_DURING_VERSION_NEGOTIATION_EVENT = 33,

    /**
     * The NFC ISO14443_4 command event.
     *
     * You can retrieve the target by calling @c nfc_get_target().
     */
    NFC_ISO14443_4_COMMAND_EVENT                = 40,

    /**
     * The NFC ISO14443_4 command event code.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #iso14443_4_event_t values as part of this event code:
     * - @c #ISO14443_4EVENT_SELECTED: The HCE-emulated card has been selected
     *                                 by the remote reader.
     * - @c #ISO14443_4EVENT_DEACTIVATED: The HCE-emulated card has been deactivated
     *                                    by the remote reader.
     */
    NFC_ISO14443_4_EVENT_CODE_EVENT             = 41,

    /**
     * The NFC LLCP read complete event code.
     *
     * You can retrieve the target by calling @c nfc_get_target().
     */
    NFC_LLCP_READ_COMPLETE_EVENT                = 42,

    /**
     * The NFC LLCP write complete event code.
     *
     * You can retrieve the target by calling @c nfc_get_target().
     */
    NFC_LLCP_WRITE_COMPLETE_EVENT               = 43,
    /**
     * A programmatic attempt to enable the "Allow Card
     * Transactions When locked or backlight is off" user setting.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_SUCCESS: The user allowed the setting change and the
     *                           setting was changed successfully.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the setting change.
     */
    NFC_CE_ENABLE_BACKLIGHT_OFF_EVENT           = 44,

    /**
     * A programmatic attempt to enable the "Allow Card Transactions When
     * device is turned off" user setting.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_SUCCESS: The user allowed the setting change and the
     *                           setting was changed successfully.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the setting change.
     */
    NFC_CE_ENABLE_POWERED_OFF_EVENT             = 45,

    /**
     * A programmatic attempt to disable the "Allow Card Transactions When
     * locked or backlight is off" user setting.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_SUCCESS: The user allowed the setting change and the
     *                           setting was changed successfully.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the setting change.
     */
    NFC_CE_DISABLE_BACKLIGHT_OFF_EVENT          = 46,

    /**
     * A programmatic attempt to disable the "Allow Card Transactions When
     * device is turned  off" user setting.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_SUCCESS: The user allowed the setting change and the
     *                           setting was changed successfully.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the setting change.
     */
    NFC_CE_DISABLE_POWERED_OFF_EVENT            = 47,

    /**
     * A programmatic attempt to set the UICC as the active secure element
     *
     * Use the @c nfc_get_notification_value() function to retrieve the following
     * @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_SUCCESS: The change was successful as the  active secure
     *                           element was already the UICC or the user
     *                           allowed the active secure element to become
     *                           the UICC.
     * - @c #NFC_RESULT_SE_NOT_PRESENT: The change was unsuccessful as no UICC
     *                                  secure element was detected.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the request to
     *                                      change the active secure element to
     *                                      the UICC.
     */
    NFC_CE_SET_UICC_ACTIVE_SE_TYPE_EVENT        = 48,

    /**
     * An NFC target is no longer being detected within the NFC field.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the target
     * connection id.
     */
    NFC_TARGET_LOST_EVENT                       = 49,

    /**
     * A programmatic attempt to enable the "NFC Connectivity" user setting.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the
     * following @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_SUCCESS: The user allowed the setting change and the
     *                           setting was changed successfully.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the setting change.
     * - @c #NFC_RESULT_RESOURCE_BUSY: The user allowed the setting change, but
     *                           setting could not be applied.
     */
    NFC_SETTING_ENABLED_ASYNC_EVENT             = 50,

    /**
     * An error occurred on the communication channel.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the
     * following @c #nfc_result_t values as part of this event code:
     * - @c #NFC_RESULT_OUT_OF_MEMORY: Too many events were queued up on the service
     *                                 and have been discarded.
     */
    NFC_CHANNEL_ERROR_EVENT                     = 60

} nfc_event_type_t;

/**
 * @brief NFC channel types
 * @details This enumeration defines the various NFC channels that are
 *          supported.
 */
typedef enum {
    /**
     * Unknown channel type.
     */
    NFC_CHANNEL_TYPE_UNKNOWN                    = -1,
    /**
     * A public channel used for communication.
     */
    NFC_CHANNEL_TYPE_PUBLIC                     = 0,
    /**
     * A secure channel used to communicate with universal integrated circuit
     * card (UICC) secure element (SE) types.
     */
    NFC_CHANNEL_TYPE_SE_UICC                    = 1,
    /**
     * A secure channel used for embedded SEs.
     */
    NFC_CHANNEL_TYPE_SE_EMBEDDED                = 2,

#ifndef OMIT_FROM_DOXYGEN
    /**
     * @internal An internal channel.
     */
    NFC_CHANNEL_TYPE_INTERNAL                   = 3
#endif
} nfc_channel_type_t;

/**
 * @brief This enumeration defines the various status masks for NFC channel
 *        status
 */
typedef enum {
    /**
     * Indicates an NFC hardware support type. The bit is set when device
     * hardware supports NFC.
     */
    NFC_CHANNEL_STATUS_HARDWARE_PRESENT         = (0x1 << 0),

    /**
     * Indicates a carrier support type. The bit is set when carrier
     * configuration allows NFC.
     */
    NFC_CHANNEL_STATUS_CARRIER_SUPPORTED        = (0x1 << 1),

    /**
     * Indicates an IT policy support type. The bit is set when IT policy
     * allows NFC.
     */
    NFC_CHANNEL_STATUS_IT_POLICY_ALLOWED        = (0x1 << 2),

    /**
     * Indicates the NFC status relative to the wireless charging status.
     * This bit is set when NFC is allowed while the device is not
     * on a wireless charger.
     * When a device is on a wireless charger, the field of the
     * wireless charger disturbs the NFC field, and NFC doesn't work.
     * For devices that are capable of wireless charging, NFC is disabled
     * while a device is on a wireless charger.
     */
    NFC_CHANNEL_STATUS_WIRELESS_CHARGER_ALLOWED = (0x1 << 3),

} nfc_channel_status_mask_t;

/**
 * @brief NFC Data Exchange Format(NDEF) Type Name Format (TNF) type
 * @details This enumeration defines the TNFs specified in the  NFC-Forum NDEF
 *          specification.
 */
typedef enum {
    /**
     * Empty TNF indicates that there is no type or payload associated with
     * this record.
     */
    NDEF_TNF_EMPTY                              = 0,
    /**
     * Well known TNF indicates that the TYPE field contains a value that
     * follows the Record Type Definition (RTD) type name format
     * defined in the NFC Forum RTD specification.
     */
    NDEF_TNF_WELL_KNOWN                         = 1,
    /**
     * Media TNF indicates that the TYPE field contains a value that
     * follows the media-type BNF grammar defined in RFC 2046.
     */
    NDEF_TNF_MEDIA                              = 2,
    /**
     * Absolute URI TNF indicates that the @e Type field contains a value
     * that follows the absolute-URI BNF construct defined by RFC 3986.
     */
    NDEF_TNF_ABSOLUTE_URI                       = 3,
    /**
     * External TNF indicates that the TYPE field contains a value that
     * follows the type name format defined in specification
     * NFC Record Type Definition (RTD) Specification for external type names.
     */
    NDEF_TNF_EXTERNAL                           = 4,
    /**
     * Unknown TNF indicate that the type of the payload is unknown.
     */
    NDEF_TNF_UNKNOWN                            = 5,
    /**
     * Unchanged TNF must be used in all middle record chunks and the
     * terminating record chunk used in chunked payloads. It must not be used
     * in any other record.
     */
    NDEF_TNF_UNCHANGED                          = 6,
} tnf_type_t;


/**
 * @brief NFC tag types
 * @details This enumeration defines tag types as specified in the NFC Forum.
 */
typedef enum {
    /**
     * NFC-Forum tag type 1.
     */
    NDEFTAG_TYPE_1                              = 1,
    /**
     * NFC-Forum tag type 2.
     */
    NDEFTAG_TYPE_2                              = 2,
    /**
     * NFC-Forum tag type 3.
     */
    NDEFTAG_TYPE_3                              = 3,
    /**
     * NFC-Forum tag type 4A.
     */
    NDEFTAG_TYPE_4_A                            = 4,
    /**
     * NFC-Forum tag type 4B.
     */
    NDEFTAG_TYPE_4_B                            = 5,
} ndef_tag_type_t;

#ifndef OMIT_FROM_DOXYGEN
/**
 * @brief Card types
 * @details This enumeration defines card types that can be emulated.
 *          Deprecated. Do not use it.
 */
typedef enum {
    /**
     * A card that does not fall into any of the below card types.
     */
    SE_CARD_TYPE_OTHER                          = 1,
    /**
     * A card that is used for payment.
     */
    SE_CARD_TYPE_PAYMENT                        = 2,
    /**
     * A card that is used for physical access.
     */
    SE_CARD_TYPE_ACCESS                         = 3,
    /**
     * A card type that is used for transit.
     */
    SE_CARD_TYPE_TRANSIT                        = 4,
} se_card_type_t;
#endif

/**
 * @brief NFC tag types
 * @details This enumeration defines NFC tag types.
 */
typedef enum {
    /**
     * Tag type based on an ISO 14443-3 connection.
     */
    TAG_TYPE_ISO_14443_3                        = (0x1 << 0),
    /**
     * Tag type based on an ISO 14443-4 connection.
     */
    TAG_TYPE_ISO_14443_4                        = (0x1 << 1),
    /**
     * Tag type based on an NDEF connection.
     */
    TAG_TYPE_NDEF                               = (0x1 << 2),
    /**
     * Tag type based on an ISO 15693-3 connection.
     */
    TAG_TYPE_ISO_15693_3                        = (0x1 << 3),

    /**
     * Tag type based on an ISO 18092 connection
     */
    TAG_TYPE_ISO_18092                          = (0x1 << 4),

    /**
     * All tag types enabled.
     */
    TAG_TYPE_ALL                                = (0xFFFF),

    #ifndef OMIT_FROM_DOXYGEN
    /**
     * For internal use only. Do not use.
     *
     * Kovio RF Barcode tag type
     */
    TAG_TYPE_KOVIO_TAG                          = (0x1 << 16),
    #endif
} nfc_tag_type_t;

#ifndef OMIT_FROM_DOXYGEN
typedef enum {
/**
 * @brief NFC tag discovery options
 * @details This enumeration defines NFC tag discovery options.
 */
    /**
     * internal use to suppress the timeout
     */
    TAG_SUPPRESS_TIMEOUT                        = (0x2 << 29),
    TAG_SUPPRESS_TIMEOUT_MASK                   = (0x3 << 29),
} nfc_discovery_options_t;
#endif

/**
 * @brief NFC tag properties
 * @details This enumeration defines NFC tag properties.
 */
typedef enum {
    /**
     * Whether the tag supports ISO14443-3 A or B technology.
     */
    TAG_PROP_ISO_14443_3_TYPE                   = 1,

    /**
     * Whether the tag supports ISO14443-4 A or B technology.
     */
    TAG_PROP_ISO_14443_4_TYPE                   = 2,

    /**
     * Whether the tag contains NFC Data Exchange Format(NDEF) data.
     */
    TAG_PROP_NDEF_TYPE                          = 3,

    /**
     * Whether the NDEF tag is locked.
     */
    TAG_PROP_NDEF_LOCKED                        = 4,

    /**
     * Whether the NDEF tag is lockable.
     */
    TAG_PROP_NDEF_LOCKABLE                      = 5,

    /**
     * The amount of free memory (in bytes) left on the NDEF tag. This value is
     * reported even when the tag is locked.
     */
    TAG_PROP_NDEF_FREE_SPACE                    = 6,

    /**
     * The serial number of the NDEF tag.
     */
    TAG_PROP_NDEF_SERIAL_NUMBER                 = 7,

    /**
     * Whether the tag can be formatted via a write operation. This means that
     * the tag is not a valid NFC formatted type. This enumerated value
     * supports type 1 and type 2 tags. Tag types are represented by a
     * @c #ndef_tag_type_t value. See the specific function description for more
     * information about the error.
     */
    TAG_PROP_NDEF_CAPABLE_TYPE                  = 8,

    /**
     * The raw capacity of memory on the tag. The capacity is represented in
     * bytes. This enumerated value supports type 1 and type 2 tags. Tag types
     * are represented by a @c #ndef_tag_type_t value. See the specific
     * function description for more information about the error.
     */
    TAG_PROP_NDEF_CAPABLE_TAG_SIZE              = 9,

    #ifndef OMIT_FROM_DOXYGEN
    /**
     * For internal use only. Do not use.
     */
    TAG_PROP_NDEF_CAPABLE_UID                   = 10,
    #endif

    /* ISO 15693 specific properties */
    /**
     * Whether a tag supports ISO 15693-3.
     */
    TAG_PROP_ISO_15693_3_TYPE                   = 11,

    /**
     * Whether a ISO 15693-3 tag supports Application
     * Family Identifier (AFI).
     */
    TAG_PROP_AFI_SUPPORTED                      = 12,

    /**
     * Whether the ISO 15693-3 tag's AFI is locked.
     */
    TAG_PROP_AFI_LOCKED                         = 13,

    /**
     * Whether the ISO 15693-3 tag supports Data Storage Format Identifier
     * (DSFID).
     */
    TAG_PROP_DSFID_SUPPORTED                    = 14,

    /**
     * Whether the ISO 15693-3 tag's DSFID is locked.
     */
    TAG_PROP_DSFID_LOCKED                       = 15,

    /**
     * The ISO 15693 tag's AFI.
     */
    TAG_PROP_AFI                                = 16,

    /**
     * The ISO 15693 tag's DSFID.
     */
    TAG_PROP_DSFID                              = 17,

    /**
     * The ISO 15693 tag's sector size (in bytes).
     */
    TAG_PROP_SECTOR_SIZE                        = 18,

    /**
     * The ISO 15693 tag's sector number.
     */
    TAG_PROP_SECTOR_NUMBER                      = 19,

    #ifndef OMIT_FROM_DOXYGEN
    /**
     * For internal use only. Do not use.
     *
     * Whether the tag supports Kovio RF Barcode technology.
     */
    TAG_PROP_KOVIO_TYPE                         = 20,
    #endif

    /* ISO 18092 specific properties */
    /**
     * Whether a tag supports ISO 18092.
     */
    TAG_PROP_ISO_18092_TYPE                     = 21,

    /* FeliCa tag propertes */
    /**
     * System code of the first system (System 0) detected on the FeliCa tag
     */
    TAG_PROP_SYSTEM_CODE                        = 22,

    /**
     * Manufacturer parameter of the first system (System 0) detected on the FeliCa tag
     */
    TAG_PROP_MANUFACTURER_PARAM                 = 23,
} target_property_type_t;


/**
 * @brief Smart card types
 * @details The enumeration indicates the type of smart card. Smart cards can be
 *          either microprocessors or memory cards.
 */
typedef enum {
    /**
     * Smart cards that provide access to ISO 14443-3 Type A properties and
     * input/output operations.
     */
    PLAIN_TYPE_14443_3_A                        = 1,

    /**
     * Smart cards that provide access to ISO 14443-3 Type B  properties and
     * input/output operations.
     */
    PLAIN_TYPE_14443_3_B                        = 2,
} plain_type_t;


/**
 * @brief Host Card Emulation (HCE) protocol types
 * @details This enumeration defines HCE protocol types.
 */
typedef enum {
    /**
     * HCE in ISO 14443-4A.
     */
    ISO14443_4TYPE_A                            = 1,
    /**
     * HCE in ISO 14443-4B.
     */
    ISO14443_4TYPE_B                            = 2,
} iso14443_4_type_t;


/**
 * @brief Host Card Emulation (HCE) event types
 * @details This enumeration defines HCE event types.
 */
typedef enum {
    /**
     * The emulated ISO 14443-4 card (HCE) has been selected by remote reader.
     */
    ISO14443_4EVENT_SELECTED                    = 1,
    /**
     * The emulated ISO 14443-4 card (HCE) has been deactivated by remote reader.
     */
    ISO14443_4EVENT_DEACTIVATED                 = 2,
} iso14443_4_event_t;


/**
 * @brief Types of card emulation an application can perform.
 * @details This enumeration describes the types of card emulation an application can perform.
 */
typedef enum {
    /**
     * The application does not use any of the specified types below.
     */
    APP_CATEGORY_OTHER                          = 1,
    /**
     * The application is used for payment.
     */
    APP_CATEGORY_PAYMENT                        = 2,
    /**
     * The application is used for physical access.
     */
    APP_CATEGORY_ACCESS                         = 3,
    /**
     * The application is used for transit.
     */
    APP_CATEGORY_TRANSIT                        = 4,
    /**
     * The application is used for loyalty cards.
     */
    APP_CATEGORY_LOYALTY                        = 5,
} app_category_type_t;


/**
 * @brief NFC Data Exchange Format(NDEF) tag types
 * @details This enumeration defines NDEF tag types.
 */
typedef enum {
    /**
     * NFC-Forum tag type 1.
     */
    NDEF_TYPE_1                                 = 1,
    /**
     * NFC-Forum tag type 2.
     */
    NDEF_TYPE_2                                 = 2,
    /**
     * NFC-Forum tag type 3.
     */
    NDEF_TYPE_3                                 = 3,
    /**
     * NFC-Forum tag type 4A.
     */
    NDEF_TYPE_4_A                               = 4,
    /**
     * NFC-Forum tag type 4B.
     */
    NDEF_TYPE_4_B                               = 5,
} ndef_type_t;


/**
 * @brief Third-party NFC tag types
 * @details This enumeration defines various third-party NFC tag types.
 */
typedef enum {
    /**
     * Unknown tag type.
     */
    TAGVARIANT_UNKNOWN                          = 1,
    /**
     * The Jewel tag type from Broadcom.
     */
    TAGVARIANT_JEWEL                            = 2,
    /**
     * The Topaz 96 tag type from Broadcom.
     */
    TAGVARIANT_TOPAZ                            = 3,
    /**
     * The Topaz 512 tag type from Broadcom.
     */
    TAGVARIANT_TOPAZ_512                        = 4,
    /**
     * The MIFARE Ultralight tag type from NXP Semiconductors.
     */
    TAGVARIANT_MIFARE_UL                        = 5,
    /**
     * The MIFARE UltralightC tag type from NXP Semiconductors.
     */
    TAGVARIANT_MIFARE_UL_C                      = 6,
    /**
     * The MIFARE DESFire D40 tag type from NXP Semiconductors.
     */
    TAGVARIANT_DESFIRE_D40                      = 7,
    /**
     * The MIFARE DESFire EV1 2K tag type from NXP Semiconductors.
     */
    TAGVARIANT_DESFIRE_EV1_2K                   = 8,
    /**
     *  The MIFARE DESFire EV1 4K tag type from NXP Semiconductors.
     */
    TAGVARIANT_DESFIRE_EV1_4K                   = 9,
    /**
     * The MIFARE DESFire EV1 8K tag type from NXP Semiconductors.
     */
    TAGVARIANT_DESFIRE_EV1_8K                   = 10,

    /* ISO15693 tag variants */
    /**
     * The Tag-it tag type from Texas Instruments.
     */
    TAGVARIANT_TI_TAGIT                         = 11,
    /**
     * The LRI 512 tag type from STMicroelectronics.
     */
    TAGVARIANT_ST_LRI_512                       = 12,
    /**
     * The LRI 2K tag type from STMicroelectronics.
     */
    TAGVARIANT_ST_LRI_2K                        = 13,
    /**
     * The ICODE tag type from NXP Semiconductors.
     */
    TAGVARIANT_NXP_ICODE                        = 14,

    #ifndef OMIT_FROM_DOXYGEN
    /**
     * For internal use only. Do not use.
     *
     * The Kovio RF Barcode tag type from Kovio
     */
    TAGVARIANT_KOVIO                            = 15,
    #endif

    /**
     *  The MIFARE 1K tag type from NXP Semiconductors.
     */
    TAGVARIANT_MIFARE_1K                        = 16,
    /**
     *  The MIFARE 4K tag type from NXP Semiconductors.
     */
    TAGVARIANT_MIFARE_4K                        = 17,
    /**
     *  The MIFARE MINI tag type from NXP Semiconductors.
     */
    TAGVARIANT_MIFARE_MINI                      = 18,

    /**
     *  The my-d move tag type from Infineon Technologies.
     */
    TAGVARIANT_MY_D_MOVE                        = 19,
    /**
     * The my-d NFC tag type from Infineon Technologies.
     */
    TAGVARIANT_MY_D_NFC                         = 20,

    /**
     * The LRI 1K tag type from STMicroelectronics.
     */
    TAGVARIANT_ST_LRI_1K                        = 21,
    /**
     * The LRI S2K tag type from STMicroelectronics.
     */
    TAGVARIANT_ST_LRI_S2K                       = 22,
    /**
     * The LRI S64K tag type from STMicroelectronics.
     */
    TAGVARIANT_ST_LRI_S64K                      = 23,

    /**
     *  The FeliCa tag type from Sony
     */
    TAGVARIANT_FELICA                           = 24,
} tag_variant_type_t;


/**
 * @brief Logical Link Control Protocol (LLCP) connection types
 * @details This enumeration defines LLCP NFC connection types.
 */
typedef enum {
    /**
     * Unknown LLCP connection type.
     */
    NFC_LLCP_UNKNOWN_CONNECTION_TYPE            = 0x00,
    /**
     * Server connection type. A Logical Link Control Protocol(LLCP) server
     * waits for an LLCP client to connect to it.
     */
    NFC_LLCP_SERVER                             = 0x01,
    /**
     * The Client connection type. An LLCP client attempts try to connect to a
     * remote LLCP server.
     */
    NFC_LLCP_CLIENT                             = 0x02,
    /**
     * Passive Server connection. A passive LLCP server is an LLCP server
     * which configures lower NFC Interface and Protocol (NFCIP1) layer to only
     * use the target role.
     */
    NFC_LLCP_SERVER_PASSIVE                     = 0x05,
} nfc_llcp_connection_type_t;


/**
 *  @brief Connection handover transport types
 *  @details This enumeration defines connection handover transport types.
 */
typedef enum {
    /**
     * Unknown handover transport type.
     */
    UNKNOWN_HANDOVER_TRANSPORT_TYPE             = 0,
    /**
     * The Bluetooth connection handover transport type.
     */
    BLUETOOTH_HANDOVER                          = 1,
    /**
     * The Wi-Fi Direct connection handover transport type.
     */
    WIFI_DIRECT_HANDOVER                        = 2,
} handover_transport_type_t;

/**
 * @brief Connection handover roles
 * @details This enumeration defines connection handover roles. Roles are
 *          specified in NFC-Forum Connection Handover Technical
 *          Specification v1.2.
 */
typedef enum {
    /**
     * Unknown handover role.
     */
    UNKNOWN_HANDOVER_ROLE                       = 0,
    /**
     * Connection handover requester role.
     */
    REQUESTER_ROLE                              = 1,
    /**
     *  Connection handover selector role.
     */
    SELECTOR_ROLE                               = 2,
} handover_role_t;

/**
 * @brief Reasons for a connection handover failure
 * @details This enumeration defines the reasons for a connection handover failure.
 */
typedef enum {
    /**
     * Handover failed because transports on the local device are not available
     * to participate in the handover negotiation.
     */
    NFC_TRANSPORTS_UNAVAILABLE                  = 1,
    /**
     *  Handover failed because the local device doesn't support the
	 *  requested transports.
     */
    NFC_TRANSPORTS_NOT_SUPPORTED_BY_LOCAL       = 2,
    /**
     *  Handover failed because the remote device doesn't support the
	 *  requested transports.
     */
    NFC_TRANSPORTS_NOT_SUPPORTED_BY_REMOTE      = 3,
} nfc_handover_failure_reason_t;

/**
 * @brief The secure element ID
 * @details This enumeration defines the unique identifier of the Secure
 *          Element.
 */
typedef enum {
    /**
     * No secure element.
     */
    SE_ID_NONE                                  = 0,
    /**
     * A Universal Integrated Circuit Card (UICC) secure element.
     */
    UICC_SE_ID                                  = 1,
    /**
     * An embedded secure element.
     */
    EMBEDDED_SE_ID                              = 2,
} secure_element_id_type_t;


/**
 * @brief File Control Parameter (FCP) type tags
 * @details This enumeration controls the @c P2 value used in the @c SELECT
 *          command when opening channel. This informs the Universal Integrated
 *          Circuit Card (UICC) of what format the device would like to receive
 *          the returned data in.
 */
typedef enum SATSAFcpTypeTag
{
    /**
     * Set the P2 value to 0x0C.
     */
    OPEN_NO_FCP_INFO                            = 1,
    /**
     * Set the P2 value to 0x00.
     */
    OPEN_FCP_WITH_REF_CLASS                     = 2,
    /**
     * Set the P2 value to 0x10
     */
    OPEN_FCP_WITH_REF_INTERFACE                 = 3,
    /**
     * Set the P2 value to 0x00.
     */
    SATSA_OPEN_EMV_FCP                          = 4
} fcp_type_t;


/**
 * @brief Battery modes
 * @details This enumeration defines battery modes. The battery modes are used
 *          to configure card emulation mode for Universal Integrated Circuit
 *          Card (UICC) or embedded secure elements.
 */
typedef enum {
    /**
     * The device is powered on.
     */
    BATTERY_MODE_ON                             =  1,
    /**
     * In feature set 1, this value indicates
     * that the device is not running on battery or the battery has been
     * removed.
     * In feature set 2, this value indicates
     * that the device has been turned off by the user or is off due to low
     * battery power.
     */
    BATTERY_MODE_OFF                            =  2
} battery_mode_t;


/**
 * @brief Technology types
 * @details This enumeration defines the technology types used to configure card
 *          emulation mode for Universal Integrated Circuit Card (UICC) or
 *          embedded secure element.
 */
typedef enum {
    /**
     *  No technology types are configured.
     */
    TECHNOLOGY_TYPE_NONE                        = (0x0),
    /**
     * ISO 14443-A-based card emulation.
     */
    TECHNOLOGY_TYPE_ISO14443A                   = (0x1 << 0),
    /**
     * ISO 144433-B-based card emulation.
     */
    TECHNOLOGY_TYPE_ISO14443B                   = (0x1 << 1),
    /**
     * ISO 144433-B'-based card emulation.
     */
    TECHNOLOGY_TYPE_ISO14443B_PRIME             = (0x1 << 2),
    /**
     * FeliCa-based card emulation.
     */
    TECHNOLOGY_TYPE_FELICA                      = (0x1 << 3),
    /**
     * MIFARE Classic-based card emulation.
     */
    TECHNOLOGY_TYPE_ISO14443A_MIFARE            = (0x1 << 4),
    /**
     * ISO 15693-based card emulation.
     */
    TECHNOLOGY_TYPE_ISO15693                    = (0x1 << 5),
} technology_types_t;

/**
 * @brief Service States
 * @details This enumeration defines the valid states for a service installed on
 *          the secure element.
 */
typedef enum {
    /**
     *  The service is not installed.
     */
    SE_SERVICE_STATE_NOT_INSTALLED              = 0,
    /**
     *  A valid token for this service has been generated.
     */
    SE_SERVICE_STATE_TOKEN_GENERATED            = 1,
    /**
     *  A valid token for this service has been generated and sent to the
     *  service-provider's backend. Once the service-provider's
     *  backend has successfully forwarded the installation attempt to the
     *  RIM TSM, installation will start.
     */
    SE_SERVICE_STATE_TOKEN_SENT                 = 2,
    /**
     *  The service is in the process of being installed.
     */
    SE_SERVICE_STATE_INSTALLING                 = 3,
    /**
     *  The service is installed.
     */
    SE_SERVICE_STATE_INSTALLED                  = 4,
    /**
     *  The service is installed and personalized.
     */
    SE_SERVICE_STATE_PERSONALIZED               = 5,
    /**
     *  The service failed to install.
     */
    SE_SERVICE_STATE_FAILED                     = 6,
    /**
     *  Reserved for future use.
     */
    SE_SERVICE_STATE_BLOCKED                    = 7,
    /**
     *  The service is marked for deletion, but deletion has not started yet.
     */
    SE_SERVICE_STATE_PENDING_DELETION           = 8,
    /**
     *  The service is in the process of being deleted.
     */
    SE_SERVICE_STATE_DELETING                   = 9,
} se_service_state_t;


/**
 * @brief TSM (Trusted Services Manager) Proxy States
 * @details This enumeration defines the states the TSM proxy is in.
 */
typedef enum {
    /**
     *  The TSM proxy is idle.
     */
    TSM_PROXY_STATE_IDLE                        = 0,
    /**
     *  The TSM proxy is waiting for the device to regain connectivity before
     *  reaching out to the TSM.
     */
    TSM_PROXY_STATE_WAITING_FOR_CONNECTIVITY    = 1,
    /**
     *  The TSM proxy is downloading commands from the TSM.
     */
    TSM_PROXY_STATE_FETCHING_COMMANDS_FROM_TSM  = 2,
    /**
     *  The TSM proxy is executing commands from the TSM.
     */
    TSM_PROXY_STATE_EXECUTING_COMMANDS                = 3,
    /**
     *  The TSM proxy is attempting to contact the TSM.
     */
    TSM_PROXY_STATE_ATTEMPTING_TO_CONTACT_TSM         = 4,

} tsm_proxy_state_t;


/**
 * @brief NFC property types
 * @details This enumeration defines the properties of the device which an
 *          application can retrieve by calling @c nfc_get_property().
 */
typedef enum {
    /**
     * Property to determine if the device supports battery low mode.
     */
    NFC_PROPERTY_BATTERY_LOW_SUPPORTED              = 0,
    /**
     * Property to determine if the device supports the battery off mode.
     */
    NFC_PROPERTY_BATTERY_OFF_SUPPORTED              = 1,
    /**
     * Property to determine if the device supports emulation of the NFC Forum
     * Type 3 Tag on the device host.
     */
    NFC_PROPERTY_T3T_CARD_EMULATION_SUPPORTED       = 2,
    /**
     * Property to determine if the device supports card emulation for FeliCa on
     * the UICC.
     */
    NFC_PROPERTY_FELICA_CARD_EMULATION_SUPPORTED    = 3,
    /**
     * Property to determine if the device supports MIFARE Classic Reader/Writer.
     */
    NFC_PROPERTY_MIFARE_CLASSIC_SUPPORTED           = 4,
    /**
     * Property to determine if the device supports DESFire Classic Reader/Writer.
     */
    NFC_PROPERTY_MIFARE_DESFIRE_SUPPORTED           = 5,

} nfc_property_id_t;

/**
 * @brief GSMA property types
 * @details This enumeration defines the device properties that an application can
 *          request by calling @c com_gsma_services_nfc_get_property().
 */
typedef enum {
    /**
     * Property to determine the version of GSMA NFC Handset Requirements
     * that the device supports.
     */
    NFC_GSMA_PROPERTY_REQUIREMENT_REVISION               = 0,
} gsma_property_id_t;

#endif /* NFC_TYPES_H_ */

