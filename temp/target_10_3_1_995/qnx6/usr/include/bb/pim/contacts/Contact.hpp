/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACT_HPP
#define BB_PIM_CONTACTS_CONTACT_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/contacts/ContactAttribute>
#include <bb/pim/contacts/ContactPostalAddress>
#include <bb/pim/contacts/ContactPhoto>
#include <bb/pim/contacts/ContactOnlineStatus>
#include <bb/pim/contacts/ContactActivity>
#include <bb/pim/contacts/ContactNews>
#include <bb/pim/Global>
#include <QString>
#include <QExplicitlySharedDataPointer>

namespace bb {
namespace pim {
namespace contacts {


class ContactBuilder;
class ContactService;
class ContactPrivate;

/*!
 * @brief The @c Contact class represents contact data, such as name, email address, and postal address.
 *
 * @details This class represents data that's commonly associated with a contact in a contacts application. Its data
 * is mostly derived from its attributes, postal addresses, and photos. The data can be populated and retrieved from
 * existing contacts by using the @c ContactService class.
 *
 * To add new contacts, a @c ContactBuilder can be used to populate the contents of a @c %Contact, and then the
 * @c %Contact can be persisted to the database by calling @c ContactService::createContact().
 *
 * @see ContactService::createContact(), ContactBuilder
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Contact
{
public:
    /*!
     * @brief Constructs an empty @c Contact.
     *
     * @details Creating a @c %Contact using this function will result in a contact that has no data in it. You should
     * populate the data for the contact by using a @c ContactBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    Contact();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c Contact containing exactly the same values as the provided @c %Contact.
     *
     * @param contact The @c %Contact to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Contact(const Contact &contact);

    /*!
     * @brief Destroys this @c Contact.
     *
     * @since BlackBerry 10.0.0
     */
    ~Contact();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Contact into this @c %Contact.
     *
     * @param contact The @c %Contact from which to copy all values.
     *
     * @return A @c %Contact with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    Contact& operator=(const Contact &contact);

    /*!
     * @brief Retrieves the display name of this @c Contact.
     *
     * @details The display name is simply the last name of the @c %Contact appended to the first name. This value will
     * be populated only when the @c %Contact is retrieved using the @c ContactService.
     *
     * @return The display name of this @c %Contact.
     *
     * @see ContactService
     *
     * @since BlackBerry 10.0.0
     */
    QString displayName() const;

    /*!
     * @brief Retrieves the display name of this @c Contact.
     *
     * @details The display name is the last name of the @c %Contact appended to the first name. This value will
     * be populated only when the @c %Contact is retrieved using the @c ContactService.
     *
     * @param order The order of the display name.
     *
     * @return The display name of this @c %Contact.
     *
     * @see ContactService
     *
     * @since BlackBerry 10.3.0
     */
    QString displayName(NameOrder::Type order) const;

    /*!
     * @brief Retrieves the company name of this @c Contact.
     *
     * @details You might choose to display the company name along with the contact name in a list view in your
     * application. This value will be populated only when a contact is retrieved using the @c ContactService.
     *
     * @return The company name of this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QString displayCompanyName() const;

    /*!
     * @brief Retrieves the file path of a small photo for this @c Contact.
     *
     * @details You might use a small photo as a thumbnail image for the @c %Contact when displaying a list of contacts in
     * your application. An example of this value is "/accounts/1000/pimdata/contacts/1345571651/img-example-small.jpg".
     * This value will be populated only when a contact is retrieved using the @c ContactService.
     *
     * @return The file path of a small photo for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QString smallPhotoFilepath() const;

    /*!
     * @brief Indicates whether this @c Contact is a favorite.
     *
     * @details If this @c %Contact is a favorite, this function returns @c true. Favorite contacts are displayed in the
     * favorites grid in the Contacts application.
     *
     * @return @c true if this @c %Contact is a favorite, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isFavourite() const;

    /*!
     * @brief Retrieves the ID of this @c Contact.
     *
     * @details You can use this value to interact with this @c %Contact and perform different operations using the
     * @c ContactService, such as retrieving the contact details, contact list anchor, or contact search anchor, and other
     * operations. The ID is assigned automatically when the contact is added to the database using the @c ContactService,
     * and you can't change the ID after it's been assigned.
     *
     * @return The ID of this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    ContactId id() const;

    /*!
     * @brief Retrieves a list of attributes of this @c Contact that represent email addresses.
     *
     * @details This function retrieves all contact attributes for this @c %Contact where the attribute kind is
     * @c AttributeKind::Email. This is a convenience function, and is equivalent to calling
     * @c filteredAttributes(AttributeKind::Email).
     *
     * @return A list of contact attributes that represent email addresses.
     *
     * @see ContactAttributeKind, filteredAttributes()
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactAttribute> emails() const;

    /*!
     * @brief Retrieves a list of attributes of this @c Contact that represent phone numbers.
     *
     * @details This function retrieves all contact attributes for this @c %Contact where the attribute kind is
     * @c AttributeKind::Phone. This is a convenience function, and is equivalent to calling
     * @c filteredAttributes(AttributeKind::Phone).
     *
     * @return A list of contact attributes that represent phone numbers.
     *
     * @see ContactAttributeKind, filteredAttributes()
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactAttribute> phoneNumbers() const;

    /*!
     * @brief Retrieves the first name of this @c Contact.
     *
     * @details This is a convenience function, and lets you retrieve the first name of this contact directly.
     * To accomplish this another way, you can retrieve the list of attributes for the contact using @c attributes(),
     * and then search for an attribute that has a kind of @c AttributeKind::Name and a sub-kind of
     * @c AttributeSubKind::NameGiven.
     *
     * This function is available only for fully populated contacts, or contacts from list queries and search queries
     * where @c AttributeKind::Name is part of the options. For example, here's how to retrieve a list of contacts on
     * which you can call this function to retrieve the contacts' first names:
     *
     * @code
     *      ContactListOptions filters;
     *      filters.setLimit(20);
     *      filters.hasAttribute(AttributeKind::Name);
     *      QList<Contact> contactList = ContactService().contacts(filters);
     * @endcode
     *
     * @return The first name of this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QString firstName() const;

    /*!
     * @brief Retrieves the last name of this @c Contact.
     *
     * @details This is a convenience function, and lets you retrieve the last name of this contact directly.
     * To accomplish this another way, you can retrieve the list of attributes for the contact using @c attributes(),
     * and then search for an attribute that has a kind of @c AttributeKind::Name and a sub-kind of
     * @c AttributeSubKind::NameSurname.
     *
     * This function is available only for fully populated contacts, or contacts from list queries and search queries
     * where @c AttributeKind::Name is part of the options. For example, here's how to retrieve a list of contacts on
     * which you can call this function to retrieve the contacts' last names:
     *
     * @code
     *      ContactListOptions filters;
     *      filters.setLimit(20);
     *      filters.hasAttribute(AttributeKind::Name);
     *      QList<Contact> contactList = ContactService().contacts(filters);
     * @endcode
     *
     * @return The last name of this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QString lastName() const;

    /*!
     * @brief Retrieves a list of photos that are associated with this @c Contact.
     *
     * @details These photos are populated only when the full contact details are retrieved from the @c ContactService
     * using @c ContactService::contactDetails(). When you call @c ContactService::contacts() or
     * @c ContactService::searchContacts, only the primary photo is retrieved.
     *
     * @return A list of photos that are associated with this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactPhoto> photos() const;

    /*!
     * @brief Retrieves the primary photo that is associated with this @c Contact.
     *
     * @return The primary photo that is associated with this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhoto primaryPhoto() const;

    /*!
     * @brief Retrieves a list of postal addresses that are associated with this @c Contact.
     *
     * @return A list of postal addresses that are associated with this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactPostalAddress> postalAddresses() const;

    /*!
     * @brief Retrieves the list of attributes for this @c Contact.
     *
     * @details Attributes represent the properties of a @c %Contact, such as name, email address, postal address, and
     * so on. This function retrieves the list of the attributes that this @c %Contact has values for.
     *
     * @return The list of attributes for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactAttribute> attributes() const;

    /*!
     * @brief Groups the attributes for this @c Contact according to the provided attribute kind.
     *
     * @details This function returns a list of lists based on the provided attribute kind. The items in the inner
     * list are values for each of the sub-kinds of the provided attribute kind.
     *
     * For example, if you provide @c AttributeKind::Phone as the argument to this function, there are several sub-kinds
     * associated with this kind, such as @c AttributeSubKind::Work, @c AttributeSubKind::PhoneMobile,
     * @c AttributeSubKind::Home, and so on. If there are multiple values for each of these sub-kinds (that is, more
     * than one work phone number, mobile phone number, or home phone number that's associated with this contact) then
     * each inner list that's returned includes the values for one of the sub-kinds.
     *
     * @param kind The kind of attribute to group by.
     *
     * @return A list of lists that represent groupings of attributes for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
	QList<QList<ContactAttribute> > filteredAttributesByGroupKey(AttributeKind::Type kind) const;

	/*!
	 * @brief Retrieves the list of attributes for this @c Contact that are of the provided attribute kind.
     *
     * @details This function returns only the attributes of this @c %Contact that are of the provided kind, represented
     * by a value from the @c AttributeKind::Type enumeration. For example, here's how to retrieve a list of attributes
     * that have a kind of @c AttributeKind::Phone:
     *
	 * @code
	 *      Contact contact = ContactService().contactDetails(5);
	 *      QList<ContactAttribute> phoneAttributes = contact.filteredAttributes(AttributeKind::Phone);
	 * @endcode
     *
     * @param kind The kind of attribute to retrieve.
     *
     * @return A list of attributes for this @c %Contact that are of the provided kind.
	 *
	 * @since BlackBerry 10.0.0
	 */
    QList<ContactAttribute> filteredAttributes(AttributeKind::Type kind) const;

    /*!
     * @brief Retrieves the current company news for this @c Contact.
     *
     * @details This function retrieves the current company news for a particular contact. The content of the news
     * will be relevant to the contact from its attributes.
     *
     * @param count <description needed here>
     *
     * @return A list of news articles for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactNews> news(int count) const;

    /*!
     * @brief Retrieves a list of contact statuses for this @c Contact.
     *
     * @details This function retrieves the online status of a contact. Each status will be from a different source. For
     * example, if the contact is retrieved from a social networking application, such as BlackBerry Messenger, you can
     * use this function to determine if the contact is online.
     *
     * @return A list of contact statuses for this @c %Contact.
     *
     * @see ContactService::onlineStatus()
     *
     * @since BlackBerry 10.0.0
     */
    QList<ContactOnlineStatus> onlineStatus() const;

    /*!
     * @brief Retrieves the account ID of this @c Contact.
     *
     * @details The account ID determines which account this @c %Contact belongs to.
     *
     * @return The account ID of this @c %Contact.
     *
     * @see bb::pim::account::AccountService
     *
     * @since BlackBerry 10.0.0
     */
    AccountId accountId() const;

    /*!
     * @brief Retrieves the number of account sources for this @c Contact.
     *
     * @details Contacts can be merged from multiple accounts to form a single contact. For example, contacts might be
     * merged from a personal account and a work account. If the same contact exists in both accounts, the contact
     * information is merged into a single contact that includes all of the information from both accounts. For this
     * merged contact, this function would return 2, because the contact information is sourced from 2 accounts.
     *
     * @return The number of account sources for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    int sourceAccountCount() const;

    /*!
     * @brief Retrieves a list of the account IDs of the sources for this @c Contact.
     *
     * @details Contacts can be merged from multiple accounts to form a single contact. For example, contacts might be
     * merged from a personal account and a work account. If the same contact exists in both accounts, the contact
     * information is merged into a single contact that includes all of the information from both accounts. This
     * function returns all of the account IDs that are sources for this contact.
     *
     * @return A list of the account IDs of the sources for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AccountId> sourceAccountIds() const;

    /*!
     * @brief Retrieves the value that's used for sorting by first name.
     *
     * @details The contacts database maintains first name data for sorting purposes. This data might not be the same
     * as the actual first name for the contact. For example, if the contact has only a last name, then the last name
     * is included in the first name sorting data as well. By using this data for sorting purposes, contacts without
     * a first name can be sorted properly when sorting by both first name and last name.
     *
     * @return The value that's used for sorting by first name.
     *
     * @since BlackBerry 10.0.0
     */
    QString sortFirstName() const;

    /*!
     * @brief Retrieves the value that's used for sorting by last name.
     *
     * @details The contacts database maintains last name data for sorting purposes. This data might not be the same
     * as the actual last name for the contact. For example, if the contact has only a first name, then the first name
     * is included in the last name sorting data as well. By using this data for sorting purposes, contacts without
     * a last name can be sorted properly when sorting by both first name and last name.
     *
     * @return The value that's used for sorting by last name.
     *
     * @since BlackBerry 10.0.0
     */
    QString sortLastName() const;

    /*!
     * @brief Retrieves the value that's used for sorting by company name.
     *
     * @details The contacts database maintains company name data for sorting purposes. This data might not be the same
     * as the actual company name for the contact. For example, if the contact has only a last name, then the last name
     * is included in the company name sorting data as well. By using this data for sorting purposes, contacts without
     * a company name can be sorted properly when sorting by both last name and company name.
     *
     * @return The value that's used for sorting by company name.
     *
     * @since BlackBerry 10.0.0
     */
    QString sortCompanyName() const;

    /*!
     * @brief Retrieves the activity stream that's shared between you and this @c Contact.
     *
     * @details An activity is an event that involves a contact. For example, an activity could be receiving an email
     * or phone call from a contact.
     *
     * @return A list of activities that are shared between you and this @c %Contact.
     *
     * @see ContactService::activities()
     *
     * @since BlackBerry 10.0.0
     */
    ContactActivityList activities() const;

    /*!
     * @brief Indicates whether this @c Contact is valid.
     *
     * @details Contacts without attributes, postal addresses, or photos are considered invalid. You should
     * use this function to determine if a @c %Contact is valid before you use it.
     *
     * @return @c true if this @c %Contact is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Indicates whether this @c Contact is a partial contact.
     *
     * @details For performance reasons, @c %Contact objects that are returned from @c ContactService may sometimes
     * be partial contacts, and won't contain all of the information for the contact. @c %Contact objects that you
     * retrieve by calling @c ContactService::contactDetails() will be full contacts, and @c %Contact objects that
     * you retrieve using other functions in @c ContactService will be partial contacts.
     *
     * @return @c true if this @c %Contact is a partial contact, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPartialContact() const;

    /*!
     * @brief Indicates whether this @c Contact is a read-only contact.
     *
     * @details You can't change the attributes of a read-only contact.
     *
     * @return @c true if this @c %Contact is read-only, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isReadOnly() const;

    /*!
     * @brief Indicates whether this @c Contact is a shadow contact.
     *
     * @details You can't unlink a shadow contact.
     *
     * @return @c true if this @c %Contact is a shadow contact, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isShadowContact() const;

    /*!
     * @brief Retrieves the type of @c Contact.
     *
     * @details @c Contact objects returned by the @c ContactService can be of multiple types.
     * For example, a @c %Contact can be a @c ContactGroup.
     *
     * @return The @c ContactType.
     *
     * @since BlackBerry 10.3.0
     */
    ContactType::Type type() const;

    /*!
     * @brief Retrieves the date when this @c Contact was last updated.
     *
     * @return The date when this @c Contact was last updated.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime lastModified() const;

    /*!
     * @brief Retrieves the possible alternate labels and sub-kinds of the provided attribute kind.
     *
     * @details This function returns a list of label/sub-kind pairs that can be used for this @c Contact, based on the
     * provided kind, that are different than any existing sub-kinds. For example, consider a contact that has a work
     * phone number, specified by the @c AttributeKind::Phone kind and @c AttributeSubKind::Work sub-kind. If you
     * provide @c %AttributeKind::Phone as the @c kind argument, this function will return other possible sub-kinds and
     * their associated labels, such as @c AttributeSubKind::Work with a label of "Work 2" (because there's already
     * a work phone number for the contact), @c AttributeSubKind::Home with a label of "Home", and so on.
     *
     * @param kind The attribute kind to retrieve the sub-kinds of.
     * @param selectedIndex The index to select.
     *
     * @return A list of pairs that represent possible alternate labels and sub-kinds for this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QPair<QString, AttributeSubKind::Type> > possibleSubKinds(AttributeKind::Type kind, int &selectedIndex) const;

    /*!
     * @brief Edits the contents of this @c Contact.
     *
     * @details This function returns a @c ContactBuilder that you can use to change the values of this @c %Contact.
     *
     * @return A @c %ContactBuilder that you can use to change the values of this @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder edit();

private:
    QExplicitlySharedDataPointer<ContactPrivate> d_ptr;
    friend class ContactPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACT_HPP
