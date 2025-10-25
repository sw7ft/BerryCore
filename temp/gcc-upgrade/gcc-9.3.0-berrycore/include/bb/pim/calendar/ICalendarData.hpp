
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDARDATA_HPP
#define BB_PIM_CALENDAR_ICALENDARDATA_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class MeetingHistory;
class ICalendarDataPrivate;

/*!
 * @brief The @c ICalendarData class represents iCalendar file data for a calendar event.
 *
 * @details This class includes additional information for a calendar event that's
 * created from an iCalendar attachment, such as method, event sequence, and history.
 * 
 * You can call @c CalendarService::parseICalendarData() to parse an iCalendar file. This
 * function returns a @c CalendarEvent object that's created using information from the
 * iCalendar file. To retrieve information about the original iCalendar file (in the form
 * of an @c %ICalendarData object), you can call @c CalendarEvent::iCalendarData().
 * 
 * @see CalendarService, CalendarEvent
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ICalendarData {
public:

    /*!
     * @brief Constructs a new @c ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarData();

    /*!
     * @brief Destroys this @c ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    ~ICalendarData();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c ICalendarData containing exactly the
     * same values as the provided @c %ICalendarData.
     *
     * @param other The @c %ICalendarData to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarData(const ICalendarData& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ICalendarData
     * into this @c %ICalendarData.
     *
     * @param other The @c %ICalendarData from which to copy all values.
     *
     * @return A reference to this @c %ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarData& operator=(const ICalendarData& other);

    /*!
     * @brief Retrieves the iCalendar method of this @c ICalendarData.
     *
     * @details This function returns the method attribute in the iCalendar file: REPLY,
     * REQUEST, or CANCEL.
     *
     * @return The iCalendar method of this @c %ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    QString method() const;

    /*!
     * @brief Retrieves the sequence number of this @c ICalendarData.
     *
     * @details This function returns the attribute in the iCalendar file that increases
     * for each new version of the event.
     *
     * @return The sequence number of this @c %ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int eventSequence() const;

    /*!
     * @brief Retrieves the meeting history of this @c ICalendarData.
     *
     * @details This function returns the local database history of the event that's
     * associated with the iCalendar file.
     *
     * @return The meeting history of this @c %ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    MeetingHistory history() const;

    /*!
     * @brief Retrieves the comments of this @c ICalendarData.
     * 
     * @details This function returns the comments from the iCalendar file.
     * 
     * @return The comments of this @c %ICalendarData.
     *
     * @since BlackBerry 10.0.0
     */
    QString comment() const;

    /*!
     * @brief Retrieves the original start time of this @c ICalendarData.
     *
     * @details This function returns the original start time from the iCalendar file.
     *
     * @return The original start time of this @c %ICalendarData.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime originalStartTime() const;

    /*!
     * @brief Retrieves the MIME type for the body of this @c ICalendarData.
     *
     * @details This function returns the MIME type for the body from the iCalendar file.
     *
     * @return The MIME type for the body of this @c %ICalendarData.
     *
     * @since BlackBerry 10.2.0
     */
    QString bodyMimeType() const;

    /*!
     * @brief Sets the iCalendar method of this @c ICalendarData.
     *
     * @param method The new iCalendar method.
     *
     * @since BlackBerry 10.0.0
     */
    void setMethod(const QString& method);

    /*!
     * @brief Sets the sequence number of this @c ICalendarData.
     *
     * @param eventSequence The new sequence number.
     *
     * @since BlackBerry 10.0.0
     */
    void setEventSequence(unsigned int eventSequence);

    /*!
     * @brief Sets the meeting history of this @c ICalendarData.
     *
     * @param history The new meeting history.
     *
     * @since BlackBerry 10.0.0
     */
    void setHistory(const MeetingHistory& history);

    /*!
     * @brief Sets the comments of this @c ICalendarData.
     * 
     * @param comment The new comments.
     *
     * @since BlackBerry 10.0.0
     */
    void setComment(const QString& comment);

    /*!
     * @brief Sets the original start time of this @c ICalendarData.
     *
     * @param originalStartTime The new original start time.
     *
     * @since BlackBerry 10.2.0
     */
    void setOriginalStartTime(const QDateTime& originalStartTime);

    /*!
     * @brief Sets the MIME type for the body of this @c ICalendarData.
     *
     * @param bodyMimeType The new MIME type.
     *
     * @since BlackBerry 10.2.0
     */
    void setBodyMimeType(const QString& bodyMimeType);

    /*!
     * @brief Indicates whether this @c ICalendarData is valid.
     *
     * @details This function determines whether the attributes of this @c %ICalendarData
     * object have acceptable values.
     *
     * @return @c True if this @c %ICalendarData is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<ICalendarDataPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDARDATA_HPP

