/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYSTATUS_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYSTATUS_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookEntryStatus.hpp <bb/pim/notebook/NotebookEntryStatus>
 *
 * @brief The @c NotebookEntryStatus class provides the available statuses that can be set on a @c NotebookEntry.
 *
 * @details You can use this class to specify that a @c %NotebookEntry is not actionable, not completed, or
 * completed. Multiple statuses can be used when set on a @c NotebookEntryFilter.
 *
 * @see NotebookEntry, NotebookEntryFilter
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntryStatus
{

public:
    /*!
     * @brief An enumeration of supported statuses for a @c NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that the @c %NotebookEntry is not actionable (that is, it cannot be completed).
         *
         * @since BlackBerry 10.0.0
         */
        NotActionable = 0x01,

        /*!
         * Indicates that the @c %NotebookEntry is actionable, but is not completed.
         *
         * @since BlackBerry 10.0.0
         */
        NotCompleted = 0x02,

        /*!
         * Indicates that the @c %NotebookEntry is actionable and completed.
         *
         * @since BlackBerry 10.0.0
         */
        Completed = 0x04
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
    NotebookEntryStatus();
    ~NotebookEntryStatus();
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NotebookEntryStatus::Types)

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYSTATUS_HPP */
