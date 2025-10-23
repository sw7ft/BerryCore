/*
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
 
/**
 * @file unified_data_source.h
 *
 * @brief Use the Unified Data Source (UDS) library to integrate your app's
 * data, including unique accounts, inbox list items, and actions, into the
 * BlackBerry Hub.
 * 
 * @mainpage Unified Data Service Library
 * 
 * You can use the Unified Data Source (UDS) library to add data from your app
 * directly to the BlackBerry Hub. By integrating your data with the BlackBerry
 * Hub, you can make it easier for users to interact with your app to view
 * updates, create new content, and more.
 * 
 * For example, if your app provides regular notifications of certain events
 * (say, updates to content that your app provides, or reminders to renew 
 * subscriptions to your app's content), you can register with the BlackBerry
 * Hub to include these notifications in a dedicated account view for your
 * app data. Or, if your app lets users send messages or start conversations
 * with other users, you can integrate your chat and conversation interface
 * with the BlackBerry Hub and let users view and create messages there, instead
 * of needing to open your app explicitly.
 * 
 * 
 * @section elementsUDS_Section Elements of the UDS library
 * 
 * The UDS library consists of several elements that you can interact with and
 * use to organize your data in the BlackBerry Hub.
 * 
 * @b Accounts
 * An account represents a grouping of related items that can be displayed
 * together in the BlackBerry Hub. If you open the BlackBerry Hub on a device,
 * you'll notice that there are already some accounts that are predefined, such
 * as "Notifications", "BBM", and "Text Messages". These accounts appear as tabs
 * in the BlackBerry Hub, and you can add your own accounts to this list.
 * 
 * Account-related data is represented by the @c uds_account_data_t structure.
 * This structure includes all of the information that's required to register
 * and display an account in the BlackBerry Hub, such as name, description,
 * icon, and so on.
 * 
 * @b Inbox @b list @b items
 * An inbox list item is an individual item that appears in an account in the
 * BlackBerry Hub. For example, if you're viewing an account that's associated
 * with an email account, each message that appears in that view is an inbox
 * list item. You can add data from your app as inbox list items, and you
 * can associate these items with accounts in the BlackBerry Hub so that they're
 * displayed on that account's tab.
 * 
 * Data that's related to inbox list items is represented by the
 * @c uds_inbox_item_data_t structure. This structure includes all of the
 * information that's required to add and display an inbox list item in the
 * BlackBerry Hub, such as source ID, category ID, name, and so on.
 * 
 * @b Categories
 * A category is a grouping of items within an account. You can use categories
 * to sort and filter inbox list items in the account. For example, a messaging
 * account might contain folders for different types of messages, and each
 * folder is considered a category.
 * 
 * Category-related data is represented by the @c uds_category_data_t
 * structure. This structure includes all of the information that's required to
 * correctly place a category in a particular account, such as account ID,
 * parent ID, type, and so on.
 * 
 * @b Account @b actions
 * An account action is an option that users can select when they view a
 * particular account in the BlackBerry Hub. Account actions can appear in the
 * action bar at the bottom of the screen, in the overflow menu, or in both
 * locations.
 * 
 * You can associate an account action with one of the invocation actions that
 * are available as part of the invocation framework. When a user selects the
 * account action in the BlackBerry Hub, the appropriate target application is
 * invoked to perform the action. For example, you might specify the
 * "bb.action.CREATE" invocation action for an account action. To learn more
 * about actions, targets, and other invocation framework principles, see
 * <a href="http://developer.blackberry.com/native/documentation/core/app_integration.html">App integration</a>.
 * 
 * Data that's related to account actions is represented by the
 * @c uds_account_action_data_t structure. This structure includes all of the
 * information that's required for an account action, such as the target, type,
 * MIME type, and so on.
 * 
 * @b Inbox @b item @b actions
 * An inbox item action is similar to an account action, but applies to the
 * inbox list items that appear within an account in the BlackBerry Hub. Inbox
 * item actions appear in the context menu when a user presses and holds an
 * inbox list item.
 * 
 * Again, similar to account actions, you can associate an inbox item action
 * with one of the invocation actions that are available as part of the
 * invocation framework. To learn more about invocation framework principles,
 * see <a href="http://developer.blackberry.com/native/documentation/core/app_integration.html">App integration</a>.
 * 
 * Inbox item actions typically appear in the context menu for all inbox list
 * items in a particular account. Additionally, you can specify
 * context-sensitive inbox actions, which appear only for certain inbox list
 * items, depending on the state of the item.
 * 
 * Data that's related to inbox item actions is represented by the
 * @c uds_item_action_data_t structure. This structure includes all of the
 * information that's required for an inbox item action, such as the target,
 * type, MIME type, and so on.
 * 
 * 
 * @section modesUDS_Section Modes for the UDS library
 * 
 * You can choose to use the UDS library in one of two modes: synchronous or
 * asynchronous. This section describes how both of these modes work and
 * introduces you to some common functions in the UDS library. For a full code
 * sample that illustrates how to use library functions, see the "Using the
 * Unified Data Source APIs" section below.
 * 
 * @b Synchronous @b mode
 * In this mode, all calls to UDS library functions (such as
 * @c uds_account_added(), @c uds_item_updated(), and so on) block until 
 * a response is received from the BlackBerry Hub server, or until an error
 * occurs.
 * 
 * To show how this mode works, consider the following sequence of
 * function calls. This sequence illustrates how you might choose to use some
 * common functions in the UDS library.
 * 
 * 1. @c uds_init()
 * Opens a connection to the BlackBerry Hub using the UDS library. To use
 * synchronous mode, you call this function with the @c async parameter set to
 * @c false.
 * 
 * 2. @c uds_register_client()
 * Registers your app with the BlackBerry Hub. This function provides a
 * unique service ID to identify your app, as well as the status of the
 * registration.
 * 
 * If your app hasn't registered with the BlackBerry Hub before, the
 * status received is @c UDS_REGISTRATION_NEW. In this case, your app must send
 * all of its information (such as account information, inbox list item
 * information, and so on) to the BlackBerry Hub for population.
 * 
 * If your app has previously registered with the BlackBerry Hub, the
 * status received is @c UDS_REGISTRATION_EXISTS. In this case, you can choose
 * to send only the information that is new since your app last synchronized
 * with the BlackBerry Hub, instead of sending all information.
 * 
 * 3. @c uds_get_service_id()
 * Retrieves the service ID that's assigned to identify your app to the
 * BlackBerry Hub. In synchronous mode, you should call this function only after
 * you call @c uds_register_client() and receive @c UDS_SUCCESS from that
 * function. This function call is optional.
 * 
 * 4. @c uds_get_service_status()
 * Retrieves the service status after you register your app with the BlackBerry
 * Hub. In synchronous mode, you should call this function only after you call
 * @c uds_register_client() and receive @c UDS_SUCCESS from that function. This
 * function call is optional.
 * 
 * 5. @c uds_account_added()
 * Adds an account to the BlackBerry Hub. Typically, your app creates one
 * account to represent its data in the BlackBerry Hub. Each account is
 * represented by a unique tab and icon (which you set using
 * @c uds_account_data_set_icon()).
 * 
 * 6. @c uds_category_added()
 * Adds a category (such as a folder) for inbox list items within an account.
 * 
 * 7. @c uds_item_added()
 * Adds an inbox list item to a specific account in the BlackBerry Hub.
 * 
 * 8. @c uds_item_updated()
 * Updates an inbox list item if its state changes (for example, if the icon
 * changes, if the number of unread messages changes, and so on).
 * 
 * 9. @c uds_item_removed()
 * Removes an inbox list item from the BlackBerry Hub.
 * 
 * @b Asynchronous @b mode
 * In this mode, all calls to UDS library functions will return immediately
 * after sending the associated command to the BlackBerry Hub server. You can
 * call @c uds_wait_for_response() on a separate thread to block until you
 * receive a response. Then, when a response is available, you can call
 * @c uds_get_response() to retrieve and parse the response. You might choose
 * to use asynchronous mode instead of synchronous mode if you want your app to
 * be able to continue doing its own operations (such as processing information
 * while it's waiting for responses from the BlackBerry Hub server.
 * 
 * To show how this mode works and how it's different than synchronous mode,
 * consider the following sequence of function calls. This sequence performs
 * the same operations as the sequence presented in the "Synchronous mode"
 * section above, but because asynchronous mode is used, a few extra function
 * calls to wait for and retrieve responses are required. Note that some of the
 * descriptions of functions have been abbreviated, so check the descriptions in
 * the "Synchronous mode" section for full details.
 * 
 * 1. @c uds_init()
 * Opens a connection to the BlackBerry Hub using the UDS library. To use
 * asynchronous mode, you call this function with the @c async parameter set to
 * @c true.
 * 
 * 2. @c uds_register_client()
 * Registers your app with the BlackBerry Hub.
 * 
 * 3. @c uds_wait_for_response()
 * Blocks (possibly on a separate thread) and waits for a response from the
 * BlackBerry Hub server. Here, this function waits for a response regarding
 * the @c uds_register_client() command that was sent in step 2 above.
 * 
 * 4. @c uds_get_response()
 * Retrieves and parses the response. Here, we're retrieving the response from
 * the @c uds_register_client() command that was sent in step 2 above.
 * 
 * 5. @c uds_get_service_id()
 * Retrieves the service ID that's assigned to identify your app to the
 * BlackBerry Hub. In asynchronous mode, you should call this function only
 * after you call @c uds_register_client() and receive and parse the response
 * using @c uds_get_response(). This function call is optional.
 * 
 * 6. @c uds_get_service_status()
 * Retrieves the service status after you register your app with the BlackBerry
 * Hub. In asynchronous mode, you should call this function only after you call
 * @c uds_register_client() and receive and parse the response using
 * @c uds_get_response(). This function call is optional.
 * 
 * 7. @c uds_account_added()
 * Adds an account to the BlackBerry Hub.
 * 
 * 8. @c uds_wait_for_response() and @c uds_get_response()
 * Blocks and waits for a response regarding the @c uds_account_added()
 * command that was sent in step 7 above. Then, retrieves and parses the
 * response.
 * 
 * 9. @c uds_category_added()
 * Adds a category (such as a folder) for inbox list items within an account.
 * 
 * 10. @c uds_wait_for_response() and @c uds_get_response()
 * Blocks and waits for a response regarding the @c uds_category_added()
 * command that was sent in step 9 above. Then, retrieves and parses the
 * response.
 * 
 * 11. @c uds_item_added()
 * Adds an inbox list item to a specific account in the BlackBerry Hub.
 * 
 * 12. @c uds_wait_for_response() and @c uds_get_response()
 * Blocks and waits for a response regarding the @c uds_item_added()
 * command that was sent in step 11 above. Then, retrieves and parses the
 * response.
 * 
 * 13. @c uds_item_updated()
 * Updates an inbox list item if its state changes (for example, if the icon
 * changes, if the number of unread messages changes, and so on).
 * 
 * 14. @c uds_wait_for_response() and @c uds_get_response()
 * Blocks and waits for a response regarding the @c uds_item_updated()
 * command that was sent in step 13 above. Then, retrieves and parses the
 * response.
 * 
 * 15. @c uds_item_removed()
 * Removes an inbox list item from the BlackBerry Hub.
 * 
 * 16. @c uds_wait_for_response() and @c uds_get_response()
 * Blocks and waits for a response regarding the @c uds_item_removed()
 * command that was sent in step 15 above. Then, retrieves and parses the
 * response.
 * 
 * 
 * @section usingUDS_Section Using the Unified Data Source APIs
 * 
 * This section provides some sample code that demonstrates how to use the 
 * functions and features of the UDS library. Note that this sample demonstrates
 * how to use the UDS library in synchronous mode.
 * 
 * First, your app must register with the BlackBerry Hub and include some
 * required data in the registration request, such as name, asset path, and so
 * on.
 * @code
 * uds_context_t udsHandle;
 * int retVal = -1;
 * int serviceId = 0;
 * int status = 0;
 * bool async = false;
 *
 * if ((retVal = uds_init(&udsHandle, async)) == UDS_SUCCESS)
 * {
 *     char* serviceURL = "c_lib_service";
 *     char* libPath = "";
 *     char* assetPath = "/apps/com.example.UDSTestApp.testDev__UDSTestApp9ded287c/app/public/assets/images";
 *     if( (retVal = uds_register_client(udsHandle, serviceURL, libPath, assetPath)) != UDS_SUCCESS)
 *     {
 *         printf("uds_register_client call failed with error %d\n", retVal);
 *     }
 *     if (retVal == UDS_SUCCESS)
 *     {
 *         serviceId = uds_get_service_id(udsHandle);
 *         status = uds_get_service_status(udsHandle);
 *     }
 * }
 * printf("uds_register_client call successful with %d as serviceId and %d as status\n", serviceId, status);
 * @endcode
 *
 * Next, your app can add unique accounts that are associated with its features
 * or services. When you add an account, it appears as a tab in the main view
 * of the BlackBerry Hub. Users can select the tab to view your data.
 * 
 * @code
 * uds_account_data_t paccount_data = uds_account_data_create();
 * uds_account_data_set_id(account_data,1000);
 * uds_account_data_set_name(account_data,"My C Account");
 * uds_account_data_set_icon(account_data,"ic_account.png");
 * uds_account_data_set_target_name(account_data,"com.example.service");
 * if (0 != (retVal = uds_account_added(udsHandle, account_data)))
 * {
 *     printf("uds_account_added failed with error %d \n", retVal);
 * }
 * @endcode
 *
 * Now, your app can register account actions and inbox item actions. Account
 * actions apply to the account as a whole, and they appear on the action bar
 * (or in the overflow menu) when users view the tab for your account. Inbox
 * item actions appear in the context menu when users press and hold an inbox
 * list item in your account.
 * 
 * @code
 * // Client service supported and defined actions on list items
 * typedef enum{
 *     Read = 0x01<<0,
 *     Unread = 0x01<<1,
 *     FriendRequest = 0x01<<2
 * } ActionState;
 * 
 * uds_account_action_data_t account_action = uds_account_action_data_create();
 * AccountActionData aItem;
 * uds_account_action_data_set_action(account_action,"bb.action.SHARE");
 * uds_account_action_data_set_target(account_action,"UDSTestApp");
 * uds_account_action_data_set_type(account_action,"text/plain");
 * uds_account_action_data_set_title(account_action,"Status");
 * uds_account_action_data_set_image_source(account_action,"ic_status.png");
 * uds_account_action_data_set_placement(account_action,uds_placement_type_t::UDS_PLACEMENT_BAR);
 * 
 * if (UDS_SUCCESS!= (retVal = uds_register_account_action(udsHandle, 1000 , account_action)))
 * {
 *     printf("uds_register_account_action failed with error %d\n", retVal);
 * }
 * uds_account_action_destroy(action_data);
 *
 * uds_item_action_data_t item_action = uds_item_action_data_create();
 * uds_item_action_data_set_action(item_action,"bb.action.MARKREAD");
 * uds_item_action_data_set_target(item_action,"text/plain");
 * uds_item_action_data_set_title(item_action,"Mark Read");
 * uds_item_action_data_set_image_source(item_action,"ca_uds_read.png");
 * uds_item_action_data_set_mime_type(item_action,"plain/message");
 * uds_item_action_data_set_context_mask(item_action,Read);
 * 
 * if (UDS_SUCCESS!= (retVal = uds_register_item_context_action(udsHandle, 1000 , item_action)))
 * {
 *     printf("uds_register_item_context_action failed with error %d\n", retVal);
 * }
 * uds_item_action_destroy(item_action);
 * @endcode
 * 
 * Finally, your app can add inbox list items that represent your data, as well
 * as categories if you want to sort the items within an account.
 * 
 * @code
 * uds_inbox_item_data_t pInboxItem = uds_inbox_item_data_create();
 * uds_inbox_item_data_set_account_id(pInboxItem,1000);
 * uds_inbox_item_data_set_source_id(pInboxItem,"1");
 * uds_inbox_item_data_set_name(pInboxItem,"C Inbox Item Unread");
 * uds_inbox_item_data_set_description(pInboxItem,"C Subject Unread");
 * uds_inbox_item_data_set_icon(pInboxItem,"ca_uds_unread.png");
 * uds_inbox_item_data_set_mime_type(pInboxItem,"plain/message");
 * uds_inbox_item_data_set_unread_count(pInboxItem,1);
 * uds_inbox_item_data_set_total_count(pInboxItem,1);
 * uds_inbox_item_data_set_category_id(pInboxItem,1);
 * uds_inbox_item_data_set_timestamp(pInboxItem,1373405489000);
 * uds_inbox_item_data_set_context_state(pInboxItem,Read);
 * 
 * if (UDS_SUCCESS!= (retVal = uds_item_added(udsHandle, pInboxItem)))
 * {
 *     printf("uds_item_added failed with error %d\n", retVal);
 * }
 * uds_inbox_item_data_destroy(pInboxItem);
 * @endcode
 */

#ifndef UNIFIED_DATASOURCE_C_H_
#define UNIFIED_DATASOURCE_C_H_

__BEGIN_DECLS


/*
 * Typedefs and structures for UDS data
 */

/**
 * @brief The primary handle that's used to communicate with the BlackBerry Hub
 * 
 * @details You need to pass this handle to many functions that interact with
 * the BlackBerry Hub and data in it, such as @c uds_init(),
 * @c uds_register_client(), @c uds_item_added(), and so on.
 */
typedef void* uds_context_t;

/**
 * @brief The primary account key that is associated with BlackBerry Hub data
 *
 * @details This key is unique across the platform, and it identifies a
 * particular user account on a device (such as a messaging account). You can
 * obtain this key by using the
 * <a href="http://developer.blackberry.com/native/reference/cascades/app_integration_account.html">PIM Accounts API</a>,
 * which includes classes such as @c AccountService, @c AccountKey, and so on.
 */
typedef long long int uds_account_key_t;

/**
 * @brief The category key of a category within an account
 *
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. For example, a messaging account
 * might contain folders for different types of messages, and each folder is
 * considered a category. In this case, the folder ID would be considered the
 * category key.
 */
typedef long long int uds_category_key_t;

/**
 * @brief The unique source key of an inbox list item
 *
 * @details When you add an inbox item to the BlackBerry Hub using
 * @c uds_item_added(), this item is assigned a unique source key. 
 * Typically, this key is unique per account and is used to represent the list
 * item that was added.
 */
typedef char* uds_source_key_t;

/**
 * @brief The unique server-side synchronization key of an inbox list item
 * 
 * @details This structure represents a unique server-side synchronization key
 * of an inbox list item.
 */
typedef char* uds_sync_key_t;

/**
 * @brief A data key that's associated with data that is added to the BlackBerry
 * Hub
 * 
 * @details This structure represents a data key that's associated with data
 * that is added to the BlackBerry Hub.
 */
typedef long long int uds_data_key_t;

/**
 * @brief A structure that represents account-related data
 * 
 * @details This structure includes all of the information that's required to
 * register and display an account in the BlackBerry Hub, such as name,
 * description, icon, and so on. You receive a @c uds_account_data_t when you
 * create a handle for an account using @c uds_account_data_create(), and you
 * pass it to functions that manipulate account data, such as
 * @c uds_account_data_set_name() and @c uds_account_data_set_description().
 *
 * You also use this structure when you add an account to the BlackBerry Hub
 * by calling @c uds_account_added(). Each account is represented as a tab in
 * the main view of the BlackBerry Hub.
 */
typedef struct uds_account_data uds_account_data_t;

/**
 * @brief A structure that represents data for an inbox list item
 * 
 * @details This structure includes all of the information that's required to
 * add and display an inbox list item in the BlackBerry Hub, such as source ID,
 * category ID, name, and so on. You receive a @c uds_inbox_item_data_t when you
 * create a handle for an inbox list item using @c uds_inbox_item_data_create(),
 * and you pass it to functions that manipulate inbox list item data, such as
 * @c uds_inbox_item_data_set_source_id() and
 * @c uds_inbox_item_data_set_mime_type().
 * 
 * You also use this structure when you add an inbox list item to the BlackBerry
 * Hub by calling @c uds_item_added(). Each unique inbox item appears as a list
 * item in both the main view of the BlackBerry Hub and the account view for the
 * account that contains the item.
 */
typedef struct uds_inbox_item_data uds_inbox_item_data_t;

/**
 * @brief A structure that represents category-related data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. For example, a messaging account
 * might contain folders for different types of messages, and each folder is
 * considered a category.
 * 
 * This structure includes all of the information that's required for a
 * category in an account, such as account ID, parent ID, type, and so on. You
 * receive a @c uds_category_data_t when you create a handle for a category
 * using @c uds_category_data_create(), and you pass it to functions that
 * manipulate category data, such as @c uds_category_data_set_parent_id() and
 * @c uds_category_data_set_type().
 * 
 * You also use this structure when you add a category to an account in the
 * BlackBerry Hub by calling @c uds_category_added(). Adding categories to an
 * account is optional.
 */
typedef struct uds_category_data uds_category_data_t;

/**
 * @brief A structure that represents data for an account action
 * 
 * @details An account on a device can have a set of associated actions. These
 * actions appear on the action bar in the account view in the BlackBerry Hub.
 * For example, you could add an action to create a new inbox list item.
 * You can add actions that are associated with invocation framework actions,
 * such as "bb.action.STATUS" and "bb.action.CREATE". When a user taps an
 * account action, it is processed using the action and target that you specify
 * (using @c uds_account_action_data_set_action() and
 * @c uds_account_action_data_set_target(), respectively).
 * 
 * This structure includes all of the information that's required for an action
 * in an account, such as the target, type, MIME type, and so on. You receive
 * a @c uds_account_action_data_t when you create a handle for an account action
 * using @c uds_account_action_data_create(), and you pass it to functions that
 * manipulate account action data, such as @c uds_account_action_data_set_type()
 * and @c uds_account_action_data_set_mime_type().
 * 
 * You also use this structure when you add an action to an account in the
 * BlackBerry Hub by calling @c uds_register_account_action(). Adding actions
 * to an account is optional.
 */
typedef struct uds_account_action_data uds_account_action_data_t;

/**
 * @brief A structure that represents data for an inbox item action
 * 
 * @details An inbox list item can have a set of associated actions. While
 * account actions appear on the action bar and apply to an entire account,
 * an inbox item action is added to the context menu and appears based on the
 * context state that's provided for the item. For example, you could add an
 * action to mark a particular inbox item as read. You can add actions that
 * are associated with invocation framework actions, such as "bb.action.ACCEPT"
 * and "bb.action.MARKREAD". When a user presses and holds an inbox item to
 * display the context menu, and then taps an action in that menu, the action is
 * processed using the action and target that you specify (using
 * @c uds_item_action_data_set_action() and
 * @c uds_item_action_data_set_target(), respectively).
 * 
 * This structure includes all of the information that's required for an inbox
 * item action, such as the target, type, MIME type, and so on. You receive a
 * @c uds_item_action_data_t when you create a handle for an inbox item action
 * using @c uds_item_action_data_create(), and you pass it to functions that
 * manipulate inbox item action data, such as @c uds_item_action_data_set_type()
 * and @c uds_item_action_data_set_mime_type().
 * 
 * You also use this structure when you add an action to an inbox item in the
 * BlackBerry Hub by calling @c uds_register_item_context_action(). Adding
 * actions to an inbox item is optional.
 */
typedef struct uds_item_action_data uds_item_action_data_t;


/*
 * Enumerations for UDS error codes, registration codes, and other values.
 */

/**
 * @brief An enumeration of error codes
 * 
 * @details These codes are returned by several functions that manipulate
 * data in the BlackBerry Hub, such as @c uds_init(), @c uds_register_client(),
 * and @c uds_item_added(). These codes correspond to common errors that might
 * occur when you call functions in this API, such as disconnection from the
 * BlackBerry Hub, invalid inbox list item, and timeouts. You can use these
 * codes to handle errors properly in your app.
 */
typedef enum{
    /**
     * @brief Indicates that the operation succeeded
     */
    UDS_SUCCESS = 0,
    
    /**
     * @brief Indicates that the operation failed
     */
    UDS_ERROR_FAILED = 501,
    
    /**
     * @brief Indicates that your app is disconnected from the BlackBerry Hub
     */
    UDS_ERROR_DISCONNECTED = 502,
    
    /**
     * @brief Indicates that the inbox list item is invalid
     * 
     * @details Note that this is currently a placeholder value and is not
     * supported at this time.
     */
    UDS_ERROR_INVALID_ITEM = 503,
    
    /**
     * @brief Indicates that an operation is not supported
     * 
     * @details Note that this is currently a placeholder value and is not
     * supported at this time.
     */
    UDS_ERROR_NOT_SUPPORTED = 504,
    
    /**
     * @brief Indicates that an operation timed out
     */
    UDS_ERROR_TIMEOUT = 505,

    /**
     * @brief Indicates that a configuration with the same values already exists
     * in the BlackBerry Hub
     * 
     * @details Note that this is currently a placeholder value and is not
     * supported at this time.
     */
    UDS_DUPLICATE_CONFIG = 601,

    /**
     * @brief Indicates that a service ID is invalid
     * 
     * @details This error code might be returned if your app tries to add data,
     * such as an inbox list item, to the BlackBerry Hub without first
     * registering by calling @c uds_register_client().
     */
    UDS_INVALID_SERVICE_ID = 602,

    /**
     * @brief Indicates that an account ID does not exist in the BlackBerry
     * Hub
     * 
     * @details This error code might be returned if the account ID that you
     * provide in a function call does not match the one that was used by
     * @c uds_account_added(). It might also be returned if the account that
     * you're trying to work with doesn't exist in the BlackBerry Hub.
     */
    UDS_INVALID_ACCOUNT_ID = 603

}uds_error_code_t;

/**
 * @brief An enumeration of registration return codes
 * 
 * @details These codes are returned by the @c uds_register_client() function
 * and indicate the status of registration with the BlackBerry Hub. These
 * codes indicate whether the registration is new, whether your app has already
 * registered with the BlackBerry Hub, or whether a registration error occurred.
 */
typedef enum {
    /**
     * @brief Indicates that an unknown error occurred and that registration
     * was not completed
     * 
     * @details Note that this is currently a placeholder value and is not
     * supported at this time.
     */
    UDS_REGISTRATION_UNKNOWN = 0,
    
    /**
     * @brief Indicates that the registration was completed successfully and
     * that it is a new registration
     * 
     * @details This code is returned from @c uds_register_client() the first
     * time your app registers with the BlackBerry Hub. It's also returned after
     * an over-the-air (OTA) upgrade of the device OS that results in a schema
     * change to the BlackBerry Hub. This code indicates that this is a fresh
     * registration, so your app should add its data to the BlackBerry Hub,
     * such as accounts, inbox list items, and so on.
     */
    UDS_REGISTRATION_NEW = 1,

    /**
     * @brief Indicates that your app has already registered
     * 
     * @details This code is returned from @c uds_register_client() if your
     * app has already completed a successful registration with the BlackBerry
     * Hub and has restarted. This code indicates that your app doesn't need to
     * add its data (such as accounts or inbox list items) to the BlackBerry Hub
     * again, if it already added the data previously.
     */
    UDS_REGISTRATION_EXISTS = 2,

    /**
     * @brief Indicates that an error occurred and that registration was not
     * completed
     * 
     * @details Note that this is currently a placeholder value and is not
     * supported at this time.
     */
    UDS_REGISTRATION_ERROR =3
}uds_registration_code_t;


/**
 * @brief An enumeration of account statuses
 * 
 * @details This enumeration represents the different account statuses that can
 * be registered with the BlackBerry Hub. Account status is used to
 * categorize an account as a work account, personal account, or hybrid account.
 */
typedef enum{
    /**
     * @brief Indicates that the account is an enterprise (work) account
     */
    UDS_ACCOUNT_ENTERPRISE = 2,
    
    /**
     * @brief Indicates that the account is a personal account
     */
    UDS_ACCOUNT_PERSONAL = 8,
    
    /**
     * @brief Indicates that the account is a hybrid account and includes both
     * work and personal information
     */
    UDS_ACCOUNT_HYBRID = 64
}uds_account_status_t;

/**
 * @brief An enumeration of perimeters that can be associated with an inbox list
 * item
 * 
 * @details BlackBerry 10 devices include two perimeters, enterprise and
 * personal, that are designed to separate sensitive work information from
 * personal information. Each inbox list item in the BlackBerry Hub can be
 * associated with one of these perimeters.
 */
typedef enum {
    /**
     * @brief Indicates that the inbox list item belongs in the enterprise
     * perimeter
     * 
     * @details This value is used only for hybrid accounts (represented by
     * @c UDS_ACCOUNT_HYBRID in the @c uds_account_status_t enumeration),
     * because items with this value can belong to both perimeters.
     */
    UDS_PERIMETER_ENTERPRISE = 0x1,
    
    /**
     * @brief Indicates that the inbox list item belongs in the personal
     * perimeter
     */
    UDS_PERIMETER_PERSONAL   = 0x2
} uds_perimeter_type_t;

/**
 * @brief An enumeration of placements for actions
 * 
 * @details Each account and inbox list item in the BlackBerry Hub can include a
 * set of actions. These actions are associated with actions in the invocation
 * framework, such as "bb.action.CREATE" and "bb.action.MARKREAD". For more
 * information about actions, see @c uds_account_action_data_t and 
 * @c uds_item_action_data_t.
 * 
 * Each action can be placed in different locations when in account view in the
 * BlackBerry Hub. You can place an action on the action bar at the
 * bottom of the screen, in the overflow menu, or in both locations. Actions can
 * also be placed in fixed locations, such as the fixed location for "delete"
 * actions. 
 */
typedef enum {
    /**
     * @brief Specifies that the action should be placed in its default
     * location, which is typically in the overflow menu
     */
    UDS_PLACEMENT_DEFAULT=0,
    
    /**
     * @brief Specifies that the action should be placed in the action menu
     * only
     */
    UDS_PLACEMENT_OVERFLOW=1,
    
    /**
     * @brief Specifies that the action should be placed on the action bar
     * 
     * @details The action will also be placed in the action menu.
     */
    UDS_PLACEMENT_BAR=2,
    
    /**
     * @brief Specifies that the action placement is fixed (for example, a
     * delete or archive action)
     */
    UDS_PLACEMENT_FIXED=3,

    /**
     * @brief Specifies that the action should be placed as the Signature action on bar
     */
    UDS_PLACEMENT_SIGNATURE=4
}uds_placement_type_t;

/**
 * @brief An enumeration of account types
 * 
 * @details This enumeration represents the different account types that can be
 * registered with the BlackBerry Hub, such as an SMS/MMS account, a social
 * account, or an instant messaging account. The account type is used to group
 * and order the accounts on the account tab in the BlackBerry Hub.
 * 
 * It's important to note that setting the type of an account does not
 * guarantee a specific placement order on the main tab in the BlackBerry Hub.
 */
typedef enum{
    /**
     * @brief Indicates that the account is a notification account
     */
    UDS_ACCOUNT_TYPE_NOTIFICATION = 2,
    
    /**
     * @brief Indicates that the account is an SMS/MMS text messaging account
     */
    UDS_ACCOUNT_TYPE_TEXT_MESSAGE = 3,
    
    /**
     * @brief Indicates that the account is a social account
     */
    UDS_ACCOUNT_TYPE_SOCIAL = 5,
    
    /**
     * @brief Indicates that the account is an instant messaging (IM) account
     */
    UDS_ACCOUNT_TYPE_IM = 6,
    
    /**
     * @brief Indicates that the account is another type of account that's not
     * listed here
     */
    UDS_ACCOUNT_TYPE_OTHER = 11
} uds_account_type_t;


/*
 * Functions to manipulate UDS accounts and account data
 */

/**
 * @brief Create a handle for account data
 * 
 * @details This handle is represented as a @c uds_account_data_t and is the
 * primary way of communicating with the BlackBerry Hub for account-related
 * changes and inquiries. It includes all of the information about a particular
 * account, and you pass this handle as a parameter to @c uds_account_added()
 * and @c uds_account_updated() when you want to add or update an account in 
 * the BlackBerry Hub, respectively.
 * 
 * You also use this handle to specify the account that you want to change
 * (using functions such as @c uds_account_data_set_name() and
 * @c uds_account_data_set_description()) or retrieve information for (using
 * functions such as @c uds_account_data_get_name() and
 * @c uds_account_data_get_description()).
 * 
 * @return A handle for account data, as a @c uds_account_data_t.
 */
uds_account_data_t *uds_account_data_create();

/**
 * @brief Delete a handle for account data
 * 
 * @details This function deletes the specified handle for account data that
 * you created by calling @c uds_account_data_create().
 * 
 * @param inst The handle for account data that you want to delete.
 */
void uds_account_data_destroy(uds_account_data_t *inst);

/**
 * @brief Set the account key for the specified account data
 * 
 * @details The account key for an account is unique across the platform and
 * it identifies a particular user account on a device. You can obtain this
 * key by using the
 * <a href="http://developer.blackberry.com/native/reference/cascades/app_integration_account.html">PIM Accounts API</a>.
 * 
 * @param account The account to set the account key for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param id The unique account key to set.
 */
void uds_account_data_set_id(uds_account_data_t *account, uds_account_key_t id);

/**
 * @brief Set the name for the specified account data
 * 
 * @details This name appears as the label of the associated account's tab in
 * the BlackBerry Hub. The string value that you pass in as the @c name
 * parameter must remain valid until the data is used in a call to
 * @c uds_account_added() or @c uds_account_updated.
 * 
 * @param account The account to set the name for. This account is represented
 * by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param name The name to set.
 */
void uds_account_data_set_name(uds_account_data_t *account, const char* name);

/**
 * @brief Set the description for the specified account data
 * 
 * @details This description appears under the main account label in the
 * associated account's tab in the BlackBerry Hub. This description could
 * include account-specific information, such as the user account name. The
 * string value that you pass in as the @c account_desc parameter must remain
 * valid until the data is used in a call to @c uds_account_added() or
 * @c uds_account_updated().
 * 
 * @param account The account to set the description for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param account_desc The description to set.
 */
void uds_account_data_set_description(uds_account_data_t *account, const char* account_desc);

/**
 * @brief Set the icon for the specified account data
 * 
 * @details This icon appears along with the account name on the associated
 * account's tab in the BlackBerry Hub. The icon that you want to use must be
 * located in the asset directory that you specify when you call
 * @c uds_register_client(). The icon should also be 81x81 pixels and in PNG
 * format.
 * 
 * The string value that you pass in as the @c icon parameter must remain valid 
 * until the data is used in a call to @c uds_account_added() or
 * @c uds_account_updated().
 *
 * @param account The account to set the icon for. This account is represented
 * by a @c uds_account_data_t and is created using @c uds_account_data_create().
 * @param icon The file name of the icon to set.
 */
void uds_account_data_set_icon(uds_account_data_t *account, const char* icon);

/**
 * @brief Set the locked icon for the specified account data
 * 
 * @details If an account is associated with the enterprise perimeter, it's
 * possible that this perimeter may be locked. If this perimeter is locked when
 * a user views the BlackBerry Hub, any accounts associated with it are not
 * accessible, and these accounts display a different icon on the account tab
 * in the BlackBerry Hub. This function lets you specify the icon that appears
 * when an account's perimeter is locked. The icon that you want to use must be
 * located in the asset directory that you specify when you call
 * @c uds_register_client(). The icon should also be 81x81 pixels and in PNG
 * format.
 * 
 * This icon is required only for enterprise (@c UDS_ACCOUNT_ENTERPRISE) and
 * hybrid (@c UDS_ACCOUNT_HYBRID) accounts. The string value that you pass in
 * as the @c locked_icon parameter must remain valid until the data is used in
 * a call to @c uds_account_added() or @c uds_account_updated().
 *
 * @param account The account to set the locked icon for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param locked_icon The file name of the locked icon to set.
 */
void uds_account_data_set_locked_icon(uds_account_data_t *account, const char* locked_icon);

/**
 * @brief Set whether the "Compose" action is supported by the specified
 * account data
 * 
 * @details When a user views the main tab of the BlackBerry Hub, a "Compose"
 * action appears on the action bar at the bottom of the screen. When this
 * action is selected, the user is asked to select an account to compose a
 * message from. You can use this function to specify whether an account should
 * appear in this list.
 * 
 * @param account The account to set "Compose" support for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param support_compose If @c true the account supports the "Compose"
 * action in the BlackBerry Hub, if @c false the account does not support the
 * "Compose" action.
 */
void uds_account_data_set_supports_compose(uds_account_data_t *account, bool support_compose);

/**
 * @brief Set the target name for the specified account data
 * 
 * @details This target name is used as a generic target for all invocation
 * framework actions that are related to this account. If an account action
 * provides its own target (by using @c uds_account_action_data_set_target()),
 * that specific target overrides the generic target for that account action.
 * The string value that you pass in as the @c target_name parameter must remain
 * valid until the data is used in a call to @c uds_account_added() or
 * @c uds_account_updated().
 *
 * @param account The account to set the target name for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param target_name The target name to set.
 */
void uds_account_data_set_target_name(uds_account_data_t *account, const char* target_name);

/**
 * @brief Set the "Compose" icon for the specified account data
 * 
 * @details When a user views the main tab of the BlackBerry Hub, a "Compose"
 * action appears on the action bar at the bottom of the screen. When this
 * action is selected, the user is asked to select an account to compose a
 * message from. You can use this function to specify the colored icon that
 * appears next to the account name in this list. The icon that you want to use
 * must be located in the asset directory that you specify when you call
 * @c uds_register_client(). The icon should also be 81x81 pixels and in PNG
 * format.
 * 
 * It's important to note that for an account to appear in this list, you must
 * enable "Compose" support for the account by calling
 * @c uds_account_data_set_supports_compose() with a parameter value of @c true.
 * 
 * The string value that you pass in as the @c compose_icon parameter must
 * remain valid until the data is used in a call to @c uds_account_added() or
 * @c uds_account_updated().
 * 
 * @param account The account to set the "Compose" icon for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param compose_icon The file name of the icon to set.
 */
void uds_account_data_set_compose_icon(uds_account_data_t *account, const char* compose_icon);

/**
 * @brief Set the type for the specified account data
 * 
 * @details The type of an account is specified by using values in the
 * @c uds_account_type_t enumeration. An account might be an SMS/MMS text
 * messaging account, a social account, or another type of account.
 * 
 * @param account The account to set the type for. This account is represented
 * by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * @param type The account type to set. If not specified, the default value is
 * @c UDS_ACCOUNT_TYPE_OTHER.
 */
void uds_account_data_set_type(uds_account_data_t *account, uds_account_type_t type);

/**
 * @brief Get the account key for the specified account data
 * 
 * @details The account key for an account is unique across the platform and
 * it identifies a particular user account on a device.
 * 
 * @param account The account to get the account key for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The account key of the specified account, as a @c uds_account_key_t.
 */
uds_account_key_t uds_account_data_get_id(uds_account_data_t const *account);

/**
 * @brief Get the name for the specified account data
 * 
 * @details This name appears as the label of the associated account's tab in
 * the BlackBerry Hub.
 * 
 * @param account The account to get the name for. This account is represented
 * by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The name of the specified account.
 */
const char* uds_account_data_get_name(uds_account_data_t const *account);

/**
 * @brief Get the description for the specified account data
 * 
 * @details This description appears under the main account label in the
 * associated account's tab in the BlackBerry Hub.
 * 
 * @param account The account to get the description for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The description of the specified account.
 */
const char* uds_account_data_get_description(uds_account_data_t const *account);

/**
 * @brief Get the file name of the icon for the specified account data
 * 
 * @details This icon appears along with the account name on the associated
 * account's tab in the BlackBerry Hub.
 * 
 * @param account The account to get the file name of the icon for. This account
 * is represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The file name of the icon for the specified account.
 */
const char* uds_account_data_get_icon(uds_account_data_t const *account);

/**
 * @brief Get the file name of the locked icon for the specified account data
 * 
 * @details If an account is associated with the enterprise perimeter, it's
 * possible that this perimeter may be locked. If this perimeter is locked when
 * a user views the BlackBerry Hub, any accounts associated with it are not
 * accessible, and these accounts display a different icon on the account tab
 * in the BlackBerry Hub. This function lets you retrieve the icon that appears
 * when an account's perimeter is locked.
 * 
 * @param account The account to get the file name of the locked icon for. This
 * account is represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The file name of the locked icon for the specified account.
 */
const char* uds_account_data_get_locked_icon(uds_account_data_t const *account);

/**
 * @brief Get whether the "Compose" action is supported by the specified
 * account data
 * 
 * @details When a user views the main tab of the BlackBerry Hub, a "Compose"
 * action appears on the action bar at the bottom of the screen. When this
 * action is selected, the user is asked to select an account to compose a
 * message from. You can use this function to retrieve whether an account should
 * appear in this list.
 * 
 * @param account The account to get "Compose" action support for. This account
 * is represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return @c true if the account supports the "Compose" action in the
 * BlackBerry Hub, @c false otherwise.
 */
bool uds_account_data_get_supports_compose(uds_account_data_t const *account);

/**
 * @brief Get the target name for the specified account data
 * 
 * @details This target name is used as a generic target for all invocation
 * framework actions that are related to this account.
 *
 * @param account The account to get the target name for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The target name of the specified account.
 */
const char* uds_account_data_get_target_name(uds_account_data_t const *account);

/**
 * @brief Get the file name of the "Compose" icon for the specified account data
 * 
 * @details When a user views the main tab of the BlackBerry Hub, a "Compose"
 * action appears on the action bar at the bottom of the screen. When this
 * action is selected, the user is asked to select an account to compose a
 * message from. You can use this function to retrieve the colored icon that
 * appears next to the account name in this list.
 * 
 * @param account The account to get the "Compose" icon for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 *
 * @return The file name of the "Compose" icon for the specified account.
 */
const char* uds_account_data_get_compose_icon(uds_account_data_t const *account);

/**
 * @brief Get the type for the specified account data
 * 
 * @details The type of an account is specified by using values in the
 * @c uds_account_type_t enumeration. An account might be an SMS/MMS text
 * messaging account, a social account, or another type of account.
 * 
 * @param account The account to get the type for. This account is
 * represented by a @c uds_account_data_t and is created using
 * @c uds_account_data_create().
 * 
 * @return The type of the specified account, as a @c uds_account_type_t.
 */
uds_account_type_t uds_account_data_get_type(uds_account_data_t const *account);


/*
 * Functions to manipulate UDS inbox items and item data
 */

/**
 * @brief Create a handle for inbox item data
 * 
 * @details This handle is represented as a @c uds_inbox_item_data_t and is the
 * primary way of communicating with the BlackBerry Hub for changes and
 * inquiries for inbox item data. It includes all of the information about a
 * particular inbox item, and you pass this handle as a parameter to
 * @c uds_item_added() and @c uds_item_updated() when you want to add or update
 * an inbox item in the BlackBerry Hub, respectively.
 * 
 * You also use this handle to specify the inbox item that you want to change
 * (using functions such as @c uds_inbox_item_data_set_source_id() and
 * @c uds_inbox_item_data_set_mime_type()) or retrieve information for (using
 * functions such as @c uds_inbox_item_data_get_source_id() and
 * @c uds_inbox_item_data_get_mime_type()).
 * 
 * @return A handle for inbox item data, as a @c uds_inbox_item_data_t.
 */
uds_inbox_item_data_t *uds_inbox_item_data_create();

/**
 * @brief Delete a handle for inbox item data
 * 
 * @details This function deletes the specified handle for inbox item data that
 * you created by calling @c uds_inbox_item_data_create().
 * 
 * @param inst The handle for inbox item data that you want to delete.
 */
void uds_inbox_item_data_destroy(uds_inbox_item_data_t *inst);

/**
 * @brief Set the account key for the specified inbox item data
 * 
 * @details The account key for an account is unique across the platform and
 * it identifies a particular user account on a device. You can obtain this
 * key by using the
 * <a href="http://developer.blackberry.com/native/reference/cascades/app_integration_account.html">PIM Accounts API</a>.
 * 
 * Based on the account key that you specify, the inbox item is added to the
 * associated account's tab in the BlackBerry Hub, as well as to the main view
 * of the BlackBerry Hub.
 * 
 * @param inbox_item The inbox item to set the account key for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param account_id The unique account key to set, as a @c uds_account_key_t.
 */
void uds_inbox_item_data_set_account_id(uds_inbox_item_data_t *inbox_item, uds_account_key_t account_id);

/**
 * @brief Set the source key for the specified inbox item data
 * 
 * @details When you add an inbox item to the BlackBerry Hub using
 * @c uds_item_added(), this item is assigned a unique source key. 
 * Typically, this key is unique per account and is used to represent the list
 * item that was added.
 * 
 * @param inbox_item The inbox item to set the source key for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param source_id The unique source key to set, as a @c uds_source_key_t.
 */
void uds_inbox_item_data_set_source_id(uds_inbox_item_data_t *inbox_item, uds_source_key_t source_id);

/**
 * @brief Set the server-side synchronization key for the specified inbox item
 * data
 * 
 * @param inbox_item The inbox item to set the synchronization key for. This
 * inbox item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param sync_id The unique synchronization key to set, as a @c uds_sync_key_t.
 */
void uds_inbox_item_data_set_sync_id(uds_inbox_item_data_t *inbox_item, uds_sync_key_t sync_id);

/**
 * @brief Set the category key for the specified inbox item data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. For example, a messaging account
 * might contain folders for different types of messages, and each folder is
 * considered a category. In this case, the folder ID would be considered the
 * category key.
 * 
 * @param inbox_item The inbox item to set the category key for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param category_id The unique category key to set, as a
 * @c uds_category_key_t.
 */
void uds_inbox_item_data_set_category_id(uds_inbox_item_data_t *inbox_item, uds_category_key_t category_id);

/**
 * @brief Set the name for the specified inbox item data
 * 
 * @details This name appears as the top-most line in the inbox list item when
 * the list item is displayed in the BlackBerry Hub. The string value that you
 * pass in as the @c name parameter must remain valid until the data is used
 * in a call to @c uds_item_added() or @c uds_item_updated().
 * 
 * @param inbox_item The inbox item to set the name for. This inbox item is
 * represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param name The name to set.
 */
void uds_inbox_item_data_set_name(uds_inbox_item_data_t *inbox_item, const char* name);

/**
 * @brief Set the description for the specified inbox item data
 * 
 * @details This description appears at the bottom of the inbox list item
 * (beneath the name) when the list item is displayed in the BlackBerry Hub.
 * This description could include more detailed information about the inbox
 * item, such as the subject of a message. The string value that you pass in as
 * the @c description parameter must remain valid until the data is used in a
 * call to @c uds_item_added() or @c uds_item_updated().
 * 
 * @param inbox_item The inbox item to set the description for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param description The description to set.
 */
void uds_inbox_item_data_set_description(uds_inbox_item_data_t *inbox_item, const char* description);

/**
 * @brief Set the icon for the specified inbox item data
 * 
 * @details This icon appears on the left side of the inbox list item
 * (beside the name and description) when the list item is displayed in the
 * BlackBerry Hub. The icon that you want to use must be located in the asset
 * directory that you specify when you call @c uds_register_client(). The icon
 * should also be 81x81 pixels and in PNG format.
 * 
 * The string value that you pass in as the @c icon parameter must remain valid
 * until the data is used in a call to @c uds_item_added() or
 * @c uds_item_updated().
 * 
 * @param inbox_item The inbox item to set the icon for. This inbox item is
 * represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param icon The file name of the icon to set.
 */
void uds_inbox_item_data_set_icon(uds_inbox_item_data_t *inbox_item, const char* icon);

/**
 * @brief Set the MIME type for the specified inbox item data
 * 
 * @details The MIME type indicates what type of content the inbox item
 * contains. For example, a message item in a messaging account might have a
 * MIME type of "plain/message" or "text/plain". The string value that you
 * pass in as the @c mime_type parameter must remain valid until the data is
 * used in a call to @c uds_item_added() or @c uds_item_updated().
 * 
 * @param inbox_item The inbox item to set the MIME type for. This inbox item is
 * represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param mime_type The MIME type to set.
 */
void uds_inbox_item_data_set_mime_type(uds_inbox_item_data_t *inbox_item, const char* mime_type);

/**
 * @brief Set the user data for the specified inbox item data
 * 
 * @details This data can be any information that you want to associate with
 * the inbox item. For example, if the inbox item is a notification that a
 * particular service or feature expires soon, you might include the expiry
 * date as user data. The string value that you pass in as the @c user_data
 * parameter must remain valid until the data is used in a call to
 * @c uds_item_added() or @c uds_item_updated().
 * 
 * @param inbox_item The inbox item to set the user data for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param user_data The user data to set.
 */
void uds_inbox_item_data_set_user_data(uds_inbox_item_data_t *inbox_item, const char* user_data);

/**
 * @brief Set the extended data for the specified inbox item data
 * 
 * @details This data can be any information that you want to associate with
 * the inbox item, and it's used to customize the inbox item when it's
 * displayed in the BlackBerry Hub. For example, in the BBM app, the delivery
 * status icon is a type of extended data and can be specified here.
 * 
 * The string value that you pass in as the
 * @c extended_data parameter must remain valid until the data is used in a
 * call to @c uds_item_added() or @c uds_item_updated().
 * 
 * @param inbox_item The inbox item to set the extended data for. This inbox
 * item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param extended_data The extended data to set.
 */
void uds_inbox_item_data_set_extended_data(uds_inbox_item_data_t *inbox_item, const char* extended_data);

/**
 * @brief Set the timestamp for the specified inbox item data
 * 
 * @details This timestamp determines the order that the inbox item is displayed
 * in the BlackBerry Hub. Items with the most recent timestamps are listed at
 * the top. This timestamp is in UNIX format, in milliseconds.
 *
 * @param inbox_item The inbox item to set the timestamp for. This inbox item is
 * represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param timestamp The timestamp to set.
 */
void uds_inbox_item_data_set_timestamp(uds_inbox_item_data_t *inbox_item, long long int timestamp);

/**
 * @brief Set the unread count for the specified inbox item data
 * 
 * @details The unread count lets you indicate when an inbox item should be
 * marked as unread. For a new unread item, this value will be greater than 0.
 * For example, if an inbox item represents a conversation, the unread count
 * indicates the number of unread messages in the conversation.
 *
 * @param inbox_item The inbox item to set the unread count for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param unread_count The unread count to set.
 */
void uds_inbox_item_data_set_unread_count(uds_inbox_item_data_t *inbox_item, int unread_count);

/**
 * @brief Set the total count for the specified inbox item data
 * 
 * @details The total count lets you indicate the total number of items in an
 * aggregated inbox item. For example, if an inbox item represents a
 * conversation, the total count indicates the total number of messages in the
 * conversation.
 * 
 * @param inbox_item The inbox item to set the total count for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param total_count The total count to set.
 */
void uds_inbox_item_data_set_total_count(uds_inbox_item_data_t *inbox_item, int total_count);

/**
 * @brief Set the perimeter for the specified inbox item data
 * 
 * @details For a hybrid account (that is, one that contains both personal and
 * work information and is represented by @c UDS_ACCOUNT_HYBRID in the
 * @c uds_account_status_t enumeration), you can use this function to indicate
 * whether any action that's invoked on this inbox item is invoked in the
 * enterprise perimeter (@c UDS_PERIMETER_ENTERPRISE) or the personal perimeter
 * (@c UDS_PERIMETER_PERSONAL).
 * 
 * @param inbox_item The inbox item to set the perimeter for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param perimeter The perimeter to set, as a @c uds_perimeter_type_t. If not
 * specified, the default value is @c UDS_PERIMETER_PERSONAL.
 */
void uds_inbox_item_data_set_perimeter(uds_inbox_item_data_t *inbox_item, uds_perimeter_type_t perimeter);

/**
 * @brief Set the context state for the specified inbox item data
 * 
 * @details The context state is used to populate context-specific actions that
 * you register using @c uds_register_item_context_action(). Each inbox item
 * action includes a context mask, which is a bitmask state that uses a bit
 * for each possible action that can be performed on an item. You set this
 * context mask by calling @c uds_item_action_data_set_context_mask(). When you
 * register an inbox item action using @c uds_register_item_context_action(),
 * the context mask is used to query the context state of the inbox item,
 * determining the actions that should appear in that item's context menu.
 * 
 * @param inbox_item The inbox item to set the context state for. This inbox
 * item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param context_state The context state to set.
 */
void uds_inbox_item_data_set_context_state(uds_inbox_item_data_t *inbox_item, unsigned int context_state);

/**
 * @brief Set whether notifications are enabled for the specified inbox item
 * 
 * @details You can use this function to suppress notifications about changes
 * to an inbox item. You might want to suppress notifications if you expect
 * a large number of changes to be made to the item in a short amount of time,
 * and you don't want to be alerted to the changes (for example, during
 * synchronization).
 * 
 * @param inbox_item The inbox item to set the notification state for. This
 * inbox item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * @param enabled If @c true a notification is triggered and sent to the
 * notification service when the inbox item changes, if @c false a notification
 * is not triggered.
 */
void uds_inbox_item_data_set_notification_state(uds_inbox_item_data_t *inbox_item, bool enabled);

/**
 * @brief Get the account key for the specified inbox item data
 * 
 * @details The account key for an account is unique across the platform and
 * it identifies a particular user account on a device.
 * 
 * @param inbox_item The inbox item to get the account key for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The account key of the specified inbox item, as a
 * @c uds_account_key_t.
 */
uds_account_key_t uds_inbox_item_data_get_account_id(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the source key for the inbox item data
 * 
 * @details When you add an inbox item to the BlackBerry Hub using
 * @c uds_item_added(), this item is assigned a unique source key. 
 * Typically, this key is unique per account and is used to represent the list
 * item that was added.
 * 
 * @param inbox_item The inbox item to get the source key for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 *
 * @return The source key of the specified inbox item, as a @c uds_source_key_t.
 */
uds_source_key_t uds_inbox_item_data_get_source_id(uds_inbox_item_data_t const  *inbox_item);


/**
 * @brief Get the server-side synchronization key for the specified inbox item
 * data
 * 
 * @param inbox_item The inbox item to get the synchronization key for. This
 * inbox item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The synchronization key of the specified inbox item, as a
 * @c uds_sync_key_t.
 */
uds_sync_key_t uds_inbox_item_data_get_sync_id(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the category key for the specified inbox item data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. For example, a messaging account
 * might contain folders for different types of messages, and each folder is
 * considered a category. In this case, the folder ID would be considered the
 * category key.
 * 
 * @param inbox_item The inbox item to get the category key for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The category key of the specified inbox item, as a
 * @c uds_category_key_t.
 */
uds_category_key_t uds_inbox_item_data_get_category_id(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the name for the specified inbox item data
 * 
 * @details This name appears as the top-most line in the inbox list item when
 * the list item is displayed in the BlackBerry Hub.
 * 
 * @param inbox_item The inbox item to get the name for. This inbox item is
 * represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The name of the specified inbox item.
 */
const char* uds_inbox_item_data_get_name(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the description for the specified inbox item data
 * 
 * @details This description appears at the bottom of the inbox list item
 * (beneath the name) when the list item is displayed in the BlackBerry Hub.
 * 
 * @param inbox_item The inbox item to get the description for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The description of the specified inbox item.
 */
const char* uds_inbox_item_data_get_description(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the file name of the icon for the specified inbox item data
 * 
 * @details This icon appears on the left side of the inbox list item
 * (beside the name and description) when the list item is displayed in the
 * BlackBerry Hub.
 * 
 * @param inbox_item The inbox item to get the file name of the icon for. This
 * inbox item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The file name of the icon for the specified inbox item.
 */
const char* uds_inbox_item_data_get_icon(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the MIME type for the specified inbox item data
 * 
 * @details The MIME type indicates what type of content the inbox item
 * contains. For example, a message item in a messaging account might have a
 * MIME type of "plain/message" or "text/plain".
 * 
 * @param inbox_item The inbox item to get the MIME type for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The MIME type of the specified inbox item.
 */
const char* uds_inbox_item_data_get_mime_type(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the user data for the specified inbox item data
 * 
 * @details This data can be any information that you want to associate with
 * the inbox item. For example, if the inbox item is a notification that a
 * particular service or feature expires soon, you might include the expiry
 * date as user data.
 * 
 * @param inbox_item The inbox item to get the user data for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The user data for the specified inbox item.
 */
const char* uds_inbox_item_data_get_user_data(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the extended data for the specified inbox item data
 * 
 * @details This data can be any information that you want to associate with
 * the inbox item, and it's used to customize the inbox item when it's
 * displayed in the BlackBerry Hub.
 * 
 * @param inbox_item The inbox item to get the extended data for. This inbox
 * item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The extended data for the specified inbox item.
 */
const char* uds_inbox_item_data_get_extended_data(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the timestamp for the specified inbox item data
 * 
 * @details This timestamp determines the order that the inbox item is displayed
 * in the BlackBerry Hub. Items with the most recent timestamps are listed at
 * the top. This timestamp is in Unix format, in milliseconds.
 * 
 * @param inbox_item The inbox item to get the timestamp for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The timestamp of the specified inbox item (in milliseconds).
 */
long long int uds_inbox_item_data_get_timestamp(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the unread count for the specified inbox item data
 * 
 * @details The unread count indicates when an inbox item should be marked as
 * unread. For a new unread item, this value will be greater than 0.
 * 
 * @param inbox_item The inbox item to get the unread count for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The unread count of the specified inbox item.
 */
int uds_inbox_item_data_get_unread_count(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the total count for the specified inbox item data
 * 
 * @details The total count indicates the total number of items in an
 * aggregated inbox item. For example, if an inbox item represents a
 * conversation, the total count indicates the total number of messages in the
 * conversation.
 * 
 * @param inbox_item The inbox item to get the total count for. This inbox item
 * is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The total count of the specified inbox item.
 */
int uds_inbox_item_data_get_total_count(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the perimeter for the specified inbox item data
 * 
 * @details For a hybrid account (that is, one that contains both personal and
 * work information and is represented by @c UDS_ACCOUNT_HYBRID in the
 * @c uds_account_status_t enumeration), the return value of this function
 * indicates whether any action that's invoked on this inbox item is invoked in
 * the enterprise perimeter (@c UDS_PERIMETER_ENTERPRISE) or the personal
 * perimeter (@c UDS_PERIMETER_PERSONAL).
 * 
 * @param inbox_item The inbox item to get the perimeter for. This inbox item is
 * represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The perimeter of the specified inbox item, as a
 * @c uds_perimeter_type_t.
 */
uds_perimeter_type_t uds_inbox_item_data_get_perimeter(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get the context state for the specified inbox item data
 * 
 * @details The context state is used to populate context-specific actions that
 * you register using @c uds_register_item_context_action(). For more
 * information, see @c uds_inbox_item_data_set_context_state().
 * 
 * @param inbox_item The inbox item to get the context state for. This inbox
 * item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return The context state of the specified inbox item.
 */
unsigned int uds_inbox_item_data_get_context_state(uds_inbox_item_data_t const  *inbox_item);

/**
 * @brief Get whether notifications are enabled for the specified inbox item
 * data
 * 
 * @details This function indicates whether to suppress notifications about
 * changes to an inbox item. You might want to suppress notifications if you
 * expect a large number of changes to be made to the item in a short amount of
 * time, and you don't want to be alerted to the changes (for example, during
 * synchronization).
 * 
 * @param inbox_item The inbox item to get the notification state for. This
 * inbox item is represented by a @c uds_inbox_item_data_t and is created using
 * @c uds_inbox_item_data_create().
 * 
 * @return @c true if a notification is triggered and sent to the notification
 * service when the inbox item changes, @c false otherwise.
 */
bool uds_inbox_item_data_get_notification_state(uds_inbox_item_data_t const  *inbox_item);


/*
 * Functions to manipulate UDS categories and category data
 */

/**
 * @brief Create a handle for category data
 * 
 * @details This handle is represented as a @c uds_category_data_t and is the
 * primary way of communicating with the BlackBerry Hub for category-related
 * changes and inquiries. It includes all of the information about a particular
 * category, and you pass this handle as a parameter to @c uds_category_added()
 * and @c uds_category_updated() when you want to add or update a category in
 * the BlackBerry Hub, respectively.
 * 
 * You also use this handle to specify the category that you want to change
 * (using functions such as @c uds_category_data_set_parent_id() and
 * @c uds_category_data_set_name()) or retrieve information for (using functions
 * such as @c uds_category_data_get_parent_id() and
 * @c uds_category_data_get_name()).
 * 
 * @return A handle for category data, as a @c uds_category_data_t.
 */
uds_category_data_t *uds_category_data_create();

/**
 * @brief Delete a handle for category data
 * 
 * @details This function deletes the specified handle for category data that
 * you created by calling @c uds_category_data_create().
 * 
 * @param inst The handle for category data that you want to delete.
 */
void uds_category_data_destroy(uds_category_data_t *inst);

/**
 * @brief Set the category key for the specified category data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. For example, a messaging account
 * might contain folders for different types of messages, and each folder is
 * considered a category. In this case, the folder ID would be considered the
 * category key.
 * 
 * @param category The category to set the category key for. This category is
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * @param id The unique category key to set, as a @c uds_category_key_t.
 */
void uds_category_data_set_id(uds_category_data_t *category, uds_category_key_t id);

/**
 * @brief Set the parent category key for the specified category data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. These categories can themselves
 * include categories within them, so the parent category key indicates the
 * category key of the parent of this category.
 * 
 * @param category The category to set the parent category key for. This
 * category is represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * @param parent_id The unique parent category key to set, as a
 * @c uds_category_key_t.
 */
void uds_category_data_set_parent_id(uds_category_data_t *category, uds_category_key_t parent_id);

/**
 * @brief Set the account key for the specified category data
 * 
 * @details The account key for an account is unique across the platform and
 * it identifies a particular user account on a device. You can obtain this
 * key by using the
 * <a href="http://developer.blackberry.com/native/reference/cascades/app_integration_account.html">PIM Accounts API</a>.
 * The account key that you specify determines the account that this category
 * appears in.
 * 
 * @param category The category to set the account key for. This category is
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * @param account_id The unique account key to set, as a @c uds_account_key_t.
 */
void uds_category_data_set_account_id(uds_category_data_t *category, uds_account_key_t account_id);

/**
 * @brief Set the type for the specified category data
 * 
 * @details This function sets the type for the specified category data. Note
 * that this value shouldn't be used for 3rd party applications.
 * 
 * @param category The category to set the type for. This category is
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * @param type The type to set.
 */
void uds_category_data_set_type(uds_category_data_t *category, int type);

/**
 * @brief Set the name for the specified category data
 * 
 * @details This name appears in the account view of the BlackBerry Hub for the
 * account where the category was added. The string value that you pass in as 
 * the @c name parameter must remain valid until the data is used in a call to
 * @c uds_category_added() or @c uds_category_updated().
 * 
 * @param category The category to set the name for. This category is 
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * @param name The name to set.
 */
void uds_category_data_set_name(uds_category_data_t *category, const char* name);

/**
 * @brief Get the category key for the specified category data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. For example, a messaging account
 * might contain folders for different types of messages, and each folder is
 * considered a category. In this case, the folder ID would be considered the
 * category key.
 * 
 * @param category The category to get the category key for. This category is
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * 
 * @return The category key of the specified category, as a
 * @c uds_category_key_t.
 */
uds_category_key_t uds_category_data_get_id(uds_category_data_t const *category);

/**
 * @brief Get the parent category key for the specified category data
 * 
 * @details An account on a device can include categories that are used to sort
 * or filter the information in the account. These categories can themselves
 * include categories within them, so the parent category key indicates the
 * category key of the parent of this category.
 * 
 * @param category The category to get the parent category key for. This
 * category is represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * 
 * @return The parent category key of the specified category, as a
 * @c uds_category_key_t.
 */
uds_category_key_t uds_category_data_get_parent_id(uds_category_data_t const *category);

/**
 * @brief Get the account key for the specified category data
 * 
 * @details The account key for an account is unique across the platform and
 * it identifies a particular user account on a device. You can obtain this
 * key by using the
 * <a href="http://developer.blackberry.com/native/reference/cascades/app_integration_account.html">PIM Accounts API</a>.
 * The account key determines the account that this category appears in.
 * 
 * @param category The category to get the account key for. This category is
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * 
 * @return The account key of the specified category, as a @c uds_account_key_t.
 */
uds_account_key_t uds_category_data_get_account_id(uds_category_data_t *category);

/**
 * @brief Get the type for the specified category data
 * 
 * @details Note that this value should not be used for 3rd party applications.
 * 
 * @param category The category to get the type for. This category is
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * 
 * @return The type of the specified category.
 */
int uds_category_data_get_type(uds_category_data_t const *category);

/**
 * @brief Get the name for the specified category data
 * 
 * @details This name appears in the account view of the BlackBerry Hub for the
 * account where the category was added.
 * 
 * @param category The category to get the name for. This category is 
 * represented by a @c uds_category_data_t and is created using
 * @c uds_category_data_create().
 * 
 * @return The name of the specified category.
 */
const char* uds_category_data_get_name(uds_category_data_t const *category);


/*
 * Functions to manipulate UDS account actions and account action data
 */

/**
 * @brief Create a handle for account action data
 * 
 * @details This handle is represented as a @c uds_account_action_data_t and is
 * the primary way of communicating with the BlackBerry Hub for changes and
 * inquiries related to account actions. It includes all of the information
 * about a particular account action, and you pass this handle as a parameter
 * to @c uds_register_account_action() and uds_update_account_action() when
 * you want to add or update an account action in the BlackBerry Hub,
 * respectively.
 * 
 * You also use this handle to specify the account action that you want to
 * change (using functions such as @c uds_account_action_data_set_action() and
 * @c uds_account_action_data_set_title()) or retrieve information for (using
 * functions such as @c uds_account_action_data_get_action() and
 * @c uds_account_action_data_get_title()).
 * 
 * @return A handle for account action data, as a @c uds_account_action_data_t.
 */
uds_account_action_data_t *uds_account_action_data_create();

/**
 * @brief Delete a handle for account action data
 * 
 * @details This function deletes the specified handle for account action data
 * that you created by calling @c uds_account_action_data_create().
 * 
 * @param inst The handle for account action data that you want to delete.
 */
void uds_account_action_data_destroy(uds_account_action_data_t *inst);

/**
 * @brief Set the invocation action for the specified account action data
 * 
 * @details When you add an account action to an account in the BlackBerry Hub,
 * you can specify the action by referring to one of the invocation framework
 * actions, such as "bb.action.STATUS" and "bb.action.CREATE". The string value
 * that you pass in as the @c action parameter must remain valid until the data
 * is used in a call to @c uds_register_account_action() or
 * @c uds_update_account_action().
 *
 * @param account_action The account action to set the invocation action for.
 * This account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * @param action The invocation action to set.
 */
void uds_account_action_data_set_action(uds_account_action_data_t *account_action, const char* action);

/**
 * @brief Set the target for the specified account action data
 * 
 * @details This target specifies the target application that's used to invoke
 * the account action. If you had previously specified a generic target for
 * all account actions using @c uds_account_data_set_target_name(), this
 * generic target is overridden by the specific target that you set using this
 * function.
 * 
 * The string value that you pass in as the @c invoke_target parameter must
 * remain valid until the data is used in a call to
 * @c uds_register_account_action() or @c uds_update_account_action().
 * 
 * @param account_action The account action to set the target for. This account
 * action is represented by a @c uds_account_action_data_t and is created using
 * @c uds_account_action_data_create().
 * @param invoke_target The target to set.
 */
void uds_account_action_data_set_target(uds_account_action_data_t *account_action, const char* invoke_target);

/**
 * @brief Set the target type for the specified account action data
 * 
 * @details This target type specifies what kind of target is used to invoke
 * the account action. For example, if the target is a "Compose" card, then the
 * target type is "card.composer". If the target is a service, then the target
 * type is "service". The string value that you pass in as the
 * @c target_type parameter must remain valid until the data is used in a call
 * to @c uds_register_account_action() or @c uds_update_account_action().
 * 
 * @param account_action The account action to set the target type for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * @param target_type The target type to set.
 */
void uds_account_action_data_set_type(uds_account_action_data_t *account_action, const char* target_type);

/**
 * @brief Set the title for the specified account action data
 * 
 * @details This title appears as the label of the action in the BlackBerry Hub,
 * wherever the action is placed (either on the action bar or in the overflow
 * menu). The string value that you pass in as the @c title parameter must
 * remain valid until the data is used in a call to
 * @c uds_register_account_action() or @c uds_update_account_action().
 * 
 * @param account_action The account action to set the title for. This account
 * action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * @param title The title to set.
 */
void uds_account_action_data_set_title(uds_account_action_data_t *account_action, const char* title);

/**
 * @brief Set the image source for the specified account action data
 * 
 * @details This image appears along with the title of the action in the
 * BlackBerry Hub, wherever the action is placed (either on the action bar or
 * in the overflow menu). The image that you want to use must be located in the
 * asset directory that you specify when you call @c uds_register_client(). The
 * image should also be 81x81 pixels and in PNG format.
 * 
 * The string value that you pass in as the @c image_source parameter must
 * remain valid until the data is used in a call to
 * @c uds_register_account_action() or @c uds_update_account_action().
 * 
 * @param account_action The account action to set the image source for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * @param image_source The file name of the image source to set.
 */
void uds_account_action_data_set_image_source(uds_account_action_data_t *account_action, const char* image_source);

/**
 * @brief Set the MIME type for the specified account action data
 * 
 * @details The MIME type indicates what type of content is associated with
 * the account action, such as "text/plain". You can specify any MIME type
 * that's supported by the invocation framework. The string value that you pass
 * in as the @c mime_type parameter must remain valid until the data is used in
 * a call to @c uds_register_account_action() or @c uds_update_account_action().
 * 
 * @param account_action The account action to set the MIME type for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * @param mime_type The MIME type to set.
 */
void uds_account_action_data_set_mime_type(uds_account_action_data_t *account_action, const char* mime_type);

/**
 * @brief Set the placement for the specified account action data
 * 
 * @details Each account action can be placed in different locations when in
 * account view in the BlackBerry Hub. Based on the placement that you specify, 
 * an account action appears on the action bar at the bottom of the screen,
 * in the overflow menu, or in both locations. Actions can also be placed in
 * fixed locations, such as the fixed location for "delete" actions.
 * 
 * @param account_action The account action to set the placement for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * @param placement The placement to set, as a @c uds_placement_type_t.
 */
void uds_account_action_data_set_placement(uds_account_action_data_t *account_action, uds_placement_type_t placement);

/**
 * @brief Get the invocation action for the specified account action data
 * 
 * @details When you add an account action to an account in the BlackBerry Hub,
 * you can specify the action by referring to one of the invocation framework
 * actions, such as "bb.action.STATUS" and "bb.action.CREATE".
 * 
 * @param account_action The account action to get the invocation action for.
 * This account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * 
 * @return The invocation action of the specified account action.
 */
const char* uds_account_action_data_get_action(uds_account_action_data_t const *account_action);

/**
 * @brief Get the target for the specified account action data
 * 
 * @details This target specifies the target application that's used to invoke
 * the account action.
 * 
 * @param account_action The account action to get the target for. This account
 * action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * 
 * @return The target for the specified account action.
 */
const char* uds_account_action_data_get_target(uds_account_action_data_t const *account_action);

/**
 * @brief Get the target type for the specified account action data
 * 
 * @details This target type specifies what kind of target is used to invoke
 * the account action. For example, if the target is a "Compose" card, then the
 * target type is "card.composer". If the target is a service, then the target
 * type is "service".
 * 
 * @param account_action The account action to get the target type for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * 
 * @return The target type for the specified account action.
 */
const char* uds_account_action_data_get_type(uds_account_action_data_t *account_action);

/**
 * @brief Get the title for the specified account action data
 * 
 * @details This title appears as the label of the action in the BlackBerry Hub,
 * wherever the action is placed (either on the action bar or in the overflow
 * menu).
 * 
 * @param account_action The account action to get the title for. This account
 * action is represented by a @c uds_account_action_data_t and is created using
 * @c uds_account_action_data_create().
 * 
 * @return The title of the specified account action.
 */
const char* uds_account_action_data_get_title(uds_account_action_data_t const *account_action);

/**
 * @brief Get the image source for the specified account action data
 * 
 * @details This image appears along with the title of the action in the
 * BlackBerry Hub, wherever the action is placed (either on the action bar or
 * in the overflow menu).
 * 
 * @param account_action The account action to get the image source for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * 
 * @return The file name to the image source of the specified account action.
 */
const char* uds_account_action_data_get_image_source(uds_account_action_data_t *account_action);

/**
 * @brief Get the MIME type for the specified account action data
 * 
 * @details The MIME type indicates what type of content is associated with
 * the account action, such as "text/plain".
 * 
 * @param account_action The account action to get the MIME type for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * 
 * @return The MIME type of the specified account action.
 */
const char* uds_account_action_data_get_mime_type(uds_account_action_data_t const *account_action);

/**
 * @brief Get the placement for the specified account action data
 * 
 * @details Each account action can be placed in different locations when in
 * account view in the BlackBerry Hub. Based on the placement that you specify, 
 * an account action will appear on the action bar at the bottom of the screen,
 * in the overflow menu, or in both locations. Actions can also be placed in
 * fixed locations, such as the fixed location for "delete" actions.
 * 
 * @param account_action The account action to get the placement for. This
 * account action is represented by a @c uds_account_action_data_t and is
 * created using @c uds_account_action_data_create().
 * 
 * @return The placement of the specified account action.
 */
uds_placement_type_t uds_account_action_data_get_placement(uds_account_action_data_t *account_action);


/*
 * Functions to manipulate UDS inbox item actions and inbox item action data
 */

/**
 * @brief Create a handle for item action data
 * 
 * @details This handle is represented as a @c uds_item_action_data_t and is the
 * primary way of communicating with the BlackBerry Hub for changes and
 * inquiries related to inbox item actions. It includes all of the information
 * about a particular item action, and you pass this handle as a parameter to
 * @c uds_register_item_context_action() and
 * @c uds_update_item_context_action() when you want to add or update an item
 * action in the BlackBerry Hub, respectively.
 * 
 * You also use this handle to specify the item action that you want to change
 * (using functions such as @c uds_item_action_data_set_action() and
 * @c uds_item_action_data_set_title()) or retrieve information for (using
 * functions such as @c uds_item_action_data_set_action() and
 * @c uds_item_action_data_get_title()).
 *
 * @return A handle for item action data, as a @c uds_item_action_data_t.
 */
uds_item_action_data_t *uds_item_action_data_create();

/**
 * @brief Delete a handle for item action data
 * 
 * @details This function deletes the specified handle for item action data that
 * you created by calling @c uds_item_action_data_create().
 * 
 * @param inst The handle for item action data that you want to delete.
 */
void uds_item_action_data_destroy(uds_item_action_data_t *inst);

/**
 * @brief Set the invocation action for the specified item action data
 * 
 * @details When you register an item action in the BlackBerry Hub, you can
 * specify the action by referring to one of the invocation framework
 * actions, such as "bb.action.ACCEPT" and "bb.action.MARKREAD". The string
 * value that you pass in as the @c action parameter must remain valid until the
 * data is used in a call to @c uds_register_item_action() or
 * @c uds_update_item_action().
 * 
 * @param item_action The item action to set the invocation action for. This
 * item action is represented by a @c uds_item_action_data_t and is created
 * using @c uds_item_action_data_create().
 * @param action The invocation action to set.
 */
void uds_item_action_data_set_action(uds_item_action_data_t *item_action, const char* action);

/**
 * @brief Set the target for the specified item action data
 * 
 * @details This target specifies the target application that's used to invoke
 * the item action. The string value that you pass in as the @c invokeTarget
 * parameter must remain valid until the data is used in a call to
 * @c uds_register_item_action() or @c uds_update_item_action().
 *
 * @param item_action The item action to set the target for. This item action
 * is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param invokeTarget The target to set.
 */
void uds_item_action_data_set_target(uds_item_action_data_t *item_action, const char* invokeTarget);

/**
 * @brief Set the target type for the specified item action data
 * 
 * @details This target type specifies what kind of target is used to invoke
 * the item action. For example, if the target is a "Compose" card, then the
 * target type is "card.composer". If the target is a service, then the target
 * type is "service". The string value that you pass in as the
 * @c targetType parameter must remain valid until the data is used in a call
 * to @c uds_register_item_action() or @c uds_update_item_action().
 *
 * @param item_action The item action to set the target type for. This item
 * action is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param targetType The target type to set.
 */
void uds_item_action_data_set_type(uds_item_action_data_t *item_action, const char* targetType);

/**
 * @brief Set the title for the specified item action data
 * 
 * @details This title appears as the label of the action on the context menu
 * when a user presses and holds the associated inbox item in the BlackBerry
 * Hub. The string value that you pass in as the @c title parameter must remain
 * valid until the data is used in a call to @c uds_register_item_action() or
 * @c uds_update_item_action().
 * 
 * @param item_action The item action to set the title for. This item action is
 * represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param title The title to set.
 */
void uds_item_action_data_set_title(uds_item_action_data_t *item_action, const char* title);

/**
 * @brief Set the image source for the specified item action data
 * 
 * @details This image appears along with the title in the context menu when a
 * user presses and holds the associated inbox item in the BlackBerry Hub. The
 * image that you want to use must be located in the asset directory that you
 * specify when you call @c uds_register_client(). The image should also be
 * 81x81 pixels and in PNG format.
 * 
 * The string value that you pass in as the @c imageSource parameter must remain
 * valid until the data is used in a call to @c uds_register_item_action() or
 * @c uds_update_item_action().
 * 
 * @param item_action The item action to set the image source for. This item
 * action is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param imageSource The file name of the image source to set.
 */
void uds_item_action_data_set_image_source(uds_item_action_data_t *item_action, const char* imageSource);

/**
 * @brief Set the MIME type for the specified item action data
 * 
 * @details The MIME type indicates what type of content is associated with the
 * item action, such as "text/plain". You can specify any MIME type that's
 * supported by the invocation framework. The string value that you pass in as
 * the @c mime_type parameter must remain valid until the data is used in a call
 * to @c uds_register_item_action() or @c uds_update_item_action().
 * 
 * @param item_action The item action to set the MIME type for. This item action
 * is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param mime_type The MIME type to set.
 */
void uds_item_action_data_set_mime_type(uds_item_action_data_t *item_action, const char* mime_type);

/**
 * @brief Set the placement for the specified item action data
 * 
 * @details Each item action can be placed in different locations when in
 * account view in the BlackBerry Hub. Based on the placement that you specify, 
 * an item action will appear in the general area of the context menu, or in
 * a specific fixed location in the context menu (such as the fixed location for
 * "delete" actions). Item actions can't be placed on the action bar, so if you
 * specify the placement as @c UDS_PLACEMENT_BAR, this placement is ignored.
 * 
 * @param item_action The item action to set the placement for. This item action
 * is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param placement The placement to set, as a @c uds_placement_type_t.
 */
void uds_item_action_data_set_placement(uds_item_action_data_t *item_action, uds_placement_type_t placement);

/**
 * @brief Set the context mask for the specified item action data
 * 
 * @details This context mask is a bitmask state that's used to populate
 * item-specific actions. You can designate a bit for each possible action that
 * can be performed on an item (such as "read", "mark as unread", and so on).
 * Then, when you register item-specific actions using
 * @c uds_register_item_context_action(), you specify a mask that's used to
 * query the bit state of the item's context state and populate the context
 * menu with the appropriate items.
 * 
 * @param item_action The item action to set the context mask for. This item
 * action is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @param mask The context mask to set.
 */
void uds_item_action_data_set_context_mask(uds_item_action_data_t *item_action, unsigned int mask);

/**
 * @brief Get the invocation action for the specified item action data
 * 
 * @details When you register an item action in the BlackBerry Hub, you can
 * specify the action by referring to one of the invocation framework
 * actions, such as "bb.action.ACCEPT" and "bb.action.MARKREAD".
 * 
 * @param item_action The item action to get the invocation action for. This
 * item action is represented by a @c uds_item_action_data_t and is created
 * using @c uds_item_action_data_create().
 * 
 * @return The invocation action of the specified item action.
 */
const char* uds_item_action_data_get_action(uds_item_action_data_t const *item_action);

/**
 * @brief Get the target for the specified item action data
 * 
 * @details This target specifies the target application that's used to invoke
 * the item action.
 * 
 * @param item_action The item action to get the target for. This item action
 * is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * 
 * @return The target of the specified item action.
 */
const char* uds_item_action_data_get_target(uds_item_action_data_t const *item_action);

/**
 * @brief Get the target type for the specified item action data
 * 
 * @details This target type specifies what kind of target is used to invoke
 * the item action. For example, if the target is a "Compose" card, then the
 * target type is "card.composer". If the target is a service, then the target
 * type is "service".
 * 
 * @param item_action The item action to get the target type for. This item
 * action is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * 
 * @return The target type of the specified item action.
 */
const char* uds_item_action_data_get_type(uds_item_action_data_t const *item_action);

/**
 * @brief Get the title for the specified item action data
 * 
 * @details This title appears as the label of the action on the context menu
 * when a user presses and holds the associated inbox item in the BlackBerry
 * Hub.
 * 
 * @param item_action The item action to get the title for. This item action is
 * represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * 
 * @return The title of the specified item action.
 */
const char* uds_item_action_data_get_title(uds_item_action_data_t const *item_action);

/**
 * @brief Get the image source for the specified item action data
 * 
 * @details This image appears along with the title in the context menu when a
 * user presses and holds the associated inbox item in the BlackBerry Hub.
 * 
 * @param item_action The item action to get the image source for. This item
 * action is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * 
 * @return The file name of the image source for the specified item action.
 */
const char* uds_item_action_data_get_image_source(uds_item_action_data_t const *item_action);

/**
 * @brief Get the MIME type for the specified item action data
 * 
 * @details The MIME type indicates what type of content is associated with the
 * item action, such as "text/plain".
 * 
 * @param item_action The item action to get the MIME type for. This item action
 * is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * 
 * @return The MIME type of the specified item action.
 */
const char* uds_item_action_data_get_mime_type(uds_item_action_data_t const *item_action);

/**
 * @brief Get the placement for the specified item action data
 * 
 * @details Each item action can be placed in different locations when in
 * account view in the BlackBerry Hub. Based on the placement that you specify, 
 * an item action will appear on the action bar at the bottom of the screen,
 * in the overflow menu, or in both locations. Actions can also be placed in
 * fixed locations, such as the fixed location for "delete" actions.
 * 
 * @param item_action The item action to get the placement for. This item action
 * is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * 
 * @return The placement of the specified item action, as a
 * @c uds_placement_type_t.
 */
uds_placement_type_t uds_item_action_data_get_placement(uds_item_action_data_t const *item_action);

/**
 * @brief Get the context mask for the specified item action data
 * 
 * @details This context mask is a bitmask state that's used to populate
 * item-specific actions. You can designate a bit for each possible action that
 * can be performed on an item (such as "read", "mark as unread", and so on).
 * Then, when you register item-specific actions using
 * @c uds_register_item_context_action(), you specify a mask that's used to
 * query the bit state of the item's context state and populate the context
 * menu with the appropriate items.
 * 
 * @param item_action The item action to get the context mask for. This item
 * action is represented by a @c uds_item_action_data_t and is created using
 * @c uds_item_action_data_create().
 * @return The context mask of the specified item action.
 */
unsigned int uds_item_action_data_get_context_mask(uds_item_action_data_t const *item_action);


/*
 * Functions to interact with the BlackBerry Hub, such as initialization and
 * registration functions.
 */

/**
 * @brief Initialize and open a connection to the BlackBerry Hub
 * 
 * @details This function initializes the UDS library and establishes a
 * connection to the BlackBerry Hub so that your app can start adding and
 * manipulating data. This function should be the first UDS function that your
 * app calls.
 * 
 * You can use the library in either asynchronous mode or synchronous mode,
 * which is specified by using the @c async parameter. In asynchronous mode, all
 * function calls return immediately after sending their associated command to
 * the server. The functions don't wait for a response after they send their
 * commands. Your app must call @c uds_wait_for_response() on a separate thread,
 * which blocks until there is a response from the server or a specified timeout
 * period has elapsed. Then, when a response is received, your app can call
 * @c uds_get_response() to retrieve the response.
 * 
 * In synchronous mode, function calls block until they receive a response from
 * the server. The functions return either @c UDS_SUCCESS if the command was
 * successful, or a non-zero error code if it was unsuccessful. The possible
 * error codes are described in @c uds_error_code_t.
 * 
 * @param pHandle The handle that's used to communicate with the BlackBerry
 * Hub. Your app must allocate a @c uds_context_t and provide a valid pointer to
 * it as this parameter. If @c uds_init() completes successfully (that is, it
 * returns @c UDS_SUCCESS), the @c uds_context_t that you passed in is filled by
 * the library with a valid handle.
 * @param async If @c true the library runs in asynchronous mode, if @c false
 * the library runs in synchronous mode.
 *
 * @return @c UDS_SUCCESS if the library was initialized successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_init(uds_context_t* pHandle, bool async);

/**
 * @brief Close the connection to the BlackBerry Hub
 * 
 * @details This function closes the connection to the BlackBerry Hub and
 * releases all of the resources that were allocated in the specified handle.
 * This function should be the last UDS function that your app calls, after
 * your app is finished manipulating data in the BlackBerry Hub. After you call
 * this function, you can no longer use the specified handle to communicate with
 * the BlackBerry Hub.
 * 
 * @param pHandle The handle that's used to communicate with the BlackBerry Hub
 * and whose connection you want to close and resources you want to release.
 *
 * @return @c UDS_SUCCESS if the connection was closed and resources were freed
 * successfully, or a non-zero error code on failure. See @c uds_error_code_t
 * or errno.h for details.
 */
int uds_close(uds_context_t* pHandle);

/**
 * @brief Register your app as a client entity with the BlackBerry Hub
 * 
 * @details This function identifies your app to the BlackBerry Hub and
 * registers it as a client entity, which means that your app is allowed to 
 * add and manipulate BlackBerry Hub data. When your app registers using this
 * function, you need to provide a service URL to identify your app, a library
 * path that specifies any modules that must be loaded by the BlackBerry Hub,
 * and a relative path to any assets that your data uses, such as images or
 * icons.
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pServiceURL A uniquely identified service URL to be registered with
 * the BlackBerry Hub.
 * @param pLibPath The library path of any module that must be loaded by the
 * BlackBerry Hub.
 * @param pAssetPath The relative path of any assets that your data uses, such
 * as images or icons.
 *
 * @return @c UDS_SUCCESS if the registration was successful, or a non-zero
 * error code on failure. See @c uds_error_code_t or errno.h for details.
 */
int uds_register_client(uds_context_t handle, const char* pServiceURL, const char* pLibPath, const char* pAssetPath);

/**
 * @brief Unregister your app as a client entity with the BlackBerry Hub
 * 
 * @details This function unregisters your app with the BlackBerry Hub, after
 * which your app is no longer eligible to add and manipulate BlackBerry Hub
 * data.
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if your app was unregistered successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_unregister_client(uds_context_t handle);

/**
 * @brief Add the specified account to the BlackBerry Hub
 *
 * @details This function adds an account to the BlackBerry Hub. If the addition
 * is successful (that is, this function returns @c UDS_SUCCESS), a unique icon
 * representing the added account appears in the BlackBerry Hub.
 * 
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pAccount The account to add. This account is represented as a
 * @c uds_account_data_t and contains all of the information that's required to
 * register and display the account in the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if the account was added successfully, or a non-zero
 * error code on failure. See @c uds_error_code_t or errno.h for details.
 */
int uds_account_added(uds_context_t handle, uds_account_data_t* pAccount);

/**
 * @brief Update an existing account in the BlackBerry Hub
 * 
 * @details This function updates the information in an account that's already
 * been added to the BlackBerry Hub using @c uds_account_added().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pAccount The existing account to update. This account is represented
 * as a @c uds_account_data_t and contains all of the information that's
 * required to register and display the account in the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if the account was updated successfully, or a non-zero
 * error code on failure. See @c uds_error_code_t or errno.h for details.
 */
int uds_account_updated(uds_context_t handle, uds_account_data_t* pAccount);

/**
 * @brief Remove an existing account from the BlackBerry Hub
 * 
 * @details This function removes an account that was added to the BlackBerry
 * Hub using @c uds_account_added().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the existing account to remove, as a
 * @c uds_account_key_t.
 *
 * @return @c UDS_SUCCESS if the account was removed successfully, or a non-zero
 * error code on failure. See @c uds_error_code_t or errno.h for details.
 */
int uds_account_removed(uds_context_t handle, uds_account_key_t accountId);

/**
 * @brief Add an inbox list item to the BlackBerry Hub
 * 
 * @details This function adds an inbox list item that's associated with an
 * existing account to the BlackBerry Hub. If the inbox list item is added
 * successfully (that is, this function returns @c UDS_SUCCESS), the item
 * appears in the BlackBerry Hub under the associated account, and within the
 * appropriate category (if a category was specified for the item).
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pItem The inbox list item to add. This item is represented as a
 * @c uds_inbox_item_data_t and contains all of the information that's required
 * to display the item in the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if the inbox list item was added successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_item_added(uds_context_t handle, const uds_inbox_item_data_t* pItem);

/**
 * @brief Update an existing inbox list item in the BlackBerry Hub
 * 
 * @details This function updates the information in an inbox list item that's
 * already been added to the BlackBerry Hub using @c uds_item_added().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pItem The inbox list item to update. This item is represented as a
 * @c uds_inbox_item_data_t and contains all of the information that's required
 * to display the item in the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if the inbox list item was updated successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_item_updated(uds_context_t handle, const uds_inbox_item_data_t* pItem);

/**
 * @brief Remove an existing inbox list item from the BlackBerry Hub
 * 
 * @details This function removes an inbox list item that was added to the 
 * BlackBerry Hub using @c uds_item_added().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the account that's associated with the
 * inbox list item to remove, as a @c uds_account_key_t.
 * @param pSourceId The unique source key of the inbox list item to remove, as
 * a @c uds_source_key_t.
 *
 * @return @c UDS_SUCCESS if the inbox list item was removed successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_item_removed(uds_context_t handle, uds_account_key_t accountId, const uds_source_key_t pSourceId);

/**
 * @brief Remove all inbox list items that have the specified MIME type from the
 * BlackBerry Hub
 *
 * @details This function removes all inbox list items that use a particular
 * MIME type from the BlackBerry Hub. For example, you could use this function
 * to remove all inbox list items that have a MIME type of "text/plain".
 * 
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the account to remove the inbox list
 * items from, as a @c uds_account_key_t.
 * @param mimetype The MIME type of the inbox list items to remove.
 *
 * @return @c UDS_SUCCESS if the inbox list items with the specified MIME type
 * were removed successfully, or a non-zero error code on failure. See
 * @c uds_error_code_t or errno.h for details.
 */
int uds_items_removed_mimetype(uds_context_t handle, uds_account_key_t accountId, const char *mimetype);

/**
 * @brief Add a category to an existing account in the BlackBerry Hub
 * 
 * @details This function adds a category to an account that's already been
 * registered with the BlackBerry Hub using @c uds_account_added(). To specify
 * the account that you want to add the category to, you can call
 * @c uds_category_data_set_account_id().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pCategory The category to add. This category is represented as a
 * @c uds_category_data_t and contains all of the information that's required
 * to display the category in the appropriate account.
 *
 * @return @c UDS_SUCCESS if the category was added successfully, or a non-zero
 * error code on failure. See @c uds_error_code_t or errno.h for details.
 */
int uds_category_added(uds_context_t handle, const uds_category_data_t* pCategory);

/**
 * @brief Update an existing category in the BlackBerry Hub
 * 
 * @details This function updates the information in a category that's already
 * been added to the BlackBerry Hub using @c uds_category_added().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param pCategory The category to update.  This category is represented as a
 * @c uds_category_data_t and contains all of the information that's required
 * to display the category in the appropriate account.
 *
 * @return @c UDS_SUCCESS if the category was updated successfuly, or a non-zero
 * error code on failure. See @c uds_error_code_t or errno.h for details.
 */
int uds_category_updated(uds_context_t handle, const uds_category_data_t* pCategory);

/**
 * @brief Remove an existing category from the BlackBerry Hub
 * 
 * @details This function removes a category that was added to the BlackBerry
 * Hub using @c uds_category_added().
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the account to remove the category from,
 * as a @c uds_account_key_t.
 * @param categoryId The unique category key of the category to remove, as a
 * @c uds_category_key_t.
 *
 * @return @c UDS_SUCCESS if the category was removed successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_category_removed(uds_context_t handle, uds_account_key_t accountId, uds_category_key_t categoryId);

/**
 * @brief Wait and block until there is a response from the server or until the
 * specified timeout period elapses
 *
 * @details This function blocks the current thread and waits for a response
 * from the server about the results of the previous command. You can specify
 * a timeout period, which is the maximum amount of time to block. If a response
 * is received (that is, this function returns @c true), you can call
 * @c uds_get_response() to retrieve the response.
 * 
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param timeout The timeout period (in milliseconds).
 *
 * @return @c true if a response is received from the server, @c false if the
 * timeout period elapses.
 */
bool uds_wait_for_response(uds_context_t handle, unsigned long timeout);

/**
 * @brief Read and parse the response from the server for the previously
 * executed command
 * 
 * @details This function reads the response from the previous command and
 * parses it. You call this function after you call @c uds_wait_for_response()
 * and that function returns @c true (indicating that a response is available).
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if the response was read and parsed successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_get_response(uds_context_t handle);

/**
 * @brief Get the service ID that's associated with your app's registration with
 * the BlackBerry Hub
 * 
 * @details This function returns the service ID that was assigned when your
 * app registered with the BlackBerry Hub using @c uds_register_client(). If
 * you're using the library in synchronous mode, you should have received a
 * return value of @c UDS_SUCCESS from @c uds_register_client() before you call
 * this function. If you're using the library in asynchronous mode, you should
 * have received a return value of @c true from @c uds_get_response() (after
 * calling @c uds_register_client()) before you call this function.
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 *
 * @return The service ID that's associated with your app's registration with
 * the BlackBerry Hub.
 */
int uds_get_service_id(uds_context_t handle);

/**
 * @brief Get the service state that's associated with your app's registration
 * with the BlackBerry Hub
 * 
 * @details This function returns the service state that was assigned when your
 * app registered with the BlackBerry Hub using @c uds_register_client(), as
 * one of the values in @c uds_registration_code_t, such as
 * @c UDS_REGISTRATION_NEW or @c UDS_REGISTRATION_EXISTS. If you're using the
 * library in synchronous mode, you should have received a return value of
 * @c UDS_SUCCESS from @c uds_register_client() before you call this function.
 * If you're using the library in asynchronous mode, you should have received a
 * return value of @c true from @c uds_get_response() (after calling
 * @c uds_register_client()) before you call this function.
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 *
 * @return The service status that's associated with your app's registration
 * with the BlackBerry Hub.
 */
int uds_get_service_status(uds_context_t handle);


/**
 * @brief Register an account action for an existing account that's registered
 * with the BlackBerry Hub
 * 
 * @details This function registers an account action for an existing account
 * that was added to the BlackBerry Hub using @c uds_account_added(). If the
 * account action is registered successfully (that is, this function returns
 * @c UDS_SUCCESS), the account action appears in the associated account view
 * in the BlackBerry Hub.
 *
 * Here's an example of how to create and populate an account action, and then
 * register the action with the BlackBerry Hub:
 *
 * @code
 * // The udsHandle variable below is the handle that your app obtains by
 * // calling uds_init()
 * int retVal = -1;
 * uds_account_action_data_t account_action = uds_account_action_data_create();
 * uds_account_action_data_set_action(account_action,"bb.action.STATUS");
 * uds_account_action_data_set_target(account_action,"UDSTestApp");
 * uds_account_action_data_set_type(account_action,"");
 * uds_account_action_data_set_title(account_action,"Status");
 * uds_account_action_data_set_image_source(account_action,"ic_status.png");
 * uds_account_action_data_set_mime_type(account_action,"text/plain");
 * uds_account_action_data_set_placement(account_action,UDS_PLACEMENT_BAR);
 * if (UDS_SUCCESS!= (retVal = uds_register_account_action(udsHandle, 1 ,
 *                                                         account_action)))
 * {
 *     printf("uds_register_account_action failed with error %d\n", retVal);
 * }
 * @endcode
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the existing account to register the
 * account action for, as a @c uds_account_key_t.
 * @param pAccountAction The account action to register. This account action is
 * represented by a @c uds_account_action_data_t and contains all of the
 * information that's required to register and display the action in the
 * appropriate account view in the BlackBerry Hub.
 *
 * @return @c UDS_SUCCESS if the account action was registered successfully, or
 * a non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_register_account_action(uds_context_t handle, uds_account_key_t accountId, const uds_account_action_data_t* pAccountAction);


/**
 * @brief Update an existing account action that's registered with the
 * BlackBerry Hub
 * 
 * @details This function updates an existing account action that's already
 * been registered with the BlackBerry Hub using
 * @c uds_register_account_action(). You might want to update account actions
 * in response to certain events, such as locale changes.
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the existing account to update the
 * account action for, as a @c uds_account_key_t.
 * @param pAccountAction The account action to update. This account action is
 * represented by a @c uds_account_action_data_t and contains all of the
 * information that's required to register and display the action in the
 * appropriate account view in the BlackBerry Hub.
 * 
 * @return @c UDS_SUCCESS if the account action was updated successfully, or a
 * non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_update_account_action(uds_context_t handle, uds_account_key_t accountId, const uds_account_action_data_t* pAccountAction);


/**
 * @brief Register an item context action for an existing account that's
 * registered with the BlackBerry Hub
 * 
 * @details This function registers an item context action for an existing
 * account that was added to the BlackBerry Hub using @c uds_account_added().
 * If the item context action is registered successfully (that is, this function
 * returns @c UDS_SUCCESS), the data from the action populates the context menu
 * when an inbox list item is selected in the account view in the BlackBerry
 * Hub.
 * 
 * Here's an example of how to create and populate a globally defined item
 * context action, and then register the action with the BlackBerry Hub:
 * 
 * @code
 * typedef enum{
 *     ReadAction = 0x01<<0,
 *     UnreadReadAction = 0x01<<1,
 *     AcceptAction = 0x01<<2
 * }ActionState;
 * 
 * // The udsHandle variable below is the handle that your app obtains by
 * // calling uds_init()
 * int retVal = -1;
 * uds_item_action_data_t *item_action = uds_item_action_data_create();
 * uds_item_action_data_set_action(item_action,"bb.action.ACCEPT");
 * uds_item_action_data_set_target(item_action,"UDSTestApp");
 * uds_item_action_data_set_type(item_action,"service");
 * uds_item_action_data_set_title(item_action,"Accept Request");
 * uds_item_action_data_set_image_source(item_action,"uds_accept.png");
 * uds_item_action_data_set_mime_type(item_action,mime_type);
 * uds_item_action_data_set_placement(item_action,
 *         "application/vnd.blackberry.socialconnect.UDSTestApp.notification");
 *  uds_item_action_data_set_context_mask(item_action,AcceptAction);
 * if (UDS_SUCCESS!= (retVal = uds_register_item_context_action(udsHandle, 1 ,
 *                                                              item_action)))
 * {
 *   printf("uds_register_item_context_action failed with error %d\n", retVal);
 * }
 * @endcode
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the existing account to register the
 * item context action for, as a @c uds_account_key_t.
 * @param pItem The item context action to register. This item action is
 * represented by a @c uds_item_action_data_t and contains all of the
 * information that's required to display and invoke the action based on the
 * state of an inbox list item in the BlackBerry Hub.
 * 
 * @return @c UDS_SUCCESS if the item context action was registered
 * successfully, or a non-zero error code on failure. See @c uds_error_code_t or
 * errno.h for details.
 */
int uds_register_item_context_action(uds_context_t handle, uds_account_key_t accountId, const uds_item_action_data_t* pItem);

/**
 * @brief Update an existing item context action that's registered with the
 * BlackBerry Hub
 * 
 * @details This function updates an existing item context action that's
 * already been registered with the BlackBerry Hub using
 * @c uds_register_item_context_action(). You might want to update item context
 * actions in response to certain events, such as locale changes.
 *
 * @param handle The handle that's associated with your app's registration with
 * the BlackBerry Hub.
 * @param accountId The account key of the existing account to update the
 * item context action for, as a @c uds_account_key_t.
 * @param pItem The item context action to update. This item action is
 * represented by a @c uds_item_action_data_t and contains all of the
 * information that's required to display and invoke the action based on the
 * state of an inbox list item in the BlackBerry Hub.
 * 
 * @return @c UDS_SUCCESS if the item context action was updated successfully,
 * or a non-zero error code on failure. See @c uds_error_code_t or errno.h for
 * details.
 */
int uds_update_item_context_action(uds_context_t handle, uds_account_key_t accountId, const uds_item_action_data_t* pItem);


__END_DECLS

#endif /* UNIFIED_DATASOURCE_C_H_ */
