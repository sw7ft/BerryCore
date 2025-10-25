/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_PAYMENTERRORCODE_HPP
#define BB_PLATFORM_PAYMENTERRORCODE_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb
{
namespace platform
{

/*!
 * @headerfile PaymentErrorCode.hpp <bb/platform/PaymentErrorCode>
 *
 * @brief The errors that can be returned by the Payment Service.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT PaymentErrorCode
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
    * @brief The possible @c PaymentReply::errorCode() values returned from the Payment Service
    */
    enum Type {
        /*!
        * @brief No error occurred.
         *
         * @since BlackBerry 10.2.0
        */
        None = 0,

        /*!
        * @brief User canceled the request. @c PaymentReply::errorInfo() will not be populated.
         *
         * @since BlackBerry 10.2.0
        */
        Canceled = 1,

        /*!
        * @brief The Payment Service is busy. Only one transaction can occur at a time.
        * @c PaymentReply::errorInfo() will not be populated.
         *
         * @since BlackBerry 10.2.0
        */
        Busy = 2,

        /*!
        * @brief Payment Service failed. See @c PaymentReply::errorInfo() and @c PaymentReply::errorText() for more detail.
         *
         * @since BlackBerry 10.2.0
         */
        Failed = 3,

        /*!
        * @brief No network connection on the device. Direct the user to Settings > Network Connections
        * to enable a Wi-Fi or mobile connection. @c PaymentReply::errorInfo() will not be populated.
         *
         * @since BlackBerry 10.2.0
         */
        NoNetwork = 8
    };


private:
//!@cond PRIVATE
    PaymentErrorCode();
    ~PaymentErrorCode();
//!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_PAYMENTERRORCODE_HPP
