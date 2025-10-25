/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file ids_blackberry_id.h
 *
 * @brief Use BlackBerry ID as an identity provider for your application
 *
 * @page  BBID_Provider BlackBerry ID as an identity provider
 *
 * Using the BlackBerry ID service as an identity provider, you can enhance
 * your app in several ways:
 * - Provide user authentication within your app, without prompting for
 * user credentials.
 * - Provide user authorization to access other BlackBerry apps and off-device
 * services without prompting for user credentials.
 * - Provide access to users' personal information that is stored in the
 * BlackBerry ID account system. User permission to access this information
 * is required.
 *
 * @section   user_auth_sec   User authentication without prompting for credentials
 *
 * Benefits of implementing BlackBerry ID user authentication:
 * - Eliminate the need to build your own username and password management.
 * - Automatically sign users in to your app after they sign in with their
 * BlackBerry ID account on their devices. This makes your app easier to use.
 * - Eliminate the need for users to create and remember a username and
 * password for your app.
 *
 * @section   off_device_service_sec   User authorization to access other BlackBerry apps and off-device services
 *
 * If your app interacts with an off-device service that requires user
 * authentication (for example, a website that requires the user to sign in
 * with a username and password), you can use BlackBerry ID APIs to perform
 * the off-device authentication/authorization using tokens, instead of
 * prompting the user for credentials. Your app and the off-device service
 * interact seamlessly.
 *
 *
 * @section pii_sec   Access personal information associated with BlackBerry ID accounts
 *
 * You can personalize the user experience of your app by incorporating your
 * users' personal information in your app. Users must allow your app to
 * access the information associated with their BlackBerry ID accounts before
 * you can access it. The application must have the
 * @c read_personally_identifiable_information permission included in their bar
 * descriptor. The information that is available includes:
 * - first name
 * - last name
 * - screen name
 * - username (an email address)
 *
 * The @c ids_get_properties() function can be used to retrieve personal
 * information stored in the BlackBerry ID account system, with
 * @c BBID_PROPERTY_CORE passed as the @c type parameter
 * (see code samples below).
 *
 * @section Code_sample_sec  Sample code for using BlackBerry ID as the identity provider for your app
 *
 * In order to use BlackBerry ID as the identity provider for your app,
 * you need to use the IDS APIs defined in the ids.h library.
 *
 * Setting up your app to use BlackBerry ID as an identity provider:
 * - Step 1 - Initialize the IDS library for use by your app. You only need to
 * do this once.
 * - Step 2 - Register with the Identity Service to use BlackBerry ID as an
 * identity provider.
 * - Step 3 - Add a file descriptor (FD) handler to handle communication with
 * the IDS library.
 *
 * Once these steps have completed successfully, the app can use the IDS APIs
 * to store and retrieve data off the device, retrieve the user's personal
 * information associated with their BlackBerry ID account, and use tokens for
 * authentication and authorization.
 *
 * This code sample shows how to initialize the IDS library:
 *
 * @code
 *
 * // Make sure to include the following header files in your application
 * #include <errno.h>
 * #include <bps/bps.h>
 * #include <ids.h>
 * #include <ids_blackberry_id.h>
 *
 * // Step 1 - Initialize IDS.
 *
 * ids_result_t result = ids_initialize();
 * if( result != IDS_SUCCESS ) {
 *     displayText( "Failure to initialize. errno: %d", errno );
 *     return;
 * }
 *
 * // Step 2 - Register to use BlackBerry ID as an identity provider.
 *
 * static ids_provider_t* ids_provider;
 * static int ids_fd = -1;
 *
 * result = ids_register_provider( BLACKBERRY_ID_PROVIDER, &ids_provider, &ids_fd );
 *
 * if( result != IDS_SUCCESS ) {
 *     displayText( "Failure to register. errno: %d", errno );
 *     return;
 * }
 *
 * // Step 3 - Add an FD handler for the IDS library communications.
 *
 * if( bps_add_fd( ids_fd, BPS_IO_INPUT, &ids_io_handler, NULL ) != BPS_SUCCESS ) {
 *     displayText( "Failure to monitor fd. errno: %d", errno );
 *     return;
 * }
 *
 * @endcode
 *
 * After these three steps are complete and return successfully, your
 * app is ready to use the IDS APIs to access functionality for BlackBerry ID
 * as an identity provider.
 *
 * Here's a code sample for how to access a user's email address, stored in
 * the "username" field.
 *
 * @code
 * const char* properties[] = { IDS_BBID_PROP_USERNAME };
 * // Other valid values include IDS_BBID_PROP_SCREENNAME,
 * IDS_BBID_PROP_FIRSTNAME, IDS_BBID_PROP_LASTNAME, IDS_BBID_PROP_UID
 *
 * result = ids_get_properties( ids_provider, BBID_PROPERTY_CORE, 1, properties, handle_properties, ids_call_failed, "get properties", &request_id );
 * if( result != IDS_SUCCESS ) {
 *     displayText( "Failure to getProperty. errno: %d", errno );
 *     return;
 * }
 * @endcode
 *
 */


#ifndef IDS_BLACKBERRY_ID_H_
#define IDS_BLACKBERRY_ID_H_

/**
 * @brief The identity provider name for BlackBerry ID
 * @sa ids_register_provider()
 */
#define BLACKBERRY_ID_PROVIDER "ids:rim:bbid"

/**
 * @brief The property types for BlackBerry ID
 * @details These are the core properties that are available to applications
 * using BlackBerry ID as an identity provider. See @c ids_get_properties()
 * with the @c BBID_PROPERTY_CORE type.
 */
typedef enum bbid_property_type {
    BBID_PROPERTY_CORE = 0       /*!< BlackBerry ID core property type. */
} bbid_property_type_t;

/** BlackBerry ID core property - Username */
#define IDS_BBID_PROP_USERNAME   "urn:bbid:username"

/** BlackBerry ID core property - Screen name */
#define IDS_BBID_PROP_SCREENNAME "urn:bbid:screenname"

/** BlackBerry ID core property - First name */
#define IDS_BBID_PROP_FIRSTNAME  "urn:bbid:firstname"

/** BlackBerry ID core property - Last name */
#define IDS_BBID_PROP_LASTNAME   "urn:bbid:lastname"

/** BlackBerry ID core property - Unique ID */
#define IDS_BBID_PROP_UID        "urn:bbid:uid"

/** BlackBerry ID core property - Validated Email */
#define IDS_BBID_PROP_EMAIL      "urn:bbid:email"

/**
 * @brief Levels of assurance returned with a BlackBerry ID challenge
 * @details These are the levels of assurance returned by the challenge API
 * using BlackBerry ID as an identity provider. See @c ids_challenge().
 *
 */
enum bbid_level_assurance {
    /**
     * @brief  BlackBerry ID level of assurance when authentication was
     * performed offline
     */
    IDS_BBID_LEVEL_AUTH_OFFLINE = 0,
    /**
     * @brief BlackBerry ID level of assurance when authentication was
     * performed online
     */
    IDS_BBID_LEVEL_AUTH_ONLINE
};

/**
 * @brief The types for challenge requests for BlackBerry ID.
 * @details These are the types of challenges that are available to applications
 * using BlackBerry ID as an identity provider. See @c ids_challenge().  In
 * cases where the screen was not able to be opened OR the user chooses not to
 * complete the challenge and cancels, the API will return the error
 * @c IDS_USER_COULD_NOT_BE_AUTHENTICATED indicating that challenge was not
 * successful.
 */
enum bbid_challenge_type {
    /**
     * @brief Authentication challenge type.
     * @details Prompts the user to authenticate with their current password.
     * An application that is challenging with this type is attempting to
     * explicitly interact with the user and a screen will attempted to be
     * opened for the user regardless if the application has previously set
     * @c IDS_OPT_GUI_ALLOWED with @c ids_set_option to false.
     */
    BBID_AUTHENTICATE = 0,
    /**
     * @brief Email confirmation challenge type.
     * @details Prompts the user to confirm their email.
     * An application that is challenging with this type is attempting to
     * explicitly interact with the user and a screen will attempted to be
     * opened for the user regardless if the application has previously set
     * @c IDS_OPT_GUI_ALLOWED with @c ids_set_option to false.  If the current
     * email address is already confirmed, no screen will be displayed and the
     * API will return with IDS_SUCCESS.
     */
    BBID_EMAIL_CONFIRMATION

};

/**
 * @brief The flags for challenge requests for BlackBerry ID.
 * @details These are the flags for the challenges request that are available
 * to applications using BlackBerry ID as an identity provider. See
 * @c ids_challenge().
 */
enum bbid_challenge_flags {
    /**
     * @brief Default challenge flag.
     * @details No options specified, and the challenge will follow the default
     * behavior.
     */
    BBID_CHALLENGE_DEFAULT = 0
};


/**
 * @brief The flags for registering/deregistering change notifications of
 * entries within the profile
 * @details Notifications can be registered for changes to BlackBerry ID
 * property values.  Upon notifications, your app can call the function
 * @c ids_get_properties() to get the new value. Multiple flags can be combined
 * using bitwise 'OR' unless stated otherwise. See the @c flags parameter for
 * the @c ids_register_notifier() function for more information.
 */
enum ids_bbid_register_notifier_flag {
    /**
     * @brief Request to start receiving notifications
     */
    IDS_BBID_NOTIFIER_START = 0x00000000,
    /**
     * @brief Request to stop receiving notifications
     */
    IDS_BBID_NOTIFIER_STOP  = 0x00000001
};

/**
 * @brief The kinds of notifications that can be generated by this provider
 */
enum ids_bbid_notification {
    /**
     * @brief Notifications will now be sent for this entry
     * @details The request to receive notifications was successful. Change
     * notifications will now be sent.
     */
    IDS_BBID_NOTIFY_STARTED = 0x00000000,
    /**
     * @brief Notifications will no longer be sent for this entry
     * @details The request to stop receiving notifications was successful, or
     * the request to start receiving has failed. Change notifications will
     * NOT be sent.
     */
    IDS_BBID_NOTIFY_STOPPED = 0x00000001,
    /**
     * @brief The entry has changed
     * @details The provider has detected that the entry has changed and is
     * notifying the application. A change can include the entry being created,
     * deleted, or modified.
     */
    IDS_BBID_NOTIFY_CHANGED = 0x00000002
};


#endif /* IDS_BLACKBERRY_ID_H_ */
