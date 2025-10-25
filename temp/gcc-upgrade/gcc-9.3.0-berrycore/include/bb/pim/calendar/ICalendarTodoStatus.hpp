
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDARTODOSTATUS_HPP
#define BB_PIM_CALENDAR_ICALENDARTODOSTATUS_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief ICalendarTodoStatus enum class
 *
 * @details
 * ICalendarTodoStatus enumeration
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ICalendarTodoStatus {
public:
    enum Type {
        /*!
         * @brief To-do needs action
         *
         * @details
         * Indicates the to-do needs action.
         *
         * @since BlackBerry 10.0.0
         */
        NeedsAction = 0,
        /*!
         * @brief To-do completed
         *
         * @details
         * Indicates the to-do is completed.
         *
         * @since BlackBerry 10.0.0
         */
        Completed = 1,
        /*!
         * @brief To-do in process
         *
         * @details
         * Indicates the user is working on the to-do.
         *
         * @since BlackBerry 10.0.0
         */
        InProcess = 2,
        /*!
         * @brief To-do cancelled
         *
         * @details
         * Indicates the to-do was abandoned.
         *
         * @since BlackBerry 10.0.0
         */
        Cancelled = 3,
    };


private:
    ICalendarTodoStatus();
    ~ICalendarTodoStatus();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDARTODOSTATUS_HPP

