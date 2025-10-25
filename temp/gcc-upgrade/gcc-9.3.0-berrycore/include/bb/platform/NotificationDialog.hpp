/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONDIALOG_HPP
#define BB_PLATFORM_NOTIFICATIONDIALOG_HPP

#include <bb/platform/Global>

#include <bb/platform/NotificationError>
#include <bb/platform/NotificationResult>
#include <bb/system/InvokeRequest>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

namespace system
{
class SystemUiButton;
} // namespace system

namespace platform
{

class NotificationDialogPrivate;

/*!
 * @headerfile NotificationDialog.hpp <bb/platform/NotificationDialog>
 *
 * @brief A notification that will be shown to the user using a dialog box.
 *
 * @details The notification also triggers effects such as vibration, LED flashing, sound playing, and so on.
 * The effects are dependent on the notification settings of the application.
 * Settings like Universal Inbox integration and badges will not be applied.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT NotificationDialog : public QObject
{
    Q_OBJECT

    //!@cond PRIVATE
    /*!
     * @brief Represents the category of this notification.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString category READ category WRITE setCategory RESET resetCategory NOTIFY categoryChanged FINAL)
    //!@endcond

    /*!
     * @brief Represents the title of the notification.
     * @details The notification settings determine whether and where the title is shown.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

    /*!
     * @brief Represents the main text of the notification.
     * @details The notification settings determine whether and where the body is shown.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString body READ body WRITE setBody RESET resetBody NOTIFY bodyChanged FINAL)

    /*!
     * @brief Represents whether the triggered effects of the notification should repeat.
     * @details Repeating effects include playing a sound.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat RESET resetRepeat NOTIFY repeatChanged FINAL)

    /*!
     * @brief Represents the location of the sound to be used when the notification is posted.
     * @details When the notification setting allows for sounds to be played,
     * this property overrides the user preference for which sound to play.
     * You must specify the @c soundUrl as a file URI to a public asset or a shared
     * asset on the device. You can set a local asset to be a public asset in the
     * Assets tab of the bar-descriptor.xml file of your project.
     *
     * @permissions You must set the @c access_shared permission for your app to access shared files.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl soundUrl READ soundUrl WRITE setSoundUrl RESET resetSoundUrl NOTIFY soundUrlChanged FINAL)

    /*!
     * @brief Represents any buttons to include in the dialog box.
     * @details When the user selects one of these buttons, the @c finished() signal will be emitted
     * with a parameter value of @c bb::platform::NotificationResult::ButtonSelection.
     * If no buttons are supplied, @c show() requests will fail.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QDeclarativeListProperty<bb::system::SystemUiButton> buttons READ qmlButtons FINAL)

    /*!
     * @brief Represents the result of the last completed request.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::platform::NotificationResult::Type result READ result NOTIFY finished FINAL)

    /*!
     * @brief Represents the last error encountered.
     * @details This property is only valid when @c result() is @c bb::platform::NotificationResult::Error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::platform::NotificationError::Type error READ error FINAL)

    /*!
     * @brief The default property is @c buttons.
     */
    Q_CLASSINFO("DefaultProperty", "buttons")

public:
    /*!
     * @brief Constructs a new instance of a notification dialog box.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit NotificationDialog(QObject* parent = 0);

    /*!
     * @brief Destroys the instance, and cancels any pending requests.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~NotificationDialog();

    //!@cond PRIVATE
    /*!
     * @brief Retrieves the category associated with this notification.
     * @return The category of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString category() const BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Retrieves the title associated with this notification.
     * @return The title of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Retrieves the text associated with this notification.
     * @return The text of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString body() const;

    /*!
     * @brief Retrieves the setting of whether or not to repeat notification settings such as vibration, LED, and so on.
     * @return @c true if the notification settings should be repeated.
     *
     * @since BlackBerry 10.0.0
     */
    bool repeat() const;

    /*!
     * @brief Retrieves the sound associated with this notification.
     * @details If empty, the user setting will be used.
     * @return The sound URL of the notification.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl soundUrl() const;

    //!@cond PRIVATE
    /*!
     * @brief Sets the category of the notification.
     * @param category The category for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setCategory(const QString& category) BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Sets the title of the notification.
     * @param title The title for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setTitle(const QString& title);

    /*!
     * @brief Sets the text of the notification.
     * @param body The body for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setBody(const QString& body);

    /*!
     * @brief Sets whether or not the notification settings like vibration, LED, etc should be repeated.
     * @param repeat The preference for repeating notification settings.
     *
     * @since BlackBerry 10.0.0
     */
    void setRepeat(bool repeat);

    /*!
     * @brief Sets the sound of the notification.
     *
     * You must specify the @c soundUrl as a file URI to a public asset or a shared
     * asset on the device. You can set a local asset to be a public asset in the
     * Assets tab of the bar-descriptor.xml file of your project.
     *
     * @permissions You must set the @c access_shared permission for your app to access shared files.
     *
     * @param newSoundUrl The soundUrl for the notification.
     *
     * @since BlackBerry 10.0.0
     */
    void setSoundUrl(const QUrl& newSoundUrl);

    /*!
     * @brief Appends @c button to the list of buttons for this notification dialog box.
     * @details The notification will become the parent of the button and be responsible for destroying it.
     * A button can only be added once.
     * @param button The button to append.
     *
     * @since BlackBerry 10.0.0
     */
    void appendButton(bb::system::SystemUiButton* button);

    /*!
     * @brief Appends @c button to the list of buttons for this notification dialog box. This button will
     * trigger @c invokeRequest when it is pressed by the user. The client will still receive a button selection
     * as it does for buttons that do not have associated invoke requests.
     * @details The notification dialog will become the parent of the button and be responsible for destroying it.
     * A button can only be added once. The invoke request must explicitly specify a
     * target. All other invoke attributes are optional.
     * @param button The button to append.
     * @param invoke The invoke request associated with the button
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(2) void appendButton(bb::system::SystemUiButton* button, const bb::system::InvokeRequest& invokeRequest);

    /*!
     * @brief Retrieves the number of buttons added to the notification.
     * @return The number of buttons.
     *
     * @since BlackBerry 10.0.0
     */
    int buttonCount() const;

    /*!
     * @brief Retrieves the button at index.
     * @details This instance retains ownership of the returned value.
     * @param index An index into the list of buttons.
     * @return The button at index or null if an invalid index is provided.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* buttonAt(int index) const;

    /*!
     * @brief Sets or replaces the InvokeRequest associated with the button at index.
     * @details @c index should be the index of an existing button before calling
     * this method. If an InvokeRequest without a target is set, no invoke will occur
     * when the button is pressed.
     * @param index An index into the list of buttons.
     * @param invokeRequest Value to set for invoke request associated with the button
     * @return false if the supplied index was invalid; true otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(2) bool setInvokeRequestAt(int index, const bb::system::InvokeRequest& invokeRequest);

    /*!
     * @brief Retrieves the invoke request associated with the button at index.
     * @details The returned value is a copy of the invoke request associated
     * with the button.
     * @param index An index into the list of buttons.
     * @return The invoke request associated with button at index or an empty
     * invoke request if no invoke was associated with the specified button index
     * or if an invalid index is provided.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(2) bb::system::InvokeRequest invokeRequestAt(int index) const;

    /*!
     * @brief Clears the list of buttons for this notification along with any
     * associated invoke requests.
     * @details The button instances will be deleted.
     *
     * @since BlackBerry 10.0.0
     */
    void clearButtons();

    //!@cond PRIVATE
    /*!
     * @brief Resets the category for the notification.
     * @details This resets the category property to its context-specific default value.
     * The default is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetCategory() BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Resets the title for the notification.
     * @details This resets the title property to its context-specific default value.
     * The default is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetTitle();

    /*!
     * @brief Resets the body for the notification.
     * @details This resets the body property to its context-specific default value.
     * The default is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetBody();

    /*!
     * @brief Resets whether effects triggered by the notification should be repeated to not repeat.
     *
     * @since BlackBerry 10.0.0
     */
    void resetRepeat();

    /*!
     * @brief Resets the sound for the notification.
     * @details When reset, the user setting will be used.
     *
     * @since BlackBerry 10.0.0
     */
    void resetSoundUrl();

    /*!
     * @brief Retrieves the result of the last completed request.
     *
     * @details If no request has been made, or if a request is pending, @c bb::platform::NotificationResult::None is returned.
     * @return The result of the last completed request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationResult::Type result() const;

    /*!
     * @brief Retrieves the error that occurred during the request.
     *
     * @details The return value will be reset when a new request is made.
     * @return The error that occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationError::Type error() const;

    /*!
     * @brief Returns the button selected when a button selection is made.
     * @details If no button has been selected, a null pointer will be returned.
     *
     * This function will return the result of the button selection of @c show() and @c exec().
     *
     * The return value will be reset when a new request is made.
     *
     * This instance retains ownership of the returned value.
     * @return The button selected.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::system::SystemUiButton* buttonSelection() const;

public Q_SLOTS:
    /*!
     * @brief Displays or updates the dialog box based on current property values.
     * @details The dialog result can be retrieved with @c buttonSelection().
     *
     * Control is returned to the caller immediately. For a blocking request, use @c exec().
     *
     * @since BlackBerry 10.0.0
     */
    void show();

    /*!
     * @brief Displays the dialog box based on current property values.
     * @details The button selection can be retrieved with @c buttonSelection().
     *
     * Unlike @c show(), this function will block until a button selection is made.
     * @return The result of the request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::NotificationResult::Type exec();

    /*!
     * @brief Cancels the dialog box if it is still displayed.
     *
     * @since BlackBerry 10.0.0
     */
    void cancel();

Q_SIGNALS:
    /*!
     * @brief Emitted when a request is completed.
     *
     * @param value The result of the request.
     *
     * @since BlackBerry 10.0.0
     */
    void finished(bb::platform::NotificationResult::Type value);

    //!@cond PRIVATE
    /*!
     * @brief Emitted when the @c category property is changed programmatically.
     * @param value The new value of the category property.
     *
     * @since BlackBerry 10.0.0
     */
    void categoryChanged(const QString& value) BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Emitted when the @c title property is changed programmatically.
     * @param value The new value of the title property.
     *
     * @since BlackBerry 10.0.0
     */
    void titleChanged(const QString& value);

    /*!
     * @brief Emitted when the @c body property is changed programmatically.
     * @param value The new value of the body property.
     *
     * @since BlackBerry 10.0.0
     */
    void bodyChanged(const QString& value);

    /*!
     * @brief Emitted when the @c repeat property is changed programmatically.
     * @param value The new value for the repeat property.
     *
     * @since BlackBerry 10.0.0
     */
    void repeatChanged(bool value);

    /*!
     * @brief Emitted when the @c soundUrl property changes.
     * @param newSoundUrl The new value for the soundUrl property.
     *
     * @since BlackBerry 10.0.0
     */
    void soundUrlChanged(const QUrl& newSoundUrl);

private:
//!@cond PRIVATE
    QDeclarativeListProperty<bb::system::SystemUiButton> qmlButtons();
    Q_DECLARE_PRIVATE(NotificationDialog)
    Q_DISABLE_COPY(NotificationDialog)
    NotificationDialogPrivate * const d_ptr;
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::NotificationDialog)
#endif // BB_PLATFORM_NOTIFICATIONDIALOG_HPP
