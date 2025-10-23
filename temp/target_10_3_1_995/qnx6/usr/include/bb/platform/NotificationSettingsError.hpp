/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONSETTINGSERROR_HPP
#define BB_PLATFORM_NOTIFICATIONSETTINGSERROR_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

namespace platform
{

/*!
 * @headerfile NotificationSettingsError.hpp <bb/platform/NotificationSettingsError>
 *
 * @brief The possible Notification Settings errors.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT NotificationSettingsError
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The possible Notification Settings errors.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief No errors have occurred.
         *
         * @since BlackBerry 10.2.0
         */
        None = 0,

        /*!
         * @brief An unknown error has occurred.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown = 1,

        /*!
         * @brief The application lacks the proper permissions needed to perform the requested operation.
         *
         * @since BlackBerry 10.2.0
         */
        InsufficientPermissions = 2,

        /*!
         * @brief An internal error has occurred.
         */
        Internal = 3,

        /*!
         * @brief Service availability determines whether Notification Settings can be accessed.
         *
         * @since BlackBerry 10.2.0
         */
        ServiceUnavailable = 4
    };

private:
//!@cond PRIVATE
    NotificationSettingsError();
    ~NotificationSettingsError();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::NotificationSettingsError)
#endif // BB_PLATFORM_NOTIFICATIONSETTINGSERROR_HPP

