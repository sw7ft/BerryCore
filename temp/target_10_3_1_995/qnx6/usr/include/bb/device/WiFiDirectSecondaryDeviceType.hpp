/*!
 * @copyright
 * Copyright BlackBerry Limited, 2014-2014
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTSECONDARYDEVICETYPE_HPP
#define BB_DEVICE_WIFIDIRECTSECONDARYDEVICETYPE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectSecondaryDeviceType.hpp <bb/device/WiFiDirectSecondaryDeviceType>
 *
 * @brief Indicates the secondary type(s) of a WiFiDirect device.
 *
 * @details This is a secondary type that provides additional information about the type of
 * the WiFiDirect device. For instance, a Miracast display has a @c Display type and a
 * @c Miracast secondary type. If the WiFiDirect display does not support Miracast, it will
 * not have the @c Miracast secondary type and the API consumer will be able to differentiate
 * Miracast displays from non-Miracast displays.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_DEVICE_EXPORT WiFiDirectSecondaryDeviceType
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Indicates the secondary types of a WiFiDirect device.
     *
     * @details A WiFiDirect device can have zero, one or more secondary types.
     * If one or more secondary type(s) cannot be determined for technical reasons, the secondary
     * type will be set to @c Unknown and only @c Unknown. If the device has no secondary types,
     * no flags will be set.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type
    {
        /*!
         * @brief The secondary type could not be determined.
         *
         * @since BlackBerry 10.3.0
         */
        Unknown = 1,

        /*!
         * @brief The device is Miracast capable.
         *
         * @since BlackBerry 10.3.0
         */
        Miracast = 2,
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
    //!@cond PRIVATE
    WiFiDirectSecondaryDeviceType();
    ~WiFiDirectSecondaryDeviceType();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectSecondaryDeviceType)
#endif // BB_DEVICE_WIFIDIRECTSECONDARYDEVICETYPE_HPP
