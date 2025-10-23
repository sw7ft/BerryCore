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
 * @file swipe.h
 *
 * @brief Definition of the swipe gesture
 *
 * The swipe.h header file provides data type definitions and functions
 * for the swipe gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */
 
#include "gestures/types.h"

#ifndef GESTURES_SWIPE_H_
#define GESTURES_SWIPE_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Swipe gesture parameters
 *
 * The stucture @c swipe_params_t represents the parameters for the swipe gesture.
 */
typedef struct {
	unsigned directions;         /**< Bitmask of the directions in which the
	                                  swipe can occur */
	unsigned off_axis_tolerance; /**< The number of touch units the swipe can
	                                  occur off axis with the direction. */
	unsigned min_distance;       /**< The minimum distance traveled in the 
	                                  touch direction for the gesture to be 
	                                  considered a swipe. */
	unsigned min_velocity;       /**< The minimum velocity between any two
	                                  points in the swipe. */
} swipe_params_t;


/** @brief The swipe gesture data type
 *
 * The structure @c gesture_swipe_t carries data about the swipe gesture.
 */ 
typedef struct {
	gesture_base_t base;             /**< The gesture base data structure. */ 
	swipe_params_t params;           /**< The swipe parameters. */
	gesture_coords_t initial_coords; /**< The coordinates of the first touch. */
	gesture_coords_t coords;         /**< The coordinates of an intermediate 
	                                      point in the swipe. */
	gesture_coords_t last_coords;    /**< The coordinates of the point where 
	                                      the finger was lifted from the screen. */
	int moving;                      /**< Indicates whether the last event was a move. */
	
	int direction;                   /**< The direction of the swipe. */
} gesture_swipe_t;

/**
 * @brief Allocate and initialize the swipe gesture structure
 *
 * The function @c swipe_gesture_alloc() allocates a new swipe gesture data structure
 * and initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params The swipe gesture parameters.
 * @param callback The function to invoke when the swipe gesture changes state.
 * @param set The gesture set to add this swipe gesture to.
 *
 * @return An initialized swipe gesture.
 */
gesture_swipe_t* swipe_gesture_alloc(swipe_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the swipe parameters
 *
 * The function @c swipe_gesture_default_params() initializes the swipe
 * parameters to default values.
 *
 * @param params The swipe gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void swipe_gesture_default_params(swipe_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* GESTURES_SWIPE_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
