/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file notification.h
 *
 * @brief Functions to control the notification system on the device
 *
 * An application can send requests for the following primary types of
 * notification:
 *    - a @e notify (using the @c notification_notify() function)
 *    - an @e alert (using the @c notification_alert() function)
 *
 * Both @e notify and @e alert may contain several data members that affect the
 * characteristics of the notification, defined in the @c
 * #notification_message_t structure. At a minimum, the @c
 * #notification_message_t structure must include @c item_id, which identifies
 * the notification message. The additional arguments used are:
 *     - @c title
 *     - @c subtitle
 *     - @c request_id
 *     - @c prompt_choices (@e alert only)
 *     - @c sound_url (@e notify only)
 *     - @c invocation_target (@e notify only)
 *     - @c invocation_payload (@e notify only)
 *     - @c invocation_payload_uri (@e notify only)
 *     - @c invocation_type (@e notify only)
 *     - @c invocation_action (@e notify only)
 *
 * These arguments, including @c item_id, are defined in greater
 * detail in their respective @c notification_message_set_*() functions. If a
 * member isn't given a value, a default value is assigned. As indicated in
 * the above list, some members are specific to either @e notify or @e alert
 * notifications. Furthermore, some functions, such as @c notification_cancel(),
 * require only certain members from the @c #notification_message_t structure.
 * In these instances, you can still provide any additional members, but these
 * are simply ignored if not used by a function. See individual @c
 * notification_message_set_*() functions for details regarding the
 * corresponding member's valid implementations.
 *
 * Both @e notify and @e alert can have lingering effects, such as the display
 * of a badge on an application icon or the activation of an LED. These may be
 * dealt with by the @c notification_cancel() or the @c notification_delete()
 * functions. We recommend that you call the @c notification_cancel() function
 * when your application launches, to remove any continuing notification
 * signals.
 *
 * There are settings that define the behavior of notification messages.
 * Examples of basic settings that apply to notification messages include:
 *    - Sound alert: Whether to play a sound for this application
 *    - SoundUrl: Defines a default sound
 *    - LED: Whether an LED light is activated by the notification caller
 *    - Badge: Whether the notification should display badges on icons by
 *          default. This is most commonly represented as a red symbol on the
 *          corner of the application icon.
 *    - UIB: Whether items should be added to the Notifications account in the
 *           BlackBerry Hub. Invocation parameters define what happens when a
 *           user clicks the item in the Hub.
 *    - Display: Whether a dialog notification will occur. This doesn't affect
 *          @e alert messages.
 *
 * For @e notify messages, settings define the means by which the message is
 * displayed and the volume of information displayed in the message. These
 * settings determine whether a message displays large amounts of information,
 * displays smaller amounts, or does't display any information at all. We
 * recommend that you fill out as much information as possible.
 *
 * Third party applications can't control the notification settings they
 * receive. The default notification settings allow applications to put
 * notifications into the Notifications account of the Hub. A notification will
 * be placed into the Hub if and only if the notification includes a title
 * and/or a subtitle. Your application can create a badge-only notification by
 * sending a notify message that doesn't contain a title or a subtitle.
 *
 * @e Alert messages are also affected by settings, but give more control to the
 * application that sends them. Display methods may be determined by the
 * information provided in the message. For example, by providing a title and
 * adding prompt choices (through the @c
 * notification_message_add_prompt_choice() function), you can guarantee that a
 * dialog will be displayed, which can communicate a user's response back to the
 * application.
 *
 * Settings are defined per application. There's one set of default settings
 * for all notifications from an application.
 *
 * @since BlackBerry 10.0.0
 *
 * @cond internal
 *
 * An application may define additional notification types. Reference these
 * types in the @c type member of a @e notify or @e alert message with the @c
 * notification_message_set_type() function. No third party application will be
 * able to set its own notification type.
 *
 * @endcond
 *
 */

#ifndef _BPS_NOTIFICATION_H_INCLUDED
#define _BPS_NOTIFICATION_H_INCLUDED

#include <sys/platform.h>
#include <stdbool.h>

#include <bps/bps.h>

__BEGIN_DECLS

/**
 * @brief The opaque notifications argument type
 *
 * This type defines the @c #notification_message_t structure used by several
 * functions in the notification system. Use this to create and control
 * notification messages. The @c #notification_message_t structure is opaque,
 * but includes the following members:
 *     - Request ID (@c char* @c request_id)
 *     - Item ID (@c char* @c item_id)
 *     - Title (@c char* @c title)
 *     - Subtitle (@c char* @c subtitle)
 *     - Invocation target (@c char* @c target)
 *     - Invocation payload (@c char* @c payload)
 *     - Invocation payload URI (@c char* @c payload_uri)
 *     - Invocation type (@c char* @c invocation_type)
 *     - Invocation action (@c char* @c action)
 *     - Prompt Choices (@c dialog_prompt_t* @c prompt_choices)
 *
 * To use this type:
 *     1. Instantiate a @c #notification_message_t structure with the @c
 *        notification_message_create() function.
 *     2. Set all desired members with the @c notification_message_set_*()
 *        functions.
 *     3. Send the desired message with the @c notification_alert() or @c
 *        notification_notify() functions.
 *     4. Remove lingering side effects from notifications with the @c
 *        notification_cancel() or @c notification_delete() functions.
 *     5. Deallocate the memory reserved for the @c #notification_message_t
 *        structure with the @c notification_message_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct notification_message_t notification_message_t;

/*
 * @cond internal
 */

/**
 * The possible application perimeter types
 *
 * This enumeration defines the possible types of perimeters in which a client
 * application can reside. This determines whether we can show any notification
 * data to the user, primarily in cases where the application is a
 * "hybrid" that can send both notifications in enterprise and personal
 * perimeters.
 */
typedef enum {
/**
 * The perimeter type is unspecified.
 */
    NOTIFICATION_PERIMETER_TYPE_UNSPECIFIED = 0,
/**
 * The application runs in the personal perimeter.
 */
    NOTIFICATION_PERIMETER_TYPE_PERSONAL    = 1,
/**
 * The application runs in the enterprise perimeter.
 */
    NOTIFICATION_PERIMETER_TYPE_ENTERPRISE  = 2
} notification_perimeter_type_t;

/*
 * @endcond
 */

/**
 * @brief The possible notification response events
 *
 * This enumeration defines the possible response events of a notification. Any
 * notification containing a @c request_id member will trigger at least one
 * response event.
 *
 * If the @c request_id member is included in the notification, an @c
 * NOTIFICATION_OK or @c NOTIFICATION_ERROR response event is sent immediately
 * to indicate that a message has been correctly parsed or not, respectively.
 * Otherwise, the response isn't sent.
 *
 * If a @c notification_alert() call displays a dialog from which the user
 * selects an option, a @c NOTIFICATION_CHOICE response event is produced. This
 * response is sent once the user makes a selection.
 *
 * All response events have a corresponding @c #notification_response_t value
 * associated with them. You can access them with the @c
 * notification_event_get_response() function. Each response also has a Request
 * ID which you can access with the @c notification_event_get_request_id()
 * function.
 *
 * You can access the button index for a @c NOTIFICATION_CHOICE event with the
 * @c notification_event_get_choice() function. @c NOTIFICATION_CHOICE may also
 * possess an item ID and/or context argument, which you can access with the @c
 * notification_event_get_item_id() and @c notification_event_get_context()
 * functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
/**
 * The notification was correctly parsed.
 *
 * @since BlackBerry 10.0.0
 */
   NOTIFICATION_OK = 0x00,
/**
 * A generic error occured in the notification.
 *
 * @since BlackBerry 10.0.0
 */
   NOTIFICATION_ERROR = 0x01,
/**
 * A dialog was displayed, and the user selected an option.
 *
 * @since BlackBerry 10.0.0
 */
   NOTIFICATION_CHOICE = 0x02,
} notification_response_t;

/**
 * The maximum number of prompt choices that can be displayed by a dialog.
 *
 * @since BlackBerry 10.0.0
 */
#define NOTIFICATION_MAX_PROMPT_CHOICES 4

/**
 * @brief Start receiving notification events
 *
 * The @c notification_request_events() function starts the delivery of
 * notification events to your application using BPS.
 *
 * If the application doesn't have permissions to listen to notifications, this
 * function will fail. Events are posted to the currently active channel.
 *
 * The varieties of events that may be returned are specified in the @c
 * #notification_response_t enumeration.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 * all events are requested. Non-zero values is reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_request_events(int flags);

/**
 * @brief Stop receiving notification events
 *
 * The @c notification_stop_events() function stops notification events from being delivered
 * to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *        events are stopped. The meaning of non-zero values is reserved for
          future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_stop_events(int flags);

/**
 * @brief Get the unique Domain ID for the notification service
 *
 * The @c notification_get_domain() function gets the unique Domain ID for the
 * notification service.  Use this function in an application to test whether an
 * event retrieved using @c bps_get_event() is a notification event.
 *
 * @return The Domain ID for the notification service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_get_domain(void);

/**
 * @brief Create a notification message structure and allocate all necessary
 * memory
 *
 * The @c notification_message_create() function creates a @c
 * #notification_message_t structure called @c message to be used by the
 * notification system.
 *
 * @param message The @c #notification_message_t structure to populate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_create(notification_message_t ** message);

/**
 * @brief Deallocate the memory used by a notification message structure
 *
 * The @c notification_message_destroy() function deallocates any memory set to
 * a given @c message. Use this function to deallocate memory used by a @c
 * #notification_message_t structure that's no longer in use. Failing to do so
 * will result in a memory leak.
 *
 * @param message The @c #notification_message_t structure to deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void notification_message_destroy(notification_message_t ** message);

/**
 * @brief Set the @c request_id of @c message to allow OK/ERROR responses
 *
 * The @c notification_message_set_request_id() function sets the request ID of
 * a @c #notification_message_t structure. You may add a @c request_id to
 * receive notification response events from the notification server. A @c
 * NOTIFICATION_ERROR or @c NOTIFICATION_OK response is delivered for every
 * message sent using the @c notification_alert() or @c notification_notify()
 * function. The @c request_id of the response will match the original message.
 * For this reason we recommend that you make them unique, but it isn't
 * strictly required.
 *
 * The @c request_id member is valid for the @c notification_alert(), @c
 * notification_notify(), @c notification_cancel(), and @c
 * notification_delete() functions.
 *
 * A @c request_id isn't required to receive @c NOTIFICATION_CHOICE responses.
 *
 * @param message The @c #notification_message_t structure whose @c request_id
 * you want to set.
 *
 * @param request_id The request ID you want to identify the message by.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_request_id(
        notification_message_t * message,
        const char * request_id);

/**
 * @brief Set the @c item_id of @c message
 *
 * The @c notification_message_set_item_id() function sets the item ID of a
 * given @c #notification_message_t structure. An item ID is required on all
 * messages used by the @c notification_alert() or @c notification_notify()
 * functions. The @c item_id member is valid in the @c notification_cancel() and
 * @c notification_delete() functions as well.
 *
 * Each item ID should be unique. If a notification with a given @c item_id is
 * currently active, sending another @e alert or @e notify message with the same
 * @c item_id will result in an error.
 * 
 * An item ID should only contain alphanumeric characters and underscores.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                item_id you want to set.
 *
 * @param item_id The item ID you want to identify the message by.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_item_id(notification_message_t * message,
        const char * item_id);

/**
 * @brief Set the @c title member of @c message
 *
 * The @c #notification_message_set_title() function sets the title to be
 * displayed by the notification message. The @c title member is valid for the
 * @c notification_alert() and @c notification_notify() functions.
 *
 * If you don't specify a title, the behavior depends on the type of
 * notification:
 *     - @c notification_notify(): The application name is used for a title
 *     - @c notification_alert(): No dialog notification is displayed if neither
 *                                the title nor the subtitle are specified.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                title you want to set.
 *
 * @param title The preferred title of the notification to be displayed.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_title(notification_message_t * message,
        const char * title);

/**
 * @brief Set the @c subtitle member of @c message
 *
 * The @c notification_message_set_subtitle() function sets the subtitle of a
 * notification to be displayed. The @c subtitle member is valid for the
 * @c notification_alert() and @c notification_notify() functions.
 *
 * If you don't call this function, no subtitle is displayed by the message.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                subtitle you want to set.
 *
 * @param subtitle The subtitle of the message to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_subtitle(notification_message_t * message,
        const char * subtitle);

/**
 * @brief Set the @c badge member of @c message
 *
 * @deprecated This function is deprecated. By default, we will put up badge if applicable.
 *
 * The @c notification_message_set_badge() function causes a splat to appear on
 * the application specified by the @c app_id (see image below for an example of
 * a splat applied to the "Messages" application icon). Use the @c
 * notification_cancel() function with the corresponding @c app_id to remove the
 * splat. The @c badge member is valid only for the @c notification_notify()
 * function.
 *
 * If you don't call this function, settings will control whether or not a badge
 * is added.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                badge you want to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_badge(notification_message_t * message) BPS_DEPRECATED;

/**
 * @brief Set the Sound URL member of @c message
 *
 * The @c notification_message_set_sound_url() function allows applications to
 * play different sounds within notifications of the same type. The sound data
 * member is valid for the @c notification_alert() and @c notification_notify()
 * functions.
 *
 * This property is optional. We recommend that you specify the sound name in
 * the settings for the application/notification type.
 *
 * If you don't call this function, a default sound specified in settings is
 * played.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                sound_url you want to set.
 *
 * @param sound_url The URL of the sound to play with the notification.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_sound_url(notification_message_t * message,
        const char * sound_url);

/**
 * @brief Set the @c target of @c message
 *
 * The @c notification_message_set_invocation_target() function sets an
 * invocation target to a given @c #notification_message_t structure. This
 * target is launched when the corresponding BlackBerry Hub item is clicked in
 * the Hub area. The @c target member is used only with the @c
 * notification_notify() function.
 *
 * If you don't call this function, no application is launched.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 * target you want to set.
 *
 * @param target The invocation framework identifier of the target to launch.
 *               The identifier should match the identifier returned by the
 *               invocation framework when the target application registered
 *               with the invocation framework.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_invocation_target(
        notification_message_t * message, const char * target);

/**
 * @brief Specify a payload of arbitrary data to be sent to the target
 *        application
 *
 * The @c notification_message_set_invocation_payload() function specifies a
 * payload to be sent to the target application via the invocation framework.
 * A payload is arbitrary data, which this function converts into base64 for
 * consumption by the invocation framework.
 *
 * The @c payload member is used only with the @c notification_notify()
 * function, and only when you've set an invocation target via the @c
 * notification_message_set_invocation_target() function.
 *
 * If you don't call this function, a payload URI is sent instead, or if you
 * haven't specified one (using the @c
 * notification_message_set_invocation_payload_uri() function), no data is
 * delivered on invocation.
 *
 * @param message A pointer to the @c #notification_message_t structure that you
 * want to set the @c payload for.
 *
 * @param payload The data to be handed to the application via invocation
 *                framework on launch. The buffer is automatically encoded to
 *                base64 to match the invocation framework.
 *
 * @param length The size of the @c payload data in bytes.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_invocation_payload(
        notification_message_t * message, const void * payload, int length);

/**
 * @brief Specify a base64-encoded payload of arbitrary data to be sent to the
 *        target application
 *
 * The @c notification_message_set_invocation_encoded_payload() function
 * specifies an encoded payload of arbitrary data to be sent to the target
 * application via the invocation framework.
 *
 * The encoded @c payload member is used only with the @c notification_notify()
 * function, and only when you've set an invocation target via the @c
 * notification_message_set_invocation_target() function, and no payload has
 * been provided through the @c notification_message_set_invocation_payload() or
 * @c notification_message_set_invocation_payload_uri() function.
 *
 * If you don't call this function, a payload URI (defined using the @c
 * notification_message_set_invocation_payload_uri() function) is sent instead,
 * or if you haven't specified one, no data is delivered on invocation.
 *
 * @param message A pointer to the @c #notification_message_t structure that you
 *                want to set the encoded @c payload for.
 *
 * @param payload The data to be handed to the application via invocation
 *                framework on launch. Encode the payload as base64 before
 *                passing it to this function to match the invocation framework.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_invocation_encoded_payload(
        notification_message_t * message, const char * payload);

/**
 * @brief Specify the MIME type of a payload
 *
 * The @c notification_message_set_invocation_type() function specifies the
 * content-type of a given payload. This is provided to the invocation framework
 * if an application is launched based on this notification.
 *
 * The @c invocation_type member is used only with the @c notification_notify()
 * function, and only when you've provided a payload through the @c
 * notification_message_set_invocation_encoded_payload(), @c
 * notification_message_set_invocation_payload(), or @c
 * notification_message_set_invocation_payload_uri() function.
 *
 * If you don't call this function, a provided payload is assumed to be
 * "text/plain".
 *
 * @param message A pointer to the @c #notification_message_t structure that you
 *                want to specify the @c invocation_type for.
 *
 * @param invocation_type The MIME type of an included payload. This is ignored
 *                        if you do not include a payload.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_invocation_type(
        notification_message_t * message, const char * invocation_type);

/**
 * @brief Set a @c payload_uri to be provided to a launch target
 *
 * The @c notification_message_set_invocation_payload_uri() function passes the
 * invoked application a URI to a payload, instead of directly including the
 * data in a @e notify message.
 *
 * The @c payload_uri member is used only with the @c notification_notify()
 * function, and only when a payload isn't provided through the @c
 * notification_message_set_invocation_encoded_payload() or @c
 * notification_message_set_invocation_payload() functions.
 *
 * If you don't call this function, data is taken from the @c payload member
 * (defined using either the @c notification_message_set_invocation_payload() or
 * @c notification_message_set_invocation_encoded_payload() function), or if you
 * haven't specified one, no data is delivered on invocation.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                payload_uri you want to set.
 *
 * @param payload_uri The path to the payload.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_invocation_payload_uri(
        notification_message_t * message, const char * payload_uri);

/**
 * @brief Set the @c action to be sent to the launch target
 *
 * The @c notification_message_set_invocation_action() function sets the @c
 * action member of a @c #notification_message_t structure, which supplies
 * information to the target application about how to react. The action should
 * be one that is registered with the invocation framework.
 *
 * The @c action member is used only with the @c notification_notify() function
 * when an invocation target is set with the @c
 * notification_message_set_invocation_target() function.
 *
 * If you don't call this function, the target isn't sent an action via the
 * invocation framework.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                action you want to set.
 *
 * @param action An action registered with the invocation framework, such as
 *               'bb.action.PUSH'.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_set_invocation_action(
        notification_message_t * message, const char * action);

/**
 * @brief Add a choice to a prompt notification
 *
 * The @c notification_message_add_prompt_choice() function adds a choice to a
 * prompt notification. If the @c #notification_message_t structure contains one
 * or more prompt choices and is passed to the @c notification_alert() function,
 * a dialog is displayed with the specified buttons. This function is used with
 * @c notification_alert() only.
 *
 * You can only add up to @c NOTIFICATION_MAX_PROMPT_CHOICES buttons to a
 * dialog. Adding more than @c NOTIFICATION_MAX_PROMPT_CHOICES results in the
 * return of @c BPS_FAILURE.
 *
 * @param message A pointer to the @c #notification_message_t structure to add
 *                the prompt choice to.
 *
 * @param label The button's label.
 *
 * @param context The context string to return if the button is selected. This
 *                is just a convenience for the application developer and isn't
 *                required. @c NULL can be provided instead.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_message_add_prompt_choice(
        notification_message_t * message,
        const char * label, const char * context);

/**
 * @brief Request an @e alert notification
 *
 * The @c notification_alert() function requests an @e alert notification
 * message.
 *
 * The presence or absence of some data members controls the presentation of the
 * notification message. All @e alerts generate a vibration, LED, and sound
 * filtered by the current device and application-specific settings.
 *
 * Use this function to provide dialog display options that aren't filtered by
 * user settings. To display a dialog with feedback, supply prompt choices with
 * the @c notification_message_add_prompt_choice() function.
 *
 * The members required by an @e alert notification are:
 *     - @c item_id
 *
 * The additional members that @e alert will consider are:
 *     - @c title
 *     - @c subtitle
 *     - @c prompt_choices
 *     - @c request_id
 *
 * @param message The data members of the notification.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_alert(notification_message_t * message);

/**
 * @brief Request a @e notify notification with members specified in @c message
 *
 * The @c notification_notify() function requests a @e notify notification
 * message. This notification message supplies the information needed to create
 * various types of notifications.
 *
 * We recommend that the sender of the notification provide as much data as
 * possible so that the notification may be presented according to the user's
 * settings.
 *
 * The members required by a @e notify notification are:
 *     - @c item_id
 *
 * The additional members that @e notify will consider are:
 *     - @c title
 *     - @c subtitle
 *     - @c sound_url
 *     - @c invocation_target
 *     - @c invocation_payload
 *     - @c invocation_payload_uri
 *     - @c invocation_type
 *     - @c invocation_action
 *     - @c request_id
 *
 * @param message The data members of the notification.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_notify(notification_message_t * message);

/**
 * @brief Cancel a request for ongoing notifications like LED, dialog, etc
 *
 * The @c notification_cancel() function cancels a previous request for a
 * notification. Normally, the function attempts to cancel all notifications
 * that have been previously sent by the application. This causes the LED to
 * stop flashing, repeating sound/vibration to stop, and dialogs and badges to
 * be removed.
 *
 * If an item ID is provided in the @c #notification_message_t structure, the
 * function attempts to cancel the notification with the same @c item_id.
 *
 * @param message A pointer to a @c #notification_message_t structure. An @c
 *                item_id can be included. If additional members are provided,
 *                they are ignored by this call.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_cancel(notification_message_t * message);

/**
 * @brief Delete notifications from the universal inbox notifications area, and
 * cancel the notifications.
 *
 * The @c notification_delete() function deletes all of the calling
 * application's notifications from the BlackBerry Hub notifications area
 * automatically. The user may delete notifications from the Hub notifications
 * area manually.
 *
 * If you specify an item ID, this function attempts to delete a notification
 * that was previously sent notification with the same @c item_id instead of all
 * of them.
 *
 * @param message A pointer to a @c #notification_message_t structure.
 * An @c item_id can be included. If additional members are provided,
 * they are ignored by this call.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_delete(notification_message_t * message);

/**
 * @brief Return the category of the response
 *
 * The @c notification_event_get_response() function defines what sort of
 * response message the event contains. See the definition for @c
 * #notification_response_t for details.
 *
 * @param event The event to get the response from.
 *
 * @return A number corresponding to an entry in the @c #notification_response_t
 *         enumeration, or @c BPS_FAILURE if there's no event response set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_event_get_response(bps_event_t * event);

/**
 * @brief Get the @c item_id of the notification message structure that the
 * response refers to
 *
 * The @c notification_event_get_item_id() function retrieves the item ID of a
 * @c #notification_message_t structure referred to by a response event. The
 * response is present only for @c NOTIFICATION_CHOICE response events that
 * refer to a previous message which had an item ID. Otherwise, @c NULL is
 * returned.
 *
 * @param event The event to get the item ID from.
 *
 * @return The item ID, otherwise a @c NULL value.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * notification_event_get_item_id(bps_event_t * event);

/**
 * @brief Get the @c request_id of an event
 *
 * The @c notification_event_get_request_id() function retrieves the request ID
 * of an event. This is valid for @c NOTIFICATION_OK and @c NOTIFICATION_ERROR
 * messages, but not @c NOTIFICATION_CHOICE messages, since those have Item IDs.
 *
 * @param event The event to get the request ID from.
 *
 * @return The request ID of the message that this event is a response to,
 *         otherwise a @c NULL value.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * notification_event_get_request_id(bps_event_t * event);

/**
 * @brief Get the context argument of a choice response
 *
 * The @c notification_event_get_context() function retrieves the context
 * argument of a choice response event. The context is present only when @c
 * event refers to a @c NOTIFICATION_CHOICE response and the prompt originally
 * contained a context argument. Otherwise, @c NULL is returned.
 *
 * @param event The event to get the context argument from.
 *
 * @return The context argument of the choice response, otherwise a @c NULL
 *         value.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * notification_event_get_context(bps_event_t * event);

/**
 * @brief Get the choice response index of the item selected by the user
 *
 * The @c notification_event_get_choice() function retrieves the button index
 * value of a user selection. Buttons are indexed incrementally, the first
 * button being indexed as @c 1. This value is valid only if @c event is a @c
 * NOTIFICATION_CHOICE event. In other cases @c 0 is returned.
 *
 * @param event The event to get the choice response index value from.
 *
 * @return The index of the selected button, or a value of @c 0 if there's
 *         none.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int notification_event_get_choice(bps_event_t * event);

/*
 * @cond internal
 */

/**
 * @brief Tell the invocation framework to launch the target in the background.
 *
 * This is not available to all the clients. Requires use_notify_system
 * capability.
 *
 * This should only be used by internal applications with appropriate
 * permissions.
 *
 * The @c notification_message_set_invocation_launch_in_background() function
 * sets the @c invocation_launch_in_background member of a @c
 * #notification_message_t structure to true, which instructs the invocation
 * framework to launch a given target application in the background.
 *
 * This function is used only with the @c notification_notify() function when an
 * invocation target is set with the @c
 * notification_message_set_invocation_target() function.
 *
 * If you don't call this function, the target application, if given, is
 * launched in the foreground.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                invocation_launch_in_background member you want to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 */
BPS_API int notification_message_set_invocation_launch_in_background(
        notification_message_t * message);

/**
 * @brief Set the @c perimeter of @c message
 *
 * This is not available to all the clients. Requires use_notify_system
 * capability.
 *
 * The @c notification_message_set_perimeter() function sets the perimeter of
 * a @c #notification_message_t structure. Notification service will not show
 * perimeter protected data when perimeter is locked. The @c perimeter member
 * is used to protect the work related information.  Setting the perimeter
 * is only required for the hybrid applications that can run in both enterprise
 * and personal perimeters.  For the non hybrid applications the perimeter is
 * mandated to be the same as the sender.
 *
 * This is not mandatory. For the hybrid applications defaults to
 * @c NOTIFICATION_PERIMETER_TYPE_ENTERPRISE, for the other applications
 * defaults to the perimeter of the client
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 * perimeter you want to set.
 *
 * @param perimeter The perimeter of the targeted application.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 */
BPS_API int notification_message_set_perimeter(notification_message_t * message,
        notification_perimeter_type_t perimeter);

/**
 * @brief Set the @c app_id of @c message
 *
 * This is not available to all the clients. Requires use_notify_system capability.
 *
 * The @c notification_message_set_app_id() function sets the application ID of
 * a @c #notification_message_t structure. The @c app_id member is used to
 * retrieve settings for the notification, and is part of the key for the @c
 * notification_cancel() and @c notification_delete() functions.
 *
 * This is not mandatory. It defaults to the app id of the client.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 * app_id you want to set.
 *
 * @param app_id The ID of the targeted application. This is the reverse DNS
 * style package ID of the application (e.g. com.ea.needforspeed).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 */
BPS_API int notification_message_set_app_id(notification_message_t * message,
        const char * app_id);

/**
 * @brief Set the @c type member of @c message
 *
 * This is not available to all the clients. Requires use_notify_system capability.
 *
 * The @c notification_message_set_type() function sets the @c type of a given
 * @c #notification_message_t structure. The @c type member defines the settings
 * and default behavior of a notification. It does this by associating the
 * notification with one of the predefined notification types registered with
 * the application. Each notification type corresponds to a list of associated
 * settings that apply to any notifications of that type.
 *
 * The @c type member is valid for the @c notification_alert() and @c
 * notification_notify() functions.
 *
 * If you don't call this function, a default notification type is used for this
 * application.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 * type member you want to set.
 *
 * @param type The type of message. The possible values for this member are
 * defined by the ones registered with the application.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 */
BPS_API int notification_message_set_type(notification_message_t * message,
        const char * type);

/**
 * @brief Set the notification to repeatedly play an audible sound and/or
 *        repeatedly vibrate
 *
 * This is not available to all the clients. Requires use_notify_system
 * capability.
 *
 * The @c notification_message_set_repeating() function sets the @c repeating
 * member of a @c #notification_message_t structure to true, which causes the
 * sound and/or vibration to repeat until it is canceled by the user. The @c
 * repeating member is valid only for the @c notification_alert() function.
 *
 * If you set @c repeating to true, we recommend that you also set an item ID
 * using the @c notification_message_set_item_id() function, and send a cancel
 * message using the @c notification_cancel() function when it is no longer
 * necessary.
 *
 * If you don't call this function, the member is set to false. The notification
 * produces an audible sound and/or vibrates only once without repetition.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 * repeating member you want to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 */
BPS_API int notification_message_set_repeating(
        notification_message_t * message);

/**
 * @brief Set the @c event_time member of @c message
 *
 * This is not available to all the clients. Requires use_notify_system capability.
 *
 * The @c notification_message_set_event_time() function sets the time of the
 * event. Use this to display a countdown timer on a dialog notification. The @c
 * event_time member is used only with the @c notification_alert() function.
 *
 * If you don't call this function, no countdown timer is displayed on the
 * dialog.
 *
 * @param message A pointer to the @c #notification_message_t structure whose @c
 *                event_time you want to set.
 *
 * @param event_time The time of the event, for the purpose of including
 *                   a countdown timer as part of the dialog to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE
 * with @c errno set otherwise.
 */
BPS_API int notification_message_set_event_time(
        notification_message_t * message,
        time_t event_time);

/*
 * @endcond
 */

__END_DECLS

#endif /* _BPS_NOTIFICATION_H_INCLUDED */
