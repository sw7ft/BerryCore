/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOK_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOK_HPP

#include <bb/pim/Global>

#include <bb/pim/account/Account>
#include <bb/pim/notebook/NotebookConstraint>
#include <bb/pim/notebook/NotebookDomain>
#include <bb/pim/notebook/NotebookEntryConstraint>
#include <bb/pim/notebook/NotebookId>

#include <QMetaType>
#include <QString>
#include <QSharedDataPointer>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookPrivate;

/*!
 * @headerfile Notebook.hpp <bb/pim/notebook/Notebook>
 *
 * @brief The @c Notebook class represents a folder-like object that contains notebook entries.
 *
 * @details Notebooks are used to organize actionable and non-actionable items called notebook entries into separate
 * folders or topics.  For example, you can create a "grocery list" notebook that contains items you need to
 * purchase, each of which can be marked as completed as it is added to your cart.  Notebooks can also contain
 * non-actionable notebook entries, such as photos taken on a trip. %Notebook entries are represented by the
 * @c NotebookEntry class.
 *
 * Some notebooks are created automatically by the system and have special meaning and behavior.  Such special
 * notebooks can be recognized by querying their @c Notebook::type() function, which will return something other than
 * @c Notebook::Generic.  Items in a non-generic notebook are generally kept in sync with another source, such as an
 * ActiveSync account.  See the @c Notebook::Type enum for supported special notebook types.
 *
 * Example usage:
 * @code
 *   // Here's how to create a Notebook with a name and custom attribute, and add
 *   // it to the default Notebook account database using the NotebookService.
 *   // Note that service objects are potentially expensive to initialize, so you
 *   // should not create them on a per-use basis as is done below.
 *   AccountKey defaultAccountKey = AccountService().defaultAccount(
 *                                                    Service::Notebook ).id();
 *   Notebook notebook;
 *   notebook.setName( "New Notebook" );
 *   notebook.setAttribute( "my_attribute", "my_attribute_value" );
 *
 *   // You should be sure to check the return code from addNotebook() for
 *   // success
 *   NotebookService().addNotebook( &notebook, defaultAccountKey );
 * @endcode
 *
 *
 * @see NotebookEntry
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Notebook
{

public:
    /*!
     * @brief An enumeration of supported @c Notebook types.
     *
     * @details Notebooks with a type other than @c Notebook::Generic have special meaning and behavior.  See the
     * class-level documentation for more details.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * The generic @c Notebook type, which implies no special meaning or behavior.
         *
         * @since BlackBerry 10.0.0
         */
        Generic = 0,

        /*!
         * An ActiveSync Memo @c Notebook type, in which each contained @c NotebookEntry is synchronized with an ActiveSync Memo.
         *
         * @since BlackBerry 10.0.0
         */
        ActiveSyncMemo = 1,

        /*!
         * An ActiveSync Task @c Notebook type, in which each contained @c NotebookEntry is synchronized with an ActiveSync Task.
         *
         * @since BlackBerry 10.0.0
         */
        ActiveSyncTask = 2,

        /*!
         * An Evernote @c Notebook type, in which each contained @c NotebookEntry is synchronized with an Evernote entry.
         *
         * @since BlackBerry 10.0.0
         */
        Evernote = 4
    };

    /*!
     * @brief Constructs a new @c Notebook with default values.
     *
     * @details A default-constructed @c %Notebook is considered invalid until at least one of its values is set.
     * You can determine whether a @c %Notebook is valid by calling @c isValid().
     *
     * @see isValid()
     *
     * @since BlackBerry 10.0.0
     */
    Notebook();

    /*!
     * @brief Constructs a new @c Notebook with the domain set to @c domain.
     *
     * @see Notebook()
     * @see setDomain()
     *
     * @since BlackBerry 10.3.0
     */
    Notebook(NotebookDomain::Type domain);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c Notebook containing exactly the same values as the provided @c %Notebook.
     *
     * @param other The @c %Notebook to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Notebook(const Notebook &other);

    /*!
     * @brief Destroys this @c Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    ~Notebook();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Notebook into this @c %Notebook.
     *
     * @param other The @c %Notebook from which to copy all values.
     *
     * @return A reference to this @c %Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    Notebook& operator=(const Notebook &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator indicates whether the provided @c Notebook contains the same name and attributes as this
     * @c %Notebook.  The purpose of this operator is to compare only the user-editable contents of the two @c %Notebook
     * objects; other fields, such as ID and type, are not considered.
     *
     * To determine whether two @c %Notebook objects represent the same notebook in the database, you should do an
     * equality comparison on the IDs of the two @c %Notebook objects, rather than on the @c %Notebook objects themselves.
     *
     * @param other The @c %Notebook to compare to this one for equality of name and attributes.
     *
     * @return @c true if the provided @c %Notebook has the same name and attributes as this @c %Notebook, @c false otherwise.
     *
     * @see NotebookId::operator==()
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const Notebook &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator indicates whether the provided @c Notebook contains a different name or different attributes than
     * this @c %Notebook.  The purpose of this operator is to compare only the user-editable contents of the two @c %Notebook
     * objects; other fields, such as ID and type, are not considered.
     *
     * To determine whether two @c %Notebook objects represent different notebooks in the database, you should do an
     * inequality comparison on the IDs of the two @c %Notebook objects, rather than on the @c %Notebook objects themselves.
     *
     * @param other The @c %Notebook to compare to this one for inequality of name or attributes.
     *
     * @return @c true if the provided @c %Notebook has a different name or different attributes than this @c %Notebook,
     * @c false otherwise.
     *
     * @see NotebookId::operator!=()
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const Notebook &other) const;

    /*!
     * @brief Indicates whether this @c Notebook is valid.
     *
     * @details A default-constructed @c %Notebook is considered invalid until at least one of its values is set.  You
     * should use this function to determine if a @c %Notebook is valid before you use it.  For example, if you call
     * @c NotebookService::notebook() to retrieve a @c %Notebook but you provide a non-existent ID, the @c %Notebook
     * object that is returned will be invalid.
     *
     * @return @c true if this @c %Notebook is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Indicates whether this @c Notebook or its @c NotebookEntry objects can be edited.
     *
     * @details Some system-created notebooks do not allow their contents (including their notebook entries) to be changed
     * in any way.  Any attempt to update this type of @c %Notebook or its @c %NotebookEntry objects by using @c NotebookService
     * will result in that operation being rejected with an appropriate error code (see the individual @c NotebookService
     * functions for details on which error code is returned).  You should query this function to determine whether an
     * operation is supported before attempting to invoke that operation, and UIs should query this function to determine
     * whether to present such operations to the user.
     *
     * A read-only @c %Notebook does not allow the following operations to take place:
     * - Updating the @c %Notebook using @c NotebookService::updateNotebook().
     * - Deleting the @c %Notebook using @c NotebookService::deleteNotebook().
     * - Adding a @c %NotebookEntry to the @c %Notebook using @c NotebookService::addNotebookEntry().
     * - Moving a @c %NotebookEntry to the @c %Notebook using @c NotebookService::updateNotebookEntry().
     * - Updating a @c %NotebookEntry in the @c %Notebook using @c NotebookService::updateNotebookEntry().
     * - Moving a @c %NotebookEntry out of the @c %Notebook using @c NotebookService::updateNotebookEntry().
     * - Deleting a @c %NotebookEntry from the @c %Notebook using @c NotebookService::deleteNotebookEntry().
     *
     * @return @c true if this @c %Notebook is read-only, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isReadOnly() const;

    /*!
     * @brief Indicates whether this @c Notebook can be deleted.
     *
     * @details Some system-created notebooks do not allow themselves to be deleted.  Any attempt to delete this type of
     * @c %Notebook using @c NotebookService::deleteNotebook() will be rejected with an error code of
     * @c NotebookServiceResult::OperationNotAllowed.  You should query this function before attempting to delete a
     * @c %Notebook, and UIs should query this function to determine whether to present a delete operation to the user.
     *
     * Note that unlike @c Notebook::isReadOnly(), this constraint does not affect the @c NotebookEntry objects that this
     * @c %Notebook contains.  Thus, a @c %Notebook that is not deletable may still have its @c NotebookEntry objects
     * deleted (as long as the @c %Notebook is not also read-only).
     *
     * @return @c true if this @c %Notebook is deletable, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isDeletable() const;

    /*!
     * @brief Indicates whether new @c NotebookEntry objects can be added or moved to this @c Notebook.
     *
     * @details Notebook entries cannot be added or moved to some system-created notebooks.  Any attempt to add or move
     * an entry to these notebooks via @c NotebookService::addNotebookEntry() will be rejected with an error code
     * of @c NotebookServiceResult::ParentNotebookNotAllowed.  You should query this function before attempting to add or
     * move a notebook entry to a notebook, and UIs should query this function to determine whether to present an add or
     * move operation to the user.
     *
     * @return @c true if @c %NotebookEntry objects can be added or moved to this @c %Notebook, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool allowAddNotebookEntry() const;

    /*!
     * @brief Indicates whether this @c Notebook has the provided constraint.
     *
     * @details Some system-created notebooks have constraints on their properties.  These are soft constraints, meaning
     * that invocations of @c NotebookService::updateNotebook() will not fail if the constraints are violated.  Instead,
     * those portions of the update that violate a constraint will be ignored.
     *
     * For example, consider a @c %Notebook whose name is not editable.  If an update is done on that @c %Notebook where
     * its name is changed and an attribute is added, then the new attribute will be persisted but the new name will not.
     *
     * You can use this function to determine how to present an edit UI to the user.  For example, given a @c %Notebook
     * whose name is not editable, the edit UI should prevent the user from editing the name instead of letting
     * @c NotebookService silently enforce that constraint.
     *
     * @param constraint The constraint being checked.
     *
     * @return @c true if this @c %Notebook has the provided constraint, @c false otherwise.
     *
     * @see NotebookService::updateNotebook()
     *
     * @since BlackBerry 10.0.0
     */
    bool hasConstraint(NotebookConstraint::Type constraint) const;

    /*!
     * @brief Indicates whether this @c Notebook imposes the provided constraint on its notebook entries.
     *
     * @details Some system-created notebooks impose constraints the properties of their contained @c NotebookEntry objects.
     * These are soft constraints, meaning that invocations of @c NotebookService::addNotebookEntry() and
     * @c NotebookService::updateNotebookEntry() will not fail if the constraints are violated.  Instead, those portions of
     * the add or update operations that violate a constraint will be ignored or made to agree with the violated constraint.
     *
     * For example, consider a @c %Notebook that imposes the constraint that the statuses of its @c %NotebookEntry objects
     * must be "not actionable".  If a @c %NotebookEntry with an actionable status (that is, "not completed" or "completed")
     * is added to this type of @c %Notebook, then its status will be persisted as "not actionable".
     *
     * You can use this function to determine how to present an add or edit UI to the user.  For example, given a
     * @c %NotebookEntry that does not support attachments, the add or edit UI should prevent the user from manipulating
     * attachments instead of letting @c NotebookService silently enforce that constraint.
     *
     * @param constraint The notebook entry constraint being checked.
     *
     * @return @c true if this @c %Notebook has the provided constraint on its notebook entries, @c false otherwise.
     *
     * @see NotebookService::addNotebookEntry(), NotebookService::updateNotebookEntry()
     *
     * @since BlackBerry 10.0.0
     */
    bool hasNotebookEntryConstraint(NotebookEntryConstraint::Type constraint) const;

    /*!
     * @brief Retrieves the ID of this @c Notebook.
     *
     * @details The ID uniquely identifies a @c %Notebook in a particular account.  The ID is assigned automatically
     * by the database when a @c %Notebook is added using the @c NotebookService.  You can't set the ID of a
     * @c %Notebook manually.
     *
     * @return The ID of this @c %Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookId id() const;

    /*!
     * @brief Retrieves the type of this @c Notebook.
     *
     * @details The types of notebooks are described in the @c Notebook::Type enumeration.
     *
     * @return The type of this @c %Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    Type type() const;

    /*!
     * @brief Retrieves the domain of this @c Notebook.
     *
     * @details The domains of notebooks are described in the @c NotebookDomain::Type enumeration.
     *
     * @return The domain of this @c %Notebook.
     *
     * @since BlackBerry 10.3.0
     */
    NotebookDomain::Type domain() const;

    /*!
     * @brief Sets the name for this @c Notebook.
     *
     * @param name The new name for this @c %Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    void setName(const QString &name);

    /*!
     * @brief Retrieves the name of this @c Notebook.
     *
     * @return The name of this @c %Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Sets the notebook domain that this @c Notebook will support.
     *
     * @param domain the new domain for this @c %Notebook.
     *
     * @details This can only be set when creating a new @c Notebook. Any attempts to edit this
     * will silently fail.
     *
     * @since BlackBerry 10.3.0
     */
    void setDomain(NotebookDomain::Type domain);

    /*!
     * @brief Sets an attribute to the given value for this key for this @c Notebook.
     *
     * @details You can set your own attributes on a @c %Notebook and these attributes will be persisted
     * for later use.
     *
     * @param key The key of the attribute.
     * @param value The value of the attribute.
     *
     * @since BlackBerry 10.0.0
     */
    void setAttribute(const QString &key, const QString &value);

    /*!
     * @brief Resets the value of the attribute with the provided key to a null @c QString.
     *
     * @param key The key of the attribute whose value is to be reset.
     *
     * @since BlackBerry 10.0.0
     */
    void resetAttribute(const QString &key);

    /*!
     * @brief Retrieves an attribute from this @c Notebook.
     *
     * @details You can retrieve an attribute that was previously set on this @c %Notebook.
     *
     * @param key The key of the attribute to retrieve.
     *
     * @return The value of the attribute, or a null (default-constructed) @c QString if no attribute value
     * exists for this key.
     *
     * @since BlackBerry 10.0.0
     */
    QString attribute(const QString &key) const;

    /*!
     * @brief Retrieves all the attributes for this @c Notebook.
     *
     * @details You can retrieve a @c QMap representing all attributes that are set on this
     * @c %Notebook.
     *
     * @return A @c QMap of all attributes set on this @c %Notebook.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QString> attributes() const;

private:
    QSharedDataPointer<NotebookPrivate> d_ptr;
    friend class NotebookPrivate;
};

} // namespace notebook
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::notebook::Notebook)
#endif // BB_PIM_NOTEBOOK_NOTEBOOK_HPP
