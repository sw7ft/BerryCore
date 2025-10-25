/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_TYPICALMAPALTITUDE_HPP
#define BB_PLATFORM_TYPICALMAPALTITUDE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile TypicalMapAltitude.hpp <bb/platform/TypicalMapAltitude>
 *
 * @brief Captures how the typical altitudes (at different view levels) should be interpreted.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT TypicalMapAltitude
{
public:
    /*!
     * @brief Typical altitude value, associated with a street view.
     *
     * @since BlackBerry 10.0.0
     */
    static const int StreetView = 70;

    /*! 
     * @brief Typical altitude value, associated with a city view.
     *
     * @since BlackBerry 10.0.0
     */
    static const int CityView = 400;

    /*! 
     * @brief Typical altitude value, associated with a state/province view.
     *
     * @since BlackBerry 10.0.0
     */
    static const int StateView = 2000;

    /*! 
     * @brief Typical altitude value, associated with a country view.
     *
     * @since BlackBerry 10.0.0
     */
    static const int CountryView = 9000;

    /*!
     * @brief Typical altitude value, associated with the world view.
     *
     * @since BlackBerry 10.0.0
     */
    static const int WorldView = 20000;

private:
//!@cond PRIVATE
    TypicalMapAltitude();
    ~TypicalMapAltitude();
//!@endcond

}; //class

} /* namespace platform */
} /* namespace bb */


#endif /* BB_PLATFORM_TYPICALMAPALTITUDE_HPP */
