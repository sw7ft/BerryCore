/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEDATETIME_HPP
#define BB_SYSTEM_INVOKEDATETIME_HPP

#include <bb/system/Global>
#include <QSharedDataPointer>
#include <QDate>
#include <QString>
#include <QTime>

namespace bb
{
namespace system
{

class InvokeDateTimePrivate;

/*!
 * @headerfile InvokeDateTime.hpp <bb/system/InvokeDateTime>
 *
 * @brief Encapsulates a specific date and time
 *
 * @details A InvokeDateTime object contains a calendar date, a clock time and
 * an optional time zone. If no time zone is assigned, then the InvokeDateTime
 * represents a Roaming time, always relative to the current time zone.
 * Otherwise (if the time zone is non-empty) the InvokeDateTime represents an
 * Anchored time - that time in that time zone, ie 8:00am in Los Angeles.
 *
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_SYSTEM_EXPORT InvokeDateTime
{

    Q_ENUMS(Type)

public:

    /*!
     * @brief The kinds of @c #InvokeDateTime objects that can be created.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type {
        /*!
         * @brief Unknown type.
         *
         * @since BlackBerry 10.3.0
         */
        Unknown = 0,
        /**
         * Represents a local time.
         * eg. 7am irrespective of the time zone
         *
         * @since BlackBerry 10.3.0
         */
        Roaming   = 1,
        /**
         * Represents a global time.
         * eg. 7am in New York
         *
         * @since BlackBerry 10.3.0
         */
        Anchored  = 2
    };

public:

    /*!
     * @brief Creates a new @c #InvokeDateTime object
     *
     * @brief The specific time params need to be set by calling the method
     * @c #set
     *
     * @since BlackBerry 10.3.0
     */
    InvokeDateTime();

    /*!
     * @brief Creates a new @c #InvokeDateTime object
     * with the params provided
     *
     * @param date      The date.
     * @param time      The time. Note: seconds and milliseconds of @c #date are
     *   ignored here.
     * @param timeZone  The timeZone ID to set.
     *   If this parameter is not empty then the @c #InvokeDateTime is
     *   of type @c #InvokeDateTime::Anchored.
     *   If this parameter is empty then the @c #InvokeDateTime is
     *   of type @c #InvokeDateTime::Roaming.
     *   The time zone ID can be a programmatic ID such as "America/Los_Angeles"
     *   which is defined in the standard Olson/IANA timezone database used by
     *   UNIX systems. The programmatic ID has the format continent/city or
     *   ocean/city.
     *   The time zone ID can also be a custom ID such as "GMT-8:00".
     *   The custom ID has the syntax "GMT[+|-]hh[[:]mm]".
     *   A list of supported time zone IDs can be obtained by calling
     *   @c #icu::TimeZone::createEnumeration() declared in header file
     *    <unicode/timezone.h>
     *   The wikipedia link
     *   http://en.wikipedia.org/wiki/List_of_tz_database_time_zones has a list
     *   of time zones in the programmatic ID format.
     *   Please use the latter with caution, as some of these may or may not be
     *   supported on your platform.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeDateTime(const QDate &date, const QTime &time, const QString &timeZone = QString());

    /*!
     * @brief Creates a copy of an existing @c #InvokeDateTime object.
     *
     * @param other The source @c #InvokeDateTime object to copy.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeDateTime(const InvokeDateTime &other);

    /*!
     * @brief Destroys this @c #InvokeDateTime object.
     *
     * @since BlackBerry 10.3.0
     */
    ~InvokeDateTime();

    /*!
     * @brief Copies the data of an existing @c #InvokeDateTime object
     * to this object.
     *
     * @param other The source @c #InvokeDateTime object to copy.
     *
     * @return The @c #InvokeDateTime instance.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeDateTime& operator=(const InvokeDateTime &other);

    /*!
     * @brief Sets the params for this @c #InvokeDateTime object.
     *
     * @param date      The date.
     * @param time      The time. Note: seconds and milliseconds of @c #date are
     *   ignored here.
     * @param timeZone  The timeZone ID to set.
     *   If this parameter is not empty then the @c #InvokeDateTime is
     *   of type @c #InvokeDateTime::Anchored.
     *   If this parameter is empty then the @c #InvokeDateTime is
     *   of type @c #InvokeDateTime::Roaming.
     *   The time zone ID can be a programmatic ID such as "America/Los_Angeles"
     *   which is defined in the standard Olson/IANA timezone database used by
     *   UNIX systems. The programmatic ID has the format continent/city or
     *   ocean/city.
     *   The time zone ID can also be a custom ID such as "GMT-8:00".
     *   The custom ID has the syntax "GMT[+|-]hh[[:]mm]".
     *   A list of supported time zone IDs can be obtained by calling
     *   @c #icu::TimeZone::createEnumeration() declared in header file
     *    <unicode/timezone.h>
     *   The wikipedia link
     *   http://en.wikipedia.org/wiki/List_of_tz_database_time_zones has a list
     *   of time zones in the programmatic ID format.
     *   Please use the latter with caution, as some of these may or may not be
     *   supported on your platform.
     *
     * @since BlackBerry 10.3.0
     */
    void set(const QDate &date, const QTime &time, const QString &timeZone = QString());

    /*!
     * @brief Sets the date
     *
     * @param date  The date.
     *
     * @since BlackBerry 10.3.0
     */
    void setDate(const QDate &date);

    /*!
     * @brief Sets the time
     *
     * @param time  The time.
     *
     * @since BlackBerry 10.3.0
     */
    void setTime(const QTime &time);

    /*!
     * @brief Sets the time zone
     *
     * @details Setting the time zone to an empty string sets the type of the
     * InvokeDateTime to Roaming.  A non-empty string makes it Anchored.
     *
     * @param timeZone  The time zone.
     *
     * @since BlackBerry 10.3.0
     */
    void setTimeZone(const QString &timeZone);

    /*!
     * @brief Return the date.
     *
     * @details The method returns the date that was previously set.
     *
     * @return date that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QDate date() const;

    /*!
     * @brief Return the time.
     *
     * @details The method returns the time that was previously set.
     *
     * @return time that was previously set
     *
     * @since BlackBerry 10.3.0
     */
    QTime time() const;

    /*!
     * @brief Return the timeZone.
     *
     * @details The method returns the timeZone that was previously set.
     *
     * @return timeZone that was previously set or an empty string
     *
     * @since BlackBerry 10.3.0
     */
    QString timeZone() const;

    /*!
     * @brief Returns true if this @c #InvokeDateTime object is valid.
     *
     * @details The method returns true if both the date and the time
     * of this @c #InvokeDateTime object are valid. This method does
     * not check to see if an assigned time zone is recognized. An assigned time
     * zone which is unrecognized is still considered valid, but may cause
     * functions taking a @c #InvokeDateTime to fail.
     *
     * @return true if valid, false otherwise
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;

    /*!
     * @brief Return the type.
     *
     * @details The method returns the type.
     *
     * @return type.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeDateTime::Type type() const;



private:
//!@cond PRIVATE
    QSharedDataPointer<InvokeDateTimePrivate> d;
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKEDATETIME_HPP
