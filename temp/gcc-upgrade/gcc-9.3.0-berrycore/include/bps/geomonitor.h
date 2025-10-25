/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file geomonitor.h
 *
 * @brief Functions to define and monitor geographic areas
 * 
 * This file defines the geomonitor service, which provides functions for
 * creating and monitoring virtual perimeters (regions) for real-world
 * geographic areas. To use the geomonitor service, the application must have
 * the @c access_location_services capability. To grant an application the @c
 * access_location_services capability, the bar-descriptor.xml file in the
 * application's project must contain the line
 * "<permission>access_location_services</permission>".
 *
 * You can use the functions from the Geomonitor library's geomonitor.h to
 * create, add, remove, and manage monitored regions. The function @c
 * bps_geomonitor_event_get_service_event() returns a @c
 * geomonitor_service_event_t structure. You can use the accessor functions
 * defined in the Geomonitor library to access information from a @c
 * geomonitor_service_event_t structure (e.g., @c
 * geomonitor_service_event_get_type()).
 *
 * The following sample code demonstrates how to use this library to create and
 * add a region for monitoring:
 *
 * @code
 *
 * #include <geomonitor.h>
 * #include <bps/geomonitor.h>
 *
 * // 1. Create a new region, give it a unique name, and set its location.
 * geomonitor_region_t region = NULL;
 * geomonitor_create_region(&region, "Home");
 * geomonitor_region_set_circle_shape(region, 45.342102,-75.770581, 200.0);
 *
 * // 2. Set additional optional parameters.
 * // Set region monitoring mode to persistent so that the region is monitored
 * // even when the application that added the region is not running.
 * // Note! The default monitoring mode is transient, which requires you to
 * // create and initialize at least one instance of geomonitor_service_t prior
 * // to adding a region. Persistent regions do not require a 
 * // geomonitor_service_t to be initialized.
 * geomonitor_region_set_monitoring_mode( region,
 *                          GEOMONITOR_MONITORING_MODE_PERSISTENT);
 *
 * // Set notification invoke target. This notification is pushed to the Hub
 * // where the user taps on it and an application is launched.
 * // Note! Application has to be registered with the invocation framework
 * // and to have "blackberry.sample.myapp" - as a valid invoke target.
 * geomonitor_region_set_notification_invoke_target(region,
 *                                             "blackberry.sample.myapp",
 *                                             GEOMONITOR_NOTIFICATION_UIB);
 *
 * // Set Hub notification message content.
 * geomonitor_region_set_notification_message(region, "Message content");
 *
 * // Set the expiration of the region. Convert the date/time of the expiration
 * // to its UTC equivalent. For example, to set the expiration of the region to
 * // November 7, 2012 at 16:34:45, use the UTC value 1352306085.
 * geomonitor_region_set_expiration(region, 1352306085);
 *
 * // Remove the monitored region once device leaves the region.
 * geomonitor_region_set_stop_monitoring_event(region,
 *                                             GEOMONITOR_EVENT_TYPE_EXIT);
 *
 * // 3. Add the region and start monitoring.
 * geomonitor_add(region);
 *
 * // Release the region instance.
 * geomonitor_destroy_region(&region);
 *
 * // 4. Initialize BPS library
 * bps_initialize();
 * // Request geomonitor events
 * bps_geomonitor_request_events(0);
 *
 * bps_event_t * event;
 * // Wait for the event
 * bps_get_event(&event, -1);
 * // Check that received event is valid and belongs to the geomonitor domain
 * if (bps_event_get_domain(event) == bps_geomonitor_get_domain() &&
 *     bps_event_get_code(event)   == GEOMONITOR_INFO ) {
 *
 *     // extract geomonitor event
 *     geomonitor_service_event_t geomonitor_event;
 *     geomonitor_event = bps_geomonitor_event_get_service_event(event);
 *
 *     // extract the event properties
 *     geomonitor_event_type_t event_type = GEOMONITOR_EVENT_TYPE_NONE;
 *     geomonitor_region_t region = NULL;
 *     geomonitor_geolocation_t location = NULL;
 *     geomonitor_service_event_get_type(geomonitor_event, &event_type);
 *     geomonitor_service_event_get_region(geomonitor_event, &region);
 *     geomonitor_service_event_get_location(geomonitor_event, &location);
 *
 *     // extract monitored region name and event location
 *     char *region_name = NULL;
 *     geomonitor_region_get_name(region, &region_name);
 *     double lat = 0.0, lon = 0.0, acc = 0.0;
 *     geomonitor_geolocation_get_latitude(location, &lat);
 *     geomonitor_geolocation_get_longtitude(location, &lon);
 *     geomonitor_geolocation_get_accuracy(location, &acc);
 * }
 * 
 * // 5. The region must be explicitly removed when it no longer needs 
 * // to be monitored; otherwise it will be continuously monitored. 
 * geomonitor_remove("Home");
 *
 * @endcode
 *
 * @since BlackBerry 10.2.0
 */

#ifndef _BPS_GEOMONITOR_H_INCLUDED
#define _BPS_GEOMONITOR_H_INCLUDED

#include <geomonitor.h>
#include <stdbool.h>
#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible geomonitor events
 *
 * This enumeration defines the possible geomonitor events.
 *
 * @anonenum bps_geomonitor_events Geomonitor events
 *
 * @since BlackBerry 10.2.0
 */
enum {
    /**
     * The geomonitor event occurred, which indicates that one of the
     * monitored areas have been entered, exited, etc.
     *
     * @since BlackBerry 10.2.0
     */
    GEOMONITOR_INFO      = 0x01,
    /**
     * The geomonitor error event, which indicates that there was an
     * error and provides details of that error.
     *
     * @since BlackBerry 10.2.0
     */
    GEOMONITOR_ERROR      = 0x02,
};

/**
 * @brief Retrieve the unique domain ID for the geomonitor service
 *
 * The @c bps_geomonitor_get_domain() function gets the unique domain ID
 * for the geomonitor service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is a
 * geomonitor event, and respond accordingly.
 *
 * @return The domain ID for the geomonitor service.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int bps_geomonitor_get_domain();

/**
 * @brief Start receiving geomonitor events
 *
 * The @c bps_geomonitor_request_events() function starts to deliver
 * geomonitor events to your application using BPS.  If the application
 * does not have the @c access_location_services capability, this function
 * will fail. Events will be posted to the currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates
 * that all events are requested. The meaning of non-zero values is reserved
 * for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int bps_geomonitor_request_events(int flags);

/**
 * @brief Stop receiving geomonitor events
 * 
 * The @c bps_geomonitor_stop_events() function stops the delivery of
 * geomonitor events to your application.  If the application does not
 * have the @c access_location_services capability, this function will fail.
 * 
 * @param flags The types of events to stop.  A value of zero indicates
 * that all events are stopped. The meaning of non-zero values is reserved
 * for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int bps_geomonitor_stop_events(int flags);

/**
 * @brief Retrieve the service event from a @c GEOMONITOR_INFO event
 *
 * The @c bps_geomonitor_event_get_service_event() function extracts the event
 * from the specified @c GEOMONITOR_INFO event. Function will return NULL
 * if an error occured during the geomonitor event. Error code or error
 * description can be extracted via @c bps_geomonitor_event_get_error_code()
 * and @c bps_geomonitor_event_get_error_message() functions respectively.
 *
 * @param event The @c GEOMONITOR_INFO event to extract the provider from.
 *
 * @return The geomonitor service event. This is a value of
 * @c geomonitor_service_event_t type that is defined in the
 * geomonitor.h header. This header file also provides
 * all the getters functions to extract the event fields,
 * like location or properties of the monitored area.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API geomonitor_service_event_t bps_geomonitor_event_get_service_event(bps_event_t * event);

/**
 * @brief Retrieve the error message from a @c GEOMONITOR_ERROR event
 *
 * The @c bps_geomonitor_event_get_error_message() function gets the
 * error message from the specified @c GEOMONITOR_ERROR event.
 * The error is with regards to the received geomonitor event and
 * is returned by geomonitor service.
 *
 * @param event The @c GEOMONITOR_ERROR event to get the error message from.
 *
 * @return The error message or @c NULL if there is no error message.
 *
 * @since BlackBerry 10.2.0
 */

BPS_API const char * bps_geomonitor_event_get_error_message(bps_event_t *event);

/**
 * @brief Retrieve the error code from a @c GEOMONITOR_ERROR event
 *
 * The @c bps_geomonitor_event_get_error_code() function gets the error code
 * from the specified @c GEOMONITOR_ERROR event.  The error is with regards
 * to the received geomonitor event and is returned by geomonitor service.
 *
 * @param event The @c GEOMONITOR_ERROR event to get the error code from.
 *
 * @return The error code. This is either a value from the Geomonitor library's
 * @c geomonitor_error_t enumeration, or @c BPS_FAILURE if the event is not
 * valid.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API geomonitor_error_t bps_geomonitor_event_get_error_code(bps_event_t *event);

__END_DECLS

#endif // include guard
