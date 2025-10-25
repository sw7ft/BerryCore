/*
 * Copyright (C) 2013-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file screen_input_guard.h
 *
 * @brief Functions to enable Screen Input Guard
 *
 * Screen Input Guard is a feature of the device whereby the screen turns off
 * and the touchscreen is disabled during a phone call or similar voice chat.
 * This ensures that the caller's face or ear do not trigger unwanted touches on
 * the device causing unintended events.
 *
 * Screen Input Guard turns off the screen and disables the touchscreen when
 * something (assumed to be a face) is detected near the screen.  When the user
 * takes the device away from their face, Screen Input Guard turns on the screen
 * and enables the touchscreen.  However, Screen Input Guard does not turn off
 * the screen and disable the touchscreen if the device is face up, e.g. lying
 * on a table.
 *
 * For best results, call @c screen_input_guard_request_events() at least 200
 * milliseconds before you need to enable Screen Input Guard.  This amount of
 * time allows the face detection sensors to stabilize and give more accurate
 * readings.  Once you actually need the screen to turn off and the touchscreen
 * to be disabled when a face is detected, call @c screen_input_guard_enable().
 * You can also call @c screen_input_guard_request_events() and @c
 * screen_input_guard_enable() immediately after each other, without delay.
 * Note that once you call @c screen_input_guard_request_events(), extra power
 * is used, so it should not be used when not required.
 *
 * For example, call @c screen_input_guard_request_events() as soon as an
 * incoming phone call comes in.  Face detection will stabilize during the time
 * it takes for the user to answer the phone call.  If the user rejects the
 * phone call, call @c screen_input_guard_stop_events().  If the user accepts
 * the phone call, immediately call @c screen_input_guard_enable().  The screen
 * and the touchscreen will turn off when the user places the phone next to
 * their face, and the screen and the touchscreen will turn on when the device
 * is moved away from their face.  When the phone call ends, call @c
 * screen_input_guard_disable() and @c screen_input_guard_stop_events().
 *
 * As another example, when the user starts to make an outgoing phone call, call
 * @c screen_input_guard_request_events().  Face detection will stabilize while
 * the user is dialing.  As soon as the user starts the phone call and is likely
 * to place the phone next to their face, call @c screen_input_guard_enable().
 * When the phone call ends, call @c screen_input_guard_disable() and
 * @c screen_input_guard_stop_events(). However, if you expect the user to be on
 * the dial screen for a long period of time without actually dialing, it would
 * be better for power usage to wait until the phone call is started to call @c
 * screen_input_guard_request_events() and @c screen_input_guard_enable().
 *
 * @since BlackBerry 10.2.0
 */

#ifndef _BPS_SCREEN_INPUT_GUARD_H_INCLUDED
#define _BPS_SCREEN_INPUT_GUARD_H_INCLUDED

#include <sys/platform.h>

__BEGIN_DECLS

/**
 * @brief Possible Screen Input Guard events
 *
 * This enumeration defines the possible Screen Input Guard events.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * Screen Input Guard status event.  These events are delivered when Screen
     * Input Guard is activated or deactivated.  They are only delivered while
     * Screen Input Guard is enabled with @c screen_input_guard_enable().
     *
     * @since BlackBerry 10.2.0
     */
    SCREEN_INPUT_GUARD_EVENT_STATUS        = 0x01,
} screen_input_guard_event_t;

/**
 * @brief Possible status values for Screen Input Guard
 *
 * This enumeration defines the possible status values of Screen Input Guard.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * Screen Input Guard is deactivated.  The screen is on and the touchscreen
     * is responsive to input.
     *
     * @since BlackBerry 10.2.0
     */
    SCREEN_INPUT_GUARD_STATUS_DEACTIVATED = 0,

    /**
     * Screen Input Guard is activated.  The screen is off and the touchscreen
     * is not responsive to input.
     *
     * @since BlackBerry 10.2.0
     */
    SCREEN_INPUT_GUARD_STATUS_ACTIVATED   = 1,
} screen_input_guard_status_t;

/**
 * @brief Start receiving Screen Input Guard events
 *
 * The @c screen_input_guard_request_events() function starts to deliver Screen
 * Input Guard events to the application using BPS.  Events are posted to the
 * currently active channel.  They are only delivered while Screen Input Guard
 * is enabled with @c screen_input_guard_enable().
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 *              all events are requested. The meaning of non-zero values is
 *              reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_input_guard_request_events(int flags);

/**
 * @brief Stop receiving Screen Input Guard events
 *
 * The @c screen_input_guard_stop_events() function stops Screen Input Guard
 * events from being delivered to the application using BPS.  This will also
 * forcibly disable Screen Input Guard if it was enabled with @c
 * screen_input_guard_enable(), ignoring the the reference count between @c
 * screen_input_guard_enable() and @c screen_input_guard_disable().
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *              events are stopped. The meaning of non-zero values is reserved
 *              for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_input_guard_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the Screen Input Guard service
 *
 * The @c screen_input_guard_get_domain() function gets the unique domain ID for
 * the Screen Input Guard service.  You can use this function in your
 * application to test whether an event that you retrieve using @c
 * bps_get_event() is a Screen Input Guard event, and respond accordingly.
 *
 * @return The domain ID for the Screen Input Guard service.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_input_guard_get_domain(void);

/**
 * @brief Enable Screen Input Guard
 *
 * The @c screen_input_guard_enable() function enables Screen Input Guard.  That
 * is, when something (assumed to be a face) is detected to be near the device,
 * the screen will turn off and the touchscreen will not respond to touch input.
 * When that something is no longer near the device, the screen will turn on and
 * the touchscreen will again respond to touch input.
 *
 * To disable Screen Input Guard call @c screen_input_guard_disable().  Calls to
 * @c screen_input_guard_enable() and @c screen_input_guard_disable() are
 * reference counted.  Thus if you call @c screen_input_guard_enable() multiple
 * times, you must call @c screen_input_guard_disable() the same number of times
 * before Screen Input Guard is actually disabled.
 *
 * Calling @c screen_input_guard_stop_events() will forcibly disable Screen
 * Input Guard, ignoring the reference count.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_input_guard_enable(void);

/**
 * @brief Disable Screen Input Guard
 *
 * The @c screen_input_guard_disable() function disables Screen Input Guard,
 * once it has been called the same number of times as @c
 * screen_input_guard_enable().
 *
 * Calls to @c screen_input_guard_enable() and @c screen_input_guard_disable()
 * are reference counted.  Thus if you call @c screen_input_guard_enable()
 * multiple times, you must call @c screen_input_guard_disable() the same number
 * of times before Screen Input Guard is actually disabled.
 *
 * Calling @c screen_input_guard_stop_events() will forcibly disable Screen
 * Input Guard, ignoring the reference count.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_input_guard_disable(void);

/**
 * @brief Retrieve the Screen Input Guard status from a @c
 * SCREEN_INPUT_GUARD_EVENT_STATUS event
 *
 * Call the @c screen_input_guard_event_get_status() function to retrieve the
 * Screen Input Guard status from a @c #SCREEN_INPUT_GUARD_EVENT_STATUS event.
 * @c #SCREEN_INPUT_GUARD_EVENT_STATUS events are delivered only while Screen
 * Input Guard is enabled via @c screen_input_guard_enable().
 *
 * @param event The @c SCREEN_INPUT_GUARD_EVENT_STATUS event to get the screen
 *              input guard status from.
 *
 * @return The Screen Input Guard status as one of the values of the @c
 *         #screen_input_guard_status_t enumeration or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_input_guard_event_get_status(bps_event_t *event);

__END_DECLS

#endif
