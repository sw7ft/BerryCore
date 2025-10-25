/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_BATTERYCHARGINGSTATE_HPP
#define BB_DEVICE_BATTERYCHARGINGSTATE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile BatteryChargingState.hpp <bb/device/BatteryChargingState>
 *
 * @brief The set of possible charging states for the battery.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT BatteryChargingState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible charging states for the battery.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Battery state could not be determined.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown              = 0,

        /*!
         * @brief Battery is plugged in, but is not receiving enough power to charge.
         *
         * @since BlackBerry 10.0.0
         */
        NotCharging          = 1,

        /*!
         * @brief Battery is charging.
         *
         * @since BlackBerry 10.0.0
         */
        Charging             = 2,

        /*!
         * @brief Battery is not plugged in.
         *
         * @since BlackBerry 10.0.0
         */
        Discharging          = 3,

        /*!
         * @brief Battery is plugged in and fully charged.
         *
         * @since BlackBerry 10.0.0
         */
        Full                 = 4
    };

private:
//!@cond PRIVATE
    BatteryChargingState();
    ~BatteryChargingState();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::BatteryChargingState)
#endif // BB_DEVICE_BATTERYCHARGINGSTATE_HPP
