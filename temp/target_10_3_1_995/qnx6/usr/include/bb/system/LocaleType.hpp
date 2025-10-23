/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_LOCALETYPE_HPP
#define BB_SYSTEM_LOCALETYPE_HPP

#include <bb/system/Global>

#include <QMetaObject>
#include <QtDeclarative/QtDeclarative>


namespace bb
{
namespace system
{

/*!
 * @headerfile LocaleType.hpp <bb/system/LocaleType>
 *
 * @brief Specifies different types of locale changes.
 *
 * The @c LocalType is used with a @c LocaleHandler to determine what types of
 * changes the handler should monitor. @c Region is used for listening to changes to
 * regional formatting, such as currency, date and time, etc. @c Messages is used for handling changes to
 * strings as a result of localization.
 *
 * @xmlonly
 * <apigrouping group="Platform/Language"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT LocaleType
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief Specifies different types of locale changes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Specifies that the @c LocaleHandler listen for changes to
         * UI display language.
         *
         * This type is intended for string localization.
         *
         * @since BlackBerry 10.0.0
         */
        Messages = 1,

        /*!
         * @brief Specifies that the @c LocaleHandler listen for changes to
         * regional formatting.
         * 
         * This type is intended for calendar building, number formatting, etc.
         *
         * @since BlackBerry 10.0.0
         */
        Region = 2,
    };


private:
//!@cond PRIVATE
    LocaleType();
    ~LocaleType();
//!@endcond

};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::LocaleType)

#endif  // BB_SYSTEM_LOCALETYPE_HPP
