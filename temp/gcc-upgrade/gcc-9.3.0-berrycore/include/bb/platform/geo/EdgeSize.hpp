/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_EDGESIZE_HPP
#define BB_PLATFORM_GEO_EDGESIZE_HPP

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
 * @headerfile EdgeSize.hpp <bb/platform/geo/EdgeSize>
 *
 * @brief An enumeration of the available edge thickness values
 * of a @c Style.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT EdgeSize
{
    Q_GADGET
    Q_ENUMS( Type );

public:
    /**
     * @brief The edge thickness within a @c Style.
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
         * @brief No edge.
         *
         * @since BlackBerry 10.2.0
         */
        None = 1,

        /**
         * @brief Edge size is very small.
         *
         * @since BlackBerry 10.2.0
         */
        XSmall = 2,

        /**
         * @brief Edge size is small.
         *
         * @since BlackBerry 10.2.0
         */
        Small = 3,

        /**
         * @brief Edge size is medium.
         *
         * @since BlackBerry 10.2.0
         */
        Medium = 4,

        /**
         * @brief Edge size is large.
         *
         * @since BlackBerry 10.2.0
         */
        Large = 5,

        /**
         * @brief Edge size is very large.
         *
         * @since BlackBerry 10.2.0
         */
        XLarge = 6

    }; // enum

private:
    /** @cond PRIVATE */
    EdgeSize();
    ~EdgeSize();
    /** @endcond */

}; // class

// having problems with visibility - comment out for now
//BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const EdgeSize::Type& pt );

} // namespace geo
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::geo::EdgeSize )

#endif /* BB_PLATFORM_GEO_EDGESIZE_HPP */
