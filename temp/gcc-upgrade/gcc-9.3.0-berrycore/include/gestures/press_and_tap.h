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
 * @file press_and_tap.h
 *
 * @brief Definition of the press and tap gesture
 *
 * The press_and_tap.h header file provides data type definitions and functions
 * for the press and tap gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */
 
 
#ifndef PRESS_AND_TAP_H_
#define PRESS_AND_TAP_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Press and touch gesture parameters
 *
 * The stucture @c pt_params_t represents the parameters for the press and tap gesture.
 */
typedef struct {
	unsigned max_tap_time;           /**< The maximum time the second finger can be held down */
	unsigned min_press_tap_interval; /**< The minimum time between the pressing finger
	                                      touching down and the tapping finger touching down */
	unsigned max_press_tap_interval; /**< The maximum time between the pressing finger
	                                      touching down and the tapping finger touching down */
	unsigned max_displacement;       /**< Maximum distance either finger can move before
	                                      the gesture fails. */
} pt_params_t;

/** @brief The press and tap gesture data type
 *
 * The structure @c gesture_pt_t carries data about the press and tap gesture.
 */
typedef struct {
	gesture_base_t base;                 /**< The gesture base data structure. */ 
	pt_params_t params;                  /**< The swipe parameters. */

	/* 0: Press, 1: Tap */
	gesture_coords_t initial_coords[2];  /**< Index of the two sets of coordinates; 0 = press; 1 = tap. */
	gesture_coords_t coords[2];          /**< The coordinates of the press and the tap */
} gesture_pt_t;

/**
 * @brief Allocate and initialize the press and tap gesture structure
 *
 * The function @c pt_gesture_alloc() allocates a new press and tap gesture data structure,
 * initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params The press and tap gesture parameters.
 * @param callback The function to invoke when the press and gesture changes state.
 * @param set The gesture set to add this press and tap gesture to.
 *
 * @return An initialized press and tap gesture.
 */
gesture_pt_t* pt_gesture_alloc(pt_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the press and tap parameters
 *
 * The function @c pt_gesture_default_params() initializes the press and tap
 * parameters to default values.
 *
 * @param params A pointer to the press and tap gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void pt_gesture_default_params(pt_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* PRESS_AND_TAP_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
