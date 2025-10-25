/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc.h
 * This file provides functions for the Near Field Communication (NFC) API
 *
 * For complete specifications, go to the NFC Forum Specifications
 * page at http://www.nfc-forum.org/specs/.
 *
 */

#ifndef NFC_H_
#define NFC_H_

#include "nfc/nfc_api.h"
#include "nfc/nfc_types.h"
#include "nfc/nfc_ndef.h"

__BEGIN_DECLS

/**
 * Transceive response buffer length. This buffer size specifies the maximum
 * size of the response buffer that can be returned by the NFC service.
 */
#define NFC_TRANSCEIVE_RESPONSE_MAX_BUFFER_LENGTH    65536

/**
 * ISO 14443-4 command buffer length. This buffer size specifies the maximum
 * size of the command buffer that can be returned by the NFC service.
 */
#define NFC_ISO14443_4_COMMAND_BUFFER_LENGTH    256

/**
 * A structure that represents the NFC target
 */
struct nfc_target_t;

/**
 * @typedef struct nfc_target_t
 * A data type for the @c nfc_target_t structure
 */
typedef struct nfc_target_t nfc_target_t;

/**
 * @typedef struct nfc_event_t
 * A data type for the @c nfc_event_t structure
 */
typedef struct nfc_event_t nfc_event_t;

/**
 * A structure representing the card type based on the ISO 14443-4 Card Type A
 */
typedef struct {
    /**
     * Unique identifier as defined by ISO 14443-3 Type A specification.
     * This parameter can be either:
     *  - @c NULL so that an internal unique identifier is created by the NFC
     *    driver upon calling @c nfc_start_iso14443_4_emulation().
     *  - a 4-byte array in which the first byte is within the range 0xH0-0xH7
     *    or 0xH9-0xHE, where 'H' can be any hex value.
     */
    char    *identifier;
    /**
     * Size of @c identifier (in bytes). This is currently not used and must be
     * set to @c 0 by the application.
     */
    size_t  identifier_size;
    /**
     * Historical bytes as defined by ISO 14443-4 Type A specification.
     */
    char    *applicationData;
    /**
     * Size of @c applicationData (in bytes)
     */
    size_t  applicationData_size;
} nfc_iso14443_4_card_type_a_t;

/**
 * A structure representing the card type based on the ISO 14443-4 Card Type B
 */
typedef struct {
    /**
     * Unique identifier as defined by ISO 14443-3 Type B specification.
     * This parameter can be either:
     *  - @c NULL so that an internal unique identifier is created by the NFC
     *    driver upon calling @c nfc_start_iso14443_4_emulation().
     *  - a 4-byte array in which the first byte is within the range 0xH0-0xH7
     *    or 0xH9-0xHE, where 'H' can be any hex value.
     */
    char    *identifier;
    /**
     * Size of @c identifier (in bytes). This is currently not used and must be
     * set to 0 by the application.
     */
    size_t  identifier_size;
     /**
     * Application family identifier as defined by ISO 14443-3 Type B
     * specification.
     */
    char    afi;
    /**
     * Number of applications that reside in the card as defined by ISO 14443-3
     * Type B specification.
     */
    char    numOfApps;
    /**
    * Higher layer response in answer to ATTRIB command defined by
    * ISO 14443-3 Type B specification.
    */
    char    *higherLayerResponse;
    /**
     * Size of @c higherLayerResponse (in bytes)
     */
    size_t  higherLayerResponse_size;
} nfc_iso14443_4_card_type_b_t;

/**
 * A structure representing the card type and ISO 14443-4 emulation data
 */
typedef struct {
    /**
     * ISO 14443-4 emulation data.
     */
    iso14443_4_type_t type;
    /**
     * The card type based on ISO 14443-4.
     */
    union {
        /**
         * Card Type A.
         */
        nfc_iso14443_4_card_type_a_t A;
        /**
         * Card Type B.
         */
        nfc_iso14443_4_card_type_b_t B;
    } info;
} nfc_iso14443_4_card_t;

/**
 * An opaque type that represents Logical Link Control Protocol (LLCP)
 * connection
 */
typedef unsigned int nfc_llcp_connection_listener_t;

/** @brief This enumeration specifies the types of user settings that are
*          available from the NFC menu on the device
*/
typedef enum {

    /**
     * User setting responsible for the current status of the NFC radio
     * (on/off).
     *
     * This setting is reflected to the user as "NFC Connectivity" menu from the
     * device.
     *
     * It is important to note that @c NFC_SETTING_ENABLED can be set to
     * @c true, but not to @c false, by using the @c nfc_set_setting() function.
     * An attempt to set @c NFC_SETTING_ENABLED to @c false through this
     * function will result in an error of @c #NFC_RESULT_INVALID_PARAMETER.
     * NFC cannot be turned off programmatically; NFC remains enabled until the
     * user explicitly disables NFC from the NFC menu on the device.
     *
     * Enabling @c NFC_SETTING_ENABLED from the nfc_set_setting() function will
     * trigger a prompt to be displayed on the device to request permission to
     * modify this user setting. If @c NFC_SETTING_ENABLED is already enabled,
     * no prompt will be displayed. The @c nfc_set_setting() function blocks
     * the caller until the user makes a selection. If you don't want a
     * blocking call, you can use the @c NFC_SETTING_ENABLED_ASYNC variant
     * with @c nfc_set_setting().
     *
     * @c nfc_set_setting() returns one of the following codes of type
     * @c #nfc_result_t:
     * - @c #NFC_RESULT_SUCCESS: The user permitted the operation.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the operation, an
     * attempt was made to enable NFC when it was already enabled, or the
     * calling application was not in the foreground.
     * - @c #NFC_RESULT_RESOURCE_BUSY: The user allowed the setting change, but
     * the change could not be applied.
     *
     * The following rules apply when querying (via the @c nfc_get_setting()
     * function) the value of this user setting:
     *  - If NFC hardware is not supported, @c NFC_SETTING_ENABLED will be
     *    @c false.
     *  - If NFC is not allowed by configuration on the device,
     *    @c NFC_SETTING_ENABLED will be @c false.
     *  - If NFC radio is OFF, @c NFC_SETTING_ENABLED will be @c false.
     *  - If NFC radio is ON, @c NFC_SETTING_ENABLED will be @c true.
     */
    NFC_SETTING_ENABLED          = 0,

    /**
     * User setting governing whether or not card transactions are allowed when
     * the device is either locked or its backlight is off.
     *
     * This user setting is reflected to the user as "Allow NFC Card
     * Transactions When locked or backlight is off" from the NFC menu on the
     * device.
     *
     * An application attempting to change this setting must currently be in
     * the foreground.
     *
     * Enabling @c NFC_SETTING_CE_BACKLIGHT_OFF from the
     * nfc_set_setting() function will trigger a prompt to be displayed on the
     * device to request permission to modify this user setting.
     * If @c NFC_SETTING_CE_BACKLIGHT_OFF is already enabled, no prompt will
     * be displayed.
     *
     * Disabling @c NFC_SETTING_CE_BACKLIGHT_OFF from the nfc_set_setting()
     * function will trigger a prompt to be displayed on the device to request
     * permission to modify this user setting.
     * If @c #NFC_SETTING_CE_POWERED_OFF is enabled, then the user prompt
     * will additionally request permission to disable both
     * @c NFC_SETTING_CE_BACKLIGHT_OFF and @c #NFC_SETTING_CE_POWERED_OFF at the
     * same time. If @c NFC_SETTING_CE_BACKLIGHT_OFF is already disabled, no
     * prompt will be displayed.
     *
     * Note that @c nfc_set_setting() returns successfully, once the prompt is
     * displayed on the device. Whether you're enabling or disabling, an
     * @c #NFC_CE_ENABLE_BACKLIGHT_OFF_EVENT or an
     * @c #NFC_CE_DISABLE_BACKLIGHT_OFF_EVENT notification is respectively sent
     * to the application. This notification includes one of the following
     * return codes of type @c #nfc_result_t:
     * - @c #NFC_RESULT_SUCCESS (the user permitted the operation)
     * - @c #NFC_RESULT_OPERATION_REJECTED (the user denied the operation)
     *
     * Use the @c nfc_get_notification_value() function to retrieve the return
     * code from either the @c #NFC_CE_ENABLE_BACKLIGHT_OFF_EVENT or
     * the @c #NFC_CE_DISABLE_BACKLIGHT_OFF_EVENT notification.
     *
     */
    NFC_SETTING_CE_BACKLIGHT_OFF = 1,

    /**
     * User setting governing whether or not card transactions are enabled when
     * the device is powered off.
     *
     * An application attempting to change this setting must currently be in the
     * foreground.
     *
     * This user setting is represented by "Allow NFC Card Transactions When
     * device is turned off" from the NFC menu on the device. Note that in order
     * for this user setting to be enabled, "Allow NFC Card Transactions When
     * locked or backlight is off" must also be enabled.
     *
     * The user will be prompted by a display on the device to permit
     * modification to this user setting if you are setting a value that is
     * different from the current value of this setting.  If the user permits
     * this change, then Card Transactions while the device is powered off will
     * reflect the settings change at once.
     *
     * Enabling @c  NFC_SETTING_CE_POWERED_OFF from the nfc_set_setting()
     * function will trigger a prompt to be displayed on the device to request
     * permission to modify this user setting.
     * If @c #NFC_SETTING_CE_BACKLIGHT_OFF is disabled, then the user prompt
     * will additionally request permission to enable both
     * @c #NFC_SETTING_CE_BACKLIGHT_OFF and @c NFC_SETTING_CE_POWERED_OFF at the
     * same time. If @c NFC_SETTING_CE_POWERED_OFF is already enabled, no prompt
     * will be displayed.
     *
     * Disabling @c NFC_SETTING_CE_POWERED_OFF from the nfc_set_setting()
     * function will trigger a prompt to be displayed on the device to request
     * permission to modify this user setting. If @c  NFC_SETTING_CE_POWERED_OFF
     * is already disabled, no prompt will be displayed.
     *
     * Note that @c nfc_set_setting() returns successfully, once the prompt is
     * displayed on the device. Whether you're enabling or disabling, an
     * @c #NFC_CE_ENABLE_POWERED_OFF_EVENT or an
     * @c #NFC_CE_DISABLE_POWERED_OFF_EVENT notification is respectively sent to
     * the application. This notification includes one of the following return
     * codes of type @c #nfc_result_t:
     * - @c #NFC_RESULT_SUCCESS (the user permitted the operation)
     * - @c #NFC_RESULT_OPERATION_REJECTED (the user denied the operation)
     *
     * Use the @c nfc_get_notification_value() function to retrieve the return
     * code from either the @c #NFC_CE_ENABLE_POWERED_OFF_EVENT or the
     * @c #NFC_CE_DISABLE_POWERED_OFF_EVENT notification.
     */
    NFC_SETTING_CE_POWERED_OFF       = 2,

    /**
     * User setting that specifies whether the confirmation prompt "Do you want
     * to send file(s)?" should be presented when a user's attempt to send
     * files to another device is detected as a result of an NFC Tap gesture.
     *
     * This user setting can be changed only by the user from the NFC menu on
     * the device. It cannot be changed using the @c nfc_set_setting()
     * function.
     */
    NFC_SETTING_PROMPT_TO_SEND_FILES = 3,

    /**
     * User setting responsible for the current status of the NFC radio
     * (on/off).
     *
     * This is the asynchronous variant of @c NFC_SETTING_ENABLED and
     * may be used in conjunction with @c nfc_set_setting().
     *
     * Enabling @c NFC_SETTING_ENABLED_ASYNC from the nfc_set_setting()
     * function will trigger a prompt to be displayed on the device to request
     * permission to modify this user setting.
     * If @c NFC_SETTING_ENABLED_ASYNC is already enabled, no prompt will be
     * displayed.
     *
     * An attempt to call @c NFC_SETTING_ENABLED_ASYNC from the nfc_get_setting()
     * function will result in an error of @c #NFC_RESULT_INVALID_PARAMETER.
     *
     * It is important to note that @c NFC_SETTING_ENABLED_ASYNC can be set to
     * @c true, but not to @c false, by using the @c nfc_set_setting() function.
     * An attempt to set @c NFC_SETTING_ENABLED_ASYNC to @c false through this
     * function will result in an error of @c #NFC_RESULT_INVALID_PARAMETER.
     * NFC cannot be turned off programmatically; NFC remains enabled until the
     * user explicitly disables NFC from the NFC menu on the device.
     *
     * Note that @c nfc_set_setting() returns successfully, once the prompt is
     * displayed on the device. After the user makes a selection an
     * @c #NFC_SETTING_ENABLED_ASYNC_EVENT notification is sent to the
     * application. This notification includes one of the following return
     * codes of type @c #nfc_result_t:
     * - @c #NFC_RESULT_SUCCESS: The user permitted the operation.
     * - @c #NFC_RESULT_OPERATION_REJECTED: The user denied the operation.
     * - @c #NFC_RESULT_RESOURCE_BUSY: The user allowed the setting change, but
     * the setting could not be applied.
     *
     * Use the @c nfc_get_notification_value() function to retrieve the return
     * code from the @c #NFC_SETTING_ENABLED_ASYNC_EVENT notification.
     */
    NFC_SETTING_ENABLED_ASYNC        = 4

} nfc_settings_t;

/**
 * @brief Set the verbosity of logging for NFC API-specific logs
 * @details This function sets the level of detail in the logs captured. By
 *          default, no logging output is generated for NFC operations. If you
 *          intend to use NFC API-specific logging, then set the verbosity to
 *          one of the following valid values:
 *          - 0: No logs are generated.
 *          - 1: Error and warning logs are generated.
 *          - 2: Error, warning, and information logs are generated.
 *
 *          When logging is enabled, logs are generated on @c stderr and are
 *          captured in your application's log file. (i.e.,
 *          /accounts/1000/appdata/\<sandbox\>/logs/log).
 *
 * @param verbosity The verbosity level to set.
 *
 * @return None.
 */
NFC_API void nfc_set_verbosity(unsigned verbosity);

/**
 * @brief Connect to the NFC system and start receiving NFC events
 * @details This function connects the application to the NFC system and
 *          starts to receive NFC events.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: A connection is already
 *           established.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system failed.
 */
NFC_API nfc_result_t nfc_connect();

/**
 * @brief Disconnect from the NFC system and stop receiving NFC events
 * @details This function disconnects the application from the NFC system and
 *          stops receiving NFC events. Applications must always call this
 *          function as part of their teardown process.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: A connection is already
 *           disconnected.
 *         - @c #NFC_RESULT_FD_ACCESS_ERROR: NFC file descriptors are
 *           inaccessible or corrupted. This cause is likely due to the
 *           client accessing NFC file descriptors manually. This error is not
 *           fatal as the client is disconnected from NFC following this error
 *           and should be able to subsequently reconnect.
 */
NFC_API nfc_result_t nfc_disconnect();

/**
 * @brief Retrieve the file descriptor that connects to the NFC system
 * @details This function retrieves the file descriptor that connects to a
 *          specific NFC system channel. Applications communicate with the NFC
 *          system via the file descriptor. Applications must not close file
 *          descriptors manually; instead, @c nfc_disconnect() must be used.
 *
 * @param type The channel type in @c #nfc_channel_type_t.
 * @param fd   The returned file descriptor.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_get_fd(nfc_channel_type_t type, int *fd);

/**
 * @brief Receive NFC events
 * @details This function receives the @c nfc_event_t from the NFC system.
 *
 * @param fd The file descriptor retrieved using the @c nfc_get_fd() function
 *           call.
 * @param event The output NFC event. The event shall be disposed through the
 *              @c nfc_free_event() function @b only when this function returns
 *              @c #NFC_RESULT_SUCCESS.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: The event queue is empty.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: There is insufficient system memory
 *           available to read the NFC event.
 */
NFC_API nfc_result_t nfc_read_event(int fd, nfc_event_t **event);

/**
 * @brief Dispose of an NFC event structure
 * @details This function disposes of the @c #nfc_event_t structure after the
 *          NFC event has been handled. This function must be called for each
 *          @c #nfc_event_t received from the NFC system through
 *          @c nfc_read_event().
 *
 * @param event The NFC event to be disposed of.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_free_event(nfc_event_t *event);

/**
 * @brief Retrieve the NFC event type
 * @details This function retrieves the type from an @c #nfc_event_t structure.
 *
 * @param event The NFC event received through @c nfc_read_event()
 * @param type The output event type.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_event_type(nfc_event_t *event,
                                        nfc_event_type_t *type);


/**
 * @brief Destroy the associated target found after a successful NFC detection
 * @details This function disposes of the associated target after a successful
 *          NFC detection.
 *
 * @param target The returned target handle.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER,
 *         which indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_destroy_target(nfc_target_t *target);

/*****************************************************************************
 *                            SNEP registration                              *
 *****************************************************************************/

/**
 * @brief Register to receive an event when an NFC-Forum SNEP client connection
 *        is ready
 * @details  This function registers for an event which indicates an LLCP
 *           connection in the @c #NFC_LLCP_CLIENT mode is established with
 *           another NFC-enabled device. The NFC-enabled device supports the NFC
 *           Forum SNEP specification. On a successful detection, a call to the
 *           @c nfc_get_event_type() function returns a
 *           @c #NFC_SNEP_CONNECTION_EVENT.
 *
 *           This function enables the communication between the application and
 *           other Forum-enabled devices. This communication uses NFC-Forum SNEP
 *           protocol as the SNEP client.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_SERVICE_CONNECTION_ERROR,
 *         which indicates that the application is not connected to the NFC system.
 *         Successive calls to this function have no effect and return
 *         @c #NFC_RESULT_SUCCESS.
 */
NFC_API nfc_result_t nfc_register_snep_client();

/**
 * @brief Unregister from receiving an event when a NFC-Forum SNEP client
 *        connection is ready
 *
 * @details This function disables the communication between the application
 *          and other NFC-Forum-enabled devices. This communication uses the
 *          NFC-Forum SNEP protocol as the SNEP client.
 *
 *          If the application exits without calling this function, the NFC
 *          system automatically unregisters.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: SNEP client is not registered.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_unregister_snep_client();

/*****************************************************************************
 *                       TAG reader/writer registration                      *
 *****************************************************************************/

/**
 * @brief Register for notification of tag events
 * @details The @c nfc_register_tag_readerwriter() function registers for
 *          notification of a tag detection event. Once a tag is detected by the
 *          NFC reader, reading and writing of tags is possible. Upon successful
 *          detection, a call to @c nfc_get_event_type() returns @c
 *          #NFC_TAG_READWRITE_EVENT.
 *
 * @param nfc_tag_type_mask One or more tag connection types represented as
 *                          bit-fields. The bit-fields are specified in the
 *                          @c #nfc_tag_type_t type.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_register_tag_readerwriter(unsigned int nfc_tag_type_mask);

/**
 * @brief Unregister for notification of tag events
 * @details This function unregisters for notification of a tag detection
 *          event. If an application exits without calling this function then
 *          the NFC system automatically unregisters.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: Tag reader/writer is not
 *           registered
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_unregister_tag_readerwriter();

/*****************************************************************************
 *                          Handover registration                            *
 *****************************************************************************/

/**
 * @brief Register for notification of a successful NFC handover
 *
 * @details This function registers a caller to be updated when an NFC handover
 *          has occurred. On successful detection, a call to the @c
 *          nfc_get_event_type() function returns
 *          @c #NFC_HANDOVER_DETECTED_EVENT.
 *
 *          Initial calls to this function register the specified @c type
 *          as the preferred transport type with the highest priority.
 *          Subsequent calls with new transport types register the supplied
 *          transport types with lower priority. Calls to this function
 *          with already registered transport types have no effect.
 *
 * @param type The transport type used to complete the NFC handover.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_register_handover_listener(handover_transport_type_t type);

/**
 * @brief Unregister for notification of a successful NFC handover
 * @details This function unregisters a caller from being updated when an NFC
 *          handover has occurred. All types listed will be unregistered.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: Listener is not registered.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_unregister_handover_listener();

/**
 * @brief Confirm whether the platform should continue the handover process
 * @details This function instructs whether the platform should continue
 *          the handover negotiation with the detected remote device.
 *          The application must react quickly when the
 *          @c #NFC_HANDOVER_DETECTED_EVENT event is received. When an
 *          application has data to share after the handover, it must invoke
 *          this function with a value of @c true.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param completeHandoverProcess @c true to indicate to the platform to
 *                                continue the handover negotiation, otherwise
 *                                @c false to indicate to the platform to abort
 *                                the handover negotiation because the
 *                                application has nothing to share.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following values:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_confirm_handover_process(nfc_target_t *target,
                                          bool completeHandoverProcess);

/**
 * @brief Tell the platform to continue the handover process with the new list
 *        of transport types.
 * @details This function instructs the platform to continue the handover
 *          negotiation with the detected remote device. The handover negotiation
 *          will use the list of handover transport types that are passed in.
 *
 *          Similar to the function @c nfc_confirm_handover_process(),
 *          an application must react quickly by calling this function when the
 *          @c #NFC_HANDOVER_DETECTED_EVENT event is received.
 *
 *          Successful completion of this function will change the handover
 *          transport types and preference that were registered by the previous
 *          calls to @c nfc_register_handover_listener().
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param transports the address of the array of handover transport types.
 * @param no_of_transports the length of the array of handover transport types.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following values:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_confirm_handover_process_with_transports(nfc_target_t *target,
                                                                  handover_transport_type_t* transports,
                                                                  unsigned int no_of_transports);

/**
 * @brief Retrieve the role of connection handover
 * @details This function gets the role of the device involved in the connection
 *          handover negotiation. The retrieval of the role of the device is
 *          dependent on the successful completion of the connection handover.
 *          Therefore, the application must wait for the
 *          @c #NFC_HANDOVER_COMPLETE_EVENT before using this function.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param role The returned role of connection handover negotiation.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_handover_role(nfc_target_t *target,
                                           handover_role_t *role);

/**
 * @brief Determine whether the connection handover target is a static handover
 *        detection or dynamic handover between two devices.
 * @details This function returns information that indicates whether a handover
 *          target is detected from an NFC tag or a remote device target. The
 *          retrieval of the information is dependent on the successful completion
 *          of the connection handover. Therefore, the application must wait for
 *          the @c #NFC_HANDOVER_COMPLETE_EVENT before using this function.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param isStatic The returned value. If true, the handover target is an NFC tag;
 *         otherwise, the handover target is a device that supports NFC
 *         connection handover.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_is_static_handover(nfc_target_t *target, bool *isStatic);

/*****************************************************************************
 *                NFC notification retrieval                                 *
 *****************************************************************************/

/**
 * @brief Retrieve the associated value from an NFC notification event
 * @details This function gets a value from the NFC notification event if there
 *          is an associated value. Not all event types may have an associated
 *          value. Refer to @c #nfc_event_type_t for events which have
 *          associated values.
 *
 * @param event The NFC event to get the from.
 * @param event_value The extra value that might be associated with different
 *                    NFC notification events.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_notification_value(nfc_event_t *event,
                                                unsigned int *event_value);

/*****************************************************************************
 *                NFC Target retrieval                                       *
 *****************************************************************************/

/**
 * @brief Retrieve the associated target found after a successful NFC detection
 * @details This function gets the associated target after a successful NFC
 *          detection. The target returned is dependent on the event type
 *          retrieved from the nfc_get_event_type() function. The target is
 *          returned for each of the following event codes:
 *
 *          - @c #NFC_SNEP_CONNECTION_EVENT: returns the target found after a
 *            successful LLCP connection has been detected; the application is
 *            now able to send and NDEF message via SNEP to another device.
 *          - @c #NFC_TAG_READWRITE_EVENT: returns the target found after a
 *            successful tag read.
 *          - @c #NFC_HANDOVER_COMPLETE_EVENT: returns the target found after a
 *            successful handover.
 *          - @c #NFC_HANDOVER_DETECTED_EVENT: returns the target found after
 *            remote device supporting handover is detected.
 *          - @c #NFC_LLCP_CONNECTION_EVENT: returns the target found after a
 *            successful LLCP connection is established.
 *          - @c #NFC_ISO14443_4_COMMAND_EVENT: returns the target found after
 *            a remote device sends a command during HCE
 *          - @c #NFC_LLCP_READ_COMPLETE_EVENT: returns the target found after a
 *            successful LLCP read; this event indicates that the reading of
 *            LLCP data is completed. This event is in response to a previous
 *            request from the application to the NFC service to read LLCP data
 *            from another device.
 *          - @c #NFC_LLCP_WRITE_COMPLETE_EVENT: returns the target found after
 *            a successful LLCP write; this event indicates that the writing of
 *            LLCP data is completed. This event is in response to a previous
 *            request from the application to the NFC service to write LLCP data
 *            to another device.
 *
 * @param event The NFC event to get the message from.
 * @param target The returned target handle. The target handle is owned by the
 *               application and therefore must be cleaned up by the application
 *               using the @c nfc_destroy_target() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: An invalid argument was passed to
 *           the function.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: The associated target has already
 *           been retrieved.
 */
NFC_API nfc_result_t nfc_get_target(nfc_event_t *event, nfc_target_t **target);

/**
 * @brief Retrieve the connection id associated with the target.
 * @details This function returns the connection id associated with the target.
 *          The id could be used to identify a target at runtime.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param target_connection_id The returned connection id of the target.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_target_connection_id(const nfc_target_t *target,
                                                  unsigned int *target_connection_id);

/*****************************************************************************
 *                        NDEF read functions                                *
 *****************************************************************************/

/**
 * @brief Retrieve the number of NDEF messages found after an NDEF read
 * @details This function retrieves the number of NDEF messages found after a
 *          successful NDEF read.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param count The returned number of NDEF messages found, corresponding to the
 *              NDEF types specified.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_ndef_message_count(const nfc_target_t *target,
                                                unsigned int *count);

/**
 * @brief Gets an NDEF message after an NDEF read
 * @details The @c nfc_get_ndef_message() function gets a message from the
 *          array of one or more messages found after an NDEF read is
 *          successful.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param index The index of the message required from the message array.
 *              A valid index ranges from @c 0 to
 *              <tt>[nfc_get_ndef_message_count() - 1]</tt>.
 * @param msg The returned NDEF message. The message is owned by the NFC system
 *            and hence should not be cleaned up by the application.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_ndef_message(const nfc_target_t *target,
                                          unsigned int index,
                                          nfc_ndef_message_t **msg);

/*****************************************************************************
 *                        NDEF push functions                                *
 *****************************************************************************/
/**
 * @brief Push an NDEF message to a remote device in a SNEP PUT request
 * @details This function pushes an NDEF message to a device that supports the
 *          NFC Forum SNEP specification. The NDEF message is returned from a
 *          successful push detection. Only one NDEF message can be pushed
 *          for each NFC tap gesture.
 *
 * @param target The NDEF target handle found after an NDEF push detection.
 * @param msg The NDEF message to push. If you provide @c NULL, it will cause
 *            the NFC service to abort any active push session if one was in
 *            progress.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_push_ndef_message(const nfc_target_t *target,
                                           const nfc_ndef_message_t *msg);

/*****************************************************************************
 *                        TAG read/write functions                           *
 *****************************************************************************/

/**
 * @brief Return the property value associated with a tag property name
 * @details The value of the requested property is copied into the provided
 *          buffer of type @c char and null-terminated.
 *
 *          The following properties have values represented as a string:
 *          - @c #TAG_PROP_ISO_14443_3_TYPE:
 *            - "A"
 *            - "B"
 *          - @c #TAG_PROP_ISO_14443_4_TYPE:
 *            - "A"
 *            - "B"
 *          - @c #TAG_PROP_NDEF_LOCKABLE:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_NDEF_LOCKED:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_NDEF_TYPE:
 *            - "1"
 *            - "2"
 *            - "3"
 *            - "4"
 *          - @c #TAG_PROP_NDEF_CAPABLE_TYPE:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_AFI_SUPPORTED:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_AFI_LOCKED:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_ISO_15693_3_TYPE:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_DSFID_SUPPORTED:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_DSFID_LOCKED:
 *            - "TRUE"
 *            - "FALSE"
 *          - @c #TAG_PROP_ISO_18092_TYPE:
 *            - "TRUE"
 *            - "FALSE"
 *
 *          The following properties have a positive integer value represented
 *          as a string:
 *          - @c #TAG_PROP_NDEF_FREE_SPACE (Free space in bytes)
 *          - @c #TAG_PROP_NDEF_CAPABLE_TAG_SIZE (Raw tag size in bytes)
 *          - @c #TAG_PROP_AFI
 *          - @c #TAG_PROP_DSFID
 *          - @c #TAG_PROP_SECTOR_SIZE
 *          - @c #TAG_PROP_SECTOR_NUMBER
 *          - @c #TAG_PROP_SYSTEM_CODE
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param property The requested property.
 * @param buffer A pointer to a preallocated buffer of type @c char in which
 *               the property value is updated.
 * @param buffer_length The size of the preallocated buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The given preallocated buffer is
 *           too small.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *
 * Note:@c #TAG_PROP_NDEF_SERIAL_NUMBER is not accessible through this
 *      function and must be read out using @c nfc_get_tag_id().
 */
NFC_API nfc_result_t nfc_get_tag_property(const nfc_target_t *target,
                                          target_property_type_t property,
                                          char *buffer,
                                          size_t buffer_length);

/**
 * @brief Retrieve the variant name associated with the tag
 * @details This function returns the name associated with the tag.
 *
 *          Whether a name is returned depends on the following three factors:
 *          - the connection type (ISO14443-3, ISO14443-4, NDEF, ISO15693-3, or ISO18092)
 *          - the tag variant (Topaz, MIFARE UL, MIFARE UL C, Jewel, etc.)
 *          - the feature set (feature set 1, feature set 2)
 *
 *          If the tag name is not provided in the combination of the factors, this
 *          function returns @c #NFC_RESULT_SUCCESS and sets @c name_length to zero.
 *
 *          The following tag names are supported:
 *          - "Desfire D40"
 *          - "Desfire EV1 2K"
 *          - "Desfire EV1 4K"
 *          - "Desfire EV1 8K"
 *          - "Jewel"
 *          - "Mifare UL"
 *          - "Mifare UL C"
 *          - "Topaz"
 *          - "Topaz 512"
 *          - "TI TAGIT"
 *          - "ST LRI 512"
 *          - "ST LRI 1K",
 *          - "ST_LRI_2K"
 *          - "ST LRI S2K",
 *          - "ST LRI S64K",
 *          - "NXP ICODE"
 *          - "Kovio"
 *          - "Mifare 1K"
 *          - "Mifare 4K"
 *          - "Mifare MINI"
 *          - "FeliCa",
 *          - "Unknown"
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param name A pointer to a preallocated buffer to return the name.
 * @param max_name_length The length of the preallocated buffer.
 * @param name_length The length of the returned name copied into the @c name
 *                    buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The given preallocated buffer is
 *           too small.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_get_tag_name(const nfc_target_t *target,
                                      char *name,
                                      size_t max_name_length,
                                      size_t *name_length);

/**
 * @brief Retrieve the ID associated with the tag
 * @details This function returns the ID associated with the tag.
 *
 *          Whether a tag ID is returned depends on the following three factors:
 *          - the connection type (ISO14443-3, ISO14443-4, NDEF, ISO15693-3, or ISO18092)
 *          - the tag variant (Topaz, MIFARE UL, MIFARE UL C, Jewel, etc.)
 *          - the feature set (feature set 1, feature set 2)
 *
 *          If the ID is not provided in the combination of the factors, this
 *          function returns @c #NFC_RESULT_SUCCESS and sets @c id_length to zero.
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param id A pointer to a preallocated buffer to return the identifier.
 * @param max_id_length The length of the preallocated buffer.
 * @param id_length The length of the returned ID copied into the @c id buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The given preallocated buffer is
 *           too small.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_get_tag_id(const nfc_target_t *target,
                                    uchar_t *id,
                                    size_t max_id_length,
                                    size_t *id_length);

/**
 * @brief Retrieve the manufacturer parameter from the first system (System 0)
 *        detected on the FeliCa tag
 * @details This function returns the manufacturer parameter from the first system
 *          detected on the FeliCa tag
 *
 * @param target The NFC target returned from the @c nfc_get_target() function.
 * @param result A pointer to a preallocated buffer where the manufacturer
 *               parameter is returned.
 * @param max_result_length The length of the preallocated buffer.
 * @param result_length The length of the returned manufacturer parameter
 *                      copied into the @c result buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The given preallocated buffer is
 *           too small.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_get_tag_manufacturer_param(const nfc_target_t *target,
                                                    uchar_t* result,
                                                    size_t max_result_length,
                                                    size_t* result_length);

/**
 * @brief Retrieve the variant of the tag
 * @details This function returns the variant of the tag.
 *
 * @param target The NFC target returned from @c nfc_get_target().
 * @param variant The returned variant associated with the tag; see
 *                @c tag_variant_type_t for a list of possible variants.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_get_tag_variant(const nfc_target_t *target,
                                         tag_variant_type_t *variant);

/**
 * @brief Indicate whether or not the specified tag supports a specified tag
 *        type
 * @details This function indicates whether or not a specified tag type is
 *          supported.
 *
 * @param tag The tag returned from the @c nfc_get_target() function.
 * @param type The requested tag type.
 * @param is_supported @c true if the specified tag supports the specified
 *        tag type, otherwise @c false.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_tag_supports_tag_type(const nfc_target_t *tag,
                                               nfc_tag_type_t type,
                                               bool *is_supported);

/**
 * @brief Indicate whether or not the specified tag is writable
 * @details This function indicates whether or not the tag is writable.
 *
 * @param tag The tag returned from the @c nfc_get_target() function.
 * @param is_writable @c true if the specified tag is writable, otherwise @c
 *                    false.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_tag_is_writable(const nfc_target_t *tag,
                                         bool *is_writable);

/**
 * @brief Indicate whether the specified tag is emulated
 * @details This function indicates whether the specified tag is an emulated tag.
 *
 * @param tag The tag returned from the @c nfc_get_target() function.
 * @param is_virtual @c true if the specified tag is an emulated tag, @c false
 *                   otherwise.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_tag_is_virtual(const nfc_target_t *tag,
                                        bool *is_virtual);

/**
 * @brief Write a command to one of the following connections: ISO 14443,
 *        ISO 15693, or ISO 18092
 * @details This function writes a command to one of the following connections:
 *          ISO 14443, ISO 15693, or ISO 18092.
 *          - Feature set 1: When using an ISO 14443-3 connection, short
 *            frames (four bits representing ACK/NACK status) returned from
 *            the tag are not returned in the response buffer. They are
 *             mapped into the return code.
 *          - Feature set 2: When using an ISO 14443-3 connection, short
 *            frames (four bits representing ACK/NACK status) returned from
 *            the tag are returned in the @response parameter and the
 *            @response_length parameter is set to 1. The short frames
 *            are not mapped into the return code.
 *
 * @param tag The tag returned from the @c nfc_get_target() function.
 * @param type The type of tag to write to. This must be one of the following types:
 *             - @c #TAG_TYPE_ISO_14443_3
 *             - @c #TAG_TYPE_ISO_14443_4
 *             - @c #TAG_TYPE_ISO_15693_3
 *             - @c #TAG_TYPE_ISO_18092
 * @param command A pointer to the buffer holding the command to be sent.
 * @param command_length The length of the command buffer.
 * @param response A pointer to a preallocated response buffer.
 * @param max_response_length The length of the preallocated response buffer.
 *                            The maximum length cannot be larger than the size
 *                            of @c NFC_TRANSCEIVE_RESPONSE_MAX_BUFFER_LENGTH.
 * @param response_length The length of the response copied into the response
 *                        buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_TIMEOUT: A timeout occurred during communication
 *           with the tag.
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: @c max_response_length is smaller
 *           than the tag's response.
 *         - @c #NFC_RESULT_OPERATION_NOT_SUPPORTED: The operation is not
             supported.
 */
NFC_API nfc_result_t nfc_tag_transceive(const nfc_target_t *tag,
                                        nfc_tag_type_t type,
                                        const uchar_t *command,
                                        size_t command_length,
                                        uchar_t *response,
                                        size_t max_response_length,
                                        size_t *response_length);

/**
 * @brief Write a RAW command to an ISO 14443 connection
 * @details This function writes a RAW command to an ISO 14443 connection.
 *
 * @param tag The tag returned from the @c nfc_get_target() function.
 * @param command A pointer to the buffer holding the command to be sent.
 * @param command_length_in_bits The length of the command in bits.
 * @param response A pointer to the response buffer.
 * @param max_response_length_in_bytes The length of the response buffer.
 *                                     The maximum length cannot be larger than
 *                                     the size of
 *                                     @c NFC_TRANSCEIVE_RESPONSE_MAX_BUFFER_LENGTH.
 * @param expected_response_length_in_bits The expected length of the response
 *                                         buffer in bits. This value must be
 *                                         set to @c 0 if expected response is
 *                                         longer then 8 bits.
 * @param response_length_in_bits The actual length of the response in bits.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_TIMEOUT: A timeout occurred during communication
 *           with the tag.
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: @c max_response_length_in_bytes is
 *           smaller than the tag's response.
 *         - @c #NFC_RESULT_OPERATION_NOT_SUPPORTED: The target does not
 *           support the operation.
 */
NFC_API nfc_result_t nfc_tag_transceive_raw(const nfc_target_t *tag,
                                    const uchar_t *command,
                                    size_t command_length_in_bits,
                                    uchar_t *response,
                                    size_t max_response_length_in_bytes,
                                    size_t expected_response_length_in_bits,
                                    size_t *response_length_in_bits);

/**
 * @brief Write an NDEF message to an NDEF target
 * @details This function writes an NDEF message to the NDEF target returned
 *          from a successful write detection.
 *          - Feature set 1: Allows you to use successive calls to this function
 *            to append multiple messages.
 *          - Feature set 2: Does not support appending multiple messages.
 *
 * @param tag The tag handle found after a tag detection.
 * @param msg The NDEF message to write.
 * @param append Use @c false to overwrite any previous messages, @c true to append
 *               multiple messages. If using feature set 2, you must set @c append
 *               to @c false.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_LOCKED: The tag is locked.
 *         - @c #NFC_RESULT_TAG_NOT_SUPPORTED: The tag type is not supported.
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The tag does not have enough space.
 *         - @c #NFC_RESULT_WRITE_FAILED: Writing the message to tag failed.
 *         - @c #NFC_RESULT_TIMEOUT: A time-out occurred.
 */
NFC_API nfc_result_t nfc_write_ndef_message_to_tag(nfc_target_t *tag,
                                                   const nfc_ndef_message_t *msg,
                                                   bool append);

/**
 * @brief Erase all NDEF messages from a tag NDEF target
 * @details This function erases all NDEF messages from the tag target returned
 *          from a successful write detection by replacing them with a single
 *          empty NDEF message.
 *
 * @param tag The tag handle found after a tag detection.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OPERATION_NOT_SUPPORTED: The @c tag parameter is
 *           not a tag handle.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_LOCKED: The tag is locked.
 *         - @c #NFC_RESULT_WRITE_FAILED: Writing the message to the tag failed.
 *         - @c #NFC_RESULT_NOT_NFC_TAG_BUT_CAPABLE: The tag does not currently
 *           support NFC operations, but can be formatted to be NFC compliant
 *           (type 1-4).
 */
NFC_API nfc_result_t nfc_erase_tag(nfc_target_t *tag);

/**
 * @brief Indicate whether or not the specified tag is locked for additional
 *        NDEF message writing
 * @details This function indicates whether or not a tag is locked for
 *          additional NDEF writes.
 *
 * @param tag The tag handle found after a tag detection.
 * @param locked @c true if the specified tag is read only, @c false if not
 *               locked against additional NDEF writes.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OPERATION_NOT_SUPPORTED: The @c tag parameter is
 *           not a tag handle.
 */
NFC_API nfc_result_t nfc_is_tag_locked(nfc_target_t *tag, bool *locked);

/**
 * @brief Lock a tag from additional NDEF messages writes
 * @details This function locks a tag from additional NDEF message writes.
 *
 * @param tag The tag handle found after a tag detection; the tag to be locked.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OPERATION_NOT_SUPPORTED: The @c tag parameter is
 *           not a tag handle.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_LOCKED: The tag is already locked.
 *         - @c #NFC_RESULT_LOCK_FAILED: The tag cannot be locked.
 *         - @c #NFC_RESULT_NOT_NFC_TAG_BUT_CAPABLE: The tag does not currently
 *              support NFC operations, but can be formatted to be NFC compliant
 *              (type 1-4).
 */
NFC_API nfc_result_t nfc_lock_tag(nfc_target_t *tag);

/*****************************************************************************
 *                            NDEF Tag Emulation                             *
 *****************************************************************************/
/**
 * @brief Start an NDEF tag emulation
 * @details This function creates a virtual NDEF tag and starts emulation when
 *          the application is in the foreground. Note that the tag is only
 *          active while this application is in the foreground. Also, only one
 *          virtual NDEF tag is allowed per application. The second call to the
 *          function will replace the NDEF message being emulated.
 *          The emulation of the NDEF tag is done in read-only mode, so it is
 *          not possible to write to the emulated tag.
 *
 * @param msg Pointer to an NDEF message to be emulated on the virtual NDEF tag.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_start_ndef_tag_emulation(const nfc_ndef_message_t *msg);

/**
 * @brief Stop an NDEF tag emulation
 * @details This function stops the NDEF tag emulation and destroys an
 *          existing virtual NDEF tag. If an application exits without calling
 *          this function, the NFC system stops the emulation automatically.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: Virtual NDEF tag emulation is
 *           not in progress
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_stop_ndef_tag_emulation();


/*****************************************************************************
 *                         HCE - Host Card Emulation                         *
 *****************************************************************************/
/**
 * @brief Start Host Card Emulation (HCE) for the calling application
 * @details HCE emulates an ISO 14443-4 smart card. This function registers card
 *          emulation information within the NFC service. It also starts HCE when
 *          the application is in the foreground. Only one instance of HCE is
 *          allowed at one time, and emulation is only active while this application
 *          is in the foreground. If an application is placed in the background,
 *          the NFC service automatically stops the appplication's HCE.
 *
 *          If you want to start HCE in the background you can use
 *          @c nfc_hce_register_aid() with a dedicated AID for the registration.
 *
 *          Once the application is placed in the foreground again, the NFC
 *          service resumes HCE. If an application attempts to call this function
 *          while it is already emulating an ISO 14443-4 card, the second call
 *          will fail with @c #NFC_RESULT_LIMITATION_EXCEEDED.
 *
 *          During HCE, the following events can occur:
 *          - @c #NFC_ISO14443_4_COMMAND_EVENT: This event indicates that a
 *            command was generated by the target reader. The application must
 *            first call @c nfc_get_target() to retrieve the event target,
 *            and then call @c nfc_get_iso14443_4_emulation_command() using the
 *            target retrieved to extract the command data from the triggered
 *            event.
 *          - @c #NFC_ISO14443_4_EVENT_CODE_EVENT: This event indicates that an
 *            ISO 14443-4 related event has occurred. This event is associated
 *            with an event code from the target reader. Call
 *            @c nfc_get_notification_value() to extract the event code,
 *            which is of type @c #iso14443_4_event_t.
 *
 * @param card The structure containing the information that will be emulated
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to NFC service.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_LIMITATION_EXCEEDED: HCE is already running.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: NFC is not enabled, or
 *           application is not in foreground.
 *         - @c #NFC_RESULT_OPERATION_NOT_SUPPORTED: The Application Data buffer
 *           of the Type A card, or  Higher Layer Response buffer of the Type B
 *           card is too large for the capabilities of the NFC Controller.
 */
NFC_API nfc_result_t nfc_start_iso14443_4_emulation(const nfc_iso14443_4_card_t *card);


/**
 * @brief Stop Host Card Emulation (HCE) for the calling application
 * @details This function stops HCE of an ISO 14443-4 card and destroys any
 *          information stored within the service for the calling application.
 *          If an application exits without calling this function, the NFC
 *          service automatically stops HCE.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: HCE is not in progress.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_stop_iso14443_4_emulation();

/**
 * @brief Retrieve an ISO 14443-4 command from the @c NFC_ISO14443_4_COMMAND_EVENT
 *        event
 * @details This function lets you retrieve the data for a @c command sent by
 *          a reader during a successful Host Card Emulation (HCE). If this function
 *          fails to return @c #NFC_RESULT_SUCCESS, @c command and @c command_length
 *          will remain unchanged.
 *
 * @param target The target returned from the @c nfc_get_target() function
 *               during the HCE.
 * @param command A pointer to a preallocated command buffer.
 * @param max_command_length The length of the preallocated command buffer. The
 *                           length should be at least
 *                           @c NFC_ISO14443_4_COMMAND_BUFFER_LENGTH to ensure
 *                           there is enough space to accommodate the returned
 *                           command from the NFC driver.
 * @param command_length The length of the returned command copied into the
 *                       @c command buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The provided command buffer is too
 *           small.
 */
NFC_API nfc_result_t nfc_get_iso14443_4_emulation_command(const nfc_target_t *target,
                                                  uchar_t *command,
                                                  size_t max_command_length,
                                                  size_t *command_length);

/**
 * @brief Send an ISO 14443-4 command response to the reader
 * @details This function sends a response to the reader of the Host Card Emulation
 *          (HCE) that was started by @c nfc_start_iso14443_4_emulation().
 *
 * @param response The buffer containing the response info to send to the reader.
 * @param response_length The length of the response command.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: The command could not be sent;
 *           the emulation is not running or NFC is disabled
 */
NFC_API nfc_result_t nfc_send_iso14443_4_emulation_command_response(const uchar_t *response,
                                                                    size_t response_length);


/**
 * @brief Register an AID for Host Card Emulation (HCE)
 * @details An application that wants to perform HCE as defined in
 *          ISO-DEP (ISO/IEC 14443-4) can use this function to register an
 *          application identifier (AID) according to ISO/IEC 7816-5.
 *          When an NFC reader issues a SELECT command with the registered AID,
 *          the application is notified through the Invocation Framework
 *          using the @c invoke_target that the application has provided.
 *
 *          An application can register a specific AID or a wildcard AID. When
 *          it registers a specific AID, the AID stays registered (that is, the
 *          emulation is active) until the application calls @c nfc_hce_unregister_aid()
 *          or until the application is uninstalled from the system. This means that
 *          the emulation remains active regardless of whether the application is
 *          running (either in the foreground or in the background) or terminated.
 *
 *          An application can register a specific AID only once, but can register
 *          more than one AID. The registration of the same AID by more than one
 *          application leads to a routing conflict in the system. When the NFC
 *          service receives the first SELECT command with the conflicting AID, it
 *          prompts the user to resolve the conflict.
 *
 *          An application can register a wildcard AID by setting the parameters
 *          @c aid to @c NULL and @c aid_len to @c 0. A wildcard AID allows the
 *          application to receive all ISO 14443-4 commands when it runs in the
 *          foreground; however, when it's running in the background or gets terminated,
 *          no HCE commands are routed to the application.
 *
 *          During emulation, the following events can occur:
 *          - @c #NFC_ISO14443_4_COMMAND_EVENT: This event indicates that a
 *            command was generated by the target reader. The application must
 *            first call @c nfc_get_target() to retrieve the
 *            event target, and then @c nfc_get_iso14443_4_emulation_command() using
 *            the  target retrieved to extract the command data from the triggered
 *            event.
 *          - @c #NFC_ISO14443_4_EVENT_CODE_EVENT: This event indicates that an
 *            ISO 14443-4 related event has occurred. This event is associated
 *            with an event code from the target reader.  Call
 *            @c nfc_get_notification_value() to extract the event code (of type
 *            @c #iso14443_4_event_t).
 *
 *         In feature set 1, this function is not supported
 *         and returns @c #NFC_RESULT_UNSUPPORTED_API.
 *
 * @param aid Pointer to the buffer containing the AID.
 * @param aid_len Length of the AID.
 * @param category The purpose of the emulating application. This is used to help the
 *                 user choose an application when an AID conflict occurs between two
 *                 or more applications.
 * @param invoke_target The target ID in a null-terminated string. When an NFC reader
 *                      selects the registered AID, the NFC system includes this target
 *                      ID in the invocation message it sends. When registering a wildcard
 *                      AID, set this parameter to @c NULL.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: One of the following errors has occurred:
 *           .The application already started an HCE.
 *           .The application already registered the same AID.
 *           .The AID is not valid for the specified category.
 *         - @c #NFC_RESULT_UNSUPPORTED_API: This API is not supported in this
 *           feature set.
 */
NFC_API nfc_result_t nfc_hce_register_aid(const uint8_t* aid,
                                          size_t aid_len,
                                          app_category_type_t category,
                                          const char* invoke_target);


/**
 * @brief Deregister an AID from Host Card Emulation (HCE)
 * @details An application uses this function to deregister an AID from the
 *          NFC system. The application can deregister only AIDs that have
 *          previously been registered by this application. Registrations from
 *          other applications remain untouched.
 *
 *          In feature set 1, this function is not supported
 *          and returns @c #NFC_RESULT_UNSUPPORTED_API.
 *
 * @param aid Pointer to the buffer containing the AID.
 * @param aid_len Length of the AID.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: This AID has not been registered
 *           by this application for HCE.
 *         - @c NFC_RESULT_UNSUPPORTED_API: This API is not supported in this
 *           feature set.
 */
NFC_API nfc_result_t nfc_hce_unregister_aid(const uint8_t* aid,
                                            size_t aid_len);


/**
 * @brief Check if an AID is registered
 * @details An application uses this function to check if it has already registered
 *          the specified AID.
 *
 *          In feature set 1, this function is not supported
 *          and returns @c #NFC_RESULT_UNSUPPORTED_API.
 *
 * @param aid Pointer to the buffer containing the AID.
 * @param aid_len Length of the AID.
 * @param is_registered A pointer to a boolean value that is set when the function
 *                      returns @c #NFC_RESULT_SUCCESS. This value is set to @c true
 *                      if the calling application has already registered the AID,
 *                      @c false otherwise.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c NFC_RESULT_UNSUPPORTED_API: This function is not supported in this
 *           feature set.
 */
NFC_API nfc_result_t nfc_hce_is_aid_registered(const uint8_t* aid,
                                               size_t aid_len,
                                               bool* is_registered);


/*****************************************************************************
 *                              LLCP functions                               *
 *****************************************************************************/

/**
 * @brief Create a client or server LLCP connection listener
 * @details This function creates a listener for a client or server LLCP
 *          connection.
 *
 * @param type The connection type. You can use @c #NFC_LLCP_CLIENT or
 *             @c #NFC_LLCP_SERVER.
 * @param sap The service access point. We recommend setting this value to 0
 *            to let the platform assign the service access point for the
 *            service specified by the service name.
 *            - In feature set 1, valid values are 0, 2, 3, and all values from 5 to 63.
 *            - In feature set 2, valid values are 0 and all values from 17 to 32.
 * @param service_name The service name.
 * @param listenerHandle The returned handle associated with this listener.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is
 *           not connected to the NFC system.
 *         - @c #NFC_RESULT_RESOURCE_BUSY: The specified SAP or service is
 *           already in use.
 *         - @c #NFC_RESULT_LIMITATION_EXCEEDED: Maximum number of socket
 *           registration has been reached.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY:  The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_llcp_register_connection_listener(nfc_llcp_connection_type_t type,
                                                           unsigned int sap,
                                                           const char *service_name,
                                                           nfc_llcp_connection_listener_t *listenerHandle);

/**
 * @brief Cancel a client or server LLCP connection listener
 * @details This function cancels a client or server LLCP connection listener.
 *          If an application exits without calling this function then NFC
 *          system unregisters automatically.
 *
 * @param listenerHandle The handle of the listener to cancel.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_llcp_unregister_connection_listener(nfc_llcp_connection_listener_t
                                                                listenerHandle);

/**
 * @brief Retrieve connection status information from an LLCP connection
 * @details This function retrieves the status of an LLCP connection from an NFC
 *          LLCP connection.
 *
 * @param llcpConnection The LLCP connection target.
 * @param listener The returned connection status information and the handle of
 *                 the associated listener.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_llcp_get_connection_status(nfc_target_t *llcpConnection,
                                                    nfc_llcp_connection_listener_t *listener);

/**
 * @brief Return the remote service access point (SAP)
 * @details This function returns the remote SAP for an LLCP connection.
 *
 * @param llcpConnection The LLCP connection target.
 * @param sap The returned remote service access point.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_llcp_get_remote_sap(nfc_target_t *llcpConnection,
                                             unsigned int *sap);

/**
 * @brief Return the remote maximum information unit (MIU)
 * @details This function returns the remote MIU for an LLCP connection.
 *
 * @param llcpConnection The LLCP connection target.
 * @param miu The returned remote maximum information unit.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_llcp_get_remote_miu(nfc_target_t *llcpConnection,
                                             unsigned int *miu);

/**
 * @brief Return the local service access point (SAP)
 * @details This function returns the local SAP for an LLCP connection.
 *
 * @param llcpConnection The LLCP connection target.
 * @param sap The returned local service access point.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_llcp_get_local_sap(nfc_target_t *llcpConnection,
                                            unsigned int *sap);

/**
 * @brief Return the local maximum information unit (MIU)
 * @details This function returns the local MIU for an LLCP connection.
 *
 * @param llcpConnection The LLCP connection target.
 * @param miu The returned local maximum information unit.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER, which
 *         indicates that an invalid argument was passed to the function.
 */
NFC_API nfc_result_t nfc_llcp_get_local_miu(nfc_target_t *llcpConnection,
                                            unsigned int *miu);

/**
 * @brief Close an LLCP connection
 * @details This function closes an LLCP connection.
 *
 * @param llcpConnection The LLCP connection to close.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_llcp_close(nfc_target_t *llcpConnection);

/**
 * @brief Retrieves the LLCP read result
 * @details This function retrieves the LLCP read result.
 *
 * @param llcpConnection The LLCP connection target.
 * @param buffer The pointer to a preallocated buffer to read into.
 * @param bufferLength The size of the preallocated buffer.
 * @param bytesRead The number of bytes read.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY:  The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_TIMEOUT: A timeout occurred in communicating with
 *           the remote peer, or the remote peer has closed the connection.
 *         - @c #NFC_RESULT_NOT_ENOUGH_SPACE: The provided buffer is too small.
 *         - @c #NFC_RESULT_READ_FAILED: There is a data integrity or RF
 *           communication error with the remote peer.
 */
NFC_API nfc_result_t nfc_llcp_get_read_result(nfc_target_t *llcpConnection,
                                              uchar_t *buffer,
                                              size_t bufferLength,
                                              size_t *bytesRead);

/**
 * @brief Register to read data from an LLCP connection
 * @details This function registers to read data from a LLCP connection.
 *          The read result is delivered via a separate NFC event.
 *
 * @param llcpConnection The LLCP connection target.
 * @param max_bytes_to_read The expected number of bytes to read. This number
 *                          should not be greater than the local MIU size. Up to
 *                          MIU bytes can be read with one @c nfc_llcp_read()
 *                          operation. If more bytes are expected, the client
 *                          must call @c nfc_llcp_read() again after retrieving
 *                          the data from the current read operation with
 *                          @c nfc_llcp_get_read_result().
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY:  The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: There was a problem
 *           connecting to the NFC system.
 */
NFC_API nfc_result_t nfc_llcp_read(nfc_target_t *llcpConnection,
                                   size_t max_bytes_to_read);

/**
 * @brief Writes data to an LLCP connection
 * @details This function writes data to an LLCP connection asynchronously.
 *          The result of the write operation will be returned in a separate NFC
 *          LLCP event.
 *
 * @param llcpConnection The LLCP connection target.
 * @param buffer The pointer to the buffer to write.
 * @param bufferLength The buffer size.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY:  The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: There was a problem
 *           connecting to the NFC system.
 */
NFC_API nfc_result_t nfc_llcp_write(nfc_target_t *llcpConnection,
                                    uchar_t *buffer,
                                    size_t bufferLength);

/**
 * @brief Retrieve the LLCP write status
 * @details This function retrieves the result of the write operation.
 *
 * @param llcpConnection The LLCP connection target.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_TIMEOUT: A timeout occurred during communication
 *           with the remote peer, or the remote peer has closed the connection.
 *         - #NFC_RESULT_WRITE_FAILED:There was a data integrity or radio
 *           communication error with the remote peer.
 */
NFC_API nfc_result_t nfc_llcp_get_write_status(nfc_target_t *llcpConnection);

/*****************************************************************************
 *                              Misc. functions                              *
 *****************************************************************************/

/**
 * @brief Set one of the NFC user settings that is available to the user from
 *        the device
 * @details This function sets the specified value for the specified user
 *          setting. It is important to note that restrictions may apply for
 *          some user settings; refer to the @c #nfc_settings_t descriptions for
 *          more details.
 *
 * @param setting User setting that is available to the user from the device.
 *                Valid settings must be of type @c #nfc_settings_t.
 * @param enable The desired value of the specified user setting.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_LOCKED: The activation request could not be
 *           completed as a mode change was already in progress. It is
 *           recommended to try calling @c nfc_set_setting() again.
 *         - @c #NFC_RESULT_RESOURCE_BUSY: A prompt is already being displayed
 *           for a setting change; try again later.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: An attempt was made at setting
 *           @c #NFC_SETTING_ENABLED to @c false. NFC can only be disabled from
 *           the NFC menu on the device.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: An attempt was made to enable
 *           NFC when it is already enabled, or that the calling application
 *           was not in the foreground.
 *         - @c #NFC_RESULT_UNSUPPORTED_API: An attempt was made at setting
 *           @c #NFC_SETTING_PROMPT_TO_SEND_FILES. This prompt can only be set
 *           at the NFC menu on the device.
 */
NFC_API nfc_result_t nfc_set_setting(nfc_settings_t setting, bool enable);

/**
 * @brief Retrieve one of the NFC user settings that is available from the
 *        device
 * @details This function retrieves the current value for the specified user
 *          setting.
 *
 * @param setting The setting whose value you want to retrieve.
 *                Valid settings must be of type @c #nfc_settings_t.
 * @param enabled The current value of the specified user setting.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_LOCKED: The activation request could not be
 *           completed as a mode change was already in progress. It is
 *           recommended to try calling @c nfc_get_setting() again.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_get_setting(nfc_settings_t setting, bool* enabled);

/**
 * @brief Retrieve the current status of an NFC service channel of the specified
 *        type
 * @details This function retrieves the current status of the specific channel
 *          of the NFC service, including Hardware Support, IT Policy, etc.
 *          Refer to @c #nfc_channel_status_mask_t for a list of supported
 *          states.
 *
 * @param type The channel type, which must be one of type
 *        @c #nfc_channel_type_t.
 * @param bitmask Contains all the information about the current status of the
 *                specific channel of the NFC service.
 *                The list of supported statuses includes:
 *                - @c #NFC_CHANNEL_STATUS_HARDWARE_PRESENT: Indicates an NFC
 *                  hardware support type. The bit is set when the device
 *                  hardware supports NFC.
 *                - @c #NFC_CHANNEL_STATUS_CARRIER_SUPPORTED: Indicates a
 *                  carrier support type. The bit is set when the carrier
 *                  configuration allows NFC.
 *                - @c #NFC_CHANNEL_STATUS_IT_POLICY_ALLOWED: Indicates an IT
 *                  policy support type. The bit is set when IT policy allows
 *                  NFC.
 *                - @c #NFC_CHANNEL_STATUS_WIRELESS_CHARGER_ALLOWED: Indicates
 *                  the NFC status relative to the wireless charging status.
 *                  This bit is set when NFC is allowed while the device is not
 *                  on a wireless charger.
 *                  When a device is on a wireless charger, the wireless field
 *                  disturbs the NFC field, and NFC doesn’t work. For devices
 *                  that are capable of wireless charging, NFC is disabled
 *                  while a device is on a wireless charger.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           able to communicate with the NFC system using the provided channel.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: Either the bitmask or the channel
 *           type specified is invalid.
 */
NFC_API nfc_result_t nfc_get_channel_status(nfc_channel_type_t type,
                                            uint64_t* bitmask);

/**
 * @brief Retrieve the feature set supported on the device
 * @details This function retrieves the feature set supported on the device.
 *          Depending on the feature set used, some NFC functionality may not
 *          be offered by the device.
 *
 * @param feature_set The returned feature set.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           able to communicate with the NFC system.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: The parameter is invalid.
 */
NFC_API nfc_result_t nfc_get_feature_set(int *feature_set);

/**
 * @brief Retrieve the NFC properties of the device
 * @details This function allows an application to retrieve the NFC properties of
 *          the device.
 *
 * @param property_id   The ID of the property to be queried.
 * @param property      The location to store the value of the property retrieved.
 *                      If the device doesn't support this property, this parameter
 *                      is set to @c 0.
 *                      If the property is supported, this parameter is set to a
 *                      positive integer.
 *                      If @c property_id is not defined, this function returns
 *                      @c #NFC_RESULT_INVALID_PARAMETER and leaves @c property untouched.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           able to communicate with the NFC system.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_get_property(nfc_property_id_t property_id, int *property);

/**
 * @brief Register for field events
 * @details This function registers for field events. These events are
 *          generated when external fields are detected by the device,
 *          which could indicate the proximity of readers or other NFC
 *          enabled devices. However, be aware that these events may be
 *          unreliable because:
 *          - field detection is stopped when NFC is disabled due to
 *            either the backlight being turned off or the device being
 *            locked
 *          - field detection is temporarily interrupted due to NFC actions
 *            like establishing card connections, or whenever this device
 *            starts driving the field
 *          - depending on its polling rate, the external field may not
 *            be detected as stable
 *          Due to the unreliable nature of the field detection, the field
 *          events serve only as a rough indicator.
 *
 *          Valid events that can be received after registering for field
 *          events are:
 *          - @c #NFC_FIELD_LOST_EVENT
 *          - @c #NFC_FIELD_DETECTED_EVENT
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: An attempt was made to register
 *           when already registered to this event.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_register_field_events(void);

/**
 * @brief Unregister from receiving field events
 * @details This function unregisters from field events.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_OPERATION_REJECTED: An attempt was made to unregister
 *           when not registered to the field event.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 */
NFC_API nfc_result_t nfc_unregister_field_events(void);

__END_DECLS

#endif /* NFC_H_ */
