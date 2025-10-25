/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CONTACTS_CONTACTREMOTESEARCHFILTERS_HPP
#define BB_PIM_CONTACTS_CONTACTREMOTESEARCHFILTERS_HPP

#include <bb/pim/Global>
#include <bb/pim/contacts/ContactConsts>
#include <QString>

namespace bb {
namespace pim {
namespace contacts {

class ContactRemoteSearchFiltersPrivate;

/*!
 * @brief The @c ContactRemoteSearchFilters class represents a set of filters that are used for remote searches.
 * 
 * @details You can use this class to filter search results that you retrieve using @c ContactService::searchRemote().
 * You can specify the string to search for, start index, end index, and account to search.
 * 
 * These filters allow pagination, but only when used with a specific account. When used without the account specified,
 * the query tries to fetch the specified page of contacts from all remote searchable sources.
 * 
 * @see ContactService::searchRemote()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactRemoteSearchFilters
{
public:
    /*!
     * @brief Constructs a new @c ContactRemoteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters();

    /*!
     * @brief Destroys this @c ContactRemoteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactRemoteSearchFilters();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactRemoteSearchFilters containing exactly the same values as the
     * provided @c %ContactRemoteSearchFilters.
     * 
     * @param copy The @c %ContactRemoteSearchFilters to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters(const ContactRemoteSearchFilters &copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactRemoteSearchFilters into this
     * @c %ContactRemoteSearchFilters.
     * 
     * @param operand The @c %ContactRemoteSearchFilters from which to copy all values.
     *
     * @return A @c %ContactRemoteSearchFilters with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters& operator=(const ContactRemoteSearchFilters &operand);

    /*!
     * @brief Sets the search value of this @c ContactRemoteSearchFilters.
     * 
     * @details This is a required field.
     * 
     * @param value The search value to set.
     * 
     * @return A @c %ContactRemoteSearchFilters with the provided search value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters& setSearchValue(QString &value);

    /*!
     * @brief Sets the start index of this @c ContactRemoteSearchFilters.
     * 
     * @details The start index is 0-based (that is, the first element to be searched is at index 0) and is inclusive.
     * 
     * @param start The start index to set.
     * 
     * @return A @c %ContactRemoteSearchFilters with the provided start index.
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters& setStartIndex(int start);

    /*!
     * @brief Sets the end index of this @c ContactRemoteSearchFilters.
     * 
     * @details The end index is 0-based (that is, the first element to be searched is at index 0) and is inclusive.
     * 
     * @param end The end index to set.
     * 
     * @return A @c %ContactRemoteSearchFilters with the provided end index.
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters& setEndIndex(int end);

    /*!
     * @brief Sets the account ID for this @c ContactRemoteSearchFilters.
     * 
     * @details The account ID specifies the account that the remote search should apply to.
     * 
     * @param accountId The account ID to set.
     * 
     * @return A @c %ContactRemoteSearchFilters with the provided account ID.
     *
     * @since BlackBerry 10.0.0
     */
    ContactRemoteSearchFilters& setAccount(AccountId accountId);

private:
    QSharedDataPointer<ContactRemoteSearchFiltersPrivate> d_ptr;
    friend class ContactRemoteSearchFiltersPrivate;
};


} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTREMOTESEARCHFILTERS_HPP
