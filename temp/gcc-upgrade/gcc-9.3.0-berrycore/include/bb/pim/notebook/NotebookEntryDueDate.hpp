/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYDUEDATE_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYDUEDATE_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookEntryDueDate.hpp <bb/pim/notebook/NotebookEntryDueDate>
 *
 * @brief The @c NotebookEntryDueDate class provides a set of options for filtering
 * notebook entries by due date or reminder date.
 * Each NotebookEntryFilter has separate NotebookEntryDueDates for the Reminder date
 * and the Due Date.
 *
 * @see NotebookEntryFilter
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntryDueDate
{

public:

    /*!
     * @brief An enumeration of supported date filter options.
     *
     * @details A search query can be restricted to any of the available filter options.
     * Each NotebookEntryFilter has separate NotebookEntryDueDate restrictions for its
     * due date and for its remidner time, and they are set independently.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that a search should match all notebook entries.
         *
         * @since BlackBerry 10.0.0
         */
        NotSpecified  = 0,

        /*!
         * Indicates that a search should match notebook entries with no date of this
         * type (due date or reminder).
         *
         * @since BlackBerry 10.0.0
         */
        NoDate = 1,

        /*!
         * Indicates that a search should match notebook entries with any date.
         *
         * @since BlackBerry 10.0.0
         */
        AnyDate = 3,

        /*!
         * Indicates that a search should match notebook entries with dates up to and including a specified date.
         *
         * @since BlackBerry 10.0.0
         */
        BySpecificDate = 2,

        /*!
         * Indicates that a search should match notebook entry dates that are after and excluding a specified date.
         *
         * @since BlackBerry 10.0.0
         */
        AfterSpecificDate = 4,

        /*!
         * Indicates that a search should match notebook entry dates that are within a specified date range.  This check
         * does not include (is strictly after) the "after" date/time, but it does include (is up to and including)
         * the "by" date/time.
         *
         * @since BlackBerry 10.0.0
         */
        WithinSpecificRange = 5
    };

private:
    NotebookEntryDueDate();
    ~NotebookEntryDueDate();
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYDUEDATE_HPP */
