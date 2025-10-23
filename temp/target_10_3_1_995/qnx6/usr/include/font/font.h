/**
 * Copyright (C) Research In Motion Limited 2012. All rights reserved.
 *
 * @file font.h
 *
 * @brief Functions to determine the font settings
 *
 * This file defines the BPS font service, which enables applications
 * to listen for font changes events.  For example, using the font
 * service allows an application to receive notifications when font
 * size changes or when font name changes. This service is meant to be
 * used with BPS main library and hence any application using this must
 * also link libbps
 */
#ifndef FONT_H_
#define FONT_H_

#ifndef FONT_API
#define FONT_API __attribute__((visibility("default")))
#endif

#include "bps/bps.h"
#include "bps/event.h"

#ifndef __BEGIN_DECLS
#define __BEGIN_DECLS
#endif
__BEGIN_DECLS

/**
 * @brief Possible font events
 *
 * This enumeration defines the possible font events.  Currently, there is
 * only one event. This event is generated when the user changes the font
 * or font size.
 */
enum {
     /**
     * Font event indicating font has changed.
     */
    FONT_CHANGED        = 0x01
};

/**
 * @brief Start receiving font status change events
 *
 * The @c font_request_events() function starts to deliver font status change
 * events to your application using BPS.  Events will be posted to the currently
 * active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested.  The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 */
FONT_API int font_request_events(int flags);

/**
 * @brief Stop receiving font status change events
 *
 * The @c font_stop_events() function stops font status change events from
 * being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 */
FONT_API int font_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the font service
 *
 * The @c font_get_domain() function gets the unique domain ID for
 * the font service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is a
 * font event, and respond accordingly.
 *
 * @return The domain ID for the font service.
 */
FONT_API int font_get_domain();

/**
 * @brief Get the current font name from the BPS font event
 *
 * The @c font_event_get_fontname() function extracts the current font name
 * from the specified font event.
 *
 * @param event The BPS font event to extract the current font name from.
 *
 * @return The font name in UTF-8 encoding specified by the event. Or NULL
 * if an error occurred
 */
FONT_API const char* font_event_get_fontname(bps_event_t* event);

/**
 * @brief Get the current font size from the BPS font event
 *
 * The @c font_event_get_size() function extracts the current size
 * from the specified font event.
 *
 * @param event The BPS font event to extract the current font size from.
 *
 * @return The system font size in points indicated by the event. Returns -1 if an
 * error occurred
 */
FONT_API int font_event_get_size(bps_event_t* event);


/**
 * @brief Get the current system font name and size on the device
 *
 * The @c font_get_system_font function extracts the current font name
 * and size currently used by the device.
 *
 * @param size pointer to where system font size will be stored.
 *
 * @return The current font name in UTF-8 encoding. Or NULL if a problem occurred.
 */
FONT_API const char* font_get_system_font(int* size);


#ifndef __END_DECLS
#define __END_DECLS
#endif
__END_DECLS

#endif /* FONT_H_ */
