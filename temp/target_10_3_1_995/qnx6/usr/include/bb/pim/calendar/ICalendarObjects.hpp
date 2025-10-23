
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDAROBJECTS_HPP
#define BB_PIM_CALENDAR_ICALENDAROBJECTS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/message/Keys>
#include <QSharedDataPointer>
#include <QList>

namespace bb {
namespace pim {
namespace calendar {

class CalendarEvent;
class ICalendarTodo;
class ICalendarObjectsPrivate;

/*!
 * @brief The @c ICalendarObjects class represents a container for iCalendar objects.
 *
 * @details This class holds objects that are constructed by functions that read data
 * in an iCalendar file, such as @c CalendarService::readICalendarFile() and
 * @c CalendarService::retrieveICalendarAttachment(). You must parse an iCalendar file
 * using these types of functions before you can retrieve event information from it.
 * 
 * This class contains information that represents both events and tasks (or to-dos).
 * You can call @c events() to retrieve a @c QList of events, and you can manipulate
 * the events in an @c %ICalendarObjects object using functions such as @c addEvent(),
 * @c setEvents(), and @c resetEvents(). Similarly, you can call @c todos() to retrieve
 * a @c %QList of tasks, and you can manipulate the tasks using functions such as
 * @c addTodo(), @c setTodos(), and @c resetTodos().
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ICalendarObjects {
public:

    /*!
     * @brief Constructs a new @c ICalendarObjects.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects();

    /*!
     * @brief Destroys this @c ICalendarObjects.
     *
     * @since BlackBerry 10.0.0
     */
    ~ICalendarObjects();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c ICalendarObjects containing exactly the
     * same values as the provided @c %ICalendarObjects.
     * 
     * @param other The @c %ICalendarObjects to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects(const ICalendarObjects& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ICalendarObjects
     * into this @c %ICalendarObjects.
     * 
     * @param other The @c %ICalendarObjects from which to copy all values.
     *
     * @return A reference to this @c %ICalendarObjects.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects& operator=(const ICalendarObjects& other);

    /*!
     * @brief Retrieves the events in the iCalendar file.
     *
     * @details This function returns the calendar events that were parsed from
     * the iCalendar file. Events in an iCalendar file are specified using the
     * VEVENT identifier.
     *
     * @return A list of events from the iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    QList<CalendarEvent> events() const;

    /*!
     * @brief Retrieves the tasks (to-dos) in the iCalendar file.
     *
     * @details This function returns the tasks (to-dos) that were parsed from
     * the iCalendar file. Tasks in an iCalendar file are specified using the
     * VTODO identifier.
     *
     * @return A list of tasks from the iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ICalendarTodo> todos() const;

    /*!
     * @brief Retrieves the attachment ID that provided the iCalendar objects.
     *
     * @details This function returns the ID for the attachment that provided the
     * iCalendar objects. The @c ICalendarObjects instance returned by
     * @c CalendarService::retrieveICalendarAttachment() will have a non-zero value
     * if the message has an iCalendar attachment that is not yet on the device. It's
     * possible to request the download of the attachment by calling
     * @c bb::pim::message::MessageService::downloadAttachment().
     *
     * @return The attachment ID that provided the iCalendar objects.
     *
     * @since BlackBerry 10.3.0
     */
    bb::pim::message::AttachmentKey attachmentKey() const;

    /*!
     * @brief Adds an event to the list of iCalendar events.
     *
     * @details This function adds a new event at the end of the existing list of
     * iCalendar events.
     *
     * @param event The event to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addEvent(const CalendarEvent& event);

    /*!
     * @brief Removes all events.
     *
     * @details This function clears the list of iCalendar events.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEvents();

    /*!
     * @brief Sets the list of events.
     *
     * @details This function changes the list of iCalendar events to the provided
     * set of events.
     *
     * @param events The new list of events.
     *
     * @since BlackBerry 10.0.0
     */
    void setEvents(const QList<CalendarEvent>& events);

    /*!
     * @brief Adds a task (to-do) to the list of iCalendar tasks.
     *
     * @details This function adds a new task at the end of the existing list of
     * iCalendar tasks.
     *
     * @param todo The task to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addTodo(const ICalendarTodo& todo);

    /*!
     * @brief Removes all tasks (to-dos).
     *
     * @details This function clears the list of iCalendar tasks.
     *
     * @since BlackBerry 10.0.0
     */
    void resetTodos();

    /*!
     * @brief Sets the list of tasks (to-dos).
     *
     * @details This function changes the list of iCalendar tasks to the provided
     * set of tasks.
     *
     * @param todos The new list of tasks.
     *
     * @since BlackBerry 10.0.0
     */
    void setTodos(const QList<ICalendarTodo>& todos);

    /*!
     * @brief Sets the attachment ID that provided the iCalendar objects.
     *
     * @details This function assigns an attachment ID to this @c ICalendarObjects
     * object.
     *
     * @param attachmentKey The attachment ID to set.
     *
     * @since BlackBerry 10.3.0
     */
    void setAttachmentKey(bb::pim::message::AttachmentKey attachmentKey);

    /*!
     * @brief Indicates whether this @c ICalendarObjects is valid.
     *
     * @details This function determines whether the attributes of this @c %ICalendarObjects
     * object have acceptable values.
     *
     * @return @c true if this @c %ICalendarObjects is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<ICalendarObjectsPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDAROBJECTS_HPP

