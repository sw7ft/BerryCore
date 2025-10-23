/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_MENUITEMTYPE_HPP
#define BB_SYSTEM_MENUITEMTYPE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile MenuItemType.hpp <bb/system/MenuItemType>
 *
 * @brief Specifies the different types of menu items.
 *
 * @c MenuItems can be grouped into two general categories: "channels" and "shortcuts".
 * "Channel" menu items represent plain invocation targets and are intended to be listed with
 * other "channel" menu items.
 *
 * "Shortcut" menu items represent invocation targets that include information to be used by the
 * target as a suggestion for pre-populating data. The suggestions are based on frecency (frequent/recent)
 * scores based on the user's device usage. By detecting that a @c MenuItem is a "shortcut", the
 * application can display the @c MenuItem in a more prominent position in the target selection menu,
 * since the @c MenuItem represents a task that the user commonly performs and is likely to want to
 * perform again. "Shortcut" menu items also include presentation information that set them apart from
 * other menu items.
 *
 * For example, if the device user frequently shares images to a specific contact using email, the
 * "Share" @c MenuItem may contain both a "channel" @c MenuItem to represent the general share-by-email
 * invocation (without a pre-selected contact), and a "shortcut" @c MenuItem to represent the
 * share-by-email to the specific contact. The "shortcut" @c MenuItem will have a the contact's
 * display name as the label, and the contact's avatar as the icon. The "shortcut" @c MenuItem can
 * be displayed prominently, and when selected will invoke the email composer which will pre-populate
 * the "To:" field with the contact's email address, instead of requiring the user to enter the
 * email address.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT MenuItemType
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Specifies the different types of menu items.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief No type specified.
         *
         * @since BlackBerry 10.2.0
         */
        Unspecified = 0,

        /*!
         * @brief Specifies that the @c MenuItem represents an invocation that
         * does not include any shortcut information.
         *
         * @since BlackBerry 10.2.0
         */
        Channel = 1,

        /*!
         * @brief Specifies that the @c MenuItem represents an invocation including a suggested
         * contact-related identifier.
         *
         * @since BlackBerry 10.2.0
         */
        ContactShortcut = 2,

        /*!
         * @brief Specifies that the @c MenuItem represents an invocation including a suggested
         * account-related identifier.
         *
         * @since BlackBerry 10.2.0
         */
        AccountShortcut = 3,

        /*!
         * @brief Specifies that the @c MenuItem represents an invocation related to a
         * calendar event.
         *
         * @since BlackBerry 10.2.0
         */
        EventShortcut = 4
    };

private:
//!@cond PRIVATE
    MenuItemType();
    ~MenuItemType();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::MenuItemType)
#endif // BB_SYSTEM_MENUITEMTYPE_HPP
