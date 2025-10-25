/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_PLATFORM_DIGITALGOODSTATE_HPP
#define BB_PLATFORM_DIGITALGOODSTATE_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb
{
namespace platform
{

/*!
 * @headerfile DigitalGoodState.hpp <bb/platform/DigitalGoodState>
 *
 * @brief The possible states of a digital good.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT DigitalGoodState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The possible states of a digital good.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The digital good is not a subscription; it is owned by the user.
         *
         * @since BlackBerry 10.0.0
         */
        Owned = 0,

        /*!
         * @brief The user is currently subscribed to the digital good. It's a new subscription.
         *
         * @since BlackBerry 10.0.0
         */
        NewSubscription = 1,

        /*!
         * @brief The subscription digital good has been refunded.
         *
         * @since BlackBerry 10.0.0
         */
        SubscriptionRefunded = 2,

        /*!
         * @brief The subscription has been canceled. 
         * 
         * @note A subscription remains active until its subscription period ends, even if it has been canceled.
         *
         * @since BlackBerry 10.0.0
         */
        SubscriptionCanceled = 3,

        /*!
         * @brief The user is currently subscribed and has renewed the subscription.
         *
         * @since BlackBerry 10.0.0
         */
        SubscriptionRenewed = 4,

        /*!
         * @brief The state of the digital good is unknown.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 5
    };

private:
//!@cond PRIVATE
    DigitalGoodState();
    ~DigitalGoodState();
//!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_DIGITALGOODSTATE_HPP
