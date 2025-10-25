/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_layoutorientation_h
#define cascades_layoutorientation_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * 
 * @brief The different orientations that can be used for layouts.
 *
 * The orientation determines the direction that children are added to the parent.
 * The default orientation is @c #TopToBottom.
 *
 * @xmlonly
 * <apigrouping group="User interface/Layouts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT LayoutOrientation {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The orientations.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*! @brief Stacks children vertically, from top to bottom; this is the default orientation.
     *
     * @since BlackBerry 10.0.0
     */
    TopToBottom, 
    /*! @brief Stacks children horizontally, from left to right.
     *
     * @since BlackBerry 10.0.0
     */
    LeftToRight, 
    /*! @brief Stacks children horizontally, from right to left.
     *
     * @since BlackBerry 10.0.0
     */
    RightToLeft, 
    /*! @brief Stacks children vertically, from bottom to top.
     *
     * @since BlackBerry 10.0.0
     */
    BottomToTop  
  };
/*! @cond PRIVATE */
private:
    /*! @brief Constructs a %LayoutOrientation object.
     *
     * @since BlackBerry 10.0.0
     */
    LayoutOrientation();
    /*! @brief Destroys a %LayoutOrientation object.
     *
     * @since BlackBerry 10.0.0
     */
    ~LayoutOrientation();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_layoutorientation_h

