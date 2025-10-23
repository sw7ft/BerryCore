/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKERECURRENCERULE_HPP
#define BB_SYSTEM_INVOKERECURRENCERULE_HPP

#include <bb/system/Global>
#include <QSharedDataPointer>
#include <bb/system/InvokeDateTime>
#include <bb/system/InvokeRecurrenceRuleFrequency>
#include <bb/system/InvokeRecurrenceRuleLimit>

namespace bb
{
namespace system
{

class InvokeRecurrenceRulePrivate;

/*!
 * @headerfile InvokeRecurrenceRule.hpp <bb/system/InvokeRecurrenceRule>
 *
 *
 * @brief Encapsulates a recurrence rule, which defines a schedule for triggering a headless application.
 *
 * @details The recurrence is invoked by a timer registration. The headless target is invoked on the specified time slot with the action
 * 'bb.action.system.TIMER_FIRED'. At a minimum, a recurrence rule is described by the following 3 parameters:
 *  - Frequency, which specifies the frequency of repeating events. It has one of values enumerated in @c #InvokeRecurrenceRuleFrequency
 *    with default value of @c InvokeRecurrenceRuleFrequency::None.
 *  - Interval, which specifies the interval of repetition for the rule (with default value of 1)
 *  - Start Date/Time, which specifies the date at which the recurrence starts. It defaults to the present date/time (now).
 *
 * The interval is a positive integer identifying the interval of repetition for the rule.
 * For example, interval equal to 1 means every hour for an @c InvokeRecurrenceRuleFrequency::Hourly rule. For a
 * @c InvokeRecurrenceRuleFrequency::Daily rule an interval of 2 means every other day.
 * Additionally, the rule can be further modified by specifying recurrences such as minutes of the hour,
 * hours of the day, days of the month and months of the year.If minutes of the hour, hours of the day, days of the month and
 * months of the year are missing, the missing values are derived from the corresponding values in the start date.
 *
 * The frequency used to define a recurrence rules may generate recurrence
 * instances with an invalid date (e.g., February 30) or nonexistent local time
 * (e.g., 1:30 AM on a day where the local time is moved forward by an hour at
 * 1:00 AM). These invalid recurrence instances will be skipped.
 *
 * Optionally, it can have a date limit or a count limit. A date limit
 * specifies the date at which the recurrence ends. The count limit specifies the number of times
 * the recurrence rule will trigger the headless application.
 *
 * The following sample code demonstrates how to register a daily recurrent
 * timer that fires at 10AM and 5PM, beginning January 1st, 2014 in local time zone. Note that error handling is omitted for
 * clarity.
 *
 * @code
 *    QDate sDate(2014, 1, 1);  //January 1st, 2014
 *    QTime sTime(0, 0);  //midnight
 *    InvokeDateTime startTime(sDate,sTime);
 *    InvokeRecurrenceRule recurrenceRule(bb::system::InvokeRecurrenceRuleFrequency::Daily, startTime);
 *    QSet<int> setHours;
 *    setHours << 10 << 17 ;
 *    recurrenceRule.setHoursOfDay(setHours);
 *
 *    InvokeTimerRequest timerRequest;
 *    QString timerId = "1234-unique-id";
 *    if (recurrenceRule.isValid()) {
 *      timerRequest.set(timerId,  recurrenceRule, "com.example.RecRuleTestService");
 *       bb::system::InvokeReply _reply = _invokeManager->registerTimer(timerRequest);
 *       if (_reply != NULL) {
 *           connect(_reply, SIGNAL(finished()), this, SLOT(finishedFired()));
 *       }
 *    }
 *
 * @endcode
 *
 * If a Recurrence Rule defines a schedule that leads to generating time slots that are less than six minutes
 * apart, this rule will be rejected and registration will fail.
 *
 * It is important to mention that Recurrence Rules have to be explicitly deregistered.
 * Otherwise, the recurrence rule timer would stay active forever. It means that @c #timerId used for timer registration must be
 * saved by developer to be used later for deregistering that Recurrence Rule. It is developer's responsibility to make sure that their
 * application logic executes at some point the following piece of code:
 * @code
 *    bb::system::InvokeReply _reply = _invokeManager->deregisterTimer(timerId);
 * @endcode
 *
 * Note that the deregisterTimer() call is asynchronious. To be notified when it completes, add:
 * @code
 *    if (_reply != NULL) {
 *       connect(_reply, SIGNAL(finished()), this, SLOT(finishedFired()));
 *     }
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_SYSTEM_EXPORT InvokeRecurrenceRule
{


public:

    /*!
     * @brief Creates a new @c #InvokeRecurrenceRule object
     *
     * @details Creates a new @c #InvokeRecurrenceRule object with start date set to "Now" and frequency set to @c InvokeRecurrenceFrequency::None
     *
     * @since BlackBerry 10.3.0
     */
    InvokeRecurrenceRule();

    /*!
     * @brief Creates a new @c #InvokeRecurrenceRule object
     * with the provided frequency.
     *
     * @details Start time is set to "Now" of local time zone. Interval is set to 1.
     *
     * @param frequency Specifies one of the frequencies from @c #bb::system::InvokeRecurrenceRuleFrequency::Type
     *
     * @since BlackBerry 10.3.0
     */
    explicit InvokeRecurrenceRule(bb::system::InvokeRecurrenceRuleFrequency::Type frequency);

    /*!
     * @brief Creates a new @c #InvokeRecurrenceRule object
     * with the provided frequency and start time.
     *
     * @details  Interval is set to 1.
     *
     * @param frequency Specifies one of the frequencies from @c #bb::system::InvokeRecurrenceRuleFrequency::Type
     * @param startTime The @c #InvokeDateTime representing the start time for the rule.
     *
     * @since BlackBerry 10.3.0
     */
    explicit InvokeRecurrenceRule(bb::system::InvokeRecurrenceRuleFrequency::Type frequency,
                                  const InvokeDateTime &startTime);

    /*!
     * @brief Creates a copy of an existing @c #InvokeRecurrenceRule object.
     *
     * @param other The source @c #InvokeRecurrenceRule object to copy.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeRecurrenceRule(const InvokeRecurrenceRule &other);

    /*!
     * @brief Destroys this @c #InvokeRecurrenceRule object.
     *
     * @since BlackBerry 10.3.0
     */
    ~InvokeRecurrenceRule();

    /*!
     * @brief Copies the data of an existing @c #InvokeRecurrenceRule object
     * to this object.
     *
     * @param other The source @c #InvokeRecurrenceRule object to copy.
     *
     * @return The @c #InvokeRecurrenceRule instance.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeRecurrenceRule& operator=(const InvokeRecurrenceRule &other);


    /*!
     * @brief Sets the frequency
     *
     * @details Specifies the frequency of repeating events. The frequence of the event is defined by frequency type and the interval
     *
     * @param frequency  The frequency from @c #InvokeRecurrenceRuleFrequency
     *
     * @since BlackBerry 10.3.0
     */
    void setFrequency(bb::system::InvokeRecurrenceRuleFrequency::Type frequency);

    /*!
     * @brief Sets the date limit of a recurrence rule.
     *
     * @param date  The date limit as @c #InvokeDateTime.
     * Setting invalid date makes the recurrence rule invalid.
     *
     * @since BlackBerry 10.3.0
     */
    void setLimit(const InvokeDateTime &date);

    /*!
     * @brief Sets the count limit of a recurrence rule.
     *
     * @param count  The count limit to set. A value of zero will reset the
     * limit. A negative value will make the rule invalid, i.e. the method @c #InvokeRecurrenceRule.isValid() will return "false"
     *
     * @since BlackBerry 10.3.0
     */
    void setLimit(int count);

    /*!
     * @brief Clears the limit
     *
     * @details Calling this method resets both count and date limit. As result, the rule repeats indefinitely until it gets unregistered.
     *
     * @since BlackBerry 10.3.0
     */
    void clearLimit();

    /*!
     * @brief Sets the interval
     *
     * @details The interval is a positive integer identifying the interval of repetition for the rule. The default interval
     * is related to the interval type specified by one of the values of as @c #InvokeRecurrenceRuleFrequency.
     *
     * @param interval  The interval. A negative or 0 value will make the rule invalid, If this method is never called the default interval of "1"
     * will be used for a specific rule.
     *
     * @since BlackBerry 10.3.0
     */
    void setInterval(int interval);


    /*!
     * @brief Sets the minutes of the hour
     *
     * @param minutes  A list of minutes within an hour when the rule is applied
     *
     * @since BlackBerry 10.3.0
     */
    void setMinutesOfHour(const QSet<int> &minutes);

    /*!
     * @brief Sets the hours of the day
     *
     * @param hours  A list of hours within an day when the rule is applied.
     *
     * @since BlackBerry 10.3.0
     */
    void setHoursOfDay(const QSet<int> &hours);

    /*!
     * @brief Sets the days of the week
     *
     * @param daysOfWeek  A list of days  within an week when the rule is applied.
     *
     * @since BlackBerry 10.3.0
     */
    void setDaysOfWeek(const QSet<int> &daysOfWeek);

    /*!
     * @brief Sets the days of the month
     *
     * @param daysOfMonth   A list of days within an month when the rule is applied.
     *
     * @since BlackBerry 10.3.0
     */
    void setDaysOfMonth(const QSet<int> &daysOfMonth);

    /*!
     * @brief Sets the months of the year
     *
     * @param monthsOfYear   A list of months within an year when the rule is applied.
     *
     * @since BlackBerry 10.3.0
     */
    void setMonthsOfYear(const QSet<int> &monthsOfYear);

    /*!
     * @brief Sets the start time of the rule
     *
     * @param startTime The @c #InvokeDateTime representing the start time
     * for the rule.
     *
     * @since BlackBerry 10.3.0
     */
    void setStartTime(const InvokeDateTime &startTime);

    /*!
     * @brief Returns the frequency.
     *
     * @details The method returns the frequency that was previously set.
     *
     * @return frequency that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    bb::system::InvokeRecurrenceRuleFrequency::Type frequency() const;

    /*!
     * @brief Returns the limit type.
     *
     * @details The method returns the limit type that was previously set.
     *
     * @return limit type that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    bb::system::InvokeRecurrenceRuleLimit::Type limitType() const;

    /*!
     * @brief Return the date limit.
     *
     * @details The method returns the date limit that was previously set.
     *
     * @return date limit that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    bb::system::InvokeDateTime dateLimit() const;

    /*!
     * @brief Return the count limit.
     *
     * @details The method returns the count limit that was previously set.
     *
     * @return count limit that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    int countLimit() const;

    /*!
     * @brief Return the interval.
     *
     * @details The method returns the interval that was previously set.
     *
     * @return interval that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    int interval() const;

    /*!
     * @brief Return the minutesOfHour.
     *
     * @details The method returns the minutesOfHour that was previously set.
     *
     * @return minutesOfHour that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QSet<int> minutesOfHour() const;

    /*!
     * @brief Return the hoursOfDay.
     *
     * @details The method returns the hoursOfDay that was previously set.
     *
     * @return hoursOfDay that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QSet<int> hoursOfDay() const;

    /*!
     * @brief Return the daysOfWeek.
     *
     * @details The method returns the daysOfWeek that was previously set.
     *
     * @return daysOfWeek that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QSet<int> daysOfWeek() const;

    /*!
     * @brief Return the daysOfMonth.
     *
     * @details The method returns the daysOfMonth that was previously set.
     *
     * @return daysOfMonth that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QSet<int> daysOfMonth() const;

    /*!
     * @brief Return the monthsOfYear.
     *
     * @details The method returns the monthsOfYear that was previously set.
     *
     * @return monthsOfYear that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QSet<int> monthsOfYear() const;

    /*!
     * @brief Return the assigned start time.
     *
     * @return start time that was previously set
     *
     * @since BlackBerry 10.3.0
     *
     */
    bb::system::InvokeDateTime startTime() const;

    /*!
     * @brief Returns true if this @c #InvokeRecurrenceRule object is valid.
     *
     * @details The rule is considered invalid in one of the following is true:
     * - frequency is @c #InvokeRecurrenceRuleFrequency::None
     * - start date/time is not valid (method @cstartTime().isValid() returns false
     * - interval is not a positive number
     * -
     *
     * @return true if valid, false otherwise
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;




private:
//!@cond PRIVATE
    QSharedDataPointer<InvokeRecurrenceRulePrivate> d;
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKERECURRENCERULE_HPP
