/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file mediacommon.h
 *
 * @brief Definitions common to media services
 *
 * This file defines enumerations common to Media services that are defined in
 * mediacontroller.h and mediaplayer.h.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_MEDIACOMMON_H_INCLUDED
#define _BPS_MEDIACOMMON_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Media commands
 *
 * This enumeration defines the available media commands.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized media command (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_UNRECOGNIZED    =  0,

    /**
     * Request to play the current track.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_PLAY            =  1,

    /**
     * Request to pause the current track.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_PAUSE           =  2,

    /**
     * Request to stop the current track.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_STOP            =  3,

    /**
     * Request to skip to the next track.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_NEXT_TRACK      =  4,

    /**
     * Request to skip to the beginning of the current track,
     * or to the previous track.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_PREVIOUS_TRACK  =  5,

    /**
     * Request to start or resume sending metadata updates.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_SEND_DATA       =  6,

    /**
     * Request to stop sending metadata updates.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_HOLD_DATA       =  7,

    /**
     * Request to enter fast forward mode.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_FAST_FORWARD    =  8,

    /**
     * Request to enter rewind mode.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_COMMAND_REWIND          =  9,
} media_command_t;

/**
 * @brief Media states
 *
 * This enumeration defines the available media states.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized media state (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_STATE_UNRECOGNIZED      =  0,

    /**
     * The media is stopped.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_STATE_STOPPED           =  1,

    /**
     * The media is paused.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_STATE_PAUSED            =  2,

    /**
     * The media is playing.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_STATE_PLAYING           =  3,

    /**
     * The media has changed track.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_STATE_TRACK_CHANGE      =  4,
} media_state_t;

/**
 * @brief Media priorities
 *
 * This enumeration defines the available media priorities.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The media has low priority.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_PRIORITY_LOW            =  0,

    /**
     * The media has high priority. Only phone or VoIP applications should use
     * a high priority.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_PRIORITY_HIGH           =  1,
} media_priority_t;

/**
 * @brief Media audio types
 *
 * This enumeration defines the available media audio types.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The media is a general audio type.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_AUDIO_TYPE_GENERAL      =  0,

    /**
     * The media is a voice audio type.  Only phone or VoIP applications should
     * use the voice audio type.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_AUDIO_TYPE_VOICE        =  1,
} media_audio_type_t;

/**
 * @brief Media volume overlays
 *
 * This enumeration defines the available media volume overlays.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The plain volume overlay.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_VOLUME_OVERLAY_PLAIN    =  0,

    /**
     * The fancy volume overlay, which has next and previous buttons.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_VOLUME_OVERLAY_FANCY    =  1,
} media_volume_overlay_t;

/**
 * @brief Media buttons
 *
 * This enumeration defines the available media buttons.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * No button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_NONE             =  0,

    /**
     * Plus button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_PLUS             =  1,

    /**
     * Minus button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_MINUS            =  2,

    /**
     * Volume up button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_VOLUME_UP        =  3,

    /**
     * Volume down button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_VOLUME_DOWN      =  4,

    /**
     * Play button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_PLAY             =  5,

    /**
     * Pause button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_PAUSE            =  6,

    /**
     * Play/Pause button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_PLAY_PAUSE       =  7,

    /**
     * Stop button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_STOP             =  8,

    /**
     * Forward button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_FORWARD          =  9,

    /**
     * Rewind button.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_REWIND           = 10,

    /**
     * Next button.
     *
     * @since BlackBerry 10.2.0
     */
    MEDIA_BUTTON_NEXT             = 11,

    /**
     * Previous button.
     *
     * @since BlackBerry 10.2.0
     */
    MEDIA_BUTTON_PREVIOUS         = 12,

    /**
     * Hookswitch button.
     *
     * @since BlackBerry 10.2.0
     */
    MEDIA_BUTTON_HOOKSWITCH       = 13,
} media_button_t;

/**
 * @brief Timeframes a media button is held down for
 *
 * This enumeration defines the length of time a media button can be held down
 * for.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized length (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_LENGTH_UNRECOGNIZED     =  0,

    /**
     * The button is held for a short length of time (less than 600 ms).
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_LENGTH_SHORT            =  1,

    /**
     * The button is held for a medium length of time (more than 600 ms).
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_LENGTH_MEDIUM           =  2,

    /**
     * Deprecated: The button is held for a long length of time.
     *
     * @deprecated Long button presses are treated as medium button presses.
     * 
     * @since BlackBerry 10.0.0
     */
    MEDIA_BUTTON_LENGTH_LONG             =  3,
} media_button_length_t;

/**
 * @brief Media actions
 *
 * This enumeration defines the available actions for a button press.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Deprecated: A launch action.
     *
     * @deprecated Launch actions are no longer supported and will fail.
     * 
     * @since BlackBerry 10.0.0
     */
    MEDIA_ACTION_LAUNCH           =  0,

    /**
     * A forwarding action.
     *
     * @since BlackBerry 10.0.0
     */
    MEDIA_ACTION_FORWARD          =  1,
} media_action_t;


__END_DECLS

#endif /* include guard */
