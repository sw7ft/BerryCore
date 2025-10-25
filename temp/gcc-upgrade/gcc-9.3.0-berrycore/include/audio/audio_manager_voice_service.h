#ifndef _AUDIO_MANAGER_VOICE_SERVICE_H_INCLUDED
#define _AUDIO_MANAGER_VOICE_SERVICE_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <audio/audio_manager_device.h>

/**
 * @file audio_manager_voice_service.h
 *
 * @brief Definitions for the supported voice services.
 *
 * The audio manager maintains the voice services status for devices. This file
 * defines voice services status attributes and the functions to use them.
 *
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief Audio voice service names
 */
#define AUDIO_VOICE_SERVICE_NAMES   \
{                                   \
    "cellular",                     \
    "voip",                         \
    "naturalsound",                 \
}

/**
 * @brief Audio voice status names
 */
#define AUDIO_VOICE_STATUS_NAMES    \
{                                   \
    "off",                          \
    "ringer",                       \
    "on",                           \
}

/**
 * @brief Audio voice option names
 */
#define AUDIO_VOICE_OPTION_NAMES    \
{                                   \
    "normal",                       \
    "boost_treble",                 \
    "boost_bass",                   \
}

/**
 * @brief Audio voice codec names
 */
#define AUDIO_VOICE_CODEC_NAMES     \
{                                   \
    "narrowband",                   \
    "wideband",                     \
}

/**
 * This macro defines the string for equalizer presets.
 */
#define AUDIOMAN_VOICE_PROCESSING_SETTINGS_EQ_NAME              "eq"
/**
 * @internal For internal use only. Do not use.
 * This macro defines the string for a reserved service
 */
#define AUDIOMAN_VOICE_PROCESSING_SETTINGS_RESERVED_0_NAME      "reserved_0"
/**
 * @internal For internal use only. Do not use.
 * This macro defines the string for a reserved service
 */
#define AUDIOMAN_VOICE_PROCESSING_SETTINGS_RESERVED_1_NAME      "reserved_1"

/**
 * @internal For internal use only. Do not use.
 * This macro defines the max secured processes during a secure voice call
 */
#define AUDIOMAN_VOICE_MAX_SECURED_PIDS 10

/**
 *
 * @brief Audio voice processing settings names
 *
 * The @c AUDIOMAN_VOICE_PROCESSING_SETTINGS_AANC_NAME and
 * @c AUDIOMAN_VOICE_PROCESSING_SETTINGS_PRO_RECEIVER_NAME are for use internal
 * use only by system components. Therefore, it is not suitable for all
 * applications.
 *
 */
#define AUDIO_VOICE_PROCESSING_SETTING_NAMES                \
{                                                           \
    AUDIOMAN_VOICE_PROCESSING_SETTINGS_EQ_NAME,             \
    AUDIOMAN_VOICE_PROCESSING_SETTINGS_RESERVED_0_NAME,     \
    AUDIOMAN_VOICE_PROCESSING_SETTINGS_RESERVED_1_NAME,     \
}

/**
 * @brief The supported status of the voice services
 *
 * This enumeration defines the supported status of the voice services.
 */
typedef enum {
    /**
     * The voice service is shutdown.
     */
    AUDIO_VOICE_OFF,
    /**
     * The voice service is playing a ringtone.
     */
    AUDIO_VOICE_RINGTONE,
    /**
     * The voice service is turned on.
     */
    AUDIO_VOICE_ON,
    /**
     * The total number of status types.
     */
    AUDIO_VOICE_STATUS_COUNT,
} audio_manager_voice_service_status_t;

/**
 * @brief The supported voice service types
 *
 * This enumeration defines the supported voice service types.
 */
typedef enum {
    /**
     * The cellular voice service.
     */
    AUDIO_VOICE_CELLULAR,
    /**
     * The Voice over IP (VoIP) service.
     */
    AUDIO_VOICE_VOIP,
    /**
     * The Naturalsound voice service.
     */
    AUDIO_VOICE_NATURALSOUND,
    /**
     * The total of voice services supported.
     */
    AUDIO_VOICE_SERVICE_COUNT,
} audio_manager_voice_service_t;

/**
 * @brief Supported voice processing capabilities
 *
 * This enumeration defines the bitmask definition of supported voice
 * processing capabilities for the audio devices used for the voice services.
 */
typedef enum {
    /**
     * The audio device supports EQ presets during voice calls.
     */
    AUDIO_VOICE_PROCESSING_EQ           = (1u<<0),
    /**
     * Reserved. Do not use
     */
    AUDIO_VOICE_PROCESSING_RESERVED_0   = (1u<<1),
    /**
     * Reserved. Do not use
     * This enumerated value is intended for use by system components.
     * Therefore, it is not suitable for all applications.
     */
    AUDIO_VOICE_PROCESSING_RESERVED_1   = (1u<<2),
} audio_manager_voice_processing_capabilities_t;
/**
 * The total number of capabilities that are supported.
 */
#define AUDIO_VOICE_PROCESSING_COUNT      (3)

/**
 * @brief Supported audio options of the voice services
 *
 * The supported audio options for voice services.
 *
 */
typedef enum {
    /**
     * The audio option for no particular audio tuning.
     */
    AUDIO_VOICE_OPTION_NORMAL,
    /**
     * The audio option for treble audio tuning.
     */
    AUDIO_VOICE_OPTION_TREBLE,
    /**
     * The audio option for bass audio tuning.
     */
    AUDIO_VOICE_OPTION_BASS,
    /**
     * The total number of audio options.
     */
    AUDIO_VOICE_OPTION_COUNT,
} audio_manager_eq_option_t;

/**
 * @brief Deprecated
 * @deprecated Do not use. Instead, use @c #audio_manager_eq_option_t.
 * Supported audio options of the voice services
 * The supported audio options for voice services.
 *
 */
typedef audio_manager_eq_option_t audio_manager_voice_option_t;

/**
 * @brief The supported voice codecs
 *
 * The supported voice codecs that are available.
 */
typedef enum {
    /**
     * The voice codec is narrowband (8 KHz).
     */
    AUDIO_VOICE_CODEC_NARROWBAND,
    /**
     * The voice codec is wideband (>=16 KHz).
     */
    AUDIO_VOICE_CODEC_WIDEBAND,
    /**
     * The total number of voice codecs.
     */
    AUDIO_VOICE_CODEC_COUNT,
} audio_manager_voice_codec_t;

/**
 * @brief The audio voice processing settings
 *
 * This enumeration defines the voice processing settings that are available
 * for use.
 */
typedef struct audio_manager_voice_processing_setting
{
    union {
        int reserved_0;
        int reserved_1;
        audio_manager_eq_option_t eq;
    };
} audio_manager_voice_processing_setting_t;

/**
 * @brief Get the audio voice service name when the type of the service is
 *        specified
 *
 * Use @c audio_manager_get_voice_service_name() to return a voice service name
 * when provided an #audio_manager_voice_service_t value.
 *
 * @param service The type of the service to query.
 *
 * @return The audio voice service name. If the provided @c
 *         #audio_manager_voice_service_status_t can't be found, @c NULL is
 *         returned.
 */
const char * audio_manager_get_voice_service_name( audio_manager_voice_service_t service );

/**
 * @brief Get the audio voice service when the name of the service is specified
 *
 * Use the @c audio_manager_get_voice_service_from_name() to return the @c
 * #audio_manager_voice_service_t value that matches the provided name of the
 * audio voice service.
 *
 * @param name The name of the service to query.
 *
 * @return The audio voice service identifier. A value of @c -1 is returned if
 *         the name is not found.
 */
audio_manager_voice_service_t audio_manager_get_voice_service_from_name( const char * name );

/**
 * @brief Get the audio voice service status name when the type of
 *        the status is specified
 *
 * Use @c audio_manager_get_voice_service_status_name() to return the
 * name of the voice service  status when you provide an @c
 * #audio_manager_voice_service_status_t value.
 *
 * @param status The type of the status to query.
 *
 * @return The service status name. If the provided @c
 *         #audio_manager_voice_service_status_t can't be found, @c NULL is
 *         returned.
 */
const char * audio_manager_get_voice_service_status_name( audio_manager_voice_service_status_t status );

/**
 * @brief Get the audio voice status value based when the  name of the
 *        voice service status  is specified
 *
 * Use @c audio_manager_get_voice_service_status_from_name() to return the
 * an @c #audio_manager_voice_service_status_t value based on the
 * voice status string.
 *
 * @param name The name of the status to query.
 *
 * @return The service status identifier. A value of @c -1 is returned the provided name
 *         can't be found.
 */
audio_manager_voice_service_status_t audio_manager_get_voice_service_status_from_name( const char * name );

/**
 * @brief Get the enhanced audio(EQ) option name when the voice option is
 *        specified.
 *
 * Use @c audio_manager_get_voice_service_option_name() to return the
 * name of the enhanced audio(EQ) option when provided an @c
 * #audio_manager_voice_option_t value.
 *
 * @param option The type of the option to query.
 *
 * @return The enhanced audio(EQ) option name. If the provided @c
 *         #audio_manager_voice_service_status_t can't be found, @c NULL is
 *         returned.
 */
const char * audio_manager_get_voice_service_option_name( audio_manager_voice_option_t option );

/**
 * @brief Get the enhanced audio(EQ) option enum when the name of the option
 *        is specified
 *
 * Use @c audio_manager_get_voice_service_option_from_name() to return
 * the enhanced audio(EQ) option as an @c #audio_manager_voice_option_t value
 * representing the name of the voice service that's specified.
 *
 * @param name The name of the option to query.
 *
 * @return The enhanced audio(EQ) enumerated @c #audio_manager_voice_option_t
 *         value.
 */
audio_manager_voice_option_t audio_manager_get_voice_service_option_from_name( const char * name );


/**
 * @brief Get the current status of the specified voice service type
 *
 * Use @c audio_manager_get_voice_service_status() to return the status of the
 * name of the specified voice service type.
 *
 * @param service The voice service type to query.
 * @param status The status returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_voice_service_status( audio_manager_voice_service_t service,
                                            audio_manager_voice_service_status_t * status );


/**
 * @internal For internal use only. Do not use.
 * @brief Get the current status and the codec settings of the specified voice
 * service type
 *
 * The @c audio_manager_get_voice_service_status_with_codec_settings() function
 * returns the status and the codec settings of the specified voice service type.
 * This function is intended for use by system components. Therefore, it is not
 * suitable for all applications.
 *
 * @param service The voice service type to query.
 * @param status The status returned.
 * @param codec_name_buf The buffer to store the name of the codec the service
 *                       provider uses. Provide value of @c NULL is it's not
 *                       required.
 * @param buf_size The size of the @c codec_name_buf argument.
 * @param codec_rate The pointer to store the audio sample rate of the service
 *                   provider.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_voice_service_status_with_codec_settings(
                                            audio_manager_voice_service_t service,
                                            audio_manager_voice_service_status_t * status,
                                            char * codec_name_buf, int buf_size, int * codec_rate);

/**
 * @brief Get the current enhanced audio(EQ) setting of the specified voice
 *        service type and audio device
 *
 * Use @c audio_manager_get_voice_service_option() to return the enhanced
 * audio(EQ) option for the specified voice service type and audio device.
 *
 * @param service The voice service type to query.
 * @param dev The audio device to query.
 * @param option A pointer that's updated with the enhanced audio(EQ) option.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int __attribute__((deprecated)) audio_manager_get_voice_service_option( audio_manager_voice_service_t service,
                                            audio_manager_device_t dev,
                                            audio_manager_voice_option_t * option );

/**
 * @brief Get the current voice processing capabilities when provided the
 *        the voice service type and audio device
 *
 * Use @c audio_manager_get_voice_service_processing_capabilities() to return
 * the voice processing capabilities when you provide a voice service type and
 * audio device.
 *
 * @param service The voice service type to query.
 * @param dev The audio device to query.
 * @param capabilities The a pointer that's updated with the voice processing
 *                     capabilities.
 *
 * @return @c EOK upon success, otherwise a negative @c errno value upon
 *         failure. The @c errno values are available in @c errno.h.
 */
int audio_manager_get_voice_service_processing_capabilities( audio_manager_voice_service_t service,
                                            audio_manager_device_t dev,
                                            int * capabilities );
/**
 * @internal For internal use only. Do not use.
 * @brief Get the current voice processing settings when provided the
 *        the voice service type, voice processing capabilities, and audio device
 *
 * Use @c audio_manager_get_voice_service_processing_capabilities() to return
 * the voice processing settings when you provide a voice service type and
 * audio device. This function is intended for use by system components.
 * Therefore, it is not suitable for all applications.
 *
 * @param service The voice service type to query.
 * @param dev The audio device to query.
 * @param caps The voice processing capabilities.
 * @param values The a pointer that's updated with the voice processing
 *                     settings.
 *
 * @return @c EOK upon success, otherwise a negative @c errno value upon
 *         failure. The @c errno values are available in @c errno.h.
 */
int audio_manager_get_voice_service_processing_settings( audio_manager_voice_service_t service,
                                             audio_manager_device_t dev,
                                             audio_manager_voice_processing_capabilities_t caps,
                                             audio_manager_voice_processing_setting_t * values );

/**
 * @internal For internal use only. Do not use.
 * @brief Set the status of the specified voice service type
 *
 * The @c audio_manager_set_voice_service_status() function sets
 * the status of the specified voice service type.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param service The voice service type that the new status is applied to.
 * @param status The status to be applied.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_service_status( audio_manager_voice_service_t service,
                                            audio_manager_voice_service_status_t status );

/**
 * @internal For internal use only. Do not use.
 * @brief Set the status and the codec settings of the specified voice
 * service type
 *
 * The @c audio_manager_set_voice_service_status_with_codec_settings() function
 * sets the status and the codec settings of the specified voice service type.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param service The voice service type that the new status is applied to.
 * @param status The status to be applied.
 * @param codec_name The name of the codec the service provider uses.
 * @param codec_rate The audio sample rate the service provider uses.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_service_status_with_codec_settings(
                                            audio_manager_voice_service_t service,
                                            audio_manager_voice_service_status_t status,
                                            const char * codec_name,
                                            int codec_rate);


/**
 * @internal For internal use only. Do not use.
 * @brief Set the enhanced audio(EQ) option
 *
 * The @c audio_manager_set_voice_service_option() function sets
 * the enhanced audio(EQ) option of the specified voice service type and
 * audio device.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param service The voice service type that the new audio option is applied
 * to.
 * @param dev_output The audio device that the new audio option is applied to.
 * @param option The new enhanced audio(EQ) option to be applied.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int __attribute__((deprecated)) audio_manager_set_voice_service_option( audio_manager_voice_service_t service,
                                            audio_manager_device_t dev_output,
                                            audio_manager_voice_option_t option );


/**
 * @internal For internal use only. Do not use.
 * @brief Set the voice processing settings
 *
 * The @c audio_manager_set_voice_service_processing_settings() function processing
 * for a specified voice type and specified device.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param service The voice service type to  which the audio option is applied.
 * @param dev_output The audio device to which the specified audio options are
 *                   applied.
 * @param option The new processing settings to apply to the specified voice type
 *               and audio device.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_service_processing_settings( audio_manager_voice_service_t service,
                                             audio_manager_device_t dev,
                                             audio_manager_voice_processing_capabilities_t caps,
                                             audio_manager_voice_processing_setting_t * values );

/**
 * @internal For internal use only. Do not use.
 * @brief Set the voice process ids whitelisted for secure phone call
 *
 * The @c audio_manager_set_voice_service_secure_pids() function whitelists the
 * process ids belong to the secured phone call process
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param pids an array of process ids that would be secure for the call
 * @param count the total number of elements in the pids with a max of @c
 * AUDIOMAN_VOICE_MAX_SECURED_PIDS
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_set_voice_service_secure_pids( pid_t * pids, unsigned int count );



/**
 * @internal For internal use only. Do not use.
 * @brief Get the ID of redirector.
 *
 * The @c audio_manager_get_redirector_id() function gets the ID of redirector.
 *
 * A process must have either an effective user ID of root, or the authman
 * capability of @c access_audio_manager, to use this function. This function
 * is intended for use by system components. Therefore, it is not suitable for
 * all applications.
 *
 * @param redirector_id The ID of redirector.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */

int audio_manager_get_redirector_id( int *redirector_id );


#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_VOICE_SERVICE_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
