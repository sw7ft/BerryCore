/* Copyright (C) 2014 Research In Motion Limited.  */

#ifndef cascades_navigation_h
#define cascades_navigation_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/UIObject>
#include <bb/cascades/NavigationFocusPolicy>

namespace bb {
    namespace cascades {

        class NavigationPrivate;
        class Control;

    /*!
     * @brief Specifies trackpad navigation properties for a control, such as whether a control can
     * get focus, and what the next controls in the navigation path are.
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     *
     * @since BlackBerry 10.3.1
     */
        class BBCASCADES_EXPORT Navigation : public UIObject {
            Q_OBJECT

            /*!
            * @brief Property for specifying which control should get focus when navigating left.
            *
            * If the value is @c 0 the default navigation algorithm will be used.
            *
            * The default value is @c 0.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bb::cascades::Control* left READ left WRITE setLeft RESET resetLeft NOTIFY leftChanged FINAL)

            /*!
            * @brief Property for specifying whether it should be possible to navigate left.
            *
            * The default value is @c true.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bool leftAllowed READ isLeftAllowed WRITE setLeftAllowed RESET resetLeftAllowed NOTIFY leftAllowedChanged FINAL)

            /*!
            * @brief Property for specifying which control should get focus when navigating right.
            *
            * If the value is @c 0 the default navigation algorithm will be used.
            *
            * The default value is @c 0.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bb::cascades::Control* right READ right WRITE setRight RESET resetRight NOTIFY rightChanged FINAL)

            /*!
            * @brief Property for specifying whether it should be possible to navigate right.
            *
            * The default value is @c true.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bool rightAllowed READ isRightAllowed WRITE setRightAllowed RESET resetRightAllowed NOTIFY rightAllowedChanged FINAL)

            /*!
            * @brief Property for specifying which control should get focus when navigating up.
            *
            * If the value is @c 0 the default navigation algorithm will be used.
            *
            * The default value is @c 0.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bb::cascades::Control* up READ up WRITE setUp RESET resetUp NOTIFY upChanged FINAL)

            /*!
            * @brief Property for specifying whether it should be possible to navigate up.
            *
            * The default value is @c true.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bool upAllowed READ isUpAllowed WRITE setUpAllowed RESET resetUpAllowed NOTIFY upAllowedChanged FINAL)

            /*!
            * @brief Property for specifying which control should get focus when navigating down.
            *
            * If the value is @c 0 the default navigation algorithm will be used.
            *
            * The default value is @c 0.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bb::cascades::Control* down READ down WRITE setDown RESET resetDown NOTIFY downChanged FINAL)

            /*!
            * @brief Property for specifying whether it should be possible to navigate down.
            *
            * The default value is @c true.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bool downAllowed READ isDownAllowed WRITE setDownAllowed RESET resetDownAllowed NOTIFY downAllowedChanged FINAL)

            /*!
            * @brief Specifies whether this control can get focus by navigating with the trackpad.
            *
            * The default @c FocusPolicy value is @c Default. A disabled @c %Control cannot have focus.
            * 
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bb::cascades::NavigationFocusPolicy::Type focusPolicy READ focusPolicy WRITE setFocusPolicy RESET resetFocusPolicy NOTIFY focusPolicyChanged FINAL)

            /*!
            * @brief Specifies whether the control should show the default highlight when the control wants a navigation highlight.
            *
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bool defaultHighlightEnabled READ isDefaultHighlightEnabled WRITE setDefaultHighlightEnabled RESET resetDefaultHighlightEnabled NOTIFY defaultHighlightEnabledChanged FINAL)

            /*!
            * @brief Read only property indicating whether the control wants a navigation highlight.
            *
            * If defaultHighlightEnabled is @c true a default highlight will be shown when wantsHighlight is @c true.
            *
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bool wantsHighlight READ wantsHighlight NOTIFY wantsHighlightChanged FINAL)

        public:
            virtual ~Navigation();

            /*!
            * @brief Gets the target of a left navigation from the control.
            *
            * Ownership will not be transferred.
            *
            * @return The target of a left navigation or @c 0 if the default navigation algorithm is used.
            *
            * @since BlackBerry 10.3.1
            */
            bb::cascades::Control* left() const;

            /*!
            * @brief Sets the target of a left navigation from the control.
            *
            * Ownership will not be transferred.
            * If operation was successful, the @c leftChanged() signal will be emitted.
            *
            * @param target The target of a left navigation. If target is @c 0 the default navigation algorithm
            * will be used.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setLeft(bb::cascades::Control* target);

            /*!
            * @brief Resets the target of a left navigation from the control to use the default navigation algorithm.
            *
            * Ownership will not be transferred.
            * If operation was successful, the @c leftChanged() signal will be emitted.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetLeft();

            /*!
            * @brief Indicates whether left navigation is allowed from the control.
            *
            * @return @c true if left navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            bool isLeftAllowed() const;

            /*!
            * @brief Sets whether left navigation should be allowed from the control.
            *
            * @param allowed @c true if left navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setLeftAllowed(bool allowed);

            /*!
            * @brief Resets the @c leftAllowed property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetLeftAllowed();

            /*!
            * @brief Gets the target of a right navigation from the control.
            *
            * Ownership will not be transferred.
            *
            * @return The target of a right navigation or @c 0 if the default navigation algorithm is used.
            *
            * @since BlackBerry 10.3.1
            */
            bb::cascades::Control* right() const;

            /*!
            * @brief Sets the target of a right navigation from the control.
            *
            * Ownership will not be transferred.
            * If the operation is successful, the @c rightChanged() signal will be emitted.
            *
            * @param target The target of a right navigation. If target is @c 0 the default navigation algorithm
            * will be used.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setRight(bb::cascades::Control* target);

            /*!
            * @brief Resets the target of a right navigation from the control to use the default navigation algorithm.
            *
            * Ownership will not be transferred.
            * If the operation is successful, the @c rightChanged() signal will be emitted.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetRight();

            /*!
            * @brief Indicates whether right navigation is allowed from the control.
            *
            * @return @c true if right navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            bool isRightAllowed() const;

            /*!
            * @brief Controls whether right navigation should be allowed from the control.
            *
            * @param allowed @c true if right navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setRightAllowed(bool allowed);

            /*!
            * @brief Resets the @c rightAllowed property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetRightAllowed();

            /*!
            * @brief Gets the target of an up navigation from the control.
            *
            * Ownership will not be transferred.
            *
            * @return The target of a up navigation or @c 0 if the default navigation algorithm is used.
            *
            * @since BlackBerry 10.3.1
            */
            bb::cascades::Control* up() const;

            /*!
            * @brief Sets the target of a up navigation from the control.
            *
            * Ownership will not be transferred.
            * If operation was successful, the @c upChanged() signal will be emitted.
            *
            * @param target The target of a up navigation. If target is @c 0 the default navigation algorithm
            * will be used.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setUp(bb::cascades::Control* target);

            /*!
            * @brief Resets the target of a up navigation from the control to use the default navigation algorithm.
            *
            * Ownership will not be transferred.
            * If operation was successful, the @c upChanged() signal will be emitted.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetUp();

            /*!
            * @brief Indicates whether up navigation is allowed from the control.
            *
            * @return @c true if up navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            bool isUpAllowed() const;

            /*!
            * @brief Controls whether up navigation should be allowed from the control.
            *
            * @param allowed @c true if up navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setUpAllowed(bool allowed);

            /*!
            * @brief Resets the @c upAllowed property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetUpAllowed();

            /*!
            * @brief Gets the target of a down navigation from the control.
            *
            * Ownership will not be transferred.
            *
            * @return The target of a down navigation or @c 0 if the default navigation algorithm is used.
            *
            * @since BlackBerry 10.3.1
            */
            bb::cascades::Control* down() const;

            /*!
            * @brief Sets the target of a down navigation from the control.
            *
            * Ownership will not be transferred.
            * If operation was successful, the @c downChanged() signal will be emitted.
            *
            * @param target The target of a down navigation. If target is @c 0 the default navigation algorithm
            * will be used.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setDown(bb::cascades::Control* target);

            /*!
            * @brief Resets the target of a down navigation from the control to use the default navigation algorithm.
            *
            * Ownership will not be transferred.
            * If operation was successful, the @c downChanged() signal will be emitted.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetDown();

            /*!
            * @brief Indicates whether down navigation is allowed from the control.
            *
            * @return @c true if down navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            bool isDownAllowed() const;

            /*!
            * @brief Sets whether down navigation should be allowed from the control.
            *
            * @param allowed @c true if down navigation is allowed, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setDownAllowed(bool allowed);

            /*!
            * @brief Resets the downAllowed property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetDownAllowed();

            /*!
            * @brief Indicates whether this control can get focus by navigating with the trackpad.
            *
            * @return The focus policy when navigating with the trackpad.
            *
            * @since BlackBerry 10.3.1
            */
            bb::cascades::NavigationFocusPolicy::Type focusPolicy() const;

            /*!
            * @brief Sets whether this control can get focus by navigating with the trackpad.
            *
            * @param focusPolicy The focus policy when navigating with the trackpad.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setFocusPolicy(bb::cascades::NavigationFocusPolicy::Type focusPolicy);

            /*!
            * @brief Resets the focusPolicy property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetFocusPolicy();

            /*!
            * @brief Indicates whether the default highlight should be shown when @c wantsHighlight is @c true.
            *
            * @return @c true if the default highlight is enabled, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            bool isDefaultHighlightEnabled() const;

            /*!
            * @brief Sets whether the default highlight should be shown when @c wantsHighlight is @c true.
            *
            * @param enabled @c true if the default highlight should be enabled, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setDefaultHighlightEnabled(bool enabled);

            /*!
            * @brief Resets the @c defaultHighlightEnabled property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetDefaultHighlightEnabled();

            /*!
            * @brief Indicates whether the control wants a navigation highlight.
            *
            * @return @c true if the control expects a highlight to be shown, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            bool wantsHighlight() const;

Q_SIGNALS:
            /*!
            * @brief Emitted when the target of left navigations has changed.
            *
            * @param target The new target of a left navigation.
            *
            * @since BlackBerry 10.3.1
            */
            void leftChanged(bb::cascades::Control* target);

            /*!
            * @brief Emitted when the @c leftAllowed property has changed.
            *
            * @param allowed If @c true left navigation is allowed, if @c false left navigation is not allowed.
             *
             * @since BlackBerry 10.3.1
            */
            void leftAllowedChanged(bool allowed);

            /*!
            * @brief Emitted when the target of right navigation has changed.
            *
            * @param target The new target of a right navigation.
            *
            * @since BlackBerry 10.3.1
            */
            void rightChanged(bb::cascades::Control* target);

            /*!
            * @brief Emitted when the @c rightAllowed property has changed.
            *
            * @param allowed If @c true right navigation is allowed, if @c false right navigation is not allowed.
             *
             * @since BlackBerry 10.3.1
            */
            void rightAllowedChanged(bool allowed);

            /*!
            * @brief Emitted when the target of up navigation has changed.
            *
            * @param target The new target of an up navigation.
            *
            * @since BlackBerry 10.3.1
            */
            void upChanged(bb::cascades::Control* target);

            /*!
            * @brief Emitted when the @c upAllowed property has changed.
            *
            * @param allowed If @c true up navigation is allowed, if @c false up navigation is not allowed.
             *
             * @since BlackBerry 10.3.1
            */
            void upAllowedChanged(bool allowed);

            /*!
            * @brief Emitted when the target of down navigation has changed.
            *
            * @param target The new target of a down navigation.
            *
            * @since BlackBerry 10.3.1
            */
            void downChanged(bb::cascades::Control* target);

            /*!
            * @brief Emitted when the @c downAllowed property has changed.
            *
            * @param allowed If @c true down navigation is allowed, if @c false down navigation is not allowed.
            *
            * @since BlackBerry 10.3.1
            */
            void downAllowedChanged(bool allowed);

            /*!
            * @brief Emitted when the @c focusPolicy property has changed.
            *
            * @param newFocusPolicy The focus policy when navigating with the trackpad.
            *
            * @since BlackBerry 10.3.1
            */
            void focusPolicyChanged(bb::cascades::NavigationFocusPolicy::Type newFocusPolicy);

            /*!
            * @brief Emitted when the @c defaultHighlightEnabled property has changed.
            *
            * @param enabled @c true if the default highlight is enabled, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            void defaultHighlightEnabledChanged(bool enabled);

            /*!
            * @brief Emitted when the @c wantsHighlight property has changed.
            *
            * @param wantsHighlight @c true if the control expects a highlight to be shown, @c false otherwise.
            *
            * @since BlackBerry 10.3.1
            */
            void wantsHighlightChanged(bool wantsHighlight);

        protected:
            /*! @cond PRIVATE */
            Navigation(Control* parent = 0);
            explicit Navigation(NavigationPrivate &_d_ptr, Control *parent = 0);
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(Navigation)
            Q_DISABLE_COPY(Navigation)
            /*! @endcond */
        };
    }
}

QML_DECLARE_TYPE(bb::cascades::Navigation)

#endif // cascades_navigation_h
