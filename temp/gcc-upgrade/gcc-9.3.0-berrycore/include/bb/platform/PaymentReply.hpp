/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_PAYMENTREPLY_HPP
#define BB_PLATFORM_PAYMENTREPLY_HPP

#include <bb/platform/Global>

#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class PaymentReplyPrivate;

/*!
 * @headerfile PaymentReply.hpp <bb/platform/PaymentReply>
 *
 * @brief Base class for all @c PaymentManager replies.
 *
 * @details This class provides the finished and error information for all @c PaymentManager replies.  Subclasses of
 * this class are returned for all @c PaymentManager request methods.  Initially, the returned object
 * will be unfinished and will not contain any valid information relating to the request (other than
 * that it is unfinished).  Once the request is finished, @c isError() can be used to determine whether the request succeeded or failed.
 * If the request was successful, then the subclass will provide data on the success result.
 * If the request failed, @c errorCode() will identify the nature of the error and, if applicable, @c errorInfo() will
 * provide more detail on the particular error that occurred.
 *
 * The @c finished() signal can be used to determine when the request finishes.  There are also signals on 
 * @c PaymentManager that can be to determine when a request finishes.
 *
 * @note Do not delete the object in a slot connected to the @c finished() signal.  Use @c QObject::deleteLater()
 * instead.
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT PaymentReply : public QObject
{
    Q_OBJECT

    /*!
	 * @brief Represents whether the request is finished.
	 *
	 * @details Whether the request is finished.
	 *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(bool finished READ isFinished CONSTANT)

    /*!
	 * @brief Represents the error text.
	 *
	 * @details If the request is unfinished or finished successfully, then this method returns an empty string.
     * If the request failed, then this method returns the a description of the error that occurred.
     *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(QString errorText READ errorText CONSTANT)

    /*!
	 * @brief Represents the error code.
	 *
	 * @details If the request is unfinished or finished successfully, then this method returns 0.
     * If the request failed, then this method returns the error code.
     *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(int errorCode READ errorCode CONSTANT)

	/*!
	 * @brief Get the extra error information.
	 *
	 * @details In the event of a @c Failed @c errorCode, this represents extra information to further identify
	 * the error that occurred, for diagnostic purposes.
	 *
	 * @since BlackBerry 10.2.0
	 */
	Q_PROPERTY(QString errorInfo READ errorInfo CONSTANT)


public:

    /*!
     * @brief Destructor.
     *
     * @details Destroys a @c PaymentReply.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PaymentReply();

    /*!
     * @brief Whether the request is finished.
     *
     * @return @c true if a result has been received, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isFinished() const;

    /*!
     * @brief Whether the request failed.
     *
     * @details If the request is unfinished or finished successfully, then this method returns @c false.
     * If the request failed, then this method returns @c true.
     *
     * @return Whether the request failed.
     *
     * @since BlackBerry 10.0.0
     */
    bool isError() const;

    /*!
     * @brief Get the error text.
     *
     * @details If the request is unfinished or finished successfully, then this method returns an empty string.
     * If the request failed, then this method returns the a description of the error that occurred.
     *
     * @return A description of the error that occurred.
     *
     * @since BlackBerry 10.0.0
     */
    QString errorText() const;

    /*!
     * @brief Get the error code.
     *
     * @details If the request is unfinished or finished successfully, then this method returns @c PaymentErrorCode::None.
     * If the request failed, then this method returns the appropriate @c PaymentErrorCode.
     *
     * @return The error code.
     *
     * @since BlackBerry 10.0.0
     */
    int errorCode() const;

    /*!
     * @brief Get the extra error information.
     *
     * @details In the event of a @c Failed @c errorCode(), this method returns extra information to further identify
     * the error that occurred, for diagnostic purposes.
     *
     * @return The extra error information.
     *
     * @since BlackBerry 10.2.0
     */
    QString errorInfo() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when a result is received.
     *
     * @since BlackBerry 10.0.0
     */
    void finished();

protected:
//!@cond PRIVATE
    PaymentReply(PaymentReplyPrivate *paymentReplyPrivate, QObject *parent);
    PaymentReplyPrivate * const d_ptr;
//!@endcond
private:
//!@cond PRIVATE
    Q_DISABLE_COPY(PaymentReply);
    Q_DECLARE_PRIVATE(PaymentReply);
//!@endcond
};

} // namespace
} // namespace

QML_DECLARE_TYPE(bb::platform::PaymentReply)
#endif // BB_PLATFORM_PAYMENTREPLY_HPP
