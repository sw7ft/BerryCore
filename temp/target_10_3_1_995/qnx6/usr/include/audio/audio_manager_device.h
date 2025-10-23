#ifndef _AUDIO_MANAGER_DEVICE_H_INCLUDED
#define _AUDIO_MANAGER_DEVICE_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @mainpage Audio Manager Library
 *
 * The Audio Manager library allows applications to set up and process events
 * from audio devices supported on the device. This library provides
 * interfaces to audio devices.
 *
 * You use audio manager handles, which are references to audio sources. Using
 * this library, you can get and set properties for audio device status, volume,
 * routing, and concurrency. You can also add and remove audio events
 * to notify clients that are using audio devices.
 *
 */

 /**
 * @file audio_manager_device.h
 *
 * @brief Definitions for supported audio devices and their properties
 *
 * Audio manager maintains a list of supported devices on the target and
 * their properties. This file defines device properties and provides get and
 * set functions for them.
 *
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief Names for supported audio devices
 */
#define AUDIO_DEVICE_NAMES  \
{                           \
    "speaker",              \
    "headset",              \
    "headphone",            \
    "a2dp",                 \
    "handset",              \
    "hac",                  \
    "btsco",                \
    "hdmi",                 \
    "toslink",              \
    "tty",                  \
    "lineout",              \
    "usb",                  \
    "tones",                \
    "voice",                \
    "miracast",             \
    "mirrorlink",           \
    "audioshare",           \
}

/**
 * @brief Names for audio channels
 */
#define AUDIO_CHANNEL_NAMES \
{                           \
    "",                     \
    "FL",                   \
    "FC",                   \
    "FR",                   \
    "RL",                   \
    "RR",                   \
    "LFE",                  \
}

/**
 * @brief Names for volume control types
 */
#define AUDIO_VOLUME_CONTROL_NAMES  \
{                                   \
    "unavailable",                  \
    "simple",                       \
    "percentage",                   \
}

/**
 * @brief Names for headset buttons
 */
#define AUDIO_HEADSET_BUTTON_NAMES  \
{                                   \
    "button_play_pause",            \
    "button_vol_up",                \
    "button_vol_down",              \
    "button_forward",               \
    "button_back",                  \
}

/**
 * @brief Names for headset button states
 */
#define AUDIO_HEADSET_BUTTON_STATE_NAMES    \
{                                           \
    "pressed",                              \
    "released",                             \
}

/**
 * @brief Names for overall audio system status
 */
#define AUDIO_SYSTEM_STATUS_NAMES   \
{                                   \
    "normal",                       \
    "resetting",                    \
    "error",                        \
}


/**
 * @brief Supported audio devices
 *
 * This enumeration defines the types of audio devices
 * supported.
 */
typedef enum {
    /**
     * The main speakers.
     */
    AUDIO_DEVICE_SPEAKER,
    /**
     * The mono/stereo headset with microphone.
     */
    AUDIO_DEVICE_HEADSET,
    /**
     * The mono/stereo output only headphone.
     */
    AUDIO_DEVICE_HEADPHONE,
    /**
     * The Bluetooth A2DP streaming service.
     */
    AUDIO_DEVICE_A2DP,
    /**
     * The phone receiver.
     */
    AUDIO_DEVICE_HANDSET,
    /**
     * The hearing aid compatibility device.
     */
    AUDIO_DEVICE_HAC,
    /**
     * The Bluetooth hands-free profile service for voice calls.
     */
    AUDIO_DEVICE_BT_SCO,
    /**
     * The HDMI connection.
     */
    AUDIO_DEVICE_HDMI,
    /**
     * The TOSLINK connection.
     */
    AUDIO_DEVICE_TOSLINK,
    /**
     * The telecommunications device for the hearing challenged.
     */
    AUDIO_DEVICE_TTY,
    /**
     * The line-out connection through the headset jack.
     */
    AUDIO_DEVICE_LINEOUT,
    /**
     * The USB connection.
     */
    AUDIO_DEVICE_USB,
    /**
     * The virtual tones port that is used for system tones.
     */
    AUDIO_DEVICE_TONES,
    /**
     * The virtual voice port that is used for voice stream processing such as
     * VoIP.
     */
    AUDIO_DEVICE_VOICE,
    /**
     * The audio device that is available from a Wi-Fi display connection.
     */
    AUDIO_DEVICE_WIFI_DISPLAY,
    /**
     * The audio device available using a MirrorLink connection.
     */
    AUDIO_DEVICE_MIRRORLINK,
    /**
     * The virtual audio device available using video share.
     */
    AUDIO_DEVICE_AUDIO_SHARE,
    /**
     * The total number of devices supported.
     */
    AUDIO_DEVICE_COUNT,
    /**
     * The current active output device that's playing audio.
     */
    AUDIO_DEVICE_DEFAULT = 0xFF,
    /**
     * The audio device is unchanged if this value is specified.
     */
    AUDIO_DEVICE_UNCHANGED = INT_MAX,
} audio_manager_device_t;

/**
 * @brief Supported audio channels
 *
 * This enumeration defines the supported types of audio channels, either
 * 2.0 or 5.1.
 */
typedef enum {
    /**
     * No output channel is supported.
     */
    AUDIO_CHANNEL_UNAVAILABLE,
    /**
     * The front-left channel.
     */
    AUDIO_CHANNEL_FRONT_LEFT,
    /**
     * The front-center channel.
     */
    AUDIO_CHANNEL_FRONT_CENTER,
    /**
     * The front-right channel.
     */
    AUDIO_CHANNEL_FRONT_RIGHT,
    /**
     * The rear-left channel.
     */
    AUDIO_CHANNEL_REAR_LEFT,
    /**
     * The rear-right channel.
     */
    AUDIO_CHANNEL_REAR_RIGHT,
    /**
     * Low-frequency effects channel, such as a subwoofer.
     */
    AUDIO_CHANNEL_LOW_FREQ_EFFECTS,
    /**
     * The total number of audio channels that are supported.
     */
    AUDIO_CHANNEL_COUNT,
} audio_manager_channel_t;

/**
 * @brief Supported audio volume control types
 *
 * This enumeration defines the supported types of the audio
 * volume control types.
 */
typedef enum {
    /**
     * Volume control is not supported.
     */
    AUDIO_VOLUME_CONTROL_UNAVAILABLE,
    /**
     * The simple volume control is supported. The simple control usually has
     * up and down buttons to increase or decrease volume.
     */
    AUDIO_VOLUME_CONTROL_SIMPLE,
    /**
     * The precise volume-control as a percentage value that is supported.
     */
    AUDIO_VOLUME_CONTROL_PERCENT,
    /**
     * The total number of volume control types that are supported.
     */
    AUDIO_VOLUME_CONTROL_COUNT,
} audio_manager_device_volume_control_t;

/**
 * @brief Supported audio device configurations
 *
 * This enumeration defines bit masks for supported audio device configurations.
 */
typedef enum {
    /**
     * The audio device supports stereo channels.
     */
    AUDIO_CHANNEL_CONFIG_STEREO = (1u<<0),
    /**
     * The audio device supports 5.1 surround sound.
     */
    AUDIO_CHANNEL_CONFIG_5_1    = (1u<<1),
} audio_manager_channel_config_t;

/**
 * @brief Supported audio device input and output
 *
 * This enumeration defines bit masks for the supported audio device I/O
 * used for playback and recording.
 */
typedef enum {
    /**
     * The audio device supports playback.
     */
    AUDIO_OUTPUT                = (1u<<0),
    /**
     * The audio device supports recording.
     */
    AUDIO_INPUT                 = (1u<<1),
} audio_manager_device_capability_t;

/**
 * @brief Audio configuration settings for the specified audio device
 *
 * This structure defines the audio configuration an audio
 * device.
 */
typedef struct {
    /**
     * The number of output channels that are supported.
     */
    int num_out_channels;
    /**
     * The number of input channels that are supported.
     */
    int num_in_channels;
    /**
     * The output channels of the audio device. The channels are listed in the 
     * order in which they ware setup.
     */
    audio_manager_channel_t channel_order[AUDIO_CHANNEL_COUNT];
    /**
     * The channel configuration of the audio device.
     */
    audio_manager_channel_config_t channel_config_mask;
} audio_manager_device_audio_config_t;

/**
 * @brief Supported audio headset button types
 *
 * This enumeration defines the supported types of the audio headset buttons.
 */
typedef enum {
    /**
     * The play and pause button. Alternatively, it can be a mute or unmute
     * button.
     */
    AUDIO_HEADSET_PLAY_PAUSE,
    /**
     * The volume up button.
     */
    AUDIO_HEADSET_VOLUME_UP,
    /**
     * The volume down button.
     */
    AUDIO_HEADSET_VOLUME_DOWN,
    /**
     * The track forward button.
     */
    AUDIO_HEADSET_FORWARD,
    /**
     * The track backward button.
     */
    AUDIO_HEADSET_BACKWARD,
    /**
     * The total number of headset button types that are supported.
     */
    AUDIO_HEADSET_BUTTON_COUNT,
} audio_manager_device_headset_button_t;

/**
 * @brief The states of the headset buttons.
 *
 * This structure defines the supported states of the audio headset buttons.
 */
typedef struct {
    /**
     * The state of the audio headset button.
     */
    bool button_state[AUDIO_HEADSET_BUTTON_COUNT];
} audio_manager_headset_button_state_t;

/**
 * @brief The states of the audio system
 *
 * This structure defines the state of the audio system.
 */
typedef enum {
    /**
     * The audio system is operating normally.
     */
    AUDIO_SYSTEM_NORMAL,
    /**
     * The audio system is in recovery mode because a recoverable error occurred.
     */
    AUDIO_SYSTEM_RECOVERY_IN_PROGRESS,
    /**
     * The audio system is in an unrecoverable or invalid state because an
     * unrecoverable error occurred.
     */
    AUDIO_SYSTEM_FAILED,
    /**
     * The total number of statuses supported for the audio system.
     */
    AUDIO_SYSTEM_STATUS_COUNT
} audio_manager_audio_system_status_t;

/**
 * @brief The audio capabilities that can be queried
 *
 * This enumeration defines the audio capabilities that can be queried.
 */
typedef enum {
    /**
     * The number of output channels that are supported, as an @c int value.
     */
    AUDIO_DEVICE_PROPERTY_NUM_OUT_CHANNELS,
    /**
     * The number of input channels that are supported, as an @c int value.
     */
    AUDIO_DEVICE_PROPERTY_NUM_IN_CHANNELS,
    /**
     * The output channels that are listed in the order that the channel was
     * setup up. Each type is an @c audio_manager_channel_t[] array. This
     * parameter is permitted only when
     * @c AUDIO_DEVICE_PROPERTY_NUM_OUT_CHANNELS is requested as
     * well. If the number of channels is greater than the input value for
     * @c AUDIO_DEVICE_PROPERTY_NUM_OUT_CHANNELS then, at most, the input value
     * is written.
     */
    AUDIO_DEVICE_PROPERTY_CHANNEL_ORDER,
    /**
     * An integer that represents the channel configuration of the audio device.
     * This integer is a combination of one or more bit masks of the type
     * @c #audio_manager_channel_config_t.
     */
    AUDIO_DEVICE_PROPERTY_CHANNEL_CONFIG,
    /**
     * Whether the device is supported on this platform, as a @c bool value.
     */
    AUDIO_DEVICE_PROPERTY_SUPPORTED,
    /**
     * Whether the device is currently connected, as a @c bool value. For
     * example, in the case of headphones, this property indicates
     * whether the headphones are plugged in.
     */
    AUDIO_DEVICE_PROPERTY_CONNECTED,
    /**
     * Whether the device is suspended, as a @c bool value.
     */
    AUDIO_DEVICE_PROPERTY_SUSPENDED,
    /**
     * The type of volume control supported by the device as an
     * @c #audio_manager_device_volume_control_t value.
     */
    AUDIO_DEVICE_PROPERTY_VOLUME_CONTROL,
    /**
     * Whether the device is public, as a @c bool value. This property
     * indicates whether the device is a public or private listening device.
     * For example, a public listening device can be heard by multiple people,
     * such as a loudspeaker as opposed to headphones, which are private listening
     * devices.
     */
    AUDIO_DEVICE_PROPERTY_PUBLIC,
    /**
    * The number of input channels supported by the device. This enumerator
    * represents the true number of input channels that a device supports and
    * is different from @c AUDIO_DEVICE_PROPERTY_NUM_IN_CHANNELS.
    */
    AUDIO_DEVICE_PROPERTY_NUM_HW_IN_CHANNELS,
    /**
    * The bitmask of voice capabilities in the format of
    * (1u<<@c audio_manager_voice_service_t) supported by the
    * specified device as an @c int value.
    */
    AUDIO_DEVICE_PROPERTY_VOICE_CAPABILITIES,
    /**
     * The total number of device properties supported.
     */
    AUDIO_DEVICE_PROPERTY_COUNT

} audio_manager_device_capabilities_t;

/**
 * @brief Get the audio device when the name of the device is specified
 *
 * Use @c audio_manager_get_device_from_name() to retrieve the audio
 * manager device when the name of the device is specified.
 *
 * @param device_name The name of the device being returned.
 *
 * @return The device identifier. A value of @c AUDIO_DEVICE_DEFAULT is returned
 *         if a matching audio device can't be found or a @c NULL is passed
 *         to this function.
 */
audio_manager_device_t audio_manager_get_device_from_name( const char * device_name );

/**
 * @brief Get the audio device name when the type of device  is specified
 *
 * Use @c audio_manager_get_device_name() to retrieve the audio
 * manager device name when provided the type of the device.
 *
 * @param device The type of the device being returned.
 *
 * @return The device name from the @c AUDIO_DEVICE_NAMES. If an error occurred
 *         or the string could not be found, a value of "default" is returned.
 */
const char * audio_manager_get_device_name( audio_manager_device_t device );

/**
 * @brief Determine whether the specified audio device is supported by the system
 *
 * The @c audio_manager_is_device_supported() function checks whether a
 * the specified audio device is supported by the system. Unsupported
 * audio devices result in errors when used against other audio manager
 * interfaces, such as volume, event, and concurrency.
 *
 * @param dev The type of the audio device to check against.
 * @param supported A pointer that is returned that specifies whether the
 *                  specified audio device is supported. A value of @c true
 *                  indicates that the specified audio device is supported, a
 *                  value of @c false specifies otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_is_device_supported( audio_manager_device_t dev,
                                       bool * supported);

/**
 * @brief Check whether the specified audio device is connected to the system
 *
 * The @c audio_manager_is_device_connected() function checks whether the
 * specified audio device is currently connected to the system. Disconnected
 * audio devices are not picked by the audio manager as a valid routing
 * destination/source.
 *
 * @param dev The type of the audio device to check against.
 * @param connected A pointer that's returned that specifies whether device is
 *                  connected. A value of @c true indicates that the audio
 *                  device is connected, a value of @c false specifies
 *                  otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_is_device_connected( audio_manager_device_t dev,
                        bool * connected);

/**
 * @brief Check whether the specified audio device is suspended by the system
 *
 * The @c audio_manager_is_device_suspended() function checks whether the
 * specified audio device is currently suspended by the system. Suspended
 * audio devices aren't picked by the audio manager as a valid routing
 * destination or source.
 *
 * @param dev The type of the audio device to check against.
 * @param suspended A pointer that's returned to indicate whether the audio
 *                  device is suspected. A value @c true specifies that the
 *                  specified audio device is suspended, a value of @c false
 *                  specifies otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_is_device_suspended( audio_manager_device_t dev,
                        bool * suspended);

/**
 * @brief Check whether the specified audio device is kept in standby mode
 *        by the system
 *
 * Use @c audio_manager_is_device_kept_alive() to determine whether the
 * specified audio device is currently kept in a standby status by the system - 
 * even when no audio streams are active. Use this function to avoid the
 * creation of excessive audio artifacts, which is caused by hardware
 * transitions.
 *
 * @param dev The type of the audio device to check against.
 * @param keep_alive A pointer that's returned that indicates whether the device
 *                   is in standby. A value of @c true indicates that the
 *                   specified audio device is in a standby status, @c false
 *                   indicates otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_is_device_kept_alive( audio_manager_device_t dev,
                        bool * keep_alive);

/**
 * @brief Determine whether the mirror mode of the HDMI settings is on
 *
 * The @c audio_manager_is_hdmi_in_mirror_mode() function checks whether the
 * HDMI is currently set to mirror mode.
 *
 * @param mirror_mode A pointer that's returned to indicate whether the HDMI
 *                    is in mirror mode. A value of @c true indicates that the
 *                    the system is in HDMI mirror mode, a value @c false
 *                    otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_is_hdmi_in_mirror_mode( bool * mirror_mode);

/**
 * @brief Get the audio configuration of the specified device
 *
 * Use @c audio_manager_get_device_audio_config() to retrieve
 * the audio configuration of the specified audio device. The configuration
 * is retrieved by passing a reference to a
 * @c audio_manager_device_audio_config_t member.
 *
 * @param dev The type of the audio device to query. If @c #AUDIO_DEVICE_DEFAULT
 *            is passed to this function, the @c num_in_channels returned
 *            represents the number of input channels available from the
 *            current default input device. The rest of the fields represent
 *            the settings of the current default output device.
 * @param config The audio configuration.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_audio_config( audio_manager_device_t dev,
                        audio_manager_device_audio_config_t * config);

/**
 * @brief Get the audio capabilities of the specified device
 *
 * Use @c audio_manager_get_device_audio_capabilities() to retrieve
 * the requested capabilities of the specified audio device.
 *
 * @param dev The type of the audio device to query.
 * @param in A list of capabilities requested.
 * @param out The output pointers must match the type required for each input.
 * @param count The number of elements in each of the @c in and @c out
 *              arguments.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_audio_capabilities( audio_manager_device_t dev,
                        audio_manager_device_capabilities_t * in,
                        void **out,
                        int count);

/**
 * @brief Deprecated
 *
 * Get the output audio path of the specified audio device
 * Use @c audio_manager_get_device_audio_path() to retrieve
 * the audio output path of the specified audio device.
 *
 * @deprecated This function is deprecated. Do not use this function.
 *             Use @c audio_manager_get_device_name() instead.
 *
 * @param dev The type of the audio device to query.
 * @param path The audio path.
 * @param size The size of the path buffer. If not sufficient, the minimum
 *                    size to store the path is returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int __attribute__((deprecated)) audio_manager_get_device_audio_path( audio_manager_device_t dev,
                        char * path, int * size);



/**
 * @brief Get whether an audio output device is public
 *
 * Use @c audio_manager_get_device_audio_public() to determine
 * whether an audio output device is public, which means it can be heard by
 * many people.
 *
 * @param dev The type of the audio device to query.
 * @param pub @c true if the device is public, @c false otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_audio_public( audio_manager_device_t dev,
                        bool * pub);


/**
 * @brief Get the preferred system audio output path
 *
 * Use @c audio_manager_get_preferred_audio_output_path() to retrieve
 * the preferred system audio output path.
 *
 * @param path The audio path.
 * @param size The size of the path buffer. If the size is not sufficient, the
 *             minimum size to store the path is returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_preferred_audio_output_path( char * path, int * size );

/**
 * @brief Get the preferred system audio input path
 *
 * Use @c audio_manager_get_preferred_audio_input_path() to retrieve
 * the preferred system audio input path.
 *
 * @param path The audio path.
 * @param size The size of the path buffer. If the size is not sufficient,
 *             the minimum size to store the path is returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_preferred_audio_input_path( char * path, int * size );

/**
 * @brief Get the capabilities of an audio device
 *
 * Use @c audio_manager_get_device_capability() to retrieve
 * the capabilities of the specified audio device. The capabilities indicate
 * whether the device is capable of output, input, or both.
 *
 * @param dev The type of the audio device to query.
 * @param cap_mask The capabilities of the audio device that are returned as a
 *                 mask of @c #audio_manager_device_capability_t.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_capability( audio_manager_device_t dev,
                        audio_manager_device_capability_t * cap_mask);

/**
 * @brief Get the type of volume control used for an audio device
 *
 * Use @c audio_manager_get_device_volume_control() to
 * return the type of volume control used for the specified device.
 *
 * @param dev The type of the audio device to query.
 * @param control The type of the volume control that's returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_volume_control( audio_manager_device_t dev,
                        audio_manager_device_volume_control_t * control);

/**
 * @brief Get the dependency of an audio device
 *
 * Use @c audio_manager_get_device_dependency() to determine the dependency
 * of an audio device. An audio device with an inactive dependency is not used
 * by the audio manager service as a valid routing destination or source. An
 * inactive dependency can be:
 * - suspended
 * - unsupported
 * - disconnected
 *
 * @param dev The type of the audio device to query.
 * @param dev_dependent The associated dependent audio device that's returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_dependency( audio_manager_device_t dev,
                        audio_manager_device_t * dev_dependent);

/**
 * @brief Get the current default audio output device that's picked
 *        by audio manager service
 *
 * Use @c audio_manager_get_default_device() to determine the type of 
 * the default audio output device selected by the audio manager service.
 *
 * @param dev The default audio device.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_default_device( audio_manager_device_t * dev );

/**
 * @brief Get the current default audio input device picked by the audio manager
 *        service
 *
 * Use @c audio_manager_get_default_input_device() to returned the type of the
 * default audio input device selected by the audio manager service.
 *
 * @param dev The default audio input device.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_default_input_device( audio_manager_device_t * dev );

/**
 * @brief Get the current button states of the specified output device
 *
 * Use @c audio_manager_get_device_button_states() to retrieve the states of
 * all the supported buttons of the specified device. Currently, only the type
 * headset is supported.
 *
 * @param dev The default audio device.
 * @param state The current button states.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_device_button_states( audio_manager_device_t dev,
                        audio_manager_headset_button_state_t * state);


/**
 * @brief Get the current status of the audio system
 *
 * Use @c audio_manager_get_audio_system_status() to determine the status
 * of the audio system. Also use this function to allow the applications to
 * respond with useful messages to the user.
 *
 * @param status The current audio system status
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_audio_system_status( audio_manager_audio_system_status_t * status);


/**
 * @internal For internal use only. Do not use.
 * @brief Deprecated
 *
 * Wake up the specified audio device and keep it awake
 * Use the @c audio_manager_set_device_keep_alive() to
 * put the specified audio device into non-sleep mode. In this mode,
 * the audio device never gets turned off, regardless of whether there
 * are any audio streams active or not.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.
 *
 * @deprecated This function is deprecated.
 *
 * @param dev The audio device.
 * @param keep_alive @c true if the audio device is to be kept alive, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_device_keep_alive( audio_manager_device_t dev, bool keep_alive);

/**
 * @internal For internal use only. Do not use.
 * @brief Set HDMI audio in mirror mode
 *
 * The @c audio_manager_set_hdmi_mirror_mode() function
 * puts the HDMI audio in mirror mode, which routes audio
 * automatically to the HDMI.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.
 *
 * @param mirror_mode @c true if the HDMI is to be put in mirror mode, @c false
 * otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_hdmi_mirror_mode( bool mirror_mode );

/**
 * @internal For internal use only. Do not use.
 * @brief Set any audio device as connected
 *
 * The @c audio_manager_set_device_connected() function
 * sets the connected status of the specified audio device to
 * help the audio manager allocate proper audio devices as
 * default.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.
 *
 * @param dev The type of the audio device.
 * @param connected Whether the device should be marked as connected. A value of
 *                  @c true specifies that the device is to be connected, a
 *                  value of @c false indicates otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_device_connected( audio_manager_device_t dev, bool connected);

/**
 * @internal For internal use only. Do not use.
 * @brief Set a supported audio device as suspended
 *
 * Use @c audio_manager_set_device_suspended() to set the suspended
 * status of the specified audio device to help the audio manager allocate
 * proper audio devices as default.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.
 *
 * @param dev The type of audio device.
 * @param suspended Whether the device is to be suspended. A value of @c true
 *                  indicates to mark the specified audio device as
 *                  suspended, a value of @c false means otherwise.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_device_suspended( audio_manager_device_t dev, bool suspended);


/**
 * @internal For internal use only. Do not use.
 * @brief Set the status of the current audio system
 *
 * The @c audio_manager_set_audio_system_status() function
 * is called by the audio drivers. It's used to notify the audio manager
 * of the overall status of the audio system.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function.
 *
 *
 * @param status The current audio system status.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_audio_system_status( audio_manager_audio_system_status_t status );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_DEVICE_H_INCLUDED

__SRCVERSION( "$URL$ $Rev$" )
