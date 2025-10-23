/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_navigationpane_h
#define cascades_navigationpane_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractpane.h>
#include <bb/cascades/controls/page.h>

namespace bb {
    namespace cascades {

        class NavigationPanePrivate;

        /*!
        * @brief A class that is used for stack-like navigation between @c Page objects.
        * 
        * The @c %NavigationPane keeps track of a stack of @c %Page objects that can be
        * pushed and popped on the stack. Only the topmost page on the stack is displayed to the 
        * user. The @c push() function adds a new page on the top of the navigation stack, 
        * displaying it while hiding the old page. The @c pop() function hides 
        * the page currently on the top of the stack, removing it from the navigation stack and
        * displaying the previous page again.
        *
        * @image html navigation_pane_push_pop.png
        * 
        * The following example creates a @c %NavigationPane and adds a page. A second page
        * is created and added to the @c %NavigationPane when nextAction is triggered. The second 
        * page has a custom back button set through the @c NavigationPaneProperties class. The 
        * @c %NavigationPaneProperties class handles properties set to the @c %NavigationPane in order
        * to customize it.
        *
        * The default back button will have a standard back icon and the title "Back".
        *
        * @image html actionlist.png This is how the back button will look like by default.
        *
        * Here's an example of how to use @c %NavigationPane in QML:
        *
        * 
        * @code
        * // navigationpane.qml
        * 
        * NavigationPane {
        *     id: navigationPane
        *     Page {
        *         Container {
        *             Label { 
        *                 text: "First page" 
        *             }
        *         }
        *
        *         actions: [
        *             ActionItem {
        *                 title: "Next page"
        *                 ActionBar.placement: ActionBarPlacement.OnBar
        *                 onTriggered: {
        *                     var page = pageDefinition.createObject();
        *                     navigationPane.push(page);
        *                 }
        *
        *                 attachedObjects: ComponentDefinition {
        *                     id: pageDefinition;
        *                     source: "secondpage.qml"
        *                 }
        *             }
        *         ]
        *     }
        *     onPopTransitionEnded: { page.destroy(); }
        * }
        * @endcode
        *
        * @code
        * // secondpage.qml
        *
        * Page {
        *     Container {
        *         Label { 
        *             text: "Second page" 
        *         }
        *     }
        *     paneProperties: NavigationPaneProperties {
        *         backButton: ActionItem {
        *             title: "Previous page"
        *             imageSource: "asset:///back.png"
        *             onTriggered: { navigationPane.pop(); }
        *         }
        *     }
        * }
        * @endcode
        *
        * And here's how to do the same using C++:
        *
        * @code
        * NavigationPane* navigationPane;
        *
        * void initializeNavigationPane()
        * {
        *     ActionItem* nextAction = ActionItem::create()
        *         .title("Next page")
        *         .onTriggered(this, SLOT(pushPage()));
        *
        *     navigationPane = NavigationPane::create();
        *     QObject::connect(navigationPane, SIGNAL(popTransitionEnded(bb::cascades::Page*)), 
        *         this, SLOT(popFinished(bb::cascades::Page*)));
        *
        *     navigationPane->push(Page::create()
        *         .content(Label::create("First page"))
        *         .addAction(nextAction, ActionBarPlacement::OnBar));
        *
        *     Application::instance()->setScene(navigationPane);
        * }
        *
        * void popFinished(bb::cascades::Page* page)
        * {
        *     delete page;
        * }
        *
        * Q_SLOT void pushPage()
        * {
        *     ActionItem* backAction = ActionItem::create()
        *         .title("Previous page")
        *         .imageSource(QUrl("asset:///back.png"))
        *         .onTriggered(navigationPane, SLOT(pop()));
        *
        *     navigationPane->push(Page::create()
        *         .content(Label::create("Second page"))
        *         .paneProperties(NavigationPaneProperties::create()
        *             .backButton(backAction)));
        * }
        * @endcode
        *
        * @xmlonly
        * <qml>
        * <class abstract="yes"/>
        * </qml>
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT NavigationPane : public AbstractPane {
        private:
            Q_OBJECT
                /*!
                * @brief The topmost page on the stack of this @c %NavigationPane.
                * 
                * This is the page that is currently displayed.
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(bb::cascades::Page* top READ top NOTIFY topChanged FINAL)

                /*!
                * @brief Indicates whether the back buttons should be visible on all pushed pages in this
                * @c %NavigationPane.
                * 
                * The back button can be set on individual pages. The back button is never visible on the
                * first page, except when the page is invoked as a Card.
                * This property is @c true by default (back buttons are visible). If no back
                * button has been set on the current page, a default back button is used. The default back
                * button pops the current page and deletes it when the button is clicked.
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(bool backButtonsVisible READ backButtonsVisible WRITE setBackButtonsVisible
                RESET resetBackButtonsVisible NOTIFY backButtonsVisibleChanged FINAL)

                /*!
                 * @brief Indicates whether peeking from within the current @c Page should be enabled.
                 *
                 * When enabled, dragging or swiping to the right inside the content of the
                 * @c Page will reveal the previous @c %Page in the navigation stack.
                 *
                 * This property only controls whether or not peeking is enabled within
                 * the content area of the @c Page. Peeking is
                 * always enabled on the Back button, even if this property is disabled.
                 *
                 * The default value is @c true (enabled).
                 *                
                 *
                 * @since BlackBerry 10.0.0
                 */
                 Q_PROPERTY(bool peekEnabled READ isPeekEnabled WRITE setPeekEnabled
                        RESET resetPeekEnabled NOTIFY peekEnabledChanged FINAL)
        public:

            /*!
            * @brief Constructs a @c %NavigationPane.
            *
            * Creating a @c %NavigationPane object:
            * @code
            * NavigationPane* navigationPane = new NavigationPane();
            * navigationPane->push(new Page());
            * @endcode
             *
             * @since BlackBerry 10.0.0
            */
            explicit NavigationPane(QObject* parent = 0);

            /*!
            * @brief Destructs this @c %NavigationPane.
             *
             * @since BlackBerry 10.0.0
            */
            virtual ~NavigationPane();

            /*!
            * @brief Returns the current topmost page on the stack of this @c %NavigationPane.
            * 
            * The @c %NavigationPane remains as the parent of the page.
            *
            * @return The topmost page on the @c %NavigationPane stack. Returns @c 0 if the stack
            * is empty.
             *
             * @since BlackBerry 10.0.0
            */
            bb::cascades::Page* top() const;

            /*! 
            * @brief Pushes a Page onto the stack of this @c %NavigationPane.
            * 
            * The pushed page is placed on the top of the navigation stack, and is displayed to
            * the user. The @c %NavigationPane takes the ownership of the pushed page. The owner
            * of the pushed page must be @c 0.
            * 
            * If the owner of the pushed page is not @c 0, or if the pushed page itself is @c 0, 
            * nothing will happen.
            *
            * This function will emit the @c topChanged() signal and when the transition is finished,
            * this function emits the @c pushTransitionEnded() signal.
            * 
            * @param child The new top child page. The parent for the page must either be @c 0 
            * or this @c %NavigationPane.
            * 
            * @see @c push(Page*), @c pop(), @c pushTransitionEnded()
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void push(bb::cascades::Page* child);

           /*! 
            * @brief Pops the top page from the stack of this @c %NavigationPane. 
            * 
            * If the stack is not empty, this function emits the topChanged() signal immediately. 
            * When the the transition is finished, the popTransitionEnded() signal is also emitted.
            * 
            * The @c %NavigationPane keeps the ownership of the Page. The Page can be safely deleted 
            * at any time after the call to pop(). If the @c Page happens to be deleted before the @c popTransitionEnded() 
            * signal has been emitted, that signal will have the parameter for the popped @c Page set to @c 0. 
            *
            * The popped @c Page can not be pushed to another control (e.g. another @c %NavigationPane) until after the 
            * @c popTransitionEnded() signal has been received. 
            * Furthermore, in order to be able to push the popped Page to another control after the @c popTransitionEnded() signal 
            * has been received, its parent must also be set to zero. 
            *
            * @return The page that was popped from the navigation stack. If the navigation stack
            *         was empty, @c 0 is returned.
            *
            * @see popTransitionEnded(), push()
            *
            * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bb::cascades::Page* pop();

            /*!
             * @brief Navigates to the specified page if it is present in the stack of this @c %NavigationPane.
             *
             * If the page is present in the stack, this function emits the topChanged() signal immediately.
             * Any pages above the one navigated to in the stack will be removed from the stack with a single transition animation.
             *
             * When the the transition is finished, this function emits the @c navigateToTransitionEnded() signal
             * The @c %NavigationPane keeps the ownership of the pages. The pages can be safely deleted
             * at any time after the call to navigateTo().
             *
             * If a given page happens to be deleted before the @c navigateToTransitionEnded() signal has been emitted,
             * that page will be excluded from the list of removed pages that are passed as input parameter to the @c navigateToTransitionEnded() signal.
             *
             * The removed pages can not be pushed to another control (e.g. another @c %NavigationPane) until after the
             * @c navigateToTransitionEnded() signal has been received.
             * Furthermore, in order to be able to push a removed Page to another control after the @c navigateToTransitionEnded() signal
             * has been received, its parent must also be set to zero.
             *
             * @return A @c QVariantList containing the pages that were removed from the @c %NavigationPane stack. If the navigation stack
             *         was empty, or the targetPage was not present in the stack, an empty list is returned.
             *
             * @see navigateToTransitionEnded(), push()
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT QVariantList navigateTo(bb::cascades::Page* targetPage);

            /*!
            * @brief Indicates whether back buttons are visible or not for this @c %NavigationPane.
            *
            * @return @c true if back buttons are visible, @c false otherwise.
             *
             * @since BlackBerry 10.0.0
            */
            bool backButtonsVisible() const;

            /*!
            * @brief Sets whether back buttons should be visible or not for this @c %NavigationPane.
            *
            * @param visible If @c true back buttons should be visible, if @c false back buttons
            * should not be visible.
             *
             * @since BlackBerry 10.0.0
            */
            Q_SLOT void setBackButtonsVisible(bool visible);

            /*!
            * @brief Resets the visibility of back buttons to its default state, which is visible.
             *
             * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetBackButtonsVisible();
            
            /*!
            * @brief Returns the number of pages in the navigation stack.
            *        
            * @return The number of pages in the navigation stack.
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE int count() const;
            
            /*!
            * @brief Returns a page at the specified index.
            *
            * The index starts from the bottom of the stack, so the bottom page will have index 0.
            * Once completed, ownership of the page remains with the @c %NavigationPane.
            *
            * @param index The index of the page.
            * @return The requested page if the index was valid, @c 0 otherwise.
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bb::cascades::Page* at(int index) const;
            
            /*!
            * @brief Returns the index of a page.
            *
            * The index starts from the bottom of the stack, so the bottom page will have index 0.
            * If the page isn't in the navigation stack or the page is @c 0, @c -1 is returned.             
            *
            * @param page The page to get the index from.
            * @return The index of the specified page if the page is valid, @c -1 otherwise.
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE int indexOf(bb::cascades::Page* page) const;
            
            /*!
            * @brief Inserts a page at a specified index in the @c %NavigationPane.
            *
            * The page that is passed must not be @c 0 or it will be ignored.
            * If the page is already present in the navigation stack, the operation will fail.
            * This operation will not trigger a transition effect, even if the page is added to
            * the top of the stack.
            * If a transition effect is desired, use @c push() instead.
            * The @c topChanged() signal will be emitted if the operation affects the top node.
            *
            * @param index The index where the page will be placed. If the index < 0 the
            * the page is inserted in the bottom. If the index > the number
            * of pages in the navigation stack, it is added on top of the stack.
            * @param page The page to be inserted, must not be @c 0.
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void insert(int index, bb::cascades::Page *page);
            
            /*!
            * @brief Removes a page from the navigation stack.
            *
            * Once the page is removed, the @c %NavigationPane no longer references it, but it is still 
            * owned by the @c %NavigationPane. It is up to the application to either delete the removed 
            * page, transfer its ownership (by setting its parent) to another object or leave 
            * it as a child of the @c %NavigationPane (in which case it will be deleted with the @c %NavigationPane).
            *
            * This operation will not trigger a transition effect, even if removing the top page.
            * If a transition effect is desired, use pop() instead.
            * The @c topChanged() signal will be emitted if the operation affects the top node.
            *
            * @param page The page to be removed; must not be @c 0.
            * @return @c true if the page was present in the navigation stack, @c false otherwise.
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE bool remove(bb::cascades::Page *page);

            /*!
            * @brief Indicates whether peeking from within the content area of the current page is enabled.
            * 
            * Peeking is always enabled on the Back button, even if this property is disabled.
            *
            * @return @c true if peeking is enabled, @c false otherwise.
             *
             * @since BlackBerry 10.0.0
            */
            bool isPeekEnabled() const;

            /*!
            * @brief Sets whether peeking from within the current @c Page should be enabled.
            *
            * Setting this property only controls whether or not peeking
            * is enabled within the content area of the @c Page. Peeking is
            * always enabled on the Back button, even if this property is disabled.
            *
            * @param enabled If @c true peeking be enabled, if @c false peeking is disabled.
             *
             * @since BlackBerry 10.0.0
            */
            Q_SLOT void setPeekEnabled(bool enabled);

            /*!
            * @brief Resets the peeking behavior of the @c %NavigationPane to its default state, which is disabled.
            *
            * Setting this property only controls whether or not peeking
            * is enabled within the content area of the @c Page area of the @c Page. Peeking is
            * always enabled on the Back button, even if this property is disabled.
             *
             * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetPeekEnabled();

Q_SIGNALS:

            /*!
            * @brief Emitted when the topmost page on the stack of this @c %NavigationPane has changed.
            *
            * This signal will be emitted as soon as the stack changes. This occurs when the @c pop(), 
            * and @c push() functions are called. This signal is also emitted when the 
            * back button is pressed.
            * 
            * @param page The new topmost page in the navigation stack if the stack is not empty, @c 0
            * otherwise.
             *
             * @since BlackBerry 10.0.0
            */
            void topChanged(bb::cascades::Page* page);

            /*!
            * @brief Emitted when a page has been pushed onto the stack of this @c %NavigationPane.
            *
            * @param page The page that was pushed.
             *
             * @since BlackBerry 10.0.0
            */
            void pushTransitionEnded(bb::cascades::Page* page);

            /*!
            * @brief Emitted when a page has been popped from the stack of this @c %NavigationPane.
            *
            * If the @c Page was removed from the stack as a result of a @c navigateTo() call on this @c %NavigationPane,
            * the @c navigateToTransitionEnded() signal is emitted instead.
            *
            * The @c %NavigationPane keeps the ownership of the @c Page, but it can be deleted if it's no longer needed.
            * Furthermore, in order to be able to push the popped @c Page to another control, its parent must first be set to zero. 
            *
            * @param page The page that was popped. @c 0 if the page has already been deleted.
             *
             * @since BlackBerry 10.0.0
            */
            void popTransitionEnded(bb::cascades::Page* page);

            /*!
            * @brief Emitted when one or more pages have been removed from the stack of this @c %NavigationPane
            * as a result of a call to @c navigateTo() on this @c %NavigationPane.
            *
            * The @c %NavigationPane keeps the ownership of the removed pages, but they can be deleted if they are no longer needed.
            * Furthermore, in order to be able to push a removed Page to another control, its parent must first be set to zero.
            *
            * @param pages A @c QVariantList containing the pages that were removed. Pages deleted before this signal is emitted are excluded from the list.
             *
             * @since BlackBerry 10.0.0
            */
            void navigateToTransitionEnded(QVariantList pages);

            /*!
            * @brief Emitted when the visibility of back buttons has changed for this @c %NavigationPane.
            *
            * @param visible If @c true back buttons are visible, if @c false back buttons are not
            * visible.
             *
             * @since BlackBerry 10.0.0
            */
            void backButtonsVisibleChanged(bool visible);

            /*!
            * @brief Emitted when peeking on the @c %NavigationPane is enabled or disabled.
            *
            * @param enabled If @c true peeking is enabled, if @c false peeking is disabled.
             *
             * @since BlackBerry 10.0.0
            */
            void peekEnabledChanged(bool enabled);

        protected:
            /*! \cond PRIVATE */
            explicit NavigationPane(NavigationPanePrivate &_d_ptr, QObject* parent = 0);
            /*! \endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(NavigationPane)
            Q_DISABLE_COPY(NavigationPane)

            typedef NavigationPane ThisClass; 
            typedef AbstractPane BaseClass;
            /*! @endcond */

        public:
            /*!
            * @brief A template builder class for constructing a @c %NavigationPane.
            * 
            * To retrieve the builder, call @c NavigationPane::create().
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
                * @brief Adds a Page to this @c %NavigationPane.
                * 
                * Using the builder to create a @c %NavigationPane:
                * @code
                * NavigationPane* navigationPane = NavigationPane::create()
                *                                    .add(newPage);
                * @endcode
                *
                * Using this convenience function in the builder pattern is equivalent to the
                * following:
                * 
                * @code
                * myNavigationPane->push(newPage);
                * @endcode
                * 
                * @param page The page to add.
                * 
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& add(bb::cascades::Page* page)
                {
                    this->instance().push(page);
                    return this->builder();
                }

                /*!
                * @brief Sets the visibility of back buttons for this @c %NavigationPane.
                * 
                * Using the builder to create a @c %NavigationPane:
                * @code
                * NavigationPane* navigationPane = NavigationPane::create()
                *                                  .backButtons(false);
                * @endcode
                *
                * Using this convenience function in the builder pattern is equivalent to the
                * following:
                * 
                * @code
                * myNavigationPane->setBackButtonsVisible(false);
                * @endcode
                *
                * @param visible If @c true back buttons should be visible, if @c false back
                * buttons should not be visible.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& backButtons(bool visible)
                {
                    this->instance().setBackButtonsVisible(visible);
                    return this->builder();
                }

                /*!
                * @brief Sets the peeking behavior of this @c %NavigationPane.
                * 
                * Using the builder to create a @c %NavigationPane:
                * @code
                * NavigationPane* navigationPane = NavigationPane::create()
                *                                  .peek(false);
                * @endcode
                *
                * Using this convenience function in the builder pattern is equivalent to the
                * following:
                * 
                * @code
                * myNavigationPane->setPeekEnabled(false);
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
            * @brief A builder for constructing a @c %NavigationPane.
            * 
            * To retrieve the builder, call @c NavigationPane::create().
            *
            * @since BlackBerry 10.0.0
            */
            class Builder : public TBuilder<Builder, NavigationPane> {
            public:
                explicit Builder() : TBuilder<Builder, NavigationPane>(new NavigationPane()) {}
            };

            /*!
            * @brief Creates and returns a builder for constructing a @c %NavigationPane.
            *
            * Using the builder to create a @c %NavigationPane:
            * @code
            * NavigationPane* navigationPane = NavigationPane::create();
            * @endcode
            * @return A builder used for constructing a @c %NavigationPane.
             *
             * @since BlackBerry 10.0.0
            */
            static Builder create() {
                return Builder();
            }
        };
    }
}

QML_DECLARE_TYPE(bb::cascades::NavigationPane)

#endif 
