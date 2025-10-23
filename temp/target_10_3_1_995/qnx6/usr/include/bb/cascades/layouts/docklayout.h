/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_docklayout_h
#define cascades_docklayout_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layout.h>


namespace bb {
    namespace cascades {

    class DockLayoutPrivate;

    /*!
     * 
     * @brief A @c Layout that docks children to a specified area of the container.
     *
     * By using the @c Control::horizontalAlignment and @c Control::verticalAlignment properties
     * you can specify where controls are docked horizontally (left, center, or right) and
     * vertically (top, center, bottom) within the layout. Controls can also 
     * be expanded/contracted to fill the container in a specified direction.
     *
     * In cases where the container of the layout should force children to be positioned within a border of its container, the
     * padding concept can be used. Each boundary of a container can be set with padding, so
     * left, right, top and bottom padding can be specified. 
     * 
     * For example, setting the left padding to 10 would mean that the left-most 10 pixels of the layout container
     * will not be available to the child controls.  
     *
     * The following examples demonstrate how to use @c %DockLayout to position buttons within a @c Container.
     * One button is docked to the top-center and the other is docked to the right-center.
     *
     * @image html docklayout.png
     *
     * QML:
     *
     * @code
     * Container {
     *     layout: DockLayout {}
     *   
     *     Button {
     *         text: "Button1"
     *         horizontalAlignment: HorizontalAlignment.Center
     *         verticalAlignment: VerticalAlignment.Top                
     *     }
     *   
     *     Button {
     *         text: "Button2"
     *         horizontalAlignment: HorizontalAlignment.Right
     *         verticalAlignment: VerticalAlignment.Center
     *     }           
     * }
     * @endcode
     *
     * C++:
     *
     * @code
     * Container* pContainer = new Container();
     * DockLayout *pDockLayout = new DockLayout();
     * pContainer->setLayout(pDockLayout);
     * 
     *
     * // Position button 1 horizontally centered and docked to the top
     * // of the container
     * Button* pButton1 = Button::create().text("Button1");
     * 
     * pButton1->setHorizontalAlignment(HorizontalAlignment::Center);
     * pButton1->setVerticalAlignment(VerticalAlignment::Top);
     *
     * // Position button 2 vertically centered and docked to the 
     * // right edge of the container
     * Button* pButton2 = Button::create().text("Button2");
     * 
     * pButton2->setHorizontalAlignment(HorizontalAlignment::Right);
     * pButton2->setVerticalAlignment(VerticalAlignment::Center);
     *
     * pContainer->add( pButton1 );
     * pContainer->add( pButton2 );
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT DockLayout : public Layout {
    private:
        Q_OBJECT        

    public:
        /*!
         * @brief Constructs a @c %DockLayout object.
         *
         * When you set a layout on a container using @c Container::setLayout() 
         * the container assumes ownership of this instance.
         *
         * @since BlackBerry 10.0.0
         */
        DockLayout();
        virtual ~DockLayout();
        
    Q_SIGNALS:
        /*! \cond PRIVATE */
    private:
        Q_DECLARE_PRIVATE(DockLayout)
        Q_DISABLE_COPY(DockLayout)
        /*! \endcond */
        

    public:
        /*! @cond PRIVATE */
        typedef DockLayout ThisClass;  
        typedef Layout BaseClass;
        /*! @endcond */

        /*!         
         * @brief A template builder class for constructing a @c %DockLayout.
         *
         * To retrieve the builder, call @c DockLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }
          
        public:
        };


        /*!        
         * @brief A concrete builder class for constructing a @c %DockLayout.
         *
         * To retrieve the builder, call @c DockLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, DockLayout> 
        {
        public:
            Builder() : TBuilder<Builder, DockLayout>(new DockLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing a dock layout.
        *
        * Using the builder to create a dock layout:
        * @code
        * DockLayout* pDockLayout = DockLayout::create()
        * @endcode
        *
        * @return A builder used for constructing a @c %DockLayout.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }
    }; // class DockLayout
} // namespace bb::cascades
}


QML_DECLARE_TYPE(bb::cascades::DockLayout)


#endif	// cascades_docklayout_h

