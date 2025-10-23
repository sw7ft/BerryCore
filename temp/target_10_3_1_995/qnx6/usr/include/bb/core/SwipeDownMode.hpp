/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_SWIPEDOWN_MODE_HPP
#define BB_CORE_SWIPEDOWN_MODE_HPP

//!@cond PRIVATE

#include <bb/Global>

#include <QObject>

namespace bb
{

/*!
 * @headerfile SwipeDownMode.hpp <bb/SwipeDownMode>
 *
 * @brief The possible modes for receiving swipe down modes.
 *
 * @details A swipe down gesture occurs when the user's finger moves from the touch-sensitive
 * bezel at the top of the screen down onto the display.  The gesture results in a @c swipedDown()
 * signal to the application.
 *
 * It is possible to control the timing and semantics of the @c swipeDown() event by setting the
 * mode using the @c UIToolkitSupport::setSwipeDownMode() method with one of the following values
 * as the parameter.
 *
 * @see @c UIToolkitSuport::setSwipeDownMode, @c UIToolkitSupportswipedDown()
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 */
class BB_CORE_EXPORT SwipeDownMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    enum Type {
        /*!
         * @brief Receive a swipe down event only on the completion of the gesture.
         *
         * @details By convention, applications should display a menu in response to this event.
         */
        OnCompletionOnly = 0,

        /*!
         * @brief Receive a swipe down event only when the gesture is started.
         *
         * @details The application will receive this event followed by a series of touch events
         * as the user's finger moves.  These touch events must be obtained using functions in 
         * @c libscreen.  By convention, an application should display a menu in response 
         * to a completed swipe down gesture.
         *
         * This mode can be useful if the UI toolkit wants to provide immediate visual feedback
         * for a swipe down gesture as it happens.  For example, this mode would allow a UI toolkit
         * to lower the menu in sync with the user's downward finger motion.
         */
        OnStartOnly = 1
    };

private:
//!@cond PRIVATE
    SwipeDownMode();
    ~SwipeDownMode();
//!@endcond
};

} // namespace bb

//!@endcond

#endif // BB_CORE_SWIPEDOWN_MODE_HPP
