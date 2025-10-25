
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_EVENTSEARCHPARAMETERS_HPP
#define BB_PIM_CALENDAR_EVENTSEARCHPARAMETERS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/DetailLevel>
#include <bb/pim/calendar/SortField>
#include <QSharedDataPointer>
#include <QList>
#include <QDateTime>
#include <QPair>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class FolderKey;
class EventKey;
class EventSearchParametersPrivate;

/*!
 * @brief The @c EventSearchParameters class includes parameters for calendar event searches.
 *
 * @details This class packages parameters that you can use to search for specific calendar
 * events. For example, an @c %EventSearchParameters object could contain information such
 * as start time, end time, or even specific events to search for.
 * 
 * To search for specific events, you can call @c CalendarService::events() and pass as a
 * parameter an @c %EventSearchParameters object that contains information about the events
 * that you want to search for. When you search for events using @c %EventSearchParameters,
 * you should provide at least the detail level, start time, and end time that you want to
 * search for.
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
class BB_PIM_EXPORT EventSearchParameters {
public:

    /*!
     * @brief Constructs a new @c EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    EventSearchParameters();

    /*!
     * @brief Destroys this @c EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    ~EventSearchParameters();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c EventSearchParameters containing exactly the
     * same values as the provided @c %EventSearchParameters.
     *
     * @param other The @c %EventSearchParameters to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    EventSearchParameters(const EventSearchParameters& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c EventSearchParameters
     * into this @c %EventSearchParameters.
     *
     * @param other The @c %EventSearchParameters from which to copy all values.
     *
     * @return A reference to this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    EventSearchParameters& operator=(const EventSearchParameters& other);

    /*!
     * @brief Retrieves the start time of this @c EventSearchParameters.
     *
     * @details This function returns the start of the query's time range. All events
     * that enter the range should be returned. The start time is considered to be in
     * the local time zone (the system's time zone).
     *
     * @return The start time of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime start() const;

    /*!
     * @brief Retrieves the end time of this @c EventSearchParameters.
     *
     * @details This function returns the end of the query's time range. Any event that
     * crosses the range should be returned. The end time is considered to be in the
     * local time zone (the system's time zone).
     *
     * @return The end time of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime end() const;

    /*!
     * @brief Retrieves the detail level of this @c EventSearchParameters.
     *
     * @details The detail level controls the set of attributes in events that are
     * populated when a search is performed.
     * 
     * The following levels are available: 
     * - Monthly: Events have accountId, allDay, busyStatus, endTime, folderId, id,
     *   parentId, and startTime.
     * - Weekly: Events have all the attributes in the monthly level plus birthday and
     *   subject.
     * - Full: Events have all the attributes in the weekly level plus attendees,
     *   bbmConference, body, guid, location, meetingSequence, meetingStatus, recurrence,
     *   reminder, sensitivity, timezone, and url.
     * - Agenda: Events have all the attributes in the weekly level plus bbmConference,
     *   guid, location, meetingSequence, meetingStatus, recurrence, reminder,
     *   sensitivity, timezone, and url.
     * - WeeklyStatus: Events have all the attributes in the weekly level plus
     *   the response status of the owner
     * - AgendaStatus: Events have all the attributes in the agenda level plus
     *   the reponse status of the owner
     * 
     * Search requests with lower detail levels are faster.
     *
     * @return The detail level of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    DetailLevel::Type details() const;

    /*!
     * @brief Indicates whether recurring events are expanded in the search results.
     *
     * @details If recurring events are expanded, all occurrences of all events
     * (including each occurrence of a recurring event) in the specified time range
     * are returned. 
     *
     * @return @c true if recurring events are expanded, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isExpand() const;

    /*!
     * @brief Retrieves the limit for the number of search results.
     *
     * @details This function returns the maximum number of returned events.
     *
     * @return The limit for the number of results.
     *
     * @since BlackBerry 10.0.0
     */
    int limit() const;

    /*!
     * @brief Retrieves the prefix search parameter of this @c EventSearchParameters.
     *
     * @details This function returns the string that's used in the prefix search. By
     * setting the prefix, you can instruct the search to return only events whose
     * subject or location fields start with the specified string.
     * The search will also return events whose participants have names or emails
     * starting with the given string.
     *
     * @return The prefix search parameter of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QString prefix() const;

    /*!
     * @brief Retrieves the subject prefix search parameter of this @c EventSearchParameters.
     *
     * @details This function returns the string that's used in the prefix search on subjects.
     *
     * @return The subject prefix search parameter of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.3.0
     */
    QString subjectPrefix() const;

    /*!
     * @brief Retrieves the location prefix search parameter of this @c EventSearchParameters.
     *
     * @details This function returns the string that's used in the prefix search on locations.
     *
     * @return The location prefix search parameter of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.3.0
     */
    QString locationPrefix() const;

    /*!
     * @brief Retrieves the attendee prefix search parameter of this @c EventSearchParameters.
     *
     * @details This function returns the string that's used in the prefix search on attendees.
     *
     * @return The attendee prefix search parameter of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.3.0
     */
    QString attendeePrefix() const;

    /*!
     * @brief Retrieves the list of event keys for this @c EventSearchParameters.
     *
     * @details An event key contains the primary key for an event in the database. When
     * the list is non-empty, the search is performed directly for the events that have the
     * provided keys.
     *
     * @return The list of event keys for this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QList<EventKey> events() const;

    /*!
     * @brief Retrieves the list of folder keys for this @c EventSearchParameters.
     *
     * @details A folder key contains the primary key for a calendar folder in the database.
     * When the list is non-empty, the search returns only events that belong to the
     * provided folders.
     *
     * @return The list of folder keys for this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QList<FolderKey> folders() const;

    /*!
     * @brief Retrieves the sort parameters of this @c EventSearchParameters.
     *
     * @details This function specifies the attributes by which the returned events will be
     * sorted and whether they will be in ascending or descending order for each attribute.
     *
     * @return The sort parameters of this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QPair<SortField::Type, bool> > sort() const;


    /*!
     * @brief Sets the start time of this @c EventSearchParameters.
     *
     * @param start The new start time.
     *
     * @since BlackBerry 10.0.0
     */
    void setStart(const QDateTime& start);

    /*!
     * @brief Sets the end time of this @c EventSearchParameters.
     *
     * @param end The new end time.
     *
     * @since BlackBerry 10.0.0
     */
    void setEnd(const QDateTime& end);

    /*!
     * @brief Sets the detail level of this @c EventSearchParameters.
     *
     * @param details The new detail level.
     *
     * @since BlackBerry 10.0.0
     */
    void setDetails(DetailLevel::Type details);

    /*!
     * @brief Sets whether recurring events are expanded in the search results.
     *
     * @details If recurring events are expanded, all occurrences of all events
     * (including each occurrence of a recurring event) in the specified time range
     * are returned. 
     *
     * @param expand If @c true recurring events are expanded, if @c false recurring
     * events are not expanded.
     *
     * @since BlackBerry 10.0.0
     */
    void setExpand(bool expand);

    /*!
     * @brief Sets the limit for the number of search results.
     *
     * @param limit The new limit for the number of search results.
     *
     * @since BlackBerry 10.0.0
     */
    void setLimit(int limit);

    /*!
     * @brief Sets the prefix search parameter of this @c EventSearchParameters.
     *
     * @param prefix The new prefix search parameter.
     *
     * @since BlackBerry 10.0.0
     */
    void setPrefix(const QString& prefix);

    /*!
     * @brief Sets the subject prefix search parameter of this @c EventSearchParameters.
     *
     * @param prefix The new subject prefix search parameter.
     *
     * @since BlackBerry 10.3.0
     */
    void setSubjectPrefix(const QString& subjectPrefix);

    /*!
     * @brief Sets the location prefix search parameter of this @c EventSearchParameters.
     *
     * @param prefix The new location prefix search parameter.
     *
     * @since BlackBerry 10.3.0
     */
    void setLocationPrefix(const QString& locationPrefix);

    /*!
     * @brief Sets the attendee prefix search parameter of this @c EventSearchParameters.
     *
     * @param prefix The new attendee prefix search parameter.
     *
     * @since BlackBerry 10.3.0
     */
    void setAttendeePrefix(const QString& attendeePrefix);

    /*!
     * @brief Adds an event key to this @c EventSearchParameters.
     *
     * @details This function appends a new event key to the existing list of event
     * keys for this @c %EventSearchParameters.
     *
     * @param event The event key to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addEvent(const EventKey& event);

    /*!
     * @brief Removes all of the event keys from this @c EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEvents();

    /*!
     * @brief Sets the list of event keys for this @c EventSearchParameters.
     *
     * @details This function replaces the current list of event keys with the
     * provided list.
     *
     * @param events The new list of event keys.
     *
     * @since BlackBerry 10.0.0
     */
    void setEvents(const QList<EventKey>& events);

    /*!
     * @brief Adds a folder key to this @c EventSearchParameters.
     *
     * @details This function appends a new folder key to the existing list of folder
     * keys for this @c %EventSearchParameters.
     *
     * @param folder The folder key to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addFolder(const FolderKey& folder);

    /*!
     * @brief Removes all of the folder keys from this @c EventSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFolders();

    /*!
     * @brief Sets the list of folder keys for this @c EventSearchParameters.
     *
     * @details This function replaces the current list of folder keys with the
     * provided list.
     *
     * @param folders The new list of folder keys.
     *
     * @since BlackBerry 10.0.0
     */
    void setFolders(const QList<FolderKey>& folders);

    /*!
     * @brief Sets the sort parameters for this @c EventSearchParameters.
     *
     * @details This function replaces the current list of sort parameters with the
     * provided list.
     *
     * @param sort The new list of sort parameters.
     *
     * @since BlackBerry 10.0.0
     */
    void setSort(QList<QPair<SortField::Type, bool > > sort);
    
    /*!
     * @brief Sets the sort parameter for this @c EventSearchParameters.
     *
     * @details This function replaces the current list of sort parameters with the
     * provided parameter.
     *
     * @param sort The new sort parameter.
     *
     * @since BlackBerry 10.0.0
     */
    void setSort(QPair<SortField::Type, bool > sort);

    /*!
     * @brief Indicates whether this @c EventSearchParameters is valid.
     *
     * @details This function determines whether the attributes of this @c %EventSearchParameters
     * object have acceptable values.
     *
     * @return @c true if this @c %EventSearchParameters is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Sets the visibleOnly parameter for this @c EventSearchParameters.
     *
     * @details The visibleOnly parameters allow to search events only through visible calendars
     *
     * @return The list of event keys for this @c %EventSearchParameters.
     *
     * @since BlackBerry 10.2.0
     */
    void setVisibleOnlyEnabled(bool visibleOnly);

    /*!
     * @brief Indicates if the visibleOnly filter is active
     *
     * @details The visibleOnly flag determines if the event search is done only
     * in visible calendars or not.
     *
     * @return True, if search is done only for visible calendars, or false otherwise
     *
     * @since BlackBerry 10.2.0
     */
    bool isVisibleOnlyEnabled() const;

private:
    QSharedDataPointer<EventSearchParametersPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_EVENTSEARCHPARAMETERS_HPP

