/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_absolutelayout_h
#define cascades_absolutelayout_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layout.h>


namespace bb {
    namespace cascades {

    class AbsoluteLayoutPrivate;

    /*!
     * 
     * @brief A Layout that allows you to set X and Y coordinates for controls.
     *
     * The following figure shows an absolute layout with three images positioned to be slightly
     * overlapping (and rotated).
     *
     * @image html absolute_position_example.png
     *
     * When controls are added to the container, they are positioned at (0,0) unless X and Y coordinates
     * are specified in the child control's @c layoutProperties. When applying @c layoutProperties to a control, 
     * you must ensure that you use an @c AbsoluteLayoutProperties object, otherwise the layout properties will
     * be ignored.
     *
     * Though the absolute layout allows for the precise positioning of controls, for most UIs it's recommended
     * that you use one of the other layouts instead (e.g. @c StackLayout or @c DockLayout). When using @c %AbsoluteLayout, 
     * resizing the UI for different displays and handling orientation changes becomes difficult. In cases where
     * the dimensions are relatively static, such as with a custom control, using an absolute layout might
     * be the preferred option.
     *
     * The following examples demonstrates how to position a button using an @c %AbsoluteLayout. The X and Y
     * coordinates are set to 100, 100.
     *
     * @image html absolute_position_button.png
     *
     * QML:
     *
     * @code
     * Container {
     *     layout: AbsoluteLayout {}
     *      
     *     Button {
     *         text: "Button"
     *         layoutProperties: AbsoluteLayoutProperties {
     *             positionX: 100
     *             positionY: 100    
     *         }                
     *     }    
     * }
     * @endcode
     *
     * C++:
     *
     * @code
     * Container* pContainer = new Container();
     * AbsoluteLayout *pAbsoluteLayout = new AbsoluteLayout();
     * pContainer->setLayout(pAbsoluteLayout);
     * 
     * AbsoluteLayoutProperties* pProperties = AbsoluteLayoutProperties::create();
     * pProperties->setPositionX(100.0);
     * pProperties->setPositionY(100.0);
     *
     * Button* pButton = Button::create().text("Button");
     * pButton->setLayoutProperties(pProperties);
     * pContainer->add( pButton );
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbsoluteLayout : public Layout {
    private:
        Q_OBJECT

    public:
        /*!
         * @brief Constructs an @c %AbsoluteLayout object.
         * 
         * When you set a layout on a container using @c Container::setLayout() 
         * the container assumes ownership of this instance. 
         *
         * @since BlackBerry 10.0.0
         */
        AbsoluteLayout();
        virtual ~AbsoluteLayout();

        /*! @cond PRIVATE */
        
    private:
        Q_DECLARE_PRIVATE(AbsoluteLayout)
        Q_DISABLE_COPY(AbsoluteLayout)
        /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef AbsoluteLayout ThisClass;  
        typedef Layout BaseClass;
        /*! @endcond */

        /*!         
         * @brief A builder template for constructing an @c %AbsoluteLayout.
         * 
         * To retrieve the builder, call @c AbsoluteLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }
        };


        /*!        
         * @brief A builder for constructing a @c %AbsoluteLayout.
         *
         * To retrieve the builder, call @c AbsoluteLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, AbsoluteLayout> 
        {
        public:
            Builder() : TBuilder<Builder, AbsoluteLayout>(new AbsoluteLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing an @c %AbsoluteLayout.
        *
        * Using the builder to create an @c %AbsoluteLayout object:
        * @code
        * AbsoluteLayout* pAbsoluteLayout = AbsoluteLayout::create()
        * @endcode
        *
        * @return A builder used for constructing an @c %AbsoluteLayout object.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }

    }; // class AbsoluteLayout
} // namespace bb::cascades

}

QML_DECLARE_TYPE(bb::cascades::AbsoluteLayout)


#endif	// cascades_absolutelayout_h

