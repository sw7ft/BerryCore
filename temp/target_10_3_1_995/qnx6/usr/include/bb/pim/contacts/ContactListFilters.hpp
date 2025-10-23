/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CONTACTS_CONTACTLISTFILTERS_HPP
#define BB_PIM_CONTACTS_CONTACTLISTFILTERS_HPP

#include <bb/pim/Global>
#include <bb/pim/contacts/ContactConsts>
#include <QSharedDataPointer>
#include <QString>
#include <QSet>
#include <QList>
#include <QVariantList>

namespace bb {
namespace pim {
namespace contacts {

class ContactListFiltersPrivate;

/*!
 * @brief The @c ContactListFilters class represents a set of filters that are used for listing and sorting contacts.
 *
 * @details You can use this class to list and sort @c Contact objects. This class is designed to work with
 * @c ContactService::contacts() to specify the number, type, and sorting of the contacts that are returned.
 *
 * @see ContactService::contacts()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactListFilters
{
public:
    /*!
     * @brief Constructs a new @c ContactListFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactListFilters containing exactly the same values as the
     * provided @c %ContactListFilters.
     *
     * @param copy The @c %ContactListFilters to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters(const ContactListFilters& copy);

    /*!
     * @brief Destroys this @c ContactListFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactListFilters();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactListFilters into this @c %ContactListFilters.
     *
     * @param operand The @c %ContactListFilters from which to copy all values.
     *
     * @return A @c %ContactListFilters with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& operator=(const ContactListFilters& operand);

    /*!
     * @brief Retrieves the list of contact IDs that are associated with this @c ContactListFilters.
     *
     * @return A list of contact IDs that are associated with this @c %ContactListFilters.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantList contactIds() const;

    /*!
     * @brief Retrieves the result limit of this @c ContactListFilters.
     *
     * @details This value represents the maximum number of results that are returned for the contact list.
     *
     * @return The result limit of this @c %ContactListFilters.
     *
     * @since BlackBerry 10.0.0
     */
    int limit() const;

    /*!
     * @brief Retrieves the anchor ID of this @c ContactListFilters.
     *
     * @details This function returns the anchor ID of the contact for the list of contacts that you receive by
     * calling @c ContactService::contacts().
     *
     * @return The anchor ID of this @c %ContactListFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ContactId anchorId() const;

    /*!
     * @brief retrieve the offset of this @c ContactListFilters
     *
     * @details This value represent the place to start query from
     *
     * @return The offset of this @c %ContactListFilters
     *
     * @since BlackBerry 10.0.0
     */
    int offset() const;

    /*!
     * @brief Indicates whether only favorite contacts are returned when using this @c ContactListFilters.
     *
     * @return @c true if only favorite contacts are returned, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isFavourite() const;

    /*!
     * @brief Indicates whether only video chat contacts are returned when using this @c ContactListFilters.
     *
     * @return @c true if only video chat contacts are returned, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isVideoChatContact() const;

    /*!
     * @brief Sets the list of contact IDs that are returned when using this @c ContactListFilters.
     *
     * @param contactIds The list of contact IDs that should be returned.
     *
     * @return A @c %ContactListFilters with the provided list of contact IDs.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setContactIds(QList<int>& contactIds);

    /*!
     * @brief Sets the result limit of this @c ContactListFilters.
     *
     * @details This value represents the maximum number of results that are returned for the contact list. The default
     * value is 20 results. If you specify 0, it will return all results. For reasonable performance specify limit as 100 or 200.
     *
     * @param limit The maximum number of results that are returned.
     *
     * @return A @c %ContactListFilters with the provided result limit.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setLimit(int limit);

    /*!
     * @brief Filters the returned contact list to contain only contacts with the provided kind/sub-kind combination.
     *
     * @param present The kind/sub-kind combination to filter based on.
     *
     * @return A @c ContactListFilters with the provided kind/sub-kind combination filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setHasKindSubkind(const KindSubKindSpecifier present);

    /*!
     * @brief Filters the returned contact list to contain only contacts with the provided set of kind/sub-kind
     * combinations.
     *
     * @param present The set of kind/sub-kind combinations to filter based on.
     *
     * @return A @c ContactListFilters with the provided kind/sub-kind combination filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setHasKindSubkind(const QSet<KindSubKindSpecifier> &present);

    /*!
     * @brief Sets whether only favorite contacts are returned when using this @c ContactListFilters.
     *
     * @param isFavourite If @c true only favorite contacts are returned, if @c false all contacts are returned.
     *
     * @return A @c ContactListFilters with the provided indication of whether favorite contacts are returned.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setIsFavourite(bool isFavourite);

    /*!
     * @brief Sets whether only video chat contacts are returned when using this @c ContactListFilters.
     *
     * @param isVideoChatContact If @c true only video chat contacts are returned, if @c false all contacts are returned.
     *
     * @return A @c ContactListFilters with the provided indication of whether video chat contacts are returned.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setIsVideoChatContact(bool isVideoChatContact);

    /*!
     * @brief Filters the returned contact list to contain only contacts with the provided attribute kind.
     *
     * @param present The attribute kind to filter based on.
     *
     * @return A @c ContactListFilters with the provided attribute kind filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setHasAttribute(AttributeKind::Type present);

    /*!
     * @brief Filters the returned contact list to contain only contacts with the provided set of attribute kinds.
     *
     * @param present The set of attribute kinds to filter based on.
     *
     * @return A @c ContactListFilters with the provided attribute kind filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setHasAttribute(const QSet<AttributeKind::Type> &present);

    /*!
     * @brief Sets the anchor ID and indicates how paging works in the returned contact list.
     *
     * @details This function sets the anchor ID to the provided contact ID. If paging is set to inclusive (that is,
     * the @c inclusive parameter is @c true), the contact with the specified contact ID is returned as the first
     * contact. Otherwise, the first contact that's returned is the next logical contact in the list.
     *
     * @param contactId The contact ID to set as the anchor ID.
     * @param inclusive If @c true the contact with the specified contact ID is returned as the first contact in the
     * list, if @c false the contact after the one with the specified contact ID is returned as the first contact.
     *
     * @return A @c ContactListFilters with the provided anchor ID and paging behavior.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setAnchorId(ContactId contactId, bool inclusive = false);

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
    ContactListFilters& setOffset(int offset);

    /*!
     * @brief Sets the sort column and sort order of this @c ContactListFilters.
     *
     * @details The default sort column is FirstName and the default sort order is ascending.
     *
     * @param column The sort column to set.
     * @param order The sort order to set.
     *
     * @return A @c %ContactListFilters with the provided sort column and sort order.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setSortBy(SortColumn::Type column, SortOrder::Type order);

    /*!
     * @brief Sets the sort column and sort order of this @c ContactListFilters using a @c SortSpecifier.
     *
     * @details The default sort column is FirstName and the default sort order is ascending.
     *
     * @param sort The sort column and sort order pair to set, represented by a @c %SortSpecifier.
     *
     * @return A @c %ContactListFilters with the provided sort column and sort order.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setSortBy(const SortSpecifier &sort);

    /*!
     * @brief Sets the sort columns and sort orders of this @c ContactListFilters using a list of @c SortSpecifier
     * objects.
     *
     * @details The default sort column is FirstName and the default sort order is ascending. The returned contact
     * list is first sorted according to the first @c %SortSpecifier in the provided list, then by the second
     * @c %SortSpecifier in the list, and so on.
     *
     * @param sorts The set of sort column and sort order pairs to set, represented by @c %SortSpecifier objects.
     *
     * @return A @c %ContactListFilters with the provided sort columns and sort orders.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setSortBy(const QList<SortSpecifier> &sorts);

    /*!
     * @brief Sets the sort column, sort order, and anchor value of this @c ContactListFilters using an
     * @c AnchorValueSpecifier.
     *
     * @details This function specifies a sort column and order, and offsets the response by a certain anchor value.
     * When anchoring by value, contacts matching the values are included in the response.
     *
     * @param anchorValue The sort column, sort order, and anchor value to set, represented by a @c %AnchorValueSpecifier
     * object.
     *
     * @return A @c %ContactListFilters with the provided sort column, sort order, and anchor value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setSortAndAnchorBy(const AnchorValueSpecifier &anchorValue);

    /*!
     * @brief Sets the sort columns, sort orders, and anchor values of this @c ContactListFilters using a list of
     * @c AnchorValueSpecifier objects.
     *
     * @details This function specifies a set of sort columns and orders, and offsets the response by anchor values.
     * When anchoring by value, contacts matching the values are included in the response.
     *
     * @param anchorValues The set of sort columns, sort orders, and anchor values to set, represented by
     * @c %AnchorValueSpecifier objects.
     *
     * @return A @c %ContactListFilters with the provided sort columns, sort orders, and anchor values.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setSortAndAnchorBy(const QList<AnchorValueSpecifier> &anchorValues);

    /*!
     * @brief Filters the returned contact list to contain only contacts where the source of the contact comes from the
     * provided account ID.
     *
     * @param accountId The account ID to filter based on.
     *
     * @return A @c ContactListFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setHasAccount(AccountId accountId);

    /*!
     * @brief Filters the returned contact list to contain only contacts where the sources of the contact come from any of
     * the provided account IDs.
     *
     * @param accountId The set of account IDs to filter based on.
     *
     * @return A @c ContactListFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setHasAccounts(const QList<AccountId> &accountId);

    /*!
     * @brief Filters the returned contact list to contain only contacts where the source of the contact doesn't come from
     * the provided account ID.
     *
     * @param accountId The account ID to filter based on.
     *
     * @return A @c ContactListFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setExcludeAccount(AccountId accountId);

    /*!
     * @brief Filters the returned contact list to contain only contacts where the sources of the contact don't come from
     * any of the provided account IDs.
     *
     * @param accountId The set of account IDs to filter based on.
     *
     * @return A @c ContactListFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setExcludeAccounts(const QList<AccountId> &accountId);

    /*!
     * @brief Filters the returned contact list to contain the contacts where the source of the contact doesn't come from
     * the provided account ID.
     *
     * @param accountId The account ID to filter based on.
     * @param includeMergedContacts Indicates whether contacts that belong to more than one account should be included in the result
     * if one of the source accounts is not excluded.
     *
     * @return A @c ContactListFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setExcludeAccount(AccountId accountId, bool includeMergedContacts);

    /*!
     * @brief Filters the returned contact list to contain the contacts where the sources of the contact don't come from
     * any of the provided account IDs.
     *
     * @param accountId The set of account IDs to filter based on.
     * @param includeMergedContacts Indicates whether contacts that belong to more than one account should be included in the result
     * if one of the source accounts is not excluded.
     *
     * @return A @c ContactListFilters with the provided account ID filter.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setExcludeAccounts(const QList<AccountId> &accountId, bool includeMergedContacts);

    /*!
     * @brief Sets whether to include photos in the returned contact list.
     *
     * @details If set to @c true, the primary photos that are associated with the contacts are returned. The default value
     * is @c false.
     *
     * @param value If @c true photos are included in the returned contact list, if @c false photos are not included in
     * the returned contact list.
     *
     * @return A @c ContactListFilters with the provided indication of whether to include photos in the returned contact
     * list.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setIncludePhotos(bool value);

    /*!
     * @brief Filters the returned contact list to contain only contacts with the provided attribute kind.
     *
     * @details This function is mutually exclusive with @c setIncludeAttributes().
     *
     * @param kind The attribute kind to filter based on.
     *
     * @return A @c ContactListFilter with the provided attribute kind filter.
     *
     * @see setIncludeAttributes()
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setIncludeAttribute(AttributeKind::Type kind);

    /*!
     * @brief Filters the returned contact list to contain only contacts with the provided attribute kinds.
     *
     * @details This function is mutually exclusive with @c setIncludeAttribute().
     *
     * @param kinds The set of attribute kinds to filter based on.
     *
     * @return A @c ContactListFilter with the provided attribute kinds filter.
     *
     * @see setIncludeAttribute()
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setIncludeAttributes(const QList<AttributeKind::Type> &kinds);

    /*!
     * @brief Sets whether to include postal addresses in the returned contact list.
     *
     * @details This function specifies whether postal addresses are included in the response, if these addresses are available
     * for the contacts.
     *
     * @param value If @c true postal addresses are included in the returned contact list, if @c false postal addresses
     * are not included in the returned contact list.
     *
     * @return A @c ContactListFilters with the provided indication of whether to include postal addresses in the returned
     * contact list.
     *
     * @since BlackBerry 10.0.0
     */
    ContactListFilters& setIncludePostalAddress(bool value);

    /*!
     * @brief Retrieves the list of contact IDs that are excluded with this @c ContactListFilters.
     *
     * @return A list of contact IDs that are excluded with this @c %ContactListFilters.
     *
     * @since BlackBerry 10.3.0
     */
    QVariantList excludeContacts() const;

    /*!
     * @brief Sets the list of contact IDs that are excluded when using this @c ContactListFilters.
     *
     * @details This function is mutually exclusive with @c setContactIds(). If @c %setContactIds()
     * was called with a list of Contact IDs, this @c setExcludeContacts() filter does nothing.
     *
     * @param contactIds The list of contact IDs that should be excluded.
     *
     * @return A @c %ContactListFilters with the provided list of contact IDs.
     *
     * @since BlackBerry 10.3.0
     */
    ContactListFilters& setExcludeContacts(const QList<ContactId> &contactIds);

    /*!
     * @brief This function filters the returned contact list to contain only contacts with a display picture.
     *
     * @param hasPhoto If @c true, only contacts with a display picture are included in the returned contact list. If @c false,
     * this filter does nothing.
     *
     * @return A @c ContactListFilters with the provided @c hasPhoto filter.
     *
     * @since BlackBerry 10.3.0
     */
    ContactListFilters& setHasPhoto(bool hasPhoto);

    /*!
     * @brief Sets whether contact groups should be included in the results or not.
     *
     * @details If set to @c true, groups will be returned as a part of the results.
     *
     * @param value @c True if groups should be included, @c false otherwise.
     *
     * @return A @c %ContactListFilters with the specified groups included mode.
     *
     * @since BlackBerry 10.3.0
     */
    ContactListFilters& setIncludeGroups(bool value);

    /*!
     * @brief Filters the contact list to contacts that belong to the specified contact groups.
     * 
     * @details This is useful if you want to list group members.
     *
     * @param groupIds the ids of the groups that the contacts returned must belong to.
     * 
     * @return A @c %ContactListFilters with the specified groups filter set.
     *
     * @since BlackBerry 10.3.0
     */
    ContactListFilters& setBelongsToGroups(QList<GroupId> groupIds);

    /*!
     * @brief Sets whether to include account IDs for content sources in the search results.
     *
     * @details If set to @c true, contacts that are returned include a list of account IDs that are the sources of
     * content for the contacts.
     *
     * @param value If @c true account IDs are included in the search results, if @c false account IDs are not
     * included in the search results.
     *
     * @return A @c %ContactListFilters with the the provided indication of whether to include source accounts list
     *
     * @since BlackBerry 10.3.0
     */
    ContactListFilters& setShowSources(bool value);

private:
    QSharedDataPointer<ContactListFiltersPrivate> d_ptr;
    friend class ContactListFiltersPrivate;
};


} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTLISTFILTERS_HPP
