/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKDOMAIN_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKDOMAIN_HPP

#include <bb/pim/Global>

#include <QFlags>
#include <QObject>
#include <QtDeclarative/QtDeclarative>


namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookDomain.hpp <bb/pim/notebook/NotebookDomain>
 *
 * @brief The @c NotebookDomain class provides the available Notebook Domains that a @c Notebook can contain.
 *
 * @details You can use this class in conjunction with setting the notebookDomain field of a @c NotebookFilter.
 *
 * @see Notebook, NotebookFilter
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT NotebookDomain : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of possible Notebook Domain Types.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type
    {
        /*!
         * Indicates the @c Notebook may contain tasks
         *
         * @since BlackBerry 10.3.0
         */
        Tasks = 0x1,

        /*!
         * Indicates the @c Notebook may contain notes
         *
         * @since BlackBerry 10.3.0
         */
        Notes = 0x2
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
    NotebookDomain();
    ~NotebookDomain();
};
Q_DECLARE_OPERATORS_FOR_FLAGS(NotebookDomain::Types)

} // namespace notebook
} // namespace pim
} // namespace bb

QML_DECLARE_TYPE(bb::pim::notebook::NotebookDomain)
#endif /* BB_PIM_NOTEBOOK_NOTEBOOKDOMAIN_HPP */
