/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_MAPSEARCHMODE_HPP
#define BB_PLATFORM_MAPSEARCHMODE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile MapSearchMode.hpp <bb/platform/MapSearchMode>
 *
 * @brief The set of possible search modes.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT MapSearchMode
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The set of possible search modes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
    	/*!
         * @brief For a radial search (i.e., search around a certain location).
    	 *
    	 * @since BlackBerry 10.0.0
         */
    	Radial = 1,

    	/*!
         * @brief For a search along a given path or route.
    	 *
    	 * @since BlackBerry 10.0.0
         */
    	Path = 2
    };

private:
//!@cond PRIVATE
    MapSearchMode();
    ~MapSearchMode();
//!@endcond
}; //class

} /* namespace platform */
} /* namespace bb */

QML_DECLARE_TYPE(bb::platform::MapSearchMode)

#endif /* BB_PLATFORM_MAPSEARCHMODE_HPP */
