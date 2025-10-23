/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEUPDATETARGETFILTERSREQUEST_HPP
#define BB_SYSTEM_INVOKEUPDATETARGETFILTERSREQUEST_HPP

#include <bb/system/Global>

#include <bb/system/InvokeTargetFilter>

#include <QList>
#include <QMetaType>
#include <QScopedPointer>
#include <QString>


namespace bb
{
namespace system
{

class InvokeUpdateTargetFiltersRequestPrivate;

/*!
 * @headerfile InvokeUpdateTargetFiltersRequest.hpp <bb/system/InvokeUpdateTargetFiltersRequest>
 *
 * @brief Encapsulates a request to update a target's list of filters.
 *
 * @details Targets declare filters to describe the kinds of unbound invocations they support.
 * A target may specify a list of filters. Through unbound invocation (or query) a target will
 * only receive invocations that match one of its filters.  However, it may also receive bound
 * invocations that do not match any of its filters. A filter describes the action/MIME type/URI
 * combinations for which the target supports unbound invocation.
 *
 * Invoke targets can specify filters by declaring them in their BAR manifest. In addition,
 * a client that has ownership of a target can update the list of filters by creating the
 * desired filters using @c InvokeTargetFilter, creating a request to update a target's filters
 * (@c InvokeUpdateTargetFiltersRequest) and sending the request with @c InvokeManager::updateTargetFilters().
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeUpdateTargetFiltersRequest
{
public:
    /*!
     * @brief Creates a new @c InvokeUpdateTargetFiltersRequest object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeUpdateTargetFiltersRequest();

    /*!
     * @brief Creates a copy of an existing @c InvokeUpdateTargetFiltersRequest object.
     *
     * @param other The source @c InvokeUpdateTargetFiltersRequest object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeUpdateTargetFiltersRequest(const InvokeUpdateTargetFiltersRequest &other);

    /*!
     * @brief Destroys this @c InvokeUpdateTargetFiltersRequest object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeUpdateTargetFiltersRequest();

    /*!
     * @brief Copies the data of an existing @c InvokeUpdateTargetFiltersRequest object to this object.
     *
     * @param other The source @c InvokeUpdateTargetFiltersRequest object to copy.
     *
     * @return The @c InvokeUpdateTargetFiltersRequest instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeUpdateTargetFiltersRequest& operator=(const InvokeUpdateTargetFiltersRequest &other);

    /*!
     * @brief Returns the target for which the list of filters is to be updated.
     *
     * @return The target for which the list of filters will be updated.
     *
     * @since BlackBerry 10.0.0
     */
    QString target() const;       

    /*!
     * @brief Sets the target that will be updated with the new list of target filters.
     *
     * @details The client must own the target to update the target's list of filters.
     *
     * @param target The target to be updated with the new list of target filters.
     *
     * @since BlackBerry 10.0.0
     */
    void setTarget(const QString &target);

    /*!
     * @brief Returns the updated list of filters for the target.
     *
     * @return The updated list of filters for the target.
     *
     * @since BlackBerry 10.0.0
     */
    QList<InvokeTargetFilter> filters() const;

    /*!
     * @brief Sets the updated list of filters for the target.
     *
     * @details If any filter in the list is invalid, @c false is returned,
     * but the operation succeeds. See @c InvokeTargetFilter::isValid() for
     * details on valid target filters. If @c filters is an empty list,
     * the list of filters will be set and @c true will be returned.
     *
     * @param filters The updated list of filters for the target.
     *
     * @return Return @c true if the filter list is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool setTargetFilters(QList<InvokeTargetFilter> filters);

private:
    /*! @cond PRIVATE */
    QScopedPointer<InvokeUpdateTargetFiltersRequestPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeUpdateTargetFiltersRequest)
    /*! @endcond */
};

} // namespace system
} // namespace bb

Q_DECLARE_METATYPE(bb::system::InvokeUpdateTargetFiltersRequest)

#endif // BB_SYSTEM_INVOKEUPDATETARGETFILTERSREQUEST_HPP
