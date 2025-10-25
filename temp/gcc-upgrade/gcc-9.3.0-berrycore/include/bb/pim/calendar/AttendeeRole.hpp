
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ATTENDEEROLE_HPP
#define BB_PIM_CALENDAR_ATTENDEEROLE_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c AttendeeRole class includes possible roles for attendees.
 *
 * @details An attendee of a meeting (represented by the @c Attendee class) can have one of
 * several different roles. The attendee can be the chair of the meeting, a required
 * participant, or an optional participant. The attendee can also be a non-participant in
 * the meeting, and this role indicates that the attendee is listed for information
 * purposes only. 
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
class BB_PIM_EXPORT AttendeeRole {
public:
    /*!
     * @brief An enumeration of supported roles for attendees.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an invalid role.
         * 
         * @details This is the default role.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = 0,
        /*!
         * @brief Indicates that the attendee is the chair of the meeting.
         *
         * @details This role means that the attendee is the organizer of the meeting.
         *
         * @since BlackBerry 10.0.0
         */
        Chair = 1,
        /*!
         * @brief Indicates that the attendee is a required participant.
         *
         * @since BlackBerry 10.0.0
         */
        ReqParticipant = 2,
        /*!
         * @brief Indicates that the attendee is an optional participant.
         *
         * @since BlackBerry 10.0.0
         */
        OptParticipant = 3,
        /*!
         * @brief Indicates that the attendee is a non-participant.
         *
         * @details This role means that the attendee is listed for information purposes
         * only.
         *
         * @since BlackBerry 10.0.0
         */
        NonParticipant = 4,
    };


private:
    AttendeeRole();
    ~AttendeeRole();

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ATTENDEEROLE_HPP

