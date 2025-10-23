/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYFILTER_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYFILTER_HPP

#include <bb/pim/Global>

#include <bb/pim/notebook/Notebook>
#include <bb/pim/notebook/NotebookEntryDetailLevel>
#include <bb/pim/notebook/NotebookEntryDueDate>
#include <bb/pim/notebook/NotebookEntrySearchField>
#include <bb/pim/notebook/NotebookEntrySortColumn>
#include <bb/pim/notebook/NotebookEntrySortOrder>
#include <bb/pim/notebook/NotebookEntryStatus>

#include <QDateTime>
#include <QSharedDataPointer>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookEntry;
class NotebookEntryFilterPrivate;

/*!
 * @brief The @c NotebookEntrySortSpecifier typedef represents a pair consisting of a
 * @c NotebookEntrySortColumn::Type value and a @c NotebookEntrySortOrder::Type value.
 *
 * @details Sort order and sort column are strongly related, and the @c %NotebookEntrySortSpecifier
 * typedef represents this relationship.
 *
 * @since BlackBerry 10.2.0
 */
typedef QPair<NotebookEntrySortColumn::Type, NotebookEntrySortOrder::Type> NotebookEntrySortSpecifier;

/*!
 * @headerfile NotebookEntryFilter.hpp <bb/pim/notebook/NotebookEntryFilter>
 *
 * @brief The @c NotebookEntryFilter class represents a filter that can be used to search and count notebook entries.
 *
 * @details A @c %NotebookEntryFilter is used to retrieve lists or counts of @c NotebookEntry objects that match certain
 * criteria, which are specified using setter functions.  Filter criteria are cumulative; a @c %NotebookEntry must match
 * all criteria set on the filter in order to be accepted by the filter.
 *
 * A @c %NotebookEntryFilter can also be used to test if individual @c %NotebookEntry objects should be accepted. This can
 * be useful if a list of @c %NotebookEntry objects has already been retrieved and a subset based on particular criteria
 * is required.
 *
 * Example usage:
 * @code
 *   // Here's how to create a filter for retrieving NotebookEntry objects in the default Notebook.
 *   // Note that service objects are potentially expensive to initialize, so you should not create
 *   // them on a per-use basis as is done below.
 *   NotebookService service;
 *   Notebook defaultNotebook = service.defaultNotebook();
 *   NotebookEntryFilter filter;
 *   filter.setParentNotebookId( defaultNotebook.id() );
 *   QList<NotebookEntry> entries = service.notebookEntries( filter );
 * @endcode
 *
 * @see NotebookService::notebookEntries(), NotebookService::notebookEntryCount()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntryFilter
{

public:

    /*!
     * @brief Constructs a new @c NotebookEntryFilter with no criteria set.
     *
     * @details A default-constructed filter accepts all @c NotebookEntry objects.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryFilter();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c NotebookEntryFilter containing exactly the same criteria as the provided
     * @c %NotebookEntryFilter.
     *
     * @param other The @c %NotebookEntryFilter to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryFilter(const NotebookEntryFilter &other);

    /*!
     * @brief Destroys this @c NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     */
    ~NotebookEntryFilter();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c NotebookEntryFilter into this
     * @c %NotebookEntryFilter.
     *
     * @param other The @c %NotebookEntryFilter from which to copy all values.
     *
     * @return A reference to this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryFilter& operator=(const NotebookEntryFilter &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator determines if this @c NotebookEntryFilter has the same values as another
     * @c %NotebookEntryFilter.  If two @c %NotebookEntryFilter objects are considered equal by this
     * operator, they will both accept the same @c NotebookEntry objects.
     *
     * @param other The @c %NotebookEntryFilter to compare to.
     *
     * @return @c True if the values are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const NotebookEntryFilter &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator determines if this @c NotebookEntryFilter has any different values from
     * another @c %NotebookEntryFilter.
     *
     * @param other The @c %NotebookEntryFilter to compare to.
     *
     * @return @c True if any of the values are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const NotebookEntryFilter &other) const;

    /*!
     * @brief Indicates whether the provided @c NotebookEntry is accepted by this @c NotebookEntryFilter.
     *
     * @details The provided @c %NotebookEntry is accepted if it matches all criteria set on this
     * @c %NotebookEntryFilter.
     *
     * @param entry The @c %NotebookEntry to check for acceptance by this @c %NotebookEntryFilter.
     *
     * @return @c True if the provided @c %NotebookEntry is accepted by this @c %NotebookEntryFilter, @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool accepts(const NotebookEntry &entry) const;

    /*!
     * @brief Sets the due date/time criteria for this @c NotebookEntryFilter.
     *
     * @details This is an overloaded function.  This function and
     * @c NotebookEntryFilter::setDueDateTime(NotebookEntryDueDate::Type, const QDateTime &, const QDateTime &) should be
     * thought of conceptually as a single function in which one or both of the @c QDateTime parameters can be omitted,
     * depending on the value of the @c type parameter.  Any omitted @c %QDateTime parameters are assigned null @c %QDateTime
     * objects by default.
     *
     * @param type One of the available due date types to filter on.
     * @param dueDateTime1 The "due after" or "due by" date/time criterion for this @c %NotebookEntryFilter, depending
     *  on the value of the @c type parameter.
     *
     * @see setDueDateTime(NotebookEntryDueDate::Type, const QDateTime &, const QDateTime &)
     *
     * @since BlackBerry 10.0.0
     */
    void setDueDateTime(NotebookEntryDueDate::Type type, const QDateTime &dueDateTime1=QDateTime());

    /*!
     * @brief Sets the due date/time criteria for this @c NotebookEntryFilter.
     *
     * @details Note: The two overloaded versions of this function should be thought of as a single function in which one
     * or both of the @c QDateTime arguments can be omitted, depending on the value of the @c type parameter.  Any omitted
     * @c %QDateTime parameters are assigned null @c %QDateTime objects by default.
     *
     * Once set, this @c %NotebookEntryFilter will only accept @c NotebookEntry objects based on the specified @c type and
     * @c %QDateTime arguments.  The @c %QDateTime objects are interpreted differently, depending on the @c type parameter, as
     * follows:
     * - @c NotebookEntryDueDate::NotSpecified: Both @c %QDateTime objects are ignored and can be omitted.
     * - @c NotebookEntryDueDate::NoDate: Both @c %QDateTime objects are ignored and can be omitted.
     * - @c NotebookEntryDueDate::AnyDate: Both @c %QDateTime objects are ignored and can be omitted.
     * - @c NotebookEntryDueDate::BySpecificDate: @c dueDateTime1 is used as the "due by" date/time; @c dueDateTime2
     *   is ignored and can be omitted.  If @c dueDateTime1 is invalid, then the due date type is set to
     *   @c %NotebookEntryDueDate::AnyDate.
     * - @c NotebookEntryDueDate::AfterSpecificDate: @c dueDateTime1 is used as the "due after" date/time; @c dueDateTime2
     *   is ignored and can be omitted.  If @c dueDateTime1 is invalid, then the due date type is set to
     *   @c %NotebookEntryDueDate::AnyDate.
     * - @c NotebookEntryDueDate::WithinSpecificRange: @c dueDateTime1 is used as the "due after" date/time; @c dueDateTime2
     *   is used as the "due by" date/time.  In other words, when selecting a range of dates/times, you specify the minimum
     *   date/time, followed by the maximum date/time.  If either of @c dueDateTime1 or @c dueDateTime2 is invalid, then the
     *   due date type is set to @c %NotebookEntryDueDate::BySpecificDate or @c %NotebookEntryDueDate::AfterSpecificDate as
     *   appropriate; if they are both invalid, then the due date type is set to @c %NotebookEntryDueDate::AnyDate.
     *
     * @param type One of the available due date types to filter on.
     * @param dueDateTime1 The "due after" or "due by" date/time criterion for this @c %NotebookEntryFilter, depending
     *  on the value of the @c type parameter.
     * @param dueDateTime2 The "due by" date/time criterion (only used when @c type is @c %NotebookEntryDueDate::WithinSpecificRange).
     *
     * @see setDueDateTime(NotebookEntryDueDate::Type, const QDateTime &), NotebookEntryDueDate
     *
     * @since BlackBerry 10.0.0
     */
    void setDueDateTime(NotebookEntryDueDate::Type type, const QDateTime &dueDateTime1, const QDateTime &dueDateTime2);

    /*!
     * @brief Resets the due date/time criteria for this @c NotebookEntryFilter.
     *
     * @details Calling this function prevents this @c %NotebookEntryFilter from rejecting @c NotebookEntry
     * objects based on due date/time, and is equivalent to invoking @c setDueDateTime() with
     * @c NotebookEntryDueDate::NotSpecified.
     *
     * @since BlackBerry 10.0.0
     */
    void resetDueDateTime();

    /*!
     * @brief Retrieves the "due by" date/time criterion being used by this @c NotebookEntryFilter.
     *
     * @return The "due by" date/time criterion being used by this @c %NotebookEntryFilter. If the "due by" date/time
     * criterion is not set or has been reset, a null @c QDateTime is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime dueDateTime() const;

    /*!
     * @brief Retrieves the "due after" date/time criterion being used by this @c NotebookEntryFilter.
     *
     * @return The "due after" date/time criterion being used by this @c %NotebookEntryFilter.  If the "due after"
     * date/time criterion is not set or has been reset, a null @c QDateTime is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime dueAfterDateTime() const;

    /*!
     * @brief Retrieves the due date type being used by this @c NotebookEntryFilter.
     *
     * @return The due date type being used by this @c %NotebookEntryFilter. If the due date criterion is not set or
     * has been reset, @c NotebookEntryDueDate::NotSpecified is returned.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryDueDate::Type dueDateTimeType() const;

    /*!
     * @brief Determines whether this @c NotebookEntryFilter is filtering based on due date/time.
     *
     * @return @c True if this @c %NotebookEntryFilter is filtering based on due date/time, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasDueDateTime() const;

    /*!
     * @brief Sets the reminder date/time criteria for this @c NotebookEntryFilter.
     *
     * @details This is an overloaded function.  This function and
     * @c NotebookEntryFilter::setReminderDateTime(NotebookEntryDueDate::Type, const QDateTime &, const QDateTime &) should be
     * thought of conceptually as a single function in which one or both of the @c QDateTime parameters can be omitted,
     * depending on the value of the @c type parameter.  Any omitted @c %QDateTime parameters are assigned null @c %QDateTime
     * objects by default.
     *
     * @param type One of the available date types to filter on.
     * @param reminderDateTime1 The "remind after" or "remind by" date/time criterion for this @c %NotebookEntryFilter, depending
     *  on the value of the @c type parameter.
     *
     * @see setReminderDateTime(NotebookEntryDueDate::Type, const QDateTime &, const QDateTime &)
     *
     * @since BlackBerry 10.2.0
     */
    void setReminderDateTime(NotebookEntryDueDate::Type type, const QDateTime &reminderDateTime1=QDateTime());

    /*!
     * @brief Sets the reminder date/time criteria for this @c NotebookEntryFilter.
     *
     * @details The two overloaded versions of this function should be thought of as a single function in which one
     * or both of the @c QDateTime arguments can be omitted, depending on the value of the @c type parameter. Any omitted
     * @c %QDateTime parameters are assigned null @c %QDateTime objects by default.
     *
     * Once set, this @c %NotebookEntryFilter accepts only @c NotebookEntry objects based on the specified @c type and
     * @c %QDateTime arguments.  The @c %QDateTime objects are interpreted differently, depending on the @c type parameter, as
     * follows:
     *
     * - @c NotebookEntryDueDate::NotSpecified: Both @c %QDateTime objects are ignored and can be omitted.
     * - @c NotebookEntryDueDate::NoDate: Both @c %QDateTime objects are ignored and can be omitted.
     * - @c NotebookEntryDueDate::AnyDate: Both @c %QDateTime objects are ignored and can be omitted.
     * - @c NotebookEntryDueDate::BySpecificDate: @c reminderDateTime1 is used as the "reminder by" date/time; @c reminderDateTime2
     *   is ignored and can be omitted. If @c reminderDateTime1 is invalid, the reminder date type is set to
     *   @c %NotebookEntryDueDate::AnyDate.
     * - @c NotebookEntryDueDate::AfterSpecificDate: @c reminderDateTime1 is used as the "reminder after" date/time; @c reminderDateTime2
     *   is ignored and can be omitted. If @c reminderDateTime1 is invalid, the reminder date type is set to
     *   @c %NotebookEntryDueDate::AnyDate.
     * - @c NotebookEntryDueDate::WithinSpecificRange: @c reminderDateTime1 is used as the "reminder after" date/time; @c reminderDateTime2
     *   is used as the "reminder by" date/time. In other words, when selecting a range of dates/times, you specify the minimum
     *   date/time, followed by the maximum date/time. If either @c reminderDateTime1 or @c reminderDateTime2 are invalid, the
     *   reminder date type is set to @c %NotebookEntryDueDate::BySpecificDate or @c %NotebookEntryDueDate::AfterSpecificDate as
     *   appropriate. If both parameters are invalid, the reminder date type is set to @c %NotebookEntryDueDate::AnyDate.
     *
     * @param type One of the available reminder date types to filter on.
     * @param reminderDateTime1 The "reminder after" or "reminder by" date/time criterion for this @c %NotebookEntryFilter, depending
     *  on the value of the @c type parameter.
     * @param reminderDateTime2 The "reminder by" date/time criterion (only used when @c type is @c %NotebookEntryDueDate::WithinSpecificRange).
     *
     * @see setReminderDateTime(NotebookEntryDueDate::Type, const QDateTime &), NotebookEntryDueDate
     *
     * @since BlackBerry 10.2.0
     */
    void setReminderDateTime(NotebookEntryDueDate::Type type, const QDateTime &reminderDateTime1, const QDateTime &reminderDateTime2);

    /*!
     * @brief Resets the reminder date/time criteria for this @c NotebookEntryFilter.
     *
     * @details Calling this function prevents this @c %NotebookEntryFilter from rejecting @c NotebookEntry
     * objects based on reminder date/time, and is equivalent to invoking @c setReminderDateTime() with
     * @c NotebookEntryDueDate::NotSpecified.
     *
     * @since BlackBerry 10.2.0
     */
    void resetReminderDateTime();

    /*!
     * @brief Retrieves the "reminder by" date/time criterion being used by this @c NotebookEntryFilter.
     *
     * @return The "reminder by" date/time criterion being used by this @c %NotebookEntryFilter. If the "reminder by" date/time
     * criterion is not set or has been reset, a null @c QDateTime is returned.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime reminderDateTime() const;

    /*!
     * @brief Retrieves the "reminder after" date/time criterion being used by this @c NotebookEntryFilter.
     *
     * @return The "reminder after" date/time criterion being used by this @c %NotebookEntryFilter.  If the "reminder after"
     * date/time criterion is not set or has been reset, a null @c QDateTime is returned.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime reminderAfterDateTime() const;

    /*!
     * @brief Retrieves the reminder date type being used by this @c NotebookEntryFilter.
     *
     * @return The reminder date type being used by this @c %NotebookEntryFilter. If the reminder date criterion is not set or
     * has been reset, @c NotebookEntryDueDate::NotSpecified is returned.
     *
     * @since BlackBerry 10.2.0
     */
    NotebookEntryDueDate::Type reminderDateTimeType() const;

    /*!
     * @brief Determines whether this @c NotebookEntryFilter is filtering based on reminder date/time.
     *
     * @return @c True if this @c %NotebookEntryFilter is filtering based on reminder date/time, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool hasReminderDateTime() const;

    /*!
     * @brief Sets the parent notebook ID criterion for this @c NotebookEntryFilter.
     *
     * @details Once set, this @c %NotebookEntryFilter will only accept @c NotebookEntry objects with a parent
     * notebook ID that is equal to the provided @c NotebookId. If the provided @c %NotebookId is not valid, then
     * this @c %NotebookEntryFilter does not reject @c %NotebookEntry objects based on parent notebook ID.
     *
     * @param parentNotebookId The parent notebook ID criterion for this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     *
     * @deprecated Please use @c setParentNotebookIds instead.
     */
    void setParentNotebookId(const NotebookId &parentNotebookId);

    /*!
     * @brief Resets the parent notebook ID criterion for this @c NotebookEntryFilter.
     *
     * @details Calling this function prevents this @c %NotebookEntryFilter from rejecting @c NotebookEntry objects
     * based on parent notebook ID, and is equivalent to invoking @c setParentNotebookId() with an invalid @c NotebookId.
     *
     * @since BlackBerry 10.0.0
     *
     * @c deprecated Please use @c resetParentNotebookIds instead.
     */
    void resetParentNotebookId();

    /*!
     * @brief Retrieves the parent notebook ID criterion being used by this @c NotebookEntryFilter.
     *
     * @return The parent notebook ID criterion being used by this @c %NotebookEntryFilter. If the parent notebook ID
     * criterion is not set or has been reset, an invalid @c %NotebookId is returned.
     *
     * @since BlackBerry 10.0.0
     *
     * @deprecated Please use @c parentNotebookIds instead.
     */
    NotebookId parentNotebookId() const;

    /*!
     * @brief Indicates whether this @c NotebookEntryFilter is filtering based on parent notebook ID.
     *
     * @return @c True if this @c %NotebookEntryFilter is filtering based on parent notebook ID, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     *
     * @deprecated Please use @c hasParentNotebookIds instead.
     */
    bool hasParentNotebookId() const;

    /*!
     * @brief Sets the parent notebook ID criteria for this @c NotebookEntryFilter.
     *
     * @details Once set, this @c %NotebookEntryFilter will only accept @c NotebookEntry objects with a parent
     * notebook ID that is in the list of provided @c NotebookId objects. If the provided list is empty, then
     * this @c %NotebookEntryFilter does not reject @c %NotebookEntry objects based on parent notebook IDs.
     * Any invalid @c NotebookId objects are not used by this @c %NotebookEntryFilter.
     *
     * @param parentNotebookIds The list of parent notebook ID criteria for this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.3.0
     */
    void setParentNotebookIds(const QList<NotebookId> &parentNotebookIds);

    /*!
     * @brief Resets the parent notebook ID criteria for this @c NotebookEntryFilter.
     *
     * @details Calling this function prevents this @c %NotebookEntryFilter from rejecting @c NotebookEntry objects
     * based on parent notebook ID, and is equivalent to invoking @c setParentNotebookIds() with an empty @c QList<NotebookId>.
     *
     * @since BlackBerry 10.3.0
     */
    void resetParentNotebookIds();

    /*!
     * @brief Retrieves the parent notebook ID criteria being used by this @c NotebookEntryFilter.
     *
     * @return The parent notebook ID criteria being used by this @c %NotebookEntryFilter. If the parent notebook ID
     * criteria has not been set or has been reset, an empty @c QList<NotebookId> is returned.
     *
     * @since BlackBerry 10.3.0
     */
    QList<NotebookId> parentNotebookIds() const;

    /*!
     * @brief Indicates whether this @c NotebookEntryFilter is filtering based on parent notebook IDs.
     *
     * @return @c True if this @c %NotebookEntryFilter is filtering based on parent notebook IDs, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool hasParentNotebookIds() const;

    /*!
     * @brief Sets the search string and search field criteria for this @c NotebookEntryFilter.
     *
     * @details Once set, this @c %NotebookEntryFilter will only accept @c NotebookEntry objects containing the specified
     * search string within the provided search field or fields. If the provided string is null or empty, then this
     * @c %NotebookEntryFilter does not reject @c %NotebookEntry objects based on search strings.
     *
     * @param searchString The search string criterion for this @c %NotebookEntryFilter.
     *        The maximum length of the search string that can be handled by the @c NotebookService is 250 characters.
     * @param searchField The search field criterion for this @c %NotebookEntryFilter. If not specified, all text fields
     * will be searched.
     *
     * @since BlackBerry 10.0.0
     */
    void setSearchString(const QString &searchString, NotebookEntrySearchField::Types searchField = NotebookEntrySearchField::All);

    /*!
     * @brief Resets the search string and search field criteria for this @c NotebookEntryFilter.
     *
     * @details Calling this function prevents this @c %NotebookEntryFilter from rejecting @c NotebookEntry objects based
     * on search string, and is equivalent to invoking @c setSearchString() with a null @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    void resetSearchString();

    /*!
     * @brief Retrieves the search string criterion being used by this @c NotebookEntryFilter.
     *
     * @return The search string criterion being used by this @c NotebookEntryFilter. If a search string criterion is not
     * set or has been reset, a null @c QString is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QString searchString() const;

    /*!
     * @brief Retrieves the search field criterion being used by this @c NotebookEntryFilter.
     *
     * @return The search field criterion being used by this @c %NotebookEntryFilter. If a search string criterion is not
     * set or has been reset, @c NotebookEntrySearchField::All is returned.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntrySearchField::Types searchField() const;

    /*!
     * @brief Determines whether this @c NotebookEntryFilter is filtering based on search strings.
     *
     * @return @c True if this @c %NotebookEntryFilter is filtering based on search strings, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasSearchString() const;

    /*!
     * @brief Sets the status criterion for this @c NotebookEntryFilter.
     *
     * @details Once set, this @c %NotebookEntryFilter will only accept @c NotebookEntry objects with any of the status
     * flags that are provided.
     *
     * @param status A set of allowed statuses for this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(NotebookEntryStatus::Types status);

    /*!
     * @brief Resets the status criterion for this @c NotebookEntryFilter.
     *
     * @details Calling this function prevents this @c %NotebookEntryFilter from rejecting @c NotebookEntry objects based
     * on status, and is equivalent to invoking @c setStatus() with 0.
     *
     * @since BlackBerry 10.0.0
     */
    void resetStatus();

    /*!
     * @brief Retrieves the status criterion being used by this @c NotebookEntryFilter.
     *
     * @return A set of allowed statuses being used by this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryStatus::Types status() const;

    /*!
     * @brief Indicates whether this @c NotebookEntryFilter is filtering based on status.
     *
     * @return @c True if this @c %NotebookEntryFilter is filtering based on status, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasStatus() const;

    /*!
     * @brief Sets the offset for this @c NotebookEntryFilter.
     *
     * @details Setting this value will skip the first @c offset number of @c NotebookEntry objects that would otherwise
     * be returned. If @c offset is larger than the number of @c %NotebookEntry objects that would otherwise be returned,
     * then no @c %NotebookEntry objects will be accepted by this @c %NotebookEntryFilter.
     *
     * @param offset The offset value for this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.0.0
     */
    void setOffset(unsigned int offset);

    /*!
     * @brief Resets the offset for this @c NotebookEntryFilter.
     *
     * @details Invoking this function is equivalent to invoking @c setOffset() with a value of 0.
     *
     * @since BlackBerry 10.0.0
     */
    void resetOffset();

    /*!
     * @brief Retrieves the offset for this @c NotebookEntryFilter.
     *
     * @return The offset value for this @c %NotebookEntryFilter, or 0 if an offset is not set.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int offset() const;

    /*!
     * @brief Sets the limit for this @c NotebookEntryFilter.
     *
     * @details This function restricts the maximum number of @c NotebookEntry objects that are accepted by this
     * @c %NotebookEntryFilter.
     *
     * @param limit The limit value for this @c %NotebookEntryFilter. A value of 0 means that there is no limit.
     *
     * @since BlackBerry 10.0.0
     */
    void setLimit(unsigned int limit);

    /*!
     * @brief Resets the limit for this @c NotebookEntryFilter.
     *
     * @details Invoking this function is equivalent to invoking @c setLimit() with a value of 0.
     *
     * @since BlackBerry 10.0.0
     */
    void resetLimit();

    /*!
     * @brief Retrieves the limit for this @c NotebookEntryFilter.
     *
     * @return The limit for this @c %NotebookEntryFilter,  or 0 if a limit is not set.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int limit() const;

    /*!
     * @brief Sets the sort columns and sort orders of this @c NotebookEntryFilter
     * using a list of @c NotebookEntrySortSpecifier objects.
     *
     * @details The default sort column is Title and the default sort order is Ascending.
     * The search results are first sorted according to the first @c %NotebookEntrySortSpecifier
     * in the provided list, then by the second @c %NotebookEntrySortSpecifier in the list, and so on.
     *
     * @param sortSpecifiers The set of sort column and sort order pairs to set, represented by
     * @c %NotebookEntrySortSpecifier objects.
     *
     * @since BlackBerry 10.2.0
     */
    void setSortSpecifiers(const QList<NotebookEntrySortSpecifier> &sortSpecifiers);

    /*!
     * @brief Retrieves the list of sort specifiers being used by this @c NotebookEntryFilter.
     *
     * @return A list of the sort specifiers being used by this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.2.0
     */
    QList<NotebookEntrySortSpecifier> sortSpecifiers() const;

    /*!
     * @brief Sets the sort columns and sort orders of this @c NotebookEntryFilter
     * using a list of @c NotebookEntrySortSpecifier objects.
     *
     * @details The default sort column is Title and the default sort order is Ascending.
     * The search results are first sorted according to the first @c %NotebookEntrySortSpecifier
     * in the provided list, then by the second @c %NotebookEntrySortSpecifier in the list, and so on.
     *
     * @param detailLevel The detail level to be set.
     *
     * @since BlackBerry 10.2.0
     */
    void setDetailLevel(NotebookEntryDetailLevel::Type detailLevel);

    /*!
     * @brief Retrieves the detail level being used by this @c NotebookEntryFilter.
     *
     * @return Detail level used by this @c %NotebookEntryFilter.
     *
     * @since BlackBerry 10.2.0
     */
    NotebookEntryDetailLevel::Type detailLevel() const;

    /* @cond PRIVATE */
    /*!
     * @brief Sets whether Enterprise Notebook Entries should be included should this filter be used.
     *
     * @param includeEnterprise @c True to include Enterprise Notebook Entries, @c false otherwise.
     * The default value is @c true.
     *
     * @since BlackBerry 10.2.0
     */
    void setIncludeEnterprise(bool includeEnterprise);

    /*!
     * @brief Returns whether Enterprise notebook entries are included if this filter is used.
     *
     * @return @c True if the include enterprise flag is set on this @c %NotebookEntryFilter,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool includeEnterprise() const;
    /* @endcond */

private:
    QSharedDataPointer<NotebookEntryFilterPrivate> d_ptr;
    friend class NotebookEntryFilterPrivate;
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif // BB_PIM_NOTEBOOK_NOTEBOOKENTRYFILTER_HPP
