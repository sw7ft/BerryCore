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
 * @file two_finger_tap.h
 *
 * @brief Definition of the two finger tap gesture
 *
 * The two_finger_tap.h header file provides data type definitions and functions
 * for the two finger tap gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */
 
#ifndef TWO_FINGER_TAP_H_
#define TWO_FINGER_TAP_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Two-finger tap gesture parameters
 *
 * The stucture @c tft_params_t represents the parameters for the two-finger tap gesture. 
 */
typedef struct {
	unsigned max_touch_interval;    /**< The maximum time that can elapse between when the
	                                     first and second fingers touch the screen. */
	unsigned max_release_interval;  /**< The maximum time that can elapse between when the
	                                     first and second fingers are released. */
	unsigned max_tap_time;          /**< The maximum time both fingers can stay down. */
	unsigned max_displacement;      /**< The maximum distance either finger can move before
	                                     the two-finger tap gesture fails. */
} tft_params_t;

/** @brief The two-finger tap gesture data type
 *
 * The structure @c gesture_tft_tap_t carries data about the two-finger tap gesture.
 */
typedef struct {
	gesture_base_t base;                 /**< The gesture base data structure. */
	tft_params_t params;                 /**< The two-finger tep parameters. */
	gesture_coords_t touch_coords[2];    /**< The coordinates of the first touch event. */
	gesture_coords_t release_coords[2];  /**< The coordinates of the second release event. */
	gesture_coords_t centroid;           /**< The midpoint between the two touches. */
	unsigned down_count;                 /**< The time in milliseconds that the fingers
	                                          remained touching. */
} gesture_tft_t;


/**
 * @brief Allocate and initialize the two-finger tap gesture structure
 *
 * The function @c tft_gesture_alloc() allocates a new two-finger tap gesture data structure,
 * initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params The two-finger tap gesture parameters.
 * @param callback The function to invoke when the two-finger tap gesture changes state.
 * @param set The gesture set to add this two-finger tap gesture to.
 *
 * @return An initialized two-finger tap gesture.
 */
gesture_tft_t* tft_gesture_alloc(tft_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the two-finger tap parameters
 *
 * The function @c tft_gesture_default_params() initializes the
 * two-finger tap parameters to default values.
 *
 * @param params The two-finger tap gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void tft_gesture_default_params(tft_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* TWO_FINGER_TAP_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
