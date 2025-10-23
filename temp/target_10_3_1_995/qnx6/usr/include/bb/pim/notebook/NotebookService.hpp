/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKSERVICE_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKSERVICE_HPP

#include <bb/pim/Global>

#include <bb/pim/account/Account>
#include <bb/pim/notebook/Notebook>
#include <bb/pim/notebook/NotebookEntry>
#include <bb/pim/notebook/NotebookEntryId>
#include <bb/pim/notebook/NotebookEntryFilter>
#include <bb/pim/notebook/NotebookEntryHeader>
#include <bb/pim/notebook/NotebookFilter>
#include <bb/pim/notebook/NotebookServiceResult>

#include <QtCore/QList>
#include <QtCore/QObject>
#include <limits.h>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookServicePrivate;

/**
 * @brief This represents the revision of the Notebooks database
 *
 * @details The revision gets incremented anytime an add, update, or delete occurs on a @c NotebookEntry
 *
 * @since BlackBerry 10.2.0
 */
typedef quint64 SourceRevision;

/*!
 * @headerfile NotebookService.hpp <bb/pim/notebook/NotebookService>
 *
 * @brief The @c NotebookService class provides CRUD (create/read/update/delete) operations on @c Notebook objects
 * and their @c NotebookEntry objects.
 *
 * @details @c %NotebookService is domain-level API that abstracts away all persistence details.  Clients of this
 * API need only deal with @c %Notebook and @c %NotebookEntry objects; all object-relational mapping is handled behind
 * the scenes.  Functions are provided for adding, retrieving, updating, and deleting @c %Notebook objects and
 * @c %NotebookEntry objects, as well as for searching and counting @c %NotebookEntry objects based on criteria
 * specified in a @c NotebookEntryFilter.
 *
 * Signals are provided for clients that want to respond to changes in the underlying database, and indicate when a
 * @c %Notebook or @c %NotebookEntry has been added, updated, or deleted.
 *
 * Example usage:
 * @code
 *   // Here's how to add a new Notebook to the default Notebook account, and add
 *   // a NotebookEntry to the new Notebook.  Note that service objects are
 *   // potentially expensive to initialize, so you should not create them on a
 *   // per-use basis as is done below.
 *   AccountKey accountKey = AccountService().defaultAccount( Service::Notebook )
 *                                           .id();
 *   NotebookService service;
 *
 *   Notebook notebook;
 *   notebook.setName( "New Notebook" );
 *
 *   // You should be sure to check the return code from addNotebook() for
 *   // success
 *   service.addNotebook( &notebook, accountKey );
 *
 *   NotebookEntry entry;
 *   entry.setTitle( "New NotebookEntry" );
 *
 *   // A notebook must have been added to the notebook service before its ID
 *   // can be used below
 *   NotebookId notebookId = notebook.id();
 *
 *   // You should be sure to check the return code from addNotebookEntry() for
 *   // success
 *   service.addNotebookEntry( &entry, notebookId );
 * @endcode
 *
 * @see Notebook, NotebookEntry
 *
 * @permissions To use the @c NotebookService class in your application, you
 * must enable the following permission in your application's bar-descriptor.xml file: @c access_pimdomain_notebooks.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookService : public QObject
{
    Q_OBJECT

public:

    /*!
     * @brief Predefined @c SourceRevision value.
     *
     * @since BlackBerry 10.2.0
     */
    enum RevisionValue {
        /*!
         * @brief Specifies an invalid @c SourceRevision.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidRevision = ULLONG_MAX
    };

    /*!
     * @brief Constructs a new @c NotebookService with the provided parent.
     *
     * @details You don't need to provide a parent when you construct a @c %NotebookService object. If you don't
     * provide a parent, the default value is 0.
     *
     * @param parent The parent of the @c %NotebookService, or 0 if no parent is provided.
     *
     * @since BlackBerry 10.0.0
     */
    explicit NotebookService(QObject *parent = 0);

    /*!
     * @brief Destroys this @c NotebookService.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~NotebookService();

    /*!
     * @brief Adds a new @c Notebook to the provided account in the database.
     *
     * @details If the provided @c %Notebook is successfully added to the database, its ID is updated to match
     * the ID assigned to it by the database, and the @c notebooksAdded() signal is emitted.  If the addition fails,
     * the ID of the @c %Notebook is made invalid (@c NotebookId::isValid() will return @c false) and no
     * signal is emitted.
     *
     * @param newNotebook The @c %Notebook to be added to the database.  If the @c %Notebook is added successfully,
     * the ID of the @c %Notebook is set.  Otherwise, the ID of the @c %Notebook is made invalid.
     * @param accountKey The account to which the provided @c %Notebook should be added.
     *
     * @return @c NotebookServiceResult::Success if the addition succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the provided account key represents a non-existent or
     *   inaccessible account.
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::NotebookNotSupported if the function failed @c %Notebook was added to an account
     *   that does not support that kind of @c Notebook.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookServiceResult::Type addNotebook(Notebook *newNotebook, bb::pim::account::AccountKey accountKey);

    /*!
     * @brief Updates a @c Notebook in the database.
     *
     * @details The contents of the @c %Notebook in the database are replaced with the contents of the provided
     * @c %Notebook, except for those fields that are not user editable or whose new value violates a
     * @c NotebookConstraint.  Such fields are silently ignored during the update.  For example, no @c %Notebook
     * can have its type changed by this function.  Similarly, a @c %Notebook that has the @c NotebookConstraint::NameNotEditable
     * constraint cannot have its name changed by this function.
     *
     * If the update is successful, the @c notebooksUpdated() signal is emitted. If the update fails,
     * no signal is emitted.
     *
     * @param updatedNotebook The @c %Notebook to be updated in the database.
     *
     * @return @c NotebookServiceResult::Success if the update succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the account key of the provided @c %Notebook represents a
     *   non-existent or inaccessible account.
     * - @c NotebookServiceResult::NonExistentNotebook if the account key of the provided @c %Notebook is valid, but
     *   its notebook key was not found in that account.
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookServiceResult::Type updateNotebook(const Notebook &updatedNotebook);

    /*!
     * @brief Deletes a @c Notebook and all of its contained @c NotebookEntry objects from the database.
     *
     * @details If the deletion of the @c %Notebook with the provided ID is successful, the @c notebooksDeleted()
     * signal is emitted, as well a single @c notebookEntriesDeleted() signal for all of its @c %NotebookEntry objects.
     * If the deletion fails, no signals are emitted.
     *
     * @note Some @c %Notebook objects cannot be deleted (this can be verified by querying the @c Notebook::isDeletable()
     * function).  Attempting to delete such a @c %Notebook will fail as outlined below.
     *
     * @param notebookId The ID of the @c %Notebook to be deleted.
     *
     * @return @c NotebookServiceResult::Success if the deletion succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the account key of the provided @c %Notebook represents a
     *   non-existent or inaccessible account.
     * - @c NotebookServiceResult::NonExistentNotebook if the account key of the provided @c %Notebook is valid, but its
     *   notebook key was not found in that account.
     * - @c NotebookServiceResult::OperationNotAllowed if the @c %Notebook being deleted is not deletable.
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookServiceResult::Type deleteNotebook(const NotebookId &notebookId);

    /*!
     * @brief Retrieves the default @c Notebook for the personal perimeter.
     *
     * @details The default @c %Notebook cannot be deleted.  Since this @c %Notebook is guaranteed
     * to exist, applications can use it as a "catch all", placing newly created @c NotebookEntry objects there if the
     * user does not choose a specific @c %Notebook as a destination.
     *
     * @return The default @c %Notebook for the personal perimeter.
     *
     * @since BlackBerry 10.0.0
     */
    Notebook defaultNotebook() const;

    /*!
     * @brief Retrieves the default tasks @c Notebook for the personal perimeter.
     *
     * @details The default tasks @c %Notebook cannot be deleted.  Since this @c %Notebook is guaranteed
     * to exist, applications can use it as a "catch all", placing newly created actionable @c NotebookEntry
     * objects there if the user does not choose a specific @c %Notebook as a destination.
     *
     * @return The default tasks @c %Notebook for the personal perimeter.
     *
     * @since BlackBerry 10.3.0
     */
    Notebook defaultTasksNotebook() const;

    /*!
     * @brief Retrieves the default notes @c Notebook for the personal perimeter.
     *
     * @details The default notes @c %Notebook cannot be deleted.  Since this @c %Notebook is guaranteed
     * to exist, applications can use it as a "catch all", placing newly created non-actionable @c NotebookEntry
     * objects there if the user does not choose a specific @c %Notebook as a destination.
     *
     * @return The default notes @c %Notebook for the personal perimeter.
     *
     * @since BlackBerry 10.3.0
     */
    Notebook defaultNotesNotebook() const;

    /*!
     * @brief Retrieves the @c Notebook with the provided ID.
     *
     * @details If no @c %Notebook exists with the provided ID, an invalid @c %Notebook is returned.  You should
     * check the @c Notebook::isValid() function of the returned @c %Notebook to ensure it is valid before using
     * it.
     *
     * @param notebookId The ID of the @c %Notebook to be retrieved.
     *
     * @return The @c %Notebook with the provided ID if it exists, or an invalid @c %Notebook otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Notebook notebook(const NotebookId &notebookId) const;

    /*!
     * @brief Retrieves all @c Notebook objects in all accessible accounts.
     *
     * @return A @c QList of @c %Notebook objects, in no particular order.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Notebook> notebooks() const;

    /*!
     * @brief Retrieves all @c Notebook objects in all accessible accounts, using the NotebookFilter
     *
     * @param filter the filter to use when retrieving a @c QList of @c %Notebooks.
     *
     * @return A @c QList of filtered @c %Notebook objects, in no particular order.
     *
     *
     * @since BlackBerry 10.3.0
     */
    QList<Notebook> notebooks(const NotebookFilter & filter) const;

    /*!
     * @brief Retrieves a list of allowed parent @c Notebook objects for the @c NotebookEntry with the provided ID.
     *
     * @details Each @c %NotebookEntry belongs to (or is parented by) exactly one @c %Notebook at any given time.  You
     * can use this function to retrieve a list of allowed parent @c %Notebook objects for a @c %NotebookEntry, both
     * when creating a new @c %NotebookEntry and when moving a @c %NotebookEntry between parent @c %Notebook objects.
     *
     * You can invoke this function with an invalid @c NotebookEntryId argument (or omit the argument altogether) to
     * retrieve a list of allowed parent @c %Notebook objects for a new @c %NotebookEntry.  However, since a @c
     * %NotebookEntry has an invalid ID before being added to the @c NotebookService, it is generally not necessary to
     * omit the @c %NotebookEntryId argument.  By using this approach, you do not have to invoke this function in
     * different ways when adding a new @c %NotebookEntry and when moving an existing @c %NotebookEntry between parent
     * @c %Notebook objects.
     *
     * @c %NotebookEntry objects can generally be moved between parent @c %Notebook objects.  However, some @c %NotebookEntry
     * objects have restrictions on which @c %Notebook objects they can be parented by.  For example, @c %NotebookEntry
     * objects in an ActiveSync Memo @c %Notebook cannot be moved to a non-ActiveSync Memo @c %Notebook, and vice versa.
     * Before moving a @c %NotebookEntry to a different @c %Notebook, you can use this function to retrieve a list of
     * allowed destinations.
     *
     * @param entryId The ID of the @c %NotebookEntry whose allowed parent @c %Notebook objects are to be retrieved.  If
     * this parameter is invalid or is omitted, a list of all @c %Notebook objects that allow new @c %NotebookEntry
     * objects is returned.
     *
     * @return A @c QList of allowed parent @c %Notebook objects for the provided @c %NotebookEntryId, in no particular
     * order.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Notebook> allowedParentNotebooks(const NotebookEntryId &entryId = NotebookEntryId()) const;

    /*!
     * @brief Adds a new @c NotebookEntry to the database.
     *
     * @details The provided @c %NotebookEntry is added to the @c Notebook that's specified by its parent notebook ID.
     * If the provided @c %NotebookEntry is successfully added, the @c NotebookEntryKey portion of its @c
     * NotebookEntryId is updated to match the key assigned to it by the database, and the @c notebookEntriesAdded() signal
     * is emitted.  If the addition fails, the @c %NotebookEntryId is made invalid (@c NotebookEntryId::isValid()
     * will return @c false) and no signal is emitted.
     *
     * @param newNotebookEntry The @c %NotebookEntry to be added to the database.
     * @param parentNotebookId The ID of the @c %Notebook to which the @c %NotebookEntry should be added.
     *
     * @return @c NotebookServiceResult::Success if the addition succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the @c %NotebookEntry was added to a @c %Notebook in an
     *   inaccessible account.
     * - @c NotebookServiceResult::NonExistentNotebook if the @c %NotebookEntry was added to a non-existent @c %Notebook.
     * - @c NotebookServiceResult::ParentNotebookNotAllowed if the @c %NotebookEntry was added to a @c %Notebook that does
     *   not allow new entries.
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @see NotebookService::allowedParentNotebooks()
     *
     * @since BlackBerry 10.0.0
     */
    NotebookServiceResult::Type addNotebookEntry(NotebookEntry *newNotebookEntry, const NotebookId &parentNotebookId);

    /*!
     * @brief Updates and/or moves a @c NotebookEntry in the database.
     *
     * @details The contents of the @c %NotebookEntry in the database are replaced with the contents of the provided
     * @c %NotebookEntry, except for those fields that are not user editable or whose new value violates a
     * @c NotebookEntryConstraint.  Such fields are silently ignored during the update.  For example, no @c %NotebookEntry
     * can have its creation date/time changed by this function.  Similarly, a @c %NotebookEntry whose parent @c Notebook
     * has the @c NotebookEntryConstraint::MustBeActionable constraint cannot have its status set to
     * @c NotebookEntryStatus::NotActionable with this function.
     *
     * You can move the provided @c %NotebookEntry to a different parent @c %Notebook by providing the new parent @c %Notebook
     * object's ID as the second argument to this function.  If this argument is omitted or is not valid, the @c
     * %NotebookEntry is not moved.  Before moving a @c %NotebookEntry to a different parent @c %Notebook, you should first
     * query @c allowedParentNotebooks() to ensure the move is allowed.  A move to a disallowed or non-existent @c %Notebook
     * will fail.
     *
     * If the update is successful, the @c notebookEntriesUpdated() signal is emitted.  If the update fails,
     * no signal is emitted.
     *
     * @param updatedNotebookEntry The @c %NotebookEntry to be updated in the database.
     * @param parentNotebookId The ID of the parent @c %Notebook to which the provided @c %NotebookEntry should be moved.
     *  If this parameter is omitted, the @c %NotebookEntry is not moved.
     *
     * @return @c NotebookServiceResult::Success if the update succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the account key of either the provided @c %NotebookEntry, or
     *   its parent @c %Notebook, represents a non-existent or inaccessible account.
     * - @c NotebookServiceResult::NonExistentNotebook if the account key of the parent @c %Notebook of the provided
     *   @c %NotebookEntry is valid, but its @c %Notebook key was not found in that account.
     * - @c NotebookServiceResult::NonExistentNotebookEntry if the account key of the provided @c %NotebookEntry is valid,
     *   but its @c %NotebookEntry key was not found in that account.
     * - @c NotebookServiceResult::ParentNotebookNotAllowed if the parent @c %Notebook ID of the @c %NotebookEntry was set
     *   to a @c %Notebook that is disallowed by @c NotebookService::allowedParentNotebooks().
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @see NotebookService::allowedParentNotebooks()
     *
     * @since BlackBerry 10.0.0
     */
    NotebookServiceResult::Type updateNotebookEntry(const NotebookEntry &updatedNotebookEntry, const NotebookId &parentNotebookId = NotebookId());

    /*!
     * @brief Deletes a @c NotebookEntry from the database.
     *
     * @details If the deletion of the @c %NotebookEntry with the provided ID is successful, the @c notebookEntriesDeleted()
     * signal is emitted.  If the deletion fails, no signal is emitted.
     *
     * @param entryId The ID of the @c %NotebookEntry to be deleted.
     *
     * @return @c NotebookServiceResult::Success if the deletion succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the account key of the provided @c %NotebookEntryId represents a
     *   non-existent or inaccessible account.
     * - @c NotebookServiceResult::NonExistentNotebookEntry if the account key of the provided @c %NotebookEntryId is valid,
     *   but its @c %NotebookEntry key was not found in that account.
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookServiceResult::Type deleteNotebookEntry(const NotebookEntryId &entryId);

    /*!
     * @brief Retrieves the @c NotebookEntry with the provided ID.
     *
     * @details If no @c %NotebookEntry exists with the provided ID, an invalid @c %NotebookEntry is returned.  You
     * should check the @c NotebookEntry::isValid() function of the returned @c %NotebookEntry to ensure it is valid
     * before using it.
     *
     * @param entryId The ID of the @c %NotebookEntry to be retrieved.
     *
     * @return The @c %NotebookEntry with the provided ID if it exists, or an invalid @c %NotebookEntry otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntry notebookEntry(const NotebookEntryId &entryId) const;

    /*!
     * @brief Retrieves the @c NotebookEntry objects that match the criteria set in the provided @c NotebookEntryFilter.
     *
     * @details The @c %NotebookEntryFilter parameter can be omitted, in which case a filter that accepts all
     * @c %NotebookEntry objects is used.  Thus, you can invoke this function with no argument to obtain a list of
     * all available @c %NotebookEntry objects.
     *
     * @param filter The @c %NotebookEntryFilter whose criteria must be matched for a @c %NotebookEntry to be included
     * in the returned list. If this parameter is omitted, all available @c %NotebookEntry objects are returned.
     *
     * @return A @c QList of @c %NotebookEntry objects that match the criteria set in the provided @c %NotebookEntryFilter,
     * sorted as specified by the sort specifier included in the filter.
     *
     * @since BlackBerry 10.0.0
     */
    QList<NotebookEntry> notebookEntries(const NotebookEntryFilter &filter = NotebookEntryFilter()) const;

    /*!
     * @brief Retrieves the @c NotebookEntry objects that match the criteria set in the provided @c NotebookEntryFilter.
     *
     * @details The @c %NotebookEntryFilter parameter can be omitted, in which case a filter that accepts all
     * @c %NotebookEntry objects is used.
     *
     * @param revision Returns the current revision of the database. If null, no revision is returned.
     *
     * @param filter The @c %NotebookEntryFilter whose criteria must be matched for a @c %NotebookEntry to be included
     * in the returned list. If this parameter is omitted, all available @c %NotebookEntry objects are returned.
     *
     * @return A @c QList of @c %NotebookEntry objects that match the criteria set in the provided @c %NotebookEntryFilter,
     * sorted as specified by the sort specifier included in the filter.
     *
     * @since BlackBerry 10.2.0
     */
    QList<NotebookEntry> notebookEntries(SourceRevision *revision, const NotebookEntryFilter &filter = NotebookEntryFilter()) const;

    /*!
     * @brief Retrieves the @c NotebookEntryHeader objects that match the criteria set in the provided @c NotebookEntryFilter.
     *
     * @details The @c %NotebookEntryFilter parameter can be omitted, in which case a filter that accepts all
     * @c %NotebookEntry objects is used.
     *
     * @param revision Returns the current revision of the database. If null, no revision is returned.
     *
     * @param filter The @c %NotebookEntryFilter whose criteria must be matched for a @c %NotebookEntryHeader to be included
     * in the returned list. If this parameter is omitted, all available @c %NotebookEntry objects are returned.
     *
     * @return A @c QList of @c %NotebookEntryHeader objects that match the criteria set in the provided @c %NotebookEntryFilter,
     * sorted as specified by the sort specifier included in the filter.
     *
     * @since BlackBerry 10.2.0
     */
    QList<NotebookEntryHeader> notebookEntryHeaders(SourceRevision *revision, const NotebookEntryFilter &filter = NotebookEntryFilter()) const;

    /*!
     * @brief Retrieves the number of @c NotebookEntry objects that match the criteria set in the provided
     * @c NotebookEntryFilter.
     *
     * @details The @c %NotebookEntryFilter parameter can be omitted, in which case a filter that accepts all
     * @c %NotebookEntry objects is used.  Thus, you can invoke this function with no argument to obtain the number of
     * all available @c %NotebookEntry objects.
     *
     * @param filter The @c %NotebookEntryFilter whose criteria must be matched for a @c %NotebookEntry to be included
     * in the returned count. If this parameter is omitted, all available @c %NotebookEntry objects are counted.
     *
     * @return The number of @c %NotebookEntry objects that match the criteria set in the provided @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     */
    int notebookEntryCount(const NotebookEntryFilter &filter = NotebookEntryFilter()) const;

    /*!
     * @brief Retrieves the number of @c NotebookEntry objects that match the criteria set in the provided
     * @c NotebookEntryFilter.
     *
     * @details The @c %NotebookEntryFilter parameter can be omitted, in which case a filter that accepts all
     * @c %NotebookEntry objects is used.
     *
     * @param revision Returns the current revision of the database. If null, no revision is returned.
     *
     * @param filter The @c %NotebookEntryFilter whose criteria must be matched for a @c %NotebookEntry to be included
     * in the returned count. If this parameter is omitted, all available @c %NotebookEntry objects are counted.
     *
     * @return The number of @c %NotebookEntry objects that match the criteria set in the provided @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.2.0
     */
    int notebookEntryCount(SourceRevision *revision, const NotebookEntryFilter &filter = NotebookEntryFilter()) const;

    /*!
     * @brief Sets the status of the @c NotebookEntry identified by the provided @c NotebookEntryId.
     *
     * @param entryId The @c NotebookEntryId of the @c NotebookEntry to set status on.
     * @param status The @c NotebookEntryStatus to set on the @c NotebookEntry.
     *
     * @return @c NotebookServiceResult::Success if the function succeeded, or one of the following error status codes:
     * - @c NotebookServiceResult::InaccessibleAccount if the account key of either the provided @c %NotebookEntryId, or
     *   its parent @c %Notebook, represents a non-existent or inaccessible account.
     * - @c NotebookServiceResult::NonExistentNotebook if the account key of the parent @c %Notebook of the provided
     *   @c %NotebookEntryId is valid, but its @c %Notebook key was not found in that account.
     * - @c NotebookServiceResult::NonExistentNotebookEntry if the account key of the provided @c %NotebookEntryId is valid,
     *   but its @c %NotebookEntry key was not found in that account.
     * - @c NotebookServiceResult::DomainLockedError if the function failed because the domain is hard locked and
     *   the enterprise file system is currently not readable.
     * - @c NotebookServiceResult::InternalError if an unspecified error occurred.
     *
     * @since BlackBerry 10.2.0
     */
    NotebookServiceResult::Type setNotebookEntryStatus(const NotebookEntryId &entryId, NotebookEntryStatus::Type status) const;

Q_SIGNALS:
    /*!
     * @brief Emitted when one or more @c Notebook objects are added to the database.
     *
     * @param notebookIds The IDs of the @c %Notebook objects that were added to the database.
     *
     * @since BlackBerry 10.0.0
     */
    void notebooksAdded(const QList<bb::pim::notebook::NotebookId> &notebookIds);

    /*!
     * @brief Emitted when one or more @c Notebook objects are updated in the database.
     *
     * @param notebookIds The IDs of the @c %Notebook objects that were updated in the database.
     *
     * @since BlackBerry 10.0.0
     */
    void notebooksUpdated(const QList<bb::pim::notebook::NotebookId> &notebookIds);

    /*!
     * @brief Emitted when one or more @c Notebook objects are deleted from the database.
     *
     * @param notebookIds The IDs of the @c %Notebook objects that were deleted from the database.
     *
     * @since BlackBerry 10.0.0
     */
    void notebooksDeleted(const QList<bb::pim::notebook::NotebookId> &notebookIds);

    /*!
     * @brief Emitted when one or more @c NotebookEntry objects are added to the database.
     *
     * @param entryIds The IDs of the @c %NotebookEntry objects that were added to the database.
     *
     * @since BlackBerry 10.0.0
     */
    void notebookEntriesAdded(const QList<bb::pim::notebook::NotebookEntryId> &entryIds);

    /*!
     * @brief Emitted when one or more @c NotebookEntry objects are updated in the database.
     *
     * @param entryIds The IDs of the @c %NotebookEntry objects that were updated in the database.
     *
     * @since BlackBerry 10.0.0
     */
    void notebookEntriesUpdated(const QList<bb::pim::notebook::NotebookEntryId> &entryIds);

    /*!
     * @brief Emitted when one or more @c NotebookEntry objects are deleted from the database.
     *
     * @param entryIds The IDs of the @c %NotebookEntry objects that were deleted from the database.
     *
     * @since BlackBerry 10.0.0
     */
    void notebookEntriesDeleted(const QList<bb::pim::notebook::NotebookEntryId> &entryIds);

    /*!
     * @brief Emitted when one or more @c NotebookEntry objects are added to, updated in, or deleted from the database.
     *
     * @param revision The current @c SourceRevision of the database.
     *
     * @since BlackBerry 10.2.0
     */
    void notebookEntriesChanged(bb::pim::notebook::SourceRevision revision);

private:
    Q_DECLARE_PRIVATE(NotebookService);
    Q_DISABLE_COPY(NotebookService);
    QScopedPointer<NotebookServicePrivate> d_ptr;
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif // BB_PIM_NOTEBOOK_NOTEBOOKSERVICE_HPP
