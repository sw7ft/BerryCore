/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_RELATIVEDATEFORMAT_HPP
#define BB_UTILITY_I18N_RELATIVEDATEFORMAT_HPP

#include <bb/utility/i18n/Global>

#include <QMetaEnum>

namespace bb
{
namespace utility
{
namespace i18n
{

/*!
 * @headerfile RelativeDateFormat.hpp <bb/utility/i18n/RelativeDateFormat>
 *
 * @brief A list of supported relative date/time formatters.
 *
 * @sa bb::utility::i18n::RelativeDateFormatter
 *
 *
 * @xmlonly
 * <qml>
 *    <class register="enum-only" />
 * </qml>
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutilityi18n"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_UTILITY_I18N_EXPORT RelativeDateFormat
{
    Q_GADGET
    Q_ENUMS(Type);

public:

    /*!
     * @brief The list of supported relative date/time formaters.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {

        /*!
         * @brief The default relative date/time formatter.
         *
         * @details This type of @c RelativeDateFormatter
         * should be used when time information is important.
         * For example, scheduled calendar events, when a
         * message/notification/call was received/sent, etc.
         *
         * | date-time range           | example          |
         * | ------------------------- | ---------------- |
         * | past years                | March 2012       |
         * | same year; past 4+ days   | Jan 20           |
         * | past 2-3 days             | Mon 1:01PM       |
         * | previous day              | Yesterday 1:01PM |
         * | same day; 1+ hours ago    | 3 hours ago      |
         * | less than an hour ago     | 10 minutes ago   |
         * | in less than an hour      | in 10 minutes    |
         * | same day; in 1+ hours     | in 3 hours       |
         * | following day             | Tomorrow 1:01PM  |
         * | future 2-3 days           | Sat 1:01PM       |
         * | same year; future 4+ days | Dec 20           |
         * | future years              | March 2014       |
         *
         * @since BlackBerry 10.2.0
         */
        TimeCritical = 1,

        /*!
         * @brief A relative date/time formatter without time.
         *
         * @details This type of @c RelativeDateFormatter
         * should be used when the user does not care about
         * the specific time. For example, when software
         * was last updated, friends' birthdays, holidays, etc.
         *
         * | date-time range           | example      |
         * | ------------------------- | ------------ |
         * | past years                | March 2012   |
         * | same year; past 4+ days   | Jan 20       |
         * | past 2-3 days             | Monday       |
         * | previous day              | Yesterday    |
         * | same day                  | Today        |
         * | following day             | Tomorrow     |
         * | future 2-3 days           | Saturday     |
         * | same year; future 4+ days | Dec 20       |
         * | future years              | March 2014   |
         *
         * @since BlackBerry 10.2.0
         */
        NonTimeCritical = 2,

    }; // enum

//!@cond PRIVATE

private:

    RelativeDateFormat();
    ~RelativeDateFormat();

//!@endcond PRIVATE

}; // class

} // namespace
} // namespace
} // namespace

#endif // _HPP
