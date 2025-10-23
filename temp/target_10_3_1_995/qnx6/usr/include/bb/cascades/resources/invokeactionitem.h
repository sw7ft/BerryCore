/*!
 * @copyright
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_invokeactionitem_h
#define cascades_invokeactionitem_h

#include <bb/cascades/InvokeState>
#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>
#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace bb {
  namespace cascades {
    class InvokeActionItemPrivate;
    class InvokeQuery;
    class InvokeHandler;

    /*!
     * @brief Represents actions for invoking application-level components.
     *
     * The @c %InvokeActionItem class represents an invocation service that can be
     * added to a context menu like an @c ActionItem. It will expand to a number of
     * visual action items in the context menu (though these generated items
     * won't be accessible in code). Each of these action items will represent
     * a possible invocation action and will display a list of possible
     * invocation targets when pressed. When selecting an invocation target
     * from the list @c %InvokeActionItem will perform the invocation using the chosen action
     * and target.
     *
     * In addition to providing a simple-to-use invocation service, this class provides
     * the option of adding data at a very late stage to be used when invoking the target.
     * If this data is actively set, then it overrides data previously set from query.
     * The data is an array that can carry multiple items defined by the caller to be
     * communicated to the target.
     *
     * This class uses the %Invocation framework (@c bb::system::MenuManager,
     * @c bb::system::InvokeManager and related classes) for its operations.
     * It is to be seen as the default way of connecting invocations to @c Control
     * objects, providing a system default UI and execution flow for the task through
     * a simple interface. If more advanced invocation options are needed or the usual
     * UI flow does not fit the task at hand, it's recommended to bypass this class and
     * access the %Invoke framework directly and build the execution flow from scratch.
     *
     * For more information about invocations and the %Invoke framework,
     * @c bb::system::MenuManager, @c bb::system::InvokeManager,
     * @c bb::system::InvokeAction, and @c bb::system::InvokeTarget might be good
     * places to start.
     *
     * @note If an @c %InvokeActionItem object is deleted within @c InvokeState.Selecting
     * state, the selection list UI will be closed by framework.
     *
     * The @c %InvokeActionItem class uses @c InvokeQuery to represent an immutable
     * query object containing properties used to ask the %Invoke framework for
     * supporting actions and targets.
     *
     * These are the rules controlling how @c %InvokeActionItem will interpret
     * an @c InvokeQuery:
     * @li If neither @c InvokeQuery::invokeActionId nor
     *     @c InvokeQuery::invokeTargetId are set, this @c %InvokeActionItem
     *     will represent an unbound invocation and will expand into zero to
     *     many @c ActionItem objects each with a different action and different set
     *     of targets.
     * @li If the @c InvokeQuery::invokeActionId but not the
     *     @c InvokeQuery::invokeTargetId is set, this @c %InvokeActionItem will
     *     expand into zero to one @c ActionItem objects using the specified action.
     * @li If the @c InvokeQuery::invokeTargetId but not the
     *     @c InvokeQuery::invokeActionId is set, this @c %InvokeActionItem will
     *     expand into zero to many @c ActionItem objects, each with a different
     *     action but all of them using the same target.
     * @li If both @c InvokeQuery::invokeActionId and @c InvokeQuery::invokeTargetId
     *     is set, this @c %InvokeActionItem will represent a bound invocation
     *     and will expand into zero to one @c ActionItem objects using the specified
     *     action and target.
     *
     * If there is only one invoke target possible for an invoke action
     * generated from an @c %InvokeActionItem, the @c ActionItem representing the
     * invoke action will immediately launch the invocation target when pressed,
     * without showing a list of targets to choose from.
     *
     * The caller has an option to control the invocation process using the property handler.
     * If (and only if) the handler is set, the caller is notified when this
     * @c %InvokeActionItem is ready to invoke the user-selected target. By default, the
     * handler is not set. Typical need for this option could for example be to ask the user
     * for necessary input by showing a dialog, show a spinner if a file needs to be updated
     * before invocation or simply for some reason choose to cancel the whole operation.
     *
     * The @c %InvokeActionItem delegates the communication with the caller to the
     * @c %InvokeHandler object (the handler) provided by the caller.
     * The handler (delegate) reports back to this @c %InvokeActionItem (delegator)
     * the corresponding answer from the caller; confirmed or cancelled. If confirmed,
     * then this @c %InvokeActionItem will continue invocation. If cancelled is intercepted,
     * then invocation is aborted and a finished signal will be sent from @c %InvokeActionItem.
     *
     * The @c title, @c image and @c imageSource properties inherited from @c AbstractActionItem
     * have no real purpose in %InvokeActionItem since the %InvokeActionItem itself will never be shown.
     * If used anyway, all the items displayed as a result from the query will have the same title/image.<br/>
     * <em>Don't use these properties on %InvokeActionItem.</em>
     *
     * Here's how to create an @c %InvokeActionItem, using the builder pattern:
     *
     * @code
     * InvokeActionItem* pInvokeActionItem(InvokeActionItem::create(
     *   InvokeQuery::create()
     *     .parent(this)
     *     .mimeType("text/txt"))
     *   .onFinished(this, SLOT(onFinished(bb::cascades::InvokeState::Type))));
     * @endcode
     *
     * And here's how to create an @c %InvokeActionItem for a @c Button using QML:
     *
     * @code
     * InvokeActionItem {
     *     query {
     *         mimeType: "text/txt"
     *         uri: "file:///path/to/my/textfile.txt"
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT InvokeActionItem : public AbstractActionItem
    {
      Q_OBJECT

    public:
      /*!
       * @brief The query used by the @c %InvokeActionItem.
       *
       * Once this @c %InvokeActionItem has been created, this property becomes
       * read-only and attempts to change it will be ignored.
       *
       * @xmlonly
       * <qml>
       * <property groupedProperty="yes"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(bb::cascades::InvokeQuery* query READ queryQml FINAL)

      /*!
       * @brief The handler used by this @c %InvokeActionItem to communicate with the caller when ready to
       * invoke the selected target.
       *
       * This @c %InvokeActionItem will wait to invoke the user-selected target when ready and delegate the
       * communication with the caller to its @c %InvokeHandler if such is set. The handler will report back
       * to this @c %InvokeActionItem to make decisions.
       * If the handler reports that the invocation has been confirmed, this @c %InvokeActionItem will continue
       * invocation. If the handler reports that the invocation has been cancelled, this @c %InvokeActionItem
       * will abort invocation.
       * If no handler is set or the set handler is reset, this feature is disabled and this @c %InvokeActionItem
       * will invoke the target directly without interruption. By default the handler is not set.
       *
       * @note When an InvokeHandler is called a target has been selected and a re-query to MenuService is not possible.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(bb::cascades::InvokeHandler* handler NOTIFY handlerChanged READ handler WRITE setHandler RESET resetHandler FINAL)

      /*!
       * @brief The data used when invoking an action/target overriding
       * the data set from query.
       *
       * The caller can set data to be invoked at a late stage prior
       * to invoke the target. If this data is set, then it
       * overrides the data previously set from query.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QVariant data READ dataQml WRITE setDataQml RESET resetData NOTIFY dataChangedQml FINAL)

      /*!
       * @brief The metadata used when invoking an action/target overriding
       * the metadata set from query.
       *
       * The caller can set metadata to be invoked at a late stage prior
       * to invoke the target. If this metadata is set, then it
       * overrides the metadata previously set from query.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QVariantMap metadata READ metadata WRITE setMetadata RESET resetMetadata NOTIFY metadataChanged FINAL)

      /*!
       * @brief The different state an @c %InvokeActionItem can be in or end up in.
       *
       * When %InvokeActionItem is finished the @c finished() signal is emitted with the final state.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(bb::cascades::InvokeState::Type state READ state NOTIFY stateChanged FINAL)

      /*!
       * @brief Creates a new @c %InvokeActionItem with a @c 0 query
       *
       * @param pParent The parent of this object.
       *
       * @since BlackBerry 10.0.0
       */
      explicit InvokeActionItem(QObject* pParent=0);

      /*!
       * @brief Creates a new @c %InvokeActionItem with provided query and optional parent.
       *
       * @param query The query to use in the new @c %InvokeActionItem.
       * @param pParent The parent of this object.
       *
       * @since BlackBerry 10.0.0
       */
      explicit InvokeActionItem(const bb::cascades::InvokeQuery* query, QObject* pParent=0);

      /*!
       * @brief Destroys this @c %InvokeActionItem.
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~InvokeActionItem();

      /*!
       * @brief Gets the immutable query used to ask for actions and
       * targets previously set by this interface.
       *
       * The caller takes ownership of the returned pointer.
       *
       * @return The query of this @c %InvokeActionItem.
       *
       * @since BlackBerry 10.0.0
       */
      bb::cascades::InvokeQuery* query() const;

      /*!
       * @brief Gets the invocation data to be invoked with target.
       *
       * The caller can inspect previously set invocation data. If
       * this data is set, then it overrides the data previously set
       * from query when invoking the action/target.
       *
       * @return The data used for invoking the action.
       *
       * @since BlackBerry 10.0.0
       */
      QByteArray data() const;

      /*!
       * @brief Sets the data to be sent when invoking the target.
       *
       * The caller can set data to be invoked at a late stage prior
       * to invoke the target. If this data is set, then it
       * overrides the data previously set from query.
       *
       * @param data is data used when invoking the action/target.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setData(const QByteArray& data);

      /*!
       * @brief Resets the data for this @c %InvokeActionItem.
       *
       * The caller can reset invocation data and this way reuse
       * the data first set from the query when invoking the action/target.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetData();

      /*!
       * @deprecated Use @c data() instead.
       *
       * @since BlackBerry 10.0.0
       */
      QByteArray invocationData() const;
      /*!
       * @deprecated Use @c setData() instead.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setInvocationData(const QByteArray& invocationData);
      /*!
       * @deprecated Use @c resetData() instead.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetInvocationData();

      /*!
       * @brief Gets the metadata to be sent when invoking the target.
       *
       * The caller can inspect previously set invocation metadata. If
       * this metadata is set, then it overrides the metadata previously set
       * from query when invoking the action/target.
       *
       * @return The metadata used for invoking the action.
       *
       * @since BlackBerry 10.0.0
       */
      QVariantMap metadata() const;

      /*!
       * @brief Sets the metadata to be sent when invoking the target.
       *
       * @param metadata The metadata used when invoking the action/target.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setMetadata(const QVariantMap& metadata);

      /*!
       * @brief Resets the metadata for this @c %InvokeActionItem.
       *
       * @note To ensure that metadata is not lost in an invocation request, you
       * must set metadata in the @c InvokeQuery class.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetMetadata();

      /*!
       * @brief Gets the current state of the @c %InvokeActionItem.
       *
       * @return The current state of the @c %InvokeActionItem.
       *
       * @since BlackBerry 10.0.0
       */
      bb::cascades::InvokeState::Type state() const;

      /*!
       * @brief Gets the invoke handler for this @c %InvokeActionItem.
       *
       * @return The invoke handler object.
       *
       * @since BlackBerry 10.0.0
       */
      bb::cascades::InvokeHandler* handler() const;

      /*!
       * @brief Sets the invoke handler for this @c %InvokeActionItem.
       *
       * If a handler is set by this interface and this @c %InvokeActionItem is ready
       * to invoke a user-selected target, it will wait for confirmation from the
       * caller. However, this @c %InvokeActionItem will delegate the communication
       * with the caller to its @c %InvokeHandler set by this interface.
       *
       * This @c %InvokeActionItem takes ownership of the handler object unless it
       * already has a parent.
       *
       * When a new handler is set by this interface, the former is replaced.
       *
       * @param pHandler The invoke handler object.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setHandler(bb::cascades::InvokeHandler* pHandler);

      /*!
       * @brief Resets the invoke handler for this @c %InvokeActionItem.
       *
       * Resetting a previously set handler means that this @c %InvokeActionItem will
       * invoke the target directly without waiting for confirmation from the caller.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetHandler();

    Q_SIGNALS:
      /*!
       * @brief Emitted when data has been changed.
       *
       * @param data The new data set late by application.
       *
       * @since BlackBerry 10.0.0
       */
      void dataChanged(const QByteArray& data);

      /*! @cond PRIVATE */
      void dataChangedQml(const QVariant& data);
      /*! @endcond */

      /*!
       * @brief Emitted when the metadata has changed.
       *
       * @param metadata The new metadata.
       *
       * @since BlackBerry 10.0.0
       */
      void metadataChanged(const QVariantMap& metadata);

      /*!
       * @brief Emitted when the state has changed.
       *
       * @note Due to a work around for a Qt Core issue with accessing enums from QML
       * the argument of this signal doesn't follow naming convention for signals in
       * which the signal arguments are typically named to match the associated property's name.
       * Use the object's property to access current property value instead of the signal argument
       * to avoid runtime errors (i.e. use @c state instead of @c newState).
       *
       * @param newState The new state.
       * @see @c finished()
       *
       * @since BlackBerry 10.0.0
       */
      void stateChanged(bb::cascades::InvokeState::Type newState);

      /*!
       * @deprecated Use @c handlerChanged(bb::cascades::InvokeHandler* handler) instead.
       *
       * @since BlackBerry 10.0.0
       */
      void handlerChanged(const bb::cascades::InvokeHandler* handler);

      /*!
       * @brief Emitted when the invoke handler is changed.
       *
       * @param handler The new invocation handler.
       *
       * @since BlackBerry 10.1.0
       */
      void handlerChanged(bb::cascades::InvokeHandler* handler);

      /*!
       * @brief Emitted when @c %InvokeActionItem processing has finished.
       *
       * @note Due to a work around for a Qt Core issue with accessing enums from QML
       * the argument of this signal doesn't follow naming convention for signals in
       * which the signal arguments are typically named to match the associated property's name.
       * Use the object's property to access current property value instead of the signal argument
       * to avoid runtime errors (i.e. use @c state instead of @c newState).
       *
       * @param newState The final state of @c %InvokeActionItem.
       *
       * @see @c InvokeState::Invoked, @c InvokeState::Cancelled, @c InvokeState::Error, @c stateChanged()
       *
       * @since BlackBerry 10.0.0
       */
      void finished(bb::cascades::InvokeState::Type newState);

    private:
      /*! @cond PRIVATE */
      typedef InvokeActionItem ThisClass;
      typedef AbstractActionItem BaseClass;

      /*!
       * @brief Return a InvokeQuery object to QML and giving JavaScript ownership.
       *
       * @return The current InvokeQuery parameters in use.
       */
      bb::cascades::InvokeQuery* queryQml() const;

      /*!
       * @brief Converts data from QByteArray into QVariant for the public UI.
       *
       * @return The data with correct type (QVariant) to be exposed in the UI.
       */
      QVariant dataQml() const;

      /*!
       * @brief Converts data from QVariant into QByteArray for the public UI.
       *
       * @param data as exposed in the UI.
       */
      void setDataQml(const QVariant& data);

      /*!
       * @brief Sets the query for this @c %InvokeActionItem.
       *
       * Ownership of the @c InvokeQuery object remains
       * unchanged.
       *
       * @param pQuery The new query for this @c %InvokeActionItem.
       */
      void setQuery(const bb::cascades::InvokeQuery* pQuery);

      Q_DECLARE_PRIVATE(InvokeActionItem)
      Q_DISABLE_COPY(InvokeActionItem)
      /*! @endcond */

      /*!
       * @brief A builder template for constructing an @c InvokeActionItem.
       *
       * To retrieve the builder,
       * call @c InvokeActionItem::create(InvokeQuery::create()).
       *
       * @since BlackBerry 10.0.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
      {
      protected:
        /*!
         * @brief Creates a new builder constructing an @c InvokeActionItem.
         *
         * @param node The instance of @c InvokeActionItem to build.
         *
         * @since BlackBerry 10.0.0
         */
        TBuilder(BuiltType* node)
          : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {
        }

      public:
        /*!
        * @copydoc bb::cascades::InvokeActionItem::setHandler(bb::cascades::InvokeHandler*)
        *
        * @param pHandler is the handler used for a certain invocation session.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& handler(bb::cascades::InvokeHandler* const pHandler) {
          this->instance().setHandler(pHandler);
          return this->builder();
        }

        /*!
         * @brief Connect a slot to the @c finished() signal.
         *
         * A convenience method for connecting passed receiver's slot to
         * the @c finished() signal with the default connection type Qt::AutoConnection.
         *
         * Example:
         * @code
         * InvokeActionItem* p(InvokeActionItem::create(InvokeQuery::create())
         *     .onFinished(this, SLOT(myOnFinished(bb::cascades::InvokeState::Type))));
         * @endcode
         *
         * @param receiver a non-@c null receiver object
         * @param method a non-@c null name of the slot in the receiver object to connect to
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onFinished(const QObject* receiver, const char* method) {
          this->connect(SIGNAL(finished(bb::cascades::InvokeState::Type)), receiver, method);
          return this->builder();
        }

        /*!
         * @brief Connect a slot to the @c stateChanged() signal.
         *
         * A convenience method for connecting passed receiver's slot to
         * the @c stateChanged() signal with the default connection type Qt::AutoConnection.
         *
         * Example:
         * @code
         * InvokeActionItem* p(InvokeActionItem::create(InvokeQuery::create())
         *     .onStateChanged(this, SLOT(myOnStateChanged(bb::cascades::InvokeState::Type))));
         * @endcode
         *
         * @param receiver a non-@c null receiver object
         * @param method a non-@c null name of the slot in the receiver object to connect to
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onStateChanged(const QObject* receiver, const char* method) {
          this->connect(SIGNAL(stateChanged(bb::cascades::InvokeState::Type)), receiver, method);
          return this->builder();
        }

        /*!
          * A convenience method for connecting the passed receiver's slot to
          * the dataChanged() signal with the default connection type set to
          * Qt::AutoConnection.Here's some related sample code:
          *
          * @code
          * InvokeActionItem *pInvokeActionItem = InvokeActionItem::create(InvokeQuery::create())
          *     .onDataChanged(this, SLOT(myOnDataChanged(const QByteArray&)));
          * @endcode
          *
          * @param receiver a non-@c null receiver object
          * @param method a non-@c null name of the slot in the receiver object to connect to
          *
          * @see BaseObject::TBuilder::connect()
          *
          * @since BlackBerry 10.0.0
          */
        BuilderType& onDataChanged(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(dataChanged(const QByteArray&)), receiver, method);
            return this->builder();
        }

        /*!
          * A convenience method for connecting the passed receiver's slot to
          * the metadataChanged() signal with the default connection type set to
          * Qt::AutoConnection.Here's some related sample code:
          *
          * @code
          * InvokeActionItem *pInvokeActionItem = InvokeActionItem::create(InvokeQuery::create())
          *     .onMetadataChanged(this, SLOT(myOnMetadataChanged(const QVariantMap&)));
          * @endcode
          *
          * @param receiver a non-@c null receiver object
          * @param method a non-@c null name of the slot in the receiver object to connect to
          *
          * @see BaseObject::TBuilder::connect()
          *
          * @since BlackBerry 10.0.0
          */
        BuilderType& onMetadataChanged(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(metadataChanged(const QVariantMap&)), receiver, method);
            return this->builder();
        }

        /*!
          * A convenience method for connecting the passed receiver's slot to
          * the handlerChanged(bb::cascades::InvokeHandler*) signal with the default connection type set to
          * Qt::AutoConnection.Here's some related sample code:
          *
          * @code
          * InvokeActionItem *pInvokeActionItem = InvokeActionItem::create(InvokeQuery::create())
          *     .onHandlerChanged(this, SLOT(myOnHandlerChanged(bb::cascades::InvokeHandler*)));
          * @endcode
          *
          * @param receiver a non-@c null receiver object
          * @param method a non-@c null name of the slot in the receiver object to connect to
          *
          * @see BaseObject::TBuilder::connect()
          *
          * @since BlackBerry 10.0.0
          */
        BuilderType& onHandlerChanged(const QObject* receiver, const char *method) {
            if (strstr(method, "const ")) {
              this->connect(SIGNAL(handlerChanged(const bb::cascades::InvokeHandler*)), receiver, method);
            } else {
              this->connect(SIGNAL(handlerChanged(bb::cascades::InvokeHandler*)), receiver, method);
            }
            return this->builder();
        }
      };

      /*!
       * @brief A builder for constructing an @c InvokeActionItem.
       *
       * To retrieve the builder, call @c InvokeActionItem::create(InvokeQuery::create()).
       *
       * @since BlackBerry 10.0.0
       */
      class Builder : public TBuilder<Builder, ThisClass>
      {
      public:
        explicit Builder(bb::cascades::InvokeQuery* pQuery)
          : TBuilder<Builder, ThisClass>(new ThisClass(pQuery))
        {
        }
      };

    public:

      /*!
       * @brief Creates and returns a builder for constructing an @c %InvokeActionItem.
       *
       * Usage:
       * @code
       * InvokeActionItem* pInvokeActionItem(InvokeActionItem::create(
       *   InvokeQuery::create()
       *     .parent(this)
       *     .mimeType("text/txt")));
       * @endcode
       *
       * @param pQuery The non-@c 0 query to use in the invocation.
       *
       * @return A builder used for constructing an @c %InvokeActionItem.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create(bb::cascades::InvokeQuery* pQuery) {
         Q_ASSERT(pQuery);
         return Builder(pQuery);
      }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::InvokeActionItem)

#endif  // cascades_invokeactionitem_h
