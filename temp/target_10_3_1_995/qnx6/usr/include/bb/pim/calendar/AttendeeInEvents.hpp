
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ATTENDEEINEVENTS_HPP
#define BB_PIM_CALENDAR_ATTENDEEINEVENTS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QList>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class EventKey;
class AttendeeInEventsPrivate;

/*!
 * @brief The @c AttendeeInEvents class represents a participant of an event.
 *
 * @details This class includes information about an event participant, such as the attendee type,
 * name, email address, and so on. This class is very similar to the @c Attendee class, but an
 * @c %AttendeeInEvents object contains information that specifies what events that attendee
 * participates in. You can use functions such as @c AttendeeInEvents::events() and
 * @c AttendeeInEvents::addEvent() to retrieve and manipulate the events that this attendee
 * participates in.
 * 
 * You can retrieve a list of an event's participants by calling @c CalendarService::attendees(). This
 * function returns a list of @c %AttendeeInEvents objects, each of which corresponds to a participant
 * of an event.
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
class BB_PIM_EXPORT AttendeeInEvents {
public:

    /*!
     * @brief Constructs a new @c AttendeeInEvents.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeInEvents();

    /*!
     * @brief Destroys this @c AttendeeInEvents.
     *
     * @since BlackBerry 10.0.0
     */
    ~AttendeeInEvents();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c AttendeeInEvents containing exactly the same values as the
     * provided @c %AttendeeInEvents.
     *
     * @param other The @c %AttendeeInEvents to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeInEvents(const AttendeeInEvents& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c AttendeeInEvents into this
     * @c %AttendeeInEvents.
     *
     * @param other The @c %AttendeeInEvents from which to copy all values.
     *
     * @return A reference to this @c %AttendeeInEvents.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeInEvents& operator=(const AttendeeInEvents& other);

    /*!
     * @brief Retrieves the email address of this @c AttendeeInEvents.
     *
     * @return The email address of this @c %AttendeeInEvents.
     *
     * @since BlackBerry 10.0.0
     */
    QString email() const;

    /*!
     * @brief Retrieves the name of this @c AttendeeInEvents.
     *
     * @return The name of this @c %AttendeeInEvents.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the list of events that this @c AttendeeInEvents participates in.
     *
     * @details This function returns a list of event keys, each of which represents an event that this
     * attendee participates in. An event key contains the primary key for an event in the calendar
     * database.
     *
     * @return The list of events that this @c %AttendeeInEvents participates in.
     *
     * @since BlackBerry 10.0.0
     */
    QList<EventKey> events() const;


    /*!
     * @brief Sets the email address of this @c AttendeeInEvents.
     *
     * @param email The new email address.
     *
     * @since BlackBerry 10.0.0
     */
    void setEmail(const QString& email);

    /*!
     * @brief Sets the name of this @c AttendeeInEvents.
     *
     * @param name The new name.
     *
     * @since BlackBerry 10.0.0
     */
    void setName(const QString& name);

    /*!
     * @brief Adds an event key to this @c AttendeeInEvents.
     *
     * @details This function appends a new event key to the list of event keys for this
     * @c %AttendeeInEvents object.
     *
     * @param event The event key to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addEvent(const EventKey& event);

    /*!
     * @brief Clears the event keys for this @c AttendeeInEvents.
     *
     * @details This function removes all event keys from this @c %AttendeeInEvents object.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEvents();

    /*!
     * @brief Sets the list of event keys for this @c AttendeeInEvents.
     *
     * @details This function clears the list of event keys for this @c %AttendeeInEvents object and
     * then populates it with @c EventKey objects from the provided list.
     *
     * @param events The new list of event keys.
     *
     * @since BlackBerry 10.0.0
     */
    void setEvents(const QList<EventKey>& events);

    /*!
     * @brief Indicates whether this @c AttendeeInEvents is valid.
     *
     * @details This function determines whether the attributes of this @c %AttendeeInEvents object have
     * acceptable values.
     *
     * @return @c true if this @c %AttendeeInEvents is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<AttendeeInEventsPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ATTENDEEINEVENTS_HPP

