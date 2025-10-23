/*
 * Research In Motion Limited. Copyright (C) 2012.
 * Research In Motion Limited. All rights reserved.
 */
 
 /**
 * @file event.h
 *
 * @brief Functions and types that are used to handle Advertising Service 
 * (bbads) asynchronous events.
 *
 * @since BlackBerry 10.0.0
 */


#ifndef _BBADS_EVENT_H_INCLUDED
#define _BBADS_EVENT_H_INCLUDED

#include <bbads/bbads.h>
#include <bps/event.h>

__BEGIN_DECLS


 /**
 * @mainpage Asynchronous event handling
 *
 * The APIs in the Advertising Service (bbads) library can be used to notify 
 * the application of certain event types. When an event is delivered through  
 * the BlackBerry Platform Services (BPS) library, the event's code, which 
 * indicates the type of event, is set. See the BPS function 
 * bps_event_get_code() for more information on how to identify asynchronous 
 * events for the Advertising Service.
 */

/**
 * @brief Event types for ad banners.
 *
 * This enumeration lists event types for ad banners.
 *
 * @since BlackBerry 10.0.0
 */ 
typedef enum
{
    /* ----- General notification events ----- */

    /**
     *  Switching to the browser because the ad was clicked.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EVENT_NAVIGATING = 0,

    /**
     * The banner is turning transparent because the ad server could
     * not be contacted and the placeholder image could not be loaded.
     * @since BlackBerry 10.0.0 
     */
    BBADS_EVENT_INVISIBLE = 1,


    /* ----- Error events ----- */

    /**
     * Unable to access the network.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EVENT_NETWORK_ERROR = 64,

    /**
     * The host returned an HTTP error for a request.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EVENT_HOST_ERROR = 65,

    /**
     * The placeholder image could not be retrieved.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EVENT_PLACEHOLDER_URL_ERROR = 66

} bbads_banner_event_type_t;

/**
 * @brief Get the BlackBerry Platform Services domain identifier for Advertising 
 * Service events.
 *
 * This function gets the BPS domain ID for bbads events.
 *
 *
 * @return
 * The BPS domain ID for bbads events. If there is no domain ID for bbads 
 * when the call is made, or if the events have not been registered, the 
 * value -1 is returned.
 *
 * @since BlackBerry 10.0.0
 */
int bbads_get_domain(void);

/**
 * @brief Extract the associated banner from an event.
 *
 * This function extracts the associated banner from an event.
 *
 *
 * @param event The @c bps_event_t* to extract the data from.
 * @param banner A pointer to the @c bbads_banner_t* that will be set to the 
 * value extracted from the @c bps_event_t*.
 *
 * @return
 *  - @c BBADS_EOK on success. This return value indicates that the extracted 
 * value was set.
 *  - @c BBADS_EINVAL if event is a null pointer or otherwise an invalid event.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_event_get_banner(bps_event_t* event, bbads_banner_t** banner);


__END_DECLS

#endif /* _BBADS_EVENT_H_INCLUDED */
