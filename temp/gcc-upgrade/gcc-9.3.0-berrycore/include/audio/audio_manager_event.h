#ifndef _AUDIO_MANAGER_EVENT_H_INCLUDED
#define _AUDIO_MANAGER_EVENT_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <audio/audio_manager_device.h>
#include <audio/audio_manager_routing.h>
#include <audio/audio_manager_volume.h>
#include <audio/audio_manager_voice_service.h>
#include <audio/audio_manager_concurrency.h>
/**
 * @file audio_manager_event.h
 *
 * @brief Definitions for supported audio manager events.
 *
 * The audio manager controls audio routing, concurrency, and volume control
 * automatically. A client can subscribe to specific events to listen for
 * changes that are related to audio manager activities. The events are
 * broadcast to all clients and are asynchronous. The clients that respond to
 * the events are subject to act within a reasonable time frame in order to have
 * audio transition without artifacts.
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief The supported audio events
 *
 * This enumeration defines the audio events currently supported.
 */
typedef enum {
    /**
     * Changes to the audio input/output path.
     */
    AUDIO_ROUTING_CHANGE,
    /**
     * Changes to the audio concurrent policy of a specified audio type.
     */
    AUDIO_CONCURRENCY_CHANGE,
    /**
     * Changes to the attributes of the specified audio device.
     */
    AUDIO_DEVICE_CHANGE,
    /**
     * Changes to the volume of the specified audio device.
     */
    AUDIO_VOLUME_CHANGE,
    /**
     * Changes to the headphone volume boost settings.
     */
    AUDIO_HEADPHONE_BOOST_CHANGE,
    /**
     * Changes to the volume of the specified audio device during voice calls.
     */
    AUDIO_VOICE_VOLUME_CHANGE,
    /**
     * Changes to the status of the specified voice service.
     */
    AUDIO_VOICE_SERVICE_CHANGE,
    /**
     * Changes to the button state of the specified audio device.
     */
    AUDIO_DEVICE_BUTTON_CHANGE,
    /**
     * Changes to the button state of the specified audio device.
     */
    AUDIO_HEADPHONE_UNSAFE_ZONE_CHANGE,
    /**
     * Changes to the statistics of audio usage.
     */
    AUDIO_STAT_CHANGE,
    /**
     * Deprecated.
     * Changes to the audio options of the voice services.
     */
    AUDIO_VOICE_OPTION_CHANGE,
    /**
     * Changes to the audio options of the voice services.
     */
    AUDIO_VOICE_PROCESSING_SETTING_CHANGE = AUDIO_VOICE_OPTION_CHANGE,
    /**
     * Changes to the headphone output volume regulation
     */
    AUDIO_HEADPHONE_OUTPUT_VOLUME_REGULATION_CHANGE,
    /**
     * Changes to the overall audio system status
     */
    AUDIO_SYSTEM_STATUS_CHANGE,

    /**
     * @internal For internal use only. Do not use.
     * Total of the event types. This function is intended for use by system
     * components. Therefore, it is not suitable for all applications.
     */
    AUDIO_EVENT_TYPE_COUNT,
} audio_manager_event_type_t;

/**
 * @brief The changes of the audio input/output path
 *
 * This structure defines the audio routing change event.
 */
typedef struct {
    /**
     * The audio output device that was previously active.
     */
    audio_manager_device_t dev_prev;
    /**
     * The audio output device currently being used as primary.
     */
    audio_manager_device_t dev_now;
    /**
     * The audio input device that was previously active.
     */
    audio_manager_device_t dev_input_prev;
    /**
     * The audio input device currently being used as primary.
     */
    audio_manager_device_t dev_input_now;

} audio_manager_routing_change_t;

/**
 * @brief The audio concurrency change event
 *
 * This structure defines the changes to the audio concurrency policy of the
 * specified audio type.
 */
typedef struct {
    /**
     * The audio type that the event is triggered for.
     */
    audio_manager_audio_type_t audio_type;
    /**
     * The concurrency policy status of the specified audio type.
     */
    audio_manager_concurrency_t status;
} audio_manager_concurrency_change_t;

/**
 * @brief The audio device change event.
 *
 * This structure defines the changes to the attribute(s) of a specified audio
 * device.
 */
typedef struct {
    /**
     * The audio device that the event is triggered for.
     */
    audio_manager_device_t dev;
    /**
     * The change in format of the audio device.
     */
    char * diff;
} audio_manager_device_change_t;

/**
 * @brief The audio volume change event
 *
 * This structure defines the changes to the volume of the specified audio
 * device.
 */
typedef struct {
    /**
     * The audio device that the event is triggered for.
     */
    audio_manager_device_t dev;
    /**
     * The current output volume level (percentage) of the specified audio device.
     */
    double output_level;
    /**
     * The current input volume level (percentage) of the specified audio device.
     */
    double input_level;
    /**
     * The current output mute status of the specified audio device.
     */
    bool output_mute;
    /**
     * The current input mute status of the specified audio device.
     */
    bool input_mute;
} audio_manager_status_volume_change_t;

/**
 * @brief The audio headphone boost change event
 *
 * This structure defines the changes to the headphone volume boost settings.
 */
typedef struct {
    /**
     * The limit level of the headphone volume without boost enabled.
     */
    int headphone_boost_level;
    /**
     * The current setting of headphone boost to override the limit.
     */
    bool headphone_override;
    /**
     * The status of the headphone volume boost.
     */
    audio_manager_headphone_volume_override_status_t headphone_boost;
} audio_manager_status_headphone_boost_change_t;

/**
 * @brief The audio headphone volume unsafe-zone change event.
 *
 * This structure defines the changes to the headphone volume boost settings.
 */
typedef struct {
    /**
     * The status of the headphone volume unsafe zone.
     */
    audio_manager_headphone_volume_override_status_t headphone_unsafe_zone;
} audio_manager_status_headphone_unsafe_zone_change_t;

/**
 * @internal For internal use only. Do not use.
 * @brief The audio headphone output volume regulation change event
 *
 * This structure defines the changes to the headphone output volume regulation
 * status.
 */
typedef struct {
    /**
     * The event defines a change to the headphone output-volume regulation.
     */
    audio_manager_headphone_output_regulation_t status;
} audio_manager_status_headphone_output_volume_regulation_change_t;

/**
 * @brief The audio voice volume change event
 *
 * This structure defines the changes to the volume of the specified audio
 * device during voice calls.
 */
typedef audio_manager_status_volume_change_t audio_manager_voice_status_volume_change_t;

/**
 * @brief The audio voice service change event
 *
 * This structure defines the changes to the status of a specified voice
 * service.
 */
typedef struct {
    /**
     * The voice service that the event is triggered for
     */
    audio_manager_voice_service_t service;
    /**
     * The current status of the voice service.
     */
    audio_manager_voice_service_status_t status;
} audio_manager_voice_service_change_t;

/**
 * @brief The headset button change event
 *
 * This structure defines the changes to the headset button presses.
 */
typedef struct {
    /**
     * The audio device that the event is triggered for.
     */
    audio_manager_device_t dev;
    /**
     * The current device button states.
     */
    audio_manager_headset_button_state_t state;
} audio_manager_device_button_change_t;

/**
 * @brief The audio statistics change event.
 *
 * This structure defines the changes to the audio statistics.
 */
typedef struct {
    /**
     * The name of the statistic entry to be monitored.
     */
    char name[64];
    /**
     * The value of the statistic entry.
     */
    uint64_t     value;
} audio_manager_stat_change_t;

/**
 * @internal For internal use only. Do not use.
 * @brief The voice audio options change event
 *
 * This structure defines the changes to the audio options of the specified
 * voice service. This structured type is intended for use by system components.
 * Therefore, it is not suitable for all applications.
 */
typedef struct {
    /**
     * The voice service that the event is triggered for.
     */
    audio_manager_voice_service_t service;
    /**
     * The audio device that the event is triggered for.
     */
    audio_manager_device_t dev;
    /**
     * The current audio option selected.
     */
    union {
        /**
         * Deprecated. The voice processing option to use.
         */
        int option;
         /**
          * The voice processing setting to use.
          */
        audio_manager_voice_processing_setting_t setting;
    };
    /**
     * The audio processing capability that the event is triggered for.
     */
    audio_manager_voice_processing_capabilities_t cap;
} audio_manager_voice_audio_option_change_t;

/**
 * @brief The overall audio system status change event
 *
 * This structure defines the changes of the status of the overall
 * audio system.
 *
 */
typedef struct {
    /**
     * The current audio option selected.
     */
    audio_manager_audio_system_status_t status;
} audio_manager_audio_system_status_change_t;


/**
 * @brief The event loop context
 *
 * This structure defines the audio event context.
 */
typedef struct audio_manager_event_context audio_manager_event_context_t;

/**
 * @brief Block until the audio manager service completes initialization
 *
 * Use @c audio_manager_wait_for_initialization() to block so that your
 * app can wait for the initialization of the audio manager service.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_wait_for_initialization();

/**
 * @brief Allocate the event context
 *
 * Use @c audio_manager_get_event_context() to allocate the context. The context
 * is required to allow for the delivery of events.
 *
 * @param context The context that's returned.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_event_context( audio_manager_event_context_t ** context );

/**
 * @brief Free the event context
 *
 * Use @c audio_manager_release_event_context() to free the context
 * @c audio_manager_get_event_context() allocated to your application.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_release_event_context( audio_manager_event_context_t ** context );

/**
 * @brief Add a routing change event to the event list
 *
 * Use @c audio_manager_add_routing_change_event() to add the change
 * event to the event list, which is monitored by calls to @c
 * audio_manager_get_event(). The function interrupts the @c 
 * audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_routing_change_event( audio_manager_event_context_t * context );

/**
 * @brief Add a concurrency change event to the event list
 *
 * Use @c audio_manager_add_concurrency_change_event() to add the change
 * event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param audio_type The audio type that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_concurrency_change_event( audio_manager_event_context_t * context,
                                                audio_manager_audio_type_t audio_type );

/**
 * @brief Add a device change event to the event list
 *
 * The @c audio_manager_add_device_change_event() function adds the change
 * event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_device_change_event( audio_manager_event_context_t * context,
                                           audio_manager_device_t dev );

/**
 * @brief Add a device button change event to the event list
 *
 * Use @c audio_manager_add_device_button_change_event() to add the
 * change event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_device_button_change_event( audio_manager_event_context_t * context,
                                                  audio_manager_device_t dev );



/**
 * @brief Add a volume change event to the event list
 *
 * Use @c audio_manager_add_volume_change_event() to add the change
 * event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_volume_change_event( audio_manager_event_context_t * context,
                                           audio_manager_device_t dev );

/**
 * @brief Add a headphone volume boost change event to the event list
 *
 * Use @c audio_manager_add_status_hp_boost_change_event() to add the
 * change event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_status_hp_boost_change_event( audio_manager_event_context_t * context );

/**
 * @brief Add a headphone volume unsafe-zone change event to the event list
 *
 * The @c audio_manager_add_status_hp_unsafe_zone_change_event() function adds
 * the change event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it is already being blocked in
 * another thread. The @c audio_manager_get_event() function is then called to
 * include the new event.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_status_hp_unsafe_zone_change_event( audio_manager_event_context_t * context );

 /**
 * @internal For internal use only. Do not use.
 * @brief Add a headphone output volume regulation change event to the event
 * list
 *
 * The @c audio_manager_add_status_hp_output_volume_regulation_change_event()
 * function adds the change event to the event list, which is monitored by calls
 * to @c audio_manager_get_event().
 *
 * The function interrupts the @c audio_manager_get_event() function if it is
 * already being blocked in another thread. The @c audio_manager_get_event()
 * function is then called to include the new event.
 *
 * This function is intended for use by system components. Therefore,
 * it is not suitable for all applications.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_status_hp_output_volume_regulation_change_event( audio_manager_event_context_t * context );


/**
 * @brief Add a voice volume change event to the event list
 *
 * Use @c audio_manager_add_voice_volume_change_event() to add the change
 * event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_voice_volume_change_event( audio_manager_event_context_t * context,
                                                 audio_manager_device_t dev );

/**
 * @brief Add a voice service change event to the event list
 *
 * Use @c audio_manager_add_voice_service_change_event() to add the
 * change event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param service The voice service that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_voice_service_change_event( audio_manager_event_context_t * context,
                                                  audio_manager_voice_service_t service );
/**
 * @internal For internal use only. Do not use.
 * @brief Add a voice processing voice change event to the event list
 *
 * The @c  audio_manager_add_voice_processing_setting_change_event() function adds
 * a change event to the event list. The change event indicates that there is a
 * setting change in voice processing. Calls to the @c audio_manager_get_event()
 * monitor the event list for changes. This function interrupts the @c
 * audio_manager_get_event() function if it's blocked in another thread. Call
 * @c audio_manager_get_event() after you call this function to include the
 * new change event that was added by this function.
 *
 * This function is intended for use by system components. Therefore,
 * it is not suitable for all applications.
 *
 * @param context The context that's returned by @c audio_manager_get_event_context().
 * @param service The voice service that the event is triggered for.
 * @param dev The audio device the event is triggered for.
 * @param cap The voice processing settings to add.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_voice_processing_setting_change_event(
                                    audio_manager_event_context_t * context,
                                    audio_manager_voice_service_t service,
                                    audio_manager_device_t dev,
                                    audio_manager_voice_processing_capabilities_t cap);

/**
 * @brief Add a voice audio option change event to the event list
 *
 * The @c audio_manager_add_voice_audio_option_change_event() function adds the
 * change event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param service The voice service that the event is triggered for.
 * @param dev The audio device the event is triggered for.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int __attribute__((deprecated)) audio_manager_add_voice_audio_option_change_event(
                                    audio_manager_event_context_t * context,
                                    audio_manager_voice_service_t service,
                                    audio_manager_device_t dev);


/**
 * @brief Add an audio statistics change event to the event list
 *
 * Use @c audio_manager_add_stat_change_event() to add the change
 * event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param name The voice service that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_stat_change_event( audio_manager_event_context_t * context,
                                         const char * name );

/**
 * @brief Add the audio system change status event to the event list
 *
 * Use @c audio_manager_add_audio_system_status_change_event() to add
 * the change event to the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_add_audio_system_status_change_event( audio_manager_event_context_t * context );

/**
 * @brief Remove a routing change event from the event list
 *
 * Use @c audio_manager_remove_routing_change_event() to remove the
 * change event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_routing_change_event( audio_manager_event_context_t * context );

/**
 * @brief Remove a concurrency change event from the event list
 *
 * Use @c audio_manager_remove_concurrency_change_event() to remove the
 * change event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param audio_type The audio type that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_concurrency_change_event( audio_manager_event_context_t * context,
                                                   audio_manager_audio_type_t audio_type );

/**
 * @brief Remove a device change event from the event list
 *
 * Use @c audio_manager_remove_device_change_event() to remove the change
 * event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_device_change_event( audio_manager_event_context_t * context,
                                              audio_manager_device_t dev );

/**
 * @brief Remove a device button change event from the event list
 *
 * Use @c audio_manager_remove_device_button_change_event() to remove
 * the change event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */

int audio_manager_remove_device_button_change_event( audio_manager_event_context_t * context,
                                                  audio_manager_device_t dev );
/**
 * @brief Remove a volume change event from the event list
 *
 * Use @c audio_manager_remove_volume_change_event() to remove the change
 * event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_volume_change_event( audio_manager_event_context_t * context,
                                              audio_manager_device_t dev );

/**
 * @brief Remove a headphone volume boost change event from the event list.
 *
 * Use @c audio_manager_add_status_hp_boost_change_event() to remove the
 * event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_status_hp_boost_change_event( audio_manager_event_context_t * context );

/**
 * @brief Remove a headphone volume unsafe-zone change event from the event list
 *
 * Use @c audio_manager_remove_status_hp_unsafe_zone_change_event() to
 * remove the event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_status_hp_unsafe_zone_change_event( audio_manager_event_context_t * context );

/**
 * @internal For internal use only. Do not use.
 * @brief Remove a headphone output volume regulation change event from the
 * event list
 *
 * Use @c audio_manager_remove_status_hp_output_volume_regulation_change_event()
 * to remove the event from the event list that will be monitored. The
 * function will interrupt the @c audio_manager_get_event() function if it's
 * blocked in another thread. Call @c audio_manager_get_event() after you call
 * this function to include the new change event that was added by this
 * function. This function is intended for use by system components. Therefore,
 * it is not suitable for all applications.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_status_hp_output_volume_regulation_change_event( audio_manager_event_context_t * context );

/**
 * @brief Remove a voice volume change event from the event list
 *
 * Use @c audio_manager_remove_voice_volume_change_event()to remove the
 * event from the event list, which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_voice_volume_change_event( audio_manager_event_context_t * context,
                                                    audio_manager_device_t dev );

/**
 * @internal For internal use only. Do not use.
 * @brief Remove a voice service change event from the event list
 *
 * Use @c audio_manager_remove_voice_service_change_event() to remove the
 * event from the event list which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * This function is intended for use by system components. Therefore,
 * it is not suitable for all applications.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param service The voice service that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_voice_service_change_event( audio_manager_event_context_t * context,
                                                     audio_manager_voice_service_t service );

int audio_manager_remove_voice_processing_settings_change_event(
                                      audio_manager_event_context_t * context,
                                      audio_manager_voice_service_t service,
                                      audio_manager_device_t dev,
                                      audio_manager_voice_processing_capabilities_t cap );

/**
 * @brief Remove a voice audio option change event from the event list
 *
 * The @c audio_manager_remove_voice_audio_option_change_event() function
 * removes the event from the event list which is  monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this
 * function to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param service The voice service that the event is triggered for.
 * @param dev The audio device that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int __attribute__((deprecated)) audio_manager_remove_voice_audio_option_change_event(
                                      audio_manager_event_context_t * context,
                                      audio_manager_voice_service_t service,
                                      audio_manager_device_t dev);



/**
 * @brief Remove an audio statistics change event from the event list
 *
 * The @c audio_manager_remove_stat_change_event() function removes the
 * event from the event list which is monitored by calls to
 * @c audio_manager_get_event(). The function interrupts the
 * @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this function
 * to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param name The voice service that the event is triggered for.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_stat_change_event( audio_manager_event_context_t * context,
                                            const char * name );

/**
 * @brief Remove the audio system status change event from the event list
 *
 * The @c audio_manager_remove_audio_system_status_change_event() function
 * removes the audio system change event from the event list which is
 * monitored by calls to @c audio_manager_get_event(). The function interrupts
 * the @c audio_manager_get_event() function if it's blocked in
 * another thread. Call @c audio_manager_get_event() after you call this function
 * to include the new change event that was added by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_remove_audio_system_status_change_event( audio_manager_event_context_t * context );

/**
 * @brief Get the next change event
 *
 * The @c audio_manager_get_event() function blocks until the next change
 * event is available. This function is used for typical message get/dispatch
 * event loops. You can call @c audio_manager_dispatch_event() to clear
 * the event that's returned by this function.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param event_type The type of the event triggered.
 * @param event_params The parameters of the event triggered. The caller is
 * responsible for casting the pointer to the proper change event structure.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_event( audio_manager_event_context_t * context,
                             audio_manager_event_type_t * event_type,
                             void ** event_params );
/**
 * @brief Get the file descriptors of the events
 *
 * The @c audio_manager_get_event_fd() function returns the current file
 * descriptors of the events added to the event list.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param fd The file descriptor. This can be passed to @c select() or
 * @c io_notify().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_get_event_fd( audio_manager_event_context_t * context,
                                int * fd );

/**
 * @brief Check for the next change event without blocking
 *
 * Use @c audio_manager_peek_event() to determine whether an event
 * has occurred. If an event is found, it returns the event. This
 * function allows you to check for and retrieve an event
 * without blocking. You can call @c audio_manager_dispatch_event()
 * to clear the event that is returned.
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param fd The file descriptor returned by @c audio_manager_get_event_fd().
 * @param event_type The type of the event triggered.
 * @param event_params The parameters of the event triggered. The caller is
 *                     responsible for casting the pointer to the proper
 *                     change event structure.
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_peek_event( audio_manager_event_context_t * context,
                              int fd,
                              audio_manager_event_type_t * event_type,
                              void ** event_params );

/**
 * @brief Dispatch the change event
 *
 * The @c audio_manager_dispatch_event() function marks an event as
 * dispatched and it no longer returns from @c audio_manager_peek_event() or
 * @c audio_manager_dispatch_event().
 *
 * @param context The context returned by @c audio_manager_get_event_context().
 * @param event_type The type of the event returned by
 *                   @c audio_manager_peek_event().
 * @param event_params The parameters of the event returned by
 *                    @c audio_manager_peek_event().
 *
 * @return @c EOK upon success, a negative @c errno upon failure. The @c errno
 *         values are available in the @c errno.h file.
 */
int audio_manager_dispatch_event( audio_manager_event_context_t * context,
                                  audio_manager_event_type_t event_type,
                                  void * event_params );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_EVENT_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
