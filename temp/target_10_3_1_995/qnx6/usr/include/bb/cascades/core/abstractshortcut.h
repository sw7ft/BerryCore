/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_abstractshortcut_h
#define cascades_abstractshortcut_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/shortcuttriggermode.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {
        
        class AbstractShortcutPrivate;

         /*!
         * @brief The base class for all shortcut subclasses.
         *
         * All subclasses can be added to a @c AbstractPane, @c Control, and @c AbstractActionItem
         *
         * @xmlonly
         *     <apigrouping group="User interface/Application structure"/>
         * @endxmlonly
          *
          * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT AbstractShortcut : public UIObject {
            Q_OBJECT

            /*!
             * @brief Describes whether the current shortcut is enabled or disabled.
             *
             * By default a shortcut is enabled.
             *
             * @since BlackBerry 10.1.0
             */
            
            Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled RESET resetEnabled NOTIFY enabledChanged FINAL)

          /*!
           * @brief Describes the user input which should trigger the shortcut.
           *
           * The default value is @c bb::cascades::ShortcutTriggerMode::Default, letting the system
           * decide the appropriate trigger mode. Set this property if you need to guarantee that
           * the shortcut is triggered by a specific user input. Otherwise, for the best user experience
           * it is recommended to always use the default value. Also, you should not assume anything
           * about the default mode, as it may vary depending on the device or other factors.
           *
           * @since BlackBerry 10.3.0
           */

          Q_PROPERTY(bb::cascades::ShortcutTriggerMode::Type triggerMode
                     READ triggerMode
                     WRITE setTriggerMode
                     RESET resetTriggerMode
                     NOTIFY triggerModeChanged
                     REVISION 3
                     FINAL)
        public:
            virtual ~AbstractShortcut();
                      
            /*!
             * @brief Sets the @c enabled state of the shortcut.
             *
             * After the operation is completed and the @c enabled state is changed,
             * the @c enabledChanged() signal is emitted.
             *
             * @param enabled If @c true the shortcut is enabled, and if @c false the shortcut is disabled.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void setEnabled(bool enabled);
            
            /*!
             * @brief Resets the @c #enabled state of the shortcut to @c true.
             *
             * After the operation is completed and the @c enabled state
             * is changed, the @c enabledChanged() signal is emitted.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void resetEnabled();                      
            
            /*!
             * @brief Gets the @c #enabled state of the shortcut.
             *
             * @return @c true if this shortcut is enabled and @c false otherwise.
             *
             * @since BlackBerry 10.1.0
             */
            bool isEnabled() const;

            /*!
             * @brief Sets which user input should trigger the shortcut.
             *
             * Set this property if you need to guarantee that the shortcut is triggered by a specific
             * user input. Otherwise, for the best user experience it is recommended to always use the
             * default value. Also, you should not assume anything about the default mode, as it may vary
             * depending on the device or other factors.
             *
             * After the operation is completed and the @c triggerMode is changed,
             * the @c triggerModeChanged() signal is emitted.
             *
             * @param triggerMode The new trigger mode to set.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void setTriggerMode(bb::cascades::ShortcutTriggerMode::Type triggerMode);

            /*!
             * @brief Resets the trigger mode to its default value.
             *
             * The default value is @c bb::cascades::ShortcutTriggerMode::Default, letting the system
             * decide the appropriate trigger mode.
             *
             * After the operation is completed and the @c triggerMode is changed,
             * the @c triggerModeChanged() signal is emitted.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void resetTriggerMode();

            /*!
             * @brief Gets the current trigger mode of the shortcut.
             *
             * @return @c The current trigger mode.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            bb::cascades::ShortcutTriggerMode::Type triggerMode() const;
            
        Q_SIGNALS:                      
            
            /*!
             * @brief Emitted when the @c #enabled property on the shortcut changes.
             *
             * @param enabled If @c true the shortcut is enabled, if @c false the shortcut is disabled.
             *
             * @since BlackBerry 10.1.0
             */
            void enabledChanged(bool enabled);

            /*!
             * @brief Emitted when the @c #triggerMode property on the shortcut changes.
             *
             * @param newTriggerMode The new trigger mode.
             *
             * @note Due to a work around for a Qt Core issue with accessing enums from QML
             * the argument of this signal doesn't follow naming convention for signals in
             * which the signal arguments are typically named to match the associated property's name.
             * Use the object's property to access current property value instead of the signal argument
             * to avoid runtime errors (i.e. use @c triggerMode instead of @c newTriggerMode).
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            void triggerModeChanged(bb::cascades::ShortcutTriggerMode::Type newTriggerMode);

            /*!
             * @brief Emitted when the @c %AbstractShortcut is triggered by the user.
             *
             * @since BlackBerry 10.1.0
             */
            void triggered();

        /*! @cond PRIVATE */
        protected:          
            AbstractShortcut(AbstractShortcutPrivate &_d_ptr, UIObject *parent = 0);
        /*! @endcond */

        private:            
            Q_DECLARE_PRIVATE(AbstractShortcut)       
            Q_DISABLE_COPY(AbstractShortcut)

        public:
            /*! @cond PRIVATE */
            typedef AbstractShortcut ThisClass;
            typedef BaseObject BaseClass;
            /*! @endcond */
            
            /*!
             * @brief A builder template for constructing an @c %AbstractShortcut. To retrieve the builder, call
             * @c Shortcut::create().
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
                 * @brief Enable or disable @c %AbstractShortcut.
                 *
                 * Using this convenience function in the builder pattern is the equivalent of the
                 * following:
                 * @code
                 * myShortcut->setEnabled(false);
                 * @endcode
                 *
                 * @param enabled Describes whether this @c %AbstractShortcut should be activated when
                 *                 a corresponding shortcut event is available for handling.
                 *
                 * @since BlackBerry 10.1.0
                 */
                BuilderType& enable(bool enabled)
                {
                    this->instance().setEnabled(enabled);
                    return this->builder();
                }
                
                /*!
                 * @brief Sets which user input should trigger the shortcut.
                 *
                 * Set this property if you need to guarantee that the shortcut is triggered by a specific
                 * user input. Otherwise, for the best user experience it is recommended to always use the
                 * default value. Also, you should not assume anything about the default mode, as it may vary
                 * depending on the device or other factors.
                 *
                 * Using this convenience function in the builder pattern is the equivalent of the
                 * following:
                 * @code
                 * myShortcut->setTriggerMode(triggerMode);
                 * @endcode
                 *
                 * @param triggerMode The new triggerMode to set.
                 *
                 * @since BlackBerry 10.3.0
                 */
                BuilderType& triggerMode(bb::cascades::ShortcutTriggerMode::Type triggerMode)
                {
                    this->instance().setTriggerMode(triggerMode);
                    return this->builder();
                }

                /*!
                 * @brief A convenience method for connecting passed receiver's slot to
                 * the @c triggered() signal with the default connection type
                 * @c Qt::AutoConnection.
                 *
                 * Example:
                 * @code
                 * Shortcut *shortcut = Shortcut::create()
                 *     .key("a")
                 *     .onTriggered(this, SLOT(onShortcutTriggeredHandler()));
                 * @endcode
                 *
                 * @param receiver A receiver object that is not @c null.
                 * @param method A name for the slot that can be connected in the receiver object.
                 *                 This parameter cannot be @c null.
                 *
                 * @see BaseObject::TBuilder::connect()
                 *
                 * @since BlackBerry 10.1.0
                 */
                BuilderType& onTriggered(const QObject* receiver, const char *method) {
                    this->connect(SIGNAL(triggered()), receiver, method);
                    return this->builder();
                }
            };                
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::AbstractShortcut)


#endif // cascades_abstractshortcut_h
