/**
 * @file bbmsp_presence.h
 *
 * @brief Definitions of the values that represent the presence status of a user
 * or contact, and the update types for a user's BBM profile.
 *
 * @details Defines the values for the presence status of a user on the BBM
 * Social Platform, and the types of updates that can be made to a user's BBM
 * profile.
 *
 * @copyright Copyright (C) Research In Motion Limited 2012. All rights
 * reserved.
 *
 */

#ifndef BBMSP_PRESENCE_H_
#define BBMSP_PRESENCE_H_

#include <sys/platform.h>

__BEGIN_DECLS

/**
 * @brief The types of updates that a user or a contact can make to their BBM
 * profile.
 *
 * @details After receiving an event belonging to the @c BBMSP_USER_PROFILE
 * category and an event type of @c BBMSP_SP_EVENT_PROFILE_CHANGED, use
 * @c bbmsp_event_profile_changed_get_presence_update_type() to retrieve the
 * @c bbmsp_presence_update_types_t instance that describes the update.
 * After receiving an event belonging to the @c BBMSP_CONTACT_LIST category with
 * and an event type of @c BBMSP_SP_EVENT_CONTACT_CHANGED, use
 * @c bbmsp_event_contact_changed_get_presence_update_type() to retrieve the
 * @c bbmsp_presence_update_types_t instance that describes the update.
 * 
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * Indicates that the display name has changed.
   * @since BlackBerry 10.0.0
   */
  BBMSP_DISPLAY_NAME = 1 << 0,

  /**
   * Indicates that the display picture has changed.
   * @since BlackBerry 10.0.0
   */
  BBMSP_DISPLAY_PICTURE = 1 << 1,

  /**
   * Indicates that the personal message has changed.
   * @since BlackBerry 10.0.0
   */
  BBMSP_PERSONAL_MESSAGE = 1 << 2,

  /**
   * Indicates that the status has changed.
   * @since BlackBerry 10.0.0
   */
  BBMSP_STATUS = 1 << 3,

  /**
   * Indicates that your app was installed/enabled.
   * @since BlackBerry 10.0.0
   */
  BBMSP_INSTALL_APP = 1 << 4,

  /**
   * Indicates that your app was uninstalled/disabled.
   * @since BlackBerry 10.0.0
   */
  BBMSP_UNINSTALL_APP = 1 << 5,

  /*!@cond PRIVATE
   * @brief Deprecated
   * @deprecated This is a deprecated definition. Do not use.
   * @since BlackBerry 10.0.0
   */
  BBMSP_INVITATION_RECEIVED = 1 << 6
  //!@endcond

} bbmsp_presence_update_types_t;

/**
 * @brief The presence status of a user or contact on the BBM Social Platform.
 *
 * @details To retrieve the status of the user, use
 * @c bbmsp_profile_get_status() and to retrieve the status of a contact, use
 * @c bbmsp_contact_get_status().
 * 
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * Indicates that the status is available.
   * @since BlackBerry 10.0.0
   */
  BBMSP_PRESENCE_STATUS_AVAILABLE = 0,

  /**
   * Indicates that the status is busy.
   * @since BlackBerry 10.0.0
   */
  BBMSP_PRESENCE_STATUS_BUSY = 1
} bbmsp_presence_status_t;

__END_DECLS

#endif /* BBMSP_PRESENCE_H_ */
