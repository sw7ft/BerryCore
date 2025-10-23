/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file orientation.h
 * 
 * @brief Functions to determine the orientation of the device
 *
 * The orientation service provides functions for reading the device's current
 * orientation.
 *
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_ORIENTATION_H_INCLUDED
#define _BPS_ORIENTATION_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible orientation events
 *  
 * This enumeration defines the possible orientation events.  Currently, there
 * is only one event.
 * @anonenum bps_orientation_events Orientation Events 
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single orientation event, which contains all the information about
     * the current orientation of the device.
     *
     * @since BlackBerry 10.0.0
     */
    ORIENTATION_INFO        = 0x01
};

/**
 * @brief Possible orientation directions
 * 
 * This enumeration defines the possible directions that the device is being
 * held in.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    ORIENTATION_FACE_UP     = 0,
    ORIENTATION_TOP_UP      = 1,
    ORIENTATION_BOTTOM_UP   = 2,
    ORIENTATION_LEFT_UP     = 3,
    ORIENTATION_RIGHT_UP    = 4,
    ORIENTATION_FACE_DOWN   = 5,
} orientation_direction_t;

/**
 * @brief Start receiving orientation events 
 * 
 * The @c orientation_request_events() function starts to deliver orientation
 * change events to your application using BPS.  Events will be posted to the
 * currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int orientation_request_events(int flags);

/**
 * @brief Stop receiving orientation change events
 *
 * The @c orientation_stop_events() function stops orientation change events
 * from being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int orientation_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the orientation service
 * 
 * The @c orientation_get_domain() function gets the unique domain ID for the
 * orientation service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is an
 * orientation change event, and respond accordingly.
 *
 * @return The domain ID for the orientation service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int orientation_get_domain();

/**
 * @brief Get the current orientation direction and angle
 * 
 * The @c orientation_get() function gets the current orientation direction and
 * angle of the device.
 * 
 * @param direction The orientation direction.
 * @param angle The orientation angle (in degrees).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int orientation_get(orientation_direction_t *direction, int *angle);

/**
 * @brief Get the curent direction that the device is being held in
 * 
 * The @c orientation_event_get_direction() function gets the current direction
 * that the device is being held in from an @c ORIENTATION_INFO event.
 *
 * @param event The event to get the direction from.
 *
 * @return The current direction.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API orientation_direction_t orientation_event_get_direction(bps_event_t *event);

/**
 * @brief Get the current angle of the device
 * 
 * The @c orientation_event_get_angle() function gets the current angle of the
 * device from an @c ORIENTATION_INFO event. For example, possible angles of the
 * device include the following:
 *
 *    - An angle of 0 is the standard orientation of the device (e.g., the
 *      BlackBerry logo is upright).
 *    - An angle of 90 is where the device has been rotated clockwise by a
 *      quarter turn from its standard orientation.
 *    - An angle of 180 is the reverse of an angle of 0, where the BlackBerry
 *      logo is now upside down.
 *    - An angle of 270 is where the device has been rotated counter-clockwise
 *      by a quarter turn from its standard orientation.
 *
 * @param event The event to get the angle from.
 *
 * @return The current angle (in degrees).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int orientation_event_get_angle(bps_event_t *event);

__END_DECLS

#endif // include guard
