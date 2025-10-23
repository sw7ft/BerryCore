/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_invocation_h
#define cascades_invocation_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/BaseObject>
#include <QtCore/QString>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {
    class InvocationPrivate;
    class InvokeQuery;

    /*!
     * @brief Represents an invocation which can be triggered from program code.
     * The @c %Invocation class represents an invocation that can be
     * made. The triggering of a particular action is specified by the
     * application.
     * If the action exists, and if one target exists the action is
     * invoked for that target.
     * If the action exists and multiple targets exist a target list
     * is presented to the user, so that the user can select a
     * valid target.
     * If the action does not exist, an error is logged in the debug
     * output.
     *
     * The @c %Invocation class uses @c InvokeQuery to represent a query.
     *
     * Here's how to create an @c %Invocation and set it off, using the builder
     * pattern:
     *
     * @code
     * // Declare an Invocation* called m_pInvocation somewhere.
     *
     * void onClicked() {
     *   m_pInvocation = Invocation::create(
     *     InvokeQuery::create()
     *       .parent(this)
     *       .mimeType("text/plain"));
     *   QObject::connect(m_pInvocation, SIGNAL(armed()),
     *     this, SLOT(onArmed()));
     *   QObject::connect(m_pInvocation, SIGNAL(finished()),
     *     this, SLOT(onFinished()));
     * }
     *
     * void onArmed() {
     *   m_pInvocation->trigger("bb.action.OPEN");
     * }
     *
     * void onFinished() {
     *  m_pInvocation->deleteLater();
     * }
     * @endcode
     *
     * And here's how to create an @c %Invocation, triggered by the click of a
     * button, using QML:
     *
     * @code
     * Button {
     *     attachedObjects: [
     *         Invocation {
     *             id: invoke
     *             query {
     *                 mimeType: "text/plain"
     *                 data: "+4640999999"
     *             }
     *         }
     *     ]
     *
     *   onClicked: {
     *     invoke.trigger("bb.action.OPEN")
     *   }
     * }
     * @endcode
     *
     * @xmlonly
     * <qml>
     * <class abstract="no"/>
     * </qml>
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Invocation : public BaseObject
    {
      Q_OBJECT

      /*!
       * @brief The query used by the @c %Invocation.
       *
       * Once this @c %Invocation has been created, this property becomes
       * read-only and attempts to change it will be ignored.
       *
       * @xmlonly
       * <qml>
       * <property groupedProperty="yes" writable="no"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(bb::cascades::InvokeQuery* query READ queryQml WRITE setQuery FINAL)

    public:
      /*!
       * @brief Destroys this @c %Invocation.
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~Invocation();

      /*!
       * @brief Triggers this invocation.
       *
       * If the @c #armed signal has not been emitted yet or there is no action
       * matching the provided ID, the invocation will not trigger.
       *
       * If there are several possible targets for the triggered invocation they
       * will be presented to the user in a list.
       *
       * @param invokeActionId The ID of the action to perform the invocation
       * for.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void trigger(const QString& invokeActionId);

      /*!
       * @brief Gets the query used by this @c %Invocation.
       *
       * The caller takes ownership of the returned pointer.
       *
       * @return The query of this @c %Invocation.
       *
       * @since BlackBerry 10.0.0
       */
      bb::cascades::InvokeQuery* query();

    Q_SIGNALS:
      /*!
       * @brief Emitted when it is possible to trigger the invocation.
       *
       * @since BlackBerry 10.0.0
       */
      void armed();

      /*!
       * @brief Emitted when the invocation is finished.
       *
       * The invocation has been finished somehow and the @c %Invocation
       * object can safely be deleted.
       *
       * @since BlackBerry 10.0.0
       */
       void finished();

    protected:
      /*! @cond PRIVATE */
      explicit Invocation(QObject* const pParent=0);
      /*! @endcond */

    private:
      /*! @cond PRIVATE */

      /*!
       * @brief Return a InvokeQuery object to QML and giving JavaScript ownership.
       *
       * @return The current InvokeQuery parameters in use.
       */
      bb::cascades::InvokeQuery* queryQml() const;

      /*!
       * @brief Sets the query for this @c %Invocation.
       *
       * Ownership of the @c InvokeQuery object remains
       * unchanged.
       *
       * @param pQuery The new query for this @c %Invocation.
       */
      void setQuery(const bb::cascades::InvokeQuery* const pQuery);

      Q_DECLARE_PRIVATE(Invocation)
      Q_DISABLE_COPY(Invocation)

      typedef Invocation ThisClass;
      typedef BaseObject BaseClass;
      /*! @endcond */

      /*!
       * @brief A builder template for constructing an @c Invocation.
       *
       * To retrieve the builder, call @c Invocation::create().
       *
       * @tparam BuilderType The type of the concrete builder of the most derived type.
       * @tparam BuiltType The type of object built by this builder.
       *
       * @since BlackBerry 10.0.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
      {
      protected:
        /*!
         * @brief Creates a new builder constructing an @c Invocation.
         *
         * @param node The instance of @c Invocation to build.
         * @param pQuery The query to use in the invocation.
         *
         * @since BlackBerry 10.0.0
         */
        TBuilder(BuiltType* node, const bb::cascades::InvokeQuery* const pQuery)
          : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {
          this->instance().setQuery(pQuery);
        }

     public:

       /*!
        * A convenience method for connecting the passed receiver's slot to
        * the armed() signal with the default connection type set to
        * Qt::AutoConnection.Here's some related sample code:
        *
        * @code
        * Invocation* pInvocation = Invocation::create()
        *     .onArmed(this, SLOT(onArmedHandler()));
        * @endcode
        *
        * @param receiver a non-@c null receiver object
        * @param method a non-null name of the slot in the receiver object to connect to
        *
        * @see BaseObject::TBuilder::connect()
        *
        * @since BlackBerry 10.0.0
        */
    BuilderType& onArmed(const QObject* receiver, const char *method) {
        this->connect(SIGNAL(armed()), receiver, method);
        return this->builder();
    }

    /*!
        * A convenience method for connecting the passed receiver's slot to
        * the finished() signal with the default connection type set to
        * Qt::AutoConnection.Here's some related sample code:
        *
        * @code
        * Invocation* pInvocation = Invocation::create()
        *     .onFinished(this, SLOT(onFinishedHandler()));
        * @endcode
        *
        * @param receiver a non-@c null receiver object
        * @param method a non-null name of the slot in the receiver object to connect to
        *
        * @see BaseObject::TBuilder::connect()
        *
        * @since BlackBerry 10.0.0
        */
    BuilderType& onFinished(const QObject* receiver, const char *method) {
        this->connect(SIGNAL(finished()), receiver, method);
        return this->builder();
    }
      };

      /*!
       * @brief A builder for constructing an @c Invocation.
       *
       * To retrieve the builder, call @c Invocation::create().
       *
       * @since BlackBerry 10.0.0
       */
      class Builder : public TBuilder<Builder, ThisClass>
      {
      public:
        explicit Builder(const bb::cascades::InvokeQuery* const pQuery)
          : TBuilder<Builder, ThisClass>(new ThisClass(), pQuery) {
        }
      };

    public:
      /*!
       * @brief Creates and returns a builder for constructing an @c %Invocation.
       *
       * Usage:
       * @code
       * Invocation* pInvocation(Invocation::create(
       *   InvokeQuery::create()
       *     .parent(this)
       *     .mimeType("text/plain")));
       * @endcode
       *
       * @param pQuery The query to use in the invocation.
       *
       * @return A builder used for constructing an @c %Invocation.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create(const bb::cascades::InvokeQuery* const pQuery) {
        return Builder(pQuery);
      }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::Invocation)

#endif  // cascades_invocation_h
