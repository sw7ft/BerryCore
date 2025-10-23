/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_NOTIFICATIONRESULT_HPP
#define BB_PLATFORM_NOTIFICATIONRESULT_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb
{
namespace platform
{

/*!
 * @headerfile NotificationResult.hpp <bb/platform/NotificationResult>
 *
 * @brief The possible results of a UI request.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT NotificationResult
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The possible results of a UI request.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief No result is available.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,
        
        /*!
         * @brief The request failed due to an error.
         *
         * @since BlackBerry 10.0.0
         */
        Error                   = 1,

        /*!
         * @brief A button was selected.
         *
         * @since BlackBerry 10.0.0
         */
        ButtonSelection         = 2
    };

private:
//!@cond PRIVATE
    NotificationResult();
    ~NotificationResult();
//!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_NOTIFICATIONRESULT_HPP
