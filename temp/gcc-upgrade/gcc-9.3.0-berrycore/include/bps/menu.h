/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file menu.h
 *
 * @brief Functions and structures to build context aware menus
 *
 * This file defines the menu service which provides common, context-aware logic
 * for building menus. Similar to the invocation framework, the menu service can
 * construct menus and action bars based on a specified type. However, the menu
 * service also considers the domain-specific context of the data objects rather
 * than relying on simple types. For example, the menu service understands the
 * context of a phone number and its relationship to a contact. The menu service
 * populates the menu/action-bar with the appropriate actions based on the state
 * of the phone number such as whether it's related to a known contact or not.
 *
 * The menu service determines the appropriate actions to add to the menu
 * based on the context of the request. However, the menu service still defers
 * to the invocation service to locate all the registered targets/providers of
 * those actions.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_MENU_H_INCLUDED
#define _BPS_MENU_H_INCLUDED

#include "bps/bps.h"
#include "bps/navigator_invoke.h"
#include <stdbool.h>
#include <stddef.h>

__BEGIN_DECLS

/**
 * @brief An opaque structure representing a menu request
 *
 * The menu request has information about its action, data, uri, etc.
 *
 * Use the following functions to work with this data type:
 * - @c menu_request_create()
 * - @c menu_request_destroy()
 * - @c menu_request_events()
 * - @c menu_request_get_action()
 * - @c menu_request_get_data()
 * - @c menu_request_get_data_length()
 * - @c menu_request_get_metadata()
 * - @c menu_request_get_file_transfer_mode()
 * - @c menu_request_get_file_uri()
 * - @c menu_request_get_mime_type()
 * - @c menu_request_get_perimeter()
 * - @c menu_request_get_target_key()
 * - @c menu_request_get_target_type_mask()
 * - @c menu_request_send()
 * - @c menu_request_set_action()
 * - &c menu_request_set_bypass_target_selection_card()
 * - @c menu_request_set_data()
 * - @c menu_request_set_metadata()
 * - @c menu_request_set_file_transfer_mode()
 * - @c menu_request_set_file_uri()
 * - @c menu_request_set_mime_type()
 * - @c menu_request_set_perimeter()
 * - @c menu_request_set_target_key()
 * - @c menu_request_set_target_type_mask()
 *
 *
 * @since BlackBerry 10.0.0
 */
typedef struct menu_request_t menu_request_t;

/**
 * @brief An opaque structure representing a menu item
 *
 * The menu item has information about its title, size, sub-items, etc.
 *
 * Use the following functions to work with this data type:
 * - @c menu_item_get_icon()
 * - @c menu_item_get_secondary_icon()
 * - @c menu_item_get_secondary_title()
 * - @c menu_item_get_sub_item()
 * - @c menu_item_get_sub_items_size()
 * - @c menu_item_get_title()
 *
 *
 * @since BlackBerry 10.0.0
 */
typedef struct menu_item_t menu_item_t;



/**
 * @brief This enumeration defines the possible types of menu sub-items.
 *
 * Menu sub-items can be grouped into two general categories: channels or shortcuts.
 *
 * Shortcut sub-items are formed based on user preferences and usage. For example,
 * a device user might share pictures more frequently with a small set of contacts
 * using specific targets to share the content, such as email or BBM.
 * In order to tailor the sharing experience to the user's activity, the menu
 * will include menu sub-items that include display information and the menu
 * invocation that represent the user's preferences. For example, the menu sub-item
 * might include a contact's display name as the label, the invocation target icon
 * as the primary icon, and the contact's icon or avatar as the secondary icon.
 * The menu invocation would include the information necessary for the invocation
 * target to preselect that contact as the recipient of the shared content.
 * Shortcut sub-items also include a frecency (frequent/recent) score that can be
 * used to display the sub-item in a prominent position in the menu.
 *
 * Channel sub-items represent invocation targets that do not include user preference
 * specific information.  Channel sub-items include display information such as
 * the label and icon that represent the target to be invoked. Channel sub-items
 * also carry a frecency score that can be used to display the sub-item in a
 * more prominent position in the menu.
 *
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * The menu sub-item type is not specified.
     *
     * @since BlackBerry 10.2.0
     */
    MENU_SUB_ITEM_TYPE_UNSPECIFIED = 0,

    /**
     * The menu sub-item represents a menu entry that includes
     * target-related display information, such as the label and icon.
     *
     * @since BlackBerry 10.2.0
     */
    MENU_SUB_ITEM_TYPE_CHANNEL = 1,

    /**
     * The menu sub-item represents a menu entry that includes
     * contact-related display information, such as the label, icon
     * and secondary icon. It is intended to be displayed apart from
     * any @c MENU_SUB_ITEM_TYPE_CHANNEL items, possibly in a more
     * prominent position within the displayed menu, based on
     * the menu sub-item's frecency.
     *
     * @since BlackBerry 10.2.0
     */
    MENU_SUB_ITEM_TYPE_SHORTCUT_CONTACT = 2,

    /**
     * The menu sub-item represents a menu entry that includes
     * account-related display information, such as the label, icon
     * and secondary icon. It is intended to be displayed apart from
     * any @c MENU_SUB_ITEM_TYPE_CHANNEL items, possibly in a more
     * prominent position within the displayed menu, based on
     * the menu sub-item's frecency.
     *
     * @since BlackBerry 10.2.0
     */
    MENU_SUB_ITEM_TYPE_SHORTCUT_ACCOUNT = 3,

    /**
     * The menu sub-item represents a menu entry that includes
     * calendar event-related display information, such as the label, icon
     * and secondary icon. It is intended to be displayed apart from
     * any @c MENU_SUB_ITEM_TYPE_CHANNEL items, possibly in a more
     * prominent position within the displayed menu, based on
     * the menu sub-item's frecency.
     *
     * @since BlackBerry 10.2.0
     */
    MENU_SUB_ITEM_TYPE_SHORTCUT_EVENT = 4,
} menu_sub_item_type_t;

/**
 * @brief An opaque structure representing a menu sub-item
 *
 * The menu sub-item has information about its icon, label, sub-items, etc.
 *
 * Use the following functions to work with this data type:
 * - @c menu_sub_item_get_icon()
 * - @c menu_sub_item_get_secondary_icon()
 * - @c menu_sub_item_get_invocation()
 * - @c menu_sub_item_get_item()
 * - @c menu_sub_item_get_label()
 * - @c menu_sub_item_get_secondary_label()
 * - @c menu_sub_item_get_tertiary_label()
 * - @c menu_sub_item_has_children()
 * - @c menu_sub_item_get_frecency()
 * - @c menu_sub_item_get_type()
 *
 *
 * @since BlackBerry 10.0.0
 */
typedef struct menu_sub_item_t menu_sub_item_t;

/**
 * @brief An opaque structure representing a menu invocation
 *
 * The menu invocation has information about its target, action, uri, etc.
 *
 * Use the following functions to work with this data type:
 * - @c menu_invocation_get_action()
 * - @c menu_invocation_get_data()
 * - @c menu_invocation_get_data_length()
 * - @c menu_invocation_get_data()
 * - @c menu_invocation_get_file_transfer_mode()
 * - @c menu_invocation_get_mime_type()
 * - @c menu_invocation_get_perimeter()
 * - @c menu_invocation_get_target()
 * - @c menu_invocation_get_target_type()
 * - @c menu_invocation_get_uri()
 * - @c menu_invocation_get_uri_match()
 *
 *
 * @since BlackBerry 10.0.0
 */
typedef struct menu_invocation_t menu_invocation_t;

/**
 * @brief Define the menu service events
 *
 * Currently, there is only one event.
 *
 * @anonenum bps_menu_events Menu events
 *
 * @since BlackBerry 10.0.0
 */
enum {
/**
 * A get menu items response is received.
 *
 * @since BlackBerry 10.0.0
 */
    MENU_GET_MENU_ITEMS_RESULT = 0x01,
};

/**
 * @brief Start receiving menu service events
 *
 * The @c menu_request_events() function starts to deliver menu service
 * events to your application using BPS. Events are posted to the currently
 * active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 *        all events are requested. The meaning of non-zero values is reserved
 *        for future use.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_events(int flags);

/**
 * @brief Stop receiving menu service events
 *
 * The @c menu_stop_events() function stops menu service events from being
 * delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *        events are stopped. The meaning of non-zero values is reserved for
 *        future use.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the menu service
 *
 * The @c menu_get_domain() function retrieves the unique domain ID for the menu
 * service. You can use this function in your application to test whether an
 * event that you retrieve using @c bps_get_event() is a menu service event
 * and respond accordingly.
 *
 * @return The domain ID for the menu service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_get_domain();

/**
 * @brief Send the get menu items request
 *
 * The @c menu_request_send() function sends the get menu items request to the
 * menu service.
 *
 * @param request The get menu items request to send. The request cannot be
 *        NULL.
 * @param id The ID of the message used to correlate the request with the
 *        response @c MENU_GET_MENU_ITEMS_RESULT. The ID cannot be NULL.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_send(menu_request_t *request, const char *id);

/**
 * @brief Create the get menu items request
 *
 * The @c menu_request_create() function creates a get menu items request
 * instance. A request instance created through @c menu_request_create() must
 * be destroyed with @c menu_request_destroy() once it isn't needed.
 *
 * @param request The pointer to the get menu items request.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_create(menu_request_t **request);

/**
 * @brief Destroy the get menu items request
 *
 * The @c menu_request_destroy() function cleans up resources for the specified
 * request. Call this function only on the menu request objects that were
 * created through the @c menu_request_create() function.
 *
 * @param request The get menu items request to destroy.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_destroy(menu_request_t *request);

/**
 * @brief Set the action of the menu request
 *
 * The @c menu_request_set_action() function sets the action of the specified
 * menu request. The expected format is up to 50 characters based on the
 * following grammar:
 *
 * @code
 * action: [domain][sub-domain]
 * sub-domain: NUL | .[domain][sub-domain]
 * domain: [a-zA-Z]([a-zA-Z0-9_])*
 * @endcode
 *
 * For example, "bb.action.SHARE"
 *
 * @param request The menu request.
 * @param action The identifier of the action to be performed by the target.
 *        Omitting the action implies brokering applies to any action
 *         supported for the specified type or that the target infers the
 *         action.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_set_action(menu_request_t *request,
        const char* action);

/**
 * @brief Set the bypass target selection card flag of the menu request
 *
 * The @c menu_request_set_bypass_target_selection_card() function sets
 * the bypass target selection card flag of the specified menu request.
 * The target selection card is a platform-owned card that presents the
 * list of targets that can be selected when the user selects Share, Set,
 * or Open menu subitems from a returned menu.
 * By default, the flag is set to @c false, meaning the target selection
 * card will be used. To bypass the use of the target selection card and to
 * manage the menu manually, set this flag to @c true.
 *
 * @param request The menu request.
 * @param bypass_tsc A boolean indicating whether to bypass the use of the
 *               target selection card or not. Use @c true to indicate
 *               that the target selection card shall be bypassed and
 *               the client will take responsibility for managing the
 *               menu.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int menu_request_set_bypass_target_selection_card(menu_request_t *request,
        bool bypass_tsc);

/**
 * @brief Set the MIME type of the menu request
 *
 * The @c menu_request_set_mime_type() function sets the MIME type of the
 * specified menu request. The MIME type of the data to be acted on must be
 * provided if the file URI attribute is not provided. The expected format is:
 *
 * @code
 * mimetype: type subtype
 * type: [a-zA-Z0-9-_\.]+
 * subtype: NUL | / type subtype
 * @endcode
 *
 * For example, "image/png"
 *
 * @param request The menu request.
 * @param mime_type The MIME type to set.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_set_mime_type(menu_request_t *request,
        const char* mime_type);

/**
 * @brief Set the file URI of the menu request
 *
 * The @c menu_request_set_file_uri() function sets the file URI of the
 * specified menu request. The file URI is used for the type interface
 * and it must be provided if the type is not specified. The expected format is
 * a string value.
 *
 * For example, "file:///path/to/file.txt"
 *
 * @param request The request to update.
 * @param file_uri The file URI to set.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_set_file_uri(menu_request_t *request,
        const char* file_uri);

/**
 * @brief Set the transfer mode for the specified file
 *
 * The @c menu_request_set_file_transfer_mode() function sets the transfer
 * mode for the associated file URI value. The file transfer mode allows the
 * sender to control how data files are transferred between the sender and
 * the target. File transfer handling applies only to file URI values that
 * refer to files that are not in the share area.
 *
 * By default, such files are copied as read-only into the target's private
 * inbox. Using a file transfer mode, senders can change this behavior to skip
 * private file transfer and deliver the specified file URI or copy the
 * file read-write, or create a link to the file.
 *
 * When creating a link to the file, the file permissions must allow the
 * application owner to have read access (o+r). In addition, if the file
 * permissions are set to the application owner having write access (o+w), then
 * the sender must be the file owner for
 * @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK mode to succeed.
 *
 * @param request The request to update.
 * @param transfer_mode The file transfer mode that is applied to
 *        the invocation.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_set_file_transfer_mode(menu_request_t *request,
        navigator_invoke_file_transfer_mode_t transfer_mode);

/**
 * @brief Set the target key of the menu request
 *
 * The @c menu_request_set_target_key() function sets the target key of the
 * specified menu request. When the target key is set, the resulting menu
 * only includes actions and targets that match the target key.
 *
 * @param request The request to update.
 * @param target_key The target key to set.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int menu_request_set_target_key(menu_request_t *request,
        const char* target_key);

/**
 * @brief Set the target type mask of the menu request
 *
 * The @c menu_request_set_target_type_mask() function indicates whether to
 * include targets of type application, service, or card in the results
 * set. Including the value @c NAVIGATOR_INVOKE_TARGET_TYPE_SELF indicates that
 * a target will be included even if it is the same as the requesting client.
 *
 * The expected values are:
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION or
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD or
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE or
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS or
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_SELF
 * - a combination of the above
 *
 * For example, @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION |
 * @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD would include targets of type
 * application and card.
 *
 * @param request The request to update.
 * @param target_type_mask The target type to set.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_set_target_type_mask(menu_request_t *request,
        int target_type_mask);

/**
 * @brief Set the data of a menu request
 *
 * The @c menu_request_set_data() function sets the data of the specified menu
 * request.
 * The @c menu_request_set_data() function sets the data and data length of
 * the specified menu request. The menu service correlates the data with the
 * invoke target information it receives so that the target invocation,
 * including the data to be acted upon, can be made if the menu item is
 * selected.
 * Omitting the data implies that the action and type are sufficient to carry
 * out the invocation.
 * The value of the data member can take the form of any binary data.
 *
 * @param request The menu request to update.
 * @param data The data to set. Omitting the data implies that the action-type
 *        is sufficient to carry out the invocation. Base64 encoding of binary
 *        data is not necessary as encoding is done for you.
 * @param data_length The size of the @c data member in bytes.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API
int menu_request_set_data(menu_request_t *request, const void* data,
    int data_length);

/**
 * @brief Set the metadata of a menu request
 *
 * The @c menu_request_set_metadata() function sets the metadata of the specified menu
 * request.
 * The @c menu_request_set_metadata() function sets the metadata of
 * the specified menu request. The menu service correlates the metadata with the
 * invoke target information it receives so that the target invocation,
 * including the associated metadata, can be made if the menu item is
 * selected.
 *
 * @param request The menu request to update.
 * @param metadata The metadata to set.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API
int menu_request_set_metadata(menu_request_t *request, const char* metadata);

/**
 * @cond internal
 */

/**
 * @brief Set the perimeter in which the resulting targets should reside
 *
 * This function should not be used by third-party developers. The Invocation
 * Framework will automatically take care of setting the perimeter across all
 * device configurations (e.g. Personal-only, Balance, Corporate Liable, etc.).
 * If you use this function to set the perimeter, it may create bugs in
 * particular device configurations.
 *
 * The @c menu_request_set_perimeter() function sets the perimeter in which the
 * resulting targets should reside. Setting the perimeter is only required for
 * hybrid applications that can run in both the enterprise and the personal
 * perimeters. In all cases, the perimeter is mandated to be the same as the
 * sender.
 *
 * The hybrid applications default to
 * @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL, while the other applications
 * default to the perimeter of the client.
 *
 * @param request The menu request to update.
 * @param perimeter The perimeter to set.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_set_perimeter(menu_request_t *request,
        navigator_invoke_perimeter_type_t perimeter);

/**
 * @endcond
 */

/**
 * @brief Retrieve the action from the menu request
 *
 * The @c menu_request_get_action() function extracts the action of
 * the specified menu request. The function doesn't copy data and
 * the returned values are released once the menu request is destroyed.
 *
 * @param request The menu request to retrieve the action from.
 * @return The menu request action if provided by the sender, NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_request_get_action(menu_request_t *request);

/**
 * @brief Retrieve the bypass target selection card flag from the menu request
 *
 * The @c menu_request_get_bypass_target_selection_card() function extracts the
 * bypass target selection card flag of the specified menu request.
 *
 * @param request The menu request to retrieve the action from.
 * @return The menu request bypass target selection card flag.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool menu_request_get_bypass_target_selection_card(menu_request_t *request);

/**
 * @brief Retrieve the MIME type from the menu request object
 *
 * The @c menu_request_get_mime_type() function extracts the MIME type of the
 * specified menu request object. The function doesn't copy data and the
 * returned values are released once the menu request is destroyed.
 *
 * @param request The menu request to retrieve the action from.
 * @return The menu request type if provided by the sender, NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_request_get_mime_type(menu_request_t *request);

/**
 * @brief Retrieve the file URI from the menu request object
 *
 * The @c menu_request_get_file_uri() function extracts the file URI of the
 * specified menu request object. The function doesn't copy data and
 * the returned values are released once the menu request is destroyed.
 *
 * @param request The menu request to retrieve file URI from.
 * @return The menu request file URI if provided by the sender, NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_request_get_file_uri(menu_request_t *request);

/**
 * @brief Retrieve the transfer mode of the menu request object
 *
 * The @c menu_request_get_file_transfer_mode() function extracts the
 * file transfer mode (@c #navigator_invoke_file_transfer_mode_t) from the
 * specified menu request object. The allowable return values are:
 *
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_PRESERVE
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RO
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RW
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK
 *
 * @param request The menu request to retrieve file transfer mode from.
 * @return The menu request file transfer mode if provided by the sender,
 *         @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_UNSPECIFIED otherwise.
 *         @c BPS_FAILURE is returned with @c errno set if an error occurs.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_get_file_transfer_mode(menu_request_t * request);

/**
 * @brief Retrieve the target key from the menu request object
 *
 * The @c menu_request_get_target_key() function extracts the target
 * key from the specified menu request object (see @c
 * menu_request_set_target_key()).
 *
 * @param request The menu request to retrieve the target key from.
 * @return The menu request target key.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const char* menu_request_get_target_key(menu_request_t *request);

/**
 * @brief Retrieve the target type mask from the menu request object
 *
 * The @c menu_request_get_target_type_mask() function extracts the target
 * type mask from the specified menu request object (see @c
 * menu_request_set_target_type_mask()).
 *
 * @param request The menu request to retrieve the target type mask from.
 * @return The menu request target type mask.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_get_target_type_mask(menu_request_t *request);

/**
 * @brief Retrieve the data from the menu request object
 *
 * The @c menu_request_get_data() function extracts the data from the specified
 * menu request object (see @c menu_request_set_data()).
 *
 * @param request The menu request to retrieve the data from.
 * @return The menu request data.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const void* menu_request_get_data(menu_request_t *request);

/**
 * @brief Retrieve the data length from the menu request object
 *
 * The @c menu_request_get_data_length() function extracts the length
 * of the data of the specified menu request object.
 *
 * @param request The menu request to retrieve the data length from (see @c
 *                menu_request_set_data()).
 *
 * @return The menu request data length.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_get_data_length(menu_request_t *request);

/**
 * @brief Retrieve the metadata from the menu request object
 *
 * The @c menu_request_get_metadata() function extracts the metadata from the
 * specified menu request object (see @c menu_request_set_metadata()).
 *
 * @param request The menu request to retrieve the metadata from.
 * @return The menu request metadata.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_request_get_metadata(menu_request_t *request);

/**
 * @brief Retrieve the perimeter from the menu request object
 *
 * The @c menu_request_get_perimeter() function extracts the perimeter from the
 * given menu request object (see @c menu_request_set_perimeter()).
 *
 * @param request The menu request to retrieve the perimeter from.
 * @return The perimeter upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_request_get_perimeter(menu_request_t *request);

/**
 * @brief Retrieve the ID from a menu event
 *
 * The @c menu_event_get_id() function extracts the ID from the
 * @c MENU_GET_MENU_ITEMS_RESULT event.
 *
 * @param event The event to extract the ID from.
 * @return The ID field from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_event_get_id(bps_event_t *event);

/**
 * @brief Retrieve the error message from a menu event
 *
 * The @c menu_event_get_err() function extracts the error message from the
 * @c MENU_GET_MENU_ITEMS_RESULT event.
 *
 * @param event The event to extract the error message from.
 * @return The error message from the event, @c NULL if there is no
 *         error message.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *menu_event_get_err(bps_event_t *event);

/**
 * @brief Retrieve the menu item
 *
 * The @c menu_event_get_menu_item() function extracts the menu item from the
 * @c MENU_GET_MENU_ITEMS_RESULT event. The function doesn't copy data and the
 * returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * Menu item ownership is not transferred to the application. An
 * application must not call the free function on the menu item pointers that
 * are retrieved using the @c menu_event_get_item() function. The pointer to
 * the menu item is valid until the @c bps_get_event() function is called
 * again.
 *
 * @param event The event to extract the menu item from.
 * @return The menu item from the event, @c NULL if there is no menu item.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API menu_item_t *menu_event_get_item(bps_event_t *event);

/**
 * @brief Retrieve the title from the menu item object
 *
 * The @c menu_item_get_title() function extracts the title of the given menu
 * item object. The title is used at the top of the menu to describe the
 * items within it. The function doesn't copy the data and the returned values
 * are released once the @c bps_get_event() function is called again.
 *
 * @param item The menu item to retrieve the title from.
 * @return The title from the menu item, @c NULL if there is no title.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_item_get_title(menu_item_t *item);

/**
 * @brief Retrieve the secondary title from the menu item object
 *
 * The @c menu_item_get_secondary_title() function extracts the secondary title
 * of the given menu item object. The secondary title may be presented as a
 * subscript to the main title. The function doesn't copy the data and the
 * returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param item The menu item to retrieve the secondary title from.
 * @return The secondary title from the menu item, @c NULL if there is no
 *         secondary title.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_item_get_secondary_title(menu_item_t *item);

/**
 * @brief Retrieve the icon URI from the menu item object
 *
 * The @c menu_item_get_icon() function extracts the icon URI of the given menu
 * item object. The function doesn't copy the data and the returned values are
 * released once the @c bps_get_event() function is called again.
 *
 * For example, "file:///path/to/icon"
 *
 * @param item The menu item to retrieve the icon URI from.
 * @return The icon URI from the menu item, @c NULL if there is no icon URI.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_item_get_icon(menu_item_t *item);

/**
 * @brief Retrieve the secondary icon URI from the menu item object
 *
 * The @c menu_item_get_secondary_icon() function extracts the secondary icon
 * URI of the given menu item object. The function doesn't copy the data and
 * the returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * For example, "file:///path/to/icon"
 *
 * @param item The menu item to retrieve the icon URI from.
 * @return The secondary icon URI from the menu item, @c NULL if there is no
 *         secondary icon URI.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_item_get_secondary_icon(menu_item_t *item);

/**
 * @brief Retrieve the number of sub-menu items inside the menu item
 *
 * The @c menu_item_get_sub_items_size() function extracts the number of
 * sub-menu items in the menu item.
 *
 * @param item The menu item to retrieve the number of sub-menu items from.
 * @return The number of sub-menu items inside the menu item.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API size_t menu_item_get_sub_items_size(menu_item_t *item);

/**
 * @brief Retrieve the sub-menu item inside the menu item
 *
 * The @c menu_item_get_sub_item() function extracts the sub-menu item at the
 * specific index inside the menu item. The function doesn't copy data and the
 * returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * The sub-menu item ownership is not transferred to the application. An
 * application must not call the free function on sub-menu item pointers that
 * are retrieved using the @c menu_item_get_sub_item() function. The pointer to
 * the sub-menu item is valid until the @c bps_get_event() function is called
 * again.
 *
 * @param item The menu item to retrieve the sub-menu item from.
 * @param index The index of the sub-menu item inside the menu item.
 * @return The pointer to the returned sub-menu item, NULL if @c item is NULL
 *         or the @c index is out of bounds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API menu_sub_item_t* menu_item_get_sub_item(menu_item_t *item,
        int index);

/**
 * @brief Retrieve the icon URI from the sub-menu item object
 *
 * The @c menu_sub_item_get_icon() function extracts the icon URI of the given
 * sub-menu item object. The function doesn't copy the data and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * For example. "file:///path/to/icon"
 *
 * @param item The sub-menu item to retrieve the icon URI from.
 * @return The icon URI from the sub-menu item, @c NULL if there is no icon URI.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_sub_item_get_icon(menu_sub_item_t *item);

/**
 * @brief Retrieve the secondary icon URI from the sub-menu item object
 *
 * The @c menu_item_get_secondary_icon() function extracts the secondary icon
 * URI of the given sub-menu item object. The secondary icon may be presented as
 * an overlay on a larger icon. The function doesn't copy the data and
 * the returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * For example, "file:///path/to/secondary_icon"
 *
 * @param item The menu item to retrieve the secondary icon URI from.
 * @return The secondary icon URI from the menu item, @c NULL if there is
 *         no icon URI.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char* menu_sub_item_get_secondary_icon(menu_sub_item_t *item);

/**
 * @brief Retrieve the localized label from the sub-menu item object
 *
 * The @c menu_sub_item_get_label() function extracts the localized label of the
 * given sub-menu item object. The label describes the menu item. The function
 * doesn't copy the data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * For example, "Pictures"
 *
 * @param item The sub-menu item to retrieve the label from.
 * @return The label from the sub-menu item.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_sub_item_get_label(menu_sub_item_t *item);

/**
 * @brief Retrieve the secondary localized label from the sub-menu item object
 *
 * The @c menu_sub_item_get_secondary_label() function extracts the secondary
 * localized label of the given sub-menu item object. The function doesn't copy
 * the data and the returned values are released once the @c bps_get_event()
 * function is called again.
 *
 * For example, the secondary label can be used to display associated
 * account information such as "account@example.com".
 *
 * @param item The sub-menu item to retrieve the secondary label from.
 * @return The secondary label from the sub-menu item.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_sub_item_get_secondary_label(
        menu_sub_item_t *item);

/**
 * @brief Retrieve the tertiary localized label from the sub-menu item object
 *
 * The @c menu_sub_item_get_tertiary_label() function extracts the tertiary
 * localized label of the given sub-menu item object. The function doesn't
 * copy the data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * For example, the tertiary label can be used to display the associated phone
 * number such as "+16131234678".
 *
 * @param item The sub-menu item to retrieve the tertiary label from.
 * @return The tertiary label from the sub-menu item.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_sub_item_get_tertiary_label(
        menu_sub_item_t *item);

/**
 * @brief Determine if the sub-menu item object has another level of menu items
 *
 * The @c menu_sub_item_has_children() function determines if the sub-menu item
 * object has another level of sub-menus. If there are no children, call
 * @c menu_sub_item_get_invocation() to retrieve the invocation object.
 * If there are children, call @c menu_sub_item_get_item() to retrieve another
 * level of menu items.
 *
 * @param item The sub-menu item.
 * @return @c True if the sub-menu item has another level of menu items,
 *         @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool menu_sub_item_has_children(menu_sub_item_t *item);

/**
 * @brief Retrieve the frecency score of the sub-menu item
 *
 * The @c menu_sub_item_get_frecency() function extracts the frecency score of
 * the given sub-menu item object.
 *
 * @param item The sub-menu item.
 * @return The frecency from the sub-menu item.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int menu_sub_item_get_frecency(menu_sub_item_t *item);

/**
 * @brief Retrieve the type of the sub-menu item
 *
 * The @c menu_sub_item_get_type() function extracts the type of the given
 * sub-menu item object.
 *
 * @param item The sub-menu item.
 * @return The type of the sub-menu item as a value of the @c
 *         #menu_sub_item_type_t enum, or @c #MENU_SUB_ITEM_TYPE_UNSPECIFIED on
 *         error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int menu_sub_item_get_type(menu_sub_item_t *item);

/**
 * @brief Retrieve the invocation from the sub-menu item object
 *
 * The @c menu_sub_item_get_invocation() function extracts the invocation of the
 * given sub-menu item object. The function doesn't copy the data and the
 * returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param item The sub-menu item to retrieve the invocation from.
 * @return The invocation from the sub-menu item, @c NULL if there is no
 *         invocation.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API menu_invocation_t* menu_sub_item_get_invocation(
        menu_sub_item_t *item);

/**
 * @brief Retrieve the menu item from the sub-menu item object
 *
 * The @c menu_sub_item_get_item() function extracts the menu item of the
 * given sub-menu item object. The function doesn't copy the data and the
 * returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param item The sub-menu item to retrieve the invocation from.
 * @return The menu item from the sub-menu item, @c NULL if there is no
 *         menu item.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API menu_item_t* menu_sub_item_get_item(menu_sub_item_t *item);

/**
 * @brief Retrieve the target type of the menu invocation
 *
 * The @c menu_invocation_get_target_type() function extracts the target type
 * of the specified menu invocation object. The allowable return values are:
 *
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 * - @c NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS
 *
 * @param invocation The menu invocation to retrieve the target type from.
 * @return The target type inside the menu invocation on success, @c BPS_FAILURE
 *         with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_invocation_get_target_type(menu_invocation_t *invocation);

/**
 * @brief Retrieve the target of the menu invocation
 *
 * The @c menu_invocation_get_target() function extracts the target of the given
 * menu invocation object. The function doesn't copy the data and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * @param invocation The menu invocation to retrieve the target from. The
 *        identifier of the target (as stated in its BAR manifest) to which
 *        invocation is delivered. If the target is supplied, then brokering is
 *        bypassed and an attempt is made to invoke the specified target.
 *
 * @return The target inside the menu invocation, @c NULL if there is no
 *         target.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_invocation_get_target(menu_invocation_t *invocation);

/**
 * @brief Retrieve the action of the menu invocation
 *
 * The @c menu_invocation_get_action() function extracts the action of the given
 * menu invocation object. The function doesn't copy the data and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * @param invocation The menu invocation to retrieve the action from.
 *        The identifier of the action to be performed by the target. Omitting
 *        action implies brokering applies to any action supported for the
 *        specified type or that the target infers the action.
 * @return The action inside the menu invocation, @c NULL if there is no
 *         action.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_invocation_get_action(menu_invocation_t *invocation);

/**
 * @brief Retrieve the MIME type of the menu invocation
 *
 * The @c menu_invocation_get_mime_type() function extracts the MIME type of the
 * given menu invocation object. The function doesn't copy the data and the
 * returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param invocation The menu invocation to retrieve the MIME type from.
 * @return The MIME type inside the menu invocation, @c NULL if there is no
 *         MIME type.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_invocation_get_mime_type(
        menu_invocation_t *invocation);

/**
 * @brief Retrieve the URI pointing to the invocation data
 *
 * The @c menu_invocation_get_uri() function extracts the URI pointing to the
 * invocation data. If the URI is not provided then this implies the
 * "data://local" URI indicating that the invocation data is provided in-band
 * retrieved through @c menu_invocation_get_data() function. The function
 * doesn't copy the data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * @param invocation The menu invocation to retrieve the URI from.
 * @return The URI inside the menu invocation, @c NULL if there is no URI.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_invocation_get_uri(menu_invocation_t *invocation);

/**
 * @brief Retrieve the matching URI pattern in the invocation's target filter
 *
 * The @c menu_invocation_get_uri_match() function extracts the URI pattern
 * that was matched in the invocation target's target filter when the menu
 * service queried for applicable targets for a given URI.
 * Although the URI pattern is an attribute of a @c #menu_invocation_t,
 * it shall not be used to populate a @c #navigator_invoke_invocation_t like
 * the other @c #menu_invocation_t parameters.
 * The URI pattern can be used when additional information about the invocation
 * target is needed. For example, if the application adds an option to set the
 * target as the default target for a specific action, it might be required
 * to provide this URI pattern in order to register the target as the default.
 * The function doesn't copy the data and the returned values are released once
 * the @c bps_get_event() function is called again.
 *
 * @param invocation The menu invocation to retrieve the URI match value from.
 * @return The URI match value inside the menu invocation, @c NULL if there is no
 *         URI match value.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char* menu_invocation_get_uri_match(menu_invocation_t *invocation);

/**
 * @brief Retrieve the transfer mode of the menu @c invocation object
 *
 * The @c menu_invocation_get_file_transfer_mode() function extracts the file
 * transfer mode (@c #navigator_invoke_file_transfer_mode_t) of the given menu
 * invocation object. The allowable return values are:
 *
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_UNSPECIFIED
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_PRESERVE
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RO
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RW
 * - @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK
 *
 * @param invocation The menu invocation to retrieve the data from.
 * @return The menu request file transfer mode if provided by the sender,
 *         @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_UNSPECIFIED otherwise,
 *         @c BPS_FAILURE with @c errno set if an error occurs.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_invocation_get_file_transfer_mode(
        menu_invocation_t *invocation);

/**
 * @brief Retrieve the data of the menu invocation
 *
 * The @c menu_invocation_get_data() function extracts the data of the
 * given menu invocation object which is encoded based on the specified
 * MIME type. Omitting the data implies that the action-type are
 * sufficient to carry out the invocation. The function doesn't copy the data
 * and the returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param invocation The menu invocation to retrieve the data from.
 * @return The data inside the menu invocation, @c NULL if there is no data.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const void* menu_invocation_get_data(menu_invocation_t *invocation);

/**
 * @brief Retrieve the data length from a @c menu invocation
 *
 * The @c menu_invocation_get_data_length() function extracts the
 * length in bytes of the data of a given @c menu_invocation_t structure.
 * The @c data_length member is used by the invocation handler to identify
 * the size of the data the invoked handler is to perform an action on
 * (see the @c menu_invocation_get_data() function for further details).
 *
 * @param invocation A pointer to the @c menu_invocation_t structure
 *                   whose @c data_length member you want to retrieve.
 * @return The size in bytes of the invocation data if one was provided by the
 *         sender, -1 otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_invocation_get_data_length(const menu_invocation_t *invocation);

/**
 * @brief Retrieve the metadata of the menu invocation
 *
 * The @c menu_invocation_get_metadata() function extracts the metadata of the
 * given menu invocation object. The function doesn't copy the data
 * and the returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param invocation The menu invocation to retrieve the metadata from.
 * @return The metadata inside the menu invocation, @c NULL if there is no metadata.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* menu_invocation_get_metadata(menu_invocation_t *invocation);

/**
 * @brief Retrieve the perimeter from the menu invocation object
 *
 * The @c menu_invocation_get_perimeter() function extracts the perimeter of the
 * given menu invocation object. The allowable return values are:
 *
 * - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 * - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * @param invocation The menu invocation to retrieve the data from.
 * @return The perimeter upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int menu_invocation_get_perimeter(menu_invocation_t *invocation);

__END_DECLS

#endif // include guard
