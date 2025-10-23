/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_fadetransition_h
#define cascades_fadetransition_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/animation/abstracttransition.h>

namespace bb {
    namespace cascades {
    
class FadeTransitionPrivate;
    
/*!
 * 
 * @brief An animation that controls the opacity of a @c VisualNode.
 *
 * The opacity property of a node is specified by the @c VisualNode::opacity property.
 * How the opacity changes is determined by the @c fromOpacity and @c toOpacity values that are specified
 * in the transition.
 * By default, a visual node's opacity is 1.0, meaning that it is fully opaque. A value of 0.0
 * indicates that the node is fully transparent.
 * The duration of the animation and the easing curve are specified by the @c AbstractTransition::duration
 * and @c AbstractTransition::easingCurve properties, respectively.
 *
 * When both the @c from and @c to properties are specified, the transition will run as
 * normal in the specified duration, using the specified easing curve.
 *
 * If only the @c from property is specified, the transition will run from the
 * @c from value specified to the current value of the @c %VisualNode::opacity property at the
 * time the animation started. 
 *
 * If only the @c to property is specified, the transition will run from the
 * current value of the @c %VisualNode::opacity property at the time animation started
 * to the @c to value specified by property.
 *
 * By not specifying a @c to or @c from property, the actual value remains undefined. So, you
 * should not attempt to read the value unless the corresponding @c isSet function is set to @c true
 * (for example, @c isToOpacitySet()).
 *
 * While a property is being animated, its value does not change.
 * It's only when the animation is completed that the animated property is updated with
 * a new value. If you need access to the intermediate values for an animated property, you can 
 * be notified of changes through the @c VisualNode::opacityChanging() signal.
 * However, because of the frequency that
 * these signals are triggered, performance issues can arise, so they should only be used when absolutely necessary.
 *
 * Once an animation is playing, changing its properties will not have an effect
 * until the next time animation is started.
 *
 * Here's an example of how you can animate the opacity property
 * of a button, from 0 to 1 in 1000 milliseconds:
 *
 * @snippet tad/examples/animation/fadetransition/src/FadeTransitionExamples.cpp fadetransition_button
 *
 * This examples shows how you can animate the opacity property
 * of the button from its current value to 0 using the StockCurve::CubicIn curve.
 * Once the transition is complete it is auto-deleted.
 *
 * @snippet tad/examples/animation/fadetransition/src/FadeTransitionExamples.cpp fadetransition_stockcurve
 * 
 * And here is how you can create a %FadeTransition in QML:
 *
 * @snippet tad/examples/animation/fadetransition/assets/main.qml fadetransition_button_qml
 *
 * @see VisualNode::opacity, VisualNode::opacityChanging, AbstractTransition
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT FadeTransition : public AbstractTransition {

   Q_OBJECT

   /*!
    * @brief Specifies the value that the @c VisualNode::opacity attribute is animated to.
    *
    * The value of this attribute is in \c [0..1] range.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(float toOpacity READ toOpacity WRITE setToOpacity RESET resetToOpacity NOTIFY toOpacityChanged FINAL)
   /*!
    * @brief Indicates whether the @c #toOpacity property of the transition is set.
    *
    * If @c true the @c toOpacity property been set for this transition; if @c false the 
    * @c toOpacity property is not set. 
    *
    * By default, @c toOpacitySet is @c false meaning @c toOpacity has not been set.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(bool toOpacitySet READ isToOpacitySet FINAL)
   /*!
    * @brief Specifies the value from which the @c VisualNode::opacity attribute is animated from.
    *
    * The value of this attribute is in @c [0..1] range.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * By default the value of this property is not set.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(float fromOpacity READ fromOpacity WRITE setFromOpacity RESET resetFromOpacity NOTIFY fromOpacityChanged FINAL)
   /*!
    * @brief Indicates whether the @c #fromOpacity property of the transition is set.
    *
    * If @c true the @c fromOpacity property been set for this transition; if @c false the 
    * @c fromOpacity property is not set. 
    *
    * By default, @c fromOpacitySet is @c false meaning @c fromOpacity has not been set.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(bool fromOpacitySet READ isFromOpacitySet FINAL)

public:
    /*!
     * @brief Creates a %FadeTransition object with unspecified \c to and \c from 
     * properties.
     *
     * @since BlackBerry 10.0.0
     */
    FadeTransition();
    /*!
     * @brief Destructor for this object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~FadeTransition();
    
    /*!
     * @brief Returns the value of the transition's @c #fromOpacity property if it is set.
     *     
     * A valid value is returned if the @c fromOpacitySet property is set to @c true, 
     * otherwise the default value of @c 0 is returned.
     *
     * @return The value of @c fromOpacity property if specified, @c 0 otherwise
     *
     * @since BlackBerry 10.0.0
     */
    float fromOpacity() const;
    /*!
     * @brief Sets the @c #fromOpacity property of this transition.
     *
     * Setting a value of the property will also change the value of @c #fromOpacitySet property to @c true
     *
     * @param value the new value of #fromOpacity property
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFromOpacity(float value);
    /*!
     * @brief Resets the #fromOpacity property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * @c #fromOpacitySet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFromOpacity();

    /*!
     * @brief Returns the value of @c #toOpacity property of this transition if it is set. 
     * 
     * A valid value is returned if the @c #toOpacitySet property is set to @c true, 
     * otherwise the default value of @c 0 is returned.
     *
     * @return The value of @c toOpacity property if specified, @c 0 otherwise
     *
     * @since BlackBerry 10.0.0
     */
    float toOpacity() const;
    /*!
     * @brief Sets the @c #toOpacity property of this transition.
     *
     * Setting a value of the property will also change the value of @c #toOpacitySet propety to @c true
     *
     * @param value The new value of the @c toOpacity property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setToOpacity(float value);
    /*!
     * @brief Resets the #toOpacity property to its default value of @c 0.
     *
     * Once reset, the property is marked as unset from the point of view of the transition.
     * Resetting this property will also change the value of the
     * #toOpacitySet property to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetToOpacity();

   /*!
    * @brief Indicates whether the @c #toOpacity property of the transition is set.
    *
    * @return @c true the @c toOpacity property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isToOpacitySet() const;
   /*!
    * @brief Indicates whether the @c #fromOpacity property of the transition is set.
    *
    * @return @c true the @c fromOpacity property is set, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
    bool isFromOpacitySet() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c #fromOpacity of the transition changes.
     *
     * @param fromOpacity The new @c fromOpacity value for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void fromOpacityChanged(float fromOpacity);
    /*!
     * @brief Emitted when the @c #toOpacity of the transition changes.
     *
     * @param toOpacity The new @c toOpacity value for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void toOpacityChanged(float toOpacity);

private:    

    Q_DECLARE_PRIVATE(FadeTransition)
    Q_DISABLE_COPY(FadeTransition)
    
    // BUILDER ---------------------------------
public: 
    /*! @cond PRIVATE */
    typedef FadeTransition ThisClass;  // The class in which scope we're currently inside
    typedef AbstractTransition BaseClass; // References the class which ThisClass derives from
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a FadeTransition instance.
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
         * @brief Sets the @c fromOpacity(float) property of this transition.
         *
         * Setting a value of the property will also change the value of @c #fromOpacitySet property to @c true
         *
         * @param value the new value of #fromOpacity property
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& from(float value) {
            this->instance().setFromOpacity(value);
            return  this->builder();
        }
       /*!
        * @brief Sets the @c toOpacity(float) property of this transition.
        *
        * Setting a value of the property will also change the value of @c #toOpacitySet propety to @c true
        *
        * @param value The new value of the @c toOpacity property.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& to(float value) {
            this->instance().setToOpacity(value);
            return  this->builder();
        }
    };
    /*!
     * @brief A concrete builder class for constructing a FadeTransition.
     *
     * See FadeTransition::create() for getting a concrete 
     * Builder for constructing a FadeTransition.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, FadeTransition> {
    public:
        explicit Builder() : TBuilder<Builder, FadeTransition>(new FadeTransition()) {}
    };

    /*!
     * @brief Creates and returns a builder with an optional explicit target.
     *
     * @snippet tad/examples/animation/fadetransition/src/FadeTransitionExamples.cpp fadetransition_button
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


QML_DECLARE_TYPE(bb::cascades::FadeTransition)


#endif // cascades_fadetransition_h
