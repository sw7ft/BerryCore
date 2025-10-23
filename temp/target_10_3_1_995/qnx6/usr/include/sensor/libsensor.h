/*
 * Research In Motion Limited. Copyright (C) 2012.
 * Research In Motion Limited. All rights reserved.
 */

#ifndef LIBSENSOR_H_
#define LIBSENSOR_H_

/**
@file libsensor.h
@brief This file contains the library interface to the BBOS sensor service

Example:
@code
int sensor_read(void)
{
#define MY_SENSOR_PULSE_CODE 1
    struct sigevent ev;

    // Create a new accelerometer sensor handle.
    sensor_t *accel = sensor_new(SENSOR_TYPE_ACCELEROMETER);

    // Initialize sigevent, for later convenience; be sure to include sensor
    // handle.
    SIGEV_PULSE_INIT(&ev, coid, SIGEV_PULSE_PRIO_INHERIT, MY_SENSOR_PULSE_CODE,
                     accel);

    // Set up notification for new events.
    sensor_event_notify(accel, &ev);

    // Repeat as needed to create additional sensor handles.
    // Notice that you can re-use local sigevent if desired (i.e., each sensor
    // handle caches a copy).
    // Be sure to change sensor handle (if populated).
    sensor_t *mag = sensor_new(SENSOR_TYPE_MAGNETOMETER);
    SIGEV_PULSE_INIT(&ev, coid, SIGEV_PULSE_PRIO_INHERIT, MY_SENSOR_PULSE_CODE,
                     mag);
    sensor_event_notify(mag, &ev);

    // Set any specific sensor attributes.
    sensor_set_delay(accel, 1000000);
    sensor_set_background(mag, true);

    // A message receive thread.
    while (!term) {
        struct _pulse pulse;
        int rcvid = MsgReceive(chid, &pulse, sizeof(pulse), NULL);

        // If you populated the sigevent value pointer, retrieve it now.
        sensor_t *sensor = (sensor_t*) pulse.value.sival_ptr;

        // Get the sensor event that woke this thread up.
        sensor_event_t event;
        if (EOK == sensor_get_event(sensor, &event)) {
            printf("Event Type(%d), Data:\t%.2f\t%.2f\t%.2f\n", event.type,
                   event.motion.dsp.x, event.motion.dsp.y, event.motion.dsp.z);
        }

        // Conveniently you can re-arm using the cached sigevent
        sensor_event_notify_rearm(sensor);
    }

    // Delete the sensor instances to free memory and save power.
    sensor_delete(&accel);
    sensor_delete(&mag);

    return EXIT_SUCCESS;
}
@endcode
 */

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <stdbool.h>
#include <stdint.h>
#include <sys/siginfo.h>
#include <sensor/sensor.h>
#include <sys/time.h>

/**
 * @brief The handle of a sensor
 *
 */
typedef struct sensor_s sensor_t;

/**
 *  @brief Check for sensor existence
 *
 *  @param[in] sensor_type  The sensor type you wish to check for existence.
 *                          Sensor types are defined in @c sensor/sensor.h.
 *  @return    bool         True if a sensor is currently available for use
 *                          on your device, false otherwise.
*/

bool sensor_exists(sensor_type_e sensor_type);

/**
 *  @brief Create a new sensor of the type specified
 *
 *  @param[in] sensor_type  The sensor type you wish to create a handle for.
 *                          Sensor types are defined in @c sensor/sensor.h.
 *  @return    sensor_t*    A pointer to the sensor if successful, otherwise
 *                          NULL. You'll need to pass this handle to many of
 *                          the sensor functions.
*/
sensor_t* sensor_new(sensor_type_e sensor_type);

/**
 * @brief Delete a sensor, freeing memory and allowing the sensor to be powered
 *        down
 *
 * @param[in] sensor A pointer to the sensor handle pointer.
*/
void sensor_delete(sensor_t **sensor);

/**
 * @brief Set up the notification method for a sensor
 *
 * This function calls @c ionotify() to arm the system with the sigevent that
 * you want to use as a notification.
 *
 * The sigevent is cached in the sensor.
 *
 * @param[in] sensor  The sensor to modify.
 * @param[in] ev      The sigevent to use as a notification.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_event_notify(sensor_t *sensor, struct sigevent *ev);

/**
 * @brief Rearm the system with the cached sigevent
 *
 * This function calls @c ionotify() to rearm the system with the sigevent
 * that was cached in the previous call to @c sensor_event_notify().
 *
 * @param[in] sensor  The sensor to modify.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_event_notify_rearm(sensor_t *sensor);

/**
 * @brief Suspend the delivery of events from the sensor to the thread
 *
 * This function effectively disables the sensor. The sensor can be re-enabled
 * and the delivery of events can be resumed by calling @c sensor_resume().
 *
 * @param[in] sensor  The sensor to modify.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_pause(sensor_t *sensor);

/**
 * @brief Resume the delivery of events from the sensor to the thread
 *
 * This function enables the sensor and resumes the delivery of events from the
 * sensor to the thread.
 *
 * Be sure to call @c sensor_event_notify or @c sensor_event_notify_rearm after
 * calling resume, or events will not be delivered.
 *
 * @param[in] sensor  The sensor to modify.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_resume(sensor_t *sensor);

/**
 * @brief Set the sensor delay between events
 *
 * @param[in] sensor  The sensor to modify.
 * @param[in] delay   The delay to set (in microseconds).
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_set_delay(sensor_t *sensor, uint32_t delay);

/**
 * @brief Get the sensor delay between events
 *
 * This function returns the sensor delay between events (i.e., the period of
 * time that elapses before the sensor delivers the next event).
 *
 * If @see sensor_set_delay() has not been called, the default delay is
 * returned. Otherwise, the rate set by @c sensor_set_delay() is returned. Note
 * that the rate returned may be different than what was set.
 *
 * @param[in]   sensor  The sensor to access.
 * @param[out]  delay   The delay (in microseconds).
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_get_delay(sensor_t *sensor, uint32_t *delay);

/**
 * @brief Enable or disable the sensor queue
 *
 * Enabling the queue creates a client-specific service side queue of
 * events. This is useful for clients wishing to not miss any events.
 *
 * @param[in]  sensor  The sensor to modify.
 * @param[in]  enable  1 to enable the queue, or 0 to disable it.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_set_queue(sensor_t *sensor, bool enable);

/**
 * @brief Enable or disable batching mode
 *
 * When batching is enabled and supported by the hardware, sensors will
 * report samples in hardware-specific batch sizes to conserve power.
 *
 * @param[in]  sensor  The sensor to modify.
 * @param[in]  enable  1 to enable batching mode, or 0 to disable it.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_set_batching(sensor_t *sensor, bool enable);

/**
 * @brief Enable or disable background mode
 *
 * When background mode is enabled, the sensor isn't automatically disabled when
 * the device is in standby. This is useful for clients that wish
 * to continue to receive sensor events when the screen is off. Power
 * consumption must be considered when using this feature.
 *
 * @param[in]  sensor  The sensor to modify.
 * @param[in]  enable  1 to enable background mode, or 0 to disable it.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_set_background(sensor_t *sensor, bool enable);

/**
 * @brief Enable or disable reduced reporting
 *
 * When reduced reporting is enabled, only a significant change between the last
 * read event and the current unread event will cause an event to be delivered
 * to the thread (e.g., duplicates are skipped, as are sensor changes that
 * are insignificant). This is useful for clients who are only interested in
 * significant changes. As the sensor will not be streaming data, enabling this
 * feature will save power.
 *
 * @param[in] sensor  The sensor to modify.
 * @param[in] enable  1 to enable reduced reporting, or 0 to disable it.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_set_reduced_reporting(sensor_t *sensor, bool enable);

/**
 * @brief Retrieve information for the specified sensor
 *
 * @param[in]  sensor  The sensor to access.
 * @param[out] info    A pointer to a location where the function can store the
 *                     sensor information.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_get_info(sensor_t *sensor, sensor_info_t *info);

/**
 * @brief Retrieve the latest event from the sensor, if available
 *
 * If the latest event isn't available, this function returns @c EAGAIN.
 *
 * This call is non-blocking.
 *
 * @param[in]  sensor        The sensor to access.
 * @param[out] sensor_event  A pointer to a location where the function can
 *                           store the event retrieved from the sensor.
 *
 * @return @c EOK on success, @c EAGAIN if the latest event is not available,
 *         an @c errno value otherwise.
*/
int sensor_get_event(sensor_t *sensor, sensor_event_t *sensor_event);

/**
 * @brief Wait for the latest event from the sensor
 *
 * This call will block until either data is available, or until the specified
 * timeout period has passed. If @c timeout is NULL, this call will block
 * indefinitely.
 *
 * @param[in]  sensor        The sensor to access.
 * @param[out] sensor_event  A pointer to a location where the function can
 *                           store the event retrieved from the sensor.
 * @param[in]  timeout       Pass a @c timeval to unblock after a certain period
 *                           of time has elapsed, or pass NULL to block
 *                           indefinitely.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_wait_event(sensor_t *sensor, sensor_event_t *sensor_event, struct timeval *timeout);

/**
 * @brief Structure to store a pressure sensor history element
 *
 * This structure is used in @c #sensor_history_pressure_data_t.
 */
typedef struct {
    uint64_t timestamp;  /**< The time the pressure sample was taken at. */
    float pressure;      /**< The pressure read at the indicated time. */
    float temperature;   /**< The temperature of the pressure sensor itself. */
} sensor_history_pressure_element_t;

/**
 * Structure used to hold an array of most recent pressure sensor events.
 *
 * This structure is populated by @c sensor_history_pressure().
 */
typedef struct {
    sensor_history_pressure_element_t element[48]; /**< Array of pressure sensor elements */
} sensor_history_pressure_data_t;

/**
 * @brief Retrieve pressure sensor history
 *
 * This function populates the passed in @c #sensor_history_pressure_data_t
 * structure with the most recently recorded pressure sensor events.
 *
 * Example usage:
 * @code
 * sensor_history_pressure_data_t data = { 0 };
 * sensor_history_pressure(&data);
 * int i;
 * for (i = 0; i < sizeof(data.element) / sizeof(*data.element); i++) {
 *     printf("Pressure: %f\n", data.element[i].pressure);
 * }
 * @endcode
 *
 * @param[in]  data  The structure to populate with pressure sensor events.
 *
 * @return @c EOK on success, an @c errno value otherwise.
*/
int sensor_history_pressure(sensor_history_pressure_data_t *data);

__END_DECLS

#endif /* LIBSENSOR_H_ */
