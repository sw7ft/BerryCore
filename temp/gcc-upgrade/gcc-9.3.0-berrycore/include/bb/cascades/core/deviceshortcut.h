/* Copyright (C) 2012-2014 Research In Motion Limited.  */

#ifndef cascades_deviceshortcut_h
#define cascades_deviceshortcut_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/abstractshortcut.h>

#include <bb/cascades/core/deviceshortcuts.h>

namespace bb {
    namespace cascades {

        class DeviceShortcutPrivate;

        /*!
        * @brief Represents a @c Shortcut that can be invoked on objects that inherit from @c Control, @c AbstractPane,
        * and @c AbstractActionItem.
        *
        * Please note that the shortcut events propagate from the control in focus up to the root of the scene.
        * In case no control is currently in focus, all shortcut events are redirected to the root.
        *
        * If a @c %DeviceShortcut is attached to an @c ActionItem, the @c ActionItem::triggered() signal is emitted
        * when the specified @c %DeviceShortcut key is pressed.  
        *
        * @xmlonly
        * <apigrouping group="User interface/Events"/>
        * @endxmlonly
        * @since BlackBerry 10.3.1
        */

        class BBCASCADES_EXPORT DeviceShortcut : public AbstractShortcut {
            Q_OBJECT

            /*!
             * @brief A device shortcut @c type that will trigger this shortcut.
             *
             * The default value is DeviceShortcuts::None, indicating that this
             * shortcut will not be triggered at all.
             *
             * This is an init-time only property. Attempts to change it after
             * initialization has completed will be ignored.
             *
             * @since BlackBerry 10.3.1
             */
            Q_PROPERTY(bb::cascades::DeviceShortcuts::Type type READ type WRITE setType FINAL)

        public:
            /*!
             * Default constructor. The resulting @c DeviceShortcut will have @c type
             * set to @c DeviceShortcuts::None, meaning the shortcut will not be triggered at all.
             *
             * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.3.1
             */
            explicit DeviceShortcut(UIObject *parent = 0);

            /*!
             * Constructor.
             *
             * @param type The device shortcut @c type that can trigger this shortcut.
             * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.3.1
             */
            DeviceShortcut(bb::cascades::DeviceShortcuts::Type type, UIObject *parent = 0);

            virtual ~DeviceShortcut();

            /*!
             * @brief Gets the device shortcut @c type used to trigger this shortcut
             *
             * @return The system shortcut @c type that can trigger this shortcut.
             *
             * @since BlackBerry 10.3.1
             */
            bb::cascades::DeviceShortcuts::Type type() const;

        public:
            /*! @cond PRIVATE */
            typedef DeviceShortcut ThisClass;
            typedef AbstractShortcut BaseClass;
            /*! @endcond */

            /*!
             * @brief A builder template for constructing a @c %DeviceShortcut. To retrieve the builder, call
             * DeviceShortcut::create().
             *
             * @since BlackBerry 10.3.1
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
             * @brief A builder template for constructing a @c DeviceShortcut.
             *
             * To retrieve the builder, call @c DeviceShortcut::create().
             *
             * @since BlackBerry 10.3.1
             */
            class Builder : public TBuilder<Builder, DeviceShortcut>
            {
            public:
                explicit Builder(bb::cascades::DeviceShortcuts::Type type) : TBuilder<Builder, DeviceShortcut>(new DeviceShortcut(type)) {}
            };

            /*!
             * @brief Creates and returns a builder for constructing a @c %DeviceShortcut.
             *
             * @return A builder used for constructing a @c %DeviceShortcut.
             *
             * @since BlackBerry 10.3.1
             */
            static Builder create(bb::cascades::DeviceShortcuts::Type type) {
                return Builder(type);
            }

        private:
            Q_DECLARE_PRIVATE(DeviceShortcut)

            /*! @cond PRIVATE */
            /*!
             * @brief Sets the device shortcut @c type to be used to trigger this shortcut
             *
             * @param type The device shortcut @c type that triggers this shortcut.
             */
            void setType(bb::cascades::DeviceShortcuts::Type type);
            /*! @endcond */

        };
    } // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::DeviceShortcut)

#endif // cascades_deviceshortcut_h
