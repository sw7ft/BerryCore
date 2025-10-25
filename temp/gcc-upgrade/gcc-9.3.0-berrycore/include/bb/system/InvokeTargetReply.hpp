/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKETARGETREPLY_HPP
#define BB_SYSTEM_INVOKETARGETREPLY_HPP

#include <bb/system/Global>
#include <bb/system/InvokeReply>
#include <bb/system/InvokeAction>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace system
{

class InvokeTargetReplyPrivate;

/*!
 * @headerfile InvokeTargetReply.hpp <bb/system/InvokeTargetReply>
 *
 * @brief Encapsulates the result from an invocation request.
 *
 * @details When a client sends an invocation request to the invocation service it subsequently
 * receives a reply message indicating the success of the request.
 * To handle the reply message connect to the @c InvokeTargetReply::finished() signal of the
 * object returned by @c InvokeManager::invoke(). This
 * method is asynchronous and returns immediately, using the returned @c InvokeTargetReply object as a future.
 * Consequently, the values returned by the @c error(), @c target() and @c targetType() methods are not
 * valid until the reply message arrives (when @c finished() is emitted).
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeTargetReply : public InvokeReply
{
    Q_OBJECT
public:
    /*!
     * @brief Creates a new @c InvokeTargetReply object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit InvokeTargetReply(QObject *parent = 0);

    /*!
     * @brief Destroys this @c InvokeTargetReply object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~InvokeTargetReply();

    /*!
     * @brief Returns the target that has been invoked.
     *
     * @details An empty @c QString is returned if the request includes a specific target.
     *
     * @return The invoked target.
     *
     * @since BlackBerry 10.0.0
     */
    QString target() const;

    /*!
     * @brief Returns the type of the target that has been invoked.
     *
     * @return The invoked target type.  See @c bb::system::InvokeTarget::Type for this list of
     * target types.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::InvokeTarget::Type targetType() const;

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(InvokeTargetReply)
    Q_DISABLE_COPY(InvokeTargetReply)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKETARGETREPLY_HPP
