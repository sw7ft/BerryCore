/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file geolocation.h
 *
 * @brief Functions to determine the current geolocation of the device
 * 
 * This file defines the geolocation service, which provides functions for
 * reading the device's geolocation.  To read the geolocation data, the
 * application must have the @c read_geolocation capability. To grant an
 * application the @c read_geolocation capability, the bar-descriptor.xml file
 * in the application's project must contain the line
 * "<permission>read_geolocation</permission>".
 *
 * Some of these geolocation functions are designed to return boolean values
 * that indicate whether their associated attributes are valid. For example, @c
 * geolocation_event_is_altitude_valid() indicates whether the altitude from a
 * @c GEOLOCATION_INFO event is valid.
 *
 * In this context, a valid attribute means that the value of the attribute was
 * included in the last update from the geolocation system. For example, if the
 * device cannot obtain a GPS fix, but has Wi-Fi connectivity, the geolocation
 * system reports latitude, longitude, and accuracy. The system doesn't provide
 * values for any other attributes (such as altitude, heading, and so on), and
 * these attributes are marked as not valid.  This means that the validity
 * functions for these attributes return @c false.
 * 
 * Subsequently, if the device obtains a GPS fix, the geolocation system reports
 * values for all attributes, and all attributes are marked as valid. This means
 * that the validity functions for these attributes return @c true. If the GPS
 * fix is lost, the attributes other than latitude, longitude, and accuracy are
 * marked as not valid again.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_GEOLOCATION_H_INCLUDED
#define _BPS_GEOLOCATION_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible geolocation events
 *
 * This enumeration defines the possible geolocation events.
 *
 * @anonenum bps_geolocation_events Geolocation events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The geolocation info event, which contains all of the information about
     * the current geolocation of the device.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_INFO        = 0x01,
    /**
     * The geolocation cancel event, which indicates that geolocation events
     * have been canceled.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_CANCEL      = 0x02,
    /**
     * The geolocation error event, which indicates that there was an error and
     * provides details of that error.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR      = 0x03,
    /**
     * The geolocation status event, which contains information about the
     * client's current request and status.
     *
     * @since BlackBerry 10.2.0
     */
    GEOLOCATION_STATUS       = 0x04,
};

/**
 * @brief Possible geolocation providers
 *
 * This enumeration defines the possible geolocation providers.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized provider (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_PROVIDER_UNRECOGNIZED  = 0,
    /**
     * The Hybrid provider combines the GNSS and Network providers to receive
     * the best location available.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_PROVIDER_HYBRID        = 1,
    /**
     * The GNSS provider manages GPS, GLONASS, and related location
     * technologies.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_PROVIDER_GNSS          = 2,
    /**
     * The Network provider manages network-based positioning technologies such
     * as cell-site and Wi-Fi.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_PROVIDER_NETWORK       = 3,
    /**
     * Number of providers.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_NUM_PROVIDERS

} geolocation_provider_t;

/**
 * @brief Possible geolocation fix types
 *
 * This enumeration defines the possible geolocation fix types.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unrecognized fix type (not one listed below).
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_UNRECOGNIZED         = 0,
    /**
     * Best fix type.  May be requested along with any provider.  May appear in
     * geolocation events when using the Hybrid provider.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_BEST                 = 1,
    /**
     * GPS MS based fix type.  May be requested with the GNSS provider.  May
     * appear in geolocation events when using the Hybrid or GNSS providers.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_GPS_MS_BASED         = 2,
    /**
     * GPS MS assisted fix type.  May be requested with the GNSS provider.  May
     * appear in geolocation events when using the Hybrid or GNSS providers.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_GPS_MS_ASSISTED      = 3,
    /**
     * GPS autonomous fix type.  May be requested with the GNSS provider.  May
     * appear in geolocation events when using the Hybrid or GNSS providers.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_GPS_AUTONOMOUS       = 4,
    /**
     * Cellsite fix type.  May be requested with the Network provider.  May
     * appear in geolocation events when using the Hybrid or Network providers.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_CELLSITE             = 5,
    /**
     * Wifi fix type.  May be requested with the Network provider.  May appear
     * in geolocation events when using the Hybrid or Network providers.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_FIX_TYPE_WIFI                 = 6,
    /**
     * Number of fix types.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_NUM_FIX_TYPES
} geolocation_fix_type_t;

/**
 * @brief Possible geolocation errors
 *
 * This enumeration defines the possible geolocation errors that can be received
 * in a @c #GEOLOCATION_ERROR event.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * No error.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_NONE                         = 0x00000,
    /**
     * Location services are disabled.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_FATAL_DISABLED               = 0x00001,
    /**
     * There is no last known position on the device.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_FATAL_NO_LAST_KNOWN_POSITION = 0x00002,
    /**
     * There are insufficient available location technology providers to process
     * the request.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_FATAL_INSUFFICIENT_PROVIDERS = 0x00003,
    /**
     * One or more of the request parameters are invalid.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_FATAL_INVALID_REQUEST        = 0x00004,
    /**
     * There are insufficient permissions available to process the request.
     *
     * @since BlackBerry 10.2.0
     */
    GEOLOCATION_ERROR_FATAL_PERMISSION             = 0x00006,
    /**
     * A timeout has occurred while processing the request. The request will
     * continue until the location is obtained.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_WARN_TIMEOUT                 = 0x10000,
    /**
     * The location fix has been lost due to insufficient coverage. The request
     * will continue until the location is reacquired.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_WARN_LOST_TRACKING           = 0x10001,
    /**
     * The device is stationary. No further updates until the device resumes
     * movement.
     *
     * @since BlackBerry 10.0.0
     */
    GEOLOCATION_ERROR_WARN_STATIONARY              = 0x10002,
} geolocation_error_t;

/**
 * @brief Retrieve the unique domain ID for the geolocation service
 *
 * The @c geolocation_get_domain() function gets the unique domain ID for the
 * geolocation service.  You can use this function in your application to test
 * whether an event that you retrieve using @c bps_get_event() is a geolocation
 * event, and respond accordingly.
 *
 * @return The domain ID for the geolocation service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_get_domain();

/**
 * @brief Set the period at which geolocation events are reported
 *
 * The @c geolocation_set_period() function sets the period (in seconds) at
 * which geolocation events are reported.  If the period is set to 0, a single
 * geolocation event is delivered, and no more geolocation events are delivered
 * subsequently.
 *
 * @param period The period (in seconds).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_period(unsigned int period);

/**
 * @brief Set the accuracy at which geolocation events are reported
 *
 * The @c geolocation_set_accuracy() function sets the desired accuracy (in
 * meters) of the fix when geolocation events are reported.  If the accuracy is
 * set to 0, then this criteria is disabled.
 *
 * @param accuracy The accuracy (in meters).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_accuracy(unsigned int accuracy);

/**
 * @brief Set the response time for geolocation events
 *
 * The @c geolocation_set_response_time() function sets the desired response
 * time (in seconds) of the fix for geolocation events.  If the response time is
 * set to 0, then this criteria is disabled.
 *
 * @param response_time The response time (in seconds).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_response_time(unsigned int response_time);

/**
 * @brief Set whether or not geolocation events will be sent while device is in
 * standby
 *
 * The @c geolocation_set_background() function sets whether or not requests are
 * allowed to run with the device in standby (i.e. screen off).
 *
 * @param background True means to allow in standby, otherwise disallow.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_background(bool background);

/**
 * @brief Set whether or not the last known position will be returned
 *
 * The @c geolocation_set_last_known() function sets whether or not the last
 * known position will be returned.  If set, only one geolocation event will be
 * reported, but it will be reported immediately.  It will either be a @c
 * #GEOLOCATION_INFO event containing the last known position or a @c
 * #GEOLOCATION_ERROR event if there is no last known position.  You may set the
 * provider with @c geolocation_set_provider(), but any other parameters will be
 * ignored.
 *
 * @param last_known True means the last known position will be returned,
 * otherwise it will not.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_last_known(bool last_known);

/**
 * @brief Set the location provider
 *
 * The @c geolocation_set_provider() function sets the location provider to use
 * for geolocation information (see @c #geolocation_provider_t).  If you do not
 * set a provider, the Hybrid provider is used by default.
 *
 * @param provider The provider to be used.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_set_provider(geolocation_provider_t provider);

/**
 * @brief Set the location fix type
 *
 * The @c geolocation_set_fix_type() function sets the desired fix type to use
 * for geolocation information (see @c #geolocation_fix_type_t).  If you do not
 * set a fix type, the Best fix type is used by default.
 *
 * @param fix_type The fix type to be used.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_set_fix_type(geolocation_fix_type_t fix_type);

/**
 * @brief Set whether satellite information is reported without a
 *        geolocation fix
 *
 * The @c geolocation_set_report_satellite_info() function sets whether or not
 * satellite information is reported without a geolocation fix.
 *
 * @param report_satellite_info @c True indicates to report satellite information
 *                              without a geolocation fix, otherwise satellite
 *                              information will only be reported with a
 *                              geolocation fix.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_report_satellite_info(bool report_satellite_info);

/**
 * @brief Set the special application ID
 *
 * The @c geolocation_set_app_id() function sets the special application ID.  If
 * you don't know what this is, don't use it.
 *
 * @param app_id The special application ID.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_app_id(char * app_id);

/**
 * @brief Set the special application password
 *
 * The @c geolocation_set_app_password() function sets the special application
 * password.  If you don't know what this is, don't use it.
 *
 * @param app_password The special application password.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_app_password(char * app_password);

/**
 * @brief Set the PDE URL
 *
 * The @c geolocation_set_pde_url() function sets the PDE URL.  If you don't
 * know what this is, don't use it.
 *
 * @param pde_url The PDE URL.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_pde_url(char * pde_url);

/**
 * @brief Set the SLP URL
 *
 * The @c geolocation_set_slp_url() function sets the SLP URL.  If you don't
 * know what this is, don't use it.
 *
 * @param slp_url The SLP URL.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void geolocation_set_slp_url(char * slp_url);

/**
 * @brief Set whether the location request should be passive
 *
 * The @c geolocation_set_passive() function sets the passive flag in a location
 * request.  A passive request will receive fixes (as geolocation events) only
 * if there are one or more non-passive location requests being serviced on the
 * device.  This includes non-passive location requests made in other processes.
 *
 * @param passive The passive flag.  Set to @c true to set the passive flag on a
 * request; @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API void geolocation_set_passive(bool passive);

/**
 * @brief Set whether the location request should enable the stationary
 * filter
 *
 * The @c geolocation_set_stationary() function sets the stationary flag of a
 * location request, which uses the device's sensors to optimize power usage in
 * case the device's physical location is not changing.
 *
 * @param stationary The stationary flag.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API void geolocation_set_stationary(bool stationary);

/**
 * @brief Start receiving geolocation events
 *
 * The @c geolocation_request_events() function starts to deliver geolocation
 * change events to your application using BPS.  If the application does not
 * have the @c read_geolocation capability, this function will fail.  Events
 * are posted to the currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_request_events(int flags);

/**
 * @brief Stop receiving geolocation events
 * 
 * The @c geolocation_stop_events() function stops the delivery of geolocation
 * change events to your application.  If the application does not have the @c
 * read_geolocation capability, this function will fail.
 * 
 * @param flags The types of events to stop.  A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_stop_events(int flags);

/**
 * @brief Request a status update
 *
 * The @c geolocation_request_status() function requests a status notification
 * to be delivered to the application using BPS. If the application does not
 * have the @c read_geolocation capability, this function will fail.  Events are
 * posted to the currently active channel. You must call @c
 * geolocation_request_events() to receive status events.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int geolocation_request_status(void);

/**
 * @brief Retrieve the provider from a @c GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_get_provider() function extracts the provider from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the provider from.
 *
 * @return The provider. This is either a value from the @c
 * #geolocation_provider_t enumeration, or @c BPS_FAILURE if the event is not
 * valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_provider(bps_event_t * event);

/**
 * @brief Indicate whether the provider from a @c GEOLOCATION_INFO event is
 * valid
 * 
 * The @c geolocation_event_is_provider_valid() function indicates whether the
 * provider from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the provider validity
 *              from.
 *
 * @return @c true if the provider is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_provider_valid(bps_event_t * event);

/**
 * @brief Retrieve the fix type from a @c GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_get_fix_type() function extracts the fix type from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event that contains the fix type you
 * want to extract.
 *
 * @return The fix type. This is either a value from the @c
 * geolocation_fix_type_t enumeration, or @c BPS_FAILURE if the event is not
 * valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_fix_type(bps_event_t * event);

/**
 * @brief Indicate whether the fix type from a @c GEOLOCATION_INFO event is
 * valid
 * 
 * The @c geolocation_event_is_fix_type_valid() function indicates whether the
 * fix type from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event that contains the fix type whose
 * validity you want to determine.
 *
 * @return @c true if the fix type is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_fix_type_valid(bps_event_t * event);

/**
 * @brief Retrieve the latitude from a @c GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_get_latitude() function extracts the latitude from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the latitude from.
 *
 * @return The latitude (in degrees).  Positive values indicate north latitude
 * and negative values indicate south latitude.  Will be not-a-number (NaN) if
 * the value is not valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_latitude(bps_event_t * event);

/**
 * @brief Indicate whether the latitude from a @c GEOLOCATION_INFO event is
 * valid
 * 
 * The @c geolocation_event_is_latitude_valid() function indicates whether the
 * latitude from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the latitude validity
 *              from.
 *
 * @return @c true if the latitude is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_latitude_valid(bps_event_t * event);

/**
 * @brief Retrieve the longitude from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_longitude() function extracts the longitude from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the longitude from.
 *
 * @return The longitude (in degrees).  Positive values indicate east longitude
 * and negative values indicate west longitude.  Will be not-a-number (NaN) if
 * not valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_longitude(bps_event_t * event);

/**
 * @brief Indicate whether the longitude from a @c GEOLOCATION_INFO event is
 * valid
 * 
 * The @c geolocation_event_is_longitude_valid() function indicates whether the
 * longitude from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the longitude validity
 * from.
 *
 * @return @c true if the longitude is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_longitude_valid(bps_event_t * event);

/**
 * @brief Retrieve the accuracy of the latitude and longitude from a @c
 * GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_get_accuracy() function extracts the accuracy of the
 * latitude and longitude from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the accuracy from.
 *
 * @return The accuracy of the latitude and longitude (in meters).  Will be
 * not-a-number (NaN) if not valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_accuracy(bps_event_t * event);

/**
 * @brief Indicate whether the accuracy from a @c GEOLOCATION_INFO event is
 * valid
 * 
 * The @c geolocation_event_is_accuracy_valid() function indicates whether the
 * accuracy from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the accuracy validity
 *              from.
 *
 * @return @c true if the accuracy is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_accuracy_valid(bps_event_t * event);

/**
 * @brief Indicate whether the geolocation data is coarse from a @c
 * GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_is_coarse() function indicates whether the
 * geolocation data from the specified @c #GEOLOCATION_INFO event is coarse.
 * For example, Wi-Fi or cellular sites provide coarse data, while GPS or
 * GLONASS can provide coarse or fine data.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the coarse flag from.
 *
 * @return @c true if the geolocation data is coarse, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_coarse(bps_event_t * event);

/**
 * @brief Retrieve the altitude from a @c GEOLOCATION_EVENT event
 * 
 * The @c geolocation_event_get_altitude() function extracts the altitude from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the altitude from.
 *
 * @return The altitude (in meters) above Mean Sea Level.  Will be not-a-number
 * (NaN) if not valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_altitude(bps_event_t * event);

/**
 * @brief Indicate whether the altitude from a @c GEOLOCATION_INFO event is
 * valid
 * 
 * The @c geolocation_event_is_altitude_valid() function indicates whether the
 * altitude from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the altitude validity
 *              from.
 *
 * @return @c true if the altitude is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_altitude_valid(bps_event_t * event);

/**
 * @brief Retrieve the accuracy of the altitude from a @c GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_get_altitude_accuracy() function extracts the 
 * accuracy of the altitude from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the accuracy from.
 *
 * @return The accuracy of the altitude (in meters).  Will be not-a-number (NaN)
 * if not valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_altitude_accuracy(bps_event_t * event);

/**
 * @brief Indicate whether the altitude accuracy from a @c GEOLOCATION_INFO
 * event is valid
 * 
 * The @c geolocation_event_is_altitude_accuracy_valid() function indicates
 * whether the accuracy of the altitude from the specified @c #GEOLOCATION_INFO
 * event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the altitude accuracy
 * validity from.
 *
 * @return @c true if the altitude accuracy is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_altitude_accuracy_valid(bps_event_t * event);

/**
 * @brief Retrieve the heading from a @c GEOLOCATION_INFO event
 * 
 * The @c geolocation_event_get_heading() function extracts the heading from the
 * specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the heading from.
 *
 * @return The heading (in degrees).  Will be not-a-number (NaN) if not valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_heading(bps_event_t * event);

/**
 * @brief Indicate whether the heading from a @c GEOLOCATION_INFO event is
 * valid
 *
 * The @c geolocation_event_is_heading_valid() function indicates whether the
 * heading from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the heading validity from.
 *
 * @return @c true if the heading is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_heading_valid(bps_event_t * event);

/**
 * @brief Retrieve the speed from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_speed() function extracts the speed from the
 * specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the speed from.
 *
 * @return The speed (in meters per second).  Will be not-a-number (NaN) if not
 * valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_speed(bps_event_t * event);

/**
 * @brief Indicate whether the speed from a @c GEOLOCATION_EVENT event is valid
 *
 * The @c geolocation_event_is_speed_valid() function indicates whether the
 * speed from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the speed validity from.
 *
 * @return @c true if the speed is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_speed_valid(bps_event_t * event);

/**
 * @brief Retrieve the time to first fix (TTFF) from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_ttff() function extracts the time to first fix
 * from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the time to first fix
 * from.
 *
 * @return The time to first fix (in seconds).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_ttff(bps_event_t * event);

/**
 * @brief Indicate whether the time to first fix from a @c GEOLOCATION_INFO
 * event is valid
 *
 * The @c geolocation_event_is_ttff_valid() function indicates whether the time
 * to first fix from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the time to first fix
 * validity from.
 *
 * @return @c true if the time to first fix is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_ttff_valid(bps_event_t * event);

/**
 * @brief Retrieve the GPS week from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_gps_week() function extracts the GPS week from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the GPS week from.
 *
 * @return The GPS week (in weeks since the epoch).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_gps_week(bps_event_t * event);

/**
 * @brief Indicate whether the GPS week from a @c GEOLOCATION_INFO event is
 * valid
 *
 * The @c geolocation_event_is_gps_week_valid() function indicates whether the
 * GPS week from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the GPS week validity
 *              from.
 *
 * @return @c true if the GPS week is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_gps_week_valid(bps_event_t * event);

/**
 * @brief Retrieve the GPS time of week from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_gps_time_of_week() function extracts the GPS
 * time of week from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the GPS time of week
 * from.
 *
 * @return The GPS time of week (in milliseconds into the current week).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_gps_time_of_week(bps_event_t * event);

/**
 * @brief Indicate whether the GPS time of week from a @c GEOLOCATION_INFO event
 * is valid
 *
 * The @c geolocation_event_is_gps_time_of_week_valid() function indicates
 * whether the GPS time of week from the specified @c #GEOLOCATION_INFO event is
 * valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the GPS time of week
 * validity from.
 *
 * @return @c true if the GPS time of week is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_gps_time_of_week_valid(bps_event_t * event);

/**
 * @brief Retrieve the UTC from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_utc_time() function extracts the Coordinated
 * Universal Time (UTC) from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the UTC from.
 *
 * @return The UTC (in milliseconds since the epoch).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API long long geolocation_event_get_utc_time(bps_event_t * event);

/**
 * @brief Indicate whether the UTC from a @c GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_utc_time_valid() function indicates whether the
 * UTC from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the UTC validity from.
 *
 * @return @c true if the UTC is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_utc_time_valid(bps_event_t * event);

/** @brief Deprecated
 *
 *  @deprecated Use @c geolocation_event_get_num_satellites_used().
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_num_satellites(bps_event_t * event) BPS_DEPRECATED;

/**
 * @brief Retrieve the number of satellites that are used to determine the
 * device's geolocation from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_num_satellites_used() function extracts the
 * number of satellites that are used to determine the device's geolocation from
 * the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the number of
 * satellites from.
 *
 * @return The number of satellites that are used to determine the device's
 * geolocation.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_num_satellites_used(bps_event_t * event);

/**
 * @brief Retrieve the total number of satellites reported from a @c
 * GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_num_satellites_total() function extracts the
 * total number of satellites reported in the specified @c #GEOLOCATION_INFO
 * event. This function indicates the total number of satellites for which data
 * is available.  The @c satellite_index argument of the satellite functions
 * must be less that this number.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the total number of
 * satellites reported from.
 *
 * @return The total number of satellites reported.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_num_satellites_total(bps_event_t * event);

/**
 * @brief Indicate whether the number of satellites used and the total number of
 * satellites from a @c GEOLOCATION_INFO event are valid
 *
 * The @c geolocation_event_is_num_satellites_valid() function indicates whether
 * the number of satellites used and the total number of satellites from the
 * specified @c #GEOLOCATION_INFO event are valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the number of satellites
 * validity from.
 *
 * @return @c true if the number of satellites is valid, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_is_num_satellites_valid(bps_event_t * event);

/**
 * @brief Retrieve the ID (PRN) of the satellite at the specified index in the
 * @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_satellite_id() function extracts the ID (PRN) of
 * the satellite at the specified index in the @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite ID (PRN)
 * from.
 * @param satellite_index The index of the satellite to extract the satellite ID
 * (PRN) of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return The ID (PRN) of the satellite at the specified index.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_satellite_id(bps_event_t * event, int satellite_index);

/**
 * @brief Retrieve the carrier-to-noise ratio of the satellite at the specified
 * index in the @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_satellite_carrier_to_noise_ratio() function
 * extracts the carrier-to-noise ratio of the satellite at the specified index
 * in the @c #GEOLOCATION_INFO event. High carrier-to-noise ratios indicate good
 * quality of reception.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite
 * carrier-to-noise ratio from.
 * @param satellite_index The index of the satellite to extract the
 * carrier-to-noise ratio of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return The carrier-to-noise ratio of the satellite at the specified index
 * (in db/Hz).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_satellite_carrier_to_noise_ratio(bps_event_t * event, int satellite_index);

/**
 * @brief Indicate whether the ephemeris of the satellite at the specified index
 * in the @c GEOLOCATION_INFO event has been decoded
 *
 * The @c geolocation_event_get_satellite_is_ephemeris_decoded() function
 * extracts whether the ephemeris of the satellite at the specified index in the
 * @c #GEOLOCATION_INFO event has been decoded. The ephemeris of a satellite
 * provides precise orbit information for the satellite. A decoded ephemeris may
 * aid in the acquisition of future fixes.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite
 *              ephemeris decoded flag from.
 * @param satellite_index The index of the satellite to extract the ephemeris
 * decoded flag of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return @c true if the ephemeris of the satellite at the specified index has
 * been decoded, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_get_satellite_is_ephemeris_decoded(bps_event_t * event, int satellite_index);

/**
 * @brief Indicate whether the almanac of the satellite at the specified index
 * in the @c GEOLOCATION_INFO event has been decoded
 *
 * The @c geolocation_event_get_satellite_is_almanac_decoded() function extracts
 * whether the almanac of the satellite at the specified index in the @c
 * #GEOLOCATION_INFO event has been decoded. The almanac of a satellite provides
 * coarse orbit and status information for the satellite. A decoded almanac may
 * aid the acquisition of future fixes.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite almanac
 * decoded flag from.
 * @param satellite_index The index of the satellite to extract the almanac
 * decoded flag of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return @c true if the almanac of the satellite at the specified index has
 * been decoded, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_get_satellite_is_almanac_decoded(bps_event_t * event, int satellite_index);

/**
 * @brief Retrieve the azimuth angle of the satellite at the specified index in
 * the @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_satellite_azimuth() function extracts the
 * azimuth angle of the satellite at the specified index in the @c
 * #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite azimuth
 * angle from.
 * @param satellite_index The index of the satellite to extract the azimuth
 * angle of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return The azimuth angle of the satellite at the specified index (in
 * degrees).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_satellite_azimuth(bps_event_t * event, int satellite_index);

/**
 * @brief Retrieve the elevation angle of the satellite at the specified index 
 * in the @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_satellite_elevation() function extracts the
 * elevation angle of the satellite at the specified index in the @c
 * #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite
 * elevation angle from.
 * @param satellite_index The index of the satellite to extract the elevation
 * angle of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return The elevation angle of the satellite at the specified index (in
 * degrees).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API double geolocation_event_get_satellite_elevation(bps_event_t * event, int satellite_index);

/**
 * @brief Indicate whether the satellite at the specified index in the @c
 * GEOLOCATION_INFO event is tracked
 *
 * The @c geolocation_event_get_satellite_is_tracked() function indicates
 * whether the satellite at the specified index in the @c #GEOLOCATION_INFO
 * event is tracked.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite tracking
 *              flag from.
 * @param satellite_index The index of the satellite to extract the satellite
 * tracking flag of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return @c true if the satellite at the specified index is tracked, @c false
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_get_satellite_is_tracked(bps_event_t * event, int satellite_index);

/**
 * @brief Indicate whether the satellite at the specified index in the @c
 * GEOLOCATION_INFO event is used in the position solution
 *
 * The @c geolocation_event_get_satellite_is_used() function indicates whether
 * the satellite at the specified index in the @c #GEOLOCATION_INFO event is
 * used in the position solution.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the satellite usage
 * flag from.
 * @param satellite_index The index of the satellite to extract the satellite
 * usage flag of.  Must be in the range 0 to @c
 * geolocation_event_get_num_satellites() - 1.
 *
 * @return @c true if the satellite at the specified index is used in the
 * position solution, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool geolocation_event_get_satellite_is_used(bps_event_t * event, int satellite_index);

/**
 * @brief Retrieve the error message from a @c GEOLOCATION_ERROR event
 *
 * The @c geolocation_event_get_error_message() function gets the error message
 * from the specified @c #GEOLOCATION_ERROR event.  The error is with regards
 * to the previous geolocation request.
 *
 * @param event The @c #GEOLOCATION_ERROR event to get the error message from.
 *
 * @return The error message or @c NULL if there is no error message.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * geolocation_event_get_error_message(bps_event_t *event);

/**
 * @brief Retrieve the error code from a @c GEOLOCATION_ERROR event
 *
 * The @c geolocation_event_get_error_code() function gets the error code
 * from the specified @c #GEOLOCATION_ERROR event.  The error is with regards
 * to the previous geolocation request.
 *
 * @param event The @c #GEOLOCATION_ERROR event to get the error code from.
 *
 * @return The error code. This is either a value from the @c
 * #geolocation_error_t enumeration, or @c BPS_FAILURE if the event is not
 * valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int geolocation_event_get_error_code(bps_event_t *event);

/**
 * @brief Indicate whether the HDOP from a @c GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_hdop_valid() function indicates whether the HDOP
 * from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the HDOP validity from.
 *
 * @return @c true if the HDOP is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_hdop_valid(bps_event_t * event);

/**
 * @brief Retrieve the HDOP from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_hdop() function extracts the Horizontal Dilution
 * of Precision (HDOP) from the specified @c #GEOLOCATION_INFO event. HDOP is an
 * indication of the geometry of the satellites around the device, on the
 * horizontal axis.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the HDOP from.
 *
 * @return The HDOP.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_hdop(bps_event_t * event);

/**
 * @brief Indicate whether the VDOP from a @c GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_vdop_valid() function indicates whether the VDOP
 * from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the VDOP validity from.
 *
 * @return @c true if the VDOP is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_vdop_valid(bps_event_t * event);

/**
 * @brief Retrieve the VDOP from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_vdop() function extracts the Vertical Dilution
 * of Precision (VDOP) from the specified @c #GEOLOCATION_INFO event. VDOP is an
 * indication of the geometry of the satellites around the device, on the
 * vertical axis.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the VDOP from.
 *
 * @return The VDOP.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_vdop(bps_event_t * event);

/**
 * @brief Indicate whether the PDOP from a @c GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_pdop_valid() function indicates whether the PDOP
 * from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the PDOP validity from.
 *
 * @return @c true if the PDOP is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_pdop_valid(bps_event_t * event);

/**
 * @brief Retrieve the PDOP from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_pdop() function extracts the Positional Dilution
 * of Precision (PDOP) from the specified @c #GEOLOCATION_INFO event. PDOP is an
 * indication of the geometry of the satellites around the device. The PDOP
 * combines the effects of the HDOP and VDOP.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the PDOP from.
 *
 * @return The PDOP.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_pdop(bps_event_t * event);

/**
 * @brief Indicate whether the propagated flag from a @c GEOLOCATION_INFO event
 * is valid
 *
 * The @c geolocation_event_is_propagated_valid() function indicates whether the
 * propagated flag from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the propagated validity
 * from.
 *
 * @return @c true if the propagated flag is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_propagated_valid(bps_event_t * event);

/**
 * @brief Retrieve the propagated flag from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_propagated() function extracts the propagated
 * flag from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the propagated
 * flag from.
 *
 * @return The propagated flag.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_get_propagated(bps_event_t * event);

/**
 * @brief Indicate whether the geoid height from a @c GEOLOCATION_INFO
 * event is valid
 *
 * The @c geolocation_event_is_geoid_height_valid() function indicates whether
 * the geoid height from the specified @c #GEOLOCATION_INFO event is valid. The
 * geoid height is the difference between Mean Sea Level and the WGS84
 * ellipsoid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the geoid height validity
 * from.
 *
 * @return @c true if the geoid height is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_geoid_height_valid(bps_event_t * event);

/**
 * @brief Retrieve the geoid height from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_geoid_height() function extracts the geoid
 * height from the specified @c #GEOLOCATION_INFO event. The geoid height is the
 * difference between Mean Sea Level and the WGS84 ellipsoid.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the geoid height
 * from.
 *
 * @return The geoid height, in meters.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_geoid_height(bps_event_t * event);

/**
 * @brief Indicate whether the accuracy semi-major axis from a @c
 * GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_accuracy_semi_major_axis_valid() function
 * indicates whether the accuracy semi-major axis from the specified @c
 * #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the accuracy semi-major
 * axis validity from.
 *
 * @return @c true if the accuracy semi-major axis is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_accuracy_semi_major_axis_valid(bps_event_t * event);

/**
 * @brief Retrieve the accuracy semi-major axis from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_accuracy_semi_major() function extracts the
 * semi-major axis of the accuracy ellipse from the specified @c
 * #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the accuracy
 * semi-major axis from.
 *
 * @return The semi-major axis accuracy, in meters.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_accuracy_semi_major_axis(bps_event_t * event);

/**
 * @brief Indicate whether the accuracy semi-minor axis from a @c
 * GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_accuracy_semi_minor_axis_valid() function
 * indicates whether the accuracy semi-minor axis from the specified @c
 * #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the accuracy semi-minor
 * axis validity from.
 *
 * @return @c true if the accuracy semi-minor axis is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_accuracy_semi_minor_axis_valid(bps_event_t * event);

/**
 * @brief Retrieve the accuracy semi-minor axis from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_accuracy_semi_minor_axis() function extracts the
 * semi-minor axis of the accuracy ellipse from the specified @c
 * #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the accuracy
 * semi-minor axis from.
 *
 * @return The semi-minor axis accuracy, in meters.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_accuracy_semi_minor_axis(bps_event_t * event);

/**
 * @brief Indicate whether the accuracy rotation angle from a @c
 * GEOLOCATION_INFO event is valid
 *
 * The @c geolocation_event_is_accuracy_rotation_angle_valid() function
 * indicates whether the accuracy rotation angle from the specified @c
 * #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the accuracy rotation
 * angle validity from.
 *
 * @return @c true if the accuracy rotation angle is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_accuracy_rotation_angle_valid(bps_event_t * event);

/**
 * @brief Retrieve the accuracy rotation angle from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_accuracy_rotation_angle() function extracts the
 * rotation angle of the accuracy ellipse from the specified @c
 * #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the accuracy rotation
 * angle from.
 *
 * @return The accuracy rotation angle, in degrees, increasing clockwise from
 * North.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_accuracy_rotation_angle(bps_event_t * event);

/**
 * @brief Indicate whether the vertical speed from a @c GEOLOCATION_INFO event
 * is valid
 *
 * The @c geolocation_event_is_vertical_speed_valid() function indicates whether
 * the vertical speed from the specified @c #GEOLOCATION_INFO event is valid.
 *
 * @param event The @c #GEOLOCATION_INFO event to get the vertical speed
 * validity from.
 *
 * @return @c true if the vertical speed is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_vertical_speed_valid(bps_event_t * event);

/**
 * @brief Retrieve the vertical speed from a @c GEOLOCATION_INFO event
 *
 * The @c geolocation_event_get_vertical_speed() function extracts the vertical
 * speed from the specified @c #GEOLOCATION_INFO event.
 *
 * @param event The @c #GEOLOCATION_INFO event to extract the vertical speed
 * from.
 *
 * @return The vertical speed, in meters per second.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_vertical_speed(bps_event_t * event);

/**
 * @brief Indicate whether the active request from a @c GEOLOCATION_STATUS event
 * is valid
 * 
 * The @c geolocation_event_is_status_active_request_valid() function indicates
 * whether the active request from the specified @c #GEOLOCATION_STATUS event is
 * valid.
 *
 * @param event The @c #GEOLOCATION_STATUS event to get the active request
 * validity from.
 *
 * @return @c true if the active request is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_status_active_request_valid(bps_event_t * event);

/**
 * @brief Retrieve the active request status from a @c GEOLOCATION_STATUS event
 *
 * The @c geolocation_event_get_status_active_request() function extracts the
 * active request flag from the specified @c #GEOLOCATION_STATUS event. This
 * flag indicates that there is a request that has already been sent by this
 * client and that has not yet been cancelled (i.e., it's still active).
 *
 * @param event The @c #GEOLOCATION_STATUS event to extract the active request
 * from.
 *
 * @return The active request flag.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_get_status_active_request(bps_event_t * event);

/**
 * @brief Indicate whether the period from a @c GEOLOCATION_STATUS event is
 * valid
 * 
 * The @c geolocation_event_is_status_period_valid() function indicates whether
 * the period from the specified @c #GEOLOCATION_STATUS event is valid.
 *
 * @param event The @c #GEOLOCATION_STATUS event to get the period validity
 * from.
 *
 * @return @c true if the period is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_status_period_valid(bps_event_t * event);

/**
 * @brief Retrieve the period of the active request from a @c GEOLOCATION_STATUS
 * event
 *
 * The @c geolocation_event_get_status_period() function extracts the period
 * value from the specified @c #GEOLOCATION_STATUS event.
 *
 * @param event The @c #GEOLOCATION_STATUS event to extract the period from.
 *
 * @return The period, in seconds.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_status_period(bps_event_t * event);

/**
 * @brief Indicate whether the accuracy from a @c GEOLOCATION_STATUS event is
 * valid
 * 
 * The @c geolocation_event_is_status_accuracy_valid() function indicates
 * whether the accuracy from the specified @c #GEOLOCATION_STATUS event is
 * valid.
 *
 * @param event The @c #GEOLOCATION_STATUS event to get the accuracy validity
 * from.
 *
 * @return @c true if the accuracy is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_status_accuracy_valid(bps_event_t * event);

/**
 * @brief Retrieve the accuracy of the active request status from a @c
 * GEOLOCATION_STATUS event
 *
 * The @c geolocation_event_get_status_accuracy() function extracts the accuracy
 * value from the specified @c #GEOLOCATION_STATUS event.
 *
 * @param event The @c #GEOLOCATION_STATUS event to extract the period from.
 *
 * @return The accuracy, in meters.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_status_accuracy(bps_event_t * event);

/**
 * @brief Indicate whether the response time from a @c GEOLOCATION_STATUS event
 * is valid
 * 
 * The @c geolocation_event_is_status_response_time_valid() function indicates
 * whether the response time from the specified @c #GEOLOCATION_STATUS event is
 * valid.
 *
 * @param event The @c #GEOLOCATION_STATUS event to get the response time
 * validity from.
 *
 * @return @c true if the response time is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_status_response_time_valid(bps_event_t * event);

/**
 * @brief Retrieve the response_time of the active request from a @c
 * GEOLOCATION_STATUS event
 *
 * The @c geolocation_event_get_status_response_time() function extracts the
 * response time value from the specified @c #GEOLOCATION_STATUS event.
 *
 * @param event The @c #GEOLOCATION_STATUS event to extract the response_time
 * from.
 *
 * @return The response time, in seconds.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API double geolocation_event_get_status_response_time(bps_event_t * event);

/**
 * @brief Indicate whether the passive flag from a @c GEOLOCATION_STATUS event
 * is valid
 * 
 * The @c geolocation_event_is_passive_valid() function indicates whether the
 * passive flag from the specified @c #GEOLOCATION_STATUS event is valid.
 *
 * @param event The @c #GEOLOCATION_STATUS event to get the passive flag
 * validity from.
 *
 * @return @c true if the passive flag is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_status_passive_valid(bps_event_t * event);

/**
 * @brief Retrieve the passive flag of the active request from a @c
 * GEOLOCATION_STATUS event
 *
 * The @c geolocation_event_get_status_passive() function extracts the passive
 * flag value from the specified @c #GEOLOCATION_STATUS event.
 *
 * @param event The @c #GEOLOCATION_STATUS event to extract the passive flag
 * from.
 *
 * @return The passive flag.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_get_status_passive(bps_event_t * event);

/**
 * @brief Indicate whether the background flag from a @c GEOLOCATION_STATUS
 * event is valid
 * 
 * The @c geolocation_event_is_status_background_valid() function indicates
 * whether the background flag from the specified @c #GEOLOCATION_STATUS event
 * is valid.
 *
 * @param event The @c #GEOLOCATION_STATUS event to get the background flag
 * validity from.
 *
 * @return @c true if the background flag is valid, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_is_status_background_valid(bps_event_t * event);

/**
 * @brief Retrieve the background flag of the active request from a @c
 * GEOLOCATION_STATUS event
 *
 * The @c geolocation_event_get_status_background() function extracts the
 * background flag value from the specified @c #GEOLOCATION_STATUS event.
 *
 * @param event The @c #GEOLOCATION_STATUS event to extract the background flag
 * from.
 *
 * @return The background flag.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool geolocation_event_get_status_background(bps_event_t * event);

__END_DECLS

#endif // include guard
