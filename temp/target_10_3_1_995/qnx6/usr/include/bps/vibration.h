/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file vibration.h
 *
 * @brief Functions to control the vibration capabilities on the device
 *
 * This file defines the vibration service, which provides functions for
 * controlling vibration on a device.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_VIBRATION_H_INCLUDED
#define _BPS_VIBRATION_H_INCLUDED

#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Vibration events
 *
 * This enumeration defines the possible vibration events.
 * @anonenum bps_vibration_events Vibration events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The vibration event, which contains all of the information about
     * the current vibration status of the device.
     *
     * @since BlackBerry 10.0.0
     */
    VIBRATION_INFO        = 0x01,
};

/**
 * @brief Vibration intensities
 *
 * This enumeration defines the possible vibration intensities.
 * @anonenum bps_vibration_intensities Vibration intensity
 *
 * @since BlackBerry 10.1.0
 */
typedef enum {
    /**
     * Specifies a low intensity vibration.
     *
     * @since BlackBerry 10.1.0
     */
    VIBRATION_INTENSITY_LOW     = 1,
    /**
     * Specifies a regular vibration.
     *
     * @since BlackBerry 10.1.0
     */
    VIBRATION_INTENSITY_MEDIUM  = 10,
    /**
     * Specifies a high intensity vibration.
     *
     * @since BlackBerry 10.1.0
     */
    VIBRATION_INTENSITY_HIGH    = 100,
} vibration_intensity_t;

/**
 * @brief Determine whether the device supports vibration
 *
 * The @c vibration_is_supported() function checks to see if the device supports
 * the Vibration service.
 *
 * @return @c true if the Vibration service is supported, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool vibration_is_supported(void);

/**
 * @brief Start receiving vibration status change events
 *
 * The @c vibration_request_events() function starts to deliver vibration status
 * change events to your application using BlackBerry Platform Services (BPS).
 * Events are posted to the currently active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 *              all events are requested. The meaning of non-zero values is
 *              reserved for future use.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_request_events(int flags);

/**
 * @brief Stop receiving vibration status change events
 *
 * The @c vibration_stop_events() function stops vibration status change events
 * from being delivered to the application using BlackBerry Platform Services
 * (BPS).
 *
 * @param flags The types of events to stop. A value of zero indicates that
 *              all events are to be stopped. The meaning of non-zero values is
 *              reserved for future use.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the vibration service
 *
 * The @c vibration_get_domain() function retrieves the unique domain ID for the
 * vibration service. Use this function in your application to test whether an
 * event that you retrieve using the @c bps_get_event() function is an vibration
 * event, and respond accordingly.
 *
 * @return The domain ID for the Vibration service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_get_domain();

/**
 * @brief Retrieve the duration of a vibration
 *
 * The @c vibration_event_get_duration() function retrieves the duration of the
 * requested vibration from a @c VIBRATION_INFO event
 *
 * @param event The @c VIBRATION_INFO event to get the vibration duration from.
 * @param duration The vibration duration will be set in this variable. A value
 *                 of less than zero means that the device will vibrate until
 *                 the vibration is cancelled (see @c vibration_request()).
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_event_get_duration(bps_event_t *event, int *duration);

/**
 * @brief Retrieve the remaining vibration time
 *
 * The @c vibration_event_get_time_left() function gets the remaining vibration
 * time from a VIBRATION_INFO event.
 *
 * @param event The @c VIBRATION_INFO event to get the time left from.
 * @param time_left If the device is vibrating, then this is set to the number
 *                  of milliseconds before the vibration is over. A value of
 *                  zero means that the device is no longer vibrating. A value
 *                  less than zero means that the device will vibrate until the
 *                  vibration is cancelled.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_event_get_time_left(bps_event_t *event, int *time_left);

/**
 * @brief Retrieve the intensity setting of a vibration
 *
 * The @c vibration_event_get_intensity() function retrieves the vibration
 * intensity from a @c VIBRATION_INFO event.
 *
 * @param event The @c VIBRATION_INFO event to get the intensity from.
 * @param intensity This is set to the intensity of the current vibration.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_event_get_intensity(bps_event_t *event, int *intensity);

/**
 * @brief Request that the device vibrates
 *
 * The @c vibration_request() function requests that the device vibrates at the
 * specified intensity and for the specified length of time.
 *
 * @param intensity The intensity at which the device should vibrate. You should
 *                  use a value from the @c #vibration_intensity_t, however, you
 *                  can use an integer value of zero and above.
 * @param duration The length of time the device should vibrate for in
 *                 milliseconds. Valid values are between zero and 5000
 *                 inclusive.  Use a value of zero to cancel the vibration if
 *                 the device is vibrating.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int vibration_request(int intensity, int duration);

__END_DECLS

#endif // include guard
