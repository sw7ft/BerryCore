/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRY_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRY_HPP

#include <bb/pim/Global>

#include <bb/pim/notebook/NotebookEntryAttachment>
#include <bb/pim/notebook/NotebookEntryDescription>
#include <bb/pim/notebook/NotebookEntryStatus>

#include <QDateTime>
#include <QList>
#include <QMetaType>
#include <QSharedDataPointer>
#include <QString>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookEntryPrivate;
class NotebookEntryId;
class NotebookId;
class NotebookRecurrence;

/*!
 * @headerfile NotebookEntry.hpp <bb/pim/notebook/NotebookEntry>
 *
 * @brief The @c NotebookEntry class represents an entry that is contained within a @c Notebook.
 *
 * @details A @c %NotebookEntry is a single "thought" or "action" that a user wants to track. Each
 * @c %NotebookEntry is contained by exactly one @c %Notebook, allowing them to be grouped together as
 * the user sees fit.
 *
 * Each @c %NotebookEntry has a status. It can be non-actionable (a "thought" that doesn't require
 * any action on the part of the user) or actionable (an "action" the user intends to take by a
 * certain date and time). Actionable @c %NotebookEntry objects are either completed or not completed.
 * For more information, see the @c NotebookEntryStatus::Type enumeration. Actionable @c %NotebookEntry
 * objects can have a due date and/or a reminder.
 *
 * A @c %NotebookEntry can be augmented with attachments, which are displayed within the Remember application,
 * leading to a richer user experience. See the @c NotebookEntryAttachment class for information on what attachment
 * MIME types are supported natively by the Remember application.  You can add attachments with
 * arbitrary MIME types to be handled by their own applications, but the Remember application will ignore
 * MIME types that it does not recognize.
 *
 * Example usage:
 * @code
 *   // Here's how to create an actionable NotebookEntry with a title and due date,
 *   // and add it to the default Notebook.  Note that service objects are
 *   // potentially expensive to initialize, so you should not create them on a
 *   // per-use basis as is done below.
 *   NotebookService service;
 *   NotebookEntry entry;
 *   entry.setTitle( "New NotebookEntry" );
 *   entry.setStatus( NotebookEntryStatus::NotCompleted );
 *   entry.setDueDateTime( QDateTime::currentDateTime().addDays( 1 ) );
 *   NotebookId notebookId = service.defaultNotebook().id();
 *
 *   // You should be sure to check the return code from addNotebookEntry() for
 *   // success
 *   service.addNotebookEntry( &entry, notebookId );
 * @endcode
 *
 * @see Notebook, NotebookEntryAttachment, NotebookEntryStatus
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntry
{

public:

    /*!
     * @brief Constructs a new @c NotebookEntry with default values.
     *
     * @details A default-constructed @c %NotebookEntry is considered invalid until at least one of its values is set.
     * You can determine whether a @c %NotebookEntry is valid by calling @c isValid().
     *
     * @see isValid()
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntry();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c %NotebookEntry containing exactly the same values as the provided
     * @c %NotebookEntry.
     *
     * @param other The @c %NotebookEntry to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntry(const NotebookEntry &other);

    /*!
     * @brief Destroys this @c NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    ~NotebookEntry();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c NotebookEntry into this @c %NotebookEntry.
     *
     * @param other The @c %NotebookEntry from which to copy all values.
     *
     * @return A reference to this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntry& operator=(const NotebookEntry &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator indicates whether the provided @c NotebookEntry contains the same title, description, due
     * date/time, status, reminder, recurrence and attachments as this @c %NotebookEntry.
     * The purpose of this operator is to compare only the
     * user-editable contents of the two @c %NotebookEntry objects; other fields, such as ID and creation date/time, are
     * not considered.
     *
     * To determine whether two @c %NotebookEntry objects represent the same notebook entry in the database, you should
     * do an equality comparison on the IDs of the two @c %NotebookEntry objects, rather than on the @c %NotebookEntry objects
     * themselves.
     *
     * @param other The @c %NotebookEntry to compare to this one for equality of user-editable contents.
     *
     * @return @c true if the provided @c %NotebookEntry has the same user-editable contents as this @c %NotebookEntry,
     * @c false otherwise.
     *
     * @see NotebookEntryId::operator==()
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const NotebookEntry &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator indicates whether the provided @c NotebookEntry contains a different title, description, due
     * date/time, status, reminder, recurrence or attachments than this @c %NotebookEntry.
     * The purpose of this operator is to compare only the
     * user-editable contents of the two @c %NotebookEntry objects; other fields, such as ID and creation date/time, are
     * not considered.
     *
     * To determine whether two @c %NotebookEntry objects represent different notebook entries in the database, you should
     * do an inequality comparison on the IDs of the two @c %NotebookEntry objects, rather than on the @c %NotebookEntry objects
     * themselves.
     *
     * @param other The @c %NotebookEntry to compare to this one for inequality of user-editable contents.
     *
     * @return @c true if the provided @c %NotebookEntry has different user-editable contents than this @c %NotebookEntry,
     * @c false otherwise.
     *
     * @see NotebookEntryId::operator!=()
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const NotebookEntry &other) const;

    /*!
     * @brief Indicates whether this @c NotebookEntry is valid.
     *
     * @details A default-constructed @c %NotebookEntry is considered invalid until at least one of its values is set.
     * You should use this function to determine if a @c %NotebookEntry is valid before you use it.  For example, if
     * you call @c NotebookService::notebookEntry() to retrieve a @c %NotebookEntry but you provide a non-existent ID,
     * the @c %NotebookEntry object that is returned will be invalid.
     *
     * @return @c true if this @c %NotebookEntry is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the ID of this @c NotebookEntry.
     *
     * @details The ID uniquely identifies a @c %NotebookEntry in a particular account.  The ID is assigned automatically
     * by the database when a @c %NotebookEntry is added using the @c NotebookService.  You can't set the ID of a
     * @c %NotebookEntry manually.
     *
     * @return The ID of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryId id() const;

    /*!
     * @brief Retrieves the parent notebook ID of this @c NotebookEntry.
     *
     * @details A @c %NotebookEntry is contained by the @c Notebook whose ID matches the notebook ID of the
     * @c %NotebookEntry. Thus, this function is used to determine which @c %Notebook this @c %NotebookEntry
     * belongs to.
     *
     * @return The parent notebook ID of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookId parentNotebookId() const;

    /*!
     * @brief Sets the title for this @c NotebookEntry.
     *
     * @param title The new title for this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void setTitle(const QString &title);

    /*!
     * @brief Retrieves the title of this @c NotebookEntry.
     *
     * @return The title of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Sets the description for this @c NotebookEntry.
     *
     * @param description The new description for this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void setDescription(const NotebookEntryDescription &description);

    /*!
     * @brief Retrieves the description of this @c NotebookEntry.
     *
     * @return The description of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryDescription description() const;

    /*!
     * @brief Retrieves the creation date and time of this @c NotebookEntry.
     *
     * @details A @c %NotebookEntry is automatically assigned a creation date and time when it is first
     * committed to persistence using the @c NotebookService.  The creation date and time cannot be changed
     * using the Notebook API.
     *
     * @return The creation date and time of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime creationDateTime() const;

    /*!
     * @brief Retrieves the last modified date and time of this @c NotebookEntry.
     *
     * @details A @c %NotebookEntry is automatically assigned a last modified date and time when it is first
     * committed to persistence using the @c NotebookService.  This is automatically updated each time it is
     * modified. The last modified date and time cannot be changed using the Notebook API.
     *
     * @return The last modified date and time of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime lastModifiedDateTime() const;

    /*!
     * @brief Sets the due date and time for this @c NotebookEntry.
     *
     * @param dueDateTime The new due date and time for this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void setDueDateTime(const QDateTime &dueDateTime);

    /*!
     * @brief Resets the due date and time for this @c NotebookEntry.
     *
     * @details This is equivalent to invoking @c setDueDateTime() with a null @c QDateTime object.
     *
     * @since BlackBerry 10.0.0
     */
    void resetDueDateTime();

    /*!
     * @brief Retrieves the due date and time of this @c NotebookEntry.
     *
     * @return The due date and time of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime dueDateTime() const;

    /*!
     * @brief Sets the reminder date and time for this @c NotebookEntry.
     *
     * @param reminderTime The new reminder date and time for this @c %NotebookEntry.
     *
     * @since BlackBerry 10.2.0
     */
    void setReminderTime(const QDateTime &reminderTime);

    /*!
     * @brief Resets the reminder date and time for this @c NotebookEntry.
     *
     * @details This is equivalent to invoking @c setReminderTime() with a null @c QDateTime object.
     *
     * @since BlackBerry 10.2.0
     */
    void resetReminderTime();

    /*!
     * @brief Retrieves the reminder date and time of this @c NotebookEntry.
     *
     * @return The reminder date and time of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime reminderTime() const;

    /*!
     * @brief Sets the status for this @c NotebookEntry.
     *
     * @param status The new status for this @c %NotebookEntry
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(NotebookEntryStatus::Type status);

    /*!
     * @brief Retrieves the status of this @c NotebookEntry.
     *
     * @return The status of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryStatus::Type status() const;

    /*!
     * @brief Appends an attachment to the list of attachments for this @c NotebookEntry.
     *
     * @param attachment The attachment to append to the list of attachments for this
     * @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void addAttachment(const NotebookEntryAttachment &attachment);

    /*!
     * @brief Appends a list of attachments for this @c NotebookEntry.
     *
     * @param attachments The attachments to add to this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void addAttachments(const QList<NotebookEntryAttachment> &attachments);

    /*!
     * @brief Retrieves the attachments of this @c NotebookEntry.
     *
     * @return The attachments of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    QList<NotebookEntryAttachment> attachments() const;

    /*!
     * @brief Removes an attachment from the list of attachments for this @c NotebookEntry.
     *
     * @details All attachments whose MIME type and data ID match those of the provided attachment
     * are removed.
     *
     * @param attachment The attachment to be removed from the list of attachments for this
     * @c %NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void removeAttachment(const NotebookEntryAttachment &attachment);

    /*!
     * @brief Removes all attachments from the list of attachments for this @c NotebookEntry.
     *
     * @since BlackBerry 10.0.0
     */
    void resetAttachments();

    /*!
     * @brief Sets the recurrence information for this @c NotebookEntry.
     *
     * @param recurrence The recurrence object to be set for this @c %NotebookEntry.
     *
     * @since BlackBerry 10.3.1
     */
    void setRecurrence(const NotebookRecurrence& recurrence);

    /*!
     * @brief Gets the recurrence information for this @c NotebookEntry.
     *
     * @details The only entries that can have a recurrence rule are actionable entries
     * from an @c bb::pim::account::Account that supports task recurrence.
     * You can check the recurrence support for an account by calling
     * @c bb::pim::Account::capabilitiesProperty() with "supports_tasks_recurrence"
     * as the argument.
     *
     * @return The recurrence object of this @c %NotebookEntry.
     *
     * @since BlackBerry 10.3.1
     */
    NotebookRecurrence recurrence() const;

private:
    QSharedDataPointer<NotebookEntryPrivate> d_ptr;
    friend class NotebookEntryPrivate;
};

} // namespace notebook
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::notebook::NotebookEntry)

#endif // BB_PIM_NOTEBOOK_NOTEBOOKENTRY_HPP
