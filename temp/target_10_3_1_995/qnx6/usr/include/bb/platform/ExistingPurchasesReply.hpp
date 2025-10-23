/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_EXISTINGPURCHASESREPLY_HPP
#define BB_PLATFORM_EXISTINGPURCHASESREPLY_HPP

#include <bb/platform/Global>
#include <bb/platform/PaymentReply>
#include <bb/platform/PurchaseReceipt>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class ExistingPurchasesReplyPrivate;

/*!
 * @headerfile ExistingPurchasesReply.hpp <bb/platform/ExistingPurchasesReply>
 *
 * @brief Represents a response to @c PaymentManager::requestExistingPurchases().
 *
 * @details An instance of this class is returned when a call to @c PaymentManager::requestExistingPurchases() is made.
 * Initially, the returned object will be unfinished and will not contain any valid information relating to the
 * request (other than that it is unfinished).  Once the request is finished, @c PaymentReply::isError() can be
 * used to determine whether the request succeeded or failed.
 * If the request was successful, then the @c purchases() method provides the list of receipts for all existing purchases.
 * If the request failed, then the error code and error text are included; these can be accessed on
 * the @c PaymentReply base class.
 *
 * The @c finished() signal can be used to determine when the request finishes.  The
 * @c PaymentManager::existingPurchasesFinished() signal can also be used to determine when a request finishes.
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
class BB_PLATFORM_EXPORT ExistingPurchasesReply : public PaymentReply
{
    Q_OBJECT

	/*!
	 * @brief Represents the list of existing purhcase(s).
	 *
	 * @details If the request finished successfully, then a list of receipts for the user's purchases is returned.
     * If the request failed or is unfinished, then an empty list is returned.
     *
     * The elements of the list are @c QVariantMap objects whose keys match the properties in @c bb::platform::PurchaseReceipt:
     *	- date
     *	- digitalGoodId
     *	- digitalGoodSku
     *	- endDate
     *	- extraParameters
     *	- initialPeriod
     *	- isSubscription
     *	- isValid
     *	- licenseKey
     *	- purchaseId
     *	- purchaseMetadata
     *	- startDate
     *	- state
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QVariantList purchases READ purchaseQML CONSTANT)

public:

    /*!
     * @brief Destructor.
     *
     * @details Destroys an @c ExistingPurchasesReply instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ExistingPurchasesReply();

    /*!
     * @brief Get the list of user purchases.
     *
     * @details If the request finished successfully, then a list of receipts for the user's purchases is returned.
     * If the request failed or is unfinished, then an empty list is returned.
     *
     * @return A list of purchase receipts.
     *
     * @since BlackBerry 10.0.0
     */
    QList<PurchaseReceipt> purchases() const;

protected:
    //!@cond PRIVATE
	explicit ExistingPurchasesReply(QObject *parent = 0);
	//!@endcond

private:
//!@cond PRIVATE
    QVariantList purchaseQML() const;
	Q_DISABLE_COPY(ExistingPurchasesReply);
	Q_DECLARE_PRIVATE(ExistingPurchasesReply);
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::ExistingPurchasesReply)
#endif // BB_PLATFORM_EXISTINGPURCHASESREPLY_HPP
