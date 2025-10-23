/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
//! @cond PRIVATE
#ifndef BB_SYSTEM_CONTEXTACTIVITYSTATE_HPP
#define BB_SYSTEM_CONTEXTACTIVITYSTATE_HPP

#include <bb/system/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile ContextActivityState.hpp <bb/system/ContextActivityState>
 *
 * @brief A list of generalized activity states, used in Context Collection events.
 *
 * @xmlonly
 * <apigrouping group="Platform/Context collector"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 */
class BB_SYSTEM_EXPORT ContextActivityState
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief A list of generalized activity states, used in Context Collection events.
     */
    enum Type { 

        /*!
         * @brief An activity was started.
         */
        Start = 0,
        
        /*!
         * @brief An activity was paused.
         */
        Pause = 1,
        
        /*!
         * @brief An activity was stopped.
         */
        Stop = 2
    };

private:
    //! @cond PRIVATE
    ContextActivityState();
    ~ContextActivityState();
    //! @endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ContextActivityState)
#endif // BB_SYSTEM_CONTEXTACTIVITYSTATE_HPP
//! @endcond
