#ifndef _AUDIO_MANAGER_ROUTING_H_INCLUDED
#define _AUDIO_MANAGER_ROUTING_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <limits.h>
#if SND_LIB_MAJOR == 1
#include <alsa/asoundlib.h>
#else
#include <sys/asoundlib.h>
#endif
#include <audio/audio_manager_device.h>

/**
 * @file audio_manager_routing.h
 *
 * @brief Definitions for supporting audio routing configurations
 *
 * The audio manager service maintains the audio routing logic based on
 * registered audio sources. This file defines routing properties
 * and provides functions to work with  audio routing configurations.
 *
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief Names for audio types
 */
#ifndef AUDIO_TYPE_NAMES_EXTENDED
#define AUDIO_TYPE_NAMES_EXTENDED
#endif

/**
 * @brief The audio type names
 */
#define AUDIO_TYPE_NAMES        \
{                               \
    "voice",                    \
    "ringtone",                 \
    "voicerecognition",         \
    "texttospeech",             \
    "videochat",                \
    "voicerecording",           \
    "multimedia",               \
    "inputfeedback",            \
    "default",                  \
    "alert",                    \
    "voicetones",               \
    "soundeffect",              \
    "pushtotalk",               \
    "reserved_0",               \
    "cmas",                     \
    "alarm",                    \
    "screenreader",             \
    AUDIO_TYPE_NAMES_EXTENDED   \
}

/**
 * @brief The supported audio types
 *
 * Use the enumerated type that describe best describes
 * the usage of the audio source. For example, if the audio
 * source is used as voice, then use choose @c  AUDIO_TYPE_VOICE, however
 * if the audio source is for a ring tone, use @c AUDIO_TYPE_RINGTONE.

 */
typedef enum {
    /**
     * The audio source is best used for voice.
     */
    AUDIO_TYPE_VOICE,
    /**
     * The audio source is best used for ringtone.
     */
    AUDIO_TYPE_RINGTONE,
    /**
     * The audio source is best used for voice recognition systems.
     */
    AUDIO_TYPE_VOICE_RECOGNITION,
    /**
     * The audio source is best used for text-to-speech.
     */
    AUDIO_TYPE_TEXT_TO_SPEECH,
    /**
     * The audio source is best used for video chat.
     */
    AUDIO_TYPE_VIDEO_CHAT,
    /**
     * The audio source is best used for a voice recording.
     */
    AUDIO_TYPE_VOICE_RECORDING,
    /**
     * The audio source is best used for multimedia.
     */
    AUDIO_TYPE_MULTIMEDIA,
    /**
     * The audio source is best used for user input feedback.
     */
    AUDIO_TYPE_INPUT_FEEDBACK,
    /**
     * The audio source used as default.
     */
    AUDIO_TYPE_DEFAULT,
    /**
     * The audio source is best used to provide alert or notification sound.
     */
    AUDIO_TYPE_ALERT,
    /**
     * The audio source is best used to provide voice tone.
     */
    AUDIO_TYPE_VOICE_TONES,
    /**
     * The audio source is best used to provide a high priority sound effect
     * or notification.
     */
    AUDIO_TYPE_SOUND_EFFECT,
    /**
     * The audio source is best used to for push-to-talk sound systems.
     */
    AUDIO_TYPE_PUSH_TO_TALK,
    /**
     * The reserved audio type 0.
     */
    AUDIO_TYPE_RESERVED_0,
    /**
     * The audio source is best used for Commercial Mobile Alert System (CMAS)
     * emergency broadcast systems.
     */
    AUDIO_TYPE_CMAS,
    /**
     * The audio source is best used to as an alarm.
     */
    AUDIO_TYPE_ALARM,
    /**
     * The audio source is best used for screen readers. Screen readers are
     * used for accessibility.
     */
    AUDIO_TYPE_SCREEN_READER,
    /**
     * The total number of all audio types.
     */
    AUDIO_TYPE_COUNT,
    /**
     * The audio type is unchanged if the specified value is specified.
     */
    AUDIO_TYPE_UNCHANGED = INT_MAX,
} audio_manager_audio_type_t;

/**
 * @brief Audio runtime names.
 */
#define AUDIO_RUNTIME_NAMES     \
{                               \
    "native",                   \
    "android"                   \
}


/**
 * @brief The supported audio runtimes
 *
 * This enumeration defines the supported audio runtimes that the audio
 * manager service supports.
 */
typedef enum {
    /**
     * The audio type used by clients that are directly designed for the QNX
     * Neutrino RTOS or BlackBerry 10 OS.
     */
    AUDIO_RUNTIME_NATIVE,
    /**
     * The audio type that is used by clients designed for Android.
     */
    AUDIO_RUNTIME_ANDROID,
    /**
     * The total number of supported runtimes.
     */
    AUDIO_RUNTIME_COUNT,
} audio_manager_runtime_t;


/**
 * @brief The supported reset conditions of the routing preference settings
 *
 * This enumeration defines the supported reset conditions for the routing
 * preferences that are using @c audio_manager_set_handle_type().
 */
typedef enum {
    /**
     * The preferences are never reset.
     */
    SETTINGS_NEVER_RESET                                    = 0,
    /**
     * The preferences are reset when any device disconnects.
     */
    SETTINGS_RESET_ON_DEVICE_DISCONNECTION                  = 1,
    /**
     * The preferences are reset when any device connects.
     */
    SETTINGS_RESET_ON_DEVICE_CONNECTION                     = (1<<1),
    /**
     * The preferences are reset when the preferred device disconnects.
     */
    SETTINGS_RESET_ON_PREFERRED_DEVICE_DISCONNECTION        = (1<<2),
    /**
     * The preferences are reset when the higher priority device connects.
     */
    SETTINGS_RESET_ON_HIGHER_PRIORITY_DEVICE_CONNECTION     = (1<<3),
} audio_manager_settings_reset_condition_t;

/**
 * @brief Get the value representing the provided runtime name
 *
 * Use @c audio_manager_get_runtime_from_name() to return handle @c
 * #audio_manager_runtime_t value representing that representing the provided
 * audio runtime name.
 *
 * @param runtime_name The name of the runtime to query.
 *
 * @return The audio manager handle runtime. A value of -1 is returned if the
 *         name can't be found.
 */
audio_manager_runtime_t audio_manager_get_runtime_from_name( const char * runtime_name );

/**
 * @brief Get the name of an audio runtime
 *
 * The @c audio_manager_get_name_from_runtime() function returns the name of
 * an audio runtime.
 *
 * @param runtime The audio runtime to query.
 *
 * @return The name of the audio manager runtime from @c AUDIO_RUNTIME_NAMES.
 */
const char* audio_manager_get_name_from_runtime( audio_manager_runtime_t runtime );

/**
 * @brief Get the value representing the provided audio type name
 *
 * Use @c audio_manager_get_type_from_name() to return the @c
 * #audio_manager_audio_type_t that corresponds to the provided audio type
 * name.
 *
 * @param type_name The name of the type to query.
 *
 * @return The audio manager handle type. A value of -1 is returned if the name
 *         can't be found.
 */
audio_manager_audio_type_t audio_manager_get_type_from_name( const char * type_name );

/**
 * @brief Get the name of the provided audio manager type
 *
 * Use the @c audio_manager_get_name_from_type() function to return the name
 * that matches the provided @c #audio_manager_audio_type_t value.
 *
 * @param type The audio manager type to query.
 *
 * @return The name of the audio manager type from @c AUDIO_TYPE_NAMES. A NULL
 *         value is returned if the provided type can't be found.
 */
const char* audio_manager_get_name_from_type( audio_manager_audio_type_t type );

/**
 * @brief Get the audio manager handle for the provided audio type
 *
 * An audio manager handle is used to track each audio source.
 * Use @c audio_manager_get_handle() to return a handle
 * based on the audio type and a flag that indicates whether
 * the handle is immediately activated.
 *
 * @param type The type of audio type to query from the audio manager service.
 * @param caller_pid The ID of the process that the audio manager handle
 *                   is allocated for. The value of zero represents the
 *                   current process ID.
 * @param start_suspended Whether the handle is to be suspended after allocation.
 *                        A value of @c true to suspend the audio source
 *                        after allocation while a value of @c false indicates
 *                        otherwise.
 * @param audioman_handle The handle to the audio source that's allocated.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_handle( audio_manager_audio_type_t type,
                              pid_t caller_pid,
                              bool start_suspended,
                              unsigned int * audioman_handle );

/**
 * @brief Get the audio manager handle for the specified audio type
 *
 * An audio manager handle is used to track each audio source.
 * Use @c audio_manager_get_handle_runtime() to return a handle to the
 * audio source based on the specified audio type and flag to indicate whether
 * the handle to the audio source is immediately activated.
 *
 * Only use this function when you use audio runtimes that implement
 * their own ducking rules. Applications should not use this function directly.
 *
 * @param type The type of the audio manager handle to query.
 * @param caller_pid The ID of the process that the audio manager handle
 *                   is allocated for. The value of zero represents the current
 *                   process ID.
 * @param start_suspended Whether the handle is to be suspended after allocation.
 *                        A value of @c true to suspend the audio source
 *                        after allocation while a value of @c false indicates
 *                        otherwise.
 * @param audioman_handle The handle to the audio source that's allocated.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_handle_for_runtime(
                                audio_manager_runtime_t runtime,
                                audio_manager_audio_type_t type,
                                pid_t caller_pid,
                                bool start_suspended,
                                unsigned int * audioman_handle );

/**
 * @brief Get a handle that's an alias to another audio manager handle
 *
 * An audio manager handle is used to track each audio source.
 * Use @c audio_manager_get_alias_handle() to return the
 * alias to another audio source. An alias to an alias source does not have
 * audio policy effect.
 *
 * @param target_audioman_handle The target audio manager handle that
 *                               the alias is created from.
 * @param audioman_handle The handle to the audio source that's allocated.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_alias_handle( unsigned int target_audioman_handle,
                                    unsigned int * audioman_handle );
/**
 * @brief Get the audio type of the specified audio manager handle
 *
 * An audio manager handle is used to track each audio source.
 * Use @c audio_manager_get_handle_type() to return the
 * audio type of the specified handle to an audio source and the
 * overrides of the default audio routing policy type. The audio
 * routing policy type contains the preferred output and input audio devices.
 *
 * @param audioman_handle The handle to the audio source that the new
 *                        type is applied to.
 * @param type The audio type that's been set on the specified
 *             audio manager handle.
 * @param pref_output The preferred output routing of the handle.
 * @param pref_input The preferred input routing of the handle.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_handle_type( unsigned int audioman_handle,
                                   audio_manager_audio_type_t *type,
                                   audio_manager_device_t *pref_output,
                                   audio_manager_device_t *pref_input );

/**
 * @brief Set the audio type of the specified audio manager handle
 *
 * An audio manager handle is used to track each audio source.
 * The @c audio_manager_set_handle_type() function sets the
 * audio type of a specified handle to the audio source and specifies the
 * option to override the default audio type routing policy. To override the
 * default audio type policy, the preferred output and input audio devices are
 * specified.
 *
 * @param audioman_handle The audio manager handle that the new
 *                        type is applied to.
 * @param type The new audio type that's set to the specified
 *             audio manager handle. If @c AUDIO_TYPE_UNCHANGED is specified,
 *             the audio type is unchanged.
 * @param pref_output The preferred output routing of the new
 *                    audio type. If @c AUDIO_DEVICE_UNCHANGED is specified,
 *                    the preferred output device is unchanged.
 * @param pref_input The preferred input routing of the new  audio type.
 *                   If @c AUDIO_DEVICE_UNCHANGED is specified, the
 * p                 referred input device is unchanged.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_handle_type( unsigned int audioman_handle,
                                   audio_manager_audio_type_t type,
                                   audio_manager_device_t pref_output,
                                   audio_manager_device_t pref_input );

/**
 * @brief Set the reset condition of the preferred input and output
 *
 * An audio manager handle is used to track each audio source.
 * Use @c audio_manager_set_handle_routing_conditions() to set the
 * reset conditions of the preferred output and input routing path. Both are
 * specified using @c audio_manager_set_handle_type().
 *
 * @param audioman_handle The audio manager handle that the conditions apply to.
 * @param routing_preference_reset_conditions The bitmask of @c
 *                                     audio_manager_settings_reset_condition_t
 *                                     that specifies more or more conditions
 *                                     that use the audio routing preferences
 *                                     that it gets set to.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_handle_routing_conditions(
        unsigned int audioman_handle,
        int routing_preference_reset_conditions );


/**
 * @brief Set the keep-alive status in the handle to the audio source
 *
 * An audio manager handle is used to track each audio source.
 * Use the @c audio_manager_set_handle_keep_alive() function to set the
 * keep-alive status to the audio manager handle. When you set the
 * keep-alive status, the device is kept in a standby status as opposed to a
 * powered off status. Setting the keep-alive status means that audio continues
 * to route to the specified even when there is no audio being played or
 * recorded. Keeping the device in a standby status can increase the consumption
 * of power.
 *
 * @param audioman_handle The audio manager handle that the keep-alive status
 *                        applies to.
 * @param direction A bitmask of @c AUDIO_INPUT or @c AUDIO_OUTPUT to control
 *                  keep-alive.
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_handle_keep_alive(
        unsigned int audioman_handle,
        int direction );


/**
 * @brief Determine the status of the specified audio manager handle
 *
 * An audio manager handle is used to track each audio source.
 * The @c audio_manager_get_handle_status() function returns the
 * activation status and binding status of the specified audio manager handle.
 *
 * @param audioman_handle The audio manager handle to query.
 * @param suspended Whether the handle is to be suspended after allocation.
 *                  A value of @c true to suspend the audio source
 *                  after allocation while a value of @c false indicates
 *                  otherwise.
 * @param bound A pointer that specifies whether handle to the audio source
 *              is bound to the PCM source. When a value of @c true is returned,
 *              it indicates that the audio manager audio manager handle is
 *              bound to a PCM handle. A value of @c false indicates otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_handle_status( unsigned int audioman_handle,
                                     bool * suspended,
                                     bool * bound );

/**
 * @brief Activate the specified audio manager handle
 *
 * An audio manager handle is used to track each audio source.
 * Use the @c audio_manager_activate_handle() to activate the specified
 * audio manager handle if it is not bound with a PCM handle.
 *
 * @param audioman_handle The audio manager handle that is being activated
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_activate_handle( unsigned int audioman_handle );


/**
 * @internal For internal use only. Do not use.
 * @brief Activate the specified audio manager handle and refresh audio
 * ducking settings
 *
 * The @c audio_manager_activate_bound_handle() function activates the
 * specified audio manager handle if it is already bound with a PCM handle
 * by @c snd_pcm_set_audioman_handle. This function is intended for use by
 * system components. Therefore, it is not suitable for all applications.
 *
 * @param audioman_handle The audio manager handle that is being
 * activated.
 * @param refresh_ducking Indicates whether refresh ducking should be enabled.
 *                        Set to @c true, when refresh ducking should be enabled;
 *                        @c false, otherwise.
 * @param cardno The identifier of the card to which the handle is bound.
 * @param devno The identifier of the device to which the handle is bound.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_activate_bound_handle( unsigned int audioman_handle,
                                         bool refresh_ducking,
                                         int cardno,
                                         int devno );


/**
 * @brief Suspend the specified audio source
 *
 * An audio manager handle is used to track each audio source.
 * Use @c audio_manager_suspend_handle() to suspend the specified handle
 * to the audio source when it is not bound with a PCM handle.
 *
 * @param audioman_handle The audio manager handle that is being
 *                        suspended.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_suspend_handle( unsigned int audioman_handle );

/**
 * @internal For internal use only. Do not use.
 * @brief Activate the specified audio manager handle and refresh audio
 * ducking settings
 *
 * The @c audio_manager_suspend_bound_handle() function suspends the
 * specified audio manager handle if it is already bound with a PCM handle
 * by @c snd_pcm_set_audioman_handle. This function is intended for use by
 * system components. Therefore, it is not suitable for all applications.
 *
 * @param audioman_handle The audio manager handle that is being
 * activated.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_suspend_bound_handle( unsigned int audioman_handle );

/**
 * @brief Release the handle to the audio source that is managed by the audio
 *        manager service
 *
 * An audio manager handle is used to track each audio source.
 * The @c audio_manager_free_handle() function frees the
 * channel associated with the audio source.
 *
 * @param audioman_handle The handle that is disassociated with the audio
 *                        source.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_free_handle( unsigned int audioman_handle );

#if SND_LIB_MAJOR == 0
/**
 * @brief Open a preferred PCM channel with the specified audio type
 *
 * The @c audio_manager_snd_pcm_open_preferred() function combines
 * the @c snd_pcm_open_preferred() and @c audio_manager_get_handle() functions
 * and allows the allocation of a specific audio type PCM channel in
 * one step.
 *
 * @param type The audio type of the PCM channel being allocated.
 * @param handle The handle of the PCM channel opened.
 * @param audioman_handle The audio manager handle allocated to the PCM channel.
 * @param rcard The audio card used to open the PCM channel.
 * @param rdevice The audio device used to open the PCM channel.
 * @param mode The PCM channel mode defined in the @c asoundlib.h file.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_snd_pcm_open_preferred(audio_manager_audio_type_t type, snd_pcm_t **handle, unsigned int *audioman_handle, int *rcard, int *rdevice, int mode);

/**
 * @brief Open a PCM channel using the specified audio type,
 *        audio card, and device
 *
 * The @c audio_manager_snd_pcm_open() function combines the following
 * functionality into a single step:
 * - Calls @c snd_pcm_open() and @c audio_manager_get_handle() functions
 * - Allows the allocation of a specific audio type PCM channel
 *
 * @param type The audio type of the PCM channel being allocated.
 * @param handle The handle of the PCM channel opened
 * @param audioman_handle The audio manager handle allocated to the PCM channel.
 * @param card The audio card to be used to open the PCM channel.
 * @param device The audio device to be used to open the PCM channel.
 * @param mode The PCM channel mode defined in @c asoundlib.h.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_snd_pcm_open(audio_manager_audio_type_t type, snd_pcm_t **handle, unsigned int *audioman_handle, int card, int device, int mode);

/**
 * @brief Open a PCM channel with the specified audio type and name of the
 *        audio path
 *
 * The @c audio_manager_snd_pcm_open_name() function provides the following
 * function in a single step:
 * - Provides the functionality provided by @c snd_pcm_open_name() and @c
 *   audio_manager_get_handle() functions.
 * - Allocates a specific audio type PCM channel.
 *
 * @param type The audio type of the PCM channel being allocated.
 * @param handle The handle of the PCM channel opened.
 * @param audioman_handle The audio manager handle allocated to the PCM channel.
 * @param name The name of the audio path to be used to open the PCM
 *             channel.
 * @param mode The PCM channel mode defined in @c asoundlib.h.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_snd_pcm_open_name(audio_manager_audio_type_t type, snd_pcm_t **handle, unsigned int *audioman_handle, char *name, int mode);
#endif

/**
 * @internal For internal use only. Do not use.
 * @brief Check if a device switch should result in an auto pause
 *
 * The @c audio_manager_check_autopause() function indicates whether it is
 * recommended that a client that has been forced to switch from one device
 * to another should auto pause. This function is intended for use by system
 * components. Therefore, it is not suitable for all applications.
 *
 * @param audioman_handle The audio manager handle on which to check.
 * @param from The device that was active at the last point in time when
 *             the associated PCM channel was prepared.
 * @param to The device that is now active.
 * @param result @c true if the client should auto pause, @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_check_autopause( unsigned int audioman_handle,
                                   audio_manager_device_t from, audio_manager_device_t to,
                                   bool* result );

/**
 * @internal Do not use. For internal use only.
 * @brief Check if audio is active at the moment the function is called
 *
 * The @c audio_manager_get_audio_activities() function returns whether there
 * is active audio playback or recording. This function is intended for use by
 * system components. Therefore, it is not suitable for all applications.
 *
 * @param activities A bitmask of @c audio_manager_device_capability_t that
 *                   indicates activities.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_audio_activities( int * activities );

/**
 * @internal Do not use. For internal use only.
 * @brief Compare the routing priority of 2 audio manager handles
 *
 * The @c audio_manager_compare_handle_routing_priority() function returns
 * the comparison result of the two provided handles.
 *
 * This function is intended for use by system components. Therefore, it
 * is not suitable for all applications.
 *
 * @param handle1 The first audio manager handle returned by
 *                @c audio_manager_get_handle.
 * @param handle2 The second audio manager handle returned by
 *                @c audio_manager_get_handle.
 * @param result A pointer to the integer to store the comparison result. A
 *               positive value means that @c handle1 has higher priority
 *               than @c handle2. A negative value means that @c handle1 has
 *               lower priority than @c handle2. Otherwise, both handles have
 *               the same priority.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_compare_handle_routing_priority( unsigned int handle1, unsigned int handle2, int * result );

/**
 * @internal Do not use. For internal use only.
 * @brief Get the process IDs associated with the audio manager handle
 *
 * The @c audio_manager_get_handle_pids() function returns
 * the process identifiers (PIDs) associated with the audio manager handle.
 * This function is intended for use by system components. Therefore,
 * it is not suitable for all applications.
 *
 * @param audioman_handle The audio manager handle returned by
 *                        @c audio_mananger_get_handle.
 * @param caller_pid The PID of the caller process. If client A plays music
 *                   through mm-renderer and allows mm-renderer to allocate
 *                   @c audioman_handle, the caller_pid = pidof(mm-renderer).
 * @param client_pid The PID of the client process. If client A plays music
 *                   through mm-renderer and allows mm-renderer to allocate the
 *                   audio manager handle, the @c caller_pid = pidof(clientA)
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_handle_pids( unsigned int audioman_handle, pid_t * caller_pid, pid_t * client_pid );

/**
 * @internal Do not use. For internal use only.
 * @brief Enable or disable use of Bluetooth hands free profile (BTSCO) by
 *        an android player
 *
 * To use this function,it must be called from the android player and the
 * process where the function is called from must belong to the
 * @c android_bluetooth process group.
 *
 * The @c audio_manager_set_android_btsco_status() function enables
 * or disables the automatic or specific routing to BTSCO (Bluetooth hands free
 * profile) when an android player handles controls routing. This function
 * is intended for use by system components. Therefore, it is not suitable
 * for any application.
 *
 * @param enable Whether to enable or disable use of BTSCO.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 *
 */
int audio_manager_set_android_btsco_status( bool enable );

/**
 * @internal Do not use. For internal use only.
 * @brief Determine whether android player allows use of Bluetooth hands free
 *        profile (BTSCO)
 *
 * This function may only be called by the android player. This function is
 * intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * The @c audio_manager_get_android_btsco_status() determines whether
 * the automatic or specific routing to btsco when an android player
 * handle controls routing is allowed.
 *
 * @param enabled Whether btsco is allowed.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_android_btsco_status( bool *enabled );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_ROUTING_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
