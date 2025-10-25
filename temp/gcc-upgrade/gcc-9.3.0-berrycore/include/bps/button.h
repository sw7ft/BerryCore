/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file button.h
 * 
 * @brief Functions to determine a device's physical button states
 *
 * This file defines the button service, which provides functions for reading
 * the device's button states. This is a read-only service.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_BUTTON_H_INCLUDED
#define _BPS_BUTTON_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief The button events
 * 
 * This enumeration defines the available button events. Currently, there are
 * two events. These events are generated when one of the physical buttons are
 * pressed or released.
 *
 * @anonenum bps_button_events Device button events
 *
 * @since BlackBerry 10.0.0
 */

enum {
    /**
     * The button is up (released).
     *
     * @since BlackBerry 10.0.0
     */
    BUTTON_UP = 0,
    /**
     * The button is down (pressed).
     *
     * @since BlackBerry 10.0.0
     */
    BUTTON_DOWN = 1,
};

/**
 * @brief The physical buttons
 *
 * This enumeration defines each of the physical buttons.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The power button.
     *
     * @since BlackBerry 10.0.0
     */
    BUTTON_POWER = 0,
    /**
     * The play-pause button.
     *
     * @since BlackBerry 10.0.0
     */
    BUTTON_PLAYPAUSE = 1,
    /**
     * The plus button.
     *
     * @since BlackBerry 10.0.0
     */
    BUTTON_PLUS = 2,
    /**
     * The minus button.
     *
     * @since BlackBerry 10.0.0
     */
    BUTTON_MINUS = 3,
} button_physical_t;

/**
 * @brief Start receiving button status change events
 *
 * The @c button_request_events() function starts to deliver physical button
 * status change events to your application using BPS. Events will be posted to
 * the currently active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 *        all events are requested. Any non-zero values are reserved for future
 *        use.
 *
 * @return @c BPS_SUCCESS upon success or @c BPS_FAILURE with @c errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int button_request_events(int flags);

/**
 * @brief Stop receiving button status change events
 *
 * The @c button_stop_events() function stops physical button status change
 * events from being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *        events are stopped. Any non-zero values are reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success or @c BPS_FAILURE with @c errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int button_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the button service
 *
 * The @c button_get_domain() function gets the unique domain ID for the button
 * service. You can use this function in your application to test whether an
 * event that you retrieve using @c bps_get_event() is a button event, and
 * respond accordingly.
 *
 * @return The domain ID for the button service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int button_get_domain();

/**
 * @brief Retrieve the button from the event
 *
 * The @c button_event_get_button() function extracts which button has had a
 * state change from the specified event.
 * 
 * @param event The event to extract the button from.
 *
 * @return One of the values enumerated in @c #button_physical_t or @c
 *         BPS_FAILURE with @c errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int button_event_get_button(bps_event_t *event);

__END_DECLS

#endif // include guard
