/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_sidebarvisualstate_h
#define cascades_sidebarvisualstate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * 
 * @brief The visual states for the sidebar.
 *
 * The sidebar is displayed along the left side of the screen and
 * is used to display each of the tabs in a @c TabbedPane. Even when tabs are forced
 * onto the Action bar, they will still appear in the sidebar.
 *
 * @see @c TabbedPane
 *
 * @xmlonly
 * <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT SidebarVisualState {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The visibility states.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*! @brief The sidebar is hidden.
     *
     * @since BlackBerry 10.0.0
     */
    Hidden, 
    /*! @brief The sidebar is currently visible and is displayed in its compact state.
     *
     * @since BlackBerry 10.0.0
     */
    VisibleCompact, 
    /*! @brief The sidebar is currently visible and is displayed in its full state.
     *
     * @since BlackBerry 10.0.0
     */
    VisibleFull,
    /*! @brief The sidebar is animating to its hidden state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToHidden, 
    /*! @brief The sidebar is animating to its compact state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToVisibleCompact, 
    /*! @brief The sidebar is animating to its full state.
     *
     * @since BlackBerry 10.0.0
     */
    AnimatingToVisibleFull,
    /*! @brief The sidebar is being peeked at.
     *
     * @since BlackBerry 10.0.0
     */
    Peeking
  };
/*! @cond PRIVATE */
private:
    SidebarVisualState();
    ~SidebarVisualState();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_sidebarvisualstate_h
