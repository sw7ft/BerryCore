/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_taphandler_h
#define cascades_taphandler_h

#include <bb/cascades/core/gesturehandler.h>

namespace bb {
    namespace cascades {

class TapHandlerPrivate;
class TapEvent;

/*!
 * @brief A tap handler can be used to react to tap gestures.
 *
 * Example of how to connect a tap handler to a visual node:
 *
 * @code
 * Container* pContainer = Container::create();
 *
 * TapHandler *pTapHandler = TapHandler::create()
 *     .onTapped(pMyObject, SLOT(onTappedHandler(bb::cascades::TapEvent*)));
 *
 * pContainer->addGestureHandler(pTapHandler);
 * @endcode
 *
 * Matching code in QML:
 *
 * @code
 * Container {
 *     gestureHandlers: [
 *         TapHandler {
 *             onTapped: {
 *                 console.log("Tap at position " + event.x + ", " + event.y)
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
 * <class abstract="no"/>
 * </qml>
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TapHandler : public GestureHandler {
    Q_OBJECT

public:

    /*!
     * @brief Creates a TapHandler
     *
     * @param parent The parent object, or @c 0. This parameter is optional.
     * The default is @c 0 if you don't specify a parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit TapHandler(bb::cascades::UIObject* parent = 0);

    /*!
     * @brief Destructs the handler.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~TapHandler();

Q_SIGNALS:
    /*!
     * Emitted when a tap gesture was performed on the associated node.
     *
     * @since BlackBerry 10.0.0
     */
    void tapped(bb::cascades::TapEvent *event);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(TapHandler)
    Q_DISABLE_COPY(TapHandler)
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef GestureHandler BaseClass;
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a handler.
     *
     * To retrieve the builder, call TapHandler::create().
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
         * A convenience method for connecting passed receiver object's slot to
         * the handler's tapped() signal with the default connection type
         * Qt::AutoConnection.
         *
         * If QObject::connect() fails an assert is raised.
         * If receiver parameter is @c 0 this method has no effect.
         *
         * Example connecting onTapped() slot in pMyObject to the handler's
         * tap() signal:
         * @code
         * TapHandler *pTapHandler = TapHandler::create()
         *     .onTapped(pMyObject, SLOT(onTapped(bb::cascades::TapEvent*)));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method a non-@c null name of the slot in the receiver object to connect to
         *
         * @see tapped(), BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onTapped(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(tapped(bb::cascades::TapEvent*)), receiver, method);
            return this->builder();
        }
    };

    /*!
     * @brief A builder that constructs a TapHandler.
     *
     * To create the builder, call @c TapHandler::create().
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, TapHandler> {
    public:
        explicit Builder() : TBuilder<Builder, TapHandler>(new TapHandler()) {}
    };

    /*!
     * @brief Creates and returns a builder for constructing a tapHandler.
     *
     * Using the builder to create a @c %TapHandler:
     * @code
     * TapHandler *pTapHandler = TapHandler::create();
     * @endcode
     *
     * @return A Builder used for constructing a TapHandler.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create() {
        return Builder();
    }

};

}
}

QML_DECLARE_TYPE(bb::cascades::TapHandler)

#endif /* cascades_taphandler_h */
