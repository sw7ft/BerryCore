/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef cascades_touchkeyboardhandler_h
#define cascades_touchkeyboardhandler_h

#include <bb/cascades/core/abstracteventhandler.h>

namespace bb {
  namespace cascades {

    class TouchKeyboardHandlerPrivate;
    class TouchKeyboardEvent;

    /*!
     * @brief A handler for reacting on touch input from a "touch keyboard".
     *
     * @warning The @c %TouchKeyboardHandler only works on devices that support
     *          an alternative soft touch on the keyboard, e.g. a physical keyboard
     *          with capacitive touch.
     *
     * @see KeyListener if you are interested in the key that was pressed on rather
     *      than the area that was touched.
     *
     * A touch keyboard handler can be added to objects that inherit from @c VisualNode
     * for being notified about the user touching the keyboard. The touch events propagate
     * starting from the @c %VisualNode currently in focus, iterating up to the root of
     * the scene, emitting TouchKeyboardHandler::touch() on the added handlers.
     *
     * Example of how to connect the touch keyboard handler to a visual node:
     *
     * @code
     * Container* container = Container::create();
     *
     * TouchKeyboardHandler* handler = TouchKeyboardHandler::create()
     *         .onTouch(this, SLOT(handleTouch(bb::cascades::TouchKeyboardEvent*)));
     *
     * container->addEventHandler(handler);
     * @endcode
     *
     * Matching code in QML:
     *
     * @code
     * Container {
     *     eventHandlers: [
     *         TouchKeyboardHandler {
     *             onTouch: {
     *                 console.log("TouchKeyboard: " + event.touchType)
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * @see VisualNode::addEventHandler()
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT TouchKeyboardHandler : public AbstractEventHandler {
      Q_OBJECT

    public:

      /*!
       * @brief Creates a TouchKeyboardHandler
       *
       * @param parent The parent object. The default is @c 0. If not @c 0, the
       * ownership of the constructed object will be transfered to the parent object.
       *
       * @since BlackBerry 10.3.0
       */
      explicit TouchKeyboardHandler(bb::cascades::UIObject* parent = 0);

      /*!
       * @brief Destructs the handler.
       *
       * @since BlackBerry 10.3.0
       */
      virtual ~TouchKeyboardHandler();

    Q_SIGNALS:

      /*!
       * @brief Emitted when a touch event is received from the touch keyboard.
       *
       * The keyboard touch events propagate starting from the @c %VisualNode
       * currently in focus, iterating up to the root of the scene, emitting
       * this signal on the added handlers.
       *
       * @warning During propagation other controls might steal focus or consume
       *          the event, in which case this signal is emitted with cancel
       *          event. This means that a touch interaction can either end with
       *          touch up or a touch cancel. See @c %TouchKeyboardEvent::touchType.
       *
       * @param event The touch event.
       *
       * @since BlackBerry 10.3.0
       */
      void touch(bb::cascades::TouchKeyboardEvent* event);

    private:
      /*! @cond PRIVATE */
      Q_DECLARE_PRIVATE(TouchKeyboardHandler)
      Q_DISABLE_COPY(TouchKeyboardHandler)
      /*! @endcond */

    public:
      /*! @cond PRIVATE */
      typedef AbstractEventHandler BaseClass;
      /*! @endcond */

      /*!
       * @brief A builder template for constructing a @c %TouchKeyboardHandler.
       *
       * See TouchKeyboardHandler::create() for getting a concrete builder for constructing a @c %TouchKeyboardHandler.
       *
       * @since BlackBerry 10.3.0
       */
       template <typename BuilderType, typename BuiltType>
       class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
       {
       protected:
           TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}

       public:
           /*!
            * A convenience method for connecting passed receiver's slot to
            * the @c touch(bb::cascades::TouchKeyboardEvent *) signal with the default
            * connection type Qt::AutoConnection.
            *
            * Example:
            * @code
            * TouchKeyboardHandler::create()
            *     .onTouch(this, SLOT(handleTouch(bb::cascades::TouchKeyboardEvent*)));
            * @endcode
            *
            * @param receiver A receiver object. This object cannot be @c null.
            * @param method a non-@c null name of the slot in the receiver object to connect to
            *
            * @see BaseObject::TBuilder::connect()
            *
            * @since BlackBerry 10.3.0
            */
           BuilderType& onTouch(const QObject* receiver, const char *method) {
               this->connect(SIGNAL(touch(bb::cascades::TouchKeyboardEvent*)), receiver, method);
               return this->builder();
           }
       };

      /*!
       * @brief A concrete builder class for constructing a @c %TouchKeyboardHandler.
       *
       * @since BlackBerry 10.3.0
       *
       */
       class Builder : public TBuilder<Builder, TouchKeyboardHandler>
       {
       public:
           explicit Builder() : TBuilder<Builder, TouchKeyboardHandler>(new TouchKeyboardHandler()) {}
       };

       /*!
        * @brief Creates and returns a builder for constructing an @c %TouchKeyboardHandler.
        *
        * Using the builder to create a handler for receiving touch events from the touch keyboard:
        * @code
        * Container::create()
        *     .addEventHandler(TouchKeyboardHandler::create()
        *         .onTouch(this, SLOT(handleTouch(bb::cascades::TouchKeyboardEvent*))));
        * @endcode
        *
        * @return A Builder for constructing an @c %TouchKeyboardHandler.
        *
        * @since BlackBerry 10.3.0
        */
       static Builder create()
       {
           return Builder();
       }

    };

  }
}

QML_DECLARE_TYPE(bb::cascades::TouchKeyboardHandler)

#endif /* cascades_touchkeyboardhandler_h */
