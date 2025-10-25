/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_navigationhandler_h
#define cascades_navigationhandler_h

#include <bb/cascades/core/abstracteventhandler.h>
#include <bb/cascades/core/consumenavigationevent.h>

namespace bb {
  namespace cascades {

    class NavigationHandlerPrivate;
    class NavigationEvent;

    /*!
     * @brief A handler for reacting to navigation events from the trackpad.
     *
     * This handler captures high-level navigation events that are filtered and scaled for the
     * dpi of the device (unlike @c TrackpadHandler which captures minimally filtered events).
     *
     * You can attach a handler to any node in your app by using @c VisualNode::addEventHandler().
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT NavigationHandler : public AbstractEventHandler {
      Q_OBJECT

     /*!
      * @brief This property defines which navigation events that are consumed by the application.
      *
      * These events are assumed to be handled by the application and are ignored by Cascades.
      *
      * The default @c consumeNavigationEvents is @c None, meaning that no events are consumed.
      *
      * (example/snippet)
      *
      * @since BlackBerry 10.3.1
      */
     Q_PROPERTY(bb::cascades::ConsumeNavigationEvent::Types consumeNavigationEvents READ consumeNavigationEvents
                WRITE setConsumeNavigationEvents RESET resetConsumeNavigationEvents NOTIFY consumeNavigationEventsChanged FINAL)

    public:

      /*!
       * @brief Creates a NavigationHandler
       *
       * @param parent The parent object. The default is @c 0. If not @c 0, the
       * ownership of the constructed object will be transfered to the parent object.
       *
       * @since BlackBerry 10.3.1
       */
      explicit NavigationHandler(bb::cascades::UIObject* parent = 0);

      /*!
       * @brief Destructs the handler.
       *
       * @since BlackBerry 10.3.1
       */
      virtual ~NavigationHandler();

      /*!
       * @brief Sets which type of navigation events that are consumed.
       *
       * @param consumeNavigationEvents The type of navigation events that are consumed.
       *
       * @since BlackBerry 10.3.1
       */
      Q_SLOT void setConsumeNavigationEvents(bb::cascades::ConsumeNavigationEvent::Types consumeNavigationEvents);

       /*!
       * @brief Gets the consume navigation event types. The flag describes which navigation events that will be consumed.
       *
       * @return The consume navigation event types for this handler.
       *
       * @since BlackBerry 10.3.1
       */
      bb::cascades::ConsumeNavigationEvent::Types consumeNavigationEvents();

       /*!
       * @brief Reset the consume navigation event types for this handler.
       *
       * @since BlackBerry 10.3.1
       */
      Q_SLOT void resetConsumeNavigationEvents();


    Q_SIGNALS:

      /*!
       * @brief Emitted when a trackpad event is received from the trackpad.
       *
       * @param event The trackpad event.
       *
       * @since BlackBerry 10.3.1
       */
      void navigation(bb::cascades::NavigationEvent* event);

      /*!
       * @brief Emitted when the consume navigation event types changes.
       *
       * @param newConsumeNavigationEvents The consume navigation event types.
       *
       * @since BlackBerry 10.3.1
       */
      void consumeNavigationEventsChanged(bb::cascades::ConsumeNavigationEvent::Types newConsumeNavigationEvents);

    private:
      /*! @cond PRIVATE */
      Q_DECLARE_PRIVATE(NavigationHandler)
      Q_DISABLE_COPY(NavigationHandler)
      /*! @endcond */

    public:
      /*! @cond PRIVATE */
      typedef AbstractEventHandler BaseClass;
      /*! @endcond */

      /*!
       * @brief A builder template for constructing a @c %NavigationHandler.
       *
       * See TrackpadHandler::create() for getting a concrete builder for constructing a @c %NavigationHandler.
       *
       * @since BlackBerry 10.3.1
       */
       template <typename BuilderType, typename BuiltType>
       class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
       {
       protected:
           TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}

       public:
           /*!
            * A convenience method for connecting passed receiver's slot to
            * the @c navigation(bb::cascades::NavigationEvent *) signal with the default
            * connection type Qt::AutoConnection.
            *
            * Example:
            * @code
            * NavigationHandler::create()
            *     .onNavigation(this, SLOT(handleNavigation(bb::cascades::NavigationEvent*)));
            * @endcode
            *
            * @param receiver A receiver object. This object cannot be @c null.
            * @param method a non-@c null name of the slot in the receiver object to connect to
            *
            * @see BaseObject::TBuilder::connect()
            *
            * @since BlackBerry 10.3.1
            */
           BuilderType& onNavigation(const QObject* receiver, const char *method) {
               this->connect(SIGNAL(navigation(bb::cascades::NavigationEvent*)), receiver, method);
               return this->builder();
           }
       };

      /*!
       * @brief A concrete builder class for constructing a @c %NavigationHandler.
       *
       * @since BlackBerry 10.3.1
       *
       */
       class Builder : public TBuilder<Builder, NavigationHandler>
       {
       public:
           explicit Builder() : TBuilder<Builder, NavigationHandler>(new NavigationHandler()) {}
       };

       /*!
        * @brief Creates and returns a builder for constructing an @c %NavigationHandler.
        *
        * Using the builder to create a handler for receiving navigation events:
        * @code
        * Container::create()
        *     .addEventHandler(NavigationHandler::create()
        *         .onNavigation(this, SLOT(handleTouch(bb::cascades::NavigationEvent*))));
        * @endcode
        *
        * @return A Builder for constructing an @c %NavigationHandler.
        *
        * @since BlackBerry 10.3.1
        */
       static Builder create()
       {
           return Builder();
       }

    };

  }
}

QML_DECLARE_TYPE(bb::cascades::NavigationHandler)

#endif /* cascades_navigationhandler_h */
