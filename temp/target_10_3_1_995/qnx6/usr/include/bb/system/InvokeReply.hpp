/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEREPLY_HPP
#define BB_SYSTEM_INVOKEREPLY_HPP

#include <bb/system/Global>
#include <bb/system/InvokeReplyError>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace system
{

class InvokeReplyPrivate;

/*!
 * @headerfile InvokeReply.hpp <bb/system/InvokeReply>
 *
 * @brief Encapsulates a reply from the invocation service.
 *
 * @details When a client sends an invoke or an update target filters request message to the
 * invocation service it subsequently receives a reply message indicating the success of
 * the request. To handle the reply message, connect to the @c InvokeReply::finished() signal of the
 * object returned by the method called to send the request
 * (@c InvokeManager::invoke() for an invoke request, @c InvokeManager::updateTargetFilters() for an update target filters request).
 * These methods are asynchronous, returning immediately and using the returned
 * @c InvokeReply object as a future. Consequently, the value returned by the @c error() method is not valid until the
 * reply message arrives (when @c finished() is emitted).
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeReply : public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c InvokeReply object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit InvokeReply(QObject *parent = 0);

    /*!
     * @brief Destroys this @c InvokeReply object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~InvokeReply();

    /*!
     * @brief Checks whether a reply message has been received.
     *
     * @details The value returned by the @c error() method is not valid until a reply message has been received.
     *
     * @return @c true if a reply message has been received, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isFinished() const;

    /*!
     * @brief Returns the error type from the reply message.
     *
     * @details The return value is not valid until a reply message has been received.
     * The error code can be retrieved via @c errorCode().
     *
     * @return The error type from the reply message.  See @c bb::system::InvokeReplyError for
     * the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::InvokeReplyError::Type error() const;

    /*!
     * @brief Returns the error code from the reply message.
     *
     * @details The return value is not valid until a reply message has been received.
     * The error type can be retrieved via @c error().
     *
     * @return The error code from the reply message.
     */
    int errorCode() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when a reply message is received.
     *
     * @details The value returned by the @c error() method is not valid until a reply message has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void finished();

protected:

//!@cond PRIVATE
    /*!
     * @brief Constructs an @c InvokeReply instance using an existing
     * private side object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     * @param invokePrivate The private side object.
     */
    InvokeReply(QObject *parent, InvokeReplyPrivate &invokePrivate);

    QScopedPointer<InvokeReplyPrivate> const d_ptr;
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(InvokeReply)
    Q_DISABLE_COPY(InvokeReply)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKEREPLY_HPP
