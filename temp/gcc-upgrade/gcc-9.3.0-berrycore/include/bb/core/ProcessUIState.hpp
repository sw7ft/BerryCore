/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PROCESSUISTATE_HPP
#define BB_CORE_PROCESSUISTATE_HPP

//!@cond PRIVATE

#include <bb/Global>

#include <QObject>

namespace bb
{

/*!
 * @headerfile ProcessUIState.hpp <bb/ProcessUIState>
 *
 * @brief The possible UI states of the process.
 *
 * @details The states reflect how much of the display that a running application is currently
 * using.
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 */
class BB_CORE_EXPORT ProcessUIState
{
    Q_GADGET
    Q_ENUMS(bb::ProcessUIState::Type)

public:
    enum Type {
        /*!
         * @brief This object does not yet know the UI state of the process, because this process has not
         * received any events indicating the state since this object was created.
         */
        Unknown = 0,

        /*!
         * @brief The UI of the process cannot be seen by the user.
         *
         * @details This can happen when another application is in the @c Fullscreen state.  It can also
         * happen when the thumbnailed application window is off-screen during an application switch.
         */
        Invisible = 1,

        /*!
         * @brief The UI of the process is visible but is not taking up the complete display.
         *
         * @details For example, a process's UI is in this state when a thumbnailed representation of the
         * application is visible during an application switch.
         */
        Thumbnailed = 2,

        /*!
         * @brief The UI of the process is currently visible and taking up the complete display.
         */
        FullScreen = 3
    };

private:
//!@cond PRIVATE
    ProcessUIState();
    ~ProcessUIState();
//!@endcond    
};

} // namespace bb

//!@endcond

#endif // BB_CORE_PROCESSUISTATE_HPP
