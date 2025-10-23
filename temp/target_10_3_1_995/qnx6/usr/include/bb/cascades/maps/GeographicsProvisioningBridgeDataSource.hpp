/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGEDATASOURCE_HPP
#define BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGEDATASOURCE_HPP

#include <bb/platform/geo/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace cascades
{
namespace maps
{

/**
 * @headerfile GeographicsProvisioningBridgeDataSource.hpp <bb/platform/geo/GeographicsProvisioningBridgeDataSource>
 *
 * @brief Indicates how data sources used with @c GeographicsProvisioningBridge will be interpreted.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT GeographicsProvisioningBridgeDataSource
{
    Q_GADGET
    Q_ENUMS( Type );

public:

    /**
     * @brief Indicates the types of data sources for @c GeographicsProvisioningBridge.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /**
         * @brief Data source type will be automatically detected.
         *
         * @since BlackBerry 10.2.0
         */
        AutoDetect = 0,

        /**
         * @brief Data source type is KML data.
         *
         * @since BlackBerry 10.2.0
         */
        Kml = 1
    };

private:
    /** @cond PRIVATE */
    GeographicsProvisioningBridgeDataSource();
    ~GeographicsProvisioningBridgeDataSource();
    /** @endcond */
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGEDATASOURCE_HPP */
