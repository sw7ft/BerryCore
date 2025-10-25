/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEO_CONVERTERS_HPP
#define BB_PLATFORM_GEO_GEO_CONVERTERS_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/GeoList>

#include <QtLocationSubset/QGeoCoordinate>
#include <QtLocationSubset/QGeoAddress>
#include <QtLocationSubset/QGeoPlace>
#include <QtLocationSubset/QGeoPositionInfo>

/** @headerfile geo_converters.hpp <bb/cascades/maps/geo_converters>
 *
 * @since BlackBerry 10.0.0
 */

namespace QtMobilitySubset
{
class QGeoSearchReply;
}

namespace bb
{
namespace platform
{
namespace geo
{
class GeoLocation;

/**
 * @brief Converts an address in the form of a @c QGeoAddress into a string.
 *
 * @param src The address to be converted.
 * @return A single-string representation of the parameter.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT QString convertToString( const QtMobilitySubset::QGeoAddress& src );

/**
 * @brief Converts a geographical position in the form of a @c QGeoCoordinate
 * into a @c Point.
 *
 * @param src The coordinate to be converted.
 * @return A @c Point representation (latitude and longitude coordinates)
 * of the parameter.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT bb::platform::geo::Point convertToPoint( const
        QtMobilitySubset::QGeoCoordinate& src );

/**
 * @brief Converts a @c Point into a Qt coordinate (@c QGeoCoordinate).
 *
 * @param src The point to be converted.
 * @return A @c QGeoCoordinate representation of the parameter.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT QtMobilitySubset::QGeoCoordinate convertToQGeoCoordinate(
    const bb::platform::geo::Point& src );

/**
 * @brief Converts a Qt position in the form of a @c QGeoPositionInfo into a
 * @c Point.
 *
 * @param src The coordinate to be converted.
 * @return A @c Point representation (latitude and longitude coordinates)
 * of the parameter.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT bb::platform::geo::Point convertToPoint( const
        QtMobilitySubset::QGeoPositionInfo& src );

/**
 * @brief Converts a Qt place in the form of a @c QGeoPlace into a location
 * (@c GeoLocation).
 *
 * Object Ownership: It is the client's responsibility to free
 * the memory of the returned parameter.
 *
 * @param src The place to be converted.
 * @return A @c GeoLocation representation of the parameter.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT bb::platform::geo::GeoLocation* convertToGeoLocation(
    const QtMobilitySubset::QGeoPlace& src );

/**
 * @brief Converts a collection of Qt places in the form of @c QGeoPlace into a
 * collection of locations (@c GeoList).
 *
 * Object Ownership: It is the client's responsibility to free
 * the memory of the @c GeoLocation objects contained in the returned
 * list.
 *
 * @param src The collection of places to be converted.
 * @return A @c GeoList representation of the parameter.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT bb::platform::geo::GeoList convertToGeoList( const
        QList<QtMobilitySubset::QGeoPlace> src );

/**
 * @brief Converts a Qt search result in the form of a @c QGeoSearchReply into a
 * collection of locations (@c GeoList).
 *
 * Object Ownership: It is the client's responsibility to free
 * the memory of the @c GeoLocation objects contained in the returned
 * list.
 *
 * @param src The search result to be converted.
 * @return A @c GeoList representation of the results.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_PLATFORM_GEO_EXPORT bb::platform::geo::GeoList convertToGeoList( const
        QtMobilitySubset::QGeoSearchReply* src );


} // namespace geo
} // namespace platform
} // namespace bb

#endif /* BB_PLATFORM_GEO_GEO_CONVERTERS_HPP */
