
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_CALENDAREVENT_HPP
#define BB_PIM_CALENDAR_CALENDAREVENT_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/Sensitivity>
#include <bb/pim/calendar/BusyStatus>
#include <bb/pim/calendar/AttendeeStatus>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QList>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class Recurrence;
class Attendee;
class BbmConference;
class OnlineConferenceData;
class ICalendarData;
class CalendarEventPrivate;

/*!
 * @brief The @c CalendarEvent class represents an event or meeting in a user's calendar.
 *
 * @details This class includes event-related information such as start and end time,
 * location, recurrence, and attendees. You can call @c CalendarService::events() to
 * retrieve the list of events, each of which is represented by a @c %CalendarEvent
 * object. The attributes of each @c %CalendarEvent are populated according to the
 * detail level that you provide in the @c EventSearchParameters argument:
 * - Monthly level: accountId, allDay, busyStatus, endTime, folderId, id, parentId,
 *   and startTime
 * - Weekly level: all the attributes in the monthly level plus birthday and subject
 * - Full level: all the attributes in the weekly level plus attendees,
 *   bbmConference, body, guid, location, meetingSequence, meetingStatus, recurrence,
 *   reminder, sensitivity, timezone, and url
 * - Agenda level: all the attributes in the weekly level plus bbmConference, guid,
 *   location, meetingSequence, meetingStatus, recurrence, reminder, sensitivity,
 *   timezone, and url
 *
 * A @c %CalendarEvent is not automatically updated when a synchronization service in the
 * back-end changes the information in the calendar database. You should connect a
 * @c QObject with the appropriate slots to the signals in @c %CalendarService to be
 * notified of an update and request a new copy of the event when needed.
 *
 * When you change the attribute of a @c %CalendarEvent, this change does not automatically
 * modify the event in the calendar database. To update the database, you should call
 * @c CalendarService::updateEvent() and pass the event as an argument.
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
class BB_PIM_EXPORT CalendarEvent {
public:

    /*!
     * @brief Constructs a new @c CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarEvent();

    /*!
     * @brief Destroys this @c CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    ~CalendarEvent();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c CalendarEvent containing exactly the
     * same values as the provided @c %CalendarEvent.
     *
     * @param other The @c %CalendarEvent to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarEvent(const CalendarEvent& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CalendarEvent
     * into this @c %CalendarEvent.
     *
     * @param other The @c %CalendarEvent from which to copy all values.
     *
     * @return A reference to this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarEvent& operator=(const CalendarEvent& other);

    /*!
     * @brief Retrieves the start time of this @c CalendarEvent.
     *
     * @details This function returns the date and time when the event starts, in the local
     * time zone (the system's time zone).
     *
     * @return The start time of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime startTime() const;

    /*!
     * @brief Retrieves the end time of this @c CalendarEvent.
     *
     * @details This function returns the date and time when the event ends, in the local
     * time zone (the system's time zone). This value should be greater than (that is,
     * occur after) the start time.
     *
     * @return The end time of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime endTime() const;

    /*!
     * @brief Retrieves the body of this @c CalendarEvent.
     *
     * @details This function returns the contents of the text field that contains details for
     * the event.
     *
     * @return The body of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QString body() const;

    /*!
     * @brief Retrieves the subject of this @c CalendarEvent.
     *
     * @details This function returns the subject, or title, of the event.
     *
     * @return The subject of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QString subject() const;

    /*!
     * @brief Retrieves the location of this @c CalendarEvent.
     *
     * @details This function returns a string that indicates where the event happened or
     * will happen.
     *
     * @return The location of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    EventLocation location() const;

    /*!
     * @brief Retrieves the time zone of this @c CalendarEvent.
     *
     * @details This function returns the name of the time zone where the event was
     * created.
     *
     * @return The time zone of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QString timezone() const;

    /*!
     * @brief Retrieves the URL that's associated with this @c CalendarEvent.
     *
     * @return The URL that's associated with this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QString url() const;

    /*!
     * @brief Retrieves the recurrence rule for this @c CalendarEvent.
     *
     * @details The recurrence rule defines how an event repeats. The information about
     * the recurrence of an event, such as start and end time, frequency, days of the
     * week, and so on, are included in the @c Recurrence class.
     *
     * By default, an event is not recurrent (that is, @c event.recurrence().isValid()
     * @c == @c false). The event becomes a recurring event when a call is made to the
     * @c setRecurrence() function with a valid @c %Recurrence object.
     *
     * @return The recurrence rule for this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    Recurrence recurrence() const;

    /*!
     * @brief Retrieves the list of participants for this @c CalendarEvent.
     *
     * @details This function returns a list of people who are attending the event.
     * Each participant is represented by an @c Attendee object.
     *
     * @return The list of participants for this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Attendee> attendees() const;

    /*!
     * @brief Retrieves the sensitivity of this @c CalendarEvent.
     *
     * @details This function indicates the degree of confidentiality for the event
     * normal, personal, private, or confidential.
     *
     * @return The sensitivity of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    Sensitivity::Type sensitivity() const;

    /*!
     * @brief Retrieves the busy status of this @c CalendarEvent.
     *
     * @details This function indicates whether the event represents free time,
     * tentative time (the user might be present or not), busy time, or time out of
     * the office.
     *
     * @return The busy status of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    BusyStatus::Type busyStatus() const;

    /*!
     * @brief Retrieves the account ID of this @c CalendarEvent.
     *
     * @details This function returns the identifier for the account that owns the
     * event.
     *
     * @return The account ID of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId accountId() const;

    /*!
     * @brief Retrieves the folder of this @c CalendarEvent.
     *
     * @details This function returns the identifier for the folder that contains the
     * event. A folder represents a specific calendar on the device.
     *
     * @return The folder of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    FolderId folderId() const;

    /*!
     * @brief Retrieves the ID of this @c CalendarEvent.
     *
     * @details The ID uniquely identifies a @c %CalendarEvent in the database.
     *
     * @return The ID of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    EventId id() const;

    /*!
     * @brief Retrieves the parent ID of this @c CalendarEvent.
     *
     * @details This attribute is only meaningful in events that are recurrence exceptions.
     *
     * A recurrence exception is a differing instance of a recurring event. For example,
     * a daily meeting at 2:00 PM is rescheduled to 3:00 PM on a given day. This
     * rescheduled occurrence is represented as an exception. It is stored in the
     * database as a separate event and it references the original recurring event by
     * using the parent ID.
     *
     * @return The parent ID of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    EventId parentId() const;

    /*!
     * @brief Retrieves the sequence number of this @c CalendarEvent.
     *
     * @return The sequence number of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    int sequence() const;

    /*!
     * @brief Retrieves the reminder time of this @c CalendarEvent.
     *
     * @details A reminder is an alert shown by the system's notification manager before the
     * event starts. This attribute determines the number of minutes between the alert
     * and the start time of the event.
     *
     * @return The reminder time of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    int reminder() const;

    /*!
     * @brief Indicates whether this @c CalendarEvent represents a birthday.
     *
     * @return @c True if this event represents a birthday, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isBirthday() const;

    /*!
     * @brief Indicates whether this @c CalendarEvent is an all-day event.
     *
     * @return @c True if this event is an all-day event, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isAllDay() const;

    /*!
     * @brief Retrieves the BBM conference data for this @c CalendarEvent.
     *
     * @details This function returns the BBM conference data that's associated with this
     * event. This data includes information such as available phone numbers, participant
     * code, and so on.
     *
     * @return The BBM conference data for this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConference bbmConference() const;

    /*!
     * @brief Retrieves the online conference data for this @c CalendarEvent.
     *
     * @details This function returns the online conference data that's associated
     * with this event.
     *
     * @return The online conference data for this @c %CalendarEvent.
     *
     * @since BlackBerry 10.3.0
     */
    OnlineConferenceData onlineConferenceData() const;

    /*!
     * @brief Retrieves the iCalendar data for this @c CalendarEvent.
     *
     * @details This function returns additional data that's available in events that are
     * created from iCalendar attachments.
     *
     * @return The iCalendar data for this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarData iCalendarData() const;

    /*!
     * @brief Retrieves the meeting status of this @c CalendarEvent.
     *
     * @details Possible return values for this function are:
     * - 0: not a meeting
     * - 1 and 9: is a meeting
     * - 3 and 11: meeting received
     * - 5 and 13: meeting is canceled
     * - 7 and 15: meeting is canceled and received
     *
     * @return The meeting status of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    int meetingStatus() const;

    /*!
     * @brief Retrieves the globally unique ID of this @c CalendarEvent.
     *
     * @details This ID is used by remote servers to uniquely identify the event.
     *
     * @return The globally unique ID of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    QString guid() const;

    /*!
     * @brief Retrieves the original start time of this @c CalendarEvent.
     *
     * @details This function returns the original start time from the CalendarEvent file.
     *
     * @return The original start time of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime originalStartTime() const;


    /*!
     * @brief Sets the start time of this @c CalendarEvent.
     *
     * @param startTime The new start time.
     *
     * @since BlackBerry 10.0.0
     */
    void setStartTime(const QDateTime& startTime);

    /*!
     * @brief Sets the end time of this @c CalendarEvent.
     *
     * @details The new end time should be greater than (that is, later than) the current
     * start time.
     *
     * @param endTime The new end time.
     *
     * @since BlackBerry 10.0.0
     */
    void setEndTime(const QDateTime& endTime);

    /*!
     * @brief Sets the body of this @c CalendarEvent.
     *
     * @param body The new body.
     *
     * @since BlackBerry 10.0.0
     */
    void setBody(const QString& body);

    /*!
     * @brief Sets the subject of this @c CalendarEvent.
     *
     * @param subject The new subject.
     *
     * @since BlackBerry 10.0.0
     */
    void setSubject(const QString& subject);

    /*!
     * @brief Sets the location of this @c CalendarEvent.
     *
     * @param location The new location.
     *
     * @since BlackBerry 10.0.0
     */
    void setLocation(const EventLocation& location);

    /*!
     * @brief Sets the time zone of this @c CalendarEvent.
     *
     * @param timezone The new time zone.
     *
     * @since BlackBerry 10.0.0
     */
    void setTimezone(const QString& timezone);

    /*!
     * @brief Sets the URL that's associated with this @c CalendarEvent.
     *
     * @param url The new URL.
     *
     * @since BlackBerry 10.0.0
     */
    void setUrl(const QString& url);

    /*!
     * @brief Sets the recurrence rule for this @c CalendarEvent.
     *
     * @param recurrence The new recurrence rule.
     *
     * @since BlackBerry 10.0.0
     */
    void setRecurrence(const Recurrence& recurrence);

    /*!
     * @brief Adds an attendee to this @c CalendarEvent.
     *
     * @details This function appends an @c Attendee object to the list of attendees for
     * this event.
     *
     * @param attendee The @c %Attendee object to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addAttendee(const Attendee& attendee);

    /*!
     * @brief Removes all attendees from this @c CalendarEvent.
     *
     * @since BlackBerry 10.0.0
     */
    void resetAttendees();

    /*!
     * @brief Sets the list of attendees for this @c CalendarEvent.
     *
     * @details This function clears the list of attendees for this @c %CalendarEvent
     * object and then populates it with attendees from the provided list.
     *
     * @param attendees The list of attendees to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setAttendees(const QList<Attendee>& attendees);

    /*!
     * @brief Sets the sensitivity of this @c CalendarEvent.
     *
     * @param sensitivity The new sensitivity.
     *
     * @since BlackBerry 10.0.0
     */
    void setSensitivity(Sensitivity::Type sensitivity);

    /*!
     * @brief Sets the busy status for this @c CalendarEvent.
     *
     * @param busyStatus The new busy status.
     *
     * @since BlackBerry 10.0.0
     */
    void setBusyStatus(BusyStatus::Type busyStatus);

    /*!
     * @brief Sets the account ID for this @c CalendarEvent.
     *
     * @param accountId The new account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccountId(AccountId accountId);

    /*!
     * @brief Sets the folder ID for this @c CalendarEvent.
     *
     * @param folderId The new folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setFolderId(FolderId folderId);

    /*!
     * @brief Sets the event ID for this @c CalendarEvent.
     *
     * @param id The new event ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setId(EventId id);

    /*!
     * @brief Sets the parent ID for this @c CalendarEvent.
     *
     * @param parentId The new parent ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setParentId(EventId parentId);

    /*!
     * @brief Sets the sequence number of this @c CalendarEvent.
     *
     * @param sequence The new sequence number.
     *
     * @since BlackBerry 10.0.0
     */
    void setSequence(int sequence);

    /*!
     * @brief Sets the reminder value of this @c CalendarEvent.
     *
     * @param reminder The new reminder value.
     *
     * @since BlackBerry 10.0.0
     */
    void setReminder(int reminder);

    /*!
     * @brief Sets whether this @c CalendarEvent represents a birthday.
     *
     * @param birthday If @c true this event represents a birthday, if @c false this
     * event does not represent a birthday.
     *
     * @since BlackBerry 10.0.0
     */
    void setBirthday(bool birthday);

    /*!
     * @brief Sets whether this @c CalendarEvent is an all-day event.
     *
     * @param allDay If @c true this event is an all-day event, if @c false this event
     * is not an all-day event.
     *
     * @since BlackBerry 10.0.0
     */
    void setAllDay(bool allDay);

    /*!
     * @brief Sets the BBM conference that's associated with this @c CalendarEvent.
     *
     * @param bbmConference The new BBM conference.
     *
     * @since BlackBerry 10.0.0
     */
    void setBbmConference(const BbmConference& bbmConference);

    /*!
     * @brief Sets the online conference data that's associated with this @c CalendarEvent.
     *
     * @param OnlineConference The new online conference.
     *
     * @since BlackBerry 10.3.0
     */
    void setOnlineConferenceData(const OnlineConferenceData& onlineConferenceData);

    /*!
     * @brief Sets the iCalendar data that's associated with this @c CalendarEvent.
     *
     * @param iCalendarData The new iCalendar data.
     *
     * @since BlackBerry 10.0.0
     */
    void setICalendarData(const ICalendarData& iCalendarData);

    /*!
     * @brief Sets the meeting status of this @c CalendarEvent.
     *
     * @param meetingStatus The new meeting status.
     *
     * @since BlackBerry 10.0.0
     */
    void setMeetingStatus(int meetingStatus);

    /*!
     * @brief Sets the globally unique identifier of this @c CalendarEvent.
     *
     * @param guid The new globally unique identifier.
     *
     * @since BlackBerry 10.0.0
     */
    void setGuid(const QString& guid);

    /*!
     * @brief Indicates whether this @c CalendarEvent is valid.
     *
     * @details This function determines whether the attributes of this @c %CalendarEvent
     * object have acceptable values.
     *
     * @return @c True if this @c %CalendarEvent is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the intended status of this @c CalendarEvent.
     *
     * @details The intended status represents the creation busy status of the event.
     *
     * @return The intended status of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.1.0
     */
    BusyStatus::Type intendedStatus() const;

    /*!
     * @brief Sets the intended status for this @c CalendarEvent.
     *
     * @param busyStatus The new intended busy status.
     *
     * @since BlackBerry 10.1.0
     */
    void setIntendedStatus(BusyStatus::Type busyStatus);

    /*!
     * @brief Retrieves the categories of this @c CalendarEvent.
     *
     * @return The list of categories that are associated to this @c CalendarEvent.
     *         There may be zero, one or more categories that can be associated to an event.
     *
     * @since BlackBerry 10.3.0
     */
    QList<QString> categories() const;

    /*!
     * @brief Retrieves the delegator of this @c CalendarEvent.
     *
     * @return The delegator of this @c %CalendarEvent.
     *         It could be the delegator's email or a non-empty string.
     *
     * @since BlackBerry 10.2.0
     */
    QString delegator() const;

    /*!
     * @brief Sets the delegator for this @c CalendarEvent.
     *
     * @param delegator The delegator for this @c CalendarEvent.
     *
     * @since BlackBerry 10.2.0
     */
    void setDelegator(const QString& delegator);

    /*!
     * @brief Retrieves whether this @c CalendarEvent is a valid meeting request or not.
     *
     * @details This function returns whether this is a valid meeting request or not.
     *          This is supported in ActiveSync.
     *
     * @return @c True if this is a valid meeting request, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isMeetingRequest() const;

    /*!
     * @brief Sets whether this @c CalendarEvent is a valid meeting request or not.
     *
     * @param isMeetingRequest @c True if this is a valid meeting request, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void setIsMeetingRequest(bool isMeetingRequest);

    /*!
     * @brief Sets the original start time of this @c CalendarEvent.
     *
     * @param originalStartTime The new original start time.
     *
     * @since BlackBerry 10.2.0
     */
    void setOriginalStartTime(const QDateTime& originalStartTime);
    /*!
     * @brief Retrieves the owner status of this @c CalendarEvent.
     *
     * @details The owner status represents owner's response to the meeting.
     *
     * @return The owner status of this @c CalendarEvent.
     *
     * @since BlackBerry 10.2.0
     */
    AttendeeStatus::Type ownerStatus() const;
    /*!
     * @brief Sets the owner status for this @c CalendarEvent.
     *
     * @param ownerStatus The new owner status.
     *
     * @since BlackBerry 10.2.0
     */
    void setOwnerStatus(AttendeeStatus::Type ownerStatus);

    /*!
     * @brief Retrieves the default reminder time of this @c CalendarEvent.
     *
     * @details The default reminder is assigned to events without reminders
     * (event.reminder() returns -1). The purpose of a default reminder is to make
     * sure that the user still receives an alert in case the reminder was not set
     * by mistake. This attribute is initialized with the value of the Meeting Reminder
     * item in the calendar app's Settings / General page.
     *
     * @return The default reminder time of this @c %CalendarEvent.
     *
     * @since BlackBerry 10.3.1
     */
    int defaultReminder() const;

    /*!
     * @brief Sets the default reminder time of this @c CalendarEvent.
     *
     * @param defaultReminder The new default reminder time.
     *
     * @since BlackBerry 10.3.1
     */
    void setDefaultReminder(int defaultReminder);

private:
    QSharedDataPointer<CalendarEventPrivate> d_ptr;
    friend class CalendarEventPrivate;
};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_CALENDAREVENT_HPP

