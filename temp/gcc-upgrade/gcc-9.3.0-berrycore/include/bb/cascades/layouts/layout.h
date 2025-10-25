/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_layout_h
#define cascades_layout_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>


namespace bb {
    namespace cascades {

    class LayoutPrivate;

    /*!
     * 
     * @brief Abstract base class inherited by all layouts.
     *
     * When a layout is set on a @c Container using @c Container::setLayout(), the container arranges its children
     * according to the rules of that particular layout. Depending on how you want to position a container's
     * children, there are three different types of layouts to choose from:
     *
     *  - @c StackLayout: Arranges children vertically or horizontally in a stack. This is the default layout
     *    for containers.
     *  - @c DockLayout: Docks children to a particular area of the container.
     *  - @c AbsoluteLayout: Places children on their specified x and y coordinates.
     *
     * Another form of input that determines how a container's children are positioned is the @c LayoutProperties
     * associated with each child. @c %LayoutProperties can be used to specify properties such as the
     * space quota, alignment, and x and y coordinates (depending on the type of layout).
     * One thing to note is that each %Layout has a corresponding @c %LayoutProperties class,
     * and they must be used together. For example, if a container uses a @c %StackLayout, its children must use 
     * @c StackLayoutProperties.
     *
     * An application can use a @c LayoutUpdateHandler to receive updates about the position and dimensions
     * of laid out controls.
     *
     * The origin of the coordinate system is the top-left corner of the container.
     *
     * @see LayoutUpdateHandler
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Layout : public UIObject {
    private:
        Q_OBJECT

    public:
        /*! @brief Destructor.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Layout();

    protected:
        /*! @brief Constructor.
         * @cond PRIVATE */
        Layout(LayoutPrivate &_d_ptr);

    private:
        Q_DECLARE_PRIVATE(Layout)
        Q_DISABLE_COPY(Layout)
        /*! @endcond */
    }; // class Layout
} // namespace bb::cascades
}


QML_DECLARE_TYPE(bb::cascades::Layout)


#endif	// cascades_layout_h
