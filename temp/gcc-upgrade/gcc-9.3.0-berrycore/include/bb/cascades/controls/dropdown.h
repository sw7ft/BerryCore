/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_dropdown_h
#define cascades_dropdown_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/option.h>

namespace bb {
    namespace cascades {

    class DropDownPrivate;
    class Container;

     /*!
     *
     * @brief A control that allows users to select an option from a drop-down.
     *
     * @image html dropdown.png Example of what the @c DropDown looks like
     *
     * The @c %DropDown control consists of a title bar and an expandable list of options.
     * The purpose is to provide a simple way to let the user select one out of a number of options.
     * The list expands and collapses when tapping on the title bar, and collapses when tapping on an option in the list.
     *
     * When the @c %DropDown is expanded, a list of options is shown. Each option displays a title with an optional
     * description and/or image.
     *
     * When the @c %DropDown is collapsed and an option is selected, the selected option's text is displayed to the right
     * in the title bar.
     * The title and description of the selected option are formatted as follows:
     * - In expanded mode, only the title is shown with the full available area at its disposal.
     * - If either the title or description is shorter than half the available area, it gets its preferred width and the other one uses the rest of the space. 
     *   For example, if the title uses 25% of the area, the description uses 75% (and might be truncated).
     * - If both the title and description are wider than 50% of the available area, they share the space equally (50% for each) with a smaller padding applied in between.
     *
     * When an option is selected, the list collapses and the @c selectedIndexChanged() signal is emitted.
     * The selected option also emits its @c Option::selectedChanged() signal with a parameter of @c true.
     * The previously selected option, if this exists, emits @c Option::selectedChanged() with a parameter of
     * @c false.
     *
     * Adding an option with @c selected set to @c true puts the @c %DropDown control in a selected state.
     * If multiple options are added with @c selected set to @c true, the last option added is selected and
     * the others deselected.
     *
     * Here's a simple example demonstrating the use of a @c %DropDown, in QML:
     *
     * @snippet tad/examples/controls/dropdown/assets/main.qml dropdown_qml1
     *
     * And here's an example in C++:
     *
     * @snippet tad/examples/controls/dropdown/src/DropDownExamples.cpp dropdown1
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
      *
      * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT DropDown : public Control
    {
    private:
        Q_OBJECT

        /*!
         * @brief The title of the @c DropDown control.
         * 
         * This text is always visible in the header, whether the @c %DropDown is expanded or collapsed.
         * 
         * The @c titleChanged() signal is emitted when the title of the @c %DropDown control changes.
         * 
         * The default @c title is @c QString::null, indicating that no title text is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

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
         * @brief Indicates whether any option in the @c DropDown is currently selected.
         *
         * This property is set to @c true if any option is selected, and is set to @c false otherwise.
         *
         * This property can be used to determine if any option is currently selected, in addition to
         * examining the @c selectedIndex property (typically from QML). Specifically, if the
         * @c hasSelectedOption property is @c false, the @c selectedIndex property will be set to
         * @c SelectedIndexNone, which is not accessible from QML.
         *
         * @snippet tad/examples/controls/dropdown/assets/main.qml dropdown_qml2
         *
         * When the value of this property changes, the @c selectedOptionSetChange() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool selectedOptionSet READ isSelectedOptionSet NOTIFY selectedOptionSetChanged FINAL)

        /*!
         * @brief The value of the currently selected @c Option.
         *
         * The @c selectedValueChanged() signal is emitted when the selected option's value is changed
         *
         * The default @c selectedValue is an invalid @c QVariant, if the selected option has no value set,
         * or no option is selected.
         *
         * @see QVariant, QVariant::Invalid
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant selectedValue READ selectedValue NOTIFY selectedValueChanged FINAL)

        /*!
         * @brief The list of @c Option controls in the @c DropDown.
         *
         * The list is empty initially if no options have been added.
         *
         * @xmlonly
         * <qml>
         * <property name="options" listType="bb::cascades::Option" defaultProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::Option> options READ options FINAL)

        Q_CLASSINFO("DefaultProperty", "options")

        /*!
         * @brief The expanded state of the @c DropDown.
         *
         * The @c expandedChanged() signal is emitted as soon as the state starts to change.
         *
         * The @c expanded state is @c true as soon as @c %DropDown starts to expand, and @c false as soon as it starts to collapse.
         *
         * The default state is @c false (collapsed).
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded RESET resetExpanded NOTIFY expandedChanged FINAL)

    public:
        /*!
         * @brief Constant indicating that there are no options selected.
         *
         * @since BlackBerry 10.0.0
         */
        static const int SelectedIndexNone;

        /*!
         * @brief Constructs a @c DropDown with a parent.
         *
         * @param parent The parent container or @c 0. This parameter is optional and will default to @c 0 if not specified.
         * If not @c 0, the ownership of the constructed @c %DropDown is transferred to the parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit DropDown(Container * parent = 0);

        /*!
         * @brief Destructs the @c DropDown.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~DropDown();

        /*!
         * @brief Returns the current title of this @c DropDown.
         *
         * @return The current title.
         *
         * @since BlackBerry 10.0.0
         */
        const QString title() const;

        /*!
         * @brief Sets the title of the @c DropDown.
         * 
         * The title is visible at all times, and is shown on the left side of the @c %DropDown header.
         * The title is truncated if it is too long to fit in the available space. 
         *
         * @param title The new title.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTitle(const QString &title);

        /*!
         * @brief Resets the title to the default value (@c QString::null).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTitle();

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
         * The @c index must either be in the range of @c [0, @c count() - 1] or @c SelectedIndexNone.
         * Otherwise, it is ignored. Passing @c SelectedIndexNone deselects any selected option.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the selected index is changed.
         *
         * @param index The index of the option to select, or @c SelectedIndexNone to deselect any
         * selected option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSelectedIndex(int index);

        /*!
         * @brief Deselects any selected option.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged() and @c selectedValueChanged()
         * signals are emitted, if an option was deselected.
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
         * The @c Option must either belong to the @c DropDown or be @c 0. Otherwise, it is ignored.
         * Passing @c 0 deselects any selected option.
         *
         * This function is equivalent to calling @c setSelectedIndex(indexOf(option)), assuming that the
         * @c Option belongs to this @c %DropDown or is @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the selected option is changed.
         *
         * @param option The option belonging to this @c %DropDown to select, or @c 0 to deselect any selected option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSelectedOption(bb::cascades::Option* option);

        /*!
         * @brief Deselects any selected option.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if an option was deselected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSelectedOption();

        /*!
         * @brief Returns whether the @c DropDown has a selected option.
         *
         * @return @c true if the @c %DropDown has a selected option, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isSelectedOptionSet() const;

        /*!
         * @brief Returns the value of the currently selected option.
         *
         * If no option is selected or no value is set on the selected option, an invalid @c QVariant is returned.
         *
         * @return The value of the currently selected option or an invalid @c QVariant.
         *
         * @since BlackBerry 10.0.0
         */
        QVariant selectedValue() const;

        /*!
         * @brief Returns the @c expanded state for the @c DropDown.
         *
         * @return @c true if the @c %DropDown is expanded, @c false if the @c %DropDown is collapsed.
         *
         * @since BlackBerry 10.0.0
         */
        bool isExpanded() const;

        /*!
         * @brief Sets the expanded state.
         *
         * In the case of a successful change, the @c expandedChanged() signal is emitted.
         *
         * @param expanded If @c true the @c DropDown is expanded, if @c false the @c %DropDown is
         * collapsed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setExpanded(bool expanded);

        /*!
         * @brief Resets the expanded state to @c false (collapsed).
         *
         * The @c expandedChanged() signal is emitted once reset.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetExpanded();

        /*!
         * @brief Adds an option to the @c DropDown.
         *
         * The added option is appended to the bottom of the @c %DropDown.
         *
         * If the option has already been added to another control, it will be removed from that control and added
         * to this @c %DropDown, which will also assume ownership of the @c Option. Once added, the @c optionAdded()
         * signal is emitted.
         *
         * If the option is @c 0, it is ignored.
         *
         * If the option is added as a selected option, the @c selectedIndexChanged(), @c selectedOptionChanged(),
         * and @c selectedValueChanged() signals are emitted.
         *
         * @param option The @c Option to be added.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void add(bb::cascades::Option* option);

        /*!
         * @brief Inserts the @c Option at the specified @c index.
         *
         * If the @c index is less than @c 0, the option is inserted at index @c 0.
         * If the @c index is equal to or greater than @c count(), the option is appended last.
         *
         * If the option is currently added to another control, it will be removed from that control and added
         * to this @c DropDown, which will also assume ownership of the option. Once added, the @c optionAdded()
         * signal is emitted.
         *
         * If the option is @c 0, it is ignored.
         *
         * If the option is added as a selected option, the @c selectedIndexChanged(),
         * @c selectedOptionChanged(), and @c selectedValueChanged() signals are emitted.
         *
         * The @c selectedIndexChanged() signal is emitted if the option is added before or at the selected
         * option's index.
         *
         * @param index The @c index to insert the @c Option at.
         * @param option The @c Option to be inserted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void insert(int index, bb::cascades::Option* option);

        /*!
         * @brief Removes the @c Option from the @c DropDown.
         *
         * This function removes the option from the @c %DropDown if the option belonged to the @c %DropDown.
         *
         * Once the @c Option is removed, the @c %DropDown no longer references it, but it is still 
         * owned by the @c DropDown. It is up to the application to either delete the removed 
         * @c Option, transfer its ownership (by setting its parent) to another object or leave 
         * it as a child of the @c %DropDown (in which case it will be deleted with the @c %DropDown).
         *
         * If an @c Option before the selected option is removed, @c selectedIndexChanged() signal is emitted.
         *
         * If the selected option is removed, the @c selectedIndex is set to @c SelectedIndexNone and the
         * @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged() signals are emitted.
         *
         * The @c optionRemoved() signal is emitted if the option is removed.
         *
         * @param option The option to be removed.
         * @return @c true if the @c Option was removed, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bool remove(bb::cascades::Option* option);

        /*!
         * @brief Removes all options from the @c DropDown and deletes them.
         *
         * The @c optionRemoved() signal is emitted with the @c option parameter as @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted if an option was selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void removeAll();

        /*!
         * @brief Returns the option at the @c index.
         *
         * The @c index must be in the range of [0, @c count() - 1], otherwise @c 0 is returned.
         *
         * The ownership the option is not transferred to the caller.
         *
         * @param index The @c index of the option to retrieve.
         * @return The retrieved option if @c index was valid, @c 0 otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bb::cascades::Option* at(int index) const;

        /*!
         * @brief Returns the index of the @c Option.
         * 
         * If the option is @c 0 or the option doesn't belong to the @c DropDown, @c SelectedIndexNone will be
         * returned.
         *
         * @param option The @c Option to get the index of.
         * @return The index of the @c Option, or @c SelectedIndexNone if the option does not belong to the @c %DropDown.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE int indexOf(bb::cascades::Option* option) const;

        /*!
         * @brief Returns the number of options in the @c DropDown.
         *
         * @return The number of options in the @c %DropDown.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE int count() const;

    Q_SIGNALS:
         /*!
         * @brief Emitted when the title of this @c DropDown changes. 
         *
         * @param title The new @c title.
          *
          * @since BlackBerry 10.0.0
         */
        void titleChanged(QString title);

        /*!
         * @brief Emitted when the @c expanded state has been changed.
         *
         * @param expanded The newly set @c expanded state
         *
         * @since BlackBerry 10.0.0
         */
        void expandedChanged(bool expanded);

        /*!
         * @brief Emitted when the selected option has changed.
         *
         * @param selectedIndex The index of the newly selected option, or @c SelectedIndexNone if no option was selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedIndexChanged(int selectedIndex);

        /*!
         * @brief Emitted when the selected option has changed.
         *
         * @param selectedOption The newly selected option, or @c 0 if no option was selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedOptionChanged(bb::cascades::Option* selectedOption);

        /*!
         * @brief Emitted when the @c selectedOptionSet property changes.
         *
         * @param selectedOptionSet @c true if the @c DropDown currently has a selected option, @c false otherwise.
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
         * @brief Emitted when an option has been added to the @c DropDown.
         *
         * @param option The option that has been added.
         *
         * @since BlackBerry 10.0.0
         */
        void optionAdded(bb::cascades::Option *option);

        /*!
         * @brief Emitted when an option has been removed from the @c DropDown.
         *        
         * @param option The option that has been removed, @c 0 if emitted by @c removeAll().
         *
         * @since BlackBerry 10.0.0
         */
        void optionRemoved(bb::cascades::Option *option);

    private:
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(DropDown)
        Q_DISABLE_COPY(DropDown)
        
        typedef DropDown ThisClass;
        typedef Control BaseClass;

        QDeclarativeListProperty<bb::cascades::Option> options();
        /*! \endcond */

    public:
        /*!
         * @brief A builder that constructs a @c DropDown.
         * 
         * To retrieve the builder, call @c DropDown::create().
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
             * @brief Sets the title for this @c DropDown.
             *
             * @param title The title to set.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& title(QString title)
            {
                this->instance().setTitle(title);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::DropDown::setExpanded(bool)
             */
            BuilderType& expanded(bool expanded)
            {
                this->instance().setExpanded(expanded);
                return this->builder();
            }

            /*!
             *
             * @copydoc bb::cascades::DropDown::add(bb::cascades::Option*)
             *
             */
            BuilderType& add(Option* option)
            {
                this->instance().add(option);
                return this->builder();
            }

            /*!
             * @brief Convenience method that creates an @c Option with specified text and an optional value, and adds it to the @c DropDown.
             *
             * @param optionText The text to be used in the option.
             * @param value An optional value parameter for the option.
             * @param selected If @c true the option is selected, if @c false the option is not selected.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& add(const QString &optionText, const QVariant &value = QVariant(), bool selected = false)
            {
                this->instance().add(Option::create().text(optionText).value(value).selected(selected));
                return this->builder();
            }
        };

        /*!
         * @brief A builder that constructs a @c DropDown.
         * 
         * To retrieve the builder, call @c DropDown::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, DropDown>
        {
        public:
            explicit Builder() : TBuilder<Builder, DropDown>(new DropDown())
            {
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing a @c DropDown.
         *
         * Using the builder to create a @c DropDown:
         *
         * @snippet tad/examples/controls/dropdown/src/DropDownExamples.cpp dropdown2
         *
         * @return A builder used for constructing a @c DropDown.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create()
        {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::DropDown)

#endif

