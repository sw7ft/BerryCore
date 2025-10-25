
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_CALENDARSETTINGS_HPP
#define BB_PIM_CALENDAR_CALENDARSETTINGS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class CalendarSettingsPrivate;

/*!
 * @brief The @c CalendarSettings class contains system settings for calendars.
 *
 * @details This class contains settings that are relevant to calendar applications, such as
 * snooze time for calendar notifications, current system time zone, and whether the device
 * time is in 24-hour format.
 * 
 * You can retrieve the current calendar settings by calling @c CalendarService::settings().
 *
 * @see CalendarService
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT CalendarSettings {
public:

    /*!
     * @brief Constructs a new @c CalendarSettings.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarSettings();

    /*!
     * @brief Destroys this @c CalendarSettings.
     *
     * @since BlackBerry 10.0.0
     */
    ~CalendarSettings();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c CalendarSettings containing exactly the
     * same values as the provided @c %CalendarSettings.
     *
     * @param other The @c %CalendarSettings to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarSettings(const CalendarSettings& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CalendarSettings
     * into this @c %CalendarSettings.
     *
     * @param other The @c %CalendarSettings from which to copy all values.
     *
     * @return A reference to this @c %CalendarSettings.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarSettings& operator=(const CalendarSettings& other);

    /*!
     * @brief Retrieves the current snooze time for calendar notifications.
     *
     * @details The system notification manager shows alerts for upcoming events. The user
     * can snooze an alert, which means that the manager will close it and then show it
     * again after a period of time. This time interval is the snooze time.
     *
     * @return The current snooze time.
     *
     * @since BlackBerry 10.0.0
     */
    int snoozeTime() const;

    /*!
     * @brief Retrieves the ID of the current time zone.
     *
     * @details This function returns the database ID for the device's current time zone.
     *
     * @return The ID of the current time zone.
     *
     * @since BlackBerry 10.0.0
     */
    QString timezoneDatabaseId() const;

    /*!
     * @brief Retrieves the name of the current time zone.
     *
     * @details This function returns the name of the device's current time zone.
     *
     * @return The name of the current time zone.
     *
     * @since BlackBerry 10.0.0
     */
    QString currentSystemTimezone() const;

    /*!
     * @brief Indicates whether the device time is in 24-hour format.
     *
     * @return @c true if the device time is in 24-hour format, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool is24HourFormat() const;

    /*!
     * @brief Retrieves the default meeting reminder.
     *
     * @details This function indicates the time when the device shows an alert
     * to remind the user that an event is about to start. The value is the number
     * of minutes before the beginning of the event.
     *
     * @return The meeting reminder value.
     *
     * @since BlackBerry 10.3.1
     */
    int meetingReminder() const;

    /*!
     * @brief Retrieves the default meeting reminder for all-day events.
     *
     * @details This function indicates the time when the device shows an alert
     * to remind the user that an all-day event is about to start. The value is
     * the number of minutes before the beginning of the event.
     *
     * @return The all-day meeting reminder value.
     *
     * @since BlackBerry 10.3.1
     */
    int allDayMeetingReminder() const;


    /*!
     * @brief Sets the snooze time for calendar notifications.
     *
     * @param snoozeTime The new snooze time.
     *
     * @since BlackBerry 10.0.0
     */
    void setSnoozeTime(int snoozeTime);

    /*!
     * @brief Sets the ID of the current time zone.
     *
     * @param timezoneDatabaseId The new time zone ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setTimezoneDatabaseId(const QString& timezoneDatabaseId);

    /*!
     * @brief Sets the name of the current time zone.
     *
     * @param currentSystemTimezone The new time zone name.
     *
     * @since BlackBerry 10.0.0
     */
    void setCurrentSystemTimezone(const QString& currentSystemTimezone);

    /*!
     * @brief Sets whether the device time is in 24-hour format.
     *
     * @param value If @c true the time is in 24-hour format, if @c false the time is
     * not in 24-hour format.
     *
     * @since BlackBerry 10.0.0
     */
    void set24HourFormat(bool value);

    /*!
     * @brief Sets the meeting reminder value.
     *
     * @param meetingReminder The new meeting reminder time, in minutes.
     *
     * @since BlackBerry 10.3.1
     */
    void setMeetingReminder(int meetingReminder);

    /*!
     * @brief Sets the all-day meeting reminder value.
     *
     * @param allDayMeetingReminder The new all-day meeting reminder time, in minutes.
     *
     * @since BlackBerry 10.3.1
     */
    void setAllDayMeetingReminder(int allDayMeetingReminder);

    /*!
     * @brief Indicates whether this @c CalendarSettings is valid.
     *
     * @details This function determines whether the attributes of this @c %CalendarSettings
     * object have acceptable values.
     *
     * @return @c true if this @c %CalendarSettings is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<CalendarSettingsPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_CALENDARSETTINGS_HPP

