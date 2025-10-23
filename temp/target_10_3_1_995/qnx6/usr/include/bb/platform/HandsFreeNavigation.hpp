/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2013-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_HANDSFREENAVIGATION_HPP
#define BB_PLATFORM_HANDSFREENAVIGATION_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile HandsFreeNavigation.hpp <bb/platform/HandsFreeNavigation>
 *
 * @brief The set of possible hands-free navigation values.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.3.0
 */
class BB_PLATFORM_EXPORT HandsFreeNavigation
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The set of possible hands-free navigation values.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type
    {
       /*!
        * @brief The hands-free navigation has not been set.
        *
        * The receiving Maps application should use its own preferred mode, by default.
        *
        * @since BlackBerry 10.3.0
        */
    	Undefined = 0,

       /*!
        * @brief Enable hands-free navigation experience.
        *
        * @since BlackBerry 10.3.0
        */
    	Enabled = 1,

       /*!
        * @brief Disable hands-free navigation experience. 
        *
        * @since BlackBerry 10.3.0
        */
    	Disabled = 2
    }; 

private:
//!@cond PRIVATE
    HandsFreeNavigation();
    ~HandsFreeNavigation();
//!@endcond

}; //class

} /* namespace platform */
} /* namespace bb */
QML_DECLARE_TYPE(bb::platform::HandsFreeNavigation)

#endif /* BB_PLATFORM_HANDSFREENAVIGATION_HPP */
