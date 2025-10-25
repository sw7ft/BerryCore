/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTINTENT_HPP
#define BB_DEVICE_WIFIDIRECTINTENT_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectIntent.hpp <bb/device/WiFiDirectIntent>
 *
 * @brief The intent of the WiFiDirect connection.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT WiFiDirectIntent
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The intent of the WiFiDirect connection.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
    	/*!
    	 * @brief Request to be the group owner.
    	 *
    	 * @details If the Group Owner intent is expressed by both ends of the
    	 * connection attempt, or if joining a group that already has a Group
    	 * Owner, the connection attempt will fail.
    	 *
    	 * @since BlackBerry 10.2.0
    	 */
        GroupOwner = 0,

        /*!
         * @brief Request to be a group client.
         *
         * @since BlackBerry 10.2.0
         */
        Client = 1,

        /*!
         * @brief Request any role within the group.
         *
         * @since BlackBerry 10.2.0
         */
        Any = 2
    };

private:
//!@cond PRIVATE
    WiFiDirectIntent();
    ~WiFiDirectIntent();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectIntent)
#endif // BB_DEVICE_WIFIDIRECTINTENT_HPP
