/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_abstracta11yobject_h
#define bb_cascades_abstracta11yobject_h

#include <bb/cascades/UIObject>
#include <bb/cascades/A11yRole>

namespace bb {
    namespace cascades {
        class AbstractA11yObjectPrivate;

        /*!
         * @brief Defines a control's accessibility properties.
         *
         * A control's accessibility properties can be used by assistive technologies for
         * users with special needs.
         *
         * @xmlonly
         * <apigrouping group="User interface/Accessibility"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        class BBCASCADES_EXPORT AbstractA11yObject : public UIObject {
            Q_OBJECT

            /*!
             * @brief The human-readable name for an accessible control.
             *
             * Every accessible control should have human-readable text associated with
             * it. In most cases, this can be inferred by the text being displayed
             * on the object or the text of a label that is labeling the
             * object. In some cases, such as with icon-only push buttons, the
             * name cannot be inferred and must be supplied by the application
             * developer. This property represents that string.
             *
             * @note Setting this property will override the default name inference of the control.
             *
             * The default value for this property is @c QString::Null, indicating that no name is set.
             *
             * @see bb::cascades::Control::accessibility
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(QString name READ name WRITE setName RESET resetName NOTIFY nameChanged FINAL)

            /*!
             * @brief The role of an accessible control.
             *
             * Describes the role of an accessible control, e.g. "button", "checkbox", "text" etc.
             *
             * The default value for this property is @c bb::cascades::A11yRole::Undefined.
             *
             * @see bb::cascades::Control::accessibility
             * @see bb::cascades::A11yRole
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(bb::cascades::A11yRole::Type role READ role)

            /*!
             * @brief The human-readable description for an accessible control.
             *
             * An accessible description is typically a short phrase or sentence
             * that briefly describes the purpose of the object. This is not a
             * required attribute of the object.
             *
             * The default value for this property is @c QString::Null, indicating that no description is set.
             *
             * @see bb::cascades::Control::accessibility
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(QString description READ description WRITE setDescription RESET resetDescription NOTIFY descriptionChanged FINAL)

            /*!
             * @brief A QDeclarativeListProperty that contains all objects that act as labels for the accessible control.
             *
             * An accessible control can use other objects as "labels" for description,
             * in addition to the name and description properties. An example of usage could be
             * a text field that is described by a label. Multiple labels can be assigned, if
             * multiple objects provide information of different levels of detail.
             *
             * If a label is added, the name and description from the label object's
             * accessibility object, or built in defaults, is used. A Label control
             * rarely needs a name set in order to act as label for another control, since
             * by default the text on the label is used as name.
             *
             * @note The objects acting as labels must be of type @c Control, @c AbstractPane
             * or @c AbstractDialog, otherwise the label object will be disregarded.
             *
             * @xmlonly
             * <qml>
             * <property name="labelledBy" listType="bb::cascades::UIObject" />
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(QDeclarativeListProperty<bb::cascades::UIObject> labelledBy READ labelledBy FINAL)

        public:
            /*!
             * @brief Destructs this accessibility object.
             */
            virtual ~AbstractA11yObject();

            /*!
             * @brief Returns the accessibility @c #name of the control.
             *
             * @return The accessibility name of the control.
             *
             * @since BlackBerry 10.2.0
             */
            QString name() const;

            /*!
             * @brief Sets the accessibility @c #name of the control.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void setName(const QString & name);

            /*!
             * @brief Resets the accessibility @c #name of the control to @c QString::Null.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void resetName();

            /*!
             * @brief Returns the accessibility @c #role of the control.
             *
             * @return The accessibility role of the control.
             *
             * @since BlackBerry 10.2.0
             */
            bb::cascades::A11yRole::Type role() const;

            /*!
             * @brief Returns the accessibility @c #description of the control.
             *
             * @return The accessibility description of the control.
             *
             * @since BlackBerry 10.2.0
             */
            QString description() const;

            /*!
             * @brief Sets the accessibility @c #description of the control.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void setDescription(const QString & description);

            /*!
             * @brief Resets the accessibility @c #description of the control to @c QString::Null.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void resetDescription();

            /*!
             * @brief Adds a label to the @c #labelledBy property of the accessible control.
             *
             * New labels are added as the last item in the list.
             * The object that is passed must not be @c 0 or it will be ignored.
             *
             * Ownership of the label object does not change. Since the object used
             * as label is typically part of the UI tree, it retains its parent. The
             * AbstractA11yObject will only become parent if explicitly set.
             *
             * @param label The object to be added as label; must be a @c Control and not @c 0.
             *
             * @since BlackBerry 10.2.0
             */
            Q_INVOKABLE void addLabel(bb::cascades::UIObject *label);

            /*!
             * @brief Removes a label from the @c #labelledBy property of the accessible control.
             *
             * If the label is found, @c #labelRemoved will be emitted.
             * If the removed label object has the AbstractA11yObject as parent, it will
             * be destroyed after the signal has been emitted.
             *
             * @param label The object to be removed; must not be @c 0.
             *
             * @since BlackBerry 10.2.0
             */
            Q_INVOKABLE void removeLabel(bb::cascades::UIObject *label);

            /*!
             * @brief Removes all labels from the @c #labelledBy property of the accessible control.
             *
             * Emits @c #labelRemoved with @c 0 as argument.
             * Removed label objects that have the AbstractA11yObject as parent will be
             * destroyed, before the signal is emitted.
             *
             * @since BlackBerry 10.2.0
             */
            Q_INVOKABLE void removeAllLabels();

            /*!
             * @brief Returns the label object at the specified index in the @c #labelledBy property.
             *
             * @param index The index of the object.
             *
             * @return The requested object if the index was valid, @c 0 otherwise.
             *
             * @since BlackBerry 10.2.0
             */
            Q_INVOKABLE bb::cascades::UIObject* labelAt(int index) const;

            /*!
             * @brief Returns the index of a label object in the @c #labelledBy property.
             *
             * If the object isn't among the labels
             * or if the object is @c 0, @c -1 is returned.
             *
             * @param label The label object to get the index from.
             *
             * @return The index of the specified label object if the object is valid, @c -1 otherwise.
             *
             * @since BlackBerry 10.2.0
             */
            Q_INVOKABLE int indexOfLabel(bb::cascades::UIObject *label) const;

            /*!
             * @brief Returns the number of labels in the @c #labelledBy property of the accessible control.
             *
             * @return The number of labels.
             *
             * @since BlackBerry 10.2.0
             */
            Q_INVOKABLE int labelCount() const;

Q_SIGNALS:
            /*!
             * @brief Emitted when the @c #name property changes.
             *
             * @param name The new value of @c #name.
             *
             * @since BlackBerry 10.2.0
             */
            void nameChanged(const QString & name);

            /*!
             * @brief Emitted when the @c #description property changes.
             *
             * @param description The new value of @c #description.
             *
             * @since BlackBerry 10.2.0
             */
            void descriptionChanged(const QString & description);

            /*!
             * @brief Emitted when a label object has been added to the @c #labelledBy property of the accessible control.
             *
             * @param label The label object that has been added.
             *
             * @since BlackBerry 10.2.0
             */
            void labelAdded(bb::cascades::UIObject *label);

            /*!
             * @brief Emitted when a label object has been removed from the @c #labelledBy property of the accessible control.
             *
             * @param label The label object that has been removed. @c 0 if emitted by removeAllLabels().
             *
             * @since BlackBerry 10.2.0
             */
            void labelRemoved(bb::cascades::UIObject *label);

        protected:
            /*! @cond PRIVATE */
            /*!
             * @brief Constructs an AbstractA11yObject object with a parent UIObject.
             *
             * The ownership of the AbstractA11yObject object is transferred to the parent if a parent is specified.
             *
             * @param _d_ptr The private representation of the object.
             * @param parent The parent UIObject, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.2.0
             */
            explicit AbstractA11yObject(AbstractA11yObjectPrivate &_d_ptr, UIObject *parent = 0);
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            QDeclarativeListProperty<bb::cascades::UIObject> labelledBy();
            Q_DECLARE_PRIVATE(AbstractA11yObject)
            Q_DISABLE_COPY(AbstractA11yObject)
            /*! @endcond */
        };
    }
}

QML_DECLARE_TYPE(bb::cascades::AbstractA11yObject)

#endif    // bb_cascades_abstracta11yobject_h
