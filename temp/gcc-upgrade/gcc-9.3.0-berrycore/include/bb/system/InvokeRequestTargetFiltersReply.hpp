/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEREQUESTTARGETFILTERSREPLY_HPP
#define BB_SYSTEM_INVOKEREQUESTTARGETFILTERSREPLY_HPP

#include <bb/system/Global>
#include <bb/system/InvokeReply>
#include <bb/system/InvokeTargetFilter>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace system
{

class InvokeRequestTargetFiltersReplyPrivate;

/*!
 * @headerfile InvokeRequestTargetFiltersReply.hpp <bb/system/InvokeRequestTargetFiltersReply>
 *
 * @brief Encapsulates the results from a request to retrieve a target's filters.
 *
 * @details When a client sends a request to get a target's set of filters to the invocation service
 * (using @c InvokeManager::requestTargetFilters()), it subsequently receives a reply message
 * containing the list of the target's filters. To handle the reply message, connect to the
 * @c InvokeRequestTargetFiltersReply::finished() signal of the object returned by
 * @c InvokeManager::requestTargetFilters().
 * This method is asynchronous, returning immediately and using the returned
 * @c InvokeRequestTargetFiltersReply as a future. Consequently, the value returned by the @c error()
 * method is not valid until the reply message arrives (when @c finished() is emitted).
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeRequestTargetFiltersReply : public InvokeReply
{
    Q_OBJECT
public:
    /*!
     * @brief Creates a new @c InvokeRequestTargetFiltersReply object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit InvokeRequestTargetFiltersReply(QObject *parent = 0);

    /*!
     * @brief Destroys this @c InvokeRequestTargetFiltersReply object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~InvokeRequestTargetFiltersReply();

    /*!
     * @brief Returns the target key to which the filters apply.
     *
     * @return The target key.
     *
     * @since BlackBerry 10.0.0
     */
    QString targetKey() const;

    /*!
     * @brief Returns the list of target filters from the reply message.
     *
     * @return The list of target filters from the reply message.
     *
     * @since BlackBerry 10.0.0
     */
    QList<InvokeTargetFilter> filters() const;

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(InvokeRequestTargetFiltersReply)
    Q_DISABLE_COPY(InvokeRequestTargetFiltersReply)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKEREQUESTTARGETFILTERSREPLY_HPP
