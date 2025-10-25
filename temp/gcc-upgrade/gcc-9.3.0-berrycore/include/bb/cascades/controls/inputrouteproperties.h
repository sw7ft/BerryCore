/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef bb_cascades_inputrouteproperties_h
#define bb_cascades_inputrouteproperties_h

#include <bb/cascades/UIObject>

namespace bb {
    namespace cascades {
        class InputRoutePropertiesPrivate;

        /*!
         * @brief Optional group of properties that can be set on controls to define their role in the propagation of input events
         * and influence the default routing logic.
         *
         * This is typically used to indicate that the control is the default target of some type of input event when
         * a target cannot be determined by the another propagation mechanism.
         * E.g. if there is no focused control, setting @c inputRoute.primaryKeyTarget to @c true on a control will make it the target
         * of key events.
         *
         * @xmlonly
         * <apigrouping group="User interface/Core controls"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT InputRouteProperties : public UIObject {
            Q_OBJECT

            /*!
             * @brief Indicates that the owner of these properties should be treated as primary key target.
             *
             * This property is read by the event system when a key event is about to be propagated and
             * there is no focused control. The event system scans the content of the current page, and
             * when a page or control with this property set to true is found, it will be used as the
             * target for the key event. The event then bubbles up to the root according to standard
             * key event propagation rules.
             *
             * The intent is to enable the developer to set a primary key target per page. If the primary
             * key target needs to change for some reason, it is up to the developer to reset and set this
             * property where needed. The scan will always pick the first occuring primary key target, in
             * a pre-order depth first search from the page (meaning parents have precedence over children).
             *
             * @note Focus set explicitly with @c Control::requestFocus() overrides the effect of this property. 
             * I.e. once focus has been set on a control, this property has no effect.
             *
             * @note There is no visual hint to indicate which control or page is the effective main key
             * target. It can be confusing for a user if it changes within the same screen.
             *
             * The default value for this property is @c false.
             *
             * QML usage:
             * @snippet tad/examples/controls/control/assets/main.qml control_qml2
             *
             * C++ usage:
             * @snippet tad/examples/controls/control/src/ControlExamples.cpp control2
             *
             * C++ usage (with builder):
             * @snippet tad/examples/controls/control/src/ControlExamples.cpp control1
             *
             * @see Page::inputRoute, Control::inputRoute
             *
             * @since BlackBerry 10.1.0
             */
            Q_PROPERTY(bool primaryKeyTarget READ isPrimaryKeyTarget WRITE setPrimaryKeyTarget RESET resetPrimaryKeyTarget NOTIFY primaryKeyTargetChanged FINAL)

            /*!
             * @brief If the focused control is this or a control somewhere in this subtree, deliever events as if nothing had focus.
             *
             * Whenever a control is focused, key events will be delivered to that control and never to the primary 
             * key target or the fallback route. Sometimes it is desirable to prevent this behavior for certain 
             * controls. (eg a button getting focus when navigated to)
             *
             * Setting this property on a control will make the event propagation treat any focused control in the node tree rooted at
             * this control to be treated as if nothing had focus.
             *
             * @note setting this property will not block key events from being delivered to a primary key target in subtree.
             *
             * The default value for this property is @c false.
             *
             * @see Page::inputRoute, Control::inputRoute
             *
             * @since BlackBerry 10.3.1
             */
            Q_PROPERTY(bool keysIgnoreFocusInSubtree READ keysIgnoreFocusInSubtree WRITE setKeysIgnoreFocusInSubtree RESET resetKeysIgnoreFocusInSubtree NOTIFY keysIgnoreFocusInSubtreeChanged REVISION 4 FINAL);

        public:
            /*!
             * @brief Constructs an @c InputRouteProperties object with a parent @c UIObject.
             *
             * The ownership of the @c InputRouteProperties object is transferred to the parent,
             * if a parent is specified.
             *
             * @param parent The parent UIObject, or @c 0. This parameter is optional.
             * The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.1.0
             */
            explicit InputRouteProperties(UIObject *parent = 0);
            virtual ~InputRouteProperties();

            /*!
             * @brief Returns the @c #primaryKeyTarget state of the control.
             *
             * @return @c true if the control is set to be primary key target, @c false otherwise.
             *
             * @since BlackBerry 10.1.0
             */
            bool isPrimaryKeyTarget() const;

            /*!
             * @brief Sets the @c #primaryKeyTarget state of the control.
             *
             * @param primaryKeyTarget If @c true the control is a primary key target and if @c false
             * the control is not a primary key target.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void setPrimaryKeyTarget(bool primaryKeyTarget);

            /*!
             * @brief Resets the @c #primaryKeyTarget state of the control to @c false.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void resetPrimaryKeyTarget();

            /*!
             * @brief Returns the @c #keysIgnoreFocusInSubtree state of the control.
             *
             * @return @c true if the control is set to be key blocker, @c false otherwise.
             *
             * @since BlackBerry 10.3.1
             */
			Q_REVISION(4)
            bool keysIgnoreFocusInSubtree() const;

            /*!
             * @brief Sets the @c #keysIgnoreFocusInSubtree state of the control.
             *
             * @param keysIgnoreFocusInSubtree If @c true the control is a key blocker and if @c false
             * the control is not a key blocker.
             *
             * @since BlackBerry 10.3.1
             */
			Q_REVISION(4)
            Q_SLOT void setKeysIgnoreFocusInSubtree(bool keysIgnoreFocusInSubtree);

            /*!
             * @brief Resets the @c #keysIgnoreFocusInSubtree state of the control to @c false.
             *
             * @since BlackBerry 10.3.1
             */
			Q_REVISION(4)
            Q_SLOT void resetKeysIgnoreFocusInSubtree();

Q_SIGNALS:
            /*!
             * @brief Emitted when the @c #primaryKeyTarget property changes.
             *
             * @param primaryKeyTarget The new value of @c #primaryKeyTarget.
             *
             * @since BlackBerry 10.1.0
             */
            void primaryKeyTargetChanged(bool primaryKeyTarget);

            /*!
             * @brief Emitted when the @c #keysIgnoreFocusInSubtree property changes.
             *
             * @param keysIgnoreFocusInSubtree The new value of @c #keysIgnoreFocusInSubtree.
             *
             * @since BlackBerry 10.3.1
             */
			Q_REVISION(4)
            void keysIgnoreFocusInSubtreeChanged(bool keysIgnoreFocusInSubtree);

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(InputRouteProperties)
            Q_DISABLE_COPY(InputRouteProperties)
            /*! @endcond */


        };
    }
}

QML_DECLARE_TYPE(bb::cascades::InputRouteProperties)

#endif    // bb_cascades_inputrouteproperties_h
