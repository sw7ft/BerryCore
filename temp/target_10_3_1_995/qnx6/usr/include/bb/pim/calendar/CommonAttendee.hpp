
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_COMMONATTENDEE_HPP
#define BB_PIM_CALENDAR_COMMONATTENDEE_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace calendar {

class Attendee;
class AnalyticsStats;
class CommonAttendeePrivate;

/*!
 * @brief The @c CommonAttendee class represents an attendee that is common between the
 * user and a specified person.
 *
 * @details You can use the @c CalendarService::commonAttendees() function to retrieve
 * a list of people that have attended meetings with both the user and a person that
 * you specify. You use the @c emails attribute of an @c AnalyticsParams object to
 * identify the person that should have participated in meetings along with the user.
 * 
 * The @c %commonAttendees() function returns a list of @c %CommonAttendee objects. Each
 * @c %CommonAttendee object includes information such as the actual attendee data
 * (represented by an @c Attendee object) and statistics for the common attendee.
 *
 * @see CalendarService, Attendee
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT CommonAttendee {
public:

    /*!
     * @brief Constructs a new @c CommonAttendee.
     *
     * @since BlackBerry 10.0.0
     */
    CommonAttendee();

    /*!
     * @brief Destroys this @c CommonAttendee.
     *
     * @since BlackBerry 10.0.0
     */
    ~CommonAttendee();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c CommonAttendee containing exactly the
     * same values as the provided @c %CommonAttendee.
     *
     * @param other The @c %CommonAttendee to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    CommonAttendee(const CommonAttendee& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CommonAttendee
     * into this @c %CommonAttendee.
     *
     * @param other The @c %CommonAttendee from which to copy all values.
     *
     * @return A reference to this @c %CommonAttendee.
     *
     * @since BlackBerry 10.0.0
     */
    CommonAttendee& operator=(const CommonAttendee& other);

    /*!
     * @brief Retrieves the @c Attendee object that's associated with this @c CommonAttendee.
     *
     * @details This function returns an @c %Attendee object that contains the actual
     * attendee data.
     *
     * @return The @c %Attendee object that's associated with this @c %CommonAttendee.
     *
     * @since BlackBerry 10.0.0
     */
    Attendee attendee() const;

    /*!
     * @brief Retrieves statistics for this @c CommonAttendee.
     *
     * @details This function returns an @c AnalyticsStats object that contains information
     * such as the number of meetings with the user and date of the most recent meeting.
     *
     * @return Statistics for this @c %CommonAttendee.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsStats stats() const;


    /*!
     * @brief Sets the @c Attendee object that's associated with this @c CommonAttendee.
     *
     * @param attendee The @c %Attendee object to associate.
     *
     * @since BlackBerry 10.0.0
     */
    void setAttendee(const Attendee& attendee);

    /*!
     * @brief Sets the statistics for this @c CommonAttendee.
     *
     * @param stats The statistics to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setStats(const AnalyticsStats& stats);

    /*!
     * @brief Indicates whether this @c CommonAttendee is valid.
     *
     * @details This function determines whether the attributes of this @c %CommonAttendee
     * object have acceptable values.
     *
     * @return @c true if this @c %CommonAttendee is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<CommonAttendeePrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_COMMONATTENDEE_HPP

