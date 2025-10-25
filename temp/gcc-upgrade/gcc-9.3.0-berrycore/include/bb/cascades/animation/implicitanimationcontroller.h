/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_implicitanimationcontroller_h
#define cascades_implicitanimationcontroller_h

#include <QMetaType>
#include <QExplicitlySharedDataPointer>

#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    class VisualNode;
    class ImplicitAnimationControllerPrivate;

    /*!
     * @brief Controls implicit (automatic) property animations.
     *
     * @warning Instances of this class must be created and handled on the
     * application thread or a runtime error will occur.
     *
     * Implicit animations are animations performed by the framework when
     * a value of property changes to a new value. When a property changes,
     * the actual value of property is not animated, it's only the visual
     * representation that is animated.
     * For example, if the application changes
     * the @c VisualNode::translationX property of an object, the property value
     * is updated instantly but the visual representation of the affected control will be animated 
     * into the new position.
     *
     * Many of the core controls in the framework contain visual
     * properties that are implicitly animated, however only 
     * the following properties are allowed to be controlled using ImplicitAnimationController
     * class:
     *
     *  - VisualNode::translationX, VisualNode::translationY
     *  - VisualNode::rotationZ
     *  - VisualNode::scaleX, VisualNode::scaleY
     *  - VisualNode::pivotX, VisualNode::pivotY
     *  - VisualNode::opacity
     *
     * This class allows for controlling either a single property of a @c VisualNode or all implicitly 
     * animated properties as a whole, if no property name is specified during the creation
     * of a controller.
     *
     * User-defined properties (those which not defined by the framework in built-in 
     * controls) are not implicitly animated and can not be controlled with this class.
     *
     * For layout-related properties, like positioning, alignment, and preferred width and height,
     * you can disable implicit animations using the @c Control::implicitLayoutAnimationsEnabled flag.
     * Once disabled, all layout-related property changes will not be implicitly animated (i.e. changes
     * happen immediately).
     *
     * The scope of the effect that an @c %ImplicitAnimationController has on implicit animations is determined
     * by the lifetime of the @c %ImplicitAnimationController instance.
     *
     * When an @c %ImplicitAnimationController instance is created using
     * @c ImplicitAnimationController::create(), the implicit animation state change immediately 
     * takes effect. When this instance is destroyed the setting is reset to the original value.
     *
     * Instances of this class are implicitly shared, so
     * the referred setting will only be reset once all controller instances sharing the
     * same setting are destroyed. Assigning a controller to another controller creates
     * another instance referring to the original setting.
     *
     * Here's how you can control the scope of implicit animation changes using @c %ImplicitAnimationController.
     * First, a basic button is created and added to the scene.
     * 
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller1
     *
     * When clicked, implicit animations are disabled on the button, but only within the scope of the method.
     * When this method is complete, the controller is destroyed and the animation state is restored.
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller2
     *
     * Nested state scopes are also supported. In the following example, all animations are initially
     * disabled. Within the method, the disabled setting is overridden to allow for animations
     * just on the node's @c rotationZ property.
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller3
     *
     * For cases where implicit animations need to be controlled for a scope wider than
     * the scope of single method, one can extend the lifetime of the corresponding controller.
     * Here's a basic button that gets added to the scene graph:
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller4
     *
     * When clicked, implicit animations are disabled within the entire scope of the class.
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller5
     *
     * To change the scope of the state that is currently in effect, before the corresponding
     * controller is deleted due to being out of scope, you can assign a new controller to it:
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller6
     *
     * You must take caution not to delete an outer scope controller before 
     * the inner scope controller. If nesting is broken the results are undefined. Here's an example 
     * of how deleting the outer scope controller first can cause undesired behavior.
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller7
     * 
     * After @c allEnabled goes out of scope the animations will
     * remain disabled because the controller restores the state it was in
     * hen it was created. The following transition will not be animated.
     *
     * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller8
     *
     * <h2>Controlling implicit animations in QML</h2>
     *
     * Controlling implicit animations from QML uses a different approach more suited for the declarative nature of
     * QML. The approach uses instances of @c %ImplicitAnimationController attached to a controlled node.
     * See UIObject::attachedObjects property for more information about attached objects.
     *
     * In QML an @c %ImplicitAnimationController can be attached to any UI node. The object has two properties:
     * - QString propertyName: This represents a name of the property this instance of controller is used to 
     *   control; if this property is not specified (or set to @c null) the controller affects all implicitly 
     *   animatable properties.
     *   in the node the controller is attached to. Once declared this property cannot be changed; any changes
     *   to it after node is instantiated will be ignored and a warning will be printed out on
     *   console. The specified property name must be one of the
     *   implicitly animated properties mentioned above, otherwise the controller will have not effect and
     *   a warning will be printed out on a console during instantiation of the document's root node.
     * - boolean enabled; which controls whether implicit animations are enabled or not.
     *
     * A node cannot declare more than one controller with the same propertyName, only the first declared 
     * controller for particular property will have effect; the others will be not have any effect and will
     * not represent the state of the implicit animation for the specified property. In addition a warning
     * will be printed out during the creation of the document's root component.
     * Same rule applies to controllers not defining propertyName: only one can be declared for a node.
     *
     * A node can declare either a single controller with propertyName undeclared (meanning it will control all
     * properties of the node it is attached to) or one or more per-property contorllers. If node does declare
     * both "all-properties" and "single-property" controllers the "all-properties" controller will have effect, 
     * and the rest will be ignored and will not represent the state for their declared property correctly.
     * In addition a warning will be printed out on the console when document's root component is created.
     *
     * Here's an example of how to use an @c %ImplicitAnimationController to control some of a node's properties, using QML.
     *
     * @snippet tad/examples/animation/implicitanimation/assets/main.qml implicitanimationcontroller_qml1
     *
     * And here's how you can use an @c %ImplicitAnimationController to control all of a node's properties, using QML.
     *
     * @snippet tad/examples/animation/implicitanimation/assets/main.qml implicitanimationcontroller_qml2
     *
     * <h3>Interaction between implicit animations state changes in C++ and QML</h3>
     *
     * Per-property state changes made by scoped controllers in C++ code are reflected in
     * attached controller objects in QML, unless the controller represents all the properties for
     * the node, in which case, changes on native level aren't reflected.
     *
     * So, if there's an "opacity" animation controller attached to a node and there's a
     * C++ call that changes the implicit animation state of the "opacity" property, the
     * QML controller's state will be updated (the "enabled" property will be updated 
     * accordingly and the enabledChanged signals will be fired).
     *
     * @see QmlDocument, UIObject::attachedObjects
     *
     * @xmlonly
     * <apigrouping group="User interface/Animations"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ImplicitAnimationController {
    public:
        /*!
         * @brief Creates a controller which doesn't change any implicit animation settings.
         *
         * @warning Instances of this class must be created on the application thread or a runtime error will occur.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ImplicitAnimationController();

        /*!
         * @brief A copy constructor for ImplicitAnimationController
         *
         * @since BlackBerry 10.0.0
         */
        ImplicitAnimationController(const ImplicitAnimationController& aCopy);

        /*!
         * @brief Assignment operator for ImplicitAnimationController.
         *
         * Note that ImplicitAnimationController class is implicitly shared.
         *
         * @since BlackBerry 10.0.0
         */
        ImplicitAnimationController& operator=(const ImplicitAnimationController& other);

        /*!
         * @brief A destructor for @c %ImplicitAnimationController.
         *
         * If this instance was created to change implicit animation state the original
         * state will be restored when the destructor is executed.
         *
         * @since BlackBerry 10.0.0
         */
        ~ImplicitAnimationController();

    private:    
        /*! \cond PRIVATE */
        friend class ImplicitAnimationControllerPrivate;
        QExplicitlySharedDataPointer<ImplicitAnimationControllerPrivate> d;    
        /*! \endcond */

    public:
        /*!
         * @brief A builder class which creates instances of ImplicitAnimationController to
         * control either global or property animation state.
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT Builder {
        private:
        /*! \cond PRIVATE */
            QExplicitlySharedDataPointer<ImplicitAnimationControllerPrivate> d;    
            friend class ImplicitAnimationController;
            Builder& init(VisualNode *target, const QString &propertyName);

        public:
            Builder();
            ~Builder();
            Builder& operator=(const Builder& other);
            Builder(const Builder& aCopy);
        /*! \endcond */

            /*!
             * @brief This operator creates the instance of the @c %ImplicitAnimationController
             * with the parameters specified by this builder.
             *
             * At the point of creation of
             * @c %ImplicitAnimationController the setting takes effect.
             *
             * @since BlackBerry 10.0.0
             */    
            operator ImplicitAnimationController();

            /*!
             * @brief Specifies whether implicit animation should be enabled or disabled
             *
             * Whether this affects a single specified property or all properties of a node depends
             * on the method used to create the builder: @c create() for all properties and @c create() for
             * a single property.
             *
             * @param enabled If @c true, implicit animations are enabled, if @c false the 
             * animations are disabled.
             *
             * @since BlackBerry 10.0.0
             */    
            Builder& enabled(bool enabled);
        };
    
        /*!
         * @brief Creates a controller which will affect implicit animations for an
         * object's specified property, or for all properties of the node if the property 
         * name isn't specified.
         *
         * This controller will not have any effect and a warning will be printed out if
         *  - the specified property cannot be implicitly animated (it is not one of the supported 
         *    properties specified by the ImplicitAnimationController class)
         *  - the specified property doesn't exist in the provided node
         *  - passed target node is @c null
         * 
         * @warning This method must be called from the application thread or a runtime error will occur.
         *
         * Here's an example for how to control implicit animations for a specific property.
         *
         * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller9
         *
         * And here's how to control implicit animations for all properties:
         *
         * @snippet tad/examples/animation/implicitanimation/src/ImplicitAnimationExamples.cpp implicitanimationcontroller10
         *
         *
         * @param target A non-@c null VisualNode to control implicit animations for.
         *
         * @param propertyName An optional string parameter specifying the name of the property 
         * to be affected or QString::null (the default) indicating that the controller will affect 
         * all implicitly animated properties properties for the specified node.
         *
         * @param target A non-@c null VisualNode to control implicit animations for.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(VisualNode *target, const QString &propertyName = QString::null) {
            Builder b;
            return b.init(target, propertyName);
        }
    
    };

}
}

Q_DECLARE_METATYPE(bb::cascades::ImplicitAnimationController)

#endif	/* cascades_implicitanimationcontroller_h */


