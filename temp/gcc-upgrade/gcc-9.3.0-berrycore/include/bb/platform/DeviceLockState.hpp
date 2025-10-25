/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_DEVICELOCKSTATE_HPP
#define BB_PLATFORM_DEVICELOCKSTATE_HPP

#include <bb/platform/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile DeviceLockState.hpp <bb/platform/DeviceLockState>
 *
 * @brief The set of possible lock states of the device.
 * 
 * @see @c HomeScreen::lockState
 * @see @c HomeScreen::lockStateChanged
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT DeviceLockState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible lock states of the device.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The current lock state is not known.  
         *
         * This state can occur when a @c HomeScreen object is first created 
         * and we have not yet received any updates on the current lock 
         * state of the device.  It can also occur if there is an error 
         * while processing the events needed to establish the lock state.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,

        /*!
         * @brief The device is not locked at this time.
         *
         * @since BlackBerry 10.0.0
         */
        Unlocked = 1,

        /*!
         * @brief The device is screen locked but not password locked.  
         *
         * The device can be unlocked with a swipe gesture without the need 
         * to enter the device password.
         *
         * @since BlackBerry 10.0.0
         */
        ScreenLocked = 2,

        /*!
         * @brief The device is password locked.  
         *
         * A swipe gesture will raise a password prompt that must be 
         * completed before the device is unlocked.
         *
         * @since BlackBerry 10.0.0
         */
        PasswordLocked = 3,

        /*!
         * @brief The device is PIN-blocked.
         *
         * The device has been disabled by the provider.
         *
         * @since BlackBerry 10.0.0
         */
        PinBlocked = 4
    };

private:
//!@cond PRIVATE
    DeviceLockState();
    ~DeviceLockState();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::DeviceLockState)
#endif // BB_PLATFORM_DEVICELOCKSTATE_HPP
