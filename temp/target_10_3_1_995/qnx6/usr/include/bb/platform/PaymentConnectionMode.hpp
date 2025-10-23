/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_PAYMENTCONNECTIONMODE_HPP
#define BB_PLATFORM_PAYMENTCONNECTIONMODE_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb
{
namespace platform
{

/*!
 * @brief Set of Payment API connection modes.
 *
 * @details The Payment API can be put into @c bb::platform::PaymentConnectionMode::Test connection mode for easier testing.
 *
 * @see PaymentManager::setConnectionMode() and @c bb::platform::PaymentConnectionMode::Test for more on this.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT PaymentConnectionMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Set of Payment API connection modes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Testing mode that bypasses the Payment server.
         *
         * @details In this mode, the application does not contact
         * the Payment server for any transactions. For purchases, a simulated
         * purchase screen is displayed, allowing the user to choose the result of the purchase.
         * For retrieving purchase history, only simulated successful purchases are returned.
         * For other requests, such as @c PaymentManager::requestPrice(), responses will contain simulated
         * data.
         * This mode is useful for testing how your application handles the possible results
         * without requiring network connections or currency.
         *
         * @note Production code should @b not use this mode.
         *
         * @since BlackBerry 10.0.0
         */
        Test       = 0,

        /*!
         * @brief Standard production mode.
         * 
         * When in this mode, purchases and retrievals of
         * existing purchases proceed normally, contacting the Payment server as necessary.
         * This is the default connection mode, and applications in production should not modify it.
         *
         * This is the default connection mode.
         *
         * @note Production code should use this mode.
         *
         * @since BlackBerry 10.0.0
         */
        Production = 1
    };

private:
//!@cond PRIVATE
    PaymentConnectionMode();
    ~PaymentConnectionMode();
//!@endcond
};

} // namespace
} // namespace

#endif // BB_PLATFORM_PAYMENTCONNECTIONMODE_HPP
