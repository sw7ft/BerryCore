/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTROLE_HPP
#define BB_DEVICE_WIFIDIRECTROLE_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectRole.hpp <bb/device/WiFiDirectRole>
 *
 * @brief The role of a device within a network group.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT WiFiDirectRole
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The role of a device within a network group.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief The role of the device could not be determined.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The device is the Group Owner of the network group.
         *
         * @since BlackBerry 10.2.0
         */
        GroupOwner = 1,

        /*!
         * @brief The device is a client within the network group.
         *
         * @since BlackBerry 10.2.0
         */
        Client = 2,

        /*!
         * @brief The device is not part of a network group and hence has no role.
         *
         * @since BlackBerry 10.3.0
         */
        NoRole = 3
    };

private:
//!@cond PRIVATE
    WiFiDirectRole();
    ~WiFiDirectRole();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectRole)
#endif // BB_DEVICE_WIFIDIRECTROLE_HPP
