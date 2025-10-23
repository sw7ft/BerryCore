/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEQUERYTARGETSREQUEST_HPP
#define BB_SYSTEM_INVOKEQUERYTARGETSREQUEST_HPP

#include <bb/system/Global>
#include <bb/system/InvokeAction>
#include <bb/system/InvokeTarget>
#include <bb/system/SecurityPerimeter>

#include <QScopedPointer>
#include <QString>
#include <QUrl>

namespace bb
{
namespace system
{

class InvokeQueryTargetsRequestPrivate;

/*!
 * @headerfile InvokeQueryTargetsRequest.hpp <bb/system/InvokeQueryTargetsRequest>
 *
 * @brief Encapsulates a request to query invokable targets that match a set of search criteria.
 *
 * @details Clients discover available targets by creating an instance of 
 * @c InvokeQueryTargetsRequest, populating it with data, and passing the object to
 * @c InvokeManager::queryTargets().  Query messages must contain a target type, and must
 * further contain either a MIME type or a uniform resource identifier (URI) or both.
 * All other fields are optional and can be used to restrict the set of search results
 * further.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeQueryTargetsRequest
{
public:

    /*!
     * @brief Creates a new @c InvokeQueryTargetsRequest object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeQueryTargetsRequest();

    /*!
     * @brief Creates a copy of an existing @c InvokeQueryTargetsRequest object.
     *
     * @param other The source @c InvokeQueryTargetsRequest object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeQueryTargetsRequest(const InvokeQueryTargetsRequest &other);

    /*!
     * @brief Destroys this @c InvokeQueryTargetsRequest object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeQueryTargetsRequest();

    /*!
     * @brief Copies the data of an existing @c InvokeQueryTargetsRequest object to this
     * object.
     *
     * @param other The source @c InvokeQueryTargetsRequest object to copy.
     *
     * @return The @c InvokeQueryTargetsRequest instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeQueryTargetsRequest& operator=(const InvokeQueryTargetsRequest &other);

    /*!
     * @brief Returns the operation to be performed by the target.
     *
     * @details Valid values are target-specific. If omitted, search results are not
     * filtered by action.
     *
     * Required: NO.
     *
     * @return The operation to be performed by the target or an empty string to select 
     *         all available actions.
     *
     * @since BlackBerry 10.0.0
     */
    QString action() const;

    /*!
     * @brief Returns the format of the data sent to the target.
     *
     * @details The MIME type must be a valid Internet media type, such as "image/png". If omitted,
     * the MIME type will be inferred from the URI.
     *
     * Required: NO if a URI is provided, YES if no URI is specified.
     *
     * @return The Internet media type of the data or an empty string to select all 
     *         available types.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Returns the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the search results are not filtered by URI handler.
     *
     * Required: NO if a MIME type is provided, YES if no MIME type is specified.
     *
     * @return The uniform resource identifier (URI) sent to the target or an empty URI to 
     *         select all available URI handlers.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl uri() const;

    /*!
     * @brief Returns the class of targets used to filter the search results.
     *
     * @details Required: YES.
     *
     * @see @c bb::system::InvokeTarget::Type for the list of individual target types.
     *
     * @return The class of targets used to filter the search results.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTarget::Types targetTypes() const;

    /*!
     * @brief Returns the class of actions used to filter the search results.
     *
     * @details The default value is @c bb::system::InvokeAction::All.
     *
     * Required: YES.
     *
     * @see @c bb::system::InvokeAction::Type for the list of actions.
     *
     * @return The class of actions used to filter the search results.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeAction::Type actionType() const;

/*! @cond PRIVATE */
    /*!
     * @brief Returns the security perimeter requested for the search results.
     *
     * @details Required: NO.
     *
     * @see @c bb::system::SecurityPerimeter for the list of %perimeter types.
     * 
     * @return The security perimeter for the search results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SecurityPerimeter::Type perimeter() const;
/*! @endcond */

    /*!
     * @brief Sets the operation to be performed by the target.
     *
     * @details Valid values are target-specific. If omitted, search results are not
     * filtered by action.
     *
     * Required: NO.
     *
     * @param name The operation to be performed by the target or an empty string to 
     *             select all available actions.
     *
     * @since BlackBerry 10.0.0
     */
    void setAction(const QString &name);

    /*!
     * @brief Returns the format of the data sent to the target.
     *
     * @details The supplied type must be a valid Internet media type, such as "image/png". If omitted, search
     * results are not filtered by MIME type.
     *
     * Required: NO if a URI is provided, YES if no URI is specified.
     *
     * @param type The Internet media type of the data or an empty string to select all 
     *             available types.
     *
     * @since BlackBerry 10.0.0
     */
    void setMimeType(const QString &type);

    /*!
     * @brief Sets the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the search results are not filtered by URI handler.
     *
     * Required: NO if a MIME type is provided, YES if no MIME type is specified.
     *
     * @param uri The uniform resource identifier (URI) sent to the target or an empty URI 
     *            to select all available URI handlers.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(const QUrl &uri);

    /*!
     * @brief Sets the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the search results are not filtered by URI handler.
     *
     * Required: NO if a MIME type is provided, YES if no MIME type is specified.
     *
     * @param uri A string representing the uniform resource identifier (URI) sent to the 
     *            target, or an empty string to select all available URI handlers.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(const QString &uri);

    /*!
     * @brief Sets the class of targets used to filter the search results.
     *
     * @details Required: YES.
     *
     * @param types The class of targets used to filter the search results.  See
     * @c bb::system::InvokeTarget::Type for the list of individual target types.
     *
     * @since BlackBerry 10.0.0
     */
    void setTargetTypes(InvokeTarget::Types types);

    /*!
     * @brief Sets the class of actions used to filter the search results.
     *
     * @details The default value is @c bb::system::InvokeAction::All.
     *
     * Required: YES.
     *
     * @param type The class of actions used to filter the search results.  See
     * @c bb::system::InvokeAction::Type for the list of actions.
     *
     * @since BlackBerry 10.0.0
     */
    void setActionType(InvokeAction::Type type);

/*! @cond PRIVATE */
    /*!
      * @brief Sets the security perimeter in which the search result targets should reside.
      *
      * @details Required: NO.
      *
      * The service can override this value to restrict the results to the calling application's perimeter based on its permissions.
      *
      * @param perimeter The security perimeter for the search results.  See @c bb::system::SecurityPerimeter for the
      * list of perimeters.
     *
     * @since BlackBerry 10.0.0
      */
     void setPerimeter(bb::system::SecurityPerimeter::Type perimeter);
/*! @endcond */
     
private:
//!@cond PRIVATE
    QScopedPointer<InvokeQueryTargetsRequestPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeQueryTargetsRequest)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKEQUERYTARGETSREQUEST_HPP
