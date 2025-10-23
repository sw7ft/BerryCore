/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_scrollviewproperties_h
#define cascades_scrollviewproperties_h

#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/scrollmode.h>
#include <bb/cascades/controls/scrollrailspolicy.h>
#include <bb/cascades/controls/scalingmethod.h>
#include <bb/cascades/resources/overscrolleffectmode.h>

namespace bb {
    namespace cascades {

        class ScrollViewPropertiesPrivate;

        /*!
         *
         * @brief A set of behavioral properties that can be applied to a @c %ScrollView.
         *
         * The @c %ScrollViewProperties class includes the following property:
         *
         * - @c scrollMode: The scroll mode for the scroll view
         *
         * Here's how to use @c %ScrollViewProperties in C++:
         *
         * @code
         * ScrollView* pMyScrollView = ScrollView::create(pMyContent);
         * pMyScrollView->setScrollMode(ScrollMode::Vertical);
         * @endcode
         *
         * And here's how to use them in QML:
         *
         * @code
         * ScrollView {
         *     Container {
         *        Button {}
         *     }
         *     scrollViewProperties {
         *         scrollMode: ScrollMode.Vertical
         *     }
         * }
         * @endcode
         *
         * @xmlonly
         * <qml>
         * <class register="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @xmlonly
         * <apigrouping group="User interface/Core controls"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT ScrollViewProperties : public UIObject {
            Q_OBJECT

            /*!
             * @brief Specifies how overscroll effects are applied.
             *
             * This property only affects the effect when the user interact with the @c ScrollView.
             * An overscroll effect is never applied to an axis that is not scrollable
             *
             * Possible values for this property are @c OverScrollEffectMode::None,
             * @c OverScrollEffectMode::OnScroll, @c OverScrollEffectMode::OnPinch, and @c OverScrollEffectMode::OnPinchAndScroll.
             *
             * When this property changes, a @c overScrollEffectModeChanged() signal is emitted.
             *
             * The default value of this property is @c ScrollMode::OnPinchAndScroll meaning that the
             * effect is applied to both scroll and scale if @c scrollMode and @c pinchToZoomEnabled
             * allows them to be applied.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bb::cascades::OverScrollEffectMode::Type overScrollEffectMode
                       READ overScrollEffectMode
                       WRITE setOverScrollEffectMode
                       RESET resetOverScrollEffectMode
                       NOTIFY overScrollEffectModeChanged FINAL)

            /*!
             * @brief The scaling method for the content.
             *
             * Specifies how the viewableArea is mapped to the
             * viewport when the scrollview is initialized or when
             * content is zoomed out to minimum zoom level
             * (when content is shown in its entirety).
             *
             * Allowed values for this property are:
             * @c AspectFit  - content is shown in the viewport in its entirety,
             *              centered vertically/horizontally if aspect ratio doesn't match,
             *              viewableArea set to content dimensions, scale is set
             *              accordingly
             * @c AspectFill - viewport is filled, visible area and scale depend on what
             *              fit in the viewport
             * @c None - content is shown with scale of 1.0f and is either
             *              cropped if the content is larger than the viewport,
             *              or centered if it is smaller
             *
             * @note method @c Fill doesn't make sense in this application, the control
             * always scales the content preserving content's aspect ratio.
             *
             * The default value is @c ScalingMethod::None.
             *
             * When changing scaling method the @c scalingMethodChanged() signal will be emitted.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bb::cascades::ScalingMethod::Type initialScalingMethod
                       READ initialScalingMethod
                       WRITE setInitialScalingMethod
                       RESET resetInitialScalingMethod
                       NOTIFY initialScalingMethodChanged FINAL)

            /*!
             * @brief Specifies whether the user can scroll content in a particular direction.
             *
             * This property only affects the ability of the user to scroll the content
             * using dragging or swiping. The application can scroll using the @c scrollToPoint()
             * method regardless of the value of this property.
             *
             * Possible values for this property are @c ScrollMode::None,
             * @c ScrollMode::Vertical, @c ScrollMode::Horizontal, and @c ScrollMode::Both.
             * If the scroll mode is disabled (scrollMode is set to @c None), the user
             * will not be able to scroll the content. When the scrolling is enabled, users are able to scroll in the
             * specified direction(s) up to the bounding edge of the container.
             *
             * Changing the @c scrollMode doesn't affect the @c viewableArea.
             *
             * When this property changes, a @c scrollModeChanged() signals is emitted.
             *
             * The default value of this property is @c ScrollMode::Vertical meaning that the user
             * can only scroll content vertically.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bb::cascades::ScrollMode::Type scrollMode
                       READ scrollMode
                       WRITE setScrollMode
                       RESET resetScrollMode
                       NOTIFY scrollModeChanged FINAL)

            /*!
             * @brief Specifies the rails policy for scrolling.
             *
             * The rails policy determines how scrolling behaves in response to a user's dragging gestures.
             * If scrolling is not locked to an axis, the scrolling behavior emulates the user's dragging gestures in
             * all directions. Otherwise, scrolling can become locked along a particular axis 
             * if the user's dragging gesture is roughly aligned with that axis.
             *
             * Rails policies do not affect programmatic scrolling (for example, calling scroll APIs like
             * @c scrollToPoint()).
             *
             * Rails policies do affect the scrolling behavior of a parent @c ScrollView. So, if a child
             * @c ScrollView has scrolling locked along a particular axis, the same will apply for the
             * parent.
             *
             * @see ScrollRailsPolicy
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(bb::cascades::ScrollRailsPolicy::Type scrollRailsPolicy
                       READ scrollRailsPolicy
                       WRITE setScrollRailsPolicy
                       RESET resetScrollRailsPolicy
                       NOTIFY scrollRailsPolicyChanged FINAL)

            /*!
             * @brief Specifies whether the user can use pinch gesture to scale the content
             * in the viewport.
             *
             * This property only affects the ability of the user to use pinch gesture
             * to scale content up or down. It does not limit the use of the APIs such as
             * zoomToPoint().
             *
             * When this property is @c true the user can use the pinch gesture to
             * scale the content up or down. The ScrollView::contentScale and
             * ScrollView::viewableArea properties of
             * the ScrollView will be updated continuously as the user applies the gesture
             * as well as when the ends the gesture.
             *
             * When this property changes a pinchToZoomEnabledChanged() signals is emited.
             *
             * The default value of this property is @c false.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bool pinchToZoomEnabled READ pinchToZoomEnabled
                       WRITE setPinchToZoomEnabled NOTIFY pinchToZoomEnabledChanged FINAL)

            /*!
             * @brief Specifies the maximum amount of scale the user can zoom content to using
             * pinch gesture.
             *
             * If the user reaches this scale factor when pinching the content won't zoom any
             * more and will bounce back to zoom level allowed by the maxContentScale.
             *
             * This property only has effect if pinchToZoomEnabled property is set to @c true,
             * meaning the user can scale the content using pinch gesture.
             *
             * When this property changes a maxContentScaleChanged() signal is emitted.
             *
             * The default value of this property is MAX_FLOAT meaning there's no scale
             * limit.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(float maxContentScale READ maxContentScale
                       WRITE setMaxContentScale NOTIFY maxContentScaleChanged FINAL)

            /*!
             * @brief Specifies the minimum amount of scale the user can zoom content to using
             * pinch gesture.
             *
             * If the user reaches this scale factor when pinching the content won't zoom any
             * more and will bounce back to zoom level allowed by the minContentScale.
             *
             * This property only has effect if pinchToZoomEnabled property is set to @c true,
             * meaning the user can scale the content using pinch gesture.
             *
             * When this property changes a minContentScaleChanged() signal is emitted.
             *
             * The default value of this property is 0 meaning there's no scale
             * limit.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(float minContentScale READ minContentScale
                       WRITE setMinContentScale NOTIFY minContentScaleChanged FINAL)

        public:
            /*!
             * @brief Constructs a @c %ScrollViewProperties.
             *
             * @since BlackBerry 10.0.0
             */
            explicit ScrollViewProperties();

            /*!
             * @brief The destructor of the @c %ScrollViewProperties.
             *
             * @since BlackBerry 10.0.0
             */
            virtual ~ScrollViewProperties();

            /*!
             * @brief Sets the overscroll effect mode of the @c %ScrollView.
             *
             * The @c overScrollEffectMode() signal will be emitted if operation was successful.
             *
             * @param overScrollEffectMode The overscroll effect mode of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setOverScrollEffectMode(bb::cascades::OverScrollEffectMode::Type overScrollEffectMode);

            /*!
             * @brief Returns the overscroll effect mode of the %ScrollView.
             *
             * The default mode is @c OverScrollEffectMode::OnPinchAndScroll.
             *
             * @return The overscroll effect mode of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            bb::cascades::OverScrollEffectMode::Type overScrollEffectMode() const;

            /*!
             * @brief Resets the current overscroll effect mode to the default mode @c ScrollMode::OnPinchAndScroll.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetOverScrollEffectMode();

            /*!
             * @brief Sets the scroll mode of the @c %ScrollView.
             *
             * The @c scrollModeChanged() signal will be emitted if operation was successful.
             *
             * @param scrollMode The scroll mode of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setScrollMode(bb::cascades::ScrollMode::Type scrollMode);

            /*!
             * @brief Returns the current scroll mode of the @c %ScrollView.
             *
             * The default mode is @c ScrollMode::Both.
             *
             * @return The scroll mode of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            bb::cascades::ScrollMode::Type scrollMode() const;

            /*!
             * @brief Resets the current scroll mode to the default mode @c ScrollMode::Both.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetScrollMode();
           
            /*!
             * @brief Sets the rails policy of the @c %ScrollView.
             *
             * The @c scrollRailsPolicyChanged() signal will be emitted if operation was successful.
             *
             * @param scrollRailsPolicy The rails policy of the @c %ScrollView.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void setScrollRailsPolicy(bb::cascades::ScrollRailsPolicy::Type scrollRailsPolicy);
            
            /*!
             * @brief Returns the current rails policy of the %ScrollView.
             *
             * @return The rails policy of the @c %ScrollView.
             *
             * @since BlackBerry 10.2.0
             */
            bb::cascades::ScrollRailsPolicy::Type scrollRailsPolicy() const;
            
            /*!
             * @brief Resets the current rails policy to the default.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void resetScrollRailsPolicy();

            /*!
             * @brief Sets the scaling method for the content of the @c %ScrollView.
             *
             * The @c scalingMethodChanged() signal will be emitted if operation was successful.
             *
             * @param scalingMethod The scaling method for the content of the @c %ScrollView. Note that method @c Fill doesn't make sense in this application, the control
             * always scales the content preserving content's aspect ratio.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setInitialScalingMethod( bb::cascades::ScalingMethod::Type scalingMethod );

            /*!
             * @brief Returns the current scale method for the content of the %ScrollView.
             *
             * The default method is @c ScalingMethod::None.
             *
             * @return The scale method for the content of the @c %ScrollView.
             *
             * @since BlackBerry 10.0.0
             */
            bb::cascades::ScalingMethod::Type initialScalingMethod() const;

            /*!
             * @brief Resets the current scaling method to the default mode @c ScalingMethod::None.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetInitialScalingMethod();

            /*!
             * @brief Set whether pinch to zoom is enabled or not.
             *
             * @param enabled Whether pinch to zoom is enabled or not
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setPinchToZoomEnabled(bool enabled);

            /*!
             * @brief Get whether pinch to zoom is enabled or not.
             *
             * @return Whether pinch to zoom is enabled or not
             *
             * @since BlackBerry 10.0.0
             */
            bool pinchToZoomEnabled() const;

            /*!
             * @brief Set the maximum allowed content scale factor for pinch zoom.
             *
             * @param scale Maximum scale factor allowed
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setMaxContentScale(float scale);

            /*!
             * @brief Get the maximum allowed content scale factor for pinch zoom.
             *
             * @return Maximum scale factor allowed
             *
             * @since BlackBerry 10.0.0
             */
            float maxContentScale() const;

            /*!
             * @brief Get the minimum allowed content scale factor for pinch zoom.
             *
             * @return Minimum scale factor allowed
             *
             * @since BlackBerry 10.0.0
             */
            float minContentScale() const;

            /*!
             * @brief Set the minimum allowed content scale factor for pinch zoom.
             *
             * @param scale Minimum scale allowed
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setMinContentScale(float scale);

        Q_SIGNALS:

            /*!
             * @brief Emitted when the overscroll effect mode has changed.
             *
             * @param newOverScrollEffectMode The new overscroll effect mode
             *
             * @since BlackBerry 10.0.0
             */
            void overScrollEffectModeChanged(bb::cascades::OverScrollEffectMode::Type newOverScrollEffectMode);

            /*!
             * @brief Emitted when the scroll mode has changed.
             *
             * @param newScrollMode The new scroll mode
             *
             * @since BlackBerry 10.0.0
             */
            void scrollModeChanged(bb::cascades::ScrollMode::Type newScrollMode);

            /*!
             * @brief Emitted when the rails policy has changed.
             *
             * @param newScrollRailsPolicy The new rails policy.
             *
             * @since BlackBerry 10.2.0
             */
            void scrollRailsPolicyChanged(bb::cascades::ScrollRailsPolicy::Type newScrollRailsPolicy);

            /*!
             * @brief Emitted when the initial scaling method has changed.
             *
             * @param newInitialScalingMethod The new initial scaling method
             *
             * @since BlackBerry 10.0.0
             */
            void initialScalingMethodChanged(bb::cascades::ScalingMethod::Type newInitialScalingMethod);

            /*!
             * @brief Emitted when pinchToZoomEnabled has changed.
             *
             * @param enabled Whether pinch to zoom is enabled or not.
             *
             * @since BlackBerry 10.0.0
             */
            void pinchToZoomEnabledChanged(bool enabled);

            /*!
             * @brief Emitted when the minimum allowed scale factor has changed.
             *
             * @param scale The new minimum content scale factor
             *
             * @since BlackBerry 10.0.0
             */
            void minContentScaleChanged(float scale);

            /*!
             * @brief Emitted when the maximum allowed scale factor has changed.
             *
             * @param scale The new maximum content scale factor
             *
             * @since BlackBerry 10.0.0
             */
            void maxContentScaleChanged(float scale);

        private:
            /*! \cond PRIVATE */
            Q_DECLARE_PRIVATE(ScrollViewProperties)
            Q_DISABLE_COPY(ScrollViewProperties)

            typedef ScrollViewProperties ThisClass;
            typedef UIObject BaseClass;
            /*! \endcond */

        };
    }
}

QML_DECLARE_TYPE(bb::cascades::ScrollViewProperties)

#endif // cascades_scrollviewproperties_h
