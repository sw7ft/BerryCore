/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKCONSTRAINT_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKCONSTRAINT_HPP

#include <bb/pim/Global>
#include <QFlags>

namespace bb {
namespace pim {
namespace notebook {

/*!
 * @headerfile NotebookConstraint.hpp <bb/pim/notebook/NotebookConstraint>
 *
 * @brief The @c NotebookConstraint class represents a constraint on the contents of a @c Notebook.
 *
 * @details Notebook constraints define constraints on the contents of a @c %Notebook.  These constraints are silently
 * enforced by the @c NotebookService, meaning that add and update operations that violate the constraints are not
 * rejected.  Instead, any such violations are simply disregarded.  For example, changing the name of a @c %Notebook
 * that disallows name changes will result in the name change being dropped during the @c %NotebookService update
 * operation.  For more information, see the documentation for individual constraints.
 *
 * @see Notebook, NotebookService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookConstraint
{
public:
    /*!
     * @brief An enumeration of possible constraints.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * Indicates that name changes to the @c Notebook are not supported. Name changes will be silently dropped when
         * updating the @c %Notebook using @c NotebookService::updateNotebook().
         *
         * @since BlackBerry 10.0.0
         */
        NameNotEditable = 0x01,

        /*!
         * Indicates that @c NotebookEntry items cannot be added to this @c Notebook.
         *
         * @since BlackBerry 10.3.0
         */
        AddNotebookEntryNotSupported = 0x02,

        /*!
         * Indicates that only Flagged Messages can be added to this @c Notebook.
         *
         * @since BlackBerry 10.3.0
         */
        FlaggedMessagesOnly = 0x04
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
    NotebookConstraint();
    ~NotebookConstraint();
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NotebookConstraint::Types)

} /* namespace notebook */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKCONSTRAINT_HPP */
