/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PLACES_SELECTEDPLACEIMAGETYPE_HPP
#define BB_CASCADES_PLACES_SELECTEDPLACEIMAGETYPE_HPP

/*!
 * @file SelectedPlaceImageType.hpp
 *
 * @since BlackBerry 10.0.0
 */

#include <bb/cascades/places/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace cascades
{
namespace places
{

/*!
 * @class SelectedPlaceImageType
 *
 * @brief The type of image data returned by the @c SelectedPlace class.
 *
 * @headerfile SelectedPlaceImageType.hpp <bb/cascades/places/SelectedPlaceImageType>
 *
 * @xmlonly
 * <apigrouping group="Location/Places"/>
 * <library name="bbcascadesplaces"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PLACES_EXPORT SelectedPlaceImageType
{
public:

    /*!
     * @brief Data type of the image.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief An undefined or unrecognized image type.
         *
         * @since BlackBerry 10.0.0
         */
        Undefined = 0,

        /*!
         * @brief A PNG image.
         *
         * @since BlackBerry 10.0.0
         */
        Png = 1,

        /*!
         * @brief A JPEG image.
         *
         * @since BlackBerry 10.0.0
         */
        Jpg = 2,

        /*!
         * @brief A BMP image.
         *
         * @since BlackBerry 10.0.0
         */
        Bmp = 3,

        /*!
         * @brief A GIF image.
         *
         * @since BlackBerry 10.0.0
         */
        Gif = 4,
    };
private:
    SelectedPlaceImageType();
    ~SelectedPlaceImageType();
};

}
}
}

QML_DECLARE_TYPE(bb::cascades::places::SelectedPlaceImageType)
#endif
