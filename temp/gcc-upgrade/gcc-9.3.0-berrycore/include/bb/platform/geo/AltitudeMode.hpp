/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_ALTITUDEMODE_HPP
#define BB_PLATFORM_GEO_ALTITUDEMODE_HPP

#include <bb/platform/geo/Global>

#include <QDebug>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{
namespace geo
{

/**
 * @headerfile AltitudeMode.hpp <bb/platform/geo/AltitudeMode>
 *
 * @brief An enumeration that captures how the @c altitude attribute should be
 * interpreted.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT AltitudeMode
{
    Q_GADGET
    Q_ENUMS( Type );

public:
    /**
     * @brief The altitude measurement can be relative to the ground
     * (default) or the sea level.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /**
         * @brief Altitude measurement is relative to the ground.
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0,

        /**
         * @brief Altitude measurement is relative to sea level (WGS
         * 84 Reference Ellipsoid).
         *
         * @since BlackBerry 10.0.0
         */
        Absolute = 1,

        /**
         * @brief Altitude is ignored, items adhere to the contour of
         * the ground.
         *
         * @since BlackBerry 10.0.0
         */
        ClampToGround = 2,

        /**
         * @brief Altitude measurement is relative to the ground.
         *
         * @since BlackBerry 10.0.0
         */
        RelativeToGround = 3

    }; // enum

private:
    /** @cond PRIVATE */
    AltitudeMode();
    ~AltitudeMode();
    /** @endcond */

}; // class

// having problems with visibility - comment out for now
//BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const AltitudeMode::Type& pt );

} // namespace geo
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::geo::AltitudeMode )

#endif /* BB_PLATFORM_GEO_ALTITUDEMODE_HPP */
