/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_SUBSCRIPTIONSTATUSREPLY_HPP
#define BB_PLATFORM_SUBSCRIPTIONSTATUSREPLY_HPP

#include <bb/platform/DigitalGoodReply>
#include <bb/platform/Global>
#include <bb/platform/PurchaseReceipt>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class SubscriptionStatusReplyPrivate;

/*!
 * @headerfile SubscriptionStatusReply.hpp <bb/platform/SubscriptionStatusReply>
 *
 * @brief Represents a response to @c PaymentManager::requestSubscriptionStatus().
 *
 * @details An instance of this class is returned when a call to @c PaymentManager::requestSubscriptionStatus() is made.  Initially, the returned object
 * will be unfinished and not contain any valid information relating to the request (other than
 * that it is unfinished).  Once the request is finished, @c PaymentReply::isError() can be used to determine whether the request succeeded or failed.
 * If the request was successful, then the @c isActive() method provides whether the subscription
 * is active.
 * If the request failed, then the error code and error text are included; these can be accessed on
 * the @c PaymentReply base class.
 *
 * The @c PaymentReply::finished() signal can be used to determine when the request finishes.  The
 * @c PaymentManager::subscriptionStatusFinished() signal can also be used to determine when a request finishes.
 *
 * @note Do not delete the object in a slot connected to any of the finished signals.  Use @c QObject::deleteLater()
 * instead.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT SubscriptionStatusReply : public DigitalGoodReply
{
    Q_OBJECT

	/*!
	 * @brief Whether the subscription is active
	 *
	 * @details If the request finished successfully, then this returns whether the subscription is active.
     * If the request failed or is unfinished, then @c false is returned.
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(bool active READ isActive CONSTANT)

public:

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SubscriptionStatusReply();

    /*!
     * @brief Whether the subscription is active.
     *
     * @details If the request finished successfully, then this returns whether the subscription is active.
     * If the request failed or is unfinished, then @c false is returned.
     *
     * @return Whether the subscription is active.
     *
     * @since BlackBerry 10.0.0
     */
    bool isActive() const;

private:
//!@cond PRIVATE
    explicit SubscriptionStatusReply(QObject *parent = 0);
    Q_DISABLE_COPY(SubscriptionStatusReply);
    Q_DECLARE_PRIVATE(SubscriptionStatusReply);
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::SubscriptionStatusReply)
#endif // BB_PLATFORM_SUBSCRIPTIONSTATUSREPLY_HPP
