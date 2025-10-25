/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_titlebar_h
#define cascades_titlebar_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/resources/titlebarkind.h>
#include <bb/cascades/resources/titlebarscrollbehavior.h>
#include <bb/cascades/resources/tribool.h>
#include <bb/cascades/resources/titlebarappearance.h>
#include <bb/cascades/controls/chromevisibility.h>
#include <bb/cascades/controls/option.h>

namespace bb {
namespace cascades {
    class TitleBarPrivate;
    class ActionItem;
    class Option;
    class AbstractTitleBarKindProperties;

    /*!
     *
     * @brief Defines a title bar on a page.
     *
     * The title bar consists of a title with optional actions for accepting or declining an action,
     * or an optional set of selectable options, depending on the type of title bar.
     * You can define the type of title bar to display using the
     * @c kind property. Possible values are @c Default (allows the action buttons to be displayed),
     * @c Segmented (allows a @c SegmentedControl to be displayed), and
     * @c FreeForm (allows controls to be placed freely on the title bar).
     * The actions will be displayed on the title bar, which is placed at the top of the screen.
     *
     * Here's an example of a default title bar:
     *
     * @image html default_titlebar.png
     *
     * QML:
     * @code
     * Page {
     *     titleBar: TitleBar {
     *         title : "This is a page title"
     *     }
     * }
     * @endcode
     *
     * C++:
     * @code
     * TitleBar* tb = new TitleBar();
     * tb->setTitle("This is a page title");
     * Page* page = Page::create().titleBar(tb);
     * @endcode
     *
     * Here's a title bar containing options:
     *
     * @image html segmented_titlebar.png
     *
     * @code
     * Page {
     *     titleBar: TitleBar {
     *         kind: TitleBarKind.Segmented
     *         options: [
     *             Option {
     *                 text: "Todo"
     *                 value: "todo"
     *             },
     *             Option {
     *                 text: "Finished"
     *                 value: "finished"
     *             },
     *             Option {
     *                 text: "Chickened out"
     *                 value: "chickened"
     *             }
     *         ]
     *     }
     * }
     * @endcode
     *
     * And lastly, this is a free-form title bar containing expandable content:
     *
     * @image html freeform_titlebar.png
     *
     * @code
     * Page {
     *     titleBar: TitleBar {
     *         kind: TitleBarKind.FreeForm
     *         kindProperties: FreeFormTitleBarKindProperties {
     *             Container {
     *                 layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
     *                 leftPadding: 10
     *                 rightPadding: 10
     *                 Label {
     *                     text: "Show expandable content"
     *                     textStyle {
     *                         color: Color.White
     *                     }
     *                     verticalAlignment: VerticalAlignment.Center
     *                     layoutProperties: StackLayoutProperties { spaceQuota: 1 }
     *                 }
     *                 CheckBox {
     *                     id: toggleExpanded
     *                     verticalAlignment: VerticalAlignment.Center
     *                 }
     *             }
     *             expandableArea {
     *                 content: RadioGroup {
     *                     Option { id: option1; text: "option 1"; selected: true }
     *                     Option { id: option2; text: "option 2" }
     *                     Option { id: option3; text: "option 3" }
     *                 }
     *                 indicatorVisibility: TitleBarExpandableAreaIndicatorVisibility.Hidden
     *                 expanded: toggleExpanded.checked
     *                 onExpandedChanged: {
     *                     toggleExpanded.checked = expanded
     *                 }
     *             }
     *         }
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     * <qml>
     * <class register="yes"/>
     * </qml>
     * @endxmlonly
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT TitleBar : public UIObject {
        Q_OBJECT

        /*!
         * @brief The kind of @c TitleBar to create.
         *
         * This property can only be set once during the construction of the @c %TitleBar.
         * Possible values for this property are @c Default, @c Segmented, and @c FreeForm.
         *
         * The @c Default state displays the title bar with left-aligned title text that
         * can be set using the @c title property. It is possible to add two action buttons
         * to the @c Default title bar, one on either side of the title. If one or more action
         * buttons are shown, the title text will be center-aligned.
         *
         * If @c kind is set to @c Segmented, the @c title, @c acceptAction, and @c dismissAction properties
         * are not used, and the title text will not be displayed. The title bar will instead display up to four options.
         * These options can be set using the @c options property.
         *
         * @xmlonly
         * <qml>
         * <property writable="init-only"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::TitleBarKind::Type kind READ kind WRITE setKind FINAL)

        /*!
         * @brief The visibility mode of the @c TitleBar.
         *
         * The default visibility state of a title bar is @c ChromeVisibility::Default.
         *
         * @note The title bar can't be immersive (ChromeVisibility::Overlay) and have
         * a non sticky scroll behavior (TitleBarScrollBehavior::NonSticky) at the same time.
         * ScrollBehavior will have precedence over the immersive visibility.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ChromeVisibility::Type visibility READ visibility WRITE setVisibility RESET resetVisibility NOTIFY visibilityChanged FINAL)

        /*!
         * @brief The title text to display on the @c TitleBar.
         *
         * The default value is @c QString::Null, indicating that no title is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

        /*!
         * @brief Specifies whether the @c TitleBar should use the colors associated with
         * the current visual brand.
         *
         * Currently, the only available brand color is blue (the default). In the future,
         * there may be the possibility to choose from different branding options.
         *
         * When @c branded is set to @c True, the title bar assumes the color associated with the current brand.
         * When set to @c False, the title bar keeps the default color
         * associated with the application's @c VisualStyle (either @c Light or @c Dark).
         *
         * If the @c VisualStyle is @c Light, the branded title bar is used by default. If the @c VisualStyle is @c Dark,
         * the branded control is still available, but not used by default.
         *
         * The default value is @c TriBool::Type Undefined.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0 Do not use. This property has no impact on the @c TitleBar.
         */
        Q_PROPERTY(bb::cascades::TriBool::Type branded READ branded WRITE setBranded RESET resetBranded NOTIFY brandedChanged FINAL)

        /*!
         * @brief Specifies what appearance the @c TitleBar should have.
         *
         * The default value is @c TitleBarAppearance::Type Default.
         *
         * @see TitleBarAppearance
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0 Do not use. This property has no impact on the @c TitleBar.
         */
        Q_PROPERTY(bb::cascades::TitleBarAppearance::Type appearance READ appearance WRITE setAppearance RESET resetAppearance NOTIFY appearanceChanged FINAL)

        /*!
         * @brief An action that will be displayed beside the title in the @c TitleBar.
         *
         * This action should typically be used to accept or confirm some sort of action.
         *
         * @see ActionItem
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ActionItem* acceptAction READ acceptAction WRITE setAcceptAction
                   RESET resetAcceptAction NOTIFY acceptActionChanged FINAL);

        /*!
         * @brief An action that will be displayed beside the title in the @c TitleBar.
         *
         * This action should typically be used to cancel an action or process, or to
         * dismiss or close the current page.
         *
         * @see AbstractActionItem
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ActionItem* dismissAction READ dismissAction WRITE setDismissAction
                   RESET resetDismissAction NOTIFY dismissActionChanged FINAL);

        /*!
         * @brief The index of the currently selected option.
         *
         * The @c selectedIndexChanged() signal is emitted when the index of the selected option is changed.
         *
         * The default @c selectedIndex is @c SelectedIndexNone, meaning that no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged RESET resetSelectedIndex FINAL)

        /*!
         * @brief The currently selected @c Option.
         *
         * The @c selectedOptionChanged() signal is emitted when the selected option is changed.
         *
         * The default @c selectedOption is @c 0, meaning that no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Option* selectedOption READ selectedOption WRITE setSelectedOption NOTIFY selectedOptionChanged RESET resetSelectedOption FINAL)

        /*!
         * @brief Indicates whether any option in the @c TitleBar is currently selected.
         *
         * This property is set to @c true if any option is selected, and is set to @c false otherwise.
         *
         * This property can be used to determine if any option is currently selected, in addition to
         * examining the @c selectedIndex property (typically from QML). Specifically, if the
         * @c hasSelectedOption property is @c false, the @c selectedIndex property will be set to
         * @c SelectedIndexNone, which is not accessible from QML.
         *
         * @code
         * TitleBar {
         *     onSelectedOptionSetChanged: {
         *         if (selectedOptionSet) {
         *             console.log("Selected option with index: " + selectedIndex);
         *         } else {
         *             console.log("No selected options");
         *         }
         *     }
         * }
         * @endcode
         *
         * When the value of this property changes, the @c selectedOptionSetChange() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool selectedOptionSet READ isSelectedOptionSet NOTIFY selectedOptionSetChanged FINAL)

        /*!
         * @brief The value of the currently selected @c Option.
         *
         * The @c selectedValueChanged() signal is emitted when the selected option's value is changed.
         *
         * The default @c selectedValue is an invalid @c QVariant if the selected option has no value set
         * or no option is selected.
         *
         * @see QVariant, QVariant::Invalid
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant selectedValue READ selectedValue NOTIFY selectedValueChanged FINAL)

        /*!
         * @brief The list of @c Option controls in the @c TitleBar.
         *
         * The list is empty initially if no options have been added.
         *
         * @xmlonly
         * <qml>
         * <property name="options" listType="bb::cascades::Option"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::Option> options READ options FINAL)

        /*!
         * @brief The properties associated with a certain title bar kind.
         *
         * Depending on the @c kind that has been set on the @c %TitleBar, a different set of properties are valid.
         * These different sets properties are bundled in classes inheriting from @c AbstractTitleBarKindProperties.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::AbstractTitleBarKindProperties* kindProperties READ kindProperties WRITE setKindProperties RESET resetKindProperties NOTIFY kindPropertiesChanged FINAL)

        /*!
         * @brief The title bar scroll behavior for the @c %Page.
         *
         * By default, the @c scrollBehavior of a @c %Page is @c TitleBarScrollBehavior::Default.
         *
         * @note The title bar can't be immersive (ChromeVisibility::Overlay) and have
         * a non sticky scroll behavior (TitleBarScrollBehavior::NonSticky) at the same time.
         * ScrollBehavior will have precedence over the immersive visibility.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::TitleBarScrollBehavior::Type scrollBehavior READ scrollBehavior WRITE setScrollBehavior FINAL)

    public:
        /*!
         * @brief A constant indicating that there are no options selected.
         *
         * @since BlackBerry 10.0.0
         */
        static const int SelectedIndexNone;

        /*!
         * @brief Constructs a @c TitleBar of the specified kind.
         *
         * The only way to set what kind of @c %TitleBar to create is to pass the kind as a parameter
         * to this constructor. See the documentation for the @c kind property for further information.
         *
         * @param kind The kind of @c %TitleBar to create, specified using the @c TitleBarKind::Type
         * enumeration.
         *
         * @since BlackBerry 10.0.0
         */
        explicit TitleBar(TitleBarKind::Type kind = TitleBarKind::Default);

        /*!
         * @brief Constructs a @c TitleBar of the specified kind and scroll behavior.
         *
         * @param behavior The scroll behavior of @c %TitleBar to create, specified using the @c TitleBarScrollBehavior::Type
         * enumeration.
         *
         * @param kind The kind of @c %TitleBar to create, specified using the @c TitleBarKind::Type
         * enumeration.
         *
         * @since BlackBerry 10.1.0
         */
        explicit TitleBar(TitleBarScrollBehavior::Type behavior, TitleBarKind::Type kind = TitleBarKind::Default);

        /*!
         * @brief Destructs the @c TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~TitleBar();

        /*!
         * @brief Returns the kind of the @c TitleBar.
         *
         * See the documentation for the @c kind property for further information.
         *
         * @return The kind of @c %TitleBar, specified using the @c TitleBarKind::Type enumeration.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TitleBarKind::Type kind() const;


        /*!
         * @brief Returns the visibility mode of the @c TitleBar.
         *
         * @return The visibility mode of the title bar, specified using the @c ChromeVisibility::Type
         * enumeration.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ChromeVisibility::Type visibility() const;


        /*!
         * @brief Sets the visibility mode of this @c TitleBar.
         *
         * @param visibility The visibility of the @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setVisibility(bb::cascades::ChromeVisibility::Type visibility);

        /*!
         * @brief Resets the visibility of the @c TitleBar to @c ChromeVisibility::Default.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetVisibility();

        /*!
         * @brief Sets the text title of this @c TitleBar.
         *
         * @param title The text title of this @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTitle(const QString& title);

        /*!
         * @brief Resets the title of this @c TitleBar to @c QString::Null.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTitle();

        /*!
         * @brief Returns the title of this @c TitleBar.
         *
         * @return The title of this @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        QString title() const;

        /*!
         * @brief Sets the brand of this @c TitleBar.
         *
         * @param branded The brand of this @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        Q_SLOT void setBranded(bb::cascades::TriBool::Type branded);

        /*!
         * @brief Resets the brand of this @c TitleBar to @c bb::cascades::TriBool::Type Undefined.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        Q_SLOT void resetBranded();

        /*!
         * @brief Returns the brand of this @c TitleBar.
         *
         * @return The brand of this @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        bb::cascades::TriBool::Type branded() const;

        /*!
         * @brief Sets the appearance of this @c TitleBar.
         *
         * @param appearance The appearance of this @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        Q_SLOT void setAppearance(bb::cascades::TitleBarAppearance::Type appearance);

        /*!
         * @brief Resets the appearance of this @c TitleBar to @c bb::cascades::TitleBarAppearance::Type Default.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        Q_SLOT void resetAppearance();

        /*!
         * @brief Returns the appearance of this @c TitleBar.
         *
         * @return The appearance of this @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        bb::cascades::TitleBarAppearance::Type appearance() const;

        /*!
         * @brief Returns the @c TitleBarScrollBehavior object for the page.
         *
         * @return The @c TitleBarScrollBehavior for the @c Page.
         */
        bb::cascades::TitleBarScrollBehavior::Type scrollBehavior() const;

        /*!
         * @brief Returns the accept action for the @c TitleBar.
         *
         * The @c %TitleBar keeps the ownership of the accept action.
         *
         * @return The accept action, or @c 0 if no accept action has been specified.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ActionItem* acceptAction() const;

        /*!
         * @brief Sets the accept action for this @c TitleBar.
         *
         * The @c %TitleBar takes the ownership of the accept button.
         *
         * If set to @c 0, the accept action is removed from this @c %TitleBar.
         *
         * When this function completes, the @c acceptActionChanged() signal is emitted.
         *
         * @param acceptAction The action to be displayed on the side of the title.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setAcceptAction(bb::cascades::ActionItem* acceptAction);

        /*!
         * @brief Resets the accept button for this @c TitleBar.
         *
         * This function removes the accept action button from the @c %TitleBar.
         * When this function completes, the @c acceptActionChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetAcceptAction();

        /*!
         * @brief Returns the dismiss button for the @c TitleBar.
         *
         * The @c %TitleBar keeps the ownership of the dismiss action.
         *
         * @return The dismiss action, or @c 0 if no dismiss action has been specified.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ActionItem* dismissAction() const;

        /*!
         * @brief Sets the dismiss action for this @c TitleBar.
         *
         * The @c %TitleBar takes the ownership of the dismiss action.
         *
         * If set to @c 0, the dismiss button is removed from the @c %TitleBar.
         *
         * When this function completes, the @c dismissActionChanged() signal is emitted.
         *
         * @param dismissAction The action button to be displayed on the side of the title.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDismissAction(bb::cascades::ActionItem* dismissAction);

        /*!
         * @brief Resets the dismiss button for this @c TitleBar.
         *
         * This function removes the dismiss action button from the @c %TitleBar.
         * When this function completes, the @c dismissActionChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDismissAction();

        /*!
         * @brief Returns the index of the currently selected option, or @c SelectedIndexNone if no option is selected.
         *
         * @return The index of the selected option, or @c SelectedIndexNone if no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        int selectedIndex() const;

        /*!
         * @brief Selects the option at @c index.
         *
         * The @c index must be greater than or equal to 0, less than @c count() and less than four.
         * Otherwise, it is ignored.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the selected index is changed.
         *
         * @param index The index of the option to select.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSelectedIndex(int index);

        /*!
         * @brief Resets the selected index of the @c TitleBar.
         *
         * The selected index is reset to @c 0 if the @c %TitleBar has an @c Option selected
         * at a non-zero index.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the index was changed to @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSelectedIndex();

        /*!
         * @brief Returns the selected @c Option*, or @c 0 if no option is selected.
         *
         * @return The selected @c Option*, or @c 0 if no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Option* selectedOption() const;

        /*!
         * @brief Selects the specified @c Option.
         *
         * The @c Option must either belong to the @c TitleBar or be @c 0. Otherwise, it is ignored.
         * Passing @c 0 resets the selected index to @c 0.
         *
         * This function is equivalent to calling @c setSelectedIndex(indexOf(option)) assuming that the @c Option
         * belongs to this @c %TitleBar, or is @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the selected option is changed.
         *
         * @param option The option belonging to this @c %TitleBar to select, or @c 0 to deselect any selected option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSelectedOption(bb::cascades::Option* option);

        /*!
         * @brief Resets the selected option of the @c TitleBar.
         *
         * The selected index is reset to @c 0 if the @c %TitleBar has an @c Option selected
         * at a non-zero index.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the index was changed to @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSelectedOption();

        /*!
         * @brief Returns whether the @c TitleBar has a selected option.
         *
         * @return @c true if the @c %TitleBar has a selected option, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isSelectedOptionSet() const;

        /*!
         * @brief Returns the value of the currently selected option.
         *
         * If no option is selected or no value is set on the selected option, an invalid @c QVariant is returned.
         *
         * @return The value of the currently selected option or an invalid @c %QVariant.
         *
         * @since BlackBerry 10.0.0
         */
        QVariant selectedValue() const;

        /*!
         * @brief Adds an option to the @c TitleBar.
         *
         * The added option is placed last in the @c %TitleBar.
         *
         * If the option has already been added to another control, it will be removed from that control and added
         * to this @c %TitleBar, which will also assume ownership of the @c Option. Once added, the @c optionAdded()
         * signal is emitted.
         *
         * If the option is @c 0, it is ignored.
         *
         * If the @c Option is added at an @c index greater than @c 3, it is inserted as unselected.
         *
         * If the option is added as a selected option, the @c selectedIndexChanged(), @c selectedOptionChanged(),
         * and @c selectedValueChanged() signals are emitted.
         *
         * @param option The @c Option to be added.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void addOption(bb::cascades::Option* option);

        /*!
         * @brief Inserts the @c Option at the specified @c index.
         *
         * If the @c index is less than @c 0, the option is inserted at index @c 0.
         * If the @c index is equal to or greater than @c count(), the option is appended last.
         *
         * If the option is currently added to another control, it will be removed from that control and added
         * to this @c TitleBar, which will also assume ownership of the option. Once added, the @c optionAdded()
         * signal is emitted.
         *
         * If the option is @c 0, it is ignored.
         *
         * If the @c Option is added at an @c index greater than @c 3, it is inserted as unselected.
         *
         * If the option is added as a selected option, the @c selectedIndexChanged(),
         * @c selectedOptionChanged(), and @c selectedValueChanged() signals are emitted.
         *
         * @param index The @c index to insert the @c Option at.
         * @param option The @c Option to be inserted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void insertOption(int index, bb::cascades::Option* option);

        /*!
         * @brief Removes the @c Option from the @c TitleBar.
         *
         * This function removes the option from the @c %TitleBar, if the option belonged to the @c %TitleBar.
         *
         * Once the @c Option is removed, the @c %TitleBar no longer references it, but it is still
         * owned by the @c Option. It is up to the application to either delete the removed
         * @c Option, transfer its ownership (by setting its parent) to another object or leave
         * it as a child of the @c %TitleBar (in which case it will be deleted with the @c %TitleBar).
         *
         * If an @c Option before the selected option is removed, @c selectedIndexChanged() signal is emitted.
         *
         * If the selected option is removed, the @c selectedIndex is set to @c 0 or @c SelectedIndexNone and the
         * @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged() signals are emitted.
         *
         * The @c optionRemoved() signal is emitted if the option is removed.
         *
         * @param option The option to be removed.
         * @return @c true if the @c Option was removed, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bool removeOption(bb::cascades::Option* option);

        /*!
         * @brief Removes all options from the @c TitleBar and deletes them.
         *
         * The @c optionRemoved() signal is emitted with the @c option parameter as @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted if an option was selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void removeAllOptions();

        /*!
         * @brief Returns an option at a specific index if the index is valid, @c 0 otherwise.
         *
         * The ownership of the returned option is not changed; this @c TitleBar will still own the
         * option.
         *
         * @param index The index that specifies the option to return.
         *
         * @return The requested option if @c index is valid, @c 0 otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bb::cascades::Option* optionAt(int index) const;

        /*!
         * @brief Returns the index of a specific option.
         *
         * If the option is @c 0 or the @c Option doesn't belong to the @c TitleBar, @c SelectedIndexNone
         * is returned.
         *
         * @param option The option to get the index of.
         *
         * @return The index of the option, or @c SelectedIndexNone.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE int indexOfOption(bb::cascades::Option* option) const;

        /*!
         * @brief Returns the number of options in the @c TitleBar.
         *
         * @return The number of options in the @c %TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE int optionCount() const;

        /*!
         * @brief Returns the kind properties of the @c TitleBar.
         *
         * @return The kind properties of the @c %TitleBar.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::AbstractTitleBarKindProperties* kindProperties() const;

        /*!
         * @brief Sets the kind properties of the @c TitleBar.
         * Ownership will always be transferred to the @c %TitleBar.
         * If @c %TitleBar already has kind properties, the old properties will still be owned by @c %TitleBar
         * and destroyed when @c %TitleBar is destroyed.
         *
         * Note that the @c kind and @c kindProperties must match.
         *
         * @param kindProperties The kind properties of the @c %TitleBar.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setKindProperties(bb::cascades::AbstractTitleBarKindProperties* kindProperties);

        /*!
         * @brief Resets the kind properties of the @c TitleBar to @c 0.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetKindProperties();

    Q_SIGNALS:

        /*!
         * @brief Emitted when the visibility of the @c TitleBar changes.
         *
         * @param newVisibility The new visibility.
         *
         * @since BlackBerry 10.0.0
         */
        void visibilityChanged(bb::cascades::ChromeVisibility::Type newVisibility);

        /*!
         * @brief Emitted when the title of this @c TitleBar changes.
         *
         * @param title The new title.
         *
         * @since BlackBerry 10.0.0
         */
        void titleChanged(const QString &title);

        /*!
         * @brief Emitted when the brand of this @c TitleBar changes.
         *
         * @param newBrand The new brand.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        void brandedChanged(bb::cascades::TriBool::Type newBrand);

        /*!
         * @brief Emitted when the appearance of this @c TitleBar changes.
         *
         * @param newAppearance The new appearance.
         *
         * @since BlackBerry 10.0.0
         *
         * @deprecated BlackBerry 10.3.0
         */
        void appearanceChanged(bb::cascades::TitleBarAppearance::Type newAppearance);

        /*!
         * @brief Emitted when the accept button has changed.
         *
         * @param acceptAction The new accept button.
         *
         * @since BlackBerry 10.0.0
         */
        void acceptActionChanged(bb::cascades::ActionItem* acceptAction);

        /*!
         * @brief Emitted when the dismiss button has changed.
         *
         * @param dismissAction The new accept button.
         *
         * @since BlackBerry 10.0.0
         */
        void dismissActionChanged(bb::cascades::ActionItem* dismissAction);

        /*!
         * @brief Emitted when the selected option has changed.
         *
         * @param selectedIndex The index of the newly selected option, or @c SelectedIndexNone if no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedIndexChanged(int selectedIndex);

        /*!
         * @brief Emitted when the selected option has changed.
         *
         * @param selectedOption The newly selected option, or @c 0 if no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedOptionChanged(bb::cascades::Option* selectedOption);

        /*!
         * @brief Emitted when the @c selectedOptionSet property changes.
         *
         * @param selectedOptionSet If @c true the @c TitleBar currently has a selected option, if @c false the
         * @c %TitleBar does not currently have a selected option.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedOptionSetChanged(bool selectedOptionSet);

        /*!
         * @brief Emitted when the value of the selected option has changed.
         *
         * @param selectedValue The value of the newly selected option, or an invalid @c QVariant if none is selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedValueChanged(const QVariant& selectedValue);

        /*!
         * @brief Emitted when an option has been added to the @c TitleBar.
         *
         * @param option The option that has been added.
         *
         * @since BlackBerry 10.0.0
         */
        void optionAdded(bb::cascades::Option *option);

        /*!
         * @brief Emitted when an option has been removed from the @c TitleBar.
         *
         * @param option The option that has been removed, @c 0 if emitted by @c removeAll().
         *
         * @since BlackBerry 10.0.0
         */
        void optionRemoved(bb::cascades::Option *option);

        /*!
         * @brief Emitted when the kind properties of this @c TitleBar changes.
         *
         * @param kindProperties The new kind related properties.
         *
         * @since BlackBerry 10.1.0
         */
        void kindPropertiesChanged(bb::cascades::AbstractTitleBarKindProperties* kindProperties);

        /*! @cond PRIVATE */
    protected:
        explicit TitleBar(TitleBarPrivate &_d_ptr);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        void setKind(bb::cascades::TitleBarKind::Type kind);
        QDeclarativeListProperty<bb::cascades::Option> options();
        void setScrollBehavior(bb::cascades::TitleBarScrollBehavior::Type behavior);

        /*! @endcond */

        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TitleBar)
        Q_DISABLE_COPY(TitleBar)

        typedef TitleBar ThisClass;
        typedef UIObject BaseClass;
        /*! @endcond */

    public:
        /*!
         * @brief A builder template for constructing a @c TitleBar object.
         *
         * To retrieve the builder, call @c TitleBar::create().
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
             * @brief Sets the visibility of the @c TitleBar.
             *
             * @param visibility The visibility mode of the @c %TitleBar.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& visibility(ChromeVisibility::Type visibility) {
                this->instance().setVisibility(visibility);
                return this->builder();
            }

            /*!
             * @brief Sets the brand of the @c TitleBar.
             *
             * @param branded The brand of the @c %TitleBar.
             *
             * @since BlackBerry 10.0.0
             *
             * @deprecated BlackBerry 10.3.0
             */
            BuilderType& branded(bb::cascades::TriBool::Type branded) {
                this->instance().setBranded(branded);
                return this->builder();
            }

            /*!
             * @brief Sets the appearance of the @c TitleBar.
             *
             * @param appearance The appearance of the @c %TitleBar.
             *
             * @since BlackBerry 10.0.0
             *
             * @deprecated BlackBerry 10.3.0
             */
            BuilderType& appearance(bb::cascades::TitleBarAppearance::Type appearance) {
                this->instance().setAppearance(appearance);
                return this->builder();
            }

            /*!
             * @brief Sets the title for this @c TitleBar
             *
             * @param title The title of this @c %TitleBar.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& title(const QString &title) {
                this->instance().setTitle(title);
                return this->builder();
            }

            /*!
             * @brief Sets the accept action of the @c TitleBar.
             *
             * Using this convenience function in the builder pattern is the equivalent of the
             * following:
             * @code
             * myTitleBar->setAcceptAction(acceptAction);
             * @endcode
             *
             * @param acceptAction The action to set as the accept action.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& acceptAction(ActionItem* acceptAction)
            {
                this->instance().setAcceptAction(acceptAction);
                return this->builder();
            }

            /*!
             * @brief Sets the dismiss action of the @c TitleBar.
             *
             * Using this convenience function in the builder pattern is the equivalent of the
             * following:
             * @code
             * myTitleBar->setDismissAction(dismissAction);
             * @endcode
             *
             * @param dismissAction The action to set as the dismiss action.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& dismissAction(ActionItem* dismissAction)
            {
                this->instance().setDismissAction(dismissAction);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::TitleBar::addOption(bb::cascades::Option*)
             */
            BuilderType& addOption(Option* option)
            {
                this->instance().addOption(option);
                return this->builder();
            }

            /*!
             * @brief Creates an option with the specified text and optional value, and adds it to this
             * @c TitleBar.
             *
             * This is a convenience method that you can use in the following way:
             *
             * @code
             * TitleBar* mySegmentedTitleBar =
             *     TitleBar::create(TitleBarKind::Segmented)
             *         .addOption(optionText, value, selected);
             * @endcode
             *
             * This is equivalent to the following:
             *
             * @code
             * Option* newOption = Option::create()
             *                     .text(optionText)
             *                     .value(value)
             *                     .selected(selected);
             * TitleBar* mySegmentedTitleBar =
             *     TitleBar::create(TitleBarKind::Segmented)
             *         .addOption(newOption);
             * @endcode
             *
             * @param optionText The text to be used in the option.
             * @param value An optional value parameter for the option.
             * @param selected An optional selected parameter for the option.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& addOption(const QString &optionText, const QVariant &value = QVariant(), bool selected = false)
            {
                this->instance().addOption(Option::create().text(optionText).value(value).selected(selected));
                return this->builder();
            }

            /*!
             * @brief Sets the properties associated with a certain @c kind of @c TitleBar.
             *
             * @param properties The properties object to be used by the @c %TitleBar.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& kindProperties(AbstractTitleBarKindProperties* properties)
            {
                this->instance().setKindProperties(properties);
                return this->builder();
            }
        };

        /*!
         * @brief A builder for constructing a @c TitleBar object.
         *
         * To retrieve the builder, call @c TitleBar::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, TitleBar>
        {
        public:
            explicit Builder(TitleBarKind::Type kind) : TBuilder<Builder, TitleBar>(new TitleBar(kind)) {}
            explicit Builder(TitleBarScrollBehavior::Type behavior, TitleBarKind::Type kind) : TBuilder<Builder, TitleBar>(new TitleBar(behavior, kind)) {}
        };


        /*!
         * @brief Creates and returns a builder for constructing a @c TitleBar object.
         *
         * Using the builder to create a @c %TitleBar object.
         *
         * Example:
         * @code
         * TitleBar::create()
         *     .visibility(ChromeVisibility::Visible);
         *     .title("Title")
         * @endcode
         *
         * @return A builder used for constructing a @c TitleBar object.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(TitleBarKind::Type kind = TitleBarKind::Default) {
            return Builder(kind);
        }

        static Builder create(TitleBarScrollBehavior::Type behavior,
                              TitleBarKind::Type kind = TitleBarKind::Default) {
            return Builder(behavior, kind);
        }
    };
}
}


QML_DECLARE_TYPE(bb::cascades::TitleBar)

#endif    //cascades_titlebar_h
