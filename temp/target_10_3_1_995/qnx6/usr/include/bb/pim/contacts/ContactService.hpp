/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTSERVICE_HPP
#define BB_PIM_CONTACTS_CONTACTSERVICE_HPP

#include <bb/pim/account/Account>
#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/contacts/Contact>
#include <bb/pim/contacts/ContactFolder>
#include <bb/pim/contacts/ContactGroup>
#include <bb/pim/contacts/ContactOnlineStatus>
#include <bb/pim/contacts/ContactFavouriteAction>
#include <bb/pim/contacts/ContactNews>
#include <bb/pim/contacts/ContactRemoteSearchFilters>
#include <bb/pim/contacts/ContactAutoCompleteSearchFilters>
#include <bb/pim/contacts/ContactSearchFilters>
#include <bb/pim/contacts/ContactListFilters>
#include <bb/pim/Global>
#include <QSharedPointer>
#include <QString>
#include <QList>
#include <QObject>

namespace bb {
namespace pim {
namespace contacts {

class BB_PIM_EXPORT ContactServicePrivate;

/*!
 * @brief The @c ContactService class provides CRUD (create/read/update/delete) operations on @c Contact objects.
 *
 * @permissions The application must have the @c access_pimdomain_contacts permission to access the contacts
 * database.
 *
 * @details @c %ContactService provides functions for adding, retrieving, updating, and deleting @c %Contact
 * objects, as well as for searching and counting @c %Contact objects based on criteria specified using filter
 * classes, such as @c ContactListFilters and @c ContactSearchFilters.
 *
 * Each contact that's retrieved using the @c %ContactService can come from any source, and can sometimes come
 * from multiple sources if it's a merged contact. For example, contacts can come from the Contacts application,
 * BlackBerry Messenger and other social networking applications, or an inserted SIM card. There are functions
 * that you can use to filter contacts or handle contacts from their respective sources. However, the primary
 * use case for this class is to treat all contacts the same, regardless of source.
 *
 * Here's how to retrieve a list of contacts using @c contacts():
 * @code
 *      ContactListFilters filters;
 *      filters.setLimit(20);
 *      QList<Contact> contactList = ContactService().contacts(filters);
 * @endcode
 *
 * Here's how to search for a list of contacts with certain criteria using @c searchContacts():
 * @code
 *      ContactSearchFilters filters;
 *      filters.setLimit(5);
 *      filters.setSearchValue("Joe");
 *      QList<Contact> contactList = ContactService().searchContacts(filters);
 * @endcode
 *
 * Here's how to retrieve the complete details of a single contact using @c contactDetails():
 * @code
 *      Contact contact = ContactService().contactDetails(5);
 * @endcode
 *
 * @see Contact
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactService : public QObject
{
Q_OBJECT
public:
    /*!
     * @brief Constructs a new @c ContactService with the provided parent.
     *
     * @details You don't need to provide a parent when you construct a @c %ContactService object. If you don't provide
     * a parent, the default value is @c NULL. If you create a @c %ContactService object and provide a parent that is
     * not @c NULL, you shouldn't allocate the instance on the stack. The parent that you provide is responsible for
     * deleting the instance.
     *
     * @param parent The parent of the @c %ContactService, or @c NULL if no parent is provided.
     *
     * @since BlackBerry 10.0.0
     */
    ContactService(QObject* parent = NULL);

    /*!
     * @brief Destroys this @c ContactService.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ContactService();

    /*!
     * @brief Retrieves the full details for the @c Contact with the provided ID.
     *
     * @details Only contacts that are retrieved using this function contain the full data of a particular contact. Other
     * functions in this class return partial contacts. For this reason, you should update only those contacts that you
     * retrieve using this function (instead of contacts that you retrieve using other functions in this class). Otherwise,
     * you risk losing data because the contact content in the data will be overwritten with partial contact content.
     *
     * @param contactId The ID of the contact whose details should be retrieved.
     *
     * @return The contact (including full details) with the provided contact ID.
     *
     * @since BlackBerry 10.0.0
     */
    Contact contactDetails(ContactId contactId) const;

    /*!
     * @brief Retrieves a list of partial contacts based on the criteria in the provided list filter.
     *
     * @details The contacts that are returned are based on the criteria that's specified in the provided
     * @c ContactListFilters. For example, you can specify that you want to return only contacts that have a specific
     * kind and sub-kind.
     *
     * You can provide an empty @c %ContactListFilters to retrieve the entire contact list. Each contact is a partial
     * contact and has very little information attached to it. These partial contacts are designed to be used to populate
     * a list view, and provide better performance in this case than returning contacts with full details. It is strongly
     * recommended to use the paging mechanism available in @c %ContactListFilters by setting an anchor ID and result
     * limit values. The more data that's retrieved from this list, the slower the response time. For reasonable
     * performance, you shouldn't exceed 200 results per page.
     *
     * Here's how to retrieve a list of partial contacts and process the contacts efficiently using anchors and result
     * limits:
     *
     * @code
     * ContactService service;
     * QList<Contact> contactPage;

     * ContactListFilters options;
     * const int maxLimit = 20;
     * options.setLimit(maxLimit);
     * do
     * {
     *     contactPage = service.contacts(options);
     *     doStuff(contactPage);
     *     if (contactPage.size() == maxLimit)
     *     {
     *         options.setAnchorId(contactPage[maxLimit-1].id());
     *     }
     *     else
     *     {
     *         break;
     *     }
     * } while (true);
     *
     * @endcode
     *
     * @param filters The list filters to apply to the returned contact list.
     *
     * @return A list of partial contacts that match the criteria in the provided list filter.
     *
     * @see ContactListFilters
     *
     * @since BlackBerry 10.0.0
     */
    QList<Contact> contacts(const ContactListFilters& filters) const;

    /*!
     * @brief Searches for and retrieves a list of contacts based on the provided search filter.
     *
     * @details Similar to @c contacts(), this function allows pagination. The filters that you provide affect the search
     * results that are returned. At a minimum, you should set the search value within the filters before calling this
     * function. Note that searches where the search value is a single letter can be slow. By default, the search is
     * performed against certain attribute types. The default attribute types are first name, last name, company name,
     * phone, and email.
     *
     * Here's how to search for contacts that include the letter H:
     *
     * @code
     * ContactService service;
     * QList<Contact> contacts;
     * ContactSearchFilters options;
     * options.setSearchValue("H");
     * contacts = service.searchContacts(options);
     * @endcode
     *
     * @param filters The search filters to apply to the search results.
     *
     * @return A list of partial contacts that match the criteria in the provided search filter.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Contact> searchContacts(const ContactSearchFilters& filters) const;

    /*!
     * @brief Retrieves the number of contacts that match the criteria in the provided list filter.
     *
     * @details Here's how to retrieve the number of contacts that include the letter H:
     *
     * @code
     * ContactService service;
     * int count;
     * ContactListFilters options;
     * options.setIsFavourite(true);
     * count = service.count(options);
     * @endcode
     *
     * @param filters The list filters to apply to the returned result.
     *
     * @return The number of contacts that match the criteria in the provided list filter.
     *
     * @since BlackBerry 10.0.0
     */
    int count(const ContactListFilters& filters) const;

    /*!
     * @brief Retrieves the number of contacts that match the criteria in the provided search filter.
     *
     * @details Here's how to retrieve the number of contacts that include the letter H:
     *
     * @code
     * ContactService service;
     * int count;
     * ContactSearchFilters options;
     * options.setSearchValue("H");
     * count = service.count(options);
     * @endcode
     *
     * @param filters The search filters to apply to the returned result.
     *
     * @return The number of contacts that match the criteria in the provided search filter.
     *
     * @since BlackBerry 10.0.0
     */
    int count(const ContactSearchFilters& filters) const;

    /*!
     * @brief Performs a search based on the provided phone number.
     *
     * @details The phone number that's provided is normalized (special characters and spaces are removed). This
     * function is similar to @c searchContacts(), but is designed specifically for reverse look-up of phone numbers.
     * This function searches only the phone number field, instead of all fields. This can be very useful for caller
     * ID functionality.
     *
     * @param filters The search filters to apply to the search results.
     *
     * @return A list of contacts that match the criteria in the provided search filter.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Contact> searchContactsByPhoneNumber(const ContactSearchFilters& filters) const;

    /*!
     * @brief Performs a search of email, social providers, and so on, for auto-complete results in the "To|Cc|Bcc"
     * fields.
     *
     * @details This search is a very targeted search, and is designed to be used as a fast lookup for
     * auto-completion of email addresses.
     *
     * @param filters The auto-complete search filters to apply to the search results.
     *
     * @return A list of contacts that match the criteria in the provided search filter.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Contact> searchContactsAutoComplete(const ContactAutoCompleteSearchFilters& filters) const;

    /*!
     * @brief Indicates whether remote search is available within any of the accounts that are integrated.
     *
     * @details This function queries the system to see if there is an integrated account that has remote search
     * capability.
     *
     * @return @c true if remote search is available in an integrated account, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isRemoteSearchAvailable() const;

    /*!
     * @brief Indicates whether remote search is available for the specified account.
     *
     * @details This function queries the system to see if there is an integrated account that has remote search
     * capability.
     *
     * @param account The account to check if remote search is currently available.
     *
     * @return @c True if remote search is available in an integrated account, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isRemoteSearchAvailable(AccountId account) const;

    /*!
     * @brief Performs a remote search based on the provided remote search filters.
     *
     * @details This function performs a remote search on the global address list (GAL) for contacts. You should use
     * this function in conjunction with @c remoteSearchableAccounts(). For each account that supports remote
     * search, you can use @c searchRemote() to paginate the search results. For example, here's how to paginate
     * search results using a start index and end index:
     *
     * @code
     * QList<bb::pim::contacts::Contact> contacts;
     * bb::pim::contacts::ContactRemoteSearchFilters options;
     * options.setSearchValue(value);
     * options.setAccount(accountId);
     * options.setStartIndex(startIndex);
     * options.setEndIndex(endIndex);
     * contacts = ContactService().searchRemote(options);
     * @endcode
     *
     * @param filters The remote search filters to apply to the search results.
     *
     * @return A list of remote contacts that match the criteria in the provided remote search filter.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Contact> searchRemote(const ContactRemoteSearchFilters& filters) const;

    /*!
     * @brief Retrieves the list of account IDs for accounts that support remote search.
     *
     * @details After you retrieve the account IDs using this function, you can use the @c AccountService to get
     * specific information about the account.
     *
     * @return A list of account IDs for accounts that support remote search.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AccountId> remoteSearchableAccounts() const;

    /*!
     * @brief Creates and adds a new contact to the database.
     *
     * @details You should use a @c ContactBuilder to create the new @c Contact and set its properties, and then
     * use this function to persist the new @c %Contact to the database. The @c contactsAdded() signal is emitted
     * when contacts are added successfully using this function.
     *
     * As a @c %Contact is added or changed, the @c %Contact might be merged automatically with an existing
     * @c %Contact that has the same contact ID. In this case, the @c %Contact that's returned might have the
     * same contact ID as an existing contact, and the @c contactsChanged() signal is emitted instead of the
     * @c contactsAdded() signal.
     *
     * Here's how to create a @c %Contact using a @c %ContactBuilder and persist it to the database:
     *
     * @code
     * using namespace bb::pim::contacts;
     *
     * ContactService service;
     * ContactBuilder builder;
     * builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Name)
     *                      .setSubKind(AttributeSubKind::NameGiven)
     *                      .setValue("Hello");
     * builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Profile)
     *                      .setSubKind(AttributeSubKind::ProfileTwitter)
     *                      .setValue("World"));
     * Contact createdContact = service.createContact(builder, false);
     * @endcode
     *
     * @param contact The new contact to be persisted.
     * @param isWork If @c true, the contact will be stored in the enterprise perimeter. If application
     * permissions do not allow it or there is no enterprise account integrated, the contact will be created in
     * the personal perimeter.
     *
     * @return The contact that was created.
     *
     * @see updateContact(), deleteContact()
     *
     * @since BlackBerry 10.0.0
     */
    Contact createContact(const Contact& contact, bool isWork) const;

    /*!
     * @brief Creates and adds a new contact to the database.
     *
     * @details You should use a @c ContactBuilder to create the new @c Contact and set its properties, and then
     * use this function to persist the new @c %Contact to the database. The @c contactsAdded() signal is emitted
     * when contacts are added successfully using this function.
     *
     * As a @c %Contact is added or changed, the @c %Contact might be merged automatically with an existing
     * @c %Contact that has the same contact ID. In this case, the @c %Contact that's returned might have the
     * same contact ID as an existing contact, and the @c contactsChanged() signal is emitted instead of the
     * @c contactsAdded() signal.
     *
     * Here's how to create a @c %Contact using a @c %ContactBuilder and persist it to the database:
     *
     * @code
     * using namespace bb::pim::contacts;
     *
     * ContactService service;
     * ContactBuilder builder;
     * builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Name)
     *                      .setSubKind(AttributeSubKind::NameGiven)
     *                      .setValue("Hello");
     * builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Profile)
     *                      .setSubKind(AttributeSubKind::ProfileTwitter)
     *                      .setValue("World"));
     * Contact createdContact = service.createContact(builder, false, true);
     * @endcode
     *
     * @param contact The new contact to be persisted.
     * @param isWork If @c true, the contact will be stored in the enterprise perimeter. If application
     * permissions do not allow it or there is no enterprise account integrated, the contact will be created in
     * the personal perimeter.
     * @param isManualMergeOnly If @c true, the contact will not be merged automatically with another contact
     * even if a matching contact is found. However, this contact can be merged by a merge request.
     *
     * @return The contact that was created.
     *
     * @see updateContact(), deleteContact()
     *
     * @since BlackBerry 10.0.0
     */
    Contact createContact(const Contact& contact, bool isWork, bool isManualMergeOnly) const;

    /*!
     * @brief Creates and adds a new contact to the database.
     *
     * @details You should use a @c ContactBuilder to create the new @c Contact and set its properties, and then
     * use this function to persist the new @c %Contact to the database. The @c contactsAdded() signal is emitted
     * when contacts are added successfully using this function.
     *
     * As a @c %Contact is added or changed, the @c %Contact might be merged automatically with an existing
     * @c %Contact that has the same contact ID. In this case, the @c %Contact that's returned might have the
     * same contact ID as an existing contact, and the @c contactsChanged() signal is emitted instead of the
     * @c contactsAdded() signal.
     *
     * Here's how to create a @c %Contact using a @c %ContactBuilder and persist it to the database:
     *
     * @code
     * using namespace bb::pim::contacts;
     *
     * ContactService service;
     * ContactBuilder builder;
     * builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Name)
     *                      .setSubKind(AttributeSubKind::NameGiven)
     *                      .setValue("Hello");
     * builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Profile)
     *                      .setSubKind(AttributeSubKind::ProfileTwitter)
     *                      .setValue("World"));
     * Contact createdContact = service.createContact(builder, false, true, accountId);
     * @endcode
     *
     * @param contact The new contact to be persisted.
     * @param isWork If @c true, the contact will be stored in the enterprise perimeter. If application
     * permissions do not allow it or there is no enterprise account integrated, the contact will be created in
     * the personal perimeter.
     * @param isManualMergeOnly If @c true, the contact will not be merged automatically with another contact
     * even if a matching contact is found. However, this contact can be merged by a merge request.
     * @param AccountId A list of accountIds that the contact will be created in.
     *
     * @return The contact that was created.
     *
     * @see updateContact(), deleteContact()
     *
     * @since BlackBerry 10.3.0
     */
    Contact createContact(const Contact& contact, bool isWork, bool isManualMergeOnly, QList<AccountId> &AccountId) const;

    /*!
     * @brief Creates and adds multiple new contacts to the database in the personal perimeter.
     *
     * @details You should use a @c ContactBuilder to create the new @c Contact objects and set their properties,
     * and then use this function to persist the @c %Contact objects to the database. The @c contactsAdded() signal
     * is emitted when contacts are added successfully using this function.
     *
     * As a @c %Contact is added or changed, the @c %Contact might be merged automatically with an existing
     * @c %Contact that has the same contact ID. In this case, the @c contactsChanged() signal is emitted instead
     * of the @c contactsAdded() signal.
     *
     * Here's how to create multiple @c %Contact objects using a @c %ContactBuilder and persist them to the database:
     *
     * @code
     * using namespace bb::pim::contacts;
     *
     * ContactService service;
     * QList<Contact> contacts;
     * for (int i = 1; i < 100; i++) {
     *      ContactBuilder builder;
     *      builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Name)
     *                      .setSubKind(AttributeSubKind::NameGiven)
     *                      .setValue(QString("Hello" + QString::number(i))));
     *      builder.addAttribute(ContactAttributeBuilder()
     *                      .setKind(AttributeKind::Profile)
     *                      .setSubKind(AttributeSubKind::ProfileTwitter)
     *                      .setValue(QString("World" + QString::number(i))));
     *      contacts.append(builder)
     * }
     *
     * bool result = service.createContacts(contacts);
     * @endcode
     *
     * @param contacts The new contacts to be persisted.
     *
     * @return @c true if contacts were added successfully, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */

    bool createContacts(const QList<Contact> &contacts) const;

    /*!
     * @brief Update an existing contact in the database.
     *
     * @details This function is similar to @c createContact(), but it uses a @c Contact that's retrieved using
     * @c contactDetails(). You can use a @c ContactBuilder to update the properties of the @c %Contact, and then
     * use this function to persist the updated information to the database. The @c contactsChanged() signal is
     * emitted when contacts are updated successfully using this function.
     *
     * As a @c %Contact is added or changed, the @c %Contact might be merged automatically with an existing
     * @c %Contact. In this case, the @c %Contact that's returned from this function might not have the same
     * contact ID as the one that was passed in to be updated, and the @c contactsDeleted() and
     * @c contactsChanged() signals are emitted.
     *
     * Here's how to update a @c %Contact:
     *
     * @code
     * Contact contact = service.contactDetails(42);
     * if (contact.id())
     * {
     *     ContactBuilder editor = contact.edit();
     *     editor.addAttribute(ContactAttributeBuilder()
     *                          .setKind(AttributeKind::Phone)
     *                          .setSubKind(AttributeSubKind::Work)
     *                          .setValue("555-6745"));
     *     Contact updatedContact = ContactService().updateContact(editor);
     * }
     * @endcode
     *
     * @param contact The contact to be updated.
     *
     * @return The contact that was updated.
     *
     * @see createContact(), deleteContact()
     *
     * @since BlackBerry 10.0.0
     */
    Contact updateContact(const Contact &contact) const;

    /*!
     * @brief Deletes a contact from the database.
     *
     * @details This function deletes the @c Contact with the provided contact ID from the database. The
     * @c contactsDeleted() signal is emitted when a contact is deleted successfully using this function.
     *
     * @param contactId The contact ID of the contact to delete.
     *
     * @see createContact(), updateContact()
     *
     * @since BlackBerry 10.0.0
     */
    void deleteContact(ContactId contactId) const;

    /*!
     * @brief Deletes a list of contacts from the database.
     *
     * @details This function deletes contacts with the provided contact IDs from the database.
     *
     * @param contactIds The list of contact IDs to delete.
     *
     * @see createContact(), updateContact()
     *
     * @since BlackBerry 10.3.0
     */
    void deleteContacts(QList<ContactId> &contactIds) const;

    /*!
     * @brief Deletes a contact from the database.
     *
     * @details This function deletes the @c Contact with the provided contact ID and account ID from the database.
     * The @c contactsDeleted() signal is emitted when a contact is deleted successfully using this function.
     *
     * @param contactId The contact ID of the contact to delete.
     * @param accountId The account ID of the contact to delete.
     *
     * @see createContact(), updateContact()
     *
     * @since BlackBerry 10.3.0
     */
    void deleteContact(ContactId contactId, AccountId accountId) const;

    /*!
     * @brief Copies a contact to another account.
     *
     * @details This function copies a contact to a specified account or accounts.
     *
     * @param contactId The contact ID of the contact to copy.
     * @param accountIds A list of accounts to copy the contact to.
     *
     * @since BlackBerry 10.3.0
     */
    void copyTo(ContactId contactId, QList<AccountId> &accountIds) const;

    /*!
     * @brief Sets whether the provided contact is a favorite.
     *
     * @details Favorite contacts are displayed in the favorites grid in the Contacts application, at the top
     * of the contact list.
     *
     * @param contactId The contact ID of the contact to set as a favorite.
     * @param favourite If @c true the contact is set as a favorite, if @c false the contact is not set as a
     * favorite.
     *
     * @since BlackBerry 10.0.0
     */
    void setFavouriteContact(ContactId contactId, bool favourite) const;

    /*!
     * @brief Retrieves the list of favorite actions associated with the provided contact.
     *
     * @details For more information about favorite actions, see @c ContactFavouriteAction.
     *
     * @param contactId The contact ID of the contact to retrieve the list of favorite actions for.
     *
     * @return A list of favorite actions associated with the provided contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactFavouriteAction> favouriteActions(ContactId contactId) const;

    /*!
     * @brief Sets a favorite action for an attribute within the provided contact.
     *
     * @details This function sets a favorite action to associate with a contact attribute.
     *
     * @param id The contact ID of the contact to set a favorite action for.
     * @param action The favorite action to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setFavouriteAction(ContactId id, const ContactFavouriteAction& action) const;

    /*!
     * @brief Retrieves the online status information about the provided contact.
     *
     * @details If a contact is sourced from a social provider, you can use this function to retrieve its online
     * status. For example, you can retrieve the online status of a BBM contact using this function.
     *
     * @param contactId The contact ID of the contact to retrieve online status information for.
     *
     * @return A list of online statuses for the provided contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactOnlineStatus> onlineStatus(ContactId contactId) const;

    /*!
     * @brief Retrieves the online status information about the provided contact from one of its source accounts.
     *
     * @details If a contact is sourced from a social provider, you can use this function to retrieve its online
     * status. For example, you can retrieve the online status of a BBM contact using this function.
     *
     * @param account The source account ID of the contact to retrieve online status information from.
     * @param contactId The contact ID of the contact to retrieve online status information for.
     *
     * @return A list of online statuses for the provided contact.
     *
     * @since BlackBerry 10.2.0
     */
    QList<ContactOnlineStatus> onlineStatus(AccountId accountId, ContactId contactId) const;

    /*!
     * @brief Retrieves the activity stream that's shared between you and the provided contact.
     *
     * @param contactId The contact ID of the contact to retrieve the activity stream for.
     *
     * @return A list of activities that are shared between you and the provided contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactActivity> activities(ContactId contactId) const;

    /*!
     * @brief Retrieves the activity stream that's shared between you and the provided contact.
     *
     * @param contactId The contact ID of the contact to retrieve the activity stream for.
     * @param activityFilter The filter for different activity types. Multiple activity types can
     *        be specified using the bitwise OR operator.
     *
     * @return A list of activities that are shared between you and the provided contact.
     *
     * @since BlackBerry 10.1.0
     */
    QList<ContactActivity> activities(ContactId contactId , Activity::Types activityFilter) const;

    /*!
     * @brief Retrieves news that's related to information in the provided contact.
     *
     * @details This function uses the contents of the provided @c Contact (such as company, email, name, and so on)
     * to form a request to fetch the relevant news for the contact.
     *
     * @param contact The contact to retrieve news for.
     * @param limit The maximum number of news items that are returned.
     *
     * @return A list of news items that are related to the provided contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactNews> retrieveNews(const Contact &contact, unsigned int limit) const;

    /*!
     * @brief Retrieves the individual contacts that make up the provided merged contact.
     *
     * @details Using the provided contact ID, this function retrieves the individual contacts that make up this
     * contact. These contacts come from the different accounts. The contacts that are returned are designed to be
     * read-only return values, and you shouldn't delete or update them using the @c ContactService.
     *
     * @param contactId The contact ID of the merged contact to retrieve individual contacts for.
     *
     * @return A list of individual contacts that make up the provided merged contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Contact> mergedContacts(ContactId contactId) const;

    /*!
     * @brief Merges the provided list of unified contacts.
     *
     * @details Using the provided list of contact IDs, this function merges them into one contact. The first
     * contact in the provided list remains, while the rest of the contacts are deleted. The appropriate signals
     * are emitted for each contact that's affected by this function (for example, @c contactsChanged() for the
     * contact that's changed, @c contactsDeleted() for the contacts that are deleted).
     *
     * @param contactIds The list of contact IDs whose contacts should be merged.
     *
     * @since BlackBerry 10.0.0
     */
    void mergeContacts(const QList<ContactId> &contactIds) const;

    /*!
     * @brief Unmerges the provided unified contact.
     *
     * @details This function results in two contacts. The list of AccountId/ContactId pairs are sub-contacts of the
     * provided unified contact and will be extracted and make up one new unified contact. What's left over will
     * remain as part of the original unified contact.
     *
     * @param contactId The contact ID of the contact to unmerge.
     * @param idPairs A list of AccountId/ContactId pairs of the sub-contacts that make up the unified contact. These
     * will result in one merged contact.
     *
     * @since BlackBerry 10.0.0
     */
    void unmergeContacts(ContactId contactId, const QList<QPair<AccountId, ContactId> > &idPairs) const;

    /*!
     * @brief Retrieves detailed contact information for a contact.
     *
     * @details This function is a more flexible version of @c contactDetails(), in which you can provide an account
     * ID to retrieve an original contact. This function is designed to be used with @c mergeContacts() and
     * @c unmergeContacts() to ensure that the contact about to be unmerged is the correct one.
     *
     * @param accountId The account ID of the contact whose details should be retrieved.
     * @param contactId The contact ID of the contact whose details should be retrieved.
     *
     * @return The contact (including full details) with the provided account ID and contact ID.
     *
     * @since BlackBerry 10.0.0
     */
    Contact contactDetails(AccountId accountId, ContactId contactId) const;

    /*!
     * @brief Sets the primary photo of the provided contact using a photo ID.
     *
     * @details This function persists the setting of a primary photo to the database. The photo ID must be one
     * belonging to the contact.
     *
     * @param contactId The contact ID of the contact whose primary photo should be set.
     * @param photoId The photo ID of the photo to set as the primary photo for the contact.
     *
     * @return @c true if the primary photo was set successfully, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool setPrimaryPhoto(ContactId contactId, int photoId) const;

    /*!
     * @brief Sets the primary photo of the provided contact using a file path.
     *
     * @details This function lets you save a new contact photo to the contact, and makes it the primary photo.
     * Another way of achieving this is to add a @c ContactPhoto object to the @c Contact and either create a new
     * contact or update that same contact. This function is just a faster way of achieving the same result if all
     * that is required is adding a new photo.
     *
     * @param contactId The contact ID of the contact whose primary photo should be set.
     * @param filepath The file path of the photo to set as the primary photo for the contact.
     *
     * @since BlackBerry 10.0.0
     */
    void setPrimaryPhoto(ContactId contactId, const QString &filepath) const;

    /*!
     * @brief Saves contacts to the SIM card.
     *
     * @details This function saves the list of personal unified contacts to the SIM card. It's possible that not
     * all contacts can be stored on the SIM card, because space on the SIM card is limited.
     *
     * @return The number of contacts that were saved to the SIM card.
     *
     * @since BlackBerry 10.0.0
     */
    int saveContactsToSimCard() const;

    /*!
     * @brief Imports contacts from the SIM card into local storage.
     *
     * @details This function imports the contacts from the SIM card to the local contacts database. This function
     * doesn't check for duplicate contacts.
     *
     * @return The number of contacts that were imported from the SIM card into local storage.
     *
     * @since BlackBerry 10.0.0
     */
    int importContactsFromSimCard() const;

    /*!
     * @brief Deletes contact data that is sourced from the SIM card.
     *
     * @details Using the provided contact ID, this function deletes the data of that contact that was sourced from
     * the SIM card. If the entire contact is composed of SIM card data, then the entire contact is deleted. If the
     * contact only includes some data that was sourced from the SIM card, only the SIM card data is removed.
     *
     * @param contactId The contact ID of the contact whose SIM card data should be removed.
     *
     * @since BlackBerry 10.0.0
     */
    void deleteSimContact(ContactId contactId) const;

    /*!
     * @brief Adds the provided contact to the SIM card.
     *
     * @details This contact is merged automatically with the existing contacts, if possible. Otherwise, it will
     * appear as a new contact in the contacts list.
     *
     * It's possible that there's no SIM card inserted in the device, or that the SIM card is full, so this function
     * may or may not succeed. To determine if the function is successful, you can check the signals that are emitted:
     * @c contactsAdded() if a contact was added, or @c contactsUpdated() if a contact was merged.
     *
     * @param contact The contact to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addContactToSim(const Contact &contact) const;

    /*!
     * @brief Retrieve a contact group.
     *
     * @param groupId The ID of the group.
     *
     * @return The contact group.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroup contactGroup(GroupId groupId) const;

    /*!
     * @brief Retrieve the size of a contact group.
     *
     * @param groupId The ID of the group.
     *
     * @return The number of members in the contact group.
     *
     * @since BlackBerry 10.3.0
     */
    int contactGroupSize(GroupId groupId) const;

    /*!
     * @brief Creates a new contact group.
     *
     * @details You should use a @c ContactGroupBuilder to create the new @c ContactGroup
     *
     * @param group The new group to be created.
     * @return The contact group that was created.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroup createContactGroup(const ContactGroup &group) const;

    /*!
     * @brief Add a contact to a group.
     *
     * @param contactId The ID of the contact to add to the group.
     * @param groupId The ID of the group to which the contact is to be added.
     *
     * @return @c True if the addition is successful.
     *
     * @since BlackBerry 10.3.0
     */
    bool addContactToGroup(ContactId contactId, GroupId groupId) const;

    /*!
     * @brief Add a contact to a group using a @c GroupMembershipSpecifier.
     *
     * @param membershipSpecifier The @c %GroupMembershipSpecifier that specifies the
     * attributes to be used with this group.
     * @param groupId The ID of the group to which the contact is to be added.
     *
     * @return @c True if the addition is successful, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool addContactToGroup(GroupMembershipSpecifier membershipSpecifier, GroupId groupId) const;

    /*!
     * @brief Add contacts to a group.
     *
     * @param contactIds The IDs of the contacts to add to the group.
     * @param groupId The ID of the group to which the contacts are to be added.
     *
     * @return @c True if the addition is successful, @c false otherwise.
     * @since BlackBerry 10.3.0
     */
    bool addContactsToGroup(QList<ContactId> contactIds, GroupId groupId) const;

    /*!
     * @brief Add contacts to a group using a @c GroupMembershipSpecifier.
     *
     * @param membershipSpecifier The @c %GroupMembershipSpecifier that specifies the
     * attributes to be used with this group.
     * @param groupId The ID of the group to which the contacts are to be added.
     *
     * @return @c True if the addition is successful, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool addContactsToGroup(QList<GroupMembershipSpecifier> membershipSpecifier, GroupId groupId) const;

    /*!
     * @brief Remove a contact from a group.
     *
     * @param contactId The ID of the contact to remove from the group.
     * @param groupId The ID of the group from which the contact is to be removed.
     *
     * @return @c True if the removal is successful, , @c false otherwise
     *
     * @since BlackBerry 10.3.0
     */
    bool removeContactFromGroup(ContactId contactId, GroupId groupId) const;

    /*!
     * @brief Delete a contact group.
     *
     * @param groupId The ID of the group to delete.
     *
     * @since BlackBerry 10.3.0
     */
    void deleteContactGroup(GroupId groupId) const;

    /*!
     * @brief Update a contact group and its membership.
     *
     * @details This function is used to update a contact group, add contacts to the group, remove contacts
     * from the group, and update membership attributes for contacts in the group.
     *
     * @param updatedGroup The group to be updated.
     * @param removeContacts The IDs of the contacts to remove from the group.
     * @param addContacts The IDs of the contacts to add to the group.
     * @param updateMemberships The updated @c GroupMembershipSpecifier objects
     * that define the attributes to use for each contact in the group.
     *
     * @return The updated contact group.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroup updateContactGroup(const ContactGroup& updatedGroup, const QList<ContactId> removeContacts, const QList<ContactId> addContacts, const QList<GroupMembershipSpecifier> updateMemberships) const;

    /*!
     * @brief Update group membership for contacts in the group.
     *
     * @param groupMemberships The updated memberships for contacts in the group.
     * @param groupId the ID of the group to update.
     *
     * @return @c True if the update is successful, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool updateGroupMembership(QList<GroupMembershipSpecifier> groupMemberships, GroupId groupId) const;

    /*!
     * @brief Retrieve the IDs of contacts that are members of the specified group.
     *
     * @param groupId The group's ID.
     *
     * @return The IDs of the contacts that are members of the group.
     *
     * @since BlackBerry 10.3.0
     */
    QList<ContactId> contactsInGroup(GroupId groupId) const;

    /*!
     * @brief Retrieve membership details for all contacts in the group.
     *
     * @see GroupMembershipSpecifier
     *
     * @param groupId The group's ID.
     *
     * @return A list of all membership details for all contacts in the group.
     *
     * @since BlackBerry 10.3.0
     */
    QList<GroupMembershipSpecifier> groupMembershipDetails(GroupId groupId);

    /*!
     * @brief return membership details for a contact in a group.
     *
     * @see GroupMembershipSpecifier
     *
     * @param groupId the group's id.
     * @return contactId the contact's id.
     *
     * @since BlackBerry 10.3.0
     */
    GroupMembershipSpecifier groupMembershipDetails(GroupId groupId, ContactId contactId);

    /*!
     * @brief Retrieve the attributes used to communicate with a group.
     *
     * @details Attributes are associated with a group using @c GroupMembershipSpecifier.
     * This specifies the @c ContactAttribute to use for each group member when
     * communicating with a group.
     *
     * @see groupMembershipDetails(), updateGroupMembership()
     *
     * @param groupId The group's ID.
     *
     * @since BlackBerry 10.3.0
     */
    QList<ContactAttribute> groupAttributes(GroupId groupId) const;

    /*!
     * @brief Retrieve groups in which a contact is a member.
     *
     * @param contactId The contact's ID.
     *
     * @return The groups for which a contact is a member
     *
     * @since BlackBerry 10.3.0
     */
    QList<ContactGroup> groupsForContact(ContactId contactId) const;

    /*!
     * @brief Retrieve all contact groups.
     *
     * @return All contact groups.
     *
     * @since BlackBerry 10.3.0
     */
    QList<ContactGroup> groups() const;

    /*!
     * @brief Retrieve the number of all contact groups.
     *
     * @return The number of all contact groups.
     *
     * @since BlackBerry 10.3.0
     */
    int groupCount() const;

    /*!
     * @brief Retrieves the current perimeter status.
     *
     * @details The perimeter status can be Inactive, Locked, Unlocked
     *
     * @return The current perimeter status.
     *
     * @since BlackBerry 10.0.0
     */
    PerimeterStatus::Type perimeterStatus() const;

    /*!
     * @brief Retrieves the number of contacts that are considered enterprise contacts.
     *
     * @return The number of contacts that are considered enterprise contacts.
     *
     * @since BlackBerry 10.0.0
     */
    int enterpriseContactCount() const;

    /*!
     * @brief Retrieves a partial contact based on the provided contact ID and contact list filter.
     *
     * @details If a @c Contact is found that matches the provided contact ID and contact list filters, that
     * @c %Contact is returned. If no such @c %Contact is found, an empty @c %Contact with an ID of 0 is
     * returned.
     *
     * @param contactId The contact ID of the contact to retrieve.
     * @param filters The contact list filters to apply to the returned contact.
     *
     * @return A contact that matches the provided contact ID and criteria in the provided contact list filter.
     *
     * @since BlackBerry 10.0.0
     */
     Contact filteredContact(ContactId contactId, const ContactListFilters &filters) const;

     /*!
      * @brief Converts a contact to a vCard stream.
      *
      * @details If a valid contact ID is provided, a vCard stream (version 3.0) is created. If a parsing error
      * occurs, an empty stream is returned.
      *
      * @param contactId The contact ID of the contact to convert.
      *
      * @return A vCard stream that corresponds to the provided contact.
      *
      * @since BlackBerry 10.0.0
      */
     QByteArray contactToVCard(ContactId contactId) const;

     /*!
      * @brief Converts a contact to a vCard stream.
      *
      * @details If a valid contact ID is provided, a vCard stream (version 3.0) is created. If a parsing error
      * occurs, an empty stream is returned.
      *
      * @param contactId The contact ID of the contact to convert.
      * @param photoEncoding The vCard photo encoding type.
      * @param sizeLimit The vCard size limit.
      *
      * @return A vCard stream that corresponds to the provided contact.
      *
      * @since BlackBerry 10.0.0
      */
     QByteArray contactToVCard(ContactId contactId, VCardPhotoEncoding::Type photoEncoding, int sizeLimit) const;

     /*!
      * @brief Converts a contact to a vCard stream.
      *
      * @details If a valid contact is provided, a vCard stream (version 3.0) is created. If a parsing error
      * occurs, an empty stream is returned. Note that if @c contact is a partial contact, the resultant vCard
      * stream only contains partial contact data.
      *
      * @param contact The contact to convert.
      *
      * @return A vCard stream that corresponds to the provided contact.
      *
      * @since BlackBerry 10.2.0
      */
     QByteArray contactToVCard(const Contact &contact) const;

     /*!
      * @brief Converts a contact to a vCard stream.
      *
      * @details If a valid contact is provided, a vCard stream (version 3.0) is created. If a parsing error
      * occurs, an empty stream is returned. Note that if @c contact is a partial contact, the resultant vCard
      * stream only contains partial contact data.
      *
      * @param contact The contact to convert.
      * @param photoEncoding The vCard photo encoding type.
      * @param sizeLimit The vCard size limit.
      *
      * @return A vCard stream that corresponds to the provided contact.
      *
      * @since BlackBerry 10.2.0
      */
     QByteArray contactToVCard(const Contact &contact, VCardPhotoEncoding::Type photoEncoding, int sizeLimit) const;

     /*!
      * @brief Converts a vCard stream to a contact.
      *
      * @details This function converts a vCard stream into a @c Contact. If a parsing error occurs, the returned
      * @c %Contact is empty (you can verify this by using @c Contact::isValid()). To save the contact to the
      * database, you can use @c createContact().
      *
      * @param vCardData The vCard stream to convert.
      *
      * @return A contact that corresponds to the provided vCard stream.
      *
      * @since BlackBerry 10.0.0
      */
     Contact contactFromVCard(const QString &vCardData) const;

     /*!
      * @brief Converts contacts to a vCards stream.
      *
      * @details If a valid list of contact IDs is provided, a vCards stream (version 3.0) is created. If parsing error
      * occurs, an empty stream is returned.
      *
      * @param contactIds The list of contact IDs whose contacts to convert.
      * @param photoEncoding The vCard photo encoding type.
      *
      * @return A vCards stream that corresponds to the provided contacts.
      *
      * @since BlackBerry 10.1.0
      */
     QByteArray exportContactVCards(const QList<ContactId> &contactIds, VCardPhotoEncoding::Type photoEncoding) const;

     /*!
      * @brief Import a vCards stream to local contacts.
      *
      * @details This function imports a vCards stream into local contacts. If a parsing error occurs on one of the vCards,
      * the vCard will not be saved to local contacts.
      * @param vCardsData The vCards stream.
      *
      * @return @c True if the vCards were imported successfully, @c false otherwise.
      *
      * @since BlackBerry 10.1.0
      */
     bool importContactVCards(const QString &vCardsData) const;

     /*!
      * @brief Initiates contact synchronization.
      *
      * @details This function initiates contact synchronization for a selected @c accountId.
      * Note that most accounts do not require explicit synchronization. This API currently only
      * supports AT&T Address Book accounts.
      *
      * @param accountId The ID of the account to sync.
      *
      * @return @c true if the synchronization was successful, @c false otherwise.
      *
      * @since BlackBerry 10.2.0
      */
     bool syncContacts(bb::pim::account::AccountKey accountId) const;

     /*!
      * @brief Retrieves a list of contact folders in the provided account.
      *
      * @param accountId The account ID to retrieve the contact folders from.
      *
      * @return A @c QList of contact folders in the provided account.
      *
      * @since BlackBerry 10.3.1
      */
     QList<bb::pim::contacts::ContactFolder> folders(AccountId accountId) const;

     /*!
      * @brief Enables synchronization for a set of contact folders.
      *
      * @param accountId The account ID of an account (for example, the account ID of an existing email account).
      * @param syncConfigPairs A list of ContactFolderKey/bool pairs containing the contact folder ID and a boolean
      * value representing whether sync is to be turned on or off for that folder.
      *
      * @return @c true if synchronization configuration was set successfully, @c false otherwise.
      *
      * @since BlackBerry 10.3.1
      */
      bool setContactFolderSyncConfig(AccountId accountId, const QList<QPair<bb::pim::contacts::ContactFolderKey, bool> > &syncConfigPairs);

Q_SIGNALS:
    /*!
     * @brief Emitted when new contacts are added.
     *
     * @param contactIds The list of contact IDs that were added.
     *
     * @since BlackBerry 10.0.0
     */
    void contactsAdded(QList<int> contactIds);

    /*!
     * @brief Emitted when contacts are deleted.
     *
     * @details When individual contacts are deleted, this signal is emitted. When an entire account is removed from
     * the system, the @c contactsReset() signal is emitted instead, in which case any cached contacts should be dropped.
     *
     * @param contactIds The list of contact IDs that were deleted.
     *
     * @since BlackBerry 10.0.0
     */
    void contactsDeleted(QList<int> contactIds);

    /*!
     * @brief Emitted when one or more contacts are changed.
     *
     * @details When contacts have been merged or changed, this signal is emitted.
     *
     * @param contactIds The list of contact IDs that were changed.
     *
     * @since BlackBerry 10.0.0
     */
    void contactsChanged(QList<int> contactIds);

    /*!
     * @brief Emitted when a contact's favorite status changes.
     *
     * @param contactId The ID of the contact whose favorite status changed.
     * @param favourited @c true if the contact is favorited, @c false if the contact is unfavorited.
     *
     * @see setFavouriteContact
     *
     * @since BlackBerry 10.2.0
     */
    void contactFavourited(int contactId, bool favourited);

    /*!
     * @brief Emitted when contact synchronization has been completed.
     *
     * @details This signal is used in a scenario where lazy loading is preferred.
     *
     * @since BlackBerry 10.0.0
     */
    void contactSyncCompleted();

    /*!
     * @brief Emitted when the current list of contacts has significantly changed.
     *
     * @details This signal is emitted when something significant has happened to the contacts database. For example,
     * a source account that has been deleted will trigger this signal. It is expected that all cached copies
     * of the contacts list will be flushed and retrieved again when this happens.
     *
     * @since BlackBerry 10.0.0
     */
    void contactsReset();

    /*!
     * @brief Emitted when a suggested contact is found.
     *
     * @details This signal is emitted when a suggested contact is found based on
     * previous patterns. It is recommended to present a dialog to the user
     * to ask whether a new contact should be made and to use the data to populate
     * a contact edit screen.
     *
     * @param data The attributes of the contact.
     *
     * @since BlackBerry 10.2.0
     */
    void contactNewSuggested(const QMap<QString, QVariant> data);

    /*!
     * @brief Emitted when the data for one or more contacts has changed.
     *
     * @details This signal is emitted when the data for one or more contacts
     * has changed.
     *
     * @param changeTimeStamp The date and time when the contact or contacts changed specified in UTC.
     *
     * @since BlackBerry 10.2.0
     */
    void contactsDataChanged(QDateTime changeTimeStamp);

    /*!
     * @brief Emitted when a contact group is added.
     *
     * @param groupId The new contact group's ID.
     *
     * @since BlackBerry 10.3.0
     */
    void contactGroupAdded(int groupId);

    /*!
     * @brief Emitted when a contact group is changed.
     *
     * @param updatedGroup The updated contact group.
     * @param contactsAdded The IDs of each @c Contact added to the group.
     * @param contactsUpdated The IDs of each @c Contact updated in the group.
     * @param contactsRemoved The IDs of each @c Contact removed from the group.
     *
     * @since BlackBerry 10.3.0
     */
    void contactGroupChanged(const bb::pim::contacts::ContactGroup &updatedGroup, QList<int> contactsAdded, QList<int> contactsUpdated, QList<int> contactsRemoved);

    /*!
     * @brief Emitted when a contact group is deleted.
     *
     * @param groupId The ID of the deleted contact group.
     *
     * @since BlackBerry 10.3.0
     */
    void contactGroupDeleted(int groupId);
private:
    //ContactServicePrivate* d_ptr;
    Q_DISABLE_COPY(ContactService)
    Q_DECLARE_PRIVATE(ContactService)
    QScopedPointer<ContactServicePrivate> d_ptr;
};

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTSERVICE_HPP
