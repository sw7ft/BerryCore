/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_CLOCKFORMAT_HPP
#define BB_UTILITY_I18N_CLOCKFORMAT_HPP

#include <bb/utility/i18n/Global>

#include <QMetaEnum>

namespace bb
{
namespace utility
{
namespace i18n
{

/*!
 * @headerfile ClockFormat.hpp <bb/utility/i18n/ClockFormat>
 *
 * @brief A wrapper for a list of supported date/time formats.
 *
 * @details This class offers an enum that represents various options for specifying the clock format.
 *
 *
 * @xmlonly
 * <qml>
 * <class register="no" />
 * </qml>
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutilityi18n"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_UTILITY_I18N_EXPORT ClockFormat
{
    Q_GADGET
    Q_ENUMS(Type);

public:

    /*!
     * @brief The list of supported clock formats.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {

        /*!
         * @brief Instructs the formatter to grab the user selected value from the device.
         *
         * @since BlackBerry 10.2.0
         */
        ApplyUserFormat = 1,

        /*!
         * @brief Instructs the formatter to grab the default format from the current locale.
         *
         * @since BlackBerry 10.2.0
         */
        ApplyLocaleFormat = 2,

        /*!
         * @brief 12 hour clock format with am/pm marker.
         *
         * @details This represents formats like "4:23 PM".
         *
         * @since BlackBerry 10.2.0
         */
        Use12hourClock = 12,

        /*!
         * @brief 24 hour clock format.
         *
         * @details This represents formats like "16:23".
         *
         * @since BlackBerry 10.2.0
         */
        Use24hourClock = 24,

    }; // enum

//!@cond PRIVATE

private:

    ClockFormat();
    ~ClockFormat();

//!@endcond PRIVATE

}; // class

} // namespace
} // namespace
} // namespace

#endif  // _HPP
