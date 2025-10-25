/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SYSTEMUIBUTTON_HPP
#define BB_SYSTEM_SYSTEMUIBUTTON_HPP

#include <bb/system/Global>

#include <QObject>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class SystemUiButtonPrivate;

/*!
 * @headerfile SystemUiButton.hpp <bb/system/SystemUiButton>
 *
 * @brief The invokable buttons that are available for dialogs and toasts.
 *
 * @details The presentation of the button is dependent on the class using it.
 * For instance, some classes may choose to always show the button as enabled, or to not show buttons with null or empty labels.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiButton : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the text of the button.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString label READ label WRITE setLabel RESET resetLabel NOTIFY labelChanged FINAL)

    /*!
     * @brief Indicates whether the button is enabled and can be clicked.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled RESET resetEnabled NOTIFY enabledChanged FINAL)

public:
    /*!
     * @brief Constructs an instance of a button.
     * @details The @c enabled property will be set to @c true and the @c label
     * property will be set to @c QString::null.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemUiButton(QObject* parent = 0);

    /*!
     * @brief Constructs an instance of a button with the label provided.
     * @details The @c enabled property will be set to @c true.
     * @param label The label for the button.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemUiButton(const QString& label, QObject* parent = 0);

    /*!
     * @brief Destroys the button.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SystemUiButton();

    /*!
     * @brief Retrieves the label description that is associated with the button.
     * @return Returns the label of the button.
     *
     * @since BlackBerry 10.0.0
     */
    QString label() const;

    /*!
     * @brief Retrieves the enabled state of the button.
     * @return Returns whether the button should be enabled.
     *
     * @since BlackBerry 10.0.0
     */
    bool enabled() const;

    /*!
     * @brief Sets the label description to associate with the button.
     * @details Empty or @c NULL labels may not be shown.
     * @param text The new label text.
     *
     * @since BlackBerry 10.0.0
     */
    void setLabel(const QString& text);

    /*!
     * @brief Enables or disables the button.
     * @param value The new enabled state of the button.
     *
     * @since BlackBerry 10.0.0
     */
    void setEnabled(bool value);

    /*!
     * @brief Resets the label description to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetLabel();

    /*!
     * @brief Resets the @c SystemUiButton::enabled property to @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetEnabled();

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c label property is changed programmatically.
     * @param value The new value of the @c label property.
     *
     * @since BlackBerry 10.0.0
     */
    void labelChanged(const QString& value);

    /*!
     * @brief Emitted when the @c enabled property is changed programmatically.
     * @param value The new value of the @c enabled property.
     *
     * @since BlackBerry 10.0.0
     */
    void enabledChanged(bool value);

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(SystemUiButton)
    Q_DISABLE_COPY(SystemUiButton)
    QScopedPointer<SystemUiButtonPrivate> d_ptr;
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiButton)
#endif // BB_SYSTEM_SYSTEMUIBUTTON_HPP
