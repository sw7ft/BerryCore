/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYSORTORDER_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYSORTORDER_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookEntrySortOrder.hpp <bb/pim/notebook/NotebookEntrySortOrder>
 *
 * @brief The @c NotebookEntrySortOrder class represents the sort order (ascending or descending)
 * of a notebook entry list or search response.
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
class BB_PIM_EXPORT NotebookEntrySortOrder
{

public:
    /*!
     * @brief An enumeration of possible sort orders.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * Indicates that notebook entries should be sorted in ascending order. This is the default value.
         *
         * @since BlackBerry 10.2.0
         */
        Ascending = 0,
        /*!
         * Indicates that notebook entries should be sorted in descending order.
         *
         * @since BlackBerry 10.2.0
         */
        Descending = 1
    };

private:
    NotebookEntrySortOrder();
    ~NotebookEntrySortOrder();
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYSORTORDER_HPP */
