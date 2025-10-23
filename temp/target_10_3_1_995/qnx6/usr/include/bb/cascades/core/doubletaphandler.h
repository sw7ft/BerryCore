/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_doubletaphandler_h
#define cascades_doubletaphandler_h

#include <bb/cascades/core/gesturehandler.h>

namespace bb {
    namespace cascades {

class DoubleTapHandlerPrivate;
class DoubleTapEvent;

/*!
 * @brief A double tap handler can be used to react to double tap gesture.
 *
 * Example of how to connect a double tap handler to a visual node:
 *
 * @code
 * Container* pContainer = Container::create();
 *
 * DoubleTapHandler *pDoubleTapHandler = DoubleTapHandler::create()
 *     .onDoubleTapped(pMyObject, SLOT(onDoubleTappedHandler(bb::cascades::DoubleTapEvent*)));
 *
 * pContainer->addGestureHandler(pDoubleTapHandler);
 * @endcode
 *
 * Matching code in QML:
 *
 * @code
 * Container {
 *     gestureHandlers: [
 *         DoubleTapHandler {
 *             onDoubleTapped: {
 *                 console.log("DoubleTap at position " + event.x + ", " + event.y)
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
 *     <class abstract="no"/>
 * </qml>
 * <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT DoubleTapHandler : public GestureHandler {
    Q_OBJECT

public:

    /*!
     * @brief Constructs a DoubleTapHandler for listening to double taps
     *
     * @code
     * DoubleTapHandler *tapHandler = new DoubleTapHandler();
     * @endcode
     *
     * @param parent The parent UIObject or 0.
     *
     * @since BlackBerry 10.0.0
     */
    explicit DoubleTapHandler(UIObject* parent = 0);

    /*!
     * @brief Destructs the handler.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~DoubleTapHandler();

Q_SIGNALS:
    /*!
     * @brief Emitted when a double tap gesture was performed on the associated node.
     *
     * @since BlackBerry 10.0.0
     */
    void doubleTapped(bb::cascades::DoubleTapEvent *event);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(DoubleTapHandler)
    Q_DISABLE_COPY(DoubleTapHandler)
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef GestureHandler BaseClass;
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a handler.
     *
     * To create the builder, call @c DoubleTapHandler::create().
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
         * @brief A convenience method for connecting passed receiver object's slot to
         * the handler's @c doubleTapped() signal with the default connection type 
         * @c Qt::AutoConnection.
         *
         * If @c QObject::connect() fails an assert is raised.
         * If the @c receiver parameter is @c 0 this method has no effect.
         *
         * Example connecting @c onDoubleTapped() slot in @c pMyObject to the handler's
         * @c doubleTapped() signal:
         * @code
         * DoubleTapHandler *pDoubleTapHandler = DoubleTapHandler::create()
         *     .onDoubleTapped(pMyObject, SLOT(onDoubleTapped(bb::cascades::DoubleTapEvent*)));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method   The name of the slot to connect to in the receiver object.
         *                 This object cannot be @c null.
         *
         * @see doubleTapped(), BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onDoubleTapped(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(doubleTapped(bb::cascades::DoubleTapEvent*)), receiver, method);
            return this->builder();
        }
    };

    /*!
     * @brief A builder that constructs a DoubleTapHandler.
     *
     * To retrieve the builder, call @c DoubleTapHandler::create().
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, DoubleTapHandler> {
    public:
        explicit Builder() : TBuilder<Builder, DoubleTapHandler>(new DoubleTapHandler()) {}
    };

    /*!
     * @brief Creates and returns a builder for constructing a doubleTapHandler.
     *
     * Using the builder to create a @c %DoubleTapHandler:
     * @code
     * DoubleTapHandler *pDoubleTapHandler = DoubleTapHandler::create();
     * @endcode
     *
     * @return A Builder used for constructing a DoubleTapHandler.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create() {
        return Builder();
    }

};

}
}

QML_DECLARE_TYPE(bb::cascades::DoubleTapHandler)

#endif /* cascades_doubletaphandler_h */
