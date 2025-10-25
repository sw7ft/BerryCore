/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYDETAILLEVEL_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYDETAILLEVEL_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookEntryDetailLevel.hpp <bb/pim/notebook/NotebookEntryDetailLevel>
 *
 * @brief The @c NotebookEntryDetailLevel class represents the detail level
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
class BB_PIM_EXPORT NotebookEntryDetailLevel
{

public:
    /*!
     * @brief An enumeration of possible detail levels.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * Indicates that notebook entries should be populated with all fields.
         * This is the default value.
         *
         * @since BlackBerry 10.2.0
         */
        Full = 0,
        /*!
         * Indicates that notebook entries should be populated with only those
         * fields necessary for showing an item in a list.
         *
         * @since BlackBerry 10.2.0
         */
        ListItem = 1
    };

private:
    NotebookEntryDetailLevel();
    ~NotebookEntryDetailLevel();
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYDETAILLEVEL_HPP */
