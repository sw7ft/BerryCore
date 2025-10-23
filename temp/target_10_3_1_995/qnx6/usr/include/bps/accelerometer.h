/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file accelerometer.h
 *
 * The BlackBerry Platform Services accelerometer service.
 *
 * The accelerometer service allows an application to read the device's
 * accelerometer sensor (if present).
 *
 * @deprecated This service is deprecated and is only included for backwards
 * compatibility.  The new Sensor API (bps/sensor.h) which includes the
 * accelerometer should be used for new projects.
 *
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_ACCELEROMETER_H_INCLUDED
#define _BPS_ACCELEROMETER_H_INCLUDED

#include <math.h>
#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * The rates at which the accelerometer values will be updated from hardware.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    FREQ_40_HZ      = 25,
    FREQ_20_HZ      = 50,
    FREQ_10_HZ      = 100,
    FREQ_5_HZ       = 200,
    FREQ_3PT3_HZ    = 300,
    FREQ_2PT5_HZ    = 400,
    FREQ_2_HZ       = 500,
    FREQ_1PT6_HZ    = 600,
    FREQ_1PT2_HZ    = 800,
    FREQ_1_HZ       = 1000
} accelerometer_frequency_t;

/**
 * Indicates whether the device has an accelerometer.
 *
 * @deprecated Use the Sensor API (bps/sensor.h).
 *
 * @return @c true if the device has an accelerometer, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool accelerometer_is_supported() BPS_DEPRECATED;

/**
 * Sets the update rate of the accelerometer.
 *
 * @deprecated Use the Sensor API (bps/sensor.h).
 *
 * @param freq The update rate to set.
 *
 * @return @c BPS_SUCCESS or @c BPS_FAILURE
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int accelerometer_set_update_frequency(accelerometer_frequency_t freq) BPS_DEPRECATED;

/**
 * Gets the G force for each axis.
 *
 * @deprecated Use the Sensor API (bps/sensor.h).
 *
 * @param x The G force for the x axis.
 * @param y The G force for the y axis.
 * @param z The G force for the z axis.
 *
 * @return @c BPS_SUCCESS or @c BPS_FAILURE
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int accelerometer_read_forces(double *x, double *y, double *z) BPS_DEPRECATED;

/**
 * Calculates roll based on force values.
 *
 * @deprecated Use the Sensor API (bps/sensor.h).
 *
 * This is a convenience macro. Requires libm.
 *
 * @param x The force along the x axis.
 * @param y The force along the y axis.
 * @param z The force along the z axis.
 *
 * @return The roll (in degrees).
 *
 * @since BlackBerry 10.0.0
 */
#define ACCELEROMETER_CALCULATE_ROLL(x, y, z) \
    (atan(x / sqrt(y * y + z * z)) * 180 * M_1_PI)

/**
 * Calculates pitch based on force values.
 *
 * @deprecated Use the Sensor API (bps/sensor.h).
 *
 * This is a convenience macro. Requires libm.
 *
 * @param x The force along the x axis.
 * @param y The force along the y axis.
 * @param z The force along the z axis.
 *
 * @return The pitch (in degrees).
 *
 * @since BlackBerry 10.0.0
 */
#define ACCELEROMETER_CALCULATE_PITCH(x, y, z) \
    (atan(y / sqrt(x * x + z * z)) * 180 * M_1_PI)

__END_DECLS

#endif // include guard
