/**
 * @file bbmsp_context.h
 *
 * @brief Functions to determine your app's access status to the BBM Social
 * Platform, profile box permission, and BBM invite permission.
 *
 * @details Access to the BBM Social Platform APIs is controlled by the registration
 * process, during which a modal dialog is displayed inside your app to
 * inform the user of registration progress. @c bbmsp_access_error_codes_t
 * lists all the possible registration access status codes. Access to the BBM Social
 * Platform APIs is successful when the retistration status code is @c BBMSP_ACCESS_ALLOWED
 * and @c is_access_allowed() returns true.
 *
 * @copyright Copyright (C) Research In Motion Limited 2012. All rights reserved.
 */

#ifndef BBMSP_CONTEXT_H_
#define BBMSP_CONTEXT_H_

#include <sys/platform.h>

#include "bbmsp.h"

__BEGIN_DECLS

/**
 * @brief The access status codes that indicate whether your app can access the BBM
 * Social Platform.
 * @details Your app must be registered with the BBM Social Platform before you
 * can use any of its APIs. After you call @c bbmsp_request_events()to initialize the BBM
 * Social Platform, wait to receive an event with category @c BBMSP_REGISTRATION
 * and type @c BBMSP_SP_EVENT_ACCESS_CHANGED. This event will return the
 * current access status of your app. If the access status is
 * @c BBMSP_ACCESS_UNREGISTERED, call @c bbmsp_register() to register the app.
 * If the access status is @c BBMSP_ACCESS_ALLOWED, the app has successfully registered and
 * you can start using other BBM Social Platform APIs.
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * @brief Indicates that access to the BBM Social Platform is allowed and your app has successfully
   * registered.
   * @details Once registered, the app does not have to call @c bbmsp_register() again.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_ALLOWED = 0,

  /**
   * @brief The BBM Social Platform has not yet retrieved the access code for this
   * app.
   * @details Wait to receive an event with category @c BBMSP_REGISTRATION
   * and type @c BBMSP_SP_EVENT_ACCESS_CHANGED. This event will return the current access code.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_UNKNOWN = 1,

  /**
   * @brief Your app is not registered with the BBM Social Platform.
   * @details Call @c bbmsp_register() to start the registration process. You
   * cannot use the BBM Social Platform APIs until the app has successfully
   * registered.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_UNREGISTERED = 2,

  /**
   * @brief Your app has initiated the registration process and it is
   * currently in progress.
   * @details You do not yet have access to the BBM Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_PENDING = 3,

  /**
   * @brief Your app was blocked by the user.
   * @details Your app does not have access to the BBM Social Platform APIs.
   * The user can unblock the app through the global settings
   * for the app.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_BLOCKED_BY_USER = 4,

  /**
   * @brief Your app was blocked by RIM.
   * @details Your app does not have access to the BBM
   * Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_BLOCKED_BY_RIM = 5,

  /**
   * @brief A data connection could not be established to complete registration.
   * @details You can call @c bbmsp_register() again once a data connection has
   * been established. You do not yet have access to the BBM Social Platform
   * APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_NO_DATA_CONNECTION = 6,

  /**
   * @brief Your app could not register due to a general error.
   * @details You do not have access to the BBM Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_UNEXPECTED_ERROR = 7,

  /**
   * @brief Your app could not register because an invalid UUID was
   * provided.
   * @details Call @c bbmsp_register() with a valid UUID. You do not yet have
   * access to the BBM Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_INVALID_UUID = 8,

  /**
   * @brief Your app could not register due to a temporary error.
   * @detaisl Call @c bbmsp_register() at a later time. You do not have access to the BBM
   * Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_TEMPORARY_ERROR = 9,

  /**
   * @brief Your app has reached the maximum allowed users.
   * @details This limit
   * is not applied to apps that are downloaded from BlackBerry World.
   * You can submit your app to BlackBerry World to remove this limitation.
   * You do not have access to the BBM Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_MAX_DOWNLOADS_REACHED = 10,

  /**
   * @brief Your app's access to the BBM Social Platform has expired.
   * @details This limit is
   * not applied to apps that are downloaded from BlackBerry World.
   * You can submit your app to BlackBerry World to remove this limitation.
   * You do not have access to the BBM Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_EXPIRED = 11,

  /**
   * @brief The registration process has been cancelled by the user.
   * @details You do not have access to the BBM Social Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_CANCELLED_BY_USER = 12,

  /**
   * @brief Your app cannot register on this device because the maximum allowable
   * number of apps has been reached. You do not have access to the BBM Social
   * Platform APIs.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_MAX_APPS_REACHED = 13,

  /**
   * Your application does not have access to the BBM Social Platform because
   * BBM has been disabled. The user needs to follow the instructions specified
   * in the BBM application to re-enable BBM. Once BBM is re-enabled, your
   * application will receive a new access status.
   * @since BlackBerry 10.0.0
   */
  BBMSP_ACCESS_BLOCKED_BBM_DISABLED = 14,

  /**
  * Your app does not have access to the BBM Social Platform because
  * it is installed in the Work perimeter. To connect to BBM you must install your
  * app in the Personal perimeter.
  * @since BlackBerry 10.2
  */
  BBMSP_ACCESS_BLOCKED_ENTERPRISE_PERIMETER = 15

} bbmsp_access_error_codes_t;

/**
 * @brief Determine whether access to the BBM Social Platform is allowed.
 *
 * @details When you receive a @c BBMSP_REGISTRATION category event of type
 * @c BBMSP_SP_EVENT_ACCESS_CHANGED, you use this function to determine if your
 * app has access to the BBM Social Platform. If you receive a status of
 * @c BBMSP_ACCESS_ALLOWED, this function returns 1, 0 otherwise.
 *
 * @param event A pointer to the @c bbmsp event that was triggered when access
 * changed.
 *
 * @return int 1 if access is @c BBMSP_ACCESS_ALLOWED, 0 otherwise.
 * @since BlackBerry 10.0.0
 */
BBMSP_API int
bbmsp_event_access_changed_get_access_allowed(bbmsp_event_t* event);

/**
 * @brief Retrieve the status code that describes your app's access to
 * BBM Social Platform.
 *
 * @details When you receive a @c BBMSP_REGISTRATION category event of type
 * @c BBMSP_SP_EVENT_ACCESS_CHANGED, you use this function to determine your
 * access to the BBM Social Platform.
 *
 * @param event A pointer to the @c bbmsp event that was triggered when access
 * changed.
 *
 * @return The access status code.
 *
 * @see bbmsp_access_error_codes_t
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_access_error_codes_t
bbmsp_event_access_changed_get_access_error_code(bbmsp_event_t* event);

/**
 * @brief Determine whether access to the BBM Social Platform is allowed.
 *
 * @details On startup, this function returns 0. After the BBM Social
 * Platform determines your app's access status, your app receives a
 * @c BBMSP_REGISTRATION category event of type
 * @c BBMSP_SP_EVENT_ACCESS_CHANGED. After you receive this event, you can use
 * this function again to retrieve the current access status.
 *
 * The value returned by this function will reflect the latest access
 * status.
 *
 * @return int 1 if @c BBMSP_ACCESS_ALLOWED, 0 otherwise.
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_is_access_allowed(void);

/**
 * @brief Retrieve your app's current access status to the BBM Social Platform.
 *
 * @details On startup, this function will return @c BBMSP_ACCESS_UNKNOWN. After
 * the BBM Social Platform determines your status, your app receives a
 * @c BBMSP_REGISTRATION category event of type
 * @c BBMSP_SP_EVENT_ACCESS_CHANGED. After you receive this event, you can use
 * this function again to retrieve the current access status.
 *
 * The value returned by this function reflects the latest access
 * status.
 *
 * @return The access status code.
 *
 * @see bbmsp_access_error_codes_t
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_access_error_codes_t bbmsp_get_access_code(void);

/**
 * @brief Determine whether the user has allowed this app and its
 * activities to appear in their BBM profile.
 *
 * @details You can use this function to determine whether your profile box is
 * displayed in the user's profile. This function returns an accurate
 * value only if your app has access to the BBM Social Platform (if
 * @c bbmsp_is_access_allowed() returns 1).
 *
 * The user can modify this permission through the global settings for the app.
 *
 * @return int 1 if access is allowed, 0 otherwise.
 *
 * @see bbmsp_user_profile_box.h
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_can_show_profile_box(void);

/**
 * @brief Determine whether this user has allowed other users of this
 * app to send this user invitations to become a BBM contact.
 *
 * @details This function returns an accurate value only if your app has access
 * to the BBM Social Platform (if @c bbmsp_is_access_allowed() returns 1).
 *
 * The user can modify this permission through the global settings for the app.
 *
 * @return int 1 if allowed, 0 otherwise.
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_can_send_bbm_invite(void);

/*!
 * @brief Determine if BBM is set up on the user's device.
 * @details Verifies whether the user has completed the set up of
 * BBM on their device by signing in with their BlackBerry ID
 * (Setup > BlackBerry Messenger).
 *
 * @return int 1 if BBM is set up, 0 otherwise.
 * @since BlackBerry 10.2.0
 */
BBMSP_API int bbmsp_is_bbm_setup(void);

__END_DECLS

#endif /* BBMSP_CONTEXT_H_ */
