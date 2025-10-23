
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_EVENTREFRESH_HPP
#define BB_PIM_CALENDAR_EVENTREFRESH_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QList>

namespace bb {
namespace pim {
namespace calendar {

class EventRefreshPrivate;

/*!
 * @brief The @c EventRefresh class represents a notification for added, changed, or
 * deleted events.
 *
 * @details An @c %EventRefresh object is sent by the calendar service whenever events
 * are created in, updated in, or removed from the local database. This object contains
 * information about the events that were created, updated, or removed, such as event
 * IDs, folder IDs, and account ID.
 * 
 * For example, the @c CalendarService::eventsRefreshed() signal is emitted when there
 * are changes to events in the database. This signal includes an @c %EventRefresh
 * parameter that contains the details of the refresh.
 * 
 * @see CalendarService
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT EventRefresh {
public:

    /*!
     * @brief Constructs a new @c EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    EventRefresh();

    /*!
     * @brief Destroys this @c EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    ~EventRefresh();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c EventRefresh containing exactly the
     * same values as the provided @c %EventRefresh.
     *
     * @param other The @c %EventRefresh to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    EventRefresh(const EventRefresh& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c EventRefresh
     * into this @c %EventRefresh.
     *
     * @param other The @c %EventRefresh from which to copy all values.
     *
     * @return A reference to this @c %EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    EventRefresh& operator=(const EventRefresh& other);

    /*!
     * @brief Retrieves the list of IDs of created events.
     *
     * @details This function returns a list that includes the IDs of events that were
     * created in the local database.
     *
     * @return The list of IDs of created events.
     *
     * @since BlackBerry 10.0.0
     */
    QList<EventId> createdEventIds() const;

    /*!
     * @brief Retrieves the list of IDs of updated events.
     *
     * @details This function returns a list that includes the IDs of events that were
     * changed or updated in the local database.
     *
     * @return The list of IDs of updated events.
     *
     * @since BlackBerry 10.0.0
     */
    QList<EventId> updatedEventIds() const;

    /*!
     * @brief Retrieves the list of IDs of deleted events.
     *
     * @details This function returns a list that includes the IDs of events that were
     * deleted from the local database.
     *
     * @return The list of IDs of deleted events.
     *
     * @since BlackBerry 10.0.0
     */
    QList<EventId> deletedEventIds() const;

    /*!
     * @brief Retrieves the list of IDs of updated folders.
     *
     * @details This function returns a list that includes the IDs of folders in which
     * events were added, deleted, or changed.
     *
     * @return The list of IDs of updated folders.
     *
     * @since BlackBerry 10.0.0
     */
    QList<FolderId> updatedFolderIds() const;

    /*!
     * @brief Retrieves the account ID of this @c EventRefresh.
     *
     * @details This function returns the identifier for the account that owns the added,
     * changed, or removed events.
     *
     * @return The account ID of this @c %EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId account() const;


    /*!
     * @brief Adds the ID of a created event to this @c EventRefresh.
     *
     * @details This function appends a new ID to the existing list of created event IDs.
     *
     * @param createdEventId The event ID to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addCreatedEventId(EventId createdEventId);

    /*!
     * @brief Removes all created event IDs from this @c EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    void resetCreatedEventIds();

    /*!
     * @brief Sets the list of created event IDs for this @c EventRefresh.
     *
     * @details This function replaces the current list of created event IDs with the
     * provided list.
     *
     * @param createdEventIds The new list of created event IDs.
     *
     * @since BlackBerry 10.0.0
     */
    void setCreatedEventIds(const QList<EventId>& createdEventIds);

    /*!
     * @brief Adds the ID of an updated event to this @c EventRefresh.
     *
     * @details This function appends a new ID to the existing list of updated event
     * IDs.
     *
     * @param updatedEventId The event ID to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addUpdatedEventId(EventId updatedEventId);

    /*!
     * @brief Removes all updated event IDs from this @c EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    void resetUpdatedEventIds();

    /*!
     * @brief Sets the list of updated event IDs for this @c EventRefresh.
     *
     * @details This function replaces the current list of updated event IDs with the
     * provided list.
     *
     * @param updatedEventIds The new list of updated event IDs.
     *
     * @since BlackBerry 10.0.0
     */
    void setUpdatedEventIds(const QList<EventId>& updatedEventIds);

    /*!
     * @brief Adds the ID of a deleted event to this @c EventRefresh.
     *
     * @details This function appends a new ID to the existing list of deleted event
     * IDs.
     *
     * @param deletedEventId The event ID to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addDeletedEventId(EventId deletedEventId);

    /*!
     * @brief Removes all deleted event IDs from this @c EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    void resetDeletedEventIds();

    /*!
     * @brief Sets the list of deleted event IDs for this @c EventRefresh.
     *
     * @details This function replaces the current list of deleted event IDs with the
     * provided list.
     *
     * @param deletedEventIds The new list of deleted event IDs.
     *
     * @since BlackBerry 10.0.0
     */
    void setDeletedEventIds(const QList<EventId>& deletedEventIds);

    /*!
     * @brief Adds the ID of an updated folder to this @c EventRefresh.
     *
     * @details This function appends a new ID to the existing list of updated folder
     * IDs.
     *
     * @param updatedFolderId The folder ID to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addUpdatedFolderId(FolderId updatedFolderId);

    /*!
     * @brief Removes all updated folder IDs from this @c EventRefresh.
     *
     * @since BlackBerry 10.0.0
     */
    void resetUpdatedFolderIds();

    /*!
     * @brief Sets the list of updated folder IDs for this @c EventRefresh.
     *
     * @details This function replaces the current list of updated folder IDs with the
     * provided list.
     *
     * @param updatedFolderIds The new list of updated folder IDs.
     *
     * @since BlackBerry 10.0.0
     */
    void setUpdatedFolderIds(const QList<FolderId>& updatedFolderIds);

    /*!
     * @brief Sets the account ID of this @c EventRefresh.
     *
     * @param account The new account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccount(AccountId account);

    /*!
     * @brief Indicates whether this @c EventRefresh is valid.
     *
     * @details This function determines whether the attributes of this @c %EventRefresh
     * object have acceptable values.
     *
     * @return @c true if this @c %EventRefresh is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<EventRefreshPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_EVENTREFRESH_HPP

