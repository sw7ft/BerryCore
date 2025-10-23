/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file paymentservice.h
 *
 * @brief Functions and structures to allow users to purchase digital goods in
 * applications using the BlackBerry Platform Services (BPS) Payment Service API
 *
 * The Payment Service API permits BlackBerry device users to initiate the
 * purchase of digital goods from within your application. Digital goods
 * available for purchase must be registered on the Vendor Portal for BlackBerry
 * World. For example, you can use the API to allow users to purchase additional
 * levels in a gaming application or music from a radio application.
 *
 * Purchases are initiated using the @c
 * paymentservice_purchase_request_with_arguments() function. The amount of time
 * that elapses before a response is returned depends on how quickly the user
 * completes the purchase process. The purchase process may include steps such
 * as signing in to their BlackBerry ID account, setting up their preferred
 * billing method, and so on. The Payment Service dispatches a @c
 * PURCHASE_RESPONSE event on purchase completion. The event contains a response
 * code that can be used to determine whether the purchase request was
 * successful or not.
 *
 * When calling the purchase function, you must provide either the ID or SKU of
 * the digital good to be purchased. It is not a requirement to provide both the
 * ID and SKU, and all other arguments are optional. When both the ID and SKU
 * are provided, the ID takes precedence. The SKU is only used when the digital
 * good cannot be located on the Payment Service server based on the ID.
 *
 * If an application requires a list of its digital goods that have already been
 * purchased by the user (for example, to avoid offering for sale a digital good
 * that the user already owns), this list can be obtained with the @c
 * paymentservice_get_existing_purchases_request() function. This function
 * requires the same user interaction as the purchase function, so it can also
 * be a long-running method. Upon completion of the request, the Payment Service
 * dispatches a @c GET_EXISTING_PURCHASES_RESPONSE event, which contains the
 * success/failure response code.
 *
 * The strings that are passed as input to the request functions and the strings
 * returned by the getter functions are ASCII-encoded by default.  When UTF-8
 * encoding is required, it is the responsibility of the application to convert
 * the UTF-8 encoded string to @c char* format. Conversely, it is your
 * responsibility to convert a returned @c char* format to a UTF-8 encoded
 * values as required.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef PAYMENTSERVICE_H_INCLUDED
#define PAYMENTSERVICE_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible Payment Service events
 *
 * This enumeration defines the Payment Service events.
 * @anonenum bps_paymentservice_events Payment service events 
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Indicates that a response to a purchase request has been received.
     *
     * @since BlackBerry 10.0.0
     */
    PURCHASE_RESPONSE = 0x00,

    /**
     * Indicates that a response to a request to retrieve purchase history has
     * been received.
     *
     * @since BlackBerry 10.0.0
     */
    GET_EXISTING_PURCHASES_RESPONSE = 0x01,

    /**
     * Indicates that a response to a request to get the price of a digital 
     * good has been received.
     *
     * @since BlackBerry 10.0.0
     */
    GET_PRICE_RESPONSE = 0x02,

    /**
     * Indicates that a response to a request to check the subscription status
     * of a digital good has been received.
     *
     * @since BlackBerry 10.0.0
     */
    CHECK_EXISTING_RESPONSE = 0x03,

    /**
     * Indicates that a response to a request to cancel a subscription has been
     * received.
     *
     * @since BlackBerry 10.0.0
     */
    CANCEL_SUBSCRIPTION_RESPONSE = 0x04,
};

/**
 * This enumeration defines response codes. These response codes indicate
 * whether a request that was sent to the Payment Service was successful or
 * unsuccessful.
 * @anonenum bps_paymentservice_responsecodes Payment service response codes
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Indicates that a request that was sent to the Payment Service was
     * successful.
     *
     * @since BlackBerry 10.0.0
     */
    SUCCESS_RESPONSE = 0,

    /**
     * Indicates that a request that was sent to the Payment Service failed.
     *
     * @since BlackBerry 10.0.0
     */
    FAILURE_RESPONSE = 1,
};

/**
 * This enumeration defines the possible states of a digital good. For example,
 * whether the digital good item is owned, subscribed, cancelled, renewed, or
 * unknown.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the digital good is not a subscription and is owned by the
     * user.
     *
     * @since BlackBerry 10.0.0
     */
    ITEM_STATE_OWNED = 0,

    /**
     * Indicates that the user is currently subscribed to the digital good.
     * It's a new subscription.
     *
     * @since BlackBerry 10.0.0
     */
    ITEM_STATE_NEW_SUBSCRIPTION,

    /**
     * Indicates that the subscription digital good has been refunded. The user
     * is no longer subscribed.
     *
     * @since BlackBerry 10.0.0
     */
    ITEM_STATE_SUBSCRIPTION_REFUNDED,

    /**
     * Indicates that the subscription has been cancelled. It is possible that
     * the subscription is still active. You can use the @c
     * paymentservice_check_existing() function to determine if the subscription
     * is still active or compare the end date with the current date.
     *
     * @since BlackBerry 10.0.0
     */
    ITEM_STATE_SUBSCRIPTION_CANCELLED,

    /**
     * Indicates that the user is currently subscribed and they have renewed the
     * subscription.
     *
     * @since BlackBerry 10.0.0
     */
    ITEM_STATE_SUBSCRIPTION_RENEWED,

    /**
     * Indicates that the state of the item is unknown.
     *
     * @since BlackBerry 10.0.0
     */
    ITEM_STATE_UNKNOWN
} item_state_t;

/**
 * @brief Possible Payment Service errors
 *
 * This enumeration defines the Payment Service errors.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * This error occurs when a user cancels the request.
     * @c paymentservice_event_get_error_info() will not contain any additional
     * information to diagnose the problem.
     *
     * @since BlackBerry 10.2.0
     */
    PAYMENTSERVICE_ERROR_USER_CANCELLED = 1,

    /**
     * This error occurs when a user attempts to purchase more than one item
     * at a time.
     * @c paymentservice_event_get_error_info() will not contain any additional
     * information to diagnose the problem.
     *
     * @since BlackBerry 10.2.0
     */
    PAYMENTSERVICE_ERROR_SYSTEM_BUSY = 2,

    /**
     * Payment Service failed. See @c paymentservice_event_get_error_text()
     * and @c paymentservice_event_get_error_info() for more detail.
     *
     * @since BlackBerry 10.2.0
     */
    PAYMENTSERVICE_ERROR_PAYMENTSERVICE_FAILED = 3,

    /**
     * No network connectivity on device. The request cannot be completed until
     * the device connects to a network.
     * @c paymentservice_event_get_error_info() will not contain any additional
     * information to diagnose the problem.
     *
     * @since BlackBerry 10.2.0
     */
    PAYMENTSERVICE_ERROR_NO_NETWORK = 8,
} paymentservice_error_t;

/**
 * @typedef struct purchase_arguments_t
 * @brief Opaque purchase arguments type
 *
 * The @c #purchase_arguments_t structure is an opaque handle to a set of
 * purchase arguments to be passed as the argument to a @c
 * paymentservice_purchase_request_with_arguments() call. Arguments can be set
 * on the structure via the various @c paymentservice_purchase_arguments_set
 * functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct purchase_arguments_t purchase_arguments_t;

/**
 * @brief Used when checking the status of an app-level subscription. This is
 * passed to @c paymentservice_check_existing() as the @c digital_good_id
 * parameter.
 *
 * @since BlackBerry 10.0.0
 */
#define PAYMENTSERVICE_APP_SUBSCRIPTION "-1"

/**
 * @brief Make a request to begin receiving events
 *
 * The @c paymentservice_request_events() function starts to deliver Payment
 * Service events to your application using BPS. Events will be posted to the
 * currently active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 *              all events are requested. The meaning of non-zero values is
 *              reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_request_events(int flags);

/**
 * @brief Stop receiving Payment Service events
 *
 * The @c paymentservice_stop_events() function stops Payment Service events
 * from being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *              events are stopped. The meaning of non-zero values is reserved
 *              for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the Payment Service
 *
 * The @c paymentservice_get_domain() function gets the unique domain ID for the
 * Payment Service. You can use this function in your application to test
 * whether an event that you retrieve using the @c bps_get_event() function is a
 * Payment Service event, and respond accordingly.
 *
 * @return The domain ID for the Payment Service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_get_domain();

/**
 * @brief Initiate the purchase of a digital good
 *
 * The @c paymentservice_purchase_request() function initiates the purchase of a
 * digital good.
 *
 * It is not a requirement to provide both the ID and SKU, and all other
 * arguments are optional. The ID takes precedence when your application
 * provides both the ID and SKU. The SKU is only used only when the digital good
 * cannot be located on the Payment Service server based on the ID.
 *
 * You should provide the name of the digital good when a single ID or SKU
 * represents multiple digital goods on the Payment Service server and when a
 * more specific digital good name is required for display on the purchase
 * screen. For example, if a game sells additional levels using the Payment
 * Service at a single price point, then a generic "My game level" digital good
 * can be used for all such levels. However, at the time of purchase, the game
 * application can override "My game level" with the name of the level that was
 * purchased. This mechanism is useful to notify the end user of what is being
 * purchased on the purchase confirmation screen.
 *
 * Metadata offers the application developer a way to store information about
 * each purchase on the Payment Service server and to retrieve that data using
 * the @c paymentservice_get_existing_purchases_request() function. For example,
 * assume a book vendor offers several titles at a single price point, and
 * represents them on the Vendor Portal as a single digital good. In this case,
 * the ISBN of the book can be provided as metadata. The metadata can be used to
 * uniquely identify the digital good that was purchased. You can also retrieve
 * the entire list of purchased books at any time by using the @c
 * paymentservice_get_existing_purchases_request() function to obtain previous
 * purchases, filtering on the book's digital good Content ID, and finally,
 * enumerating the ISBNs in the metadata of each purchase.
 *
 * To further give context to the end user during an in-application purchase, a
 * banner is displayed along the top of the purchase and BlackBerry ID login
 * screens. The banner shows the name and icon of the application that the
 * purchase is being made from.
 *
 * To customize the name and icon that are displayed, simply provide them as
 * arguments. When the name or icon are not provided as arguments, then they are
 * retrieved from the purchasing application's bar-descriptor.xml file - though
 * this may not work for applications that register with the home screen
 * dynamically. In these cases, it is highly recommended that the purchasing
 * application explicitly provides a name and icon as part of the purchase
 * arguments.

 * There may be output parameters present, in the form of key/value pairs, in
 * the @c PURCHASE_RESPONSE. The number of output parameters, if any, can be
 * retrieved via @c paymentservice_event_get_extra_parameter_count(), and the
 * parameters themselves can be retrieved via @c
 * paymentservice_event_get_extra_parameter_key_at_index()
 * and @c paymentservice_event_get_extra_parameter_value_at_index().
 *
 * @param digital_good_id The ID of the digital good to purchase. Use a @c NULL
 *                        value if @c digital_good_sku should be used to
 *                        reference the digital good on the server.
 * @param digital_good_sku The SKU of the digital good to purchase. Use a @c
 *                         NULL value if the @c digital_good_id should be used
 *                         to reference the digital good on the server.
 * @param digital_good_name (Optional) The name of the digital good to
 *                          purchase. Use a @c NULL to omit this argument.
 * @param metadata (Optional) The metadata for the digital good. Use a @c NULL
 *                 value to omit this argument.
 * @param app_name (Optional) The name of the application through which the
 *                 purchase is being made, or a @c NULL value to omit this
 *                 argument. If provided, this name will be displayed in a
 *                 banner along the top of the purchase confirmation screen that
 *                 shall be presented to the user.
 * @param app_icon (Optional) The full URL to an icon to display, or a @c NULL
 *                 value to omit this argument. If provided, the icon shall be
 *                 displayed on the purchase confirmation screen that shall be
 *                 presented to the user.
 * @param group_id The window group ID of the application. This ID is required
 *                 so that the Payment Service can properly display dialogs.
 * @param request_id The Payment Service populates this argument upon
 *                   successful completion of the request with the request ID.
 *                   It can be used to correlate the response to the request.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_request(const char* digital_good_id,
        const char* digital_good_sku, const char* digital_good_name,
        const char* metadata, const char* app_name, const char* app_icon,
        const char* group_id, unsigned* request_id);

/**
 * @brief Initiate the purchase of a digital good
 *
 * The @c paymentservice_purchase_request_with_arguments() function initiates
 * the purchase of a digital good, using the contents of the provided @c
 * #purchase_arguments_t as its arguments.
 *
 * A @c #purchase_arguments_t can be acquired via @c
 * paymentservice_purchase_arguments_create() and populated using the various
 * @c paymentservice_purchase_arguments_set functions.
 *
 * See the @c paymentservice_purchase_request() function for more details on
 * requirements and options for purchase arguments.
 *
 * In addition to the arguments outlined in the @c
 * paymentservice_purchase_request() function, @e extra parameters can be
 * attached to a @c #purchase_arguments_t using the @c 
 * paymentservice_purchase_arguments_set_extra_parameter(). These extra
 * parameters are only relevant to the initial purchase (and would no longer be
 * present, for example, in a @c GET_EXISTING_PURCHASE_RESPONSE). Input and
 * output (see @c paymentservice_purchase_request()) parameters may not be
 * directly related (i.e. output parameters may be present in the @c
 * PURCHASE_RESPONSE where none were input, or vice versa).
 *
 * Once a purchase has been initiated, the @c #purchase_arguments_t must be
 * freed using @c paymentservice_purchase_arguments_destroy().
 *
 * @param purchase_arguments The set of arguments to use for the purchase.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_request_with_arguments(purchase_arguments_t* purchase_arguments);

/**
 * @brief Retrieve the previous successful purchases
 *
 * The @c paymentservice_get_existing_purchases_request() function retrieves the
 * previous successful purchases made by the end user from within the calling
 * application.
 *
 * @param allow_refresh A value of @c true specifies that the device should be
 *                      allowed to refresh the list of purchases from the
 *                      Payment Service server, When a value of @c false is
 *                      specified, the current list of cached purchases is
 *                      returned immediately.
 * @param group_id The window group ID of the application. This ID is required
 *                 so that the Payment Service can properly display dialogs.
 * @param request_id The Payment Service populates this argument upon
 *                   successful completion of the request with the request ID.
 *                   It can be used to correlate the response to the request.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_get_existing_purchases_request(bool allow_refresh,
        const char* group_id, unsigned* request_id);

/**
 * @brief Retrieve the price of a digital good
 *
 * The @c paymentservice_get_price() function gets the price of a digital good.
 * Only the ID or SKU of the digital good is required as input in order to
 * retrieve the digital good's price. If the ID and SKU are both provided, then
 * the ID is used. To use the SKU, you must pass an empty string for the @c
 * digital_good_id.
 *
 * @param digital_good_id   The digital good ID.
 * @param digital_good_sku  The digital good SKU.
 * @param group_id The window group ID of the application. This ID is required
 *                 so that the Payment Service can properly display dialogs.
 * @param request_id The Payment Service populates this argument upon
 *                   successful completion of the request with the request ID.
 *                   It can be used to correlate the response to the request.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_get_price(const char* digital_good_id,
        const char* digital_good_sku, const char* group_id,
        unsigned* request_id);

/**
 * @brief Determine whether a subscription digital good is currently active
 *
 * The @c paymentservice_check_existing() function determines whether a
 * subscription digital good is currently active. Only the ID or SKU of the
 * digital good is required as input in order to retrieve the subscription
 * status of a digital good. If both are provided, then the ID takes precedence,
 * and the SKU will only be used in case the digital good cannot be retrieved
 * using the ID.
 *
 * @param digital_good_id The digital good ID. To check the status of a
 * subscription app (not a digital good), use @c PAYMENTSERVICE_APP_SUBSCRIPTION
 * as the @c digital_good_id parameter.
 * @param digital_good_sku The digital good SKU.
 * @param group_id The window group ID of the application. This ID is required
 *                 so that the Payment Service can properly display dialogs.
 * @param request_id The Payment Service populates this argument upon
 *                   successful completion of the request with the request ID.
 *                   It can be used to correlate the response to the request.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_check_existing(const char* digital_good_id,
        const char* digital_good_sku, const char* group_id,
        unsigned* request_id);

/**
 * @brief Cancel a subscription to a digital good
 *
 * To cancel a subscription to a digital good, you need to provide the 
 * purchase ID from the initial purchase, which you can retrieve using the 
 * @c paymentservice_event_get_purchase_id() function. You cannot cancel a 
 * subscription using the purchase ID of a subscription renewal.
 *
 * @param purchase_id The purchase ID of the digital good to cancel the
 *                    subscription to.
 * @param group_id The window group ID of the application. This ID is required
 *                 so that the Payment Service can properly display dialog 
 *                 boxes.
 * @param request_id The Payment Service populates this argument upon
 *                   successful completion of the request with the request ID.
 *                   It can be used to correlate the response to the request.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_cancel_subscription(const char* purchase_id,
        const char* group_id, unsigned* request_id);

/**
 * @brief Set the connection mode
 *
 * The @c paymentservice_set_connection_mode() function sets the connection mode
 * that is used in the application. If the connection mode is set to local, the
 * application does not contact the Payment Service server for any
 * transactions. For purchases, a simulated purchase screen is displayed,
 * allowing the user to choose the result of the purchase. For retrieving
 * purchase history, only simulated successful purchases are returned. This mode
 * is useful for testing how your application handles the possible results
 * without requiring network connections or currency.
 *
 * @b Note: Local connection mode should @b not be used in production code.
 *
 * If the connection mode is set to network, purchases and retrievals of
 * existing purchases proceed normally, contacting the Payment Service server as
 * necessary. This is the default connection mode, and applications in
 * production should not modify it.
 *
 * @param local When the value is @c true the connection mode is set to local,
 *              otherwise the connection mode is set to network.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_set_connection_mode(bool local);

/**
 * @brief Retrieve a purchase arguments structure to populate 
 *
 * Once populated, you can pass the @c #purchase_arguments_t structure to @c
 * paymentservice_purchase_request_with_arguments().
 *
 * The caller must call @c paymentservice_purchase_arguments_destroy() when done
 * with this structure.
 *
 * @param purchase_arguments The pointer at the provided location will be set to
 *                           point to a @c #purchase_arguments_t structure,
 *                           which can be populated via the @c
 *                           paymentservice_purchase_arguments_set functions.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_create(purchase_arguments_t **purchase_arguments);

/**
 * @brief Free the memory that is used by a purchase arguments structure.
 *
 * The @c paymentservice_purchase_arguments_destroy() function frees the memory
 * that is used by the specified @c #purchase_arguments_t structure.
 *
 * @param purchase_arguments The @c #purchase_arguments_t whose memory needs to
 *                           be freed. Note that the pointer to the structure is
 *                           not freed.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_destroy(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the ID of the digital good to purchase.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           digital_good_id.
 * @param digital_good_id The digital good ID to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_digital_good_id(purchase_arguments_t *purchase_arguments,
        const char* digital_good_id);

/**
 * @brief Get the digital good ID from the purchase arguments.
 *
 * Retrieve the digital good ID that was previously set via @c
 * paymentservice_purchase_arguments_set_digital_good_id().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           digital good id.
 *
 * @return The digital good ID, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * paymentservice_purchase_arguments_get_digital_good_id(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the SKU of the digital good to purchase.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           digital_good_sku.
 * @param digital_good_sku The digital good SKU to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_digital_good_sku(purchase_arguments_t *purchase_arguments,
        const char* digital_good_sku);

/**
 * @brief Get the digital good SKU from the purchase arguments.
 *
 * Retrieve the digital good SKU that was previously set via @c
 * paymentservice_purchase_arguments_set_digital_good_sku().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           digital good SKU.
 *
 * @return The digital good SKU, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_digital_good_sku(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the (optional) name of the digital good to purchase.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           digital_good_name.
 * @param digital_good_name The digital good Name to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_digital_good_name(purchase_arguments_t *purchase_arguments,
        const char* digital_good_name);

/**
 * @brief Get the digital good name from the purchase arguments.
 *
 * Retrieve the digital good name that was previously set via @c
 * paymentservice_purchase_arguments_set_digital_good_name().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           digital good name.
 *
 * @return The digital good name, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_digital_good_name(purchase_arguments_t *purchase_arguments);

/**
 * @brief Attach (optional) metadata to the purchase request.
 *
 * See @c paymentservice_purchase_request() for more information on the use of
 * purchase metadata.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           metadata.
 * @param metadata The metadata to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_metadata(purchase_arguments_t *purchase_arguments,
        const char* metadata);

/**
 * @brief Get the metadata from the purchase arguments.
 *
 * Retrieve the metadata that was previously set via @c
 * paymentservice_purchase_arguments_set_metadata().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           metadata.
 *
 * @return The metadata, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * paymentservice_purchase_arguments_get_metadata(purchase_arguments_t *purchase_arguments);

/**
 * @brief Add an extra input parameter, as a key/value pair, to the purchase
 * request.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to add the
 *                           extra parameter.
 * @param key The key of the extra parameter to be set.
 * @param value The value of the extra parameter to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_extra_parameter(purchase_arguments_t *purchase_arguments,
        const char* key, const char* value);

/**
 * @brief Get the value of an extra parameter from the purchase arguments.
 *
 * Retrieve the value of the extra parameter with the provided key, which was
 * previously set via @c paymentservice_purchase_arguments_set_extra_parameter().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           value of the extra parameter.
 * @param key The key of the extra parameter value to be retrieved.
 *
 * @return The value, or NULL if no extra parameter with the provided key has
 *         been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char* paymentservice_purchase_arguments_get_extra_parameter_by_key(purchase_arguments_t *purchase_arguments,
        const char* key);

/**
 * @brief Set the (optional) name of the application through which the digital
 * good is being purchased.
 *
 * If provided, this name will be displayed in a banner along the top of the
 * purchase confirmation screen that shall be presented to the user.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           app_name.
 * @param app_name The application name to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_app_name(purchase_arguments_t *purchase_arguments,
        const char* app_name);

/**
 * @brief Get the application name from the purchase arguments.
 *
 * Retrieve the application name that was previously set via @c
 * paymentservice_purchase_arguments_set_app_name().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           application name.
 *
 * @return The application name, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_app_name(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the (optional) application icon to display.
 *
 * A full URL to an icon to display. If provided, the icon shall be displayed
 * on the purchase confirmation screen that shall be presented to the user.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           app_icon.
 * @param app_icon The application icon URL to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_app_icon(purchase_arguments_t *purchase_arguments,
        const char* app_icon);

/**
 * @brief Get the application icon URL from the purchase arguments.
 *
 * Retrieve the application icon URL that was previously set via @c
 * paymentservice_purchase_arguments_set_app_icon().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           application icon URL.
 *
 * @return The application icon URL, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_app_icon(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the window group ID of the application.
 *
 * This ID is required so that the Payment Service can properly display dialogs.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           group_id.
 * @param group_id The window group ID to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_group_id(purchase_arguments_t *purchase_arguments,
        const char* group_id);

/**
 * @brief Get the window group ID from the purchase arguments.
 *
 * Retrieve the window group ID that was previously set via @c
 * paymentservice_purchase_arguments_set_group_id().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           window group ID.
 *
 * @return The window group ID, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_group_id(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the vendor customer id to be associated with the purchase.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           vendor customer ID.
 * @param vendor_customer_id The vendor customer ID to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_vendor_customer_id(purchase_arguments_t *purchase_arguments,
        const char* vendor_customer_id);

/**
 * @brief Get the vendor customer ID from the purchase arguments.
 *
 * Retrieve the vendor customer ID that was previously set via @c
 * paymentservice_purchase_arguments_set_vendor_customer_id().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           vendor customer ID.
 *
 * @return The vendor customer ID, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_vendor_customer_id(purchase_arguments_t *purchase_arguments);

/**
 * @brief Set the vendor content id to be associated with the purchase.
 *
 * @param purchase_arguments The @c #purchase_arguments_t in which to set the
 *                           vendor content ID.
 * @param vendor_content_id The vendor content ID to be set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_purchase_arguments_set_vendor_content_id(purchase_arguments_t *purchase_arguments,
        const char* vendor_content_id);

/**
 * @brief Get the vendor content ID from the purchase arguments.
 *
 * Retrieve the vendor content ID that was previously set via @c
 * paymentservice_purchase_arguments_set_vendor_content_id().
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           vendor content ID.
 *
 * @return The vendor content ID, or NULL if it has not yet been set.
 *
 * @since BlackBerry 10.0.0
 */
 BPS_API const char * paymentservice_purchase_arguments_get_vendor_content_id(purchase_arguments_t *purchase_arguments);

/**
 * @brief Get the request ID from the purchase.
 *
 * This value will be populated by the Payment System after a @c
 * paymentservice_purchase_request_with_arguments() using the @c
 * #purchase_arguments_t in question. It can be used to correlate the response
 * to the request.
 *
 * @param purchase_arguments The @c #purchase_arguments_t from which to get the
 *                           request ID.
 *
 * @return The purchase request ID, or NULL if the purchase has not yet been
 *         initiated.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned paymentservice_purchase_arguments_get_request_id(purchase_arguments_t *purchase_arguments);

/**
 * @brief Retrieve the response code from a Payment Service event
 *
 * The @c paymentservice_event_get_response_code() function gets the response
 * code from the specified event that is received from the Payment Service.
 *
 * @param event The event to get the response code from.
 *
 * @return @c SUCCESS_RESPONSE to indicate that the request made to the payment
 *         system was successful and @c FAILURE_RESPONSE to indicate that the
 *         request that was made to the payment system failed. Both @c
 *         SUCCESS_RESPONSE and @c FAILURE_RESPONSE indicate that a valid
 *         response code was extracted from the event, however, if @c
 *         BPS_FAILURE is returned, it indicates that there was an error
 *         determining the response code from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_event_get_response_code(bps_event_t *event);

/**
 * Retrieve attributes from a @c PURCHASE_RESPONSE or @c
 * GET_EXISTING_PURCHASES_RESPONSE event in which the response code indicates
 * that the request was successful.
 *
 * Successful @c PURCHASE_RESPONSE and @c GET_EXISTING_PURCHASES_RESPONSE events
 * contain an array of existing purchases. For a @c PURCHASE_RESPONSE event, the
 * array will contain at most one purchase, so the index passed in should always
 * be 0. For a @c GET_EXISTING_PURCHASES_RESPONSE event, retrieve the data for
 * each purchase by first calling the @c
 * paymentservice_event_get_number_purchases() function to determine the number
 * of existing purchases that were retrieved. Then, retrieve the data from each
 * index, where the index ranges from 0 to the number of purchases minus one.
 */

/**
 * @brief Get the number of retrieved purchases from a Payment Service event
 *
 * The @c paymentservice_event_get_number_purchases() function gets the number
 * of purchases that were retrieved from the specified Payment Service event.
 *
 * @param event The event to retrieve the number of purchases from.
 *
 * @return The number of retrieved purchases.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_event_get_number_purchases(bps_event_t *event);

/**
 * @brief Retrieve the request ID from a Payment Service event
 *
 * The @c paymentservice_event_get_request_id() function gets the request ID
 * from the specified Payment Service event.
 *
 * @param event The event to retrieve the request ID from.
 *
 * @return The request ID.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned paymentservice_event_get_request_id(bps_event_t *event);

/**
 * @brief Retrieve the date of a purchase
 *
 * The @c paymentservice_event_get_date() function gets the date of a purchase.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The date that the purchase was made.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_date(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the digital good ID of a purchase
 *
 * The @c paymentservice_event_get_digital_good_id() function gets the digital
 * good ID of a purchase.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The digital good ID of the purchase.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_digital_good_id(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the digital good SKU of a purchase
 *
 * The @c paymentservice_event_get_digital_good_sku() function retrieves the
 * digital good SKU of a purchase.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The digital good SKU of the purchase.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_digital_good_sku(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the digital good license key of a purchase
 *
 * The @c paymentservice_event_get_license_key() function retrieves the digital
 * good license key of a purchase.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The digital good license key of the purchase.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_license_key(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the digital good metadata of a purchase
 *
 * The @c paymentservice_event_get_metadata() function retrieves the digital
 * good metadata of a purchase.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The digital good metadata of the purchase.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_metadata(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the number of extra parameters that are present in a @c
 * PURCHASE_RESPONSE event.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The number of extra parameters that are present in the @c
 *         PURCHASE_RESPONSE.
 *
 * @since BlackBerry 10.0.0
*/
BPS_API int paymentservice_event_get_extra_parameter_count(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the extra parameter key from a @c PURCHASE_RESPONSE at the
 * specified index.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 * @param key_index The index into the list of extra parameters. You can specify
 *                  an index value that ranges from zero to the number of extra
 *                  parameters minus one. You can retrieve the number of extra
 *                  parameters using the @c
 *                  paymentservice_event_get_extra_parameter_count() function.
 *
 * @return The extra parameter key at the specified key_index, or NULL if the
 *         key_index was out of bounds.
 *
 * @since BlackBerry 10.0.0
*/
BPS_API const char* paymentservice_event_get_extra_parameter_key_at_index(bps_event_t *event,
        unsigned int index, unsigned int key_index);

/**
 * @brief Retrieve the extra parameter value from a @c PURCHASE_RESPONSE at the
 * specified index.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 * @param value_index The index into the list of extra parameters. You can specify
 *                    an index value that ranges from zero to the number of extra
 *                    parameters minus one. You can retrieve the number of extra
 *                    parameters using the @c
 *                    paymentservice_event_get_extra_parameter_count() function.
 *
 * @return The extra parameter value at the specified value_index, or NULL if the
 *         value_index was out of bounds.
 *
 * @since BlackBerry 10.0.0
*/
BPS_API const char* paymentservice_event_get_extra_parameter_value_at_index(bps_event_t *event,
        unsigned int index, unsigned int value_index);

/**
 * @brief Retrieve the unique ID of a purchase
 *
 * The @c paymentservice_event_get_purchase_id() function retrieves the unique
 * ID of a purchase. A purchase ID is generated when a user purchases an app 
 * or subscription, or when a subscription renewal takes place. Each purchase 
 * ID has a corresponding transaction ID that represents the transfer of funds
 * for that purchase. The purchase ID for the initial purchase is required in 
 * order to cancel a subscription. You cannot use the purchase ID of a 
 * subscription renewal to cancel a subscription. 
 * See @c paymentservice_cancel_subscription() for more information on 
 * canceling a subscription.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The unique ID of the purchase.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_purchase_id(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the start date of a digital good subscription
 *
 * The @c paymentservice_event_get_start_date() function gets the start date of
 * a digital good subscription.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The start date of the purchased digital good subscription, or a @c
 *         NULL value if the digital good is not a subscription.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_start_date(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the end date of a digital good subscription
 *
 * The @c paymentservice_event_get_end_date() function gets the end date of a
 * digital good subscription.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The end date of the purchased digital good subscription, or a @c NULL
 *         value if the digital good is not a subscription.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_end_date(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the number of days in the initial period of a subscription
 *
 * The @c paymentservice_event_get_purchase_initial_period() function retrieves
 * the number of days in the initial period of a subscription. After the initial
 * period, the user is billed the renewal price.
 *
 * @param event The event containing the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The initial purchase period of the purchased digital good
 *         subscription or a @c NULL value if the digital good is not a
 *         subscription.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_purchase_initial_period(bps_event_t *event, unsigned int index);

/**
 * @brief Retrieve the state of the digital good
 *
 * The @c paymentservice_event_get_item_state() function retrieves the state of
 * the digital good. Possible states of digital goods are defined in the @c
 * #item_state_t enumeration.
 *
 * @param event The event which contains the array of existing purchases.
 * @param index The index into the array of existing purchases. You can specify
 *              an index value that ranges from zero to the number of purchases
 *              minus one. You can retrieve the number of purchases using the @c
 *              paymentservice_event_get_number_purchases() function.
 *
 * @return The state of the digital good.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API item_state_t paymentservice_event_get_item_state(bps_event_t *event, unsigned int index);

/**
 * @brief Deprecated: Retrieve the ID for a transaction 
 *
 * A transaction ID is generated every time there is a transfer of funds. For 
 * example, a transaction ID is generated when a user first purchases an app 
 * or subscription, purchases an avatar or extra level for a game, or when a 
 * subscription renewal takes place. A transaction ID is also generated when 
 * funds are returned. The transaction ID appears on users' purchase receipts 
 * as "Order ID".
 * 
 * @deprecated Use paymentservice_event_get_purchase_id() instead.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_transaction_id(bps_event_t *event, unsigned int index) BPS_DEPRECATED;

/**
 * @brief Retrieve the price attribute from a @c GET_PRICE_RESPONSE event
 *
 * The @c paymentservice_event_get_price() function retrieves the price
 * attribute from the specified @c GET_PRICE_RESPONSE event. The response code
 * of the @c GET_PRICE_RESPONSE event must be @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the price information.
 *
 * @return The price of the digital good.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_price(bps_event_t *event);

/**
 * @brief Retrieve the initial period attribute from a @c GET_PRICE_RESPONSE
 *        event
 *
 * The @c paymentservice_event_get_initial_period() function retrieves the
 * initial period attribute from the specified @c GET_PRICE_RESPONSE event. The
 * response code of the @c GET_PRICE_RESPONSE event must be @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the price information.
 *
 * @return The initial period of the digital good subscription.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_initial_period(bps_event_t *event);

/**
 * @brief Retrieve the renewal price attribute from a @c GET_PRICE_RESPONSE
 *        event
 *
 * The @c paymentservice_event_get_renewal_price() function retrieves the
 * renewal price attribute from the specified @c GET_PRICE_RESPONSE event. The
 * response code of the @c GET_PRICE_RESPONSE event must be @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the price information.
 *
 * @return The renewal price of the digital good subscription.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_renewal_price(bps_event_t *event);

/**
 * @brief Retrieve the renewal period attribute from a @c GET_PRICE_RESPONSE
 *        event
 *
 * The @c paymentservice_event_get_renewal_period() function retrieves the
 * renewal period attribute from the specified @c GET_PRICE_RESPONSE event. The
 * response code of the @c GET_PRICE_RESPONSE event @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the price information.
 *
 * @return The renewal period of the digital good subscription.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_renewal_period(bps_event_t *event);

/**
 * @brief Retrieve the attribute that indicates whether a subscription exists
 *        from a @c CHECK_EXISTING_RESPONSE event
 *
 * The @c paymentservice_event_get_subscription_exists() function retrieves the
 * attribute that indicates whether a subscription exists from the specified @c
 * CHECK_EXISTING_RESPONSE event. The response code of the @c
 * CHECK_EXISTING_RESPONSE event must be @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the subscription information.
 *
 * @return @c true if the digital good subscription exists, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool paymentservice_event_get_subscription_exists(bps_event_t *event);

/**
 * @brief Retrieve the purchase ID of a request to cancel a subscription
 *
 * The @c paymentservice_event_get_cancelled_purchase_id() function retrieves
 * the purchase ID of a request to cancel a subscription to a digital good from
 * the specified @c CANCEL_SUBSCRIPTION_RESPONSE event. The response code of the
 * @c CANCEL_SUBSCRIPTION_RESPONSE event must be @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the purchase cancellation response.
 *
 * @return The purchase ID that was sent in the cancellation request.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_cancelled_purchase_id(bps_event_t *event);

/**
 * @brief Retrieve the result of a request to cancel a subscription
 *
 * The @c paymentservice_event_get_cancelled() function retrieves the result of
 * a request to cancel a subscription to a digital good from the specified @c
 * CANCEL_SUBSCRIPTION_RESPONSE event. The response code of the @c
 * CANCEL_SUBSCRIPTION_RESPONSE event must be @c SUCCESS_RESPONSE.
 *
 * @param event The event containing the purchase cancellation response.
 *
 * @return @c true if the purchase was cancelled, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool paymentservice_event_get_cancelled(bps_event_t *event);

/**
 * @brief Retrieve the error ID from an event
 *
 * The @c paymentservice_event_get_error_id() function retrieves the error ID
 * from the specified event. The response code of the event must be @c
 * FAILURE_RESPONSE.
 *
 * @param event The event to retrieve the error ID from.
 *
 * @return The error ID or @c BPS_FAILURE if no error. See @c
 * #paymentservice_error_t for possible values.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int paymentservice_event_get_error_id(bps_event_t *event);

/**
 * @brief Retrieve additional information about the error
 *
 * The @c paymentservice_event_get_error_info() function gets the error info
 * from the specified event. The response code of the event must be @c
 * FAILURE_RESPONSE.
 * This information may be used to diagnose the cause of payment service
 * failures.
 *
 * @param event The event to retrieve the error info from.
 *
 * @return the error information text or @c NULL if no error information.
 *
 * @since 10.2.0
 */
BPS_API const char* paymentservice_event_get_error_info(bps_event_t *event);

/**
 * @brief Retrieve the error text from an event
 *
 * The @c paymentservice_event_get_error_text() function gets the error text
 * from the specified event. The response code of the event must be @c
 * FAILURE_RESPONSE.
 *
 * @param event The event to retrieve the error text from.
 *
 * @return The error text.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* paymentservice_event_get_error_text(bps_event_t *event);

__END_DECLS

#endif
