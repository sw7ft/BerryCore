/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file ids.h
 *
 * @brief Use the Identity Service library to incorporate user authentication
 * and authorization, using one or more external identity providers, in your
 * app
 *
 * @mainpage Identity Service library
 *
 * You can use the APIs in the Identity Service library to enable your users 
 * to access off-device services and content that require user authentication 
 * or authorization. Content and services include data storage and retrieval, 
 * and access to services with an external identity provider. You can also 
 * personalize the user experience by integrating users' personal information 
 * in your app. 
 *
 * The Identity Service works with identity providers to provide user 
 * authentication, so in order to use the Identity Service, you need to 
 * register your app with at least one identity provider. Ideally, your app's 
 * users will already have an account with the identity provider that you 
 * choose to register with.
 *
 * Your users can sign in with their identity provider, using their BlackBerry
 * device, and access content or services that they have with that identity 
 * provider from within your app and elsewhere on their device.
 * 
 * Any authorization that your app requires can also be done using the login
 * credentials associated with an identity provider. This approach frees your 
 * users from having to remember another login profile, and saves you from 
 * having to build user authentication into your app.
 * 
 * For example, if you registered your app with BlackBerry ID as your identity 
 * provider, your users could access BlackBerry ID controlled resources from 
 * within your app, without having to log in again. BlackBerry ID is one of 
 * the supported identity providers, and the list of available identity 
 * providers is growing.
 *  
 * Identity providers can offer different features and levels of access. It's 
 * important to understand the features that are available from your 
 * identity provider because those features impact how you design your 
 * app. For example, one identity provider might provide off-device data 
 * storage while another might provide on-device data storage. Similarly, the 
 * personal information that you can retrieve with the @c ids_get_properties() 
 * function can differ based on the information that each identity provider 
 * stores in their account system.
 * 
 * You'll need to use this documentation in conjunction with information from 
 * your identity provider about how they have implemented the Identity Service 
 * APIs on their end. If you are using BlackBerry ID as the identity provider 
 * for your app, you can find information specific to integrating with 
 * BlackBerry ID in ids_blackberry_id.h.
 * 
 * 
 * @section  DataStorage_section  Data storage and retrieval APIs
 * 
 * You can use the APIs in the Identity Service library (IDS) to: 
 * - store data initially (ids_create_data())
 * - retrieve data (ids_get_data())
 * - update data (ids_set_data())
 * - remove data (ids_delete_data())
 * - list stored data (ids_list_data())
 * 
 * @section   UserAuth_Section   User authentication without prompting for credentials
 * 
 * With the user authentication APIs in this library, you can avoid 
 * implementing username and password management in your app. After your user 
 * signs in with the identity provider on their device, that user is 
 * automatically signed in to your app as well. This eliminates the need for 
 * users to create and remember a username and password for your app, and it 
 * also reduces the number of times that users need to log in, providing a 
 * more fluid user experience.
 * 
 * @section   OffDeviceAuth_Section   User authorization for access to off-device services
 * 
 * If your app interacts with one of your identity provider's apps or 
 * off-device services, and that app or service requires user authentication,  
 * you can use the Identity Service APIs to perform that authentication. 
 * User authentication/authorization is done using tokens, and does not 
 * require user input. This allows your app and the off-device service to 
 * interact seamlessly.
 *  
 * @section PII_Section   Using personal information in your app
 * 
 * Users must first allow your app to access their information. If allowed 
 * access, you can integrate the personal information associated with your 
 * users' accounts in your app. The personal information that is available to 
 * your app depends on what information is available from your identity 
 * provider's account system.
 * 
 * For example, if your app uses BlackBerry ID as an identity provider, your 
 * app can access the following pieces of a user's personal information:
 * - first name
 * - last name
 * - screen name
 * - username
 * 
 * Check with other identity providers to identify the personal information 
 * that they make available.
 * 
 * 
 * @section ids_callback_sec Callback functions
 * 
 * Many of the IDS APIs have the following three parameters:
 * - Success callback function
 * - Failure callback function
 * - Callback data (@c cb_data)
 * 
 * When your app sends API calls using the IDS APIs, the Identity Service 
 * responds asynchronously. When your app receives a response, the 
 * corresponding callback function that your app provided for the success 
 * or failure case is executed.
 * 
 * The Identity Service uses callback functions to pass the parsed response
 * back to your app. Callback functions cannot be NULL. Your app must specify 
 * what to do in both the success and failure scenarios.
 * 
 * Your app sends callback data (@c cb_data) to the callback functions. The
 * Identity Service does not process the @c cb_data in any way. The
 * @c cb_data parameter is merely passed into the API from your app, and is 
 * passed along to the callback function. If your app doesn't need to pass 
 * information to the callback functions, you can set the @c cb_data parameter 
 * to @c NULL.
 * 
 * 
 * @section bbid_modes_sec Registering your app to use the IDS APIs
 * 
 * To register your app so that it can use the IDS APIs, call
 * @c ids_register_provider() from your app for at least one identity provider.
 * Your app must then monitor the returned file descriptor for changes, using 
 * any of ionotify, poll, select, BPS, etc. When your app detects a change to 
 * the file descriptor, it must execute @c ids_process_msg(), which processes
 * the data in the file descriptor.
 * 
 * After your app sends a request, the Identity Service processes the
 * request asynchronously, and writes the response to a file descriptor (@c fd).
 * The file descriptor contains the result of the @c ids_get_properties() call,
 * and either the success or failure callback is executed accordingly, all in 
 * the same thread that the app is currently running in.
 * 
 * For example, your app can call @c ids_get_properties() and pass a success
 * callback of @c my_app_success_callback and a failure callback of
 * @c my_app_failure_callback. When your app detects a change to the file
 * descriptor, it would call @c ids_process_msg(), which parses the information
 * in the file descriptor. The file descriptor contains the result of the
 * @c ids_get_properties() call, and either the success or failure callback 
 * would be invoked accordingly, all in the same thread that the app is 
 * currently running in.
 */




#ifndef _IDS_IDS_H_INCLUDED
#define _IDS_IDS_H_INCLUDED

#include <sys/platform.h>
#include <stdbool.h>

/**
 * @brief This identifier is used to make the IDS functions visible for public use
 */
#ifndef IDS_API
#define IDS_API __attribute__((visibility("default")))
#endif

/**
 * @brief This identifier is used to indicate that the IDS API has been deprecated.
 */
#ifndef IDS_DEPRECATED
#define IDS_DEPRECATED  __attribute__((__deprecated__))
#endif

__BEGIN_DECLS

/**
 * @brief The version of the IDS library
 *
 * @details The version number is constructed by adding the major version 
 * number, minor version number, and patch number, as follows:
 * (Major * 1000000) + (Minor * 1000) + Patch (0)
 */
#define IDS_VERSION             ( 1001000 )

/**
 * @brief The version of the IDS library as a string
 *
 * @details The version is constructed by separating the major version, minor
 * version, and patch with decimal points, for example: 
 * 1.1.0
 *
 */
#define IDS_VERSION_STRING      "1.1.0"

/**
 * @brief Unique identifier for a request to an application to easily correlate
 * the request with the response
 *
 * @details The IDS API passes the ID of a request to the response
 * callback for that request. This allows your application to associate the
 * correct response with each request, and is especially useful in cases where
 * responses are returned in an order that is different from the order that
 * requests were made. It is also useful if requests and responses are sent
 * over different threads in multi-threaded applications.
*/
typedef unsigned int ids_request_id_t;

/**
 * @brief IDS result codes returned to the application
 *
 * @details Each result code is applicable to some, but not 
 * all, of the IDS APIs. Please refer to the documentation for each API to 
 * determine which errors are applicable to that specific API, and how they 
 * can be interpreted for that specific API.
 *
 */
typedef enum {
    IDS_FAILURE = -1,    /*!< The IDS API call did not complete successfully; 
                              check the value of @c errno for additional 
                              information. */

    IDS_SUCCESS = 0,     /*!< The IDS API call completed 
                              successfully. In asynchronous calls, the request 
                              has been sent and either the success or failure 
                              callback is called when the response arrives. */

    IDS_DEFAULT_ERROR = 49999, /*!< Error code 49999 is the default error code, 
                                    and indicates that an internal error 
                                    occurred while processing the request. */

    IDS_NAME_TOO_LONG = 50002, /*!< The name provided is too long. The maximum
                                    number of allowed characters is determined
                                    by the identity provider. */

    IDS_ACCOUNT_LOCALLY_LOCKED_OUT = 50003, /*!< User authentication could not 
                                                 complete because the user 
                                                 account is locked out. */

    IDS_USER_COULD_NOT_BE_AUTHENTICATED = 50004, /*!< The identity provider 
                                                      could not authenticate
                                                      the user. There are a 
                                                      variety of possible 
                                                      causes for this error, 
                                                      including technical 
                                                      reasons, the user 
                                                      canceled the 
                                                      authentication request, 
                                                      and failure to meet other
                                                      conditions that the 
                                                      identity provider 
                                                      requires. */

    IDS_TOO_MANY_NAMES_PASSED = 50005, /*!< The number of entries provided 
                                            exceeds what the identity provider 
                                            can handle. */

    IDS_INVALID_REQUEST = 50006, /*!< The request is malformed or not 
                                      supported. */

    IDS_DOES_NOT_EXIST = 50007, /*!< The requested item does not exist. */

    IDS_UNKNOWN_TOKEN_TYPE = 50008, /*!< This error may be returned with the 
                                         ids_get_token() function, and 
                                         indicates that the identity provider 
                                         is unable to determine, or does not 
                                         support, the type of token that was 
                                         requested. This error is specific to 
                                         the identity provider. */
    
    IDS_UNKNOWN_APPLIES_TO = 50009, /*!< This error may be returned with the 
                                         ids_get_token() function, and 
                                         indicates that the identity provider 
                                         is unable to determine the application
                                         or service that the token applies to. 
                                         This error is specific to the identity
                                         provider. */

    IDS_NOT_ENOUGH_RESOURCES = 50010, /*!< This is a general error that could 
                                           refer to a variety of causes. For 
                                           example, the queue might be full 
                                           and unable to process the request, 
                                           there's insufficient memory to 
                                           process the request, or other 
                                           conditions established by the 
                                           identity provider are preventing 
                                           the request from completing 
                                           successfully. */

    IDS_CANNOT_GET_TOKEN_WHILE_OFFLINE = 50011, /*!< This error is returned 
                                                     with the ids_get_token() 
                                                     function, and indicates 
                                                     that a token could not be 
                                                     obtained because the 
                                                     identity provider's user 
                                                     authentication service is
                                                     offline. */

    IDS_ERROR_WHILE_CONTACTING_SERVICE = 50012, /*!< An error occurred while 
                                                     contacting the identity 
                                                     service, which could 
                                                     include network issues. */

    IDS_NULL_OR_UNKNOWN_PARAMETERS = 50015, /*!< This is a general error that
                                                 indicates that the parameters 
                                                 provided are not valid.  */

    IDS_NOT_ALLOWED = 50017, /*!< This error is specific to the identity 
                                  provider, and is returned if their security 
                                  model does not allow the request by the 
                                  application. */

    IDS_VALUE_TOO_LARGE = 50107, /*!< This error is specific to the identity 
                                      provider, and is returned if the value
                                      exceeds the size that the identity 
                                      provider allows. */

    IDS_ALREADY_EXISTS = 50159, /*!< The requested item cannot be created 
                                     because it already exists. */

    IDS_NOT_READY = 50207, /*!< The request could not be completed because the
                                provider is not ready to process the request.*/

    IDS_QUOTA_EXCEEDED = 50018,  /*!< This error is specific to the identity
                                      provider, and is returned if the quota
                                      has been exceeded as set by the
                                      identity provider.*/

    // Deprecated Return Codes, no longer used.

    IDS_PROPERTY_DOES_NOT_EXIST = 50007, /*!< Deprecated, use 
                                              @c IDS_DOES_NOT_EXIST. */

    IDS_PROPERTY_NOT_AUTHORIZED = 50017, /*!< Deprecated, use 
                                              @c IDS_NOT_ALLOWED. */
    
    IDS_CLEAR_TOKEN_FAIL = 50016, /*!< Deprecated, use
                                       @c IDS_DEFAULT_ERROR. */

    IDS_NAME_MUST_BE_SET = 50107 /*!< Deprecated, use
                                      @c IDS_NULL_OR_UNKNOWN_PARAMETERS. */
} ids_result_t;

/**
 * @brief An opaque handle that the IDS library uses to maintain information 
 * related to a specific identity provider
 * @details The application uses this handle with each API to ensure that
 * requests are made to the appropriate identity provider, such as 
 * BlackBerry ID.
 */
typedef struct ids_provider_t ids_provider_t;

/**
 * @brief Additional information for token parameters
 * @details Information about token parameters, including the name 
 * and value of the token.
 */
typedef struct ids_token_param_s {
    const char* name;  /*!< The name of the parameter. */
    const char* value; /*!< The value of the parameter. */
} ids_token_param_t;

/**
 * @brief The property value associated with an identity
 * @details Properties for an identity, including name and value.
 */
typedef struct ids_property_s {
    const char* name;  /*!< The name of the property. */
    const char* value; /*!< The value of the property. */
} ids_property_t;

/**
 * @brief A generic data container for use with identity providers' 
 * data storage
 * @details This struct is a generic data container for use with 
 * identity providers' data storage.
 */
typedef struct ids_data_s {
    const char* name; /*!< The name of the data. */
    void* value;      /*!< The actual data. */
    int length;       /*!< The length in bytes of data pointed to by @c value. */
} ids_data_t;

/**
 * @brief The success callback function for @c ids_get_token()
 * @details The success callback function for @c ids_get_token().
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param token A pointer to the string representation of the requested token.
 * @param param_count The number of additional token parameters returned.
 * @param params A pointer to the list of additional token parameters.
 * @param cb_data The @c cb_data pointer passed in during the request.
 */
typedef void (*get_token_cb_t)( ids_request_id_t request_id,
                                const char* token,
                                int param_count,
                                const ids_token_param_t* params,
                                void* cb_data );

/**
 * @brief The success callback function for @c ids_clear_token()
 * @details The success callback function for @c ids_clear_token().
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param clear Indicates whether or not the token was actually cleared.
 * @param cb_data The @c cb_data pointer passed in during the request.
 */
typedef void (*clear_token_cb_t)( ids_request_id_t request_id,
                                  bool clear,
                                  void* cb_data );

/**
 * @brief The success callback function for @c ids_get_properties()
 * @details The success callback function for @c ids_get_properties().
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param property_count The number of properties returned.
 * @param params A pointer to the list of returned properties.
 * @param cb_data The @c cb_data pointer passed during the request.
 */
typedef void (*get_properties_cb_t)( ids_request_id_t request_id,
                                     int property_count,
                                     const ids_property_t* properties,
                                     void* cb_data );

/**
 * @brief The success callback function for @c ids_get_data()
 * @details The success callback function for @c ids_get_data().
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param data A pointer to the data retrieved.
 * @param cb_data The @c cb_data pointer passed during the request.
 */
typedef void (*get_data_cb_t)( ids_request_id_t request_id,
                               const ids_data_t* data,
                               void* cb_data );

/**
 * @brief The success callback function for @c ids_list_data()
 * @details The success callback function for @c ids_list_data().
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param list_count The number of items in the list pointed to by @c list.
 * @param list A pointer to the list of string items.
 * @param cb_data The @c cb_data pointer passed during the request.
 */
typedef void (*list_cb_t)( ids_request_id_t request_id,
                           int list_count,
                           const char** list,
                           void* cb_data );

/**
 * @brief The success callback function for @c ids_challenge()
 * @details The success callback function for @c ids_challenge()
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param level Indicates the level of assurance of the successful challenge
 * completed. See the specific identity provider's documentation for 
 * additional information on the values that can be returned.
 * @param cb_data The @c cb_data pointer passed in during the request.
 */
typedef void (*challenge_cb_t)( ids_request_id_t request_id,
                                int level,
                                void* cb_data );

/**
 * @brief The success callback function for requests that do not have data to
 * return to the calling application
 *
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param cb_data The @c cb_data pointer passed during the request.
 *
 * @details This represents the successful completion of the request by the
 * identity provider.
 */
typedef void (*success_cb_t)( ids_request_id_t request_id,
                              void* cb_data );

/**
 * @brief The function that is executed to notify that a change was detected 
 * for the given entry
 *
 * @param type The type of entry, and is the same as the value used when 
 * registering the notifier.
 * @param notification Indicates the kind of change that occurred; see
 * your identity provider's documentation for the values it returns.
 * @param name The name of the entry, which is the same as the value that was 
 * used when registering the notifier.
 * @param cb_data The @c cb_data pointer that was passed in during the 
 * registration.
 */
typedef void (*notify_cb_t)( int type,
                             const char* name,
                             int notification,
                             void* cb_data );

/**
 * @brief The failure callback function
 *
 * @param request_id The request id that matches the one returned during the
 * request.
 * @param result The failure result code of the request.
 * @param info Information about the failure that is specific to the identity 
 * provider. It's possible that some identity providers have not populated 
 * this information. See your specific identity provider for information on 
 * the contents of this field.
 * @param cb_data The @c cb_data pointer passed during the request.
 *
 * @details Each function has a number of listed 
 * result codes that can occur while processing the request, but it is a good 
 * practice to implement this callback to handle additional/new results. 
 * Implementing the failure callback can provide a generic check for failure, 
 * and help maintain future compatibility.
 */
typedef void (*failure_cb_t)( ids_request_id_t request_id,
                              ids_result_t result,
                              const char* info,
                              void* cb_data );

/**
 * @brief Retrieve the version of the IDS APIs
 *
 * @return The version of the IDS library using the scheme
 * described for @c IDS_VERSION.
 *
 * @details Retrieves the version of the IDS APIs that your
 * application is using.
 */
IDS_API int ids_get_version( void );

/**
 * @brief Initialize the library
 *
 * @return @c IDS_SUCCESS when the function completes successfully, or 
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details Initializes the library for use by the current 
 * application, and is called once at the start of the calling process.
 *
 * @b Errors
 * The value of @c errno can be one of the following:
 * - @c EBUSY: Library has already been initialized.
 */ 
IDS_API ids_result_t ids_initialize( void );

/**
 * @brief Free up library resources for the application
 * @details Called once at shutdown of the calling process to release resources
 * held by the library.
 */
IDS_API void ids_shutdown( void );

/**
 * @brief Register your application with an identity provider
 *
 * @param name The name of the identity provider that your app will use to
 * retrieve user identity information.
 * @param provider The updated identity provider if the function completes 
 * successfully, or @c errno set to @c EEXIST if it fails.
 * @param fd If the function completes successfully, or fails with @c errno set
 * to @c EEXIST, this parameter is populated with a file descriptor (@c fd) that
 * the library can use to communicate with the identity provider. Your 
 * application must listen to this @c fd for input and call @c ids_process_msg to 
 * handle any input provided. The @c fd may be the same as a @c fd from a previously 
 * added identity provider. Your application must handle unique and repeated 
 * @c fd values when adding them to its monitoring mechanism, and your 
 * application should monitor the @c fd for input and exceptions. 
 *
 * @return @c IDS_SUCCESS if the identity provider was successfully added for the
 * application, or @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details You can use this function to register your application for each
 * identity provider (such as BlackBerry ID) that your application might use.
 *
 * @b Errors
 * The value of @c errno can be one of the following:
 * - @c EFAULT: The library has not been initialized.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EEXIST: The identity provider has already been registered.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: The system has insufficient memory to complete the operation.
 */
IDS_API ids_result_t ids_register_provider( const char* name,
                                            ids_provider_t** provider,
                                            int* fd );


/**
 * @brief Handle input from a file descriptor (@c fd)
 *
 * @param fd The @c fd that has changed.
 *
 * @return @c IDS_SUCCESS if the change was successfully processed. In cases 
 * where there are errors, this returns @c IDS_FAILURE with the @c errno 
 * value set, indicating to your app that the @c fd is no longer usable.
 * You should re-add any identity providers that were using that @c fd to your 
 * app. The @c fd should no longer be monitored by your app.
 *
 * @details This function handles input from a file descriptor (@c fd) obtained 
 * from the @c ids_add_provider that your app is monitoring. Your app needs to
 * call this function whenever it detects that input is available on any 
 * @c fd returned from the @c ids_register_provider() function.
 * 
 * @b Errors
 * The value of @c errno can be one of the following:
 * - @c ENOMEM: Not enough memory available to process the message.
 * - @c EFAULT: The library has not been initialized.
 * - @c EIO: Problem communicating with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 */
IDS_API ids_result_t ids_process_msg( int fd );


//*****************************************************************************
// User Identity Functions
//*****************************************************************************

/**
 * @section bbid_loglevels_sec Logging levels for the library
 * Logging levels are used to specify the logging verbosity of the library.
 * @sa ids_set_option() with the @c IDS_OPT_VERBOSITY option.
 */

/**
 * With the logging verbosity set to "silent", logs will not be generated. 
 */
#define IDS_LOG_NONE    "Silent" 

/**
 * "Normal" is the default verbosity, which generates errors and warnings.
 */
#define IDS_LOG_NORMAL  "Normal" 

/**
 * The "verbose" logging level includes the "normal" level plus info logging 
 * to help debug application integration. 
 */
#define IDS_LOG_VERBOSE "Verbose" 


/**
 * @brief Configurable options
 * @details These options can be set using the @c ids_set_option() function.
 */
typedef enum {
    /**
     * @brief Set the GUI allowed flag
     *
     * @details The GUI allowed flag can have a value of "true" or "false". By 
     * default, in cases where user input is required, the identity provider 
     * performs the user interaction on behalf of the calling application. If 
     * the GUI allowed flag is set to false, and user input is required, the 
     * API returns an error. If user interaction is not required to complete 
     * the API, this setting has no effect. Not all identity providers 
     * require/support this option.
     */
    IDS_OPT_GUI_ALLOWED = 0,
    /**
     * @brief Set the group ID of the calling application for dialog boxes
     *
     * @details The group ID accepts a string version of UI group id. This is 
     * required in cases where the identity provider requires user input and 
     * must open an interface in the context of the calling application. Not 
     * all identity providers require/support this option.
     */
    IDS_OPT_GROUP_ID,
    /**
     * @brief Set the verbosity level of library logging
     * @details Increasing the logging level during application development
     * can be useful for diagnosing errors. Note that logs are generated
     * on stderr, and so should be captured in the application's log file.
     */
    IDS_OPT_VERBOSITY
} ids_option_t;

/**
 * @brief Modify default behavior
 *
 * @param option The option to be modified.
 * @param value A pointer to the new string value to set.
 * @return @c IDS_SUCCESS when the request is issued successfully, or 
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details This function allows an application to modify the default behavior
 * of the APIs as well as configure how the library and application are
 * integrated. See @c ids_option_t for information on the options that you
 * can modify.
 *
 * @b Errors
 * The value of @c errno can be one of the following:
 * - @c EFAULT: The library has not been initialized.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to store the setting.
 */
IDS_API ids_result_t ids_set_option( ids_option_t option,
                                     const char* value );

/**
 * @brief Issue a get token request
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param token_type A pointer to the token type. It cannot be set to NULL and 
 * the value must be between 1 and 32 characters, inclusive. 
 * @param applies_to A pointer to the application or service that the token 
 * applies to. It cannot be set to NULL and the value must be between 1 and 96 
 * characters, inclusive. 
 * @param success_cb The function that is invoked upon successful operation 
 * of this function.
 * @param failure_cb The function that is invoked when this function fails. 
 * This callback contains an @c errorCode parameter to specify the failure 
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not 
 * required. This pointer for callback data is passed to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully.
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request. 
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_UNKNOWN_APPLIES_TO: The @c applies_to value is not valid.
 * - @c IDS_UNKNOWN_TOKEN_TYPE: The @c token_type value is not valid.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked, token
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_CANNOT_GET_TOKEN_WHILE_OFFLINE: The service is currently offline
 * and cannot retrieve the requested token.
 * - @c IDS_ERROR_WHILE_CONTACTING_SERVICE: An error occurred communicating
 * with the service.
 */
IDS_API ids_result_t ids_get_token( ids_provider_t* provider,
                                    const char* token_type,
                                    const char* applies_to,
                                    get_token_cb_t success_cb,
                                    failure_cb_t failure_cb,
                                    void* cb_data,
                                    ids_request_id_t* request_id );

/**
 * @brief Issue a request to clear a token
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param token_type A pointer to the token type. It cannot be set to NULL and 
 * the value must be between 1 and 32 characters, inclusive. 
 * @param applies_to A pointer to the application or service that the token
 * applies to. It cannot be set to NULL and the value must be between 1 and 96
 * characters, inclusive.
 * @param success_cb A pointer to the function that is invoked upon successful
 * operation of this function.
 * @param failure_cb A pointer to the function that is invoked when this
 * function fails. This callback contains an @c errorCode parameter to specify
 * the failure condition.
 * @param cb_data This parameter can be set to NULL if callback data is not 
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id A pointer to the request ID that can be used to match the 
 * response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or 
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details In cases where the token seems to be invalid or too close to expiry
 * to be deemed useful, an application can clear the currently cached token in
 * order to retrieve a newly generated token in the next @c ids_get_token()
 * call.
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation. 
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_UNKNOWN_APPLIES_TO: The @c applies_to value is not valid.
 * - @c IDS_UNKNOWN_TOKEN_TYPE: The @c token_type value is not valid.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked; token
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 */
IDS_API ids_result_t ids_clear_token( ids_provider_t* provider,
                                      const char* token_type,
                                      const char* applies_to,
                                      clear_token_cb_t success_cb,
                                      failure_cb_t failure_cb,
                                      void* cb_data,
                                      ids_request_id_t* request_id );


/**
 * @brief The maximum number of properties that can be included in a single 
 * @c ids_get_properties() call
 */
#define IDS_MAX_PROPERTY_COUNT 10

/**
 * @brief The maximum string length of a single property name that can be
 * passed in a single @c ids_get_properties() call, excluding the terminating 
 * NULL
 */
#define IDS_MAX_PROPERTY_NAME_LEN 32

/**
 * @brief The maximum string length of a single data name that can be
 * passed in @c ids_get_data(), @c ids_set_data(), @c ids_create_data()
 * and @c ids_delete_data() calls, excluding the terminating NULL
 */
#define IDS_MAX_DATA_NAME_LEN 128

/**
 * @brief Issue a request for a property
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of properties contained in the @c propertyList
 * parameter. Each identity provider may have a unique set of types that it can
 * accept. See the identity providers' documentation for details on valid 
 * types.
 * @param count The number of properties contained in the @c propertyList
 * parameter.
 * @param propertyList An array of strings listing each of the properties
 * requested.
 * @param success_cb The function that is invoked upon successful operation of
 * this function.
 * @param failure_cb The function that is invoked when this function fails. 
 * This callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked;
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_NAME_MUST_BE_SET: The value of @c count must be greater than 1 and
 * match the number of properties in the @c propertyList.
 * - @c IDS_TOO_MANY_NAMES_PASSED: Too many properties were requested. See 
 * @c IDS_MAX_PROPERTY_COUNT.
 * - @c IDS_NAME_TOO_LONG: The length of a property name in the list exceeds
 * the maximum name length as defined by @c IDS_MAX_PROPERTY_NAME_LEN.
 * - @c IDS_PROPERTY_NOT_AUTHORIZED: The application does not have access to
 * one of the requested properties.
 * - @c IDS_PROPERTY_DOES_NOT_EXIST: Property does not exist.
 * - @c IDS_BAD_PROPERTY_NAME: Invalid property name.
 * - @c IDS_NULL_OR_UNKNOWN_PARAMETERS: Null or invalid parameter.
 * - @c IDS_NON_EXISTING_PROPERTY: Property does not exist.
 * - @c IDS_PROFILE_SERVER_ERROR: Server error.
 * - @c IDS_PROPERTY_VALUE_TOO_LARGE: Property value is too large.
 * - @c IDS_GET_FAIL: Get failed.
 */
IDS_API ids_result_t ids_get_properties( ids_provider_t* provider,
                                         int type,
                                         int count,
                                         const char* propertyList[],
                                         get_properties_cb_t success_cb,
                                         failure_cb_t failure_cb,
                                         void* cb_data,
                                         ids_request_id_t* request_id );

/**
 * @brief Issue a request to get data
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The storage type of the data entry. Each identity provider may 
 * have a unique set of types that it supports. See your identity provider's 
 * documentation for details on valid types.
 * @param flags Special flags for the operation. Each identity provider may 
 * have a unique set of flags that it supports. See the identity providers' 
 * documentation for details on valid flags and their behavior for this 
 * operation.
 * @param name The name of the data entry to retrieve.
 * @param success_cb The function that is invoked upon successful operation 
 * of this function.
 * @param failure_cb The function that is invoked when this function fails. 
 * This callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @return @b Error @b Handling:
 * @return The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * @return Successfully issued requests that do not complete successfully result
 * in the failure callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked;
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_NULL_OR_UNKNOWN_PARAMETERS: Null or invalid parameter.
 * - @c IDS_DOES_NOT_EXIST: An entry with the given @c name does not exist.
 * - @c IDS_NOT_ALLOWED: The application is not allowed to perform this 
 * operation.
 * - @c IDS_ERROR_WHILE_CONTACTING_SERVICE: The identity provider was unable to
 * communicate with its service to perform the operation.
 * - @c USER_RESOURCE_NAME_TOO_LONG: The @c name is longer than the maximum 
 * length allowed by the identity provider.
 */
IDS_API ids_result_t ids_get_data( ids_provider_t* provider,
                                   int type,
                                   int flags,
                                   const char* name,
                                   get_data_cb_t success_cb,
                                   failure_cb_t failure_cb,
                                   void* cb_data,
                                   ids_request_id_t* request_id );

/**
 * @brief Issue a request to set data
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of properties contained in the @c data parameter. Each
 * identity provider may have a unique set of types that it is able to handle.
 * See the identity provider's documentation for details on valid types.
 * @param flags Special flags for the operation. Each identity provider may
 * have a unique set of flags that it supports.  See the identity provider's
 * documentation for details on valid flags and their behavior for this
 * operation.
 * @param data The data entry to set.
 * @param success_cb The function that is invoked upon successful operation of
 * this function.
 * @param failure_cb The function that is invoked when this function fails. This
 * callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked;
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_NULL_OR_UNKNOWN_PARAMETERS: Null or invalid parameter.
 * - @c IDS_DOES_NOT_EXIST: An entry with the given @c name does not exist.
 * - @c IDS_NOT_ALLOWED: The application is not allowed to perform this 
 * operation.
 * - @c IDS_ERROR_WHILE_CONTACTING_SERVICE: The identity provider was unable to
 * communicate with its service to perform the operation.
 * - @c USER_RESOURCE_NAME_TOO_LONG: The @c name is longer than the maximum 
 * length allowed by the identity provider.
 * - @c IDS_QUOTA_EXCEEDED: The data quota set by the identity provider has
 * been exceeded.
 */
IDS_API ids_result_t ids_set_data( ids_provider_t* provider,
                                   int type,
                                   int flags,
                                   const ids_data_t* data,
                                   success_cb_t success_cb,
                                   failure_cb_t failure_cb,
                                   void* cb_data,
                                   ids_request_id_t* request_id );

/**
 * @brief Issue a request to create data
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of properties contained in the @c data parameter. Each 
 * identity provider may have a unique set of types that it is able to handle. 
 * See the identity provider's documentation for details on valid types.
 * @param flags Special flags for the operation. Each identity provider may 
 * have a unique set of flags that it supports. See the identity provider's
 * documentation for details on valid flags and their behavior for this 
 * operation.
 * @param data The data entry to create and store.
 * @param success_cb The function that is invoked upon successful operation of
 * this function.
 * @param failure_cb The function that is invoked when this function fails. This
 * callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked;
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_NULL_OR_UNKNOWN_PARAMETERS: Null or invalid parameter.
 * - @c IDS_ERROR_WHILE_CONTACTING_SERVICE: The identity provider was unable to
 * communicate with its service to perform the operation.
 * - @c IDS_ALREADY_EXISTS: An entry with @c name already exists.
 * - @c IDS_NOT_ALLOWED: The application is not allowed to perform this 
 * operation.
 * - @c USER_RESOURCE_NAME_TOO_LONG: The @c name is longer than the maximum 
 * length allowed by the identity provider. 
 * - @c IDS_QUOTA_EXCEEDED: The data quota set by the identity provider has
 * been exceeded.
 */
IDS_API ids_result_t ids_create_data( ids_provider_t* provider,
                                      int type,
                                      int flags,
                                      const ids_data_t* data,
                                      success_cb_t success_cb,
                                      failure_cb_t failure_cb,
                                      void* cb_data,
                                      ids_request_id_t* request_id );

/**
 * @brief Issue a request to delete data
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of data referenced in the @c name parameter. Each 
 * identity provider may have a unique set of types that it is able to handle. 
 * See the identity provider's documentation for details on valid types.
 * @param flags Special flags for the operation. Each identity provider may 
 * have a unique set of flags that it supports. See the identity provider's 
 * documentation for details on valid flags and their behavior for this 
 * operation.
 * @param name The name of the data to be deleted.
 * @param success_cb The function that is invoked upon successful operation of
 * this function.
 * @param failure_cb The function that is invoked when this function fails. This
 * callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked;
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_NOT_ALLOWED: The application does not have access to delete
 * the requested value.
 * - @c IDS_NULL_OR_UNKNOWN_PARAMETERS: Null or invalid parameter.
 * - @c IDS_DOES_NOT_EXIST: The @c name specified does not exist.
 * - @c IDS_ERROR_WHILE_CONTACTING_SERVICE: The identity provider was unable to
 * communicate with its service to perform the operation.
 * - @c USER_RESOURCE_NAME_TOO_LONG: The @c name is longer than the maximum 
 * length allowed by the identity provider.
 */
IDS_API ids_result_t ids_delete_data( ids_provider_t* provider,
                                      int type,
                                      int flags,
                                      const char* name,
                                      success_cb_t success_cb,
                                      failure_cb_t failure_cb,
                                      void* cb_data,
                                      ids_request_id_t* request_id );

/**
 * @brief Request the list of stored data.
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of data to list. Each identity provider may have a 
 * unique set of types that it is able to handle. See the identity provider's 
 * documentation for details on valid data types.
 * @param flags Special flags for the operation. Each identity provider may 
 * have a unique set of flags that it supports. See the identity provider's 
 * documentation for details on valid flags and their behavior.
 * @param success_cb The function that is invoked upon successful operation of
 * this function.
 * @param failure_cb The function that is invoked when this function fails. This
 * callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked;
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 * - @c IDS_NOT_ALLOWED: The application does not have access to list
 * the requested values.
 * - @c IDS_NULL_OR_UNKNOWN_PARAMETERS: Null or invalid parameter.
 * - @c IDS_DOES_NOT_EXIST: Data that matches the specified parameters does 
 * not exist.
 * - @c IDS_ERROR_WHILE_CONTACTING_SERVICE: The identity provider was unable to
 * communicate with its service to perform the operation.
 */
IDS_API ids_result_t ids_list_data( ids_provider_t* provider,
                                    int type,
                                    int flags,
                                    list_cb_t success_cb,
                                    failure_cb_t failure_cb,
                                    void* cb_data,
                                    ids_request_id_t* request_id );

/**
 * @brief Issue a request to challenge for identity
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of challenge requested. Each identity provider may
 * have a unique set of types that it supports. See the identity provider's
 * documentation for details on valid types and their behavior.
 * @param flags Special flags for the operation. Each identity provider may 
 * have a unique set of flags that it supports. See the identity provider's
 * documentation for details on valid flags and their behavior.
 * @param success_cb The function that is invoked upon successful operation of
 * this function.
 * @param failure_cb The function that is invoked when this function fails. 
 * This callback contains an @c errorCode parameter to specify the failure
 * condition.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's success or failure callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 * @param request_id An updated pointer to the request ID that can be used to
 * match the response to the request.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or 
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 *
 * Requests that do not complete successfully result in the failure
 * callback being called with one of the following result codes:
 * - @c IDS_DEFAULT_ERROR: An internal error occurred while attempting to 
 * process the request.
 * - @c IDS_NOT_READY: The identity provider is not ready to process the
 * request.
 * - @c IDS_NOT_ENOUGH_RESOURCES: There are not enough resources available to
 * process the request.
 * - @c IDS_ACCOUNT_LOCALLY_LOCKED_OUT: The account is currently locked,
 * access is unavailable while the account is locked.
 * - @c IDS_USER_COULD_NOT_BE_AUTHENTICATED: The user could not be
 * authenticated.
 */
IDS_API ids_result_t ids_challenge( ids_provider_t* provider,
                                    int type,
                                    int flags,
                                    challenge_cb_t success_cb,
                                    failure_cb_t failure_cb,
                                    void* cb_data,
                                    ids_request_id_t* request_id );

/**
 * @brief Register a callback function to be called when the named entry
 * changes
 *
 * @param provider A pointer to the identity provider to send this request to.
 * @param type The type of data referred to by the @c name parameter.
 * @param flags Special flags for the operation. Each identity provider may 
 * have a unique set of flags that it supports. See the identity provider's 
 * documentation for details on valid flags and their behavior.
 * @param name The name of the entry to receive notifications for.
 * @param on_change_cb The function that is invoked when a change is detected.
 * @param cb_data This parameter can be set to NULL if callback data is not
 * required. This pointer for callback data is passed in to the calling
 * application's on_change callback without being modified. The
 * application can determine whether it passes it in to the API or leaves it
 * NULL, and also determine how to use it in the callback functions.
 *
 * @return @c IDS_SUCCESS when the request is issued successfully, or 
 * @c IDS_FAILURE with the @c errno value set otherwise.
 *
 * @details
 *
 * @b Error @b Handling:
 *
 * The value of @c errno when @c IDS_FAILURE is returned can be one of the
 * following:
 * - @c EFAULT: The library has not been initialized.
 * - @c E2BIG: The message is too big to send to the identity provider.
 * - @c ECOMM: Unable to communicate with the identity provider.
 * - @c EINVAL: An invalid parameter was passed to the function.
 * - @c ENOMEM: There is not enough memory to complete the operation.
 */
IDS_API ids_result_t ids_register_notifier( ids_provider_t* provider,
                                            int type,
                                            int flags,
                                            const char* name,
                                            notify_cb_t on_change_cb,
                                            void* cb_data );


__END_DECLS

#endif /* _IDS_IDS_H_INCLUDED */
