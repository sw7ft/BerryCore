/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_SUBSCRIPTIONTERMSREPLY_HPP
#define BB_PLATFORM_SUBSCRIPTIONTERMSREPLY_HPP

#include <bb/platform/Global>
#include <bb/platform/PriceReply>
#include <bb/platform/PurchaseReceipt>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class SubscriptionTermsReplyPrivate;

/*!
 * @headerfile SubscriptionTermsReply.hpp <bb/platform/SubscriptionTermsReply>
 *
 * @brief Represents a response to @c PaymentManager::requestSubscriptionTerms().
 *
 * @details An instance of this class is returned when a call to @c PaymentManager::requestSubscriptionStatus() is made.  Initially, the returned object
 * will be unfinished and not contain any valid information relating to the request (other than
 * that it is unfinished).  Once the request is finished, @c PaymentReply::isError() can be used to determine whether the request succeeded or failed.
 * If the request was successful, then the @c initialPeriod(), @c renewalPrice(), @c renewalPeriod(), and
 * @c PriceReply::price() methods provide the subscription terms.
 * If the request failed, then the error code and error text are included; these can be accessed on
 * the @c PaymentReply base class.
 *
 * The @c PaymentReply::finished() signal can be used to determine when the request finishes.  The
 * @c PaymentManager::subscriptionTermsFinished() signal can also be used to determine when a request finishes.
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
class BB_PLATFORM_EXPORT SubscriptionTermsReply : public PriceReply
{
    Q_OBJECT

	/*!
	 * @brief The initial period of the subscription
	 *
	 * @details If the request finished successfully, then this returns the initial period.
     * If the request failed or is unfinished, then an empty string is returned.
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString initialPeriod READ initialPeriod CONSTANT)

	/*!
	 * @brief The renewal price of the subscription.
	 *
	 * @details If the request finished successfully, then this returns the renewal price.
     * If the request failed or is unfinished, then an empty string is returned.
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString renewalPrice READ renewalPrice CONSTANT)

	/*!
	 * @brief The renewal period of the subscription.
	 *
	 * @details If the request finished successfully, then this returns the renewal period.
     * If the request failed or is unfinished, then an empty string is returned.
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString renewalPeriod READ renewalPeriod CONSTANT)

public:

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SubscriptionTermsReply();

    /*!
     * @brief Get the initial period of the subscription.
     *
     * @details If the request finished successfully, then this returns the initial period.
     * If the request failed or is unfinished, then an empty string is returned.
     *
     * @return The initial period of the subscription.
     *
     * @since BlackBerry 10.0.0
     */
    QString initialPeriod() const;

    /*!
     * @brief Get the renewal price of the subscription.
     *
     * @details If the request finished successfully, then this returns the renewal price.
     * If the request failed or is unfinished, then an empty string is returned.
     *
     * @return The renewal price of the subscription.
     *
     * @since BlackBerry 10.0.0
     */
    QString renewalPrice() const;

    /*!
     * @brief Get the renewal period of the subscription.
     *
     * @details If the request finished successfully, then this returns the renewal period.
     * If the request failed or is unfinished, then an empty string is returned.
     *
     * @return The renewal period of the subscription.
     *
     * @since BlackBerry 10.0.0
     */
    QString renewalPeriod() const;

private:
//!@cond PRIVATE
    explicit SubscriptionTermsReply(QObject *parent = 0);
    Q_DISABLE_COPY(SubscriptionTermsReply);
    Q_DECLARE_PRIVATE(SubscriptionTermsReply);
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::SubscriptionTermsReply)
#endif // BB_PLATFORM_SUBSCRIPTIONTERMSREPLY_HPP
