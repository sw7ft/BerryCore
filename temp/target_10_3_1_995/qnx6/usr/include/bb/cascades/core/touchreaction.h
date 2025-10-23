/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchreaction_h
#define cascades_touchreaction_h

#include <QObject>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/touchtype.h>
#include <bb/cascades/core/touchresponse.h>
#include <bb/cascades/core/propagationphase.h>

#include <bb/cascades/core/eventreaction.h>

namespace bb {
    namespace cascades {

class TouchReactionPrivate;

/*!
 * @brief Touch reactions are used to build up touch behaviors.
 *
 * Touch reactions consist of three properties:
 * a touch event type, the propagation phase, and a touch response.
 *
 * The touch response is triggered when a touch event of the desired type is received within
 * the specified propagation phase.
 *
 * @code
 * TouchReaction* pStartTrackingAtTouchDown =
 *     TouchReaction::create(TouchType::Down, 
 *                           PropagationPhase::AtTarget,
 *                           TouchResponse::StartTracking);
 * @endcode
 *
 * Refer to the documentation of @c TouchBehavior to see how this class is used
 * in conjunction with touch behaviors.
 *
 * @see @c TouchBehavior, @c TouchType, @c TouchResponse
 *
 * @xmlonly
 * <qml>
 * <class abstract="no"/>
 * </qml>
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TouchReaction : public EventReaction {
    Q_OBJECT

    /*!
     * @brief Property that specifies which type of touch event to respond to.
     *
     * @see TouchType
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::TouchType::Type eventType READ eventType WRITE setEventType FINAL)

    /*!
     * @brief Property that specifies which propagation phase the touch event to respond to should be in.
     *
     * @see TouchType
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::PropagationPhase::Type phase READ phase WRITE setPhase FINAL)

    /*!
     * @brief Property that specifies a response to the touch event.
     *
     * @see bb::cascades::TouchResponse
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::TouchResponse::Type response READ response WRITE setResponse FINAL)

public:

    /*!
     * @brief Destroys the TouchReaction object
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~TouchReaction();


protected:
    /*! @cond PRIVATE */
    explicit TouchReaction();
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(TouchReaction)
    Q_DISABLE_COPY(TouchReaction)

    TouchType::Type eventType() const;
    void setEventType(bb::cascades::TouchType::Type eventType);

    PropagationPhase::Type phase() const;
    void setPhase(bb::cascades::PropagationPhase::Type phase);

    TouchResponse::Type response() const;
    void setResponse(bb::cascades::TouchResponse::Type response);
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef EventReaction BaseClass;
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a touch reaction.
     *
     * See TouchReaction::create() for getting a concrete Builder to contruct a touch reaction.
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
         * @brief Specifies which type of touch event to respond to.
         *
         * @param touchType Type of touch event to respond to.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& event(TouchType::Type touchType)
        {
            this->instance().setEventType(touchType);
            return this->builder();
        }

        /*!
         * @brief Specifies which propagation phase the touch event to respond to should be in.
         *
         * @param phase Propagation phase.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& phase(PropagationPhase::Type phase)
        {
            this->instance().setPhase(phase);
            return this->builder();
        }

        /*!
         * @brief Specifies a response to the touch event.
         *
         * @param touchResponse Touch event response.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& response(TouchResponse::Type touchResponse)
        {
            this->instance().setResponse(touchResponse);
            return this->builder();
        }
    };

    /*!
     * @brief A concrete builder class used to construct a touch reaction.
     *
     * See TouchReaction::create() for more information about using the Builder.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, TouchReaction>
    {
    public:
        explicit Builder() : TBuilder<Builder, TouchReaction>(new TouchReaction())
        {
        }
    };

    /*!
     * @brief Constructs a Builder used to create a touch reaction.
     *
     * @param touchType Type of touch event to respond to.
     * @param phase Propagation phase the touch event to respond to should be in.
     * @param response Response to the touch event.
     * @return A Builder to construct a touch reaction.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create(TouchType::Type touchType, PropagationPhase::Type phase, TouchResponse::Type response)
    {
        return Builder().event(touchType).phase(phase).response(response);
    }
};

}
}

QML_DECLARE_TYPE(bb::cascades::TouchReaction)

#endif //cascades_touchreaction_h
