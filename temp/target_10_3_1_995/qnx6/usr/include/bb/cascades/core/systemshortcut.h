/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_systemshortcut_h
#define cascades_systemshortcut_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/abstractshortcut.h>

#include <bb/cascades/core/systemshortcuts.h>

namespace bb {
    namespace cascades {

        class SystemShortcutPrivate;

        /*!
        * @brief Represents a @c Shortcut that can be invoked on objects that inherit from @c Control, @c AbstractPane,
        * and @c AbstractActionItem.
        *
        * Please note that the shortcut events propagate from the control in focus up to the root of the scene.
        * In case no control is currently in focus, all shortcut events are redirected to the root.
        *
        * If a @c %SystemShortcut is attached to an @c ActionItem, the @c ActionItem::triggered() signal is emitted
        * when the specified @c %SystemShortcut key is pressed.  
        *
        * Use of system shortcuts over key shortcuts (where applicable) is strongly
        * recommended, and application developers are encouraged to map these shortcuts
        * to their own actions in a logical way.
        *
        * If there is a conflict between a @c SystemShortcut and a @c %Shortcut,
        * the @c %SystemShortcut will get priority.
        *
        * You can specify a system shortcut type to be used to trigger a particular @c %SystemShortcut, like this:
        *
        * @snippet tad/examples/shortcut/system/src/SystemShortcutExamples.cpp system_cpp1
        *
        * Here's an example of creating a @c %SystemShortcut by calling the constructor
        * and connecting to the signal individually:
        *
        * @snippet tad/examples/shortcut/system/src/SystemShortcutExamples.cpp system_cpp2
        *
        * Here's how to create a @c %SystemShortcut for a @c %Control using QML:
        *
        * @snippet tad/examples/shortcut/system/assets/main.qml system_qml1
        *
        * @xmlonly
        * <apigrouping group="User interface/Events"/>
        * @endxmlonly
        * @since BlackBerry 10.1.0
        */

        class BBCASCADES_EXPORT SystemShortcut : public AbstractShortcut {
            Q_OBJECT

            /*!
             * @brief A system shortcut @c type that will trigger this shortcut.
             *
             * The default value is SystemShortcuts::None, indicating that this
             * shortcut will not be triggered at all.
             *
             * This is an init-time only property. Attempts to change it after
             * initialization has completed will be ignored.
             *
             * @since BlackBerry 10.1.0
             */
            Q_PROPERTY(bb::cascades::SystemShortcuts::Type type READ type WRITE setType FINAL)

        public:
            /*!
             * Default constructor. The resulting @c SystemShortcut will have @c type
             * set to @c SystemShortcuts::None, meaning the shortcut will not be triggered at all.
             *
             * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.1.0
             */
            explicit SystemShortcut(UIObject *parent = 0);

            /*!
             * Constructor.
             *
             * @param type The system shortcut @c type that can trigger this shortcut.
             * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.1.0
             */
            SystemShortcut(bb::cascades::SystemShortcuts::Type type, UIObject *parent = 0);

            virtual ~SystemShortcut();

            /*!
             * @brief Gets the system shortcut @c type used to trigger this shortcut
             *
             * @return The system shortcut @c type that can trigger this shortcut.
             *
             * @since BlackBerry 10.1.0
             */
            bb::cascades::SystemShortcuts::Type type() const;

        public:
            /*! @cond PRIVATE */
            typedef SystemShortcut ThisClass;
            typedef AbstractShortcut BaseClass;
            /*! @endcond */

            /*!
             * @brief A builder template for constructing a @c %SystemShortcut. To retrieve the builder, call
             * SystemShortcut::create().
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
            };

            /*!
             * @brief A builder template for constructing a @c SystemShortcut.
             *
             * To retrieve the builder, call @c SystemShortcut::create().
             *
             * @since BlackBerry 10.1.0
             */
            class Builder : public TBuilder<Builder, SystemShortcut>
            {
            public:
                explicit Builder(bb::cascades::SystemShortcuts::Type type) : TBuilder<Builder, SystemShortcut>(new SystemShortcut(type)) {}
            };

            /*!
             * @brief Creates and returns a builder for constructing a @c %SystemShortcut.
             *
             * Using the builder to create a @c SystemShortcut:
             *
             * @snippet tad/examples/shortcut/system/src/SystemShortcutExamples.cpp system_cpp1
             *
             * @return A builder used for constructing a @c %SystemShortcut.
             *
             * @since BlackBerry 10.1.0
             */
            static Builder create(bb::cascades::SystemShortcuts::Type type) {
                return Builder(type);
            }

        private:
            Q_DECLARE_PRIVATE(SystemShortcut)

            /*! @cond PRIVATE */
            /*!
             * @brief Sets the system shortcut @c type to be used to trigger this shortcut
             *
             * @param type The system shortcut @c type that triggers this shortcut.
             */
            void setType(bb::cascades::SystemShortcuts::Type type);
            /*! @endcond */

        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::SystemShortcut)


#endif // cascades_systemshortcut_h
