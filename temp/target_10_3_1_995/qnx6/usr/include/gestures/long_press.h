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
 * @file long_press.h
 *
 * @brief Definition of the long press gesture
 *
 * The long_press.h header file provides data type definitions and functions
 * for the long press gesture.
 *
 */

#ifndef LONG_PRESS_H_
#define LONG_PRESS_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 *
 * @brief Parameters for the long press gesture
 *
 * The structure @c long_press_params_t represents the parameters for the long press
 * gesture.
 */
typedef struct {
	unsigned max_displacement;    /**< The maximum number of pixels from the initial
	                                   coordinates of the touch before the press fails. */
	unsigned min_press_time_ms;   /**< The minumum time in millisecond for the gesture
	                                   to be considered a long press and not a tap. */
} long_press_params_t;

/**
 *
 * @brief The long press data structure
 *
 * The structure @c gesture_long_press_t carries data about the long
 * press gesture.
 */
typedef struct {
	gesture_base_t base;          /**< The gesture base data structure. */
	long_press_params_t params;   /**< The long press parameters. */
	gesture_coords_t coords;      /**< The coordinates of the touch. */
	int success_timer;            /**< The ID of the timer for this gesture. */ 
} gesture_long_press_t;

/**
 * @brief Allocate a new long press gesture
 *
 * The function @c long_press_gesture_alloc() allocates a new long press gesture data structure
 * and initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params     A pointer to the long press gesture parameters.
 * @param callback   The function to invoke when the long press gesture changes state.
 * @param set        A pointer to the gesture set to add this long press gesture to.
 *
 * @return A pointer to an initialized pinch gesture. 
 */
gesture_long_press_t* long_press_gesture_alloc(long_press_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the long press parameters
 *
 * The function @c long_press_gesture_default_params() initializes the gestures parameters
 * to default values.
 *
 * @param params     The long press gesture parameters.
 *
 * @return Nothing.
 */
void long_press_gesture_default_params(long_press_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* LONG_PRESS_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
