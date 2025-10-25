/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_PLATFORM_PURCHASERECEIPT_HPP
#define BB_PLATFORM_PURCHASERECEIPT_HPP

#include <bb/platform/Global>
#include <bb/platform/DigitalGoodState>

#include <QDateTime>
#include <QScopedPointer>
#include <QString>
#include <QVariant>

namespace bb
{
namespace platform
{

class PurchaseReceiptPrivate;

/*!
 * @headerfile PurchaseReceipt.hpp <bb/platform/PurchaseReceipt>
 *
 * @brief A purchase receipt.
 *
 * @details Represents a receipt issued for a successful purchase of a digital good.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT PurchaseReceipt
{
public:
    /*!
     * @brief Creates an invalid @c PurchaseReceipt.
     *
     * @since BlackBerry 10.0.0
     */
    PurchaseReceipt();

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PurchaseReceipt();

    /*!
     * @brief Copy constructor.
     *
     * @details Creates a copy of a @c PurchaseReceipt.
     *
     * @param rhs The source @c PurchaseReceipt instance.
     *
     * @since BlackBerry 10.0.0
     */
    PurchaseReceipt(const PurchaseReceipt &rhs);

    /*!
     * @brief Assignment operator.
     *
     * @details Assigns a copy of a @c PurchaseReceipt.
     *
     * @param rhs The source @c PurchaseReceipt instance.
     *
     * @return The @c PurchaseReceipt instance.
     *
     * @since BlackBerry 10.0.0
     */
    PurchaseReceipt& operator=(const PurchaseReceipt &rhs);

    /*!
     * @brief Whether this @c PurchaseReceipt object contains valid information about a purchase.
     *
     * @return @c true if this @c PurchaseReceipt object contains valid information about a purchase; @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Gets the state of the digital good.
     *
     * @return The digital good state.
     *
     * @since BlackBerry 10.0.0
     */
    DigitalGoodState::Type state() const;

    /*!
     * @brief Returns whether or not a digital good is a subscription.
     *
     * @details A digital good is a subscription if its state is any
     * value except @c bb::platform::DigitalGoodState::Owned.
     *
     * @return @c true if the digital good is a subscription;
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSubscription() const;

    /*!
     * @brief Gets the date of purchase.
     *
     * @return The date of purchase.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime date() const;

    /*!
     * @brief Gets the ID of the purchased digital good.
     *
     * @details Gets the ID of the purchased digital good, or the
     * empty string if the good does not have a digital good ID.
     *
     * @return The digital good ID.
     *
     * @since BlackBerry 10.0.0
     */
    QString digitalGoodId() const;

    /*!
     * @brief Gets the SKU of the purchased digital good.
     *
     * @details Gets the SKU of the purchased digital good, or the
     * empty string if the good does not have a digital good SKU.
     *
     * @return The digital good SKU.
     *
     * @since BlackBerry 10.0.0
     */
    QString digitalGoodSku() const;

    /*!
     * @brief Gets the license key associated with the purchase.
     *
     * @return The license key.
     *
     * @since BlackBerry 10.0.0
     */
    QString licenseKey() const;

    /*!
     * @brief Gets the metadata associated with the digital good purchase.
     *
     * @details Gets the metadata associated with the digital good purchase,
     * or the empty string if no metadata was provided in the request.
     *
     * @return The purchase metadata.
     *
     * @since BlackBerry 10.0.0
     */
    QString purchaseMetadata() const;

    /*!
     * @brief Gets the extra parameters associated with the digital good purchase.
     *
     * @details Gets the extra parameters associated with the digital good purchase.
     * If no parameters were returned, then a default constructed @c QVariantMap is returned.
     *
     * @return The extra parameters.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap extraParameters() const;

    /*!
     * @brief Gets the purchase ID that uniquely identifies the purchase.
     *
     * @details The purchase ID is a unique value assigned by the Payment Service.
     *
     * @return The purchase ID.
     *
     * @since BlackBerry 10.0.0
     */
    QString purchaseId() const;

    /*!
     * @brief Gets the start date of the purchased digital good subscription.
     *
     * @details Gets the start date of the purchased digital good subscription.
     * If the purchased digital good is not a subscription, then a default
     * constructed @c QDateTime is returned.
     *
     * @return The subscription start date.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime startDate() const;

    /*!
     * @brief Gets the end date of the purchased digital good subscription.
     *
     * @details If the purchased digital good is not a subscription, then a default
     * constructed @c QDateTime is returned.
     *
     * @return The subscription end date.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime endDate() const;

    /*!
     * @brief Gets the initial period of the purchased digital good subscription.
     *
     * @details If the purchased digital good is not a subscription, then -1 is returned,
     * which indicates a invalid initial period.
     *
     * @return The subscription initial period, in days.
     *
     * @since BlackBerry 10.0.0
     */
    int initialPeriod() const;

private:
//!@cond PRIVATE
    QScopedPointer<PurchaseReceiptPrivate> d_ptr;
    Q_DECLARE_PRIVATE(PurchaseReceipt)
//!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_PURCHASERECEIPT_HPP
