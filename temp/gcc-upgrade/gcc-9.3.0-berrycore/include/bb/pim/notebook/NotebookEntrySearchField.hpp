/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYSEARCHFIELD_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYSEARCHFIELD_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookEntrySearchField.hpp <bb/pim/notebook/NotebookEntrySearchField>
 *
 * @brief The @c NotebookEntrySearchField class provides a set of flags that determine which @c NotebookEntry
 * fields to search when specified with a @c NotebookEntryFilter.
 *
 * @details You can use this class to specify that a @c %NotebookEntryFilter should search all fields, only
 * the title field, or only the description field.
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
class BB_PIM_EXPORT NotebookEntrySearchField
{

public:

    /*!
     * @brief An enumeration of supported search fields for a @c NotebookEntryFilter.
     *
     * @details A search query can be restricted to any of the available search fields (for example, the title
     * field or the description field).
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that the @c %NotebookEntryFilter should search all available fields.
         *
         * @since BlackBerry 10.0.0
         */
        All = 0x01,

        /*!
         * Indicates that the @c %NotebookEntryFilter should search the title field only.
         *
         * @since BlackBerry 10.0.0
         */
        Title = 0x02,

        /*!
         * Indicates that the @c %NotebookEntryFilter should search the description field only.
         *
         * @since BlackBerry 10.0.0
         */
        Description = 0x04
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
    NotebookEntrySearchField();
    ~NotebookEntrySearchField();
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NotebookEntrySearchField::Types)

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYSEARCHFIELD_HPP */
