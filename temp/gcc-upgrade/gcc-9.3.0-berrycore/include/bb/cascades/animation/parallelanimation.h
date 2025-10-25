/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_parallelanimation_h
#define cascades_parallelanimation_h

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeListProperty> 

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/animation/groupanimation.h>

namespace bb {
    namespace cascades {

class VisualNode;
class GroupAnimationPrivate;

/*!
 * 
 * @brief A group animation that plays its children animations in parallel.
 * 
 * Children animations can be added to the animation using the builder model.
 *
 * When the animations' @c AbstractAnimation::play() method is called the 
 * children animations will be played in parallel.
 * 
 * Setting an explicit target via the @c AbstractAnimation::target property
 * will set implicit targets for its children animations automatically.
 * This allows you to specify a target only for the root of the animation
 * tree.
 *
 * Children animations of a @c %ParallelAnimation will not have
 * their states updated while an animation is playing.
 * AbstractAnimation functions such as @c isPlaying(), @c isStopped(), @c isEnded()
 * can not be used on children animations since their return values will
 * not accurately represent the current state of the animation.
 * Only the root animation in the animation tree will contain accurate states
 * and will have corresponding lifecycle signals emitted.
 * 
 * This example shows how to use a parallel animation to run a fade transition
 * and a translate transition on a @c Button, simultaneously.
 * The button is translated along its x-axis from @c 0 to @c 100 and is faded out
 * at the same time.
 * Since the target node (pButton) is specified as the root of the animation tree, the
 * @c %SequentialAnimation and its children animations will target the same node (it becomes
 * the children's implicit target).
 *
 * @snippet tad/examples/animation/parallelanimation/src/ParallelAnimationExamples.cpp parallelanimation_button
 *
 * And here's how to create a %ParallelAnimation in QML:
 *
 * @snippet tad/examples/animation/parallelanimation/assets/main.qml parallelanimation_qml
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ParallelAnimation : public GroupAnimation {
    Q_OBJECT
 
public:
    /*!
     * @brief Constructs a @c %ParallelAnimation with no children.
     *
     * @since BlackBerry 10.0.0
     */
    ParallelAnimation();

    /*!
     * @brief A destructor for this class
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ParallelAnimation();

private:
    Q_DECLARE_PRIVATE(GroupAnimation)
    Q_DISABLE_COPY(ParallelAnimation)

public:

    /*!
     * @brief A concrete builder class for constructing a @c %ParallelAnimation.
     *
     * See ParallelAnimation::create() for getting a concrete
     * builder for contructing a %ParallelAnimation.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public GroupAnimation::TBuilder<Builder, ParallelAnimation> {
    public:
        Builder() : TBuilder<Builder, ParallelAnimation>(new ParallelAnimation()) {
        }
    };

    /*!
     * @brief Creates and returns a builder for creating the group animation.
     *
     * Using the builder to create an animation:
     *
     * @snippet tad/examples/animation/parallelanimation/src/ParallelAnimationExamples.cpp parallelanimation_button
     *
     * @param target An optional explicit target for the animation.
     * @return A builder for constructing the animation.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create(VisualNode *target = 0) {
        return Builder().target(target);
    }
};



}
}


QML_DECLARE_TYPE(bb::cascades::ParallelAnimation)

#endif // cascades_parallelanimation_h
