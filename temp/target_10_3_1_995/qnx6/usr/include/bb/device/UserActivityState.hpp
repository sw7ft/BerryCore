/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_USERACTIVITYSTATE_HPP
#define BB_DEVICE_USERACTIVITYSTATE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile UserActivityState.hpp <bb/device/UserActivityState>
 * 
 * @brief The possible user activity states of a device.
 * 
 * @details Note that this is a device-wide activity state, and not a
 * process activity state. These states indicate whether the user can
 * interact with the device.
 * 
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 * 
 * @since BlackBerry 10.2.0
 */

class BB_DEVICE_EXPORT UserActivityState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The possible user activity states of a device.
     * 
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The current user activity state could not be determined.
         * 
         * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The device is currently active.
         * 
         * @details The user can interact with the device. This implies that the
         * display is currently enabled. However, it does not provide any indication
         * of the lock state of the device.  That is, an active device may be
         * unlocked, screen-locked, or password-locked.
         * 
         * @since BlackBerry 10.2.0
         */
        Active = 1,

        /*!
         * @brief The device is currently inactive.
         * 
         * @details The user cannot interact with the device. This implies that the
         * display is currently disabled. The device may also be in standby mode
         * and possibly locked.
         * 
         * @since BlackBerry 10.2.0
         */
        Inactive = 2
    };

private:
    //!@cond PRIVATE
    UserActivityState();
    ~UserActivityState();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::UserActivityState)
#endif // BB_DEVICE_USERACTIVITYSTATE_HPP
