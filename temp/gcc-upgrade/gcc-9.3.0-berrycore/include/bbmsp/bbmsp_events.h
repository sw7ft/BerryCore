/**
 * @file bbmsp_events.h
 *
 * @brief Defines event categories and event types for handling BBM Social
 * Platform events.
 *
 * @details To handle a BBM Social Platform event, determine the events category
 * using @c bbmsp_event_get_category(), determine the event type using
 * @c bbmsp_event_get_type(), and create a bbmsp_event_t instance using
 * @c bbmsp_event_get().
 *
 * @copyright Copyright (C) Research In Motion Limited 2012. All rights
 * reserved.
 */
#ifndef BBMSP_EVENTS_H_
#define BBMSP_EVENTS_H_

#include <sys/platform.h>

__BEGIN_DECLS

/**
 * @brief BBMSP event categories.
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * Events belonging to this category describe notifications about your app's
   * BBM Social Platform access and other permissions.
   * @since BlackBerry 10.0.0
   */
  BBMSP_REGISTRATION = 0,

  /**
   * Events belonging to this category describe notifications about the BBM
   * user's profile.
   * @since BlackBerry 10.0.0
   */
  BBMSP_USER_PROFILE = 1,

  /*!@cond PRIVATE
   * @brief Deprecated
   * @details Events belonging to this category describe notifications about
   * your app's BBM connections.
   * @deprecated This is a deprecated definition. Do not use.
   * @since BlackBerry 10.0.0
   */
  BBMSP_CONNECTION = 2,
  //!@endcond PRIVATE

  /**
   * Events belonging to this category describe notifications about the contact
   * list.
   * @since BlackBerry 10.0.0
   */
  BBMSP_CONTACT_LIST = 3,

  /**
   * Events belonging to this category describe notifications about your app's
   * profile box.
   * @since BlackBerry 10.0.0
   */
  BBMSP_USER_PROFILE_BOX = 4,

  BBMSP_RESERVED = 128
} bbmsp_event_category_t;

/**
 * @brief BBMSP event types.
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * Used for events with category @c BBMSP_REGISTRATION to indicate a change
   * to the access status of the application.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_ACCESS_CHANGED = 0,

  /**
   * Used for events with category @c BBMSP_USER_PROFILE to indicate a change
   * to the user's profile.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_PROFILE_CHANGED = 1,

  /**
   * Used for events with category @c BBMSP_CONTACT_LIST to indicate a change
   * to a contact's profile.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_CONTACT_CHANGED = 2,

  /**
   * Used for events with category @c BBMSP_CONTACT_LIST to indicate that
   * the contact list has been retrieved.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_CONTACT_LIST_FULL = 3,

  /**
   * Used for events with category @c BBMSP_USER_PROFILE_BOX to report that
   * a profile box item has been added.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_USER_PROFILE_BOX_ITEM_ADDED = 13,

  /**
   * Used for events with category @c BBMSP_USER_PROFILE_BOX to report that
   * a profile box item has been removed.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_USER_PROFILE_BOX_ITEM_REMOVED = 14,

  /**
   * Used for events with category @c BBMSP_USER_PROFILE_BOX to report that
   * a profile box icon has been added.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_USER_PROFILE_BOX_ICON_ADDED = 15,

  /**
   * Used for events with category @c BBMSP_USER_PROFILE_BOX to report that
   * a profile box icon has been retrieved.
   * @since BlackBerry 10.0.0
   */
  BBMSP_SP_EVENT_USER_PROFILE_BOX_ICON_RETRIEVED = 17,

  BBMSP_SP_EVENT_RESERVED = 128
} bbmsp_event_type_t;

__END_DECLS

#endif /* BBMSP_EVENTS_H_ */
