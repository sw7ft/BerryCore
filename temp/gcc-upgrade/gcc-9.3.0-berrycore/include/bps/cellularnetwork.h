/*
 * Copyright (C) 2013-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file cellularnetwork.h
 *
 * @brief Functions to determine changes to the cellular network status on the
 * device
 *
 * This file defines the cellular network status change service, which
 * provides functions for notification of when the device's cellular network
 * status changes.
 * For example, you can use the cellular_network status change service to
 * determine when the device is camped on a different cellular network.
 *
 * @since BlackBerry 10.2.0
 */

#ifndef _BPS_CELLULARNETWORK_H_INCLUDED
#define _BPS_CELLULARNETWORK_H_INCLUDED


#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible cellular network status change events
 *
 * This enumeration defines the possible cellular network status change events.
 * Currently, there is only one event.
 * @anonenum bps_cellular_network_status_events Cellular network events
 *
 * @since BlackBerry 10.2.0
 */
enum {
    /**
     * The single cellular network status change event, which contains all of
     * the information about changes to the mobile network identification
     * information (e.g., Mobile Country code (MNC) and Mobile Network Code
     * (MNC) for GSM network).
     *
     * @since BlackBerry 10.2.0
     */
    CELLULAR_NETWORK_ID_INFO        = 0x01
};

/**
 * @brief Start receiving cellular network status change events
 *
 * The @c cellular_network_request_events() function starts to deliver cellular
 * network status change events to the application using BPS.  Events are
 * posted to the currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int cellular_network_request_events(int flags);

/**
 * @brief Stop receiving cellular network status change events
 *
 * The @c cellular_network_stop_events() function stops cellular network status
 * change events from being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int cellular_network_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the cellular network status change
 * service
 *
 * The @c cellular_network_get_domain() function gets the unique domain ID for
 * the cellular_network status change service.  You can use this function in
 * your application to test whether an event retrieved using
 * @c bps_get_event() is a cellular_network status change event, and respond
 * accordingly.
 *
 * @return The domain ID for the cellular_network status change service.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int cellular_network_get_domain();

/**
 * @brief Get the current cellular network country code and network code
 *
 * The @c cellular_network_get_network_id() function gets the current cellular
 * network country code and network code. After the caller is done using the
 * MCC and MNC, use @c bps_free() to free the memory.
 *
 * @param mcc The current mobile country code of the network that the device
 * is camped on or NULL if the MCC is not available. Upon success the caller
 * must call @c bps_free() to free the buffer.
 * @param mnc The current mobile network code of the network that the device
 * is camped on or NULL if the MNC is not available. Upon success the caller
 * must call @c bps_free() to free the buffer.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int cellular_network_get_network_id(char** mcc, char** mnc);

/**
 * @brief Get the Mobile Country Code (MCC) change from a
 * @c #CELLULAR_NETWORK_ID_INFO event
 *
 * The @c cellular_network_event_get_mcc() function extracts the Mobile Country
 * Code (MCC) change from the specified @c #CELLULAR_NETWORK_ID_INFO event. This
 * function returns the Mobile Country Code of the network that the device is
 * currently camped on.
 *
 * @param event The @c #CELLULAR_NETWORK_ID_INFO event to extract the MCC change
 * from.
 *
 * @return The MCC change in string. If MCC is not available, this function
 * returns NULL with @c errno set to @c ENOTSUP. For example, NULL is returned
 * if the device is correctly connected to a CDMA/EVDO network.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char* cellular_network_event_get_mcc(bps_event_t * event);

/**
 * @brief Get the Mobile Country Code (MNC) change from a
 * @c CELLULAR_NETWORK_ID_INFO event
 *
 * The @c cellular_network_event_get_mnc() function extracts the Mobile Network
 * Code (MNC) change from the specified @c #CELLULAR_NETWORK_ID_INFO event. This
 * function returns the Mobile Network Code of the network that the device is
 * currently camped on.
 *
 * @param event The @c ROAMING_INFO event to extract the MCC change from.
 *
 * @return The MNC change in string. If MNC is not available, this function
 * returns NULL with @c errno set to @c ENOTSUP. For example, NULL is returned
 * if the device is correctly connected to a CDMA/EVDO network.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char* cellular_network_event_get_mnc(bps_event_t * event);

__END_DECLS


#endif /* _BPS_CELLULARNETWORK_H_INCLUDED */
