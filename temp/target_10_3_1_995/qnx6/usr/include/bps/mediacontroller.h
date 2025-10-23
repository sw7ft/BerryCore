/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file mediacontroller.h
 *
 * @brief Functions to control media playing.
 *
 * This file defines the Media Controller service, which provides functions for
 * controlling the playing of media files.
 *
 * Media Controllers allow you to connect to the @e Now @e Playing service to
 * determine what content is currently playing. It also allows you to submit
 * requests to control playback for the current, active media player in the
 * system.
 *
 * Devices have two default controllers on the system. One is tied to the
 * physical buttons on the device and another tied to the @e Now @e Playing UI
 * that appears when the user taps the now playing indicator in the status bar.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_MEDIACONTROLLER_H_INCLUDED
#define _BPS_MEDIACONTROLLER_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>
#include "bps/bps.h"
#include "bps/mediacommon.h"

__BEGIN_DECLS

/**
 * @brief Media Controller events
 *
 * This enumeration defines the available Media Controller events.
 * 
 * @anonenum bps_mediacontroller_events Media controller events
 *
 * @since BlackBerry 10.0.0
 */
enum {

     /**
      * The active player's state has changed.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIACONTROLLER_STATE               =  1,
     /**
      * The active player's metadata has changed.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIACONTROLLER_METADATA            =  2,
};

/**
 * @brief Start receiving Media Controller events
 *
 * The @c mediacontroller_request_events() function starts to deliver Media
 * Controller events to your application using BlackBerry Platform Services
 * (BPS). Events are posted to the currently active channel.
 *
 * @param flags Additional flags that are reserved for future use. Set this
 *              value to 0 to request all Media Controller events.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_request_events(int flags);

/**
 * @brief Stop receiving Media Controller events
 *
 * The @c mediacontroller_stop_events() function stops Media Controller events
 * from being delivered to your application using BlackBerry Platform Services
 * (BPS).
 *
 * @param flags Additional flags that are reserved for future use. Set this
 *              value to 0 to stop Media Controller events from being delivered
 *              to your application.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the Media Controller service
 *
 * The @c mediacontroller_get_domain() function gets the unique domain ID for
 * the Media Controller service.  You can use this function in your application
 * to determine whether an event that you receive using the @c bps_get_event()
 * function is a Media Controller event, and respond accordingly.
 *
 * @return The domain ID for the Media Controller service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_get_domain(void);

/**
 * @brief Set the volume level
 *
 * The @c mediacontroller_volume_set_level() function sets the volume to the
 * given level.
 *
 * @param level The level to set the volume to. You specify the level as a
 *              percentage value, such as 50 or 75.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_volume_set_level(float level);

/**
 * @brief Increase the volume level
 *
 * The @c mediacontroller_volume_up() function increases the volume level.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_volume_up(void);

/**
 * @brief Decrease the volume level
 *
 * The @c mediacontroller_volume_down() function decreases the volume level.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_volume_down(void);

/**
 * @brief Set the volume mute state
 *
 * The @c mediacontroller_volume_set_mute() function sets the volume mute state
 * to the given mute state.
 *
 * @param mute The state to set the volume mute to.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_volume_set_mute(bool mute);

/**
 * @brief Indicate that the volume was changed
 *
 * The @c mediacontroller_volume_update() function informs the @e Now @e Playing
 * service that the volume was changed and that a volume toast should be
 * displayed.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_volume_update(void);

/**
 * @brief Play the current media content
 *
 * The @c mediacontroller_play() function directs the connected media player to
 * play its content.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_play(void);

/**
 * @brief Pause the current media content
 *
 * The @c mediacontroller_pause() function directs the connected media player to
 * pause playing content.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_pause(void);

/**
 * @brief Play or pause the current media content
 *
 * The @c mediacontroller_play() function directs the connected media player to
 * play or pause its content accordingly.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_play_pause(void);

/**
 * @brief Stop the current media content
 *
 * The @c mediacontroller_stop() function directs the connected media player to
 * stop playing content.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_stop(void);

/**
 * @brief Skip to the next track
 *
 * The @c mediacontroller_next_track() function directs the connected media
 * player to skip to the next track.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_next_track(void);

/**
 * @brief Skip to the beginning of the current track, or to the previous track
 *
 * The @c mediacontroller_previous_track() function directs the connected media
 * player to skip to the beginning of the current track, or to the previous
 * track.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_previous_track(void);

/**
 * @brief Fast-forward the media
 *
 * The @c mediacontroller_fast_forward() function directs the connected media
 * player to enter fast forward mode.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_fast_forward(void);

/**
 * @brief Rewind the media
 *
 * The @c mediacontroller_rewind() function directs the connected media player
 * to enter rewind mode.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_rewind(void);

/**
 * @brief Send a button-down message
 *
 * The @c mediacontroller_button_down() function sends a button down message to
 * the connected media player.
 *
 * @param button The button for which the button down message is sent, must be
 *               one of the values of the @c #media_button_t enum, not including
 *               @c #MEDIA_BUTTON_NONE.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_button_down(int button);

/**
 * @brief Send a button-up message
 *
 * The @c mediacontroller_button_up() function sends a button up message to the
 * connected media player.
 *
 * @param button The button for which the button up message is sent, must be one
 *               of the values of the @c #media_button_t enum, not including @c
 *               #MEDIA_BUTTON_NONE.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_button_up(int button);

/**
 * @brief Retrieve the state of the Media Controller from the @c
 *        MEDIACONTROLLER_STATE event
 *
 * The @c mediacontroller_event_get_state() function extracts the current state
 * from the specified @c #MEDIACONTROLLER_STATE event.
 *
 * @param event The @c #MEDIACONTROLLER_STATE event to extract the current state
 *              from. The state will be one of the values from the @c
 *              #media_state_t enumeration.
 *
 * @return The current state.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_event_get_state(bps_event_t *event);

/**
 * @brief Retrieve the artist from the @c MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_artist() function extracts the
 * artist from the specified @c #MEDIACONTROLLER_METADATA event.
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the artist
 *              from.
 *
 * @return The string representing an artist, or @c a NULL value if the artist
 *         was not available or specified.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mediacontroller_event_get_metadata_artist(bps_event_t *event);

/**
 * @brief Retrieve the album from the @c MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_album() function extracts the album
 * from the specified @c #MEDIACONTROLLER_METADATA event.
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the album
 *              from.
 *
 * @return The string representing an album, or @c a NULL value if the album
 *         was not available or specified.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mediacontroller_event_get_metadata_album(bps_event_t *event);

/**
 * @brief Retrieve the track from the @c MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_track() function extracts the track
 * from the specified @c #MEDIACONTROLLER_METADATA event.
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the track
 *              from.
 *
 * @return The string representing an track, or @c a NULL value if the track
 *         was not available or specified.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mediacontroller_event_get_metadata_track(bps_event_t *event);

/**
 * @brief Retrieve the current position in the track from the @c
 *        MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_position() function extracts the
 * position in the track from the specified @c #MEDIACONTROLLER_METADATA event.
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the position
 *              from.
 *
 * @return The position of the track (in milliseconds), a negative number
 *         indicates position was not specified.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_event_get_metadata_position(bps_event_t *event);

/**
 * @brief Retrieve the duration from the @c MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_duration() function extracts the
 * duration from the specified @c #MEDIACONTROLLER_METADATA event.
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the duration
 *              from.
 *
 * @return The duration  of the track (in milliseconds), a negative number
 *         indicates duration was not specified.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediacontroller_event_get_metadata_duration(bps_event_t *event);

/**
 * @brief Retrieve the path to the album artwork from the @c
 *        MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_album_artwork() function extracts
 * the path to the album artwork from the specified @c #MEDIACONTROLLER_METADATA
 * event.
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the path to
 *              the album artwork from.
 *
 * @return The string representing the path to the album artwork, or @c a NULL
 *         value if the album artwork was not available.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *mediacontroller_event_get_metadata_album_artwork(bps_event_t *event);

/**
 * @brief Retrieve whether the @e next @e track functionality should be enabled
 *        from the @c MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_next_enabled() function extracts
 * whether the @e next @e track functionality should be enabled from the
 * specified @c #MEDIACONTROLLER_METADATA event. Enabled in this sense implies
 * that there is a @e next @e track to proceed to should the command be sent
 * (see the @c mediacontroller_next_track() function for more details).
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the @e next @e
 *              track enabled state from.
 *
 * @return The boolean value representing the @e next @e track enabled state.
 *         Returning @c false indicates disabled, and @c true indicates enabled.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool mediacontroller_event_get_next_enabled(bps_event_t *event);

/**
 * @brief Retrieve whether the @e previous @e track functionality should be
 *        enabled from the @c MEDIACONTROLLER_METADATA event
 *
 * The @c mediacontroller_event_get_metadata_previous_enabled() function
 * extracts whether the @e previous @e track functionality should be enabled
 * from the specified @c #MEDIACONTROLLER_METADATA event. Enabled in this sense
 * implies that there is a @e previous @e track to proceed to should the command
 * be sent (see the @c mediacontroller_previous_track() function for more
 * details).
 *
 * @param event The @c #MEDIACONTROLLER_METADATA event to extract the @e
 *              previous @e track enabled state from.
 *
 * @return The boolean value representing the @e previous @e track enabled
 *         state. Returning @c false indicates disabled, and @c true indicates
 *         enabled.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool mediacontroller_event_get_previous_enabled(bps_event_t *event);

__END_DECLS

#endif /* include guard */
