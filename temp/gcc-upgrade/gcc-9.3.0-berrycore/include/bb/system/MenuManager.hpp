/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_MENUMANAGER_HPP
#define BB_SYSTEM_MENUMANAGER_HPP

#include <bb/system/Global>
#include <bb/system/InvokeTarget>
#include <bb/system/MenuManagerError>
#include <bb/system/Menu>
#include <bb/system/SecurityPerimeter>
#include <bb/system/FileTransferMode>

#include <QObject>
#include <QScopedPointer>
#include <QUrl>
#include <QtCore/QVariantMap>

namespace bb
{
namespace system
{

class MenuManagerPrivate;

/*!
 * @headerfile MenuManager.hpp <bb/system/MenuManager>
 *
 * @brief An interface for populating a menu of invokable items.
 *
 * The menu service provides common context-aware logic for building menus. It
 * can construct menus based on a specified type of data. The menu service
 * uses the data, its type, and the context in which the data is being acted on
 * to build a menu and populate it with information to be displayed and with the
 * actions to be performed when an item in the menu is selected.
 *
 * To build a menu of invokable items, create an instance of
 * the @c MenuManager class, populate the required parameters
 * using the setter methods, and call @c populateMenu() to send
 * the request.
 *
 * The menu service populates menus based on the context of the
 * data being acted upon. The data being acted upon can be specified
 * using a combination of URI, MIME type, and the data being acted upon.
 * Typically, the data will be specified using one of these combinations:
 * - Specify the URI to the data. The type of the data will be inferred by
 *   the menu service.
 * - Specify the URI to the data and the MIME type of the data to which the URI refers.
 * - Specify the data and its MIME type.
 *
 * If all three properties are specified, then the MIME type shall be
 * assumed to be the MIME type of the data referenced by the URI.
 *
 * Connect to the @c finished() signal to receive a notification that
 * the menu service has completed the request. Call @c error() to
 * check that the request was successful; if so, retrieve the
 * populated menu using @c menu().
 *
 * Here's an example of how to send a request, receive the response,
 * and read the menu data.
 *
 * @code
 *
 * // Populate the query parameters.
 * bb::system::MenuManager *_menuManager = new MenuManager;
 * _menuManager->setUri(QUrl("file://path/to/file"));
 * _menuManager->setTargetTypes(InvokeTarget::Application);
 *
 * // Connect to the finished() signal.
 * connect(_menuManager, SIGNAL(finished()), this, SLOT(onFinished()));
 *
 * // Send the request to have the menu populated.
 * if (_menuManager->populateMenu() != true) {
 *     // Handle the error.
 * }
 *
 * @endcode
 *
 * @code
 * // Define a slot to receive the finished() signal.
 * Q_SLOT void onFinished()
 * {
 *     // Check for errors.
 *     if (_menuManager->error() != MenuManagerError::None) {
 *         // Handle the error.
 *     } else {
 *         // The menu was populated. Retrieve the data.
 *         bb::system::Menu = _menuManager->menu();
 *     }
 * }
 *
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT MenuManager : public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c MenuManager object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MenuManager(QObject *parent = 0);

    /*!
     * @brief Destroys this @c MenuManager object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MenuManager();

    /*!
     * @brief Sets the action to be used to filter the invoke target results.
     * If no action is provided, all actions will be considered.
     *
     * Required: NO
     *
     * @param action The action to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setAction(const QString &action);

    /*!
     * @brief Sets the MIME type of the data to be acted on.
     *
     * @details If a URI
     * is specified, the MIME type is not required and the menu service
     * will infer the type of data being acted upon. If a URI is
     * not specified, then the MIME type is required.
     *
     * Required: YES, if the URI is not set; NO, if
     *           a URI is set.
     *
     * @param mimeType The MIME type of the data to be acted on.
     *
     * @since BlackBerry 10.0.0
     */
    void setMimeType(const QString &mimeType);

    /*!
     * @brief Sets the URI of the data for which the menu applies.
     *
     * @note For URIs to local files, consider using @c QUrl::fromLocalFile() to construct a @c QUrl instance.
     *
     * @param uri The URI of the data.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(QUrl uri);

    /*!
     * @brief Sets the file transfer mode of the data for which the menu applies.
     *
     * @details The file transfer mode will be applied if the scheme of the URI is @c "file://"
     * and the path references a file that is not in the shared area.
     *
     * @param fileTransferMode The file transfer mode of the data.  See @c bb::system::FileTransferMode
     * for the list of possible transfer modes.
     *
     * @since BlackBerry 10.0.0
     */
    void setFileTransferMode(bb::system::FileTransferMode::Type fileTransferMode);

    /*!
     * @brief Sets the data to be acted upon.
     *
     * @param data The data to be acted upon.
     *
     * @since BlackBerry 10.0.0
     */
    void setData(const QByteArray &data);

    /*!
     * @brief Sets the metadata associated with the invocation.
     *
     * @details Metadata is optional and can be included to pass additional information
     * to the target. It will be encoded as a JSON object and sent to the target.
     *
     * @param metadata The metadata to be associated with the invocation.
     *
     * @since BlackBerry 10.0.0
     */
    void setMetadata(const QVariantMap &metadata);

    /*!
     * @brief Sets the target types, which indicate the types
     * of targets to consider when building the menu.
     *
     * Required: NO
     *
     * @param types The target types.  See @c bb::system::InvokeTarget::Type for the list
     * of individual target types.
     *
     * @note The menu service does not construct menus that contain
     * viewer targets. Therefore, @c bb::system::InvokeTarget::Viewer is not a
     * valid value. The menu service will reject queries that contain
     * @c bb::system::InvokeTarget::Viewer as a target type.
     *
     * @since BlackBerry 10.0.0
     */
    void setTargetTypes(InvokeTarget::Types types);

/*! @cond PRIVATE */
    /*!
     * @brief Sets the perimeter in which the selected action is
     * to be invoked.
     *
     * Required: NO
     *
     * @param perimeter The perimeter in which the selected action is to be invoked.
     * See @c bb::system::SecurityPerimeter for the list of perimeters.
     *
     * @since BlackBerry 10.0.0
     */
    void setPerimeter(SecurityPerimeter::Type perimeter);
/*! @endcond */

    /*!
     * @brief Sets the target key to be used to filter the invoke target results.
     * If no target key is provided, all target keys will be considered.
     *
     * Required: NO
     *
     * @param targetKey The target key to set.
     *
     * @since BlackBerry 10.3.0
     */
    void setTargetKey(const QString &targetKey);

    /*!
     * @brief Returns the action.
     *
     * @return The action.
     *
     * @since BlackBerry 10.0.0
     */
    QString action() const;

    /*!
     * @brief Returns the MIME type of the data to be acted upon.
     *
     * @return The MIME type of the data.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Returns the URI of the data for which the menu applies.
     *
     * @return The URI of the data.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl uri() const;

    /*!
     * @brief Returns the file transfer mode of the data for which the menu applies.
     *
     * @details The file transfer mode will be applied if the scheme of the URI is @c "file://"
     * and the path references a file that is not in the shared area.
     *
     * @return The file transfer mode of the data.  See @c bb::system::FileTransferMode for the list
     * of file transfer modes.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::FileTransferMode::Type fileTransferMode() const;

    /*!
     * @brief Returns the data that is to be acted on.
     *
     * @return The data to be acted on.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray data() const;

    /*!
     * @brief Returns the metadata associated with the invocation.
     *
     * @details Metadata is optional and can be included to pass additional information
     * to the target. It will be encoded as a JSON object and sent to the target.
     *
     * @return The metadata.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap metadata() const;

    /*!
     * @brief Returns the target types.
     *
     * @return The target types.  See @c bb::system::InvokeTarget::Type for the list of individual target types.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTarget::Types targetTypes() const;

/*! @cond PRIVATE */
    /*!
     * @brief Returns the perimeter in which the selected
     * action is to be invoked.
     *
     * @return The perimeter in which the action will be invoked.
     *
     * @since BlackBerry 10.0.0
     */
    SecurityPerimeter::Type perimeter() const;
/*! @endcond */

    /*!
     * @brief Returns the target key.
     *
     * @return The target key.
     *
     * @since BlackBerry 10.3.0
     */
    QString targetKey() const;

    /*!
     * @brief Sends a request to the menu service to populate a menu of invokable
     * items based on the properties set as criteria.
     *
     * It is recommended that the client only make one request at a time on the same @c MenuManager instance.
     * If a new request is made before receiving a reply from a previous request, the end result can be
     * indeterminate if the state of the @c MenuManager instance changes.  This can happen because
     * replies may be received in a different order than requests were made.
     *
     * @return @c true if the request was successful, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool populateMenu();

    /*!
     * @brief Returns the populated list of menu items.
     *
     * @details The returned menu is not valid until the @c finished()
     * signal has been emitted, and when @c error() returns @c MenuManagerError::None.
     *
     * @return The populated list of menu items, or an empty list if the menu has not been
     *         populated or if the request was unsuccessful.
     *
     * @since BlackBerry 10.0.0
     */
    Menu menu() const;

    /*!
     * @brief Returns the error code from the menu service.
     *
     * @details The error code is not
     * valid until the @c finished() signal has been emitted.
     *
     * @return The error code from the menu service.  See @c bb::system::MenuManagerError for
     * the list of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    MenuManagerError::Type error() const;

    /*!
     * @brief Checks whether a reply from the menu service has been received.
     *
     * @details If this method returns @c false, the values returned by the @c menu() and @c error() methods are not valid.
     * If this method returns @c true, the value returned by @c error() gives the status of the last request.
     * If the request was successful, @c menu() will return a valid, populated menu obtained from the menu service.
     *
     * @return @c true if a reply from the menu service has been received and this object
     *         is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isFinished() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when this object becomes valid.
     *
     * @details When this signal is received, the value returned by @c error() is valid.  If the request was successful,
     * @c menu() will return a valid, populated menu obtained from the menu service.
     *
     * @since BlackBerry 10.0.0
     */
    void finished();

private:
//!@cond PRIVATE
    QScopedPointer<MenuManagerPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(MenuManager)
    Q_DISABLE_COPY(MenuManager)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_MENUMANAGER_HPP

