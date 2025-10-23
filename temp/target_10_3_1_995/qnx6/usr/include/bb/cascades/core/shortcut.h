/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_shortcut_h
#define cascades_shortcut_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/abstractshortcut.h>

namespace bb {
    namespace cascades {
        
        class ShortcutPrivate;

        /*!  
        * @brief Represents a shortcut that can be invoked on objects that inherit from @c Control, @c AbstractPane, 
        * and @c AbstractActionItem.        
        *
        * The @c %Shortcut events propagate from the control in focus up to the root of the scene.
        * In case no control is currently in focus, all shortcut events are redirected to the root (eg. @c Page).
        *
        * If a @c %Shortcut is attached to an @c ActionItem, the @c ActionItem::triggered() signal is emitted
        * when the specified @c %Shortcut key is pressed.     
        *
        * You can specify a character to be used to trigger a particular @c %Shortcut: 
        *
        * @snippet tad/examples/shortcut/application/src/ShortcutExamples.cpp shortcut_cpp1
        *
        * Here's an example of creating a key @c %Shortcut by calling the constructor
        * and connecting to each signal individually:
        *
        * @snippet tad/examples/shortcut/application/src/ShortcutExamples.cpp shortcut_cpp2
        *
        * And here's how to create a key shortcut for a @c %Control using QML:
        * @snippet tad/examples/shortcut/application/assets/main.qml shortcut_qml1
        * 
        * @xmlonly
        * <apigrouping group="User interface/Events"/>
        * @endxmlonly		
         *
         * @since BlackBerry 10.1.0
        */

        class BBCASCADES_EXPORT Shortcut : public AbstractShortcut {
            Q_OBJECT
            
            /*!
             * @brief A string that will trigger this shortcut.
             *
             * The default value is a null @c QString, indicating that no key will trigger this shortcut.
             *
             * @since BlackBerry 10.1.0
             */
            Q_PROPERTY(QString key READ key WRITE setKey RESET resetKey NOTIFY keyChanged FINAL)
            
        public:
            
            /*!
             * @brief Default constructor. 
             *
             * The resulting @c Shortcut will have @c key set to a null @c QString,
             * meaning the shortcut will not be triggered at all.
             *
             * @since BlackBerry 10.1.0
             */
            explicit Shortcut(UIObject *parent = 0);
            virtual ~Shortcut();
            
            /*!
             * @brief Sets the key or a key combination to be used to trigger this shortcut.
             *
             * If the key is changed, the keyChanged() signal is emitted
             * after the value has been set.
             *
             * The accepted syntax for this string is case insensitive and is defined as follows
             * [Shift+][Alt+]\<Key\>
             *
             * Where:
             *
             * - The key is a single character, symbol or a special key (defined below).
             * - Alpha key values are case insensitive.  The character maps to
             * the key, not the ASCII value. This means that "Shift+a" is the same
             * shortcut as "Shift+A".
             * - Modifiers are optional, but the key must be defined.
             * - '+' must separate modifiers.
             * - The order of modifiers is not important as long as they precede key.
             * - Each modifier may exist exactly once.
             *
             * Special keys have a unique word used to identify them. The available special keys are:
             * - Enter
             * - Space
             * - Backspace
             * - Delete
             * - Escape
             * - Tab
             *
             * Examples:
             * @snippet tad/examples/shortcut/application/src/ShortcutExamples.cpp shortcut_cpp3
             *
             * @param key The key that triggers this shortcut if it is a key shortcut and it is enabled.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void setKey(const QString &key);
            
            /*!
             * @brief Resets the key on the shortcut to a null @c QString.
             *
             * If the key actually changes, the @c keyChanged() signal is emitted
             * after the value has been reset.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void resetKey();
                                   
            /*!
             * @brief Gets the key used to trigger this shortcut
             *
             * @return A key shortcut that can trigger this shortcut. Note that a null @c QString is
             *         returned if the key has not been set.
             *
             * @since BlackBerry 10.1.0
             */
            QString key() const;            
            
        Q_SIGNALS:
            
            /*!
             * @brief Emitted when the key has changed.
             *
             * @param key The new key or key combination to use to trigger this shortcut
             *
             * @since BlackBerry 10.1.0
             */
            void keyChanged(const QString& key);                      
            
        public:
            /*! @cond PRIVATE */
            typedef Shortcut ThisClass;
            typedef AbstractShortcut BaseClass;
            /*! @endcond */
            
            /*!
             * @brief A builder template for constructing a @c %Shortcut. To retrieve the builder, call
             * Shortcut::create().
             *
             * @since BlackBerry 10.1.0
             */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
            {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
                {
                }
            public:
                /*!
                 * @brief Sets a key to use for activating this @c %Shortcut.
                 *
                 * Using this convenience function in the builder pattern is the equivalent of the
                 * following:
                 * @code
                 * myShortcut->setKey("a");
                 * @endcode
                 *
                 * @param shortcutKey The key used to activate this @c %Shortcut.
                 *
                 * @since BlackBerry 10.1.0
                 */
                BuilderType& key(const QString& shortcutKey)
                {
                    this->instance().setKey(shortcutKey);
                    return this->builder();
                }                              
            };
            
            /*!
             * @brief A builder template for constructing a @c Shortcut.
             *
             * To retrieve the builder, call @c Shortcut::create().
             *
             * @since BlackBerry 10.1.0
             */
            class Builder : public TBuilder<Builder, Shortcut>
            {
            public:
                explicit Builder() : TBuilder<Builder, Shortcut>(new Shortcut()) {}
            };
            
            /*!
             * @brief Creates and returns a builder for constructing a @c %Shortcut.
             *
             * Using the builder to create a @c %Shortcut:
             * @code
             * Shortcut* shortcut = Shortcut::create();
             * @endcode
             *
             * @return A builder used for constructing a @c %Shortcut.
             *
             * @since BlackBerry 10.1.0
             */
            static Builder create() {
                return Builder();
            } 
            
        private:            
            Q_DECLARE_PRIVATE(Shortcut)           
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::Shortcut)


#endif // cascades_shortcut_h
