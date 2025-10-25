/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_PURCHASEREPLY_HPP
#define BB_PLATFORM_PURCHASEREPLY_HPP

#include <bb/platform/DigitalGoodReply>
#include <bb/platform/Global>
#include <bb/platform/PurchaseReceipt>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class PurchaseReplyPrivate;

/*!
 * @headerfile PurchaseReply.hpp <bb/platform/PurchaseReply>
 *
 * @brief Represents a response to @c PaymentManager::requestPurchase().
 *
 * @details An instance of this class is returned when a @c PaymentManager::requestPurchase() is made.  Initially, the returned object
 * will be unfinished and not contain any valid information relating to the request (other than
 * that it is unfinished).  Once the request is finished, @c PaymentReply::isError() can be used to determine whether the request succeeded or failed.
 * If the request was successful, then the @c receipt() method provides a purchase receipt with details of the purchase.
 * If the request failed, then the error code and error text are included; these can be accessed on
 * the @c PaymentReply base class.
 *
 * The @c finished() signal can be used to determine when the request finishes.  The
 * @c PaymentManager::purchaseFinished() signal can also be used to determine when a request finishes.
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
class BB_PLATFORM_EXPORT PurchaseReply : public DigitalGoodReply
{
	Q_OBJECT

	/*!
	 * @brief Represents the purchase metadata
	 *
	 * @details If the request finished successfully, then the purchase metadata is returned.
	 *
	 * If no metadata was provided in the request, then metadata is empty.
	 *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(QString purchaseMetadata READ purchaseMetadata CONSTANT)

	/*!
	 * @brief Represents the purchase receipt
	 *
	 * @details If the request finished successfully, then the purchase receipt is returned.
	 *
     * If the request failed or is unfinished, then an invalid purchase receipt is returned.
     *
     * The keys match the properties in @c bb::platform::PurchaseReceipt:
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
	Q_PROPERTY(QVariantMap receipt READ receiptQML CONSTANT)

public:

    /*!
     * @brief Destructor.
     *
     * @details Destroys a @c PurchaseReply instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PurchaseReply();

    /*!
     * @brief Gets the receipt from a successful purchase response.
     *
     * @details If the request finished successfully, then the purchase receipt is returned.
     * If the request failed or is unfinished, then an invalid purchase receipt is returned.
     *
     * @return The purchase receipt.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::PurchaseReceipt receipt() const;

    /*!
     * @brief Gets the purchase metadata from an error purchase response.
     *
     * @details If the request finished successfully, then the purchase metadata is returned.
     * If the request failed or is unfinished, then the empty string is returned.
     * 
     * If no metadata was provided in the request, then metadata is empty.
     *
     * @return The purchase metadata, if passed in the request.
     *
     * @since BlackBerry 10.0.0
     */
    QString purchaseMetadata() const;


private:
//!@cond PRIVATE
    explicit PurchaseReply(QObject *parent = 0);
    QVariantMap receiptQML() const;
    Q_DISABLE_COPY(PurchaseReply);
    Q_DECLARE_PRIVATE(PurchaseReply);
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::PurchaseReply)
#endif // BB_PLATFORM_PURCHASEREPLY_HPP
