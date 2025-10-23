/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARCONNECTIONSTATE_HPP
#define BB_DEVICE_CELLULARCONNECTIONSTATE_HPP

#include <bb/device/Global>

#include <QObject>

namespace bb
{
namespace device
{

/*!
 * @headerfile CellularConnectionState.hpp <bb/device/CellularConnectionState>
 *
 * @brief The connection status of a @c CellularDataInterface object.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT CellularConnectionState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The connection status of a @c CellularDataInterface object.
     */
    enum Type
    {
        /*!
         * @brief The network connection for the current cellular data service is 
         * de-activated.
         *
         * @since BlackBerry 10.2.0
         */
        Disconnected = 0,
        
        /*!
         * @brief The request to activate the network connection for the current 
         * cellular data service has been issued but has not completed.
         *
         * @since BlackBerry 10.2.0
         */
        PendingConnect = 1,
        
        /*!
         * @brief The network connection for the current cellular data service is 
         * activated.
         *
         * @since BlackBerry 10.2.0
         */
        Connected = 2
    };
    
private:
//!@cond PRIVATE
    CellularConnectionState();
    ~CellularConnectionState();
//!@endcond
};

} // namespace device
} // namespace bb

#endif // BB_DEVICE_CELLULARCONNECTIONSTATE_HPP
