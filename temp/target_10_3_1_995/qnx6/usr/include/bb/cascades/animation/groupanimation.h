/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_groupanimation_h
#define cascades_groupanimation_h

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeListProperty> 

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/animation/abstractanimation.h>

namespace bb {
    namespace cascades {

class VisualNode;
class GroupAnimationPrivate;

/*!
 * 
 * @brief Abstract class containing properties exposed to group animations.
 *
 * @c %GroupAnimations exposes a property called @c #animations, which allows for
 * a list of animations and transitions to be attached.
 *
 * There are two concrete subclasses of @c %GroupAnimation:
 * - @c ParallelAnimation - a group animation which plays its children animations in parallel
 * - @c SequentialAnimation - a group animation which plays its children in sequence, one after another
 *
 * Group animations own the child animations and transitions that are added to them.
 *
 * Children animations of a group animation will not have their states updated while an animation is playing.
 * AbstractAnimation functions such as @c %isPlaying(), @c %isStopped(), @c %isEnded()
 * can not be used on children animations since their return values will
 * not accurately represent the current state of the animation.
 *
 * Only the root animation in the animation tree will contain accurate states
 * and will have corresponding lifecycle signals emitted.
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT GroupAnimation : public AbstractAnimation {
   Q_OBJECT

   /*!
    * @brief A QDeclarativeListProperty containing a list of animations owned by this GroupAnimation.
    * 
    * @xmlonly
    * <qml>
    * <property name="animations" listType="bb::cascades::AbstractAnimation" defaultProperty="yes"/>
    * </qml>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
   Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractAnimation> animations READ animations) 
   Q_CLASSINFO("DefaultProperty", "animations")

public:

    /*!
     * @brief Destructor for this object
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~GroupAnimation();

protected:
    /*! @cond PRIVATE */
    GroupAnimation(GroupAnimationPrivate &_d_ptr);
    /*! @endcond */

private:    
    /*! @cond PRIVATE */
    QDeclarativeListProperty<bb::cascades::AbstractAnimation> animations();
    void add(AbstractAnimation *animation);
    /*! @endcond */

    Q_DECLARE_PRIVATE(GroupAnimation)
    Q_DISABLE_COPY(GroupAnimation)
    
    // BUILDER ---------------------------------
public:
    /*! @cond PRIVATE */
    typedef GroupAnimation ThisClass;  // The class in which scope we're currently inside
    typedef AbstractAnimation BaseClass; // References the class which ThisClass derives from
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a slider.
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
         * @brief Adds a non-null animation to this %GroupAnimation.
         *
         * The ownership of the animation is passed to the %GroupAnimation.
         * If @c null is passed it is ignored.
         *
         * @param animation The animation to be added as a child of the group animation.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& add(AbstractAnimation *animation) {
            this->instance().add(animation);
            return this->builder();
        }
    };
};



}
}

QML_DECLARE_TYPE(bb::cascades::GroupAnimation)

#endif // cascades_groupanimation_h
