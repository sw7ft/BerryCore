/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_actionmenuvisualstate_h
#define cascades_actionmenuvisualstate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * 
 * @brief The visual states for the action menu.
 *
 * The action menu is displayed along the right side of the screen and
 * is used to display the actions on a @c Page. Even when actions appear
 * on the action bar, they will also appear in the action menu.
 *
 * @see @c Page, @c ActionItem
 *
 * @xmlonly
 * <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ActionMenuVisualState {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The visibility states.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*! 
     * @brief The action menu is hidden.
     *
     * @since BlackBerry 10.0.0
     */
    Hidden, 
    /*! 
     * @brief The action menu is currently visible and is displayed in its full state.
     *
     * @since BlackBerry 10.0.0
     */
    VisibleFull,
    /*! 
     * @brief The action menu is animating to its hidden state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToHidden, 
    /*! 
     * @brief The action menu is animating to its full state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToVisibleFull
  };
/*! @cond PRIVATE */
private:
    ActionMenuVisualState();
    ~ActionMenuVisualState();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_sidebarvisualstate_h
