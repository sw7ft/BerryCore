/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CONTACTS_CONTACTSEARCHFILTERS_HPP
#define BB_PIM_CONTACTS_CONTACTSEARCHFILTERS_HPP

#include <bb/pim/Global>
#include <bb/pim/contacts/ContactConsts>
#include <QSharedDataPointer>
#include <QString>
#include <QList>
#include <QSet>
#include <QVariantList>

namespace bb {
namespace pim {
namespace contacts {

class ContactSearchFiltersPrivate;


/*!
 * @brief The @c ContactSearchFilters class represents a set of filters that are used to search for specific contacts.
 *
 * @details You can use this class to search for @c Contact objects. This class is designed to work with the various
 * search functions in @c ContactService, such as @c ContactService::searchContacts(),
 * @c ContactService::searchContactsByPhoneNumber(), and so on. You can specify search parameters such as sub-kind,
 * attribute, and specific search fields, and you can sort the search results in different ways (for example, by
 * column values, ascending, descending, and so on).
 *
 * @see ContactService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactSearchFilters
{
public:
    /*!
     * @brief Constructs a new @c ContactSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters();

    /*!
     * @brief Destroys this @c ContactSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactSearchFilters();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactSearchFilters containing exactly the same values as the
     * provided @c %ContactSearchFilters.
     *
     * @param copy The @c %ContactSearchFilters to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters(const ContactSearchFilters &copy);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactSearchFilters into this
     * @c %ContactSearchFilters.
     *
     * @param operand The @c %ContactSearchFilters from which to copy all values.
     *
     * @return A @c %ContactSearchFilters with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& operator=(const ContactSearchFilters &operand);

    /*!
     * @brief Sets the result limit of this @c ContactSearchFilters.
     *
     * @details This value represents the maximum number of results that are returned from the search.
     *
     * @param limit The maximum number of results that are returned.
     *
     * @return A @c %ContactSearchFilters with the provided result limit.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setLimit(int limit);

    /*!
     * @brief Set offset to start query of this @c ContactListFilters
     *
     * @ details This value represents the place to start query from
     *
     * @param offset The offset number to start searching from
     *
     * @return A @c %ContactListFilters with the provided offset
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setOffset(int offset);

    /*!
     * @brief Filters the search results to contain only contacts with the provided kind/sub-kind combination.
     *
     * @param present The kind/sub-kind combination to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided kind/sub-kind combination filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setHasKindSubkind(const KindSubKindSpecifier present);

    /*!
     * @brief Filters the search results to contain only contacts with the provided set of kind/sub-kind
     * combinations.
     *
     * @param present The set of kind/sub-kind combinations to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided kind/sub-kind combination filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setHasKindSubkind(const QSet<KindSubKindSpecifier> &present);

    /*!
     * @brief Sets whether only favorite contacts are returned when using this @c ContactSearchFilters.
     *
     * @param value If @c true only favorite contacts are returned, if @c false all contacts are returned.
     *
     * @return A @c ContactSearchFilters with the provided indication of whether favorite contacts are returned.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setIsFavourite(bool value);

    /*!
     * @brief Indicates whether only video chat contacts are returned when using this @c ContactListFilters.
     *
     * @return @c true if only video chat contacts are returned, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isVideoChatContact() const;

    /*!
     * @brief Sets whether only video chat contacts are returned when using this @c ContactListFilters.
     *
     * @param isVideoChatContact If @c true only video chat contacts are returned, if @c false all contacts are returned.
     *
     * @return A @c ContactListFilters with the provided indication of whether video chat contacts are returned.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setIsVideoChatContact(bool isVideoChatContact);

    /*!
     * @brief Filters the search results to contain only contacts with the provided attribute kind.
     *
     * @param present The attribute kind to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided attribute kind filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setHasAttribute(AttributeKind::Type present);

    /*!
     * @brief Filters the search results to contain only contacts with the provided set of attribute kinds.
     *
     * @param present The set of attribute kinds to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided attribute kind filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setHasAttribute(const QSet<AttributeKind::Type> &present);

    /*!
     * @brief Sets the anchor ID and indicates how paging works in the search results.
     *
     * @details This function sets the anchor ID to the provided contact ID. If paging is set to inclusive (that is,
     * the @c inclusive parameter is @c true), the contact with the specified contact ID is returned as the first
     * contact. Otherwise, the first contact that's returned is the next logical contact in the results.
     *
     * @param contactId The contact ID to set as the anchor ID.
     * @param inclusive If @c true the contact with the specified contact ID is returned as the first contact in the
     * results, if @c false the contact after the one with the specified contact ID is returned as the first contact.
     *
     * @return A @c ContactSearchFilters with the provided anchor ID and paging behavior.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setAnchorId(ContactId contactId, bool inclusive = false);

    /*!
     * @brief Sets the sort column and sort order of this @c ContactSearchFilters.
     *
     * @details The default sort column is FirstName and the default sort order is ascending.
     *
     * @param column The sort column to set.
     * @param order The sort order to set.
     *
     * @return A @c %ContactSearchFilters with the provided sort column and sort order.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSortBy(SortColumn::Type column, SortOrder::Type order);

    /*!
     * @brief Sets the sort column and sort order of this @c ContactSearchFilters using a @c SortSpecifier.
     *
     * @details The default sort column is FirstName and the default sort order is ascending.
     *
     * @param sort The sort column and sort order pair to set, represented by a @c %SortSpecifier.
     *
     * @return A @c %ContactSearchFilters with the provided sort column and sort order.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSortBy(const SortSpecifier &sort);

    /*!
     * @brief Sets the sort columns and sort orders of this @c ContactSearchFilters using a list of @c SortSpecifier
     * objects.
     *
     * @details The default sort column is FirstName and the default sort order is ascending. The search results
     * are first sorted according to the first @c %SortSpecifier in the provided list, then by the second
     * @c %SortSpecifier in the list, and so on.
     *
     * @param sorts The set of sort column and sort order pairs to set, represented by @c %SortSpecifier objects.
     *
     * @return A @c %ContactSearchFilters with the provided sort columns and sort orders.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSortBy(const QList<SortSpecifier> &sorts);

    /*!
     * @brief Sets the sort column, sort order, and anchor value of this @c ContactSearchFilters using an
     * @c AnchorValueSpecifier.
     *
     * @details This function specifies a sort column and order, and offsets the response by a certain anchor value.
     * When anchoring by value, contacts matching the values are included in the response.
     *
     * @param anchorValue The sort column, sort order, and anchor value to set, represented by a @c %AnchorValueSpecifier
     * object.
     *
     * @return A @c %ContactSearchFilters with the provided sort column, sort order, and anchor value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSortAndAnchorBy(const AnchorValueSpecifier &anchorValue);

    /*!
     * @brief Sets the sort columns, sort orders, and anchor values of this @c ContactSearchFilters using a list of
     * @c AnchorValueSpecifier objects.
     *
     * @details This function specifies a set of sort columns and orders, and offsets the response by anchor values.
     * When anchoring by value, contacts matching the values are included in the response.
     *
     * @param anchorValues The set of sort columns, sort orders, and anchor values to set, represented by
     * @c %AnchorValueSpecifier objects.
     *
     * @return A @c %ContactSearchFilters with the provided sort columns, sort orders, and anchor values.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSortAndAnchorBy(const QList<AnchorValueSpecifier> &anchorValues);

    /*!
     * @brief Filters the search results to contain only contacts where the source of the contact comes from the
     * provided account ID.
     *
     * @param accountId The account ID to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setHasAccount(AccountId accountId);

    /*!
     * @brief Filters the search results to contain only contacts where the sources of the contact come from any of
     * the provided account IDs.
     *
     * @param accountId The set of account IDs to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setHasAccounts(const QList<AccountId> &accountId);

    /*!
     * @brief Filters the search results to contain only contacts where the source of the contact doesn't come from
     * the provided account ID.
     *
     * @param accountId The account ID to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setExcludeAccount(AccountId accountId);

    /*!
     * @brief Filters the search results to contain only contacts where the sources of the contact don't come from
     * any of the provided account IDs.
     *
     * @param accountId The set of account IDs to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setExcludeAccounts(const QList<AccountId> &accountId);

    /*!
     * @brief Filters the search results to contain only contacts where the source of the contact doesn't come from
     * the provided account ID.
     *
     * @param accountId The set of account ID to filter based on.
     * @param includeMergedContacts Indicates whether contacts that belong to more than one account should be included in the result
     * if one of the source accounts is not excluded.
     *
     * @return A @c ContactSearchFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setExcludeAccount(AccountId accountId, bool includeMergedContacts);

    /*!
     * @brief Filters the search results to contain only contacts where the sources of the contact don't come from
     * any of the provided account IDs.
     *
     * @param accountId The set of account IDs to filter based on.
     * @param includeMergedContacts Indicates whether contacts that belong to more than one account should be included in the result
     * if one of the source accounts is not excluded.
     *
     * @return A @c ContactSearchFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setExcludeAccounts(const QList<AccountId> &accountId, bool includeMergedContacts);

    /*!
     * @brief Sets whether to include photos in the search results.
     *
     * @details If set to @c true, the primary photos that are associated with the contacts are returned. The default value
     * is @c false.
     *
     * @param value If @c true photos are included in the search results, if @c false photos are not included in the
     * search results.
     *
     * @return A @c ContactSearchFilters with the provided indication of whether to include photos in the search results.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setIncludePhotos(bool value);

    /*!
     * @brief Filters the search results to contain only contacts with the provided attribute kind.
     *
     * @details This function is mutually exclusive with @c setIncludeAttributes().
     *
     * @param kind The attribute kind to filter based on.
     *
     * @return A @c ContactSearchFilters with the provided attribute kind filter.
     *
     * @see setIncludeAttributes()
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setIncludeAttribute(AttributeKind::Type kind);

    /*!
     * @brief Filters the search results to contain only contacts with the provided attribute kinds.
     *
     * @details This function is mutually exclusive with @c setIncludeAttribute().
     *
     * @param kinds The set of attribute kinds to filter based on.
     *
     * @return A @c ContactSearchFilter with the provided attribute kinds filter.
     *
     * @see setIncludeAttribute()
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setIncludeAttributes(QList<AttributeKind::Type> kinds);

    /*!
     * @brief Sets the search value of this @c ContactSearchFilters.
     *
     * @details This value represents the string to search for in the list of contacts. This is a required field.
     *
     * @param value The search value to set.
     *
     * @return A @c %ContactSearchFilters with the provided search value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSearchValue(const QString &value);

    /*!
     * @brief Sets whether to include attributes in the search results.
     *
     * @details If set to @c true, attributes are returned in the search results. If set to @c true along with
     * along with @c setHasAttribute, then only the matching attributes are returned. You should use this function
     * with care, because retrieving a large amount of data in any response will be slow.
     *
     * @param value If @c true attributes are included in the search results, if @c false attributes are not included
     * in the search results.
     *
     * @return A @c ContactSearchFilters with the provided indication of whether to include attributes in the search
     * results.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setShowAttributes(bool value);

    /*!
     * @brief Sets whether to include account IDs for content sources in the search results.
     *
     * @details If set to @c true, contacts that are returned include a list of account IDs that are the sources of
     * content for the contacts.
     *
     * @param value If @c true account IDs are included in the search results, if @c false account IDs are not
     * included in the search results.
     *
     * @return A @c %ContactSearchFilters with the the provided indication of whether to include source accounts list
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setShowSources(bool value);

    /*!
     * @brief Sets the search fields of this @c ContactSearchFilters.
     *
     * @details This function sets the search fields that the search applies to. These fields are searched for the
     * value that's set using @c setSearchValue().
     *
     * The default search fields are first name, last name, company name, phone, and email.
     *
     * @param fields The search fields to set.
     *
     * @return A @c %ContactSearchFilters with the specified search fields.
     *
     * @since BlackBerry 10.0.0
     */
    ContactSearchFilters& setSearchFields(const QList<SearchField::Type> &fields);

    /*!
     * @brief Sets whether to use exact matching for search fields or not.
     *
     * @details If set to @c true, only contacts that contain an exact match on a search field are returned.
     *
     * The default search fields are: first name, last name, company name, phone, and email.
     *
     * @param value @c True if exact matching should be used, @c false otherwise.
     *
     * @return A @c %ContactSearchFilters with the specified exact match mode.
     *
     * @since BlackBerry 10.2.0
     */
    ContactSearchFilters& setExactMatch(bool value);

    /*!
     * @brief Sets whether contact groups should be included in the search results or not.
     *
     * @details If set to @c true, groups will be returned as a part of the search.
     *
     * @param value @c True if groups should be included, @c false otherwise.
     *
     * @return A @c %ContactSearchFilters with the specified groups included filter.
     *
     * @since BlackBerry 10.3.0
     */
    ContactSearchFilters& setIncludeGroups(bool value);

    /*!
     * @brief Retrieves the list of contact IDs that are excluded with this @c ContactSearchFilters.
     *
     * @return A list of contact IDs that are excluded with this @c %ContactSearchFilters.
     *
     * @since BlackBerry 10.3.0
     */
    QVariantList excludeContacts() const;

    /*!
     * @brief Sets the list of contact IDs that are excluded when using this @c ContactSearchFilters.
     *
     * @param contactIds The list of contact IDs that should be excluded.
     *
     * @return A @c %ContactSearchFilters with the provided list of contact IDs.
     *
     * @since BlackBerry 10.3.0
     */
    ContactSearchFilters& setExcludeContacts(const QList<ContactId> &contactIds);

    /*!
     * @brief This function filters the returned contact list to contain only contacts with a display picture.
     *
     * @param hasPhoto If @c true, only contacts with a display picture are included in the returned contact list. If @c false,
     * this filter does nothing.
     *
     * @return A @c ContactSearchFilters with the provided @c hasPhoto filter.
     *
     * @since BlackBerry 10.3.0
     */
    ContactSearchFilters& setHasPhoto(bool hasPhoto);

private:
    QSharedDataPointer<ContactSearchFiltersPrivate> d_ptr;
    friend class ContactSearchFiltersPrivate;
};


} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTSEARCHFILTERS_HPP
