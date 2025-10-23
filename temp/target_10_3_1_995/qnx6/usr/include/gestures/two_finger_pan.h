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
 * @file two_finger_pan.h
 *
 * @brief Definition of the two finger pan gesture
 *
 * The two_finger_pan.h header file provides data type definitions and functions
 * for the two-finger pan gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */ 
 
#ifndef TWO_FINGER_PAN_H_
#define TWO_FINGER_PAN_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Two-finger pan gesture parameters
 *
 * The stucture @c tfpan_params_t is provided for consistency with other gesture
 * implementations. Although carries no information, it cannot be empty because
 * common functions rely on its existence. 
 */
typedef struct {
	int none;
} tfpan_params_t;

/** @brief The two-finger pan gesture data type
 *
 * The structure @c gesture_tfpan_t carries data about the pinch gesture.
 */
typedef struct {
	gesture_base_t base;              /**< The gesture base data structure. */
	tfpan_params_t params;            /**< The two-finger pan parameters. */
	gesture_coords_t coords[2];       /**< The coordinates of the touch events for the two fingers. */
	gesture_coords_t centroid;        /**< The coordintes of the midpoint between the two touches. */
	gesture_coords_t last_centroid;   /**< The coordintes of the midpoint between the previous two touches. */
} gesture_tfpan_t;

/**
 * @brief Allocate and initialize the two-finger pan gesture structure
 *
 * The function @c tfpan_gesture_alloc() allocates a new two-finger pan gesture data structure,
 * initializes it with the specified parameters and callback function, and adds it to
 * the specified gesture set.
 *
 * @param params A pointer to the two-finger pan gesture parameters.
 * @param callback The function to invoke when the two-finger pan gesture changes state.
 * @param set A pointer to the gesture set to add this two-finger pan gesture to.
 *
 * @return A pointer to an initialized two-finger pan gesture.
 */
gesture_tfpan_t* tfpan_gesture_alloc(tfpan_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the two-finger pan parameters
 *
 * The function @c tfpan_gesture_default_params() initializes the two-finger pan
 * parameters to default values.
 *
 * @param params A pointer to the two-finger pan gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void tfpan_gesture_default_params(tfpan_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* TWO_FINGER_PAN_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
