/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_sidebarstate_h
#define cascades_sidebarstate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * 
 * @brief The visibility states for the Tab menu.
 *
 * The Tab menu is displayed along the left side of the screen and
 * is used to display each of the tabs in a @c TabbedPane. Even when tabs are forced
 * onto the Action bar, they will still appear in the Tab menu.
 *
 * @see @c TabbedPane
 *
 * @xmlonly
 * <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT SidebarState {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The visibility states.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*! @brief The Tab menu is hidden.
     *
     * @since BlackBerry 10.0.0
     */
    Hidden, 
    /*! @brief The Tab menu is currently visible and is displayed in its compact state.
     *
     * @since BlackBerry 10.0.0
     */
    VisibleCompact, 
    /*! @brief The Tab menu is currently visible and is displayed in its full state.
     *
     * @since BlackBerry 10.0.0
     */
    VisibleFull
  };
/*! @cond PRIVATE */
private:
    SidebarState();
    ~SidebarState();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_sidebarstate_h
