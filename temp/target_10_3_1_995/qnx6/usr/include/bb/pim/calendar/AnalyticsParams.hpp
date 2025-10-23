
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ANALYTICSPARAMS_HPP
#define BB_PIM_CALENDAR_ANALYTICSPARAMS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QVariant>
#include <QMap>

namespace bb {
namespace pim {
namespace calendar {

class AnalyticsParamsPrivate;

/*!
 * @brief The @c AnalyticsParams class provides parameters for analytics queries.
 *
 * @details This class encapsulates the parameters that are used for analytics functions in the
 * @c CalendarService class. These analytics functions include @c CalendarService::lastEvents(),
 * @c CalendarService::nextEvents(), @c CalendarService::commonAttendees(), and
 * @c CalendarService::commonLocations(). The emails in an @c %AnalyticsParams object (which you
 * can retrieve using @c emails()) represent attendees that participate in the current user's meetings.
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
class BB_PIM_EXPORT AnalyticsParams {
public:

    /*!
     * @brief Constructs a new @c AnalyticsParams.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsParams();

    /*!
     * @brief Destroys this @c AnalyticsParams.
     *
     * @since BlackBerry 10.0.0
     */
    ~AnalyticsParams();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c AnalyticsParams containing exactly the same values as the
     * provided @c %AnalyticsParams.
     *
     * @param other The @c %AnalyticsParams to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsParams(const AnalyticsParams& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c AnalyticsParams into this
     * @c %AnalyticsParams.
     *
     * @param other The @c %AnalyticsParams from which to copy all values.
     *
     * @return A reference to this @c %AnalyticsParams.
     *
     * @since BlackBerry 10.0.0
     */
    AnalyticsParams& operator=(const AnalyticsParams& other);

    /*!
     * @brief Indicates whether this @c AnalyticsParams should include only entries in calendars that
     * are visible.
     *
     * @details In the Calendar application, users can choose which calendars are visible. If this
     * function returns @c true, then this @c %AnalyticsParams doesn't include entries that correspond
     * to invisible calendars.
     * 
     * You can change the visibility of a calendar by using @c CalendarFolder::setVisible() and
     * @c CalendarService::updateFolder().
     *
     * @return @c true if this @c %AnalyticsParams includes only entries in calendars that are visible,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isVisibleOnly() const;

    /*!
     * @brief Retrieves the maximum number of results for this @c AnalyticsParams.
     *
     * @return The maximum number of results.
     *
     * @since BlackBerry 10.0.0
     */
    int limit() const;

    /*!
     * @brief Retrieves a list of emails that identify attendees that participate in the user's
     * meetings.
     *
     * @details This map associates keys with @c QList objects that should have one email. The
     * key shows up in the maps that are returned by the @c CalendarService functions that use
     * @c AnalyticsParams (@c lastEvents(), @c nextEvents(), @c commonAttendees(), and @c commonLocations()).
     * The email identifies an attendee that participates in the user's meetings.
     * 
     * It's possible to have multiple pairs of keys and emails. The maps returned by the
     * @c %CalendarService functions will associate each key to the result set produced with the
     * corresponding email.
     *
     * @return The map of keys and emails.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, QVariant> emails() const;


    /*!
     * @brief Sets whether this @c AnalyticsParams should include only entries in calendars that are
     * visible.
     * 
     * @param visibleOnly If @c true this @c %AnalyticsParams includes only entries in calendars that
     * are visible, if @c false this @c %AnalyticsParams includes all entries for both visible and
     * invisible calendars.
     *
     * @since BlackBerry 10.0.0
     */
    void setVisibleOnly(bool visibleOnly);

    /*!
     * @brief Sets the maximum number of results for this @c AnalyticsParams.
     *
     * @param limit The new maximum number of results.
     *
     * @since BlackBerry 10.0.0
     */
    void setLimit(int limit);

    /*!
     * @brief Sets the map of keys and emails for this @c AnalyticsParams.
     *
     * @param emails The new map of keys and emails.
     *
     * @since BlackBerry 10.0.0
     */
    void setEmails(QMap<QString, QVariant> emails);

    /*!
     * @brief Indicates whether this @c AnalyticsParams is valid.
     *
     * @details This function determines whether the attributes of this @c %AnalyticsParams object have
     * acceptable values.
     *
     * @return @c true if this @c %AnalyticsParams is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<AnalyticsParamsPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ANALYTICSPARAMS_HPP

