
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_DAYOFWEEK_HPP
#define BB_PIM_CALENDAR_DAYOFWEEK_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c DayOfWeek class includes possible days of the week for calendar events. 
 *
 * @details Days of the week include the standard days (Monday, Tuesday, and so on),
 * the last day of a month, or an undefined day.
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT DayOfWeek {
public:
    /*!
     * @brief An enumeration of possible days of the week.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an undefined day of the week.
         *
         * @details This is the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Undefined = -1,
        /*!
         * @brief Indicates that an event occurs on Sunday.
         *
         * @since BlackBerry 10.0.0
         */
        Sunday = 1,
        /*!
         * @brief Indicates that an event occurs on Monday.
         *
         * @since BlackBerry 10.0.0
         */
        Monday = 2,
        /*!
         * @brief Indicates that an event occurs on Tuesday.
         *
         * @since BlackBerry 10.0.0
         */
        Tuesday = 4,
        /*!
         * @brief Indicates that an event occurs on Wednesday.
         *
         * @since BlackBerry 10.0.0
         */
        Wednesday = 8,
        /*!
         * @brief Indicates that an event occurs on Thursday.
         *
         * @since BlackBerry 10.0.0
         */
        Thursday = 16,
        /*!
         * @brief Indicates that an event occurs on Friday.
         *
         * @since BlackBerry 10.0.0
         */
        Friday = 32,
        /*!
         * @brief Indicates that an event occurs on Saturday.
         *
         * @since BlackBerry 10.0.0
         */
        Saturday = 64,
        /*!
         * @brief Indicates that an event occurs on the last day of a month.
         *
         * @since BlackBerry 10.0.0
         */
        LastDayInMonth = 127,
    };


private:
    DayOfWeek();
    ~DayOfWeek();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_DAYOFWEEK_HPP

