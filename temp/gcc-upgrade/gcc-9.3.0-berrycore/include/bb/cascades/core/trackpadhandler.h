/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_trackpadhandler_h
#define cascades_trackpadhandler_h

#include <bb/cascades/core/abstracteventhandler.h>
#include <bb/cascades/core/consumetrackpadevent.h>

namespace bb {
  namespace cascades {

    class TrackpadHandlerPrivate;
    class TrackpadEvent;

    /*!
     * @brief A handler for capturing input from the trackpad.
     *
     * This handler returns minimally filtered events. To avoid hardware-specific dependencies
     * it's recommended that you use the high-level @c NavigationHandler instead.
     *
     * @see VisualNode::addEventHandler()
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT TrackpadHandler : public AbstractEventHandler {
      Q_OBJECT

     /*!
      * @brief This property defines which trackpad events that are consumed by the application.
      *
      * These events are assumed to be handled by the application and are ignored by Cascades.
      *
      * The default @c consumeTrackpadEvents is @c None, meaning that no events are consumed.
      *
      * (example/snippet)
      *
      * @since BlackBerry 10.3.1
      */
     Q_PROPERTY(bb::cascades::ConsumeTrackpadEvent::Types consumeTrackpadEvents READ consumeTrackpadEvents
                WRITE setConsumeTrackpadEvents RESET resetConsumeTrackpadEvents NOTIFY consumeTrackpadEventsChanged FINAL)

    public:

      /*!
       * @brief Creates a TrackpadHandler
       *
       * @param parent The parent object. The default is @c 0. If not @c 0, the
       * ownership of the constructed object will be transfered to the parent object.
       *
       * @since BlackBerry 10.3.1
       */
      explicit TrackpadHandler(bb::cascades::UIObject* parent = 0);

      /*!
       * @brief Destructs the handler.
       *
       * @since BlackBerry 10.3.1
       */
      virtual ~TrackpadHandler();

      /*!
      * @brief Sets which type of trackpad events that are consumed.
      *
      * @param consumeTrackpadEvents The type of trackpad events that are consumed.
      *
      * @since BlackBerry 10.3.1
      */
      Q_SLOT void setConsumeTrackpadEvents(bb::cascades::ConsumeTrackpadEvent::Types consumeTrackpadEvents);

      /*!
      * @brief Gets the consume trackpad event types. The flag describes which trackpad events that will be consumed.
      *
      * @return The consume trackpad event types for this handler.
      *
      * @since BlackBerry 10.3.1
      */
      bb::cascades::ConsumeTrackpadEvent::Types consumeTrackpadEvents();

      /*!
      * @brief Reset the consume trackpad event types for this handler.
      *
      * @since BlackBerry 10.3.1
      */
      Q_SLOT void resetConsumeTrackpadEvents();

    Q_SIGNALS:

      /*!
       * @brief Emitted when a trackpad event is received from the trackpad.
       *
       * @param event The trackpad event.
       *
       * @since BlackBerry 10.3.1
       */
      void trackpad(bb::cascades::TrackpadEvent* event);

      /*!
       * @brief Emitted when the consume trackpad event types changes.
       *
       * @param newConsumeTrackpadEvents The consume trackpad event types.
       *
       * @since BlackBerry 10.3.1
       */
      void consumeTrackpadEventsChanged(bb::cascades::ConsumeTrackpadEvent::Types newConsumeTrackpadEvents);

    private:
      /*! @cond PRIVATE */
      Q_DECLARE_PRIVATE(TrackpadHandler)
      Q_DISABLE_COPY(TrackpadHandler)
      /*! @endcond */

    public:
      /*! @cond PRIVATE */
      typedef AbstractEventHandler BaseClass;
      /*! @endcond */

      /*!
       * @brief A builder template for constructing a @c %TrackpadHandler.
       *
       * See TrackpadHandler::create() for getting a concrete builder for constructing a @c %TrackpadHandler.
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
            * the @c trackpad(bb::cascades::TrackpadEvent *) signal with the default
            * connection type Qt::AutoConnection.
            *
            * Example:
            * @code
            * TrackpadHandler::create()
            *     .onTrackpad(this, SLOT(handleTrackpad(bb::cascades::TrackpadEvent*)));
            * @endcode
            *
            * @param receiver A receiver object. This object cannot be @c null.
            * @param method a non-@c null name of the slot in the receiver object to connect to
            *
            * @see BaseObject::TBuilder::connect()
            *
            * @since BlackBerry 10.3.1
            */
           BuilderType& onTrackpad(const QObject* receiver, const char *method) {
               this->connect(SIGNAL(trackpad(bb::cascades::TrackpadEvent*)), receiver, method);
               return this->builder();
           }
       };

      /*!
       * @brief A concrete builder class for constructing a @c %TrackpadHandler.
       *
       * @since BlackBerry 10.3.1
       *
       */
       class Builder : public TBuilder<Builder, TrackpadHandler>
       {
       public:
           explicit Builder() : TBuilder<Builder, TrackpadHandler>(new TrackpadHandler()) {}
       };

       /*!
        * @brief Creates and returns a builder for constructing an @c %TrackpadHandler.
        *
        * Using the builder to create a handler for receiving trackpad events:
        * @code
        * Container::create()
        *     .addEventHandler(TrackpadHandler::create()
        *         .onTrackpad(this, SLOT(handleTrackpad(bb::cascades::TrackpadEvent*))));
        * @endcode
        *
        * @return A Builder for constructing an @c %TrackpadHandler.
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

QML_DECLARE_TYPE(bb::cascades::TrackpadHandler)

#endif /* cascades_trackpadhandler_h */
