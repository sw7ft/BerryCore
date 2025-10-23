
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_BUSYSTATUS_HPP
#define BB_PIM_CALENDAR_BUSYSTATUS_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c BusyStatus class includes possible free/busy statuses for an event.
 * 
 * @details An event can be marked as free time, tentative, busy, or out-of-office.
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
class BB_PIM_EXPORT BusyStatus {
public:
    /*!
     * @brief An enumeration of possible free/busy statuses.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates free time.
         *
         * @details This value is used to indicate that the event represents free time
         * (the event's owner is available).
         *
         * @since BlackBerry 10.0.0
         */
        Free = 0,
        /*!
         * @brief Indicates a tentative event.
         *
         * @details This value indicates that an event may or may not happen (the owner
         * may be available).
         *
         * @since BlackBerry 10.0.0
         */
        Tentative = 1,
        /*!
         * @brief Indicates busy time.
         *
         * @details This value indicates that the event is confirmed (the owner is busy).
         *
         * @since BlackBerry 10.0.0
         */
        Busy = 2,
        /*!
         * @brief Indicates out-of-office status.
         *
         * @details This value indicates that the event owner is out of the office.
         *
         * @since BlackBerry 10.0.0
         */
        OutOfOffice = 3,
        /*!
         * @brief Indicates non defined status.
         *
         * @details This value indicates that the value is not defined.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown = 100,
    };


private:
    BusyStatus();
    ~BusyStatus();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_BUSYSTATUS_HPP

