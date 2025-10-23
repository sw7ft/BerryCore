
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ATTENDEESTATUS_HPP
#define BB_PIM_CALENDAR_ATTENDEESTATUS_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c AttendeeStatus class includes possible statuses for attendees.
 *
 * @details An attendee of a meeting (represented by the @c Attendee class) can have one of
 * several different statuses. The attendee can have accepted the meeting invitation, declined
 * the meeting invitation, or be tentative for the meeting. The attendee can also not have
 * responded to the meeting invitation.
 *
 * @see Attendee
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT AttendeeStatus {
public:
    /*!
     * @brief An enumeration of supported statuses for attendees.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an unknown status.
         * 
         * @details This is the default status.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,
        /*!
         * @brief Indicates that the attendee is tentative and will attempt to attend the
         * meeting.
         *
         * @since BlackBerry 10.0.0
         */
        Tentative = 2,
        /*!
         * @brief Indicates that the attendee has accepted the meeting invitation.
         *
         * @since BlackBerry 10.0.0
         */
        Accepted = 3,
        /*!
         * @brief Indicates that the attendee has declined the meeting invitation.
         *
         * @since BlackBerry 10.0.0
         */
        Declined = 4,
        /*!
         * @brief Indicates that the attendee has not responded to the meeting invitation.
         *
         * @since BlackBerry 10.0.0
         */
        NotResponded = 5,
    };


private:
    AttendeeStatus();
    ~AttendeeStatus();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ATTENDEESTATUS_HPP

