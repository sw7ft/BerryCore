/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIINPUTMODE_HPP
#define BB_SYSTEM_SYSTEMUIINPUTMODE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiInputMode.hpp <bb/system/SystemUiInputMode>
 *
 * @brief The possible types of content for a system input field.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiInputMode
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The mode used to determine input method assistance depending on the content of the input field.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The default mode.
         *
         * @since BlackBerry 10.0.0
         */
        Default                 = 0,

        /*!
         * @brief The input field is intended for entering email addresses.
         *
         * @since BlackBerry 10.0.0
         */
        Email                   = 1,

        /*!
         * @brief The input field is intended for entering passwords.
         *
         * @since BlackBerry 10.0.0
         */
        Password                = 2,

        /*!
         * @brief The input field is intended for entering phone numbers.
         *
         * @since BlackBerry 10.0.0
         */
        Phone                   = 3,

        /*!
         * @brief The input field is intended for entering PINs.
         *
         * @since BlackBerry 10.0.0
         */
        Pin                     = 4,

        /*!
         * @brief The input field is intended for entering web addresses.
         *
         * @since BlackBerry 10.0.0
         */
        Url                     = 5,

        /*!
         * @brief The input field is intended for entering symbols.
         *
         * @since BlackBerry 10.0.0
         */
        Symbols                 = 6,

        /*!
         * @brief The input field is intended for entering numbers using a numeric keypad.
         *
         * @since BlackBerry 10.0.0
         */
        NumericKeypad           = 7,

        /*!
         * @brief The input field is intended for entering numbers and punctuation.
         *
         * @since BlackBerry 10.0.0
         */
        NumbersAndPunctuation   = 8
    };

private:
//!@cond PRIVATE
    SystemUiInputMode();
    ~SystemUiInputMode();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiInputMode)
#endif // BB_SYSTEM_SYSTEMUIINPUTMODE_HPP
