/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARCONNECTIONREQUESTRESULT_HPP
#define BB_DEVICE_CELLULARCONNECTIONREQUESTRESULT_HPP

#include <bb/device/Global>

#include <QObject>

namespace bb
{
namespace device
{

/*!
 * @headerfile CellularConnectionRequestResult.hpp <bb/device/CellularConnectionRequestResult>
 *
 * @brief The result of a connect/disconnect request for a @c CellularDataInterface 
 * object.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT CellularConnectionRequestResult
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The result of a connect/disconnect request for a @c CellularDataInterface 
     * object.
     */
    enum Type
    {
        /*!
         * @brief No error was immediately detected.
         *
         * @details The request will proceed but may still fail later.
         *
         * @since BlackBerry 10.2.0
         */
        Requested = 0,
        
        /*!
         * @brief An internal error occurred that is not recoverable.
         *
         * @since BlackBerry 10.2.0
         */
        InternalError = 1,
        
        /*!
         * @brief The current cellular data service is not valid or the service 
         * does not support connect/disconnect requests.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidInterface = 2,
        
        /*!
         * @brief The caller does not have the required permssion to issue a 
         * connect/disconnect request for the current cellular data service.
         *
         * @since BlackBerry 10.2.0
         */
        PermissionDenied = 3,
        
        /*!
         * @brief The connect/disconnect request is not a valid operation at this 
         * time.
         *
         * @details This can occur when attempting to connect when already connected, 
         * when attempting to disconnect when already disconnected, or when data 
         * services for the device are disabled.
         *
         * @since BlackBerry 10.2.0
         */
        NotPossible = 4
    };
    
private:
//!@cond PRIVATE
    CellularConnectionRequestResult();
    ~CellularConnectionRequestResult();
//!@endcond
};

} // namespace device
} // namespace bb

#endif // BB_DEVICE_CELLULARCONNECTIONREQUESTRESULT_HPP
