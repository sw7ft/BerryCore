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
 * @file triple_tap.h
 *
 * @brief Definition of the triple tap gesture
 *
 * The triple_tap.h header file provides data type definitions and functions
 * for the triple tap gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */ 
 
 
#include "gestures/types.h"

#ifndef TRIPLE_TAP_H_
#define TRIPLE_TAP_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Triple tap gesture parameters
 *
 * The stucture @c triple_tap_params_t represents the parameters for the triple
 * tap gesture.
 */
typedef struct {
	unsigned max_displacement; /**< Maximum distance the finger can move before
	                                the triple tap gesture fails. */
	unsigned max_hold_ms;      /**< Maximum time the finger can remain touching
	                                the screen before the tap gesture fails. */
	unsigned max_delay_ms;     /**< The maximum time between release and touch. */
} triple_tap_params_t;

/** @brief States for the triple tap gesture
 *
 * The enumeration @c triple_tap_state_e defines additional states the triple
 * tap gesture can transition between.
 */
typedef enum {
	TT_STATE_INIT = 0,
	TT_STATE_FIRST_TOUCH,
	TT_STATE_FIRST_RELEASE,
	TT_STATE_SECOND_TOUCH,
	TT_STATE_SECOND_RELEASE,
	TT_STATE_THIRD_TOUCH,
	TT_STATE_THIRD_RELEASE
} triple_tap_state_e;

/** @brief The triple tap gesture data type
 *
 * The structure @c gesture_triple_tap_t carries data about the triple tap gesture.
 */
typedef struct {
	gesture_base_t base;             /**< The gesture base data structure. */
	triple_tap_params_t params;      /**< The triple tep parameters. */
	gesture_coords_t first_touch;    /**< The coordinates of the first touch event. */
	gesture_coords_t first_release;  /**< The coordinates of the first release event. */
	gesture_coords_t second_touch;   /**< The coordinates of the second touch event. */
	gesture_coords_t second_release; /**< The coordinates of the second release event. */
	gesture_coords_t third_touch;    /**< The coordinates of the third touch event. */
	gesture_coords_t third_release;  /**< The coordinates of the third release event. */
	triple_tap_state_e tt_state;     /**< The intermediate state of the triple tap. */
	int fail_timer;                  /**< The ID of the timer for this gesture. */
} gesture_triple_tap_t;

/**
 * @brief Allocate and initialize the triple tap gesture structure
 *
 * The function @c triple_tap_gesture_alloc() allocates a new triple tap gesture data structure,
 * initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params   A ponter to the triple tap gesture parameters.
 * @param callback The function to invoke when the triple tap gesture changes state.
 * @param set      A pointer to the gesture set to add this tap gesture to.
 *
 * @return A pointer to an initialized triple tap gesture.
 */
gesture_triple_tap_t* triple_tap_gesture_alloc(triple_tap_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the triple tap parameters
 *
 * The function @c triple_tap_gesture_default_params() initializes the
 * triple tap parameters to default values.
 *
 * @param params A pointer to the triple tap gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void triple_tap_gesture_default_params(triple_tap_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* TRIPLE_TAP_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
