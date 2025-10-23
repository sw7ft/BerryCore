/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_invokehandler_h
#define cascades_invokehandler_h

#include <bb/cascades/bbcascades_global.h>
#include <QtCore/QString>
#include <bb/cascades/BaseObject>

namespace bb {
  namespace cascades {
    class InvokeHandlerPrivate;

    /*!
     * @brief Communicates with the caller when an action item is ready to invoke the target.
     *
     * This @c %InvokeHandler is delegated the task of communication with the caller from an @c %InvokeActionItem.
     * The communication is initiated when the signal InvokeHandler::invoking() is triggered by the delegator.
     * Then @c %InvokeHandler waits for the caller to call either InvokeHandler::confirm() or
     * InvokeHandler::cancel(). The @c %InvokeHandler returns back the delegator.
     * If a new signal InvokeHandler::invoking() is triggered by this @c %InvokeHandler while waiting for an
     * answer from the caller, the previous session is ignored.
     *
     * The following sample code shows how to use @c %InvokeHandler in collaboration with an @c %InvokeActionItem in QML:
     *
     * @code
     * ImageView {
     *   attachedObjects: [
     *     Dialog {
     *       id: myDialog
     *       onClosed: {
     *         if (isOk()) {
     *           myHandler.confirm()
     *         }
     *       }
     *       onCancel: {
     *         if (isOk()) {
     *           myHandler.cancel()
     *         }
     *       }
     *     }
     *   ]
     *   contextActions: [
     *     ActionSet {
     *       InvokeActionItem {
     *         handler : InvokeHandler {
     *           onInvoking: {
     *             myDialog.open()
     *           }
     *         }
     *       }
     *     }
     *   ]
     * }
     * @endcode
     *
     * This @c %InvokeHandler can be shared among several invoke action items too.
     * In this case, it need to be placed in an attached object of a common parent.
     * The following sample code explains this:
     *
     * @code
     * ImageView {
     *   attachedObjects: [
     *     InvokeHandler {
     *       id: myHandler
     *       onInvoking: {
     *         myDialog.open()
     *       }
     *     },
     *     Dialog {
     *       id: myDialog
     *       onClosed: {
     *         if (isOk()) {
     *           myHandler.confirm()
     *         }
     *       }
     *       onCancel: {
     *         if (isOk()) {
     *           myHandler.cancel()
     *         }
     *       }
     *     }
     *  ]
     *  contextActions: [
     *    ActionSet {
     *      InvokeActionItem {
     *        query {
     *          // whatever
     *        }
     *        handler: myHandler
     *      }
     *    }
     *  ]
     *}
     * @endcode

     * In C++ using a handler may look like this:
     *
     *@code
     * InvokeHandler hand;
     * InvokeActionItem item;
     * Label* notify;
     *
     * void onInvokingHandler() {
     *     // Show dialog and set connect button clicked slots
     *     // In this case onConfirmedClicked() and onCancelledClicked()
     * }
     *
     * void onConfirmedClicked() {
     *     item.handler()->confirm();
     * }
     *
     * void onCancelledClicked() {
     *     item.handler()->cancel();
     * }
     *
     * void onHandlerChangedHandler(const bb::cascades::InvokeHandler* hand) {
     *     notify.setText("Handler has been updated!");
     * }
     *
     * hand = invokeHandler::create()
     *     .onInvoking(this, SLOT(onInvokingHandler()));
     *
     * item = InvokeActionItem::create(
     *         InvokeQuery::create()
     *             .mimeType("image/png")
     *             .parent(this))
     *         .title("Confirm invocation")
     *         .handler(hand)
     *         .onHandlerChanged(this, SLOT(onHandlerChangedHandler(const bb::cascades::InvokeHandler*)));
     *
     * notify = Label::create();
     *@endcode
	 *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * <qml>
     * <class abstract="no"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT InvokeHandler : public BaseObject
    {
      Q_OBJECT

    public:
      ~InvokeHandler();

      /*!
       * @brief Used by the caller to confirm invocation.
       *
       * The caller confirms a previously intercepted signal InvokeHandler::invoking() from this
       * @c %InvokeHandler that it wants to continue invoking the target.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void confirm();

      /*!
       * @brief Used by the caller to cancel invocation.
       *
       * The caller answers a previously intercepted signal InvokeHandler::invoking() from the
       * handler that it wants to cancel the invocation session.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void cancel();

    Q_SIGNALS:
      /*!
       * @brief Emitted by the invoke action item when it is ready to invoke the target.
       *
       * @since BlackBerry 10.0.0
       */
      void invoking();

    protected:
      /*! @cond PRIVATE */
      explicit InvokeHandler(QObject* const pParent=0);
      /*! @endcond */

    private:
      /*! @cond PRIVATE */
      Q_DECLARE_PRIVATE(InvokeHandler)
      Q_DISABLE_COPY(InvokeHandler)

      typedef InvokeHandler ThisClass;
      typedef BaseObject BaseClass;
      /*! @endcond */

      /*!
       * @brief A builder template for constructing an @c InvokeHandler.
       *
       * To retrieve the builder, call @c InvokeHandler::create().
       *
       * @since BlackBerry 10.0.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
      {
      protected:
        /*!
         * @brief Creates a new builder constructing an @c InvokeHandler.
         *
         * @param node The instance of @c InvokeHandler to build.
         *
         * @since BlackBerry 10.0.0
         */
        TBuilder(BuiltType* node)
          : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {}

      public:
        /*!
          * A convenience method for connecting the passed receiver's slot to
          * the invoking() signal with the default connection type set to
          * Qt::AutoConnection. Here's some related sample code:
          *
          * @code
          * invokeHandler *hand(invokeHandler::create())
          *   .onInvoking(this, SLOT(onInvokingHandler()));
          * @endcode
          *
          * @param receiver a non-@c null receiver object
          * @param method a non-null name of the slot in the receiver object to connect to
          *
          * @see BaseObject::TBuilder::connect()
          *
          * @since BlackBerry 10.0.0
          */
        BuilderType& onInvoking(const QObject* receiver, const char *method) {
          this->connect(SIGNAL(invoking()), receiver, method);
          return this->builder();
        }
      };

      /*!
       * @brief A builder for constructing an @c InvokeHandler.
       *
       * To retrieve the builder, call @c InvokeHandler::create().
       *
       * @since BlackBerry 10.0.0
       */
      class Builder : public TBuilder<Builder, ThisClass>
      {
      public:
        /*!
         * @brief Creates a new builder constructing an @c InvokeHandler.
         *
         * @since BlackBerry 10.0.0
         */
        explicit Builder()
          : TBuilder<Builder, ThisClass>(new ThisClass()) {
        }
      };

    public:

      /*!
       * @brief Creates and returns a builder for constructing an @c %InvokeHandler.
       *
       * Usage:
       * @code
       * InvokeHandler* hand(InvokeHandler::create());
       * @endcode
       *
       * @return A builder used for constructing an @c %InvokeHandler.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create() {
         return Builder();
      }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::InvokeHandler)

#endif  // cascades_invokehandler
