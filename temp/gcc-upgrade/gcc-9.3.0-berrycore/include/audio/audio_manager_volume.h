#ifndef _AUDIO_MANAGER_VOLUME_H_INCLUDED
#define _AUDIO_MANAGER_VOLUME_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <stdint.h>
#include <audio/audio_manager_device.h>

/**
 * @file audio_manager_volume.h
 *
 * @brief The definitions for supported audio volume controls
 *
 * The audio manager maintains the volume control interfaces for all supported
 * devices. This file provides audio volume control types and functions to
 * work with volume control.
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @internal For internal use only. Do not use.
 * @brief Statistic entry name used with @c audio_manager_get_stat_counter() for
 * EU headphone volume regulations.
 *
 * This counter tracks the total time the user has spent in the EU
 * unsafe volume zone with headphones.
 *
 * This definition is intended for use by system components. Therefore, it is
 * not suitable for all applications.
 */
#define UNSAFEZONE_TIMEOUT_ID "Audio.EU.headphone.boost.timer"
/**
 * @internal For internal use only. Do not use.
 * @brief The default threshold in percentage for entering the EU unsafe
 *         volume zone for headphones
 *
 * This definition is intended for use by system components. Therefore, it is
 * not suitable for all applications.
 */
#define UNSAFEZONE_DEFAULT_EU_UNSAFE_LEVEL   75
/**
 * @internal For internal use only. Do not use.
 * @brief The default timeout of the EU unsafe volume zone for headphones
 *
 * Once the timer reaches this threshold, the user is required to acknowledge
 * the EU regulations again to use headphones with volume level above
 * the @c UNSAFEZONE_DEFAULT_EU_UNSAFE_LEVEL.
 *
 * This definition is intended for use by system components. Therefore, it is
 * not suitable for all applications.
 */
#define UNSAFEZONE_DEFAULT_EU_UNSAFE_TIMEOUT 72000000


/**
 * @brief The headphone volume override status
 *
 * This structure defines the status of the configuration of the specified
 * headphone volume override feature.
 */
typedef struct {
    /**
     * Whether the extra volume override is supported. A value of @c true
     * indicates that the device or region supports the override, a value of
     * @c false indicates otherwise.
     */
    bool supported;
    /**
     * Whether an extra volume range is allowed.  A value of @c true specifies
     * that extra volume range is allowed, a value of @c false indicates
     * otherwise.
     */
    bool enabled;
    /**
     * The output level that the headphone volume is limited to when the extra
     * volume override, @c supported is set to @c false. The output level is
     * expressed as a percentage value between 0-100.
     */
    int level;
} audio_manager_headphone_volume_override_status_t;


/**
 * @internal For internal use only. Do not use.
 * @brief The status of the headphone output-volume regulation
 *
 * This structure defines the status of whether and at which level the headphone
 * output volume is regulated. This structured type is intended for use by
 * system components. Therefore, it is not suitable for all applications.
 */
typedef struct {
    /**
     * The current status of whether the headphone volume is regulated.
     */
    bool regulated;
    /**
     * The output level in percentage that the headphone volume is regulated at.
     */
    double level;
} audio_manager_headphone_output_regulation_t;

/**
 * @brief Set the audio output level of the specified audio device
 *
 * The @c audio_manager_set_output_level() function sets
 * the audio output level of a device. The value is set using the @c level
 * argument that represents a percentage of the maximum output level. For
 * example, if, a value of 90.00 is specified, the output level is set to
 * 90% of the maximum.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The new output level as a percentage value from 0.00 to 100.00.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_output_level( audio_manager_device_t dev, double level );

/**
 * @brief Get the audio output level of a specified device
 *
 * Use @c audio_manager_get_output_level() to return the audio output
 * level of the specified device. The value is returned in the @c level argument
 * that represents a percentage of the maximum output level. For example, if
 * A value of 90.00 is returned, it that the current output level is 90% of the
 * maximum.
 *
 * @param dev The audio device to query.
 * @param level The output level being returned as a percentage value between
 *              0.00 to 100.0.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_output_level( audio_manager_device_t dev, double * level );

/**
 * @brief Adjust the audio output level of a specified device
 *
 * The @c audio_manager_adjust_output_level() function adjusts
 * the audio output level of the specified device by a certain percentage value.
 * A negative value means to decrease the output level,  while a non-negative
 * value means to increase the output level for. For example, when you set
 * @c level to a value of 10.00, it represents a 10% increase to the existing
 * output level. If you set the value to -10.00, it represents 10% decrease
 * to the output level.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The change in level of the audio output is provided as
 *              a percentage value. For example, value of 10.00 represents a 10%
 *              increase, while a value of -10.00 represents 10% decrease.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_adjust_output_level( audio_manager_device_t dev, double level );

/**
 * @brief Increase the audio output level of a device
 *
 * The @c audio_manager_increase_output_level() function increases
 * the audio output level of the device. The amount or step of the output level
 * increase is defined by the specified audio device.
 *
 * @param dev The audio device which to apply the output level increase.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_increase_output_level( audio_manager_device_t dev );

/**
 * @brief Decrease the audio output level of the specified audio device
 *
 * The @c audio_manager_decrease_output_level() function decreases
 * the audio output level of the specified audio device. The audio device defines the
 * amount or step of the output level to decrease.
 *
 * @param dev The audio device to apply the output level decrease to.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_decrease_output_level( audio_manager_device_t dev );

/**
 * @brief Get the number of available output volume steps
 *
 * The @c audio_manager_get_output_volume_steps() function returns the
 * number of available volume steps.
 *
 * @param dev The audio device to query.
 * @param steps The available volume steps returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_output_volume_steps( audio_manager_device_t dev, int * steps );

/**
 * @brief Mute the audio output of the specified audio device
 *
 * The @c audio_manager_set_output_mute() function mutes
 * the audio output of the specified audio device.
 *
 * @param dev The audio device to mute output.
 * @param mute @c true if the output of the audio device should be muted,
 * @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_output_mute( audio_manager_device_t dev, bool mute );

/**
 * @brief Get the mute status of the audio output of the specified audio device
 *
 * The @c audio_manager_get_output_mute() function returns the
 * mute status of the audio output of the specified audio device.
 *
 * @param dev The audio device to query.
 * @param mute @c true if the output of the audio device is being muted,
 * @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_output_mute( audio_manager_device_t dev, bool * mute );

/**
 * @brief Toggle the audio output mute status of the specified audio device
 *
 * The @c audio_manager_toggle_output_mute() function toggles the
 * mute status of the audio output of the specified audio device.
 *
 * @param dev The audio device that the toggle is applied to.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_toggle_output_mute( audio_manager_device_t dev );

/**
 * @brief Set the audio input level of the specified audio device
 *
 * The @c audio_manager_set_input_level() function sets
 * the audio input level of the specified audio device.
 *
 * @param dev The audio device that the new input level is applied to.
 * @param level The new input level in percentage, 0.00 to 100.00 (e.g. 90.00 =
 * 90%).
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_input_level( audio_manager_device_t dev, double level );

/**
 * @brief Get the audio input level of the specified audio device
 *
 * The @c audio_manager_get_input_level() function returns
 * the audio input level of the specified audio device.
 *
 * @param dev The audio device to query.
 * @param level The input level being returned in percentage, 0.00 to 100.0
 * (e.g. 90.00 = 90%).
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_input_level( audio_manager_device_t dev, double * level );

/**
 * @brief Adjust the audio input level of the specified audio device
 *
 * The @c audio_manager_adjust_input_level() function adjusts
 * the audio input level of the specified audio device.
 *
 * @param dev The audio device the new input level is applied to.
 * @param level The change in level of the audio input in
 * percentage (e.g. 10.00 = 10% increase, -10.00 = 10% decrease).
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_adjust_input_level( audio_manager_device_t dev, double level );

/**
 * @brief Mute the audio input of the specified audio device
 *
 * The @c audio_manager_set_input_mute() function mutes
 * the audio input of the specified audio device.
 *
 * @param dev The audio device to mute input.
 * @param mute @c true if the input of the audio device should be muted,
 * @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_input_mute( audio_manager_device_t dev, bool mute );

/**
 * @brief Get the mute status of the audio input of the specified audio device
 *
 * The @c audio_manager_get_input_mute() function returns the
 * mute status of the audio input of the specified audio device.
 *
 * @param dev The audio device to query.
 * @param mute @c true if the input of the audio device is being muted, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_input_mute( audio_manager_device_t dev, bool * mute );

/**
 * @brief Toggle the audio input mute status of the specified audio device
 *
 * The @c audio_manager_toggle_output_mute() function toggles the
 * mute status of the audio input of the specified audio device.
 *
 * @param dev The audio device that the toggle is applied to.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_toggle_input_mute( audio_manager_device_t dev );

/**
 * @brief Deprecated
 * @deprecated This function is deprecated.
 *
 * Get the headphone override status.
 * The @c audio_manager_get_headphone_override() function returns
 * the headphone volume override status. The override allows extra volume boost
 * to the headphone output.
 *
 * @param override @c true if the extra volume boost is allowed, @c false
 * otherwise.
 * @param level The output level in percentage (0 to 100) that the headphone
 * volume is allowed.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int __attribute__((deprecated)) audio_manager_get_headphone_override( bool * override, int * level );

/**
 * @brief Get the headphone volume boost status
 *
 * The @c audio_manager_get_headphone_boost_status() function returns
 * the headphone volume boost status. The override allows extra volume boost
 * to the headphone output.
 *
 * @param status The status of the volume boost as
 * @c audio_manager_headphone_volume_override_status_t.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_headphone_boost_status( audio_manager_headphone_volume_override_status_t * status );

/**
 * @brief Get the headphone volume unsafe zone status
 *
 * The @c audio_manager_get_headphone_unsafe_zone_status() function returns
 * the headphone volume unsafe zone status.
 *
 * @param status The status of the volume unsafe zone as
 * @c audio_manager_headphone_volume_override_status_t.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_headphone_unsafe_zone_status( audio_manager_headphone_volume_override_status_t * status );

/**
 * @internal For internal use only. Do not use.
 * @brief Get whether the current headphone output level is restricted due to
 * regulations
 *
 * The @c audio_manager_get_headphone_level_regulated() function returns whether
 * the level of the current headphone output level is regulated to a lower
 * level than the user or application might have set.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param regulated @c true if the output of the audio device is being
 * regulated, @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_headphone_output_level_regulation_status( audio_manager_headphone_output_regulation_t * status );

/**
 * @brief Get the number of available voice output volume steps
 *
 * The @c audio_manager_get_voice_output_volume_steps() function returns the
 * number of available volume steps for voice calls.
 *
 * @param dev The audio device to query.
 * @param steps The available volume steps returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_voice_output_volume_steps( audio_manager_device_t dev, int * steps );


/**
 * @brief Get the statistic counter of the specified statistic entry name
 *
 * The @c audio_manager_get_stat_counter() function returns the counter of
 * the specified statistic entry.
 *
 * @param name The name of the statistic entry.
 * @param counter The counter of the selected entry returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_stat_counter( const char * name, uint64_t * counter );

// privileged calls

/**
 * @internal For internal use only. Do not use.
 * @brief Set the audio output level of the specified audio
 *        device during voice calls
 *
 * The @c audio_manager_set_voice_output_level() function sets
 * the audio output level of the specified audio device during voice calls.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The new output level in percentage, 0.00 to 100.0 (e.g. 90.00 =
 * 90%).
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_output_level( audio_manager_device_t dev, double level );

/**
 * @internal For internal use only. Do not use.
 * @brief Get the audio output level of the specified audio
 *        device during voice calls
 *
 * The @c audio_manager_get_voice_output_level() function returns
 * the audio output level of the specified audio device during voice
 * calls.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device to query.
 * @param level The output level being returned in percentage, 0.00 to 100.0
 * (e.g. 90.00 = 90%).
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_voice_output_level( audio_manager_device_t dev, double * level );

/**
 * @internal For internal use only. Do not use.
 * @brief Adjust the audio output level of the specified audio
 *        device during voice calls
 *
 * The @c audio_manager_adjust_voice_output_level() function adjusts
 * the audio output level of the specified audio device during voice calls.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The change in level of the audio output in
 * percentage, 0.00 to 100.0. (e.g. 10.00 = 10% increase, -10.00 = 10% decrease)
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_adjust_voice_output_level( audio_manager_device_t dev, double level );

/**
 * @internal For internal use only. Do not use.
 * @brief Increase the audio output level of the specified audio
 *        device during voice calls
 *
 * The @c audio_manager_increase_voice_output_level() function increases
 * the audio output level of the specified audio device during voice calls.
 * The step of the output level increase is defined by the particular
 * audio device.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device that the increase is applied to.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_increase_voice_output_level( audio_manager_device_t dev );

/**
 * @internal For internal use only. Do not use.
 * @brief Decrease the audio output level of the specified audio
 *        device during voice calls
 *
 * The @c audio_manager_decrease_voice_output_level() function decreases
 * the audio output level of the specified audio device during voice calls.
 * The step of the output level decrease is defined by the particular
 * audio device.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device that the decrease is applied to.
 *
 * @return@c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_decrease_voice_output_level( audio_manager_device_t dev );

/**
 * @internal For internal use only. Do not use.
 * @brief Clear the statistic counter of the specified statistic entry name
 *
 * The @c audio_manager_clear_stat_counter() function clears the counter of
 * the specified statistic entry.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param name The name of the statistic entry to clear.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_clear_stat_counter( const char * name );

/**
 * @internal For internal use only. Do not use.
 * @brief Mute the audio output of the specified audio device
 *        during voice calls
 *
 * The @c audio_manager_set_voice_output_mute() function mutes
 * the audio output of the specified audio device during voice calls.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device to mute output.
 * @param mute @c true if the output of the audio device should be muted,
 * @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_output_mute( audio_manager_device_t dev, bool mute );

/**
 * @internal For internal use only. Do not use.
 * @brief Get the mute status of the audio output of a
 *        specified audio device during voice calls
 *
 * The @c audio_manager_get_voice_output_mute() function returns the
 * mute status of the audio output of the specified audio device during
 * voice calls.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device to query.
 * @param mute @c true if the output of the audio device is being muted,
 * @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_voice_output_mute( audio_manager_device_t dev, bool * mute );

/**
 * @internal For internal use only. Do not use.
 * @brief Mute the audio output of the modem
 *
 * The @c audio_manager_set_modem_output_mute() function mutes
 * the audio output of the modem.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param mute @c true if the output of the modem should be muted, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_modem_output_mute( bool mute );

/**
 * @internal For internal use only. Do not use.
 * @brief Get the mute status of the audio output of the
 * modem
 *
 * The @c audio_manager_get_modem_output_mute() function returns the
 * mute status of the audio output of the modem.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param mute @c true if the output of the modem is muted, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_modem_output_mute( bool * mute );

/**
 * @internal For internal use only. Do not use.
 * @brief Toggle the audio output mute status of the specified
 * audio device during voice calls
 *
 * The @c audio_manager_toggle_voice_output_mute() function toggles the
 * mute status of the audio output of the specified audio device during voice
 * calls.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param dev The audio device that the toggle is applied to.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_toggle_voice_output_mute( audio_manager_device_t dev );

/**
 * @internal For internal use only. Do not use.
 * @brief Mute the audio input (to the far end) of the current
 * voice call
 *
 * The @c audio_manager_set_voice_input_mute() function mutes
 * the audio input (to the far end) of the current voice call.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.

 *
 * @param mute @c true if the input of the current voice call should be muted,
 * @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_input_mute( bool mute );

/**
 * @internal For internal use only. Do not use.
 * @brief Get the mute status of the audio input (to the far end) of
 * the current voice call
 *
 * The @c audio_manager_get_voice_input_mute() function returns the mute status
 * of the audio input (to the far end) of the current voice call.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function is
 * intended for use by system components. Therefore, it is not suitable for all
 * applications.
 *
 * @param mute @c true if the input of the voice call is being muted, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_voice_input_mute( bool *mute );

/**
 * @internal For internal use only. Do not use.
 * @brief Set the override status of the headphone output level
 * @deprecated This function is deprecated.
 *
 * The @c audio_manager_set_headphone_override() function sets the
 * override status of the headphone output level to allow an extra volume
 * boost to the headphone output.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param override @c true if the extra volume boost is allowed, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int  __attribute__((deprecated)) audio_manager_set_headphone_override( bool override );

/**
 * @internal For internal use only. Do not use.
 * @brief Set the use of the headphone output volume boost
 *
 * The @c audio_manager_set_headphone_volume_boost() function sets the
 * enable status of the headphone output level to allow an extra volume
 * boost to the headphone output.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param enable @c true if the extra volume boost is allowed, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_headphone_volume_boost( bool enable );

/**
 * @internal For internal use only. Do not use.
 * @brief Set the use of the unsafe range of the headphone
 *        output volume
 *
 * The @c audio_manager_set_headphone_volume_unsafe_zone() function sets the
 * enable status of the unsafe volume range of the headphone output to allow
 * an extra volume range to the headphone output.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.  This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param enable @c true if the extra volume range is allowed, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_headphone_volume_unsafe_zone( bool enable );




#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_VOLUME_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
