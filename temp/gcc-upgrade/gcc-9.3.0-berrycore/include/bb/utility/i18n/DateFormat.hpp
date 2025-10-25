/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_DATEFORMAT_HPP
#define BB_UTILITY_I18N_DATEFORMAT_HPP

#include <bb/utility/i18n/Global>

namespace bb
{
namespace utility
{
namespace i18n
{

/*!
 * @headerfile DateFormat.hpp <bb/utility/i18n/DateFormat>
 *
 * @brief A wrapper for a list of supported date/time formats.
 *
 * @details This class offers an enum that represents Qt equivalents of
 * International Components for Unicode (ICU) date/time format patterns.
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
 * @since BlackBerry 10.0.0
 */
class BB_UTILITY_I18N_EXPORT DateFormat {

public:

    /*!
     * @brief The list of supported date/time formats.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {

        /*!
         * @brief The equivalent to the ICU pattern, @c DateFormat::kShort.
         *
         * @details This represents "3/2/13 5:04 PM" in the US English locale.
         *
         * @since BlackBerry 10.0.0
         */
        Short = 1,

         /*!
         * @brief The equivalent to the ICU pattern, @c DateFormat::kMedium.
         *
         * @details This represents "Mar 2, 2013 5:04:11 PM" in the US English locale.
          *
          * @since BlackBerry 10.0.0
         */
        Medium = 2,

        /*!
         * @brief The equivalent to the ICU pattern, @c DateFormat::kLong.
         *
         * @details This represents "March 2, 2013 5:04:11 PM EST" in the US English locale.
         *
         * @since BlackBerry 10.0.0
         */
        Long = 3,

        /*!
         * @brief The equivalent to the ICU pattern, @c DateFormat::kFull.
         *
         * @details This represents "Sunday, March 2, 2013 5:04:11 PM EST" in the US English locale.
         *
         * @since BlackBerry 10.0.0
         */
        Full = 4

    }; // enum

//!@cond PRIVATE

private:

    DateFormat ();
    ~DateFormat ();

//!@endcond PRIVATE

}; // class

} // namespace
} // namespace
} // namespace

#endif // _HPP
