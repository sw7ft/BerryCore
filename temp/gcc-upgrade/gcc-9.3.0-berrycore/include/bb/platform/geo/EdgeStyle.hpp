/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_EDGESTYLE_HPP
#define BB_PLATFORM_GEO_EDGESTYLE_HPP

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
 * @headerfile EdgeStyle.hpp <bb/platform/geo/EdgeStyle>
 *
 * @brief An enumeration of the available edge patterns
 * of a @c Style.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT EdgeStyle
{
    Q_GADGET
    Q_ENUMS( Type );

public:
    /**
     * @brief The edge patterns within a @c Style.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {

        /**
         * @brief Edge size is inherited from style set.
         *
         * @since BlackBerry 10.2.0
         */
        Inherited = 0,

        /**
         * @brief Solid edge.
         *
         * @since BlackBerry 10.2.0
         */
        Solid = 1,

        /**
         * @brief Dotted edge.
         *
         * @since BlackBerry 10.2.0
         */
        Dot = 2,

        /**
         * @brief Dashed edge.
         *
         * @since BlackBerry 10.2.0
         */
        Dash = 3

    }; // enum

private:
    /** @cond PRIVATE */
    EdgeStyle();
    ~EdgeStyle();
    /** @endcond */

}; // class

// having problems with visibility - comment out for now
//BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const EdgeStyle::Type& pt );

} // namespace geo
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::geo::EdgeStyle )

#endif /* BB_PLATFORM_GEO_EDGESTYLE_HPP */
