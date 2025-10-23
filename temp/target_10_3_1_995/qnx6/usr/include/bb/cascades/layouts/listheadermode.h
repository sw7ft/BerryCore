/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listheadermode_h
#define cascades_listheadermode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * @brief Specifies header modes for list layouts.
 *
 * The different header modes determine if and how headers are shown by the @c %ListLayout.
 *
 * @xmlonly
 * <apigrouping group="User interface/Layouts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ListHeaderMode {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The header modes.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*!
     * @brief No headers are shown.
     *
     * Causes @c %ListView to only load items that are direct children of @c ListView::rootIndexPath.
     *
     * @since BlackBerry 10.0.0
     */
    None,
    /*! 
     * @brief Headers are shown and behave just like any other items.
     *
     * @since BlackBerry 10.0.0
     */
    Standard,
    /*!
     * @brief Headers are shown on top of the first item in each group.
     *
     * The headers don't take up any space in the layout when using this mode.
     *
     * @since BlackBerry 10.0.0
     */
    Overlay,
    /*!
     * @brief Headers are shown at the beginning of the visible area and stay there when scrolling.
     *
     * Headers do take up space in the layout when using this mode, but won't always
     * stay in that space. Headers stay at the beginning of the visible area until
     * pushed away by another header when scrolling.
     *
     * @since BlackBerry 10.0.0
     */
    Sticky,
    /*!
     * @brief A combination of the modes Sticky and Overlay.
     *
     * The headers don't take up any space in the layout when using this mode.
     * Headers stay at the beginning of the visible area until pushed away by
     * another header when scrolling.
     *
     * @since BlackBerry 10.0.0
     */
    StickyOverlay
  };
/*! @cond PRIVATE */
private:
    ListHeaderMode();
    ~ListHeaderMode();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_listheadermode_h

