/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef cascades_contextmenuvisualstate_h
#define cascades_contextmenuvisualstate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*! 
 * @brief The visual states for the context menu.
 *
 * The context menu is displayed along the right side of the screen and
 * is used to display actions associated with a control. The user can open
 * the context menu by long-pressing the control.
 *
 * @see @c ActionSet, @c ActionItem
 *
 * @xmlonly
 *     <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ContextMenuVisualState {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The visibility states.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*! @brief The context menu is hidden.
     *
     * @since BlackBerry 10.0.0
     */
    Hidden,
    /*! @brief The context menu is visible in compact mode.
     *
     * @since BlackBerry 10.0.0
     */
    VisibleCompact,
    /*! @brief The context menu is animating to its hidden state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToHidden,
    /*! @brief The context menu is animating to its visible compact state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToVisibleCompact,
  };
/*! @cond PRIVATE */
private:
    ContextMenuVisualState();
    ~ContextMenuVisualState();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_contextmenuvisualstate_h
