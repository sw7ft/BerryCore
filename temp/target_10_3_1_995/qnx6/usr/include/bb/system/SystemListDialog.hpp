/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SYSTEMLISTDIALOG_HPP
#define BB_SYSTEM_SYSTEMLISTDIALOG_HPP

#include <bb/system/Global>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiReturnKeyAction>
#include <bb/system/SystemUiError>
#include <bb/system/SystemUiResult>
#include <bb/system/ListSelectionMode>
#include <bb/system/ListSelectionIndicator>

#include <QObject>
#include <QScopedPointer>
#include <QStringList>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class SystemListDialogPrivate;

/*!
 * @headerfile SystemListDialog.hpp <bb/system/SystemListDialog>
 *
 * @brief A dialog box that presents the user with a list of choices.
 *
 * @image html cascades_systemlistdialog_with_no_items_selected.png A system list dialog
 *
 * @details The dialog box displayed is an application-modal window, though it is possible to use a system-modal window by setting the
 * @c SystemListDialog::modality property.
 * The dialog box presents a list of choices.  By default, single selection mode is enabled, which allows a user to select a single option from the list.
 * Alternately, multiple selection mode can be enabled to allow the user to select multiple options from the list.  In both modes, the confirm button is disabled until the user
 * selects at least one of the presented options.

 * In addition, the @c buttonAreaLimit property controls the number of buttons that are contained in the button area of the window.
 * By default, the button area is large enough to contain @c confirmButton, @c customButton, and @c cancelButton, if they are valid.
 * The buttons are considered invalid if they do not have a label set.
 *
 * Presentation properties are marked as such, and affect future requests.
 * Any pending requests will use the values of the presentation properties at the time of the request.
 *
 * When the dialog box is displayed after a call to @c show() or @c exec(), there are two methods for updating the dialog box after changing its presentation properties.
 *
 * The default method is to update all the necessary presentation properties and call the @c update() method.
 * This guarantees that all the presentation properties are updated at the same time.
 *
 * The second method is to have the dialog box update automatically after every presentation property change. To enable these automatic updates,
 * the @c autoUpdateEnabled property must be set to @c true.
 *
 * The second method does not guarantee automatic updates for all the presentation properties changes.
 * This method can lead to noticeable delays between updates of individual properties. If more than one property needs to be updated, use the first method.
 * If only one presentation property is being updated frequently
 * (for example, the text on the dialog box @c body must be updated to notify the user of the application's current status)
 * the second approach can be used.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemListDialog : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the title of the window.
     * @details This is a presentation property whose default value is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

    /*!
     * @brief Represents the main text of the window.
     * @details This is a presentation property whose default value is a default-constructed @c QString.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY(QString body READ body WRITE setBody RESET resetBody NOTIFY bodyChanged FINAL)

    /*!
     * @brief Retrieves whether the text can be displayed with emoticons.
     * @details This is a presentation property whose default value is @c false.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY(bool emoticonsEnabled READ emoticonsEnabled WRITE setEmoticonsEnabled RESET resetEmoticonsEnabled NOTIFY emoticonsEnabledChanged FINAL)

    /*!
     * @brief Indicates whether a check box for remembering user selection should be included in the dialog box.
     * @details If a check box is requested, then the user will have the ability to enable and disable it.
     * The user selection is available using @c rememberMeSelection() when the request is finished.
     * To customize how the check box is presented, use @c rememberMeChecked() and @c rememberMeText().
     *
     * This is a presentation property whose default value is @c false.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY(bool includeRememberMe READ includeRememberMe WRITE setIncludeRememberMe RESET resetIncludeRememberMe NOTIFY includeRememberMeChanged FINAL)

    /*!
     * @brief Indicates whether the dialog box is updated every time a presentation property is changed.
     * @details If @c autoUpdateEnabled is @c true, every time any of the presentation properties on the dialog box are changed,
     * the dialog box also updates immediately to reflect the changes on the UI. If @c autoUpdateEnabled is @c false, the dialog
     * box is not updated automatically, instead the @c show() method must be called. This is the default behavior.
     *
     * @note The behavior of the @c autoUpdateEnabled flag is apparent when multiple presentation properties are changed.
     * When@c autoUpdateEnabled is set to @c true, the on-screen dialog box may be updated after each individual presentation property is changed.
     * This may not be an ideal user experience, particularly as the number of changed presentation properties increases.
     * When @c autoUpdateEnabled is set to @c false, it is possible to combine multiple presentation property updates and apply them
     * to the on-screen dialog box as one request by calling @c show().
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool autoUpdateEnabled READ isAutoUpdateEnabled WRITE setAutoUpdateEnabled RESET resetAutoUpdateEnabled NOTIFY autoUpdateEnabledChanged REVISION 1)

    /*!
     * @brief Represents the checked state of the check box for remembering user selection.
     * @details The state is only applied if @c includeRememberMe is @c true.
     * To obtain the user selection for this property when the request is finished, use @c rememberMeSelection().
     *
     * This is a presentation property whose default value is @c true.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY(bool rememberMeChecked READ rememberMeChecked WRITE setRememberMeChecked RESET resetRememberMeChecked NOTIFY rememberMeCheckedChanged FINAL)

    /*!
     * @brief Represents the text to associate with the check box associated with @c rememberMeChecked.
     * @details This property is only applied if @c includeRememberMe is @c true.
     *
     * This is a presentation property whose default value is @c "Remember Me".
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY(QString rememberMeText READ rememberMeText WRITE setRememberMeText RESET resetRememberMeText NOTIFY rememberMeTextChanged FINAL)

    /*!
     * @brief The maximum number of buttons that can be shown without causing an overflow.
     * @details When overflow occurs, all buttons are stacked vertically.
     *
     * This is a presentation property whose default value is -1.
     * @note -1 implies that the default system behavior will be applied. The supported range is 1-3, with any values outside the range resetting the property to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int buttonAreaLimit READ buttonAreaLimit WRITE setButtonAreaLimit RESET resetButtonAreaLimit NOTIFY buttonAreaLimitChanged FINAL)

    /*!
     * @brief Indicates whether to dismiss the dialog box when a button is selected.
     * @details If @c false, the dialog box must be dismissed using @c cancel(). Otherwise, the dialog box is dismissed when a button is selected.
     *
     * This is a presentation property whose default value is @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool dismissAutomatically READ dismissAutomatically WRITE setDismissAutomatically RESET resetDismissAutomatically NOTIFY dismissAutomaticallyChanged FINAL)

    /*!
     * @brief Indicates whether to display an activity indicator in the title bar of the dialog box.
     *
     * This is a presentation property whose default value is @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool activityIndicatorVisible READ activityIndicatorVisible WRITE setActivityIndicatorVisible RESET resetActivityIndicatorVisible NOTIFY activityIndicatorVisibleChanged REVISION 1)

    /*!
     * @brief Represents the action associated with the return key for this dialog box.
     * @details This is a presentation property whose default value is @c bb::system::SystemUiReturnKeyAction::Default.
     * @see @c bb::system::SystemUiReturnKeyAction for the list of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiReturnKeyAction::Type returnKeyAction READ returnKeyAction WRITE setReturnKeyAction RESET resetReturnKeyAction NOTIFY returnKeyActionChanged FINAL)

    /*!
     * @brief Represents the modality of the dialog box.
     * @details This is a presentation property whose value is @c bb::system::SystemUiModality::Application.
     * @see @c bb::system::SystemUiModality for the list of valid values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiModality::Type modality READ modality WRITE setModality RESET resetModality NOTIFY modalityChanged FINAL)

    /*!
     * @brief Controls the number of items that may be selected in the list for this dialog box.
     *
     * @details If this property is set to @c ListSelectionMode::Single, selecting one item in the list will clear any other item in the list.
     * If it is set to @c bb::system::ListSelectionMode::Multiple, then any number of items may be selected in the list.
     * In either selection mode, the user can decide to select no items from the list.
     *
     * This is a presentation property whose default value is @c bb::system::ListSelectionMode::Single.
     * @see @c bb::system::ListSelectionMode for the list of valid values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::ListSelectionMode::Type selectionMode READ selectionMode WRITE setSelectionMode RESET resetSelectionMode NOTIFY selectionModeChanged FINAL)

    /*!
     * @brief Represents the button associated with the default confirming action of the window.
     *
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is @c "OK".
     *
     * @note This button is omitted if its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiButton* confirmButton READ confirmButton RESET resetConfirmButton FINAL)

    /*!
     * @brief Represents the button associated with the tertiary action of the window.
     *
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @note This button is omitted if its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiButton* customButton READ customButton RESET resetCustomButton FINAL)

    /*!
     * @brief Represents the button associated with the default cancellation action of the window.
     *
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is @c "Cancel".
     *
     * @note This button is omitted if its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiButton* cancelButton READ cancelButton RESET resetCancelButton FINAL)

    /*!
     * @brief Represents the button associated with the return key action of the window.
     * @details When the user triggers the return key action, this button is automatically selected.
     * If the @c defaultButton is @c NULL, then triggering the return key action will not select any button.
     *
     * If @c defaultButton is set to a button that this instance does not manage, then this property is undefined.
     *
     * This is a presentation property whose default value determined dynamically based on which managed buttons are available.
     * The precedence of the buttons is as follows:
     * - @c confirmButton
     * - @c cancelButton
     * - @c customButton
     * - last element of @c buttons
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiButton* defaultButton READ defaultButton WRITE setDefaultButton RESET resetDefaultButton FINAL)

    /*!
     * @brief Represents any additional buttons to include in the window.
     *
     * @details This is a presentation property which is initialized as an empty list.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QDeclarativeListProperty<bb::system::SystemUiButton> buttons READ qmlButtons FINAL)

    /*!
     * @brief Represents the result of the last completed request.
     * @details To obtain result values when the request is finished, use the following functions:
     * - @c result() - the result of the request
     * - @c error() - the error that occurred during the request (if applicable)
     * - @c buttonSelection() - the button selected (if applicable)
     * - @c selectedIndices() - the indices of the selected list items (if applicable)
     *
     * @see @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiResult::Type result READ result NOTIFY finished FINAL)

    /*!
     * @brief Represents the last error encountered.
     * @details This property is only valid when the @c SystemListDialog::result property is @c bb::system::SystemUiResult::Error.
     * @see @c bb::system::SystemUiError for the list of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiError::Type error READ error FINAL)

    /*!
     * @brief The selected elements in the supplied list of elements.
     *
     * This list contains the indices of the elements that were selected in the list.  If this
     * dialog box is set to @c bb::system::ListSelectionMode::Single (the default) the list will either be empty
     * or contain exactly one value.  If the dialog box is set to @c bb::system::ListSelectionMode::Multiple then
     * the list will contain zero or more indices.
     *
     * @note The indices are the position of the elements as they were appended to the dialog box,
     * not the index of the selectable items within the list.  For example, if you appended a header,
     * then a separator, followed by 2 items, and the user selected the first item in the list the
     * value @c 2 are returned (the header is at index 0, the separator is at index 1, and the items are
     * at indices 2 and 3 respectively).
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariantList selectedIndices READ selectedIndicesQML NOTIFY finished FINAL )

    /*!
     * @brief Indicates whether the dialog box should be dismissed when an item is selected.
     *
     * @details This is a presentation property whose default value is @c false.
     *
     * This property allows the dialog box to be automatically dismissed when a list item is selected.  The dialog
     * box will indicate that no button was selected (that is, @c buttonSelection() will return 0), and the selected index
     * will be available using @c selectedIndices().
     *
     * @note It will not be possible for a user to select multiple items with this property set to @c true.
     * On the first selection, the dialog box is dismissed.
     *
     * @note By default, the dialog box will show the confirmation button, though it is of limited use with this
     * property set to @c true.  You can remove the confirmation button by setting its label to @c QString::null.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool dismissOnSelection READ dismissOnSelection WRITE setDismissOnSelection RESET resetDismissOnSelection NOTIFY dismissOnSelectionChanged REVISION 1 FINAL)

    /*!
     * @brief Controls the highlighting style for selected list items.
     *
     * @details This is a presentation property whose default value is @c bb::system::ListSelectionIndicator::Button.
     *
     * This property allows the dialog box to indicate how selected list items are highlighted for the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::system::ListSelectionIndicator::Type selectionIndicator READ selectionIndicator WRITE setSelectionIndicator RESET resetSelectionIndicator NOTIFY selectionIndicatorChanged REVISION 1 FINAL)

    /*!
     * @brief The default property is @c buttons.
     */
    Q_CLASSINFO("DefaultProperty", "buttons")

public:
    /*!
     * @brief Constructs a new instance of a dialog box with default confirmation and cancellation buttons.
     * @details The confirmation and cancellation buttons will have their default label values.
     * @param parent If not 0, the supplied parent is responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemListDialog(QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a dialog box with only a confirmation button.
     * @details To show the cancellation and custom button set the labels of @c SystemListDialog::cancelButton
     * and @c SystemListDialog::customButton respectively.
     * @param confirmLabel The label to use for the confirmation button.
     * @param parent If not 0, the supplied parent is responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemListDialog(const QString& confirmLabel, QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a dialog box with defined confirmation and cancellation buttons.
     * @details To show the custom button set the label of @c SystemListDialog::customButton.
     * @param confirmLabel The label to use for the confirmation button.
     * @param cancelLabel The label to use for the cancellation button.
     * @param parent If not 0, the supplied parent is responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    SystemListDialog(const QString& confirmLabel, const QString& cancelLabel, QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a dialog box with defined confirmation, custom, and cancellations buttons.
     * @param confirmLabel The label to use for the confirmation button.
     * @param customLabel The label to use for the custom button.
     * @param cancelLabel The label to use for the cancellation button.
     * @param parent If not 0, the supplied parent is responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    SystemListDialog(const QString& confirmLabel, const QString& customLabel, const QString& cancelLabel, QObject* parent = 0);

    /*!
     * @brief Destroys the dialog box, and cancels any pending requests.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SystemListDialog();

    /*!
     * @brief Obtains the current selection mode for the dialog box.
     *
     * @return The current selection mode of the dialog box.
     * See @c bb::system::ListSelectionMode for the list of selection modes.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::ListSelectionMode::Type selectionMode() const;

    /*!
     * @brief Retrieves the title for the dialog box.
     * @return The title of the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Retrieves the main text of the dialog box.
     * @return The text of the dialog box.
     *
     * @since BlackBerry 10.1.0
     */
    QString body() const;

    /*!
     * @brief Retrieves whether the text can be displayed as emoticons.
     * @return Whether the dialog box supports emoticons.
     *
     * @since BlackBerry 10.1.0
     */
    bool emoticonsEnabled() const;

    /*!
     * @brief Retrieves the flag indicating if a check box to remember user selection should be included in the dialog box.
     * @return @c true if a check box for remembering the user selection should be included in the dialog box, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    bool includeRememberMe() const;

    /*!
     * @brief Retrieves the flag indicating if the dialog box is updated every time the value of a presentation property is changed.
     * @return @c true if the dialog box automatically updates, @c false if the dialog box doesn't update (in which case the @c show() method
     * must be called after updating the dialog box presentation properties).
     *
     * @since BlackBerry 10.2.0
     */
    bool isAutoUpdateEnabled() const;

    /*!
     * @brief Retrieves whether the check box for @c includeRememberMe is selected by default.
     * @details To obtain the user selection, use @c rememberMeSelection() instead.
     * @return @c true if the check box should be selected by default, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    bool rememberMeChecked() const;

    /*!
     * @brief Retrieves the text associated with the check box for @c includeRememberMe.
     * @return The text for the check box for @c includeRememberMe.
     *
     * @since BlackBerry 10.1.0
     */
    QString rememberMeText() const;

    /*!
     * @brief Retrieves the dialog box's confirmation button.
     * @details This instance retains ownership of the returned value.
     * @return The dialog box's confirmation button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* confirmButton();

    /*!
     * @brief Retrieves the dialog box's custom action button.
     * @details This instance retains ownership of the returned value.
     * @return The dialog box's custom action button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* customButton();

    /*!
     * @brief Retrieves the dialog box's cancellation button.
     * @details This instance retains ownership of the returned value.
     * @return The dialog box's cancellation button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* cancelButton();

    /*!
     * @brief Retrieves the dialog box's default button.
     * @details This instance retains ownership of the returned value.
     *
     * The default button is automatically selected when the user triggers the return key action.
     * If the default button is @c NULL, no button is automatically selected.
     *
     * The returned value is one of the buttons managed by this instance, or @c NULL.
     * @return The dialog box's default button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* defaultButton();

    /*!
     * @brief Indicates if the dialog box is dismissed when a button is selected.
     * @return @c true if selecting a button dismisses the dialog box, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool dismissAutomatically() const;

    /*!
     * @brief Indicates if an activity indicator is displayed on the title bar of the dialog box.
     * @return @c true if the activity indicator is displayed, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool activityIndicatorVisible() const;

    /*!
     * @brief Retrieves the dialog box's return key action.
     * @return The dialog box's return key action.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiReturnKeyAction::Type returnKeyAction() const;

    /*!
     * @brief Retrieves the dialog box's modality.
     * @return The dialog box's modality.  See @c bb::system::SystemUiModality for the list of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiModality::Type modality() const;

    /*!
     * @brief The maximum number of buttons that can be shown without causing an overflow.
     * @details If @c buttonAreaLimit is larger than the number of buttons that will be displayed, all buttons are stacked vertically.
     * @return The limit for the number of buttons that can be accommodated in the button area, or -1 if system defaults should be used.
     *
     * @since BlackBerry 10.0.0
     */
    int buttonAreaLimit() const;

    /*!
     * @brief Indicates if the dialog box is dismissed when a list item is selected.
     *
     * @return @c true if the dialog box should be dismissed when a list item is selected, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool dismissOnSelection() const;

    /*!
     * @brief Indicates how selected list items are highlighted.
     *
     * @return The current highlighting indicator for selected list items.
     * See @c bb::system::ListSelectionIndicator for the list of possible highlighting indicators.
     *
     * @since BlackBerry 10.2.0
     */
    bb::system::ListSelectionIndicator::Type selectionIndicator() const;

    /*!
     * @brief Changes the way in which selection works for this dialog box.
     * @param selectionMode The new method by which selections can be made in the list.
     * See @c bb::system::ListSelectionMode for the list of selection modes.
     *
     * @since BlackBerry 10.0.0
     */
    void setSelectionMode( bb::system::ListSelectionMode::Type selectionMode );

    /*!
     * @brief Sets the title for the dialog box.
     * @param title The new title of the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    void setTitle(const QString& title);

    /*!
     * @brief Sets the main text of the dialog box.
     * @param body The new text of the dialog box.
     *
     * @since BlackBerry 10.1.0
     */
    void setBody(const QString& body);

    /*!
     * @brief Sets whether the text can be displayed as emoticons.
     * @param newEmoticonsEnabled Whether the dialog box supports emoticons.
     *
     * @since BlackBerry 10.1.0
     */
    void setEmoticonsEnabled(bool newEmoticonsEnabled);

    /*!
     * @brief Sets the flag indicating if a check box for remembering user selection should be included in the dialog box.
     * @param value @c true if a check box for remembering user selection should be included, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    void setIncludeRememberMe(bool value);

    /*!
     * @brief Sets the @c autoUpdateEnabled flag of the dialog box.
     * @param update @c true if the dialog box updates automatically,
     * @c false if the dialog box does not update automatically (in which case the @c show() method
     * must be called after updating the dialog box presentation properties).
     *
     * @since BlackBerry 10.2.0
     */
    void setAutoUpdateEnabled(bool update);

    /*!
     * @brief Sets whether the check box for @c includeRememberMe is selected by default.
     * @param newRememberMeSelected @c true if the check box should be selected by default, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    void setRememberMeChecked(bool newRememberMeSelected);

    /*!
     * @brief Sets the text associated with the check box for @c includeRememberMe.
     * @param newRememberMeText The new text for the check box for @c includeRememberMe.
     *
     * @since BlackBerry 10.1.0
     */
    void setRememberMeText(const QString& newRememberMeText);

    /*!
     * @brief Sets the dialog box's default button.
     * @details @c newDefaultButton must be one of the buttons managed by this instance, or @c NULL.
     * If @c NULL is specified, then no button will be associated with the return key action.
     *
     * If a non-managed button is specified, then this property is undefined.
     * @param newDefaultButton The button to associate with the return key action.
     *
     * @since BlackBerry 10.0.0
     */
    void setDefaultButton(bb::system::SystemUiButton* newDefaultButton);

    /*!
     * @brief Sets whether the dialog box is dismissed when a button is selected.
     * @param automaticDismissal @c true if the dialog box should be automatically dismissed
     * on a button press, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void setDismissAutomatically(bool automaticDismissal);

    /*!
     * @brief Sets whether an activity indicator is displayed on the title bar of the dialog box.
     * @param visible @c true if the dialog box displays an activity indicator, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void setActivityIndicatorVisible(bool visible);

    /*!
     * @brief Sets the return key action for the dialog box.
     * @param newReturnKeyAction The new return key action.
     *
     * @since BlackBerry 10.0.0
     */
    void setReturnKeyAction(bb::system::SystemUiReturnKeyAction::Type newReturnKeyAction);

    /*!
     * @brief Sets the modality for the dialog box.
     * @param newModality The new modality preference.
     * @see @c bb::system::SystemUiModality for the list of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    void setModality(bb::system::SystemUiModality::Type newModality);

    /*!
     * @brief Sets the maximum number of buttons to accommodate in the dialog box button area without overflow.
     * @details Values outside the range [1,3] will reset the property to its default value, -1.
     * If @c newButtonAreaLimit is smaller than the number of buttons that will be displayed, all buttons are stacked vertically.
     * @param newButtonAreaLimit The maximum number of buttons in the button area.
     *
     * @since BlackBerry 10.0.0
     */
    void setButtonAreaLimit(int newButtonAreaLimit);

    /*!
     * @brief Sets a flag indicating if the dialog box will be dismissed when the user selects a list item.
     *
     * @param newDismissOnSelection @c true if the dialog box will be dismissed when the user selects a list item,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void setDismissOnSelection(bool newDismissOnSelection);

    /*!
     * @brief Sets the highlighting indicator of selected list items.
     *
     * @param newSelectionIndicator The new highlighting indicator for list items.
     * See @c bb::system::ListSelectionIndicator for the list of possible values.
     *
     * @since BlackBerry 10.2.0
     */
    void setSelectionIndicator(bb::system::ListSelectionIndicator::Type newSelectionIndicator);

    /*!
     * @brief Returns the selection mode to the default of @c bb::system::ListSelectionMode::Single.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetSelectionMode();

    /*!
     * @brief Resets the title of the dialog box to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetTitle();

    /*!
     * @brief Resets the main text of the dialog box to @c QString::null.
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE void resetBody();

    /*!
     * @brief Resets whether the text can display emoticons to @c false.
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE void resetEmoticonsEnabled();

    /*!
     * @brief Resets the flag to show the check box for remembering user selection to @c false.
     * @details To reset the selection state for the check box, use @c resetRememberMeChecked().
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE void resetIncludeRememberMe();

    /*!
     * @brief Resets the @c autoUpdateEnabled flag to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void resetAutoUpdateEnabled();

    /*!
     * @brief Resets the selection state for the check box for @c includeRememberMe to @c true.
     * @details To reset whether to include the check box use @c resetIncludeRememberMe().
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE void resetRememberMeChecked();

    /*!
     * @brief Resets the text for the check box for @c includeRememberMe to @c "Remember Me".
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE void resetRememberMeText();

    /*!
     * @brief Resets the confirmation button for this dialog box.
     * @details When the confirmation button is reset, its label is set to the default value of @c "OK".
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetConfirmButton();

    /*!
     * @brief Resets the custom action button for this dialog box.
     * @details When the custom action button is reset, its label is an empty @c QString, therefore, this button is
     * omitted during @c show() and @c exec() events.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetCustomButton();

    /*!
     * @brief Resets the cancellation button for this dialog box.
     * @details When the cancellation button is reset, its label is set to the default value of @c "Cancel".
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetCancelButton();

    /*!
     * @brief Resets the default button for this dialog box based on the property's precedence rules.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetDefaultButton();

    /*!
     * @brief Resets whether the dialog box is dismissed when a button is selected to @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetDismissAutomatically();

    /*!
     * @brief Resets the dialog box's @c activityIndicatorVisible property to its default value.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE Q_REVISION(1) void resetActivityIndicatorVisible();

    /*!
     * @brief Resets the return key action of the dialog box to @c bb::system::SystemUiReturnKeyAction::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetReturnKeyAction();

    /*!
     * @brief Resets the modality of the dialog box to @c bb::system::SystemUiModality::Application.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetModality();

    /*!
     * @brief Resets the maximum number of buttons to accommodate in the dialog box button area without overflow to -1.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetButtonAreaLimit();

    /*!
     * @brief Resets the dialog box so it will not be dismissed when a list item is selected.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE Q_REVISION(1) void resetDismissOnSelection();

    /*!
     * @brief Resets the highlighting indicator to @c bb::system::ListSelectionIndicator::Button.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE Q_REVISION(1) void resetSelectionIndicator();

    /*!
     * @brief Appends a button to the list of other buttons for this dialog box.
     * @details The dialog box becomes the parent of the button and is responsible for destroying it.
     * @param button The button to add to this dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    void appendButton(bb::system::SystemUiButton* button);

    /*!
     * @brief Retrieves the number of other buttons added to the dialog box.
     * @details This method returns the count of buttons added using the @c appendButton() method.
     * The count does not include the confirmation, custom, or cancellation buttons.
     * @return Returns the number of other buttons.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE int buttonCount() const;

    /*!
     * @brief Retrieves the button at the supplied index.
     * @details This instance retains ownership of the returned value.
     * @param index An index into the list of buttons added using the @c appendButton() method.
     * @return Returns the button at the supplied index or 0 if an invalid index is provided.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* buttonAt(int index) const;

    /*!
     * @brief Clears the list of other buttons for this dialog box.
     * @details This method only affects buttons added to the dialog box using the @c appendButton() method.
     * This method does not affect the confirmation, custom, or cancellation buttons.
     * The button instances are deleted.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void clearButtons();

    /*!
     * @brief Retrieves the result of the last completed request.
     *
     * @details If no request has been made, or if a request is pending, @c bb::system::SystemUiResult::None is returned.
     * @return The result of the last completed request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiResult::Type result() const;

    /*!
     * @brief Retrieves the error that occurred during the request.
     *
     * @details The return value is reset when a new request is made.
     * @return The error that occurred.  See @c bb::system::SystemUiError for the list of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiError::Type error() const;

    /*!
     * @brief Returns the button that was selected when a button selection is made.
     * @details If no button was selected, 0 is returned.
     *
     * This function will return the result of the button selection of @c show() and @c exec().
     *
     * The return value is reset when a new request is made.
     *
     * This instance retains ownership of the returned value.
     * @return The button selected by the user.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::system::SystemUiButton* buttonSelection() const;

    /*!
     * @brief Returns the state of the check box for remembering user selection when the user dismisses the dialog box.
     *
     * @return @c true if the check box for remembering the user selection was checked, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE bool rememberMeSelection() const;

    /*!
     * @brief Returns the indices of the selected elements in this dialog box when a button is pressed.
     *
     * This list contains the indices of the elements that were selected in the list when a button
     * is pressed.  If the selection mode is set to @c bb::system::ListSelectionMode::Single (the default) the list will
     * either be empty or contain exactly one value.  If the selection mode is set to
     * @c bb::system::ListSelectionMode::Multiple the list will contain zero or more values.
     *
     * @note The indices are the position of the elements as they were appended to the dialog box,
     * not the index of the selectable items within the list.  For example, if you appended a header,
     * then a separator, followed by 2 items, and the user selected the first item in the list, the
     * value @c 2 is returned (the header is 0, the separator is 1, and the items are 2 and 3 respectively).
     *
     * @return The list of selected element indices from the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    QList<int> selectedIndices() const;

    /*!
     * @brief Adds a non-selectable separator to the list to be presented.
     *
     * @param text The string to be displayed as the separator.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendSeparator( const QString& text );

    /*!
     * @brief Adds a non-selectable header to the list to be presented.
     *
     * @param text The string to be displayed as the header.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendHeader( const QString& text );

    /*!
     * @brief Adds a non-selectable, optionally disabled, header to the list
     * to be presented.
     *
     * @param text The string to be displayed as the header.
     * @param enabled If @c false, the header is visually disabled.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendHeader( const QString& text, bool enabled );

    /*!
     * @brief Adds a selectable item to the list to be presented.
     *
     * @param text The string to be displayed for this selectable item.
     *
     * @note The item is not tracked by this dialog box or retrievable from this dialog box,
     * therefore, in order to correlate a @c SystemListDialog::selectedIndices entry to an item you must
     * maintain this information yourself.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendItem( const QString& text );

    /*!
     * @brief Adds a selectable, optionally disabled, item to the list to be presented.
     *
     * @param text The string to be displayed for this selectable item.
     * @param enabled If set to @c false this item is visually disabled and will
     * not be allowed to have its selected state toggled.
     *
     * @note The item is not tracked by this dialog box or retrievable from this dialog box,
     * therefore, in order to correlate a @c SystemListDialog::selectedIndices entry to an item, you must
     * maintain this information yourself.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendItem( const QString& text, bool enabled );

    /*!
     * @brief Adds a selectable, optionally disabled and selected, item to the list to be presented.
     *
     * @param text The string to be displayed for this selectable item.
     * @param enabled If set to @c false this item is visually disabled and will
     * not be allowed to have its selected state toggled.
     * @param selected If set to @c true, this item is initially displayed as already selected, if
     * the selection mode allows it.
     *
     * @note The item is not tracked by this dialog box or retrievable from this dialog box,
     * therefore, in order to correlate a @c SystemListDialog::selectedIndices entry to an item, you must
     * maintain this information yourself.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendItem( const QString& text, bool enabled, bool selected );

//!@cond PRIVATE
    /*!
     * @brief Adds a collection of items to the list, each of which is enabled and cleared.
     *
     * @param text The list of strings to be added to the list.
     *
     * @note The item is not tracked by this dialog box or retrievable from this dialog box,
     * so in order to correlate a @c SystemListDialog::selectedIndices entry to an item you must
     * maintain this information yourself.
     *
     * @since BlackBerry 10.0.0
     */
    void appendItems( const QList<QString> &text ) BB_DEPRECATED;
//!@endcond

    /*!
     * @brief Adds a collection of items to the list, each of which is enabled and cleared.
     *
     * @param text The list of strings to be added to the list.
     *
     * @note The item is not tracked by this dialog box or retrievable from this dialog box,
     * so in order to correlate a @c SystemListDialog::selectedIndices entry to an item you must
     * maintain this information yourself.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void appendItems( const QStringList &text );

public Q_SLOTS:

    /*!
     * @brief Removes all headers, separators and items from the list to be presented.
     *
     * @since BlackBerry 10.0.0
     */
    void clearList();

    /*!
     * @brief Displays a dialog box based on current property values.
     * @details The result of the request can be retrieved with the @c SystemListDialog::result property, or by using the @c finished() signal.
     * The button selection can be retrieved with the @c SystemListDialog::buttonSelection property.
     * The list of selected item indices can be retrieved with the @c SystemListDialog::selectedIndices property.
     *
     * Control is returned to the caller immediately. For a blocking request, use @c exec().
     *
     * @since BlackBerry 10.0.0
     */
    void show();

    /*!
     * @brief Displays the dialog box based on current property values.
     * @details The result of the request can be retrieved with the @c SystemListDialog::result property, or by using the @c finished() signal.
     * The button selection can be retrieved with the @c SystemListDialog::buttonSelection property.
     * The list of selected item indices can be retrieved with the @c SystemListDialog::selectedIndices property.
     *
     * Unlike @c show(), this function will block until a button selection is made. If the dialog box is already on the screen,
     * this method will return immediately with @c bb::system::SystemUiResult::DialogCannotBlock.
     *
     * @note Blocking occurs by starting a nested @c QEventLoop. To use this method safely, the following conditions must be met:
     * - Any connections to this slot must use a @c Qt::QueuedConnection, or the slot must be triggered using @c QTimer::singleShot(), and
     * - @c QObject::deleteLater() must be used in place of @c delete when deleting the dialog box object.
     * If these conditions are not met, unexpected behavior may result.
     *
     * @return The result of the request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiResult::Type exec();

    /*!
     * @brief Updates an on-screen dialog box based on the current property values.
     * @details If the dialog box is not on the screen, this method returns immediately and no changes
     * are made to the dialog box.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void update();

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
     * @details The button selection can be retrieved with @c buttonSelection().
     * The list of selected item indices can be retrieved with the @c selectedIndices property.
     * The state of the check box for remembering the content of this dialog box can be retrieved using @c rememberMeSelection().
     * @param value The result of the request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    void finished(bb::system::SystemUiResult::Type value);

    /*!
     * @brief Emitted when the @c selectionMode property is changed programmatically.
     *
     * @param newSelectionMode The new selection mode for this dialog box.  See @c bb::system::ListSelectionMode for the list of possible
     * selection modes.
     *
     * @since BlackBerry 10.0.0
     */
    void selectionModeChanged( bb::system::ListSelectionMode::Type newSelectionMode );

    /*!
     * @brief Emitted when the @c title property is changed programmatically.
     * @param value The new value of the @c title property.
     *
     * @since BlackBerry 10.0.0
     */
    void titleChanged(const QString& value);

    /*!
     * @brief Emitted when the @c body property is changed programmatically.
     * @param value The new value of the @c body property.
     *
     * @since BlackBerry 10.1.0
     */
    void bodyChanged(const QString& value);

    /*!
     * @brief Emitted when the @c emoticonsEnabled property is changed programmatically.
     * @param newEmoticonsEnabled The new value of the @c emoticonsEnabled property.
     *
     * @since BlackBerry 10.1.0
     */
    void emoticonsEnabledChanged(bool newEmoticonsEnabled);

    /*!
     * @brief Emitted when the @c includeRememberMe property is changed programmatically.
     * @param value The new value of the @c includeRememberMe property.
     *
     * @since BlackBerry 10.1.0
     */
    void includeRememberMeChanged(bool value);

    /*!
     * @brief Emitted when the @c autoUpdateEnabled property is changed programmatically.
     * @param value The new value of the @c autoUpdateEnabled property.
     *
     * @since BlackBerry 10.2.0
     */
    void autoUpdateEnabledChanged(bool value);

    /*!
     * @brief Emitted when the @c rememberMeChecked property is changed programmatically.
     * @details When the user dismisses the dialog box, the user selection is available using @c rememberMeSelection().
     * @param newRememberMeSelected The new value of the @c rememberMeChecked property.
     *
     * @since BlackBerry 10.1.0
     */
    void rememberMeCheckedChanged(bool newRememberMeSelected);

    /*!
     * @brief Emitted when the @c rememberMeText property is changed programmatically.
     * @param newRememberMeText The new value of the @c rememberMeText property.
     *
     * @since BlackBerry 10.1.0
     */
    void rememberMeTextChanged(const QString& newRememberMeText);

    /*!
     * @brief Emitted when the @c defaultButton property is changed programmatically.
     * @param newDefaultButton The new value of the @c defaultButton property, or @c NULL if none is set.
     *
     * @since BlackBerry 10.0.0
     */
    void defaultButtonChanged(bb::system::SystemUiButton* newDefaultButton);

    /*!
     * @brief Emitted when the @c dismissAutomatically property is changed programmatically.
     * @param automaticDismissal The new value of the @c dismissAutomatically property.
     *
     * @since BlackBerry 10.0.0
     */
    void dismissAutomaticallyChanged(bool automaticDismissal);

    /*!
     * @brief Emitted when the @c activityIndicatorVisible property is changed programmatically.
     * @param value The new value of the @c activityIndicatorVisible property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void activityIndicatorVisibleChanged(bool value);

    /*!
     * @brief Emitted when the @c returnKeyAction property is changed programmatically.
     * @param newReturnKeyAction The new value of the @c returnKeyAction property.
     *
     * @since BlackBerry 10.0.0
     */
    void returnKeyActionChanged(bb::system::SystemUiReturnKeyAction::Type newReturnKeyAction);

    /*!
     * @brief Emitted when the @c modality property is changed programmatically.
     * @param newModality The new value of the @c modality property.
     *
     * @since BlackBerry 10.0.0
     */
    void modalityChanged(bb::system::SystemUiModality::Type newModality);

    /*!
     * @brief Emitted when the @c buttonAreaLimit property is changed programmatically.
     * @param newButtonAreaLimit The new value of the @c buttonAreaLimit property.
     *
     * @since BlackBerry 10.0.0
     */
    void buttonAreaLimitChanged(int newButtonAreaLimit);

    /*!
     * @brief Emitted when the @c dismissOnSelection property is changed programmatically.
     *
     * @param newDismissOnSelection The new value of the @c dismissOnSelection property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void dismissOnSelectionChanged(bool newDismissOnSelection);

    /*!
     * @brief Emitted when the @c selectionIndicator property is changed programatically.
     *
     * @param newSelectionIndicator The new value of the @c selectionIndicator property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void selectionIndicatorChanged(bb::system::ListSelectionIndicator::Type newSelectionIndicator);

//!@cond PRIVATE
    void finished( int value );
    void returnKeyActionChanged(int newReturnKeyAction);
    void modalityChanged(int newModality);

    void selectionModeChanged( int newSelectionMode );

    Q_REVISION(1) void selectionIndicatorChanged(int newSelectionIndicator);
//!@endcond

private:
//!@cond PRIVATE
    QVariantList selectedIndicesQML() const;
    QDeclarativeListProperty<SystemUiButton> qmlButtons();

    Q_DECLARE_PRIVATE(SystemListDialog)
    Q_DISABLE_COPY(SystemListDialog)
    QScopedPointer<SystemListDialogPrivate> d_ptr;
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemListDialog)
#endif // BB_SYSTEM_SYSTEMLISTDIALOG_HPP
