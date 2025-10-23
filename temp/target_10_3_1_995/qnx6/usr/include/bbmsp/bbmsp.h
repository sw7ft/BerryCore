/**
 * @file bbmsp.h
 *
 * @brief Functions and structures for the BBM Social Platform.
 *
 * @details This file declares functions and structures that are used across the
 * entire BBM Social Platform library. You can access functions to register your
 * app with the BBM Social Platform, process @c bbmsp events, and get the
 * version of the BBM Social Platform library that your app is using.
 */

/**
 * @mainpage The BBM Social Platform
 * The BBM Social Platform (BBMSP) provides APIs that allow you to access the
 * social features and functionality of BlackBerry Messenger from within your
 * app. For example, you can:
 * <ul>
 * <li>Invite BBM contacts to download your app by accessing a user's BBM contact list.</li>
 * <li>Update a user's or a contact's BBM personal message, status, and avatar.</li>
 * <li>Add a customizable application box to a user's BBM profile to broadcast achievements or provide updates.</li>
 * </ul>
 * The BBM Social Platform library provides an interface to BBM features such
 * as:
 * <ul>
 * <li> BBM user profile
 * <li> Contact list
 * <li> Download invitations
 * <li> Application profile box
 * </ul>
 *
 */

#ifndef BBMSP_H_
#define BBMSP_H_


#ifndef BBMSP_API

/*!@cond PRIVATE
 * Hiding the definitions.
 */
#if defined(__GNUC__)
// Default visibility. Use this when deprecating to maintain
// binary-compatibility.
#   define BBMSP_API __attribute__ ((visibility ("default")))
// Deprecation warning.
#   define BBMSP_API_DEPRECATED    __attribute__ ((deprecated))
#else
#   define BBMSP_API
#   define BBMSP_API_DEPRECATED
#endif

//!@endcond PRIVATE

#endif

#include <sys/platform.h>
#include <bps/event.h>

__BEGIN_DECLS

/**
 * @brief The current version number of the BBM Social Platform.
 * @details The version number represented as an integer constant.
 * @since BlackBerry 10.0.0
 */
#define BBMSP_VERSION             (200)

/*!@cond PRIVATE
 * @brief Deprecated
 * @details The BBM Social Platform Version as a string.
 * @deprecated This is a deprecated definition. Do not use.
 *
 * @see BBMSP_VERSION
 * @since BlackBerry 10.0.0
 */
#define BBMSP_VERSION_STRING      ("1.0.0")
//!@endcond PRIVATE

/*
 * @brief Version 200 of the BBM Social Platform.
 * @details This is the second release of the BBM Social Platform for BlackBerry
 * 10.  
 * @since BlackBerry 10.2.0
 */
#define BBMSP_VERSION_200           (200)

/*
 * @brief Version 100 of the BBM Social Platform.
 * @details This is the first release of the BBM Social Platform for BlackBerry
 * 10. Release date: January, 2013. This is also the first release of the BBM
 * Social Platform running on BlackBerry Device Software version 5, BlackBerry
 * 6, and BlackBerry 7. Release date: October, 2011.
 * @since BlackBerry 10.0.0
 */
#define BBMSP_VERSION_100           (100)

/*
 * @brief Version 120 of the BBM Social Platform.
 * @details This is the first release of the BBM Social Platform, running on
 * BlackBerry Device Software version 5, BlackBerry 6, and BlackBerry 7. Release
 * date: November, 2011.
 * @since BlackBerry 10.0.0
 */
#define BBMSP_VERSION_120           (120)

/*
 * @brief Version 130 of the BBM Social Platform.
 * @details This is the first release of the BBM Social Platform, running on
 * BlackBerry Device Software version 5, BlackBerry 6, and BlackBerry 7. Release
 * date: February, 2012.
 * @since BlackBerry 10.0.0
 */
#define BBMSP_VERSION_130           (130)

/**
 * @brief Result codes that can be returned by a function.
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * @brief Indicates that a function has completed successfully.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SUCCESS = 0,

  /**
   * @brief Indicates that an operation will be completed asynchronously.
   *
   * @details An event is pushed when the operation completes successfully.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ASYNC = 1,

  /**
   * @brief Indicates that a function did not complete successfully.
   * @details When the @c errno value is set, its value indicates the reason for
   * the failure.
   * @since BlackBerry 10.0.0
   *
   */
  BBMSP_FAILURE = -1
} bbmsp_result_t;


/**
 * @brief A BBM Social Platform event.
 * @since BlackBerry 10.0.0
 */
typedef struct bbmsp_event_t bbmsp_event_t;

/**
 * @brief Retrieve the version number of the BBM Social Platform.
 *
 * @details Retrieves the version of the BBM Social Platform library
 * that your application is using. You can use the version number to check
 * whether your application is compatible with this version of the BBM Social
 * Platform.
 *
 * @return The version number of the BBM Social Platform library in the format
 * described in @c BBMSP_VERSION.
 *
 * @see BBMSP_VERSION, BBMSP_VERSION_STRING
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_get_version(void);

/**
 * @brief Listen for BPS events from the BBM Social Platform.
 *
 * @details Delivers BBM Social Platform events to your application using
 * the BPS event loop. Events will be posted to the currently active channel.
 *
 * @param flags The types of events to deliver. @c flags must be an integer. A
 * value of zero indicates that all events are requested. The meaning of
 * non-zero values is reserved for future use.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 *
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_request_events(int flags);

/**
 * @brief Retrieve the unique BPS domain ID for the BBM Social Platform.
 *
 * @details Each event in BPS is associated with a domain that
 * represents the service that generated the event (for example, contactlist or
 * userprofile). You can use @c %bbmsp_get_domain() to determine the service
 * (event domain) that generated a particular event.
 *
 * @return int The domain ID for the service.
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_get_domain(void);

/**
 * @brief Retrieve the event category for the BBM Social Platform event.
 *
 * @details In addition to being associated with a domain,
 * each event in BPS has a category that represents the specific type of event
 * that occurred, for example, an event associated with registration or the
 * user's profile.
 *
 * @param bps_event A pointer to the BPS event that contains the BBM Social
 * Platform event information.
 * @param category An updated pointer to the category of the @c bbmsp event.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 *
 * @see bbmsp_events.h, bbmsp_get_domain(), BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_event_get_category(bps_event_t* bps_event,
                         int* category);

/**
 * @brief Retrieve the type of the BBM Social Platform event.
 * @details An event handler uses the event domain and the event type to
 * determine what the event is.
 *
 * @param bps_event A pointer to the BPS event that contains the @c bbmsp event
 * information.
 * @param type An updated pointer to the type of @c bbmsp event.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 *
 * @see bbmsp_get_domain(), BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_event_get_type(bps_event_t* bps_event,
                                              int* type);

/**
 * @brief Retrieve the BBM Social Platform event.
 *
 * @param bps_event The BPS event that contains the @c bbmsp event information.
 * @param bbmsp_event Updated with a void pointer to the BBM Social Platform
 * event that can be cast to the appropriate type (if needed) based on
 * @c bbmsp_event_t.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 *
 * @see bbmsp_event_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_event_get(bps_event_t* bps_event,
                                         bbmsp_event_t** bbmsp_event);

/**
 * @brief Register your app with the BBM Social Platform.
 * @details A UUID is a unique, 128-bit, 36-character identifier that you
 * generate for your app using a UUID (or GUID) generator. The UUID string must conform to
 * the Microsoft 8-4-4-4-12 format (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx).
 * Valid characters consist of hexadecimal values in the ranges 0 to 9 and a to f.
 * <p>A progress registration dialog may appear in your application after you
 * invoke this function. The user will be able to cancel the registration by
 * dismissing the dialog. After registration is complete, a system toast might
 * appear to indicate to the user that your application is now connected
 * to BBM. If registration does not complete successfully, a system dialog
 * might appear informing the user about the reason for failure.</p>
 * <p>If permission to connect to BBM is not set up when registration starts, 
 * the user may decide to set up BBM. This action will cause registration to resume.</p>
 * <p>This is an asynchronous request. The response will be an event with
 * category @c BBMSP_REGISTRATION and event type @c
 * BBMSP_SP_EVENT_ACCESS_CHANGED.</p>
 *
 * @param uuid A pointer to your app's UUID. @c uuid must be a null-terminated
 * C-string, encoded as UTF-8.
 *
 * @return @c BBMSP_ASYNC if the request was sent successfully,
 * @c BBMSP_FAILURE otherwise.
 *
 * @see BBMSP_ASYNC, BBMSP_FAILURE, BBMSP_REGISTRATION and
 * BBMSP_SP_EVENT_ACCESS_CHANGED
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_register(const char* uuid);

/**
  * @brief Register your app with the BBM Social Platform.
  * @details A UUID is a unique, 128-bit, 36-character identifier that you
  * generate for your app using a UUID (or GUID) generator. The UUID string must conform to
  * the Microsoft 8-4-4-4-12 format (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx).
  * Valid characters consist of hexadecimal values in the ranges 0 to 9 and a to f.
  * <p>Registration takes place in "silent" mode so that the registration progress
  * dialog does not appear to the user after you invoke this function.
  * Once registration is complete, a system toast appears to indicate to
  * the user that your application is now connected to BBM. If registration
  * does not complete successfully, no system dialog is displayed to inform
  * the user about the reason for failure.</p>
  * <p>If permission to connect to BBM is not set up when registration starts, 
  * the user may decide to set up BBM. This action will cause registration to resume.</p>
  * <p>This is an asynchronous request. The response will be an event with
  * category @c BBMSP_REGISTRATION and event type @c BBMSP_SP_EVENT_ACCESS_CHANGED.</p>
  *
 *
 * @param uuid A pointer to your app's UUID. @c uuid must be a null-terminated
 * C-string, encoded as UTF-8.
 *
 * @return @c BBMSP_ASYNC if the request was sent successfully,
 * @c BBMSP_FAILURE otherwise.
 *
 * @see BBMSP_ASYNC, BBMSP_FAILURE, BBMSP_REGISTRATION and
 * BBMSP_SP_EVENT_ACCESS_CHANGED
 * @since BlackBerry 10.2.0
 */
BBMSP_API bbmsp_result_t bbmsp_register_silent(const char* const uuid);

__END_DECLS

#endif /* BBMSP_H_ */
