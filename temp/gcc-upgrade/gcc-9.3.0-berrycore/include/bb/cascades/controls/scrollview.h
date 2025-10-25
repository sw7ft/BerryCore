/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_scrollview_h
#define cascades_scrollview_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/resources/scrollanimation.h>
#include <bb/cascades/resources/scrollviewproperties.h>
#include <bb/cascades/resources/scrollrole.h>

namespace bb {
    namespace cascades {

    class Container;
    class ScrollViewPrivate;

    /*!
     * @brief A container class that enables scrolling and zooming of its content.
     *
     * Zooming and scrolling can either be done interactively by the user or programmatically by the
     * application.
     *
     * A @c %ScrollView shows a "viewport" into the the content being scrolled,
     * where only the content which fits into the current viewport will be
     * shown, the rest being clipped. If the content's dimensions are smaller
     * than the viewport then the content will be shown in its entirety.
     *
     * The dimensions of the @c %ScrollView specify the viewport's size (can be controlled
     * with @c VisualNode::preferredWidth, @c VisualNode::preferredHeight, @c VisualNode::minWidth,
     * and @c VisualNode::minHeight properties).
     *
     * The application can specify whether the @c %ScrollView is interactive,
     * and which directions the user can scroll by using @c ScrollViewProperties::scrollMode.
     *
     * Using a @c %ScrollView with horizontal scrolling in C++:
     *
     * @code
     * ScrollView* pMyScrollView = ScrollView::create(pMyContent)
     *     .scrollMode(ScrollMode::Horizontal);
     * @endcode
     *
     * Using a @c %ScrollView with horizontal scrolling in QML:
     *
     * @code
     * ScrollView {
     *     id: scrollView
     *     ImageView {
     *         imageSource: "asset:///background.png"
     *     }
     *     scrollViewProperties {
     *         scrollMode: ScrollMode.Horizontal
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     * <qml>
     * <class abstract="yes" />
     * </qml>
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     *
     * @since BlackBerry 10.0.0
     */

    class BBCASCADES_EXPORT ScrollView : public Control
    {
    private:
        Q_OBJECT

        /*!
         * @brief The content to be displayed by the @c %ScrollView
         *
         * This is the default property of the @c %ScrollView control, so it does
         * not need to be explicitly declared in the QML. A control added inside
         * the @c Page will automatically be assigned to the @c content property.
         *
         * @code
         * ScrollView {
         *     Container {
         *         ImageView { imageSource: "an_image.png" }
         *     }
         * }
         * @endcode
         *
         * The default value of this property is @c 0.
         *
         * @xmlonly
         * <qml>
         * <property defaultProperty="yes"/>
         * </qml>
         * @endxmlonly
         * 
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent NOTIFY contentChanged FINAL)
        Q_CLASSINFO("DefaultProperty", "content")

        /*!
         * @brief The scale at which the content is displayed in the viewport.
         *
         * The scale is the ratio between the visible area and the viewport (the dimensions
         * of the scroll view).
         *
         * The @c contentScale changes when the ration changes in response to either 
         * user interaction (user applying pinch gesture) or to application changing
         * the visible area via calls to the @c zoomToPoint() method.
         *
         * When this property changes a @c contentScaleChanged() and @c viewableAreaChanged() signals
         * are emitted.
         *
         * The default value of this property is defined by the dimensions of the
         * @c ScrollView, the content and the value of the @c scaleMethod property.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float contentScale READ contentScale NOTIFY contentScaleChanged FINAL)

        /*!
         * @brief Specifies the properties for the @c ScrollView.
         * 
         * The properties can be changed by setting values on the @c ScrollViewProperties
         * object held by this property.
         *
         * Example when used in C++:
         *
         * @code
         * ScrollViewProperties* pMyScrollViewProp = pMyScrollView->scrollViewProperties();
         * pMyScrollViewProp->setScrollMode(ScrollMode::Horizontal);
         * @endcode
         *
         * Example when used in QML:
         *
         * @code
         * ScrollView {
         *     ImageView {imageSource: "an_image.png"}
         *
         *     scrollViewProperties {
         *        scrollMode: ScrollMode.Both
         *     }
         * }
         * @endcode
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ScrollViewProperties* scrollViewProperties READ scrollViewProperties FINAL)

        /*!
         * Represents the area which is currently being shown in the viewport
         *
         * The area is updated in response to application or user input: either
         * when the application is manipulating the viewable area using @c scrollToPoint(),
         * @c zoomToPoint() or @c zoomToRect() methods or when the user is scrolling or
         * using pinch gesture to adjust the viewable area.
         * 
         * The location and dimensions values are in content's coordinate system.
         *
         * The default value of this property depends on the value of the
         * @c scalingMethod property.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QRectF viewableArea READ viewableArea RESET resetViewableArea NOTIFY viewableAreaChanged FINAL)

      /*!
       * @brief Specifies the @c scrollRole of a scrollable @c Control.
       *
       * A @c scrollRole is an abstract concept that indicates to the framework
       * which scrollable control can be considered as main scrollable,
       * and is connected to various appropriate features such as
       * automatically hiding the Action bar. Typical characteristics for a main scrollable is that it covers
       * a big part of the screen, that it doesn't have any siblings, and that it doesn't have any other scrollable
       * controls as ancestors. Controls with @c scrollRole set to bb::cascades::ScrollRole::None 
       * are ignored and can't become a main scrollable control of the @c Page. All scrollable controls 
       * with @c %scrollRole set to @c bb::cascades::ScrollRole::Main are considered as main scrollable 
       * controls of the @c Page. A scrollable control with @c scrollRole set to @c bb::cascades::ScrollRole::Default 
       * may be considered as the main scrollable control of the @c Page if it satisfies default requirements.
       *
       * The default value is bb::cascades::ScrollRole::Default.
       *
       * @see Page::actionBarAutoHideBehavior
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bb::cascades::ScrollRole::Type scrollRole READ scrollRole WRITE setScrollRole RESET resetScrollRole NOTIFY scrollRoleChanged FINAL)

    public:

        /*!
         * @brief Constructs a @c ScrollView and assigns a parent container.
         *
         * The ownership of the scroll view is transferred to the parent if one is specified.
         *
         * @param parent The parent container, or @c 0. This parameter is optional.
         * The default is @c 0 if you don't specify a parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ScrollView(bb::cascades::Container * parent = 0);

        /*!
         * @brief The destructor of the @c ScrollView.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ScrollView();

        /*!
         * @brief Sets the content for the @c %ScrollView.
         *
         * Ownership will always be transferred to the @c %ScrollView.
         * If the @c %ScrollView already has @c content specified, the old content will still be owned by @c %ScrollView
         * and destroyed when the @c %ScrollView is destroyed.
         *
         * If the operation was successful, the @c contentChanged() signal will be emitted.
         *
         * @param content The content for the scroll view. Can be set to @c 0 to remove content (old content will 
         *                still be owned by the @c %ScrollView).
         *
         * @since BlackBerry 10.0.0
         */
        void setContent(bb::cascades::Control* content);

        /*!
         * @brief Gets the active content for the @c ScrollView.
         *
         * Ownership will not be transferred.
         *
         * @return The content for the @c ScrollView.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Control* content() const;

        /*!
         * @brief The viewable area of the content in scaled coordinated
         *
         * @return The viewable area.
         *
         * @since BlackBerry 10.0.0
         */
        QRectF viewableArea() const;

        /*!
         * @brief Get the scale of the content.
         *
         * @return Scale of content.
         *
         * @since BlackBerry 10.0.0
         */
        float contentScale() const;

        /*!
         * @brief Gets the current @c %ScrollView properties.
         *
         * @return The @c %ScrollView properties.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ScrollViewProperties* scrollViewProperties() const;

        /*!
         * @brief Changes the @c x and @c y coordinates of the top left corner
         * of the @c viewableArea in the local
         * coordinate system of the content, without changing the current
         * @c contentScale.
         *
         * If the requested position can not be accommodated (for example,
         * if the provided coordinates place the visible area outside the
         * content's dimensions), the visible area is set as
         * close as possible to the requested parameters while 
         * still keeping the visible area within content's bounds.
         *
         * Once set, the @c viewableArea property is updated accordingly.
         * 
         *
         * @param x The x coordinate of the intended center of the visible area.
         * @param y The y coordinate of the intended center of the visible area.
         * @param scrollAnimation Animation types for scrolling.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void scrollToPoint(float x, float y, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default );
        
        /*!
         * @brief Resets the viewable area and content scale factor to the values determined by
         * the scalingMethod property.
         *
         * When this method is called the viewable area and content scale will be
         * set to the values determined by the @c scalingMethod property.
         *
         *
         * @param scrollAnimation Animation types for scrolling.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void resetViewableArea( bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default );
        
        /*!
         * @brief Changes the @c viewableArea to be positioned such that its
         * center is in @c x, @c y coordinates in the local coordinate system
         * of the content, and @c contentScale to be the provided @c scale.
         *
         * If requested position and scale could not be accommodated (for example
         * if provided coordinates place the visible area to be outside of the
         * content's dimensions), the visible area and the scale will be chosen
         * to be as close as possible to the requested parameters while 
         * still keeping the visible area to be within content's bounds.
         *
         * If provided scale is equal to the current value of @c contentScale this
         * method is similar to @c scrollToPoint() except the visible area
         * will be position with x,y being the center instead of 
         * x,y being in top the left corner as with @c %scrollToPoint() method.
         * 
         * This method could be used to display certain area in
         * of the content with specified zoom level, such as when user taps
         * an area of the content.
         *
         * @c %viewableArea and @c %contentScale properties will be updated accordingly.
         *
         *
         * @param x The x coordinate of the intended center of the visible area.
         * @param y The y coordinate of the intended center of the visible area.
         * @param contentScale A positive intended contentScale. If passed content scale is
         * not positive the method call is ignored and a warning is printed out.
         * @param scrollAnimation Animation types for scrolling.
         *
         * @since BlackBerry 10.1.0
         */
        Q_INVOKABLE void zoomToPoint( float x, float y, float contentScale, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default );

        /*!
         * @brief Changes the @c viewableArea to be positioned such that its
         * top left corner is at the provided @c x, @c y coordinates in the
         * content's local coordinate system, and the dimensions of the 
         * visible area are such that at least @c width x @c height are of 
         * the content is visible with the scale factor not exceeding @c maxScale
         *
         * If requested position and dimensions could not be accommodated (for example
         * if provided coordinates place the visible area to be outside of the
         * content's dimensions), the visible area and the content scale will 
         * be chosen to be as close as possible to the requested parameters while 
         * still keeping the visible area to be within content's bounds.
         *
         * This method could be used to ensure that certain area of the content
         * is visible at certain maximum scale. For example, if the user selects
         * an area of interest and it needs to be zoomed in but not to fill
         * the visible area entirely.
         *
         * @c viewableArea and @c contentScale properties will be updated accordingly.
         *
         *
         * @param rect A valid @c rect to zoom to in unscaled coordinates. If @c rect is not
         * valid the method call is ignored and a warning is printed out.
         * @param scrollAnimation Animation types for scrolling.
         *
         * @since BlackBerry 10.1.0
         */
        Q_INVOKABLE void zoomToRect( const QRectF& rect, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default );


        /*!
         * @brief Gets the current @c scrollRole for the @c %ScrollView.
         *
         * @return The current @c scrollRole for the @c %ScrollView.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::ScrollRole::Type scrollRole() const;

        /*!
         * @brief Sets the @c %ScrollView scrollRole.
         *
         * Signal @c scrollRoleChanged() is emitted if value is changed.
         * @param scrollRole Specifies the new scrollRole of the @c %ScrollView.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setScrollRole(bb::cascades::ScrollRole::Type scrollRole);

        /*!
         * @brief Resets the @c scrollRole of a @c Control.
         *
         * Default value is @c ScrollRole::Default.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetScrollRole();

    Q_SIGNALS:

        /*!
         * @brief Emitted when @c ScrollView::scrollRole has changed.
         *
         * @param newScrollRole The new @c scrollRole of the @c %ScrollView.
         *
         * @since BlackBerry 10.1.0
         */
        void scrollRoleChanged(bb::cascades::ScrollRole::Type newScrollRole);

        /*!
         * @brief Emitted when the content of this @c %ScrollView has changed.
         *
         * @param content The new content of this @c %ScrollView.
         *
         * @since BlackBerry 10.0.0
         */
        void contentChanged(bb::cascades::Control* content);

        /*!
         * @brief Emitted when the visible area is being changed.
         *
         * This signal is emitted in response to a continious gesture (pinch,
         * panning), or during animations (kinetic scrolling or animation of the
         * visible area to a new location or scale).
         *
         * This signal is a convenient place to listen to the scale factor
         * currently being applied by the user and adjust content if
         * certain scale threshold is reached.
         *
         * @param viewableArea A center aligned rect with width and height 
         * of the content shown in the viewport.
         * @param contentScale The scale of the content.
         *
         * @since BlackBerry 10.0.0
         */
        void viewableAreaChanging(const QRectF &viewableArea, float contentScale);

        /*!
         * @brief Emitted when the visible area has changed.
         *
         * This signal is emitted when a user gesture, such as pinch, 
         * has been completed, and or implicit animations were completed.
         *
         * This signal is convenient place to update the content if
         * required (for example after user finished a pinch gesture
         * and higher resolution content needs to be loaded), or
         * if content placeholder needs to be replaced with real
         * content.
         *
         * @param viewableArea A center aligned rect with width and height 
         * of the content that is shown in the viewport.
         * @param contentScale The scale of the content.
         *
         * @since BlackBerry 10.0.0
         */
        void viewableAreaChanged(const QRectF &viewableArea, float contentScale);

        /*!
         * @brief Emitted when the scale has changed.
         *
         * @param scale The new scale
         *
         * @since BlackBerry 10.0.0
         */
         void contentScaleChanged( float scale );
         
    protected:
        /*! @cond PRIVATE */
        ScrollView(ScrollViewPrivate &_d_ptr, Container *parent = 0);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */

      

        Q_DECLARE_PRIVATE(ScrollView)

        typedef ScrollView ThisClass;
        typedef Control BaseClass;
        /*! @endcond */

    public:
        /*!
         * @brief A builder template for constructing a @c ScrollView.
         *
         * To retrieve the builder, call @c ScrollView::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        public:

            /*!
             * @brief Sets the content for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollview->setContent(myControl);
             * @endcode
             *
             * @param control The @c Control to set as content in the @c ScrollView, or @c QString::Null to remove content.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& content(bb::cascades::Control* control) {
                this->instance().setContent(control);
                return this->builder();
            }

            /*!
             * @brief Sets the overscroll effect mode for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollViewProp = myScrollview->scrollViewProperties();
             * myScrollviewProp->setOverScrollEffectMode(OverScrollEffectMode::OnScroll);
             * @endcode
             *
             * @param overScrollEffectMode The overscroll effect mode of the %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& overScrollEffectMode(bb::cascades::OverScrollEffectMode::Type overScrollEffectMode) {
                this->instance().scrollViewProperties()->setOverScrollEffectMode(overScrollEffectMode);
                return this->builder();
            }

            /*!
             * @brief Sets the scroll mode for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollViewProp = myScrollview->scrollViewProperties();
             * myScrollviewProp->setScrollMode(ScrollMode::Both);
             * @endcode
             *
             * @param mode The scroll mode of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& scrollMode(bb::cascades::ScrollMode::Type mode) {
                this->instance().scrollViewProperties()->setScrollMode(mode);
                return this->builder();
            }

            /*!
             * @brief Sets the scroll role for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollview->setScrollRole(role);
             * @endcode
             *
             * @param role The scroll role of the @c %ScrollView.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& scrollRole(bb::cascades::ScrollRole::Type role) {
              this->instance().setScrollRole(role);
                return this->builder();
            }

            /*!
             * @brief Sets the initial scaling method for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollViewProp = myScrollview->scrollViewProperties();
             * myScrollviewProp->setInitialScalingMethod(ScalingMethod::AspectFit);
             * @endcode
             *
             * @param scalingMethod The initial scaling method of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& initialScalingMethod(bb::cascades::ScalingMethod::Type scalingMethod) {
                this->instance().scrollViewProperties()->setInitialScalingMethod(scalingMethod);
                return this->builder();
            }

            /*!
             * @brief Sets if pinch-to-zoom is enabled for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollViewProp = myScrollview->scrollViewProperties();
             * myScrollviewProp->setPinchToZoomEnabled(true);
             * @endcode
             *
             * @param enabled Whether pinch-to-zoom is enabled or not.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& pinchToZoomEnabled(bool enabled) {
                this->instance().scrollViewProperties()->setPinchToZoomEnabled(enabled);
                return this->builder();
            }

            /*!
             * @brief Sets minimum content scale for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollViewProp = myScrollview->scrollViewProperties();
             * myScrollviewProp->setMinContentScale(0.5f);
             * @endcode
             *
             * @param minScale The minimum content scale.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& minContentScale(float minScale) {
                this->instance().scrollViewProperties()->setMinContentScale(minScale);
                return this->builder();
            }

            /*!
             * @brief Sets maximum content scale for this @c ScrollView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myScrollViewProp = myScrollview->scrollViewProperties();
             * myScrollviewProp->setMaxContentScale(2.0f);
             * @endcode
             *
             * @param maxScale The maximum content scale.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& maxContentScale(float maxScale) {
                this->instance().scrollViewProperties()->setMaxContentScale(maxScale);
                return this->builder();
            }
        };

        /*!
         * @brief A builder that constructs a @c ScrollView.
         *
         * To retrieve the builder, call @c ScrollView::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ScrollView> {
        public:
            explicit Builder() : TBuilder<Builder, ScrollView>(new ScrollView()) {}
        };

        /*!
         * @brief Creates and returns a builder for constructing a @c ScrollView.
         *
         * Using the builder to create a @c %ScrollView:
         * @code
         * ScrollView* myScrollView = ScrollView::create().content(myControl);
         * @endcode
         *
         * @return A builder used for constructing a @c %ScrollView.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }

        /*!
         * @brief Creates and returns a builder for constructing a @c %ScrollView with content.
         *
         * Using the builder to create a @c %ScrollView:
         * @code
         * ScrollView* myScrollView = ScrollView::create(myControl);
         * @endcode
         *
         * This builder is a convenience constructor for creating a %ScrollView with content. This
         * is equivalent to the following:
         * @code
         * ScrollView::create().content(myControl);
         * @endcode
         *
         * @param content The content for the scroll view.
         * @return A builder used to create a @c %ScrollView with content.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(bb::cascades::Control* content) {
            return Builder().content(content);
        }
    };

  } // namespace Heimdall
} // namespace TAD

QML_DECLARE_TYPE(bb::cascades::ScrollView)

#endif // cascades_scrollview_h
