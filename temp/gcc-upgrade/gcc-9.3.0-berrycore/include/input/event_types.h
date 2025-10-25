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
 * @mainpage Input Events Library Overview
 *
 * The input events library allows applications to receive and process events from
 * input devices. 
  
 */
 
/**
 * @file event_types.h
 * 
 * @brief Enumerations and structures for input events
 * 
 * The event_types.h header file provides type definitions for classifying
 * input event types.  These type definitions can be used to determine the kind
 * of input event that has occurred and the properties of the event.
 *
 */
#include <inttypes.h>
#include <sys/types.h>
#include <time.h>

#ifndef INPUTEVENTS_H_
#define INPUTEVENTS_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Enumeration for categorizing input event classes
 * 
 * The @c input_class_e enumeration defines the types of input events that can be
 * reported.
 */
 typedef enum {
	INPUT_CLASS_MTOUCH = 1, /**< A touch event on the screen */
	INPUT_CLASS_KEYBOARD,   /**< A key event on the virtual keyboard */
	INPUT_CLASS_MOUSE,       /**< A mouse event using a connected mouse */
	INPUT_CLASS_MTOUCH_EXTERNAL /**< A touch event on the screen is forwarded  to Screen using inject */
} input_class_e;

/**
 * @brief Enumeration for the types of @c INPUT_CLASS_MTOUCH events
 * 
 * The @c input_event_e enumeration defines the possible @c INPUT_CLASS_MTOUCH input event
 * types.
 */
typedef enum {
	INPUT_EVENT_UNKNOWN = 0,        /**< Unknown event type (default) */
	INPUT_EVENT_MTOUCH_TOUCH = 100, /**< Event type for when a finger just
                                         touched the screen */
	INPUT_EVENT_MTOUCH_MOVE,        /**< Event type for when a finger is already
                                         touching the screen but is changing
                                         position */
	INPUT_EVENT_MTOUCH_RELEASE,     /**< Event type for when a finger is removed
                                         from the screen */
	INPUT_EVENT_MTOUCH_CANCEL,      /**< Event type for when a gesture is cancelled,
	                                      touch controller power off could cause cancel */
	INPUT_EVENT_FLUSH,               /**< Event type for an flush event,
		                                      normally requested by filter */
	INPUT_EVENT_LARGE_OBJECT,       /**< Event type for a large object
		                                      touch controller can report a large object */
	INPUT_EVENT_LARGE_OBJECT_CANCEL  /**< Event type for a large object cancel
		                                      used to distinguish a large object cancel from a cancel
		                                      This is a bit of a hack to get around the lack of a cancel event
		                                      It should not be need once a  cancel event is propergated to the application */
} input_event_e;

/**
 * @brief Enumeration for the types of contact for a @c INPUT_CLASS_MTOUCH event
 *
 * The @c contact_type_e enumeration defines the possible contact types for
 * @c INPUT_CLASS_MTOUCH input event types.
 */
typedef enum {
	CONTACT_TYPE_FINGER = 0,        /**< Finger touch (default) */
	CONTACT_TYPE_STYLUS = 1,        /**< Stylus touch */
} contact_type_e;

/**
 * @brief Common structure that contains details of @c INPUT_CLASS_MTOUCH input events
 * 
 * The @c mtouch_event structure represents information that is common to all
 * input events of class @c INPUT_CLASS_MTOUCH.  This information is filled in by
 * the driver whenever an @c INPUT_CLASS_MTOUCH event occurs.
 */
typedef struct mtouch_event {
	input_event_e event_type;   /**< The @c INPUT_CLASS_MTOUCH event type */
	_Uint64t timestamp;         /**< The approximate time at which the event
                                     occurred */
	_Uint32t seq_id;            /**< The sequence number for the event, incremented
                                     each time a new touch event occurs */
	_Uint32t contact_id;        /**< The order of occurrence for multiple touch
                                     contacts */
	_Int32t x;                  /**< The x screen position for the event, in pixels */
	_Int32t y;                  /**< The y screen position for the event, in pixels */
	_Uint32t width;             /**< The width of the touch area, in pixels */
	_Uint32t height;            /**< The height of the touch area, in pixels */
	_Uint32t orientation;       /**< The orientation of the contact, not implemented */
	_Uint32t pressure;          /**< The pressure of the touch contact, ranging
                                     from 0 to 2^32 - 1, not implemented */
	_Uint32t contact_type;      /**< The contact type, e.g. finger, stylus, etc */
	_Uint32t select;            /**< The selected buttons */
	_Uint32t flags;             /**< screen flag property */
} mtouch_event_t;

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* INPUTEVENTS_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
