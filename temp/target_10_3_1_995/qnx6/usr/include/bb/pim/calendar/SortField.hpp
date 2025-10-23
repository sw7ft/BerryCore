
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_SORTFIELD_HPP
#define BB_PIM_CALENDAR_SORTFIELD_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c SortField class includes possible fields that can be used to sort calendar
 * events.
 *
 * @details When you retrieve events using functions in the @c CalendarService class
 * (such as @c CalendarService::events()), you provide an @c EventSearchParameters object
 * that includes information about the results that you want. You can set a @c %SortField
 * in the @c %EventSearchParameters that describes what fields you want to use to sort the
 * search results.
 * 
 * @see CalendarService, EventSearchParameters
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SortField {
public:
    /*!
     * @brief An enumeration of possible sort fields for calendar events.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an undefined sort field.
         *
         * @details This is the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Undefined = 0,
        /*!
         * @brief Indicates that events are sorted by guid.
         *
         * @since BlackBerry 10.0.0
         */
        Guid = 1,
        /*!
         * @brief Indicates that events are sorted by subject.
         *
         * @since BlackBerry 10.0.0
         */
        Subject = 2,
        /*!
         * @brief Indicates that events are sorted by location.
         *
         * @since BlackBerry 10.0.0
         */
        Location = 3,
        /*!
         * @brief Indicates that events are sorted by start time.
         *
         * @since BlackBerry 10.0.0
         */
        StartTime = 4,
        /*!
         * @brief Indicates that events are sorted by end time.
         *
         * @since BlackBerry 10.0.0
         */
        EndTime = 5,
    };


private:
    SortField();
    ~SortField();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_SORTFIELD_HPP

