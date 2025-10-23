/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstractpane_h
#define cascades_abstractpane_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/AbstractA11yObject>
#include <bb/cascades/core/systemshortcuts.h>

namespace bb {
    namespace cascades {
    
    class AbstractPanePrivate;
    class PaneProperties;
    class KeyListener;
    class AbstractShortcut;

    /*!
     * @brief An abstract class that provides functionality for inherited page and pane classes.
     * 
     * Only classes deriving from the @c %AbstractPane class can be set
     * as the root component of an application. This means that every application will have at least one object that
     * derives from @c %AbstractPane.
     *
     * @c %AbstractPane has an attribute called @c #paneProperties, which contains properties used for
     * visual representation within its parent (for example, a title or icon).
     * The type of pane properties of the child must match up with parent. For example, if you add a @c Page to a
     * @c NavigationPane, the @c %Page must use @c NavigationPaneProperties.
     *
     * @c %AbstractPane has another attribute called @c #peekedAt. When @c true, a user is currently "peeking" at
     * the @c %AbstractPane from another pane. Depending on the type of @c %AbstractPane, peeking behaves differently.
     * In a @c NavigationPane, the user can swipe from left to right to peek at the previous pane in the stack, or
     * drag the Back button to peek at root pane. On a @c Sheet, the user can swipe
     * from left to right to peek at the content directly beneath it.
     *
     * Here's an example that shows "peeking" from a sheet to the page behind it.
     *
     * @image html peek_example.png
     *
     * @see @c Page, @c TabbedPane, @c NavigationPane
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbstractPane : public UIObject {
        Q_OBJECT

        /*!
         * @brief The pane properties for this @c %AbstractPane.
         *
         * The @c paneProperties property specifies data that the parent @c %AbstractPane may use.
         * The type of pane properties of the child must match up with parent. For example, if you add a
         * @c Page to a @c NavigationPane, you must use @c NavigationPaneProperties.
         *
         * By default, the @c paneProperties of an @c AbstractPane is @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::PaneProperties* paneProperties READ paneProperties WRITE setPaneProperties
                   RESET resetPaneProperties NOTIFY panePropertiesChanged FINAL)

        /*!
         * @brief Indicates whether this @c %AbstractPane is being "peeked" at.
         *
         * If @c true, the pane is currently being revealed by peeking from a @c Sheet or a @c Page within
         * a @c NavigationPane. By default, the value is @c false, indicating that the pane is not currently being peeked at.
         *
         * If a @c %NavigationPane is being peeked at, both the @c %NavigationPane and its currently visible
         * page will return @c true for the @c peekedAt property.
         *
         * As a convenience, there are two signals available called @c %peekStarted and @c %peekEnded, which are emitted when
         * a peek on the @c %AbstractPane starts or ends.
         *
         * The @c peekedAtChanged() signal is emitted when @c peekedAt changes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool peekedAt READ isPeekedAt NOTIFY peekedAtChanged FINAL)

       /*!
        * @brief A list of shortcuts that can be triggered via user actions.
        *
        * The order in which they are added will determine which shortcut will be triggered in case of an overlap.
        * Predefined shortcuts take precedence over shortcuts defined via @c QString in case of a collision.
        *                
        * @see AbstractShortcut        
        *
        * @xmlonly
        * <qml>
        * <property name="shortcuts" listType="bb::cascades::AbstractShortcut" defaultProperty="no"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.1.0
        */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractShortcut> shortcuts READ shortcuts FINAL)

       /*!
        * @brief A list of key listeners attached to this abstract pane.
        *
        * The order in which key listeners are added does not change their behavior.
        *                
        * @see KeyListener        
        *
        * @xmlonly
        * <qml>
        * <property name="keyListeners" listType="bb::cascades::KeyListener" defaultProperty="no"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.1.0
        */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::KeyListener> keyListeners READ keyListeners FINAL)

        /*!
         * @brief Defines this pane's accessibility object.
         *
         * Accessibility objects are used by assistive technologies for
         * people with disabilities or special needs (for example, visual impairment).
         *
         * @see @c Control::accessibility
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bb::cascades::AbstractA11yObject* accessibility READ accessibility REVISION 2 FINAL)


        /*!
         * @brief Enables or disables all AbstractPane's core shortcuts.
         *
         * This property is used when all AbstractPane's core shortcuts should be enabled or disabled.
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bool builtInShortcutsEnabled READ builtInShortcutsEnabled WRITE setBuiltInShortcutsEnabled
                   RESET resetBuiltInShortcutsEnabled NOTIFY builtInShortcutsEnabledChanged REVISION 2 FINAL)
    public:
        virtual ~AbstractPane();
       
       /*!
        * @brief Adds a shortcut to the @c %AbstractPane. 
        *
        * @c %AbstractPane will always take ownership as shortcuts should never be shared.
        * If the shortcut already belongs to the @c %AbstractPane or the @c shortcut is @c 0, nothing will happen.        
        * The order in which shortcuts are added will determine which shortcut will be triggered in case of an overlap.  
        *
        * @param shortcut The @c AbstractShortcut to add to the @c %AbstractPane.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void addShortcut(bb::cascades::AbstractShortcut* shortcut);

       /*!
        * @brief Removes a shortcut from the @c %AbstractPane. 
        *
        * Once the shortcut is removed, the @c %AbstractPane no longer references it, but it is still 
        * owned by the @c %AbstractPane. It is up to the application to either delete the removed 
        * shortcut, transfer its ownership (by setting its parent) to another object, or leave 
        * it as a child of the @c %AbstractPane (in which case it will be deleted with the @c %AbstractPane).
        *
        * @param shortcut The @c AbstractShortcut to remove.
        * @return @c true if the shortcut was owned by the @c %AbstractPane, @c false otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bool removeShortcut(bb::cascades::AbstractShortcut* shortcut);

       /*!
        * @brief Removes all of AbstractPane's shortcuts and frees up their memory.        
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void removeAllShortcuts();      

       /*!
        * @brief Returns the number of shortcuts.
        *
        * @return The number of shortcuts.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE int shortcutCount() const;

       /*!
        * @brief Returns a shortcut at the specified index. 
        *
        * Ownership of the shortcut remains with the @c %AbstractPane.
        *                       
        * @param index The index of the shortcut.
        * @return The requested shortcut if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bb::cascades::AbstractShortcut* shortcutAt(int index) const;

       /*!
        * @brief Enables all shortcuts attached to the @c %AbstractPane.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void enableAllShortcuts();
        
       /*!
        * @brief Disables all shortcuts attached to the @c %AbstractPane.
        * 
        * Shortcuts that are attached afterward will use the default enabled state.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void disableAllShortcuts();

       /*!
        * @brief Sets the enabled state of all built-in shortcut attached to the @c %AbstractPane at a system level
        *
        * @param enabled If @c true all built-in shortcuts are enabled, and if @c false all shortcut are disabled.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_SLOT void setBuiltInShortcutsEnabled(bool enabled);


       /*!
        * @brief Returns a builtInShortcutsEnabled property value.
        *
        * @return true if builtInShortcutsEnabled property is set to @c true and @c false otherwise
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_INVOKABLE bool builtInShortcutsEnabled() const;

       /*!
        * @brief Resets a builtInShortcutsEnabled property to default value.
        *
        * Default value is true.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_SLOT void resetBuiltInShortcutsEnabled();

       /*!
        * @brief Sets the enabled state of the built-in shortcuts attached to the @c %AbstractPane at a system level
        *
        * Built-in shortcuts that are attached afterward will use the specified enabled state.
        *
        * @note Selected Built-in shortcut can be enabled or disbaled only if @c AbstractPane::builtInShortcutsEnabled
        * property is set to true.
        *
        * @param type The system shortcut type
        * @param enabled If @c true the shortcut is enabled, and if @c false the shortcut is disabled.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_INVOKABLE void setBuiltInShortcutEnabled(bb::cascades::SystemShortcuts::Type type, bool enabled);
        
        /*!
        * @brief Adds a key listener to the @c %AbstractPane. 
        *
        * @c %AbstractPane will always take ownership as key listener should never be shared.
        * If the key listener already belongs to the @c %AbstractPane or the @c key listener is @c 0, nothing will happen.               
        *      
        * @param keyListener The @c KeyListener to add to the @c %AbstractPane.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void addKeyListener(bb::cascades::KeyListener* keyListener);

        /*!
        * @brief Removes a key listener from the @c %AbstractPane. 
        *
        * Once the key listener is removed, the @c %AbstractPane no longer references it, but it is still 
        * owned by the @c %AbstractPane. It is up to the application to either delete the removed 
        * key listener, transfer its ownership (by setting its parent) to another object, or leave 
        * it as a child of the @c %AbstractPane (in which case it will be deleted with the @c %AbstractPane).
        *
        * @param keyListener The @c KeyListener to remove.
        * @return @c true if the key listener was owned by the @c %AbstractPane, @c false otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bool removeKeyListener(bb::cascades::KeyListener* keyListener);

       /*!
        * @brief Removes all of AbstractPane's key listeners and frees up their memory.        
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void removeAllKeyListeners();      

        /*!
        * @brief Returns the number of key listeners.
        *
        * @return The number of key listeners.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE int keyListenerCount() const;

       /*!
        * @brief Returns a key listener at the specified index. 
        *
        * Ownership of the key listener remains with the @c %AbstractPane.
        *                       
        * @param index The index of the key listener.
        * @return The requested key listener if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bb::cascades::KeyListener* keyListenerAt(int index) const;
        
        /*!
         * @brief Returns the @c PaneProperties object for the pane.
         *
         * Ownership of the @c %PaneProperties object remains unchanged.
         *
         * @return The @c %PaneProperties for the pane.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::PaneProperties* paneProperties() const;

        /*!
         * @brief Sets the @c #paneProperties property for the pane.
         *
         * The pane takes ownership of the @c PaneProperties object if no other pane owns it already.
         * If the @c %PaneProperties object already has an owner, the properties are applied to the pane,
         * but ownership of the @c %PaneProperties object remains unchanged. If the pane already owns a
         * @c %PaneProperties object, the existing settings are replaced by the specified @c %PaneProperties object
         * and the pane retains ownership of both.
         *
         * @param paneProperties The new @c %PaneProperties for the pane.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPaneProperties(bb::cascades::PaneProperties *paneProperties);

        /*!
         * @brief Resets the @c #paneProperties property for the pane to @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPaneProperties();

        /*!
         * @brief Indicates if this @c %AbstractPane is being peeked at.
         *
         * @return @c true if being peeked at, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isPeekedAt() const;

        /*!
         * @brief Returns the accessibility object.
         *
         * @return The accessibility object.
         *
         * @since BlackBerry 10.2.0
         */
         bb::cascades::AbstractA11yObject *accessibility() const;

    Q_SIGNALS:

        /*!
         * @brief Emitted when the @c #paneProperties of the pane changes.
         *
         * @param paneProperties The new @c %PaneProperties for the @c %AbstractPane.
         *
         * @since BlackBerry 10.0.0
         */
        void panePropertiesChanged(bb::cascades::PaneProperties *paneProperties);

        /*!
         * @brief Emitted when the @c #peekedAt property of this @c %AbstractPane changes.
         *
         * @param peekedAt If @c true the @c %AbstractPane is being peeked at, otherwise
         * false.
         *
         * @since BlackBerry 10.0.0
         */
        void peekedAtChanged(bool peekedAt);

        /*!
         * @brief Emitted when a peek on this @c %AbstractPane starts.
         *
         * @since BlackBerry 10.0.0
         */
        void peekStarted();

        /*!
         * @brief Emitted when a peek on this @c %AbstractPane ends.
         *
         * @since BlackBerry 10.0.0
         */
        void peekEnded();

        /*!
         * @brief Emitted when the @c #builtInShortcutsEnabled property changes.
         *
         * @param builtInShortcutsEnabled The new value.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
         void builtInShortcutsEnabledChanged(bool builtInShortcutsEnabled);

    protected:
        /*! \cond PRIVATE */
        explicit AbstractPane(AbstractPanePrivate &_d_ptr, QObject* parent = 0);
        /*! \endcond */

    private:

        Q_DECLARE_PRIVATE(AbstractPane)
        Q_DISABLE_COPY(AbstractPane)

        /*! \cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::AbstractShortcut> shortcuts();
        QDeclarativeListProperty<bb::cascades::KeyListener> keyListeners();
        typedef AbstractPane ThisClass;
        typedef UIObject BaseClass;
        /*! \endcond */

   public:
        /*! @cond PRIVATE
         * Workaround for the Qt bug that prevents our enums from being
         * function arguments in QML.
         */
        Q_REVISION(2)
        Q_INVOKABLE void setBuiltInShortcutEnabled(int type, bool enabled);
        /*! \endcond */

       /*!
        * @brief A builder template for constructing an @c %AbstractPane.
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
             * @brief Sets the layout properties for the pane.
             *
             * The pane takes ownership of the @c %PaneProperties object if no other pane owns it already.
             * If the @c %PaneProperties object already has an owner, the properties are applied to the control,
             * but ownership of the @c %PaneProperties object remains unchanged. If the pane already owns a
             * @c %PaneProperties object, the existing settings are replaced by the specified @c %PaneProperties object
             * and the pane retains ownership of both.
             *
             * @param paneProperties The new @c %PaneProperties for the pane.
             *
             * @see @c AbstractPane::paneProperties
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& paneProperties(PaneProperties* paneProperties) {
                this->instance().setPaneProperties(paneProperties);
                return this->builder();
            }

            /*!
            * @brief Adds a shortcut to the @c %AbstractPane. 
            *
            * @c %AbstractPane will always take ownership as shortcuts should never be shared.
            * If the shortcut already belongs to the @c %AbstractPane or the @c shortcut is @c 0, nothing will happen.        
            * The order in which shortcuts are added will determine which shortcut will be triggered in case of an overlap.
            *
            * @param shortcut The @c AbstractShortcut to add to the @c %AbstractPane.
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& addShortcut(AbstractShortcut* shortcut) {
                this->instance().addShortcut(shortcut);
                return this->builder();
            }

            /*!
            * @brief Adds a key listener to the @c %AbstractPane. 
            *
            * @c %AbstractPane will always take ownership as key listener should never be shared.
            * If the key listener already belongs to the @c %AbstractPane or the @c key listener is @c 0, nothing will happen.               
            *
            * @param keyListener The @c KeyListener to add to the @c %AbstractPane.
            *
            * @since BlackBerry 10.1.0
            */            
            BuilderType& addKeyListener(KeyListener* keyListener) {
                this->instance().addKeyListener(keyListener);
                return this->builder();
            }/*!
            * @brief Sets the accessibility name property of the @c %AbstractPane.
            *
            * @param name The text string to use as the accessibility name of the control.
            *
            * @see Control::accessibility
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityName(const QString & name) {
                this->instance().accessibility()->setName(name);
                return this->builder();
            }

           /*!
            * @brief Sets the accessibility description property of the @c %AbstractPane.
            *
            * @param description The text string to use as the accessibility description of the control.
            *
            * @see Control::accessibility
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityDescription(const QString & description) {
                this->instance().accessibility()->setDescription(description);
                return this->builder();
            }

           /*!
            * @brief Adds a label object to the list of labels in the accessibility object.
            *
            * @param labelledBy The object to add as an accessibility label for the @c AbstractPane.
            *
            * @see Control::accessibility
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityAddLabel(bb::cascades::UIObject* labelledBy) {
                this->instance().accessibility()->addLabel(labelledBy);
                return this->builder();
            }

            /*!
             * @brief Sets the builtInShortcutsEnabled property.
             *
             * @param enabled If the AbstractPane's built-in shortcuts should be enabled and false otherwise.
             *
             * @see AbstractPane::builtInShortcutsEnabled
             *
             * @since BlackBerry 10.2.0
             */
             BuilderType& builtInShortcutsEnabled(bool enabled)
             {
                 this->instance().setBuiltInShortcutsEnabled(enabled);
                 return this->builder();
             }
        };
    };
}
}

QML_DECLARE_TYPE(bb::cascades::AbstractPane)

#endif
