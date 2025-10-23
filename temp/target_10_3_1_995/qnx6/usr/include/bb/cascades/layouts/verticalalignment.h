/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_verticalalignment_h
#define cascades_verticalalignment_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * 
 * @brief Ways to vertically align a control within its parent container.
 *
 * Vertical alignment can be set on a control using the @c Control::verticalAlignment property.
 * Setting the alignment only has an effect on controls within a @c StackLayout or @c DockLayout.
 * Controls in an @c AbsoluteLayout are not affected.
 *
 * The default alignment is @c Top.
 *
 * @xmlonly
 * <apigrouping group="User interface/Layouts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT VerticalAlignment {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief Specifies the vertical alignment of the control within its parent container.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*! @brief Aligns to the top; this is the default alignment.
         *
         * @since BlackBerry 10.0.0
         */
        Top, 
        /*! @brief Aligns to the bottom.
         *
         * @since BlackBerry 10.0.0
         */
        Bottom, 
        /*! @brief Aligns on the vertical center.
         *
         * @since BlackBerry 10.0.0
         */
        Center, 
        /*! @brief Expands to fill the available height.
         *
         * @since BlackBerry 10.0.0
         */
        Fill 
        //BaseLine?
    };
private:
    VerticalAlignment();
    ~VerticalAlignment();
};

} // namespace bb::cascades
}

#endif // cascades_verticalalignment_h

