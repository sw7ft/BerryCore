
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDARDATAPATH_HPP
#define BB_PIM_CALENDAR_ICALENDARDATAPATH_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class ICalendarDataPathPrivate;

/*!
 * @brief The @c ICalendarDataPath class contains information on exported iCalendar files.
 *
 * @details This class contains attributes of files that are created by calling
 * @c CalendarService::createICalendarData(), which exports calendar events to
 * iCalendar files. These attributes include information such as system path, MIME type,
 * and size.
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
class BB_PIM_EXPORT ICalendarDataPath {
public:

    /*!
     * @brief Constructs a new @c ICalendarDataPath.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarDataPath();

    /*!
     * @brief Destroys this @c ICalendarDataPath.
     *
     * @since BlackBerry 10.0.0
     */
    ~ICalendarDataPath();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c ICalendarDataPath containing exactly the
     * same values as the provided @c %ICalendarDataPath.
     *
     * @param other The @c %ICalendarDataPath to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarDataPath(const ICalendarDataPath& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ICalendarDataPath
     * into this @c %ICalendarDataPath.
     *
     * @param other The @c %ICalendarDataPath from which to copy all values.
     *
     * @return A reference to this @c %ICalendarDataPath.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarDataPath& operator=(const ICalendarDataPath& other);

    /*!
     * @brief Retrieves the path for the iCalendar file.
     *
     * @details This function returns the path in the device's file system for the
     * created iCalendar file.
     *
     * @return The path for the iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    QString systemPath() const;

    /*!
     * @brief Retrieves the MIME type of the iCalendar file.
     *
     * @details This function returns the MIME type (RFC 2046) of the iCalendar file.
     *
     * @return The MIME type of the iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Retrieves the size of the iCalendar file.
     *
     * @return The size of the iCalendar file.
     *
     * @since BlackBerry 10.0.0
     */
    int size() const;


    /*!
     * @brief Sets the path for the iCalendar file.
     *
     * @param systemPath The new path.
     *
     * @since BlackBerry 10.0.0
     */
    void setSystemPath(const QString& systemPath);

    /*!
     * @brief Sets the MIME type of the iCalendar file.
     *
     * @param mimeType The new MIME type.
     *
     * @since BlackBerry 10.0.0
     */
    void setMimeType(const QString& mimeType);

    /*!
     * @brief Sets the size of the iCalendar file.
     *
     * @param size The new size.
     *
     * @since BlackBerry 10.0.0
     */
    void setSize(int size);

    /*!
     * @brief Indicates whether this @c ICalendarDataPath is valid.
     *
     * @details This function determines whether the attributes of this @c %ICalendarDataPath
     * object have acceptable values.
     *
     * @return @c true if this @c %ICalendarDataPath is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<ICalendarDataPathPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDARDATAPATH_HPP

