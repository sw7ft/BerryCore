/*!
 * @copyright
 * Copyright BlackBerry Limited, 2014-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPCOVERAGECHECKER_HPP
#define BB_CASCADES_MAPS_MAPCOVERAGECHECKER_HPP

#include <bb/cascades/maps/ViewProperties>

#include <QStringList>

namespace bb
{
namespace cascades
{
namespace maps
{

/**
 * @headerfile MapCoverageChecker.hpp <bb/cascades/maps/MapCoverageChecker>
 *
 * @brief A collection of functions for determining if map coverage is available in
 * @c MapView.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 * @since BlackBerry 10.3.0
 */
class MapCoverageChecker
{
public:
    /**
     * @brief Checks if map coverage is available from any @c RenderEngine for
     * the given @c ViewProperties.
     *
     * @param viewProperties The @c ViewProperties describing the area to check.
     * @return @c true if map coverage is available for the given area, @c false otherwise.
     * @since BlackBerry 10.3.0
     */
    BB_CASCADES_MAPS_EXPORT static bool isCoverageAvailable( const
            bb::cascades::maps::ViewProperties& viewProperties );

    /**
     * @brief Retrieves a list of @c RenderEngine names that have map coverage for
     * the given @c ViewProperties.
     *
     * @param viewProperties The @c ViewProperties describing the area to check.
     * @return A list of @c RenderEngine names, or an empty list if none were found.
     * @since BlackBerry 10.3.0
     */
    BB_CASCADES_MAPS_EXPORT static QStringList renderersWithCoverage(
        const bb::cascades::maps::ViewProperties& viewProperties );

    /**
     * @brief Checks if map coverage is available from any @c RenderEngine for
     * the given country.
     *
     * @param countryCode An ISO 3166-1 alpha-3 country code.
     * @return @c true if map coverage is available for the given country,
     * @c false if no coverage or partial coverage.
     * @since BlackBerry 10.3.0
     */
    BB_CASCADES_MAPS_EXPORT static bool isCoverageAvailable( const QString& countryCode );

    /**
     * @brief Retrieves a list of @c RenderEngine names that have map coverage for
     * the given country.
     *
     * @param countrycode An ISO 3166-1 alpha-3 country code.
     * @return A list of @c RenderEngine names, or an empty list if none were found.
     * @since BlackBerry 10.3.0
     */
    BB_CASCADES_MAPS_EXPORT static QStringList renderersWithCoverage( const QString& countryCode );

private:
    MapCoverageChecker();
    MapCoverageChecker( MapCoverageChecker const& );
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPCOVERAGECHECKER_HPP */
