/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SYSTEMUIINPUTFIELD_HPP
#define BB_SYSTEM_SYSTEMUIINPUTFIELD_HPP

#include <bb/system/Global>
#include <bb/system/SystemUiInputMode>

#include <QObject>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class SystemUiInputFieldPrivate;

/*!
 * @headerfile SystemUiInputField.hpp <bb/system/SystemUiInputField>
 *
 * @brief An input field that can be used with dialog boxes.
 *
 * @details The presentation of the input field is dependent on the class using it.
 * For instance, some classes may choose not to show the label.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiInputField: public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the text to include in the input field when it is first displayed.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString defaultText READ defaultText WRITE setDefaultText RESET resetDefaultText NOTIFY defaultTextChanged FINAL)

    /*!
     * @brief Represents the text to include in the input field when it is empty.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString emptyText READ emptyText WRITE setEmptyText RESET resetEmptyText NOTIFY emptyTextChanged FINAL)

    /*!
     * @brief Represents the input mode for entering text into the input field.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiInputMode::Type inputMode READ inputMode WRITE setInputMode RESET resetInputMode NOTIFY inputModeChanged FINAL)

    /*!
     * @brief Represents the number of characters that the input field can contain.
     * @details 0 is the default value and corresponds to no maximum length restrictions.
     *
     * @note Setting a value less than 0 resets the property to the default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int maximumLength READ maximumLength WRITE setMaximumLength RESET resetMaximumLength NOTIFY maximumLengthChanged FINAL)

public:

    /*!
     * @brief Constructs an input field instance with a default keyboard layout @c bb::system::SystemUiInputMode::Default.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemUiInputField(QObject* parent = 0);

    /*!
     * @brief Constructs an input field instance.
     * @param type The content type of the text for the new instance.  See @c bb::system::SystemUiInputMode for the list
     * of content types.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemUiInputField(bb::system::SystemUiInputMode::Type type, QObject* parent = 0);

    /*!
     * @brief Destroys the input field.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SystemUiInputField();

    /*!
     * @brief Retrieves the default text that will be shown in the input field prior to user input.
     * @return Returns the default text of the input field.
     *
     * @since BlackBerry 10.0.0
     */
    QString defaultText() const;

    /*!
     * @brief Retrieves the text that will be shown in the input field when it is empty.
     * @return Returns the text to show when the input field is empty.
     *
     * @since BlackBerry 10.0.0
     */
    QString emptyText() const;

    /*!
     * @brief Retrieves the content type of the text in the input field.
     *
     * @see @c bb::system::SystemUiInputMode for a list of content types.
     *
     * @return Returns the input field's content type.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiInputMode::Type inputMode() const;

    /*!
     * @brief Retrieves the number of characters allowed in the input field.
     * @return The input field's upper character limit.
     *
     * @since BlackBerry 10.0.0
     */
    int maximumLength() const;

    /*!
     * @brief Sets the default text that will be shown in the input field prior to user input.
     * @param text The default text of the input field.
     *
     * @since BlackBerry 10.0.0
     */
    void setDefaultText(const QString& text);

    /*!
     * @brief Sets the text that will be shown in the input field when it is empty.
     * @param text The text to show when the input field is empty.
     *
     * @since BlackBerry 10.0.0
     */
    void setEmptyText(const QString& text);

    /*!
     * @brief Sets the content type of the text for the input field.
     *
     * @see @c bb::system::SystemUiInputMode for the list of content types.
     *
     * @param type The input field's content type.
     *
     * @since BlackBerry 10.0.0
     */
    void setInputMode(bb::system::SystemUiInputMode::Type type);

    /*!
     * @brief Sets the number of characters allowed in the input field.
     *
     * @details Values less than 0 reset the property.
     * @param newMaximumLength The input field's upper character limit.
     *
     * @since BlackBerry 10.0.0
     */
    void setMaximumLength(int newMaximumLength);

    /*!
     * @brief Resets the default text to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetDefaultText();

    /*!
     * @brief Resets the text that will be shown in the input field when it is empty to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetEmptyText();

    /*!
     * @brief Resets the input mode to @c bb::system::SystemUiInputMode::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetInputMode();

    /*!
     * @brief Resets the maximum length to 0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetMaximumLength();

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c defaultText property is changed programmatically.
     * @param value The new value of the @c defaultText property.
     *
     * @since BlackBerry 10.0.0
     */
    void defaultTextChanged(const QString& value);

    /*!
     * @brief Emitted when the @c emptyText property is changed programmatically.
     * @param value The new value of the @c emptyText property.
     *
     * @since BlackBerry 10.0.0
     */
    void emptyTextChanged(const QString& value);

    /*!
     * @brief Emitted when the @c inputMode property is changed programmatically.
     * @see @c bb::system::SystemUiInputMode for the list of content types.
     * @param value The new value of the @c inputMode property.
     *
     * @since BlackBerry 10.0.0
     */
    void inputModeChanged(bb::system::SystemUiInputMode::Type value);

    /*!
     * @brief Emitted when the @c maximumLength property is changed programmatically.
     * @param newMaximumLength The new value of the @c maximumLength property.
     *
     * @since BlackBerry 10.0.0
     */
    void maximumLengthChanged(int newMaximumLength);

//!@cond PRIVATE
    void inputModeChanged(int value);
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(SystemUiInputField)
    Q_DISABLE_COPY(SystemUiInputField)
    QScopedPointer<SystemUiInputFieldPrivate> d_ptr;
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiInputField)
#endif // BB_SYSTEM_SYSTEMUIINPUTFIELD_HPP
