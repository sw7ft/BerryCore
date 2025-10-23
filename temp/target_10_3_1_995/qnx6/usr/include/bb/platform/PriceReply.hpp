/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_PRICEREPLY_HPP
#define BB_PLATFORM_PRICEREPLY_HPP

#include <bb/platform/DigitalGoodReply>
#include <bb/platform/Global>
#include <bb/platform/PurchaseReceipt>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class PriceReplyPrivate;

/*!
 * @headerfile PriceReply.hpp <bb/platform/PriceReply>
 *
 * @brief Represents a response to @c PaymentManager::requestPrice().
 *
 * @details An instance of this class is returned when a @c PaymentManager::requestPrice() is made.  Initially, the returned object
 * will be unfinished and will not contain any valid information relating to the request (other than
 * that it is unfinished).  Once the request is finished, @c PaymentReply::isError() can be used to determine whether the request succeeded or failed.
 * If the request was successful, then the @c price() method provides the price of the digital good.
 * If the request failed, then the error code and error text are included; these can be accessed on
 * the @c PaymentReply base class.
 *
 * The @c finished() signal can be used to determine when the request finishes.  The
 * @c PaymentManager::priceFinished() signal can also be used to determine when a request finishes.
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
class BB_PLATFORM_EXPORT PriceReply : public DigitalGoodReply
{
    Q_OBJECT

	/*!
	 * @brief Represents the price.
	 *
	 * @details The price of the digital good.
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString price READ price CONSTANT)

public:

    /*!
     * @brief Destructor.
     *
     * @details Destroys a @c PriceReply instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PriceReply();

    /*!
     * @brief Gets the price of a digital good.
     *
     * @details If the request finished successful, then the price is returned.
     * If the request failed or is unfinished, then the empty string is returned.
     *
     * @return The price of the digital good.
     *
     * @since BlackBerry 10.0.0
     */
    QString price() const;

protected:
//!@cond PRIVATE
    PriceReply(PriceReplyPrivate *priceReplyPrivate, QObject *parent);
//!@endcond

private:
//!@cond PRIVATE
    explicit PriceReply(QObject *parent = 0);
    Q_DISABLE_COPY(PriceReply);
    Q_DECLARE_PRIVATE(PriceReply);
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::PriceReply)
#endif // BB_PLATFORM_PRICEREPLY_HPP
