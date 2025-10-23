/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PROCESSSTATE_HPP
#define BB_CORE_PROCESSSTATE_HPP

#include <bb/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

/*!
 * @headerfile ProcessState.hpp <bb/ProcessState>
 *
 * @brief The possible states of the process.
 *
 * @details This state indicates whether this process is currently in the Foreground
 * execution partition, the Background partition or is being moved to the Stopped partition.
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT ProcessState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The possible states of the process.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The state of the process is currently not known because this process
         * has not received an event indicating this state.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,

        /*!
         * @brief The process is executing in the Foreground partition.
         *
         * @details The process is currently receiving unbounded system resources.
         *
         * @since BlackBerry 10.0.0
         */
        Foreground = 1,
 
        /*!
         * @brief The process is executing in the Background partition.
         *
         * @details The Background partition is for processes that are allowed in the background.
         * This may include thumbnailed applications.
         * 
         * The amount of CPU available to applications in this partition can depend on external
         * factors, such as the amount of battery charge and the charging indicator. If the battery
         * charge is low, the amount of CPU for the Background partition may be restricted to either
         * extend battery life or enable faster charging.
         * 
         * A process in the Background partition is expected to make every effort to be as light
         * on the system as possible, to have minimal impact on applications running in the Foreground
         * partition. The process should consume as little memory and CPU as possible.  Connections to
         * other systems should be as brief and lightweight as can be managed.
         *
         * @since BlackBerry 10.0.0
         */
        Background = 2,

        /*!
         * @brief The process will be moving to the Stopped partition shortly.
         *
         * @details The Stopped partition is for processes that are not currently allowed
         * to execute. This state is a warning that the process will soon stop receiving
         * CPU. The process should attempt to close all connections and free all
         * possible resources as quickly as possible.  The application is not being
         * terminated, but it is likely that there will be no interaction with the
         * process for a lengthy period of time.
         * 
         * A process is typically moved to the Stopped partition after it is minimized or
         * invisible.
         *
         * @since BlackBerry 10.0.0
         */
        Stopping = 3
    };

private:
//!@cond PRIVATE
    ProcessState();
    ~ProcessState();
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::ProcessState)
#endif // BB_CORE_PROCESSSTATE_HPP
