/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file clock.h
 *
 * @brief Functions to determine changes to the clock on the device
 * 
 * This file defines the clock change service, which provides functions for
 * notification of when the device's clock changes.  For example, you can use
 * the clock change service to determine when the date or time zone changes on
 * the device.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_CLOCK_H_INCLUDED
#define _BPS_CLOCK_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible clock change events
 * 
 * This enumeration defines the possible clock change events.  Currently, there
 * is only one event.
 * @anonenum bps_clock_events Clock events 
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single clock change event, which contains all of the information
     * about changes to the device's clock.
     *
     * @since BlackBerry 10.0.0
     */
    CLOCK_INFO        = 0x01
};

/**
 * @brief Start receiving clock change events
 *
 * The @c clock_request_events() function starts to deliver clock change events
 * to the application using BPS.  Events will be posted to the currently active
 * channel.
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
BPS_API int clock_request_events(int flags);

/**
 * @brief Stop receiving clock change events
 *
 * The @c clock_stop_events() function stops clock change events from being
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
BPS_API int clock_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the clock change service
 * 
 * The @c clock_get_domain() function gets the unique domain ID for
 * the clock change service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is a
 * clock change event, and respond accordingly.
 *
 * @return The domain ID for the clock change service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int clock_get_domain();

/**
 * @brief Get the date change from a @c CLOCK_INFO event
 * 
 * The @c clock_event_get_date_change() function extracts the date change from
 * the specified @c CLOCK_INFO event. The date change is returned as seconds
 * since the epoch, where the epoch is midnight on January 1, 1970 UTC.
 * 
 * Note that the date change that this function returns is the last date and
 * time that was set by the user. This may or may not be the
 * current time. For example, if the user changes the time to 3:52 PM, this
 * function will report the date change as 3:52 PM, even after that time has
 * passed. This function will continue to report the date change as 3:52 PM
 * until the user resets the time manually.
 *
 * @param event The @c CLOCK_INFO event to extract the date change from.
 *
 * @return The date change (in seconds since the epoch).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int clock_event_get_date_change(bps_event_t * event);

/**
 * @brief Get the time zone change from a @c CLOCK_INFO event
 * 
 * The @c clock_event_get_time_zone_change() function extracts the time zone
 * change from the specified @c CLOCK_INFO event. The format of the returned
 * time zone is as follows:
 *
 * @e std @e offset_std @e dst @e offset_dst, @e rule_to, @e rule_from
 * 
 * where:
 * 
 * - @e std specifies the standard time zone (for example, EST).
 * 
 * - @e offset_std specifies the value you must add to the standard
 *   time to arrive at Coordinated Universal Time (UTC) (for example, 5 or
 *   05 for Eastern Standard Time).
 * 
 * - @e dst specifies the daylight saving time zone (for example,
 *   EDT). If @e dst is omitted, then daylight saving time doesn't
 *   apply in this locale.
 * 
 * - @e offset_dst specifies the value you must add to the daylight
 *   saving time to arrive at UTC (for example, 4 or 04 for Eastern
 *   Daylight Time).
 * 
 * - @e rule_to indicates when to change to daylight saving time. The format of
 *   @e rule_to is @e Mm.n.d/time, which means day @e d (0 <= @e d <= 6) of week
 *   @e n (1 <= @e n <= 5) of month @e m (1 <= @e m <= 12) of the year.
 *   @e time indicates, in local time, when the change occurs.
 * 
 * - @e rule_from indicates when to change from daylight saving time back to
 *   standard time. The format of @e rule_from is the same as the format of
 *   @e rule_to.
 * 
 * The following is an example of this format for Eastern Standard Time:
 * 
 * EST05EDT04,M3.2.0/2,M11.1.0/2
 * 
 * @param event The @c CLOCK_INFO event to extract the time zone change from.
 *
 * @return The time zone change.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * clock_event_get_time_zone_change(bps_event_t * event);


__END_DECLS

#endif // include guard
