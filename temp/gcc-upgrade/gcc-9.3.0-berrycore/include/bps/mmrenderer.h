/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file mmrenderer.h
 * 
 * @brief Functions to monitor the state of the multimedia renderer
 *
 * This file defines the multimedia renderer service, which provides functions
 * for monitoring the multimedia renderer's state. You can use the multimedia
 * renderer to play multimedia files, such as audio or video files, in your
 * applications. You can use the multimedia renderer service to monitor various
 * state properties of the multimedia renderer, such as position and buffer
 * level.
 * 
 * The multimedia renderer service allows you to monitor a specific context,
 * which represents a multimedia object that is being played.  Note that this
 * service is used only to monitor the status of a context, and provides no
 * functionality for creating or controlling contexts.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_MMRENDERER_H_INCLUDED
#define _BPS_MMRENDERER_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>
#include <mm/renderer.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible multimedia renderer events
 * 
 * This enumeration defines the possible multimedia renderer events.
 * @anonenum bps_mmrenderer_events Multimedia renderer events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Indicates that the state of the context that the multimedia renderer is
     * monitoring has changed. For example, the context may have changed from a
     * playing state to a stopped state, or the playback speed may have changed.
     *
     * @since BlackBerry 10.0.0
     */
    MMRENDERER_STATE_CHANGE  = 0x01,
    
    /**
     * Indicates that a warning was received. A warning doesn't cause playback
     * to stop. Warnings that might be generated include audio underrun, dropped
     * video frames, and so on.
     *
     * @since BlackBerry 10.0.0
     */
    MMRENDERER_WARNING       = 0x02,
    
    /**
     * Indicates that the status of the multimedia renderer has been updated.
     * For example, the playback position or buffer level may have changed.
     *
     * @since BlackBerry 10.0.0
     */
    MMRENDERER_STATUS_UPDATE = 0x03,
};

/**
 * @brief Possible context states for the multimedia renderer
 * 
 * This enumeration defines the possible context states of the multimedia
 * renderer.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum mmrenderer_state {
    /**
     * Indicates that the context has been destroyed.
     *
     * @since BlackBerry 10.0.0
     */
    MMR_DESTROYED,
    
    /**
     * Indicates that the context exists but no input is attached to the
     * context (for example, no file is being played).
     *
     * @since BlackBerry 10.0.0
     */
    MMR_IDLE,
    
    /**
     * Indicates that an input is attached to the context but currently isn't
     * playing.
     *
     * @since BlackBerry 10.0.0
     */
    MMR_STOPPED,
    
    /**
     * Indicates that the input that is attached to the context is playing or
     * paused. A speed of 0 means that the context is paused.
     *
     * @since BlackBerry 10.0.0
     */
    MMR_PLAYING,
} mmrenderer_state_t;

/**
 * @brief Handle that identifies a monitored context
 * 
 * The @c mmrenderer_monitor_t structure defines a handle that identifies a
 * monitored context for the multimedia renderer. You create this structure
 * for a particular context by calling @c mmrenderer_request_events(). This
 * structure is then valid until you call @c mmrenderer_stop_events() or
 * @c bps_shutdown().
 *
 * @since BlackBerry 10.0.0
 */
typedef struct mmrenderer_monitor mmrenderer_monitor_t;

/**
 * @brief Start receiving multimedia renderer events
 *
 * The @c mmrenderer_request_events() function starts to deliver multimedia
 * renderer events to your application using BPS. When you call this function,
 * you must specify the name of a multimedia renderer context to monitor. This
 * context must have been created previously, either by your application or by
 * another application that allows the context to be shared.
 *
 * @param ctxtname The name of the multimedia renderer context to monitor.
 * @param flags The types of events to deliver. A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 * @param userdata A user data value. You can use this data to store any
 * additional information that your application needs to interact with 
 * the multimedia renderer.
 *
 * @return A handle for the specified context, or @c NULL if an error occurred.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API mmrenderer_monitor_t *mmrenderer_request_events(const char *ctxtname, unsigned flags, intptr_t userdata);

/**
 * @brief Get the unique domain ID for the multimedia renderer service
 * 
 * The @c mmrenderer_get_domain() function gets the unique domain ID for
 * the multimedia renderer service.  You can use this function in your
 * application to test whether an event that you retrieve using
 * @c bps_get_event() is a multimedia renderer event, and respond accordingly.
 *
 * @return The domain ID for the multimedia renderer service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mmrenderer_get_domain(void);

/**
 * @brief Stop receiving multimedia renderer events
 * 
 * The @c mmrenderer_stop_events() function stops the delivery of multimedia
 * renderer events to the application using BPS.
 *
 * @param mon The handle of the context to stop receiving events from. This
 * handle is returned from @c mmrenderer_request_events().
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void mmrenderer_stop_events(mmrenderer_monitor_t *mon);

/**
 * @brief Get the user data from an multimedia renderer event
 *
 * The @c mmrenderer_event_get_userdata() function gets the user data from the
 * specified multimedia renderer event. This function returns the user data that
 * was passed to @c mmrenderer_request_events().
 *
 * @param event The multimedia renderer event to get the user data from.
 * 
 * @return The user data that was passed to @c mmrenderer_request_events().
 *
 * @since BlackBerry 10.0.0
 */
BPS_API intptr_t mmrenderer_event_get_userdata(bps_event_t *event);

/**
 * @brief Get the current context state from an @c MMRENDERER_STATE_CHANGE event
 * 
 * The @c mmrenderer_event_get_state() function gets the current context state
 * from the specified @c MMRENDERER_STATE_CHANGE event.
 *
 * @param event The @c MMRENDERER_STATE_CHANGE event to get the context state
 * from.
 * 
 * @return The context state.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API mmrenderer_state_t mmrenderer_event_get_state(bps_event_t *event);

/**
 * @brief Get the current context speed from an @c MMRENDERER_STATE_CHANGE event
 * 
 * The @c mmrenderer_event_get_speed() function gets the current context speed
 * from the specified @c MMRENDERER_STATE_CHANGE event.
 *
 * @param event The @c MMRENDERER_STATE_CHANGE event to get the context speed
 * from.
 *
 * @return The context speed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mmrenderer_event_get_speed(bps_event_t *event);

/**
 * @brief Get the error information from an @c MMRENDERER_STATE_CHANGE event
 * 
 * The @c mmrenderer_event_get_error() function gets the error information from
 * the specified @c MMRENDERER_STATE_CHANGE event. 
 *
 * @param event The @c MMRENDERER_STATE_CHANGE event to get the error
 * information from.
 * 
 * @return A pointer to a structure that represents the error information, or
 * @c NULL if this event was not generated by a state change from @c MMR_PLAYING
 * to @c MMR_STOPPED, or if the state change was caused by an API call. This
 * pointer is valid until you destroy the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const mmr_error_info_t *mmrenderer_event_get_error(bps_event_t *event);

/**
 * @brief Get the error position from an @c MMRENDERER_STATE_CHANGE event
 * 
 * The @c mmrenderer_event_get_error_position() function gets the position that
 * an error occurred from the specified @c MMRENDERER_STATE_CHANGE event.
 *
 * @param event The @c MMRENDERER_STATE_CHANGE event to get the error position
 * from.
 * 
 * @return A string that represents the error position, or @c NULL if this event
 * was not generated by a state change from @c MMR_PLAYING to @c MMR_STOPPED,
 * or if the state change was caused by an API call. This pointer is valid until
 * you destroy the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_error_position(bps_event_t *event);


/**
 * @brief Get the warning string from an @c MMRENDERER_WARNING event
 * 
 * The @c mmrenderer_event_get_warning() function gets the warning string from
 * the specified @c MMRENDERER_WARNING event.
 * 
 * @param event The @c MMRENDERER_WARNING event to get the warning string from.
 * 
 * @return A string that represents the warning. This pointer is valid until you
 * destroy the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_warning(bps_event_t *event);

/**
 * @brief Get the warning position from an @c MMRENDERER_WARNING event
 * 
 * The @c mmrenderer_event_get_warning_position() function gets the position
 * in the context that a warning occurred from the specified
 * @c MMRENDERER_WARNING event.
 * 
 * @param event The @c MMRENDERER_WARNING event to get the warning position
 * from.
 * 
 * @return A string that represents the warning position. This pointer is valid
 * until you destroy the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_warning_position(bps_event_t *event);

/**
 * @brief Get the playing position from an @c MMRENDERER_STATUS_UPDATE event
 * 
 * The @c mmrenderer_event_get_position() function gets the playing position of
 * the context from the specified @c MMRENDERER_STATUS_UPDATE event.
 * 
 * @param event The @c MMRENDERER_STATUS_UPDATE event to get the playing
 * position from.
 * 
 * @return A string that represents the position, or @c NULL if the context has
 * not reported a position yet. This pointer is valid until you destroy the
 * event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_position(bps_event_t *event);

/**
 * @brief Get the buffer level from an @c MMRENDERER_STATUS_UPDATE event
 * 
 * The @c mmrenderer_event_get_bufferlevel() function gets the buffer level from
 * the specified @c MMRENDERER_STATUS_UPDATE event.
 * 
 * @param event The @c MMRENDERER_STATUS_UPDATE event to get the buffer level
 * from.
 * 
 * @return A string that represents the buffer level (in the form @e
 * level/capacity), or @c NULL if the context has not reported a buffer
 * level. This pointer is valid until you destroy the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_bufferlevel(bps_event_t *event);

/**
 * @brief Get the buffer status from an @c MMRENDERER_STATUS_UPDATE event
 * 
 * The @c mmrenderer_event_get_bufferstatus() function gets the buffer status
 * from the specified @c MMRENDERER_STATUS_UPDATE event.
 * 
 * @param event The @c MMRENDERER_STATUS_UPDATE event to get the buffer status
 * from.
 * 
 * @return A string that represents the buffer status (@e playing, @e buffering,
 * or @e idle), or @c NULL if the context has not reported a buffer status.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_bufferstatus(bps_event_t *event);

/**
 * @brief Get the audio volume from an @c MMRENDERER_STATUS_UPDATE event
 * 
 * The @c mmrenderer_event_get_volume() function gets the audio volume from the
 * specified @c MMRENDERER_STATUS_UPDATE event.
 * 
 * @param event The @c MMRENDERER_STATUS_UPDATE event to get the audio volume
 * from.
 * 
 * @return A string that represents the volume (in the form @e current/max), or
 * @c NULL if the context has not reported a volume (volume is only reported
 * during audio recording). This pointer is valid until you destroy the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mmrenderer_event_get_volume(bps_event_t *event);

__END_DECLS

#endif // include guard

