/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEREPLYERROR_HPP
#define BB_SYSTEM_INVOKEREPLYERROR_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile InvokeReplyError.hpp <bb/system/InvokeReplyError>
 *
 * @brief The list of possible results of a request to the invocation service.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeReplyError
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The list of possible results of a request to the invocation service.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Success.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,

        /*!
         * @brief No target was found.
         *
         * @details This can happen if a bad target was sent in the request or if brokering failed.
         *
         * @since BlackBerry 10.0.0
         */
        NoTarget                = 1,

        /*!
         * @brief The request could not be parsed.
         *
         * @since BlackBerry 10.0.0
         */
        BadRequest              = 2,

        /*!
         * @brief The invocation service failed as a result of an internal error.
         *
         * @details Examples of internal errors include the service running out of memory or 
         * entering an unexpected state.
         *
         * @since BlackBerry 10.0.0
         */
        Internal                = 3,

        /*!
         * @brief An attempt to set or retrieve a target's filter list failed because the
         * requesting entity does not own the target.
         *
         * @since BlackBerry 10.0.0
         */
        TargetNotOwned          = 4,

        /*!
         * @brief A request failed because the requesting entity lacks sufficient privileges.
         *
         * @since BlackBerry 10.0.0
         */
        InsufficientPrivileges  = 5,

        /*!
         * @brief The target failed or otherwise misbehaved during invocation, causing the request to fail.
         *
         * @since BlackBerry 10.0.0
         */
        Target                  = 6

    };

private:
//!@cond PRIVATE
    InvokeReplyError();
    ~InvokeReplyError();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::InvokeReplyError)
#endif // BB_SYSTEM_INVOKEREPLYERROR_HPP
