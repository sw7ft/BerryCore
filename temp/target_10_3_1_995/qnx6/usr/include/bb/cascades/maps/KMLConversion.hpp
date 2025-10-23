/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_KMLCONVERSION_HPP
#define BB_CASCADES_MAPS_KMLCONVERSION_HPP

#include <bb/cascades/maps/Global>
#include <bb/cascades/maps/DataProvider>

class QString;

namespace bb
{
namespace cascades
{
namespace maps
{

/**
 * @brief Converts KML data content into a @c DataProvider.
 * The @c DataProvider instance contains various geographic elements
 * that are created as a result of parsing this KML content. Its ID is
 * set to the unique ID available within the KML content itself.
 *
 * The returned object is owned by the calling client,
 * which must delete the associated memory. Note, when the returned
 * object is passed to a @c MapData instance, then that @c MapData becomes
 * the owner of the data, and the deletion of memory is handled by the
 * @c MapData.
 *
 * @param kmlContent The KML content ready to be parsed.
 * @return The @c DataProvider instance that holds the geographic entities that
 * correspond to the KML data, or @c NULL if an error occurred during the
 * parsing of KML content. If no supported geographic elements were encountered
 * (e.g. Placemarks), but the parsing itself was successful, then an
 * empty data provider is returned.
 *
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
BB_CASCADES_MAPS_EXPORT bb::cascades::maps::DataProvider* convertKmlContentToDataProvider(
    const QString& kmlContent );


} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_KMLCONVERSION_HPP */
