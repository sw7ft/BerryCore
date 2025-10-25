/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEQUERYTARGETSREPLY_HPP
#define BB_SYSTEM_INVOKEQUERYTARGETSREPLY_HPP

#include <bb/system/Global>
#include <bb/system/InvokeReply>
#include <bb/system/InvokeAction>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace system
{

class InvokeQueryTargetsReplyPrivate;

/*!
 * @headerfile InvokeQueryTargetsReply.hpp <bb/system/InvokeQueryTargetsReply>
 *
 * @brief Encapsulates the set of results from a query request.
 *
 * @details When a client sends a query message to the invocation service it subsequently 
 * receives a reply message indicating the success of the request and the results of the 
 * search. To handle the reply message, connect to the @c InvokeQueryTargetsReply::finished()
 * signal of the object returned by @c InvokeManager::queryTargets(). This 
 * method is asynchronous returning immediately and using @c InvokeQueryTargetsReply as a future.
 * Consequently, the values returned by the @c error() and @c actions() methods are not valid until
 * the reply message arrives (when @c finished() is emitted).
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeQueryTargetsReply : public InvokeReply
{
    Q_OBJECT
public:
    /*!
     * @brief Creates a new @c InvokeQueryTargetsReply object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit InvokeQueryTargetsReply(QObject *parent = 0);

    /*!
     * @brief Destroys this @c InvokeQueryTargetsReply object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~InvokeQueryTargetsReply();

    /*!
     * @brief Returns the list of matching targets, grouped by action, from the reply message.
     *
     * @return The list of matching targets from the reply message.
     *
     * @since BlackBerry 10.0.0
     */
    QList<InvokeAction> actions() const;

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(InvokeQueryTargetsReply)
    Q_DISABLE_COPY(InvokeQueryTargetsReply)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKEQUERYTARGETSREPLY_HPP
