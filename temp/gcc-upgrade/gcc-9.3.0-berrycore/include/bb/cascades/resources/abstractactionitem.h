/* Copyright (C) 2011 - 2014 BlackBerry Limited. All rights reserved. */

#ifndef cascades_abstractactionitem_h
#define cascades_abstractactionitem_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/AbstractA11yObject>
#include <bb/cascades/core/systemshortcuts.h>

namespace bb {
    namespace cascades {

        class AbstractActionItemPrivate;
        class AbstractShortcut;
        class KeyListener;
        class ColorPaint;

        /*!
         *
         * @brief The base class for all action items.
         *
         * This class serves as a base class to all action item. It allows the user to
         * configure common action attributes such as title, image and accessibility.
         *
         * @see Page, TabbedPane, Tab, Menu, ActionItem
         *
         * @xmlonly
         * <apigrouping group="User interface/Application structure"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT AbstractActionItem : public UIObject
        {
        private:
            Q_OBJECT

           /*!
            * @brief A string that will be displayed with the action.
            *
            * The default value is QString::Null, indicating that no text is set.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(QString title READ title WRITE setTitle
                      RESET resetTitle NOTIFY titleChanged FINAL)

           /*!
            * @brief The image set on the action.
            *
            * The default value is an empty image, indicating no image is set.
            *
            * @xmlonly
            * <qml>
            * <variant type="bb::cascades::Image"/>
            * </qml>
            * @endxmlonly
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(QVariant image READ imageQml WRITE setImageQml
                      RESET resetImage NOTIFY imageChanged FINAL)

           /*!
            * @brief The image set on the action.
            *
            * If no image is set, an invalid QUrl will be returned.
            * When changing the image source the imageSourceChanged() signal will be emitted.
            *
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource
                      RESET resetImageSource NOTIFY imageSourceChanged FINAL)

           /*!
            * @brief Indicates whether the action is enabled.
            *
            * When an action is disabled, it will be dimmed and it will not be possible
            * for the user to press on it and it will not emit the triggered signal.
            *
            * @since BlackBerry 10.0.0
            */
            Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled 
                      RESET resetEnabled NOTIFY enabledChanged FINAL)

           /*!
            * @brief Defines this action's accessibility object.
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
            * @brief Enables or disables all ActionItem's built-in shortcuts.
            *
            * This property is used when all ActionItem's built-in shortcuts should be enabled or disabled.
            * built-in shortcuts are ActionItem's built-in shortcuts like 'backspace' shortcut in @c DeleteActionItem
            *
            * @since BlackBerry 10.2.0
            */
            Q_PROPERTY(bool builtInShortcutsEnabled READ builtInShortcutsEnabled WRITE setBuiltInShortcutsEnabled
                       RESET resetBuiltInShortcutsEnabled NOTIFY builtInShortcutsEnabledChanged REVISION 2 FINAL)

            /*!
             * @brief A background color to display on an action item.
             * Right now it's only a signature action that utilizes it but may well be used by other action items.
             *
             * The default value is the system primary color as a @c QVariant.
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Color"/>
             * <variant type="bb::cascades::ColorPaint"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.3.0
             */
            Q_PROPERTY(QVariant backgroundColor READ backgroundColor WRITE setBackgroundColor RESET resetBackgroundColor NOTIFY backgroundColorChanged REVISION 3 FINAL)

            /*!
             * @brief Specifies if this action item is the default action.
             *
             * The default action will get focus when opening a menu where the action item is presented.
             * Note that the action will not get focus if the menu is already open. Specifying signature
             * action placement for an action will change this property to @c true. If there is more than
             * one default action when opening a menu the menu will give one of these actions focus.
             *
             * @since BlackBerry 10.3.1
             */
            Q_PROPERTY(bool defaultAction READ isDefaultAction WRITE setDefaultAction RESET resetDefaultAction NOTIFY defaultActionChanged REVISION 4 FINAL)

        public:
            virtual ~AbstractActionItem();

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
            * @brief Adds a shortcut to the @c %AbstractActionItem. 
            *
            * @c %AbstractActionItem will always take ownership, as shortcuts should never be shared.
            * If the shortcut already belongs to the @c %AbstractActionItem or the @c shortcut is @c 0, nothing will happen.
            * The order in which shortcuts are added will determine which shortcut will be triggered in case of an overlap.
            *
            * @param shortcut The @c AbstractShortcut to add to the @c %AbstractActionItem.
            *
            * @since BlackBerry 10.1.0
            */
            Q_INVOKABLE void addShortcut(bb::cascades::AbstractShortcut* shortcut);

            /*!
            * @brief Removes a shortcut from the @c %AbstractActionItem.
            *
            * Once the shortcut is removed, the @c %AbstractActionItem no longer references it, but it is still
            * owned by the @c %AbstractActionItem. It is up to the application to either delete the removed
            * shortcut, transfer its ownership (by setting its parent) to another object, or leave
            * it as a child of the @c %AbstractActionItem (in which case it will be deleted with the @c %AbstractActionItem).
            *
            * @param shortcut The @c AbstractShortcut to remove.
            * @return @c true if the shortcut was owned by the @c %AbstractActionItem, @c false otherwise.
            *
            * @since BlackBerry 10.1.0
            */
            Q_INVOKABLE bool removeShortcut(bb::cascades::AbstractShortcut* shortcut);

            /*!
            * @brief Removes all of a AbstractActionItem's shortcuts and frees up their memory.
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
            * Ownership of the shortcut remains with the @c %AbstractActionItem.
            *
            * @param index The index of the shortcut.
            * @return The requested shortcut if the index was valid, @c 0 otherwise.
            *
            * @since BlackBerry 10.1.0
            */
            Q_INVOKABLE bb::cascades::AbstractShortcut* shortcutAt(int index) const;

            /*!
            * @brief Enables all shortcuts attached to the @c %AbstractActionItem.
            *
            * @since BlackBerry 10.1.0
            */
            Q_INVOKABLE void enableAllShortcuts();

            /*!
            * @brief Disables all shortcuts attached to the @c %AbstractActionItem.
            *
            * Shortcuts that are attached afterward will use the default enabled state.
            *
            * @since BlackBerry 10.1.0
            */
            Q_INVOKABLE void disableAllShortcuts();

           /*!
            * @brief Sets the enabled state of all built-in shortcut attached to the @c %AbstractActionItem at a system level.
            *
            * Built-in shortcuts that are attached afterward will use the specified enabled state.
            *
            * @param enabled If @c true all shortcuts are enabled, and if @c false all shortcut are disabled.
            *
            * @since BlackBerry 10.2.0
            */
            Q_REVISION(2)
            Q_SLOT void setBuiltInShortcutsEnabled(bool enabled);

           /*!
            * @brief Returns a builtInShortcutsEnabled property value.
            *
            * @return true if builtInShortcutsEnabled property is set to @c true and @c false otherwise.
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
            Q_INVOKABLE void resetBuiltInShortcutsEnabled();

           /*!
            * @brief Sets the enabled state of the built-in shortcut attached to the @c %AbstractActionItem at a system level
            *
            * Built-in SystemShortcuts that are attached afterward will use the same enabled state.
            *
            * @note Selected built-in shortcut can be enabled or disbaled only if @c AbstractActionItem::builtInShortcutsEnabled
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
            * @brief Sets the title on the action.
            *
            * After the operation is completed, and the title changed,
            * the @c titleChanged() signal is emitted.
            *
            * @param title The title of the action.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setTitle(const QString& title);

           /*!
            * @brief Resets the title on the action to @c QString::Null.
            *
            * After the operation is completed,
            * and the title is changed, the @c titleChanged() signal is emitted.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetTitle();

           /*!
            * @brief Gets the title of the action.
            *
            * @return The title of the action.
            *
            * @since BlackBerry 10.0.0
            */
            const QString title() const;

           /*!
            * @brief Returns the @c #enabled state of the action.
            *
            * @return @c true if the control is enabled, @c false otherwise.
            *
            * @since BlackBerry 10.0.0
            */
            bool isEnabled() const;

           /*!
            * @brief Sets the #enabled state of the action.
            *
            * After the operation is completed and the enabled state is changed,
            * the @c enabledChanged() signal is emitted.
            *
            * @param enabled If @c true the action is enabled and if @c false the action is disabled.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setEnabled(bool enabled);

           /*!
            * @brief Resets the @c #enabled state of the action to @c true.
            *
            * After the operation is completed and the enabled state
            * is changed, the @c enabledChanged() signal is emitted.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetEnabled();

           /*!
            * @brief Returns the image to display on the action item.
            *
            * @return The image for the item or an empty image.
            *
            * @since BlackBerry 10.0.0
            */
            bb::cascades::Image image() const;

           /*!
            * @brief Sets the image to display on the action item.
            *
            * After the operation is completed and the image is changed, the @c imageChanged()
            * signal is emitted.
            *
            * @param image The image to display.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setImage(const bb::cascades::Image& image);

           /*!
            * @brief Resets the image, meaning no image is set for the action.
            *
            * After the operation is completed and the image is changed, the @c imageChanged()
            * signal is emitted.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetImage();

           /*!
            * @brief Returns the image source.
            *
            * @return The source of the displayed image.
            *
            * @since BlackBerry 10.0.0
            */
           QUrl imageSource() const;

           /*!
             * @brief Sets the Image for the action.
             *
             * An invalid @c QUrl indicates no image.
             * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
             *
             * @param source The image URL.
            *
            * @since BlackBerry 10.0.0
             */
           Q_SLOT void setImageSource(const QUrl &source);

           /*!
            * @brief Resets the Image on the action to its default, meaning that no image is set.
            *
            * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
            *
            * @since BlackBerry 10.0.0
            */
           Q_SLOT void resetImageSource();

           /*!
            * @brief Returns the accessibility object.
            *
            * @return The accessibility object.
            *
            * @since BlackBerry 10.2.0
            */
            bb::cascades::AbstractA11yObject *accessibility() const;

            /*!
             * @brief Returns the backgroundColor used on this action item.
             *
             * The returned @c QVariant contain values of type @c Color or @c ColorPaint.
             *
             * Use @c QVariant::canConvert<Type T>() to find the type, and
             * then use @c QVariant::value<Type T>() to get the value.
             *
             * @return The background @c %Color or @c %ColorPaint used on the action item.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            QVariant backgroundColor() const;

            /*!
             * @brief Sets the background color used on this action item.
             *
             * @param backgroundColor The background @c %Color or @c %ColorPaint used on the action item.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void setBackgroundColor(const ColorPaint& backgroundColor);

            /*!
             * @brief Resets the background color for this action item to the system primary color.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void resetBackgroundColor();

            /*!
            * @brief Returns @c true if the action item is the default action.
            *
            * @return @c true if the action item is the default action, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            Q_REVISION(4)
            bool isDefaultAction() const;

           /*!
            * @brief Specifies if this action item is the default action.
            *
            * The default action will get focus when opening a menu where the action item is presented.
            * Note that the action will not get focus if the menu is already open. Specifying signature
            * action placement for an action will change this property to @c true. If there is more than
            * one default action when opening a menu the menu will give one of these actions focus.
            *
            * @param defaultAction If @c true the action item is the default action and if @c false the action item is not the default action.
            *
            * @since BlackBerry 10.3.1
            */
            Q_REVISION(4)
            Q_SLOT void setDefaultAction(bool defaultAction);

           /*!
            * @brief Resets the action item to not being the default action.
            *
            * @since BlackBerry 10.3.1
            */
            Q_REVISION(4)
            Q_SLOT void resetDefaultAction();

        Q_SIGNALS:

           /*!
            * @brief Emitted when the title has changed.
            *
            * @param title The new title.
            *
            * @since BlackBerry 10.0.0
            */
            void titleChanged(const QString& title);

           /*!
            * @brief Emitted when the @c ActionItem is triggered by user.
            *
            * @since BlackBerry 10.0.0
            */
            void triggered();

           /*!
            * @brief Emitted when the @c #enabled property on the action changes.
            *
            * @param enabled If @c true the action is enabled, if @c false the action is disabled.
            *
            * @since BlackBerry 10.0.0
            */
            void enabledChanged(bool enabled);

           /*!
            * @brief Emitted when the image for the action changes.
            *
            * @param image The new image or an empty image if changed to no image.
            *
            * @xmlonly
            * <qml>
            * <param name="image" type="QVariant"/>
            * </qml>
            * @endxmlonly
            *
            * @since BlackBerry 10.0.0
            */
            void imageChanged(const bb::cascades::Image& image);


          /*!
            * @brief Emitted when the image source changes.
            *
            * @param imageSource The new image source or an invalid @c QUrl if no source is set.
           *
           * @since BlackBerry 10.0.0
            */
            void imageSourceChanged(const QUrl& imageSource);

           /*! @cond PRIVATE */
           /*!
            * @brief Emitted when the image for the action changes. This is used for QML.
            */
            void imageChanged(const QVariant& image);

            /*! @endcond */

            /*!
             * @brief Emitted when the background color for this action changes.
             *
             * @param backgroundColor The new background color for this action
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            void backgroundColorChanged(const ColorPaint& backgroundColor);

            /*! @cond PRIVATE */
            /*!
             * @brief Emitted when the background color changes.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            void backgroundColorChanged(const QVariant& backgroundColor);
            /*! \endcond */

           /*!
            * @brief Emitted when the @c #builtInShortcutsEnabled property changes.
            *
            * @param builtInShortcutsEnabled The new value.
            *
            * @since BlackBerry 10.2.0
            */
            Q_REVISION(2)
            void builtInShortcutsEnabledChanged(bool builtInShortcutsEnabled);

           /*!
            * @brief Emitted when the @c #defaultAction property on the action item changes.
            *
            * @param defaultAction If @c true the action item is the default action, if @c false the action item is not the default action.
            *
            * @since BlackBerry 10.3.1
            */
            Q_REVISION(4)
            void defaultActionChanged(bool defaultAction);

        /*! @cond PRIVATE */
        protected:
            AbstractActionItem(AbstractActionItemPrivate &_d_ptr, UIObject *parent = 0);
        /*! @endcond */

        private:
            Q_DECLARE_PRIVATE(AbstractActionItem)
            Q_DISABLE_COPY(AbstractActionItem)

            /*! @cond PRIVATE */
            QDeclarativeListProperty<bb::cascades::AbstractShortcut> shortcuts();
            const QVariant imageQml() const;
            Q_SLOT void setImageQml(const QVariant & image);
            /*! @endcond */

            /*! @cond PRIVATE */
            /*!
             * @brief Sets the background color used by this action item.
             *
             * @param backgroundColor The background color to display on this action item.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void setBackgroundColor(const QVariant& backgroundColor);
            /*! @endcond */

        public:
            /*! @cond PRIVATE */
            typedef AbstractActionItem ThisClass;
            typedef UIObject BaseClass;
            /*!
             * Workaround for the Qt bug that prevents our enums from being
             * function arguments in QML.
             */
            Q_INVOKABLE void setBuiltInShortcutEnabled(int type, bool enabled);
            /*! @endcond */

            /*!
             * @brief A builder template for constructing an AbstractActionItem.
             *
             * @since BlackBerry 10.0.0
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
                * @brief Sets the title.
                *
                * Using this convenience function in the builder pattern is the equivalent of the
                * following:
                * @code
                * myAction->setTitle("a title");
                * @endcode
                *
                * @param title The title to set on the Action.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& title(const QString & title)
                {
                    this->instance().setTitle(title);
                    return this->builder();
                }

               /*!
                * @brief Sets the enabled property.
                *
                * Using this convenience function in the builder pattern is the equivalent of the
                * following:
                * @code
                * myAction->setEnabled(false);
                * @endcode
                *
                * @param enabled If the action should be enabled or not.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& enabled(bool enabled)
                {
                    this->instance().setEnabled(enabled);
                    return this->builder();
                }

               /*!
                * @brief Sets the image.
                *
                * Using this convenience function in the builder pattern is the equivalent of the
                * following:
                * @code
                * myAction->setImage(image);
                * @endcode
                *
                * @param image The image to set on the action.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& image(const bb::cascades::Image& image)
                {
                    this->instance().setImage(image);
                    return this->builder();
                }

               /*!
                * @brief Convenience function for setting the image by image source.
                *
                * This is equivalent to calling:
                * @code
                * image(Image("images/myImage.png"));
                * @endcode
                *
                * @param imageSource The image source of the image to load.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& imageSource(const QUrl &imageSource) {
                  return image(Image(imageSource));
                }

                /*!
                 * A convenience method for connecting passed receiver's slot to
                 * the triggered() signal with the default connection type
                 * Qt::AutoConnection.
                 *
                 * Example:
                 * @code
                 * ActionItem *action = ActionItem::create()
                 *     .title("Action!")
                 *     .onTriggered(this, SLOT(onTriggeredHandler()));
                 * @endcode
                 *
                 * @param receiver a non-@c null receiver object
                 * @param method a non-null name of the slot in the receiver object to connect to
                 *
                 * @see BaseObject::TBuilder::connect()
                 *
                 * @since BlackBerry 10.0.0
                 */
                BuilderType& onTriggered(const QObject* receiver, const char *method) {
                    this->connect(SIGNAL(triggered()), receiver, method);
                    return this->builder();
                }

                /*!
                 * @brief Adds a shortcut to the @c %AbstractActionItem.
                 *
                 * @c %AbstractActionItem will always take ownership as shortcuts should never be shared.
                 * If the shortcut already belongs to the @c %AbstractActionItem or the @c shortcut is @c 0, nothing will happen.
                 * The order in which shortcuts are added will determine which shortcut will be triggered in case of an overlap.
                 *
                 *
                 * @param shortcut The @c AbstractShortcut to add to the @c %AbstractActionItem.
                 *
                 * @since BlackBerry 10.1.0
                 */
                BuilderType& addShortcut(AbstractShortcut* shortcut) {
                    this->instance().addShortcut(shortcut);
                    return this->builder();
                }

                /*!
                 * @brief Sets the background color used by this action item.
                 *
                 * @param backgroundColor The value of the background color to set for this action item.
                 *
                 * @since BlackBerry 10.3.0
                 */
                BuilderType& backgroundColor(const bb::cascades::ColorPaint &backgroundColor) {
                  this->instance().setBackgroundColor(backgroundColor);
                  return this->builder();
                }

                /*!
                 * @brief Sets the accessibility name property of the @c %AbstractActionItem.
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
                 * @brief Sets the accessibility description property of the @c %AbstractActionItem.
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
                 * @param labelledBy The object to add as an accessibility label for the @c AbstractActionItem.
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
                 * Using this convenience function in the builder pattern is the equivalent of the
                 * following:
                 * @code
                 * myAction->setBuiltInShortcutsEnabled(false);
                 * @endcode
                 *
                 * @param enabled If the action's built-in shortcuts should be enabled or not.
                 *
                 * @since BlackBerry 10.2.0
                 */
                BuilderType& builtInShortcutsEnabled(bool enabled)
                {
                    this->instance().setBuiltInShortcutsEnabled(enabled);
                    return this->builder();
                }

               /*!
                * @brief Sets the defaultAction property.
                *
                * Using this convenience function in the builder pattern is the equivalent of the
                * following:
                * @code
                * myAction->setDefaultAction(false);
                * @endcode
                *
                * @param defaultAction If the action should be default or not.
                *
                * @since BlackBerry 10.3.1
                */
                BuilderType& defaultAction(bool defaultAction)
                {
                    this->instance().setDefaultAction(defaultAction);
                    return this->builder();
                }
            };
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::AbstractActionItem)


#endif	// cascades_abstractactionitem_h


