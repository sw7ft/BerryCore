/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYCONSTRAINT_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYCONSTRAINT_HPP

#include <bb/pim/Global>
#include <QFlags>

namespace bb {
namespace pim {
namespace notebook {

/*!
 * @headerfile NotebookEntryConstraint.hpp <bb/pim/notebook/NotebookEntryConstraint>
 *
 * @brief The @c NotebookEntryConstraint class represents a constraint on the contents of a @c NotebookEntry, imposed by the
 * parent @c Notebook that the @c %NotebookEntry belongs to.
 *
 * @details Notebook entry constraints define constraints on the contents of a @c %NotebookEntry. These constraints are
 * imposed upon a @c %NotebookEntry by the parent @c %Notebook that it belongs to, and so they may change as a @c %NotebookEntry
 * moves between @c %Notebooks.
 *
 * Notebook entry constraints are silently enforced by the @c NotebookService, meaning that add and update operations that
 * violate the constraints are not rejected. Instead, any such violations are simply disregarded as part of the
 * @c %NotebookService commit operation. For example, adding attachments to a @c %NotebookEntry that does not
 * support attachments results in those attachments being dropped during the @c %NotebookService add or update operation.
 * For more information, see the documentation for individual constraints.
 *
 * @see Notebook, NotebookEntry, NotebookService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntryConstraint
{
public:
    /*!
     * @brief An enumeration of possible constraints.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * Indicates that attachments are not supported. Attachments are silently dropped when updating using the
         * @c NotebookService.
         *
         * @since BlackBerry 10.0.0
         */
        AttachmentsNotSupported = 0x01,

        /*!
         * Indicates that the @c NotebookEntry must not be actionable. The status is set to
         * @c NotebookEntryStatus::NotActionable when updating using the @c NotebookService.
         *
         * @since BlackBerry 10.0.0
         */
        MustNotBeActionable = 0x02,

        /*!
         * Indicates that the @c NotebookEntry must be actionable. A status of @c NotebookEntryStatus::NotActionable
         * is changed to @c NotebookEntryStatus::NotCompleted when updating using the @c NotebookService. Other status
         * values are not changed.
         *
         * @since BlackBerry 10.0.0
         */
        MustBeActionable = 0x04,

        /*!
         * Indicates that title changes to the @c NotebookEntry are not supported. Title changes are silently dropped
         * when updating the @c %NotebookEntry using @c NotebookService::updateNotebookEntry().
         *
         * @since BlackBerry 10.0.0
         */
        TitleNotEditable = 0x08,

        /*!
         * Indicates that description changes to the @c NotebookEntry are not supported. Description changes are
         * silently dropped when updating the @c %NotebookEntry using @c NotebookService::updateNotebookEntry().
         *
         * @since BlackBerry 10.0.0
         */
        DescriptionNotEditable = 0x10,

        /*!
         * Indicates that the @c NotebookEntry does not support the addition of tags. Tag changes are silently
         * dropped when updating the @c NotebookEntry using @c NotebookService::updateNotebookEntry().
         *
         * @since BlackBerry 10.3.0
         */
        TagsNotSupported = 0x20
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
    NotebookEntryConstraint();
    ~NotebookEntryConstraint();
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NotebookEntryConstraint::Types)

} /* namespace notebook */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYCONSTRAINT_HPP */
