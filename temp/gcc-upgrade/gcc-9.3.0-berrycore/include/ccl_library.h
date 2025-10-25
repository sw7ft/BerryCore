/** \file ccl_library.h
 * Content Collection Library (CCL) helps RIM internal application developers to instrument their
 * applications by logging analytical and contextual information. 'ccl_library.h' provided the necessary
 * APIs for accessing CCL library.
 *
 * This example creates a ccl library and logging some standard and custom events.
 * @code
 * void try_ccl_library()
 *	{
 *	ccl_event_keys_t event = NULL;
 *	ccl_library_t ccl_lib = NULL;
 *
 *	ccl_lib = ccl_init("QNXTestApp", "1.0.001");
 *
 *	event = ccl_event_keys_create();
 *	ccl_event_keys_add(event, "eventPath", "app/mainmenu", 0);
 *	ccl_onapplication_start(ccl_lib, event);
 *	ccl_event_keys_delete(event);
 *
 *	ccl_onapplication_start(ccl_lib, NULL); // no additional event keys
 *
 *	event = ccl_event_keys_create();
 *	ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_PATH, "home/contactList", 0);
 *	ccl_event_keys_add(event, "Group", "BBM group", 0);
 *	ccl_event_keys_add(event, "Account Type", "Premium User", 0);
 *	ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_DESC, "New account added for premium user", 0);
 *	ccl_oncustom_event(ccl_lib, "onContactAdded", event);
 *	ccl_event_keys_delete(event);
 *
 *	ccl_shutdown(ccl_lib);
 *}
 * @endcode

 *  @date Created on: Sep 15, 2011
 *  @author     cjose
 */

#ifndef _CCL_LIBRARY_H_
#define _CCL_LIBRARY_H_

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif


#define CCL_DISABLE_CONTENT_COLLECTION				0
#define CCL_ENABLE_CONTENT_COLLECTION				1

///Error codes
#define CCL_SUCCESS							0
#define CCL_NOT_AVAILABLE					-1
#define CCL_NULL_PARAMETER_PASSED			-1
#define CCL_LIBRARY_NOT_INITIALIZED			-1
#define CCL_INITIALIZE_EVENT_KEYS_FAILED	-2
#define CCL_ILLEGAL_LIBRARY_SHUTDOWN		-2
#define CCL_ILLEGAL_CONSENT_STATE			-2
#define CCL_EVENT_DECORATOR_FAILED			-2
#define CCL_INVALID_PARAMETER_PASSED		-2
#define CCL_ADD_EVENT_NODE_FAILED			-3
#define CCL_DATA_COLLECTION_DISABLED		-3
#define CCL_NO_CONSENT						-4

#define CCL_INIT_EVENT							"CCL_INIT_EVENT"
#define CCL_EVENT_KEY_EVENT_PATH				"eventPath"
#define CCL_EVENT_KEY_EVENT_DESC				"eventDesc"
#define CCL_EVENT_KEY_EVENT_TYPE				"eventType"

#define CCL_EVENT_ATTRIBUTE_ACTIVITY_NAME		"activityName"
#define CCL_EVENT_ATTRIBUTE_AD_NAME				"adName"
#define CCL_EVENT_ATTRIBUTE_SEARCH_PHRASE		"searchPhrase"
#define CCL_EVENT_ATTRIBUTE_SEARCH_RESULT		"searchResult"
#define CCL_EVENT_ATTRIBUTE_CONVERSION_NAME		"conversionName"
#define CCL_EVENT_ATTRIBUTE_CONTENT_GROUP		"contentGroup"
#define CCL_EVENT_ATTRIBUTE_CORPORATE_LIABLE	"corporateLiable"

#define CCL_EVENT_PII                       0x1     // PII flag
#define CCL_EVENT_PII_PIN                   0x3     // PII flag for PINs

/// ccl_event_keys_t pointer holds the event key hashtable
typedef void* ccl_event_keys_t;
/// ccl_library_t pointer holds the ccl library
typedef void* ccl_library_t;


/**
 * Initializing Content Collection Library, this function must be called before calling any other event logging functions.
 * This will allow CCL library to prepares some initialization operations before any ccl_onXXX() operations. Use of any CCL
 * function without a successful invocation of ccl_init() will result in undefined behavior.
 *
 * An application may call ccl_init() more than once, but the same ccl_library_t instance will be returned always. An application
 * that calls ccl_init() should call ccl_shutdown() while exiting.
 *
 * @code
 * ccl_library_t ccl_lib = ccl_init("QNXTestApp", "1.0.001");
 * @endcode
 *
 * @param app_name CCL complaint application name, Application needs to use a CCL complaint name for logging events.
 * @param app_version application version
 * @return ccl_library_t CCL library pointer upon success, NULL otherwise.
 */
ccl_library_t  ccl_init(const char *app_name, const char *app_version);

/**
 * Shutdown Content Collection Library, this function must be called before exiting calling application.
 * All associated memory in the CCL library will be freed. You should not call any other CCL functions after this call
 * completes.
 *
 * @code
 * ccl_shutdown(ccl_lib);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @return int 0 if success, -1 if ccl_library_t is NULL
 */
int ccl_shutdown(ccl_library_t ccl_library);

/**
 * This API is deprecated and does a no-op.
 *
 * @returns -1 (CCL_NOT_AVAILABLE)
 *
 */
int ccl_set_ccl_enabled(ccl_library_t ccl_library, int enable_status);

/**
 * This API is used to get the CCL enable/disable status .
 *
 * @details Only returns the global state, including killswitch and perimeter status.
 *
 * @code
 * int ccl_enable_status = ccl_is_ccl_enabled(ccl_lib);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 *
 * @return int 0 if CCL is enabled (CCL_SUCCESS), -4 if CCL is disabled (CCL_NO_CONSENT) or -1 if ccl_library_t is NULL (CCL_NULL_PARAMETER_PASSED)
 *
 */
int ccl_is_ccl_enabled(ccl_library_t ccl_library);

/**
 * This event is deprecated as it is automatically handled by the agent.
 */
int ccl_onapplication_start(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * This event is deprecated as it is automatically handled by the agent.
 */
int ccl_onapplication_end(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * This event is deprecated as it is automatically handled by the agent.
 */
int ccl_onapplication_foreground(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * This event is deprecated as it is automatically handled by the agent.
 */
int ccl_onapplication_background(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * This event collects data related to application error. Calling application can use this API to instrument
 * various errors or exceptions  happening in application.
 *
 * @code
 * ccl_event_keys_t errorData = ccl_event_keys_create();
 * ccl_event_keys_add(errorData, CCL_EVENT_KEY_EVENT_PATH, "WeatherScreen/San Francisca");
 * ccl_event_keys_add(errorData, "errorMessage", "Invalid City");
 * ccl_onapplication_error(ccl_lib, errorData);
 * ccl_event_keys_delete(errorData);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @return int 0 if success, -1 if ccl_library_t is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onapplication_error(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * The onButtonClick method collects data when a user clicks an application button. Could also be used with touch based devices.
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @return int 0 if success, -1 if ccl_library_t is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onbutton_click(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * This event collects data when an application user searches within the application. It accepts both the search term and the result.
 *
 * @code
 * ccl_event_keys_t event = ccl_event_keys_create();
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_PATH, "/edit/reviews/reviewSearch");
 * ccl_event_keys_add(event, "searchKey", "hotels");
 * ccl_onsearch_event(ccl_lib, event, "Hyatt");
 * ccl_event_keys_delete(event);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @param search_phrase Specifies the search term submitted during an in-app search (Required)
 * @return int 0 if success, -1 if ccl_library_t/search_phrase is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onsearch_event(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys, const char* search_phrase);

/**
 * This event collects data when content such as a screen, article, or image is viewed.
 *
 * @code
 * ccl_event_keys_t tweet_data = ccl_event_keys_create();
 * ccl_event_keys_add(tweet_data, "from", "joshuatopolosky");
 * ccl_event_keys_add(tweet_data, "to", "futurepaul");
 * ccl_event_keys_add(tweet_data, "via", "Tweetie for Mac");
 * ccl_event_keys_add(tweet_data, "tinyurl", "http://bit.ly/gw3oOZ");
 * ccl_oncontent_view(ccl_lib, tweet_data);
 * ccl_event_keys_delete(tweet_data);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @return int 0 if success, -1 if ccl_library_t is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_oncontent_view(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys);

/**
 * This event collects data when an activity starts
 *
 * @code
 * ccl_event_keys_t event = ccl_event_keys_create();
 * ccl_event_keys_add(event, "podcastIdentifier", "ideacast: Your Organization energy");
 * ccl_onactivity_start(ccl_lib, event, "ideaCast");
 * ccl_event_keys_delete(event);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @param activity_name Name of the activity (Required)
 * @return int 0 if success, -1 if ccl_library_t/activity_name is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onactivity_start(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys, const char* activity_name);

/**
 * This event collects data when an activity ends
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @param activity_name Name of the activity (Required)
 * @return int 0 if success, -1 if ccl_library_t/activity_name is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onactivity_end(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys, const char* activity_name);

/**
 * This event collects data on the pause of the any activity.
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @param activity_name Name of the activity that was paused (Required)
 * @return int 0 if success, -1 if ccl_library_t/activity_name is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onactivity_pause(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys, const char* activity_name);

/**
 * This event collects data when an application user clicks an ad.
 *
 * @code
 * ccl_event_keys_t event = ccl_event_keys_create();
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_PATH, "/edit/reviews/reviewEdit");
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_DESC, "ClickAdBanner");
 * ccl_onadclick_event(ccl_lib, event, "3DGlassesAd");
 * ccl_event_keys_delete(event);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @param ad_name Specifies the name of the advertisement (Required)
 * @return int 0 if success, -1 if ccl_library_t/ad_name is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onadclick_event(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys, const char* ad_name);

/**
 * This event is used to collect data when a conversion event such as a purchase occurs.
 *
 * @code
 * ccl_event_keys_t event = ccl_event_keys_create();
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_PATH, "/edit/reviews/reviewSubmit");
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_DESC, "reviewRestaurants");
 * ccl_onconversion_event(ccl_lib, event, "ReviewAcceptedForConsideration");
 * ccl_event_keys_delete(event);
 * @endcode
 *
 * @param ccl_library_t CCL library pointer
 * @param ccl_event_keys_t CCL event key vector pointer
 * @param conversion_name Specifies the name used to identify a customer conversion.
 * @return int 0 if success, -1 if ccl_library_t is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_onconversion_event(ccl_library_t ccl_library, ccl_event_keys_t ccl_event_keys, const char* conversion_name);

/**
 * This event collects data related to various custom application events. Calling application can use this API to instrument
 * various events happening in application.
 *
 * @code
 * ccl_event_keys_t event = ccl_event_keys_create();
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_PATH, "home/contactList");
 * ccl_event_keys_add(event, "Group", "BBM group");
 * ccl_event_keys_add(event, "Account Type", "Premium User");
 * ccl_event_keys_add(event, CCL_EVENT_KEY_EVENT_DESC, "New account added for user");
 * ccl_oncustom_event(ccl_lib, "onContactAdded", event);
 * ccl_event_keys_delete(event);
 * @endcode
 *
 *
 * @param ccl_library_t CCL library pointer
 * @param event_name CCL event name
 * @param ccl_event_keys_t CCL event key vector pointer
 * @return int 0 if success, -1 if ccl_library_t is NULL, -2 if any memory error, -3 if event filtering enabled
 */
int ccl_oncustom_event(ccl_library_t ccl_library, const char* event_name, ccl_event_keys_t ccl_event_keys);

/**
 * This event collects data for corporate liable related events, bypassing the regular context collection checks for consent as well as
 * not auto scrubbing Personally Identifiable Information.
 *
 * @param ccl_library_t CCL library pointer
 * @param event_name CCL event name
 * @param ccl_event_keys_t CCL event key vector pointer
 * @return int 0 if success, -1 if ccl_library_t is NULL, -2 if any memory error
 */
int ccl_oncorporateliable_event(ccl_library_t ccl_library, const char* event_name, ccl_event_keys_t ccl_event_keys);

/**
 * Initializing CCL event vector, this function must be called before calling any other ccl_event_keys_XXX functions.
 *
 */
ccl_event_keys_t ccl_event_keys_create();

/**
 * This function will add the given key and value to CCL event vector. Neither the key nor the value can be NULL.
 *
 * @param ccl_event_keys CCL event key vector pointer
 * @param key CCL event key, this cannot be NULL. A shallow copy will be performed and caller has to free the memory allocated.
 * @param value CCL event value, this cannot be NULL.
 * @param isPii indicated whether the key value is personally identifying information e.g. PIN, Phone Number, Email etc.
 *        Set using the CCL_EVENT_PII flag.  PIN and other short values < 16 bytes should use CCL_EVENT_PII_PIN.
 * @return int 0 if success, -1 if any argument is NULL, -2 if any memory error, -3 if any internal error
 */
int ccl_event_keys_add(ccl_event_keys_t ccl_event_keys, const char* key, const char* value, short isPii);

/**
 * This function will add the given key and timestamp to CCL event vector.
 *
 * @param ccl_event_keys CCL event key vector pointer
 * @param key CCL event key, this cannot be NULL. A shallow copy will be performed and caller has to free the memory allocated.
 * @param timestamp UTC timestamp in seconds.
 * @return int 0 if success, -1 if any argument is NULL, -2 if any memory error, -3 if any internal error
 */
int ccl_event_keys_add_corporateliable_time(ccl_event_keys_t ccl_event_keys, const char* key, time_t timestamp);

/**
 * This function will clear the CCL event vector and releases all associated memory. Please note that key and value are shallow
 * copied and caller has to clean the memory for key and value.
 *
 * @param ccl_event_keys CCL event key vector pointer
 */
void ccl_event_keys_delete(ccl_event_keys_t ccl_event_keys);

/**
 * A utility function to print the values in CCL event key vector
 *
 * @param ccl_event_keys CCL event key vector pointer
 */
void ccl_event_keys_print(ccl_event_keys_t ccl_event_keys);

#ifdef _UNITTEST
char* ccl_event_keys_get_value(ccl_event_keys_t ccl_event, const char* key);
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_CCL_LIBRARY_H_
