/*!
 * @copyright
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_contextmenuhandler_h
#define cascades_contextmenuhandler_h

#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/contextmenuvisualstate.h>

namespace bb {
    namespace cascades {

    class ContextMenuHandlerPrivate;
    class ContextMenuShowingEvent;

    /*!
     * @brief A handler for communicating with the Context menu.
     *
     * Example of how to connect a context menu handler to a visual node:
     *
     * @code
     * ImageView* myControl = ImageView::create();
     *
     * ContextMenuHandler *contextMenuHandler = ContextMenuHandler::create()
     *     .onPopulating(myControl,
     *         SLOT(myPopulating(bb::cascades::ContextMenuShowingEvent*)))
     *     .onVisualStateChanged(myControl,
     *         SLOT(myVisualStateChanged(bb::cascades::ContextMenuVisualState::Type)));
     *
     * myControl->setContextMenuHandler(contextMenuHandler);
     * @endcode
     *
     *
     * An example in QML:
     *
     * @code
     * ImageView {
     *     contextMenuHandler: ContextMenuHandler {
     *         id: myHandler
     *         onPopulating: {
     *             // Abort the showing of the context menu if the user long-pressed
     *             // in the top left corner
     *             if (event.touchX < 100 && event.touchY < 100) {
     *                 event.abort();
     *             }
     *         }
     *         onDepopulated: {
     *             // Remove actions, or do something with the action set.
     *         }
     *         onVisualStateChanged: {
     *             if (ContextMenuVisualState.VisibleCompact == myHandler.visualState) {
     *                 hideSomethingInMyUi();
     *             }
     *             else if (ContextMenuVisualState.Hidden == myHandler.visualState) {
     *                 showSomethingInMyUi();
     *             }
     *         }
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     *     <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ContextMenuHandler : public UIObject
    {
        Q_OBJECT

       /*!
        * @brief The current visual state of the context menu.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ContextMenuVisualState::Type visualState READ visualState
                   NOTIFY visualStateChanged FINAL)

    public:

      /*!
       * @brief Creates a @c %ContextMenuHandler.
       *
       * @param parent The object that will own the created handler. This parameter is optional.
       *
       * @since BlackBerry 10.0.0
       */
      explicit ContextMenuHandler(UIObject* parent = 0);

      /*!
       * @brief Destructs the @c %ContextMenuHandler.
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~ContextMenuHandler();

      /*!
       * @brief Returns the current visual state of the context menu.
       *
       * @return The current visual state of the context menu.
       *
       * @since BlackBerry 10.0.0
       */
       bb::cascades::ContextMenuVisualState::Type visualState() const;

      /*!
       * @brief Closes the context menu.
       *
       * @details Forcibly closes the context menu in the current context menu scope.
       * Dialog and Sheet have their own context menu scope.
       * This function will close the menu regardless of what state it is in. Even
       * if it is in MultiSelect mode.
       *
       * Normally, the user should be the one deciding when to close the menu. Only in cases
       * where the user can't make that decision should this function be used.
       *
       * @since BlackBerry 10.2.0
       */
       Q_REVISION(2)
       Q_SLOT void closeMenu();

    Q_SIGNALS:

      /*!
       * @brief Emitted when the ContextMenu is ready to start populating for the target control.
       *
       * @details This signal is emitted synchronously. During the signal call, the application has a chance
       * to update the @c %ActionSet of the target control before the menu is shown.
       * The target control is typically the control for which this @c %ContextMenuHandler
       * is set as the @c Control::contextMenuHandler property.
       *
       * No context actions are shown in the Context Menu until this call returns. However, if this call
       * takes too long to return, the Context Menu will appear without any items, indicating that the
       * items are being loaded. Action items from @c Control::contextActions will be added to the
       * menu as soon as this call returns.
       *
       * Calling @c ContextMenuShowingEvent::abort() will abort the showing of the Context Menu.
       *
       * @see Control::contextMenuHandler, Control::contextActions, ContextMenuShowingEvent::abort()
       *
       * @param event The showing event.
       *
       * @since BlackBerry 10.0.0
       */
      void populating(bb::cascades::ContextMenuShowingEvent *event);

      /*!
       * @brief Emitted when the ContextMenu no longer needs the @c ActionSet.
       *
       * @details This signal will help developers know when it is safe to remove actions
       * or the ActionSet without having the change reflected in an open context menu.
       * The signal populating will always be followed by a depopulated before
       * populating is emitted again.
       *
       * @see Control::contextMenuHandler, Control::contextActions
       *
       * @since BlackBerry 10.3.1
       */
      Q_REVISION(4)
      void depopulated();

      /*!
       * @brief Emitted when the @c #visualState property changed.
       *
       * @note Due to a work around for a Qt Core issue with accessing enums from QML,
       * the argument of this signal doesn't follow naming convention for signals in
       * which the signal arguments are typically named to match the associated property's name.
       * Use the object's @c visualState property to access the current property value instead of
       * the signal argument to avoid runtime errors.
       *
       * For example, use @c visualState instead of @c newVisualState.
       *
       * @param newVisualState The new value of the @c #visualState property.
       *
       * @since BlackBerry 10.0.0
       */
      void visualStateChanged(bb::cascades::ContextMenuVisualState::Type newVisualState);

      /*!
       * @brief Emitted when the context menu is about to be shown for the target control.
       *
       * @details This signal is emitted synchronously. During the signal call, the application has a chance
       * to update the @c %ActionSet of the target control before the menu is shown.
       * The target control is typically the control for which this @c %ContextMenuHandler
       * is set as the @c Control::contextMenuHandler property.
       *
       * No context actions are shown in the Context Menu until this call returns. However, if this call
       * takes too long to return the Context Menu will appear without any items, indicating that the
       * items are being loaded. Action items from @c Control::contextActions will be added the
       * menu as soon as this call returns.
       *
       * Calling @c ContextMenuShowingEvent::abort() will abort the showing of the Context Menu.
       *
       * @see Control::contextMenuHandler, Control::contextActions, ContextMenuShowingEvent::abort()
       *
       * @param event The showing event.
       *
       * @deprecated Use @c ContextMenuHandler.populating or @c contextMenuHandler.visualState instead.
       *
       * @since BlackBerry 10.0.0
       */
      void showing(bb::cascades::ContextMenuShowingEvent *event);

      /*!
       * @brief Emitted when the Context menu is about to be hidden for the target control.
       *
       * This signal will be emitted when the Context menu starts to hide.
       *
       * This signal will not be emitted if @c ContextMenuShowingEvent::abort() was called to abort
       * showing the Context menu.
       *
       * @see Control::contextMenuHandler, Control::contextActions, ContextMenuShowingEvent::abort()
       *
       * @deprecated Use @c ContextMenuHandler.visualState instead
       *
       * @since BlackBerry 10.0.0
       */
      void hiding();

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ContextMenuHandler)
        Q_DISABLE_COPY(ContextMenuHandler)
        /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef UIObject BaseClass;
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a handler.
         *
         * To create the builder, call @c ContextMenuHandler::create().
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
             * @brief Connects the populating() signal to a slot.
             *
             * @details A convenience method for connecting the slot of receiver object,
             * that is passed in as a parameter, to the handler's @c populating() signal
             * with the default connection type @c Qt::AutoConnection.
             *
             * Example connecting @c myPopulating() slot in @c myObject to the handler's
             * @c populating() signal:
             * @code
             * ContextMenuHandler *contextMenuHandler = ContextMenuHandler::create()
             *     .onPopulating(myObject, SLOT(myPopulating(bb::cascades::ContextMenuShowingEvent*)));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method   The name of the slot to connect to in the receiver object.
             *                 This object cannot be @c null.
             *
             * @see showing(), QObject::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onPopulating(const QObject* receiver, const char *method) {
                bool res = QObject::connect(&this->instance(), SIGNAL(populating(bb::cascades::ContextMenuShowingEvent*)), receiver, method);
                Q_ASSERT(res);
                Q_UNUSED(res);
                return this->builder();
            }

            /*!
             * @brief Connects the @c depopulated() signal to a slot.
             *
             * @details A convenience method for connecting the slot of receiver object,
             * that is passed in as a parameter, to the handler's @c depopulated() signal
             * with the default connection type @c Qt::AutoConnection.
             *
             * Example connecting @c myDepopulated() slot in @c myObject to the handler's
             * @c depopulated() signal:
             * @code
             * ContextMenuHandler *contextMenuHandler = ContextMenuHandler::create()
             *     .onDepopulated(myObject, SLOT(myDepopulated(bb::cascades::ContextMenuShowingEvent*)));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method   The name of the slot to connect to in the receiver object.
             *                 This object cannot be @c null.
             *
             * @see showing(), QObject::connect()
             *
             * @since BlackBerry 10.3.1
             */
            BuilderType& onDepopulated(const QObject* receiver, const char *method) {
                bool res = QObject::connect(&this->instance(), SIGNAL(depopulated()), receiver, method);
                Q_ASSERT(res);
                Q_UNUSED(res);
                return this->builder();
            }

            /*!
             * @brief Connects a the @c visualStateChanged() signal to a slot.
             *
             * @details A convenience method for connecting the slot of the receiver object,
             * that's passed in as a parameter, to the handler's @c visualStateChanged() signal
             * with the default connection type @c Qt::AutoConnection.
             *
             * Example connecting @c myVisualStateChanged() slot in @c myObject to the handler's
             * @c visualStateChanged() signal:
             * @code
             * ContextMenuHandler *contextMenuHandler = ContextMenuHandler::create()
             *     .onVisualStateChanged(myObject, SLOT(myVisualStateChanged(bb::cascades::ContextMenuVisualState::Type)));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method   The name of the slot to connect to in the receiver object.
             *                 This object cannot be @c null.
             *
             * @see hiding(), QObject::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onVisualStateChanged(const QObject* receiver, const char *method) {
                bool res = QObject::connect(&this->instance(), SIGNAL(visualStateChanged(bb::cascades::ContextMenuVisualState::Type)), receiver, method);
                Q_ASSERT(res);
                Q_UNUSED(res);
                return this->builder();
            }

            /*!
             * @brief Connects a the showing() signal to a slot.
             *
             * @details A convenience method for connecting the slot of the receiver object,
             * that's passed in as a paramter, to the handler's @c showing() signal with the
             * default connection type @c Qt::AutoConnection.
             *
             * Example connecting @c myShowing() slot in @c myObject to the handler's
             * @c showing() signal:
             * @code
             * ContextMenuHandler *contextMenuHandler = ContextMenuHandler::create()
             *     .onShowing(myObject, SLOT(myShowing(bb::cascades::ContextMenuShowingEvent*)));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see showing(), QObject::connect()
             *
             * @deprecated Use ContextMenuHandler.visualState instead or ContextMenuHandler.populating
             */
            BuilderType& onShowing(const QObject* receiver, const char *method) {
                bool res = QObject::connect(&this->instance(), SIGNAL(showing(bb::cascades::ContextMenuShowingEvent*)), receiver, method);
                Q_ASSERT(res);
                Q_UNUSED(res);
                return this->builder();
            }

            /*!
             * @brief Connects a the hiding() signal to a slot.
             *
             * A convenience method for connecting passed receiver object's slot to
             * the handler's hiding() signal with the default connection type
             * Qt::AutoConnection.
             *
             * Example connecting myHiding() slot in myObject to the handler's
             * hiding() signal:
             * @code
             * ContextMenuHandler *contextMenuHandler = ContextMenuHandler::create()
             *     .onHiding(myObject, SLOT(myHiding()));
             * @endcode
             *
             * @param receiver A receiver object. This object cannot be @c null.
             * @param method   The name of the slot to connect to in the receiver object.
             *                 This object cannot be @c null.
             *
             * @see hiding(), QObject::connect()
             *
             * @deprecated Use ContextMenuHandler.visualState instead.
             */
            BuilderType& onHiding(const QObject* receiver, const char *method) {
                bool res = QObject::connect(&this->instance(), SIGNAL(hiding()), receiver, method);
                Q_ASSERT(res);
                Q_UNUSED(res);
                return this->builder();
            }
        };

        /*!
         * @brief A @c builder that constructs a @c ContextMenuHandler.
         *
         * To retrieve the @c builder, call @c ContextMenuHandler::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ContextMenuHandler> {
        public:
            explicit Builder() : TBuilder<Builder, ContextMenuHandler>(new ContextMenuHandler()) {}
        };

        /*!
         * @brief Creates and returns a @c builder for constructing a @c ContextMenuHandler.
         *
         * Example of how to use the @c builder to create a @c %ContextMenuHandler:
         * @code
         * ContextMenuHandler *pContextMenuHandler = ContextMenuHandler::create();
         * @endcode
         *
         * @return A @c Builder used to construct a @c ContextMenuHandler.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::ContextMenuHandler)

#endif /* cascades_contextmenuhandler_h */
