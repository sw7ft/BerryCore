/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CONTACTS_CONTACTAUTOCOMPLETESEARCHFILTERS_HPP
#define BB_PIM_CONTACTS_CONTACTAUTOCOMPLETESEARCHFILTERS_HPP
#include <bb/pim/Global>
#include <bb/pim/contacts/ContactConsts>
#include <QString>
#include <QSet>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace contacts {

class ContactAutoCompleteSearchFiltersPrivate;

/*!
 * @brief The @c ContactAutoCompleteSearchFilters class represents a set of search filters that are used for
 * auto-complete searches.
 * 
 * @details You can use this class to provide support for auto-complete searches, which are performed by calling
 * @c ContactService::searchContactsAutoComplete(). Auto-complete searches are designed to be fast, and are used
 * primarily to display auto-completion results for email addresses. Users can type partial search terms and
 * the API will try to find matching completions.
 * 
 * @see ContactService::searchContactsAutoComplete()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactAutoCompleteSearchFilters
{
public:
    /*!
     * @brief Constructs a new @c ContactAutoCompleteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters();

    /*!
     * @brief Destroys this @c ContactAutoCompleteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactAutoCompleteSearchFilters();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactAutoCompleteSearchFilters containing exactly the same values as the
     * provided @c %ContactAutoCompleteFilters.
     * 
     * @param copy The @c %ContactAutoCompleteSearchFilters to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters(const ContactAutoCompleteSearchFilters &copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactAutoCompleteSearchFilters into this
     * @c %ContactAutoCompleteSearchFilters.
     * 
     * @param operand The @c %ContactAutoCompleteSearchFilters from which to copy all values.
     *
     * @return A @c %ContactAutoCompleteSearchFilters with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters& operator=(const ContactAutoCompleteSearchFilters &operand);

    /*!
     * @brief Retrieves the result limit of this @c ContactAutoCompleteSearchFilters.
     * 
     * @details This value represents the maximum number of results that are returned for the auto-complete search.
     * 
     * @return The result limit of this @c %ContactAutoCompleteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    int limit() const;

    /*!
     * @brief Retrieves the search value of this @c ContactAutoCompleteSearchFilters.
     * 
     * @details This value represents the string to search for in the list of contacts.
     *
     * @return The search value of this @c %ContactAutoCompleteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    QString searchValue() const;

    /*!
     * @brief Retrieves the search field of this @c ContactAutoCompleteSearchFilters.
     * 
     * @details This value represents the search field that the auto-complete search applies to. For example, you can
     * specify that the search should apply to emails, Twitter profile information, Facebook profile information,
     * and so on.
     * 
     * @return The search field of this @c %ContactAutoCompleteSearchFilters.
     *
     * @since BlackBerry 10.0.0
     */
    SearchAutoCompleteField::Type searchField() const;

    /*!
     * @brief Indicates whether the primary photo that's associated with a contact should be included as part of the
     * search results.
     * 
     * @return @c true if the primary photo should be included in the results, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool includePhotos() const;

    /*!
     * @brief Sets the result limit of this @c ContactAutoCompleteSearchFilters.
     * 
     * @details This value represents the maximum number of results that are returned for the auto-complete search. If
     * no limit is set, the default value is 20 results.
     * 
     * @param limit The maximum number of results that are returned.
     * 
     * @return A @c %ContactAutoCompleteSearchFilters with the provided result limit.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters& setLimit(int limit);

    /*!
     * @brief Sets the search value of this @c ContactAutoCompleteSearchFilters.
     * 
     * @details This value represents the string to search for in the list of contacts. This is a required field.
     * 
     * @param value The search value to set.
     * 
     * @return A @c %ContactAutoCompleteSearchFilters with the provided search value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters& setSearchValue(const QString &value);

    /*!
     * @brief Sets the search field of this @c ContactAutoCompleteSearchFilters.
     * 
     * @details This function sets the search field that the auto-complete search applies to, according to the provided
     * value from the @c SearchAutoCompleteField::Type enumeration. If no field is specified, the default search field
     * is by email (@c SearchAutoCompleteField::Email).
     * 
     * @param field The search field to set.
     * 
     * @return A @c %ContactAutoCompleteSearchFilter with the provided search field.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters& setSearchField(SearchAutoCompleteField::Type field);

    /*!
     * @brief Sets whether to include the primary photo that's associated with a contact as part of the search results.
     * 
     * @param includePhotos If @c true the primary photo should be included in the results, if @c false the primary
     * photo should not be included in the results.
     *
     * @return A @c %ContactAutoCompleteSearchFilter with the provided indication of whether to include the primary
     * photo in the search results.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAutoCompleteSearchFilters& setIncludePhotos(bool includePhotos);

private:
    QSharedDataPointer<ContactAutoCompleteSearchFiltersPrivate> d_ptr;
    friend class ContactAutoCompleteSearchFiltersPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTAUTOCOMPLETESEARCHFILTERS_HPP
