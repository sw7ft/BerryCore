
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_COMMONLOCATION_HPP
#define BB_PIM_CALENDAR_COMMONLOCATION_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class AnalyticsStats;
class CommonLocationPrivate;

/*!
 * @brief The @c CommonLocation class represents a meeting location that is common between
 * the user and a specified person.
 *
 * @details You can use the @c CalendarService::commonLocations() function to retrieve
 * a list of meeting locations where both the user and a person that you specify were
 * present. You use the @c emails attribute of an @c AnalyticsParams object to
 * identify the person that should have participate in meetings along with the user at
 * a location.
 * 
 * The @c %commonLocations() function returns a list of @c %CommonLocation objects. Each
 * @c %CommonLocation object includes information such as the location itself and
 * statistics about the common location.
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
class BB_PIM_EXPORT CommonLocation {
public:

    /*!
     * @brief Constructs a new @c CommonLocation.
     *
     * @since BlackBerry 10.0.0
     */
    CommonLocation();

    /*!
     * @brief Destroys this @c CommonLocation.
     *
     * @since BlackBerry 10.0.0
     */
    ~CommonLocation();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c CommonLocation containing exactly the
     * same values as the provided @c %CommonLocation.
     *
     * @param other The @c %CommonLocation to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    CommonLocation(const CommonLocation& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CommonLocation
     * into this @c %CommonLocation.
     *
     * @param other The @c %CommonLocation from which to copy all values.
     *
     * @return A reference to this @c %CommonLocation.
     *
     * @since BlackBerry 10.0.0
     */
    CommonLocation& operator=(const CommonLocation& other);

    /*!
     * @brief Retrieves the location of this @c CommonLocation.
     *
     * @details This function returns the place where the user and the person identified
     * in the @c CalendarService::commonLocations() call met.
     *
     * @return The location of this @c %CommonLocation.
     *
     * @since BlackBerry 10.0.0
     */
    QString location() const;

    /*!
     * @brief Retrieves statistics for this @c CommonLocation.
     *
     * @details This function returns an @c AnalyticsStats object that contains information
     * such as the total number of meetings between the user and the attendee provided to
     * @c CalendarService::commonLocations() and the date of their last meeting.
     *
     * @return Statistics for this @c %CommonLocation.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsStats stats() const;


    /*!
     * @brief Sets the location for this @c CommonLocation.
     *
     * @param location The new location.
     *
     * @since BlackBerry 10.0.0
     */
    void setLocation(const QString& location);

    /*!
     * @brief Sets the statistics for this @c CommonLocation.
     *
     * @param stats The statistics to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setStats(const AnalyticsStats& stats);

    /*!
     * @brief Indicates whether this @c CommonLocation is valid.
     *
     * @details This function determines whether the attributes of this @c %CommonLocation
     * object have acceptable values.
     *
     * @return @c true if this @c %CommonLocation is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<CommonLocationPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_COMMONLOCATION_HPP

