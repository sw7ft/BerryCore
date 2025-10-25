/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATION_HPP
#define BB_PLATFORM_NOTIFICATION_HPP

#include <bb/platform/Global>

#include <bb/platform/NotificationError>
#include <bb/platform/NotificationResult>
#include <bb/platform/NotificationType>

#include <bb/system/InvokeRequest>

#include <QObject>
#include <QDateTime>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

namespace platform
{

class NotificationPrivate;

/*!
 * @headerfile Notification.hpp <bb/platform/Notification>
 *
 * @brief A notification message that will trigger effects such as vibration, LED flashing,
 * playing a sound, adding an entry to the Universal Inbox, instant preview, and so on.
 *
 * @details The effects are dependent on the notification settings of the application.
 * You can use @c NotificationApplicationSettings to set your app's
 * notification behavior, including preview behavior.
 * Instant previews are disabled for your app by default, unless the app has
 * an account in the BlackBerry Hub.
 *
 * @note You can only change your notification settings once.
 *
 * @see @c bb::platform::NotificationApplicationSettings, bb::platform::NotificationDefaultApplicationSettings, @c bb::platform::NotificationGlobalSettings
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT Notification : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the unique identifier of this notification.
     *
     * @details The key can be used to clear the effects of notifications after this notification instance has been destroyed.
     *
     * Note that notification effects span beyond the application's lifecycle and as such, the key can be persisted in order
     * to cancel notifications that were created in a previous application instance.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString key READ key CONSTANT FINAL)

    //!@cond PRIVATE
    /*!
     * @brief Represents the category of this notification.
     *
     * @details The category determines which effects are triggered when the notification is posted.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString category READ category WRITE setCategory RESET resetCategory NOTIFY categoryChanged FINAL)
    //!@endcond

    /*!
     * @brief Represents the title of the notification.
     *
     * @details The notification settings determine whether and where the title is shown.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

    /*!
     * @brief Represents the main text of the notification.
     *
     * @details The notification settings determine whether and where the body is shown.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString body READ body WRITE setBody RESET resetBody NOTIFY bodyChanged FINAL)

    /*!
     * @brief Represents the time at which the event triggering the notification occurred.
     *
     * @details If the timestamp is invalid, then the time of the request is used, i.e., when @c notify() is called.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp RESET resetTimestamp NOTIFY timestampChanged FINAL)

    /*!
     * @brief Represents the location of the sound to be used when the notification is posted.
     * You must specify the @c soundUrl as a file URI to a public asset or a shared
     * asset on the device. You can set a local asset to be a public asset in the
     * Assets tab of the bar-descriptor.xml file of your project.
     *
     * @permissions You must set the @c access_shared permission for your app to access shared files.
     *
     * @details When the notification setting allows for sounds to be played, this property overrides the user preference for which sound to play.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl soundUrl READ soundUrl WRITE setSoundUrl RESET resetSoundUrl NOTIFY soundUrlChanged FINAL)

    /*!
     * @brief Represents the location of the icon to be shown in the preview for this item.
     *
     * @details When the notification setting allows instant previews, this property specifies the
     * path to the icon to be shown for the preview of this item.
     * You must specify the @c iconUrl as a file URI to a public asset or a shared
     * asset on the device. You can set a local asset to be a public asset in the
     * Assets tab of the bar-descriptor.xml file of your project.
     *
     * @permissions You must set the @c access_shared permission for your app to access shared files.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QUrl iconUrl READ iconUrl WRITE setIconUrl RESET resetIconUrl NOTIFY iconUrlChanged REVISION 1 FINAL)

    /*!
     * @brief Represents how a notification will be shown.
     *
     * @details Allows a notification to be restricted in the way it may be shown and how the user will be alerted.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::platform::NotificationType::Type type READ type WRITE setType RESET resetType NOTIFY typeChanged REVISION 1 FINAL)

    /*!
     * @brief Represents the error, if any, encountered during the last operation.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::platform::NotificationError::Type error READ error FINAL)

public:
    /*!
     * @brief Constructs a new instance of a notification.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Notification(QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a notification.
     *
     * @param key The key to associate with this instance. Note that supplying a non-unique key results in undefined results.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Notification(const QString& key, QObject* parent = 0);

    /*!
     * @brief Destroys the instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Notification();

    /*!
     * @brief Retrieves the unique identifier associated with this notification.
     *
     * @return The notification's identifier.
     *
     * @since BlackBerry 10.0.0
     */
    QString key() const;

    //!@cond PRIVATE
    /*!
     * @brief Retrieves the category associated with this notification.
     *
     * @return The category of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString category() const BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Retrieves the title associated with this notification.
     *
     * @return The title of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Retrieves the text associated with this notification.
     *
     * @return The text of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString body() const;

    /*!
     * @brief Retrieves the timestamp associated with this notification.
     *
     * @return The time of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime timestamp() const;

    /*!
     * @brief Retrieves the sound associated with this notification.
     *
     * @details If empty, the user setting will be used.
     *
     * @return The sound URL of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl soundUrl() const;

    /*!
     * @brief Retrieves the icon for previews associated with this notification.
     *
     * @details If empty, no icon will be shown on previews.
     *
     * @return The icon URL of the notification.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) QUrl iconUrl() const;

    /*!
     * @brief Retrieves the type of this notification.
     *
     * @return The type of the notification.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) bb::platform::NotificationType::Type type() const;

    /*!
     * @brief Retrieves a copy of the invoke request associated with this notification.
     *
     * @return The invoke request of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::InvokeRequest invokeRequest() const;

    //!@cond PRIVATE
    /*!
     * @brief Sets the category of the notification.
     *
     * @param category The category for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setCategory(const QString& category) BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Sets the title of the notification.
     *
     * @param title The title for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setTitle(const QString& title);

    /*!
     * @brief Sets the text of the notification.
     *
     * @param body The body for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setBody(const QString& body);

    /*!
     * @brief Sets the timestamp of the notification.
     *
     * @details The notification will be triggered when @c notify is invoked.
     * The timestamp is the time of the event associated with the notification.
     *
     * @param newTimestamp The time to associate with the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setTimestamp(const QDateTime& newTimestamp);

    /*!
     * @brief Sets the timestamp of the notification.
     *
     * @details The notification will be triggered when @c notify is invoked.
     * The timestamp is the time of the event associated with the notification.
     *
     * @param millisecondsTimestamp The time in milliseconds since the epoch to associate with the notification.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void setTimestamp(qint64 millisecondsTimestamp);

    /*!
     * @brief Sets the sound of the notification.
     * You must specify the @c soundUrl as a file URI to a public asset or a shared
     * asset on the device. You can set a local asset to be a public asset in the
     * Assets tab of the bar-descriptor.xml file of your project.
     *
     * @permissions You must set the @c access_shared permission for your app to access shared files.
     *
     * @param newSoundUrl The URL for the sound for this notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setSoundUrl(const QUrl& newSoundUrl);

    /*!
     * @brief Sets the icon for previews associated with this notification.
     * @details If no icon is set then no icon will be shown for previews.
     * You must specify the @c iconUrl as a file URI to a public asset or a shared
     * asset on the device. You can set a local asset to be a public asset in the
     * Assets tab of the bar-descriptor.xml file of your project.
     *
     * @permissions You must set the @c access_shared permission for your app to access shared files.
     *
     * @param newIconUrl The URL for the icon for this notification.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void setIconUrl(const QUrl& newIconUrl);

    /*!
     * @brief Sets the type of this notification.
     *
     * @param type The type of the notification.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void setType(bb::platform::NotificationType::Type type);

    /*!
     * @brief Sets the invoke request of the notification.
     *
     * @param newInvokeRequest The invoke request for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setInvokeRequest(const bb::system::InvokeRequest& newInvokeRequest);

    //!@cond PRIVATE
    /*!
     * @brief Resets the category for the notification.
     *
     * @details This resets the category property to its context-specific default value.
     * The default is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetCategory() BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Resets the title for the notification.
     *
     * @details This resets the title property to its context-specific default value.
     * The default is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetTitle();

    /*!
     * @brief Resets the body for the notification.
     *
     * @details This resets the body property to its context-specific default value.
     * The default is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetBody();

    /*!
     * @brief Resets the timestamp for the notification.
     *
     * @details This resets the timestamp property to its context-specific default value.
     * The default is a null QDateTime.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetTimestamp();

    /*!
     * @brief Resets the sound for the notification.
     *
     * @details When reset, the user setting will be used.
     *
     * @since BlackBerry 10.0.0
     */
    void resetSoundUrl();

    /*!
     * @brief Resets the icon for the preview of this notification.
     *
     * @details When reset, no icon will be shown.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void resetIconUrl();

    /*!
     * @brief Resets the type of this notification to default.
     *
     * @details Resets the type of this notification to fully enable all user settings
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void resetType();

    /*!
     * @brief Resets the invoke request for the notification.
     *
     * @details This resets the @c invokeRequest property to its context-specific default value.
     * The default is a default-constructed @c bb::system::InvokeRequest instance.
     *
     * @since BlackBerry 10.0.0
     */
    void resetInvokeRequest();

    /*!
     * @brief Retrieves the error that occurred during the request.
     *
     * @details The return value will be reset when a new request is made.
     *
     * @return The error that occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationError::Type error() const;

public Q_SLOTS:

    /*!
     * @brief Posts the notification.
     *
     * @details The result of this operation can be retrieved through @c error().
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationError::Type notify();

    /*!
     * @brief Clears effects for this notification but keeps it in the notification (universal) inbox.
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationError::Type clearEffects();

    /*!
     * @brief Deletes the notification from the notification inbox.
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationError::Type deleteFromInbox();

    /*!
     * @brief Clears effects for all notifications posted by the application.
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    static bb::platform::NotificationError::Type clearEffectsForAll();

    /*!
     * @brief Deletes all notifications from the notification inbox for this application.
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    static bb::platform::NotificationError::Type deleteAllFromInbox();

    /*!
     * @brief Clears effects for the specified notification but keeps it in the notification (universal) inbox.
     *
     * @details The key of notification can be obtained through @c key().
     *
     * @param key The unique identifier for the notification for which all effects should be cleared.
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    static bb::platform::NotificationError::Type clearEffects(const QString& key);

    /*!
     * @brief Deletes the specified notification from the notification inbox.
     *
     * @details The key of notification can be obtained through @c key().
     *
     * @param key The unique identifier for the notification to delete from the notification inbox.
     *
     * @return The result of this request.
     *
     * @since BlackBerry 10.0.0
     */
    static bb::platform::NotificationError::Type deleteFromInbox(const QString& key);

Q_SIGNALS:

    //!@cond PRIVATE
    /*!
     * @brief Emitted when the @c category property changes programmatically.
     *
     * @param value The new value for the @c category property.
     *
     * @since BlackBerry 10.0.0
     */
    void categoryChanged(const QString& value) BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Emitted when the @c title property changes programmatically.
     *
     * @param value The new value for the @c title property.
     *
     * @since BlackBerry 10.0.0
     */
    void titleChanged(const QString& value);

    /*!
     * @brief Emitted when the @c body property changes programmatically.
     *
     * @param value The new value for the @c body property.
     *
     * @since BlackBerry 10.0.0
     */
    void bodyChanged(const QString& value);

    /*!
     * @brief Emitted when the @c timestamp property changes programmatically.
     *
     * @param newTimestamp The new value for the @c timestamp property.
     *
     * @since BlackBerry 10.0.0
     */
    void timestampChanged(const QDateTime& newTimestamp);

    /*!
     * @brief Emitted when the @c soundUrl property changes programmatically.
     *
     * @param newSoundUrl The new value for the @c soundUrl property.
     *
     * @since BlackBerry 10.0.0
     */
    void soundUrlChanged(const QUrl& newSoundUrl);

    /*!
     * @brief Emitted when the @c iconUrl property changes programmatically.
     *
     * @param newIconUrl The new value for the @c iconUrl property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void iconUrlChanged(const QUrl& newIconUrl);

    /*!
     * @brief Emitted when the @c type property changes programmatically.
     *
     * @param type The new value for the @c type property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void typeChanged(bb::platform::NotificationType::Type& type);

    /*!
     * @brief Emitted when the @c invokeRequest property changes programmatically.
     *
     * @param newInvokeRequest The new value for the @c invokeRequest property.
     *
     * @since BlackBerry 10.0.0
     */
    void invokeRequestChanged(const bb::system::InvokeRequest& newInvokeRequest);

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(Notification)
    Q_DISABLE_COPY(Notification)
    NotificationPrivate* d_ptr;
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::Notification)
#endif // BB_PLATFORM_NOTIFICATION_HPP

