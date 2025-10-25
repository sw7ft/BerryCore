/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/*
 * EXPERIMENTAL. This class or interface has been added as part of a work in
 * progress. There is no guarantee that this API will work or that it will
 * remain the same.
 *
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <devctl.h>

#define ACCEL_DEV_NAME "/dev/accel"

/**
 * Accelerometer API return values
 */
typedef enum {
	ACCEL_INIT_ERROR = -1,
	ACCEL_SUCCESS = 0,
	ACCEL_FAIL = 1,
	ACCEL_SUPPORTED = 2,
	ACCEL_ERR_UNSUPPORTED = 3,
	ACCEL_ERR_BAD_SAMPLE = 4,
	ACCEL_ERR_CONFIG_VALUE_INVALID = 5,
	ACCEL_ERR_NUM = 6,
} _ACCEL_ERROR;
typedef unsigned char ACCEL_ERROR;

/**
 * Raw axis acceleration data
 *
 * Raw acceleration data on each axis of the device.
 * Units are in g's, where 1 g = 9.8 m/s^2;
 * the nominal acceleration due to gravity on Earth.
 */
typedef struct {
	double xAxis_rawdata;
	double yAxis_rawdata;
	double zAxis_rawdata;
} ACCEL_RAW_DATA;

/**
 * Orientation of the device
 */
typedef enum {
	ACCEL_ORIENTATION_LEFT_UP,
	ACCEL_ORIENTATION_RIGHT_UP,
	ACCEL_ORIENTATION_TOP_UP,
	ACCEL_ORIENTATION_BOTTOM_UP,
	ACCEL_ORIENTATION_FACE_UP,
	ACCEL_ORIENTATION_FACE_DOWN,
	ACCEL_ORIENTATION_UNKNOWN
} _ACCEL_ORIENTATION;
typedef unsigned char ACCEL_ORIENTATION;

/**
 * Update frequencies for use with the
 * ACCEL_SET_UPDATE_FREQ devctl call.
 */
#define UPDATE_FREQ_0025_MS     25
#define UPDATE_FREQ_0050_MS     50
#define UPDATE_FREQ_0100_MS     100
#define UPDATE_FREQ_0200_MS     200
#define UPDATE_FREQ_0300_MS     300
#define UPDATE_FREQ_0400_MS     400
#define UPDATE_FREQ_0500_MS     500
#define UPDATE_FREQ_0600_MS     600
#define UPDATE_FREQ_0700_MS     700
#define UPDATE_FREQ_0800_MS     800
#define UPDATE_FREQ_0900_MS     900
#define UPDATE_FREQ_1000_MS     1000

/**
 * Data returned by the ACCEL_IS_SUPPORTED
 * devctl call.
 */
#define ACCEL_FEATURE_SUPPORTED   1
#define ACCEL_FEATURE_UNSUPPORTED 0

/**
 * Transaction structure for use with devctl calls.
 */
typedef struct{
	unsigned int    response;
	float           data;
}AccelTransaction;

#define ACCEL_CMD_CODE      1

/**
 * ACCEL_SET_UPDATE_FREQ
 * Set Accelerometer Update Frequency.
 *
 * Example usage: devctl(fd, ACCEL_SET_UPDATE_FREQ, transaction, sizeof(AccelTransaction), NULL);
 *         where:
 *             fd = open handle to ACCEL_DEV_NAME
 *             transaction = AccelTransaction *transaction with allocated size
 *                           of sizeof(AccelTransaction)
 *             transaction->data = Frequency in milli-seconds (eg: UPDATE_FREQ_0100_MS)
 *         transaction after the call:
 *             transaction->data      N/A
 *             transaction->response  ACCEL_SUCCESS or ACCEL_FAIL
 */
#define ACCEL_SET_UPDATE_FREQ	__DIOT (_DCMD_MISC,  ACCEL_CMD_CODE + 0, AccelTransaction)

/**
 * ACCEL_GET_TEMPERATURE
 * Read temperature of the device (BMA150).
 *
 * Example usage: devctl(fd, ACCEL_GET_TEMPERATURE, transaction, sizeof(AccelTransaction), NULL);
 *         where:
 *             fd = open handle to ACCEL_DEV_NAME
 *             transaction = AccelTransaction *transaction with allocated size
 *                           of sizeof(AccelTransaction)
 *             transaction->data = N/A
 *         transaction after the call:
 *             transaction->data      Temperature data in C (temp range from -30 to +90)
 *             transaction->response  ACCEL_SUCCESS or ACCEL_FAIL
 */
#define ACCEL_GET_TEMPERATURE   __DIOF (_DCMD_MISC,  ACCEL_CMD_CODE + 1, AccelTransaction)

/**
 * ACCEL_IS_SUPPORTED
 * Returns ACCEL_FEATURE_SUPPORTED/ACCEL_FEATURE_UNSUPPORTED
 *
 * Example usage: devctl(fd, ACCEL_IS_SUPPORTED, transaction, sizeof(AccelTransaction), NULL);
 *         where:
 *            fd = open handle to ACCEL_DEV_NAME
 *            transaction = AccelTransaction *transaction with allocated size
 *                          of sizeof(AccelTransaction)
 *            transaction->data = N/A
 *         transaction after the call:
 *            transaction->data      ACCEL_FEATURE_SUPPORTED or ACCEL_FEATURE_UNSUPPORTED
 *            transaction->response  ACCEL_SUCESS
 */
#define ACCEL_IS_SUPPORTED   __DIOF (_DCMD_MISC,  ACCEL_CMD_CODE + 2, AccelTransaction)

#endif /* ACCELEROMETER_H_ */
