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
 * @file screen_helpers.h
 * 
 * @brief Helper functions for screen input events
 * 
 * The screen_helpers.h header file provides functions for processing screen
 * input events.
 *
 */
#include <screen/screen.h>
#include "input/event_types.h"

#ifndef SCREEN_HELPERS_H_
#define SCREEN_HELPERS_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Retrieve touch event data from a screen event
 *
 * The function @c screen_get_mtouch_event() populates the mtouch_event with
 * data fetched from the screen event.
 *
 * @param screen_event The screen event to retrieve data from.
 * @param mtouch_event The mtouch_event to populate.
 * @param screen_abs If 1, use screen coordinates otherwise use source viewport.
 * @return 0 on success, -1 on failure.
 */
static inline int
screen_get_mtouch_event(screen_event_t screen_event, mtouch_event_t* mtouch_event, int screen_abs)
{
	int ev_type;
	int touch_size[2];
	int coords[2];
	int rc;

	rc = screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TYPE, &ev_type);
	if (rc || (ev_type == SCREEN_EVENT_NONE)) {
		return -1;
	}

	switch (ev_type) {
		case SCREEN_EVENT_MTOUCH_TOUCH:
			/* Fallthrough */
		case SCREEN_EVENT_MTOUCH_MOVE:
			/* Fallthrough */
		case SCREEN_EVENT_MTOUCH_RELEASE:
			mtouch_event->event_type = (input_event_e)ev_type;
			screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TOUCH_ID, (int*)&mtouch_event->contact_id);
			if (screen_abs) {
				screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_POSITION, (int*)&coords);
			} else {
				screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_SOURCE_POSITION, (int*)&coords);
			}
			mtouch_event->x = coords[0];
			mtouch_event->y = coords[1];
			screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_SIZE, (int*)&touch_size);
			mtouch_event->width = touch_size[0];
			mtouch_event->height = touch_size[1];
			screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TOUCH_ORIENTATION, (int*)&mtouch_event->orientation);
			screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TOUCH_PRESSURE, (int*)&mtouch_event->pressure);
			screen_get_event_property_llv(screen_event, SCREEN_PROPERTY_TIMESTAMP, (long long*)&mtouch_event->timestamp);
			screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_SEQUENCE_ID, (int*)&mtouch_event->seq_id);
			return 0;
		default:
			return -1;
	}
}

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* SCREEN_HELPERS_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
