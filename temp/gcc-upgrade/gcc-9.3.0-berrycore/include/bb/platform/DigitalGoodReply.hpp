/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_DIGITALGOODREPLY_HPP
#define BB_PLATFORM_DIGITALGOODREPLY_HPP

#include <bb/platform/Global>
#include <bb/platform/PaymentReply>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class DigitalGoodReplyPrivate;

/*!
 * @headerfile DigitalGoodReply.hpp <bb/platform/DigitalGoodReply>
 *
 * @brief Base class for @c PaymentManager replies for digital goods or subscriptions.
 *
 * @details This class provides common details for @c PaymentManager replies to digital good
 * or subscription-related requests.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT DigitalGoodReply : public PaymentReply
{
    Q_OBJECT

    /*!
	 * @brief Represents the digital good ID.
	 *
	 * @details If the request finished successfully, then this returns the digital good ID.
     * If the request failed or is unfinished, then the empty string is returned.
     *
     * If no digital good ID was provided in the request, then the digital good ID is empty.
     *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(QString digitalGoodId READ digitalGoodId CONSTANT)

    /*!
	 * @brief Represents the digital good SKU.
	 *
	 * @details If the request finished successfully, then this returns the digital good SKU.
     * If the request failed or is unfinished, then the empty string is returned.
     *
     * If no digital good SKU was provided in the request, then digital good SKU is empty.
     *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(QString digitalGoodSku READ digitalGoodSku CONSTANT)


public:
    /*!
     * @brief Destructor.
     *
     * @details Destroys a @c DigitalGoodReply instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~DigitalGoodReply();

    /*!
     * @brief Get the digital good ID.
     *
     * @details If the request finished successfully, then this returns the digital good ID.
     * If the request failed or is unfinished, then the empty string is returned.
     *
     * If no digital good ID was provided in the request, then the digital good ID is empty.
     *
     * @return The digital good ID.
     *
     * @since BlackBerry 10.0.0
     */
    QString digitalGoodId() const;

    /*!
     * @brief Get the digital good SKU.
     *
     * @details If the request finished successfully, then this returns the digital good SKU.
     * If the request failed or is unfinished, then the empty string is returned.
     *
     * If no digital good SKU was provided in the request, then digital good SKU is empty.
     *
     * @return The digital good SKU.
     *
     * @since BlackBerry 10.0.0
     */
    QString digitalGoodSku() const;

protected:
//!@cond PRIVATE
    DigitalGoodReply(DigitalGoodReplyPrivate *digitalGoodReplyPrivate, QObject *parent);
//!@endcond

private:
//!@cond PRIVATE
    Q_DISABLE_COPY(DigitalGoodReply);
    Q_DECLARE_PRIVATE(DigitalGoodReply);
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::DigitalGoodReply)
#endif // BB_PLATFORM_DIGITALGOODREPLY_HPP
