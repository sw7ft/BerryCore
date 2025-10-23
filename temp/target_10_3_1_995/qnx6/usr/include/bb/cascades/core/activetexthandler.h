/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef cascades_activetexthandler_h
#define cascades_activetexthandler_h

#include <bb/cascades/core/gesturehandler.h>

namespace bb {
    namespace cascades {

    class ActiveTextHandlerPrivate;
    class ActiveTextTriggeredEvent;

    /*! 
     * @brief A handler for active text interaction.
     *
     * QML example of how to use an active text handler to override the default action of an active text.
     *
     * @code
     * TextArea {
     *     activeTextHandler: ActiveTextHandler {
     *         onTriggered: {
     *             // Abort the action for the active text.
     *             event.abort();
     *         }
     *     }
     * }
     * @endcode
     *
     *
     * @xmlonly
     *     <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ActiveTextHandler : public UIObject 
    {
        Q_OBJECT

    public:

      /*!
       * @brief Creates an @c %ActiveTextHandler.
       *
       * @param parent The object that will own the created handler. This parameter is optional.
       *
       * @since BlackBerry 10.0.0
       */
      explicit ActiveTextHandler(UIObject* parent = 0);

      /*!
       * @brief Destructs the @c %ActiveTextHandler.
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~ActiveTextHandler();

    Q_SIGNALS:

      /*!
       * @brief Emitted when the @c ActiveText is triggered.
       *
       * This signal is emitted synchronously. 
       *
       * Calling ActiveTextTriggeredEvent::abort() will abort the default action of the active text.
       *
       * @see ActiveTextTriggeredEvent::abort()
       *
       * @param event The trigger event.
       *
       * @since BlackBerry 10.0.0
       */
      void triggered(bb::cascades::ActiveTextTriggeredEvent *event);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ActiveTextHandler)
        Q_DISABLE_COPY(ActiveTextHandler)
        /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef UIObject BaseClass;
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a handler.
         *
         * To create the builder, call @c ActiveTextHandler::create().
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
              * @brief A convenience method for connecting the receiver's slot, 
              * passed in as a parameter, to the @c triggered() signal with the 
              * default connection type @c Qt::AutoConnection.
              *
              * Example:
              * @code
              * ActiveTextHandler *activeTextHandler = ActiveTextHandler::create()
              *     .onTriggered(this, SLOT(onTriggeredHandler()));
              * @endcode
              *
              * @param receiver A receiver object. This parameter cannot be @c null.
              * @param method A name for the slot to connect to in the receiver object. 
              *
              * @see @c BaseObject::TBuilder::connect().
              *
              * @since BlackBerry 10.0.0
              */
            BuilderType& onTriggered(const QObject* receiver, const char *method) {
                bool res = QObject::connect(&this->instance(), SIGNAL(triggered(bb::cascades::ActiveTextTriggeredEvent*)), receiver, method);
                Q_ASSERT(res);
                Q_UNUSED(res);
                return this->builder();
            }
        };

        /*!
         * @brief A builder that constructs a ActiveTextHandler.
         *
         * To retrieve the builder, call @c ActiveTextHandler::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ActiveTextHandler> {
        public:
            explicit Builder() : TBuilder<Builder, ActiveTextHandler>(new ActiveTextHandler()) {}
        };

        /*!
         * @brief Creates and returns a builder for constructing a ActiveTextHandler.
         *
         * Using the builder to create a @c %ActiveTextHandler:
         * @code
         *     ActiveTextHandler *pActiveTextHandler = ActiveTextHandler::create();
         * @endcode
         *
         * @return A Builder used for constructing an @c ActiveTextHandler.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::ActiveTextHandler)

#endif /* cascades_activetexthandler_h */
