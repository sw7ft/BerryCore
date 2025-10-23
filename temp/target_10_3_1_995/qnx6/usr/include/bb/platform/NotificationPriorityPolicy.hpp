/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONPRIORITYPOLICY_HPP
#define BB_PLATFORM_NOTIFICATIONPRIORITYPOLICY_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile NotificationPriorityPolicy.hpp <bb/platform/NotificationPriorityPolicy>
 *
 * @brief A set of notification priority policy values.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT NotificationPriorityPolicy
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The set of notification priority policy values.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The policy could not be determined.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The Notification system may trigger the effect when notifying
         *        the user.
         *
         * @details Whether an effect is actually triggered may also depend on
         *          other notification settings.
         *
         * @since BlackBerry 10.2.0
         */
        Allow = 1,

        /*!
         * @brief The Notification system will not trigger the effect when notifying
         *        the user.
         *
         * @since BlackBerry 10.2.0
         */
        Deny = 2,

        /*!
         * @brief The effect is not applicable to this application. The
         *        user setting will be hidden from the Application Settings UI.
         *
         * @since BlackBerry 10.2.0
         */
        NotApplicable = 3,

        /*!
         * @brief The Notification system may only trigger the effect for
         *        notifications coming from priority sources.
         *
         * @details Priority is determined by the Notification system.
         *
         * @since BlackBerry 10.2.0
         */
        PriorityOnly = 4
    };

private:
//!@cond PRIVATE
    NotificationPriorityPolicy();
    ~NotificationPriorityPolicy();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::NotificationPriorityPolicy)
#endif // BB_PLATFORM_NOTIFICATIONPRIORITYPOLICY_HPP

