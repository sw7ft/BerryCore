/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file bps.h
 *
 * @brief Functions for the BlackBerry Platform Services library
 *
 * This file defines functions that are used across the entire BlackBerry
 * Platform Services (BPS) library.
 *
 * @since BlackBerry 10.0.0
 */

/**
 * @mainpage BlackBerry Platform Services Library
 *
 * @section bps_intro_sec BPS Introduction
 *
 * The BlackBerry Platform Services (BPS) library provides C/C++ developers with
 * a single consistent interface to a number of different platform services:
 *
 * - Audio devices
 * - Audio mixer
 * - Battery
 * - Buttons
 * - Cellular network status
 * - Clock
 * - Device information
 * - Dialogs
 * - Events
 * - Geofencing
 * - Geolocation
 * - Holster
 * - Invocation
 * - LED
 * - Locale
 * - Media controllers
 * - Media player
 * - Menus
 * - Multimedia renderer
 * - Navigator
 * - Network status
 * - Notifications
 * - Orientation
 * - Payment services
 * - Region
 * - Removable media
 * - Screen
 * - Screen capture
 * - Screen input guard
 * - Sensors
 * - Sound player
 * - Vibration
 * - Virtual keyboard
 *
 * BPS provides a functional interface to platform services, along with an
 * event-retrieval mechanism for asynchronous notification.
 *
 * @section bps_usage_sec Requesting and Listening for Events
 * 
 * The BPS library provides a high-level view of various platform services. Each
 * client application simply makes one request to the platform services that it
 * wants to receive events for. A loop is set up to listen for the events and
 * the client application determines how to handle the event using custom
 * application logic.
 *
 * Events are then generated and processed, and the application can interact
 * with the platform service as necessary.
 *
 * @subsection bps_queue_sec Using an Event Queue
 * 
 * @code
 * 
 * // 1. Start the library
 * bps_initialize();
 *
 * // 2. Request events to flow into the event queue
 * virtualkeyboard_request_events(0);
 * orientation_request_events(0);
 * navigator_request_events(0);
 *
 * // 3. Use any service at any time
 * virtualkeyboard_show(); // Show the virtual keyboard
 *
 * // 4. Listen for events
 * for (;;) {
 *   // get an event
 *    bps_event_t *event;
 *    bps_get_event(&event, -1); // blocking
 *
 *    // handle the event
 *    handle_event(&event);
 * }
 *
 * bps_shutdown();
 *
 * @endcode
 *
 * @section bps_event_sec Events
 *
 * Different platform services generate different events. Events are
 * differentiated by the event domain (the service that generated the event) and
 * the event code (the type of the event). In addition, events can have a
 * payload that includes any information sent along from the service when it
 * generated the event.
 *
 * You can use the @c bps_event_get_domain() function to determine the service
 * (event domain) that generated a particular event. The event code can be
 * determined with the @c bps_event_get_code() function. Normally, an event
 * handler uses the event domain and event code to determine what the event is.
 * Once the event is known, it can be handled properly. For example, individual
 * accessor functions can be used to extract the payload data appropriate to the
 * event.
 * 
 * For example:
 * 
 * @code
 *  if (bps_event_get_domain(event) == virtualkeyboard_get_domain()) {
 *         uint16_t code = bps_event_get_code(event);
 *        if (code == VIRTUALKEYBOARD_EVENT_VISIBLE) {
 *           // Keyboard is now visible. Handle event...
 *        } else if (code == VIRTUALKEYBOARD_EVENT_HIDDEN) {
 *            // Keyboard is now hidden. Handle event...
 *        } else if (code == VIRTUALKEYBOARD_EVENT_INFO) {
 *            // Extract the keyboard height
 *            int height = virtualkeyboard_event_get_height(event)
 *            // Handle...
 *         }
 *    }
 * @endcode
 * 
 * For more details on individual events, consult the documentation for the
 * service that generates the event.
 *
 * @section bps_function_sec Service Functions
 * 
 * Many services provide functions that a client can invoke. These functions are
 * documented individually with each service. The BPS library provides simple
 * functions to invoke these service functions.
 * 
 * For example:
 *
 * @code
 *    // show the keyboard
 *    virtualkeyboard_show();
 * @endcode
 *
 * 
 * @section bps_channel_sec BlackBerry Platform Services Channels
 *
 * The BlackBerry Platform Services (BPS) uses channels to receive platform
 * service events. Each BPS channel has an event queue associated with it. BPS
 * restricts ownership of a channel to the thread that created the channel
 * because access to the event queue is not thread-safe. This differs from
 * channels created directly in QNX Neutrino, where a channel is owned by a
 * process and therefore, channels can be accessed by any thread owned by the
 * process.
 *
 * When you use the @c bps_initialize() function, a default channel is created
 * that is set as active. You can use the @c bps_channel_create() function to
 * create a new channel on behalf of the application. The new channel can
 * receive events once it is active. Active channels are used when you want to
 * work with events and file descriptors in your application.  You use the @c
 * bps_channel_set_active() to set a channel as active and @c
 * bps_channel_destroy() to destroy a channel you created using the
 * @c bps_channel_create() function.
 */

#ifndef _BPS_BPS_H_INCLUDED
#define _BPS_BPS_H_INCLUDED

#include <sys/platform.h>
#include <bbndk.h>

#ifndef BPS_API
/**
 * This identifier is used to make the BPS functions visible for public use.
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_API
#endif

#ifndef BPS_DEPRECATED
/**
 * An identifier to denote that the BPS API has been deprecated.
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_DEPRECATED  __attribute__((__deprecated__))
#endif

#include "bps/event.h"

__BEGIN_DECLS

/**
 * The structure for a sigevent.
 */
struct sigevent;

/**
 * The version of the BPS.
 *
 * The version number is computed as follows:
 * (Major * 1000000) + (Minor * 1000) + Patch
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_VERSION             (3001003)

/**
 * The version of BPS as a string.
 *
 * @see BPS_VERSION
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_VERSION_STRING      "3.1.3"

/**
 * A return code that indicates that a function completed successfully.
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_SUCCESS (0)

/**
 * A return code that indicates that a function did not complete successfully.
 * When @c errno value is set, it indicates the reason for the failure.
 *
 * @since BlackBerry 10.0.0
 */
#define BPS_FAILURE (-1)

/**
 * @brief Retrieve the version of BPS
 *
 * The @c bps_get_version() function retrieves the version of the BPS library
 * that your application is using.
 *
 * @return The version of BPS library using the scheme described for @c
 *         BPS_VERSION.
 *
 * @see BPS_VERSION
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_get_version(void);

/**
 * @brief Initialize the BPS library for use with the caller's current thread
 *
 * The @c bps_initialize() function initializes the BPS library. This function
 * must be the first BPS function you call for a thread when you want to use BPS
 * library functions.
 *
 * If initialization of the library fails, a @c BPS_FAILURE value is returned
 * with @c errno value set. The use of any BPS library function without a
 * successful invocation of the @c bps_initialize() functions results in
 * undefined behavior.
 *
 * Your application can call the @c bps_initialize() function more than once.
 * An application that calls the @c bps_initialize() function multiple times
 * should call the @c bps_shutdown() function the same number of times.
 *
 * For multi-threaded applications, call the @c bps_initialize() function at the
 * beginning of the thread, and call the @c bps_shutdown() function before the
 * thread terminates. When the @c bps_initialize() function is called for a new
 * thread, it automatically creates a default @c channel and sets it as the
 * thread's active @c channel. Events are requested on a per-channel basis.
 *
 * For example, when you want to receive navigator events on a new thread, call
 * the @c navigator_request_events() function after calling @c bps_initialize()
 * function, even if you had already called the @c navigator_request_events()
 * function previously on a different thread. See the @c bps_channel_create()
 * function for more details about channels.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_initialize(void);

/**
 * @brief Free the platform service resources for the current thread specified
 *        by the caller
 *
 * When an application calls the @c bps_initialize() function multiple times,
 * the application must call the @c bps_shutdown() function the same number of
 * times. For multi-threaded applications, threads that call the @c
 * bps_initialize() function should call the @c bps_shutdown() function prior to
 * the thread terminating.
 *
 * Resources that are used by the BPS library are freed only after the @c
 * bps_shutdown() function is called the same number of times that the @c
 * bps_initialize() function is called. In addition, all callbacks registered
 * with the @c bps_register_shutdown_handler() function are called. The
 * application must not call any other BPS library functions after this function
 * completes.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void bps_shutdown(void);

/**
 * @brief Create an event channel tied to the caller's current thread
 *
 * The @c bps_channel_create() function causes the platform services to create a
 * channel on behalf of the application. This channel allows the application to
 * receive platform services events by making it active through the @c
 * bps_channel_set_active() function.
 *
 * A channel is an event queue, a set of file descriptors with callbacks, and a
 * set of domain data. The channel monitors the I/O state of its file
 * descriptors and fires registered callbacks when the appropriate conditions
 * are met. Channels are tied to the thread that created them. A channel in one
 * thread cannot be used by another thread. Events can be pushed from one
 * channel to another using the @c bps_channel_push_event() function.
 *
 * When platform services are initialized using the @c bps_initialize()
 * function, a default event channel is created and set as the active channel.
 * You may want your application to create additional channels and associate
 * different services to different channels. Multiple channels can be associated
 * with the same thread. You can switch channel using the @c
 * bps_channel_set_active() function.
 *
 * @param chid After the function is called, the new channel ID is written to
 *             the specified value.
 * @param flags (Reserved for future use). Additional flags that are reserved
 *              for future use. You should set this value to 0.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_channel_create(int *chid, int flags);

/**
 * @brief Set the thread's active channel
 *
 * The active channel for a thread determines which channel subsequent calls
 * affect. Calls to various functions, such as the @c bps_get_event(), @c
 * bps_push_event(), @c bps_add_fd() functions, work on the active channel. In
 * addition, several service functions affect the active channel. Typically,
 * function names that end in @c _request_events() adds a service's file
 * descriptor to the active channel so that the events will start to enter the
 * active channel's event queue.
 *
 * A call to the @c bps_channel_set_active() function is only necessary when the
 * application has created a channel using the @c bps_channel_create()
 * function. A call to the @c bps_initialize() function creates a default
 * channel, and that default channel is set as the active channel.
 *
 * @param chid A channel ID supplied by a previous call to the @c
 *             bps_channel_create() function.
 *
 * @return The previous active channel ID, @c BPS_FAILURE with @c errno value
 *         set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_channel_set_active(int chid);

/**
 * @brief Retrieve the thread's active channel ID
 *
 * Use this function when a thread needs to communicate its channel ID to
 * another thread that uses the @c bps_channel_push_event() function.
 *
 * @return The active channel ID for the calling thread.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_channel_get_active(void);

/**
 * @brief Destroy the specified channel based on the channel ID
 *
 * After an application is finished using the channel, call the @c
 * bps_channel_destroy() function for channels that are created using the @c
 * bps_channel_create() function. After this function is called, all events that
 * are waiting in the channel's event queue are completed and all callbacks
 * registered with the @c bps_register_channel_destroy_handler() function are
 * called.
 *
 * When the @c chid argument is the thread's active channel, it is destroyed
 * and the default channel for the thread is set as the active channel.
 *
 * @param chid The channel ID set by a call to the @c bps_channel_create()
 *             function.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_channel_destroy(int chid);

/**
 * @brief Retrieve the next event from the application's active channel
 *
 * The @c bps_get_event() function retrieves the next event for the application.
 * The event is pulled from the active channel's event queue. If an event is
 * available, it is immediately returned. If an event is not immediately
 * available, the behavior of this function depends on the value of the @c
 * timeout_ms argument.
 *
 * Note: Event "ownership" is not transferred to the application. An application
 * must not call the @c bps_event_destroy() function on event pointers that are
 * retrieved using the @c bps_get_event() function. The pointer to the event is
 * valid until the @c bps_get_event() function is called again. Use the @c
 * bps_channel_push_event() function to transfer ownership of the event to a
 * different channel.
 *
 * When an application needs to pull an event from a different channel's event
 * queue, it should call the @c bps_channel_set_active() function to the desired
 * channel.
 *
 * @param event The pointer to return the event to. The event is returned
 *              through this pointer. In the case of a timeout, a @c NULL value
 *              is returned.
 * @param timeout_ms An integer value that defines the timeout:
 *                   - positive: Return when event is available or after @c
 *                               timeout_ms milliseconds, whichever occurs
 *                               first.
 *                   - 0: Return immediately.
 *                   - negative: Block until an event is available.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise. In the case of a
 *         timeout or when polling occurs, a value of @c BPS_SUCCESS is
 *         returned, but the @c event is set to a @c NULL value.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_get_event(bps_event_t **event, int timeout_ms);

/**
 * @brief Post an event to the active channel
 *
 * The @c bps_push_event() function allows an application to post to the
 * application's active channel's event queue. You can use the @c
 * bps_event_create() function to create a custom event in your application,
 * and then use the @c bps_push_event() function to add the event to the
 * active event queue.
 *
 * Use the @c bps_channel_push_event() function to post the event when a
 * channel is not active at the time or is owned by a different thread.
 *
 * @param event The event to post to the active channel.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_push_event(bps_event_t *event);

/**
 * @brief Post an event to the selected channel
 *
 * The @c bps_channel_push_event() function allows an application to post an
 * event to any channel. You can use the @c bps_event_create() function to
 * create a custom event in your application, and then use the @c
 * bps_channel_push_event(chid, event) function to add the event to a channel
 * that isn't currently active, or owned by the thread.
 *
 * You can also use this function to dispatch an event to a different channel
 * than the channel the event originated on. This makes passing events off to a
 * different thread possible. In order for the transfer of event ownership to
 * work properly, the active channel should be the same channel that the event
 * was originally retrieved from.
 *
 * @param chid The event channel to push the event onto.
 * @param event The event to post to the event queue.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_channel_push_event(int chid, bps_event_t *event);

/**
 * @brief Register a function for eventual execution
 *
 * Calling @c bps_channel_exec() registers the provided function by creating an
 * exec event, which is an event that combines the function and the specified
 * data. The function is referred to as the exec function, although it can also
 * be thought of as a callback function. The exec event is added to the event
 * queue of the destination channel (@c chid). The exec function is invoked with
 * the provided data during a call to @c bps_get_event() when the exec event is
 * removed from the event queue. Note that the caller of @c bps_get_event() will
 * not receive this exec event; it is consumed by BPS and converted into a call
 * to the exec function.
 *
 * The @c bps_channel_exec() function works across threads. The channel @c chid
 * can be owned by the same thread that is calling @c bps_channel_exec() or by
 * an entirely different thread. When performing a cross-thread exec, care must
 * be taken to safe-guard any data that is shared between the calling thread
 * and the thread that owns the destination channel @c chid.  The same
 * precautions should be taken with the use of the @c data argument.
 *
 * @param chid The channel ID designating which channel event queue
 *             to enqueue the exec callback.
 * @param exec The function that will be executed. The first argument to the
 *             callback will be the data that is passed to @c
 *             bps_channel_exec() function. Any returned result will be ignored.
 * @param data The user data that will be used as the first argument of the
 *             invoke function.
 *
 * @return @c BPS_SUCCESS if the invoke callback was successfully registered
 * with channel @c chid.  @c BPS_FAILURE if registration failed. errno will be
 * set to the cause of failure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_channel_exec(int chid, int (*exec)(void *), void *data);

/** @cond internal
 */

/**
 * @brief Setup a default slog2 buffer if one is not set.
 *
 * The @c bps_logging_init() function sets up a default slog2 buffer if one is
 * not set.  BPS will log to the default slog2 buffer.  If you would like to
 * setup your own slog2 buffers, do so with @c slog2_register() and @c
 * slog2_set_default_buffer() before calling any BPS function.
 *
 * @return @c BPS_SUCCESS if a default slog2 buffer was set up successfully or
 *         if one was already setup.  @c BPS_FAILURE if setting up a default
 *         slog2 buffer failed.
 */
BPS_API int bps_logging_init(void);

/** @endcond
 */

/**
 * @brief Set the verbosity of logging for platform services
 *
 * The @c bps_set_verbosity() function sets the verbosity (level of detail) of
 * logging for BPS.  Logs are sent to slog2's default buffer with code 8900.
 * BPS will setup a default slog2 buffer to use if one is not set.  The @c
 * bps_set_verbosity() function simply changes the verbosity setting of slog2's
 * default buffer.
 *
 * Logs can be viewed by using the slog2info utility from a shell prompt on the
 * device or in the Device Log window in the Momentics IDE.
 *
 * Often, the details in the log file explain the reason for receiving a @c
 * BPS_FAILURE value.
 *
 * @param verbosity The desired verbosity. Use the following values:
 *                  - 0: Shutdown and Critical messages are logged.
 *                  - 1: Shutdown, Critical, Error and Warning messages are
 *                       logged.
 *                  - 2: Shutdown, Critical, Error, Warning, Notice and Info
 *                       messages are logged. This is the default verbosity.
 *                  - 3: Shutdown, Critical, Error, Warning, Notice, Info,
 *                       Debug1 and Debug2 messages are logged.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void bps_set_verbosity(unsigned verbosity);

/**
 * @brief Free the memory allocated by platform services
 *
 * The @c bps_free() function releases memory allocated by BPS.
 *
 * @param ptr The pointer to the memory to be freed.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void bps_free(void *ptr);

/**
 * @addtogroup services
 * @{
 */

/**
 * @brief Reserve a unique domain ID for identifying a service's events
 *
 * The @c bps_register_domain() function reserves a unique domain ID for use in
 * a service's events. Services should cache this value. When this function is
 * called again, it yields a new domain ID.
 *
 * The domain ID is used on calls to the @c bps_event_create() function.
 * Typically, an application determines which service generated the event prior
 * to handling it. For example, the code as follows shows a service called
 * "myservice" that defines two functions: @c myservice_get_domain() and @c
 * myservice_event_handle():
 *
 * @code
 *
 * bps_event_t *event;
 * bps_get_event(&event, -1);
 *
 * if (event) {
 *      if (bps_event_get_domain(event) == myservice_get_domain()) {
 *          myservice_event_handle(event);
 *      }
 * }
 *
 * @endcode
 *
 * @return A domain ID for a service. A value of -1 indicates an error and the
 *         @c errno value is set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_register_domain(void);

/**
 * @brief Register a callback that will be invoked when the last shutdown
 *        function is called
 *
 * Shutdown handlers/callbacks are called when @c bps_shutdown() is called for
 * the last time. BPS tracks how many times @c bps_initialize() has been called,
 * and when @c bps_shutdown() has been called the same number of times (i.e.,
 * a reference count drops to 0), the shutdown handlers are called.
 *
 * This function cleans up a service's global data. Typically, a service has to
 * reset the domain ID to indicate it has been uninitialized. Other cleanup
 * activities depend on the service's implementation.
 *
 * @param shutdown_handler The function for platform services to call when the
 *                         library is shutting down. BPS passes the data that
 *                         the caller provided as the first argument.
 * @param data The user data that is passed as the first argument when the BPS
 *             calls the shutdown handler.
 *
 * @return @c BPS_SUCCESS is returned if the handler registered successfully
 *         with the data, @c BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_register_shutdown_handler(void (*shutdown_handler)(void *),
                                          void *data);

/**
 * @brief Register a callback that will be invoked when the active channel is
 *        being destroyed
 *
 * The function is used for services that have channel specific resources
 * allocated that require cleanup when the channel is destroyed. At a minimum,
 * most services have at least one file descriptor that needs to be closed.
 *
 * A channel can be destroyed for a variety of reason that include:
 * - The thread that created the channel has terminated.
 * - The application has called the @c bps_channel_destroy() function.
 * - The final @c bps_shutdown() function has been called, and all channels are
 *   being destroyed.
 *
 * The destroy_handler is invoked when the channel is destroyed and the user
 * data is passed into the function as the first argument. In the
 * destroy_handler, do not call BPS library functions that use the channel that
 * is being destroyed, with the exception of the @c bps_get_domain_data()
 * function.
 *
 * @param destroy_handler The callback that is invoked on channel destruction.
 * @param data The user data that is passed to the destroy_handler.
 *
 * @return @c BPS_SUCCESS when the handler has successfully been registered
 *         along with the data, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_register_channel_destroy_handler(void (*destroy_handler)(void *),
                                                 void *data);

/**
 * @brief The bit to use when adding a file descriptor
 *
 * When you call @c bps_add_fd() to register an I/O handler with a channel, you
 * specify the type of I/O to monitor with a bitwise OR of the corresponding @c
 * #bps_io_events_t bits.
 *
 * When the I/O handler is called by the BPS library, the type of I/O event is
 * passed into the second argument of the callback. You can perform a bitwise OR
 * operation on this argument with the values of the @c #bps_io_events_t
 * enumeration to determine the I/O condition that was met.
 *
 * @sa bps_add_fd
 *
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicate that there is data available for reading
     *
     * @since BlackBerry 10.0.0
     */
    BPS_IO_INPUT    = 1 << 0,

    /**
     * Indicate that there is room in the output buffer for more data.
     *
     * @since BlackBerry 10.0.0
     */
    BPS_IO_OUTPUT   = 1 << 1,

    /**
     * Indicate one of three things occurred:
     * - An error occurred.
     * - The device has been disconnected.
     * - The provided file descriptor was invalid.
     *
     * @since BlackBerry 10.0.0
     */
    BPS_IO_EXCEPT   = 1 << 2,
} bps_io_events_t;

/**
 * @brief Add a file descriptor to the currently active channel
 *
 * Call the function when a service wants to include a file descriptor in the
 * active channel's set of file descriptors.  At that time, the channel includes
 * the supplied file descriptor into the set of file descriptors that it is
 * monitoring. When the I/O conditions, specified in @c io_events, are met then
 * the channel calls the io_handler callback supplied.
 *
 * An error occurs when you add a file descriptor that was already added to the
 * channel.
 *
 * You can perform a bitwise OR to @c #bps_io_events_t enumerations and pass it
 * as a second argument to specify the I/O conditions that the channel monitors.
 *
 * For example, the code that follows shows when you want to monitor for input
 * and supply no user data:
 *
 * @code
 * bps_add_fd(fd, BPS_IO_INPUT, &io_handler, NULL);
 * @endcode
 *
 * The code that follows shows how to monitor for input and errors, with a
 * channel specific data "service":
 *
 * @code
 * bps_add_fd(service->fd, BPS_IO_INPUT | BPS_IO_EXCEPT, &io_handler, &service);
 * @endcode
 *
 * The io_handler callback is called whenever @c io_events I/O conditions are
 * present for the file descriptor. The first argument will be the file
 * descriptor, the second argument will be one or more @c #bps_io_events_t
 * enumerated values to indicate which conditions are present. The third
 * argument is the user data.  If the @c io_handler callback returns
 * @c BPS_FAILURE, @c io_handler callback will no longer be called to handle the
 * specified condtions.
 *
 * @param fd The file descriptor to start monitoring.
 * @param io_events The I/O conditions to monitor for.
 * @param io_handler The I/O callback that is called whenever I/O conditions are
 *                   met.
 * @param data User supplied data that will be given to the I/O callback as the
 *             third argument.
 *
 * @return @c BPS_SUCCESS if the @c fd (file descriptor) was successfully added
 *         to the channel, @c BPS_FAILURE with the errno value set otherwise.
 *
 * @sa bps_remove_fd
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_add_fd(int fd, int io_events, int (*io_handler)(int, int, void*),
                       void *data);

/**
 * @brief Remove a file descriptor from the active channel
 *
 * The function is called when a service wants to remove a file descriptor from
 * the channel's set of file descriptors that it is monitoring for input or
 * output.
 *
 * If the file descriptor is present it is removed from the channel. The
 * io_handler callback and associated user data are also removed.
 *
 * Typically, the function is used in services that provide a function to stop
 * events from arriving on the channel's event queue.
 *
 * @param fd The file descriptor to remove.
 *
 * @return @c BPS_SUCCESS if the @c fd (file descriptor) was successfully
 *         removed from the channel, @c BPS_FAILURE with @c errno value set
 *         otherwise.
 *
 * @sa bps_add_fd
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_remove_fd(int fd);

/**
 * @brief Add a sigevent handler to the active channel
 *
 * This function is for situations where a service doesn't have a file
 * descriptor with raw event data. In these cases, services can call @c
 * bps_add_sigevent_handler() instead of @c bps_add_fd(). The purpose of the
 * sigevent_handler callback is to push events onto the event queue. This
 * callback has the same purpose as the @c bps_add_fd() functions's io_handler
 * callback. The difference between the io_handler and sigevent_handler
 * callbacks is that the sigevent_handler is fired whenever the channel receives
 * the sigevent that gets filled in by calling this function and the io_handler
 * gets fired when IO conditions are met for a file descriptor.
 *
 * @param sigevent An allocated sigevent that will be filled in by @c
 *                 bps_add_sigevent_handler(). A service can then use function
 *                 like @c MsgDeliverEvent to signal the callback.
 * @param sigevent_handler The sigevent callback that gets fired whenever the
 *                         channel receives the corresponding sigevent. 
 *                         - The first argument will be the data supplied
 *                           in this function. 
 *                         - If sigevent_handler returns anything other than 
 *                           @c EXIT_SUCCESS (0), the callback is removed from
 *                           the active channel. In addition, subsequent
 *                           deliveries of the sigevent will not result in a
 *                           call to sigevent_handler.
 * @param data Service specific data that will be passed into every call to
 *             sigevent_handler.
 *
 * @return @c BPS_SUCCESS if the sigevent_handler was successfully registered,
 * and sigevent was filled in. Otherwise, @c BPS_FAILURE is returned and the @c
 * errno value will indicate the type of error. On failure, no callback is
 * registered.
 *
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_add_sigevent_handler(struct sigevent *sigevent,
                                     int (*sigevent_handler)(void *), 
                                     void *data);

/**
 * @brief Remove the sigevent handler from the active channel
 *
 * When a service is finished delivering events it can unregister its
 * sigevent_handler by calling this function.
 *
 * @param sigevent The sigevent that was filled in by a call to
 * @c bps_add_sigevent_handler().
 *
 * @return @c BPS_SUCCESS if the sigevent_handler was unregistered from the
 * active channel, @c BPS_FAILURE with @c errno set to an
 * appropriate error code otherwise.
 *
 * @sa bps_add_sigevent_handler()
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_remove_sigevent_handler(const struct sigevent *sigevent);

/**
 * @brief Set domain specific data for the active channel
 *
 * Call the function when a service wants to set specific user data for the
 * active channel. Often, a service has data that is particular to a channel.
 * Since each service needs to call the @c bps_register_domain() function to
 * create events, the same domain ID is used for a service to reference its
 * data. The specifics of the type of data to store, however, is dependent on
 * the implementation of each service.
 *
 * At minimum, most services pass a structure that contains a file descriptor.
 * In most cases, this is the same file descriptor that was added using the @c
 * bps_add_fd() function.
 *
 * Channels are thread-specific and a channel on one thread cannot be used by
 * another thread. In addition, only active channels can retrieve data.
 *
 * To clear domain data from the channel, call this function with the @c
 * new_data argument set to a value of @c NULL.
 *
 * If @c old_data is not a @c NULL value, it is set to the previous data that
 * was associated with same value of the @c domain_id argument. If no data was
 * previously set, it is set to a value of @c NULL.
 *
 * @param domain_id The domain ID to associate new_data with.
 * @param new_data The service user data that should be stored in the active
 *                 channel.
 * @param old_data If a value of @c NULL is not provided, it is set to the
 *                 previous data for the @c domain_id argument.
 *
 * @return @c BPS_SUCCESS if the file descriptor was successfully removed from
 *         the channel, @c BPS_FAILURE with @c errno value set otherwise.
 *
 * @sa bps_get_domain_data
 * @sa bps_register_domain
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int bps_set_domain_data(int domain_id, void *new_data, void **old_data);

/**
 * @brief Retrieve domain-specific data from the active channel
 *
 * A service calls this function when it needs to retrieve the user data that
 * was previously provided to the channel using the @c bps_set_domain_data()
 * function.
 *
 * When no data is associated with the @c domain_id argument, a @c NULL value
 * is returned.
 *
 * @param domain_id The domain ID provided by the @c bps_register_domain()
 *                  function.
 *
 * @return The user data that was associated with the active channel and the @c
 *         domain_id. If no data is found, a @c NULL value is returned.
 *
 * @sa bps_set_domain_data
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void * bps_get_domain_data(int domain_id);

/**
 * @}
 */

__END_DECLS

#endif
