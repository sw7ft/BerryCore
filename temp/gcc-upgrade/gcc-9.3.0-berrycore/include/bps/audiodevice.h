/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file audiodevice.h
 *
 * @brief Functions to determine the status of audio devices
 * 
 * This file defines the audio device service, which reads audio device change
 * events.  For example, using the audio device service allows an application
 * to receive notifications when audio should be directed to the HDMI
 * output because an HDMI cable has been plugged in.
 *
 * You should call the function @c audiodevice_get_info() to verify that the
 * audio device you want to use exists on the platform. If the specified audio
 * device does not exist, the function returns @c BPS_FAILURE, @c *info is not
 * updated, and using the unavailable audio device type or accessing @c *info
 * may result in program error or termination.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_AUDIODEVICE_H_INCLUDED
#define _BPS_AUDIODEVICE_H_INCLUDED

#include <sys/platform.h>
#include <stdbool.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Available audio device events
 * 
 * This enumeration defines the possible audio device events.  Currently, there
 * is only one event, @c AUDIODEVICE_INFO.
 * @anonenum bps_audiodevice_events Audio device events 
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single audio device event, which contains all the information about
     * the current audio device status.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_INFO             = 0x01,
};

/**
 * This enumeration defines the different audio devices that the audio device
 * service supports.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized device (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_UNRECOGNIZED = 0,

    /**
     * The main audio device.
     *
     * This device is reported by BlackBerry Tablet OS 1.0 if the audio device
     * is either the internal speaker or the headphone jack.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_MAIN         = 1,

    /**
     * The HDMI audio device.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_HDMI         = 2,

    /**
     * The internal speaker.
     *
     * This device is reported by BlackBerry 10 OS/BlackBerry Tablet OS 2.0 and
     * later if the audio device is the internal speaker.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_SPEAKER      = 3,

    /**
     * The headphone jack.
     *
     * This device is reported by BlackBerry 10 OS/BlackBerry Tablet OS 2.0 and
     * later if the audio device is the headphone jack.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_HEADPHONE    = 4,

    /**
     * A headset with microphone input.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_HEADSET      = 5,

    /**
     * The phone receiver on the device.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_HANDSET      = 6,

    /**
     * A Bluetooth Advanced Audio Distribution Profile (A2DP) connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_A2DP         = 7,

    /**
     * A Bluetooth Synchronous Connection Oriented/Hands-Free Profile (SCO/HFP)
     * connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_BTSCO        = 8,

    /**
     * A Hearing Aid Compatibility (HAC) coil used for hearing aids.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_HAC          = 9,

    /**
     * A TOSLINK optical audio cable connection.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_TOSLINK      = 10,

    /**
     * A TTY telecommunication device for the hearing impaired (connected
     * through the headphone jack).
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_TTY          = 11,

    /**
     * A device connected through the headset jack.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_DEVICE_LINEOUT      = 12,

    /**
     * The number of audio devices.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_NUM_DEVICES
} audiodevice_device_t;

/**
 * @typedef struct audiodevice_info_t
 * @brief Opaque audio device information type
 *
 * The @c #audiodevice_info_t structure is an opaque handle to information
 * pertaining to an audio device.  You can extract audio device information
 * using accessor functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct audiodevice_info_t audiodevice_info_t;

/**
 * This enumeration defines the different types of volume control available.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized volume type.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_VOLUME_UNRECOGNIZED = 0,

    /**
     * No volume control supported.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_VOLUME_UNAVAILABLE = 1,

    /**
     * Only simple volume control is supported.  Can only request volume
     * increase or decrease, but not the amount.  Mute is not supported.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_VOLUME_SIMPLE      = 2,

    /**
     * Full volume control is supported.
     *
     * @since BlackBerry 10.0.0
     */
    AUDIODEVICE_VOLUME_PERCENTAGE  = 3,
} audiodevice_volume_type_t;

/**
 * @brief Retrieve the information on an audio device
 *
 * The @c audiodevice_get_info() function gets the information on the specified
 * audio device.
 *
 * If the specified audio device does not exist on the platform, this function
 * returns @c BPS_FAILURE, @c *info is not updated, and using the unavailable
 * audio device type or accessing @c *info may result in program error or
 * termination.
 *
 * @param device The audio device to get the information on.  If this value is
 * @c AUDIODEVICE_DEVICE_UNRECOGNIZED or an audio device that's not supported by
 * the device, @c BPS_FAILURE is returned.
 * @param info This will be populated with the information on the specified
 * audio device.  The caller must call @c audiodevice_free_info() when done with
 * this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_get_info(audiodevice_device_t device, audiodevice_info_t **info);

/**
 * @brief Free the memory that is used by an audio device information structure
 * 
 * The @c audiodevice_free_info() function frees the memory that is used by the
 * specified audio device information structure.
 *
 * @param info The structure whose memory needs to be freed.  Note that the
 * pointer to the structure is not freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void audiodevice_free_info(audiodevice_info_t **info);

/**
 * @brief Retrieve the audio device from an audio device information structure
 *
 * The @c audiodevice_info_get_device() function gets the audio device that the
 * specified @c #audiodevice_info_t structure applies to.
 *
 * @param info The @c #audiodevice_info_t structure to get the audio device
 *             from.
 *
 * @return The audio device.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API audiodevice_device_t audiodevice_info_get_device(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device specified in an audio device
 *        information structure is connected
 *
 * The @c audiodevice_info_is_connected() function indicates whether the audio
 * device in the specified @c #audiodevice_info_t structure is connected.
 *
 * @param info The @c #audiodevice_info_t structure to get the connected flag
 * from.
 *
 * @return The connected flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_is_connected(audiodevice_info_t *info);

/**
 * @brief Retrieve the number of channels of the audio device specified in an
 * audio device information structure
 *
 * The @c audiodevice_info_get_numchans() function gets the number of channels
 * of the audio device in the specified @c #audiodevice_info_t structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the number of channels
 * from.
 *
 * @return The number of channels.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_info_get_numchans(audiodevice_info_t *info);

/**
 * @brief Retrieve the order of the channels of the audio device specified in
 * an audio device information structure
 *
 * The @c audiodevice_info_get_order() function gets the order of the channels
 * of the audio device in the specified @c #audiodevice_info_t structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the order from.
 *
 * @return The order of the channels.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * audiodevice_info_get_order(audiodevice_info_t *info);

/**
 * @brief Retrieve the path of the audio device specified in an audio device
 *        information structure
 *
 * The @c audiodevice_info_get_path() function gets the path of the audio device
 * in the specified @c #audiodevice_info_t structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the path from.
 *
 * @return The path.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * audiodevice_info_get_path(audiodevice_info_t *info);

/**
 * @brief Retrieve the audio configuration of the audio device specified in an
 * audio device information structure
 *
 * The @c audiodevice_info_get_audioconfig() function gets the audio
 * configuration of the audio device in the specified @c #audiodevice_info_t
 * structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the audio
 * configuration from.
 *
 * @return The audio configuration.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * audiodevice_info_get_audioconfig(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device has input from an audio device
 *        information structure
 *
 * The @c audiodevice_info_has_input() function indicates whether the audio
 * device in the specified @c #audiodevice_info_t structure has input.
 *
 * @param info The @c #audiodevice_info_t structure to get the input flag from.
 *
 * @return The input flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_has_input(audiodevice_info_t *info);

/**
 * @brief Retrieve the number of input channels of the audio device specified in
 * an audio device information structure
 *
 * The @c audiodevice_info_get_num_input_channels() function gets the number of
 * input channels of the audio device in the specified @c #audiodevice_info_t
 * structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the number of input
 * channels from.
 *
 * @return The number of input channels.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_info_get_num_input_channels(audiodevice_info_t *info);

/**
 * @brief Retrieve the input path of the audio device specified in an audio
 *        device information structure
 *
 * The @c audiodevice_info_get_input_path() function gets the input path of the
 * audio device in the specified @c #audiodevice_info_t structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the input path from.
 *
 * @return The input path.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * audiodevice_info_get_input_path(audiodevice_info_t *info);

/**
 * @brief Retrieve the volume control of the audio device specified in an audio
 *        device information structure
 *
 * The @c audiodevice_info_get_volumecontrol() function gets the volume control
 * of the audio device in the specified @c #audiodevice_info_t structure.
 *
 * @param info The @c #audiodevice_info_t structure to get the volume control
 * from.
 *
 * @return The volume control.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API audiodevice_volume_type_t audiodevice_info_get_volumecontrol(audiodevice_info_t *info);

/**
 * @brief Retrieve the dependency of the audio device specified in an audio
 *        device information structure
 *
 * The @c audiodevice_info_get_dependency() function gets the dependency of the
 * audio device in the specified @c #audiodevice_info_t structure. The device
 * has no effect unless the dependency is also connected.  If there is no
 * dependency, this function will return a value of @c
 * AUDIODEVICE_DEVICE_UNRECOGNIZED.
 *
 * @param info The @c #audiodevice_info_t structure to get the dependency from.
 *
 * @return The dependency or @c AUDIODEVICE_DEVICE_UNRECOGNIZED if there is no
 * dependency.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API audiodevice_device_t audiodevice_info_get_dependency(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device specified in an audio device
 *        information structure is kept alive
 *
 * The @c audiodevice_info_has_keepalive() function indicates whether the audio
 * device in the specified @c #audiodevice_info_t structure is kept alive when
 * no audio stream is active.
 *
 * @param info The @c #audiodevice_info_t structure to get the keep alive flag
 * from.
 *
 * @return The keep alive flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_has_keepalive(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device specified in an audio device
 *        information structure is supported
 *
 * The @c audiodevice_info_is_supported() function indicates whether the audio
 * device in the specified @c #audiodevice_info_t structure is physically
 * installed on the hardware.
 *
 * @param info The @c #audiodevice_info_t structure to get the supported flag
 * from.
 *
 * @return The supported flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_is_supported(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device specified in an audio device
 *        information structure is suspended
 *
 * The @c audiodevice_info_is_suspended() function indicates whether the audio
 * device in the specified @c #audiodevice_info_t structure is temporarily
 * disabled by the system.
 *
 * @param info The @c #audiodevice_info_t structure to get the suspended flag
 * from.
 *
 * @return The suspended flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_is_suspended(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device specified in an audio device
 *        information structure is public
 *
 * The @c audiodevice_info_is_public() function indicates whether the audio
 * device in the specified @c #audiodevice_info_t structure is public (audibile
 * by many people) or not (audible by only one person).
 *
 * @param info The @c #audiodevice_info_t structure to get the public flag from.
 *
 * @return The public flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_is_public(audiodevice_info_t *info);

/**
 * @brief Indicate whether the audio device has audio processing from an audio
 *        device information structure
 *
 * The @c audiodevice_info_has_audioprocessing() function indicates whether the
 * audio device in the specified @c #audiodevice_info_t structure has audio
 * processing.
 *
 * @param info The @c #audiodevice_info_t structure to get the audio processing
 * flag from.
 *
 * @return The audio processing flag.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool audiodevice_info_has_audioprocessing(audiodevice_info_t *info);

/**
 * @brief Structure to contain audio device details
 *
 * @deprecated Use @c audiodevice_info_t
 *
 * The @c audiodevice_details_t structure contains the details of an audio
 * device, such as the connection status, number of channels, and so on.
 *
 * @since BlackBerry 10.0.0
 */
struct audiodevice_details_t {
    /**
     * The audio device that these details apply to.
     *
     * @since BlackBerry 10.0.0
     */
    audiodevice_device_t device;

    /**
     * Whether the audio device is connected.
     *
     * @since BlackBerry 10.0.0
     */
    bool                 connected;

    /**
     * The number of channels of the audio device.
     *
     * @since BlackBerry 10.0.0
     */
    int                  numchans;

    /**
     * The order of the channels of the audio device.
     *
     * @since BlackBerry 10.0.0
     */
    char *               order;

    /**
     * The path of the audio device.
     *
     * @since BlackBerry 10.0.0
     */
    char *               path;

    /**
     * The audioconfig of the audio device.
     *
     * @since BlackBerry 10.0.0
     */
    char *               audioconfig;

    /**
     * Whether the device has input.
     *
     * @since BlackBerry 10.0.0
     */
    bool                 input;

    /**
     * Whether the device supports volume control.
     *
     * @since BlackBerry 10.0.0
     */
    bool                 volumecontrol;

    /**
     * The device that this device is dependent on.  The device has no effect
     * unless the dependency is also connected.  If there is no dependency, this
     * field will have a value of @c AUDIODEVICE_DEVICE_UNRECOGNIZED.
     *
     * @since BlackBerry 10.0.0
     */
    audiodevice_device_t dependency;
};
/**
 * @deprecated  Use @c audiodevice_info_t.
 * A data type for the @c struct @c audiodevice_details_t that describes information
 * about the audio device.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct audiodevice_details_t audiodevice_details_t;

/**
 * @brief Retrieve the details of an audio device
 *
 * @deprecated use @c audiodevice_get_info()
 * 
 * The @c audiodevice_get_details() function gets the details of the specified
 * audio device.
 *
 * @param device The audio device to get the details of.  If this value is @c
 * AUDIODEVICE_DEVICE_UNRECOGNIZED or an audio device not supported by the
 * current version of the operating system, @c BPS_FAILURE is returned.
 * @param details This will be populated with the details of the specified audio
 * device.  The caller must call @c audiodevice_free_details() when done with
 * this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_get_details(audiodevice_device_t device, audiodevice_details_t * details) BPS_DEPRECATED;

/**
 * @brief Free the memory that is used by an audio device details structure
 *
 * @deprecated
 * 
 * The @c audiodevice_free_details() function frees the memory that is used by
 * the specified audio device details structure.
 *
 * @param details The structure whose memory needs to be freed.  Note that the
 * pointer to the structure is not freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void audiodevice_free_details(audiodevice_details_t * details) BPS_DEPRECATED;

/**
 * @brief Retrieve the unique domain ID for the audio device service
 *
 * The @c audiodevice_get_domain() function retrieves the unique domain ID for
 * the audio device service.  You can use this function in your application
 * to test whether an event that you retrieved using @c bps_get_event() is an
 * audio device event, and respond accordingly.
 *
 * @return The domain ID for the audio device service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_get_domain(void);

/**
 * @brief Retrieve the current audio device and path
 * 
 * The @c audiodevice_get() function gets the current audio device and the path
 * of that device.  Note that this will fetch values that are valid at the time
 * this function is called.
 *
 * @param device A pointer to an @c #audiodevice_device_t value that is
 *               populated with the current audio device.
 * @param path The @c char* value that is populated with the current audio
 *             device's path if the function returns @c BPS_SUCCESS. Upon
 *             success the caller is responsible for freeing the buffer using the
 *             @c bps_free() function.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_get(audiodevice_device_t *device, char **path);

/**
 * @brief Start receiving audio device events
 * 
 * The @c audiodevice_request_events() function starts to deliver audio device
 * events to the application using BPS. Events will be posted to the currently
 * active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, or @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int audiodevice_request_events(int flags);

/**
 * @brief Stop receiving audio device events
 *
 * The @c audiodevice_stop_events() function stops audio device events from
 * being delivered to the application using BPS.
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
BPS_API int audiodevice_stop_events(int flags);

/**
 * @brief Retrieve the audio device from an @c AUDIODEVICE_INFO event
 * 
 * The @c audiodevice_event_get_device() function extracts the audio device from
 * the specified @c AUDIODEVICE_INFO event.
 *
 * @param event The @c AUDIODEVICE_INFO event to extract the audio device from.
 *
 * @return The audio device.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API audiodevice_device_t audiodevice_event_get_device(bps_event_t *event);

/**
 * @brief Retrieve the audio device's path from an @c AUDIODEVICE_INFO event
 * 
 * The @c audiodevice_event_get_path() function extracts the audio device's path
 * from the specified @c AUDIODEVICE_INFO event.
 *
 * @param event The @c AUDIODEVICE_INFO event to extract the audio device from.
 *
 * @return The audio device's path.  The caller does not free this buffer.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * audiodevice_event_get_path(bps_event_t *event);

__END_DECLS

#endif
