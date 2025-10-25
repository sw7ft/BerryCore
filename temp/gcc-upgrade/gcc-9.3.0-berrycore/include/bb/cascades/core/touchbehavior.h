/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchbehavior_h
#define cascades_touchbehavior_h

#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/touchtype.h>
#include <bb/cascades/core/propagationphase.h>
#include <bb/cascades/core/touchresponse.h>
#include <bb/cascades/core/eventreaction.h>
#include <bb/cascades/core/touchreaction.h>

namespace bb {
    namespace cascades {

class TouchBehaviorPrivate;

/*!
 * @brief A series of touch-input reactions that can be added to a @c VisualNode.
 *
 * @c %TouchBehavior is built up of an arbitrary number of event reactions and
 * cannot be modified after construction.
 *
 * Here's an example of how to customize the touch behavior of a container.
 * Upon receiving a touch down event in the
 * target propagation phase, it tracks further touch events until a touch up occurs.
 *
 * @code
 * Container* pContainer = Container::create();
 *
 * pContainer->addTouchBehavior(
 *     TouchBehavior::create()
 *         .addTouchReaction(TouchType::Down,
 *                           PropagationPhase::AtTarget,
 *                           TouchResponse::StartTracking));
 * @endcode
 *
 * And here's how to do the same in QML.
 *
 * @code
 * Container {
 *     touchBehaviors: [
 *         TouchBehavior {
 *             TouchReaction {
 *                 eventType: TouchType.Down
 *                 phase: PropagationPhase.AtTarget
 *                 response: TouchResponse.StartTracking
 *             }
 *         }
 *     ]
 * }
 * @endcode
 *
 * When a control is tracking events, it receives them in the @c AtTarget phase. To listen for
 * touch events in this phase, connect a slot to the @c VisualNode::touch() signal.
 *
 * @see VisualNode::addTouchBehavior(), TouchReaction, VisualNode::touch()
 *
 * @xmlonly
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TouchBehavior : public UIObject {
    Q_OBJECT

    /*!
     * @brief A QDeclarativeListProperty object that contains a list of event reactions.
     *
     * A QDeclarativeListProperty object that contains a list of event reactions.
     *
     * @xmlonly
     * <qml>
     * <property name="eventReactions" listType="bb::cascades::EventReaction" defaultProperty="yes"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QDeclarativeListProperty<bb::cascades::EventReaction> eventReactions READ eventReactions FINAL)
    Q_CLASSINFO("DefaultProperty", "eventReactions")

public:

    /*!
     * @brief Creates a TouchBehavior
     *
     * @since BlackBerry 10.0.0
     */
    explicit TouchBehavior();

    /*!
     * @brief Destructs the handler.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~TouchBehavior();

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(TouchBehavior)
    Q_DISABLE_COPY(TouchBehavior)

    QDeclarativeListProperty<bb::cascades::EventReaction> eventReactions();

    void addEventReaction(EventReaction* eventReaction);
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef UIObject BaseClass;
    /*! @endcond */

    /*!
     * @brief  A builder template for constructing a touch behavior.
     *
     * See TouchBehavior::create() for getting a concrete Builder to contruct a touch behavior.
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>
    class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
    {
    protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {
        }

    public:
        /*!
         * @brief Adds an event reaction to the touch behavior.
         *
         * @param eventReaction The event reaction to add.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& addEventReaction(EventReaction* eventReaction)
        {
            this->instance().addEventReaction(eventReaction);
            return this->builder();
        }

        /*!
         * @brief Adds a touch reaction to the touch behavior.
         *
         * @param touchType Type of touch event to respond to.
         * @param phase Propagation phase the touch event to respond to should be in.
         * @param response Response to the touch event.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& addTouchReaction(TouchType::Type touchType, PropagationPhase::Type phase, TouchResponse::Type response)
        {
            this->instance().addEventReaction(TouchReaction::create(touchType, phase, response));
            return this->builder();
        }
    };

    /*!
     * @brief A concrete builder class used to construct a touch behavior.
     *
     * See TouchBehavior::create() for more information about using the Builder.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, TouchBehavior>
    {
    public:
        explicit Builder() : TBuilder<Builder, TouchBehavior>(new TouchBehavior())
        {
        }
    };

    /*!
     * @brief Constructs a Builder used to create a touch behavior.
     *
     * @return A Builder to construct a touch behavior.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create()
    {
        return Builder();
    }
};

}
}

QML_DECLARE_TYPE(bb::cascades::TouchBehavior)

#endif /* cascades_touchbehavior_h */
