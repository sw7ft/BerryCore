/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_longpresshandler_h
#define cascades_longpresshandler_h

#include <bb/cascades/core/gesturehandler.h>

namespace bb {
    namespace cascades {

class LongPressHandlerPrivate;
class LongPressEvent;

/*! 
 * @brief A long press handler can be used to react to long press gestures.
 *
 * Example of how to connect a long press handler to a visual node:
 * @code
 * Container* pContainer = Container::create();
 *
 * LongPressHandler *pLongPressHandler = LongPressHandler::create()
 *     .onLongPressed(pMyObject, SLOT(onLongPressedHandler(bb::cascades::LongPressEvent*)));
 *
 * pContainer->addGestureHandler(pLongPressHandler);
 * @endcode
 *
 * Example of how to connect a long press handler to a visual node in QML:
 * @code
 * Container {
 *     gestureHandlers: [
 *         LongPressHandler {
 *             onLongPressed: {
 *                 console.log("LongPress at position " + event.x + ", " + event.y)
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
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT LongPressHandler : public GestureHandler {
    Q_OBJECT

public:
    
    /*!
     * @brief Constructs the handler.
     *
     * @since BlackBerry 10.0.0
     */
    explicit LongPressHandler(UIObject* parent = 0);

    /*!
     * @brief Destructs the handler.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~LongPressHandler();

Q_SIGNALS:
    /*!
     * @brief Emitted when a long press gesture was performed on the associated node.
     *
     * @since BlackBerry 10.0.0
     */
    void longPressed(bb::cascades::LongPressEvent *event);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(LongPressHandler)
    Q_DISABLE_COPY(LongPressHandler)
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef GestureHandler BaseClass;
    /*! @endcond */

    /*!
     * @brief A builder template for constructing a handler.
     *
     * @details To create the builder, call @c LongPressHandler::create().
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
         * the handler's @c longPressed() signal with the default connection type @c Qt::AutoConnection.
         *
         * @details If @c QObject::connect() fails an assert is raised.
         * If the receiver parameter is @c 0 this method has no effect.
         *
         * Example connecting @c onLongPressed() slot in @c pMyObject to the handler's
         * @c longPressed() signal:
         * @code
         * LongPressHandler *pLongPressHandler = LongPressHandler::create()
         *     .onLongPressed(pMyObject, SLOT(onLongPressed(bb::cascades::LongPressEvent*)));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method The name of the slot to connect to in the receiver object.
         *               This receiver object cannot be @c null.
         * 
         * @see longPressed(), BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onLongPressed(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(longPressed(bb::cascades::LongPressEvent*)), receiver, method);
            return this->builder();
        }
    };

    /*!
     * @brief A builder that constructs a LongPressHandler.
     *
     * To retrieve the builder, call @c LongPressHandler::create().
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, LongPressHandler> {
    public:
        explicit Builder() : TBuilder<Builder, LongPressHandler>(new LongPressHandler()) {}
    };

    /*!
     * @brief Creates and returns a builder for constructing a longPressHandler.
     *
     * How to use the builder to create a @c %LongPressHandler:
     * @code
     * LongPressHandler *pLongPressHandler = LongPressHandler::create();
     * @endcode
     *
     * @return A @c Builder used for constructing a @c LongPressHandler.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create() {
        return Builder();
    }

};

}
}

QML_DECLARE_TYPE(bb::cascades::LongPressHandler)

#endif /* cascades_longpresshandler_h */
