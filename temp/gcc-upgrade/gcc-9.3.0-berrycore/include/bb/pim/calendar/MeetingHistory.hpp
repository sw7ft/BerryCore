
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_MEETINGHISTORY_HPP
#define BB_PIM_CALENDAR_MEETINGHISTORY_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/AttendeeStatus>
#include <QSharedDataPointer>
#include <QDateTime>

namespace bb {
namespace pim {
namespace calendar {

class MeetingHistoryPrivate;

/*!
 * @brief The @c MeetingHistory class represents the history of an iCalendar event.
 *
 * @details This class contains data related to the changes done to a meeting that was
 * created from an iCalendar file. This data includes information such as owner
 * attendance status, status date, and updated date.
 * 
 * You can retrieve the meeting history from an iCalendar event by calling
 * @c ICalendarData::history(). This function returns a @c %MeetingHistory object
 * with the history information.
 * 
 * @see ICalendarData
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MeetingHistory {
public:

    /*!
     * @brief Constructs a new @c MeetingHistory.
     *
     * @since BlackBerry 10.0.0
     */
    MeetingHistory();

    /*!
     * @brief Destroys this @c MeetingHistory.
     *
     * @since BlackBerry 10.0.0
     */
    ~MeetingHistory();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c MeetingHistory containing exactly the
     * same values as the provided @c %MeetingHistory.
     *
     * @param other The @c %MeetingHistory to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MeetingHistory(const MeetingHistory& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MeetingHistory
     * into this @c %MeetingHistory.
     *
     * @param other The @c %MeetingHistory from which to copy all values.
     *
     * @return A reference to this @c %MeetingHistory.
     *
     * @since BlackBerry 10.0.0
     */
    MeetingHistory& operator=(const MeetingHistory& other);

    /*!
     * @brief Retrieves the owner's attendee status.
     *
     * @details This function returns the attendance status for the organizer of the
     * meeting.
     *
     * @return The host's attendee status.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeStatus::Type ownerStatus() const;

    /*!
     * @brief Retrieves the timestamp for status updates.
     *
     * @details This function returns the time of the most recent update to the owner's
     * status.
     *
     * @return The timestamp for status updates.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime statusDate() const;

    /*!
     * @brief Retrieves the sequence number for the meeting.
     *
     * @details The sequence number is a number that increases each time the event is
     * updated. For example, this number changes when the user receives a newer iCalendar
     * representation of the event as an attachment.
     *
     * @return The sequence number for the meeting.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int meetingSequence() const;

    /*!
     * @brief Retrieves the timestamp for general updates.
     *
     * @details This function returns the time when the organizer last updated the meeting.
     *
     * @return The timestamp for general updates.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime updatedDate() const;

    /*!
     * @brief Retrieves the timestamp for cancellation.
     *
     * @details This function returns the time when the organizer cancelled the meeting.
     *
     * @return The timestamp for cancellation.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime canceledDate() const;


    /*!
     * @brief Sets the owner's attendee status.
     *
     * @param ownerStatus The new owner attendee status.
     *
     * @since BlackBerry 10.0.0
     */
    void setOwnerStatus(AttendeeStatus::Type ownerStatus);

    /*!
     * @brief Sets the date for the last status update.
     *
     * @param statusDate The new date for the last status update.
     *
     * @since BlackBerry 10.0.0
     */
    void setStatusDate(const QDateTime& statusDate);

    /*!
     * @brief Sets the meeting sequence number.
     *
     * @param meetingSequence The new meeting sequence number.
     *
     * @since BlackBerry 10.0.0
     */
    void setMeetingSequence(unsigned int meetingSequence);

    /*!
     * @brief Sets the date for the last update to the meeting.
     *
     * @param updatedDate The new date for the last update to the meeting.
     *
     * @since BlackBerry 10.0.0
     */
    void setUpdatedDate(const QDateTime& updatedDate);

    /*!
     * @brief Sets the date that the meeting was cancelled.
     *
     * @param canceledDate The new date that the meeting was cancelled.
     *
     * @since BlackBerry 10.0.0
     */
    void setCanceledDate(const QDateTime& canceledDate);

    /*!
     * @brief Indicates whether this @c MeetingHistory is valid.
     *
     * @details This function determines whether the attributes of this @c %MeetingHistory
     * object have acceptable values.
     *
     * @return @c true if this @c %MeetingHistory is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<MeetingHistoryPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_MEETINGHISTORY_HPP

