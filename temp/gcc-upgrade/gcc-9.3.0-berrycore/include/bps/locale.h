/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file locale.h
 *
 * @brief The BlackBerry Platform Service locale service
 *
 * The locale service provides functions for reading the device's current locale
 * and language settings. These settings determine the language used to display
 * text in the UI.
 *
 * You can only retrieve the locale settings with this API; you can't change
 * them.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_LOCALE_H_INCLUDED
#define _BPS_LOCALE_H_INCLUDED

#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible locale events
 *
 * This enumeration defines the possible locale events.  Currently, there is
 * only one event. This event is generated when the user changes the current
 * language or locale.
 * @anonenum bps_locale_events Locale events
 *
 * @since BlackBerry 10.0.0
 */
enum {
     /**
     * The single locale event, which contains all of the information
     * about the current locale of the device.
      *
      * @since BlackBerry 10.0.0
     */
    LOCALE_INFO        = 0x01
};

/**
 * @brief Start receiving locale status change events
 *
 * The @c locale_request_events() function starts to deliver locale status
 * change events to your application using BPS.  Events will be posted to the
 * currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested.  The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int locale_request_events(int flags);

/**
 * @brief Stop receiving locale status change events
 *
 * The @c locale_stop_events() function stops locale status change events from
 * being delivered to the application using BPS.
 *
 * @param flags The types of events to stop delivering to the application. A
 * value of zero indicates that all events are stopped.
 * The meaning of non-zero values is reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int locale_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the locale service
 *
 * The @c locale_get_domain() function gets the unique domain ID for
 * the locale service.  You can use this function in your application
 * to test whether an event that you retrieved using @c bps_get_event() is a
 * locale event, and respond accordingly.
 *
 * @return The domain ID for the locale service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int locale_get_domain();

/**
 * @brief Get the current locale string
 *
 * The @c locale_get_locale() function extracts the locale string without any
 * processing (e.g., en_US, fr_FR, en_GR, zh_TW, zh_Hant_TW, etc.) that is set
 * on the device.  Upon success, the caller is responsible for freeing the
 * returned buffer using @c bps_free().
 *
 * @param locale Upon success, the current locale.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int locale_get_locale(char **locale);

/**
 * @brief Get the current locale language and country.
 *
 * The @c locale_get() function gets the current locale language and country
 * that is set on the device.  Upon success, the caller is responsible for
 * freeing all buffers that are returned using @c bps_free().
 *
 * @param language The current locale language.
 * @param country The current locale country.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int locale_get(char **language, char **country);

/**
 * @brief Get the current language from a @c LOCALE_INFO event
 *
 * The @c locale_event_get_language() function extracts the current language
 * (e.g., en, fr, es, etc.) from the specified @c LOCALE_INFO event.
 *
 * The language returned is from the language codes defined by ISO 639-1
 * ( http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes ), using the rules set
 * by BCP47 ( http://tools.ietf.org/html/bcp47 ).
 *
 * @param event The @c LOCALE_INFO event to extract the current language from.
 *
 * @return The current language.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *locale_event_get_language(bps_event_t *event);

/**
 * @brief Get the current script from a @c LOCALE_INFO event
 *
 * The @c locale_event_get_script() function extracts the current script (e.g.,
 * Hans, Hant, etc.) from the specified @c LOCALE_INFO event.
 *
 * The script returned is from the language codes defined by ISO 639-1
 * ( http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes ), using the rules set
 * by BCP47 ( http://tools.ietf.org/html/bcp47 ).
 *
 * @param event The @c LOCALE_INFO event to extract the current script from.
 *
 * @return The current script.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *locale_event_get_script(bps_event_t *event);

/**
 * @brief Get the current country from a @c LOCALE_INFO event
 *
 * The @c locale_event_get_country() function extracts the current country
 * (e.g., US, GB, FR, etc.) from the specified @c LOCALE_INFO event.
 *
 * The country returned is from the country codes defined by ISO 3166-1
 * ( http://en.wikipedia.org/wiki/ISO_3166-1 ), using the
 * rules set by BCP47 ( http://tools.ietf.org/html/bcp47 ).
 *
 * @param event The @c LOCALE_INFO event to extract the current country from.
 *
 * @return The current country.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *locale_event_get_country(bps_event_t *event);

/**
 * @brief Get the locale string from a @c LOCALE_INFO event
 *
 * The @c locale_event_get_locale() function extracts the locale string without
 * any processing (e.g., en_US, fr_FR, en_GR, etc.) from the specified
 * @c LOCALE_INFO event.
 *
 * @param event The @c LOCALE_INFO event to extract the locale from.
 *
 * @return The current locale.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * locale_event_get_locale(bps_event_t *event);

__END_DECLS

#endif // include guard
