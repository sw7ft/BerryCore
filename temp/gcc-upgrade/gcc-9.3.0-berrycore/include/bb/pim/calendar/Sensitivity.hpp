
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_SENSITIVITY_HPP
#define BB_PIM_CALENDAR_SENSITIVITY_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c Sensitivity class includes possible sensitivity levels for calendar
 * events.
 * 
 * @details A calendar event can be marked with various sensitivity levels, including
 * normal, personal, private, and confidential. You can retrieve the sensitivity level
 * of an event by calling @c CalendarEvent::sensitivity().
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
class BB_PIM_EXPORT Sensitivity {
public:
    /*!
     * @brief An enumeration of possible sensitivity levels.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates a normal sensitivity level.
         *
         * @details This level is used for unrestricted events.
         *
         * @since BlackBerry 10.0.0
         */
        Normal = 0,
        /*!
         * @brief Indicates a personal sensitivity level.
         *
         * @since BlackBerry 10.0.0
         */
        Personal = 1,
        /*!
         * @brief Indicates a private sensitivity level.
         *
         * @since BlackBerry 10.0.0
         */
        Private = 2,
        /*!
         * @brief Indicates a confidential sensitivity level.
         *
         * @details This level is the maximum sensitivity level for events.
         *
         * @since BlackBerry 10.0.0
         */
        Confidential = 3,
    };


private:
    Sensitivity();
    ~Sensitivity();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_SENSITIVITY_HPP

