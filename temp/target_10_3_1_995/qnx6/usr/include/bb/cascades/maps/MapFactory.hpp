/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPFACTORY_HPP
#define BB_CASCADES_MAPS_MAPFACTORY_HPP

#include <bb/cascades/maps/Global>
#include <bb/cascades/maps/MapImageGenerator>
#include <bb/cascades/maps/ViewProperties>
#include <bb/platform/geo/GeoList>
#include <bb/ImageData>

#include <QMap>

/** @headerfile MapFactory.hpp <bb/cascades/maps/MapFactory> */

namespace bb
{
namespace cascades
{
namespace maps
{

/** @cond PRIVATE */
/**
 * @deprecated Use @c MapImageGenerator.
 */
BB_CASCADES_MAPS_EXPORT bb::ImageData generateMapImage( const bb::cascades::maps::ViewProperties&
        viewProperties );

/**
 * @deprecated Use @c MapImageGenerator.
 */
BB_CASCADES_MAPS_EXPORT bb::ImageData generateStaticMapImage( const
        bb::cascades::maps::ViewProperties&
        viewProperties );

/**
 * @deprecated Use @c MapImageGenerator.
 */
BB_CASCADES_MAPS_EXPORT bb::ImageData generateMapImage( const bb::cascades::maps::ViewProperties&
        viewProperties, const bb::platform::geo::GeoList& data );

/**
 * @deprecated Use @c MapImageGenerator.
 */
BB_CASCADES_MAPS_EXPORT bb::ImageData generateStaticMapImage( const
        bb::cascades::maps::ViewProperties&
        viewProperties, const bb::platform::geo::GeoList& data );
/** @endcond */

/**
 * @brief Generates a URL encapsulating the map defined by the given
 * @c ViewProperties.
 *
 * @param viewProperties The @c ViewProperties describing the area to
 * encode in the URL.
 * @param label The label of the location in the center of the map,
 * or an empty string for no label.
 * @return The URL.
 *
 * @since BlackBerry 10.0.0
 */
BB_CASCADES_MAPS_EXPORT QString generateMapUrl(
    const bb::cascades::maps::ViewProperties& viewProperties,
    const QString& label );

/**
 * @brief Generates a URL encapsulating the map defined by the given
 * @c ViewProperties and optional key/value pairs of location data.
 *
 * Valid keys are:
 *
 * - @c label The label of the location.
 * - @c desc The description of the location.
 * - @c address The street address of the location.
 * - @c city The city of the location.
 * - @c region The region of the location (state, province, and so on).
 * - @c country The country of the location.
 * - @c postalCode The postal code/ZIP code of the location.
 * - @c phone The phone number of the location.
 * - @c fax The fax number of the location.
 * - @c url URL of the location.
 * - @c email Email address of the location.
 *
 * @param viewProperties The @c ViewProperties describing the area to
 * encode in the URL.
 * @param queryStringValues Query string key/value pairs of location data.
 * @return The URL.
 *
 * @since BlackBerry 10.2.0
 */
BB_CASCADES_MAPS_EXPORT QString generateMapUrl(
    const bb::cascades::maps::ViewProperties& viewProperties,
    const QMap< QString, QString >& queryStringValues );

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPFACTORY_HPP */
