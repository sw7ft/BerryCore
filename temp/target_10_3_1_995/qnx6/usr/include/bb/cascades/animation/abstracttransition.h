/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstracttransition_h
#define cascades_abstracttransition_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/animation/abstractanimation.h>

namespace bb {
    namespace cascades {
    
class AbstractTransitionPrivate;
class EasingCurve;

/*!
 * 
 * @brief Abstract class containing properties inherited by all transitions.
 *
 * Transitions are used to change properties from one state to another. Each transition that 
 * inherits this class is used to target a different
 * VisualNode property.
 *
 * - FadeTransition: Changes the opacity of the target node.
 * - RotateTransition: Rotates the target node.
 * - ScaleTransition: Scales the size of the target node.
 * - TranslateTransition: Changes the position of the target node.
 *
 * Each transition has a #duration property and an #easingCurve property that can be used to customize the effect
 * of the transition. The duration of the of the transition is the literal amount of time that the transition takes
 * from start to finish if ran uninterrupted. The EasingCurve specifies the rate of change of the transition over
 * the duration of the transition.
 * The StockCurve class contains predefined easing curves that are available for use.
 *
 * Once an animation is playing changing its properties will not take effect
 * until the next time animation is started.
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT AbstractTransition : public AbstractAnimation {
   Q_OBJECT

   /*!
    * @brief The duration of the transition (in milliseconds).
    *
    * The value of this property must be non-negative. A duration of @c 0 milliseconds
    * means the transition is instantaneous. 
    *
    * If the duration is @c 0, the value
    * of AbstractAnimation::repeatCount is ignored (it is treated if it was @c 1).
    * 
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * The default value of this property is @c 300 milliseconds.
    *
    * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(int duration READ duration WRITE setDuration RESET resetDuration NOTIFY durationChanged FINAL)

    /*!
    * @brief Specifies the easing curve for this transition.
    *
    * If the animation was playing when this property is set the
    * change will not take effect until the next time the animation is started.
    *
    * The default value of this attribute is @c StockCurve::CubicIn
    *
    * To assign a value to the @c easingCurve property from JavaScript, use the assignment operator instead of calling the setter method directly
    *
    * @see EasingCurve
    *
    * @xmlonly
    * <qml>
    * <variant type="bb::cascades::EasingCurve"/>
    * </qml>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
    */
    Q_PROPERTY(QVariant easingCurve READ easingCurve WRITE setEasingCurveQML RESET resetEasingCurve NOTIFY easingCurveChanged FINAL)

public:
    /*!
     * @brief Returns the #duration of this transition.
     *
     * @return A positive number indicating the duration of the transition, in milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    int duration() const;

   /*!
    * @brief Sets the duration for the transition, in millseconds.
    *
    * Passed argument must be non-negative or it is ignored.
    * A duration of @c 0 indicates an instantaneous transition.
    *
    * @param duration A non-negative value in milliseconds.
    *
    * @since BlackBerry 10.0.0
    */
    Q_SLOT void setDuration(int duration);

    /*!
     * @brief Resets the #duration property to its default value of @c 300 milliseconds
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetDuration();

    /*!
     * @brief Sets the value of the #easingCurve for the transition.
     *
     * The passed value must be an @c EasingCurve or one of its subclasses, or
     * the passed value will be ignored and a warning will be printed on the console.
     *
     * @param curve A derivative of @c EasingCurve.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setEasingCurve(const bb::cascades::EasingCurve &curve);

    /*!
     * @brief Returns a @c QVariant containing the #easingCurve for the transition.
     *
     * @return A QVariant containing current easing curve for this transition.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant easingCurve() const;

    /*!
     * @brief Resets the @c #easingCurve to its default value of @c StockCurve::CubicIn
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetEasingCurve();

    /*!
     * @brief Destructor for this object
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AbstractTransition();
    
Q_SIGNALS:
    /*!
     * @brief Emitted when the @c #duration of the transition changes.
     *
     * @param duration The new @c duration for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void durationChanged(int duration);
    /*!
     * @brief Emitted when the @c #easingCurve of the transition changes.
     *
     * @param easingCurve The new @c easingCurve for the transition.
     *
     * @since BlackBerry 10.0.0
     */
    void easingCurveChanged(const QVariant &easingCurve);

protected:
    /*! @cond PRIVATE */
    AbstractTransition(AbstractTransitionPrivate &_d_ptr);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_SLOT void setEasingCurveQML(QVariant easingCurve);
    /*! @endcond */
    
    Q_DECLARE_PRIVATE(AbstractTransition)
    Q_DISABLE_COPY(AbstractTransition)

    
    // BUILDER ---------------------------------
public: 
    /*! @cond PRIVATE */
    typedef AbstractTransition ThisClass;
    typedef AbstractAnimation BaseClass;
    /*! @endcond */
    
    /*!
     * @brief A builder template for constructing an AbstractTransition object.
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>                                //
    class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {              //
    protected:                                                                         //
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {  //
        }                                                                                //
    public:                                                                            //

        /*!
         * @copydoc AbstractTransition::setDuration()
         */
        BuilderType& duration(int duration) {
            this->instance().setDuration(duration);
            return  this->builder();
        }
        
        /*!
         * @copydoc AbstractTransition::setEasingCurve
         */
        BuilderType& easingCurve(const bb::cascades::EasingCurve &curve) {
            this->instance().setEasingCurve(curve);
            return this->builder();
        }
    };
    
};
    


}
}

QML_DECLARE_TYPE(bb::cascades::AbstractTransition)


#endif // cascades_abstracttransition_h
