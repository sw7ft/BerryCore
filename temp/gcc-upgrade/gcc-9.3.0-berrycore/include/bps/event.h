/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file event.h
 *
 * @brief Functions and structures for BlackBerry Platform Services (BPS) events
 *
 * BPS events are generic structures that encapsulate
 * various types of data.  The event structure and event delivery mechanism
 * provide a way for the system to communicate with the application in an
 * asynchronous manner.
 *
 * The purpose of having a common event type across multiple services is to
 * facilitate the uniform handling of heterogenous input to your application.
 *
 * This file defines a generic event type, @c bps_event_t, that can be used by a
 * BlackBerry Platform Service to communicate with an application.  An
 * application may also use @c bps_event_t events for its own purposes.
 *
 * See bps.h for information on how to retrieve events.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_EVENT_H_INCLUDED
#define _BPS_EVENT_H_INCLUDED

#include <sys/platform.h>
#include <stdint.h>

/**
 * @struct bps_event_t
 * @brief Opaque event type
 *
 * The @c bps_event_t structure represents an event in BPS.
 */
struct bps_event_t;

/**
 * @typedef struct bps_event_t
 * A data type that contains the structure for an event used in BPS.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct bps_event_t bps_event_t;

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * The maximum allowable domain of an event that you create using
 * @c bps_event_create().
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_EVENT_DOMAIN_MAX 0x00000FFF

/**
 * @brief Get the domain of an event
 *
 * The @c bps_event_get_domain() function gets the domain of a BPS event.  Each
 * event in BPS is associated with a domain, which represents the service
 * that generated the event (for example, navigator, network status,
 * accelerometer, and so on).
 *
 * @param event The event to get the domain of.
 *
 * @return The domain of the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_event_get_domain(bps_event_t *event);

/**
 * @brief Get the code of an event
 *
 * The @c bps_event_get_code() function gets the code of a BPS event.  In
 * addition to being associated with a domain, each event in BPS has a code,
 * which represents the specific type of event that occurred.  For example,
 * the virtual keyboard service includes event codes that indicate when the
 * keyboard becomes visible, when the keyboard becomes hidden, and so on.
 *
 * @param event The event to get the code of.
 *
 * @return The code of the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned int bps_event_get_code(bps_event_t *event);



/*
 * The following functions are typically not needed by applications.
 * Applications that create their own events should use these functions
 * carefully.
 */


/**
 * @brief Structure that represents the payload of an event
 *
 * The @c bps_event_payload_t structure represents the payload of a BPS event.
 * Events carry three data members as payload.  These data members may contain
 * the event's data themselves, or they may be pointers to additional data
 * pertaining to the event.  In most cases, an application does not need to
 * use the data members, because a service will provide accessor methods.  An
 * application may use the @c bps_event_payload_t structure when creating its own
 * events.
 *
 * Note that if an event's payload contains dynamically allocated
 * resources, they should be freed in the event's destructor function, which
 * is called by @c bps_event_destroy().
 *
 * @since BlackBerry 10.0.0
 */
struct bps_event_payload_t {
    /** Payload data.
     *
     * @since BlackBerry 10.0.0
     */
    uintptr_t data1;
    /** Payload data.
     *
     * @since BlackBerry 10.0.0
     */
    uintptr_t data2;
    /** Payload data.
     *
     * @since BlackBerry 10.0.0
     */
    uintptr_t data3;
};
/**
 * A data type that stores the data (payload) sent as part of an event.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct bps_event_payload_t bps_event_payload_t;

/**
 * @brief Completion function for an event
 *
 * An event may have a completion function that will be called by the system
 * when the event is no longer used.  A completion function may be used by the
 * originator of the event to free dynamic resources associated with the
 * event's payload.  When an event's completion function is invoked, the event
 * may safely be reused by the event's originator or @c bps_event_destroy()
 * should be invoked.  If @c NULL is set as an event's completion function, the
 * event is destroyed internally.  An event may be resubmitted to BPS from
 * within the completion function by using @c bps_push_event().
 *
 * @since BlackBerry 10.0.0
 */
typedef void (*bps_event_completion_func) (bps_event_t *event);

/**
 * @brief Create an event
 *
 * The @c bps_event_create() function creates a @c bps_event_t event.  An
 * application may create its own event, which may then be passed to
 * @c bps_push_event().
 *
 * If @c bps_push_event() is successfully called on the event, the event will be
 * destroyed by the event's completion function (or by the library if a
 * completion function is not set).
 *
 * If an event is created using @c bps_event_create() @b and the event is not
 * pushed to BPS using @c bps_push_event() or @c bps_channel_push_event(), then
 * you must call @c bps_event_destroy() to destroy the event, after which the
 * event must not be used.
 *
 * @param event The event to be returned.
 * @param domain The domain of the event. This value must be no greater than @c
 *               BPS_EVENT_DOMAIN_MAX. Your event's domain must be a number
 *               generated by a call to @c bps_register_domain() to ensure
 *               uniqueness.
 * @param code The code of the event.  This value may be any number from 0 to
 *             UINT16_MAX.
 * @param payload_ptr A pointer to the event's payload, which will be copied.
 * @param completion_function An optional completion function that will be
 *                            invoked when the system is done with the event.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_event_create(bps_event_t **event, unsigned int domain, unsigned int code, const bps_event_payload_t *payload_ptr, bps_event_completion_func completion_function);

/**
 * @brief Destroy an event
 *
 * The @c bps_event_destroy() function destroys a @c bps_event_t event.  The
 * event must not be used after this function is invoked.  An application should
 * rarely call this function.  This function must be called only if an event is
 * created using @c bps_event_create() @b and the event is not pushed to BPS
 * using @c bps_push_event() or @c bps_channel_push_event(). If @c
 * bps_push_event() is successfully called on the event, the event will be
 * destroyed by the event's completion function (or by the library if a
 * completion function is not set).
 *
 * @param event The event to destroy.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void bps_event_destroy(bps_event_t *event);

/**
 * @brief Get a pointer to an event's payload
 *
 * The @c bps_event_get_payload() function gets a pointer to the payload of a
 * @c bps_event_t event.
 *
 * @param event The event to get the payload for.
 *
 * @return A pointer to the event's payload.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bps_event_payload_t* bps_event_get_payload(bps_event_t *event);


__END_DECLS

#endif
