/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SYSTEMTOAST_HPP
#define BB_SYSTEM_SYSTEMTOAST_HPP

#include <bb/system/Global>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiPosition>
#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiError>
#include <bb/system/SystemUiResult>

#include <QObject>
#include <QScopedPointer>
#include <QUrl>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class SystemToastPrivate;

/*!
 * @headerfile SystemToast.hpp <bb/system/SystemToast>
 *
 * @brief A message displayed to the user that does not usually require user interaction to be dismissed.
 *
 * @image html cascades_systemtoast_on_a_keyboard_device.png A system toast
 *
 * @details The toast is dismissed after a predefined timeout period lapses. If the toast includes a button,
 * then the timeout period is activated with the first user interaction, for example, user touching the screen.
 * During this time, if a button is displayed, the user can select it.
 *
 * Presentation properties are marked as such, and affect future requests.
 * Any pending requests will use the values of the presentation properties at the time of the request.
 *
 * When the toast is displayed after a call to @c show() or @c exec(), there are two methods for updating the toast after changing its presentation properties.
 *
 * The default method is to update all the necessary presentation properties and call the @c update() method.
 * This guarantees that all the presentation properties are updated at the same time.
 *
 * The second method is to have the toast update automatically after every presentation property change. To enable these automatic updates,
 * the @c autoUpdateEnabled property must be set to @c true.
 *
 * The second method does not guarantee automatic updates for all the presentation properties changes.
 * This method can lead to noticeable delays between updates of individual properties. If more than one property needs to be updated, use the first method.
 * If only one presentation property is being updated frequently
 * (for example, the text on the toast @c body must be updated to notify the user of the application's current status)
 * the second approach can be used.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemToast : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the main text of the toast.
     * @details This is a presentation property whose default value is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString body READ body WRITE setBody RESET resetBody NOTIFY bodyChanged FINAL)

    /*!
     * @brief Indicates whether the toast is updated every time a presentation property is changed.
     * @details If @c autoUpdateEnabled is @c true, every time any of the presentation properties on the toast are changed,
     * the toast is updated immediately to reflect the changes on the UI. If @c autoUpdateEnabled is @c false, the toast
     * is not updated automatically, instead the @c show() method must be called. This is the default behavior.
     *
     * @note The behavior of the @c autoUpdateEnabled flag is apparent when multiple presentation properties are changed.
     * When @c autoUpdateEnabled is set to @c true, the on-screen toast may be updated after each individual presentation property is changed.
     * This may not be an ideal user experience, particularly as the number of changed presentation properties increases.
     * When @c autoUpdateEnabled is set to @c false, it is possible to combine multiple presentation property updates and apply them
     * to the on-screen toast as one request by calling @c show().
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool autoUpdateEnabled READ isAutoUpdateEnabled WRITE setAutoUpdateEnabled RESET resetAutoUpdateEnabled NOTIFY autoUpdateEnabledChanged REVISION 1)

    /*!
     * @brief Represents the path to an image file that can be included in the toast.
     * @details This is a presentation property whose default value is a default-constructed @c QUrl.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon RESET resetIcon NOTIFY iconChanged FINAL)

    /*!
     * @brief Represents the position of the toast on the display.
     * @details This is a presentation property whose default value is @c bb::system::SystemUiPosition::MiddleCenter.
     * @see @c bb::system::SystemUiPosition for a list of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiPosition::Type position READ position WRITE setPosition RESET resetPosition NOTIFY positionChanged FINAL)

    /*!
     * @brief Represents the modality of the toast.
     * @details This is a presentation property whose value is @c bb::system::SystemUiModality::Application.
     * @see @c bb::system::SystemUiModality for the list of valid values.
     *
     * @note Toasts are non-modal. Modality refers to the scope of the toast.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiModality::Type modality READ modality WRITE setModality RESET resetModality NOTIFY modalityChanged FINAL)

    /*!
     * @brief Represents the button that can be included in the toast.
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @note The button is always shown as enabled. This button is omitted if
     *      its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiButton* button READ button RESET resetButton FINAL)

    /*!
     * @brief Represents the result of the last completed request.
     * @details To obtain result values once the request is finished, use the following functions:
     * - @c result() - the result of the request
     * - @c error() - the error that occurred during the request (if applicable)
     * - @c buttonSelection() - the button selected (if applicable)
     *
     * @see @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiResult::Type result READ result NOTIFY finished FINAL)

    /*!
     * @brief Represents the last error encountered.
     * @details This property is only valid when @c SystemToast::result is @c bb::system::SystemUiResult::Error.
     * @see @c bb::system::SystemUiError for the list of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiError::Type error READ error FINAL)

public:
    /*!
     * @brief Constructs a new instance of a toast.
     * @param parent If not 0, the supplied parent is responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemToast(QObject* parent = 0);

    /*!
     * @brief Destroys the toast, and cancels any pending requests.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SystemToast();

    /*!
     * @brief Retrieves the main text of the toast.
     * @return The text of the toast.
     *
     * @since BlackBerry 10.0.0
     */
    QString body() const;

    /*!
     * @brief Retrieves the flag indicating if the toast is updated every time the value of a presentation property is changed.
     * @return @c true if the toast automatically updates, @c false if the toast doesn't update (in which case the @c show() method
     * must be called after updating the toast presentation properties).
     *
     * @since BlackBerry 10.2.0
     */
    bool isAutoUpdateEnabled() const;

    /*!
     * @brief Retrieves the icon for the toast.
     * @return The local path to the icon for the toast.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl icon() const;

    /*!
     * @brief Retrieves the position of the toast.
     * @see @c bb::system::SystemUiPosition for the list of valid positions.
     * @return The toast position.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiPosition::Type position() const;

    /*!
     * @brief Retrieves the toast's button.
     * @details This instance retains ownership of the returned value.
     * @return The toast's button.
     *
     * @since BlackBerry 10.0.0
     */
    SystemUiButton* button();

    /*!
     * @brief Retrieves the toast's modality.
     * @see @c bb::system::SystemUiModality for the list of possible values.
     * @return The toast's modality.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiModality::Type modality() const;

    /*!
     * @brief Sets the main text of the toast.
     * @param body The new text of the toast.
     *
     * @since BlackBerry 10.0.0
     */
    void setBody(const QString& body);

    /*!
     * @brief Sets the @c autoUpdateEnabled flag of the toast.
     * @param update @c true if the toast updates automatically,
     * @c false if the toast does not update automatically (in which case the @c show() method
     * must be called after updating the toast presentation properties).
     *
     * @since BlackBerry 10.2.0
     */
    void setAutoUpdateEnabled(bool update);

    /*!
     * @brief Sets the icon for the toast.
     * @param icon The new local path to the icon for the toast.
     *
     * @since BlackBerry 10.0.0
     */
    void setIcon(const QUrl& icon);

    /*!
     * @brief Sets the position of the toast.
     * @param newPosition The new toast position.  See @c bb::system::SystemUiPosition for the list
     * of valid positions.
     *
     * @since BlackBerry 10.0.0
     */
    void setPosition(bb::system::SystemUiPosition::Type newPosition);

    /*!
     * @brief Sets the modality for the toast.
     * @param newModality The new modality preference.  See @c bb::system::SystemUiModality for the list
     * of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    void setModality(bb::system::SystemUiModality::Type newModality);

    /*!
     * @brief Resets the main text of the toast to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetBody();

    /*!
     * @brief Resets the @c autoUpdateEnabled flag to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void resetAutoUpdateEnabled();

    /*!
     * @brief Resets the icon URL for the toast to an empty, default-constructed @c QUrl.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetIcon();

    /*!
     * @brief Resets the position of the toast to @c bb::system::SystemUiPosition::MiddleCenter.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetPosition();

    /*!
     * @brief Resets the button for this toast to be a default button with no text.
     * @details A reset button will not be shown.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetButton();

    /*!
     * @brief Resets the modality of the toast to @c bb::system::SystemUiModality::Application.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetModality();

    /*!
     * @brief Retrieves the result of the last completed request.
     *
     * @details If no request has been made, or if a request is pending, @c bb::system::SystemUiResult::None is returned.
     * @see @c bb::system::SystemUiResult for the list of possible results.
     * @return The result of the last completed request.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiResult::Type result() const;

    /*!
     * @brief Retrieves the error that occurred during the request.
     *
     * @details The return value is reset when a new request is made.
     * @see @c bb::system::SystemUiError for the list of possible errors.
     * @return The error that occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiError::Type error() const;

    /*!
     * @brief Returns the button that was selected when a button selection is made.
     * @details If no button has been selected, 0 is returned.
     * This can occur when the toast timeout expires.
     *
     * This function returns the result of the button selection of @c show() and @c exec().
     *
     * The return value is reset when a new request is made.
     *
     * This instance retains ownership of the returned value.
     * @return The button selected by the user.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::system::SystemUiButton* buttonSelection() const;

public Q_SLOTS:
    /*!
     * @brief Displays a toast based on current property values.
     * @details The result of the request can be retrieved with the @c SystemToast::result property, or by using the @c finished() signal.
     * The button that was selected can be retrieved with the @c buttonSelection() method.
     *
     * Control is returned to the caller immediately. For a blocking request, use @c exec().
     *
     * @since BlackBerry 10.0.0
     */
    void show();

    /*!
     * @brief Displays or updates the toast based on current property values.
     * @details The result of the request can be retrieved using the @c SystemToast::result property, or by using the @c finished() signal.
     * The button that was selected can be retrieved with the @c buttonSelection() method.
     *
     * Unlike @c show(), this function blocks until a button selection is made or the toast times out. If the toast is already on the screen,
     * this method returns immediately with @c bb::system::SystemUiResult::DialogCannotBlock.
     *
     * @note Blocking occurs by starting a nested @c QEventLoop. To use this method safely, the following conditions must be met:
     * - Any connections to this slot must use a @c Qt::QueuedConnection, or the slot must be triggered using @c QTimer::singleShot(), and
     * - @c QObject::deleteLater() must be used in place of @c delete when deleting the toast object.
     * If these conditions are not met, unexpected behavior may result.
     *
     * @return The result of the request. See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiResult::Type exec();

    /*!
     * @brief Updates an on-screen toast based on the current property values.
     * @details If the toast is not on the screen, this method returns immediately and no changes
     * are made to the toast.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void update();

    /*!
     * @brief Cancels the toast if it is still displayed.
     *
     * @since BlackBerry 10.0.0
     */
    void cancel();

Q_SIGNALS:
    /*!
     * @brief Emitted when a request is completed.
     *
     * @details The button selection can be retrieved with @c buttonSelection().
     * @param value The result of the request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    void finished(bb::system::SystemUiResult::Type value);

    /*!
     * @brief Emitted when the @c body property is changed programmatically.
     * @param value The new value of the @c body property.
     *
     * @since BlackBerry 10.0.0
     */
    void bodyChanged(const QString& value);

    /*!
     * @brief Emitted when the @c autoUpdateEnabled property is changed programmatically.
     * @param value The new value of the @c autoUpdateEnabled property.
     *
     * @since BlackBerry 10.2.0
     */
    void autoUpdateEnabledChanged(bool value);

    /*!
     * @brief Emitted when the @c icon property is changed programmatically.
     * @param value The new value of the @c icon property.
     *
     * @since BlackBerry 10.0.0
     */
    void iconChanged(const QUrl& value);

    /*!
     * @brief Emitted when the @c position property is changed programmatically.
     * @param value The new value of the @c position property.
     *
     * @since BlackBerry 10.0.0
     */
    void positionChanged(bb::system::SystemUiPosition::Type value);

    /*!
     * @brief Emitted when the @c modality property is changed programmatically.
     * @param newModality The new value of the @c modality property.
     *
     * @since BlackBerry 10.0.0
     */
    void modalityChanged(bb::system::SystemUiModality::Type newModality);

//!@cond PRIVATE
    void finished( int value );
    void positionChanged(int value);
    void modalityChanged(int newModality);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<SystemToastPrivate> d_ptr;
    Q_DECLARE_PRIVATE(SystemToast)
    Q_DISABLE_COPY(SystemToast)
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemToast)
#endif // BB_SYSTEM_SYSTEMTOAST_HPP
