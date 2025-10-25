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
 * @file event_list.h
 *
 * @brief Data types and functions for event lists
 *
 * The event_list.h header file provides data type definitions and functions
 * for lists of touch events to be processed by the gesture sets.
 * 
 * This file makes use of list and queue macros defined in the header file
 * @c sys/queue.h. For more information about these macros, see the documentation
 * in the @c sys/queue.h file. 
 *
 */  
 
#include <sys/queue.h>
#include <sys/cdefs.h>

#include "input/event_types.h"

#ifndef EVENT_LIST_H_
#define EVENT_LIST_H_

__BEGIN_DECLS

/**
 * @brief Event list
 *
 * The structure @c event_list is a private data type representing the list of
 * touch events that need to be handled. Use the @c event_list_*() 
 * functions to manipulate the event list.
 */
struct event_list;

/**
 * @brief Event list item
 *
 * The structure @c event_list_item_t represents an item in the list of
 * touch events that need to be handled. Use the @c event_list_*() 
 * functions to manipulate the event list.
 */
typedef struct event_list_item {
	STAILQ_ENTRY(event_list_item) link;  /**< A macro that resolves to a an 
	                                          @c event_list_item pointer. Use the
	                                          @c event_list_*() functions and the 
	                                          @c STAILQ macros to manipulate the
	                                          event list, rather than manipulating
	                                          it directly.*/
	mtouch_event_t event;                /**< A touch event */
} event_list_item_t;

/**
 * @brief Allocate and initialize an event list
 *
 * The function @c event_list_alloc() allocates and initializes a new event list.
 * If @c init_size, @c grow_size and @c max_size are all zero, the defaults values
 * of 256, 128 and 1024, respectively, are used. If the @c allow_compress parameter
 * is non-zero, touch events of type @c INPUT_EVENT_MTOUCH_MOVE will be deleted from
 * the list when it is full to make room for more items.
 *
 * @param init_size       The initial size of the list, in number of events.
 * @param grow_size       The size by which a list is to be grown when full, in number of events.
 * @param max_size        The maximum size a list will be allowed to grow to, in number of events.
 * @param allow_compress  Allow move events to be dropped to make room in the list.
 *
 * @return The newly allocated event list on success, NULL on failure
 */
struct event_list* event_list_alloc(unsigned init_size, unsigned grow_size, unsigned max_size, int allow_compress);

/**
 * @brief Allocate and initialize an event list from an existing list
 *
 * The function @c event_list_alloc_copy() allocates and initializes a new
 * event list by copying the entries from an existing event list.
 *
 * @param list  A pointer to the event list to copy
 *
 * @return The newly allocated event list on success, NULL on failure
 */
struct event_list* event_list_alloc_copy(struct event_list* list);

/**
 * @brief Copy an event list
 *
 * The function @c event_list_copy() copies the events from one event list
 * to another.
 *
 * @param from_list A pointer to the event list to copy from.
 * @param to_list   A pointer to the event list to copy to.
 *
 * @returns 0 on success, -1 if to_list is too small to hold all events.
 */
int event_list_copy(struct event_list* from_list, struct event_list* to_list);

/**
 * @brief Free an event list
 *
 * The function @c event_list_free() resets the members of the specified
 * list and frees the associated memory.
 *
 * @param list A pointer to the event list.
 *
 * @return Nothing.
 */
void event_list_free(struct event_list* list);

/**
 * @brief Add an event to an event list
 *
 * The function @c event_list_add() adds an event to an event list.
 *
 * @param list   A pointer to the event list.
 * @param event  A pointer to the event to add.
 *
 * @return 0 on success, -1 on failure
 */
int event_list_add(struct event_list* list, mtouch_event_t* event);

/**
 * @brief Clear an event list
 *
 * The function @c event_list_clear() returns an event list to the empty state.
 * It does not free any of the associated memory.
 *
 * @param list A pointer to the even list to clear.
 *
 * @return Nothing.
 */
void event_list_clear(struct event_list* list);

/**
 * @brief Return the first item in an event list
 *
 * The function @c event_list_get_first() gets the first element in an event list.
 * Use the macro @c STAILQ_NEXT(element, field) to walk the list, where @c element 
 * is a pointer to an event list item, and @c field is the @c link member of 
 * the event list item.
 *
 * @param list A pointer to an event list.
 *
 * @return A pointer to the first item in the event list.
 */
event_list_item_t* event_list_get_first(struct event_list* list);

__END_DECLS

#endif /* EVENT_LIST_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
