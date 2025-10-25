/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_CONTACTPICKER_HPP
#define BB_CASCADES_PICKERS_CONTACTPICKER_HPP

#include <bb/cascades/pickers/ContactSelectionMode>
#include <bb/cascades/pickers/SelectedContactAttribute>

#include <bb/cascades/pickers/Global>
#include <bb/pim/contacts/ContactConsts>
#include <bb/system/SecurityPerimeter>

#include <QObject>
#include <QFlags>
#include <QtDeclarative>

namespace bb
{
namespace cascades
{
namespace pickers
{

class ContactPickerPrivate;

/*!
 * @headerfile ContactPicker.hpp <bb/cascades/pickers/ContactPicker>
 *
 * @brief A picker for selecting a contact, multiple contacts, or an attribute of a contact.
 *
 * @details A @c %ContactPicker is a full screen control that allows the user to select a contact, multiple contacts,
 * or an attribute of a contact. The picker can be configured to show only contacts that match specific criteria.
 * When selection is completed, a signal is emitted from the picker with the selected information.
 * A @c canceled() signal is emitted if the user cancels the selection.
 *
 * Filter criteria:
 *
 * Account - The @c %ContactPicker can be filtered to show only contacts belonging to a specific contacts account.
 *
 * Kind    - Only contacts that have a specific kind of @c %ContactAttribute (e.g. Email, Phone) will be shown in the picker.
 *           When the picker is in @c ContactAttributeSelection mode, only those attributes will be shown.
 *
 * SubKind - Only contacts that have a specific kind/subKind pair (e.g. Work Email) will be shown in the picker.
 *           When the picker is in @c %ContactAttributeSelection mode, only those attributes will be shown.
 *
 * The following example demonstrates how to create a @c %ContactPicker for selecting multiple contacts that are
 * filtered to show only contacts that have phone numbers:
 *
 * @code
 * ContactPicker *contactPicker = new ContactPicker();
 * contactPicker->setMode(ContactSelectionMode::Multiple);
 * contactPicker->setKindFilters(QSet<bb::pim::contacts::AttributeKind::Type>()
 *      << bb::pim::contacts::AttributeKind::Phone);
 *
 * QObject::connect(contactPicker,
 *      SIGNAL(contactsSelected(QList<int> &)),
 *      this,
 *      SLOT(onContactsSelected(QList<int> &)));
 *
 * QObject::connect(contactPicker,
 *      SIGNAL(canceled()),
 *      this,
 *      SLOT(onCanceled()));
 * contactPicker->open();
 *@endcode
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT ContactPicker : public QObject{
    Q_OBJECT

    /*!
     * @brief The mode the picker should be launched in.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::pickers::ContactSelectionMode::Type mode READ mode WRITE setMode NOTIFY modeChanged FINAL)

    /*!
     * @brief A custom message to be displayed in the title of the picker.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)

    /*!
     * @brief A custom label to be displayed in the confirmation button of the picker.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString confirmButtonLabel READ confirmButtonLabel WRITE setConfirmButtonLabel NOTIFY confirmButtonLabelChanged FINAL)

    /*!
     * @brief A specific account to select contacts from.
     *
     * When this is set, only contacts that belong to this account will be displayed.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int account READ account WRITE setAccount NOTIFY accountChanged FINAL)

    /*!
     * @brief Enable remote search to be used in the contact picker.
     *
     * When this is set to true, remote search will be allowed in the picker if it is supported by any accounts.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bool remoteSearchEnabled READ remoteSearchEnabled WRITE setRemoteSearchEnabled NOTIFY remoteSearchEnabledChanged FINAL)

public:

    /*!
     * @brief Constructs a @c ContactPicker.
     *
     * By default the picker is in the @c %ContactSelectionMode::Single mode.
     *
     *@param parent The parent or @c 0. If not @c 0, the ownership of constructed @c %ContactPicker will be transferred to the parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit ContactPicker(QObject *parent = 0);

    /*!
     * @brief Destructs the @c %ContactPicker.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ContactPicker();

    /*!
     * @brief Opens the @c %ContactPicker.
     *
     * This will display the contact picker allowing the user to perform the selection.
     *
     * Any filters or customizations to the picker need to be set before @c open() is called. Any call to setters after @c open() is called will be ignored.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void open();

    /*!
     * @brief Closes the picker.
     *
     * Use this only when the user's input is no longer needed. Typically, the picker is closed as soon the user completes the selection.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void close();

    /*!
     * @brief Sets the mode the picker should be launched in.
     *
     * By default, the picker is launched in @c %ContactSelectionMode::Single mode.
     *
     * @param ContactSelectionMode The selection mode for the picker.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setMode(bb::cascades::pickers::ContactSelectionMode::Type mode);

    /*!
     * @brief Returns the mode of the picker
     *
     * @return The @c ContactSelectionMode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::ContactSelectionMode::Type mode() const;

    /*!
     * @brief Sets a message to be displayed in the title of the picker.
     *
     * If this is not set, the default title will be used.
     *
     * @param QString The title for the picker.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setTitle(const QString &title);

    /*!
     * @brief Returns the title of the picker.
     *
     * @return The title of the picker as a @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Sets a specific account to select contacts from.
     *
     * When this is set, only contacts that belong to this account will be displayed.
     *
     * @see AccountService
     *
     * @param accountId The account id
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setAccount(int accountId);

    /*!
     * @see setAccount()
     *
     * @since BlackBerry 10.0.0
     */
    int account() const;

    /*!
     * @brief Filters the list of contacts displayed to contain only contacts where the sources of the contact do not belong to
     * any of the provided account IDs.
     *
     * @param accountIds The set of account IDs to filter based on.
     *
     */
    Q_SLOT void setExcludeAccounts(const QList<int> &accountIds);

    /*!
     * @see excludeAccounts()
     */
    QList<int> excludedAccounts() const;

    /*!
     * @brief Sets a custom label to be displayed in the confirmation button of the picker.
     *
     * If this is not set, the default label will be used.
     *
     * @param confirmButtonLabel The label displayed in the confirmation button.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setConfirmButtonLabel(const QString &confirmButtonLabel);

    /*!
     * @see setConfirmButtonLabel.
     *
     * @since BlackBerry 10.0.0
     */
    QString confirmButtonLabel() const;

    /*!
     * @brief Sets a set of attribute kinds (e.g. Email, Phone) that should be used for filtering the contacts in the picker.
     *
     * A contact must have one or more of the attributes in this set in order to be displayed.
     *
     * @see ContactConsts
     *
     * @param kindFilters The set of filters.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setKindFilters(const QSet<bb::pim::contacts::AttributeKind::Type> &kindFilters);

    /*!
     * @brief Returns the attribute kind filters.
     *
     * @see setKindFilters()
     *
     * @since BlackBerry 10.0.0
     */
    QSet<bb::pim::contacts::AttributeKind::Type> kindFilters() const;

    /*!
     * @brief Sets a set of Attribute kind/subKind pairs to should be used for filtering the contacts in the picker.
     *
     * A contact must have at least one attribute that matches one of the pairs of kind/subKind.
     *
     * @see ContactConsts
     *
     * @param subKindFilters The set of @c kindSubKindSpecifier.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setSubKindFilters(const QSet<bb::pim::contacts::KindSubKindSpecifier> &subKindFilters);

    /*!
     * @see setSubKindFilters()
     *
     * @since BlackBerry 10.0.0
     */
    QSet<bb::pim::contacts::KindSubKindSpecifier> subKindFilters() const;

    /*!
     * @brief Returns the @c id of the contact that was selected in the @c %ContactPicker when in @c %ContactSelectionMode::Single mode.
     *
     * If the picker mode is not @c %ContactSelectionMode::Single, this value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    int selectedContactId() const;

    /*!
     * @brief Returns the @c ids of the contacts that were selected in the ContactPicker when in @c %ContactSelectionMode::Multiple mode.
     *
     * If the picker mode is not @c %ContactSelectionMode::Multiple, this value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QList<int> selectedContactsIds() const;

    /*!
     * @brief Returns the attribute selected in the @c %ContactPicker when in @c %ContactSelectionMode::Attribute mode.
     *
     * If the picker mode is not @c %ContactSelectionMode::Attribute, this value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    SelectedContactAttribute selectedContactAttribute() const;

    /*!
     * @brief Returns the attributes selected in the @c %ContactPicker when in @c %ContactSelectionMode::AttributeTokens mode.
     *
     * If the picker mode is not @c %ContactSelectionMode::MultipleAttributes, this value is undefined.
     *
     * @return A list of @c SelectedContactAttribute objects that were selected by the user.
     *
     * @since BlackBerry 10.3.1
     */
    QList<SelectedContactAttribute> selectedContactAttributes() const;

    /*!
     * @brief Sets a flag to allow remote search to be used in the contact picker, this allows the picker
     * to search remote accounts for contacts if supported.
     *
     * If this is not set, remote search will not be enabled in the picker.
     *
     * @param remoteSearchEnabled the flag whether to enable remote search
     *
     * @since BlackBerry 10.3.0
     */
    Q_SLOT void setRemoteSearchEnabled(bool remoteSearchEnabled);

    /*!
     * @brief Returns true if remote search is enabled in the current contact picker.
     *
     * @since BlackBerry 10.3.0
     */
    bool remoteSearchEnabled() const;

/*! @cond PRIVATE */
    /*!
     * @brief Sets the security perimeter in which @c %ContactPicker should be invoked. Only required for hybrid applications using this api.
     *
     * @param perimeter Security perimeter to use for @c %ContactPicker invocation.
     *
     * @since BlackBerry 10.1.0
     */
    void setPerimeter(bb::system::SecurityPerimeter::Type perimeter);
/*! @endcond */
Q_SIGNALS:

    /*!
     * @brief Emitted when the cancel button is clicked in the @c %ContactPicker.
     *
     * @since BlackBerry 10.0.0
     */
    void canceled();

    /*!
     * @brief Emitted when launching the picker fails. This occurs only when system resources are depleted.
     *
     * @since BlackBerry 10.0.0
     */
    void error();

    /*!
     * @brief Emitted when a contact is selected when not in multi-select mode.
     *
     * @param contactId The id of the selected contact.
     *
     * @since BlackBerry 10.0.0
     */
    void contactSelected(int contactId);

    /*!
     * @brief Emitted completes the selection when in multi-select mode.
     *
     * @param contactIds The list of selected @c contactIds.
     *
     * @since BlackBerry 10.0.0
     */
    void contactsSelected(const QList<int> &contactIds);

    /*!
     * @brief Emitted when a contact attribute is selected.
     *
     * @param attribute A @c SelectedContactAttribute object populated with the values of the selected attribute.
     *
     * @since BlackBerry 10.0.0
     */
    void contactAttributeSelected(const bb::cascades::pickers::SelectedContactAttribute &attribute);

    /*!
     * @brief Emitted when one or more contact attributes are selected in multiple attribute selection mode.
     *
     * @param attributes A list of @c SelectedContactAttribute objects populated with the values of the selected attributes.
     *
     * @since BlackBerry 10.3.1
     */
    void contactAttributesSelected(const QList<bb::cascades::pickers::SelectedContactAttribute> &attributes);

    /*!
     * @brief Emitted when the @c Mode property changes
     *
     * @param newMode The new @c %Mode of the @c %ContactPicker.
     *
     * @since BlackBerry 10.0.0
     */
    void modeChanged(bb::cascades::pickers::ContactSelectionMode::Type newMode);

    /*!
     * @brief Emitted when the confirm label changes
     *
     * @param newLabel The new @c Mode of the @c %ContactPicker.
     *
     * @since BlackBerry 10.0.0
     */
    void confirmButtonLabelChanged(const QString &newLabel);

    /*!
     * @brief Emitted when the kind filter list is replaced
     *
     * @since BlackBerry 10.0.0
     */
    void kindFiltersChanged(const QSet<bb::pim::contacts::AttributeKind::Type> &kindFilters);

    /*!
     * @brief Emitted when the kind filter list is replaced
     *
     * @since BlackBerry 10.0.0
     */
    void subKindFiltersChanged(const QSet<bb::pim::contacts::KindSubKindSpecifier> &subKindFilters);

    /*!
     * @brief Emitted when the title property changes
     *
     * @param newTitle The new title for the @c %ContactPicker.
     *
     * @since BlackBerry 10.0.0
     */
    void titleChanged(const QString &newTitle);

    /*!
     * @brief Emitted when the account filter changes
     *
     * @param newAccount The new account id.
     *
     * @since BlackBerry 10.0.0
     */
    void accountChanged(int newAccount);

    /*!
     * @brief Emitted when the excluded accounts change
     *
     * @param accountIds The new set of excluded accounts.
     */
    void excludedAccountsChanged(const QList<int> &accountIds);

    /*!
     * @brief Emitted when the flag for allowing remote search changes.
     *
     * @param remoteSearchEnabled The value whether remote search is allowed.
     *
     * @since BlackBerry 10.3.0
     */
    void remoteSearchEnabledChanged(bool remoteSearchEnabled);

private:
    //! @cond PRIVATE
    Q_DECLARE_PRIVATE(ContactPicker)
    Q_DISABLE_COPY(ContactPicker)
    ContactPickerPrivate *d_ptr;
    //! @endcond PRIVATE
};

} /* namespace pickers */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_PICKERS_CONTACTPICKER_HPP */
