//Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved

#ifndef cascades_visualnode_h
#define cascades_visualnode_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/touchevent.h>
#include <bb/cascades/core/touchpropagation.h>
#include <bb/cascades/core/overlaptouchpolicy.h>

namespace bb {
    namespace cascades {

    class VisualNodePrivate;
    class AbstractAnimation;
    class TouchEvent;
    class TouchBehavior;
    class TouchEnterEvent;
    class TouchExitEvent;
    class GestureHandler;
    class AbstractEventHandler;
    class AbstractEffect;

    /*!
     * @brief A visual node in the scene graph.
     *
     * @details The position of a @c %VisualNode in the scene graph is determined by two forms of input:
     * the @c Control::layoutProperties set on the node, and 
     * the type of @c Layout of its parent node. In addition, extra transforms (translation, 
     * rotation, and scale) can be applied to offset the visual node from its layout placement.
     * When rotating or scaling a node, the @c pivotX and @c pivotY properties can be used
     * to change the anchoring point for the transition. The default pivot point for a visual
     * node is (0,0), which represents the center of the node.
     *
     * In addition to managing the transforms of a node, @c %VisualNode also contains
     * an @c opacity property for changing its transparency, and a 
     * @c visible property for specifying whether the visual node should be laid out in the scene.
     * Setting the @c visible value to @c false is not the same as setting @c opacity to 
     * @c 0.0f (fully transparent).
     * While the transparent node is still positioned by the layout and takes up room in the
     * scene, a node that is not @c visible will not be rendered or positioned inside the scene.
     *
     * Setting @c visible to @c false essentially removes the node from the scene without unlinking it from the
     * scene graph. In this state, no touch events will be sent to the node. This 
     * is a convenient way of removing nodes to optimize the performance of the scene without 
     * actually unlinking them. It is highly recommended to use this property to hide visual 
     * nodes whenever possible.
     *
     * 
     * <h2>Animating visual properties</h2>
     *
     * For most of the visual properties of a @c %VisualNode (translation, rotation, scale, and opacity),
     * changing the value at runtime initiates a default implicit animation. For example,
     * if the @c opacity property of a node is changed from 1.0 to 0.0, instead of becoming instantly transparent,
     * the visuals are animated gradually (but, the actual property value is changed right away).
     *
     * If implicit animations are not enough, a set of explicit animations can be added
     * to a visual node (using @c VisualNode:animations) for animating its properties or the
     * properties of the derived class:
     *
     * - @c FadeTransition: animates the @c opacity property
     * - @c RotateTransition: animates the @c rotationZ property
     * - @c ScaleTransition: animates the @c scaleX and @c scaleY properties
     * - @c TranslateTranstion: animates the @c translationX and @c translationY properties
     *
     * <h2>Touch events</h2>
     *
     * The visual node receives touch events through two signals: touch() and touchCapture().
     * The first one receives events delivered in the PropagationPhase::AtTarget and
     * PropagationPhase::Bubble phases, the second one receives events in the
     * PropagationPhase::Capturing phase.
     * 
     * @xmlonly
     *     <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT VisualNode : public UIObject {
        Q_OBJECT

        /*!
         * @brief The opacity of the visual node.
         *
         * A value between @c 0.0 (transparent) and @c 1.0 (opaque). This is the local opacity of the 
         * visual node, i.e. not taking the ancestor opacities into account. 
         * The default opacity is @c 1.0 (opaque).
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float opacity READ opacity WRITE setOpacity RESET resetOpacity NOTIFY opacityChanged FINAL)

        /*!
         * @brief Whether the visual node is laid out or not.
         *
         * If the visible property is set to @c false, the visual node is neither laid out nor rendered.
         * The default visible value is @c true.
         *
         * \e Important: Setting the visible value to @c false is not the same as setting opacity to 
         * @c 0.0f (transparent). While a transparent node is still laid out taking up room in the
         * scene, a node that is not visible, will neither be rendered nor laid out inside the scene.
         * It will behave as if it was removed from the scene without actually been unlinked from the
         * scene graph. No touch events will be sent to the node if the visible value is @c false. This 
         * a convenient way of removing nodes to optimize the performance of the scene without 
         * is actually unlinking them. It is highly recommended to use this property to hide visual 
         * nodes whenever possible.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible RESET resetVisible NOTIFY visibleChanged FINAL)

        /*!
         * @brief The translation of the visual node along the x-axis.
         *
         * The translationX and translationY correspond to pixels as long as the translationZ is @c 0.0.
         *
         * The translation is mostly useful for animations as it doesn't affect the actual laid out
         * position of the visual node. This translation is added after the node has been laid out so
         * it doesn't affect layout in any way.
         *
         * @see Layout for more details.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float translationX READ translationX WRITE setTranslationX RESET resetTranslationX NOTIFY translationXChanged FINAL)

        /*!
         * @brief The translation of the visual node along the y-axis.
         *
         * The translationX and translationY correspond to pixels as long as the translationZ is @c 0.0.
         *
         * The translation is mostly useful for animations as it doesn't affect the actual laid out
         * position of the visual node. This translation is added after the node has been laid out so
         * it doesn't affect layout in any way.
         *
         * @see Layout for more details.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float translationY READ translationY WRITE setTranslationY RESET resetTranslationY NOTIFY translationYChanged FINAL)

        /*!
         * @brief The rotation of the visual node around the z-axis in degrees.
         *
         * The visual node is rotated around the z-axis, centered around a pivot point defined by 
         * the components pivotX, pivotY and pivotZ. The default rotation is @c 0.0 degrees.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float rotationZ READ rotationZ WRITE setRotationZ RESET resetRotationZ NOTIFY rotationZChanged FINAL)

        /*!
         * @brief The scale factor of the visual node along the x-axis.
         *
         * The visual node is scaled along the x-axis, centered around a pivot point defined by 
         * the components pivotX, pivotY and pivotZ. The default scale factor is 1.0 (not scaled).
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float scaleX READ scaleX WRITE setScaleX RESET resetScaleX NOTIFY scaleXChanged FINAL)

        /*!
         * @brief The scale factor of the visual node along the y-axis.
         *
         * The visual node is scaled along the y-axis, centered around a pivot point defined by 
         * the components pivotX, pivotY and pivotZ. The default scale factor is 1.0 (not scaled).
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float scaleY READ scaleY WRITE setScaleY RESET resetScaleY NOTIFY scaleYChanged FINAL)        

        /*!
         * @brief The position of pivot point of the visual node along the x-axis.
         *
         * The pivot is used as the anchoring point when rotating and scaling the visual node. It 
         * is defined by the components pivotX, pivotY and pivotZ and is relative to the center of the
         * visual node. The default position of the pivot point is (@c 0.0, @c 0.0, @c 0.0), which
         * means it is at the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float pivotX READ pivotX WRITE setPivotX RESET resetPivotX NOTIFY pivotXChanged FINAL)

        /*!
         * @brief The position of pivot point of the visual node along the y-axis.
         *
         * The pivot is used as the anchoring point when rotating and scaling the visual node. It 
         * is defined by the components pivotX, pivotY and pivotZ and is relative to the center of the
         * visual node. The default position of the pivot point is (@c 0.0, @c 0.0, @c 0.0), which
         * means it is at the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float pivotY READ pivotY WRITE setPivotY RESET resetPivotY NOTIFY pivotYChanged FINAL)

    public:
        /*!
         * @brief The touch propagation mode for the visual node.
         *
         * This property controls how the visual node and its subtree partakes in touch event propagation. There 
         * are three possible modes, as defined by @c TouchPropagationMode::Type:
         *
         * \li @c TouchPropagationMode::Full means that touch events will be fully propagated to the visual 
         *     node and it's subtree.
         * \li @c TouchPropagationMode::None means no touch events will be propagated to the visual node or its 
         *     subtree. The subtree is practically invisible to the touch system.
         * \li @c TouchPropagationMode::PassThrough means touch events will not be handled by the visual node 
         *     itself, but its subtree will get touch events as usual.
         *
         * TouchPropagationMode::None can be used as an optimization if you have complex, non-interactive 
         * content, that overlaps interactive controls.
         *
         * The default propagation mode is @c TouchPropagationMode::Full.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::TouchPropagationMode::Type touchPropagationMode READ touchPropagationMode WRITE setTouchPropagationMode RESET resetTouchPropagationMode NOTIFY touchPropagationModeChanged FINAL)

        /*!
         * @brief Determines whether the visual node will prevent underlying (spatially overlapped) nodes from partaking in touch event propagation.
         *
         * If overlap touch policy is @c OverlapTouchPolicy::Deny, overlapped nodes will be excluded from touch 
         * propagation at an early stage during the processing of touch input. This means a 
         * scene with many layers of visual nodes with overlap touch policy set to @c OverlapTouchPolicy::Allow, may affect 
         * touch performance negatively.
         *
         * \note The policy has no effect if propagation mode is @c TouchPropagationMode::None for the same visual node.
         *
         * The default policy is OverlapTouchPolicy::Deny.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::OverlapTouchPolicy::Type overlapTouchPolicy READ overlapTouchPolicy WRITE setOverlapTouchPolicy NOTIFY overlapTouchPolicyChanged FINAL)
        
        /*!
         * @brief List of the touch behaviors added on the visual node.
         *
         * @xmlonly
         * <qml>
         * <property name="touchBehaviors" listType="bb::cascades::TouchBehavior" defaultProperty="no"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::TouchBehavior> touchBehaviors READ touchBehaviors FINAL)

        /*!
         * @brief List of the gesture handlers added on the visual node.
         *
         * @xmlonly
         * <qml>
         * <property name="gestureHandlers" listType="bb::cascades::GestureHandler" defaultProperty="no"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::GestureHandler> gestureHandlers READ gestureHandlers FINAL)

        /*!
         * @brief List of the animations attached to the visual node.
         *
         * This node will be used as the implicit target for the animations in this list.
         *
         * @xmlonly
         * <qml>
         * <property name="animations" listType="bb::cascades::AbstractAnimation" defaultProperty="no"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
         Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractAnimation> animations READ animations)

        /*!
         * @brief List of the event handlers added on the visual node.
         *
         * @xmlonly
         * <qml>
         * <property name="eventHandlers" listType="bb::cascades::AbstractEventHandler" defaultProperty="no"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
         Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractEventHandler> eventHandlers READ eventHandlers REVISION 3 FINAL)

        /*!
         * @brief List of the effects added on the visual node.
         *
         *
         * @since BlackBerry 10.3.1
         */
         Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractEffect> effects READ effects REVISION 4 FINAL)
    public:

        /*!
         * @brief Destructs the the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~VisualNode();

        /*!
         * @brief Adds an effect to the visual node.
         *
         * @param effect The effect to add. The ownership of the added effect will be
         * transferred to the visual node. If the added effect was previously added to another
         * visual node, it will be left on that node and added to this node.
         *
         * @see removeEffect()
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_INVOKABLE void addEffect(bb::cascades::AbstractEffect* effect);
      
        /*!
         * @brief Removes an effect to the visual node.
         *
         * @param effect The effect to remove. The ownership of the effect will
         * remain until the effect is either deleted or set as effect on another node.
         *
         * @see addEffect()
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_INVOKABLE void removeEffect(bb::cascades::AbstractEffect* effect);

        /*!
         * @brief Returns the opacity of the visual node.
         *
         * @copydetails VisualNode::opacity
         *
         * @return A value between between @c 0.0 (transparent) and @c 1.0 (opaque).
         *
         * @since BlackBerry 10.0.0
         */
        float opacity() const;

        /*!
         * @brief Sets the opacity of the visual node.
         *
         * @copydetails VisualNode::opacity
         *
         * @param opacity A value between between @c 0.0 (transparent) and @c 1.0 (opaque). If the
         *  value is outside the range it will be clamped to [@c 0.0, @c 1.0].
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setOpacity(float opacity);

        /*!
         * @brief Resets the opacity of the visual node to @c 1.0 (opaque).
         *
         * @copydetails VisualNode::opacity
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetOpacity();
        
        /*!
         * @brief Checks whether the visual node is visible or not.
         *
         * @copydetails VisualNode::visible
         *
         * @return @c true if the visual node is visible, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isVisible() const;

        /*!
         * @brief Sets whether the visual should be visible or not.
         *
         * @copydetails VisualNode::visible
         *
         * @param visible @c True to make the visual node visible, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setVisible(bool visible);

        /*!
         * @brief Resets the visual node to be visible.
         *
         * @copydetails VisualNode::visible
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetVisible();        

        /*!
         * @brief Returns the translation of the visual node along the x-axis.
         *
         * @copydetails VisualNode::translationX
         *
         * @return The translation along the the x-axis (pointing towards right).
         *
         * @since BlackBerry 10.0.0
         */
        float translationX() const;

        /*!
         * @brief Sets the translation of the visual node along the x-axis.
         *
         * @copydetails VisualNode::translationX
         *
         * @see setTranslation(float, float), setTranslation(float, float, float)
         *
         * @param translationX The translation along the the x-axis (pointing towards right).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTranslationX(float translationX);

        /*!
         * @brief Resets the translation of the visual node to @c 0.0 along the x-axis.
         *
         * @copydetails VisualNode::translationX
         *
         * @see resetTranslation()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTranslationX();

        /*!
         * @brief Returns the translation of the visual node along the y-axis.
         *
         * @copydetails VisualNode::translationY
         *
         * @return The translation along the the y-axis (pointing downwards).
         *
         * @since BlackBerry 10.0.0
         */
        float translationY() const;

        /*!
         * @brief Sets the translation of the visual node along the y-axis.
         *
         * @copydetails VisualNode::translationY
         *
         * @see setTranslation(float, float), setTranslation(float, float, float)
         *
         * @param translationY The translation along the the y-axis (pointing downwards).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTranslationY(float translationY);

        /*!
         * @brief Resets the translation of the visual node to @c 0.0 along the y-axis.
         *
         * @copydetails VisualNode::translationY
         *
          * @see resetTranslation()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTranslationY();

        /*!
         * @brief Convenience function for setting the translation along all axes.
         *
         * @copydetails VisualNode::translationX
         *
         * @see setTranslationX(), setTranslationY()
         *
         * @param translationX The translation along the the x-axis (pointing towards right).
         * @param translationY The translation along the the y-axis (pointing downwards).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTranslation(float translationX, float translationY);
        

        /*!
         * @brief Convenience function for resetting the translation along all axes.
         *
         * @copydetails VisualNode::translationX
         *
         * @see resetTranslationX(), resetTranslationY()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTranslation();
        
        /*!
         * @brief Returns the rotation of the visual node around the z-axis.
         * 
         * @copydetails VisualNode::rotationZ
         *
         * @return The rotation around the z-axis in degrees.
         *
         * @since BlackBerry 10.0.0
         */
        float rotationZ() const;
        
        /*!
         * @brief Sets the rotation of the visual node around the z-axis.
         * 
         * @copydetails VisualNode::rotationZ
         *
         * @param rotationZ The rotation around the z-axis in degrees, anchored at (pivotX and pivotY).
         * @see setPivotX(), setPivotY()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setRotationZ(float rotationZ);

        /*!
         * @brief Resets the rotation of the visual node around the z-axis to @c 0.0 degrees.
         * 
         * @copydetails VisualNode::rotationZ
         *
         * @see resetRotation()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetRotationZ();

        /*!
         * @brief Returns the scale factor of the visual node along the x-axis.
         *
         * @copydetails VisualNode::scaleX
         *
         * @return The scale factor along the x-axis.
         *
         * @since BlackBerry 10.0.0
         */
        float scaleX() const;
        
        /*!
         * @brief Sets the scale factor of the visual node along the x-axis.
         *
         * @copydetails VisualNode::scaleX
         *
         * @see setScale(), setPivotX()
         *
         * @param scaleX The scale factor along the x-axis, anchored at pivotX.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setScaleX(float scaleX);
        
        /*!
         * @brief Resets the scale factor of the visual node along the x-axis to @c 1.0 (no scaling).
         *
         * @copydetails VisualNode::scaleX
         *
         * @see resetScale()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetScaleX();
        
        /*!
         * @brief Returns the scale factor of the visual node along the y-axis.
         *
         * @copydetails VisualNode::scaleY
         *
         * @return The scale factor along the y-axis.
         *
         * @since BlackBerry 10.0.0
         */
        float scaleY() const;

        /*!
         * @brief Sets the scale factor of the visual node along the y-axis.
         *
         * @copydetails VisualNode::scaleY
         *
         * @see setScale()
         *
         * @param scaleY The scale factor along the y-axis, anchored at pivotY.
         * @see setPivotY()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setScaleY(float scaleY);
        
        /*!
         * @brief Resets the scale factor of the visual node along the y-axis to @c 1.0 (no scaling).
         *
         * @copydetails VisualNode::scaleY
         *
         * @see resetScale()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetScaleY();

       /*!
        * @brief Convenience function for setting the scale factor for each axes.
        *
        * @see setScaleX(), setScaleY(), setPivotX(), setPivotY()
        *
        * @param scaleX The scale factor along the x-axis, anchored at pivotX.
        * @param scaleY The scale factor along the y-axis, anchored at pivotY.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setScale(float scaleX, float scaleY);
        

        /*!
         * @brief Convenience function for setting the same scale factor for all axes.
         *
         * @see setScaleX(), setScaleY(), setPivotX(), setPivotY()
         *
         * @param scaleXY The scale factor to set for all axes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setScale(float scaleXY);

        /*!
         * @brief Resets the scale factor for all axis to @c 1.0 (no scaling).
         *
         * @see resetScaleX(), resetScaleY()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetScale();
        
        /*!
         * @brief Returns the position of pivot point of the visual node along the x-axis.
         *
         * @copydetails VisualNode::pivotX
         *
         * @return The position of pivot point along the x-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        float pivotX() const;
        
        /*!
         * @brief Sets the position of pivot point of the visual node along the x-axis.
         *
         * @copydetails VisualNode::pivotX
         *
         * @see setPivot(float,  float), setPivot(float,  float, float)
         *
         * @param pivotX The position of pivot point along the x-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPivotX(float pivotX);

        /*!
         * @brief Resets the position of pivot point of the visual node along the x-axis to @c 0.0 (center of node).
         *
         * @copydetails VisualNode::pivotX
         *
         * @see resetPivot()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPivotX();
        
        /*!
         * @brief Returns the position of pivot point of the visual node along the y-axis.
         *
         * @copydetails VisualNode::pivotY
         *
         * @return The position of pivot point along the y-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        float pivotY() const;
        
        /*!
         * @brief Sets the position of pivot point of the visual node along the y-axis.
         *
         * @copydetails VisualNode::pivotY
         *
         * @see setPivot(float,  float), setPivot(float,  float, float)
         *
         * @param pivotY The position of pivot point along the y-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPivotY(float pivotY);

        /*!
         * @brief Resets the position of pivot point of the visual node along the y-axis to @c 0.0 (center of node).
         *
         * @copydetails VisualNode::pivotY
         *
         * @see resetPivot()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPivotY();

        /*!
         * @brief Convenience function for setting the position of pivot point of the visual node along 
         * the x- and y-axes.
         *
         * @copydetails VisualNode::pivotX
         *
         * @see setPivotX(), setPivotY()
         *
         * @param pivotX The position of pivot point along the x-axis, relative to the center of the visual node.
         * @param pivotY The position of pivot point along the y-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPivot(float pivotX, float pivotY);

        /*!
         * @brief Convenience function for resetting the position of pivot point to @c 0.0 (center of node) along all axes.
         *
         * @copydetails VisualNode::pivotX
         *
         * @see resetPivotX(), resetPivotY()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPivot();

        /*!
         * @brief Returns the touch propagation mode for the visual node.
         *
         * @copydetails VisualNode::touchPropagationMode
         *
         * @return The touch propagation mode for the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        TouchPropagationMode::Type touchPropagationMode() const;

        /*!
         * @brief Sets the touch propagation mode for the visual node.
         *
         * @copydetails VisualNode::touchPropagationMode
         *
         * @param mode The new touch propagation mode for the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTouchPropagationMode(bb::cascades::TouchPropagationMode::Type mode);

        /*!
         * @brief Resets the touch propagation mode for the visual node to @c TouchPropagationMode::Full.
         *
         * @copydetails VisualNode::touchPropagationMode
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTouchPropagationMode();

        /*!
         * @brief Returns the overlap touch policy for the visual node.
         *
         * @copydetails VisualNode::overlapTouchPolicy
         *
         * @return The overlap touch policy for the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::OverlapTouchPolicy::Type overlapTouchPolicy() const;

        /*!
         * @brief Sets the overlap touch policy for the visual node.
         *
         * @copydetails VisualNode::overlapTouchPolicy
         * 
         * @param policy The new overlap touch policy for the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setOverlapTouchPolicy(bb::cascades::OverlapTouchPolicy::Type policy);

        /*!
         * @brief Resets the overlap touch policy for the visual node to @c OverlapTouchPolicy::Deny.
         *
         * @copydetails VisualNode::overlapTouchPolicy
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetOverlapTouchPolicy();

        /*!
         * @brief Adds a touch behavior to the visual node.
         *
         * Multiple behaviors can be added, they
         * will get evaluated in parallel.
         *
         * For example usage, refer to documentation of bb::cascades::TouchBehavior.
         *
         * @param touchBehavior The touch behavior to add. The ownership of the added touch
         * behavior will be transferred to the visual node. If the added touch behavior was
         * previously added to another visual node, it will be removed from that node and
         * added to (and owned by) this node.
         *
         * @see removeTochBehavior(), removeAllTouchBehaviors(), bb::cascades::TouchBehavior
         *
         * @since BlackBerry 10.0.0
         */
        void addTouchBehavior(TouchBehavior* touchBehavior);

        /*!
         * @brief Removes a touch behavior from the visual node.
         *
         * Once the touch behavior is removed, the visual node no longer references it, but it is still 
         * owned by the visual node. It is up to the application to either delete the removed 
         * touch behavior, transfer its ownership (by setting its parent) to another object or leave 
         * it as a child of the visual node (in which case it will be deleted with the visual node).
         *
         * @param touchBehavior The touch behavior to remove.
         *
         * @return Returns @c False if the touch behavior to remove wasn't removed from the visual node or 
         * if the touch behavior was @c 0, @c true otherwise. 
         *
         * @see removeAllTouchBehaviors()
         *
         * @since BlackBerry 10.0.0
         */
        bool removeTouchBehavior(TouchBehavior* touchBehavior);

        /*!
         * @brief Removes and deletes all touch behaviors currently added to this visual node.
         *
         * @see bb::cascades::VisualNode::addTouchBehavior
         *
         * @since BlackBerry 10.0.0
         */
        void removeAllTouchBehaviors();

        /*!
         * @brief Adds a gesture handler to the visual node.
         *
         * For example usage, refer to documentation of bb::cascades::GestureHandler.
         *
         * @param gestureHandler The gesture handler to add. The ownership of the added gesture
         * handler will be transferred to the visual node. If the added gesture handler was
         * previously added to another visual node, it will be removed from that node and
         * added to (and owned by) this node.
         *
         * @see removeGestureHandler(), removeAllGestureHandlers(), bb::cascades::GestureHandler
         *
         * @since BlackBerry 10.0.0
         */
        void addGestureHandler(GestureHandler* gestureHandler);

        /*!
         * @brief Removes a gesture handler from the visual node.
         *
         * Once the gesture handler is removed, the visual node no longer references it, but it is still 
         * owned by the visual node. It is up to the application to either delete the removed 
         * gesture handler, transfer its ownership (by setting its parent) to another object or leave 
         * it as a child of the visual node (in which case it will be deleted with the visual node).
         *
         * @param gestureHandler The gesture handler to remove.
         *
         * @return @c false if the gesture handler to remove wasn't removed from the visual node or 
         * if the gesture handler was @c 0, @c true otherwise. 
         *
         * @see removeAllGestureHandlers(), addGestureHandler()
         *
         * @since BlackBerry 10.0.0
         */
        bool removeGestureHandler(GestureHandler* gestureHandler);

        /*!
         * @brief Removes and deletes all gesture handlers currently added to this visual node.
         *
         * @see removeGestureHandler(), addGestureHandler()
         *
         * @since BlackBerry 10.0.0
         */
        void removeAllGestureHandlers();

        /*!
         * @brief Adds an event handler to the visual node.
         *
         * @param eventHandler The event handler to add. The ownership of the added event
         * handler will be transferred to the visual node. If the added event handler was
         * previously added to another visual node, it will be removed from that node and
         * added to (and owned by) this node.
         *
         * @see removeEventHandler(), removeAllEventHandlers(), bb::cascades::EventHandler
         *
         * @since BlackBerry 10.3.0
         */
        void addEventHandler(AbstractEventHandler* eventHandler);

        /*!
         * @brief Removes a event handler from the visual node.
         *
         * Once the event handler is removed, the visual node no longer references it, but it is still
         * owned by the visual node. It is up to the application to either delete the removed
         * event handler, transfer its ownership (by setting its parent) to another object or leave
         * it as a child of the visual node (in which case it will be deleted with the visual node).
         *
         * @param eventHandler The event handler to remove.
         *
         * @return @c false if the event handler to remove wasn't removed from the visual node or
         * if the event handler was @c 0, @c true otherwise.
         *
         * @see removeAllEventHandlers(), addEventHandler()
         *
         * @since BlackBerry 10.3.0
         */
        bool removeEventHandler(AbstractEventHandler* eventHandler);

        /*!
         * @brief Removes and deletes all event handlers currently added to this visual node.
         *
         * @see removeEventHandler(), addEventHandler()
         *
         * @since BlackBerry 10.3.0
         */
        void removeAllEventHandlers();

        /*!
         * @brief Adds an animation to the visual node.
         *
         * @param animation The animation to add. The ownership of the added animation will be 
         * transferred to the visual node. If the added animation was previously added to another 
         * visual node, it will be removed from that node and added to (and owned by) this node.
         *
         * @see removeAnimation(), removeAllAnimation(), animationCount(), animationAt()
         *
         * @since BlackBerry 10.0.0
         */
        void addAnimation(AbstractAnimation *animation);

        /*!
         * @brief Removes an animation from the visual node.
         *
         * Once the animation is removed, the visual node no longer references it, but it is still 
         * owned by the visual node. It is up to the application to either delete the removed 
         * animation, transfer its ownership (by setting its parent) to another object or leave 
         * it as a child of the visual node (in which case it will be deleted with the visual node).
         *
         * Here is an example on how to remove and delete all animations added to the visual node:
         * @code
         * for (int i = 0; i < animationCount(); ++i) {
         *     AbstractAnimation* animation = animationAt(i);
         *     removeAnimation(animation);
         *     delete animation;
         * }
         * @endcode
         *
         * @see removeAllAnimation(), animationCount(), animationAt(), addAnimation()
         *
         * @param animation The animation to remove.
         *
         * @return Returns @c False of the animation to remove wasn't added to the visual node or 
         * if the animation was @c 0, @c true otherwise. 
         *
         * @since BlackBerry 10.0.0
         */
        bool removeAnimation(AbstractAnimation *animation);

        /*!
         * @brief Convenience function for removing and deleting all animations added to the visual node.
         *
         * All animations added to the visual node will be removed and deleted.
         *
         * @see removeAnimation(), animationCount(), animationAt(), addAnimation()
         *
         * @since BlackBerry 10.0.0
         */
        void removeAllAnimations();


        /*!
         * @brief Returns the number of animations added to the visual node.
         *
         * This function, together with animationAt(), is used for iterating over all animations:
         * @code
         * for (int i = 0; i < animationCount(); ++i) {
         *     AbstractAnimation* animation = animationAt(i);
         *     ...
         * }
         * @endcode
         *
         * @see animationAt()
         *
         * @return The number of animations added to the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        int animationCount() const;

        /*!
         * @brief Returns an animation added at a specified index.
         *
         * This function, together with animationCount(), is used for iterating over all animations:
         * @code
         * for (int i = 0; i < animationCount(); ++i) {
         *     AbstractAnimation* animation = animationAt(i);
         *     ...
         * }
         * @endcode
         *
         * @see animationCount()
         *
         * @param index The index of the animation to retrieve. It must in the range of 
         * [ @c 0, animationCount() [, otherwise the function will return @c 0;
         *
         * @return @c The animation at the specified index; @c 0 if the index was out of range. 
         * The ownership is not changed by this call.
         *
         * @since BlackBerry 10.0.0
         */
        AbstractAnimation * animationAt(int index) const;


    Q_SIGNALS:
        /*!
         * @brief Emitted after the opacity of the visual node has changed.
         * 
         *
         * @copydetails VisualNode::opacity
         *
         * @param opacity The new opacity set on the visual node.
         * 
         * @see opacityChanging
         *
         * @since BlackBerry 10.0.0
         */
        void opacityChanged(float opacity);

        /*!
         * @brief Emitted while the opacity of the visual node is changing.
         * 
         
         * 
         * @copydetails VisualNode::opacity
         *
         * @param opacity The new opacity set on the visual node.
         * 
         * @see opacityChanged
         *
         * @since BlackBerry 10.0.0
         */
        void opacityChanging(float opacity);     
        
        /*!
         * @brief Emitted when the visible property of the visual node is changed.
         * 
         * @copydetails VisualNode::visible
         *
         * @param visible The new visible property set on the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        void visibleChanged(bool visible);
        
        /*!
         * @brief Emitted after translationX of the visual node has changed.
         * 
         * @copydetails VisualNode::translationX
         *
         * @param translationX The translation along the the x-axis (pointing towards right)
         * 
         * @see translationXChanging()
         *
         * @since BlackBerry 10.0.0
         */
        void translationXChanged(float translationX);

        /*!
         * @brief Emitted after translationY of the visual node has changed.
         * 
         * @copydetails VisualNode::translationY
         *
         * @param translationY The new translation along the the y-axis (pointing downwards).
         * 
         * @see translationYChanging()
         *
         * @since BlackBerry 10.0.0
         */
        void translationYChanged(float translationY);

        /*!
         * @brief Emitted while translationX of the visual node is changing.
         * 
         * @copydetails VisualNode::translationX
         *
         * @param translationX The new translation along the the x-axis (pointing towards right)
         * 
         * @see translationXChanged()
         *
         * @since BlackBerry 10.0.0
         */
        void translationXChanging(float translationX);

        /*!
         * @brief Emitted while translationY of the visual node is changing.         
         * 
         * @copydetails VisualNode::translationY
         *
         * @param translationY The new translation along the the y-axis (pointing downwards).
         * 
         * @see translationYChanged() 
         *
         * @since BlackBerry 10.0.0
         */
        void translationYChanging(float translationY);

        /*!
         * @brief Emitted while rotationZ of the visual node is changing.
         * 
         * @copydetails VisualNode::rotationZ
         *
         * @param rotationZ The new rotation around the z-axis in degrees.
         *
         * @see rotationZChanging()
         *
         * @since BlackBerry 10.0.0
         */
        void rotationZChanging(float rotationZ);

        /*!
         * @brief Emitted after rotationZ of the visual node has changed.
         * 
         * @copydetails VisualNode::rotationZ
         *
         * @param rotationZ The new rotation around the z-axis in degrees.
         * 
         * @see rotationZChanged()
         *
         * @since BlackBerry 10.0.0
         */
        void rotationZChanged(float rotationZ);

        /*!
         * @brief Emitted after scaleX of the visual node has changed.
         * 
         * @copydetails VisualNode::scaleX
         *
         * @param scaleX The new scale factor along the x-axis.
         * 
         * @see scaleXChanging()
         *
         * @since BlackBerry 10.0.0
         */
        void scaleXChanged(float scaleX);

        /*!
         * @brief Emitted after scaleY of the visual node has changed.
         * 
         * @copydetails VisualNode::scaleY
         *
         * @param scaleY The new scale factor along the y-axis.
         * 
         * @see scaleYChanging()
         *
         * @since BlackBerry 10.0.0
         */
        void scaleYChanged(float scaleY);

        /*!
         * @brief Emitted while scaleX of the visual node is changing.
         * 
         * @copydetails VisualNode::scaleX
         *
         * @param scaleX The new scale factor along the x-axis.
         * 
         * @see scaleXChanged()
         *
         * @since BlackBerry 10.0.0
         */
        void scaleXChanging(float scaleX);

        /*!
         * @brief Emitted while scaleY of the visual node is changing.
         * 
         * @copydetails VisualNode::scaleY
         *
         * @param scaleY The new scale factor along the y-axis.
         * 
         * @see scaleYChanged()
         *
         * @since BlackBerry 10.0.0
         */
        void scaleYChanging(float scaleY);
        
        /*!
         * @brief Emitted after pivotX of the visual node has changed.
         * 
         * @copydetails VisualNode::pivotX
         *
         * @param pivotX The new position of pivot point along the x-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        void pivotXChanged(float pivotX);

        /*!
         * @brief Emitted after pivotY of the visual node has changed.
         * 
         * @copydetails VisualNode::pivotY
         *
         * @param pivotY The new position of pivot point along the y-axis, relative to the center of the visual node.
         *
         * @since BlackBerry 10.0.0
         */
        void pivotYChanged(float pivotY);

        /*!
         * @brief Emitted when a touch event is received.
         * 
         * Adding touch behaviors is a way to influence under what circumstances the node receives events.
         *
         * @param event Pointer to the touch event.
         * 
         * @see bb::cascades::VisualNode::addTouchBehavior
         *
         * @since BlackBerry 10.0.0
         */
        void touch(bb::cascades::TouchEvent *event);

        /*!
         * @brief Emitted when a touch event is directed towards a child of this node.
         *
         * Adding touch behaviors is a way to influence under what circumstances the node receives events.
         *
         * @param event - Pointer to the touch event.
         * 
         * @see bb::cascades::VisualNode::addTouchBehavior
         *
         * @since BlackBerry 10.0.0
         */
        void touchCapture(bb::cascades::TouchEvent *event);

        /*!
         * @brief Emitted when touch enters the enter/exit area of this node.
         *
         * touchEnter is not emitted when touch down happens on the enter/exit area, but 
         * only when touch moves into the area from outside.
         *
         * <h3>Enter/exit areas</h3>
         * An enter/exit area is defined by 
         * <ul>
         *   <li> the node where the listener is connected,</li>
         *   <li> its subtree and</li>
         *   <li> overlapping nodes that are not part of the subtree</li>
         * </ul>
         * combined with the properties 
         * <ul>
         *   <li> touchPropagationMode and</li>
         *   <li> overlapTouchPolicy</li>
         * </ul>
         *
         * <h4>touchPropagationMode</h4>
         * <ul>
         *   <li> None means a node and its subtree does not count towards the enter/exit area.</li>
         *   <li> PassThrough means a node does not count towards any enter/exit area, but its subtree does.</li>
         *   <li> Full means a node and its subtree counts towards the enter/exit area.</li>
         * </ul>
         *
         * <h4>overlapTouchPolicy</h4>
         * <ul>
         *   <li> Deny means a node that overlaps an enter/exit area (and is not part of the enter/exit subtree) subtracts from the enter/exit area.</li>
         *   <li> Allow means a node that overlaps an enter/exit area (and is not part of the enter/exit subtree) doesn't affect the enter/exit area.</li>
         * </ul>
         * 
         * @image html enterexitarea.png An example.
         *
         * @param event - Pointer to the touch enter event.
         * 
         * @see touchExit
         *
         * @since BlackBerry 10.0.0
         */
        void touchEnter(bb::cascades::TouchEnterEvent *event);

        /*!
         * @brief Emitted when touch leaves the enter/exit area of this node.
         *
         * touchExit is not emitted when touch up happens on the enter/exit area, but 
         * only when touch moves out from the area.
         *
         * See touchEnter for more information. 
         *
         * @param event - Pointer to the touch exit event.
         *
         * @see touchEnter
         *
         * @since BlackBerry 10.0.0
         */
        void touchExit(bb::cascades::TouchExitEvent *event);

        /*!
         * @brief Emitted when the touch propagation mode of the visual node is changed.
         * 
         * @copydetails VisualNode::touchPropagationMode
         *
         * @param newTouchPropagationMode The new touch propagation mode for the visual node.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c touchPropagationMode instead of @c newTouchPropagationMode).
         *
         * @since BlackBerry 10.0.0
         */
        void touchPropagationModeChanged(bb::cascades::TouchPropagationMode::Type newTouchPropagationMode);

        /*!
         * @brief Emitted when the overlap touch policy of the visual node is changed.
         * 
         * @copydetails VisualNode::overlapTouchPolicy
         *
         * @param newOverlapTouchPolicy The new overlap touch policy.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c overlapTouchPolicy instead of @c newOverlapTouchPolicy).
         *
         * @since BlackBerry 10.0.0
         */
        void overlapTouchPolicyChanged(bb::cascades::OverlapTouchPolicy::Type newOverlapTouchPolicy);



    protected:
        /*! @cond PRIVATE */
        VisualNode(VisualNodePrivate &_d_ptr, VisualNode* parent = 0);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(VisualNode)
        Q_DISABLE_COPY(VisualNode)

        QDeclarativeListProperty<bb::cascades::AbstractAnimation> animations();

      	QDeclarativeListProperty<bb::cascades::TouchBehavior> touchBehaviors();
        QDeclarativeListProperty<bb::cascades::GestureHandler> gestureHandlers();

        QDeclarativeListProperty<bb::cascades::AbstractEventHandler> eventHandlers();
        QDeclarativeListProperty<bb::cascades::AbstractEffect> effects();
        /*! @endcond */
      
    // BUILDER ---------------------------------
    public: 
        /*! @cond PRIVATE */
        typedef VisualNode ThisClass;  // The class in which scope we're currently inside
        typedef UIObject BaseClass; // References the class which ThisClass derives from
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a VisualNode.
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
             * @brief Sets the translation of the visual node along the x-axis.
             *
             * @copydetails VisualNode::translationX
             *
             * @param translationX The translation along the the x-axis (pointing towards right).
             *
             * @see translate(float, float), translate(float, float, float)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& tx(float translationX) {
                this->instance().setTranslationX(translationX);
                return this->builder();
            }

            /*!
             * @brief Sets the translation of the visual node along the y-axis.
             *
             * @copydetails VisualNode::translationY
             *
             * @param translationY The translation along the the y-axis (pointing downwards).
             *
             * @see translate(float, float), translate(float, float, float)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& ty(float translationY) {
                this->instance().setTranslationY(translationY);
                return this->builder();
            }

            /*!
             * @brief Convenience function for setting the translation along each x and y-axes.
             *
             * @copydetails VisualNode::translationX
             *
             * @param translationX The translation along the the x-axis (pointing towards right).
             * @param translationY The translation along the the y-axis (pointing downwards).
             *
             * @see tx(), ty()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& translate(float translationX, float translationY) {
                this->instance().setTranslation(translationX, translationY);
                return  this->builder();
            }
          
            /*!
             * @brief Sets the rotation of the visual node around the z-axis.
             * 
             * @copydetails VisualNode::rotationZ
             *
             * @param rotationZ The rotation around the z-axis in degrees, anchored at (pivotX and pivotY).
             * 
             * @see pivotX(), pivotY()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& rz(float rotationZ) {
                this->instance().setRotationZ(rotationZ);
                return this->builder();
            }

            /*!
             * @brief Sets the scale factor of the visual node along the x-axis.
             *
             * @copydetails VisualNode::scaleX
             *
             * @param scaleX The scale factor along the x-axis, anchored at pivotX.
             * 
             * @see pivotX(), scale()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& sx(float scaleX) {
                this->instance().setScaleX(scaleX);
                return this->builder();
            }

            /*!
             * @brief Sets the scale factor of the visual node along the y-axis.
             *
             * @copydetails VisualNode::scaleY
             *
             * @param scaleY The scale factor along the y-axis, anchored at pivotY.
             * 
             * @see scale(), pivotY()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& sy(float scaleY) {
                this->instance().setScaleY(scaleY);
                return this->builder();
            }

            /*!
             * @brief Convenience function for setting the scale factor for each axes.
             *
             * @param scaleX The scale factor along the x-axis, anchored at pivotX.
             * @param scaleY The scale factor along the y-axis, anchored at pivotY.
             *
             * @see sx(), sy(), pivotX(), pivotY()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& scale(float scaleX, float scaleY) {
                this->instance().setScale(scaleX, scaleY);
                return this->builder();
            }

            /*!
             * @brief Convenience function for setting the same scale factor for all axes.
             *
             * @param scaleXY The scale factor to set for all axes, anchored at pivotX and pivotY.
             *
             * @see sx(), sy(), pivotX(), pivotY()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& scale(float scaleXY) {
                this->instance().setScale(scaleXY);
                return this->builder();
            }

            /*!
             * @brief Sets the position of pivot point of the visual node along the x-axis.
             *
             * @copydetails VisualNode::pivotX
             *
             * @param pivotX The position of pivot point along the x-axis, relative to the center of the visual node.
             *
             * @see pivot(float,  float), pivot(float,  float, float)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& pivotX(float pivotX) {
                this->instance().setPivotX(pivotX);
                return this->builder();
            }

            /*!
             * @brief Sets the position of pivot point of the visual node along the y-axis.
             *
             * @copydetails VisualNode::pivotY
             *
             * @param pivotY The position of pivot point along the y-axis, relative to the center of the visual node.
             *
             * @see pivot(float,  float), pivot(float,  float, float)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& pivotY(float pivotY) {
                this->instance().setPivotY(pivotY);
                return this->builder();
            }


            /*!
             * @brief Convenience function for setting the position of pivot point of the visual node along 
             * the x- and y-axes.
             *
             * @copydetails VisualNode::pivotX
             *
             * @param pivotX The position of pivot point along the x-axis, relative to the center of the visual node.
             * @param pivotY The position of pivot point along the y-axis, relative to the center of the visual node.
             *
             * @see pivot(float, float), pivotX(), pivotY()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& pivot(float pivotX, float pivotY) {
                this->instance().setPivot(pivotX, pivotY);
                return this->builder();
            }
          
          
            /*!
             * @brief Sets the opacity of the visual node.
             *
             * @copydetails VisualNode::opacity
             *
             * @param opacity A value between between @c 0.0 (transparent) and @c 1.0 (opaque). If the 
             *  value is outside the range it will be clamped to [@c 0.0, @c 1.0].
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& opacity(float opacity) {
                this->instance().setOpacity(opacity);
                return  this->builder();
            }

            /*!
             * @copydoc VisualNode::setVisible()
             */
            BuilderType& visible(bool visible) {
                this->instance().setVisible(visible);
                return  this->builder();
            }

            /*!
             * @copydoc VisualNode::addGestureHandler()
             */
            BuilderType& addGestureHandler(GestureHandler* gestureHandler) {
                this->instance().addGestureHandler(gestureHandler);
                return this->builder();
            }

            /*!
             * @copydoc VisualNode::addEventHandler()
             */
            BuilderType& addEventHandler(AbstractEventHandler* eventHandler) {
                this->instance().addEventHandler(eventHandler);
                return this->builder();
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the @c touch(bb::cascades::TouchEvent *) signal with the default
             * connection type Qt::AutoConnection.
             *
             * Example:
             * @code
             * Container *container = Container::create()
             *     .onTouch(this, SLOT(onTouchHandler(bb::cascades::TouchEvent*)));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onTouch(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(touch(bb::cascades::TouchEvent*)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the @c touchCapture(bb::cascades::TouchEvent *) signal with the default
             * connection type Qt::AutoConnection.
             *
             * Example:
             * @code
             * Container *container = Container::create()
             *     .onTouchCapture(this, SLOT(onTouchCaptureHandler(bb::cascades::TouchEvent*)));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onTouchCapture(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(touchCapture(bb::cascades::TouchEvent*)), receiver, method);
                return this->builder();
            }

            /*!
             * @copydoc VisualNode::addEffect()
             */
            BuilderType& addEffect(bb::cascades::AbstractEffect* effect) {
                this->instance().addEffect(effect);
                return this->builder();
            }
        };
    };
}
}


QML_DECLARE_TYPE(bb::cascades::VisualNode)


#endif	/* cascades_visualnode_h */

