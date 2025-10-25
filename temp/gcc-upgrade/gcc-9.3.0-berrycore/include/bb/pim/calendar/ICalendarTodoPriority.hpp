
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDARTODOPRIORITY_HPP
#define BB_PIM_CALENDAR_ICALENDARTODOPRIORITY_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief ICalendarTodoPriority enum class
 *
 * @details
 * ICalendarTodoPriority enumeration
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ICalendarTodoPriority {
public:
    enum Type {
        /*!
         * @brief High priority
         *
         * @details
         * Indicates a high-priority to-do.
         *
         * @since BlackBerry 10.0.0
         */
        High = 0,
        /*!
         * @brief Medium priority
         *
         * @details
         * Indicates a medium-priority to-do.
         *
         * @since BlackBerry 10.0.0
         */
        Medium = 1,
        /*!
         * @brief Low priority
         *
         * @details
         * Indicates a low-priority to-do.
         *
         * @since BlackBerry 10.0.0
         */
        Low = 2,
    };


private:
    ICalendarTodoPriority();
    ~ICalendarTodoPriority();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDARTODOPRIORITY_HPP

