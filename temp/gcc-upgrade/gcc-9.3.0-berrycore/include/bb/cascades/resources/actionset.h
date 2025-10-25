/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_actionset_h
#define cascades_actionset_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/resources/abstractactionitem.h>

namespace bb {
    namespace cascades {

    class ActionSetPrivate;

   /*!    
    * 
    * @brief Used to group a set of actions to be displayed in the Context Menu.
    *
    * The Context Menu is a menu that is displayed by pressing and holding a control. It
    * displays a set of actions that are relevant for that particular control.
    *
    * An example is an application showing a list of emails where the user can press and hold
    * a particular email to show the Context Menu. The menu could then typically show
    * actions such as "Reply", "Forward" and "Read".
    *
    * It is possible to specify several @c %ActionSet objects on the same control. Currently, 
    * only the first @c %ActionSet is used.
    *
    * Here is an example of how to specify @c %ActionSet objects, in QML:
    *
    * @code
    * ImageView {
    *     imageSource: "john.png"
    *     contextActions: [
    *         ActionSet {
    *             title: "Email"
    *             subtitle: "From: John Doe"
    *             ActionItem {title: "Reply"}
    *             ActionItem {title: "Forward"}
    *         },
    *         ActionSet {
    *             title: "Sender"
    *             ActionItem {title: "Call"}
    *             ActionItem {title: "Send SMS"}
    *         }
    *     ]
    * }
    * @endcode
    *
    * Here is an example of how to specify @c %ActionSet objects, in C++:
    *
    * @code
    * ImageView* imageView = ImageView::create("john.png");
    * ActionSet* actionSet = ActionSet::create()
    *            .title("Email")
    *            .subtitle("From: John Doe")
    *            .add(ActionItem::create().title("Reply"))
    *            .add(ActionItem::create().title("Forward"));
    * imageView->addActionSet(actionSet);
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
    class BBCASCADES_EXPORT ActionSet : public UIObject
    {
        Q_OBJECT
        
       /*!
        * @brief A list of actions that will be displayed in the Context Menu.
        *
        * Only one DeleteActionItem can be shown in the Context Menu. If more than one is added, 
        * only the first one is used and the rest are ignored. It is placed at a fixed position 
        * in the Context Menu along with the other actions.
        *
        * Only one MultiSelectActionItem can be shown in the Context Menu. If more than one is added, 
        * only the first one is used and the rest are ignored. The %MultiSelectActionItem is used 
        * to start a multiple selection session. It is placed at a fixed position in the 
        * Context Menu along with the other actions.
        *
        * @note Make sure the @c AbstractActionItem objects live long enough for the action to occur.
        * This is especially important if you work with just-in-time population of a Context %Menu.
        * A good place to clear the @c %ActionSet is just before adding items to it.
        * This way you are sure the objects are still available while they may be used.
        *
        * @xmlonly
        * <qml>
        * <property name="actions" listType="bb::cascades::AbstractActionItem" defaultProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractActionItem> actions READ actions FINAL)
        Q_CLASSINFO("DefaultProperty", "actions")
        
        /*!
         * @brief The title displayed in the Context Menu header.
         *
         * The Context Menu header is only displayed if either of the properties @c title or @c subtitle
         * are set. The default value is QString::Null, indicating no title is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)
       
        /*!
         * @brief The subtitle displayed in the Context Menu header, below the @c title.
         *
         * The Context Menu header is only displayed if either of the properties @c title or @c subtitle
         * are set. The default value is QString::Null, indicating no subtitle is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle RESET resetSubtitle NOTIFY subtitleChanged FINAL)

    public:

       /*!
        * @brief Constructs an @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        explicit ActionSet();
        
       /*!
        * @brief Destroys the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        virtual ~ActionSet();
        
       /*!
        * @brief Adds an action to the @c %ActionSet.
        *
        * @c %ActionSet takes ownership of the action, 
        * so actions cannot be shared. If action already belongs to the @c %ActionSet or 
        * actionItem is @c 0, nothing will happen. Once completed, the actionAdded()
        * signal is emitted.
        *
        * @param action The actionItem to add to the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void add(bb::cascades::AbstractActionItem* action);

       /*!
        * @brief Inserts an ActionItem at a specified index in the %ActionSet.
        *
        * @c %ActionSet takes ownership of the action, 
        * so actions cannot be shared. If action already belongs to the @c %ActionSet or 
        * action is @c 0, nothing will happen. If the action is currently belongs to
        * another @c %ActionSet, it is removed from that @c %ActionSet, and ownership 
        * is transferred to the new @c %ActionSet.
        * Once completed, the actionAdded() signal is emitted.
        *
        * @param index The index where the action will be placed. If index < 0 the
        * action is inserted as the first item. If index > the number
        * of items in the @c %ActionSet it is added as the last item.
        * @param action The AbstractActionItem to add to the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void insert(int index, bb::cascades::AbstractActionItem* action);

       /*!
        * @brief Returns the number of actions.
        *
        * @return The number of actions.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int count() const;

       /*!
        * @brief Returns the action at the specified index.
        *
        * Ownership of the action remains with the @c %ActionSet.
        *
        * @param index The index of the action.
        * @return The requested action if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::AbstractActionItem* at(int index) const;

       /*!
        * @brief Returns the index of an action.
        *
        * If the action does not belong to the @c %ActionSet 
        * or if the action is @c 0, @c -1 is returned.
        *
        * @param action The action to get the index of.
        * @return The index of the specified action if the action is valid, @c -1 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int indexOf(bb::cascades::AbstractActionItem* action) const;

       /*!
        * @brief Removes an action from the @c %ActionSet.
        *
        * Once the action is removed, the @c %ActionSet no longer references it, but it is still 
        * owned by the @c %ActionSet. It is up to the application to either delete the removed 
        * action, transfer its ownership (by setting its parent) to another object or leave 
        * it as a child of the @c %ActionSet (in which case it will be deleted with the @c %ActionSet).
        *
        * Once completed, the actionRemoved() signal is emitted.
        *
        * @param action The action to remove.
        * @return @c true if the action was owned by the @c %ActionSet, @c false otherwise.
        *
        * @see removeAll();
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bool remove(bb::cascades::AbstractActionItem* action);

       /*!
        * @brief Removes all actions from the @c %ActionSet and frees up their memory.
        *
        * Once completed, the actionRemoved() signal is emitted with @c 0 as its parameter.
        *
        * @see remove(bb::cascades::AbstractActionItem*);
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void removeAll();
        
       /*!
        * @brief Gets the title of the @c %ActionSet.
        *
        * @return The title of the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        QString title() const;

       /*!
        * @brief Sets the title on the @c %ActionSet.
        *
        * @param title The title of the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setTitle(const QString& title);

       /*!
        * @brief Resets the title on the @c %ActionSet to QString::Null.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetTitle();


       /*!
        * @brief Gets the subtitle of the @c %ActionSet.
        *
        * @return The subtitle of the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        QString subtitle() const;

       /*!
        * @brief Sets the subtitle on the @c %ActionSet.
        *
        * @param subtitle The subtitle of the @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setSubtitle(const QString& subtitle);

       /*!
        * @brief Resets the subtitle on the @c %ActionSet to QString::Null.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetSubtitle();

Q_SIGNALS:        

       /*!
        * @brief Emitted when an action has been added to the @c %ActionSet.
        *
        * @param action The action that has been added.
        *
        * @since BlackBerry 10.0.0
        */
        void actionAdded(bb::cascades::AbstractActionItem *action);

       /*!
        * @brief Emitted when an action has been removed from the @c %ActionSet.
        *        
        * @param action The action that has been removed. @c 0 if emitted by removeAll().
        *
        * @since BlackBerry 10.0.0
        */
        void actionRemoved(bb::cascades::AbstractActionItem *action);
       
       /*!
        * @brief Emitted when the title has changed.
        *
        * @param title The new title.
        *
        * @since BlackBerry 10.0.0
        */
        void titleChanged(const QString& title);

       /*!
        * @brief Emitted when the subtitle has changed.
        *
        * @param subtitle The new title.
        *
        * @since BlackBerry 10.0.0
        */
        void subtitleChanged(const QString& subtitle);

    private:
        /*! \cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::AbstractActionItem> actions();
        Q_DECLARE_PRIVATE(ActionSet)
        Q_DISABLE_COPY(ActionSet)
        /*! \endcond */
        
    public:
        /*! \cond PRIVATE */
        typedef ActionSet ThisClass; 
        typedef UIObject BaseClass;
        /*! \endcond */

       /*!
        * @brief A builder template for constructing a @c %ActionSet.
        *
        * See ActionSet::create() for getting a concrete builder for constructing a @c %ActionSet.
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
            * @brief Adds an action to the @c %ActionSet.
            *
            * @c %ActionSet takes ownership of the action, 
            * so actions cannot be shared. If action already belongs to the @c %ActionSet or 
            * actionItem is @c 0, nothing will happen.
            *
            * Using this convenience function in the builder pattern is the equivalent of the 
            * following:
            * @code
            * actionSet->add(action);
            * @endcode
            *
            * @param action The actionItem to add to the @c %ActionSet.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& add(AbstractActionItem *action)
            {
                this->instance().add(action);
                return this->builder();
            }

           /*!
            * @brief Sets the title on the @c %ActionSet.
            *
            * Using this convenience function in the builder pattern is the equivalent of the 
            * following:
            * @code
            * actionSet->setTitle("This is the title.");
            * @endcode
            *
            * @param title The subtitle of the @c %ActionSet.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& title(const QString & title)
            {
                this->instance().setTitle(title);
                return this->builder();
            }

           /*!
            * @brief Sets the subtitle on the @c %ActionSet.
            *
            * Using this convenience function in the builder pattern is the equivalent of the 
            * following:
            * @code
            * actionSet->setSubtitle("This is the subtitle.");
            * @endcode
            *
            * @param subtitle The subtitle of the @c %ActionSet.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& subtitle(const QString & subtitle)
            {
                this->instance().setSubtitle(subtitle);
                return this->builder();
            }          
        };

       /*!
        * @brief A concrete builder class for constructing a @c %ActionSet.
        * 
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, ActionSet>
        {
        public:
            explicit Builder() : TBuilder<Builder, ActionSet>(new ActionSet()) {}
        };

       /*!
        * @brief Creates and returns a builder for constructing an @c %ActionSet.
        *
        * Using the builder to create an action set:
        * @code
        * ActionSet* actionSet = ActionSet::create()
        *            .title("Email")
        *            .subtitle("From: John Doe")
        *            .add(ActionItem::create().title("Reply")
        *            .add(ActionItem::create().title("Forward");s
        * @endcode
        *
        * @return A Builder for constructing an @c %ActionSet.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create()
        {
            return Builder();
        }
    }; 
    
  }
}


#endif // cascades_actionset_h
