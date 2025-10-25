/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKFILTER_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKFILTER_HPP

#include <bb/pim/account/Account>

#include <bb/pim/notebook/Notebook>
#include <bb/pim/notebook/NotebookConstraint>
#include <bb/pim/notebook/NotebookDomain>

#include <bb/pim/Global>

#include <QDateTime>
#include <QSharedDataPointer>

namespace bb
{
namespace pim
{
namespace notebook
{
class NotebookFilterPrivate;

/*!
 * @headerfile NotebookFilter.hpp <bb/pim/notebook/NotebookFilter>
 *
 * @brief The @c NotebookFilter class represents a filter that can be used to search and count notebook entries.
 *
 * @details A @c %NotebookFilter is used to retrieve lists or counts of @c Notebook objects that match certain
 * criteria, which are specified using setter functions.  Filter criteria are cumulative; a @c %Notebook must match
 * all criteria set on the filter in order to be accepted by the filter.
 *
 *
 * Example usage:
 * @code
 *   // Here's how to create a filter for retrieving Notebook objects.
 *   // Note that service objects are potentially expensive to initialize, so you should not create
 *   // them on a per-use basis as is done below.
 *   NotebookService service;
 *   NotebookFilter filter;
 *   filter.setSearchString( "Physics Class Notes" );
 *   QList<Notebook> folders = service.notebooks( filter );
 * @endcode
 *
 * @see NotebookService::notebooks()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT NotebookFilter
{
public:
    /*!
     * @brief Constructs a new @c NotebookFilter with no criteria set.
     *
     * @details A default-constructed filter accepts all @c Notebook objects.
     *
     * @since BlackBerry 10.3.0
     */
    NotebookFilter();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c NotebookFilter containing exactly the same criteria as the provided
     * @c %NotebookFilter.
     *
     * @param other The @c %NotebookFilter to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    NotebookFilter(const NotebookFilter &other);

    /*!
     * @brief Destroys this @c NotebookFilter.
     *
     * @since BlackBerry 10.3.0
     */
    ~NotebookFilter();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c NotebookFilter into this
     * @c %NotebookFilter.
     *
     * @param other The @c %NotebookFilter from which to copy all values.
     *
     * @return A reference to this @c %NotebookFilter.
     *
     * @since BlackBerry 10.3.0
     */
    NotebookFilter& operator=(const NotebookFilter &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator determines if this @c NotebookFilter has the same values as another
     * @c %NotebookFilter.  If two @c %NotebookFilter objects are considered equal by this
     * operator, they will both accept the same @c NotebookEntry objects.
     *
     * @param other The @c %NotebookFilter to compare to.
     *
     * @return @c True if the values are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool operator==(const NotebookFilter &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator determines if this @c NotebookFilter has any different values from
     * another @c %NotebookFilter.
     *
     * @param other The @c %NotebookFilter to compare to.
     *
     * @return @c True if any of the values are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool operator!=(const NotebookFilter &other) const;

    /*!
     * @brief Sets the search string for this @c NotebookFilter.
     *
     * @details Once set, this @c %NotebookFilter will only accept @c Notebook objects containing the specified
     * search string within the provided search field or fields. If the provided string is null or empty, then this
     * @c %NotebookFilter does not reject @c %Notebook objects based on search strings.
     *
     * @param searchString The search string criterion for this @c %NotebookFilter.
     *        The maximum length of the search string that can be handled by the @c NotebookService is 250 characters.
     *
     * @since BlackBerry 10.3.0
     */
    void setSearchString(const QString &searchString);

    /*!
     * @brief Resets the search string for this @c NotebookFilter.
     *
     * @details Calling this function prevents this @c %NotebookFilter from rejecting @c Notebook objects based
     * on search string, and is equivalent to invoking @c setSearchString() with a null @c QString.
     *
     * @since BlackBerry 10.3.0
     */
    void resetSearchString();

    /*!
     * @brief Retrieves the search string criterion being used by this @c NotebookFilter.
     *
     * @return The search string criterion being used by this @c NotebookFilter. If a search string criterion is not
     * set or has been reset, a null @c QString is returned.
     *
     * @since BlackBerry 10.3.0
     */
    QString searchString() const;

    /*!
     * @brief Determines whether this @c NotebookFilter is filtering based on search strings.
     *
     * @return @c True if this @c %NotebookFilter is filtering based on search strings, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool hasSearchString() const;

    /*!
     * @brief Retrieves the notebook domain criterion being used by this @c NotebookFilter.
     *
     * @return The notebook domain criterion being used by this @c NotebookFilter
     *
     * @since BlackBerry 10.3.0
     */
    NotebookDomain::Types notebookDomains() const;

    /*!
     * @brief Sets the notebook domain of this @c NotebookFilter.
     *
     * @details Once set, this @c %NotebookFilter will only accept @c Notebook objects containing the specified
     * notebook domain within the provided search field or fields.
     *
     * @param domains The notebook domain criterion for this @c %NotebookFilter.
     *
     * @since BlackBerry 10.3.0
     */
    void setNotebookDomains(const NotebookDomain::Types domains);

    /*!
     * @brief Resets the notebook domain criteria for this @c NotebookFilter.
     *
     * @details Calling this function prevents this @c %NotebookFilter from rejecting @c Notebook objects based
     * on notebook domain, and is equivalent to invoking @c setNotebookDomain() with a
     * (NotebookDomain::Tasks | NotebookDomain::Notes) @c NotebookDomain::Types
     *
     * @since BlackBerry 10.3.0
     */
    void resetNotebookDomains();

    /*!
     * @brief Retrieves the account key criterion being used by this @c NotebookFilter.
     *
     * @return The account key criterion being used by this @c NotebookFilter
     *
     * @since BlackBerry 10.3.0
     */
    bb::pim::account::AccountKey accountKey() const;

    /*!
     * @brief Sets the account key of this @c NotebookFilter.
     *
     * @details Once set, this @c %NotebookFilter will only accept @c Notebook objects that
     * belong to the account specified by the account key
     *
     * @param accountKey The account key criterion for this @c %NotebookFilter.
     *
     * @since BlackBerry 10.3.0
     */
    void setAccountKey(const bb::pim::account::AccountKey accountKey);

    /*!
     * @brief Resets the account key for this @c NotebookFilter.
     *
     * @details Calling this function prevents this @c %NotebookFilter from rejecting @c Notebook objects based
     * on account key, and is equivalent to invoking @c setAccountKey() with a Account::InvalidKey account key.
     *
     * @since BlackBerry 10.3.0
     */
    void resetAccountKey();

    /*!
     * @brief Sets the notebook constraints criterion for this @c NotebookFilter.
     *
     * @details Once set, this @c %NotebookFilter will only accept @c Notebook objects with the specified
     * notebook constraints.
     *
     * @param notebookConstraints The notebook constraints criterion for this @c %NotebookFilter.
     *
     * @since BlackBerry 10.3.0
     */
    void setNotebookConstraints(NotebookConstraint::Types notebookConstraints);

    /*!
     * @brief Resets the notebook constraints criterion for this @c NotebookFilter.
     *
     * @details Calling this function prevents this @c %NotebookFilter from rejecting @c Notebook objects based
     * on notebook constraints, and is equivalent to invoking @c setNotebookConstraints() with 0.
     *
     * @since BlackBerry 10.3.0
     */
    void resetNotebookConstraints();

    /*!
     * @brief Retrieves the notebook constraints criterion being used by this @c NotebookFilter.
     *
     * @return The notebook constraints criterion being used by this @c NotebookFilter
     *
     * @since BlackBerry 10.3.0
     */
    NotebookConstraint::Types notebookConstraints() const;

private:
    QSharedDataPointer<NotebookFilterPrivate> d_ptr;
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif // BB_PIM_NOTEBOOK_NOTEBOOKFILTER_HPP
