
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_FREQUENCY_HPP
#define BB_PIM_CALENDAR_FREQUENCY_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c Frequency class includes possible recurrence frequencies for calendar
 * events.
 *
 * @details This class provides values for the frequency attribute in the @c Recurrence
 * class.
 * 
 * @see Recurrence
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Frequency {
public:
    /*!
     * @brief An enumeration of possible recurrence frequencies.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an undefined frequency.
         *
         * @details This is the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Undefined = -1,
        /*!
         * @brief Indicates that a recurring event occurs daily.
         *
         * @since BlackBerry 10.0.0
         */
        Daily = 0,
        /*!
         * @brief Indicates that a recurring event occurs on a specific day of the week.
         *
         * @since BlackBerry 10.0.0
         */
        Weekly = 1,
        /*!
         * @brief Indicates that a recurring event occurs on a certain day of every
         * month.
         *
         * @details The day in the month is defined by @c Recurrence::dayInMonth().
         *
         * @since BlackBerry 10.0.0
         */
        Monthly = 2,
        /*!
         * @brief Indicates that a recurring event occurs every month on a certain day of
         * a certain week.
         *
         * @details The week in the month is defined by @c Recurrence::weekInMonth(). The
         * day in the week is defined by @c Recurrence::dayInWeek().
         *
         * @since BlackBerry 10.0.0
         */
        MonthlyAtWeekDay = 3,
        /*!
         * @brief Indicates that a recurring event occurs every year, on a certain day
         * of a month.
         *
         * @details The day is defined by @c Recurrence::dayInMonth(). The month is
         * defined by @c Recurrence::monthInYear().
         *
         * @since BlackBerry 10.0.0
         */
        Yearly = 5,
        /*!
         * @brief Indicates that a recurring event occurs every year, on a certain week
         * day, week, and month.
         *
         * @details The week day is defined by @c Recurrence::dayInWeek(). The week is
         * defined by @c Recurrence::weekInMonth(). The month is defined by
         * @c Recurrence::monthInYear().
         *
         * @since BlackBerry 10.0.0
         */
        YearlyAtWeekDayOfMonth = 6,
    };


private:
    Frequency();
    ~Frequency();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_FREQUENCY_HPP

