/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYSORTCOLUMN_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYSORTCOLUMN_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookEntrySortColumn.hpp <bb/pim/notebook/NotebookEntrySortColumn>
 *
 * @brief The @c NotebookEntrySortColumn class represents the columns that can be used to sort notebook entries.
 *
 * @details You can use the @c NotebookEntrySortColumn::Type enumeration to specify the columns that
 * should be used to sort notebook entries. For example, you can use a @c %NotebookEntrySortColumn::Type
 * enumeration value in @c NotebookEntryFilter::setSortBy() to sort notebook entries by title,
 * due date, last modified date or creation date.
 *
 * @see NotebookEntryFilter
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PIM_EXPORT NotebookEntrySortColumn
{

public:
    /*!
     * @brief An enumeration of possible columns that can be used to sort notebook entries.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * Indicates that notebook entries should be sorted by Title. This is the default value.
         *
         * @since BlackBerry 10.2.0
         */
        Title = 0,
        /*!
         * Indicates that notebook entries should be sorted by due date.
         *
         * @since BlackBerry 10.2.0
         */
        DueDate = 1,
        /*!
         * Indicates that notebook entries should be sorted by creation date.
         *
         * @since BlackBerry 10.2.0
         */
        CreationDate = 2,
        /*!
         * Indicates that notebook entries should be sorted by last modified date.
         *
         * @since BlackBerry 10.2.0
         */
        LastModifiedDate = 3,
        /*!
		 * Indicates that notebook entries should be sorted by first letter headers.
		 * (A, B, C, D, E, F, G ...)
		 * This is only valid as the first order sort.  If passed in as a second or
		 * later order sort, it will revert to Title ordering
		 *
		 * @since BlackBerry 10.2.0
		 */
		FirstLetterHeaders = 4,
        /*!
         * Indicates that notebook entries should be sorted by due date headers.
         * (Overdue, Today, Tomorrow, This Week, Next Week, Later)
         * This is only valid as the first order sort.  If passed in as a second or
         * later order sort, it will revert to DueDate ordering
         *
         * @since BlackBerry 10.2.0
         */
        DueDateHeaders = 5,
        /*!
         * Indicates that notebook entries should be sorted by creation date headers.
         * (Today, Yesterday, This Week, Last Week, Earlier)
         * This is only valid as the first order sort.  If passed in as a second or
         * later order sort, it will revert to CreationDate ordering
         *
         * @since BlackBerry 10.2.0
         */
        CreationDateHeaders = 6,
        /*!
         * Indicates that notebook entries should be sorted by last modified date headers.
         * (Today, Yesterday, This Week, Last Week, Earlier)
         * This is only valid as the first order sort.  If passed in as a second or
         * later order sort, it will revert to LastModifiedDate ordering
         *
         * @since BlackBerry 10.2.0
         */
        LastModifiedDateHeaders = 7,
        /*!
         * Indicates that notebook entries should be sorted by status.
         * (NotCompleted, Completed, NotActionable)
         *
         * @since BlackBerry 10.2.0
         */
        Status = 8,
        /*!
         * Indicates that notebook entries should be sorted by status with one caveat.
         * (NotCompleted, Completed, NotActionable)
         * Just completed entries are not considered complete until
         * the next day.  This enables a user to see how many and which tasks
         * they accomplished that day.
         *
         * @since BlackBerry 10.3.0
         */
        StatusIgnoringJustCompleted = 9

    };

private:
    NotebookEntrySortColumn();
    ~NotebookEntrySortColumn();
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYSORTCOLUMN_HPP */
