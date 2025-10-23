/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_multiselecthandler_h
#define cascades_multiselecthandler_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/resources/actionitem.h>

namespace bb {
    namespace cascades {

    class MultiSelectActionItem;
    class MultiSelectHandlerPrivate;
    class VisualNode;

   /*!
    * @brief A handler used during multiple selection to populate the Context Menu.
    *
    * The multi-select handler represents a multiple selection session involving the Context Menu.
    * Only one multi-select handler can be active at at time. The @c active property tells whether
    * the handler is active or not. Setting the @c active property to @c true will start multiple
    * selection with this handler and cancel any other handler that was active. During multiple 
    * selection the Context Menu is shown populated with the actions from the current handler. 
    *
    * The @c %MultiSelectHandler can be specified as an attached object in any control or specified in
    * the ListView as a multiSelectHandler property.
    *
    * There are some special cases where you will get a lot for free from the @c %MultiSelectHandler:
    *
    * If you add the @c %MultiSelectHandler to a ListView and that @c %MultiSelectHandler has the
    * multiSelectAction property set, the ListItems will automatically have a MultiSelectActionItem in
    * their context menu. If One of the ListItems have the multiSelectAction property set that
    * MultiSelectActionItem will override the one set in the @c %MultiSelectHandler, but just for that
    * specific ListItem type.
    *
    * If you have a MultiSelectActionItem connected to your @c %MultiSelectHandler that item will activate
    * the handler automatically. However, if you add a MultiSelectActionItem to a control, then you must connect 
    * the signals and activate the desired @c %MultiSelectHandler manually.
    *
    * @code
    * Container {
    *     background: Color.Black
    *
    *     attachedObjects: [
    *         MultiSelectHandler {
    *             id: theFirstSelectHandler
    *             actions: [
    *                  ActionItem { title: "Create Album" },
    *                  ActionItem { title: "Mark as read" },
    *                  ActionItem { title: "Mark as unread" },
    *                  DeleteActionItem { title: "Delete" }
    *             ]
    *
    *             status: "This is the status text"
    *
    *             onActiveChanged: {
    *                  console.log("First handler active!");
    *             }
    *             
    *             onCanceled: {
    *                  console.log("Multi selection canceled!");
    *             }
    *         }
    *     ]
    * }
    * @endcode
    *
    * @code
    * ListView {
    *     id: theListView
    *
    *     // This multi-select action will be placed inside the ActionSets of each 
    *     // list item that doesn't have a MultiSelectActionItem of its own.
    *     multiSelectAction: MultiSelectActionItem {}
    *
    *     multiSelectHandler {
    *         // These actions will be shown during multiple selection, while this 
    *         // multiSelectHandler is active
    *         actions: [
    *             ActionItem {title: "Multi-select action"},
    *             DeleteActionItem {}
    *         ]
    *
    *         status: "None selected"
    *
    *         onActiveChanged: {
    *             if (active == true) {
    *                 console.log("Multiple selection is activated");
    *             }
    *             else {
    *                 console.log("Multiple selection is deactivated");
    *             }
    *         }
    *
    *         onCanceled: {
    *             console.log("Multi selection canceled!");
    *         }
    *     }
    *
    *     listItemComponents: [
    *         ListItemComponent {
    *             id: friend
    *             // This MultiSelectActionItem set on the ListView will automatically show up here.
    *             ActionSet {
    *             }
    *         },
    *
    *         ListItemComponent {
    *             id: colleague
    *             // This MultiSelectActionItem set on the ListView will not show up here, since
    *             // it already has a MultiSelectActionItem in the ActionSet.
    *             ActionSet {
    *                 MultiSelectActionItem { title: "Special Select"}
    *             }
    *         }
    *     ]
    * }
    * @endcode
    *
    * Here is an example of multiple handlers. Since only one handler can be active at time,
    * activating one will deactivate the other and switch the content in the Context Menu.
    *
    * @code
    * Page {
    *   actions:  [
    *     MultiSelectActionItem { 
    *       multiSelectHandler: theFirstSelectHandler 
    *       onTriggered: {
    *         multiSelectHandler.active = true;
    *       }
    *     }
    *   ]
    *
    *   Container {
    *     background: Color.Black
    *
    *     attachedObjects: [
    *       MultiSelectHandler {
    *         id: theFirstSelectHandler
    *         actions: [
    *           ActionItem {
    *             title: "Create Album"
    *           },
    *           ActionItem {
    *             title: "Mark as read"
    *           },
    *           ActionItem {
    *             title: "Mark as unread"
    *           },
    *           DeleteActionItem { title: "Delete" }
    *         ]
    *
    *         status: "This is the status text"
    *       
    *         onActiveChanged: {
    *           console.log("First handler active!");
    *         }
    *
    *         onCanceled: {
    *             console.log("Multi selection canceled!");
    *         }
    *       },
    *       
    *       MultiSelectHandler {
    *         id: theSecondSelectHandler
    *         actions: [
    *           ActionItem {
    *             title: "Copy"
    *           },
    *           ActionItem {
    *             title: "Paste"
    *           },
    *           DeleteActionItem { title: "Delete" }
    *         ]
    *        
    *         status: "This is the status text"
    *        
    *         onActiveChanged: {
    *           console.log("Second handler active!");
    *         }
    *
    *         onCanceled: {
    *             console.log("Multi selection canceled!");
    *         }
    *       }  
    *     ]  
    *   }  
    * } 
    * @endcode
    *
    * @xmlonly
    * <qml>
    * <class register="yes"/>
    * </qml>
    * @endxmlonly
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT MultiSelectHandler : public UIObject
    {
        Q_OBJECT

       /*!
        * @brief Indicates whether the handler is activated for multiple selection.
        *
        * When a multi-select handler is active, the Context Menu is shown for multiple selection and it
        * is populated using the content of the active handler. Only one multi-select handler can be active 
        * at at time, so activating one handler will deactivate any previously active handler. 
        * 
        * The default value is @c false, indicating that the handler is not active.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool active READ isActive WRITE setActive RESET resetActive NOTIFY activeChanged FINAL)

       /*!
        * @brief Actions to display during multiple selection when the handler is active.
        *
        * These actions are displayed in the Context Menu during multiple selection when the
        * multi-select handler is active.
        *
        * Only one DeleteActionItem can be shown in the Context Menu. If more than one is added, 
        * only the first one is used and the rest are ignored. It is placed at a fixed position 
        * in the Context Menu along with the other actions.
        *
        *
        * @xmlonly
        * <qml>
        * <property name="actions" listType="bb::cascades::AbstractActionItem"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractActionItem> actions READ actions FINAL)


       /*!
        * @brief The status text to show during multiple selection.
        *
        * The selection status text is shown on the Action Bar at a fixed position 
        * during  multiple selection when this handler is active.
        * According to general guidelines this should be a short sentence telling
        * how many items are selected, e.g. "3 emails selected".
        * 
        * The default value is @c QString::null, indicating no status text is shown.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QString status READ status WRITE setStatus RESET resetStatus NOTIFY statusChanged FINAL)

       /*! \cond PRIVATE */
       /*!
        * @brief Decides if input events should reach the focused control while the multi-select handler is active,
        *        even if the context menu is shown.
        *
        * When a multi-select handler is active, the context menu is shown. Normally input events (e.g. key events)
        * will always go to the context menu when it is showing. Setting @c inputAllowed to @c true will make the input events
        * go to the focused control even if the context menu is showing.
        *
        * The default value is @c false.
        *
        * Example use case:
        * The application has a list with a search field that should be usable (requires key input) while in multi select mode.
        *
        * @since BlackBerry 10.2.0
        */
        Q_PROPERTY(bool inputAllowed READ isInputAllowed WRITE setInputAllowed RESET resetInputAllowed NOTIFY inputAllowedChanged FINAL)
        /*! \endcond */

    public:

       /*!
        * @brief Constructs a @c %MultiSelectHandler.
        *
        * @since BlackBerry 10.0.0
        */
        explicit MultiSelectHandler(VisualNode* parent = 0);
        
       /*!
        * @brief Destroys the @c %MultiSelectHandler.
        *
        * @since BlackBerry 10.0.0
        */
        virtual ~MultiSelectHandler();
        
       /*!
        * @brief Returns whether the multi-select handler is currently active.
        *
        * @return @c true if the handler is active, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isActive() const;

       /*!
        * @brief Activates or deactivates the multi-select handler.
        *
        * @param active If @c true the handler will be activated for multiple selection, and if @c false the handler will deactivated.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setActive(bool active);

       /*!
        * @brief Deactivates the multi-select handler.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetActive();
        
       /*!
        * @brief Returns the number of added actions.
        *
        * @see actionAt()
        *
        * @return The number of actions.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int actionCount() const;

       /*!
        * @brief Returns a action at the specified index.
        *
        * The ownership of the action remains with the handler.
        * @see actionCount()
        *
        * @param index The index of the action.
        * @return The requested action if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::AbstractActionItem* actionAt(int index) const;

       /*!
        * @brief Adds an action to show during multiple selection.
        *
        * The actions are shown in the Context Menu during multiple selection when this
        * handler is active.
        *
        * The multi-select handler takes ownership of the action, so actions cannot be 
        * shared. If the action already has a parent or if it is @c 0, nothing will happen.
        * Once completed, the actionAdded() signal is emitted.
        *
        * @see removeAction(), removeAllAction()
        *
        * @param action The action to add.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void addAction(bb::cascades::AbstractActionItem* action);

        /*!
        * @brief Removes a previously added action.
        *
        * Once the action is removed, the handler no longer references it, but it is still 
        * owned by the handler. It is up to the application to either delete the removed 
        * action, transfer its ownership (by setting its parent) to another object or leave 
        * it as a child of the handler (in which case it will be deleted with the handler).
        *
        * Once completed, the actionRemoved() signal is emitted.
        *
        * @see addAction(), removeAllActions()
        *
        * @param action The actionItem to remove.
        * @return @c true if the action was owned by the @c %MultiSelectHandler, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bool removeAction(bb::cascades::AbstractActionItem* action);

       /*!
        * @brief Removes and deletes all the added actions.
        *
        * Once completed, the actionRemoved() signal is emitted with @c 0 as its parameter.
        *
        * @see addAction(), removeAction()
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void removeAllActions();


       /*!
        * @brief Returns the status text set for this handler.
        *
        * @return The status text set for this handler, or @c QString::null of no text was set.
        *
        * @since BlackBerry 10.0.0
        */
        QString status() const;

       /*!
        * @brief Sets the status text to show during multiple selection.
        *
        * The selection status text is shown on the Action Bar at a fixed position 
        * during  multiple selection when this handler is active.
        * According to general guidelines this should be a short sentence telling
        * how many items are selected, e.g. "3 emails selected".
        *
        * Once completed, the statusChanged() is emitted with the new text.
        *
        * \param status The new status text for this list item.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setStatus(const QString& status);

       /*!
        * @brief Removes the status text by setting it to String::null.
        *
        * Once completed, the statusChanged() is emitted with @c String::null.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetStatus();

       /*! \cond PRIVATE */
       /*!
        * @brief Returns whether input is allowed when the multi-select handler is active and the context menu is showing.
        *
        * @return @c true if input is allowed when the context menu is showing, @c false otherwise.
        *
        * @since BlackBerry 10.2.0
        */
        bool isInputAllowed() const;

       /*!
        * @brief Sets wether input is allowed when the multi-select handler is active and the context menu is showing.
        *
        * @param inputAllowed @c true if input should be allowed when the multi-select handler is active and the context menu is showing, @c false otherwise.
        *
        * @since BlackBerry 10.2.0
        */
        Q_SLOT void setInputAllowed(bool inputAllowed);

       /*!
        * @brief Resets inputAllowed to the default value of @c false.
        *
        * @since BlackBerry 10.2.0
        */
        Q_SLOT void resetInputAllowed();
        /*! \endcond */

Q_SIGNALS:

       /*!
        * @brief Emitted when the multi-select handler is activated or deactivated.
        *
        * @param active If @c true the handler was activated for multiple selection, and if @c false the handler was deactivated.
        *
        * @since BlackBerry 10.0.0
        */
        void activeChanged(bool active);

       /*!
        * @brief Emitted when an action has been added to the @c %MultiSelectHandler.
        *
        * @param action The action that has been added.
        *
        * @since BlackBerry 10.0.0
        */
        void actionAdded(bb::cascades::AbstractActionItem *action);

       /*!
        * @brief Emitted when an action has been removed from the @c %MultiSelectHandler.
        *        
        * @param action The action that has been removed. @c 0 if emitted by removeAll().
        *
        * @since BlackBerry 10.0.0
        */
        void actionRemoved(bb::cascades::AbstractActionItem *action);

       /*!
        * @brief Emitted when the status text is changed or removed.
        *
        * @param status The new status text or @c QString::null if it was removed.
        *
        * @since BlackBerry 10.0.0
        */
        void statusChanged(const QString& status);
        
        /*!
        * @brief Emitted when the multi select is canceled.
         *
         * @since BlackBerry 10.0.0
        */
        void canceled();

        /*! \cond PRIVATE */
        /*!
         * @brief Emitted when the inputAllowed property is changed.
         *
         * @param inputAllowed The new value of the property.
         *
         * @since BlackBerry 10.2.0
         */
        void inputAllowedChanged(bool inputAllowed);
        /*! \endcond */

    private:
        /*! \cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::AbstractActionItem> actions();
        Q_DECLARE_PRIVATE(MultiSelectHandler)
        Q_DISABLE_COPY(MultiSelectHandler)
        /*! \endcond */
        
    public:
        /*! \cond PRIVATE */
        typedef MultiSelectHandler ThisClass; 
        typedef UIObject BaseClass;
        /*! \endcond */

       /*!
        * @brief A builder template for constructing a @c %MultiSelectHandler.
        *
        * See MultiSelectHandler::create() for getting a concrete builder for constructing a @c %MultiSelectHandler.
        *
        * @since BlackBerry 10.0.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> 
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        
        public:
           /*!
            * @brief Adds an action to show during multiple selection.
            *
            * The actions are shown in the Context Menu during multiple selection when this
            * handler is active.
            *
            * The multi-select handler takes ownership of the action, so actions cannot be 
            * shared. If the action already has a parent or if it is @c 0, nothing will happen.
            *
            * Using this convenience function in the builder pattern is the equivalent of the 
            * following:
            * @code
            * myHandler->addAction(action);
            * @endcode
            *
            * @param action The action to add.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& addAction(AbstractActionItem *action)
            {
                this->instance().addAction(action);
                return this->builder();
            }

           /*!
            * @brief Sets the status text to show during multiple selection.
            *
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myHandler->setStatus("3 emails selected");
            * @endcode
            *
            * @param status The status text to set.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& status(const QString& status)
            {
                this->instance().setStatus(status);
                return this->builder();
            }

           /*! \cond PRIVATE */
           /*!
            * @copydoc bb::cascades::MultiSelectHandler::setInputAllowed(bool)
            */
            BuilderType& inputAllowed(bool inputAllowed)
            {
                this->instance().setInputAllowed(inputAllowed);
                return this->builder();
            }
           /*! \endcond */
        };

       /*!
        * @brief A concrete builder class for constructing a @c %MultiSelectHandler.
        *
        * @since BlackBerry 10.0.0
        * 
        */
        class Builder : public TBuilder<Builder, MultiSelectHandler>
        {
        public:
            explicit Builder(VisualNode* target) : TBuilder<Builder, MultiSelectHandler>(new MultiSelectHandler(target)) {}
        };

       /*!
        * @brief Creates and returns a builder for constructing an @c %MultiSelectHandler.
        *
        * Using the builder to create a multi-select handler:
        * @code
        * Container* targetContainer = Container::create()
        * MultiSelectHandler* handler = MultiSelectHandler::create(targetContainer)
        *            .addAction(ActionItem::create().title("Reply")
        *            .addAction(ActionItem::create().title("Forward");
        * @endcode
        *
        * The user needs to specify what VisualNode this @c %MultiSelectHandler will target,
        * this is done automatically if you use QML but must be provided if it is created
        * in C++. The target parameter is allowed to be 0 but then the @c %MultiSelectHandler
        * will do nothing.
        *
        * @return A Builder for constructing an @c %MultiSelectHandler.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create(VisualNode* target)
        {
            return Builder(target);
        }
    }; 
    
  }
}


QML_DECLARE_TYPE(bb::cascades::MultiSelectHandler)


#endif // cascades_multiselecthandler_h
