
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_RECURRENCE_HPP
#define BB_PIM_CALENDAR_RECURRENCE_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/Frequency>
#include <bb/pim/calendar/WeekStartDay>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QList>

namespace bb {
namespace pim {
namespace calendar {

class RecurrencePrivate;

/*!
 * @brief The @c Recurrence class represents recurrence data for calendar events.
 *
 * @details This class specifies how an event repeats. An event that happens over and
 * over (for example, every day, or on working days, or every Monday, Wednesday
 * and Friday) has an associated recurrence rule (that is, @c event.recurrence().isValid()
 * returns @c true).
 * 
 * A recurrence may be infinite (no end date or number of occurrences specified). A
 * finite recurrence has an end date or a number of occurrences.
 * 
 * This class is modeled after the ActiveSync Recurrence element
 * (http://msdn.microsoft.com/en-us/library/ee219748%28v=EXCHG.80%29.aspx). It can
 * express as many recurrence patterns as the ActiveSync element, but not as many
 * as the iCalendar RRULE element (http://www.kanzaki.com/docs/ical/rrule.html).
 * For example, it's not possible to define a rule for hourly recurrence with this
 * class.
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
class BB_PIM_EXPORT Recurrence {
public:

    /*!
     * @brief Constructs a new @c Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    Recurrence();

    /*!
     * @brief Destroys this @c Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    ~Recurrence();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c Recurrence containing exactly the
     * same values as the provided @c %Recurrence.
     *
     * @param other The @c %Recurrence to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Recurrence(const Recurrence& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Recurrence
     * into this @c %Recurrence.
     *
     * @param other The @c %Recurrence from which to copy all values.
     *
     * @return A reference to this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    Recurrence& operator=(const Recurrence& other);

    /*!
     * @brief Retrieves the start time of this @c Recurrence.
     *
     * @return The start time of this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime start() const;

    /*!
     * @brief Retrieves the end time of this @c Recurrence.
     *
     * @return The end time of this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime end() const;

    /*!
     * @brief Retrieves the until date of this @c Recurrence.
     *
     * @details This function returns the date when the recurrence ends. A finite
     * recurrence should have an until date or a defined number of occurrences.
     *
     * @return The until date of this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime until() const;

    /*!
     * @brief Retrieves the exception dates for this @c Recurrence.
     *
     * @details This function returns the dates of occurrences that were modified
     * (recurrence exceptions) or deleted (recurrence exclusions).
     *
     * @return The exception dates for this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QDateTime> exceptions() const;

    /*!
     * @brief Retrieves the recurrence frequency of this @c Recurrence.
     *
     * @details The frequency is represented by a @c Frequency object. This object
     * indicates the type of recurrence, and can be one of the following:
     * - daily
     * - weekly
     * - monthly on a day of the week (for example, the first Monday every month)
     * - monthly on a date (for example, the 15th day every month)
     * - yearly on a week day of a month (for example, the second Sunday of May)
     * - yearly on a date (for example, July 1st)
     *
     * @return The recurrence frequency of this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    Frequency::Type frequency() const;

    /*!
     * @brief Retrieves the recurrence interval of this @c Recurrence.
     *
     * @details The recurrence interval is the number of times a rule must generate a
     * possible date to produce an occurrence.
     * 
     * A recurrence rule and a start date yield a set of possible dates. For example, a
     * daily event that repeats five times starting at July 23rd 2012 has five possible
     * dates. With the default interval value of one, the occurrences for this event will be
     * the 23rd, 24th, 25th, 26th and 27th. With a value of two, the occurrences will
     * be 24th, 26th, 28th, 30th and 1st of August.
     *
     * @return The recurrence interval of this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    int interval() const;

    /*!
     * @brief Retrieves the recurrence firstDay of the week of this @c Recurrence.
     *
     * @details The recurrence firstDay specifies the day on which the workweek starts.
     * Valid values are MO, TU, WE, TH, FR, SA and SU. This is significant
     * when a WEEKLY RRULE has an interval greater than 1, and a BYDAY rule
     * part is specified. This is also significant when in a YEARLY RRULE
     * when a BYWEEKNO rule part is specified. The default value is SU.
     * The value is not significant in other types of recurrences.
     * Possible values are:
     *   0 - Sunday (SU)
     *   1 - Monday (MO)
     *   2 - Tuesday (TU)
     *   3 - Wednesday (WE)
     *   4 - Thursday (TH)
     *   5 - Friday (FR)
     *   6 - Saturday (SA)
     *
     * @return The recurrence firstDay of the week this @c %Recurrence.
     *
     * @since BlackBerry 10.2.0
     */
    WeekStartDay::Type firstDay() const;

    /*!
     * @brief Retrieves the number of occurrences of this @c Recurrence.
     *
     * @details This function returns the number of repetitions in a finite recurrence.
     *
     * @return The number of occurrences of this @c %Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    int numberOfOccurrences() const;

    /*!
     * @brief Retrieves the days of the week when this @c Recurrence repeats.
     *
     * @details This value is meaningful only when the frequency is weekly, monthly
     * on a week day, or yearly on a week day of a month.
     * 
     * Each week day has a corresponding value:
     * 1 - Sunday
     * 2 - Monday
     * 4 - Tuesday
     * 8 - Wednesday
     * 16 - Thursday
     * 32 - Friday
     * 64 - Saturday
     * 127 - Last day in the month
     * 
     * The values can be OR'ed together to have rules with multiple days. For example,
     * a recurrence that happens on Tuesday and Thursday should have a value of 4 + 16 = 20.
     *
     * @return The days of the week when this @c %Recurrence repeats.
     *
     * @since BlackBerry 10.0.0
     */
    int dayInWeek() const;

    /*!
     * @brief Retrieves the day of the month when this @c Recurrence repeats.
     *
     * @details This value is meaningful only when the frequency is monthly on a date
     * or yearly on a date.
     *
     * @return The day of the month when this @c %Recurrence repeats.
     *
     * @since BlackBerry 10.0.0
     */
    int dayInMonth() const;

    /*!
     * @brief Retrieves the week in the month when this @c Recurrence repeats.
     *
     * @details This value is meaningful only when the frequency is monthly on a week day
     * or yearly on a week day of a month.
     * 
     * For example, the recurrence rule for an event on the second Sunday of May would
     * have a value of 2 in this attribute.
     *
     * @return The week in the month when this @c %Recurrence repeats.
     *
     * @since BlackBerry 10.0.0
     */
    int weekInMonth() const;

    /*!
     * @brief Retrieves the month in the year when this @c Recurrence repeats.
     *
     * @details This value is meaningful only when the frequency is yearly on a
     * date or yearly on a week day of a month.
     *
     * @return The month in the year when this @c %Recurrence repeats.
     *
     * @since BlackBerry 10.0.0
     */
    int monthInYear() const;

    /*!
     * @brief Retrieves the dates of the occurrences for this @c Recurrence.
     *
     * @details This function returns the dates of occurrences.
     *
     * @return The occurrence dates for this @c %Recurrence.
     */
    QList<QDateTime> occurrenceDates() const;

    /*!
     * @brief Sets the start time of this @c Recurrence.
     *
     * @param start The new start time.
     *
     * @since BlackBerry 10.0.0
     */
    void setStart(const QDateTime& start);

    /*!
     * @brief Sets the end time of this @c Recurrence.
     *
     * @param end The new end time.
     *
     * @since BlackBerry 10.0.0
     */
    void setEnd(const QDateTime& end);

    /*!
     * @brief Sets the until date of this @c Recurrence.
     *
     * @param until The new until time.
     *
     * @since BlackBerry 10.0.0
     */
    void setUntil(const QDateTime& until);

    /*!
     * @brief Adds an exception date to this @c Recurrence.
     *
     * @details This function appends a new exception date to the list of existing
     * exception dates.
     *
     * @param exception The exception date to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addException(const QDateTime& exception);

    /*!
     * @brief Removes all of the exception dates from this @c Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    void resetExceptions();

    /*!
     * @brief Sets the list of exception dates for this @c Recurrence.
     *
     * @details This function replaces the current list of exception dates with the
     * provided list.
     *
     * @param exceptions The list of exception dates to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setExceptions(const QList<QDateTime>& exceptions);

    /*!
     * @brief Sets the recurrence frequency of this @c Recurrence.
     *
     * @param frequency The new recurrence frequency.
     *
     * @since BlackBerry 10.0.0
     */
    void setFrequency(Frequency::Type frequency);

    /*!
     * @brief Sets the recurrence interval of this @c Recurrence.
     *
     * @param interval The new recurrence interval.
     *
     * @since BlackBerry 10.0.0
     */
    void setInterval(int interval);

    /*!
     * @brief Sets the recurrence firstDay of the week of this @c Recurrence.
     *
     * @param firstDay The new firstDay of the week.
     *
     * @since BlackBerry 10.2.0
     */
    void setFirstDay(WeekStartDay::Type firstDay);

    /*!
     * @brief Sets the number of occurrences of this @c Recurrence.
     *
     * @param numberOfOccurrences The new number of occurrences.
     *
     * @since BlackBerry 10.0.0
     */
    void setNumberOfOccurrences(int numberOfOccurrences);

    /*!
     * @brief Sets the day of the week for this @c Recurrence.
     *
     * @param dayInWeek The new day of the week.
     *
     * @since BlackBerry 10.0.0
     */
    void setDayInWeek(int dayInWeek);

    /*!
     * @brief Sets the day of the month for this @c Recurrence.
     *
     * @param dayInMonth The new day of the month.
     *
     * @since BlackBerry 10.0.0
     */
    void setDayInMonth(int dayInMonth);

    /*!
     * @brief Sets the week of the month for this @c Recurrence.
     *
     * @param weekInMonth The new week of the month.
     *
     * @since BlackBerry 10.0.0
     */
    void setWeekInMonth(int weekInMonth);

    /*!
     * @brief Sets the month of the year for this @c Recurrence.
     *
     * @param monthInYear The new month of the year.
     *
     * @since BlackBerry 10.0.0
     */
    void setMonthInYear(int monthInYear);

    /*!
     * @brief Adds an occurrence date to this @c Recurrence.
     *
     * @details This function appends a new occurrence date to the list of existing
     * occurrence dates.
     *
     * @param occurrenceDate The occurrence date to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addOccurrenceDate(const QDateTime& occurrenceDate);

    /*!
     * @brief Removes all of the occurrence dates from this @c Recurrence.
     *
     * @since BlackBerry 10.0.0
     */
    void resetOccurrenceDates();

    /*!
     * @brief Sets the list of occurrence dates for this @c Recurrence.
     *
     * @details This function replaces the current list of occurrence dates with the
     * provided list.
     *
     * @param occurrenceDates The list of occurrence dates to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setOccurrenceDates(const QList<QDateTime>& occurrenceDates);

    /*!
     * @brief Indicates whether this @c Recurrence is valid.
     *
     * @details This function determines whether the attributes of this @c %Recurrence
     * object have acceptable values.
     *
     * @return @c true if this @c %Recurrence is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<RecurrencePrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_RECURRENCE_HPP

