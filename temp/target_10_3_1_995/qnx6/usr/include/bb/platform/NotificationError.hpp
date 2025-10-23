/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_NOTIFICATIONERROR_HPP
#define BB_PLATFORM_NOTIFICATIONERROR_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb
{
namespace platform
{

/*!
 * @headerfile NotificationError.hpp <bb/platform/NotificationError>
 *
 * @brief The errors that can be returned by the Notification service.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT NotificationError
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The errors that can be returned by the Notification service.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief No errors have occurred.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,

        /*!
         * @brief An unknown error has occurred.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown                 = 1,

        /*!
         * @brief Invalid request errors occur when the Notification service cannot interpret a request.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidRequest          = 2,

        /*!
         * @brief Requests may be invalid if buttons are required to be used, but no buttons are included.
         *
         * @since BlackBerry 10.0.0
         */
        NoButtons               = 3,

        /*!
         * @brief The Notification Settings cannot be accessed because the Notification service is unavailable.
         *
         * @since BlackBerry 10.0.0
         */
        ServiceUnavailable      = 4

    };

private:
//!@cond PRIVATE
    NotificationError();
    ~NotificationError();
//!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_NOTIFICATIONERROR_HPP
