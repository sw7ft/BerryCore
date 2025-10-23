
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_DETAILLEVEL_HPP
#define BB_PIM_CALENDAR_DETAILLEVEL_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c DetailLevel class includes the possible levels of detail for calendar
 * views.
 *
 * @details The level of detail determines how many fields in an event are populated.
 * For example, the @c Monthly detail level includes only information for the following
 * fields:
 * - @c accountId
 * - @c allDay
 * - @c busyStatus
 * - @c endTime
 * - @c folderId
 * - @c id
 * - @c parentId
 * - @c startTime
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT DetailLevel {
public:
    /*!
     * @brief An enumeration of possible levels of detail.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates the monthly detail level.
         *
         * @details This is the lowest detail level, and is used for monthly calendar
         * views. The event fields that are populated are @c accountId, @c allDay,
         * @c busyStatus, @c endTime, @c folderId, @c id, @c parentId, and @c startTime.
         *
         * @since BlackBerry 10.0.0
         */
        Monthly = 1,
        /*!
         * @brief Indicates the weekly detail level.
         *
         * @details This detail level is used for weekly calendar views. The event fields
         * that are populated are those in the @c Monthly level plus @c birthday and
         * @c subject.
         *
         * @since BlackBerry 10.0.0
         */
        Weekly = 2,
        /*!
         * @brief Indicates the full detail level.
         *
         * @details In this detail level, all fields are populated.
         *
         * @since BlackBerry 10.0.0
         */
        Full = 3,
        /*!
         * @brief Indicates the agenda detail level.
         *
         * @details This detail level is used for agenda calendar views. The event fields
         * that are populated are those in the @c Weekly level plus @c bbmConference,
         * @c guid, @c location, @c meetingSequence, @c meetingStatus, @c recurrence,
         * @c reminder, @c sensitivity, @c timezone, and @c url.
         *
         * @since BlackBerry 10.0.0
         */
        Agenda = 4,
        /*!
         * @brief Indicates the weekly status detail level.
         *
         * @details This detail level is used for weekly calendar views. The event fields
         * that are populated are those in the @c Weekly level plus @c owner response status.
         *
         * @since BlackBerry 10.2.0
         */
        WeeklyStatus = 5,
        /*!
         * @brief Indicates the agenda status detail level.
         *
         * @details This detail level is used for agenda calendar views. The event fields
         * that are populated are those in the @c Agenda level plus @c owner response status.
         *
         * @since BlackBerry 10.2.0
         */
        AgendaStatus = 6,
        /*!
         * @brief Indicates the attendee detail level.
         *
         * @details This detail level is used to return for every event the list of attendees.
         *
         * @since BlackBerry 10.3.0
         */
        Attendee = 7,
    };


private:
    DetailLevel();
    ~DetailLevel();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_DETAILLEVEL_HPP

