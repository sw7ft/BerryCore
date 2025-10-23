
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_WEEK_START_DAY_HPP
#define BB_PIM_CALENDAR_WEEK_START_DAY_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c WeekStartDay class includes possible recurrence week start days
 * for calendar events.
 *
 * @details This class provides values for the firstDay attribute in the @c Recurrence
 * class.
 * 
 * @see Recurrence
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PIM_EXPORT WeekStartDay {
public:
    /*!
     * @brief An enumeration of possible recurrence week start days.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief List of valid days to be defined as start week day.
         * Use Sunday as the default value.
         *
         * @since BlackBerry 10.2.0
         */
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6,
    };


private:
    WeekStartDay();
    ~WeekStartDay();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_WEEK_START_DAY_HPP

