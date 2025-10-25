/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_control_h
#define cascades_control_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/visualnode.h>
#include "bb/cascades/controls/focuspolicy.h"
#include "bb/cascades/controls/spacings.h"
#include <bb/cascades/layouts/horizontalalignment.h>
#include <bb/cascades/layouts/verticalalignment.h>
#include <bb/cascades/controls/focusretentionpolicy.h>
#include <bb/cascades/controls/focusautoshow.h>
#include <bb/cascades/controls/inputrouteproperties.h>
#include <bb/cascades/accessibility/abstracta11yobject.h>
#include <bb/cascades/accessibility/a11ymode.h>
#include <bb/cascades/core/systemshortcuts.h>

namespace bb {
    namespace cascades {

    class ActionSet;
    class ControlPrivate;
    class ContextMenuHandler;
    class LayoutProperties;
    class KeyListener;
    class AbstractShortcut;
    class Navigation;
 
    /*!
     *
     * @brief Base class for all UI controls.
     * @image html controls.png
     *
     * The @c %Control class contains properties for specifying the following types of
     * control attributes:
     * - preferred width and height
     * - maximum and minimum width and height
     * - margins 
     * - enabled state
     * - layout properties used by the parent container
     * - contextual actions for a control
     * - horizontal and vertical alignment (only to be used for controls in a @c StackLayout or @c DockLayout)
     *
     * @c %Control should not be used directly, nor should it be subclassed. If you want to implement 
     * your own custom controls you should subclass @c CustomControl instead.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Control : public VisualNode {
        Q_OBJECT

        /*!
         * @brief Specifies the @c HorizontalAlignment for the control.
         * 
         * The default alignment is @c HorizontalAlignment::Left.    
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::HorizontalAlignment::Type horizontalAlignment
                   READ horizontalAlignment
                   WRITE setHorizontalAlignment
                   RESET resetHorizontalAlignment
                   NOTIFY horizontalAlignmentChanged
                   FINAL)
        /*!
         * @brief Specifies the @c VerticalAlignment for the control.
         * 
         * The default alignment is @c VerticalAlignment::Top.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::VerticalAlignment::Type verticalAlignment
                   READ verticalAlignment
                   WRITE setVerticalAlignment
                   RESET resetVerticalAlignment
                   NOTIFY verticalAlignmentChanged
                   FINAL)
            
        /*!
         * @brief The preferred width of the control.
         *
         * The preferred width is a positive value
         * used by the @c Layout of the parent @c Container to position the control. If the preferred 
         * width for a control is not set (or was set but has since been reset), the parent container
         * ignores this value and uses the control-specific default width. See the 
         * API reference for a specific control for more details about its default width. You can 
         * check whether the @c preferredWidth of a control is set by calling @c isPreferredWidthSet().
         *
         * However, just because the preferred width has been set on a control, does not mean it is being used.
         * The preferred width is ignored by the parent container if it is smaller
         * than the minimum size allowed for that control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float preferredWidth READ preferredWidth WRITE setPreferredWidth RESET resetPreferredWidth NOTIFY preferredWidthChanged FINAL)
      
        /*!
         * @brief Indicates whether the @c #preferredWidth of a control is set.
         *
         * If @c true the preferred width has been set on a control, if @c false the 
         * preferred width is not set. 
         * By default, @c preferredWidthSet is @c false, meaning that the parent container
         * ignores the preferred width and uses the control-specific default
         * instead.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool preferredWidthSet READ isPreferredWidthSet NOTIFY preferredWidthSetChanged FINAL);
      
        /*!
         * @brief The preferred height of the control.
         *
         * The preferred height is a positive value
         * used by the @c Layout of the parent @c Container to position the control. If the preferred 
         * height for a control is not set, the parent container 
         * ignores this value and uses the control-specific default height. See the 
         * API reference for a specific control for more details about its default height. You can 
         * check whether the @c preferredHeight of a control is set by calling @c isPreferredHeightSet().
         *
         * However, just because the preferred height has been set on a control, does not mean it is being used.
         * The preferred height is ignored by the parent container if it is smaller
         * than the minimum size allowed for that control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float preferredHeight READ preferredHeight WRITE setPreferredHeight RESET resetPreferredHeight NOTIFY preferredHeightChanged FINAL)
      
        /*!
         * @brief Indicates whether the @c #preferredHeight of a control is set.
         *
         * If @c true the preferred height has been set on a control, if @c false the 
         * preferred height is not set. 
         * By default, @c preferredHeightSet is @c false, meaning that the parent container
         * ignores the preferred height and uses the control-specific default
         * instead.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool preferredHeightSet READ isPreferredHeightSet NOTIFY preferredHeightSetChanged FINAL);
      
      
      
        /*!
         * @brief The left padding for the control.
         *
         * The default left padding is 0.
         *
         * Left padding only works for the following controls, for all other controls left padding is undefined:
         * - Container
         * - ListView
         * - TextArea
         * - TextField
         * 
         * Negative padding values are supported in the @c %ListView control, for all other controls
         * negative padding is undefined.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float leftPadding
                   READ leftPadding
                   WRITE setLeftPadding
                   RESET resetLeftPadding
                   NOTIFY leftPaddingChanged
                   FINAL)
      
        /*!
         * @brief The right padding for the control.
         *
         * The default right padding is 0.
         *
         * Right padding only works for the following controls, for all other controls right padding is undefined:
         * - Container
         * - ListView
         * - TextArea
         * - TextField
         *
         * Negative padding values are supported in the @c %ListView control, for all other controls
         * negative padding is undefined.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_PROPERTY(float rightPadding
                   READ rightPadding
                   WRITE setRightPadding
                   RESET resetRightPadding
                   NOTIFY rightPaddingChanged
                   FINAL)
      
        /*!
         * @brief The top padding for the control.
         *
         * The default top padding is 0.
         *
         * Top padding only works for the following controls, for all other controls top padding is undefined:
         * - Container
         * - ListView
         *
         * Negative padding values are supported in the @c %ListView control, for all other controls
         * negative padding is undefined.
         *
         * @since BlackBerry 10.0.0
         */            
        Q_PROPERTY(float topPadding
                   READ topPadding
                   WRITE setTopPadding
                   RESET resetTopPadding
                   NOTIFY topPaddingChanged
                   FINAL)
      
        /*!
         * @brief The bottom padding for the control.
         *
         * The default bottom padding is 0.
         *
         * Bottom padding only works for the following controls, for all other controls bottom padding is undefined:
         * - Container
         * - ListView
         *
         * Negative padding values are supported in the @c %ListView control, for all other controls
         * negative padding is undefined.
         *
         * @since BlackBerry 10.0.0
         */                  
        Q_PROPERTY(float bottomPadding
                   READ bottomPadding
                   WRITE setBottomPadding
                   RESET resetBottomPadding
                   NOTIFY bottomPaddingChanged
                   FINAL)      


        /*!
         * @brief Indicates whether the control is enabled.
         *
         * When a control is disabled, it does not 
         * respond to user input. The disabled control continues to receive events, but does not process them.
         * Changing the enabled state may also affect the appearance of the control.
         * 
         * If @c true the control is enabled, if @c false it's disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled RESET resetEnabled NOTIFY enabledChanged FINAL)
               
        /*!
        * @brief The focus retention policy that determines the conditions under which a control loses focus.
        *
        * Normally, a control loses focus whenever a user touches outside of the control or on another control, or when scrolling
        * a @c ListView (may differ from device to device). However, it may be convenient at times to retain focus. This property
        * makes it possible to specify the conditions under which the control should lose focus and when it shouldn't.
        * The property only affects focus changes initiated by user interaction, not when programmatically changing focus (i.e.
        * by calling @c requestFocus() on a control).
        *
        * Here's an example of how to set the focus retention policy in QML:
        * 
        * @snippet tad/examples/controls/control/assets/main.qml control_qml1
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::FocusRetentionPolicy::Types focusRetentionPolicyFlags READ focusRetentionPolicyFlags
                   WRITE setFocusRetentionPolicyFlags RESET resetFocusRetentionPolicyFlags NOTIFY focusRetentionPolicyFlagsChanged FINAL)

        /*!
         * @brief Indicates whether the control is focused.
         *
         * If @c true the control is focused, if @c false it's not focused.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool focused READ isFocused NOTIFY focusedChanged FINAL)

        /*!
         * @brief Indicates whether this control is focusable or not and what kind of user input focus can be received (touch and/or key).
         *
         * The default @c focusPolicy value is @c None. A disabled @c %Control can not have focus.
         * 
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::FocusPolicy::Type focusPolicy READ focusPolicy WRITE setFocusPolicy RESET resetFocusPolicy NOTIFY focusPolicyChanged FINAL)

        /*!
         * @brief Indicates whether a control should automatically be made visible when it receives focus.
         *
         * The default @c focusAutoShow value is @c Default.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::FocusAutoShow::Type focusAutoShow READ focusAutoShow WRITE setFocusAutoShow RESET resetFocusAutoShow NOTIFY focusAutoShowChanged FINAL)

        /*!
         * @brief Indicates whether the control has local focus.
         *
         * Each focus scope keeps track of a local focus. The local focus can be used to set which control should get focus when navigating to the focus scope.
         * If the focus scope contains the actual focus when setting local focus to true, actual will be requested by this control.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bool locallyFocused READ isLocallyFocused WRITE setLocallyFocused RESET resetLocallyFocused NOTIFY locallyFocusedChanged REVISION 4 FINAL)

        /*!
         * @brief Defines this control's role in the propagation of input events.
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
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::InputRouteProperties* inputRoute READ inputRoute FINAL)

        /*!
         * @brief The layout properties for the control.
         *
         * The @c layoutProperties property specifies how the parent container should position and size the 
         * control. The layoutProperties object must match the Layout type of the container. For example, if the 
         * parent container uses a stack layout, the @c layoutProperties should be a @c StackLayoutProperties object.
         *
         * By default, a control's @c layoutProperties is @c 0. If the @c layoutProperties for a control is not 
         * explicitly set, the parent container uses the default layout properties for the type of 
         * layout that it's using.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::LayoutProperties* layoutProperties READ layoutProperties WRITE setLayoutProperties RESET resetLayoutProperties NOTIFY layoutPropertiesChanged FINAL)

        /*!
         * @brief Full margins for the control.
         *
         * Margins are positive values that specify the space around a control.
         *
         * How the margin is actually used depends on how the control is laid out within its parent,
         * both @c Containers, @c ListViews and @c ScrollViews (and other controls that have children)
         * can use the information to position their children.
         *
         * For example when the control is laid out in a @c StackLayout, the margin is considered both for the
         * distance from the side of the parent and between the siblings in the
         * layout direction. In such a case the distance between two children in the layout direction will be
         * the largest margin of the two adjacent children in the layout direction.
         *
         * For @c DockLayout the margin values will affect only the position from the side of the parent to the child.
         *
         * The Margin group property is not created until it's needed, default value for the margins of a control are
         * undefined which means that the containing parent will decide. In the margins group property this is specified
         * by the float values defaulting to @c NAN.
         *
         * This is a new API that will replace the current version using #topMargin et.c. but
         * until the support is fully implemented in all Containing Controls, the old way is not deprecated. 
         * I the current version the difference between using the margin group property and separate margin properties
         * (#topMargin et.c.) is that the group property can be used both for the space between siblings in a @c StackLayout
         * and @c StackListLayout but that the Layouts in a container also use it to position the children from the inside of
         * the container. Lessening the need for extra layers of containers with padding. 
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bb::cascades::Spacings* margin READ margin REVISION 3)
      
        /*!
         * @brief The accessibility mode for the control.
         *
         * This property defines how the control and its subtree will be exposed to assistive technologies.
         * The default value is @c Default which means that the framework automates accessibility mode based on accessible
         * information and context. Typically accessibility information is assumed to be available, unless any parent is
         * configured with accessibilityMode = Collapsed.
         *
         * When accessibility information is available, the @c accessibility property will be used to define the accessibility properties.
         *
         * @see @c #accessibility
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bb::cascades::A11yMode::Type accessibilityMode READ accessibilityMode WRITE setAccessibilityMode RESET resetAccessibilityMode NOTIFY accessibilityModeChanged REVISION 2 FINAL);

        /*!
         * @brief Defines the control's accessibility object.
         *
         * Accessibility objects are used by assistive technologies for
         * people with disabilities or special needs (for example, visual impairment).
         *
         * QML usage:
         * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml1
         *
         * C++ usage:
         * @snippet tad/examples/accessibility/src/AccessibilityExamples.cpp accessibility1
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bb::cascades::AbstractA11yObject* accessibility READ accessibility REVISION 2)

        /*!
         * @brief The left margin for the control.
         *
         * Margins are positive values that specify the space around a control.
         *
         * How the margin is actually used depends on how the control is laid out within its parent container.
         * When the control is laid out in a @c StackLayout, the margin is considered between the siblings in the
         * layout direction. In that case the distance between two children in the layout direction will be
         * the largest margin of the two adjacent margins in the layout direction.
         *
         * The default value depends on the actual control. For the @c Container class the value is 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float leftMargin READ leftMargin WRITE setLeftMargin RESET resetLeftMargin NOTIFY leftMarginChanged FINAL)

        /*!
         * @brief Indicates whether the @c #leftMargin of a control is set.
         *
         * If @c true the left margin has been set on a control, if @c false the 
         * leftMargin is not set. 
         * By default, @c leftMargin is @c false, meaning that the control will use control-specific default
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool leftMarginSet READ isLeftMarginSet NOTIFY leftMarginSetChanged FINAL);

        /*!
         * @brief The right margin for the control.
         *
         * Margins are positive values that specify the space around a control.
         *
         * How the margin is actually used depends on how the control is laid out within it's parent container.
         * When the control is laid out in a @c StackLayout, the margin is considered between the siblings in the
         * layout direction. In that case the distance between two children in the layout direction will be
         * the largest margin of the two adjacent margins in the layout direction.
         *
         * The default value depends on the actual control. For the @c Container class the value is 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float rightMargin READ rightMargin WRITE setRightMargin RESET resetRightMargin NOTIFY rightMarginChanged FINAL)

        /*!
         * @brief Indicates whether the @c #rightMargin of a control is set.
         *
         * If @c true the right margin has been set on a control, if @c false the 
         * rightMargin is not set. 
         * By default, @c rightMargin is @c false, meaning that the control will use control-specific default
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool rightMarginSet READ isRightMarginSet NOTIFY rightMarginSetChanged FINAL);

        /*!
         * @brief The top margin for the control.
         *
         * Margins are positive values that specify the space around a control.
         *
         * How the margin is actually used depends on how the control is laid out within it's parent container.
         * When the control is laid out in a @c StackLayout, the margin is considered between the siblings in the
         * layout direction. In that case the distance between two children in the layout direction will be
         * the largest margin of the two adjacent margins in the layout direction.
         *
          * The default value depends on the actual control. For the @c Container class the value is 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float topMargin READ topMargin WRITE setTopMargin RESET resetTopMargin NOTIFY topMarginChanged FINAL)

        /*!
         * @brief Indicates whether the #topMargin of a control is set.
         *
         * If @c true the top Margin has been set on a control, if @c false the 
         * topMargin is not set. 
         * By default, @c topMargin is @c false, meaning that the control will use control-specific default
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool topMarginSet READ isTopMarginSet NOTIFY topMarginSetChanged FINAL);

        /*!
         * @brief The bottom margin for the control.
         *
         * Margins are positive values that specify the space around a control.
         *
         * How the margin is actually used depends on how the control is laid out within it's parent container.
         * When the control is laid out in a @c StackLayout, the margin is considered between the siblings in the
         * layout direction. In that case the distance between two children in the layout direction will be
         * the largest margin of the two adjacent margins in the layout direction.
         *
         * 
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float bottomMargin READ bottomMargin WRITE setBottomMargin RESET resetBottomMargin NOTIFY bottomMarginChanged FINAL)

        /*!
         * @brief Indicates whether the @c #bottomMargin of a control is set.
         *
         * If @c true the bottom Margin has been set on a control, if @c false the 
         * bottomMargin is not set. 
         * By default, @c bottomMargin is @c false, meaning that the control will use control-specific default
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool bottomMarginSet READ isBottomMarginSet NOTIFY bottomMarginSetChanged FINAL);

        /*!
         * @brief The minimum width for the control.
         *
         * The min width is a positive value used by the layout system to position
         * the control.
         *
         * The default @c minWidth for a control is 0.0. The control can determine the effective @c minWidth of
         * a control by combining the @c minWidth with the size of contents of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float minWidth READ minWidth WRITE setMinWidth RESET resetMinWidth NOTIFY minWidthChanged FINAL)

        /*!
         * @brief The maximum width for the control.
         *
         * The max width is a positive value used by the layout system to position
         * the control.
         *
         * The default @c maxWidth is infinitely large (no limit). The control can determine the effective @c 
         * maxWidth of a control by combining the @c maxWidth with the size of contents of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float maxWidth READ maxWidth WRITE setMaxWidth RESET resetMaxWidth NOTIFY maxWidthChanged FINAL)

        /*!
         * @brief The minimum height for the control.
         *
         * The min height is a positive value used by the layout system to position
         * the control.
         *
         * The default @c minHeight for a control is 0.0. The control can determine the effective @c minHeight of
         * a control by combining the @c minHeight with the size of contents of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float minHeight READ minHeight WRITE setMinHeight RESET resetMinHeight NOTIFY minHeightChanged FINAL)

        /*!
         * @brief The maximum height for the control.
         *
         * The max height is a positive value used by the layout system to position
         * the control.
         *
         * The default @c maxHeight is infinitely large (no limit). The control can determine the effective @c 
         * maxHeight of a control by combining the @c maxHeight with the size of contents of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float maxHeight READ maxHeight WRITE setMaxHeight RESET resetMaxHeight NOTIFY maxHeightChanged FINAL)
        
       /*!
        * @brief A list of @c ActionSet object that are displayed in the control's context menu.
        *
        * These action sets are displayed in the Context Menu for this control. When the context menu is opened, 
        * the first @c ActionSet object in the list is displayed initially, and the user can cycle through them in 
        * the order that they are added to the control.
        *
        * @see ActionSet
        *
        * @xmlonly
        * <qml>
        * <property name="contextActions" listType="bb::cascades::ActionSet" defaultProperty="no"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */                   
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::ActionSet> contextActions READ contextActions FINAL)

       /*!
        * @brief The handler for interacting with the Context menu for this Control.
        *
        * Setting this handler allows you to listen on events from the Context menu.
        * For example the @c ContextMenuHandler::showing() signal is emitted when the Context
        * menu is about to show, allowing you to update the content of your context
        * actions just-in-time.
        *
        * @see @c #contextActions, @c ContextMenuHandler::showing()
        *
        * The default value is @0, indicating no %ContextMenuHandler is set.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ContextMenuHandler* contextMenuHandler READ contextMenuHandler WRITE setContextMenuHandler RESET resetContextMenuHandler NOTIFY contextMenuHandlerChanged FINAL)

       /*!
        * @brief Enables or disables implicit animations when layout-related properties for a @c Control are changed.
        *
        * This property affects implicit animations on the following properties for a control.
        *
        * - positioning in a layout, including x and y coordinates and horizontal and vertical alignment
        * - preferred height and width
        * - maximum and minimum height and width
        * - margins and padding
        *
        * The default is @c true meaning that implicit animations are enabled.
        *
        * For @c VisualNode properties, you can customize implicit animations by using @c ImplicitAnimationController.
        * These properties include translation, rotation, scaling, pivoting, and opacity.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool implicitLayoutAnimationsEnabled READ implicitLayoutAnimationsEnabled WRITE setImplicitLayoutAnimationsEnabled
                   RESET resetImplicitLayoutAnimationsEnabled NOTIFY implicitLayoutAnimationsEnabledChanged FINAL);

       /*!
        * @brief A list of shortcuts that can be triggered via user actions.
        *
        * The order in which they are added will determine which shortcut will be triggered in case of an overlap.
        * Note that predefined shortcuts have precedence over shortcuts defined via QString in case of a collision
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
        * @brief A list of key listeners attached to this control.
        *
        * The order in which key listeners are added does not change their behavior
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
        * @brief Enables or disables all Control's built-in shortcuts.
        *
        * This property is used when all Control's built-in shortcuts should be enabled or disabled.
        * Cotrol's built-in shortcuts are shortcuts like Navigation shortcuts in @c ScrollView
        * and @c ListView.
        *
        * @since BlackBerry 10.2.0
        */
        Q_PROPERTY(bool builtInShortcutsEnabled READ builtInShortcutsEnabled WRITE setBuiltInShortcutsEnabled
                   RESET resetBuiltInShortcutsEnabled NOTIFY builtInShortcutsEnabledChanged REVISION 2 FINAL)

       /*!
        * @brief Defines the behavior for navigation with trackpad and similar input.
        *
        * @since BlackBerry 10.3.1
        */
        Q_PROPERTY(bb::cascades::Navigation* navigation READ navigation CONSTANT REVISION 4 FINAL)

    public:
        virtual ~Control();

       /*!
        * @brief Adds a shortcut to the @c %Control. 
        *
        * The @c %Control will always take ownership as shortcuts should never be shared.
        * If the shortcut already belongs to the @c %Control or the @c shortcut is @c 0, nothing will happen.
        * The order in which shortcuts are added will determine which shortcut will be triggered in case of an overlap.
        *      
        * @param shortcut The @c AbstractShortcut to add to the @c %Control.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void addShortcut(bb::cascades::AbstractShortcut* shortcut);

       /*!
        * @brief Removes a shortcut from the @c %Control. 
        *
        * Once the shortcut is removed, the @c %Control no longer references it, but it is still 
        * owned by the @c %Control. It is up to the application to either delete the removed 
        * shortcut, transfer its ownership (by setting its parent) to another object, or leave 
        * it as a child of the @c %Control (in which case it will be deleted with the @c %Control).
        *  
        * @param shortcut The @c AbstractShortcut to remove.
        * @return @c true if the shortcut was owned by the @c %Control, @c false otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bool removeShortcut(bb::cascades::AbstractShortcut* shortcut);

       /*!
        * @brief Removes all of a control's shortcuts and frees up their memory.        
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
        * Ownership of the shortcut remains with the @c %Control.
        *                       
        * @param index The index of the shortcut.
        * @return The requested shortcut if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bb::cascades::AbstractShortcut* shortcutAt(int index) const;

       /*!
        * @brief Enables all shortcuts attached to the @c %Control
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void enableAllShortcuts();
        
       /*!
        * @brief Disables all shortcuts attached to the @c %Control
        * 
        * Shortcuts that are attached afterward will use the default enabled state.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void disableAllShortcuts();

       /*!
        * @brief Returns an builtInShortcutsEnabled property value.
        *
        * @return true if builtInShortcutsEnabled property is set to @c true and @c false otherwise
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_INVOKABLE bool builtInShortcutsEnabled() const;

       /*!
        * @brief Sets the enabled state of all built-in shortcuts attached to the @c %Control at a system level
        *
        * Built-in Shortcuts that are attached afterward will use the specified enabled state.
        *
        * @param enabled If @c true all built-in shortcuts are enabled, and if @c false all built-in shortcut are disabled.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_SLOT void setBuiltInShortcutsEnabled(bool enabled);


       /*!
        * @brief Resets an builtInShortcutsEnabled property to default value.
        *
        * Default value is true.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_INVOKABLE void resetBuiltInShortcutsEnabled();

       /*!
        * @brief Sets the enabled state of the built-in shortcut attached to the @c %Control at a system level
        *
        * Built-in Shortcuts that are attached afterward will use the specified enabled state.
        *
        * @note Selected Built-In shortcut can be enabled or disabled only if @c Control::builtInShortcutsEnabled
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
        * @brief Adds a key listener to the @c %Control. 
        *
        * The @c %Control will always take ownership as a key listener should never be shared.
        * If the key listener already belongs to the @c %Control or the @c key listener is @c 0, nothing will happen.               
        *
        * @param keyListener The @c KeyListener to add to the @c %Control.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE void addKeyListener(bb::cascades::KeyListener* keyListener);

       /*!
        * @brief Removes a key listener from the @c %Control. 
        *
        * Once the key listener is removed, the @c %Control no longer references it, but it is still 
        * owned by the @c %Control. It is up to the application to either delete the removed 
        * key listener, transfer its ownership (by setting its parent) to another object, or leave 
        * it as a child of the @c %Control (in which case it will be deleted with the @c %Control).
        *  
        * @param keyListener The @c KeyListener to remove.
        * @return @c true if the key listener was owned by the @c %Control, @c false otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bool removeKeyListener(bb::cascades::KeyListener* keyListener);

       /*!
        * @brief Removes all of a Control's key listeners and frees up their memory.        
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
        * Ownership of the key listener remains with the @c %Control.
        *                       
        * @param index The index of the key listener.
        * @return The requested key listener if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.1.0
        */
        Q_INVOKABLE bb::cascades::KeyListener* keyListenerAt(int index) const;

        /*!
         * @brief Returns the horizontal alignment for the control.
         * 
         * @return The horizontal alignment for the control.
         *
         * @since BlackBerry 10.0.0
         */ 
        bb::cascades::HorizontalAlignment::Type horizontalAlignment() const;

        /*!
         * @brief Sets the horizontal alignment for the control.
         * 
         * After the horizontal alignment is set, the @c horizontalAlignmentChanged() signal is emitted.
         *
         * @param horizontalAlignment The horizontal alignment for the control.
         *
         * @since BlackBerry 10.0.0
         */  
        Q_SLOT void setHorizontalAlignment(bb::cascades::HorizontalAlignment::Type horizontalAlignment);

        /*!
         * @brief Resets the horizontal alignment to its default.
         *
         * The default alignment is @c HorizontalAlignment::Left.
         *
         * After the horizontal alignment is reset, the @c horizontalAlignmentChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */  
        Q_SLOT void resetHorizontalAlignment();

        /*!
         * @brief Returns the vertical alignment for the control.
         *
         * @return The vertical alignment for the control.
         *
         * @since BlackBerry 10.0.0
         */   
        bb::cascades::VerticalAlignment::Type verticalAlignment() const;
        /*!
         * @brief Sets the vertical alignment for the control.
         *
         * After the vertical alignment is set, the @c verticalAlignmentChanged() signal is emitted.
         * 
         * @param verticalAlignment The vertical alignment for the control.
         *
         * @since BlackBerry 10.0.0
         */   
        Q_SLOT void setVerticalAlignment(bb::cascades::VerticalAlignment::Type verticalAlignment);
        /*!
         * @brief Resets the vertical alignment to its default.
         *
         * The default alignment is @c VerticalAlignment::Top.
         *
         * After the vertical alignment is reset, the @c verticalAlignmentChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */           
        Q_SLOT void resetVerticalAlignment();


        /*!
         * @brief Returns the @c #preferredWidth of the control.
         *
         * To check whether the preferred width 
         * is set for the control, call @c isPreferredWidthSet().
         *
         * @return The preferred width of a control as a positive number, or @c 0 if the preferred 
         * width is not set.
         *
         * @since BlackBerry 10.0.0
         */
        float preferredWidth() const;

        /*!
         * @brief Sets the @c #preferredWidth of the control.
         *
         * @param preferredWidth The preferred width of the control as a positive, non-zero number.
         *
         * @see @c setPreferredSize()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPreferredWidth(float preferredWidth);

        /*!
         * @brief Resets the @c #preferredWidth to its default value of @c 0.
         *
         * @see @c resetPreferredSize()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPreferredWidth();

       /*!
        * @brief Sets the focus retention policy. The policy describes under which condtions the control will lose focus.
        *
        * @param policy The new policy.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setFocusRetentionPolicyFlags(bb::cascades::FocusRetentionPolicy::Types policy);


       /*!
        * @brief Gets the focus retention policy. The policy describes under which condtions the control will lose focus
        *
        *
        * @return The focus retention policy for this control.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::FocusRetentionPolicy::Types focusRetentionPolicyFlags();

       /*!
        * @brief Reset the focus retention policy to default value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetFocusRetentionPolicyFlags();


        /*!
         * @brief Indicates whether the @c #preferredWidth of the control is set.
         *
         * @return @c true if the preferred width is set, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isPreferredWidthSet() const;

        /*!
         * @brief Returns the @c #preferredHeight of the control.
         *
         * To check whether the preferred height 
         * is set for a control, call @c isPreferredHeightSet().
         *
         * @return The preferred height of a control as a positive number, or @c 0 if the preferred 
         * width is not set.
         *
         * @since BlackBerry 10.0.0
         */
        float preferredHeight() const;


        /*!
         * @brief Sets the @c #preferredHeight of the control.
         *
         * @param preferredHeight The preferred height of the control as a positive, non-zero number.
         *
         * @see setPreferredSize()         
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPreferredHeight(float preferredHeight);

        /*!
         * @brief Resets the @c #preferredHeight to its default value of @c 0.
         *
         * @see resetPreferredSize()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPreferredHeight();

        /*!
         * @brief Indicates whether the @c #preferredHeight of the control is set.
         *
         * @return @c true if the preferred height is set, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isPreferredHeightSet() const;
        
        /*!
         * @brief Sets the preferred width and height of the control.
         *
         * A convenience function for setting both preferred width and height. 
         * It is equivalent to calling both @c setPreferredWidth() and @c setPreferredHeight().
         *
         * @param preferredWidth The preferred width of the control as a positive, non-zero number.
         * @param preferredHeight The preferred height of the control as a positive, non-zero number.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPreferredSize(float preferredWidth, float preferredHeight);

        /*!
         * @brief Resets the preferred width and height of the control.
         *
         * A convenience function for resetting both the preferred width and height.
         * It is equivalent to calling both @c resetPreferredWidth() and @c resetPreferredHeight().
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPreferredSize();
      
        /*!
         * @brief Returns the left padding on the control.
         *
         * @return The left padding.
         *
         * @since BlackBerry 10.0.0
         */
        float leftPadding() const;
      
        /*!
         * @brief Sets the left padding for the control.
         *
         * After the padding is set, the @c leftPaddingChanged() signal is emitted.
         *
         * @param leftPadding The new left padding.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_SLOT void setLeftPadding(float leftPadding);
      
        /*!
         *@brief  Resets the left padding to its default.
         *
         * The default left padding is 0.
         *
         * After the padding is reset, the @c leftPaddingChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_SLOT void resetLeftPadding();
      
        /*!
         * @brief Returns the right padding on the control.
         *
         * @return The right padding.
         *
         * @since BlackBerry 10.0.0
         */
        float rightPadding() const;
      
        /*!
         * @brief Sets the right padding for the control.
         *
         * After the padding is set, the @c rightPaddingChanged() signal is emitted.
         *
         * @param rightPadding The new left padding.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setRightPadding(float rightPadding);
      
        /*!
         * @brief Resets the right padding to its default.
         *
         * The default right padding is 0.
         *
         * After the padding is reset, the @c rightPaddingChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetRightPadding();
      
        /*!
         * @brief Returns the top padding on the control.
         *
         * @return The top padding.
         *
         * @since BlackBerry 10.0.0
         */      
        float topPadding() const;
      
        /*!
         * @brief Sets the top padding for the control.
         *
         * After the padding is set, the @c topPaddingChanged() signal is emitted.
         *
         * @param topPadding The new left padding.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_SLOT void setTopPadding(float topPadding);
      
        /*!
         * @brief Resets the top padding to its default.
         *
         * The default top padding is 0.
         *
         * After the padding is reset, the @c topPaddingChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTopPadding();
      
        /*!
         * @brief Returns the bottom padding on the control.
         *
         * @return The bottom padding.
         *
         * @since BlackBerry 10.0.0
         */            
        float bottomPadding() const;
      
        /*!
         * @brief Sets the bottom padding for the control.
         *
         * After the padding is set, the @c bottomPaddingChanged() signal is emitted.
         *
         * @param bottomPadding The new left padding.
         *
         * @since BlackBerry 10.0.0
         */            
        Q_SLOT void setBottomPadding(float bottomPadding);
      
        /*!
         * @brief Resets the bottom padding to its default.
         *
         * The default bottom padding is 0.
         *
         * After the padding is reset, the @c bottomPaddingChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_SLOT void resetBottomPadding();
      

        /*!
         * @brief Returns the @c #enabled state of the control.
         *
         * @return @c true if the control is enabled, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isEnabled() const;

        /*!
         * @brief Returns the @c #focusPolicy property of the control.
         *
         * @return The focusPolicy state of the control as a FocusPolicy 
         * 
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::FocusPolicy::Type focusPolicy() const;

        /*!
         * @brief Sets the @c #focusPolicy of the control.
         *
         * @param focusPolicy The focusPolicy state of the @c Control as a FocusPolicy.
         *
         * @see FocusPolicy
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setFocusPolicy(const bb::cascades::FocusPolicy::Type focusPolicy);

        /*!
         * @brief Resets the @c #focusPolicy to its default value of @c FOCUSPOLICY_NONE.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetFocusPolicy();

        /*!
         * @brief Returns the @c #focusAutoShow property of the control.
         *
         * @return The focusAutoShow state of the control
         *
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::FocusAutoShow::Type focusAutoShow() const;

        /*!
         * @brief Sets the @c #focusAutoShow of the control.
         *
         * @param focusAutoShow The focusAutoShow state of the @c Control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setFocusAutoShow(const bb::cascades::FocusAutoShow::Type focusAutoShow);

        /*!
         * @brief Resets the @c #focusAutoShow to its default value.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetFocusAutoShow();

        /*!
         * @brief Returns the @c #locallyFocused state of the control.
         *
         * @return @c true if the controls locallyFocused property is set, @c false otherwise.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        bool isLocallyFocused() const;

        /*!
         * @brief Sets the @c #locallyFocused of the control.
         *
         * @param locallyFocused The locallyFocused state of the @c Control.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void setLocallyFocused(bool locallyFocused);

        /*!
         * @brief Resets the @c #locallyFocused to its default value.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void resetLocallyFocused();

        /*!
         * @brief Returns the @c #focused state of the control.
         *
         * @return @c true if the control is focused, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isFocused() const;

        /*!
         * @brief Sets the @c #enabled state of the control.
         *
         * @param enabled If @c true the control is enabled and if @c false the control is disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setEnabled(bool enabled);

        /*!
         * @brief Resets the @c #enabled state of the control to @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetEnabled();

        /*!
         * @brief Returns the @c LayoutProperties object for the control.
         *
         * Ownership of the @c LayoutProperties object remains 
         * unchanged. 
         *
         * @return The layout properties for the control.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::LayoutProperties* layoutProperties() const;

        /*!
         * @brief Sets the @c #layoutProperties for the control. 
         * 
         * The control takes ownership of the @c LayoutProperties object if no other control owns it already. 
         * If the @c %LayoutProperties object already has an owner, the properties are applied to the control,
         * but ownership of the @c %LayoutProperties object remains unchanged. If the control already owns a 
         * @c %LayoutProperties object, the existing settings are replaced
         * by the specified @c %LayoutProperties object and the container retains ownership of both.
         *
         * @param layoutProperties The new layout properties for the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setLayoutProperties(bb::cascades::LayoutProperties *layoutProperties);

        /*!
         * @brief Resets the @c #layoutProperties for the control to @c 0 (automatic selection of @c 
         * LayoutProperties).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetLayoutProperties();

        /*!
         * @brief Returns the @c #margin group property for the control.
         *
         * @return The margin property for the control.
         *
         * @since BlackBerry 10.3.0
         */        
        bb::cascades::Spacings *margin();
      
        /*!
         * @brief Returns the @c #leftMargin for the control.
         *
         * @return The left margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        float leftMargin() const;

        /*!
         * @brief Sets the @c #leftMargin for the control.
         *
         * @param leftMargin The left margin for control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setLeftMargin(float leftMargin);

        /*!
         * @brief Resets the @c #leftMargin.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetLeftMargin();

        /*!
         * @brief Indicates whether the @c #leftMargin of the control is set.
         *
         * @return @c true if the left margin is set, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isLeftMarginSet() const;

        /*!
         * @brief Returns the @c #rightMargin for the control.
         *
         * @return The right margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        float rightMargin() const;

        /*!
         * @brief Sets the @c #rightMargin for the control.
         *
         * @param rightMargin The right margin for control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setRightMargin(float rightMargin);

        /*!
         * @brief Resets the #rightMargin.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetRightMargin();

        /*!
         * @brief Indicates whether the @c #rightMargin of the control is set.
         *
         * @return @c true if the right margin is set, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isRightMarginSet() const;

        /*!
         * @brief Returns the @c #topMargin for the control.
         *
         * @return The top margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        float topMargin() const;

        /*!
         * @brief Sets the @c #topMargin for the control.
         *
         * @param topMargin The top margin for control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTopMargin(float topMargin);

        /*!
         * @brief Resets the @c #topMargin.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTopMargin();

        /*!
         * @brief Indicates whether the @c #topMargin of the control is set.
         *
         * @return @c true if the top margin is set, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isTopMarginSet() const;

        /*!
         * @brief Returns the @c #bottomMargin for the control.
         *
         * @return The bottom margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        float bottomMargin() const;

        /*!
         * @brief Sets the @c #bottomMargin for the control.
         *
         * @param bottomMargin The bottom margin for control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setBottomMargin(float bottomMargin);

        /*!
         * @brief Resets the #bottomMargin.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetBottomMargin();

        /*!
         * @brief Indicates whether the @c #bottomMargin of the control is set.
         *
         * @return @c true if the bottom margin is set, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isBottomMarginSet() const;

        /*!
         * @brief Returns the @c #minWidth of the control.
         *
         * @return The minimum width of the control.
         *
         * @since BlackBerry 10.0.0
         */
        float minWidth() const;

        /*!
         * @brief Sets the @c #minWidth of the control.
         *
         * @param minWidth The new minimum width of the control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMinWidth(float minWidth);

        /*!
         * @brief Resets the @c #minWidth of the control.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMinWidth();

        /*!
         * @brief Returns the @c #maxWidth of the control.
         *
         * @return The maximum width of the control.
         *
         * @since BlackBerry 10.0.0
         */
        float maxWidth() const;

        /*!
         * @brief Sets the @c #maxWidth of the control.
         *
         * @param maxWidth The new maximum width of the control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMaxWidth(float maxWidth);

        /*!
         * @brief Resets the @c #maxWidth of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMaxWidth();

        /*!
         * @brief Returns the @c #minHeight of the control.
         *
         * @return The minimum height of the control.
         *
         * @since BlackBerry 10.0.0
         */
        float minHeight() const;

        /*!
         * @brief Sets the @c #minHeight of the control.
         *
         * @param minHeight The new minimum height of the control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMinHeight(float minHeight);

        /*!
         * @brief Resets the @c #minHeight of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMinHeight();

        /*!
         * @brief Returns the @c #maxHeight of the control.
         *
         * @return The maximum height of the control.
         *
         * @since BlackBerry 10.0.0
         */
        float maxHeight() const;

        /*!
         * @brief Sets the @c #maxHeight of the control.
         *
         * @param maxHeight The new maximum height of the control; must be greater than or equal to 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMaxHeight(float maxHeight);

        /*!
         * @brief Resets the @c #maxHeight of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMaxHeight();
        
       /*!
        * @brief Adds an @c ActionSet to the control.
        * 
        * The control takes ownership of the @c %ActionSet object, since 
        * @c %ActionSet objects should not typically be shared. If the @c %ActionSet is @c 0 or it already 
        * belongs to the control, the action set is not added. Once completed, the @c actionSetAdded()
        * signal is emitted.
        *
        * @see @c Control::contextActions
        *
        * @param actionSet The @c %ActionSet to add to the @c Control.
        *
        * @since BlackBerry 10.0.0
        */
        void addActionSet(bb::cascades::ActionSet* actionSet);

       /*!
        * @brief Returns the number of @c %ActionSet objects.
        *
        * @see @c Control::contextActions
        *
        * @return The number of @c %ActionSet objects.
        *
        * @since BlackBerry 10.0.0
        */
        int actionSetCount() const;

       /*!
        * @brief Returns an @c %ActionSet at a specified index.
        *
        * Ownership of the @c %ActionSet object remains with 
        * the control.
        *
        * @see @c Control::contextActions
        *
        * @param index The index of the @c %ActionSet.
        * @return The requested @c %ActionSet if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        ActionSet* actionSetAt(int index) const;

       /*!
        * @brief Removes an @c %ActionSet from the control.
        *
        * Once the @c %ActionSet is removed, the control no longer references it, but it is still 
        * owned by the control. It is up to the application to either delete the removed 
        * @c %ActionSet, transfer its ownership (by setting its parent) to another object or leave 
        * it as a child of the control (in which case it will be deleted with the control).
        *
        * Once completed, the @c actionSetRemoved() signal is emitted.
        *
        * @see @c Control::contextActions
        *
        * @param actionSet The actionSet to remove.
        * @return @c true if the @c ActionSet was owned by the @c %Control, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool removeActionSet(bb::cascades::ActionSet* actionSet);

       /*!
        * @brief Removes all @c ActionSet objects from the control and deletes them.
        *
        * Once completed, the @c actionSetRemoved() signal is emitted with @c 0 as its parameter.
        *
        * @see @c Control::contextActions
        *
        * @since BlackBerry 10.0.0
        */
        void removeAllActionSets();

       /*!
        * @brief Requests focus to this control.
        *
        * When requesting focus for a control, you must ensure that the control is currently
        * a part of the scene.
        *
        * A common use case for requesting focus is when a new @c Page is loaded into the scene.
        * For example, on a page that requires text input from the user, you might want to request
        * focus on a @c TextField as soon as the page loads so that the keyboard is automatically displayed.
        * In this scenario, the natural assumption might be to
        * request focus within the page's @c BaseObject::creationCompleted() signal, which is emitted once the object's
        * construction is complete. However, this approach is incorrect. Even though the object has been created, it
        * has not yet been added to the UI tree, so the call would fail.
        *
        * Here are two different methods that you can use for requesting focus. The first method involves listening for
        * changes to the @c Application::scene property. Here's a .qml file called RequestFocusPage.qml, which contains
        * a @c TextField that you want to request focus for as soon as the page loads. The page contains a @c variant property
        * that is bound to the application's @c scene property. When you declare a variable in QML, a value-change signal
        * is implicitly created as well. So, whenever this page gets added to the scene, the @c onAppSceneChanged() signal handler
        * is called where it's safe to request focus for the control.
        *
        * @snippet tad/examples/controls/controlrequestfocus/assets/RequestFocusPage.qml requestfocus_qml1
        *
        * The second method involves using a @c ComponentDefinition to load the pages. Here's another version
        * called RequestFocusPage2.qml. It contains a Boolean property called @c readyForFocus which is
        * initialized to @c false. When the value changes, the @c onreadyForFocusChanged() signal handler
        * is called and focus is requested.
        *
        * @snippet tad/examples/controls/controlrequestfocus/assets/RequestFocusPage2.qml requestfocus_qml2
        *
        * Here's how you can create the @c Page and set the @c readyForFocus property from
        * a @c ComponentDefinition in a @c NavigationPane:
        *
        * @snippet tad/examples/controls/controlrequestfocus/assets/main.qml requestfocus_qml3
        *
        * If succeeded, the @c focusedChanged() signal is emitted with @c true as its parameter.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void requestFocus();

       /*!
        * @brief Called when the control should lose its focus.
        *
        * If succeeded, the @c focusedChanged() signal is emitted with @c false as its parameter.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void loseFocus();
        /*!
        *
        * @return The @c ContextMenuHandler that was set or @c 0 if no handler was set.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::ContextMenuHandler* contextMenuHandler() const;

        /*!
        * @brief Sets the @c ContextMenuHandler for this @c %Control.
        *
        * The control takes ownership of the @c %ContextMenuHandler object. Once completed, 
        * the @c contextMenuHandlerChanged() signal is emitted.
        * The replaced context menu handler (if one was set) remains owned by the control.
        *
        * @param contextMenuHandler The @c %ContextMenuHandler to set or @c 0 to remove
        * currently set ContextMenuHandler.
        *
        * @since BlackBerry 10.0.0
        */
        void setContextMenuHandler(bb::cascades::ContextMenuHandler* contextMenuHandler);

        /*!
         * @brief Resets the @c contextMenuHandler property to the default value of @c 0.
         *
         * Removes the @c ContextMenuHandler from this @c control by resetting it to @c 0.
         *
         * @since BlackBerry 10.0.0
         */
         Q_SLOT void resetContextMenuHandler();

        /*!
         * @brief Controls whether layout changes trigger automatic animations or not.
         *
         * @param enable If true trigger animations, if false do not
         *
         * @since BlackBerry 10.0.0
         */
         Q_SLOT void setImplicitLayoutAnimationsEnabled(bool enable);

        /*!
         * @brief Return the current value of the #implicitLayoutAnimationsEnabled property
         *
         * @return If true layout changes will implicitely trigger animations, if false the animations are disabled.
         *
         * @since BlackBerry 10.0.0
         */
         bool implicitLayoutAnimationsEnabled() const;

        /*!
         * @brief Resets the implicitLayoutAnimationsEnabled property to its default value
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetImplicitLayoutAnimationsEnabled();

        /*!
         * @brief Controls how the control is exposed to assistive technologies.
         *
         * @param accessibilityMode The @c A11yMode to set on the control
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_SLOT void setAccessibilityMode(bb::cascades::A11yMode::Type accessibilityMode);

        /*!
         * @brief Return the current value of the #accessibilityMode property
         *
         * @return The @c A11yMode of the control.
         *
         * @since BlackBerry 10.2.0
         */
        bb::cascades::A11yMode::Type accessibilityMode() const;

        /*!
         * @brief Resets the @c accessibilityMode property to its default value of @c Default.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_SLOT void resetAccessibilityMode();

        /*!
         * @brief Returns the accessibility object.
         *
         * @return The accessibility object.
         */
        bb::cascades::AbstractA11yObject *accessibility() const;

        /*!
         * @brief Returns the input route properties object.
         *
         * @return The input route properties object.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::InputRouteProperties *inputRoute() const;

        /*!
         * @brief Returns a Navigation object that specifies the behavior for navigation with trackpad and similar input.
         *
         * @ return A Navigation object that specifies the behavior for navigation with trackpad and similar input.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        bb::cascades::Navigation* navigation() const;

    Q_SIGNALS:
        
        /*!
         * @brief Emitted when the @c #horizontalAlignment property changes.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c horizontalAlignment instead of @c newHorizontalAlignment).
         *
         * @param newHorizontalAlignment The new horizontal alignment for the control.
         *
         * @since BlackBerry 10.0.0
         */           
        void horizontalAlignmentChanged(bb::cascades::HorizontalAlignment::Type newHorizontalAlignment);
        /*!
         * @brief Emitted when the @c #verticalAlignment property changes.
         * 
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c verticalAlignment instead of @c newVerticalAlignment).
         *
         * @param newVerticalAlignment The new vertical alignment for the control.
         *
         * @since BlackBerry 10.0.0
         */           
        void verticalAlignmentChanged(bb::cascades::VerticalAlignment::Type newVerticalAlignment);

        /*!
         * @brief Emitted when the @c #preferredWidth of the control changes.
         *
         * @param preferredWidth The new preferred width; will always be positive.
         *
         * @since BlackBerry 10.0.0
         */
        void preferredWidthChanged(float preferredWidth);

        /*!
         * @brief Emitted when the @c #preferredWidthSet of the control changes.
         *
         * @param isSet information whether the preferred width is now set.
         *
         * @since BlackBerry 10.0.0
         */
        void preferredWidthSetChanged(bool isSet);

        /*!
         * @brief Emitted when the @c #preferredHeight of the control changes.
         *
         * @param preferredHeight The new preferred height; will always be positive.
         *
         * @since BlackBerry 10.0.0
         */
        void preferredHeightChanged(float preferredHeight);

        /*!
         * @brief Emitted when the @c #preferredHeightSet of the control changes.
         *
         * @param isSet information whether the preferred height is now set.
         *
         * @since BlackBerry 10.0.0
         */
        void preferredHeightSetChanged(bool isSet);
      
        /*!
         * @brief Emitted when the @c #leftPadding property changes.
         *
         * @param leftPadding The new left padding.
         *
         * @since BlackBerry 10.0.0
         */      
        void leftPaddingChanged(float leftPadding);
      
        /*!
         * @brief Emitted when the @c #rightPadding property changes.
         *
         * @param rightPadding The new right padding.
         *
         * @since BlackBerry 10.0.0
         */            
        void rightPaddingChanged(float rightPadding);
      
        /*!
         * @brief Emitted when the @c #topPadding property changes.
         *
         * @param topPadding The new top padding.
         *
         * @since BlackBerry 10.0.0
         */                  
        void topPaddingChanged(float topPadding);
      
        /*!
         * @brief Emitted when the @c #bottomPadding property changes.
         *
         * @param bottomPadding The new bottom padding.
         *
         * @since BlackBerry 10.0.0
         */                        
        void bottomPaddingChanged(float bottomPadding);

        /*!
         * @brief Emitted when the @c #enabled property on the control changes.
         *
         * @param enabled If @c true the control is enabled, if @c false the control is disabled.
         *
         * @since BlackBerry 10.0.0
         */
        void enabledChanged(bool enabled);

        /*!
         * @brief Emitted when the @c #focused property on the control changes.
         *
         * @param focused If @c true the control is focused, if @c false the control is not focused.
         *
         * @since BlackBerry 10.0.0
         */
        void focusedChanged(bool focused);

         /*!
         * @brief Emitted when the @c #focusPolicy of the control changes.
         *
         * @param newFocusPolicy The new focusPolicy state of the control.
          *
          * @since BlackBerry 10.0.0
         */
        void focusPolicyChanged(bb::cascades::FocusPolicy::Type newFocusPolicy);

        /*!
         * @brief Emitted when the @c #focusAutoShow of the control changes.
         *
         * @param newFocusAutoShow The new focusAutoShow state of the control.
         *
         * @since BlackBerry 10.0.0
         */
        void focusAutoShowChanged(bb::cascades::FocusAutoShow::Type newFocusAutoShow);

        /*!
         * @brief Emitted when the @c #locallyFocused of the control changes.
         *
         * @param newLocallyFocused The new locallyFocused state of the control.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void locallyFocusedChanged(bool newLocallyFocused);

        /*!
         * @brief Emitted when the @c #layoutProperties of the control changes.
         *
         * @param layoutProperties The new layout properties for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void layoutPropertiesChanged(bb::cascades::LayoutProperties *layoutProperties);

        /*!
         * @brief Emitted when the @c #leftMargin of the control changes.
         *
         * @param leftMargin The new left margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void leftMarginChanged(float leftMargin);

        /*!
         * @brief Emitted when the @c #leftMarginSet of the control changes.
         *
         * @param isSet information whether the preferred Width is now set.
         *
         * @since BlackBerry 10.0.0
         */
        void leftMarginSetChanged(bool isSet);

        /*!
         * @brief Emitted when the @c #topMargin of the control changes.
         *
         * @param topMargin The new top margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void topMarginChanged(float topMargin);

        /*!
         * @brief Emitted when the @c #topMarginSet of the control changes.
         *
         * @param isSet information whether the preferred Width is now set.
         *
         * @since BlackBerry 10.0.0
         */
        void topMarginSetChanged(bool isSet);

        /*!
         * @brief Emitted when the @c #bottomMargin of the control changes.
         *
         * @param bottomMargin The new bottom margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void bottomMarginChanged(float bottomMargin);

        /*!
         * @brief Emitted when the @c #bottomMarginSet of the control changes.
         *
         * @param isSet information whether the preferred Width is now set.
         *
         * @since BlackBerry 10.0.0
         */
        void bottomMarginSetChanged(bool isSet);

        /*!
         * @brief Emitted when the @c #rightMargin of the control changes.
         *
         * @param rightMargin The new right margin for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void rightMarginChanged(float rightMargin);

        /*!
         * @brief Emitted when the @c #rightMarginSet of the control changes.
         *
         * @param isSet information whether the preferred Width is now set.
         *
         * @since BlackBerry 10.0.0
         */
        void rightMarginSetChanged(bool isSet);

        /*!
         * @brief Emitted when the @c #minWidth of the control changes.
         *
         * @param minWidth The new minimum width for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void minWidthChanged(float minWidth);

        /*!
         * @brief Emitted when the @c #maxWidth of the control changes.
         *
         * @param maxWidth The new maximum width for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void maxWidthChanged(float maxWidth);

        /*!
         * @brief Emitted when the @c #minHeight of the control changes.
         *
         * @param minHeight The new minimum height for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void minHeightChanged(float minHeight);

        /*!
         * @brief Emitted when the @c #maxHeight of the control changes.
         *
         * @param maxHeight The new maximum height for the control.
         *
         * @since BlackBerry 10.0.0
         */
        void maxHeightChanged(float maxHeight);
        
       /*!
        * @brief Emitted when an @c ActionSet has been added to the Control.
        *
        * @param actionSet The @c %ActionSet that has been added.
        *
        * @since BlackBerry 10.0.0
        */
        void actionSetAdded(bb::cascades::ActionSet *actionSet);

       /*!
        * @brief Emitted when an @c ActionSet has been removed from the @c control.
        *        
        * @param actionSet The @c %ActionSet that has been removed. @c 0 if emitted by @c removeAllActionSets().
        *
        * @since BlackBerry 10.0.0
        */
        void actionSetRemoved(bb::cascades::ActionSet *actionSet);

       /*!
        * @brief Emitted when a @c %ContextMenuHandler has been set for the Control.
        *        
        * @param contextMenuHandler The @c %ContextMenuHandler that has been set, or @c 0 if it was reset.
        *
        * @since BlackBerry 10.0.0
        */
        void contextMenuHandlerChanged(bb::cascades::ContextMenuHandler* contextMenuHandler);

       /*!
        * @brief Emitted when the @c #focusRetentionPolicyFlags property on the control changes.
        *
        * @param policy The new focusRetentionPolicy.
        *
        * @since BlackBerry 10.0.0
        */
        void focusRetentionPolicyFlagsChanged(bb::cascades::FocusRetentionPolicy::Types policy);

       /*!
        * @brief Emitted when the @c #implicitLayoutAnimationsEnabled property on the control changes.
        *
        * @param implicitLayoutAnimationsEnabled The new value.
        *
        * @since BlackBerry 10.0.0
        */
        void implicitLayoutAnimationsEnabledChanged(bool implicitLayoutAnimationsEnabled);

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
        * @brief Emitted when the @c #accessibilityMode property on the control changes.
        *
        * @note Due to a work around for a Qt Core issue with accessing enums from QML,
        * the argument of this signal doesn't follow naming convention for signals in
        * which the signal arguments are typically named to match the associated property's name.
        * Use the object's @c accessibilityMode property to access the current property value instead of 
        * the signal argument to avoid runtime errors.
        *
        * @param newAccessibilityMode The new value.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        void accessibilityModeChanged(bb::cascades::A11yMode::Type newAccessibilityMode);

    protected:
        /*! @cond PRIVATE */
        Control(ControlPrivate &_d_ptr, Control* parent = 0);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::ActionSet> contextActions();
        Q_DECLARE_PRIVATE(Control)
        Q_DISABLE_COPY(Control)
        /*! @endcond */

    public:
        /*! @cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::AbstractShortcut> shortcuts();
        QDeclarativeListProperty<bb::cascades::KeyListener> keyListeners();
        typedef Control ThisClass;  // The class in which scope we're currently inside
        typedef VisualNode BaseClass; // References the class which ThisClass derives from
        /*!
         * Workaround for the Qt bug that prevents our enums from being
         * function arguments in QML.
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_INVOKABLE void setBuiltInShortcutEnabled(int type, bool enabled);
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a control.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }
        public:


            /*!
             * @copydoc bb::cascades::Control::setHorizontalAlignment(HorizontalAlignment::Type )
             */
            BuilderType& horizontal(HorizontalAlignment::Type horizontalAlignment) {
                this->instance().setHorizontalAlignment(horizontalAlignment);
                return this->builder();
            }
            /*!
             * @copydoc bb::cascades::Control::setVerticalAlignment(VerticalAlignment::Type)
             */
            BuilderType& vertical(VerticalAlignment::Type verticalAlignment) {
                this->instance().setVerticalAlignment(verticalAlignment);
                return this->builder();
            }
            
            /*!
             * @brief Sets the @c bb::cascades::Control#focusPolicy of the control.
             *
             * @param _focusPolicy The focusPolicy state of the @c Control as a @c FocusPolicy.
             * @see FocusPolicy
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& focusPolicy(FocusPolicy::Type _focusPolicy) {
                this->instance().setFocusPolicy(_focusPolicy);
                return this->builder();
            }

            /*!
             * @brief Sets the preferred width of the control.
             * 
             * @param _preferredWidth The preferred width of the control as a positive, non-zero number.
             *
             * @see @c Control::preferredWidth
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& preferredWidth(float _preferredWidth) {
                this->instance().setPreferredWidth(_preferredWidth);
                return this->builder();
            }

            /*!
             * @brief  Sets the preferred height of the control.
             *
             * By setting the preferred width of a control, the
             * @c Control::isPreferredHeightSet flag is automatically set to @c true.
             *
             * @param _preferredHeight The preferred height of the control as a positive, non-zero number.
             *
             * @see Control::preferredHeight   
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& preferredHeight(float _preferredHeight) {
                this->instance().setPreferredHeight(_preferredHeight);
                return this->builder();
            }

            /*!
             * @brief Sets the width and height of the control.
             *
             * A convenience function for setting both the preferred width and height. 
             * It is equivalent to calling @c preferredWidth() and @c preferredHeight().
             *
             * @param _preferredWidth The preferred width of the control as a positive, non-zero number.
             * @param _preferredHeight The preferred height of the control as a positive, non-zero number.
             *
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& preferredSize(float _preferredWidth, float _preferredHeight) {
                this->instance().setPreferredSize(_preferredWidth, _preferredHeight);
                return this->builder();
            }
          
            /*!
             * @brief Sets the margin property offsets to a common value on all side of the control.
             *
             * @see Control::margin
             *
             * @since BlackBerry 10.3.0
             */
            BuilderType& marginOffset( float fCommonMarginOffset ) {
                bb::cascades::Spacings* margin = this->instance().margin();
                margin->setTopOffset(fCommonMarginOffset);
                margin->setBottomOffset(fCommonMarginOffset);
                margin->setLeftOffset(fCommonMarginOffset);
                margin->setRightOffset(fCommonMarginOffset);
           	    return this->builder();
            }
          
            /*!
             * @brief Sets the margin property offsets of the control.
             *
             * @see Control::margin
             *
             * @since BlackBerry 10.3.0
             */
            BuilderType& marginOffset( float _topMarginOffset, float _rightMarginOffset, float _bottomMarginOffset, float _leftMarginOffset) {
                bb::cascades::Spacings* margin = this->instance().margin();
                margin->setTopOffset(_topMarginOffset);
                margin->setBottomOffset(_bottomMarginOffset);
                margin->setLeftOffset(_leftMarginOffset);
                margin->setRightOffset(_rightMarginOffset);
                return this->builder();
            }
          
            /*!
             * @brief Sets the left margin for the control.
             *            
             * @param _leftMargin The left margin for the control.
             *
             * @see Control::leftMargin   
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType &leftMargin(float _leftMargin) {
                this->instance().setLeftMargin(_leftMargin);
                return this->builder();
            }

            /*!
             * @brief Sets the right margin for the control.
             *
             * @param _rightMargin The right margin for the control.
             *
             * @see @c Control::rightMargin     
             *
             * @since BlackBerry 10.0.0             
             */
            BuilderType &rightMargin(float _rightMargin) {
                this->instance().setRightMargin(_rightMargin);
                return this->builder();
            }

            /*!
             * @brief Sets the top margin for the control.
             *
             * @param _topMargin The right margin for the control.
             *
             * @see @c Control::topMargin   
             *
             * @since BlackBerry 10.0.0             
             */
            BuilderType &topMargin(float _topMargin) {
                this->instance().setTopMargin(_topMargin);
                return this->builder();
            }

            /*!
             * @brief Sets the bottom margin for the control.
             *
             * @param _bottomMargin The bottom margin for the control.
             *
             * @see @c Control::bottomMargin
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType &bottomMargin(float _bottomMargin) {
                this->instance().setBottomMargin(_bottomMargin);
                return this->builder();
            }

            /*!
             * @brief Sets all the control's margins at once.
             *
             * @param _topMargin The right margin for the control.
             * @param _rightMargin The right margin for the control.             
             * @param _bottomMargin The bottom margin for the control.
             * @param _leftMargin The left margin for the control.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType &margins(float _topMargin, float _rightMargin, float _bottomMargin, float _leftMargin) {
                this->instance().setTopMargin(_topMargin);
                this->instance().setRightMargin(_rightMargin);
                this->instance().setBottomMargin(_bottomMargin);
                this->instance().setLeftMargin(_leftMargin);
                return this->builder();
            }
          
            /*!
             * @copydoc bb::cascades::Control::setTopPadding(float)
             */                    
            BuilderType& top(float topPadding) {
              this->instance().setTopPadding(topPadding);
              return this->builder();
            }
          
            /*!
             * @copydoc bb::cascades::Control::setBottomPadding(float)
             */                    
            BuilderType& bottom(float bottomPadding) {
              this->instance().setBottomPadding(bottomPadding);
              return this->builder();
            }
          
            /*!
             * @copydoc bb::cascades::Control::setLeftPadding(float)
             */                    
            BuilderType& left(float leftPadding) {
              this->instance().setLeftPadding(leftPadding);
              return this->builder();
            }
          
            /*!
             * @copydoc bb::cascades::Control::setRightPadding(float)
             */                    
            BuilderType& right(float rightPadding) {
              this->instance().setRightPadding(rightPadding);
              return this->builder();
            }

            /*!
             * @brief Sets the enabled state of the control.
             *
             * @param _enabled If @c true the control is enabled and if @c false the control is disabled.
             *
             * @see @c Control::enabled       
             *
             * @since BlackBerry 10.0.0             
             */
            BuilderType& enabled(bool _enabled) {
                this->instance().setEnabled(_enabled);
                return this->builder();
            }

            /*!
             * @brief Sets the layout properties for the control.
             *
             * The control takes ownership of the @c LayoutProperties object if no other control owns it already. 
             * If the @c %LayoutProperties object already has an owner, the properties are applied to the control,
             * but ownership of the @c %LayoutProperties object remains unchanged. If the control already owns a 
             * @c %LayoutProperties object, the existing settings are replaced by the specified @c %LayoutProperties object
             * and the container retains ownership of both.
             *
             * @param layoutProperties The new layout properties for the control.
             *
             * @see Control::layoutProperties
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& layoutProperties(LayoutProperties* layoutProperties) {
                this->instance().setLayoutProperties(layoutProperties);
                return this->builder();
            }           
            
           /*!
            * @brief Adds an @c ActionSet to the Control.
            *
            * @see Control::contextActions
            *
            * @param actionSet The ActionSet to add to the Control.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& actionSet(ActionSet* actionSet) {
                this->instance().addActionSet(actionSet);
                return this->builder();
            }

           /*!
            * @brief Sets the @c ContextMenuHandler for the @c control.
            *
            * @see Control::contextMenuHandler
            *
            * @param contextMenuHandler The @c %ContextMenuHandler to set for the @c %Control.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& contextMenuHandler(ContextMenuHandler* contextMenuHandler) {
                this->instance().setContextMenuHandler(contextMenuHandler);
                return this->builder();
            }

            /*!
             * @brief Enable or disable implicit layout animations for the control.
             *
             * @see @c Control::implicitLayoutAnimationsEnabled
             *
             * @param _enabled If true enable implicit layout animations for the Control, if false disable
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& implicitLayoutAnimations(bool _enabled) {
                this->instance().setImplicitLayoutAnimationsEnabled(_enabled);
                return this->builder();
            }

            /*!
            * @brief Adds a shortcut to the @c %Control. 
            *
            * @c %Control will always take ownership as shortcuts should never be shared.
            * If the shortcut already belongs to the @c %Control or the @c shortcut is @c 0, nothing will happen.        
            * The order in which shortcuts are added will determine which shortcut will be triggered in case of an overlap.
            *      
            *
            * @param shortcut The @c AbstractShortcut to add to the @c %Control.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& addShortcut(AbstractShortcut* shortcut) {
                this->instance().addShortcut(shortcut);
                return this->builder();
            }

            /*!
            * @brief Adds a key listener to the @c %Control. 
            *
            * @c %Control will always take ownership as key listener should never be shared.
            * If the key listener already belongs to the @c %Control or the @c key listener is @c 0, nothing will happen.               
            *      
            *
            * @param keyListener The @c KeyListener to add to the @c %Control.
            *
            * @since BlackBerry 10.0.0
            */            
            BuilderType& addKeyListener(KeyListener* keyListener) {
                this->instance().addKeyListener(keyListener);
                return this->builder();
            }

           /*!
            * @brief Sets primaryKeyTarget property of the inputRoute.
            *
            * @param primaryKeyTarget @c true if the control should be treated as a primary key target.
            *
            * @see Control::inputRoute
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& primaryKeyTarget(bool primaryKeyTarget) {
                this->instance().inputRoute()->setPrimaryKeyTarget(primaryKeyTarget);
                return this->builder();
            }

            /*!
            * @brief Sets keysIgnoreFocusInSubtree property of the inputRoute.
            *
            * @param keysIgnoreFocusInSubtree @c true if key events should ignore focused controls in this subtree
            *
            * @see Control::inputRoute
            *
            * @since BlackBerry 10.3.1
            */
            BuilderType& keysIgnoreFocusInSubtree(bool keysIgnoreFocusInSubtree) {
                this->instance().inputRoute()->setKeysIgnoreFocusInSubtree(keysIgnoreFocusInSubtree);
                return this->builder();
            }

           /*!
            * @brief Sets the @c accessibilityMode property of the control.
            *
            * @param mode The @c A11yMode to set on the control.
            *
            * @see Control::accessibilityMode
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityMode(bb::cascades::A11yMode::Type mode) {
                this->instance().setAccessibilityMode(mode);
                return this->builder();
            }

           /*!
            * @brief Sets the accessibility name property of the control.
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
            * @brief Sets the accessibility description property of the control.
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
            * @param labelledBy The object to add as an accessibility label for the @c Control.
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
            * @param enabled If the Control's built-in shortcuts should be enabled and false otherwise.
            *
            * @see Control::builtInShortcutsEnabled
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


QML_DECLARE_TYPE(bb::cascades::Control)

#endif /* cascades_control_h */

