/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_menu_h
#define cascades_menu_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

        class ActionItem;
        class HelpActionItem;
        class SettingsActionItem;
        class MenuPrivate;

       /*! 
        * @brief A menu that contains important application-wide actions.
        * 
        * @details A @c Menu is positioned at the top of the screen and can be accessed by swiping downwards
        * from the top of the screen. It is typically used to display seldom-used actions such as Help or Settings that
        * are global (that is, apply from anywhere in the application).
        *
        * Example of C++ usage:
        * @code
        * Menu *menu = Menu::create()
        *     .addAction(ActionItem::create().title("Menu Item 1"))
        *     .addAction(ActionItem::create().title("Menu Item 2"))
        *     .help(HelpActionItem::create());
        * Application::instance()->setMenu(menu);
        * @endcode
        *
        * Example of QML usage:
        * @code
        * Page {
        *   Menu.definition: MenuDefinition {
        *     settingsAction: SettingsActionItem {
        *       onTriggered : {}
        *     }
        *     actions: [
        *       ActionItem {}
        *     ]
        *   }
        * }
        * @endcode
        *
        * @xmlonly
        * <qml>
        *     <class register="yes" name="MenuDefinition"/>
        * </qml>
        *     <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT Menu : public UIObject {
        private:
            Q_OBJECT
   
           /*!
            * @brief Specifies the actions that will be shown on the application menu.
            * 
            * @details A maximum of five actions can be shown at the same time, including the @c helpAction
            * and @c settingAction actions. If these actions are set, only three additional actions
            * can be displayed.
            *
            * @xmlonly
            * <qml>
            *     <property name="actions" listType="bb::cascades::ActionItem"/>
            * </qml>
            * @endxmlonly
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(QDeclarativeListProperty<bb::cascades::ActionItem> actions READ actions FINAL)
    
           /*!
            * @brief Specifies the Help action item.
            * 
            * @details The @c Help action is placed in a specific location, and if an image isn't
            * specified on the action, a default icon is shown.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bb::cascades::HelpActionItem* helpAction READ helpAction WRITE setHelpAction 
                       RESET resetHelpAction NOTIFY helpActionChanged FINAL);
              
           /*!
            * @brief Specifies the Settings action item.
            * 
            * @details The @c Settings action is placed in a specific location, and if an image isn't
            * specified on the action, a default icon is shown.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bb::cascades::SettingsActionItem* settingsAction READ settingsAction WRITE setSettingsAction 
                       RESET resetSettingsAction NOTIFY settingsActionChanged FINAL);

        public:
            
           /*!
            * @brief Creates the @c Menu.
            *
            * @since BlackBerry 10.0.0
            */
            explicit Menu(QObject* parent = 0);
            
           /*!
            * @brief Destroys this @c Menu.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~Menu();
 
           /*!
            * @brief Adds an action to this @c Menu.
            * 
            * @details This @c %Menu will always take ownership of the specified action, because actions should
            * not be shared.
            * If the specified action already belongs to this @c %Menu, or is @c 0, then nothing will happen.
            * The @c actionAdded() signal is emitted, when the operation is successful.
            * The order in which actions are added determines how they appear on the @c %Menu. If there are no 
            * help or settings actions new actions will be placed those locations first. The rest of the actions will be
            * placed together from left to right in the order they were added.
            *
            * @param actionItem The action to add to the @c %Menu.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void addAction(bb::cascades::ActionItem* actionItem);
            
           /*!
            * @brief Removes an action from this @c %Menu.
            * 
            * @details Once the action is removed, the @c %Menu no longer references it, but it is still 
            * owned by the @c %Menu. It is up to the application to either delete the removed 
            * action, transfer its ownership (by setting its parent) to another object, or leave 
            * it as a child of the @c %Menu, in which case it will be deleted with the @c %Menu.
            *
            * If the operation was successful, the @c actionRemoved() signal is emitted.
            *
            * @param actionItem The action to remove.
            * 
            * @return @c true if the action was owned by this @c %Menu, @c false otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bool removeAction(bb::cascades::ActionItem* actionItem);
            
           /*!
            * @brief Returns the number of actions in this @c Menu.
            *
            * @return The number of actions.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE int actionCount() const;

           /*!
            * @brief Returns the action at the specified index in this @c Menu.
            * 
            * @details Ownership of the action remains with this @c %Menu.
            *
            * @param index The index of the action.
            * 
            * @return The requested action if the index was valid, @c 0 otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bb::cascades::ActionItem* actionAt(int index) const;
                               
           /*!
            * @brief Gets the @c Help action for this @c Menu.
            *
            * The @c %Menu keeps the ownership of the @c Help action.
            *
            * @return The @c Help action, or @c 0 if no @c Help action is specified.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::HelpActionItem* helpAction() const;
            
           /*!
            * @brief Sets the @c Help action for this @c Menu.
            * 
            * @details The @c %Menu takes the ownership of the @c Help action.
            * When this function completes, the @c helpActionChanged() signal is emitted.
            *
            * @param helpAction The Help action.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setHelpAction(bb::cascades::HelpActionItem* helpAction);
            
           /*!
            * @brief Resets the @c Help action for this @c Menu.
            * 
            * @details This function removes the @c Help action for this @c %Menu.
            * When this function completes, the @c helpActionChanged() signal is emitted.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetHelpAction();
            
           /*!
            * @brief Gets the @c Settings action for this @c Menu.
            *
            * @details The @c %Menu keeps the ownership of the @c Settings action.
            *
            * @return The @c Settings action, or @c 0 if no @c Settings action has been specified.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::SettingsActionItem* settingsAction() const;
            
           /*!
            * @brief Sets the @c Settings action for this @c Menu.
            * 
            * @details The @c %Menu takes the ownership of the @c Settings action.
            * When this function completes, the @c settingsActionChanged() signal is emitted.
            *
            * @param settingsAction The @c Settings action.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setSettingsAction(bb::cascades::SettingsActionItem* settingsAction);
            
           /*!
            * @brief Resets the Settings action for this @c Menu.
            * 
            * @details This function removes the Settings action for this @c %Menu.
            * When this function completes, the @c settingsActionChanged() signal is emitted.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetSettingsAction();
 
        Q_SIGNALS:
        
           /*!
            * @brief Emitted when the enabled property has changed.
            *
            * @param enabled If @c true the @c Menu is enabled, if @c false the @c %Menu is not enabled.
            *
            * @since BlackBerry 10.0.0
            */
            void enabledChanged(bool enabled);  

           /*!
            * @brief Emitted when an action has been added to the @c Menu.
            *
            * @param action The action that has been added.
            *
            * @since BlackBerry 10.0.0
            */
            void actionAdded(bb::cascades::ActionItem *action);

           /*!
            * @brief Emitted when an action has been removed from the @c Menu.
            *        
            * @param action The action that has been removed.
            *
            * @since BlackBerry 10.0.0
            */
            void actionRemoved(bb::cascades::ActionItem *action);
        
           /*!
            * @brief Emitted when the @c Help action has changed.
            *
            * @param helpAction The new @c Help action.
            *
            * @since BlackBerry 10.0.0
            */
            void helpActionChanged(bb::cascades::HelpActionItem* helpAction);
            
           /*!
            * @brief Emitted when the @c Settings action has changed.
            *
            * @param settingsAction The new @c Settings action.
            *
            * @since BlackBerry 10.0.0
            */
            void settingsActionChanged(bb::cascades::SettingsActionItem* settingsAction);

    private:

           /*! @cond PRIVATE */
            QDeclarativeListProperty<bb::cascades::ActionItem> actions();
            Q_DECLARE_PRIVATE(Menu)
            Q_DISABLE_COPY(Menu)
        
            typedef Menu ThisClass;
            typedef UIObject BaseClass;
           /*! @endcond */

    public:

           /*!
            * @brief A builder template for constructing a @c Menu. To retrieve the builder, call
            * @c Menu::create().
            *
            * @since BlackBerry 10.0.0
            */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
                {
                }
            public:           
 
 
           /*!
            * @brief Adds an action to this @c Menu.
            * 
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myMenu->addAction(action);
            * @endcode
            *
            * @param action The action to add to the @c %Menu.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& addAction(ActionItem *action)
            {
                this->instance().addAction(action);
                return this->builder();
            }
          
           /*!
            * @brief Sets the Help action of this @c Menu.
            * 
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myMenu->setHelpAction(helpAction);
            * @endcode
            *
            * @param helpAction The action to set as the @c Help action.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& help(HelpActionItem* helpAction)
            {
                this->instance().setHelpAction(helpAction);
                return this->builder();
            }
            
           /*!
            * @brief Sets the @c Settings action if this @c Menu.
            * 
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myMenu->setSettingsAction(settingsAction);
            * @endcode
            *
            * @param settingsAction The action to set as the @c Settings action.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& settings(SettingsActionItem* settingsAction)
            {
                this->instance().setSettingsAction(settingsAction);
                return this->builder();
            }
        };

       /*!
        * A builder template for constructing a @c Menu. To retrieve the builder, call
        * @c Menu::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Menu>
        {
        public:
            explicit Builder() : TBuilder<Builder, Menu>(new Menu()) {
            }
        };

       /*! Creates and returns a builder for constructing a @c Menu.
        *
        * Using the builder to create a @c %Menu:
        * @code
        * Menu* menu = Menu::create();
        * @endcode
        *
        * @return A builder used for constructing a @c %Menu.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }     
        };
    }
};

#endif //cascades_menu_h
