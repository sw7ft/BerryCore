/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_BATTERYCONDITION_HPP
#define BB_DEVICE_BATTERYCONDITION_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile BatteryCondition.hpp <bb/device/BatteryCondition>
 *
 * @brief The set of possible conditions of the battery.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT BatteryCondition
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible conditions of the battery.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Battery condition could not be determined.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown              = 0,

        /*!
         * @brief Battery is OK
         *
         * @since BlackBerry 10.0.0
         */
        OK                   = 1,

        /*!
         * @brief Battery is bad.
         *
         * @since BlackBerry 10.0.0
         */
        Bad                  = 2
    };

private:
//!@cond PRIVATE
    BatteryCondition();
    ~BatteryCondition();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::BatteryCondition)
#endif // BB_DEVICE_BATTERYCONDITION_HPP
