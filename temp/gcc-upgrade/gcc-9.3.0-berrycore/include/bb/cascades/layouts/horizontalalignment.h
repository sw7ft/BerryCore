/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_horizontalalignment_h
#define cascades_horizontalalignment_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>


namespace bb {
    namespace cascades {

    /*!
     * 
     * @brief Ways to horizontally align a control within its parent container.
     *
     * Horizontal alignment can be set on a control using the @c Control::horizontalAlignment property. 
     * Setting the alignment only has an effect on controls within a @c StackLayout or @c DockLayout.
     * Controls in an @c AbsoluteLayout are not affected.
     *
     * The default alignment is @c Left.
     *  
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT HorizontalAlignment {
        Q_GADGET
        Q_ENUMS(Type)
    public:
        /*!
         * @brief Specifies the horizontal alignment of the control within its parent container.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
            /*! @brief Aligns to the left; this is the default alignment.
             *
             * @since BlackBerry 10.0.0
             */
            Left, 
            /*! @brief Aligns to the right.
             *
             * @since BlackBerry 10.0.0
             */
            Right, 
            /*! @brief Aligns on the horizontal center.
             *
             * @since BlackBerry 10.0.0
             */
            Center, 
            /*! @brief Expands to fill the available width.
             *
             * @since BlackBerry 10.0.0
             */
            Fill 
        };
    private:
        HorizontalAlignment();
        ~HorizontalAlignment();
    };

} // namespace bb::cascades
}

#endif // cascades_horizontalalignment_h

