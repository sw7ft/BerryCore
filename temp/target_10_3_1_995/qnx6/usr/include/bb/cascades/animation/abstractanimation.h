/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstractanimation_h
#define cascades_abstractanimation_h

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeListProperty> 

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/visualnode.h>
#include <bb/cascades/animation/animationstate.h>
#include <bb/cascades/animation/animationrepeatcount.h>

namespace bb {
    namespace cascades {
    
class AbstractAnimationPrivate;
    
/*!
 * 
 * @brief Abstract class containing properties inherited by all animations.
 *
 * Animations represent a change, over time, of a property or set of properties according to specified rules.
 * Each animation that inherits this class has a @c #target property (the node that the animation changes), 
 * a @c #delay property (the time between initiation and when the animation actually starts) 
 * and a @c #repeatCount property (the number of times the animation is repeated).
 *
 * Once an animation is playing, changing its properties will not take effect
 * until the next time animation is re-started (either stopped and started, or ended
 * and started).
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT AbstractAnimation : public UIObject {
   Q_OBJECT

   /*!
    * @brief The target for the animation.
    * 
    * Even if a target is not explicitly set, the animation
    * can have an implicit target in the following instances:
    *
    * - If the animation is a child of a @c VisualNode object, the parent is assumed to be the 
    *   animation's implicit target
    * - If the animation is a child of a @c GroupAnimation object, the @c GroupAnimation
    *   object's target is assumed to be the animation's implicit target 
    *
    * If an animation has children, setting the explicit target for the animation causes the children's
    * implicit targets to change accordingly.
    *
    * When the target node is explicitly set on the animation, the node it is attached to 
    * does not take ownership, meaning that if the target node is destroyed, the animation 
    * is not removed with it. To help manage the animation lifecycle, the ownership of an 
    * animation can assigned to a @c VisualNode by calling @c VisualNode::addAnimation(). 
    * This can help ensure that the animation's memory is cleaned up properly.
    *
    * Once an animation is playing, changing its properties will not take effect
    * until the next time animation is started.
    *
    * The default value of this property is @c 0.
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(bb::cascades::VisualNode* target READ target WRITE setTarget RESET resetTarget NOTIFY targetChanged FINAL)
   
   /*!
    * @brief The delay (in milliseconds) before an animation executes when the @c play() 
    * function is invoked.
    *
    * Once an animation is playing, changing its properties will not take effect
    * until the next time animation is started.
    *
    * The default delay is @c 0.
    *
    * @since BlackBerry 10.0.0
    */ 
   Q_PROPERTY(int delay READ delay WRITE setDelay RESET resetDelay NOTIFY delayChanged FINAL)

   /*!
    * @brief The number of times that an animation runs.
    *
    * Once an animation is playing, changing its properties will not take effect
    * until the next time animation is started.
    *
    * To have an animation run forever, you can specify @c AnimationRepeatCount::Forever. Here's
    * how you can set an animation to run forever in QML:
    *
    * @snippet tad/examples/animation/abstractanimation/assets/main.qml abstractanimation_repeatforever
    *
    * The default value is @c 1. This must not be a negative value.
    *
    * @since BlackBerry 10.0.0
    */ 
   Q_PROPERTY(int repeatCount READ repeatCount WRITE setRepeatCount RESET resetRepeatCount NOTIFY repeatCountChanged FINAL)

   /*!
    * @brief The current state of the animation.
    *
    * The default value is @c bb::cascades:AnimationState::Stopped.
    *
    * @since BlackBerry 10.0.0
    */ 
   Q_PROPERTY(bb::cascades::AnimationState::Type state READ state NOTIFY stateChanged FINAL)

public:

    /*!
     * @brief Destructs an @c %AbstractAnimation object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AbstractAnimation();

    /*!
     * @brief Returns the explicit target for the animation.
     *
     * Once the operation is completed, ownership of the animation does not change.
     * This function only works for explicit targets; implicit targets are not returned.
     *
     * @return The explicit target for the animation, or @c 0 if a target is not set.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::VisualNode *target() const;

    /*!
     * @brief Sets the explicit target for the animation.
     *
     * Once the operation is completed, ownership of the passed object does not change.
     * The animation does not become a child of the target @c VisualNode.
     *
     * Once an animation is playing, changing its properties will not take effect
     * until the next time animation is started.
     *
     * If an animation has children, setting the explicit target for the animation causes 
     * the children's implicit targets to change accordingly (unless they already have 
     * an explicit target).
     *
     * @param target The explicit target for the animation, or @c 0 to remove the current target.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setTarget(bb::cascades::VisualNode * target);

    /*!
     * @brief Resets the @c #target to its default value of @c 0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetTarget();

    /*!
     * @brief Returns the current state.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::AnimationState::Type state() const;

    /*!
     * @brief Indicates whether the animation has been started but is not yet playing.
     *
     * If the animation is a child of a @c GroupAnimation object, this 
     * function cannot be used to determine the state of this animation
     * node. Only the root @c %GroupAnimation in an animation tree will indicate 
     * its state correctly.
     *
     * @return @c true if the animation is started, but not yet playing,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isStarted() const;

    /*!
     * @brief Indicates whether the animation is currently playing.
     *    
     * Note that if this node is a child of @c GroupAnimation this 
     * method cannot be used to determine the state of this animation
     * node. Only the root @c %GroupAnimation in an animation tree will indicate 
     * its state correctly.
     *
     * @return @c true if the animation is currently playing, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isPlaying() const;

    /*!
     * @brief Indicates whether the animation was interrupted by the @c stop() function.
     *     
     * It should be noted that if this node is a child of @c GroupAnimation this 
     * method cannot be used to determine the state of this animation
     * node. Only the root @c %GroupAnimation in an animation tree will indicate 
     * its state correctly.
     *
     * @return @c true if the animation was interrupted, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isStopped() const;

    /*!
     * @brief Indicates whether the animation has ended.
     *
     * An animation has ended if it has run its course without being stopped.
     * It should be noted that if this node is a child of @c GroupAnimation this 
     * method cannot be used to determine the state of this animation
     * node. Only the root @c %GroupAnimation in an animation tree will indicate 
     * its state correctly.
     *
     * @return @c true if the animation has ended, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isEnded() const;

    /*!
     * @brief Returns the delay (in milliseconds) before an animation executes after the 
     * @c play() function is invoked.
     *
     * @return A non-negative number indicating the delay of this animation.
     *
     * @since BlackBerry 10.0.0
     */
    int delay() const;

    /*!
     * @brief Sets the delay (in milliseconds) before an animation executes after the 
     * @c play() function is invoked.
     *
     * The passed argument must be non-negative or it is ignored.
     *
     * @param delay A non-negative number representing animation delay in milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    void setDelay(int delay);

    /*!
     * @brief Resets the @c #delay to its default value of @c 0 milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetDelay();

    /*!
     * @brief Returns the value of the @c #repeatCount property.
     *
     * The @c repeatCount property is the number of times the 
     * animation will be repeated after it started.
     *
     * @return A positive number indicating the number of times this animation will
     * be repeated. If @c #repeatCount is equal to @c bb::cascades::AnimationRepeatCount::Forever,
     * the animation will repeat indefinitely.
     *
     * @since BlackBerry 10.0.0
     */
    int repeatCount() const;

    /*!
     * @brief Sets the value of the @c #repeatCount property.
     *
     * The @c repeatCount property is the number of times that the 
     * animation will be repeated after it started. The passed argument must be 
     * positive or it is ignored.
     *
     * @c #bb::cascades::AnimationRepeatCount::Forever can be used to specify an animation that repeats forever.
     *
     * @param repeatCount A positive number representing number of times animation will be repeated.
     *
     * @since BlackBerry 10.0.0
     */
    void setRepeatCount(int repeatCount);

    /*!
     * @brief Resets the @c #repeatCount property to its default value of @c 1.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetRepeatCount();

    /*!
     * @brief A constant to be used for specifying an animation that repeats forever.
     * 
     * @deprecated Use @c bb::cascades::AnimationRepeatCount::Forever instead.
     * 
     * @see #setRepeatCount()
     *
     * @since BlackBerry 10.0.0
     */
    static const int RepeatForever;

    /*!
     * @brief Plays the animation.
     *
     * Only the root animation in a tree of animations can be played explicitly. If 
     * this function is called on a child animation, the function is ignored.
     *
     * If more than one animation is affecting the same property, calling @c play() on more
     * than one will stop the running one. 
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void play();

    /*!
     * @brief Stops this animation.
     *
     * If the animation is started again it will restart from the beginning.
     *
     * Only the root animation in a tree of animations can be stopped explicitly. If 
     * this function is called on a child animation, the function is ignored.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void stop();

Q_SIGNALS:
    /*!
     * @brief Emitted when the animation is started.
     *
     * Note that this may happen sometimes after the @c play() method is invoked.
     *
     * This signal is not emitted for child animations.
     *
     * @since BlackBerry 10.0.0
     */
    void started();

    /*!
     * @brief Emitted when the animation is stopped.
     *
     * Note that this may happen sometimes after the @c stop() method is invoked.
     * It will also be emitted if an animation is stopped because a different
     * animation, implicit or explicit, is started on the same value.
     *
     * The animation can be deleted from this signal only using
     * @c QObject::deleteLater() signal.
     *
     * This signal is not emitted for child animations.
     *
     * @since BlackBerry 10.0.0
     */
    void stopped();

    /*!
     * @brief Emitted when the animation has ended.
     *
     * The animation can be deleted from this signal only using
     * @c QObject::deleteLater() signal.
     *
     * This signal is not emitted for child animations.
     *
     * @since BlackBerry 10.0.0
     */
    void ended();

    /*!
     * @brief Emitted when the @c #target property changed.
     *
     * @param target The new target or @c 0 if it was unset.
     *
     * @since BlackBerry 10.0.0
     */
    void targetChanged(bb::cascades::VisualNode *target);

    /*!
     * @brief Emitted when the @c #delay of the animation changes.
     *
     * @param delay The new delay for the animation.
     *
     * @since BlackBerry 10.0.0
     */
    void delayChanged(int delay);

    /*!
     * @brief Emitted when the @c #repeatCount of the animation changes.
     *
     * @param repeatCount The new repeat count for the animation.
     *
     * @since BlackBerry 10.0.0
     */
    void repeatCountChanged(int repeatCount);
    
    /*!
     * @brief Emitted when the @c #state of the animation changes.
     *
     * @param newState The new state of the animation.
     *
     * @since BlackBerry 10.0.0
     */
    void stateChanged(bb::cascades::AnimationState::Type newState);

protected:
    /*! @cond PRIVATE */
    AbstractAnimation(AbstractAnimationPrivate &_d_ptr);
    /*! @endcond */

private:
    /*! @cond PRIVATE */

    void setAutoDeleted(bool autoDeleted);

    Q_DECLARE_PRIVATE(AbstractAnimation)
    Q_DISABLE_COPY(AbstractAnimation)

    /*! @endcond */

    // BUILDER ---------------------------------
public: 
    /*! @cond PRIVATE */
    typedef AbstractAnimation ThisClass;
    typedef UIObject BaseClass;
    /*! @endcond */

    /*!
     * @brief A base builder template for constructing AbstractAnimation descendants
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
         * @copydoc AbstractAnimation::setTarget()
         */
        BuilderType& target(VisualNode *target) {
            this->instance().setTarget(target);
            return this->builder();
        }

        /*!
         * @copydoc AbstractAnimation::setDelay()
         */
        BuilderType& delay(int delay) {
            this->instance().setDelay(delay);
            return this->builder();
        }

        /*!
         * @copydoc AbstractAnimation::setRepeatCount()
         */
        BuilderType& repeatCount(int repeatCount) {
            this->instance().setRepeatCount(repeatCount);
            return this->builder();
        }

        /*!
         * @brief Specifies whether this animation should be automatically deleted
         * when it ends.
         *
         * This setting is ignored for non-child animations. If the animation is interrupted
         * (stopped) it will not be auto-deleted.
         *
         * If an auto-deleted animation is stopped the application is expected to
         * delete the animation in response to the @c stopped() signal
         * using @c QObject::deleteLater() signal.
         *
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& autoDeleted(bool autoDeleted = true) {
            this->instance().setAutoDeleted(autoDeleted);
            return this->builder();
        }
    };
};



}
}


QML_DECLARE_TYPE(bb::cascades::AbstractAnimation)

#endif // cascades_abstractanimation_h
