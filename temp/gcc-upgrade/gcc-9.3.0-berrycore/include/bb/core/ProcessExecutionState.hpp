/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PROCESSEXECUTIONSTATE_HPP
#define BB_CORE_PROCESSEXECUTIONSTATE_HPP

//!@cond PRIVATE

#include <bb/Global>

#include <QObject>

namespace bb
{

/*!
 * @headerfile ProcessExecutionState.hpp <bb/ProcessExecutionState>
 *
 * @brief The possible execution states of the process.
 *
 * @details This state indicates whether this process is currently executing or not.
 * The timing of execution state changes, specifically the transition from Active to Inactive,
 * is directly affected by the "Application Behavior" setting on the device. 
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 */
class BB_CORE_EXPORT ProcessExecutionState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    enum Type {
        /*!
         * @brief The execution state of the process is currently not known because this process
         * has not received an event indicating this state.
         */
        Unknown = 0,

        /*!
         * @brief The process is inactive (i.e., no longer executing)
         *
         * @details In general, the process will no longer be receiving CPU time.
         */
        Inactive = 1,
 
        /*!
         * @brief The process is active (i.e., executing) 
         */
        Active = 2
    };

private:
//!@cond PRIVATE
    ProcessExecutionState();
    ~ProcessExecutionState();
//!@endcond
};

} // namespace bb

//!@endcond

#endif // BB_CORE_PROCESSEXECUTIONSTATE_HPP
