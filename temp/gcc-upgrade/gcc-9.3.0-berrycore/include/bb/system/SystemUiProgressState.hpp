/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIPROGRESSSTATE_HPP
#define BB_SYSTEM_SYSTEMUIPROGRESSSTATE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiProgressState.hpp <bb/system/SystemUiProgressState>
 *
 * @brief The possible states the progress of a task can have when shown to the user.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiProgressState
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The possible states the progress of a task can have when shown to the user.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The task's progress is ongoing.
         *
         * @since BlackBerry 10.0.0
         */
        Active      = 0,

        /*!
         * @brief The task's progress has stopped.
         *
         * @since BlackBerry 10.0.0
         */
        Inactive    = 1,

        /*!
         * @brief The task whose progress is being monitored has encountered an error.
         *
         * @since BlackBerry 10.0.0
         */
        Error       = 2
    };

private:
//!@cond PRIVATE
    SystemUiProgressState();
    ~SystemUiProgressState();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiProgressState)
#endif // BB_SYSTEM_SYSTEMUIPROGRESSSTATE_HPP
