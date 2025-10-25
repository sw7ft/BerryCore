/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_stacklayout_h
#define cascades_stacklayout_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layout.h>
#include <bb/cascades/layouts/layoutorientation.h>

namespace bb {
    namespace cascades {

    class StackLayoutPrivate;


    /*!
     * 
     * @brief A layout that is used to position a container's children in a stack.
     *
     * The stack can be either vertical or horizontal, depending on the @c #orientation. The default orientation is 
     * @c LayoutOrientation::TopToBottom. The @c StackLayoutProperties class contains additional layout properties
     * that you can set on the individual children within the @c Container.
     *
     * By using the @c Control::horizontalAlignment and @c Control::verticalAlignment properties
     * you can specify where controls are positioned horizontally (left, center, or right) and
     * vertically (top, center, bottom) within the containers area in the StackLayout. Controls can also 
     * be expanded/contracted to fill the container in a specified direction.
     * 
     * In cases where children must not extend outside a container's borders, the
     * padding property can be used to create some separation between the boundary
     * of the container and its child controls. Each boundary of a container
     * (left, right, top and bottom) can have a different value set on it.
     * 
     * For example, setting the left padding to 10 would mean that the left-most 10 pixels of the layout container
     * will not be available to the child controls.
     *
     * In the following examples, a @c %StackLayout is used to position some
     * buttons in a vertical stack, centered on the screen.
     *
     * @image html stacklayout.png
     *
     * QML:
     *
     * @code
     * Container {
     *     layout: StackLayout {}
     *
     *     Button {
     *         text: "Button1"
     *         layoutProperties: StackLayoutProperties {}
     *         horizontalAlignment: HorizontalAlignment.Center
     *     }
     *     Button {
     *         text: "Button2"
     *         layoutProperties: StackLayoutProperties {}
     *         horizontalAlignment: HorizontalAlignment.Center
     *     }
     *     Button {
     *         text: "Button3"
     *         layoutProperties: StackLayoutProperties {}
     *         horizontalAlignment: HorizontalAlignment.Center
     *     }               
     * }
     * @endcode
     *
     * C++:
     *
     * @code
     * Container* pContainer = new Container();
     * StackLayout *pStackLayout = new StackLayout();
     * pStackLayout->setOrientation( LayoutOrientation::TopToBottom );
     * pContainer->setLayout(pStackLayout);
     * 
     * Button* pButton1 = Button::create().text("Button1");
     * Button* pButton2 = Button::create().text("Button2");
     * Button* pButton3 = Button::create().text("Button3");
     *
     * pButton1->setLayoutProperties( StackLayoutProperties::create()
     *         .horizontal( HorizontalAlignment::Center ) );
     * pButton2->setLayoutProperties( StackLayoutProperties::create()
     *         .horizontal( HorizontalAlignment::Center ) );
     * pButton3->setLayoutProperties( StackLayoutProperties::create()
     *         .horizontal( HorizontalAlignment::Center ) );
     *
     * pContainer->add( pButton1 );
     * pContainer->add( pButton2 );
     * pContainer->add( pButton3 );
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT StackLayout : public Layout {
    private:
        Q_OBJECT

        /*!
         * @brief The orientation for the stack layout.
         * 
         * The default value is Default
         *
         * QML example for a Container with a left-to-right StackLayout:
         * @code
         *
         * Container {
         *     layout: StackLayout {
         *         orientation: LayoutOrientation.LeftToRight;
         *     }
         * }
         * @endcode
         * The default orientation is 
         * @c TopToBottom, but @c LeftToRight, @c RightToLeft, and @c BottomToTop can also be used.
         *
         * @see LayoutOrientation
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::LayoutOrientation::Type orientation
                   READ orientation
                   WRITE setOrientation
                   RESET resetOrientation
                   NOTIFY orientationChanged
                   FINAL)
      
    public:
        /*!
         * @brief Constructs a %StackLayout object.
         *
         * When you set a layout on a container using Container::setLayout 
         * the container assumes ownership of this instance.
         *
         * @since BlackBerry 10.0.0
         */
        StackLayout();
        virtual ~StackLayout();

        /*!
         * @brief Returns the @c #orientation for the stack layout.
         *
         * @return The orientation.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::LayoutOrientation::Type orientation() const;
      
        /*!
         * @brief Sets the @c #orientation for the stack layout.
         *
         * After the orientation is set, the @c orientationChanged() signal is emitted.
         *
         * @param orientation The new orientation.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setOrientation(bb::cascades::LayoutOrientation::Type orientation);

        /*!
         * @brief Resets the @c #orientation to its default.
         *
         * The default orientation is @c LayoutOrientation::TopToBottom.
         *
         * After the orientation is reset, the @c orientationChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetOrientation();
      
    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c #orientation property changes.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c orientation instead of @c newOrientation).
         *
         * @param newOrientation The new orientation.
         *
         * @since BlackBerry 10.0.0
         */
        void orientationChanged(bb::cascades::LayoutOrientation::Type newOrientation);
      
    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(StackLayout)
        Q_DISABLE_COPY(StackLayout)
        /*! @endcond */
      
    public:
        /*! @cond PRIVATE */
        typedef StackLayout ThisClass;  
        typedef Layout BaseClass;
        /*! @endcond */

        /*!         
         * @brief A template builder class for constructing a @c %StackLayout.
         *
         * To retrieve the builder, call @c StackLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }
        public:
          
            /*!
             * @copydoc bb::cascades::StackLayout::setOrientation(bb::cascades::LayoutOrientation::Type)
             */          
            BuilderType& orientation(bb::cascades::LayoutOrientation::Type orientation) {
                this->instance().setOrientation(orientation);
                return this->builder();
            }
        };


        /*!        
         * @brief A concrete builder class for constructing a @c %StackLayout.
         *
         * To retrieve the builder, call @c StackLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, StackLayout> 
        {
        public:
            Builder() : TBuilder<Builder, StackLayout>(new StackLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing a stack layout.
        *
        * Using the builder to create a stack layout:
        * @code
        * StackLayout* stackLayout = StackLayout::create()
        *         .orientation(LayoutOrientation::LeftToRight);
        * @endcode
        *
        * @return A builder used for constructing a stack layout.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }

    }; // class StackLayout
} // namespace bb::cascades
}


QML_DECLARE_TYPE(bb::cascades::StackLayout)


#endif	// cascades_stacklayout_h
