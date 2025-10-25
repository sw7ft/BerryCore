
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ANALYTICSSTATS_HPP
#define BB_PIM_CALENDAR_ANALYTICSSTATS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QDateTime>

namespace bb {
namespace pim {
namespace calendar {

class AnalyticsStatsPrivate;

/*!
 * @brief The @c AnalyticsStats class provides statistics for analytics results.
 *
 * @details The data in this class augments the results of the analytics queries in the
 * @c CalendarService class. These queries include @c CalendarService::commonAttendees() and
 * @c CalendarService::commonLocations().
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
class BB_PIM_EXPORT AnalyticsStats {
public:

    /*!
     * @brief Constructs a new @c AnalyticsStats.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsStats();

    /*!
     * @brief Destroys this @c AnalyticsStats.
     *
     * @since BlackBerry 10.0.0
     */
    ~AnalyticsStats();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c AnalyticsStats containing exactly the same values as the
     * provided @c %AnalyticsStats.
     *
     * @param other The @c %AnalyticsStats to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsStats(const AnalyticsStats& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c AnalyticsStats into this
     * @c %AnalyticsStats.
     *
     * @param other The @c %AnalyticsStats from which to copy all values.
     *
     * @return A reference to this @c %AnalyticsStats.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsStats& operator=(const AnalyticsStats& other);

    /*!
     * @brief Retrieves the last-met date for this @c AnalyticsStats.
     *
     * @details This function returns the date when the user last visited a location or met an
     * attendee.
     *
     * @return The last-met date for this @c %AnalyticsStats.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime lastMet() const;

    /*!
     * @brief Retrieves the number of visits or meetings for this @c AnalyticsStats.
     *
     * @details This function returns the number of times the user visited a location or met
     * an attendee.
     *
     * @return The number of visits or meetings for this @c %AnalyticsStats.
     *
     * @since BlackBerry 10.0.0
     */
    int count() const;


    /*!
     * @brief Sets the last-met date for this @c AnalyticsStats.
     *
     * @param lastMet The new last-met date.
     *
     * @since BlackBerry 10.0.0
     */
    void setLastMet(const QDateTime& lastMet);

    /*!
     * @brief Sets the number of visits or meetings for this @c AnalyticsStats.
     *
     * @param count The new number of visits or meetings.
     *
     * @since BlackBerry 10.0.0
     */
    void setCount(int count);

    /*!
     * @brief Indicates whether this @c AnalyticsStats is valid.
     *
     * @details This function determines whether the attributes of this @c %AnalyticsStats object have
     * acceptable values.
     *
     * @return @c true if this @c %AnalyticsStats is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<AnalyticsStatsPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ANALYTICSSTATS_HPP

