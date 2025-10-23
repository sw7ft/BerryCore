
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ATTENDEESEARCHPARAMETERS_HPP
#define BB_PIM_CALENDAR_ATTENDEESEARCHPARAMETERS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QList>

namespace bb {
namespace pim {
namespace calendar {

class EventKey;
class AttendeeSearchParametersPrivate;

/*!
 * @brief The @c AttendeeSearchParameters class represents parameters for attendee search.
 *
 * @details This class encapsulates the arguments that are required when you call
 * @c CalendarService::attendees(). This function retrieves a list of people who are participating
 * in the specified set of meetings.
 * 
 * You can use an @c %AttendeeSearchParameters to store a set of meetings that you want to use
 * in an attendee search. For example, if you wanted to retrieve the list of attendees for all
 * meetings that occur on a particular date, you can add the meetings to an
 * @c %AttendeeSearchParameters object and then provide this object as an argument when you call
 * @c %CalendarService::attendees().
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
class BB_PIM_EXPORT AttendeeSearchParameters {
public:

    /*!
     * @brief Constructs a new @c AttendeeSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeSearchParameters();

    /*!
     * @brief Destroys this @c AttendeeSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    ~AttendeeSearchParameters();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c AttendeeSearchParameters containing exactly the
     * same values as the provided @c %AttendeeSearchParameters.
     *
     * @param other The @c %AttendeeSearchParameters to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeSearchParameters(const AttendeeSearchParameters& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c AttendeeSearchParameters
     * into this @c %AttendeeSearchParameters.
     *
     * @param other The @c %AttendeeSearchParameters from which to copy all values.
     *
     * @return A reference to this @c %AttendeeSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeSearchParameters& operator=(const AttendeeSearchParameters& other);

    /*!
     * @brief Retrieves the list of events keys for this @c AttendeeSearchParameters.
     *
     * @details An event key is a unique identifier for an event in the calendar database. This
     * function returns a list of event keys, and the corresponding events are searched when you
     * call @c CalendarService::attendees() with this @c %AttendeeSearchParameters object.
     *
     * @return The list of events for this @c %AttendeeSearchParameters.
     *
     * @since BlackBerry 10.0.0
     */
    QList<EventKey> events() const;


    /*!
     * @brief Adds an event key to this @c AttendeeSearchParameters.
     *
     * @details This function appends a new event key to the list of event keys for this
     * @c %AttendeeSearchParameters object.
     *
     * @param event The event key to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addEvent(const EventKey& event);

    /*!
     * @brief Clears the event keys for this @c AttendeeSearchParameters.
     *
     * @details This function removes all event keys from this @c %AttendeeSearchParameters
     * object.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEvents();

    /*!
     * @brief Sets the list of event keys for this @c AttendeeSearchParameters.
     *
     * @details This function clears the list of event keys for this @c %AttendeeSearchParameters
     * object and then populates it with @c EventKey objects from the provided list.
     *
     * @param events The new list of event keys.
     *
     * @since BlackBerry 10.0.0
     */
    void setEvents(const QList<EventKey>& events);

    /*!
     * @brief Indicates whether this @c AttendeeSearchParameters is valid.
     *
     * @details This function determines whether the attributes of this @c %AttendeeSearchParameters
     * object have acceptable values.
     *
     * @return @c true if this @c %AttendeeSearchParameters is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<AttendeeSearchParametersPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ATTENDEESEARCHPARAMETERS_HPP

