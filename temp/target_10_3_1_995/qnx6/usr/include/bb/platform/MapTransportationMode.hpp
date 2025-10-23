/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_MAPTRANSPORTATIONMODE_HPP
#define BB_PLATFORM_MAPTRANSPORTATIONMODE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile MapTransportationMode.hpp <bb/platform/MapTransportationMode>
 *
 * @brief The set of possible modes of transportation.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT MapTransportationMode
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The set of possible modes of transportation.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
    	/*!
    	 * @brief The mode of transportation has not been set by the user.
         *
    	 * The Maps application should use its own preferred mode, as the default.
    	 *
    	 * @since BlackBerry 10.0.0
    	 */
    	Undefined = 0,

    	/*!
         * @brief Produce routes using a car as the mode of transportation.
    	 *
    	 * @since BlackBerry 10.0.0
         */
    	Car = 1,

    	/*! 
         * @brief Produce routes for a pedestrian.
    	 *
    	 * @since BlackBerry 10.0.0
         */
    	Pedestrian = 2
    };

private:
//!@cond PRIVATE
    MapTransportationMode();
    ~MapTransportationMode();
//!@endcond
}; //class

} /* namespace platform */
} /* namespace bb */

QML_DECLARE_TYPE(bb::platform::MapTransportationMode)

#endif /* BB_PLATFORM_MAPTRANSPORTATIONMODE_HPP */
