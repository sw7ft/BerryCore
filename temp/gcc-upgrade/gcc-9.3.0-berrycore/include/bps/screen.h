/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file screen.h
 *
 * @brief Functions to interact with libscreen events
 * 
 * This file defines a partial wrapping of the Screen API (libscreen) to allow
 * its events and input model to work with BlackBerry Platform Services.
 *
 * This wrapping does not abstract libscreen events, but instead it directs them
 * through the BPS event dispatching mechanism. Once a libscreen event is
 * received through BPS, you must use libscreen functions to manipulate it.
 *
 * Consult the @ref bps_event_sec section for information about handling events
 * in BPS, and the Screen API documentation for details about libscreen events.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_SCREEN_H_INCLUDED
#define _BPS_SCREEN_H_INCLUDED

#include <screen/screen.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Event code for libscreen events
 *
 * This enumeration defines the event code for the BPS event that wraps all
 * libscreen events.
 * 
 * @anonenum bps_screen_anon_events Screen events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The event code for the BPS event that wraps all libscreen events.
     *
     * @since BlackBerry 10.0.0
     */
    BPS_SCREEN_EVENT       = 0x01,
    /**
     * The event code for the BPS event that indicates a failure from libscreen.
     *
     * @since BlackBerry 10.2.0
     */
    BPS_SCREEN_FAILURE     = 0x02,
};

/**
 * @brief Start receiving libscreen events
 *
 * The @c screen_request_events() function starts to deliver libscreen events to
 * an application using BPS.  An application must not invoke libscreen's @c
 * screen_get_event() function if it is receiving screen events through BPS.
 * The @c screen_request_events() function should not be called multiple times
 * before calling @c screen_stop_events().  An application may only request
 * events for a single @c screen_context_t at one time, and only for a single
 * thread.
 *
 * @param context The libscreen context to use for event retrieval.
 * 
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int screen_request_events(screen_context_t context);

/**
 * @brief Get the unique domain ID for the screen
 * 
 * The @c screen_get_domain() function gets the unique domain ID for the screen.
 * You can use this function in your application to test whether an event that
 * you retrieve using @c bps_get_event() is a screen event, and respond
 * accordingly.
 *
 * @return The domain ID for the screen.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int screen_get_domain();

/**
 * @brief Stop receiving libscreen events
 *
 * The @c screen_stop_events() function stops libscreen events from being
 * delivered to the application using BPS.  You should call this function after
 * you call @c screen_request_events() for the first time, and before you call
 * @c screen_request_events() again.
 * 
 * @param context The libscreen context that was passed to @c
 * screen_request_events().
 * 
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int screen_stop_events(screen_context_t context);

/**
 * @brief Get the libscreen context from a BPS event
 * 
 * The @c screen_event_get_context() function extracts the libscreen @c
 * screen_context_t that is stored within a BPS context.  This is the screen
 * context that the event applies to, which is the same context that was passed
 * into @c screen_request_events().
 *
 * @param event The event to extract the libscreen @c screen_context_t from.
 *
 * @return The libscreen @c screen_context_t.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API screen_context_t screen_event_get_context(bps_event_t *event);

/**
 * @brief Get the libscreen event from a BPS event
 * 
 * The @c screen_event_get_event() function extracts the libscreen @c
 * screen_event_t that is stored within a BPS event.  Note that the @c
 * screen_event_t is valid for the same period as the @c #bps_event_t; that is,
 * until @c bps_get_event() is called again.  An application must not call @c
 * screen_destroy_event() on the @c screen_event_t that is extracted from the
 * BPS event.
 *
 * The domain of the event must be the same as the domain that is returned from
 * @c screen_get_domain(), and the code of the event must be @c
 * BPS_SCREEN_EVENT.
 *
 * @param event The event to extract the libscreen @c screen_event_t from.
 *
 * @return The libscreen @c screen_event_t.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API screen_event_t screen_event_get_event(bps_event_t *event);

/**
 * @brief Get the errno from a BPS_SCREEN_FAILURE event
 * 
 * The @c screen_event_get_event() function returns the error number (errno)
 * reported from the failure in libscreen.
 *
 * The domain of the event must be the same as the domain that is returned from
 * @c screen_get_domain(), and the code of the event must be @c
 * BPS_SCREEN_FAILURE.
 *
 * @param event The event to get the errno from.
 *
 * @return The errno.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int screen_event_get_errno(bps_event_t *event);

__END_DECLS

#endif // include guard
