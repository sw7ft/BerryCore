/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file audiomixer.h
 *
 * @brief Functions to interact with the audio mixer
 * 
 * The audio mixer service reads audio mixer change events, such as when the
 * volume level or gain of mixer channels changes.  You can also use the audio
 * mixer service to set and get different audio attributes, such as volume,
 * gain, and mute status.
 *
 * For example, using the audio mixer service allows an application to receive
 * notifications when a headset is present, or when the speaker volume is
 * muted.  The application can also set headset volume, speaker volume, and so
 * on.
 *
 * You should call the function @c audiodevice_get_info() to verify that the
 * audio device you want to use exists on the platform. If the function returns
 * @c BPS_FAILURE, then the specified @c #audiodevice_device_t audio device does
 * not exist and using the unavailable audio device type may result in program
 * error or termination.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_AUDIOMIXER_H_INCLUDED
#define _BPS_AUDIOMIXER_H_INCLUDED

#include <sys/platform.h>
#include <stdbool.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible audio mixer events
 * 
 * This enumeration defines the possible audio mixer events.  Currently, there
 * is only one event.
 * @anonenum bps_audiomixer_events Audio mixer events 
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single audio mixer event, which contains all the information about
     * the current audio mixer status.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INFO             = 0x01,
};

/**
 * @brief Output channels
 * 
 * This enumeration defines the different output channels that can be available.
 * Only one output channel can be available at a time, and you can determine
 * the available output channel by calling @c audiomixer_event_get_available().
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The default output channel.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_DEFAULT   = 0,

    /**
     * The internal speaker.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_SPEAKER   = 1,

    /**
     * The headphone jack.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_HEADPHONE = 2,

    /**
     * A headset with microphone input.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_HEADSET   = 3,

    /**
     * The phone receiver on the device.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_HANDSET   = 4,

    /**
     * A Bluetooth Advanced Audio Distribution Profile (A2DP) connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_A2DP      = 5,

    /**
     * A Bluetooth Synchronous Connection Oriented/Hands-Free Profile (SCO/HFP)
     * connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_BTSCO     = 6,

    /**
     * A Hearing Aid Compatibility (HAC) coil used for hearing aids.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_HAC       = 7,

    /**
     * The HDMI audio channel.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_HDMI      = 8,

    /**
     * A TOSLINK optical audio cable connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_TOSLINK   = 9,

    /**
     * A TTY telecommunication device for the hearing impaired (connected
     * through the headphone jack).
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_TTY       = 10,

    /**
     * A device connected through the headset jack.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_OUTPUT_LINEOUT   = 11,
} audiomixer_output_t;

/**
 * @brief Input channels
 * 
 * This enumeration defines the different input channels that are available.
 * Note that some input channels are simply aliases for the default input
 * channel @c AUDIOMIXER_INPUT_DEFAULT.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The default input channel.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_DEFAULT    = AUDIOMIXER_OUTPUT_DEFAULT,

    /**
     * The default input channel, for backwards compatibility.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT            = AUDIOMIXER_OUTPUT_DEFAULT,

    /**
     * The internal speaker.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_SPEAKER    = AUDIOMIXER_OUTPUT_SPEAKER,

    /**
     * The headphone jack.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_HEADPHONE  = AUDIOMIXER_OUTPUT_HEADPHONE,

    /**
     * A headset with microphone input.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_HEADSET    = AUDIOMIXER_OUTPUT_HEADSET,

    /**
     * The phone receiver on the device.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_HANDSET    = AUDIOMIXER_OUTPUT_HANDSET,

    /**
     * A Bluetooth Advanced Audio Distribution Profile (A2DP) connection.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_A2DP       = AUDIOMIXER_OUTPUT_A2DP,

    /**
     * A Bluetooth Synchronous Connection Oriented/Hands-Free Profile (SCO/HFP)
     * connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_BTSCO      = AUDIOMIXER_OUTPUT_BTSCO,

    /**
     * A Hearing Aid Compatibility (HAC) coil used for hearing aids.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_HAC        = AUDIOMIXER_OUTPUT_HAC,

    /**
     * The HDMI audio channel.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_HDMI       = AUDIOMIXER_OUTPUT_HDMI,

    /**
     * A TOSLINK optical audio cable connection.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_TOSLINK    = AUDIOMIXER_OUTPUT_TOSLINK,

    /**
     * A TTY telecommunication device for the hearing impaired (connected
     * through the headphone jack).
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_TTY        = AUDIOMIXER_OUTPUT_TTY,

    /**
     * A device connected through the headset jack.
     *
     * If this channel is specified, the default input channel is used.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_INPUT_LINEOUT    = AUDIOMIXER_OUTPUT_LINEOUT,
} audiomixer_input_t;

/**
 * @brief Audio modes
 *
 * This enumeration defines the different audio modes that may be active.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized mode (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_MODE_UNRECOGNIZED = 0,

    /**
     * The audio audio mode.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_MODE_AUDIO        = 1,

    /**
     * The video audio mode.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_MODE_VIDEO        = 2,

    /**
     * The record audio mode.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_MODE_RECORD       = 3,

    /**
     * The voice audio mode.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIOMIXER_MODE_VOICE        = 4,
} audiomixer_mode_t;

/**
 * @brief Start receiving audio mixer events
 * 
 * The @c audiomixer_request_events() function starts to deliver audio mixer
 * events to the application using BPS.  Events will be posted to the currently
 * active channel.
 * 
 * @param flags The types of events to deliver. A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 * 
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_request_events(int flags);

/**
 * @brief Stop receiving audio mixer events
 *
 * The @c audiomixer_stop_events() function stops audio mixer events from being
 * delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the audio mixer service
 * 
 * The @c audiomixer_get_domain() function gets the unique domain ID for the
 * audio mixer service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is an
 * audio mixer event, and respond accordingly.
 *
 * @return The domain ID for the audio mixer service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_get_domain(void);

// Set messages

/**
 * @brief Set an output channel's volume
 * 
 * The @c audiomixer_set_output_level() function sets the volume of the
 * specified output channel to the specified level.  This function can only be
 * used for audio devices that have full volume control.
 * 
 * @param channel The output channel to set the volume for.
 * @param level The new volume for the output channel.  This value must be
 * between 0.0 and 100.0.
 * 
 * @return @c BPS_SUCCESS if the volume was set successfully, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_set_output_level(audiomixer_output_t channel, float level);

/**
 * @brief Set an input channel's gain
 * 
 * The @c audiomixer_set_input_level() function sets the gain of the specified
 * input channel to the specified level.  This function can only be used for
 * audio devices that have full volume control.
 * 
 * @param channel The input channel to set the gain for.
 * @param level The new gain for the input channel.  This value must be between
 * 0.0 and 100.0.
 * 
 * @return @c BPS_SUCCESS if the gain was set successfully, @c BPS_FAILURE with
 * @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_set_input_level(audiomixer_input_t channel, float level);

/**
 * @brief Adjust an output channel's volume
 * 
 * The @c audiomixer_adjust_output_level() function adjusts the volume of the
 * specified output channel by the specified amount.  This function can only be
 * used for audio devices that have full volume control.
 * 
 * @param channel The output channel to adjust the volume for.
 * @param level The amount to adjust the channel's volume.  Final level will
 *              not exceed the range of 0.0 to 100.0.
 * 
 * @return @c BPS_SUCCESS if the volume was adjusted successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_adjust_output_level(audiomixer_output_t channel, float level);

/**
 * @brief Adjust an input channel's gain
 * 
 * The @c audiomixer_adjust_input_level() function adjusts the gain of the
 * specified input channel by the specified amount.  This function can only be
 * used for audio devices that have full volume control.
 * 
 * @param channel The input channel to adjust the gain for.
 * @param level The amount to adjust the channel's gain.  Final level will not
 *              exceed the range of 0.0 to 100.0.
 * 
 * @return @c BPS_SUCCESS if the gain was adjusted successfully, @c BPS_FAILURE
 * with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_adjust_input_level(audiomixer_input_t channel, float level);

/**
 * @brief Mute or un-mute an output channel
 * 
 * The @c audiomixer_set_output_mute() function mutes or un-mutes the specified
 * output channel.  This function can only be used for audio devices that have
 * full volume control.
 * 
 * @param channel The output channel to mute or un-mute.
 * @param is_mute If @c true the output channel is muted, if @c false the
 * output channel is un-muted.
 * 
 * @return @c BPS_SUCCESS if the channel was muted or un-muted successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_set_output_mute(audiomixer_output_t channel, bool is_mute);

/**
 * @brief Mute or un-mute an input channel
 * 
 * The @c audiomixer_set_input_mute() function mutes or un-mutes the specified
 * input channel.  This function can only be used for audio devices that have
 * full volume control.
 * 
 * @param channel The input channel to mute or un-mute.
 * @param is_mute If @c true the input channel is muted, if @c false the
 * input channel is un-muted.
 *
 * @return @c BPS_SUCCESS if the channel was muted or un-muted successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_set_input_mute(audiomixer_input_t channel, bool is_mute);

/**
 * @brief Toggle an output channel's mute setting
 * 
 * The @c audiomixer_toggle_output_mute() function toggles the mute setting of
 * the specified output channel.  This function can only be used for audio
 * devices that have full volume control.
 * 
 * @param channel The output channel to toggle the mute setting for.
 * 
 * @return @c BPS_SUCCESS if the mute setting was toggled successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_toggle_output_mute(audiomixer_output_t channel);

/**
 * @brief Toggle an input channel's mute setting
 * 
 * The @c audiomixer_toggle_input_mute() function toggles the mute setting of
 * the specified input channel.  This function can only be used for audio
 * devices that have full volume control.
 * 
 * @param channel The input channel to toggle the mute setting for.
 * 
 * @return @c BPS_SUCCESS if the mute setting was toggled successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_toggle_input_mute(audiomixer_input_t channel);

// Get messages

/**
 * @brief Get an output channel's volume
 *
 * The @c audiomixer_get_output_level() function gets the volume of the
 * specified output channel.  This function can only be used for audio devices
 * that have full volume control.
 *
 * @param channel The output channel to get the volume for.
 * @param level The output channel's current volume.  This value is between 0.0
 * and 100.0.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_get_output_level(audiomixer_output_t channel, float* level);

/**
 * @brief Get an input channel's gain
 * 
 * The @c audiomixer_get_input_level() function gets the gain of the specified
 * input channel.  This function can only be used for audio devices that have
 * full volume control.
 *
 * @param channel The input channel to get the gain for.
 * @param level The input channel's current gain.  This value is between 0.0 and
 * 100.0.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_get_input_level(audiomixer_input_t channel, float* level);

/**
 * @brief Get an output channel's mute status
 *
 * The @c audiomixer_get_output_mute() function gets the mute status of the
 * specified output channel.  This function can only be used for audio devices
 * that have full volume control.
 *
 * @param channel The output channel to get the mute status for.
 * @param is_mute If @c true the output channel is muted, if @c false the
 * output channel is not muted.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_get_output_mute(audiomixer_output_t channel, bool *is_mute);

/**
 * @brief Get an input channel's mute status
 *
 * The @c audiomixer_get_input_mute() function gets the mute status of the
 * specified input channel.  This function can only be used for audio devices
 * that have full volume control.
 *
 * @param channel The input channel to get the mute status for.
 * @param is_mute If @c true the input channel is muted, if @c false the input
 * channel is not muted.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_get_input_mute(audiomixer_input_t channel, bool* is_mute);

/**
 * @brief Increase an output channel's volume
 * 
 * The @c audiomixer_increase_output_level() function increases the volume of
 * the specified output channel by an unspecified amount.  This function can be
 * used for audio devices that have simple or full volume control.
 * 
 * @param channel The output channel to increase the volume for.
 * 
 * @return @c BPS_SUCCESS if the volume was increased successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_increase_output_level(audiomixer_output_t channel);

/**
 * @brief Decrease an output channel's volume
 * 
 * The @c audiomixer_decrease_output_level() function decreases the volume of
 * the specified output channel by an unspecified amount.  This function can be
 * used for audio devices that have simple or full volume control.
 * 
 * @param channel The output channel to decrease the volume for.
 * 
 * @return @c BPS_SUCCESS if the volume was decreased successfully,
 * @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiomixer_decrease_output_level(audiomixer_output_t channel);

/**
 * @brief Get the currently active audio mode from an @c AUDIOMIXER_INFO event
 *
 * The @c audiomixer_event_get_mode() function extracts the audio mode currently
 * active from an @c AUDIOMIXER_INFO event.
 *
 * @param event The @c AUDIOMIXER_INFO event to extract the mode from.
 *
 * @return The currently active audio mode.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API audiomixer_mode_t audiomixer_event_get_mode(bps_event_t *event);

/**
 * @brief Get an output channel's volume from an @c AUDIOMIXER_INFO event
 *
 * The @c audiomixer_event_get_output_level() function extracts the volume of
 * the specified output channel from an @c AUDIOMIXER_INFO event.  This function
 * can only be used for audio devices that have full volume control.
 *
 * @param event The @c AUDIOMIXER_INFO event to extract the volume from.
 * @param channel The output channel to get the volume for.
 *
 * @return The output channel's volume.  This value is between 0.0 and 100.0.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float audiomixer_event_get_output_level(bps_event_t *event, audiomixer_output_t channel);

/**
 * @brief Get an input channel's gain from an @c AUDIOMIXER_INFO event
 *
 * The @c audiomixer_event_get_input_level() function extracts the gain of the
 * specified input channel from an @c AUDIOMIXER_INFO event.  This function can
 * only be used for audio devices that have full volume control.
 *
 * @param event The @c AUDIOMIXER_INFO event to extract the gain from.
 * @param channel The input channel to get the gain for.
 *
 * @return The input channel's gain.  This value is between 0.0 to 100.0.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float audiomixer_event_get_input_level(bps_event_t *event, audiomixer_input_t channel);

/**
 * @brief Get an output channel's mute status from an @c AUDIOMIXER_INFO event
 *
 * The @c audiomixer_event_get_output_mute() function extracts the mute status
 * of the specified output channel from an @c AUDIOMIXER_INFO event.  This
 * function can only be used for audio devices that have full volume control.
 *
 * @param event The @c AUDIOMIXER_INFO event to extract the mute status from.
 * @param channel The output channel to get the mute status for.
 *
 * @return @c true if the output channel is muted, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiomixer_event_get_output_mute(bps_event_t *event, audiomixer_output_t channel);

/**
 * @brief Get an input channel's mute status from an @c AUDIOMIXER_INFO event
 *
 * The @c audiomixer_event_get_input_mute() function extracts the mute status of
 * the specified input channel from an @c AUDIOMIXER_INFO event.  This function
 * can only be used for audio devices that have full volume control.
 *
 * @param event The @c AUDIOMIXER_INFO event to extract the mute status from.
 * @param channel The input channel to get the mute status for.
 *
 * @return @c true if the input channel is muted, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiomixer_event_get_input_mute(bps_event_t *event, audiomixer_input_t channel);

/**
 * @brief Get the available output channel
 * 
 * The @c audiomixer_event_get_available() function extracts the available output
 * channel from an @c AUDIOMIXER_INFO event.
 *
 * @param event The @c AUDIOMIXER_INFO event to extract the available output
 * channel from.
 * 
 * @return The available output channel.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API audiomixer_output_t audiomixer_event_get_available(bps_event_t *event);

__END_DECLS

#endif
