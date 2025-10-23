/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scaletransition_h
#define cascades_scaletransition_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/animation/abstracttransition.h>

namespace bb {
  namespace cascades {
    
class XyzTransitionPrivate;

/*!
 * @brief An animation that scales the size of a @c VisualNode.
 *
 * The scale properties are specified by @c VisualNode::scaleX and @c VisualNode::scaleY. By default,
 * these properties are set to 1.0, meaning that the node isn't being scaled.
 *
 * When scaling a visual node, you can specify how the node is scaled using @c from and @c to values for
 * the x and y axes (fromX/toX for scaling the width and fromY/toY for scaling the height).
 * The duration of the animation and the easing curve are specified by the @c AbstractTransition::duration
 * and @c AbstractTransition::easingCurve properties, respectively.
 * 
 * When both the @c from and @c to properties are specified, the transition will run
 * as normal in the specified duration, using the specified easing curve.
 *
 * If only the @c from property is specified, the transition will run from the
 * value specified by @c from to the value of the @c VisualNode::scaleX or @c VisualNode::scaleY
 * property at the time the animation was started.
 *
 * If only the @c to property is specified, the transition will run from the
 * current value of the @c VisualNode::scaleX or @c VisualNode::scaleY property at the time animation started
 * to the @c to value specified by property.
 *
 * By not specifying a @c to or @c from property, the actual value remains undefined. So, you
 * should not attempt to read the value unless the corresponding @c isSet function is set to @c true
 * (for example, @c isToXSet()).
 *
 * While a property is being animated, its value does not change.
 * It's only when the animation is completed that the animated property is updated with
 * a new value. If you need access to the intermediate values for an animated property, you can 
 * be notified of changes through the @c VisualNode::scaleXChanging or @c VisualNode::scaleYChanging
 * signals. However, because of the frequency that
 * these signals are triggered, performance issues can arise, so they should only be used when absolutely necessary.
 *
 * Once an animation is playing, changing its properties will not have an effect
 * until the next time animation is started.
 *
 * Here's how you can animate a node's @c scaleX property
 * from 1 to 2 in 1000 milliseconds.
 *
 * @snippet tad/examples/animation/scaletransition/src/ScaleTransitionExamples.cpp scaletransition1
 *
 * This example shows how you can animate the @c scaleY attribute
 * of a button from its current value to 2.0 using the @c StockCurve::CubicIn curve.
 * Once the transition is complete it is automatically deleted.
 *
 * @snippet tad/examples/animation/scaletransition/src/ScaleTransitionExamples.cpp scaletransition2
 *
 * In QML, you add animations to a control's animations list, which represents
 * all of the animations that apply to the control. When you want to start the 
 * animation, you simply call its play() function. Here's how to create a button that,
 * when clicked, scales it's width to twice its original size in 3 seconds.
 *
 * @snippet tad/examples/animation/scaletransition/assets/main.qml scaletransition_qml
 *
 * To animate multiple properties at once, use @c ParallelAnimation
 *
 * @see @c VisualNode::scaleX, @c VisualNode::scaleY, @c VisualNode::scaleXChanging, 
 * @c VisualNode::scaleYChanging, @c AbstractTransition, @c ParallelAnimation
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ScaleTransition : public AbstractTransition {

   Q_OBJECT

   /*!
    * @brief Specifies the value that the @c VisualNode::scaleX property is animated to.
    *
    * By default the value of this property is not set
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float toX READ toX WRITE setToX RESET resetToX NOTIFY toXChanged FINAL)
   /*!
    * @brief Indicates whether the @c toX property of the transition is set.
    *
    * If @c true the @c toX property been set for this transition; if @c false the 
    * #toX property is not set. 
    *
    * By default, @c toXSet is @c false meaning @c toX has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool toXSet READ isToXSet FINAL)
   /*!
    * @brief Specifies the value that the @c VisualNode::scaleY property is animated to.
    *
    * By default the value of this property is not set
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float toY READ toY WRITE setToY RESET resetToY NOTIFY toYChanged FINAL)
   /*!
    * @brief Indicates whether the @c toY property of the transition is set.
    *
    * If @c true the @c toY property been set for this transition; if @c false the 
    * #toY property is not set. 
    *
    * By default, @c toYSet is @c false meaning @c toY has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool toYSet READ isToYSet FINAL)
   /*!
    * @brief Specifies the value from which the VisualNode::scaleX attribute is animated from.
    *
    * By default the value of this property is not set
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float fromX READ fromX WRITE setFromX RESET resetFromX NOTIFY fromXChanged FINAL)
   /*!
    * @brief Indicates whether the #fromX property of the transition is set.
    *
    * If @c true the fromX property been set for this transition; if @c false the 
    * #fromX property is not set. 
    *
    * By default, @c fromXSet is @c false meaning @c fromX has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool fromXSet READ isFromXSet FINAL)
   /*!
    * @brief Specifies the value from which the VisualNode::scaleY attribute is animated from.
    *
    * By default the value of this property is not set
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float fromY READ fromY WRITE setFromY RESET resetFromY NOTIFY fromYChanged FINAL)
   /*!
    * @brief Indicates whether the @c fromY property of the transition is set.
    *
    * If @c true the @c fromY property been set for this transition; if @c false the 
    * @c fromY property is not set. 
    *
    * By default, @c fromYSet is @c false meaning @c fromY has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool fromYSet READ isFromYSet FINAL)

public:
    /*!
     * @brief Creates a @c %ScaleTransition object with unspecified @c to and @c from 
     * properties.
     *
     * @since BlackBerry 10.0.0
     */
    ScaleTransition();
    /*!
     * @brief Destructor for this object
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ScaleTransition();

    /*!
     * @brief Returns the value of the @c fromX property of this transition if it is set.
     *     
     * A valid value is returned if the @c fromXSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of #fromX attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float fromX() const;
    /*!
     * @brief Sets the @c fromX property of this transition.
     *
     * Setting the value of the property will also change the value of
     * @c fromXSet propety to @c true.
     *
     * @param value The new value of #fromX attribute.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFromX(float value);
    /*!
     * @brief Resets the @c fromX property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of @c fromXSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFromX();

    /*!
     * @brief Returns the value of the @c toX property of this transition if it is set. 
     *
     * A valid value is returned if the @c toXSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of #toX attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float toX() const;
    /*!
     * @brief Sets the @c toX property of this transition.
     *
     * Setting a value of the property will also change the value of
     * @c toXSet propety to @c true.
     *
     * @param value the new value of #toX attribute
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setToX(float value);
    /*!
     * @brief Resets the @c toX property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * @c toXSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetToX();

    /*!
     * @brief Returns the value of the @c fromY property of this transition if it is set.
     *
     * A valid value is returned if the @c fromYSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of @c fromY attribute if specified, @c 0 otherwise
     *
     * @since BlackBerry 10.0.0
     */
    float fromY() const;
    /*!
     * @brief Sets the @c fromY property of this transition.
     *
     * Setting a value of the property will also change the value of
     * @c fromYSet propety to @c true
     *
     * @param value The new value of @c fromY property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFromY(float value);
    /*!
     * @brief Resets the @c fromY property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * @c fromYSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFromY();

    /*!
     * @brief Returns the value of the @c toY property of this transition if it is set.
     *     
     * A valid value is returned if the @c toYSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of the @c toY attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float toY() const;
    /*!
     * @brief Sets the @c toY property of this transition.
     *
     * Setting a value of the property will also change the value of the
     * @c toYSet property to @c true
     *
     * @param value The new value of the @c toY attribute
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setToY(float value);
    /*!
     * @brief Resets the @c toY property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * @c toYSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetToY();

   /*!
    * @brief Indicates whether the @c toX property of the transition is set.
    *
    * @return @c true the @c toX property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isToXSet() const;
   /*!
    * @brief Indicates whether the @c fromX property of the transition is set.
    *
    * @return @c true the @c fromX property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isFromXSet() const;
   /*!
    * @brief Indicates whether the @c toY property of the transition is set.
    *
    * @return @c true the @c toY property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isToYSet() const;
   /*!
    * @brief Indicates whether the @c fromY property of the transition is set.
    *
    * @return @c true the @c fromY property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isFromYSet() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c fromX property of the transition changes.
     *
     * @param fromX The new @c fromX for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void fromXChanged(float fromX);
    /*!
     * @brief Emitted when the @c toX property of the transition changes.
     *
     * @param toX The new @c toX for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void toXChanged(float toX);
    /*!
     * @brief Emitted when the @c fromY of the transition changes.
     *
     * @param fromY The new @c fromY for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void fromYChanged(float fromY);
    /*!
     * @brief Emitted when the @c toY property of the transition changes.
     *
     * @param toY The new @c toY for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void toYChanged(float toY);

private:    

    Q_DECLARE_PRIVATE(XyzTransition)
    Q_DISABLE_COPY(ScaleTransition)
    
    // BUILDER ---------------------------------
public: 
    /*! \cond PRIVATE */
    typedef ScaleTransition ThisClass;  // The class in which scope we're currently inside
    typedef AbstractTransition BaseClass; // References the class which ThisClass derives from
    /*! \endcond */
    
    /*!
     * @brief A builder template for constructing a ScaleTransition instance
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
         * @copydoc bb::cascades::ScaleTransition::setFromX(float)
         */
        BuilderType& fromX(float value) {
            this->instance().setFromX(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::ScaleTransition::setToX(float)
         */
        BuilderType& toX(float value) {
            this->instance().setToX(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::ScaleTransition::setFromY(float)
         */
        BuilderType& fromY(float value) {
            this->instance().setFromY(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::ScaleTransition::setToY(float)
         */
        BuilderType& toY(float value) {
            this->instance().setToY(value);
            return  this->builder();
        }

        /*!
         * @brief Convenience method for setting both @c fromX and
         * @c fromY simultaneously to the same value.
         *
         * Using this method can help achieve a uniform scale.
         *
         * @see @c fromX(), @c fromY()
         * @param scale The scale to use for @c fromX and @c fromY.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& fromScale(float scale) {
            this->instance().setFromX(scale);
            this->instance().setFromY(scale);
            return  this->builder();
        }

        /*!
         * @brief Convenience method for setting both @c toX and
         * @c toY simultaneously to the same value. 
         * 
         * Using this method can help achieve a uniform scale.
         *
         * @see @c toX(), @c toY()
         * @param scale The scale to use for @c toX and @c toY.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& toScale(float scale) {
            this->instance().setToX(scale);
            this->instance().setToY(scale);
            return  this->builder();
        }

    };
    /*!
     * @brief A concrete builder class for constructing a ScaleTransition.
     *
     * See @c ScaleTransition::create() for getting a concrete 
     * Builder for contructing a @c %ScaleTransition.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, ScaleTransition> {
    public:
        explicit Builder() : TBuilder<Builder, ScaleTransition>(new ScaleTransition()) {}
    };

    /*!
     * @brief Creates and returns a builder with an optional explicit target.
     *
     * Using the builder to create the transition:
     *
     * @snippet tad/examples/animation/scaletransition/src/ScaleTransitionExamples.cpp scaletransition1
     *
     * @param target The explicit target for this transition.
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

QML_DECLARE_TYPE(bb::cascades::ScaleTransition)


#endif // cascades_scaletransition_h
