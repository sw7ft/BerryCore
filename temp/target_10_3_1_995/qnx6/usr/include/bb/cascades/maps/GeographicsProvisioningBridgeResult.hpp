/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGERESULT_HPP
#define BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGERESULT_HPP

#include <bb/platform/geo/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace cascades
{
namespace maps
{

/**
 * @headerfile GeographicsProvisioningBridgeResult.hpp <bb/platform/geo/GeographicsProvisioningBridgeResult>
 *
 * @brief Represents the types of results that can occur when using @c GeographicsProvisioningBridge.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT GeographicsProvisioningBridgeResult
{
    Q_GADGET
    Q_ENUMS( Type );

public:

    /**
     * @brief Represents the geographic data source result types.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /**
         * @brief The operation completed successfully.
         *
         * @since BlackBerry 10.2.0
         */
        Success = 0,

        /**
         * @brief The source URL or file was not defined or not found.
         *
         * @since BlackBerry 10.2.0
         */
        SourceNotFound = 1,

        /**
         * @brief An error occurred with a remote connection.
         *
         * @since BlackBerry 10.2.0
         */
        ConnectionFailure = 2,

        /**
         * @brief An error occurred performing the data operation.
         *
         * This value can indicate several types of errors, such as:
         * - parsing failed
         * - accessing a remote source resulted in a networking error or infinite redirection
         *
         * This list is not exhaustive, so check the error string to determine the exact
         * cause of the error.
         *
         * @since BlackBerry 10.2.0
         */
        OperationFailure = 3,

        /**
         * @brief The content type of the data source could not be automatically detected.
         *
         * @since BlackBerry 10.2.0
         */
        UnknownContentType = 4,

        /**
         * @brief The @c destinationProvider property was invalid when @c GeographicsProvisioningBridge::load() was called.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidDataProvider = 5,

        /**
         * @brief There was an error opening a local file.
         *
         * @since BlackBerry 10.2.0
         */
        UnableToOpenFile = 6
    };

private:
    /** @cond PRIVATE */
    GeographicsProvisioningBridgeResult();
    ~GeographicsProvisioningBridgeResult();
    /** @endcond */
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGERESULT_HPP */
