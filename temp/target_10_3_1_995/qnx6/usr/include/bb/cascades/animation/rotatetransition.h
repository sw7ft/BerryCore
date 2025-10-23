/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_rotatetransition_h
#define cascades_rotatetransition_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/animation/abstracttransition.h>

namespace bb {
    namespace cascades {
    
class XyzTransitionPrivate;
    
/*!
 * @brief An animation that rotates a @c VisualNode around its z-axis.
 *
 * When rotating a visual node, you specify the beginning and ending of the transition
 * by using the @c #fromAngleZ and @c #toAngleZ properties. The values of the @c to
 * and @c from properties represent the degrees of a circle. The duration of the animation and
 * the easing curve are specified by the @c AbstractTransition::duration and @c AbstractTransition::easingCurve
 * properties, respectively.
 *
 * When both the @c fromAngleZ and @c toAngleZ properties are specified, the transition will run
 * as normal in the specified duration, using the specified easing curve.
 *
 * If only the @c fromAngleZ property is specified, the transition will run from the
 * value specified by @c fromAngleZ to the value of the VisualNode::rotationZ property at the time
 * the animation was started.
 *
 * If only the @c toAngleZ property is specified, the transition will run from the
 * current value of the VisualNode::rotationZ property at the time animation started
 * to the @c toAngleZ that was specified.
 *
 * By not specifying a @c to or @c from property, the actual value remains undefined. So, you
 * should not attempt to read the value unless the corresponding @c isSet function is set to @c true
 * (for example, @c isToAngleZSet()).
 *
 * While a property is being animated, its value does not change.
 * It's only when the animation is completed that the animated property is updated with
 * a new value. If you need access to the intermediate values for an animated property, you can 
 * be notified of changes through the @c VisualNode::rotationZChanging signal. However, because of the frequency that
 * this signal is triggered, performance issues can arise, so it should only be used when absolutely necessary.
 *
 * Once an animation is playing, changing its properties will not have an effect
 * until the next time animation is started.
 *
 * Here's an example of how to create a transition that animates the @c rotationZ property
 * of a @c Slider from 90 to 270 in 1000 milliseconds.
 *
 * @snippet tad/examples/animation/rotatetransition/src/RotateTransitionExamples.cpp rotatetransition1
 *
 * In this example, the transition animates the @c rotationZ property
 * of the slider from its current value to 180 using @c StockCurve::CubicIn curve.
 * Once the transition is complete it is auto-deleted.
 *
 * @snippet tad/examples/animation/rotatetransition/src/RotateTransitionExamples.cpp rotatetransition2
 *
 * In QML, you add animations to a control's animations list, which represents
 * all of the animations that apply to the control. When you want to start the 
 * animation, you simply call its @c play() function. Here's how to create a button that,
 * when clicked, rotates 180 degrees over the course of three seconds:
 *
 * @snippet tad/examples/animation/rotatetransition/assets/main.qml rotatetransition_qml
 * 
 * @see VisualNode::rotationZ, VisualNode::rotationZChanging, AbstractTransition
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT RotateTransition : public AbstractTransition {

   Q_OBJECT

   /*!
    * @brief Specifies the value that the @c VisualNode::rotationZ property is animated to.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float toAngleZ READ toAngleZ WRITE setToAngleZ RESET resetToAngleZ NOTIFY toAngleZChanged FINAL)

   /*!
    * @brief Indicates whether the @c #toAngleZ property of the transition is set.
    *
    * If @c true the @c toAngleZ property been set for this transition; if @c false the 
    * @c toAngleZ property is not set. 
    *
    * By default, @c toAngleZSet is @c false meaning @c toAngleZ has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool toAngleZSet READ isToAngleZSet FINAL)

    /*!
    * @brief Specifies the value that the @c VisualNode::rotationZ property is animated from.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
     *
     * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float fromAngleZ READ fromAngleZ WRITE setFromAngleZ RESET resetFromAngleZ NOTIFY fromAngleZChanged FINAL)

   /*!
    * @brief Indicates whether the @c #fromAngleZ property of the transition is set.
    *
    * If @c true the @c fromAngleZ property been set for this transition; if @c false the 
    * @c fromAngleZ property is not set. 
    *
    * By default, @c fromAngleZSet is @c false meaning @c fromAngleZ has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool fromAngleZSet READ isFromAngleZSet FINAL)

public:
    /*!
     * @brief Creates a %RotateTransition object with unspecified @c to and @c from 
     * properties.
     *
     * @since BlackBerry 10.0.0
     */
    RotateTransition();

    /*!
     * @brief Destructor for this object
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~RotateTransition();
    
    /*!
     * @brief Returns the value of the @c #fromAngleZ property of this transition if it is set.
     *
     * A valid value is returned if the @c #fromAngleZSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of #fromAngleZ attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float fromAngleZ() const;
    /*!
     * @brief Sets the #fromAngleZ property of this transition.
     *
     * Setting a value of the property will also change the value of
     * @c fromAngleZSet property to @c true.
     *
     * @param value the new value of #fromAngleZ attribute
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFromAngleZ(float value);
    /*!
     * @brief Resets the #fromAngleZ property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of
     * #fromAngleZSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFromAngleZ();

    /*!
     * @brief Returns the value of @c #toAngleZ property of this transition if it is set.
     *
     * A valid value is returned if the @c #toAngleZSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of #toAngleZ attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float toAngleZ() const;
    /*!
     * @brief Sets the #toAngleZ property of this transition.
     *
     * Setting a value of the property will also change the value of the
     * @c #toAngleZSet property to @c true.
     *
     * @param value the new value of #toAngleZ attribute
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setToAngleZ(float value);
    /*!
     * @brief Resets the #toAngleZ property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of
     * #toAngleZSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetToAngleZ();

   /*!
    * @brief Indicates whether the @c #toAngleZSet property of the transition is set.
    *
    * @return @c true the @c toAngleZSet property is set, @c false otherwise
    *
    * @since BlackBerry 10.0.0
    */
    bool isToAngleZSet() const;

   /*!
    * @brief Indicates whether the #fromAngleZSet property of the transition is set.
    *
    * @return @c true the @c fromAngleZSet property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isFromAngleZSet() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c #fromAngleZ property of the transition changes.
     *
     * @param fromAngleZ The new @c fromAngleZ for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void fromAngleZChanged(float fromAngleZ);
    /*!
     * @brief Emitted when the #toAngleZ of the transition changes.
     *
     * @param toAngleZ The new toAngleZ for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void toAngleZChanged(float toAngleZ);

private:    

    Q_DECLARE_PRIVATE(XyzTransition)
    Q_DISABLE_COPY(RotateTransition)
    
    // BUILDER ---------------------------------
public: 
    /*! @cond PRIVATE */
    typedef RotateTransition ThisClass;  // The class in which scope we're currently inside
    typedef AbstractTransition BaseClass; // References the class which ThisClass derives from
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a RotateTransition instance.
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>                                //
    class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {              //
    protected:                                                                         //
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {  //
        }                                                                                //
    public:                                                                            //
        //-------------------------------------------------------------------------------//
        
        /*!
         * @copydoc bb::cascades::RotateTransition::setFromAngleZ(float)
         */
        BuilderType& fromAngleZ(float value) {
            this->instance().setFromAngleZ(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::RotateTransition::setToAngleZ(float)
         */
        BuilderType& toAngleZ(float value) {
            this->instance().setToAngleZ(value);
            return  this->builder();
        }
    };
    /*!
     * @brief A concrete builder class for constructing a RotateTransition.
     *
     * See RotateTransition::create() for getting a concrete 
     * builder for constructing a %RotateTransition.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, RotateTransition> {
    public:
        explicit Builder() : TBuilder<Builder, RotateTransition>(new RotateTransition()) {}
    };

    /*!
     * @brief Creates and returns a builder with an optional explicit target.
     *
     * Using the builder to create the transition:
     *
     * @snippet tad/examples/animation/rotatetransition/src/RotateTransitionExamples.cpp rotatetransition1
     *
     * @param target An optional explicit target for the transition.
     * @return A builder for creating the transition.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create(VisualNode *target = 0) {
        return Builder().target(target);
    }     
};    



}
}



QML_DECLARE_TYPE(bb::cascades::RotateTransition)


#endif // cascades_rotatetransition_h
