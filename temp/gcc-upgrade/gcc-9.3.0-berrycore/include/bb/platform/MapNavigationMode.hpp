/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_MAPNAVIGATIONMODE_HPP
#define BB_PLATFORM_MAPNAVIGATIONMODE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile MapNavigationMode.hpp <bb/platform/MapNavigationMode>
 *
 * @brief The set of possible navigation modes.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT MapNavigationMode
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The set of possible navigation modes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
       /*!
        * @brief The navigation mode has not been set.
        *
        * The receiving Maps application should use its own preferred mode, by default.
        *
        * @since BlackBerry 10.0.0
        */
    	Undefined = 0,

       /*!
        * @brief Generate the fastest route.
        *
        * @since BlackBerry 10.0.0
        */
    	FastestRoute = 1,

       /*!
        * @brief Generate the shortest route. 
        *
        * @since BlackBerry 10.0.0
        */
    	ShortestRoute = 2
    }; 

private:
//!@cond PRIVATE
    MapNavigationMode();
    ~MapNavigationMode();
//!@endcond

}; //class

} /* namespace platform */
} /* namespace bb */
QML_DECLARE_TYPE(bb::platform::MapNavigationMode)

#endif /* BB_PLATFORM_MAPNAVIGATIONMODE_HPP */
