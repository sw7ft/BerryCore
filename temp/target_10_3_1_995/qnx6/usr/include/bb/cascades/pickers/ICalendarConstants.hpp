/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PICKERS_ICALENDARCONSTANTS_HPP
#define BB_CASCADES_PICKERS_ICALENDARCONSTANTS_HPP

#include <bb/cascades/pickers/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace pickers
{

/*!
 * @headerfile ICalendarConstants.hpp <bb/cascades/pickers/ICalendarConstants>
 *
 * @brief A class containing the various iCal constants being used.
 *
 *
 * @details
 *
 * The @c %ICalendarConstants class is used to determine various iCal constants, such as iCal version.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BB_CASCADES_PICKERS_EXPORT ICalendarConstants
{
    Q_GADGET
    Q_ENUMS(Version)

public:
    enum Version {
        /*!
         * @brief Version 1.0 (vcs).
         *
         * @since BlackBerry 10.1.0
         */
        ICAL_1_0 = 1,

        /*!
         * @brief Version 2.0 (ics).
         *
         * @since BlackBerry 10.1.0
         */
        ICAL_2_0  = 2,

    };

private:
//!@cond PRIVATE
    ICalendarConstants();
    ~ICalendarConstants();
//!@endcond PRIVATE
};

} // namespace bb
} // namespace cascades
} // namespace pickers
#endif // BB_CASCADES_PICKERS_ICALENDARCONSTANTS_HPP
