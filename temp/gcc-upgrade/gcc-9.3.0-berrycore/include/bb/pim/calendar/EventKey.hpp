
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_EVENTKEY_HPP
#define BB_PIM_CALENDAR_EVENTKEY_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QList>

namespace bb {
namespace pim {
namespace calendar {

class EventKeyPrivate;

/*!
 * @brief The @c EventKey class represents a database key for calendar events.
 *
 * @details This class includes attributes (such as event ID, account ID, and dates)
 * that uniquely identify an event in the calendar database.
 * 
 * @c %EventKey objects are used by the @c EventSearchParameters class, which itself
 * is used when you want to search for specific events in the calendar database. When
 * you call @c EventSearchParameters::events(), a list of @c %EventKey objects is
 * returned. Each object represents a particular event to search for. You can call
 * @c EventSearchParameters::addEvent() or @c EventSearchParameters::setEvents() to
 * add or set events to search for.
 * 
 * @see EventSearchParameters
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT EventKey {
public:

    /*!
     * @brief Constructs a new @c EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    EventKey();

    /*!
     * @brief Destroys this @c EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    ~EventKey();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c EventKey containing exactly the
     * same values as the provided @c %EventKey.
     *
     * @param other The @c %EventKey to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    EventKey(const EventKey& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c EventKey
     * into this @c %EventKey.
     *
     * @param other The @c %EventKey from which to copy all values.
     *
     * @return A reference to this @c %EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    EventKey& operator=(const EventKey& other);

    /*!
     * @brief Retrieves the event ID of this @c EventKey.
     *
     * @details The event ID uniquely identifies an event in a particular account. Two
     * events in different accounts may have the same event ID.
     *
     * @return The event ID of this @c %EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    EventId eventId() const;

    /*!
     * @brief Retrieves the account ID of this @c EventKey.
     *
     * @details The account ID is the database identifier for a particular account.
     *
     * @return The account ID of this @c %EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId accountId() const;

    /*!
     * @brief Retrieves the recurrence dates for this @c EventKey.
     *
     * @details This is an optional attribute that's used to select occurrences of a
     * recurring event by date. A query with dates is faster because it overrides the
     * recurrence expansion mechanism.
     *
     * @return The recurrence dates for this @c %EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QDateTime> dates() const;


    /*!
     * @brief Sets the event ID of this @c EventKey.
     *
     * @param eventId The new event ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setEventId(EventId eventId);

    /*!
     * @brief Sets the account ID of this @c EventKey.
     *
     * @param accountId The new account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccountId(AccountId accountId);

    /*!
     * @brief Adds a new date to the list of recurrence dates for this @c EventKey.
     *
     * @param date The date to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addDate(const QDateTime& date);

    /*!
     * @brief Removes all recurrence dates from this @c EventKey.
     *
     * @since BlackBerry 10.0.0
     */
    void resetDates();

    /*!
     * @brief Sets the list of recurrence dates for this @c EventKey.
     *
     * @details This function replaces the current list of recurrence dates with the
     * provided list.
     *
     * @param dates The new list of recurrence dates.
     *
     * @since BlackBerry 10.0.0
     */
    void setDates(const QList<QDateTime>& dates);

    /*!
     * @brief Indicates whether this @c EventKey is valid.
     *
     * @details This function determines whether the attributes of this @c %EventKey
     * object have acceptable values.
     *
     * @return @c true if this @c %EventKey is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<EventKeyPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_EVENTKEY_HPP

