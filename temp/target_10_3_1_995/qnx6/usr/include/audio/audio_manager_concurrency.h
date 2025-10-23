#ifndef _AUDIO_MANAGER_CONCURRENCY_H_INCLUDED
#define _AUDIO_MANAGER_CONCURRENCY_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <audio/audio_manager_device.h>
#include <audio/audio_manager_routing.h>

/**
 * @file audio_manager_concurrency.h
 *
 * @brief Definitions for supported audio concurrency policies
 *
 * The audio manager service maintains the audio concurrency policies for the
 * supported audio types. This file defines concurrency properties and provides
 * functions to work with concurrency policies.
 *
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @internal For internal use only. Do not use.
 * @brief Supported audio attenuation types
 *
 * This enumeration defines the supported audio attenuation types.
 * This enumerated type is intended for use by system components. Therefore,
 * it is not suitable for all applications.

 */
typedef enum {

    AUDIO_ATTENUATION_MUTE          = -1,
    AUDIO_ATTENUATION_NO_EFFECT     = 100,
    AUDIO_ATTENUATION_DEFAULT       = INT_MAX,
} audio_manager_attenuation_type_t;

/**
 * @internal For internal use only. Do not use.
 * @brief Supported audio voice attenuation types
 *
 * This enumeration defines the supported audio voice attenuation types.
 * This enumerated type is intended for use by system components. Therefore,
 * it is not suitable for all applications.
 */
typedef enum {
    ATTENUATION_VOICE_UPLINK   = (1u<<0),
    ATTENUATION_VOICE_DOWNLINK = (1u<<1),
} audio_manager_attenuation_extra_option_t;

/**
 * @internal For internal use only. Do not use.
 * @brief Supported audio attenuation parameters
 *
 * This structure defines the parameters for setting the attenuation effect
 * of an audio source. This structure type is intended for use by system
 * components. Therefore, it is not suitable for all applications.
 */
typedef struct {
    /**
     * Attenuation value is a value 0-100 specified as an
     * @c #audio_manager_attenuation_type_t.
     */
    int attenuation;
    /**
     * Extra attenuation options that are represented by a bitmask of
     * @c #audio_manager_attenuation_extra_option_t.
     */
    int attenuation_extra_options;
} audio_manager_attenuation_params_t;

/**
 * @brief Audio concurrency settings
 *
 * This structure defines the audio concurrency settings.
 */
typedef struct {
    /**
     * Specifies whether the audio type is being attenuated. A value of @c true
     * indicates that the audio type is being attenuated, @c false indicates
     * otherwise.
     */
    bool attenuated;
    /**
     * Specifies whether the audio type is fully muted. A value of @c true
     * indicates that the audio type is fully muted, @c false indicates
     * otherwise.
     */
    bool muted;
    /**
     * The audio type causing the mute policy to be applied.
     */
    audio_manager_audio_type_t muted_by;
    /**
     * The identifier of the process causing the mute policy to be applied.
     */
    pid_t muted_by_pid;
} audio_manager_concurrency_t;

/**
 * @brief Get the audio concurrency status of the specified audio type
 *
 * Use @c audio_manager_get_audio_type_concurrency_status() to return
 * the audio concurrency status as a @c #audio_manager_concurrency_t for the
 * specified audio type.
 *
 * @param type The audio type to query.
 * @param status The audio concurrency status that's returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_audio_type_concurrency_status( audio_manager_audio_type_t type,
                                     audio_manager_concurrency_t * status );
/**
 * @brief Get the audio concurrency status of the specified audio manager
 *        handle
 *
 * The audio manager handle points to an audio source.
 * Use @c audio_manager_get_current_audio_handle_concurrency_status()
 * to return the current audio concurrency status as a
 * @c #audio_manager_concurrency_t value for the specified handle to the
 * audio manager service.
 *
 * @param audioman_handle The handle to the audio source to query.
 * @param status The audio concurrency status that's returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_current_audio_handle_concurrency_status( unsigned int audioman_handle,
                                     audio_manager_concurrency_t * status );

/**
 * @internal For internal use only. Do not use.
 * @brief Override the attenuation that's associated with the type of an
 *        audio source
 *
 * The @c audio_manager_set_handle_attenuation() function overrides the
 * attenuation of the specified audio manager handle applied to the lower
 * ducking priority audio sources. This function is intended for use by system
 * components. Therefore, it is not suitable for all applications.
 *
 * @param audioman_handle The audio manager handle returned by
 *                        @c audio_mananger_get_handle.
 * @param params The parameters for the handle attenuation to apply.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_handle_attenuation( unsigned int audioman_handle, audio_manager_attenuation_params_t params );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_CONCURRENCY_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
