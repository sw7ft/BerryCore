/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_page_h
#define cascades_page_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractpane.h>
#include <bb/cascades/controls/chromevisibility.h>
#include <bb/cascades/controls/pageresizebehavior.h>
#include <bb/cascades/controls/actionbarplacement.h>
#include <bb/cascades/controls/actionmenuvisualstate.h>
#include <bb/cascades/controls/inputrouteproperties.h>
#include <bb/cascades/resources/actionbarautohidebehavior.h>
#include <bb/cascades/resources/actionbarfollowkeyboardpolicy.h>

namespace bb {
    namespace cascades {

    class PagePrivate;
    class Control;
    class AbstractActionItem;
    class TitleBar;

   /*!
    *
    * @brief Defines an individual screen within an application.
    *
    * On a @c %Page it's possible to specify a root control and a set of actions. The actions are displayed on the Action bar placed
    * at the bottom of the screen. If no actions are specified, the Action bar will not be displayed,
    * and the screen content assumes the full height of the screen. As soon as one or more actions are
    * added, the Action bar will appear. To specify that an action should appear on the Action bar, rather than in the Action 
    * menu, the attached property ActionBar.placement can be used. Please note that the actionbar placement property will only be
    * considered at initialization ie. it can only be specified once.
    *
    * @image html page_example.png
    *
    * Here's an example of how to create a simple @c Page with an action placed on the Action bar.
    *
    * @code
    * Page {
    *     actions: [
    *         ActionItem {
    *             title: "Refresh"
    *             onTriggered: app.initiateRequest()
    *             ActionBar.placement: ActionBarPlacement.OnBar
    *         }
    *     ]
    *     content: Container {
    *         layout: DockLayout {}
    *        
    *         ActivityIndicator {
    *             verticalAlignment: VerticalAlignment.Fill
    *             horizontalAlignment: HorizontalAlignment.Fill    
    *         }
    *     }
    * }
    * @endcode
    *
    * @see ActionItem
    *
    * @xmlonly
    * <qml>
    * <class abstract="yes" />
    * </qml>
    * @endxmlonly
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT Page : public AbstractPane {
    private:
        Q_OBJECT

        /*!
        * @brief The title bar properties for this @c %Page.
        *
        * By default, the @c titleBar of a @c %Page is @c 0.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::TitleBar* titleBar READ titleBar WRITE setTitleBar
        RESET resetTitleBar NOTIFY titleBarChanged FINAL)

        /*!
        * @brief A list of actions that will be displayed on the Action bar or in the Action menu.
        *
        * The order in which they are added will determine how they appear
        * on the Action bar and in the Action menu.
        *
        * Since this list consists of @c AbstractActionItem, you should cast
        * the value to either an @c ActionItem or an @c InvokeActionItem before you use them.
        *
        * Only one @c DeleteActionItem and @c MultiSelectActionItem can be displayed at one time. If more than one is added, 
        * only the first one is used and the rest are ignored. They are placed at a fixed position 
        * on the Action bar or in the Action menu along with the other actions. The @c %MultiSelectActionItem is used 
        * to start a multiple selection session.
        *
        * @see ActionItem
        * @see InvokeActionItem
        *
        * @xmlonly
        * <qml>
        * <property name="actions" listType="bb::cascades::AbstractActionItem" defaultProperty="no"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractActionItem> actions READ actions FINAL)

        
       /*!
        * @brief The root control for the @c %Page (the contents of the screen).
        *
        * This is the default property of the @c %Page control, so it does not need to be explicitly
        * declared in QML. A control added inside the @c %Page will automatically be assigned to
        * the content property.
        *
        * @code
        * Page {
        *     Container {
        *         Button {}
        *         Button {}
        *     }
        * }
        * @endcode
        *
        * The code snippet above is equal to the following code snippet:
        *
        * @code
        * Page {
        *     content: Container {
        *         Button {}
        *         Button {}
        *     }
        * }
        * @endcode
        *
        * @xmlonly
        * <qml>
        * <property defaultProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent NOTIFY contentChanged FINAL)
      
       /*!
        * @brief The different ways that a @c Page can be resized when the available screen space is affected by external
        * components (for example, when the keyboard appears).
        *
        * The default resize behavior is
        * @c PageResizeBehavior::Resize, but @c PageResizeBehavior::None can also be used.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::PageResizeBehavior::Type resizeBehavior
                   READ resizeBehavior
                   WRITE setResizeBehavior
                   RESET resetResizeBehavior
                   NOTIFY resizeBehaviorChanged
                   FINAL)

       /*!
        * @brief Specifies the Action bar visibility.
        *
        * This property specifies the visibility mode of the associated Action bar. By default, the Action bar is
        * fully visible (if there are actions) and the @c %Page content is compressed to show the Action bar at
        * the bottom of the screen. Using this property, you can set the Action bar to be in a compact mode, overlaid
        * (on top of the @c %Page) or fully hidden.
        *
        * @code
        * Page {
        *     actionBarVisibility: ChromeVisibility.Overlay
        * }
        * @endcode
        *
        * In cases where the Action bar is overlaid on top of the page's content, you might want to pad the
        * bottom part of the UI so that it's not obscured by the Action bar. Here's an example of how to
        * use the @c PageLayoutUpdateHandler::bottomOverlayHeight to pad a ListView so that the last item
        * isn't obscured by the action bar when the user has scrolled to the bottom:
        *
        * @snippet tad/examples/applicationstructure/page/assets/main.qml page_qml3
        * @see PageLayoutUpdateHandler::bottomOverlayHeight
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ChromeVisibility::Type actionBarVisibility READ actionBarVisibility
            WRITE setActionBarVisibility RESET resetActionBarVisibility NOTIFY actionBarVisibilityChanged FINAL)

       /*!
        * @brief This property specifies the follow keyboard policy of the associated Action bar.
        * By default, the Action bar is not following the Virtual Keyboard when it is invoked.
        * However, this property allows you to change this behavior and make the Action bar able to follow
        * the Virtual Keyboard in the Portrait mode.
        *
        * @code
        * Page {
        *     actionBarFollowKeyboardPolicy: ActionBarFollowKeyboardPolicy.Portrait
        * }
        * @endcode
        *
        * @since BlackBerry 10.3.0
        */
        Q_PROPERTY(bb::cascades::ActionBarFollowKeyboardPolicy::Type actionBarFollowKeyboardPolicy READ actionBarFollowKeyboardPolicy
                   WRITE setActionBarFollowKeyboardPolicy RESET resetActionBarFollowKeyboardPolicy NOTIFY actionBarFollowKeyboardPolicyChanged
                   REVISION 3 FINAL)

       /*!
        * @brief The current visual state of the action menu.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ActionMenuVisualState::Type actionMenuVisualState READ actionMenuVisualState 
                NOTIFY actionMenuVisualStateChanged FINAL)

        /*!
         * @brief Defines this page's role in the propagation of input events.
         *
         * QML usage:
         * @snippet tad/examples/applicationstructure/page/assets/main.qml page_qml1
         *
         * C++ usage:
         * @snippet tad/examples/applicationstructure/page/src/PageExamples.cpp page1
         *
         * C++ usage (with builder):
         * @snippet tad/examples/applicationstructure/page/src/PageExamples.cpp page2
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::InputRouteProperties* inputRoute READ inputRoute FINAL)

      /*!
       * @brief Sets the auto-hide behavior of the Action Bar.
       *
       * The @c Page uses the concept of "main scrollable" to decide which scrollable control to listen to
       * for auto-hide behavior of the Action Bar. If a @c %Page finds a main scrollable, either by the user
       * explicitly specifying one, or automatically by inspecting the ui-tree, it will consider hiding the
       * Action Bar when appropriate. Hiding the Action Bar is a best practice for devices with small screens
       * and on OLED (organic light-emitting diode) screens to prevent burn in.
       *
       * @note Automatically hidding the Action bar only works if @c Page::actionBarVisibility is also set
       *       to @c ChromeVisibility::Overlay.
       *
       * @see Page::actionBarVisibility
       * @see ListView::scrollRole
       * @see ScrollView::scrollRole
       *
       * @since BlackBerry 10.1.0
       */
       Q_PROPERTY(bb::cascades::ActionBarAutoHideBehavior::Type actionBarAutoHideBehavior READ actionBarAutoHideBehavior
           WRITE setActionBarAutoHideBehavior RESET resetActionBarAutoHideBehavior NOTIFY actionBarAutoHideBehaviorChanged FINAL)

      /*!
       * @brief If the focus is on the action bar, deliver events as if nothing had focus.
       *
       * Whenever something on the action bar is focused, key events will be delivered to that item and never to the primary 
       * key target or the fallback route. Sometimes it is desirable to prevent this behavior for items on the action bar.
       *
       * Setting this property will make the event propagation treat anything focused on the action bar as if nothing had focus.
       *
       * The default value for this property is @c false.
       *
       * @see Page::inputRoute, Control::inputRoute
       *
       * @since BlackBerry 10.3.1
       */
       Q_PROPERTY(bool keysIgnoreFocusInActionBar READ keysIgnoreFocusInActionBar WRITE setKeysIgnoreFocusInActionBar RESET resetKeysIgnoreFocusInActionBar NOTIFY keysIgnoreFocusInActionBarChanged REVISION 4 FINAL);

    public:

       /*!
        * @brief Returns the @c TitleBar object for the page.
        *
        * @return The @c TitleBar for the page.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::TitleBar* titleBar() const;

       /*!
        * @brief Sets the @c TitleBar property for the @c Page.
        *
        * The @c %Page takes ownership of the @c %TitleBar object. 
        * If the @c %TitleBar object is already set on another @c %Page, it is 
        * removed from the original @c %Page. Ownership of the @c %TitleBar object 
        * stays with the original @c %Page.
        *
        *
        * @param titleBar The new @c TitleBar for the page or @c 0 to remove title bar from 
        * the page.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setTitleBar(bb::cascades::TitleBar *titleBar);

       /*!
        * @brief Resets the @c #titleBar property for the @c Page to @c 0.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetTitleBar();

        Q_CLASSINFO("DefaultProperty", "content")

       /*!
        * @brief Constructs a @c %Page.
        *
        * @since BlackBerry 10.0.0
        */
        explicit Page(QObject* parent = 0);

       /*!
        * @brief The destructor of the @c %Page.
        *
        * @since BlackBerry 10.0.0
        */
        virtual ~Page();


       /*!
        * @brief Adds an action to the @c %Page. 
        *
        * A @c %Page will always take ownership of the action, as actions should typically not be shared.
        * If the action already belongs to the @c %Page or the @c actionItem is @c 0, nothing will happen.
        * If the operation was successful, the @c actionAdded() signal will be emitted.
        * The order in which actions are added will decide how they appear on the
        * Action bar and in the Action menu.
        *
        * Valid action items are @c ActionItem or @c InvokeActionItem, and all other items will be ignored.
        *
        * @param actionItem The @c ActionItem or @c InvokeActionItem to add to the @c %Page.
        * @param placement Specifies where the action should be placed.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void addAction(bb::cascades::AbstractActionItem* actionItem,
          bb::cascades::ActionBarPlacement::Type placement = bb::cascades::ActionBarPlacement::Default);

       /*!
        * @brief Removes an action from the @c %Page. 
        *
        * Once the action is removed, the @c %Page no longer references it, but it is still 
        * owned by the @c %Page. It is up to the application to either delete the removed 
        * action, transfer its ownership (by setting its parent) to another object, or leave 
        * it as a child of the @c %Page (in which case it will be deleted with the @c %Page).
        *
        * If operation was successful, the @c actionRemoved() signal will be emitted.
        *
        * @param actionItem The @c ActionItem or @c InvokeActionItem to remove.
        * @return @c true if the action was owned by the @c %Page, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bool removeAction(bb::cascades::AbstractActionItem* actionItem);

       /*!
        * @brief Removes all actions on a @c Page and frees their memory.
        *
        * The actionRemoved(bb::cascades::AbstractActionItem*) signal is emitted with @c 0 as its parameter.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void removeAllActions();

       /*!
        * @brief Returns the number of actions.
        *
        * @return The number of actions.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int actionCount() const;

       /*!
        * @brief Returns an action at the specified index. 
        *
        * Ownership of the action remains with the @c %Page.
        *
        * Since this method returns an @c AbstractActionItem, you should cast the value to either an
        * @c ActionItem or an @c InvokeActionItem before you use it. For example:
        *
        * @code
        * AbstractActionItem *item = myPage->actionAt(0);
        * ActionItem *castedItem = qobject_cast<ActionItem *>(item);
        * @endcode
        *
        * @param index The index of the action.
        * @return The requested action if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::AbstractActionItem* actionAt(int index) const;

       /*!
        * @brief Set the content of the @c %Page. 
        *
        * Ownership will always be transferred to the @c %Page.
        * If @c %Page already has a content, the old content will still be owned by @c %Page
        * and destroyed when @c %Page is destroyed.
        * If operation was successful, the @c contentChanged() signal will be emitted.
        *
        * @param content The content. Can be @c 0 to remove content (old content will
        * still be owned by @c %Page).
        *
        * @since BlackBerry 10.0.0
        */
        void setContent(bb::cascades::Control* content);

       /*!
        * @brief Get the active content.
        *
        * Ownership will not be transferred.
        *
        * @return The content.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::Control* content() const;

        /*!
         * @brief Returns the resize behavior for the @c %Page.
         *
         * @return The resize behavior.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::PageResizeBehavior::Type resizeBehavior() const;

        /*!
         * @brief Sets the resize behavior for the @c %Page.
         *
         * After the resize behavior is set, the @c resizeBehaviorChanged() signal is emitted.
         *
         * @param resizeBehavior The new resize behavior.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setResizeBehavior(bb::cascades::PageResizeBehavior::Type resizeBehavior);

        /*!
         * @brief Resets the resize behavior for the @c %Page to its default.
         *
         * The default resize behavior is @c PageResizeBehavior::Resize.
         *
         * After the resize behavior is set, the @c resizeBehaviorChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetResizeBehavior();

        /*!
        * @brief Sets the Action bar visibility mode.
        *
        * This property specifies the visibility mode of the associated Action bar. By default, 
        * the Action bar is fully visible (if there are actions) and the content on the @c %Page
        * is compressed to display the Action bar at the bottom of the screen. Using this property,
        * you can set the Action bar to either be overlaid (on top of the page) or fully hidden.
        *
        * The signal @c actionBarVisibilityChanged() is emitted if the visibility mode is changed.
        *
        * @param visibility The Action bar visibility mode.
         *
         * @since BlackBerry 10.0.0
        */
        void setActionBarVisibility(const bb::cascades::ChromeVisibility::Type visibility);

       /*!
        * @brief Gets the Action bar visibility mode.
        *
        * @return The Action bar visibility mode.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::ChromeVisibility::Type actionBarVisibility() const;

       /*!
        * @brief Resets the Action bar visibility mode to its default value.
        * The default value is @c ChromeVisibility::Default.
        *
        * The signal @c actionBarVisibilityChanged() is emitted if the Action bar visibility mode is
        * changed.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetActionBarVisibility();


       /*!
        * @brief Sets the Action bar follow keyboard behavior.
        *
        * The signal @c actionBarFollowKeyboardChanged() is emitted if the follow keyboard behavior is changed.
        *
        * @param followKeyboardPolicy The Action bar follow keyboard policy.
        *
        * @since BlackBerry 10.3.0
        */
        Q_REVISION(3)
        void setActionBarFollowKeyboardPolicy(const bb::cascades::ActionBarFollowKeyboardPolicy::Type followKeyboardPolicy);

        /*!
        * @brief Gets the Action bar follow keyboard policy.
        *
        * @return The Action bar follow keyboard policy.
        *
        * @since BlackBerry 10.3.0
        */
        Q_REVISION(3)
        bb::cascades::ActionBarFollowKeyboardPolicy::Type actionBarFollowKeyboardPolicy() const;

       /*!
        * @brief Resets the Action bar follow keyboard policy to its default value.
        * The default value is @c ActionBarFollowKeyboardPolicy::Default.
        *
        * The signal @c actionBarFollowKeyboardChanged() is emitted if the Action bar follow keyboard is
        * changed.
        *
        * @since BlackBerry 10.3.0
        */
        Q_REVISION(3)
        Q_SLOT void resetActionBarFollowKeyboardPolicy();

       /*!
        * @brief Returns the current visual state of the action menu.
        * 
        * @return The current visual state of the action menu.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::ActionMenuVisualState::Type actionMenuVisualState() const;

       /*!
        * @brief Opens the Action Overflow Menu
        *
        * Opens the Action Overflow Menu if there is an @c ActionSet attached to the page.
        *
        * @since BlackBerry 10.3.1
        */
        Q_REVISION(4)
        Q_SLOT void openActionMenu();

        /*!
         * @brief Returns the input route properties object.
         *
         * @return The input route properties object.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::InputRouteProperties *inputRoute() const;

        /*!
         * @brief Returns the @c actionBarAutoHideBehavior.
         *
         * @return The current @c %actionBarAutoHideBehavior.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::ActionBarAutoHideBehavior::Type actionBarAutoHideBehavior() const;

        /*!
         * @brief Sets the @c actionBarAutoHideBehavior.
         *
         * The signal @c %actionBarAutoHideBehaviorChanged() is emitted if the value is changed.
         * @param actionBarAutoHideBehavior The new @c %actionBarAutoHideBehavior.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setActionBarAutoHideBehavior(bb::cascades::ActionBarAutoHideBehavior::Type actionBarAutoHideBehavior);

        /*!
         * @brief Resets @c actionBarAutoHideBehavior to its default value.
         *
         * The default value is Default.
         * The signal @c actionBarAutoHideBehaviorChanged() is emitted if the value is changed.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetActionBarAutoHideBehavior();

        /*!
         * @brief Returns the @c #keysIgnoreFocusInActionBar state of the action bar.
         *
         * @return @c true if key events should ignore focus on the action bar, @c false otherwise.
         *
         * @since BlackBerry 10.3.1
         */
         Q_REVISION(4)
         bool keysIgnoreFocusInActionBar() const;

        /*!
         * @brief Sets the @c #keysIgnoreFocusInActionBar state of the action bar.
         *
         * @param keysIgnoreFocusInActionBar If @c true key events will ignore focus on the action bar and if @c false
         * key events will go to the focused item on the action bar.
         *
         * @since BlackBerry 10.3.1
         */
         Q_REVISION(4)
         Q_SLOT void setKeysIgnoreFocusInActionBar(bool keysIgnoreFocusInActionBar);

        /*!
         * @brief Resets the @c #keysIgnoreFocusInActionBar state of the action bar to @c false.
         *
         * @since BlackBerry 10.3.1
         */
         Q_REVISION(4)
         Q_SLOT void resetKeysIgnoreFocusInActionBar();

    Q_SIGNALS:

        /*!
         * @brief Emitted when @c actionBarAutoHideBehavior changed.
         *
         * @param newActionBarAutoHideBehavior The new value of @c %actionBarAutoBehavior.
         *
         * @since BlackBerry 10.1.0
         */
         void actionBarAutoHideBehaviorChanged(bb::cascades::ActionBarAutoHideBehavior::Type newActionBarAutoHideBehavior);

        /*!
         * @brief Emitted when the @c #keysIgnoreFocusInActionBar property changes.
         *
         * @param keysIgnoreFocusInActionBar The new value of @c #keysIgnoreFocusInActionBar.
         *
         * @since BlackBerry 10.3.1
         */
         Q_REVISION(4)
         void keysIgnoreFocusInActionBarChanged(bool keysIgnoreFocusInActionBar);

        /*!
         * @brief Emitted when Action bar visibility changes.
         *
         * @param newVisibility The new visibility.
         *
         * @since BlackBerry 10.0.0
         */
         void actionBarVisibilityChanged(bb::cascades::ChromeVisibility::Type newVisibility);

        /*!
         * @brief Emitted when Action bar follow keyboard policy property changes.
         *
         * @param newFollowKeyboardPolicy The new ActionBarFollowKeyboardPolicy value.
         *
         * @since BlackBerry 10.3.0
         */
         Q_REVISION(3)
         void actionBarFollowKeyboardPolicyChanged(bb::cascades::ActionBarFollowKeyboardPolicy::Type newFollowKeyboardPolicy);

       /*!
        * @brief Emitted when the @c #resizeBehavior property changes.
        *
        * @note Due to a work around for a Qt Core issue with accessing enums from QML,
        * the argument of this signal doesn't follow the usual naming convention for signals. 
        * Typically, signal arguments are named to match the associated property's name.
        * In this case, you must use the object's property to access the current 
        * property value instead of the signal argument to avoid runtime errors 
        * (i.e. use @c resizeBehavior instead of @c newResizeBehavior).
        *
        * @param newResizeBehavior The new resize behavior.
        *
        * @since BlackBerry 10.0.0
        */
        void resizeBehaviorChanged(bb::cascades::PageResizeBehavior::Type newResizeBehavior);

       /*!
        * @brief Emitted when the @c #titleBar of the page changes.
        *
        * @param titleBar The new @c TitleBar for the @c %Page.
        *
        * @since BlackBerry 10.0.0
        */
        void titleBarChanged(bb::cascades::TitleBar *titleBar);

       /*!
        * @brief Emitted when the content has changed.
        *
        * @param content The new content.
        *
        * @since BlackBerry 10.0.0
        */
        void contentChanged(bb::cascades::Control* content);

       /*!
        * @brief Emitted when an action has been added to the @c %Page.
        *
        * @param action The action that has been added.
        *
        * @since BlackBerry 10.0.0
        */
        void actionAdded(bb::cascades::AbstractActionItem *action);

       /*!
        * @brief Emitted when a action has been removed from the @c %Page.
        *
        * @param action The action that has been removed. @c 0 if emitted by removeAllActions().
        *
        * @since BlackBerry 10.0.0
        */
        void actionRemoved(bb::cascades::AbstractActionItem *action);

       /*!
        * @brief Emitted when @c #actionMenuVisualState property changed.
        * 
        *
        * @note Due to a work around for a Qt Core issue with accessing enums from QML,
        * the argument of this signal doesn't follow the usual naming convention for signals. 
        * Typically, signal arguments are named to match the associated property's name.
        * In this case, you must use the object's property to access the current 
        * property value instead of the signal argument to avoid runtime errors 
        * (i.e. use @c actionMenuVisualState instead of @c newActionMenuVisualState).
        *
        * @param newActionMenuVisualState The new value of the @c #actionMenuVisualState property.
        *
        * @since BlackBerry 10.0.0
        */
        void actionMenuVisualStateChanged(bb::cascades::ActionMenuVisualState::Type newActionMenuVisualState);

    private:

        /*! \cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::AbstractActionItem> actions();
        Q_DECLARE_PRIVATE(Page)
        Q_DISABLE_COPY(Page)

        typedef Page ThisClass;
        typedef AbstractPane BaseClass;
        /*! \endcond */

    public:

       /*!
        * @brief A builder template for constructing a @c %Page. To retrieve the builder, call
        * Page::create().
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
            * @brief Adds an action to the @c %Page.
            *
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myPage->addAction(action);
            * @endcode
            *
            * @param action The action to add to the @c %Page, valid actions is @c ActionItem or c@ InvokeActionItem.
            * @param placement The placement of the action.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& addAction(AbstractActionItem *action,
              bb::cascades::ActionBarPlacement::Type placement = bb::cascades::ActionBarPlacement::Default)
            {
                this->instance().addAction(action, placement);
                return this->builder();
            }

           /*!
            * @brief Sets the content.
            *
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myPage->setContent(control);
            * @endcode
            *
            * @param control The control to set as content.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& content(Control *control)
            {
                this->instance().setContent(control);
                return this->builder();
            }

            /*!
             * @brief Sets the Action bar visibility mode.
             *
             * This property specifies the visibility mode of the associated Action bar. By default it will be fully visible (if
             * there are actions) and the page will be compressed. Using this property it's possible to set the Action bar to either
             * be overlaid i.e. on top of the page or fully hidden.
             *
             * @param newVisibility The new Action bar visibility.
             *
             * @since BlackBerry 10.0.0
             */
             BuilderType& actionBarVisibility(bb::cascades::ChromeVisibility::Type newVisibility)
             {
                 this->instance().setActionBarVisibility(newVisibility);
                 return this->builder();
             }

            /*!
             * @brief Sets the Action bar follow keyboard policy.
             *
             * @param newFollowKeyboardPolicy The new Action bar follow keyboard policy value.
             *
             * @since BlackBerry 10.3.0
             */
             BuilderType& actionBarFollowKeyboardPolicy(bb::cascades::ActionBarFollowKeyboardPolicy::Type newFollowKeyboardPolicy)
             {
                 this->instance().setActionBarFollowKeyboardPolicy(newFollowKeyboardPolicy);
                 return this->builder();
             }

           /*!
            * @brief Sets the resize behavior for the @c %Page.
            *
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myPage->setResizeBehavior(resizeBehavior);
            * @endcode
            *
            * @param resizeBehavior The resize behavior.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& resizeBehavior(bb::cascades::PageResizeBehavior::Type resizeBehavior) {
                this->instance().setResizeBehavior(resizeBehavior);
                return this->builder();
            }

           /*!
            * @brief Sets the layout properties for the page.
            *
            * The @c %Page takes ownership of the @c TitleBar object if no other pane owns it already.
            * If the @c %TitleBar object already has an owner, the properties are applied to the control,
            * but ownership of the @c %TitleBar object remains unchanged. If the @c %Page already owns a
            * @c %TitleBar object, the existing settings are replaced by the specified @c %TitleBar object
            * and the pane retains ownership of both.
            *
            * @param titleBar The new @c %TitleBar for the page.
            *
            * @see Page::titleBar
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& titleBar(TitleBar* titleBar) {
                this->instance().setTitleBar(titleBar);
                return this->builder();
            }

           /*!
            * @brief Sets the @c primaryKeyTarget property of the @c inputRoute.
            *
            * @param primaryKeyTarget @c true if the page should be treated as a primary key target, @c false otherwise.
            *
            * @see Page::inputRoute
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& primaryKeyTarget(bool primaryKeyTarget) {
                this->instance().inputRoute()->setPrimaryKeyTarget(primaryKeyTarget);
                return this->builder();
            }

            /*!
            * @brief Sets the @c keysIgnoreFocusInSubtree property of the @c inputRoute.
            *
            * @param keysIgnoreFocusInSubtree @c true if the control should be treated as a key blocker.
            *
            * @see Control::inputRoute
            *
            * @since BlackBerry 10.3.1
            */
            BuilderType& keysIgnoreFocusInSubtree(bool keysIgnoreFocusInSubtree) {
                this->instance().inputRoute()->setKeysIgnoreFocusInSubtree(keysIgnoreFocusInSubtree);
                return this->builder();
            }
        };

       /*!
        * @brief A builder template for constructing a @c %Page. To retrieve the builder, call
        * Page::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Page>
        {
        public:
            explicit Builder() : TBuilder<Builder, Page>(new Page()) {
            }
        };

       /*! @brief Creates and returns a builder for constructing a @c %Page.
        *
        * Using the builder to create a @c %Page:
        * @code
        * Page* page = Page::create();
        * @endcode
        *
        * @return A builder used for constructing a @c %Page.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Page)

#endif
