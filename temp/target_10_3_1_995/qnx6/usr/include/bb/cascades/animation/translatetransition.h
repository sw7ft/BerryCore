/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_translatetransition_h
#define cascades_translatetransition_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/animation/abstracttransition.h>

namespace bb {
    namespace cascades {
    
class XyzTransitionPrivate;

/*!
 * @brief An animation that controls the position of a @c VisualNode.
 *
 * The translation properties of a node are specified by @c VisualNode::translationX and
 * @c VisualNode::translationY. When translating a node along its x or y
 * axis, the layout of the node is not affected, just it's positioning
 * on the screen. The translation properties correspond with actual pixel amounts. 
 *
 * You can reposition a visual node using @c from and @c to values for
 * the x and y axes (@c fromX/toX for moving horizontally and @c fromY/toY for moving vertically).
 * The @c from and @c to values
 * are always relative to the node's current position on the screen. So, if the node is
 * in the center of the screen, you would specify a negative @c toX value to move
 * the node horizontally to the right. 
 * The duration of the animation and the easing curve are specified by the @c AbstractTransition::duration
 * and @c AbstractTransition::easingCurve properties, respectively.
 *
 * When both from and to properties are specified, the transition will run
 * as normal in the specified duration, using the specified easing curve.
 *
 * If only the @c from property is specified, the transition will run from the
 * value specified by @c from to the value of the @c VisualNode::translationX or
 * @c VisualNode::translationY property at the time the animation was started.
 *
 * If only the @c to property is specified, the transition will run from the
 * current value of the @c VisualNode::translationX or
 * @c VisualNode::translationY property at the time animation started
 * to the @c to value specified by property.
 *
 * By not specifying a @c to or @c from property, the actual value remains undefined. So, you
 * should not attempt to read the value unless the corresponding @c isSet function is set to @c true
 * (for example, @c isToXSet()).
 *
 * While a property is being animated, its value does not change.
 * It's only when the animation is completed that the animated property is updated with
 * a new value. If you need access to the intermediate values for an animated property, you can 
 * be notified of changes through the @c VisualNode::translationXChanging or @c VisualNode::translationYChanging
 * signals. However, because of the frequency that
 * these signals are triggered, performance issues can arise, so they should only be used when absolutely necessary.
 *
 * Once an animation is playing, changing its properties will not have an effect
 * until the next time animation is started.
 *
 * Here's how to animate the repositioning of a button, along its x axis
 * from 10 to 100 pixels in 1000 milliseconds.
 *
 * @snippet tad/examples/animation/translatetransition/src/TranslateTransExamples.cpp translatetransition_button
 *
 * This example shows how to animate the position
 * of a button vertically from its current value to 100 using the StockCurve::CubicIn curve.
 * Once the transition is complete it is auto-deleted.
 *
 * @snippet tad/examples/animation/translatetransition/src/TranslateTransExamples.cpp translatetransition_stockcurve
 *
 * In QML, you add animations to a control's animations list, which represents
 * all of the animations that apply to the control. When you want to start the 
 * animation, you simply call its play() function. Here's how to create a button that,
 * when clicked, moves 500 pixels along its x axis over 3 seconds.
 *
 * @snippet tad/examples/animation/translatetransition/assets/main.qml translatetransition_button_qml
 *
 * @see @c VisualNode::translationX, @c VisualNode::translationY, @c VisualNode::translationXChanging,
 * @c VisualNode::translationYChanging, @c AbstractTransition
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TranslateTransition : public AbstractTransition {

   Q_OBJECT

   /*!
    * @brief Specifies the value that the VisualNode::translationX property is animated to.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(float toX READ toX WRITE setToX RESET resetToX NOTIFY toXChanged FINAL)
   /*!
    * @brief Indicates whether the @c #toX property of the transition is set.
    *
    * If @c true the @c toX property been set for this transition; if @c false the 
    * @c toX property is not set. 
    *
    * By default, @c toXSet is @c false meaning @c toX has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool toXSet READ isToXSet FINAL)
   /*!
    * @brief Specifies the value that the @c VisualNode::translationY property is animated to.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(float toY READ toY WRITE setToY RESET resetToY NOTIFY toYChanged FINAL)
   /*!
    * @brief Indicates whether the @c #toY property of the transition is set.
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
    * @brief Specifies the value from which the VisualNode::translationX property
    * is animated from.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(float fromX READ fromX WRITE setFromX RESET resetFromX NOTIFY fromXChanged FINAL)
   /*!
    * @brief Indicates whether the @c #fromX property of the transition is set.
    *
    * If @c true the @c fromX property been set for this transition; if @c false the 
    * @c fromX property is not set. 
    *
    * By default, @c fromXSet is @c false meaning @c fromX has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool fromXSet READ isFromXSet FINAL)
   /*!
    * @brief Specifies the value from which the @c VisualNode::translationY property
    * is animated from.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(float fromY READ fromY WRITE setFromY RESET resetFromY NOTIFY fromYChanged FINAL)
   /*!
    * @brief Indicates whether the @c #fromY property of the transition is set.
    *
    * If @c true the fromY property been set for this transition; if @c false the 
    * @c fromY property is not set. 
    *
    * By default, @c fromYSet is @c false meaning @c fromY has not been set.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(bool fromYSet READ isFromYSet FINAL)

public:
    /*!
     * @brief Creates %TranslateTransition object with unspecified @c to and @c from 
     * properties.
     *
     * @since BlackBerry 10.0.0
     */
    TranslateTransition();
    /*!
     * @brief Destructor for this object
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~TranslateTransition();
    
    /*!
     * @brief Returns the value of @c #fromX property of this transition if it is set.
     *
     * A valid value is returned if the @c #fromXSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of @c #fromX attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float fromX() const;
    /*!
     * @brief Sets the @c #fromX property of this transition.
     *
     * Setting a value of the property will also change the value of
     * @c #fromXSet propety to @c true.
     *
     * @param value The new value of the @c fromX property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFromX(float value);
    /*!
     * @brief Resets the @c #fromX property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     *
     * @note Resetting this property will also change the value of
     * @c fromXSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFromX();

    /*!
     * @brief Returns the value of @c #toX property of this transition if it is set.
     *
     * A valid value is returned if the @c toXSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of @c toX attribute if specified, @c 0 otherwise
     *
     * @since BlackBerry 10.0.0
     */
    float toX() const;
    /*!
     * @brief Sets the @c #toX property of this transition.
     *
     * Setting a value of the property will also change the value of #toXSet propety to @c true
     *
     * @param value The new value of the @c toX property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setToX(float value);
    /*!
     * @brief Resets the @c #toX property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * @c #toXSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetToX();

    /*!
     * @brief Returns the value of the @c #fromY property of this transition if it is set.
     *     
     * A valid value is returned if the @c fromYSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of #fromY attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float fromY() const;
    /*!
     * @brief Sets the @c #fromY property of this transition.
     *
     * Setting a value of the property will also change the value of the
     * @c #fromYSet property to @c true.
     *
     * @param value The new value of @c fromY attribute.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFromY(float value);
    /*!
     * @brief Resets the @c #fromY property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * @c #fromYSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFromY();

    /*!
     * @brief Returns the value of @c #toY property of this transition if it is set.
     * 
     * A valid value is returned if the @c #toYSet property is set to @c true, otherwise the default value of 
     * @c 0 is returned.
     *
     * @return The value of #toY attribute if specified, @c 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    float toY() const;
    /*!
     * @brief Sets the @c #toY property of this transition.
     *
     * Setting a value of the property will also change the value of @c toYSet property to @c true.
     *
     * @param value The new value of #toY attribute.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setToY(float value);
    /*!
     * @brief Resets the @c #toY property to its default value of @c 0 and marks it unset
     * from the point of view of the transition.
     *
     * Resetting this property will also change the value of
     * @c #toYSet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetToY();

   /*!
    * @brief Indicates whether the @c #toX property of the transition is set.
    *
    * @return @c true if the @c toX property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isToXSet() const;
   /*!
    * @brief Indicates whether the @c #fromX property of the transition is set.
    *
    * @return @c true if the @c fromX property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isFromXSet() const;
   /*!
    * @brief Indicates whether the @c #toY property of the transition is set.
    *
    * @return @c true if the @c toY property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isToYSet() const;
   /*!
    * @brief Indicates whether the @c #fromY property of the transition is set.
    *
    * @return @c true if the @c fromY property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isFromYSet() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c #fromX of the transition changes.
     *
     * @param fromX The new @c fromX for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void fromXChanged(float fromX);
    /*!
     * @brief Emitted when the @c #toX of the transition changes.
     *
     * @param toX The new @c toX for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void toXChanged(float toX);
    /*!
     * @brief Emitted when the @c #fromY of the transition changes.
     *
     * @param fromY The new @c fromY for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void fromYChanged(float fromY);
    /*!
     * @brief Emitted when the @c #toY of the transition changes.
     *
     * @param toY The new @c toY for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void toYChanged(float toY);

private:    

    Q_DECLARE_PRIVATE(XyzTransition)
    Q_DISABLE_COPY(TranslateTransition)
    
    // BUILDER ---------------------------------
public: 
    /*! @cond PRIVATE */
    typedef TranslateTransition ThisClass;  // The class in which scope we're currently inside
    typedef AbstractTransition BaseClass; // References the class which ThisClass derives from
    /*! @endcond */
    
    /*!
     * @brief A builder template for constructing a %TranslateTransition instance
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
         * @copydoc bb::cascades::TranslateTransition::setFromX(float)
         */
        BuilderType& fromX(float value) {
            this->instance().setFromX(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::TranslateTransition::setToX(float)
         */
        BuilderType& toX(float value) {
            this->instance().setToX(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::TranslateTransition::setFromY(float)
         */
        BuilderType& fromY(float value) {
            this->instance().setFromY(value);
            return  this->builder();
        }
        /*!
         * @copydoc bb::cascades::TranslateTransition::setToY(float)
         */
        BuilderType& toY(float value) {
            this->instance().setToY(value);
            return  this->builder();
        }
    };
    /*!
     * @brief A concrete builder class for constructing a TranslateTransition.
     *
     * See @c TranslateTransition::create() for getting a concrete 
     * builder for contructing a TranslateTransition.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, TranslateTransition> {
    public:
        explicit Builder() : TBuilder<Builder, TranslateTransition>(new TranslateTransition()) {}
    };

    /*!
     * @brief Creates and returns a builder with an optional explicit target.
     *
     * Using the builder to create the transition:
     *
     * @snippet tad/examples/animation/translatetransition/src/TranslateTransExamples.cpp translatetransition_button
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


QML_DECLARE_TYPE(bb::cascades::TranslateTransition)


#endif // cascades_translatetransition_h
