/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_layoutproperties_h
#define cascades_layoutproperties_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

    class LayoutPropertiesPrivate;
    class VisualNode;

    /*!
     * 
     * @brief Abstract base class inherited by all layout properties classes.
     *
     * For most layouts there's a corresponding @c %LayoutProperties class
     * that can be set on the individual children within that container. For example, when using a container with a
     * @c StackLayout, layout properties for its children are set using @c StackLayoutProperties.
     *
     * Layout properties determine how a control is laid out in relation to other controls
     * within the same container. Layout properties can be used to specify
     * the space quota or the x and y coordinates for controls depending on the type of layout
     * used by the parent container.
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT LayoutProperties : public UIObject {
    private:
        Q_OBJECT

    public:
        virtual ~LayoutProperties();

    protected:
    /*! @cond PRIVATE */
        LayoutProperties(LayoutPropertiesPrivate &_d_ptr);

    private:
        Q_DECLARE_PRIVATE(LayoutProperties)
        Q_DISABLE_COPY(LayoutProperties)
    /*! @endcond */
    }; // class LayoutProperties
} // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::LayoutProperties)


#endif	// cascades_layoutproperties_h

