/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_CANCELSUBSCRIPTIONREPLY_HPP
#define BB_PLATFORM_CANCELSUBSCRIPTIONREPLY_HPP

#include <bb/platform/Global>
#include <bb/platform/PaymentReply>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class CancelSubscriptionReplyPrivate;

/*!
 * @headerfile CancelSubscriptionReply.hpp <bb/platform/CancelSubscriptionReply>
 *
 * @brief Represents a response to @c PaymentManager::requestCancelSubscription().
 *
 * @details An instance of this class is returned when a call to @c PaymentManager::requestCancelSubscription is made.  Initially, the returned object
 * will be unfinished and will not contain any valid information relating to the request (other than
 * that it is unfinished).  Once the request is finished, @c PaymentReply::isError() can be used to determine whether the request succeeded or failed.
 * If the request was successful, then the @c isCanceled() method indicates whether the subscription
 * was canceled.
 * If the request failed, then the error code and error text are included; these can be accessed on
 * the @c PaymentReply base class.
 *
 * The @c finished() signal can be used to determine when the request finishes.  The
 * @c PaymentManager::cancelSubscriptionFinished signal can also be used to determine when a request finishes.
 *
 * @note A successful response does not indicate that the subscription was canceled.  The request is
 * successful if the BlackBerry World server can be contacted and the purchase could be located. It is possible for
 * a successful request to have not canceled the subscription.  In this case, @c PaymentReply::isError() and
 * @c isCanceled() will both return @c false.
 *
 * @note Do not delete the object in a slot connected to the any of the finished signals.  Use @c QObject::deleteLater()
 * instead.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT CancelSubscriptionReply : public PaymentReply
{
    Q_OBJECT

	/*!
	 * @brief Represents the result of a cancel subscription request.
	 *
	 * @details If the request finished successfully, then this returns whether the subscription was successfully canceled.
     * If the request failed or is unfinished, then @c false is returned.
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(bool canceled READ isCanceled CONSTANT)

	/*!
	 * @brief Represents the purchase id .
	 *
	 * @details The purchase id passed to @c PaymentManager::requestCancelSubscription().
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString purchaseId READ purchaseId CONSTANT)

public:

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CancelSubscriptionReply();

    /*!
     * @brief Whether the subscription was successfully canceled.
     *
     * @details If the request finished successfully, then this returns whether the subscription was successfully canceled.
     * If the request failed or is unfinished, then @c false is returned.
     *
     * @note A successful response does not indicate that the subscription was canceled.  The request is
     * successful if the BlackBerry World server can be contacted and the purchase could be located. It is possible for
     * a successful request to have not canceled the subscription.  In this case, @c PaymentReply::isError() and
     * @c isCanceled() will both return @c false.
     *
     * @return Whether the subscription was successfully canceled.
     *
     * @since BlackBerry 10.0.0
     */
    bool isCanceled() const;

    /*!
     * @brief Get the purchase id.
     *
     * @return The purchase id passed to @c PaymentManager::requestCancelSubscription().
     *
     * @since BlackBerry 10.0.0
     */
    QString purchaseId() const;

private:
//! @cond PRIVATE
    explicit CancelSubscriptionReply(QObject *parent = 0);
    Q_DISABLE_COPY(CancelSubscriptionReply);
    Q_DECLARE_PRIVATE(CancelSubscriptionReply);
//! @endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::CancelSubscriptionReply)
#endif // BB_PLATFORM_CANCELSUBSCRIPTIONREPLY_HPP
