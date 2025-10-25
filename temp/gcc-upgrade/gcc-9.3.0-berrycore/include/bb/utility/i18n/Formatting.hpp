/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_FORMATTING_HPP
#define BB_UTILITY_I18N_FORMATTING_HPP

#include <bb/utility/i18n/Global>
#include <bb/utility/i18n/DateFormat>

#include <QString>

class QLocale;

/*!
 * @namespace bb::utility::i18n
 *
 * @headerfile Formatting.hpp <bb/utility/Formatting>
 *
 *
 * @brief This namespace offers functions for formatting text into dates, time, and percentages.
 *
 * @details These functions open up International Components for Unicode (ICU) Internationalization (i18n) APIs
 * in a manner that can be conveniently used with Qt.
 *
 * @xmlonly
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutilityi18n"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
namespace bb
{
namespace utility
{
namespace i18n
{


/*!
 * @brief Provides a @c QDate formatting pattern based on a @c DateFormat::Type
 * and the current @c LocaleType::Region @c QLocale.
 *
 * @details If provided with @c DateFormat::Medium and the user has selected
 * US English as the region locale, "MMM d,yyyy" is returned.
 *
 * The returned @c QString can be passed in as the second parameter of
 * <tt>QLocale::toString(const QDate &, const QString &) const</tt>,
 * thus allowing you to display any @c QDate object in a localized standard ICU format.
 *
 * @note You should always make sure to format the text using the region locale.
 * See the documentation for @c bb::system::LocaleHandler for more details.
 *
 * @param format A @c DateFormat::Type to specify the length and complexity of the generated format.
 *
 * @return A localized date format pattern string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString dateFormat (DateFormat::Type format = DateFormat::Short);

/*!
 * @brief Provides @c QDate formatting pattern given a @c QLocale and a @c DateFormat::Type.
 *
 * @details This overloaded function is identical to @c dateFormat(DateFormat::Type) except
 * that it allows for specifying a custom @c QLocale instead of the user's region locale.
 *
 * @param locale The @c QLocale used for generating the date pattern.
 * @param format A @c DateFormat::Type to specify the length and complexity of the generated format.
 *
 * @return A localized date format pattern string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString dateFormat (const QLocale & locale, DateFormat::Type format = DateFormat::Short);


/*!
 * @brief Provides a @c QTime formatting pattern based on a @c DateFormat::Type
 * and the current @c bb::system::LocaleType::Region @c QLocale.
 *
 * @details If supplied with @c DateFormat::Medium, and the user has selected
 * US English as the region locale, "h:mm:ss" is returned.
 * This function accounts for the user's choice of the 12/24 hour clock.
 *
 * The returned @c QString can be passed in as the second parameter of
 * <tt>QLocale::toString(const QTime &, const QString &) const</tt>
 * thus allowing you to display any @c QTime object in a localized standard ICU format.
 *
 * @note You should always make sure to format the text using the region locale.
 * See the documentation for @c bb::system::LocaleHandler for more details.
 *
 * @param format A @c DateFormat::Type to specify the length and complexity of the generated format.
 *
 * @return A localized time format pattern string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString timeFormat (DateFormat::Type format = DateFormat::Short);

/*!
 * @brief This function provides a @c QTime formatting pattern given a @c QLocale and @c DateFormat::Type.
 *
 * @details This overloaded function is identical to @c timeFormat(DateFormat::Type) except
 * that it allows for specifying a custom @c QLocale instead of the user's region locale.
 *
 * @param locale The @c QLocale used for generating the time pattern.
 * @param format A @c DateFormat::Type to specify the length and complexity of the generated format.
 *
 * @return A localized time format pattern string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString timeFormat (const QLocale & locale, DateFormat::Type format = DateFormat::Short);


/*!
 * @brief This function provides a @c QDateTime formatting pattern based on a @c DateFormat::Type
 * and the current @c bb::system::LocaleType::Region @c QLocale.
 *
 * @details If supplied with @c DateFormat::Medium, and the user has selected
 * US English as the region locale, "MMM d,yyyy h:mm:ss" is returned.
 * This function accounts for the user's choice of the 12/24 hour clock.
 *
 * The returned @c QString can be passed in as the second parameter of
 * <tt>QLocale::toString(const QDateTime &, const QString &) const</tt>
 * thus allowing you to display any @c QDateTime object in a localized standard ICU format.
 *
 * @note You should always make sure to format the text using the region locale.
 * See the documentation for @c bb::system::LocaleHandler for more details.
 *
 * @param format A @c DateFormat::Type to specify the length and complexity of the generated format.
 *
 * @return A localized date-time format pattern string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString dateTimeFormat (DateFormat::Type format = DateFormat::Short);

/*!
 * @brief This function provides a @c QDateTime formatting pattern given a @c QLocale and @c DateFormat::Type.
 *
 * @details This overloaded function is identical to @c dateTimeFormat(DateFormat::Type) except
 * that it allows for specifying a custom @c QLocale instead of the user's region locale.
 *
 * @param locale The @c QLocale used for generating the date-time pattern.
 * @param format A @c DateFormat::Type to specify the length and complexity of the generated format.
 *
 * @return A localized date-time format pattern string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString dateTimeFormat (const QLocale & locale, DateFormat::Type format = DateFormat::Short);


/*!
 * @brief This function formats a number as a percentage according to
 * the current @c bb::system::LocaleType::Region @c QLocale.
 *
 * @details Some example use cases:
 * @li @c toPercentageString(0.4500005) returns "45%" if the region locale is US English.
 * @li @c toPercentageString(0.4499995) returns "% 45" if the region locale is Turkish.
 *
 * @sa bb::system::LocaleHandler for more details on the region locale.
 *
 * @param number The number to be represented as a percentage.
 * @param maxFractionDigits The maximum number of digits allowed in the fraction portion of the percentage.
 * @param minFractionDigits The minimum number of digits allowed in the fraction portion of the percentage.
 *
 * @return Returns a localized percentage string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString toPercentageString (double number, int maxFractionDigits = 6, int minFractionDigits = 0);

/*!
 * @brief This function formats a number as a percentage localized to any @c QLocale.
 *
 * @details
 * This overloaded function is identical to <tt>toPercentageString(double, int, int)</tt> except
 * that it allows specifying a custom @c QLocale instead of the user's region locale.
 *
 * @param locale The @c QLocale used for generating the date-time pattern.
 * @param number The number to be represented as a percentage.
 * @param maxFractionDigits The maximum number of digits allowed in the fraction portion of the percentage.
 * @param minFractionDigits The minimum number of digits allowed in the fraction portion of the percentage.
 *
 * @return Returns a localized percentage string.
 *
 * @since BlackBerry 10.0.0
 */
BB_UTILITY_I18N_EXPORT QString toPercentageString (const QLocale & locale, double number, int maxFractionDigits = 6, int minFractionDigits = 0);


} // namespace
} // namespace
} // namespace

#endif // _HPP
