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

 /**
 * @file rotate.h
 *
 * @brief Definition of the rotate gesture
 *
 * The rotate.h header file provides data type definitions and functions
 * for the rotate gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */
 
#include "gestures/types.h"

#ifndef ROTATE_H_
#define ROTATE_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Rotate gesture parameters
 *
 * The stucture @c rotate_params_t is provided for consistency with other gesture
 * implementations. Although carries no information, it cannot be empty because
 * common functions rely on its existence. 
 */
typedef struct {
	int none;
} rotate_params_t;

/** @brief The rotate gesture data type
 *
 * The structure @c gesture_rotate_t carries data about the rotate gesture.
 */
typedef struct {
	gesture_base_t base;             /**< The gesture base data structure. */
	rotate_params_t params;          /**< The swipe parameters. */
	gesture_coords_t coords[2];      /**< The coordinates of the touch events for the two fingers. */
	gesture_coords_t centroid;       /**< The coordintes of the midpoint between the two touches. */
	gesture_coords_t last_centroid;  /**< The coordintes of the midpoint between the previous two touches. */
	int angle;                       /**< The angle of the current two touches relative to the x axis. */
	int last_angle;                  /**< The previous angle. */
} gesture_rotate_t;

/**
 * @brief Allocate and initialize the rotate gesture structure
 *
 * The function @c rotate_gesture_alloc() allocates a new rotate gesture data structure
 * and initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params A pointer to the rotate gesture parameters.
 * @param callback The function to invoke when the rotate gesture changes state.
 * @param set A pointer to the gesture set to add this rotate gesture to.
 *
 * @return A pointer to an initialized rotate gesture.
 */
gesture_rotate_t* rotate_gesture_alloc(rotate_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the rotate parameters
 *
 * The function @c rotate_gesture_default_params() initializes the rotate
 * parameters to default values.
 *
 * @param params A pointer to the rotate gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void rotate_gesture_default_params(rotate_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* ROTATE_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
