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
 * @file double_tap.h
 *
 * @brief Definition of the double tap gesture
 *
 * The double_tap.h header file provides data type definitions and functions
 * for the double tap gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */
 
#include "gestures/types.h"

#ifndef DOUBLE_TAP_H_
#define DOUBLE_TAP_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Double tap gesture parameters
 *
 * The stucture @c double_tap_params_t represents the parameters for the double tap gesture.
 */
typedef struct {
	unsigned max_displacement; /**< The maximum distance the finger can move before
	                                the double tap gesture fails. */
	unsigned max_hold_ms;      /**< The maximum time the finger can remain touching
	                                the screen before the double tap gesture fails. */
	unsigned max_delay_ms;     /**< The time between the first release and the second touch. */
} double_tap_params_t;

/** @brief States for the double tap gesture
 *
 * The enumeration @c double_tap_state_e defines additional states the double
 * tap gesture can transition between.
 */
typedef enum {
	DT_STATE_INIT = 0,
	DT_STATE_FIRST_TOUCH,
	DT_STATE_FIRST_RELEASE,
	DT_STATE_SECOND_TOUCH,
	DT_STATE_SECOND_RELEASE
} double_tap_state_e;

/** @brief The double tap gesture data type
 *
 * The structure @c gesture_double_tap_t carries data about the double tap gesture.
 */
typedef struct {
	gesture_base_t base;             /**< The gesture base data structure. */
	double_tap_params_t params;      /**< The double tap parameters. */
	gesture_coords_t first_touch;    /**< The coordinates of the first touch. */
	gesture_coords_t first_release;  /**< The coordinates of the first release. */
	gesture_coords_t second_touch;   /**< The coordinates of the second touch. */
	gesture_coords_t second_release; /**< The coordinates of the second release. */
	double_tap_state_e dt_state;     /**< The intermediate state of the double tap. */
	int fail_timer;                  /**< The ID of the timer for this gesture. */
} gesture_double_tap_t;

/**
 * @brief Allocate and initialize the double tap gesture structure
 *
 * The function @c double_tap_gesture_alloc() allocates a new double tap gesture data structure,
 * initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params The double tap gesture parameters.
 * @param callback The function to invoke when the double tap gesture changes state.
 * @param set The gesture set to add this double tap gesture to.
 *
 * @return An initialized double tap gesture.
 */
gesture_double_tap_t* double_tap_gesture_alloc(double_tap_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the double tap parameters
 *
 * The function @c double_tap_gesture_default_params() initializes the
 * double tap parameters to default values.
 *
 * @param params The double tap gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void double_tap_gesture_default_params(double_tap_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* DOUBLE_TAP_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
