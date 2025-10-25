/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file region.h
 *
 * @brief The BlackBerry Platform Service region service
 *
 * The region service provides functions for reading the device's current
 * region locale settings. The region locale contains a language and a region
 * that may dictate the formatting of dates and numbers (e.g., time, units of
 * measurement, currency, etc.) as well as the formatting of other output that
 * may vary from region to region.
 *
 * Region settings may only be retrieved with these functions - the settings
 * cannot be changed using these functions.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_REGION_H_INCLUDED
#define _BPS_REGION_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible region events
 *
 * This enumeration defines the possible region events. Currently, there is
 * only one event. This event is generated when the user changes the current
 * language or region.
 * @anonenum bps_region_events Region events
 *
 * @since BlackBerry 10.0.0
 */
enum {
     /**
     * The single region event, which contains all of the information
     * about the current region of the device.
      *
      * @since BlackBerry 10.0.0
     */
    REGION_INFO        = 0x01
};

/**
 * @brief Start receiving region status change events
 *
 * The @c region_request_events() function starts to deliver region status
 * change events to your application using BPS. Events will be posted to the
 * currently active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int region_request_events(int flags);

/**
 * @brief Stop receiving region status change events
 *
 * The @c region_stop_events() function stops region status change events from
 * being delivered to the application using BPS.
 *
 * @param flags The types of events to stop delivering to the application. A
 * value of zero indicates that all events are stopped. The meaning
 * of non-zero values is reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int region_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the region service
 *
 * The @c region_get_domain() function gets the unique domain ID for
 * the region service. You can use this function in your application
 * to test whether an event that you retrieved using @c bps_get_event() is a
 * region event, and respond accordingly.
 *
 * @return The domain ID for the region service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int region_get_domain();

/**
 * @brief Get the current region string
 *
 * The @c region_get_region() function extracts the region string without any
 * processing (e.g., en_US, fr_FR, en_GR, zh_TW, zh_Hant_TW, etc.) that is set
 * on the device.  Upon success, the caller is responsible for freeing the
 * returned buffer using @c bps_free().
 *
 * @param region Upon success, the current region.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int region_get_region(char **region);

/**
 * @brief Get the current region language and country.
 *
 * The @c region_get() function gets the current region language and country
 * that is set on the device.  Upon success, the caller is responsible for
 * freeing all buffers that are returned using @c bps_free().
 *
 * @param language The current region language.
 * @param country The current region country.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int region_get(char **language, char **country);

/**
 * @brief Get the current language from a @c REGION_INFO event
 *
 * The @c region_event_get_language() function extracts the current language tag
 * (e.g., en, fr, es, etc.) from the specified @c REGION_INFO event.
 *
 * The language returned is from the language codes defined by ISO 639-1
 * ( http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes ), using the rules set
 * by BCP47 ( http://tools.ietf.org/html/bcp47 ).
 *
 * @param event The @c REGION_INFO event to extract the current language from.
 *
 * @return The current language.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *region_event_get_language(bps_event_t *event);

/**
 * @brief Get the current script from a @c REGION_INFO event
 *
 * The @c region_event_get_language() function extracts the current script
 * (e.g., Hans, Hant, etc.) from the specified @c REGION_INFO event.
 *
 * The script returned is from the language codes defined by ISO 639-1
 * ( http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes ), using the rules set
 * by BCP47 ( http://tools.ietf.org/html/bcp47 ).
 *
 * @param event The @c REGION_INFO event to extract the current script from.
 *
 * @return The current script.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *region_event_get_script(bps_event_t *event);

/**
 * @brief Get the current country from a @c REGION_INFO event
 *
 * The @c region_event_get_country() function extracts the current country
 * (e.g., US, GB, FR, etc.) from the specified @c REGION_INFO event.
 *
 * The country returned is from the country codes defined by ISO 3166-1
 * ( http://en.wikipedia.org/wiki/ISO_3166-1 ), using the rules set by BCP47
 * ( http://tools.ietf.org/html/bcp47 ).
 *
 * @param event The @c REGION_INFO event to extract the current country from.
 *
 * @return The current country.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *region_event_get_country(bps_event_t *event);

/**
 * @brief Get the raw region string from a @c REGION_INFO event
 *
 * The @c region_event_get_region() function extracts the region string without
 * any processing (e.g., en_US, fr_FR, en_GR, etc.) from the specified
 * @c REGION_INFO event.
 *
 * @param event The @c REGION_INFO event to extract the region from.
 *
 * @return The current region.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * region_event_get_region(bps_event_t *event);

__END_DECLS

#endif // include guard
