/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEREQUEST_HPP
#define BB_SYSTEM_INVOKEREQUEST_HPP

#include <bb/system/Global>

#include <bb/system/InvokeSource>
#include <bb/system/InvokeTarget>
#include <bb/system/SecurityPerimeter>
#include <bb/system/FileTransferMode>

#include <QMetaType>
#include <QScopedPointer>
#include <QByteArray>
#include <QString>
#include <QUrl>
#include <QVariantMap>

namespace bb
{
namespace system
{

class InvokeRequestPrivate;

/*!
 * @headerfile InvokeRequest.hpp <bb/system/InvokeRequest>
 *
 * @brief Encapsulates a request to invoke a remote application, card or service.
 *
 * Clients send invoke messages to a target by creating an instance of @c InvokeRequest, 
 * populating it with data, and passing the object to @c InvokeManager::invoke(). An invoke 
 * messages must contain a MIME type. All other fields are optional.
 *
 * Targets handle invoke messages by connecting to the @c InvokeManager::invoked() signal and 
 * parsing the @c InvokeRequest object passed to their slot.
 *
 * Invoke requests can also belong to a specific invoke list. When the target of an invoke request
 * belongs to a invoke list, then the user will be able to navigate among the list targets
 * using gestures and keyboard shortcuts (@c bb::system::InvokeManager for more details).
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeRequest
{
public:
    /*!
     * @brief Creates a new @c InvokeRequest object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeRequest();

    /*!
     * @brief Creates a copy of an existing @c InvokeRequest object.
     *
     * @param other The source @c InvokeRequest object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeRequest(const InvokeRequest &other);

    /*!
     * @brief Destroys this @c InvokeRequest object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeRequest();

    /*!
     * @brief Copies the data of an existing @c InvokeRequest object to this object.
     *
     * @param other The source @c InvokeRequest object to copy.
     *
     * @return The @c InvokeRequest instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeRequest& operator=(const InvokeRequest &other);

    /*!
     * @brief Returns the source of this request.
     *
     * @details This property is set when the application receives an invocation request.
     *
     * @return The source of the request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::InvokeSource source() const;

    /*!
     * @brief Returns the identity of the receiver as stated in its BAR manifest file.
     *
     * @details If omitted, the invocation service performs brokering to find the most appropriate
     * target for the action and MIME type in this invocation request.
     *
     * Required: NO.
     *
     * @return The identity of the receiver or an empty string if invocation service should 
     *         perform brokering.
     *
     * @since BlackBerry 10.0.0
     */
    QString target() const;       

    /*!
     * @brief Returns the operation the client is asking the target to perform.
     *
     * @details Valid values are target-specific. If omitted, the invocation service or
     * target will choose an appropriate action based on the MIME type.
     *
     * Required: NO.
     *
     * @return The operation the client is asking the target to perform or an empty string if
     *         the invocation service or target should choose an appropriate action.
     *
     * @since BlackBerry 10.0.0
     */
    QString action() const;

    /*!
     * @brief Returns the format of the data sent to the target.
     *
     * @details The MIME type must be a valid Internet media type, such as "image/png".
     *
     * Required: YES.
     *
     * @return The Internet media type of the data.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Returns the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the MIME type, action, and/or data are sufficient
     * for the target to do its work.
     *
     * Required: NO.
     *
     * @return The uniform resource identifier (URI) sent to the target or an empty URI if the 
     *         target does not require a URI.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl uri() const;

    /*!
     * @brief Returns the file transfer mode for this request.
     *
     * @details The file transfer mode controls how a file specified by the URI in an
     * invocation request (if present) is transferred to the target.
     *
     * @details If omitted, the default transfer mode will apply.
     *
     * Required: NO.
     *
     * @return The file transfer mode for this request.  See @c bb::system::FileTransferMode
     * for the list of file transfer modes.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::FileTransferMode::Type fileTransferMode() const;

    /*!
     * @brief Returns the class of targets that will be considered for an unbound invocation.
     *
     * @details Required: NO.
     *
     * @see @c bb::system::InvokeTarget::Type for the list of individual target types.
     *
     * @note @c targetTypes() only applies to the @c InvokeRequest sent to the invocation framework.
     * It is not available in the @c InvokeRequest received by the invoked target.
     *
     * @return The class of targets that will be considered for an unbound invocation.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::InvokeTarget::Types targetTypes() const;

    /*!
     * @brief Returns the binary data sent to the target.
     *
     * @details Valid values are target-specific. If omitted, the specified MIME type, action,
     * and URI must be sufficient for the target to complete the request.
     *
     * Required: NO.
     *
     * @return The binary data sent to the target or an empty array if the target does not 
     *         require any data.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray data() const;

    /*!
     * @brief Returns the metadata sent to the target.
     *
     * @details Metadata is optional and can be included to pass additional information
     * to the target. It will be encoded as a JSON object and sent to the target.
     *
     * Required: NO.
     *
     * @return The metadata.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap metadata() const;
    
/*! @cond PRIVATE */
    /*!
     * @brief Returns the security perimeter requested for the target.
     *
     * @details Required: NO.
     *
     * @return The security perimeter for the request.  See @c bb::system::SecurityPerimeter
     * for the list of perimeters.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SecurityPerimeter::Type perimeter() const;
/*! @endcond */
    
    /*!
     * @brief Returns the list that this request belongs to.
     *
     * @details Requests can belong to lists that are navigable. This allows the user to
     * navigate to the previous and next items in the list.
     *
     * Required: NO.
     *
     * @return The list the request belongs to or @c 0 if the request should not belong to a list.
     *
     * @since BlackBerry 10.2.0
     */
    int listId() const;

    /*!
     * @brief Sets the identity of the receiver as stated in its BAR manifest.
     *
     * @details If omitted, the invocation service performs brokering to find the most
     * appropriate target for the action and MIME type in this invocation request.
     *
     * Required: NO.
     *
     * @param name The identity of the receiver or an empty string if invocation service 
     *             should perform brokering.
     *
     * @since BlackBerry 10.0.0
     */
    void setTarget(const QString &name);

    /*!
     * @brief Sets the operation the client is asking the target to perform.
     *
     * @details Valid values are target-specific. If omitted, the invocation service
     * or target will choose an appropriate action based on the MIME type.
     *
     * Required: NO.
     *
     * @param name The operation the client is asking the target to perform or an empty 
     *             string if the invocation service or target should choose an appropriate action.
     *
     * @since BlackBerry 10.0.0
     */
    void setAction(const QString &name);

    /*!
     * @brief Sets the format of the data sent to the target.
     *
     * @details The MIME type must be a valid Internet media type, such as "image/png".
     *
     * Required: YES.
     *
     * @param type The Internet media type of the data.
     *
     * @since BlackBerry 10.0.0
     */
    void setMimeType(const QString &type);

    /*!
     * @brief Sets the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the specified MIME type, action, and data must be sufficient for
     * the target to do its work.
     *
     * @note For URIs to local files, consider using @c QUrl::fromLocalFile() to construct a @c QUrl instance.
     *
     * Required: NO.
     *
     * @param uri The uniform resource identifier (URI) sent to the target or an empty URI if 
     *            the target does not require a URI.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(const QUrl &uri);

    /*!
     * @brief Sets the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the specified MIME type, action, and data must be sufficient for
     * the target to do its work.
     *
     * @note Use this method to pass a URI that is in human-readable format.
     * @note @c QUrl(const QString&) will be used for constructing the URI.
     *
     * Required: NO.
     *
     * @param uri A string representing the uniform resource identifier (URI) sent to the target,
     *            or an empty string if the target does not require a URI.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(const QString &uri);

    /*!
     * @brief Sets the uniform resource identifier (URI) sent to the target.
     *
     * @details If omitted, the specified MIME type, action, and data must be sufficient for
     * the target to do its work.
     *
     * @note Use this method to pass a URI that is in human-readable format in UTF-8 encoding.
     * @note @c QUrl(const QString&) will be used for constructing the URI.
     *
     * Required: NO.
     *
     * @param uri A character array representing the uniform resource identifier (URI) sent to the target,
     *            or an empty character array if the target does not require a URI.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(const char *uri);

    /*!
     * @brief Sets the file transfer mode for the request.
     *
     * @details The file transfer mode controls how a file specified by the URI in an
     * invocation request (if present) is transferred to the target.
     *
     * Required: NO.
     *
     * @param fileTransferMode The file transfer mode for this request.  See
     * @c bb::system::FileTransferMode for the list of file transfer modes.
     *
     * @since BlackBerry 10.0.0
     */
    void setFileTransferMode(bb::system::FileTransferMode::Type fileTransferMode);

    /*!
     * @brief Sets the binary data sent to the target.
     *
     * @details Valid values are target-specific. If omitted, the specified MIME type, action
     * and URI must be sufficient for the target to complete the request.
     *
     * Required: NO.
     *
     * @param data The binary data sent to the target or an empty array if the target does 
     *             not require any data.
     *
     * @since BlackBerry 10.0.0
     */
    void setData(const QByteArray &data);

    /*!
     * @brief Sets the metadata sent to the target.
     *
     * @details Metadata is optional and can be included to pass additional information to the
     * target. It will be encoded as a JSON object and sent to the target.
     *
     * Required: NO.
     *
     * @param metadata The metadata to be sent to the target.
     *
     * @since BlackBerry 10.0.0
     */
    void setMetadata(const QVariantMap &metadata);

/*! @cond PRIVATE */
    /*!
      * @brief Sets the security perimeter in which the target should be invoked.
      *
      * @details Required: NO.
      *
      * The service can override this value to invoke the target in the same perimeter as the calling application based on its permissions.
      *
      * @param perimeter The security perimeter for the invoked target.  See @c bb::system::SecurityPerimeter for the list of valid values.
     *
     * @since BlackBerry 10.0.0
      */
    void setPerimeter(bb::system::SecurityPerimeter::Type perimeter);
/*! @endcond */

    /*!
     * @brief Sets the list that this request belongs to.
     *
     * @details Requests can belong to lists that are navigable. This allows the user to
     * navigate to the previous and next items in the list. @c bb::system::InvokeManager
     * includes signals and functions that allow for list operations.
     *
     * @note The invoke target must have a list-compatible @c bb::system::InvokeTarget::Type
     * for list navigation to be enabled. @c bb::system::InvokeTarget::Card is currently the
     * only list-enabled type.
     *
     * @note An application can have only one currently active list.
     *
     * Required: NO.
     *
     * @param listId The list the request belongs to or @c 0 if the request should not belong to a list.
     *
     * @since BlackBerry 10.2.0
     */
    void setListId(int listId);

    /*!
     * @brief Sets the class of targets that will be considered for an unbound invocation.
     *
     * @details Required: NO.
     *
     * @note @c targetTypes() only applies to the @c InvokeRequest sent to the invocation framework.
     * It is not available in the @c InvokeRequest received by the invoked target.
     *
     * @param types The class of targets that will be considered for an unbound invocation.  See
     * @c bb::system::InvokeTarget::Type for the list of individual target types.
     *
     * @since BlackBerry 10.0.0
     */
    void setTargetTypes(bb::system::InvokeTarget::Types types);

private:
//!@cond PRIVATE
    QScopedPointer<InvokeRequestPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeRequest)
//!@endcond
};

} // namespace system
} // namespace bb

Q_DECLARE_METATYPE(bb::system::InvokeRequest)

#endif // BB_SYSTEM_INVOKEREQUEST_HPP
