/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPIMAGEGENERATORERROR_HPP
#define BB_CASCADES_MAPS_MAPIMAGEGENERATORERROR_HPP

#include <bb/platform/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace cascades
{
namespace maps
{

/**
 * @headerfile MapImageGeneratorError.hpp <bb/cascades/maps/MapImageGeneratorError>
 *
 * @brief The set of possible error codes when getting a static map image.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT MapImageGeneratorError
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /**
     * @brief The set of possible image generation errors.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /**
         * @brief For the case when there is no error.
         *
         * @since BlackBerry 10.2.0
         */
        NoError = 0,

        /**
         * @brief When the source of the image generator was not found.
         *
         * @since BlackBerry 10.2.0
         */
        GeneratorSourceNotFound = 1,

        /**
         * @brief When the image generation attempt failed.
         *
         * @since BlackBerry 10.2.0
         */
        ImageGenerationFailed = 2,

        /**
         * @brief When the image itself is invalid.
         *
         * @since BlackBerry 10.2.0
         */
        ImageInvalid = 3
    };

private:
    //!@cond PRIVATE
    MapImageGeneratorError();
    ~MapImageGeneratorError();
    //!@endcond
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPIMAGEGENERATORERROR_HPP */
