/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTRESULT_HPP
#define BB_DEVICE_WIFIDIRECTRESULT_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectResult.hpp <bb/device/WiFiDirectResult>
 *
 * @brief The possible outcomes of WiFiDirect service operations.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT WiFiDirectResult
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The possible outcomes of WiFiDirect service operations.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
    	/*!
    	 * @brief The operation was successful.
    	 *
    	 * @since BlackBerry 10.2.0
    	 */
        Success = 0,

        /*!
         * @brief An unrecoverable internal error occured.
         *
         * @since BlackBerry 10.2.0
         */
        InternalError = 1,

        /*!
         * @brief Cannot scan as system is busy and being used by other WiFi service (eg. Miracast).
         *
         * @since BlackBerry 10.2.0
         */
        Busy = 2,

        /*!
         * @brief Device with specified hardware address was not found.
         *
         * @since BlackBerry 10.2.0
         */
        DeviceNotFound = 3,

        /*!
         * @brief Device was not connected to a network.
         *
         * @since BlackBerry 10.2.0
         */
        NoNetworkConnection = 4,

        /*!
         * @brief No active connection attempt available to cancel.
         *
         * @since BlackBerry 10.2.0
         */
        NoRequestToCancel = 5,

        /*!
         * @brief WiFiDirect is not supported on this device.
         *
         * @since BlackBerry 10.2.0
         */
        NotSupported = 6,

        /*!
         * @brief The supplied session was not found.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidSession = 7
    };

private:
//!@cond PRIVATE
    WiFiDirectResult();
    ~WiFiDirectResult();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectResult)
#endif // BB_DEVICE_WIFIDIRECTRESULT_HPP
