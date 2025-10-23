/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/**
 * @file tap.h
 *
 * @brief Definition of the tap gesture
 *
 * The tap.h header file provides data type definitions and functions
 * for the tap gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */ 
 
#include "gestures/types.h"

#ifndef TAP_H_
#define TAP_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Tap gesture parameters
 *
 * The stucture @c tap_params_t represents the parameters for the tap gesture.
 */
typedef struct {
	unsigned max_displacement; /**< Maximum distance the finger can move before
	                                the tap gesture fails. */
	unsigned max_hold_ms;      /**< Maximum time the finger can remain touching
	                                the screen before the tap gesture fails. */
} tap_params_t;

/** @brief The tap gesture data type
 *
 * The structure @c gesture_tap_t carries data about the tap gesture.
 */
typedef struct {
	gesture_base_t base;           /**< The gesture base data structure. */ 
	tap_params_t params;           /**< The swipe parameters. */
	gesture_coords_t touch_coords; /**< The coordinates of the touch event. */
} gesture_tap_t;

/**
 * @brief Allocate and initialize the tap gesture structure
 *
 * The function @c tap_gesture_alloc() allocates a new tap gesture data structure
 * and initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params The tap gesture parameters.
 * @param callback The function to invoke when the tap gesture changes state.
 * @param set The gesture set to add this tap gesture to.
 *
 * @return An initialized tap gesture.
 */
gesture_tap_t* tap_gesture_alloc(tap_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the tap parameters
 *
 * The function @c tap_gesture_default_params() initializes the tap
 * parameters to default values.
 *
 * @param params The tap gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void tap_gesture_default_params(tap_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* TAP_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
