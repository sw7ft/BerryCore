/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file holster.h
 *
 * @brief Functions to determine device's holster states
 *
 * The holster API defines the holster service, which provides functions for
 * reading the device's holster states. Use this in order to read when a
 * BlackBerry device is in or out of its holster. This is a read-only service.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_HOLSTER_H_INCLUDED
#define _BPS_HOLSTER_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible holster events
 *
 * This enumeration defines the possible holster events. This event is generated
 * when the user holsters or unholsters their device, and provides information
 * on the holster status of the device. Use the @c
 * holster_event_get_holster_status() function to retrieve information from this
 * event.
 *
 * @anonenum bps_holster_events Device holster events
 *
 * @since BlackBerry 10.0.0
 */
enum {
     /**
      * The device has been holstered or unholstered. This value contains all of
      * the required information about the holster.
      *
      * @since BlackBerry 10.0.0
      */
    HOLSTER_INFO        = 0x01
};

/**
 * @brief Possible holster states
 *
 * This enumeration defines the possible holster states. This is used to
 * indicate whether the device is in or out of its holster.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The device is in the holster.
     *
     * @since BlackBerry 10.0.0
     */
    HOLSTER_IN = 0,
    /**
     * The device is out of the holster.
     *
     * @since BlackBerry 10.0.0
     */
    HOLSTER_OUT = 1,
} holster_state_t;

/**
 * @brief Start receiving holster status change events
 *
 * The @c holster_request_events() function starts to deliver holster
 * status change events to your application using BPS. Events are posted to the
 * currently active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 *              all events are requested. The meaning of non-zero values is
 *              reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int holster_request_events(int flags);

/**
 * @brief Stop receiving holster status change events
 *
 * The @c holster_stop_events() function stops holster satus change events from
 * being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *              events are stopped. The meaning of non-zero values is reserved
 *              for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int holster_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the holster service
 *
 * The @c holster_get_domain() function retrieves the unique domain ID for the
 * holster service. Use this function in your application to test whether an
 * event that you retrieve using @c bps_get_event() is a holster event.
 *
 * @return The domain ID for the holster service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int holster_get_domain();

/**
 * @brief Get the holster status of the device
 *
 * The @c holster_event_get_holster_status() function extracts the holster
 * status of a device. The holster status is used to determine whether or
 * not the the device is holstered by reading the specified @c HOLSTER_INFO
 * event.
 *
 * @param event The @c HOLSTER_INFO event to extract the holster status from.
 *
 * @return @c HOLSTER_HOLSTER_IN if the device is holstered, @c
 *         HOLSTER_HOLSTER_OUT if it isn't, or @c BPS_FAILURE upon error with
 *         errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int holster_event_get_holster_status(bps_event_t *event);

__END_DECLS

#endif // include guard
