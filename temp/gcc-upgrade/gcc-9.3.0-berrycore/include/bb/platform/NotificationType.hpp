/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_NOTIFICATIONTYPE_HPP
#define BB_PLATFORM_NOTIFICATIONTYPE_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb
{
namespace platform
{

/*!
 * @headerfile NotificationType.hpp <bb/platform/NotificationType>
 *
 * @brief The type of notifications.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT NotificationType
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief Notification types.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {

        /*!
         * @brief Notifications will be shown according to the notification settings.
         *
         * @since BlackBerry 10.2.0
         */
        Default                 = 0,

        /*!
         * @brief Preview for this notification will not be shown, regardless of notification settings.
         *
         * @since BlackBerry 10.2.0
         */
        PreviewOff              = 1,

        /*!
         * @brief Notification will only be shown in Hub and all alerts except icon badging will be suppressed, regardless of notification settings
         *
         * @since BlackBerry 10.2.0
         */
        AllAlertsOff            = 2,

        /*!
         * @brief Notification will not appear in the Notifications account in the Hub, regardless of notification settings
         *
         * @since BlackBerry 10.2.0
         */
        HubOff                     = 3,
    };

private:
    //!@cond PRIVATE
    NotificationType();
    ~NotificationType();
    //!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_NOTIFICATIONTYPE_HPP
