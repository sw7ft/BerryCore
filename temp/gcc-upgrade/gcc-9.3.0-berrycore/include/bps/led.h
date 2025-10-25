/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file led.h
 * 
 * @brief Functions to control the LEDs on the device
 *
 * This file defines the LED service, which provides functions for controlling
 * the light emitting diodes (LEDs) on the device.  To control the LEDs, the
 * application must have the @c access_led_control capability. To grant an
 * application the @c access_led_control capability, the bar-descriptor.xml file
 * in the application's project must contain the line
 * "<permission>access_led_control</permission>".
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_LED_H_INCLUDED
#define _BPS_LED_H_INCLUDED

#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * This enumeration defines the possible LED events.  Currently, there is
 * only one event.
 * @anonenum bps_led_events LED events 
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single LED event, which contains the status of the red, green, and
     * blue LEDs (for example, whether they are on or off).
     *
     * @since BlackBerry 10.0.0
     */
    LED_INFO        = 0x01
};

/**
 * @brief LED colors
 *
 * This enumeration defines the possible LED colors.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    LED_COLOR_BLUE    = 0x000000FF,
    LED_COLOR_GREEN   = 0x0000FF00,
    LED_COLOR_CYAN    = 0x0000FFFF,
    LED_COLOR_RED     = 0x00FF0000,
    LED_COLOR_MAGENTA = 0x00FF00FF,
    LED_COLOR_YELLOW  = 0x00FFFF00,
    LED_COLOR_WHITE   = 0x00FFFFFF,
} led_color_t;

/**
 * @brief Start receiving LED status change events
 * 
 * The @c led_request_events() function starts to deliver LED status change
 * events to your application using BPS.  If the application does not have the
 * @c access_led_control capability, this function will fail.  Events will be
 * posted to the currently active channel.
 * 
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested.  The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int led_request_events(int flags);

/**
 * @brief Stop receiving LED status change events
 *
 * The @c led_stop_events() function stops LED status change events from being
 * delivered to the application using BPS.
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
BPS_API int led_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the LED service
 * 
 * The @c led_get_domain() function gets the unique domain ID for the LED
 * service.  You can use this function in your application to test whether an
 * event that you retrieve using @c bps_get_event() is an LED event, and respond
 * accordingly.
 *
 * @return The domain ID for the LED service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int led_get_domain();

/**
 * @brief Get the status of the LEDs from a @c LED_INFO event
 *
 * The @c led_event_get_rgb() function gets the status of the red, green, and
 * blue LEDs from the specified @c LED_INFO event.
 *
 * @param event The @c LED_INFO event to get the LED status from.
 * @param red The status of the red LED will be set in this variable. If @c true
 * the red LED is on, if @c false the red LED is off.
 * @param green The status of the green LED will be set in this variable. If @c
 * true the green LED is on, if @c false the green LED is off.
 * @param blue The status of the blue LED will be set in this variable. If @c
 * true the blue LED is on, if @c false the blue LED is off.
 * 
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int led_event_get_rgb(bps_event_t *event, bool *red, bool *green, bool *blue);

/**
 * @brief Request that the LEDs flash a named color
 *
 * The @c led_request() function requests that the LEDs flash the named
 * color and the specified number of times.  If the application does not have
 * the @c access_led_control capability, this function will fail.
 *
 * @param id An identifier for this request.  This is used when updating a
 * request by calling @c led_request_color() or @c led_request_rgb() again or
 * when canceling a request with @c led_cancel().
 * @param color The color to flash the LEDs.
 * @param blink_count The number of times to blink.  Use a value of 0 to
 * continue blinking until canceled or until the application exits.
 * 
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int led_request_color(const char *id, led_color_t color, int blink_count);

/**
 * @brief Request that the LEDs flash a color that is specified by its red,
 * green, and blue components
 *
 * The @c led_request() function requests that the LEDs flash the color
 * specified by its red, green, and blue components and the specified number of
 * times.  If the application does not have the @c access_led_control
 * capability, this function will fail.
 *
 * @param id An identifier for this request.  This is used when updating a
 * request by calling @c led_request_color() or @c led_request_rgb() again or
 * when canceling a request with @c led_cancel().
 * @param rgb The color to flash the LEDs.  The red, green, and blue components
 * are specified in this value as @e "0x00rrggbb" where:
 *     - @e rr specifies the red intensity
 *     - @e gg specifies the green intensity
 *     - @e bb specifies the blue intensity
 *     .
 * Note that the intensity is fixed so that any non-zero intensity is
 * treated as full intensity.  That is, a distinction is only made between
 * zero and non-zero in each component so that only 7 unique colors are
 * available.
 * @param blink_count The number of times to blink.  Use a value of 0 to
 * continue blinking until canceled or until the application exits.
 * 
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int led_request_rgb(const char *id, int rgb, int blink_count);

/**
 * @brief Cancel a request to flash the LEDs
 *
 * The @c led_cancel() function cancels a previous request to flash the LEDs.
 * If the application does not have the @c access_led_control capability, this
 * function will fail.
 *
 * @param id The identifier used for the request in @c led_request_color() or @c
 * led_request_rgb().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int led_cancel(const char *id);


__END_DECLS

#endif // include guard
