/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONMODE_HPP
#define BB_PLATFORM_NOTIFICATIONMODE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile NotificationMode.hpp <bb/platform/NotificationMode>
 *
 * @brief The set of supported notification modes.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT NotificationMode
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The set of supported notification modes.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The mode could not be determined.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief Disable sound and vibration notifications.
         *
         * @details If the notification mode is set to @c Silent,
         *          the global notification setting for sound and vibrate
         *          will be set to off. The global notification volume level
         *          will be set to 0. Other settings will remain unchanged.
         *
         * @since BlackBerry 10.2.0
         */
        Silent = 1,

        /*!
         * @brief Play all sound and vibration notifications as vibrations.
         *
         * @details If the notification mode is set to @c vibrate,
         *          the global notification setting for sound will be set
         *          to off, and the global notification setting for vibrate
         *          will be set to on. The global notification volume level
         *          will be set to 0. Other settings will remain in custom
         *          states.All notifications set to deliver as sound or
         *          vibration will be delivered as a vibration.
         *
         * @since BlackBerry 10.2.0
         */
        Vibrate = 2,

        /*!
         * @brief The normal notification mode.
         *
         * @details The normal mode of operations for notifications. This
         *          mode allows for custom notification settings. Custom
         *          settings are saved when switching out of this mode, and
         *          are restored when switching into this mode.
         *
         * @since BlackBerry 10.2.0
         */
        Normal = 3,

        /*!
         * @brief Deliver only phone related notifications.
         *
         * @details Custom notification settings are preserved when switching
         *          into this mode, but only Phone related notifications
         *          will be delivered.
         *
         * @since BlackBerry 10.2.0
         */
        PhoneOnly = 4,

        /*!
         * @brief Disable all notifications.
         *
         * @details If the notification mode is set to @c AlertsOff,
         *          all global notification settings will be set to
         *          off. The global notification volume level will be
         *          set to 0.
         *
         * @since BlackBerry 10.2.0
         */
        AlertsOff = 5
    };

private:
//!@cond PRIVATE
    NotificationMode();
    ~NotificationMode();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::NotificationMode)
#endif // BB_PLATFORM_NOTIFICATIONMODE_HPP

