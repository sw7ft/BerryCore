/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTCONNECTIONSTATE_HPP
#define BB_DEVICE_WIFIDIRECTCONNECTIONSTATE_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectConnectionState.hpp <bb/device/WiFiDirectConnectionState>
 *
 * @brief The state of the WiFiDirect connection to the network group.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT WiFiDirectConnectionState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The state of the WiFiDirect connection to the network group.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
    	/*!
    	 * @brief Unable to determine the current network group state.
    	 *
    	 * @since BlackBerry 10.2.0
    	 */
        Unknown = 0,

        /*!
         * @brief A connection to the network group is currently in progress.
         *
         * @since BlackBerry 10.2.0
         */
        Connecting = 1,

        /*!
         * @brief Currently connected to a network group.
         *
         * @since BlackBerry 10.2.0
         */
        Connected = 2,

        /*!
         * @brief Not currently connected to a network group.
         *
         * @since BlackBerry 10.2.0
         */
        Disconnected = 3
    };

private:
//!@cond PRIVATE
    WiFiDirectConnectionState();
    ~WiFiDirectConnectionState();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectConnectionState)
#endif // BB_DEVICE_WIFIDIRECTCONNECTIONSTATE_HPP
