/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file sensor.h
 *
 * @brief Functions to read various input sensors on the device
 *
 * This file defines the sensor service, which provides functions for reading
 * the various input sensors that are available on the device, including the
 * accelerometer, magnetometer, temperature, illuminance, and so on.
 *
 * The sensors are listed by the enumeration @c #sensor_type_t.  To see if a
 * sensor is supported on the device call @c sensor_is_supported().  To start
 * receiving sensor events, call @c sensor_request_events() and pass in the
 * sensor type. To set the refresh rate of the sensor, call the @c
 * sensor_set_rate() function. To specify whether duplicate sensor events should
 * be skipped, call the @c sensor_set_skip_duplicates() function.
 *
 * Once a BPS event is received, you can call the @c sensor_get_domain()
 * function to determine whether it was a sensor event and the @c
 * bps_event_get_code() to determine the type of sensor event.
 *
 * The sensors return a variety of different data, so depending on which sensor
 * you want to use, you need to call a different @c sensor_event_get_* function
 * to retrieve the readings. See the individual functions to determine which
 * sensors they work with.
 *
 * To stop receiving sensor events, call the @c sensor_stop_events() function.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_SENSOR_H_INCLUDED
#define _BPS_SENSOR_H_INCLUDED

#include <sys/platform.h>
#include <stdbool.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * The Earth's gravity.
 *
 * @since BlackBerry 10.0.0
 */
#define SENSOR_GRAVITY_EARTH 9.80665

/**
 * @brief Sensor readings
 *
 * This enumeration defines event codes for the sensor events.
 * @anonenum bps_sensor_events Sensor events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * A reading was made by the acceleration sensor.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ACCELEROMETER_READING            = 0x00,

    /**
     * A reading was made by the magnetometer sensor.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_MAGNETOMETER_READING             = 0x01,

    /**
     * A reading was made by the gyroscope.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_GYROSCOPE_READING                = 0x02,

    /**
     * A reading for azimuth, pitch, and roll is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_AZIMUTH_PITCH_ROLL_READING       = 0x03,

    /**
     * A reading for the altitude is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ALTIMETER_READING                = 0x04,

    /**
     * A reading for the temperature is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TEMPERATURE_READING              = 0x05,

    /**
     * A reading that measures how close an object is to the front of the
     * device.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_PROXIMITY_READING                = 0x06,

    /**
     * A reading that measures the brightness level.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_LIGHT_READING                    = 0x07,

    /**
     * A reading for the gravitational field is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_GRAVITY_READING                  = 0x08,

    /**
     * A reading for linear acceleration is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_LINEAR_ACCEL_READING             = 0x09,

    /**
     * A reading for the rotational vector is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ROTATION_VECTOR_READING          = 0x0A,

    /**
     * A reading for the rotation provided as a rotational matrix is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ROTATION_MATRIX_READING          = 0x0B,

    /**
     * A reading that the orientation changed and is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_READING              = 0x0C,

    /**
     * A reading that detected a face (or object) near the device is available.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_FACE_DETECT_READING              = 0x0D,

    /**
     * A reading that indicates whether the device has been or holstered, or
     * not.
     *
     * @since BlackBerry 10.2.0
     */
    SENSOR_HOLSTER_READING                  = 0x0E,

    /**
     * A reading that indicates the compass heading.
     *
     * @since BlackBerry 10.2.0
     */
    SENSOR_COMPASS_READING                  = 0x0F,

    /**
     * A reading for air pressure is available.
     *
     * @since BlackBerry 10.2.0
     */
    SENSOR_PRESSURE_READING                 = 0x10,
};

/**
 * @brief Supported sensors
 *
 * This enumeration defines the various sensors that are supported by this API.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The acceleration sensor that measures the acceleration force along the x,
     * y, and z-axis.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_ACCELEROMETER               = 0,

    /**
     * The magnetic sensor that measures the magnetic field for x, y, and
     * z-axis.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_MAGNETOMETER                = 1,

    /**
     * The gyroscope sensor that measures the rate of rotation around the x, y,
     * and z-axis.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_GYROSCOPE                   = 2,

    /**
     * The azimuth-pitch-roll sensor that measures the current angles with
     * reference to the world reference frame.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_AZIMUTH_PITCH_ROLL          = 3,

    /**
     * The altimeter measures the altitude by using air pressure measurements.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_ALTIMETER                   = 4,

    /**
     * The temperature sensor that measures the temperature in degrees Celsius.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_TEMPERATURE                 = 5,

    /**
     * The proximity sensor measures how close an object, such as a user's ear,
     * is to the front of the device.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_PROXIMITY                   = 6,

    /**
     * The illuminance sensor that measures the amount of ambient light or
     * illumination.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_LIGHT                       = 7,

    /**
     * The gravity sensor that measures the force of gravity along the x, y, and
     * z-axis.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_GRAVITY                     = 8,

    /**
     * The linear acceleration sensor that measures acceleration along the x, y,
     * or z-axis. The measurement excludes gravity.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_LINEAR_ACCEL                = 9,

    /**
     * The rotation sensor that measures the orientation of the device by
     * providing the rotation vector around the x, y, and z-axis.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_ROTATION_VECTOR             = 10,

    /**
     * The rotation matrix represents the orientation of the world frame in the
     * device frame.
     *
     * @since BlackBerry 10.0.0
     */

    SENSOR_TYPE_ROTATION_MATRIX             = 11,

    /**
     * The orientation sensor that measures the degrees of orientation around
     * the x, y, and z-axis.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_ORIENTATION                 = 12,

    /**
     * The face-detection sensor is used to detect a face that is near the
     * device.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_TYPE_FACE_DETECT                 = 13,

    /**
     * The holster sensor that detects when the device is holstered or removed
     * from the holster.
     *
     * @since BlackBerry 10.2.0
     */
    SENSOR_TYPE_HOLSTER                     = 14,

    /**
     * The compass sensor give compass heading readings.
     *
     * @since BlackBerry 10.2.0
     */
    SENSOR_TYPE_COMPASS                     = 15,

    /**
     * The pressure sensor give air pressure readings.
     *
     * @since BlackBerry 10.2.0
     */
    SENSOR_TYPE_PRESSURE                    = 16,
} sensor_type_t;

/**
 * @brief Sensor accuracy
 *
 * This enumeration defines the different accuracy level values for each sensor
 * reading.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The sensor accuracy is not reliable and should not be trusted.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ACCURACY_UNRELIABLE              = 0,

    /**
     * This sensor is reporting data with low accuracy. You can use calibration
     * with the environment to make the data more useful.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ACCURACY_LOW                     = 1,

    /**
     * This sensor is reporting data with average accuracy. You can use
     * calibration with the environment to improve readings.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ACCURACY_MEDIUM                  = 2,

    /**
     * This sensor is reporting data with maximum accuracy that is possible.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ACCURACY_HIGH                    = 3
} sensor_accuracy_t;

/**
 * @brief Orientation of the device
 *
 * This enumeration defines the possible direction that the device is facing.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The front of the device, usually the screen, is pointed up.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_FACE_UP     = 0,

    /**
     * The front of the device is pointed up.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_TOP_UP      = 1,

    /**
     * The bottom of the device is pointed up.
      *
      * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_BOTTOM_UP   = 2,

    /**
     * The top of the device is pointed to the left.
      *
      * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_LEFT_UP     = 3,

    /**
     * The top of the device is pointed to right.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_RIGHT_UP    = 4,

    /**
     * The front of the device, usually a screen, is pointed down.
     *
     * @since BlackBerry 10.0.0
     */
    SENSOR_ORIENTATION_FACE_DOWN   = 5,
} sensor_orientation_t;

/**
 * @brief Start sending sensor events to BlackBerry Platform Services (BPS)
 *
 * The @c sensor_request_events() function starts to deliver sensor events to
 * the application using BPS.
 *
 * @param type The types of events to deliver. You can use the values that are
 *             defined in the @c #sensor_type_t enumeration to specify the
 *             sensor events to deliver.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_request_events(sensor_type_t type);

/**
 * @brief Stop sending sensor events to BlackBerry Platform Services (BPS)
 *
 * The @c sensor_stop_events() function stops sensor events from being delivered
 * to the application using BPS. You must make sure that you call this function
 * with the same parameters that you specified in @c sensor_request_events().
 * For example, if you called the @c
 * sensor_request_events(SENSOR_TYPE_MAGNETOMETER) function, you must make sure
 * to call the @c sensor_stop_events(SENSOR_TYPE_MAGNETOMETER) function instead
 * of specifying a different sensor type, such as @c SENSOR_TYPE_GYROSCOPE or @c
 * SENSOR_TYPE_TEMPERATURE.
 *
 * @param type The types of events to stop. You can use the values that are
 *             defined in the @c #sensor_type_t enumeration to specify the
 *             sensor events to stop.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_stop_events(sensor_type_t type);

/**
 * @brief Retrieve the unique domain ID for the sensor service
 *
 * The @c sensor_get_domain() function gets the unique domain ID for the sensor
 * service. Use this function in your application to test whether an event that
 * you retrieve using the @c bps_get_event() function is a sensor event, and
 * respond accordingly.
 *
 * @return The domain ID for the sensor service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_get_domain(void);

/**
 * @brief Indicate whether a sensor type is supported
 *
 * The @c sensor_is_supported() function indicates whether the specified sensor
 * type is supported on the device.
 *
 * @param type The sensor to check support for.
 *
 * @return @c true if the sensor type is supported on the device, @c false if
 *         the sensor type is not supported on the device.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool sensor_is_supported(sensor_type_t type);

/**
 * @brief Enable or disable sensor calibration
 *
 * @deprecated This function is deprecated.
 *
 * The @c sensor_set_calibration() function enables or disables calibration for
 * the specified sensor. The accuracy of a sensor might degrade over time. By
 * enabling calibration, if sensor accuracy degrades by a significant amount,
 * the sensor service calibrates the sensor. This improves sensor accuracy.
 *
 * During normal operation of your application, you shouldn't need to call this
 * function, because your application can rely on background calibration.  You
 * should enable calibration only if your application requires higher quality
 * readings from a sensor. After the desired level of quality is reached, you
 * should disable calibration; calibration should not be left enabled for an
 * extended period of time.
 *
 * @param type The sensor to enable or disable calibration for.
 * @param enable_calibration If @c true calibration is enabled, if @c false
 *                           calibration is disabled.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_set_calibration(sensor_type_t type, bool enable_calibration) BPS_DEPRECATED;

/**
 * @brief Specify whether duplicate sensor events should be skipped
 *
 * The @c sensor_set_skip_duplicates() function enables or disables the skipping
 * of duplicate events that are received from the specified sensor.
 *
 * @param type The sensor that should skip duplicate events.
 * @param enable_skipdup If @c true the device should attempt to skip duplicate
 *                       events from the specified sensor, if @c false the
 *                       device should not skip duplicate events.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_set_skip_duplicates(sensor_type_t type, bool enable_skipdup);

/**
 * @brief Set a sensor's refresh rate
 *
 * The @c sensor_set_rate() function sets the rate at which the specified sensor
 * should provide updates. The device attempts to achieve the specified rate,
 * but this is not guaranteed; the sensor might provide updates more frequently
 * or less frequently than the specified rate. The rate that you specify here
 * corresponds roughly to the number of sensor events that are delivered to the
 * event queue for your application.
 *
 * @param type The sensor to set the refresh rate for.
 * @param rate The rate to set (in microseconds).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_set_rate(sensor_type_t type, unsigned int rate);

/**
 * @brief Specify whether the sensor should continue operation when the system
 * goes into standby
 *
 * The @c sensor_set_background() function when enabled allows the sensor to
 * continue operation even when the system goes into standby mode.
 *
 * If a sensor is set to stay active when the system is in standby mode, battery
 * life is reduced.
 *
 * @param type The sensor that should continue operation even in standby mode.
 * @param enable_background If @c true the sensor continues operation while in
 *                          standby.  If @c false, the sensor stops operation
 *                          while the system is in standby.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_set_background(sensor_type_t type, bool enable_background);

/**
 * @brief Report readings from a sensor in hardware-specific batch sizes
 *
 * When enabled and supported by the hardware, readings will be batched
 * together.  The readings are held in a hardware queue until a threshold is
 * reached.  Once the threshold is reached, all queued sensor events will be
 * delivered at once.
 *
 * @param type The sensor that should batch readings if supported.
 * @param enable_batching If @c true and if it is supported by the hardware,
 *                        sensor readings will be batched.  Once a hardware
 *                        specific threshold is reached, readings will be
 *                        reported to the app.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int sensor_set_batching(sensor_type_t type, bool enable_batching);

/**
 * @brief Coordinates from a sensor event will be remapped based on the angle
 *
 * The x, y, and z values are based off of an angle of 0.  After calling this
 * function, getting axis values from events will automatically be corrected
 * based on the provided angle.
 *
 * Will remap coordinates on the following calls:
 * - @c sensor_event_get_xyz()
 * - @c sensor_event_get_apr()
 * - @c sensor_event_get_rotation_matrix()
 *
 * The initial angle of the application is provided in the "ORIENTATION"
 * environment variable.  That value can be converted to an int and passed into
 * this function.
 *
 * On a rotation event, the new angle will be provided in the event, it can be
 * extracted and passed into this function.
 *
 * @param angle The angle (in degrees) to base the remapping off of.  Must be a
 *              value of 0, 90, 180, or 270.  A value of 0 effectively disables
 *              remapping.
 *
 * @return @c BPS_SUCCESS upon success. Otherwise, @c BPS_FAILURE with the @c
 * errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_remap_coordinates(int angle);

/**
 * @brief Retrieve the x, y, and z data values from a sensor event
 *
 * The @c sensor_event_get_xyz() function gets the data values of the x-axis,
 * y-axis, and z-axis from the specified sensor event. The sensor event that you
 * pass to this function must be @c SENSOR_ACCELEROMETER_READING, @c
 * SENSOR_MAGNETOMETER_READING, @c SENSOR_GYROSCOPE_READING, @c
 * SENSOR_LINEAR_ACCEL_READING, or @c SENSOR_GRAVITY_READING, because these are
 * the only sensor events with x, y, and z data components.
 *
 * The units that are used for x, y, and z depend on which sensor event was
 * passed in. For accelerometer and linear accelerometer events, the values are
 * in G forces. For magnetometer events, the values indicate the strength of the
 * magnetic field along a particular vector, in microteslas. For gyroscope
 * events, the values are in radians per second. For gravity events, the values
 * are in meters per seconds squared (m/s^2).
 *
 * @param event The sensor event to get the x, y, and z data values from.
 * @param x The pointer to the x-axis value.
 * @param y The pointer to the y-axis value.
 * @param z The pointer to the z-axis value.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_xyz(bps_event_t *event, float *x, float *y, float *z);

/**
 * @brief Retrieve the azimuth, pitch, and roll data values from a sensor event
 *
 * The @c sensor_event_get_apr() function gets the azimuth, pitch, and roll data
 * values from the specified sensor event. The sensor event that you pass to
 * this function must be @c SENSOR_AZIMUTH_PITCH_ROLL_READING.
 *
 * Azimuth refers to the angle between magnetic north (not true north) and the
 * y-axis, around the z-axis. If you require the azimuth relative to true north,
 * you must apply magnetic declination manually. Pitch refers to the rotation
 * around the x-axis. Positive values indicate that the z-axis is moving towards
 * the y-axis. Roll refers to the rotation around the y-axis. Positive values
 * indicate that the x-axis is moving toward the z-axis.
 *
 * @param event The sensor event to get the azimuth, pitch, and roll data values
 *              from.
 * @param azimuth The device's azimuth value (in degrees). Valid values can
 *                range from 0 to 359 degrees.
 * @param pitch The device's pitch value (in degrees). Valid values can range
 *              from -180 to 180 degrees.
 * @param roll The device's roll value (in degrees). Valid values can range from
 *             -90 and 90 degrees.
 * @return @c BPS_SUCCESS when the function completes successfully, @c
 *         BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_apr(bps_event_t *event, float *azimuth, float *pitch, float *roll);

/**
 * @brief Returns the device orientation in degrees: 0, 90, 180, or 270
 *
 * Fetch the device orientation angle from a @c SENSOR_ORIENTATION_READING
 * event. Possible results are 0, 90, 180, or 270 degrees.
 *
 * This is the device orientation angle relative to gravity, which may not match
 * the screen orientation. For example, the device may physically be in
 * landscape mode, but the application may be restricted to portrait mode. In
 * such a case, this function would return an orientation angle that implies
 * landscape mode, but the application's screen orientation would be in portrait
 * mode.
 *
 * @param event The @c SENSOR_ORIENTATION_READING event.
 *
 * @return 0, 90, 180, or 270 when the function completes successfully, -1 with
 *         the @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_orientation_angle(bps_event_t *event);

/**
 * @brief Returns the direction the device is facing
 *
 * Retrieves the @c #sensor_orientation_t that the device is currently facing
 * from a @c SENSOR_ORIENTATION_READING event.
 *
 * @param event The @c SENSOR_ORIENTATION_READING event.
 *
 * @return The direction the device is facing, @c -1 with the errno value set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_orientation_face(bps_event_t *event);

/**
 * @brief Retrieve the altitude from a @c SENSOR_ALTIMETER_READING event
 *
 * The @c sensor_event_get_altitude() function gets the altitude from the
 * specified @c SENSOR_ALTIMETER_READING event.
 *
 * @param event The @c SENSOR_ALTIMETER_READING event to get the altitude from.
 *
 * @return The altitude (in meters).  NaN in the event of an error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_event_get_altitude(bps_event_t *event);

/**
 * @brief Retrieve the temperature from a @c SENSOR_TEMPERATURE_READING event
 *
 * The @c #sensor_event_get_temperature() function gets the temperature from the
 * specified @c SENSOR_TEMPERATURE_READING event.
 *
 * @param event The @c SENSOR_TEMPERATURE_READING event to get the temperature
 *              from.
 *
 * @return The temperature (in degrees Celsius).  NaN in the event of an error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_event_get_temperature(bps_event_t *event);

/**
 * @brief Retrieve the proximity from a @c SENSOR_PROXIMITY_READING event
 *
 * The @c sensor_event_get_proximity() function gets the proximity from the
 * specified @c SENSOR_PROXIMITY_READING event. The proximity indicates whether
 * the closest object to the device is near or far from the device.
 *
 * @param event The @c SENSOR_PROXIMITY_READING event to get the proximity from.
 *
 * @return The proximity as a boolean value of 0.0f (close) and 1.0f (far) when
 *         the function completes successfully, @c NaN with the @c errno value
 *         set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_event_get_proximity(bps_event_t *event);

/**
 * @brief Retrieve the normalized proximity from a @c SENSOR_PROXIMITY_READING
 *        event
 *
 * The @c sensor_event_get_proximity_normalized() function gets the proximity
 * from the specified @c SENSOR_PROXIMITY_READING event and normalizes it to a
 * value between 0.0f and 1.0f. Where 0.0f is close and 1.0f is far.  The
 * normalized proximity is a unitless value.
 *
 * Note that while the proximity from an event is normalized to a value in the
 * range of 0.0f to 1.0f, it is common that the full range of values is not
 * seen. This is because it is difficult for many proximity sensors to register
 * values at the top end of their range, and the normalized value is calculated
 * against the full range of the sensor. For this reason, it is important to
 * consider the relative change in proximity, rather than the absolute proximity
 * values.
 *
 * @param event The @c SENSOR_PROXIMITY_READING event to get the normalized
 *              proximity from.
 *
 * @return The proximity as a unitless measurement between 0.0f (close) and 1.0f
 *         (far) when the function completes successfully, @c NaN with the @c
 *         errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_event_get_proximity_normalized(bps_event_t *event);

/**
 * @brief Retrieve the illuminance from a @c SENSOR_LIGHT_READING event
 *
 * The @c sensor_event_get_illuminance() function gets the illuminance from the
 * specified @c SENSOR_LIGHT_READING event.
 *
 * @param event The @c SENSOR_LIGHT_READING event to get the illuminance from.
 *
 * @return The illuminance (in lux) when the function completes successfully, @c
 *         NaN otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_event_get_illuminance(bps_event_t *event);

/**
 * @brief Structure for a rotation matrix
 *
 * The @c #sensor_rotation_matrix_t structure defines a rotation matrix that
 * represents the current rotation of the device. This structure is used with
 * the @c sensor_event_get_rotation_matrix() function.
 *
 * The rotational matrix computes the inclination matrix I as well as the
 * rotation matrix R transforming a vector from the device coordinate system to
 * the world's coordinate system which is defined as a direct orthonormal basis,
 * where X is defined as the vector product Y.Z (It is tangential to the ground
 * at the device's current location and roughly points east.)
 *
 * @since BlackBerry 10.0.0
 */
typedef struct {
    /**
     * The rotation matrix.
     *
     * @since BlackBerry 10.0.0
     */
    float matrix[3*3];
} sensor_rotation_matrix_t;

/**
 * @brief Retrieve a rotation matrix from a @c SENSOR_ROTATION_MATRIX_READING
 *        event
 *
 * The @c sensor_event_get_rotation_matrix() function fills in a @c
 * #sensor_rotation_matrix_t structure with a rotation matrix that is created
 * using the values from the specified @c SENSOR_ROTATION_MATRIX_READING event.
 *
 * @param event The @c SENSOR_ROTATION_MATRIX_READING event to get the rotation
 *              matrix from.
 * @param matrix The @c #sensor_rotation_matrix_t structure to
 *               fill in.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_rotation_matrix(bps_event_t *event, sensor_rotation_matrix_t *matrix);

/**
 * @brief Structure for a rotation vector
 *
 * @deprecated The function that uses this structure is deprecated.  Instead,
 *             use the @c sensor_event_get_rotation_matrix() function.
 *
 * The @c #sensor_rotation_vector_t structure defines a rotation vector that
 * represents the current rotation of the device. This structure is used with
 * the @c sensor_event_get_rotation_vector() function.
 *
 * See sensor_event_get_rotation_matrix().
 *
 * @since BlackBerry 10.0.0
 */
typedef struct {
    /**
     * The rotation vector.
     *
     * @since BlackBerry 10.0.0
     */
    float vector[4];
} sensor_rotation_vector_t;

/**
 * @brief Get a rotation vector from a @c SENSOR_ROTATION_VECTOR_READING event
 *
 * @deprecated This function is deprecated, use rotation matrix instead.
 *
 * The @c sensor_event_get_rotation_vector() function fills in a @c
 * #sensor_rotation_vector_t structure with a rotation vector that is created
 * using the values from the specified @c SENSOR_ROTATION_VECTOR_READING event.
 *
 * @param event The @c SENSOR_ROTATION_VECTOR_READING event to get the rotation
 *              vector from.
 * @param vector The @c #sensor_rotation_vector_t structure to
 *               fill in.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @sa sensor_event_get_rotation_matrix
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_rotation_vector(bps_event_t *event, sensor_rotation_vector_t *vector) BPS_DEPRECATED;

/**
 * @brief Retrieve whether a face was detected close to our touching the screen
 *
 * @deprecated This function is deprecated, use the proximity sensor.
 *
 * The @c sensor_event_get_face_detect() function returns 1 when an object is
 * detected to be close to or touching the screen. Otherwise it returns 0.  The
 * value is retrieved from a @c SENSOR_FACE_DETECT_READING event.
 *
 * @param event The @c SENSOR_FACE_DETECT_READING event to get the value from.
 *
 * @return A value of @c 1 when an object is detected to be close to or touching
 *         the screen on the device, @c 0 if no object is close to or touching
 *         the screen, and @c -1 with @c errno value set if an an error
 *         occurred.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_event_get_face_detect(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief Reserved for future use
 *
 * Retrieve the flags of a sensor reading.
 *
 * The @c sensor_event_get_flags() function gets the flags of the specified
 * sensor event. The flags are returned with each sensor reading event.
 *
 * @param event The sensor event to get the flags of.
 *
 * @return The flags of the sensor reading.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API uint64_t sensor_event_get_flags(bps_event_t *event);

/**
 * @brief Retrieve the accuracy of a sensor reading
 *
 * The @c sensor_event_get_accuracy() function gets the accuracy of the
 * specified sensor event. The sensor's accuracy is returned with each sensor
 * reading event. The #sensor_accuracy_t structure defines the possible levels
 * of accuracy of sensor readings.
 *
 * @param event The sensor event to get the accuracy of.
 *
 * @return The accuracy of the sensor reading.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API sensor_accuracy_t sensor_event_get_accuracy(bps_event_t *event);

/**
 * @brief Retrieve the timestamp of a sensor reading
 *
 * The @c sensor_event_get_timestamp() function gets the timestamp of the
 * specified sensor event. The sensor event's time stamp is returned with each
 * sensor reading.  The time (in nanoseconds) is a reference from the monotonic
 * clock from the last the device started up.
 *
 * @param event The sensor event to get the timestamp of.
 *
 * @return The timestamp of the sensor reading.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API uint64_t sensor_event_get_timestamp(bps_event_t *event);

/**
 * @brief Retrieve whether the device is holstered
 *
 * The @c sensor_event_is_holstered() function sets @c is_holstered to true when
 * the device is holstered.  When the device is removed from the holster @c
 * is_holstered will be set to false.  The value is retrieved from a @c
 * SENSOR_HOLSTER_READING event.
 *
 * @param event The @c SENSOR_HOLSTER_READING event to get the value from.
 * @param is_holstered This is set to true if the device is holstered, false
 *                     otherwise.
 *
 * @return @c BPS_FAILURE will be returned if the event passed in is not a @c
 *         SENSOR_HOLSTER_READING, or if @c is_holstered is @c NULL.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int sensor_event_is_holstered(bps_event_t *event, bool *is_holstered);

/**
 * @brief Retrieve the compass heading
 *
 * The @c sensor_event_get_heading() function returns the compass heading
 * relative to magnetic north, from 0 to 359 degrees.  The value is retrieved
 * from a @c SENSOR_COMPASS_READING event.
 *
 * @param event The @c SENSOR_COMPASS_READING event to get the value from.
 *
 * @return On success, a compass heading of 0 to 359 degrees relative to
 *         magnetic north.  If the event passed in is not a @c
 *         SENSOR_COMPASS_EVENT, @c NaN will be returned with @c errno set
 *         appropriately.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API float sensor_event_get_heading(bps_event_t *event);

/**
 * @brief Determine whether the compass heading is flipped
 *
 * The @c sensor_event_is_heading_flipped() function sets @c is_flipped to @c
 * true if the device is face down.  When the device is face down, turning the
 * device clockwise will report the same heading as turning it counter-clockwise
 * if the device was face up.  @c is_flipped is set to @c false if the device is
 * face up and the heading is not flipped.  The value is retrieved from a @c
 * SENSOR_COMPASS_READING event.
 *
 * @param event The @c SENSOR_COMPASS_READING event to get the value from.
 * @param is_flipped This is set to true if the device is face down, false
 *                   otherwise.
 *
 * @return On success, @c BPS_SUCCESS is returned and @c is_flipped is set.  If
 * the event passed in is not a @c SENSOR_COMPASS_READING event or if @c
 * is_flipped is @c NULL, @c BPS_FAILURE will be returned with @c errno set
 * appropriately.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int sensor_event_is_heading_flipped(bps_event_t *event, bool *is_flipped);

/**
 * @brief Retrieve the air pressure from a @c SENSOR_PRESSURE_READING event
 *
 * The @c sensor_event_get_pressure() function gets the air pressure from the
 * specified @c SENSOR_PRESSURE_READING event.
 *
 * @param event The @c SENSOR_PRESSURE_READING event to get the air pressure
 *              from.
 *
 * @return The pressure (in pascals).  NaN in the event of an error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API float sensor_event_get_pressure(bps_event_t *event);

/**
 * @brief Structure to represent sensor information
 *
 * The @c #sensor_info_t structure represents information about a particular
 * type of sensor. This structure is used with the various @c sensor_info_*
 * functions to obtain sensor information that includes:
 * - resolution
 * - the minimum and maximum range
 * - the minimum, maximum, and default delays (in microseconds (usec))
 * - the power used
 *
 * @since BlackBerry 10.0.0
 */
typedef struct sensor_info_t sensor_info_t;

/**
 * @brief Retrieve information for a sensor
 *
 * The @c sensor_info() function allocates sensor information data. It is the
 * caller's responsibility to call @c sensor_info_destroy() once they are
 * finished with the sensor information structure that is allocated by this
 * function.
 *
 * @param type The type of sensor to get information for (for example, @c
 *             SENSOR_TYPE_ACCELEROMETER, @c SENSOR_TYPE_MAGNETOMETER, and so
 *             on).
 * @param info The @c #sensor_info_t structure to populate with the sensor
 *             information.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_info(sensor_type_t type, sensor_info_t **info);

/**
 * @brief Retrieve the resolution of a sensor
 *
 * The @c sensor_info_get_resolution() function gets the resolution of the
 * sensor that is represented by the specified sensor information. The
 * resolution represents the sensitivity of a sensor.
 *
 * @param info The information for the sensor to get the resolution of.
 *
 * @return The sensor's resolution.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_info_get_resolution(sensor_info_t *info);

/**
 * @brief Retrieve the minimum range of a sensor
 *
 * The @c sensor_info_get_range_minimum() function gets the minimum range of the
 * sensor that is represented by the specified sensor information.
 *
 * @param info The information for the sensor to get the minimum range from.
 *
 * @return The sensor's minimum range.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_info_get_range_minimum(sensor_info_t *info);

/**
 * @brief Retrieve the maximum range of a sensor
 *
 * The @c sensor_info_get_range_maximum() function gets the maximum range of the
 * sensor that is represented by the specified sensor information.
 *
 * @param info The information for the sensor to get the maximum range from.
 *
 * @return The sensor's maximum range.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_info_get_range_maximum(sensor_info_t *info);

/**
 * @brief Retrieve the minimum delay of a sensor
 *
 * The @c sensor_info_get_delay_minimum() function gets the minimum delay of the
 * sensor that is represented by the specified sensor information. Delay is the
 * time between sensor events. A delay of 1000000 usec (or 1 second), indicates
 * that an event is received every 1 second.
 *
 * @param info The information value for the sensor to get the minimum delay
 *             from.
 *
 * @return The sensor's minimum delay in microseconds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned int sensor_info_get_delay_minimum(sensor_info_t *info);

/**
 * @brief Deprecated
 *
 * @deprecated Use the @c sensor_info_get_delay_minimum() function.
 *
 * @param info The information value for the sensor to get the minimum delay
 *             from.
 *
 * @return The sensor's minimum delay in microseconds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned int sensor_info_get_delay_mininum(sensor_info_t *info) BPS_DEPRECATED;

/**
 * @brief Retrieve the maximum delay of a sensor
 *
 * The @c sensor_info_get_delay_maximum() function gets the maximum delay of the
 * sensor that is represented by the specified sensor information. Delay is the
 * time between sensor events. A delay of 1000000 usec (or 1 second), indicates
 * that an event is received every 1 second.
 *
 * @param info The information for the sensor to get the maximum delay from.
 *
 * @return The sensor's maximum delay in microseconds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned int sensor_info_get_delay_maximum(sensor_info_t *info);

/**
 * @brief Retrieve the default delay of a sensor
 *
 * The @c sensor_info_get_delay_default() function gets the default delay of the
 * sensor that is represented by the specified sensor information. Delay is the
 * time between sensor events. A delay of 1000000 usec (or 1 second), indicates
 * that an event is received every 1 second.
 *
 * @param info The information for the sensor to get the default delay from.
 *
 * @return The sensor's default delay in microseconds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned int sensor_info_get_delay_default(sensor_info_t *info);

/**
 * @brief Reserved for future use
 *
 * Retrieve the power that is consumed by sensor.
 *
 * The @c sensor_info_get_power() function gets the power of the sensor that is
 * represented by the specified sensor information.
 *
 * @param info The information for the sensor to retrieve power that is consumed
 *             from the device.
 *
 * @return The power consumed by the sensor.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API float sensor_info_get_power(sensor_info_t *info);

/**
 * @brief Free the resources that were allocated for a sensor information
 *        structure
 *
 * The @c sensor_info_destroy() function releases the resources that were
 * allocated for the specified @c #sensor_info_t structure.
 *
 * @param info A pointer to the @c #sensor_info_t structure to free.
 *
 * @return @c BPS_SUCCESS upon successfully completing the function,
 *         @c BPS_FAILURE with @c errno value set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int sensor_info_destroy(sensor_info_t *info);

__END_DECLS

#endif // include guard
