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
 * @file set.h
 *
 * @brief Data types and functions for gesture sets
 *
 * The set.h header file provides data type definitions and functions
 * for the gesture set.
 *
 */ 
 
#include "gestures/types.h"

#ifndef GESTURES_SET_H_
#define GESTURES_SET_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Gesture set
 *
 * The structure @c gestures_set_t is a private data type that represents a set
 * of gestures. All gestures in the gesture set receive touch events simultaneously,
 * therefore it is up to the application to define dependencies between gestures
 * and to supply callback functions for handling gestures that are recognized.
 */
struct gestures_set;

struct mtouch_event;
struct event_list;


/**
 * @brief Callback function for gesture set failure
 *
 * The callback function @c gestures_set_fail_f() is invoked when the gesture set
 * fails. The gesture set fails when all gestures in the set transition to the 
 * FAILED state. The callback is passed the list of events leading up to the failure,
 * so that those events can be passed to another gesture set, if necessary.
 *
 * The @c async parameter indicates which thread invoked the callback:
 *   <ul>
 *     <li>the thread that called @c gestures_set_process_event() (@c async == 0) </li>
 *     <li>the timer thread (@c async == 1)</li>
 *   </ul>
 *
 * @param set     A pointer to the gesture set.
 * @param list    A pointer to the event list.
 * @param async   Indicator of the originating thread (see description). 
 *
 * @return Nothing.
 */
typedef void(*gestures_set_fail_f)(struct gestures_set* set, struct event_list* list, int async);

/**
 * @brief Allocate and initialize a new gesture set
 *
 * The function @c gestures_set_alloc() creates a new gesture set and 
 * initializes.
 *
 * @return Nothing.
 */
struct gestures_set* gestures_set_alloc();

/**
 * @brief Free a gesture set
 *
 * The function @c gestures_set_free() frees the memory associated with
 * a gesture set.
 *
 * @param set A pointer to the gesture set to free.
 * @return Nothing.
 */
void gestures_set_free(struct gestures_set* set);

/**
 * @brief Add a gesture to a gesture set
 *
 * The function @c gestures_set_add() adds the specified gesture to the specified
 * gesture set.
 *
 * @param set A pointer to the gesture set.
 * @param gesture A pointer to the gesture to add.
 * @return Nothing.
 */
void gestures_set_add(struct gestures_set* set, gesture_base_t* gesture);

/**
 * @brief Add a failure callback to a gesture set
 *
 * The function @c gestures_set_register_fail_cb() adds the specified callback function
 * to the specified gesture set.
 *
 * @param set A pointer to the gesture set.
 * @param callback The callback function to add.
 * @return Nothing.
 */
void gestures_set_register_fail_cb(struct gestures_set* set, gestures_set_fail_f callback);

/**
 * @brief Process a touch event at the gesture set level
 *
 * The function @c gestures_set_process_event() processes incoming touch events by adding them to the
 * event list and passing them to the individual gestures so that their processing
 * callback functions can be invoked as appropriate.
 *
 * @param set A pointer to the gesture set.
 * @param event The touch event to process.
 * @param param A pointer to the parameter list for the callback functions.
 * @return The number of callback functions invoked.
 */
int gestures_set_process_event(struct gestures_set* set, struct mtouch_event* event, void* param);

/**
 * @brief Process the event list
 *
 * The function @c gestures_set_process_event_list() processes the event list by adding the events
 * to the gesture set, updating various properties associated with the events, evaluating timers,
 * and passing each event to the individual gestures for processing.
 *
 * @param set A pointer to the gesture set.
 * @param list The event list to process.
 * @param param A pointer to the parameter list for the callback functions.
 * @return The number of callback functions invoked.
 */
int gestures_set_process_event_list(struct gestures_set* set, struct event_list* list, void* param);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* GESTURES_SET_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
