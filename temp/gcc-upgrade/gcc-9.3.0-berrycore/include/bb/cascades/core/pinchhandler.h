/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_pinchhandler_h
#define cascades_pinchhandler_h

#include <bb/cascades/core/gesturehandler.h>

namespace bb {
    namespace cascades {

class PinchHandlerPrivate;
class PinchEvent;

/*!
 * @brief A pinch handler can be used to react to pinch gesture.
 *
 * @details A pinch gesture goes through the following stages:
 * - pinch gesture is started when user places second finger on the screen;
 *   at that moment pinchStarted() signal is emitted from the handler.
 * - pinch gesture is updated when the user moves one or both fingers; at that 
 *   moment a pinchUpdated() signal is emitted from the handler. Note that this stage is 
 *   optional and does not happen if the user
 *   lifts one or both fingers off the screen without moving them or if the gesture
 *   is cancelled.
 * - pinch gesture ends when the user lifts one or both fingers off the screen, at
 *   which point a pinchEnded() signal is emitted. This is one of two
 *   possible end stages of the pinch gesture and it may not happen if
 *   the gesture is cancelled.
 * - pinch gesture is cancelled, a pinchCancelled() signal is emitted. This is the
 *   second possible end stage for the pinch gesture. A pinch gesture may be 
 *   cancelled under certain conditions such as when interaction is cancelled 
 *   due to a system event.
 *
 * Example of how to connect a pinch handler to a visual node:
 * @code
 * Container* pContainer = Container::create();
 *
 * PinchHandler *pPinchHandler = PinchHandler::create()
 *     .onPinch(pMyObject,
 *              SLOT(onPinchStarted(bb::cascades::PinchEvent*)),
 *              SLOT(onPinchUpdated(bb::cascades::PinchEvent*)),
 *              SLOT(onPinchEnded(bb::cascades::PinchEvent*)),
 *              SLOT(onPinchCancelled()));
 *
 * pContainer->addGestureHandler(pPinchHandler);
 * @endcode
 *
 * Example of how to connect a pinch handler to a visual node in QML:
 * @code
 * Container {
 *     gestureHandlers: [
 *         PinchHandler {
 *             onPinchStarted: {
 *                 console.log("midPointX: "+event.midPointX+" midPointY: "+event.midPointY +" pinchRatio: "
 *                      +event.pinchRatio +" rotation:" +event.rotation + " distance:"+event.distance);
 *             }
 *             onPinchUpdated: {
 *                 console.log("midPointX: "+event.midPointX+" midPointY: "+event.midPointY +" pinchRatio: "
 *                      +event.pinchRatio +" rotation:" +event.rotation + " distance:"+event.distance);
 *             }
 *             onPinchEnded: {
 *                 console.log("midPointX: "+event.midPointX+" midPointY: "+event.midPointY +" pinchRatio: "
 *                      +event.pinchRatio +" rotation:" +event.rotation + " distance:"+event.distance);
 *             }
 *             onPinchCancelled: {
 *                 console.log("midPointX: "+event.midPointX+" midPointY: "+event.midPointY +" pinchRatio: "
 *                     +event.pinchRatio +" rotation:" +event.rotation + " distance:"+event.distance);
 *             }
 *         }
 *     ]
 * }
 * @endcode
 *
 * @see VisualNode::addGestureHandler()
 *
 * @xmlonly
 * <qml>
 *    <class abstract="no"/>
 * </qml>
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT PinchHandler : public GestureHandler {
    Q_OBJECT

public:
    /*!
     * @brief Creates a PinchHandler
     *
     * @param parent The parent @c UIObject, or @c 0. This parameter is optional
     * and defaults to @c 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PinchHandler(bb::cascades::UIObject* parent = 0);

    /*!
     * @brief Destructs the handler.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PinchHandler();

Q_SIGNALS:

    /*!
     * @brief Emitted at the start of the pinch gesture, specifically when
     * the second finger was placed on the screen.
     *
     * @param event the pinch event with current pinch parameters.
     *
     * @since BlackBerry 10.0.0
     */
    void pinchStarted(bb::cascades::PinchEvent *event);

    /*!
     * @brief Emitted after the gesture started, when one or both fingers moved.
     *
     * @details This signal will not be emitted if the user just places two fingers
     * and lifts them without moving.
     *
     * @param event The pinch event with current pinch parameters.
     *
     * @since BlackBerry 10.0.0
     */
    void pinchUpdated(bb::cascades::PinchEvent *event);

    /*!
     * Emitted when the user lifts one or both fingers off the screen.
     *
     * This signal is one of the two possible outcomes of a pinch gesture,
     * the other being the cancelation of the gesture (pinchCancelled() is emitted).
     *
     * @param event the pinch event with current pinch parameters
     *
     * @since BlackBerry 10.0.0
     */
    void pinchEnded(bb::cascades::PinchEvent *event);

    /*!
     * @brief Emitted when the gesture is cancelled.
     *
     * A gesture can be cancelled for example if another window or a dialog is shown
     * on top of the window the user is interacting with, or if the phone gets locked, etc.
     * If the pinch gesture is cancelled, the effect of the gesture should be disregarded
     * (reset to the original or some other sane state).
     *
     * @details This signal is one of the two possible outcomes of a pinch gesture,
     * the other being the gesture ended (@c pinchEnded() is emitted).
     *
     * @since BlackBerry 10.0.0
     */
    void pinchCancelled();

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(PinchHandler)
    Q_DISABLE_COPY(PinchHandler)
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef GestureHandler BaseClass;
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a handler.
     * To create the builder, call @c PinchHandler::create().
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>
    class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
    {
    protected:
        /*! @cond PRIVATE */
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {
        }
        /*! @endcond */

    public:
        /*!
         * @brief A convenience method for connecting the slot of the receiver object, passed in as a paramter, to
         * the handler's pinch signals, with the default connection type @c Qt::AutoConnection.
         *
         * @details A @c 0 can be passed as slot parameter name for any of the slots
         * to indicate that a particular signal should not be connected to any slot.
         *
         * If @c QObject::connect() fails an assert is raised.
         * If the receiver parameter is @c 0 this method has no effect.
         *
         * Example connecting pinch slots in pMyObject to the handler's
         * pinch signals:
         * @code
         * PinchHandler *pPinchHandler = PinchHandler::create()
         *     .onPinch(pMyObject,
         *              SLOT(onPinchStarted(bb::cascades::PinchEvent*)),
         *              SLOT(onPinchUpdated(bb::cascades::PinchEvent*)),
         *              SLOT(onPinchEnded(bb::cascades::PinchEvent*)),
         *              0); // indicates that receiver is not interested in pinchCancelled() signal.
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param onStarted  a slot name of in the receiver object for pinchStarted() signal, can be @c 0.
         * @param onUpdated a slot name of in the receiver object for pinchUpdated() signal, can be @c 0.
         * @param onEnded    a slot name of in the receiver object for pinchEnded() signal, can be @c 0.
         * @param onCancelled a slot name of in the receiver object for pinchCancelled() signal, can be @c 0.
         *
         * @see @c pinchStarted(), @c pinchUpdated(), @c pinchEnded(), @c pinchCancelled(), @c BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onPinch(const QObject* receiver,
                             const char *onStarted,
                             const char *onUpdated,
                             const char *onEnded,
                             const char *onCancelled)
        {
            if (onStarted) {
                this->connect(SIGNAL(pinchStarted(bb::cascades::PinchEvent*)), receiver, onStarted);
            }
            if (onUpdated) {
                this->connect(SIGNAL(pinchUpdated(bb::cascades::PinchEvent*)), receiver, onUpdated);
            }
            if (onEnded) {
                this->connect(SIGNAL(pinchEnded(bb::cascades::PinchEvent*)), receiver, onEnded);
            }
            if (onCancelled) {
                this->connect(SIGNAL(pinchCancelled()), receiver, onCancelled);
            }
            return this->builder();
        }
    };

    /*!
     * @brief A builder that constructs a PinchHandler.
     * To retrieve the builder, call @c PinchHandler::create().
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, PinchHandler> {
    public:
        explicit Builder() : TBuilder<Builder, PinchHandler>(new PinchHandler()) {}
    };

    /*!
     * @brief Creates and returns a builder for constructing a pinchHandler.
     *
     * Using the builder to create a @c %PinchHandler:
     * @code
     * PinchHandler *pPinchHandler = PinchHandler::create();
     * @endcode
     *
     * @return A @c Builder used for constructing a @c PinchHandler.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create() {
        return Builder();
    }

};

}
}

QML_DECLARE_TYPE(bb::cascades::PinchHandler)

#endif /* cascades_pinchhandler_h */
