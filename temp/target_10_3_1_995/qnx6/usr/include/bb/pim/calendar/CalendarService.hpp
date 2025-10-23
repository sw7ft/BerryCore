
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_CALENDARSERVICE_HPP
#define BB_PIM_CALENDAR_CALENDARSERVICE_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/AttendeeStatus>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/Notification>
#include <bb/pim/calendar/Result>
#include <bb/pim/message/Keys>
#include <QDateTime>
#include <QList>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QScopedPointer>
#include <QString>

namespace bb {
namespace pim {
namespace message {
    class Message;
}

namespace calendar {

class CalendarServicePrivate;

class AnalyticsParams;
class Attendee;
class AttendeeInEvents;
class AttendeeSearchParameters;
class CalendarEvent;
class CalendarFolder;
class CalendarSettings;
class CommonAttendee;
class CommonLocation;
class DetailLevel;
class EventRefresh;
class EventSearchParameters;
class ICalendarDataPath;
class ICalendarObjects;
class Notification;

/*!
 * @brief The @c CalendarService class provides access to PIM calendar data.
 *
 * @permissions @c access_pimdomain_calendars
 *
 * @details This class is an interface to the calendar service. This service
 * manages a local database and controls a set of synchronization services. Functions
 * in this class affect this database. The signals in this class are emitted
 * by changes in the calendar database, in calendar accounts, or in settings that
 * are relevant to calendar applications (for example, the current timezone).
 *
 * You can use the @c %CalendarService to create, retrieve, modify, and remove
 * calendar events. For instances of recurring events, the class provides functions
 * for modification and exclusion. There are also functions for responding to requests
 * for meetings and to forward events to email addresses.
 *
 * Here's an example of how to perform simple operations on a calendar event and save
 * these changes to the database.
 *
 * @code
 * CalendarService calendarService;
 *
 * // create a new event
 * CalendarEvent ev;
 * ev.setAccountId(1);
 * ev.setFolderId(1);
 * ev.setStartTime(QDateTime(2012, 7, 16, 12, 0, 0));
 * ev.setEndTime(QDateTime(2012, 7, 16, 13, 0, 0));
 * ev.setSubject("lunch");
 *
 * // save it to the database
 * calendarService.createEvent(ev);
 *
 * // modify the event, then save it to the database
 * ev.setStartTime(QDateTime(2012, 7, 16, 12, 30, 0));
 * ev.setEndTime(QDateTime(2012, 7, 16, 13, 30, 0));
 * calendarService.updateEvent(ev);
 *
 * // get any events happening from 12:30 to 13:30
 * EventSearchParameters params;
 * params.setStart(QDateTime(2012, 7, 16, 12, 30, 0));
 * params.setEnd(QDateTime(2012, 7, 16, 13, 30, 0));
 * params.setDetails(DetailLevel::Full);
 * QList<CalendarEvent> evs = calendarService.events(params);
 *
 * // remove the event from the database
 * calendarService.deleteEvent(ev);
 * @endcode
 *
 * Folders are containers for events. Each folder represents a separate calendar in the
 * Calendar application on the device. You can use the @c %CalendarService to retrieve
 * a list of folders and update the events within these folders. Here's an example of
 * how to do this:
 *
 * @code
 * QList<CalendarFolder> folders = calendarService.folders();
 * CalendarFolder firstFolder = folders.at(0);
 * firstFolder.setColor(0xFF0000);
 * calendarService.updateFolder(firstFolder);
 * @endcode
 *
 * You can also retrieve and change calendar-related system settings, such as time zone
 * and snooze time for calendar notifications. These settings are included in the
 * @c CalendarSettings class, and you can retrieve the current settings by calling
 * @c CalendarService::settings().
 *
 * @see CalendarEvent
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT CalendarService : public QObject {
    Q_OBJECT

public:
    /*!
     * @brief Constructs a new @c CalendarService.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarService();

    /*!
     * @brief Destroys this @c CalendarService.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CalendarService();

    /*!
     * @brief Creates an event.
     *
     * @details This function adds a new calendar event to the database. Optionally,
     * this function can notify participants by email.
     *
     * Some accounts are associated with remote databases. If the new event belongs to
     * this type of account, the calendar service communicates with the remote
     * database to replicate the event there.
     *
     * The event that you want to add should have values for the following parameters:
     * - account ID
     * - folder ID
     * - start time
     * - end time
     * - subject
     *
     * The call fails if any of these values are missing.
     *
     * The @c notification parameter is optional.
     *
     * On success, this function sets the event's ID attribute. This function assigns
     * the ID of the new database row to the ID attribute of the event object that you
     * pass as an argument, and the @c eventsRefreshed() signal is emitted. This signal
     * includes an @c EventRefresh parameter, and the @c createdEventIds list in this
     * parameter contains the event ID of the new event.
     *
     * @param event The event to be created.
     * @param notification Details for the email notification sent to the participants.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type createEvent(const CalendarEvent& event, const Notification& notification = Notification());

    /*!
     * @brief Changes an event in the database.
     *
     * @details This function saves the current state of an event that already exists in
     * the database. Optionally, this function can notify participants by email.
     *
     * Some accounts are associated with remote databases. If the event belongs to this
     * type of account, the calendar service communicates with the remote database to
     * replicate the changes there.
     *
     * It's not possible to move an event to a different account by calling this
     * function.
     *
     * The @c notification parameter is optional.
     *
     * On success, the @c eventsRefreshed() signal is emitted. This signal includes an
     * @c EventRefresh parameter, and the @c updatedEventIds list in this parameter
     * contains the event ID of the updated event.
     *
     * @param event The event to be updated.
     * @param notification Details for the email notification sent to the participants.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type updateEvent(const CalendarEvent& event, const Notification& notification = Notification());

    /*!
     * @brief Deletes an event.
     *
     * @details This function removes an event from the database. Optionally, this
     * function can notify participants by email.
     *
     * Some accounts are associated with remote databases. If the event belongs to
     * this type of account, the calendar service communicates with the remote
     * database to delete the event from it.
     *
     * The @c notification parameter is optional.
     *
     * On success, the @c eventsRefreshed() signal is emitted. This signal includes an
     * @c EventRefresh parameter, and the @c deletedEventIds list in this parameter
     * contains the event ID of the deleted event.
     *
     * @param event The event to be removed.
     * @param notification Details for the email notification sent to the participants.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type deleteEvent(const CalendarEvent& event, const Notification& notification = Notification());

    /*!
     * @brief Creates a recurrence exception.
     *
     * @details A recurrence exception is an instance of a recurring event that differs
     * from the series. This function changes the database so that a new event is created
     * with data from the modified occurrence. This event's parent ID is equal to the
     * recurring event's ID. The original start time of the modified occurrence is
     * added to the list of exceptions in the recurring event.
     *
     * Some accounts are associated with remote databases. If the recurring event belongs
     * to this type of account, the calendar service communicates with the remote
     * database to create the exception there.
     *
     * The @c notification parameter is optional.
     *
     * On success, the @c eventsRefreshed() signal is emitted. This signal includes an
     * @c EventRefresh parameter, and the @c createdEventIds list in this parameter
     * contains the ID for the exception. The @c updatedEventIds list in this parameter
     * contains the ID of the recurring event.
     *
     * @param occurrence The modified instance of the recurring event.
     * @param originalStartTime The previous start time for the occurrence being changed.
     * @param notification Details for the email notification sent to the participants.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type createRecurrenceException(const CalendarEvent& occurrence, const QDateTime& originalStartTime, const Notification& notification = Notification());

    /*!
     * @brief Excludes an occurrence of a recurring event.
     *
     * @details A recurrence exclusion is a deleted occurrence in a recurring event.
     *
     * Occurrences don't exist in the database as separate events. They are represented
     * by a unique event that has a non-empty recurrence rule attribute. The rule
     * specifies the dates on which the event occurs. It contains a list of exceptions,
     * which eliminates dates on which the event would otherwise occur.
     *
     * This function deletes an occurrence by adding its start time to the list of
     * exceptions of the recurring event.
     *
     * Some accounts are associated with remote databases. If the recurring event belongs
     * to this type of account, the calendar service communicates with the remote
     * database to create the exclusion there.
     *
     * The @c notification parameter is optional.
     *
     * On success, the @c eventsRefreshed() signal is emitted. This signal includes an
     * @c EventRefresh parameter, and the @c updatedEventIds list in this parameter
     * contains the ID of the recurring event.
     *
     * @param occurrence The removed occurrence of the recurring event.
     * @param notification Details for the email notification sent to the participants.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type createRecurrenceExclusion(const CalendarEvent& occurrence, const Notification& notification = Notification());

    /*!
     * @brief Retrieves an event.
     *
     * @details This function retrieves a single event from the database. You must
     * specify the account ID and event ID of the event that you want to retrieve.
     *
     * @param accountId The ID of the account that contains the event.
     * @param eventId The ID of the event to retrieve.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return The event with the specified account ID and event ID.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarEvent event(AccountId accountId, EventId eventId, Result::Type* result = 0);

    /*!
     * @brief Retrieves a list of events with the specified event IDs.
     *
     * @details This function retrieves events based on unique IDs.
     *
     * You can pass a start time along with each UID. The start time identifies
     * a recurrence exception, and is required because exceptions usually share the
     * UID of the recurring event that originated them.
     *
     * A UID that doesn't require a start time should be associated with a plain
     * @c QDateTime. Here's an example:
     *
     * @code
     * QMap<QString, QDateTime> uidMap;
     * uidMap.insert("6ab40924-cfa1-11e1-9852-002241284a73", QDateTime());
     * QList<CalendarEvent> evs = calendarService.eventsByUid(1, uidMap);
     * @endcode
     *
     * It's possible to request multiple events by adding as many UID/start time pairs
     * to the map parameter as needed.
     *
     * @param accountId The ID of the account that contains the specified events.
     * @param uids A map that associates UIDs with original start times. You should pass
     * a @c QDateTime() if a start time is not required.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A list of the specified events.
     *
     * @since BlackBerry 10.0.0
     */
    QList<CalendarEvent> eventsByUid(AccountId accountId, const QMap<QString, QDateTime>& uids, Result::Type* result = 0);

    /*!
     * @brief Retrieves a list of events that match the specified search criteria.
     *
     * @details The @c EventSearchParameters argument defines what events should be
     * returned:
     * - The start and end times define a range for the search. Events that enter this
     *   range are eligible to be part of the result set.
     * - The detail level controls what attributes are returned for each event.
     * - The expand flag causes the expansion of the recurring events that cross the
     *   query's range.
     * - The limit field defines the maximum number of events in the result set.
     * - The sort field determines how the result set is ordered.
     * - The events list is used to retrieve events by ID.
     * - The folders list is used to retrieve events by their folder IDs.
     *
     * Depending on the number of events in the database and on the breadth of the time
     * range, this operation may take from tenths of seconds to a few seconds.
     *
     * The calendar service assumes that the start and end times are in the device's time
     * zone.
     *
     * @param params The search parameters to use to search for events.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A list of events that match the specified criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<CalendarEvent> events(const EventSearchParameters& params, Result::Type* result = 0);

    /*
     * @brief Retrieves a list of attendees that match the specified search criteria.
     *
     * @details The @c EventSearchParameters argument determines which attendees should be returned:
     * - The start and end times define a range for the search.
     * - The detail level automatically defaults to Details::Attendee.
     * - The expand flag causes the expansion of the recurring events that match the
     *   query's range.
     * - The limit field defines the maximum number of events in the result set.
     *
     * Depending on the number of events in the database and on the breadth of the time
     * range, this operation may take from tenths of seconds to a few seconds.
     *
     * The calendar service assumes that the start and end times are in the device's time
     * zone.
     *
     * @param params The search parameters to use to search for attendees.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A list of pairs that contains the attendee emails and names present in the events
     * that match the specified criteria.
     *
     * @since BlackBerry 10.3.0
     */
    QList<QPair<QString, QString> > attendeesInEvents(const EventSearchParameters& params, Result::Type* result = 0);

    /*!
     * @brief Retrieves the last events that involve the specified person.
     *
     * @details This function returns the most recent meetings in which the user and
     * the specified person participate.
     *
     * The @c emails attribute of the @c AnalyticsParams parameter identifies the person
     * that should be present in the returned meetings. It's possible to request common
     * past meetings for more than one person by adding multiple associations to the
     * @c emails map. Here's an example:
     *
     * @code
     * CalendarService calendarService;
     * AnalyticsParams params;
     * QMap<QString, QVariant> map;
     *
     * QList<QString> emailsFromSchool;
     * emailsFromSchool.insert("joe@school.org");
     * map.insert("school", emailsFromSchool);
     *
     * QList<QString> emailsFromOffice;
     * emailsFromOffice.insert("jane@office.com");
     * map.insert("office", emailsFromOffice);
     * params.setEmails(map);
     *
     * QMap<QString, QList<CalendarEvent> > resultMap = calendarService.lastEvents(params);
     * QList<CalendarEvent> meetingsAtSchool = resultMap.value("school");
     * QList<CalendarEvent> meetingsAtOffice = resultMap.value("office");
     * @endcode
     *
     * The number of returned meetings is controlled by the @c limit attribute of
     * @c %AnalyticsParams.
     *
     * @param params The search parameters to use to search for events.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A map that contains the lists of past events involving the specified people.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QList<CalendarEvent> > lastEvents(const AnalyticsParams& params, Result::Type* result = 0);

    /*!
     * @brief Retrieves the next events that involve the specified person.
     *
     * @details This function returns the nearest future meetings in which the user and
     * the specified person participate.
     *
     * The @c emails attribute of the @c AnalyticsParams parameter identifies the person
     * that should be present in the returned meetings. It's possible to request future
     * meetings for more than one person by adding multiple associations to the @c emails
     * map. Here's an example:
     *
     * @code
     * CalendarService calendarService;
     * AnalyticsParams params;
     * QMap<QString, QVariant> map;
     *
     * QList<QString> emailsFromSchool;
     * emailsFromSchool.insert("joe@school.org");
     * map.insert("school", emailsFromSchool);
     *
     * QList<QString> emailsFromOffice;
     * emailsFromOffice.insert("jane@office.com");
     * map.insert("office", emailsFromOffice);
     * params.setEmails(map);
     *
     * QMap<QString, QList<CalendarEvent> > resultMap = calendarService.nextEvents(params);
     * QList<CalendarEvent> meetingsAtSchool = resultMap.value("school");
     * QList<CalendarEvent> meetingsAtOffice = resultMap.value("office");
     * @endcode
     *
     * The number of returned meetings is controlled by the @c limit attribute of
     * @c %AnalyticsParams.
     *
     * @param params The search parameters to use to search for events.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A map that contains the lists of future events involving the specified
     * people.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QList<CalendarEvent> > nextEvents(const AnalyticsParams& params, Result::Type* result = 0);

    /*!
     * @brief Retrieves common participants.
     *
     * @details This function returns people that have been in meetings with the user
     * and the given person.
     *
     * The @c emails attribute of the @c AnalyticsParams parameter identifies the person
     * that should participate (along with the user) with the people in common. It's
     * possible to request common attendees for more than one person by adding multiple
     * associations to the @c emails map. Here's an example:
     *
     * @code
     * CalendarService calendarService;
     * AnalyticsParams params;
     * QMap<QString, QVariant> map;
     *
     * QList<QString> emailsFromSchool;
     * emailsFromSchool.insert("joe@school.org");
     * map.insert("school", emailsFromSchool);
     *
     * QList<QString> emailsFromOffice;
     * emailsFromOffice.insert("jane@office.com");
     * map.insert("office", emailsFromOffice);
     * params.setEmails(map);
     *
     * QMap<QString, QList<CommonAttendee> > resultMap = calendarService.commonAttendees(params);
     * QList<CommonAttendee> peopleFromSchool = resultMap.value("school");
     * QList<CommonAttendee> peopleFromOffice = resultMap.value("office");
     * @endcode
     *
     * The number of returned attendees is controlled by the @c limit attribute of
     * @c %AnalyticsParams.
     *
     * @param params The search parameters to use to search for attendees.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A map that contains the lists of common attendees.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QList<CommonAttendee> > commonAttendees(const AnalyticsParams& params, Result::Type* result = 0);

    /*!
     * @brief Retrieves common locations.
     *
     * @details This function returns places where the user and the given person have met.
     *
     * The @c emails attribute of the @c AnalyticsParams parameter identifies the person
     * that met or will meet the user at the returned places. It's possible to request
     * common locations for more than one person by adding multiple associations to the
     * @c emails map. Here's an example:
     *
     * @code
     * CalendarService calendarService;
     * AnalyticsParams params;
     * QMap<QString, QVariant> map;
     *
     * QList<QString> joeEmails;
     * joeEmails.insert("joe@school.org");
     * map.insert("joe", joeEmails);
     *
     * QList<QString> janeEmails;
     * janeEmails.insert("jane@office.com");
     * map.insert("jane", janeEmails);
     * params.setEmails(map);
     *
     * QMap<QString, QList<CommonLocation> > resultMap = calendarService.commonLocations(params);
     * QList<CommonLocation> joePlaces = resultMap.value("joe");
     * QList<CommonLocation> janePlaces = resultMap.value("jane");
     * @endcode
     *
     * The number of places returned is controlled by the @c limit attribute of
     * @c %AnalyticsParams.
     *
     * @param params The search parameters to use to search for locations.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A map that contains the lists of common locations.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QList<CommonLocation> > commonLocations(const AnalyticsParams& params, Result::Type* result = 0);

    /*!
     * @brief Retrieves free/busy information.
     *
     * @details This function returns a map that associates users' email addresses with
     * their free/busy statuses.
     *
     * Each digit in a free/busy string corresponds to a 30-minute block. The zero digit
     * means that the block is free (no events in the 30-minute interval). The one digit
     * means that the block is tentative (there are events marked as tentative in the
     * interval). The two digit means that the block is busy (there are events marked as
     * busy in the interval).
     *
     * @param emails The list of users for whom the free/busy information should be
     * retrieved
     * @param start The start time for the free/busy query.
     * @param end The end time for the free/busy query.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A map that associates emails and free/busy data.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QString> freeBusy(const QStringList& emails, const QDateTime& start, const QDateTime& end, Result::Type* result = 0);

    /*!
     * @brief Updates a folder in the database.
     *
     * @details This function updates a folder in the calendar database with the data
     * from the provided folder.
     *
     * It is only possible to update a folder's color to one of the following values:
     * 0xF7941E, 0x779933, 0x289FC5, 0x6B3073, 0x53B89D,
     * 0x864301, 0xFFCB1A, 0xF7668F, 0x40C2CC, 0x425DAB,
     * 0x4BB578, 0xCC3399, 0xC0C61D, 0xCB8600, 0x7D5DE3.
     *
     * @param folder The folder to be updated.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type updateFolder(const CalendarFolder& folder);

    /*!
     * @brief Retrieves calendar folders.
     *
     * @details This function returns calendar folders from all calendar accounts. A
     * folder is a container for events, and usually serves as a way to classify
     * the events.
     *
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A list of calendar folders.
     *
     * @since BlackBerry 10.0.0
     */
    QList<CalendarFolder> folders(Result::Type* result = 0);

    /*!
     * @brief Replies to an invitation with an acceptance status.
     *
     * @details This function changes the acceptance status for the provided event and
     * optionally sends a reply message.
     *
     * @param event The event that's associated with the invitation.
     * @param status The user acceptance status.
     * @param comments Comments to be sent with the reply.
     * @param emailAccountId The messaging account that sends the reply.
     * @param notify Indicates whether to send a reply or not. If @c true a reply is
     * sent, if @c false the calendar service updates only the status for the event
     * and won't send a reply.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type reply(const CalendarEvent& event, AttendeeStatus::Type status, const QString& comments, AccountId emailAccountId, bool notify);

    /*!
     * @brief Replies to an invitation that includes a message ID with an acceptance
     * status.
     *
     * @details This function changes the acceptance status for the provided event and
     * optionally sends a reply message. This function includes a parameter that
     * represents the ID of the message containing the invitation.
     *
     * @param event The event that's associated with the invitation.
     * @param status The user acceptance status.
     * @param comments Comments to be sent with the reply.
     * @param emailAccountId The messaging account that sends the reply.
     * @param notify Indicates whether to send a reply or not. If @c true a reply is
     * sent, if @c false the calendar service updates only the status for the event
     * and won't send a reply.
     * @param originalMessageId An identifier for the message containing the invitation.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.1.0
     */
    Result::Type replyWithMessageId(const CalendarEvent& event, AttendeeStatus::Type status, const QString& comments, AccountId emailAccountId, bool notify, int originalMessageId);

    /*!
     * @brief Replies to a single occurrence of a recurring event.
     *
     * @details This function changes the acceptance status for the provided occurrence
     * of a recurring event and optionally sends a reply message. The occurrence also
     * becomes a recurrence exception event. That is, it is stored in the
     * database as a separate event and it references the original recurring event by
     * using the parent ID, which you can retrieve using @c CalendarEvent::parentId().
     *
     * @param occurrence The modified instance of the recurring event.
     * @param originalStartTime The previous start time for the occurrence being changed.
     * @param status The user acceptance status.
     * @param comments Comments to be sent with the reply.
     * @param emailAccountId The messaging account that sends the reply.
     * @param notify Indicates whether to send a reply or not. If @c true a reply is
     * sent, if @c false the calendar service updates only the status for the event
     * and won't send a reply.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.3.0
     */
    Result::Type replySingleOccurrence(const CalendarEvent& occurrence,
                                       const QDateTime& originalStartTime,
                                       AttendeeStatus::Type status,
                                       const QString& comments,
                                       AccountId emailAccountId,
                                       bool notify);

    /*!
     * @brief Parses an iCalendar file.
     *
     * @details This function creates a @c CalendarEvent object with data taken from
     * the provided iCalendar file.
     *
     * Any information that the database might have on the previous state of the event is
     * returned as part of its @c iCalendarData attribute.
     *
     * The iCalendar file is usually an attachment in a message.
     *
     * iCalendar is a standard format that represents events and tasks. The
     * format's specification is available at <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>.
     *
     * @param calendarAccount The account where the event is searched for.
     * @param messagingAccount The messaging account that received the message
     * containing the iCalendar attachment.
     * @param filepath The file path for the iCalendar file.
     * @param mimeType The MIME type for iCalendar (text/calendar, application/ics).
     * This parameter is optional.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A calendar event that includes the data from the provided iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarEvent parseICalendarData(AccountId calendarAccount, AccountId messagingAccount, const QString& filepath, const QString& mimeType, Result::Type* result = 0);

    /*!
     * @brief Builds data objects from the contents of an iCalendar file.
     *
     * @details This function reads objects from an iCalendar file.
     *
     * An iCalendar file may contain calendar events and tasks. This function returns
     * an @c ICalendarObjects object, which contains the event (if one exists) and
     * the task (if one exists) from the file.
     *
     * Any information the database might have on the previous state of the event is
     * returned as part of its @c iCalendarData attribute.
     *
     * The iCalendar file is usually an attachment in a message.
     *
     * iCalendar is a standard format for representation of events and tasks. The
     * format's specification is available at <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>.
     *
     * @param calendarAccount The account where the event is searched for.
     * @param messagingAccount The messaging account that received the message
     * containing the iCalendar attachment.
     * @param filepath The file path for the iCalendar file.
     * @param mimeType The MIME type for iCalendar (text/calendar, application/ics).
     * This parameter is optional.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return An @c %ICalendarObjects object that includes the event and task from the
     * provided iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects parseICalendarFile(AccountId calendarAccount, AccountId messagingAccount, const QString& filepath, const QString& mimeType, Result::Type* result = 0);

    /*!
     * @brief Builds objects from the contents of an iCalendar attachment.
     *
     * @details This function reads objects from an iCalendar attachment.
     *
     * An iCalendar attachment may contain calendar events and tasks. This function returns
     * an @c ICalendarObjects object, which contains the event (if one exists) and
     * the task (if one exists) from the file.
     *
     * Any information the database might have on the previous state of the event is
     * returned as part of its @c iCalendarData attribute.
     *
     * If a message has an iCalendar attachment that is not yet in the device's
     * database, there will be no events or tasks in the @c %ICalendarObjects returned, but
     * the attachment ID will be available (using @c ICalendarObjects::attachmentKey()). It's
     * possible to request the download of an attachment by calling
     * @c bb::pim::message::MessageService::downloadAttachment().
     *
     * iCalendar is a standard format for representation of events and tasks. The
     * format's specification is available at <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>.
     *
     * @param messagingAccount The messaging account that received the message
     * containing the iCalendar attachment.
     * @param messageId The ID of the message containing the iCalendar attachment.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return An @c %ICalendarObjects object that includes the event and task from the
     * provided iCalendar file.
     *
     * @since BlackBerry 10.3.0
     */
    ICalendarObjects retrieveICalendarAttachment(AccountId messagingAccount, bb::pim::message::MessageKey messageId, Result::Type* result = 0);

    /*!
     * @brief Sends a message with an event (specified by event ID) attached.
     *
     * @details The calendar service creates an iCalendar attachment with data from the
     * event specified by the provided IDs and sends an email with it.
     *
     * iCalendar is a standard format that represents events and tasks. The
     * format's specification is available at <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>.
     *
     * @param calendarAccount The account to which the event belongs.
     * @param calendarEventId The ID of the event.
     * @param message The message to which the event is attached.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type forwardEvent(AccountId calendarAccount, EventId calendarEventId, const bb::pim::message::Message& message);

    /*!
     * @brief Sends a message with an event (specified by a @c CalendarEvent) attached.
     *
     * @details The calendar service creates an iCalendar attachment with data from the
     * provided event and sends an email with it.
     *
     * iCalendar is a standard format that represents events and tasks. The
     * format's specification is available at <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>.
     *
     * @param calendarAccount The account to which the event belongs.
     * @param event The event to be sent as an ICS.
     * @param message The message to which the event is attached.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type forwardEvent(AccountId calendarAccount, const CalendarEvent& event, const bb::pim::message::Message& message);

    /*!
     * @brief Retrieves system settings for calendar events.
     *
     * @details This function returns system settings that are relevant to calendar
     * applications, such as time zone and snooze time for event notifications.
     *
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return The system settings for calendar events.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarSettings settings(Result::Type* result = 0);

    /*!
     * @brief Changes the default snooze time for calendar alerts.
     *
     * @details The system's notification manager shows visual alerts to inform the user of
     * upcoming events. When an alert is shown, the user has the option of snoozing it,
     * which means it will occur again after a certain time. The time for this next
     * alert is the default snooze value.
     *
     * @param minutes The new value for the snooze time, in minutes.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type updateSnoozeDefaultValue(unsigned int minutes);

    /*!
     * @brief Retrieves the list of people who participate in the specified events with
     * the user.
     *
     * @details The @c AttendeeSearchParameters parameter contains the list of event IDs
     * to process.
     *
     * @param params The search parameters.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A list of attendees who participate in the specified events with the user.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AttendeeInEvents> attendees(const AttendeeSearchParameters& params, Result::Type* result = 0);

    /*!
     * @brief Creates an iCalendar file for an event.
     *
     * @details This function exports the event specified by the account ID and event
     * ID to an iCalendar file.
     *
     * The calendar service attempts to create the file at the given path. If it's not
     * able to write at the location requested, it creates the file in a directory
     * that's accessible to it. You can retrieve this new path from the @c result object.
     *
     * iCalendar is a standard format that represents events and tasks. The
     * format's specification is available at <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>.
     *
     * @param accountId The account that contains the event.
     * @param eventId The ID of the event.
     * @param destinationPath The file path where the ICS should be created.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return An @c ICalendarDataPath object that contains information about the
     * created iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarDataPath createICalendarData(AccountId accountId, EventId eventId, const QString& destinationPath, Result::Type* result = 0);

     /*!
     * @brief Exports an event as an iCalendar file.
     *
     * @details This function exports the event specified by the account and event IDs to an
     * iCalendar file.
     *
     * The calendar service attempts to create the file at the given path. If it's not
     * able to write at the location requested, it creates the file in a directory
     * that's accessible to it. You can retrieve this new path from the @c result object.
     *
     * You can specify a trusted date. If present, it replaces the date in the
     * event's start and end times.
     *
     * The @c addAttendees parameter may be used to suppress the event's participants in
     * the exported file.
     *
     * iCalendar is a standard format for representation of events and tasks.
     * - Specification for the 2.0 format: <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>
     * - Specification for the 1.0 format: <a href="http://www.imc.org/pdi/pdiproddev.html">http://www.imc.org/pdi/pdiproddev.html</a>
     *
     * @param accountId The account that contains the event.
     * @param eventId The event identifier.
     * @param destinationPath The path where the file should be created.
     * @param trustedDate A date that replaces the date when the event starts. This parameter
     * is optional.
     * @param addAttendees If @c true this function generates an iCalendar that includes
     * attendees, if @c false this function generates an iCalendar without attendees. This
     * parameter is optional.
     * @param formatVersion The iCalendar format version: 2 (default) or 1.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return An instance of @c ICalendarDataPath, which provides information about the
     * created iCalendar file.
      *
      * @since BlackBerry 10.0.0
     */
    ICalendarDataPath exportICalendar(AccountId accountId, EventId eventId, const QString& destinationPath, const QDate& trustedDate = QDate(), bool addAttendees = true, int formatVersion = 2, Result::Type* result = 0);

    /*!
     * @brief Associates a calendar account with a messaging account.
     *
     * @details Attached calendar accounts react to messages containing information about
     * meetings:
     * - An event is created in the associated calendar when an invitation email
     *   arrives.
     * - Updates to a meeting received by email are reflected in the corresponding
     *   event.
     *
     * @param calendarId The ID of the calendar account.
     * @param messagingId The ID of the messaging account.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type attachCalendar(AccountId calendarId, AccountId messagingId);

    /*!
     * @brief Disassociates a calendar account and a messaging account.
     *
     * @details This function disconnects a calendar account from the associated messaging
     * account. Then, the calendar account can be linked to a different messaging account.
     *
     * @param calendarId The calendar account to disassociate.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type detachCalendar(AccountId calendarId);

    /*!
     * @brief Retrieves the default calendar folder.
     *
     * @details This function returns a pair of IDs (an account ID and a folder ID) that
     * determine the default calendar folder. This folder is the preferred location for
     * events created on the device. The user may select it using the Settings application
     * on the device.
     *
     * A calendar application should let the user choose the folder for a new event.
     * When user doesn't specify a folder, the application should place the new event
     * in the default folder.
     *
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A pair of identifiers (an account ID and a folder ID) for the default
     * folder.
     *
     * @since BlackBerry 10.0.0
     */
    QPair<AccountId, FolderId> defaultCalendarFolder(Result::Type* result = 0);

    /*!
     * @brief Sets the default calendar folder.
     *
     * @param accountId The ID for the account containing the folder.
     * @param folderId The ID for the folder.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.0.0
     */
    Result::Type setDefaultCalendarFolder(AccountId accountId, FolderId folderId);

    /*!
     * @brief Serializes an event as an iCalendar byte array.
     *
     * @details This function generates an iCalendar byte array that represents the
     * event passed as parameter.
     *
     * iCalendar is a standard format for representation of events and tasks.
     * - Specification for the 2.0 format: <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>
     * - Specification for the 1.0 format: <a href="http://www.imc.org/pdi/pdiproddev.html">http://www.imc.org/pdi/pdiproddev.html</a>
     *
     * @param event The event to be serialized.
     * @param result A pointer to the variable that receives the operation status.
     * This status indicates whether the operation was successful.
     *
     * @return A byte array containing data from the given event.
     *
     * @since BlackBerry 10.1.0
     */
    QByteArray eventToICalendarString(const CalendarEvent& event, Result::Type* result = 0);

    /*!
     * @brief Creates or updates an event from the given iCalendar data.
     *
     * @details This function takes the data in the iCalendar string and uses it to create an event
     * in the database. If an event with the same UID already exists, it receives an
     * update.
     *
     * Only the first event in the iCalendar string is processed.
     *
     * This function strips off any attendees mentioned in the iCalendar string.
     *
     * iCalendar is a standard format for representation of events and tasks.
     * - Specification for the 2.0 format: <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>
     * - Specification for the 1.0 format: <a href="http://www.imc.org/pdi/pdiproddev.html">http://www.imc.org/pdi/pdiproddev.html</a>
     *
     * @param accountId The ID for the account in which the event is created.
     * @param folderId The ID for the folder that contains the event.
     * @param iCalendarData A string containing information about the appointment.
     * @param uid The unique ID for the event. If not provided, the function searches for
     * a UID in the iCalendar string.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.2.0
     */
    Result::Type addOrUpdateEventInICalendarData(AccountId accountId, FolderId folderId, const QString& iCalendarData, const QString& uid=QString());

    /*!
     * @brief Creates or updates an event from the given iCalendar file.
     *
     * @details This function takes the data in the iCalendar file and uses it to create an event
     * in the database. If an event with the same UID already exists, it receives an
     * update.
     *
     * Only the first event in the iCalendar file is processed.
     *
     * This function strips off any attendees mentioned in the iCalendar file.
     *
     * iCalendar is a standard format for representation of events and tasks.
     * - Specification for the 2.0 format: <a href="http://tools.ietf.org/html/rfc5545">http://tools.ietf.org/html/rfc5545</a>
     * - Specification for the 1.0 format: <a href="http://www.imc.org/pdi/pdiproddev.html">http://www.imc.org/pdi/pdiproddev.html</a>
     *
     * @param accountId The ID for the account in which the event is created.
     * @param folderId The ID for the folder that contains the event.
     * @param filepath The path to the file containing information about the appointment.
     * @param uid The unique ID for the event. If not provided, the function searches for
     * a UID in the iCalendar string.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.2.0
     */
    Result::Type addOrUpdateEventInICalendarFile(AccountId accountId, FolderId folderId, const QString& filepath, const QString& uid=QString());

    /*!
     * @brief Deletes an event specified by a UID.
     *
     * @details This function searches the database for an event having the given UID
     * and deletes it. To delete a recurrence exception, you should also specify
     * the original start time.
     *
     * Some accounts are associated with remote databases. If the event belongs to
     * this type of account, the calendar service communicates with the remote
     * database to delete the event from it.
     *
     * On success, the @c eventsRefreshed() signal is emitted. This signal includes an
     * @c EventRefresh parameter, and the @c deletedEventIds list in this parameter
     * contains the event ID of the deleted event.
     *
     * @param accountId The ID for the account associated with the event.
     * @param uid The event's universal identifier.
     * @param originalStartTime The recurrence exception's original start time.
     * @param notification Details for the email notification sent to the participants.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.2.0
     */
    Result::Type deleteEventByUid(AccountId accountId, const QString& uid, const QDateTime& originalStartTime = QDateTime(), const Notification& notification = Notification());

    /*!
     * @brief Proposes a new time for a meeting.
     *
     * @details This function replies to an event with a proposal for a new time.
     *
     * @param event The event that's associated with the invitation.
     * @param newTime The new time proposed.
     * @param status The user acceptance status.
     * @param comments Comments to be sent with the reply.
     * @param emailAccountId The messaging account that sends the reply.
     * @param originalMessageId An identifier for the message containing the invitation.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.3
     */
    Result::Type proposeNewTime(const CalendarEvent& event, const QDateTime& newTime, AttendeeStatus::Type status, const QString& comments, AccountId emailAccountId, int originalMessageId);

    /*!
     * @brief Updates the default meeting reminder.
     *
     * @details When an event is about to begin, the device shows a dialog box to
     * alert the user. The meeting reminder controls when the dialog box appears,
     * and it represents the number of minutes before the event starts.
     * 
     * The default meeting reminder is assigned to events without reminders. The
     * purpose of a default reminder is to make sure that the user still receives
     * an alert in case the reminder was not set by mistake.
     *
     * @param minutes The new default meeting reminder time, in minutes.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.3.1
     */
    Result::Type updateDefaultMeetingReminder(unsigned int minutes);

    /*!
     * @brief Updates the default all-day meeting reminder.
     *
     * @details When an event is about to begin, the device shows a dialog box to
     * alert the user. The meeting reminder controls when the dialog box appears,
     * and it represents the number of minutes before the event starts.
     *
     * The default meeting reminder is assigned to events without reminders. The
     * purpose of a default reminder is to make sure that the user still receives
     * an alert in case the reminder was not set by mistake.
     *
     * @param minutes The new default all-day meeting reminder time, in minutes.
     *
     * @return A result value that indicates whether the operation was successful.
     *
     * @since BlackBerry 10.3.1
     */
    Result::Type updateDefaultAllDayMeetingReminder(unsigned int minutes);

Q_SIGNALS:
    /*!
     * @brief Emitted when events are added, changed, or removed.
     *
     * @details The @c CalendarService emits this signal whenever the events in the
     * database change, either as a result of a @c %CalendarService call or after a
     * synchronization process reconciles the local and remote data sources.
     *
     * @param notification A list of IDs for added events, changed events,
     * removed events and changed folders.
     *
     * @since BlackBerry 10.0.0
     */
    void eventsRefreshed(const bb::pim::calendar::EventRefresh& notification);

    /*!
     * @brief Emitted when the default calendar folder has changed.
     *
     * @param accountId The account ID that contains the new folder.
     * @param folderId The ID of the new folder.
     *
     * @since BlackBerry 10.3.1
     */
    void defaultCalendarFolderChanged(int accountId, int folderId);

    /*!
     * @brief Emitted when the list of available calendars has changed.
     *
     * @details This signal is emitted when new calendars become available after an
     * account is integrated, removed, or changed.
     *
     * @since BlackBerry 10.0.0
     */
    void calendarsChanged();

    /*!
     * @brief Emitted when the time zone on the device has changed.
     *
     * @param timezoneId The name of the new time zone.
     *
     * @since BlackBerry 10.0.0
     */
    void timezoneChanged(const QString& timezoneId);

    /*!
     * @brief Emitted when the hour format on the device has changed.
     *
     * @param format24Hours If @c true, the hour format is 24-hour, if @c false the hour
     * format is not 24-hour.
     *
     * @since BlackBerry 10.0.0
     */
    void hourFormatChanged(bool format24Hours);

    /*!
     * @brief Emitted when a new folder has been created.
     *
     * @param folderId The ID of the new folder.
     * @param accountId The account ID that contains the new folder.
     *
     * @since BlackBerry 10.0.0
     */
    void folderCreated(int folderId, int accountId);

    /*!
     * @brief Emitted when a folder has been deleted.
     *
     * @param folderId The ID of the deleted folder.
     * @param accountId The account ID that contained the deleted folder.
     *
     * @since BlackBerry 10.0.0
     */
    void folderDeleted(int folderId, int accountId);

    /*!
     * @brief Emitted when a folder has been changed.
     *
     * @param folderId The ID of the changed folder.
     * @param accountId The account ID that contained the changed folder.
     *
     * @since BlackBerry 10.0.0
     */
    void folderChanged(int folderId, int accountId);

private:
    Q_DISABLE_COPY(CalendarService)
    Q_DECLARE_PRIVATE(CalendarService)
    QScopedPointer<CalendarServicePrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_CALENDARSERVICE_HPP
