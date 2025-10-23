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
 * @file timer.h
 *
 * @brief Functions and datatypes for gestures timers
 *
 * The timer.h header file provides data type definitions and functions
 * for manipulating timers used for determining the time elapsed between
 * touches or the length of a touch.
 *
 */ 
 
#include "gestures/types.h"

#ifndef GESTURES_TIMER_H_
#define GESTURES_TIMER_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

struct gesture_base;
struct mtouch_event;
struct timespec;

/**
 * @brief Gesture timer callback function type
 *
 * The callback function @c gesture_timer_callback_t is invoked
 * when a timer expires.
 *
 * @param gesture A pointer to the gesture.
 * @param param   A pointer to the parameter list.
 *
 * @return The current gesture state. 
 */
typedef gesture_state_e(*gesture_timer_callback_t)(struct gesture_base* gesture, void* param);


/**
 * @brief Create a gesture timer
 *
 * The function @c gesture_timer_create() creates a new gesture timer that
 * invokes the callback function when expired.
 *
 * @param gesture  A pointer to the gesture.
 * @param callback The gesture timer callback function.
 * @param param    A pointer to the parameter list.
 *
 * @return The timer ID, or -1 on failure.
 */
int gesture_timer_create(struct gesture_base* gesture, gesture_timer_callback_t callback, void* param);


/**
 * @brief Set a gesture timer from now
 *
 * The function @c gesture_timer_set_now() sets a timer using the current time
 * as the reference time.
 *
 * @param gesture   A pointer to the gesture.
 * @param timer_id  The timer to set.
 * @param ms        The expiry time in milliseconds (from now).
 *
 * @return 0 on success, or -1 on failure.
 */
int gesture_timer_set_now(struct gesture_base* gesture, int timer_id, unsigned ms);

/**
 * @brief Set a gesture timer from a timestamp
 *
 * The function @c gesture_timer_set_ms() sets a timer using a timestamp
 * as the reference time.
 *
 * @param gesture    A pointer to the gesture.
 * @param timer_id   The timer to set.
 8 @param ms         The expiry time in milliseconds.
 * @param base_nsec  The base time in nanoseconds. The @c ms parameter is compared
 *                   to this time to determine whether the timer has expired.
 *
 * @return 0 on success, or -1 on failure. 
 */
int gesture_timer_set_ms(struct gesture_base* gesture, int timer_id, unsigned ms, _Uint64t base_nsec);

/**
 * @brief Set a gesture timer from a touch event timestamp
 *
 * The function @c gesture_timer_set() evemt sets a timer using a touch event 
 * timestamp as the reference time.
 *
 * @param gesture     A pointer to the gesture.
 * @param timer_id    The timer to set.
 * @param ms          The expiry time in milliseconds.
 * @param base_event  A pointer to the touch event whose timestamp is to be used as 
 *                    the base time.
 *
 * @return 0 on success, or -1 on failure. 
 */
int gesture_timer_set_event(struct gesture_base* gesture, int timer_id, unsigned ms, struct mtouch_event* base_event);


/**
 * @brief Clear an armed timer
 *
 * The function @c gesture_timer_clear() clears an armed timer (a timer
 * previously set by one of the @c gesture_timer_set_*() functions). If
 *the timer is unarmed, this function does nothing and returns 0.
 *
 * @param gesture   A pointer to the gesture.
 * @param timer_id  The timer to clear.
 *
 * @return 0 on success, or -1 on failure. 
 */
int gesture_timer_clear(struct gesture_base* gesture, int timer_id);


/**
 * @brief Destroy a timer
 *
 * The function @c gesture_timer_destroy() destroys the specified timer by resetting
 * the timer data structure. It does not free any memory associated with the timer.
 *
 * @param gesture   A pointer to the gesture.
 * @param timer_id  The timer to clear.
 *
 * @return 0 on success, or -1 on failure.
 */
void gesture_timer_destroy(struct gesture_base* gesture, int timer_id);


/**
 * @brief Query a timer
 *
 * The function @c gesture_timer_query() returns information about the timer.
 * If the timer is valid, the return value is set to 0, the parameter @c pending is set
 * to the timer's current pending state (destroyed timer will result in a -1 return
 * value), and @c expiry is set to the timer's expiry time.
 *
 * @param gesture        A pointer to the gesture.
 * @param timer_id       The id of the timer to query.
 * @param [out] pending  Returns the current state of the timer.
 * @param [out] expiry   Returns the expiry time of the timer.
 *
 * @return 0 if the timer is valid, -1 otherwise. 
 */
int gesture_timer_query(struct gesture_base* gesture, int timer_id, int* pending, _Uint64t* expiry);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* GESTURES_TIMER_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
