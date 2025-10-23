/*
 * Copyright Research In Motion Limited, 2012-2013.
 * Research In Motion Limited. All rights reserved.
 */

#pragma once
/**
 * @file    geo_search.h
 * @brief   A library for the geocoding and reverse geocoding service
 *
 * @details The geocoding library provides functionality to determine a
 * geographic coordinate given a location (geocoding), and conversely, to
 * determine a location given a geographic coordinate (reverse geocoding).
 * Location here can mean a specific street address, a city, or a country, and
 * so on. A geographic coordinate is specified by a latitude and longitude,
 * relative to the WGS84 datum.
 *
 * For both geocoding and reverse geocoding searches, the location results are
 * provided in a reply. A reply consists of a list of one or more location
 * results. A location result contains the following fields:
 * - name
 * - latitude
 * - longitude
 * - description
 * - street
 * - city
 * - county
 * - region
 * - district
 * - country
 * - postal code
 * - time zone
 * - mobile country code
 * - ISO alpha-2 country code
 * - ISO alpha-3 country code
 * - ISO country id
 *
 * Depending on the search and the geographic location of the result, some of
 * the result fields may be empty. As well, depending on the geographic
 * location, the formatting, interpretation, and even language of the fields may
 * vary.
 *
 * Successful use of these functions requires a Wi-Fi or cellular network data
 * connection. Search operations are free, although each call of the geocoding
 * and reverse geocoding functions may incur network access (and possible data
 * charges). Searches are carried out by a remote server.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A handle to the geo_search service
 *
 * This handle is provided when the geo_search service is opened and is a
 * required parameter for calling geocoding and reverse geocoding functions.
 */
typedef struct _geo_search_handle_t *geo_search_handle_t;

/**
 * @brief A handle to a geo_search reply
 *
 * This handle is returned by the geocoding and reverse geocoding functions. It
 * provides access to the search results.
 */
typedef struct _geo_search_reply_t *geo_search_reply_t;

/**
 * @brief The boundary defines the level of specificity desired for a
 * reverse geocoding search
 *
 * For reverse geocoding, the desired location may be the nearest street
 * address or simply the city within which the geographic coordinate lies.
 * Use the boundary to indicate this level of specificity.
 *
 * Note that for less specific boundaries, such as city and country, the
 * search results may be cached. This means that network access may not be
 * required for subsequent reverse geocoding searches, for neighbouring
 * geographic coordinates.
 */
typedef enum {
    /**
     * Represents an invalid search boundary. It is applicable only for
     * @c geo_search_boundary_next() and @c geo_search_boundary_valid().
     */
    GEO_SEARCH_BOUNDARY_NONE = 0,

    /**
     * Specifies that the address nearest to the geographic point is to be
     * searched for.
     */
    GEO_SEARCH_BOUNDARY_ADDRESS = 1,

    /**
     * Specifies that the country containing the geographic point is to be
     * searched for.
     */
    GEO_SEARCH_BOUNDARY_COUNTRY = 2,

    /**
     * Specifies that the state or province containing the geographic point is
     * to be searched for.
     */
    GEO_SEARCH_BOUNDARY_PROVINCE = 3,

    /**
     * Specifies that the city containing the geographic point is to be
     * searched for.
     */
    GEO_SEARCH_BOUNDARY_CITY = 4,

    /**
     * Specifies that the postal code corresponding to the geographic point is
     * to be searched for.
     */
    GEO_SEARCH_BOUNDARY_POSTAL = 5,

    /**
     * Specifies that the mobile country code coresponding to the geographic
     * point is to be searched for.
     */
    GEO_SEARCH_BOUNDARY_MCC = 6,

    /**
     * Specifies that the time zone coresponding to the geographic
     * point is to be searched for.
     */
    GEO_SEARCH_BOUNDARY_TIMEZONE = 7,
} geo_search_boundary_t;

/**
 * @brief The geo_search error codes provide information on search status
 *
 * This enumeration defines the errors that are supported by this API.
 */
typedef enum {
    /**
     * The search or other operation completed successfully.
     */
    GEO_SEARCH_OK = 0,

    /**
     * Invalid parameters were passed to a geo_search function.
     */
    GEO_SEARCH_ERROR_INPUT = 1,

    /**
     * Error occurred while opening the geo_search service.
     */
    GEO_SEARCH_ERROR_SERVER_OPEN = 0x1000,

    /**
     * The remote server rejected the search request.
     */
    GEO_SEARCH_ERROR_SERVER_INVALID_REQUEST = 0x1001,

    /**
     * The remote server returned an invalid response.
     */
    GEO_SEARCH_ERROR_SERVER_RESPONSE = 0x1002,

    /**
     * The remote server returned empty data.
     */
    GEO_SEARCH_ERROR_SERVER_EMPTY = 0x1003,

    /**
     * An error occurred  with the reply.
     */
    GEO_SEARCH_ERROR_REPLY = 0x2000,
} geo_search_error_t;

/**
 * @brief Return the printable error string corresponding to the supplied error
 * code
 *
 * @param [in] error A valid error code.
 *
 * @return A printable error string.  If @c error is not valid, an "Unknown"
 *         type string is returned.
 *
 */
const char *geo_search_strerror(geo_search_error_t error);

/**
 * @brief Open the geo_search service
 *
 * Opens the geo_search service and provides the corresponding handle.
 * Any number of geocode and reverse geocode searches can be made using
 * this handle.
 *
 * You can open the geo_search service and check for errors as follows:
 * @code
 * geo_search_handle_t handle;
 * geo_search_error_t error = geo_search_open( &handle );
 * if ( error == GEO_SEARCH_OK ) {
 *     // do searches
 *
 *     // only need to call if geo_search_open() succeeded.
 *     geo_search_close( &handle );
 * }
 * @endcode
 *
 * @param [out] handle A geo_search handle
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns one of the
 * @c GEO_SEARCH_ERROR_SERVER_* values.
 */
geo_search_error_t geo_search_open(geo_search_handle_t *handle);

/**
 * @brief Close the geo_search service
 *
 * Closes the geo_search service and frees resources associated with the
 * handle. Note that any geo_search replies are not freed - see
 * @c geo_search_free_reply().
 *
 * The following shows when to use @c geo_search_close():
 * @code
 * geo_search_handle_t handle;
 * geo_search_error_t error = geo_search_open( &handle );
 * if ( error == GEO_SEARCH_OK ) {
 *     // do searches
 *
 *     // only need to call if geo_search_open() succeeded.
 *     geo_search_close( &handle );
 * }
 * @endcode
 *
 * @param [in] handle A valid geo_search handle.
 */
void geo_search_close(geo_search_handle_t *handle);

/**
 * @brief Free any resources associated with a geo_search reply
 *
 * Calling a geocoding or reverse geocoding function provides a
 * geo_search reply. When done with the reply @c geo_search_free_reply()
 * must be called to free it.
 *
 * @param [in] reply The reply to free.
 */
void geo_search_free_reply(geo_search_reply_t *reply);

/**
 * @brief Perform a geocode search
 *
 * Given a free form string specifying a location, this function provides a
 * reply containing one or more matching results. If the location specified is a
 * complete street address the reply may contain only one result. If the
 * location given is less specific (e.g. "Springfield") then there may be
 * multiple results in the reply. Note that searching for local or obscure
 * names may provide no results at all (this function returns
 * @c #GEO_SEARCH_ERROR_SERVER_EMPTY). In such cases it may help to provide
 * a geographic coordinate (latitude, longitude) as a hint using
 * @c geo_search_geocode_latlon() instead.
 *
 * Note that this function may make a network request and blocks until the
 * remote server responds.
 *
 * The following shows how to perform a geocode search:
 * @code
 * geo_search_handle_t handle;
 * geo_search_error_t error = geo_search_open( &handle );
 * if ( error == GEO_SEARCH_OK ) {
 *     geo_search_reply_t reply;
 *     const char *search_string = "Springfield";
 *
 *     error = geo_search_geocode(&handle, &reply, search_string);
 *     if ( error == GEO_SEARCH_OK ) {
 *         // do something with the results in the search reply
 *
 *         geo_search_free_reply( &reply );
 *     }
 *     geo_search_close( &handle );
 * }
 * @endcode
 *
 * See @c geo_search_reply_get_name() for an example of how to access the
 * results in a search reply.
 *
 * @param [in] handle A geo_search handle.
 * @param [out] reply A reply handle.
 * @param [in] search_string A null-terminated free format search string
 *                           (UTF-8).
 *
 * @return @c #GEO_SEARCH_OK if successful, otherwise one of the values from
 *         @c #geo_search_error_t.
 */
geo_search_error_t geo_search_geocode(geo_search_handle_t *handle, geo_search_reply_t *reply, const char *search_string);

/**
 * @brief Perform a geocode search near a geographic coordinate
 *
 * Given a free form string specifying a location and a geographic coordinate,
 * this function provides a reply containing one or more matching results. If
 * the location specified is a complete street address, the reply may contain
 * only one result. If the location given is less specific (e.g. "Springfield"),
 * then there may be multiple results in the reply. The results will be sorted
 * in order of proximity to the specified geographic coordinate. Note that even
 * with a geographic coordinate provided as a hint, it is still possible that no
 * results are found (this function returns @c #GEO_SEARCH_ERROR_SERVER_EMPTY).
 *
 * Note that this function may make a network request and will block until the
 * remote server responds.
 *
 * The following shows how to perform a geocode search near a geographic
 * coordinate:
 * @code
 * geo_search_handle_t handle;
 * geo_search_error_t error = geo_search_open( &handle );
 * if ( error == GEO_SEARCH_OK ) {
 *   geo_search_reply_t reply;
 *   const char *search_string = "Springfield";
 *   double lat = 39.8017;
 *   double lon = -89.6436;
 *
 *   error = geo_search_geocode_latlon(&handle, 
 *                                     &reply,
 *                                     search_string,
 *                                     lat,
 *                                     lon);
 *   if ( error == GEO_SEARCH_OK ) {
 *     // do something with the results in the search reply
 *
 *     geo_search_free_reply( &reply );
 *   }
 *   geo_search_close( &handle );
 * }
 * @endcode
 *
 * See @c geo_search_reply_get_name() for an example of how to access the
 * results in a search reply.
 *
 * @param [in] handle A geo_search handle.
 * @param [out] reply A reply handle.
 * @param [in] search_string A null-terminated free format search string (UTF-8).
 * @param [in] lat Latitude in decimal degrees of the geographic coordinate to
 *                 search near. This must be specified using the WGS84 datum.
 * @param [in] lon Longitude in decimal degrees of the geographic coordinate to
 *                 search near. This must be specified using the WGS84 datum.
 *
 * @return @c #GEO_SEARCH_OK if successful, otherwise one of the values from
 *         @c #geo_search_error_t.
 */
geo_search_error_t geo_search_geocode_latlon(geo_search_handle_t *handle, geo_search_reply_t *reply, const char *search_string, double lat, double lon);

/**
 * @brief Perform a reverse geocode search
 *
 * Given a geographic coordinate and boundary type this function provides a
 * reply containing one or more matching results. It is possible that no result
 * may be found, in which case this function returns @c
 * #GEO_SEARCH_ERROR_SERVER_EMPTY.
 *
 * To access the search result see the @c geo_search_reply_* functions. Note
 * that depending on the search boundary specified the fields in the search
 * result may not all be populated. For example if @c #GEO_SEARCH_BOUNDARY_CITY
 * is specified only the city and country fields may have values that are not
 * empty.
 *
 * Note that this function may make a network request and blocks until the
 * remote server responds.
 *
 * The following shows how to perform a reverse geocode search:
 * @code
 * geo_search_handle_t handle;
 * geo_search_error_t error = geo_search_open( &handle );
 * if ( error == GEO_SEARCH_OK ) {
 *   geo_search_reply_t reply;
 *   double lat = 39.8017;
 *   double lon = -89.6436;
 *
 *   error = geo_search_reverse_geocode(&handle,
 *                                      &reply,
 *                                      lat,
 *                                      lon,
 *                                      GEO_SEARCH_BOUNDARY_CITY);
 *   if ( error == GEO_SEARCH_OK ) {
 *     // do something with the results in the search reply
 *
 *     geo_search_free_reply( &reply );
 *   }
 *   geo_search_close( &handle );
 * }
 * @endcode
 *
 * See @c geo_search_reply_get_name() for an example of how to access the
 * results in a search reply.
 *
 * @param [in]  handle    A geo_search handle.
 * @param [out] reply     A reply handle.
 * @param [in]  lat       Latitude in decimal degrees of the geographic
 *                        coordinate to determine the location of. This must be
 *                        specified using the WGS84 datum.
 * @param [in]  lon       Longitude in decimal degrees of the geographic
 *                        coordinate to determine the location of. This must be
 *                        specified using the WGS84 datum.
 * @param [in]  boundary  The level of specificity according to
 *                        @c #geo_search_boundary_t.
 *
 * @return @c #GEO_SEARCH_OK if successful, otherwise one of the values from
 *         @c #geo_search_error_t.
 */
geo_search_error_t geo_search_reverse_geocode(geo_search_handle_t *handle, geo_search_reply_t *reply, double lat, double lon, geo_search_boundary_t boundary);

/**
 * @brief Return the next search boundary
 *
 * This function is provided as a convenience for cycling through the possible
 * search boundaries. The following is an example of using this function:
 *
 * @code
 *
 *      for (boundary = geo_search_boundary_next(GEO_SEARCH_BOUNDARY_NONE); geo_search_boundary_valid(boundary); boundary = geo_search_boundary_next(boundary) ) {
 *          printf("geo_search_reverse_geocode() using boundary %s...\n", geo_search_boundary_name(boundary));
 *      }
 *
 * @endcode
 *
 * @param [in] current Specifies the current boundary from which the next
 *                     boundary is determined.  Use @c #GEO_SEARCH_BOUNDARY_NONE
 *                     the first time you call this function.
 *
 * @return The next search boundary.
 */
geo_search_boundary_t geo_search_boundary_next(geo_search_boundary_t current);

/**
 * @brief Check whether the specified search boundary is valid
 *
 * A boundary is valid if it is one of the values from @c
 * #geo_search_boundary_t.
 *
 * This is a convenience function intended for use with @c
 * geo_search_boundary_next().
 *
 * @param [in] boundary The boundary to check.
 *
 * @return @c #GEO_SEARCH_BOUNDARY_NONE if not valid, a valid search boundary
 * otherwise.
 *
 */
int geo_search_boundary_valid(geo_search_boundary_t boundary);

/** @cond internal
 */

/**
 * @brief Get the printable name of a given search boundary
 *
 * This is a convenience function for working with search boundaries.
 *
 * This function is currently for internal use only, pending localization.
 *
 * @param [in] boundary The search boundary.
 *
 * @return The printable string of the search boundary.
 *
 */
const char *geo_search_boundary_name(geo_search_boundary_t boundary);

/** @endcond
 */

/**
 * @brief Get the number of results in the search reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] length The number of results in the reply.
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_length(const geo_search_reply_t *reply, int *length);

/**
 * @brief Set the index of the current result in the reply
 *
 * Results in the reply can be accessed by array index. Use this function to
 * set the result index from which the various @c geo_search_reply_get
 * functions provide data for.
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [in] index The result index to be set current. This must be
 * between 0 and @c length-1 inclusively, where @c length is
 * provided by @c geo_search_reply_get_length().
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_set_index(geo_search_reply_t *reply, int index);

/* Note: code samples in the following documentation has been adjusted to fit
 * the margins of html output; please do not re-align.                        */
/**
 * @brief Retrieve the location name of the result at the current index in the
 * reply
 *
 * The name can be that of a business or venue, or the full address. It is also
 * valid for @c name to be empty, if a name is not applicable for the resultant
 * location.
 *
 * The following example shows how @c geo_search_reply_get_name(), as well as
 * the other @c geo_search_reply_* functions, can be used as follows:
 * @code
 *
 *  int n;
 *
 *  if (GEO_SEARCH_OK != geo_search_reply_get_length(&reply, &n)) {
 *    n = 0;
 *  }
 *
 *  printf("** %d entries in reply\n", n);
 *
 *  int i;
 *  for (i=0; i < n; i++) {
 *    if (!geo_search_reply_set_index(&reply, i))
 *      break;
 *
 *    if (i) {
 *      printf("\n");
 *    }
 *
 *    const char *value = NULL;
 *    if (GEO_SEARCH_OK == geo_search_reply_get_name(&reply, &value)) {
 *      printf("\tname: %s\n", value);
 *    }
 *
 *    double lat;
 *    if (GEO_SEARCH_OK == geo_search_reply_get_lat(&reply, &lat)) {
 *      printf("\tlat: %.6f\n", lat);
 *    }
 *
 *    double lon;
 *    if (GEO_SEARCH_OK == geo_search_reply_get_lon(&reply, &lon)) {
 *      printf("\tlon: %.6f\n", lon);
 *    }
 *
 *    if (GEO_SEARCH_OK == 
 *            geo_search_reply_get_description(&reply, &value)) {
 *      printf("\tdescription: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK == geo_search_reply_get_street(&reply,
 *                                                     &value)) {
 *      printf("\tstreet: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK == geo_search_reply_get_city(&reply, &value)) {
 *      printf("\tcity: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK == geo_search_reply_get_region(&reply,
 *                                                     &value)) {
 *      printf("\tregion: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK == 
 *            geo_search_reply_get_county(&reply, &value)) {
 *      printf("\tcounty: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK ==
 *            geo_search_reply_get_district(&reply, &value)) {
 *      printf("\tdistrict: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK == 
 *            geo_search_reply_get_country(&reply, &value)) {
 *      printf("\tcountry: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK ==
 *            geo_search_reply_get_postal_code(&reply, &value)) {
 *      printf("\tpostal_code: %s\n", value);
 *    }
 *
 *    int mcc;
 *    if (GEO_SEARCH_OK == geo_search_reply_get_mcc(&reply, &mcc)) {
 *      printf("\tmcc: %d\n", mcc);
 *    }
 *
 *    if (GEO_SEARCH_OK ==
 *            geo_search_reply_get_timezone(&reply, &value)) {
 *      printf("\ttimezone: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK ==
 *        geo_search_reply_get_iso_alpha2_country_code(&reply,
 *                                                     &value)) {
 *      printf("\tiso2_country_code: %s\n", value);
 *    }
 *
 *    if (GEO_SEARCH_OK ==
 *            geo_search_reply_get_iso_alpha3_country_code(&reply,
 *                                                         &value)) {
 *      printf("\tiso3_country_code: %s\n", value);
 *    }
 *
 *    int id;
 *    if (GEO_SEARCH_OK == geo_search_reply_get_iso_country_id(&reply,
 *                                                             &id)) {
 *      printf("\tiso_country_id: %d\n", id);
 *    }
 *  }
 * @endcode
 *
 * @param [in] reply The search reply.
 * @param [out] name The resultant location name (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 *         #GEO_SEARCH_ERROR_REPLY.
 */
geo_search_error_t geo_search_reply_get_name(const geo_search_reply_t *reply, const char **name);

/**
 * @brief Retrieve the latitude of the result at the current index in the reply
 *
 * The latitude is given in decimal degrees, within the range of -90.0 to +90.0.
 * For a reverse geocode search the resultant latitude may be the same as the
 * search latitude.
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] lat The resultant latitude, relative to the WGS84 datum.
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_lat(geo_search_reply_t *reply, double *lat);

/**
 * @brief Retrieve the longitude of the result at the current index in the
 *        reply
 *
 * The longitude is given in decimal degrees, within the range of -180.0 to
 * +180.0.
 * For a reverse geocode search the resultant longitude may be the same as the
 * search longitude.
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] lon The resultant longitude, relative to the WGS84 datum.
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_lon(geo_search_reply_t *reply, double *lon);

/**
 * @brief Retrieve the location description of the result at the current index
 * in the reply
 *
 * The description may contain ancillary information relevant to the location.
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] description The resultant description (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_description(geo_search_reply_t *reply, const char **description);

/**
 * @brief Retrieve the street field of the result at the current index in the
 * reply
 *
 * The street field typically contains street address information including
 * number, name, and a modifier such as street, road, or avenue.
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] street The resultant street information (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_street(geo_search_reply_t *reply, const char **street);

/**
 * @brief Retrieve the city of the result at the current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] city The resultant city (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_city(geo_search_reply_t *reply, const char **city);

/**
 * @brief Retrieve the region (state or province) of the result at the
 * current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] region The resultant state or province (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_region(geo_search_reply_t *reply, const char **region);

/**
 * @brief Retrieve the county of the result at the current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] county The resultant county (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_county(geo_search_reply_t *reply, const char **county);

/**
 * @brief Retrieve the district of the result at the current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] district The resultant district (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_district(geo_search_reply_t *reply, const char **district);

/**
 * @brief Retrieve the country of the result at the current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * Some examples of country names that are returned are: USA, Canada, and South
 * Africa.
 *
 * @param [in] reply The search reply.
 * @param [out] country The resultant country (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_country(geo_search_reply_t *reply, const char **country);

/**
 * @brief Retrieve the postal (or zip) code of the result at the current index
 * in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] postal The resultant postal code (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_postal_code(geo_search_reply_t *reply, const char **postal);

/**
 * @brief Retrieve the mobile country code of the result at the current index
 * in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] mcc The resultant mobile country code.
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_mcc(geo_search_reply_t *reply, int *mcc);

/**
 * @brief Retrieve the time zone of the result at the current index in the
 * reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] timezone The resultant time zone (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_timezone(geo_search_reply_t *reply, const char **timezone);

/**
 * @brief Retrieve the ISO 3166-1 alpha-2 country code of the result at the
 * current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] iso2_country_code The resultant two character ISO 3166-1
 * alpha-2 country code (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_iso_alpha2_country_code(geo_search_reply_t *reply, const char **iso2_country_code);

/**
 * @brief Retrieve the ISO 3166-1 alpha-3 country code of the result at the
 * current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] iso3_country_code The resultant three character ISO 3166-1
 * alpha-3 country code (UTF-8 string).
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_iso_alpha3_country_code(geo_search_reply_t *reply, const char **iso3_country_code);

/**
 * @brief Retrieve the ISO 3166-1 country numeric id of the result at the
 * current index in the reply
 *
 * See @c geo_search_reply_get_name() for an example of usage.
 *
 * @param [in] reply The search reply.
 * @param [out] iso_country_id The resultant ISO 3166-1 country numeric id.
 *
 * @return @c #GEO_SEARCH_OK if successful. On error, returns @c
 * #GEO_SEARCH_ERROR_REPLY.
 *
 */
geo_search_error_t geo_search_reply_get_iso_country_id(geo_search_reply_t *reply, int *iso_country_id);

#ifdef __cplusplus
}
#endif
