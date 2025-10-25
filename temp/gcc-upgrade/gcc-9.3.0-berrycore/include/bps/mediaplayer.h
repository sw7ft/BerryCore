/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file mediaplayer.h
 *
 * @brief Functions for media playing
 *
 * This file defines the Media Player service, which provides functions for the
 * playing of media files.
 *
 * Media players connect to @e Now @e Playing service to co-operatively work
 * with other media players in the system, acquiring the right to play content,
 * and giving up the right if the user directs another media player to start
 * playing content.
 *
 * If your media player app is interrupted by a higher priority player (for
 * example, a phone call or voice control), the @e Now @e Playing service
 * instructs your app to pause. In most cases, once the interrupting media
 * player releases control (for example, the phone call ends), the @e Now @e
 * Playing service sends a play command to your app. The one exception is when
 * the output device switches from private (for example, headphones) to public
 * (for example, speaker) while the high priority player is active. In these
 * cases, music is supposed to automatically pause when the switch occurs.
 *
 * If a higher priority media player starts and the @e Now @e Playing services
 * pauses your app, the user can still hit the play button on the screen. Your
 * app can monitor the @e Now @e Playing status object to see the priority of
 * the currently active player. If the priority is higher than 'low', your app
 * should not attempt to play, as doing so will result in the @e Now @e Playing
 * service sending an error response.
 * 
 * If your media player app is interrupted by a media player of the same
 * priority, your app will receive a @c MEDIAPLAYER_REVOKE event. Your app must
 * stop playback at this point and free up multimedia resources. It is your
 * media player's responsibility to re-acquire the right to play content after
 * receiving this event.
 * 
 * Media players also can provide metadata to the system and receive commands
 * from media controllers.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_MEDIAPLAYER_H_INCLUDED
#define _BPS_MEDIAPLAYER_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"
#include "bps/mediacommon.h"

__BEGIN_DECLS

/**
 * @brief Media player events
 *
 * This enumeration defines the available Media player events.
 * 
 * @anonenum bps_mediaplayer_events Media player events
 *
 * @since BlackBerry 10.0.0
 */
enum {
     /**
      * An acquired request has been processed.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_ACQUIRE_RESULT          =  1,

     /**
      * The player's state as the active media player in the system is being
      * revoked. The player should immediately stop playback and free up
      * multimedia resources. It is the player's responsibility to re-acquire
      * the right to play content after receiving this event.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_REVOKE                  =  2,

     /**
      * Requests the media player to handle a command.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_COMMAND                 =  3,

     /**
      * A button has been pressed.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_BUTTON                  =  4,

     /**
      * A release request has been processed.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_RELEASE_RESULT          =  5,

     /**
      * A register request has been processed.
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_REGISTER_RESULT         =  6,

     /**
      * A button registration request has been processed.
      *
      * @since BlackBerry 10.2.0
      */
    MEDIAPLAYER_REGISTER_BUTTON_RESULT  =  7,

     /**
      * Deprecated: A button registration request has been processed.
      *
      * @deprecated Use @c #MEDIAPLAYER_REGISTER_BUTTON_RESULT instead
      *
      * @since BlackBerry 10.0.0
      */
    MEDIAPLAYER_BUTTON_RESULT           =  MEDIAPLAYER_REGISTER_BUTTON_RESULT,

     /**
      * A button deregistration request has been processed.
      *
      * @since BlackBerry 10.2.0
      */
    MEDIAPLAYER_DEREGISTER_BUTTON_RESULT  =  8,
};

/**
 * A data type that represents the structure for storing metadata for media.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct mediaplayer_metadata_t mediaplayer_metadata_t;

/**
 * @brief Start receiving Media player events
 *
 * The @c mediaplayer_request_events() function starts to deliver Media player
 * events to your application using BlackBerry Platform Services (BPS). Events
 * will be posted to the currently active channel.
 *
 * @param flags Additional flags that are reserved for future use. Set this
 *              value to 0 to request all Media player events.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_request_events(int flags);

/**
 * @brief Stop receiving Media player events
 *
 * The @c mediaplayer_stop_events() function stops Media player events from
 * being delivered to your application using BlackBerry Platform Services (BPS).
 *
 * @param flags Additional flags that are reserved for future use. Set this
 *              value to 0 to stop Media player events from being delivered to
 *              your application.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the Media Player service
 *
 * The @c mediaplayer_get_domain() function gets the unique domain ID for the
 * Media Player service. You can use this function in your application to
 * determine whether an event that you retrieve using the @c bps_get_event()
 * function is a Media player event, and respond accordingly.
 *
 * @return The domain ID for the Media Player service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_get_domain(void);

/**
 * @brief Acquire the status of active media player in the system
 *
 * The @c mediaplayer_acquire() function requests that the system establish the
 * calling player as the active media player in the system.  The previous active
 * media player (if any) will have its active state revoked.  To support the
 * cooperative rules of engagement, media players must send acquire before they
 * begin media playback, to allow other players to stop playback.  Media players
 * should only do this on an explicit action by the user (the user pressed the
 * play button or just launched the player).
 *
 * @param id If not @c NULL, the ID used in the acquire request will be returned
 *           in @c id.  The caller must free this buffer using @c bps_free().
 *           This same ID will be delivered in the corresponding @c
 *           #MEDIAPLAYER_ACQUIRE_RESULT event.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_acquire(char **id);

/**
 * @brief Release the status of the active media player in the system
 *
 * The @c mediaplayer_release() function notifies the system that the calling
 * player is relinquishing its status as the active media player in the system.
 * If the calling player is a higher priority player than any previously active
 * media player that is currently paused, then the higher priority player is
 * acquired and given active status.
 *
 * @param id If not @c NULL, the ID used in the release request will be returned
 *           in @c id.  The caller must free this buffer using @c bps_free().
 *           This same ID will be delivered in the corresponding @c
 *           #MEDIAPLAYER_RELEASE_RESULT event.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_release(char **id);

/**
 * @brief Register the media player
 *
 * The @c mediaplayer_register() function registers the media player.
 *
 * @param name The descriptive name.
 * @param priority The priority, one of the values of the @c #media_priority_t
 *                 enumeration.
 * @param audio_type The audio type, one of the values of the @c
 *                   #media_audio_type_t enumeration.
 * @param volume_overlay The volume overlay, one of the values of the @c
 *                       #media_volume_overlay_t enumeration.
 * @param id If not @c NULL, the ID used in the register request is returned in
 *           the @c id argument. The caller must free this buffer using the @c
 *           bps_free() function.  This same ID will be delivered in the
 *           corresponding @c #MEDIAPLAYER_REGISTER_RESULT event.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_register(const char *name, int priority, int audio_type, int volume_overlay, char **id);

/**
 * @brief Deprecated: Register a button to a forwarding action
 *        
 * @deprecated Use @c mediaplayer_register_button() instead.
 *
 * The @c mediaplayer_button() function registers a button to a forwarding
 * action.
 *
 * @param button1 The first button. This must be one of the values of the @c
 *                #media_button_t enumeration. This value cannot be @c
 *                #MEDIA_BUTTON_NONE.
 * @param button2 The optional second button. This must be one of the values of
 *                the @c #media_button_t enumeration. If the value is not @c
 *                #MEDIA_BUTTON_NONE, the function registers the action to be
 *                taken when the user presses @c button1 and @c button2
 *                simultaneously.
 * @param length The length of the button press. Use one of the values of the @c
 *               #media_button_length_t enumeration.
 * @param action The action. Use one of the values of the @c #media_action_t
 *               enumeration. If you use a value of @c #MEDIA_ACTION_FORWARD,
 *               the button notifications are forwarded to the application as @c
 *               #MEDIAPLAYER_BUTTON events and the @c path argument should not
 *               be specified. Use of @c #MEDIA_ACTION_LAUNCH is deprecated and
 *               the registration will fail.
 * @param path The path. This is only required when @c action is @c
 *             #MEDIA_ACTION_LAUNCH, not required otherwise. However, use of @c
 *             #MEDIA_ACTION_LAUNCH is deprecated and the registration will
 *             fail.
 * @param id When this is not a @c NULL value, the ID used in the button request
 *           is returned when the function completes. The caller must free this
 *           buffer using the @c bps_free() function. The same ID is also
 *           delivered in the corresponding @c #MEDIAPLAYER_BUTTON_RESULT event.
 *           
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_button(int button1, int button2, int length, int action, const char *path, char **id) BPS_DEPRECATED;

/**
 * @brief Register a button to a forwarding action
 *        
 * The @c mediaplayer_register_button() function registers a button to forward a
 * @c #MEDIAPLAYER_BUTTON event to the application.  A button event will arrive
 * when the user releases the button, i.e., on button up.
 *
 * There are various combinations of button events that you can register for:
 * 
 * - a press of a single button
 * - a pair of buttons pressed simultaneously
 * - short or medium button presses, or both
 * - a button event on button down instead of button up
 *
 * To receive both short and medium button events for the same button or pair of
 * buttons, you will need to call this function twice, one for each button
 * length.
 *
 * To receive the button event on button down, you must register for both short
 * and medium button lengths.  When registering the short button length, set the
 * @c immediate parameter to @c true.  You will receive a button event with a
 * short button length as soon as the button is pressed down.  Even thought you
 * will not receive medium button length events, you must register for them to
 * get immediate button down events.
 *
 * @param button1 The first button. This must be one of the values of the @c
 *                #media_button_t enumeration. This value cannot be @c
 *                #MEDIA_BUTTON_NONE.
 * @param button2 The optional second button. This must be one of the values of
 *                the @c #media_button_t enumeration. If the value is not @c
 *                #MEDIA_BUTTON_NONE, the function registers the action to be
 *                taken when the user presses @c button1 and @c button2
 *                simultaneously.
 * @param length The length of the button press. Use one of the values of the @c
 *               #media_button_length_t enumeration.
 * @param immediate This flag is effective only when registering a short button
 *                  press.  This flag only affects behaviour when both a short
 *                  button press and a medium button press are registered for
 *                  the same button or pair of buttons.  If this parameter is
 *                  set to @c false when registering a short button press, then
 *                  either a short button press or a medium button press will be
 *                  reported.  If this parameter is set to @c true when
 *                  registering a short button press, then only a short button
 *                  press will be reported, but it will be reported immediately
 *                  when the button is pressed down, and not on button up.  You
 *                  must also register the medium button press to get this
 *                  behaviour.
 * @param id When this is not a @c NULL value, the ID used in the button request
 *           is returned when the function completes. The caller must free this
 *           buffer using the @c bps_free() function. The same ID is also
 *           delivered in the corresponding @c #MEDIAPLAYER_BUTTON_RESULT event.
 *           
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int mediaplayer_register_button(int button1, int button2, int length, bool immediate, char **id);

/**
 * @brief Deregister a button to a forwarding action
 *        
 * The @c mediaplayer_deregister_button() function deregisters a previously
 * registered button from forwarding a @c #MEDIAPLAYER_BUTTON event to the
 * application.
 *
 * @param button1 The first button. This must be one of the values of the @c
 *                #media_button_t enumeration. This value cannot be @c
 *                #MEDIA_BUTTON_NONE.
 * @param button2 The optional second button. This must be one of the values of
 *                the @c #media_button_t enumeration. If the value is not @c
 *                #MEDIA_BUTTON_NONE, the function registers the action to be
 *                taken when the user presses @c button1 and @c button2
 *                simultaneously.
 * @param length The length of the button press. Use one of the values of the @c
 *               #media_button_length_t enumeration.
 * @param id When this is not a @c NULL value, the ID used in the button request
 *           is returned when the function completes. The caller must free this
 *           buffer using the @c bps_free() function. The same ID is also
 *           delivered in the corresponding @c #MEDIAPLAYER_BUTTON_RESULT event.
 *           
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int mediaplayer_deregister_button(int button1, int button2, int length, char **id);

/**
 * @brief Set the state of the media player
 *
 * The @c mediaplayer_set_state() function sets the state of the media player to
 * a given state.
 *
 * @param state The state to set the media player to, must be one of the value
 *              of the @c #media_state_t enumeration.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_set_state(int state);

/**
 * @brief Create a metadata structure
 *
 * The @c mediaplayer_metadata_create() function creates a metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to populate.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_create(mediaplayer_metadata_t **metadata);

/**
 * @brief Destroy a metadata structure
 *
 * The @c mediaplayer_metadata_destroy() function destroys a metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to destroy.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void mediaplayer_metadata_destroy(mediaplayer_metadata_t **metadata);

/**
 * @brief Set the artist in a metadata structure
 *
 * The @c mediaplayer_metadata_set_artist() function sets the artist in the
 * given metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param artist The artist.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_artist(mediaplayer_metadata_t *metadata, const char *artist);

/**
 * @brief Set the album in a metadata structure
 *
 * The @c mediaplayer_metadata_set_album() function sets the album in the given
 * metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param album The album.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_album(mediaplayer_metadata_t *metadata, const char *album);

/**
 * @brief Set the track in a metadata structure
 *
 * The @c mediaplayer_metadata_set_track() function sets the track in the given
 * metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param track The track.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_track(mediaplayer_metadata_t *metadata, const char *track);

/**
 * @brief Set the position in a metadata structure
 *
 * The @c mediaplayer_metadata_set_position() function sets the position in the
 * given metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param position The position.  Use a negative number to leave position
 *                 unspecified.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_position(mediaplayer_metadata_t *metadata, int position);

/**
 * @brief Set the duration in a metadata structure
 *
 * The @c mediaplayer_metadata_set_duration() function sets the duration in the
 * given metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param duration The duration.  Use a negative number to leave duration
 *                 unspecified.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_duration(mediaplayer_metadata_t *metadata, int duration);

/**
 * @brief Set the album artwork in a metadata structure
 *
 * The @c mediaplayer_metadata_set_album_artwork() function sets the album
 * artwork in the given metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param album_artwork The album artwork.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_album_artwork(mediaplayer_metadata_t *metadata, const char *album_artwork);

/**
 * @brief Set the @e next @e track enabled state in a metadata structure
 *
 * The @c mediaplayer_metadata_set_next_enabled() function sets the @e next
 * @e track enabled state in the given metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param enabled The enabled state.  @c true indicates enabled,
 *                @c false indicates disabled.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_next_enabled(mediaplayer_metadata_t *metadata, bool enabled);

/**
 * @brief Set the @e previous @e track enabled state in a metadata structure
 *
 * The @c mediaplayer_metadata_set_previous_enabled() function sets the
 * @e previous @e track enabled state in the given metadata structure.
 *
 * @param metadata The @c #mediaplayer_metadata_t structure to update.
 *
 * @param enabled The enabled state.  @c true indicates enabled,
 *                @c false indicates disabled.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_metadata_set_previous_enabled(mediaplayer_metadata_t *metadata, bool enabled);

/**
 * @brief Sets the metadata of the currently playing track
 *
 * The @c mediaplayer_set_metadata() function sets the metadata of the currently
 * playing track.
 *
 * @param metadata The metadata of the currently playing track.
 *
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_set_metadata(mediaplayer_metadata_t *metadata);

/**
 * @brief Retrieve the ID from a Media player event
 *
 * The @c mediaplayer_event_get_id() function extracts the ID from the specified
 * Media player event.
 *
 * @param event The Media player event to extract the ID from.
 * @return The ID of the Media player event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * mediaplayer_event_get_id(bps_event_t *event);

/**
 * @brief Retrieve the command from the @c MEDIAPLAYER_COMMAND event
 *
 * The @c mediaplayer_event_get_command() function extracts the command from the
 * specified @c #MEDIAPLAYER_COMMAND event.
 *
 * @param event The @c #MEDIAPLAYER_COMMAND event to extract the command from.
 *
 * @return The command, one of the values of the @c #media_command_t
 *         enumeration, or @c BPS_FAILURE with @c errno value set on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_event_get_command(bps_event_t *event);

/**
 * @brief Retrieve the first button from the @c MEDIAPLAYER_BUTTON event
 *
 * The @c mediaplayer_event_get_button1() function extracts the first button
 * from the specified @c #MEDIAPLAYER_BUTTON event.
 *
 * @param event The @c #MEDIAPLAYER_BUTTON event to extract the button from.
 *
 * @return The first button, one of the values of the @c #media_button_t
 *         enumeration, or @c BPS_FAILURE with @c errno value set on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_event_get_button1(bps_event_t *event);

/**
 * @brief Retrieve the second button from the @c MEDIAPLAYER_BUTTON event
 *
 * The @c mediaplayer_event_get_button2() function extracts the second button
 * from the specified @c #MEDIAPLAYER_BUTTON event.
 *
 * @param event The @c #MEDIAPLAYER_BUTTON event to extract the button from.
 *
 * @return The second button, one of the values of the @c #media_button_t
 *         enumeration, or @c BPS_FAILURE with @c errno value set on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_event_get_button2(bps_event_t *event);

/**
 * @brief Retrieve the button length of time a button was held down from the @c
 *        MEDIAPLAYER_BUTTON event
 *
 * The @c mediaplayer_event_get_button_length() function extracts the length of
 * time the button was held down from the specified @c #MEDIAPLAYER_BUTTON
 * event.
 *
 * @param event The @c #MEDIAPLAYER_BUTTON event to extract the length from.
 *
 * @return The length, one of the values of the @c #media_button_length_t
 *         enumeration, or @c BPS_FAILURE with @c errno value set on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int mediaplayer_event_get_button_length(bps_event_t *event);

__END_DECLS

#endif /* include guard */
