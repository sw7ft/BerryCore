/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_tabbedpane_h
#define cascades_tabbedpane_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractpane.h>
#include <bb/cascades/controls/sidebarstate.h>
#include <bb/cascades/controls/sidebarvisualstate.h>
#include <bb/cascades/resources/tab.h>

namespace bb {
    namespace cascades {

        class ActionItem;
        class TabbedPanePrivate;

       /*!    
        *
        * @brief A navigation control that allows the user to switch between tabs.
        *
        * @image html cascades_navigation_tabs.png A TabbedPane with three tabs
        *
        * The tabs can be used to either completely replace displayed content by
        * setting new panes or to filter existing content in a single pane based on
        * which tab is currently selected.
        *        
        * The @c %Tab objects in the @c %TabbedPane are added to the Action bar, which is a 
        * horizontal bar displayed at the bottom of the screen. The tabs on the Action bar 
        * can be pressed to switch to display their content. The @c %Tab objects take an 
        * @c %AbstractPane as their @c %content. If the content is not @c 0, it will be 
        * displayed in the @c %TabbedPane when the corresponding tab is selected.
        *
        * If the @c %TabbedPane has only one @c %Tab and the content of that @c %Tab has no
        * actions, the Action bar is not displayed since there aren't any additional tabs or 
        * actions to be displayed.
        *
        * The first added Tab becomes the active one.
        *
        * If the content of the @c %Tab that is being displayed has any @c %ActionItem objects 
        * associated with it, these actions take priority and are placed on the Action bar, while 
        * the other tabs are pushed to the side bar. This behavior can be changed by setting the 
        * @c showTabsOnActionBar property to @c true. If @c showTabsOnActionBar is @c true, tabs 
        * will be placed on the Action bar and actions will be placed in the Action menu.
        *
        * @image html cascades_navigation_tabs_and_action.png A TabbedPane with three tabs and an action
        * 
        * The user can access tabs or actions that are not present on the Action bar by pressing 
        * the overflow tab, which is automatically added to the Action bar when it is needed.
        *
        * If a tab is selected that is not currently present on the Action bar, the side bar will
        * then change to the active-tab state and show the title and image of that tab 
        * along with an overflow symbol.
        *
        * It is possible for the application to programmatically change the appearance of the sidebar
        * by setting the property @c sidebarState.
        *
        * A tab can display a visual notification image if there is new content available.
        * If any tab that is only shown in the side bar contains such a visual notification,
        * the overflow tab will also display such a visual notification. This visual notification will remain on the
        * overflow tab until the corresponding tab(s) have been displayed (e.g. by opening the side bar) or the
        * visual notification is removed from all tabs that are only visible in the side bar and that had new content.
        *
        * Here's an example of a @c %TabbedPane with three tabs, each with its own page and set of actions.
        * The tabs are set to show on the Action bar so that the actions get pushed to the Action
        * menu.
        *
        * @image html tabbedpane_action_overflow.png
        *
        * QML implementation:
        *
        * @code
        * TabbedPane {
        *     showTabsOnActionBar: true
        *     Tab {
        *         title: "Home"
        *         Page {
        *             id: page1
        *             actions: [
        *                 ActionItem {
        *                     title: "New"
        *                 },
        *                 ActionItem {
        *                     title: "Delete"
        *                 }
        *             ]
        *         }
        *     }
        *     Tab {
        *         title: "Options"
        *         Page {
        *             id: page2
        *             actions: [
        *                 ActionItem {
        *                     title: "Edit"
        *                 },
        *                 ActionItem {
        *                     title: "Save"
        *                 }
        *             ]
        *         }
        *     }
        *     Tab {
        *         title: "Help"
        *         Page {
        *             id: page3
        *             actions: [
        *                 ActionItem {
        *                     title: "Search"
        *                 },
        *                 ActionItem {
        *                     title: "Browse"
        *                 }
        *             ]
        *         }
        *     }
        * }
        * @endcode
        *
        * C++ implementation:
        *
        * @code
        * TabbedPane* tabbedPane = TabbedPane::create()
        *     .showTabsOnActionBar(true)
        *     .add(Tab::create()
        *         .title("Home")
        *         .content(Page::create()
        *             .addAction(ActionItem::create().title("New"))
        *             .addAction(ActionItem::create().title("Delete"))))
        *     .add(Tab::create()
        *         .title("Options")
        *         .content(Page::create()
        *             .addAction(ActionItem::create().title("Edit"))
        *             .addAction(ActionItem::create().title("Save"))))
        *     .add(Tab::create()
        *         .title("Help")
        *         .content(Page::create()
        *             .addAction(ActionItem::create().title("Search"))
        *             .addAction(ActionItem::create().title("Browse"))));
        * @endcode
        *
        * To get the actions displayed on the Action bar and the tabs in the Tab menu,
        * the @c showTabsOnActionBar property must be set to @c false and the
        * ActionBar.placement property for each action must be set to ActionBarPlacement.OnBar. Here's
        * how a @c TabbedPane looks with the actions on the Action bar and the tabs in the Tab
        * menu:
        *
        * @image html tabbedpane_tab_overflow.png
        *
        * In addition to switching between pages, tabs can also be used for filtering content that appears on
        * the screen. Here's an example that shows how to change the text for a label by using tabs.
        *
        * @code
        * TabbedPane {
        *     showTabsOnActionBar: true
        *     activePane:
        *         Page {
        *             Label {
        *                 id: label
        *                 text: "What do you like more, kittens or puppies?"
        *             }
        *         }
        * 
        *     Tab { 
        *         title: "Puppies"
        *         onTriggered: label.text = "I love puppies!"
        *     }
        * 
        *     Tab {
        *         title: "Kittens"
        *         onTriggered: label.text = "I love kittens!"
        *     }
        * }
        * @endcode
        *        
        * @see @c Tab, @c Page, @c NavigationPane
        *
        * @xmlonly
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT TabbedPane : public AbstractPane
        {
            Q_OBJECT

           /*!
            * @brief A set of @c Tab objects added to the @c %TabbedPane.
            *
            * For each @c %Tab in the @c %TabbedPane, a tab is added to the Action bar, 
            * which can be pressed to switch to its corresponding content. If the active
            * @c %Tab has actions added to it, they will be displayed in the Action bar.
            *
            * @see @c Tab, @c Page, @c NavigationPane
            *
            * @xmlonly
            * <qml>
            * <property name="tabs" listType="bb::cascades::Tab" defaultProperty="yes"/>
            * </qml>
            * @endxmlonly
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(QDeclarativeListProperty<bb::cascades::Tab> tabs READ tabs FINAL)
            Q_CLASSINFO("DefaultProperty", "tabs") 

           /*!
            * @brief The @c Tab that is currently active in the @c %TabbedPane.
            *
            * The active tab is @c 0 if the @c %TabbedPane doesn't have any children.
            *
            * The @c activeTabChanged() signal is emitted when this property changes.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bb::cascades::Tab* activeTab READ activeTab WRITE setActiveTab NOTIFY activeTabChanged FINAL)

           /*!
            * @brief The @c AbstractPane which is currently being shown by the @c TabbedPane.
            *
            * The active pane is @c 0 of the @c %TabbedPane doesn't have any children or there
            * is no pane currently being displayed.
            *
            * The value of this property may not match the value of the currently active tab's 
            * Tab::content property: if active @c %Tab's content is @c 0 the active pane will not
            * change.
            *
            * The value of this property will change in the following cases:
            * - when a new @c Tab with a non-@c 0 Tab::content property becomes active the value
            *   this property will become the active @c Tab's content. If new active tab's content @c 0 
            *   this property doesn't change.
            * - when a new active pane is set explicitly. An active pane may belong to one of the @c Tabs
            *   or be a separate pane belonging to the @c TabbedPane, or be @c 0.
            * - when a @c %Tab the active  pane belonged to is removed
            *
            * Here is how this property can be used to define common pane which will not
            * change when active tab changes
            *
            * @code
            * TabbedPane {
            *     showTabsOnActionBar: true
            *     // there is only one content page, and it is explicitly
            *     // set to be the active pane of this TabbedPane
            *     activePane:
            *         Page {
            *             Label {
            *                 id: label
            *                 text: "Default"
            *             }
            *         }
            *     Tab {
            *         title: "Tab 1"
            *         onTriggered: {
            *             // change some content in the activePane
            *             label.text = "Tab 1 Label";
            *         }
            *     }
            * 
            *     Tab {
            *         title: "Tab 2"
            *         onTriggered: {
            *             label.text = "Tab 2 Label";
            *         }
            *     }
            * }
            * @endcode
            *
            * If the more than one pane needs to be displayed:
            *
            * @code
            * TabbedPane {
            *     id: tabbed
            *     showTabsOnActionBar: true
            *
            *     // the first two tabs share their page and only change 
            *     // the content of a label
            *     Tab {
            *         id: firstTab
            *         title: "Tab 1"
            *         onTriggered: {
            *             tabbed.activePane = defaultPane;
            *             label.text = "Tab 1 Label";
            *         }
            *     }
            * 
            *     Tab {
            *         title: "Tab 2"
            *         onTriggered: {
            *             tabbed.activePane = defaultPane;
            *             label.text = "Tab 2 Label";
            *         }
            *     }
            *
            *     // the third tab has its own pane which will be automatically
            *     // set as the active pane when the tab becomes active
            *     Tab {
            *         title: "Tab 3"
            *         Page {
            *             Label {
            *                 text: "Tab 3 Label"
            *             }
            *         }
            *     }
            *
            *     attachedObjects: [
            *         Page {
            *             id: defaultPane
            *             Label {
            *                 id: label
            *                 text: "Default"
            *             }
            *         }
            *     ]
            * }
            * @endcode
            *
            * The @c activePaneChanged() signal is emitted when this property changes.
            * The default value of this property is @c 0 .
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bb::cascades::AbstractPane* activePane READ activePane WRITE setActivePane NOTIFY activePaneChanged FINAL)

           /*!
            * @brief Specifies whether tabs should take priority in the Action bar instead of action items.
            * 
            * If the content of the @c %Tab that is being displayed has any @c %ActionItem objects 
            * associated with it, these actions take priority and are placed on the Action bar, while 
            * the other tabs are pushed to the side bar. This behavior can be changed by setting the 
            * @c showTabsOnActionBar property to @c true. If @c showTabsOnActionBar is @c true, tabs for 
            * will be placed on the Action bar and actions will be placed in the side bar.
            *
            * The default value is @c false.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bool showTabsOnActionBar READ showTabsOnActionBar WRITE setShowTabsOnActionBar
                RESET resetShowTabsOnActionBar NOTIFY showTabsOnActionBarChanged FINAL)

           /*!
            * @brief The current visibility state of the sidebar.
            * 
            * The default state is @c Hidden. 
            * The other available visibility states are @c VisibleCompact, and @c VisibleFull.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bb::cascades::SidebarState::Type sidebarState READ sidebarState WRITE setSidebarState
                   RESET resetSidebarState NOTIFY sidebarStateChanged FINAL)

           /*!
            * @brief Indicates whether peeking from within the current Page should be enabled.
            *
            * When enabled, dragging or swiping to the right inside the content of the
            * @c Page will reveal the Tab menu.
            *
            * This property only controls whether or not peeking is enabled within
            * the content area of the @c Page. Peeking is
            * always enabled on the Action bar, even if this property is disabled.
            *
            * The default value is @c true (enabled).
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bool peekEnabled READ isPeekEnabled WRITE setPeekEnabled
                   RESET resetPeekEnabled NOTIFY peekEnabledChanged FINAL)

           /*!
            * @brief The current visual state of the sidebar.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bb::cascades::SidebarVisualState::Type sidebarVisualState READ sidebarVisualState 
                   NOTIFY sidebarVisualStateChanged FINAL)
        public:

           /*!
            * @brief Constructs the @c %TabbedPane.
            *
            * @since BlackBerry 10.0.0
            */
            explicit TabbedPane(QObject* parent = 0);

           /*!
            * @brief Destructs the @c %TabbedPane.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~TabbedPane();

           /*!
            * @brief Returns the current value of the @c #sidebarState property.
            * 
            * @return The current state of the sidebar.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::SidebarState::Type sidebarState() const;

           /*!
            * @brief Specifies the current value of the @c #sidebarState property.
            * 
            * The @c sidebarStateChanged() signal will be emitted if the value of the @c #sidebarState property changed.
            *
            * @param sidebarState The new @c SidebarState.
            *
            * @since BlackBerry 10.0.0
            */
            void setSidebarState(bb::cascades::SidebarState::Type sidebarState);

            /*!
            * @brief Resets the @c #sidebarState property to its default value, which is 'Hidden'.
            *
            * The @c sidebarStateChanged() signal will be emitted if property changed.
             *
             * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetSidebarState();

           /*!
            * @brief Returns the currently active @c Tab.
            * 
            * @return The active @c %Tab or @c 0 if the @c %TabbedPane doesn't have any children.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::Tab* activeTab() const;

           /*!
            * @brief Sets the active @c %Tab.
            *
            * The @c activeTabChanged() signal will be emitted if the operation was successful. 
            * It will not be emitted if the @c %Tab was already active.
            *
            * @param activeTab The new active @c %Tab. If @c tab is @c 0, if it doesn't belong to 
            *                  the @c %TabbedPane, or if it already was active, nothing will happen.
            *
            * @since BlackBerry 10.0.0
            */
            void setActiveTab(bb::cascades::Tab* activeTab);

           /*!
            * @brief Returns the currently active @c AbstractPane.
            * 
            * @return The active @c %AbstractPane or @c 0 if one isn't currently
            * being displayed.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::AbstractPane* activePane() const;

           /*!
            * @brief Sets the active @c %AbstractPane.
            *
            * This method sets the pane to be displayed by this @c %TabbedPane.
            *
            * If the passed @c %AbstractPane was already active or if it had a parent but
            * did not belong to either this @c %TabbedPane or one of its @c Tabs it is ignored.
            * If @c 0 is passed no pane will be displayed.
            *
            * The replaced pane (if one was set) will not change ownership and will
            * continue to be owned by its parent.
            *
            * The @c %TabbedPane will only assume ownership of the passed pane if it doesn't
            * already have a parent (which can only be either one of this @c %TabbedPane's tabs
            * or the @c %TabbedPane itself). 
            *
            * The @c activePaneChanged() signal will be emitted if setting the new pane
            * was successful.
            *
            * @param activePane A pane to be set as the active pane or @c 0
            *
            * @since BlackBerry 10.0.0
            */
            void setActivePane(bb::cascades::AbstractPane* activePane);

           /*!
            * @brief Adds a @c Tab to the @c %TabbedPane.
            *
            * If this is the first @c %Tab added to this pane it will become the active tab.
            *
            * New tabs are added as the last child in the @c %TabbedPane.
            * The @c %Tab that is passed must not be @c 0 or it will be ignored. If the @c %Tab is
            * already a child of the @c %TabbedPane that it is being added to, the operation fails. 
            * If the @c %Tab is currently a child of another @c %TabbedPane, it is removed as a child 
            * from that @c %TabbedPane, and ownership is transferred to the new @c %TabbedPane.
            *
            * @param tab The @c %Tab to be added; must not be @c 0 or it will be ignored.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void add(bb::cascades::Tab* tab);

           /*!
            * @brief Inserts a @c Tab at a specified index in the @c %TabbedPane.
            *
            * If this is the first @c %Tab added to this pane it will become the active tab.
            *
            * The @c %Tab that is passed must not be @c 0 or it will be ignored. If the @c %Tab is
            * already a child of the @c %TabbedPane that it is being added to, the operation fails. 
            * If the @c %Tab is currently a child of another @c %TabbedPane, it is removed as a child 
            * from that @c %TabbedPane, and ownership is transferred to the new @c %TabbedPane.
            *
            * @param index The index where the @c %Tab will be placed. If the index < 0 the
            *              the @c %Tab is inserted as the first child. If the index > the number
            *              of children in the @c %TabbedPane, it is added as the last child.
            * @param tab The @c %Tab to be inserted; must not be @c 0 or it will be ignored..
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void insert(int index, bb::cascades::Tab* tab);

           /*!
            * @brief Returns a @c %Tab at the specified index.
            *
            * Once completed, ownership of the @c %Tab remains with the @c %TabbedPane.
            *
            * @param index The index of the @c %Tab.
            * @return The requested @c %Tab if the index was valid, @c 0 otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bb::cascades::Tab* at(int index) const;

           /*!
            * @brief Returns the index of a @c %Tab.
            *
            * If the @c %Tab isn't a child of the @c %TabbedPane 
            * or if the @c %Tab is @c 0, @c -1 is returned.
            *
            * @param tab The @c %Tab to get the index from.
            * @return The index of the specified @c %Tab if the @c %Tab is valid, @c -1 otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE int indexOf(bb::cascades::Tab *tab) const;

           /*!
            * @brief Returns the number of %Tabs in the @c tabs list property.
            *
            * @return The number of %Tabs in the @c tabs list property.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE int count() const;

           /*!
            * @brief Removes a @c %Tab from the @c %TabbedPane.
            *
            * If the removed tab was the active tab, the #activeTab property will
            * be set to @c 0. If the content of the removed tab was the active pane,
            * the #activePane property will be set to @c 0.
            *
            * Once the tab is removed, the @c %TabbedPane no longer references it, but it is still 
            * owned by the @c %TabbedPane. It is up to the application to either delete the removed 
            * tab, transfer its ownership (by setting its parent) to another object or leave 
            * it as a child of the @c %TabbedPane (in which case it will be deleted with the @c %TabbedPane).
            *
            * @param tab The @c %Tab to be removed; must not be @c 0.
            * @return @c true if the @c %Tab was a child of the @c %TabbedPane, @c false otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bool remove(bb::cascades::Tab* tab);

           /*!
            * @brief Removes all the tabs from the @c %TabbedPane and deletes them.
            *
            * Both #activeTab and #activePane properties will become @c 0 when this call is completed.
            *
            * The @c tabRemoved() signal is emitted with @c 0 as its parameter.
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void removeAll();

           /*!
            * @brief Returns the #showTabsOnActionBar state, which specifies whether tabs 
            * take priority over actions on the Action bar.
            *
            * @return @c true if tabs should take priority over actions on the Action bar, otherwise @c false.
            *
            * @since BlackBerry 10.0.0
            */
            bool showTabsOnActionBar() const;

           /*!
            * @brief Sets the @c #showTabsOnActionBar state, which specifies whether tabs 
            * take priority over actions on the Action bar.
            *
            * The @c showTabsOnActionBarChanged() signal will be emitted if the property changed.
            *
            * @param showTabsOnActionBar @c true if tabs should take priority over actions on the Action bar, otherwise @c false.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setShowTabsOnActionBar(bool showTabsOnActionBar);
            
           /*!
            * @brief Resets the @c #showTabsOnActionBar property to its default value, which is 'false'.
            *
            * The @c showTabsOnActionBarChanged() signal will be emitted if the property changed.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetShowTabsOnActionBar();

           /*!
            * @brief Indicates whether peeking from within the content area of the current @c Page is enabled.
            *
            * However, peeking is always enabled on the Action bar, even if this property is disabled.
            *
            * @return @c true if peeking is enabled, @c false otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            bool isPeekEnabled() const;

           /*!
            * @brief Sets whether peeking from within the current Page should be enabled.
            *
            * Setting this property only controls whether or not peeking is enabled within
            * the content area of the @c Page. Peeking is
            * always enabled on the Action bar, even if this property is disabled.
            *
            * @param enabled If @c true peeking be enabled, if @c false peeking is disabled.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setPeekEnabled(bool enabled);

           /*!
            * @brief Resets the peeking behavior of the %TabbedPane to its default state, which is disabled.
            *
            * Setting this property only controls whether or not peeking is enabled within
            * the content area of the @c Page. Peeking is
            * always enabled on the Action bar, even if this property is disabled.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetPeekEnabled();

           /*!
            * @brief Returns the current visual state of the sidebar.
            * 
            * @return The current visual state of the sidebar.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::SidebarVisualState::Type sidebarVisualState() const;

Q_SIGNALS:

           /*!
            * @brief Emitted when the @c #activeTab property has changed.
            *
            * @param activeTab The new active @c Tab.
            *
            * @since BlackBerry 10.0.0
            */
            void activeTabChanged(bb::cascades::Tab* activeTab);

           /*!
            * @brief Emitted when the @c #activePane property has changed.
            *
            * @param activePane The new active @c AbstractPane.
            *
            * @since BlackBerry 10.0.0
            */
            void activePaneChanged(bb::cascades::AbstractPane* activePane);

           /*!
            * @brief Emitted when the transition to a new active pane has finished.
            *
            * Always sent when navigating from the Sidebar or clicking on tabs on the Action bar.
            * @param activePane The new active @c AbstractPane.
            *
            * @since BlackBerry 10.0.0
            */
            void activePaneTransitionEnded(bb::cascades::AbstractPane* activePane);

           /*!
            * @brief Emitted when a @c Tab has been added to the @c %TabbedPane.
            *
            * @param tab The @c %Tab that has been added.
            *
            * @since BlackBerry 10.0.0
            */
            void tabAdded(bb::cascades::Tab* tab);

           /*!
            * @brief Emitted when a @c Tab has been removed from the @c %TabbedPane.
            *        
            * @param tab The @c %Tab that has been removed. @c 0 if emitted by @c removeAll().
            *
            * @since BlackBerry 10.0.0
            */
            void tabRemoved(bb::cascades::Tab* tab);

           /*!
            * @brief Emitted when the @c #showTabsOnActionBar property has changed.
            * 
            * @param showTabsOnActionBar The new value of the @c #showTabsOnActionBar property.
            *
            * @since BlackBerry 10.0.0
            */
            void showTabsOnActionBarChanged(bool showTabsOnActionBar);

           /*!
            * @brief Emitted when @c #sidebarState property changed.
            * 
            * @note Due to a work around for a Qt Core issue with accessing enums from QML
            * the argument of this signal doesn't follow naming convention for signals in
            * which the signal arguments are typically named to match the associated property's name.
            * Use the object's property to access current property value instead of the signal argument
            * to avoid runtime errors (i.e. use @c sidebarState instead of @c newSidebarState).
            *
            * @param newSidebarState The new value of the @c #sidebarState property.
            *
            * @since BlackBerry 10.0.0
            */
            void sidebarStateChanged(bb::cascades::SidebarState::Type newSidebarState);
            
            /*!
            * @brief Emitted when peeking on the %TabbedPane is enabled or disabled.
            *
            * @param enabled If @c true peeking is enabled, if @c false peeking is disabled.
             *
             * @since BlackBerry 10.0.0
            */
            void peekEnabledChanged(bool enabled);

           /*!
            * @brief Emitted when @c #sidebarVisualState property changed.
            * 
            *
            * @note Due to a work around for a Qt Core issue with accessing enums from QML
            * the argument of this signal doesn't follow naming convention for signals in
            * which the signal arguments are typically named to match the associated property's name.
            * Use the object's property to access current property value instead of the signal argument
            * to avoid runtime errors (i.e. use @c sidebarVisualState instead of @c newSidebarVisualState).
            *
            * @param newSidebarVisualState The new value of the @c #sidebarVisualState property.
            *
            * @since BlackBerry 10.0.0
            */
            void sidebarVisualStateChanged(bb::cascades::SidebarVisualState::Type newSidebarVisualState);

        private:
            /*! \cond PRIVATE */
            QDeclarativeListProperty<bb::cascades::Tab> tabs();
            Q_DECLARE_PRIVATE(TabbedPane)
            Q_DISABLE_COPY(TabbedPane)
            /*! \endcond */            

        public:
            /*! \cond PRIVATE */
            typedef TabbedPane ThisClass; 
            typedef AbstractPane BaseClass;
            /*! \endcond */

           /*!
            * @brief A builder template for constructing a %TabbedPane.
            *
            * See TabbedPane::create() for getting a concrete builder for constructing a %TabbedPane.
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
                * @brief Adds a @c %Tab to the %TabbedPane.
                *
                * New tabs are added as the last child in the @c %TabbedPane.
                * The @c %Tab that is passed must not be @c 0 or it will be ignored. If the @c %Tab is
                * already a child of the @c %TabbedPane that it is being added to, the operation fails. 
                * If the @c %Tab is currently a child of another @c %TabbedPane, it is removed as a child 
                * from that @c %TabbedPane, and ownership is transferred to the new @c %TabbedPane.
                *
                * @param tab The @c %Tab to be added; must not be @c 0 or it will be ignored.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& add(bb::cascades::Tab* tab)
                {
                    this->instance().add(tab);
                    return this->builder();
                }

                /*!
                 * @copydoc bb::cascades::TabbedPane::setActivePane(bb::cascades::AbstractPane*)
                 */
                BuilderType& activePane(bb::cascades::AbstractPane* activePane)
                {
                    this->instance().setActivePane(activePane);
                    return this->builder();
                }

               /*!
                * @copydoc bb::cascades::TabbedPane::setShowTabsOnActionBar(bool)
                */
                BuilderType& showTabsOnActionBar(bool showTabsOnActionBar)
                {
                    this->instance().setShowTabsOnActionBar(showTabsOnActionBar);
                    return this->builder();
                }

               /*!
                * @copydoc bb::cascades::TabbedPane::setSidebarState(bb::cascades::SidebarState::Type)
                */
                BuilderType& sidebarState(bb::cascades::SidebarState::Type sidebarState)
                {
                    this->instance().setSidebarState(sidebarState);
                    return this->builder();
                }

               /*!
                * @brief Sets the peeking behavior of this @c %TabbedPane.
                *
                * Using the builder to create a @c %TabbedPane:
                * @code
                * TabbedPane* tappedPane = TabbedPane::create()
                *                          .peek(false);
                * @endcode
                *
                * Using this convenience function in the builder pattern is equivalent to the
                * following:
                *
                * @code
                * myTappedPane->setPeekEnabled(false);
                * @endcode
                *
                * @param enabled If @c true peeking is enabled, if @c false peeking is disabled.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& peek(bool enabled)
                {
                    this->instance().setPeekEnabled(enabled);
                    return this->builder();
                }
            };

           /*!
            * @brief A concrete builder class for constructing a %TabbedPane.
            *
            * @since BlackBerry 10.0.0
            */
            class Builder : public TBuilder<Builder, TabbedPane>
            {
            public:
                explicit Builder() : TBuilder<Builder, TabbedPane>(new TabbedPane()) {}
            };

           /*!
            * @brief Creates and returns a Builder for constructing a @c %TabbedPane.
            *
            * Using the builder model to create a @c %TabbedPane with a page:
            *
            * @code
            * TabbedPane* tabbedPane = TabbedPane::create()
            *     .showTabsOnActionBar(true);
            *     .add(Tab::create()
            *         .title("My tab")
            *         .content(Page::create())
            *      )
            * @endcode
            *
            * @return A builder for constructing a @c %TabbedPane.
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

QML_DECLARE_TYPE(bb::cascades::TabbedPane)


#endif 
