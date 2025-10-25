/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_sequentialanimation_h
#define cascades_sequentialanimation_h

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
 * @brief A group animation that plays its children animations sequentially.
 * 
 * Children animations can be added to the animation using the builder model.
 *
 * When the animations' @c AbstractAnimation::play() method is called the 
 * children animations will be played sequentially one after the other in the
 * order they were added.
 * 
 * Setting an explicit target via the @c AbstractAnimation::target property
 * will set implicit targets for its children animations automatically.
 * This allows you to specify a target only for the root of the animation
 * tree.
 *
 * Children animations of a @c %SequentialAnimation will not have
 * their states updated while an animation is playing.
 * @c AbstractAnimation functions such as @c isPlaying(), @c isStopped(), @c isEnded()
 * can not be used on children animations since their return values will
 * not accurately represent the current state of the animation.
 * Only the root animation in the animation tree will contain accurate states
 * and will have corresponding lifecycle signals emitted.
 *
 * In the following example, a sequential animation is used to play a fade transition 
 * after a translate transition, on a @c %Button node.
 * First, the button is translated along its x-axis from @c 0 to @c 100; then 
 * it is faded out.
 * Since the target node (pButton) is specified as the root of the animation tree, the
 * @c %SequentialAnimation and its children animations will target the same node (it becomes
 * the children's implicit target).
 *
 * @snippet tad/examples/animation/sequentialanimation/src/SequentialAnimExamples.cpp sequentialanimation1
 *
 * Here's an example of how you can create a sequential animation in QML.
 *
 * @snippet tad/examples/animation/sequentialanimation/assets/main.qml sequentialanimation_qml
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT SequentialAnimation : public GroupAnimation {
     Q_OBJECT
 
public: 
    /*!
     * @brief Constructs a @c %SequentialAnimation with no children.
     *
     * @since BlackBerry 10.0.0
     */
     SequentialAnimation();

    /*!
     * @brief A destructor for this class.
     *
     * @since BlackBerry 10.0.0
     */
     virtual ~SequentialAnimation();

    /*! \cond PRIVATE */
private:
    Q_DECLARE_PRIVATE(GroupAnimation)
    Q_DISABLE_COPY(SequentialAnimation)
    /*! \endcond */

public:

    /*!
     * @brief A concrete builder for constructing a SequentialAnimation.
     *
     * Call @c SequentialAnimation::create() to retrieve a
     * builder for contructing a @c %SequentialAnimation.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public GroupAnimation::TBuilder<Builder, SequentialAnimation> {
    public:
        Builder() : TBuilder<Builder, SequentialAnimation>(new SequentialAnimation()) {
        }
    };

    /*!
     * @brief Creates and returns a builder for creating the group animation.
     *
     * Using the builder to create an animation:
     *
     * @snippet tad/examples/animation/sequentialanimation/src/SequentialAnimExamples.cpp sequentialanimation1
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

QML_DECLARE_TYPE(bb::cascades::SequentialAnimation)


#endif // cascades_sequentialanimation_h
