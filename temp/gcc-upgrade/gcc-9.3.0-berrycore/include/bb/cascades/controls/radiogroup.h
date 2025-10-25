/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_radiogroup_h
#define cascades_radiogroup_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/option.h>

namespace bb {
    namespace cascades {

    class RadioGroupPrivate;
    class Container;

    /*!
     * @brief Used for grouping a set of @c Option controls.
     *
     * @image html radiogroup.png This is how radio buttons look.
     *
     * This control is useful for presenting users with some sort of choice.
     *
     * In a @c RadioGroup more than one option cannot be selected at one time.
     * Each  @c %Option can have several attributes, such as text, a description, and an image.
     * The options are displayed as a group of radio buttons.
     *
     * Here's an example of how to define a @c %RadioGroup, by using the builder methods in C++. 
     * One of the options is specified as selected:
     *
     * @snippet tad/examples/controls/radiogroup/src/RadioGroupExamples.cpp radiogroup1
     *
     * Here's another example of how to define a @c %RadioGroup. 
     * Since @c option is the default property of @c %RadioGroup,
     * options can be added without specifying the @c options property:
     *
     * @snippet tad/examples/controls/radiogroup/src/RadioGroupExamples.cpp radiogroup2
     *
     * And here's how to define a @c %RadioGroup in QML, including buttons to interact with it:
     *
     * @snippet tad/examples/controls/radiogroup/assets/main.qml radiogroup_qml1
     *
     * The size of the @c %RadioGroup behaves as follows:
     * - By default, the width of the control is adjusted automatically to fill its parent container.
     * - By default, the height of the control is adjusted automatically to fit all its options.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth
     * and @c Control::maxWidth properties.
     * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight
     * and @c Control::maxHeight and properties.
     *
     * @xmlonly
     * <qml>
     * <apigrouping group="User interface/Core controls"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT RadioGroup : public Control
    {
    private:
        Q_OBJECT

        /*!
         * @brief Controls whether the dividers between options are visible.
         *
         * If set to @c true, the dividers are shown. If set to @c false, the dividers are not shown.
         * The default value is @c false, which means no dividers are visible.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool dividersVisible READ dividersVisible WRITE setDividersVisible RESET resetDividersVisible NOTIFY dividersVisibleChanged FINAL)

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
         * @brief Indicates whether any option in the @c RadioGroup is currently selected.
         *
         * This property is set to @c true if any option is selected, and is set to @c false otherwise.
         *
         * This property can be used (typically from QML) to determine if any option is 
         * currently selected, in addition to
         * examining the @c selectedIndex property, or the @c selectedOption property. 
         * Specifically, if the
         * @c selectedOptionSet property is @c false, the @c selectedIndex property will be set to
         * @c SelectedIndexNone, which is not accessible from QML.
         *
         * @snippet tad/examples/controls/radiogroup/assets/main.qml radiogroup_qml2
         *
         * When the value of this property changes, the @c selectedOptionSetChanged() signal is emitted.
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
         * The default @c selectedValue is an invalid @c QVariant, if selected option has no value set,
         * or no option is selected.
         *
         * @see QVariant, QVariant::Invalid
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant selectedValue READ selectedValue NOTIFY selectedValueChanged FINAL)

        /*!
         * @brief The list of @c Option controls in the @c RadioGroup.
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

    public:

        /*!
         * @brief Constant indicating that there are no options selected.
         *
         * @since BlackBerry 10.0.0
         */
        static const int SelectedIndexNone;

        /*!
         * @brief Constructs a radio group with a parent.
         *
         * If not @c 0, the ownership of the constructed radio group will be transferred to the parent.
         *
         * @param parent The parent container or @c 0. Optional and will default to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit RadioGroup(Container * parent = 0);

        /*!
         * @brief Destructs the @c RadioGroup.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~RadioGroup();

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
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
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
         * The @c Option must either belong to the @c RadioGroup or be @c 0. Otherwise, it is ignored.
         * Passing @c 0 deselects any selected option.
         *
         * This function is equivalent to calling @c setSelectedIndex(indexOf(option)), assuming that the
         * @c Option belongs to this @c %RadioGroup or is @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the selected option is changed.
         *
         * @param option The option belonging to this @c %RadioGroup to select, or @c 0 to deselect any selected option.
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
         * @brief Return whether the @c RadioGroup has a selected option.
         *
         * @return @c true if the @c %RadioGroup has a selected option, @c false otherwise.
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
         * @brief Returns the value of the @c dividersVisible property indicating whether the dividers
         * between options are shown.
         *
         * @return @c true if a divider is shown between each option, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool dividersVisible() const;

        /*!
         * @brief Sets the value of the @c dividersVisible property.
         *
         * This property indicates whether the dividers between options should be shown or not.
         *
         * @param dividersVisible If @c true a divider is shown between each option, if @c false dividers
         * are not shown.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDividersVisible(bool dividersVisible);

        /*!
         * @brief Resets the @c dividersVisible property to the default value of @c false (dividers are not shown).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDividersVisible();

        /*!
         * @brief Adds an option to the @c RadioGroup.
         *
         * The added option is appended to the bottom of the @c %RadioGroup.
         *
         * If the option has already been added to another control, it will be removed from that control and added
         * to this @c %RadioGroup, which will also assume ownership of the @c Option. Once added, the @c optionAdded()
         * signal is emitted.
         *
         * If the option is @c 0, it is ignored.
         *
         * If the option is added as a selected option, the @c selectedIndexChanged(), @c selectedOptionChanged()
         * and @c selectedValueChanged() signals are emitted 
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
         * to this @c RadioGroup, which will also assume ownership of the option. Once added, the @c optionAdded()
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
         * @brief Removes the @c Option from the @c RadioGroup.
         *
         * This function removes the option from the @c %RadioGroup, if the option belonged to the @c %RadioGroup.
         *
         * Once the @c Option is removed, the @c %RadioGroup no longer references it, but it is still 
         * owned by the @c RadioGroup. It is up to the application to either delete the removed 
         * @c Option, transfer its ownership (by setting its parent) to another object or leave 
         * it as a child of the @c %RadioGroup (in which case it will be deleted with the @c %RadioGroup).
         *
         * If an @c Option before the selected option is removed, @c selectedIndexChanged() signal is emitted.
         *
         * If the selected option is removed, the @c selectedIndex is set to @c SelectedIndexNone and the
         * @c selectedIndexChanged(), @c selectedOptionChanged() and @c selectedValueChanged() signals are emitted.
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
         * @brief Removes all options from the @c RadioGroup and deletes them.
         *
         * The @c optionRemoved() signal is emitted with the @c option parameter as @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged() and @c selectedValueChanged()
         * signals are emitted, if an option was selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void removeAll();

       /*!
        * @brief Returns an option at a specific index if the index is valid, @c 0 otherwise.
        *
        * The ownership of the returned option is not changed; this @c RadioGroup will still own the
        * option.
        *
        * @param index The index that specifies the option to return.
        *
        * @return The requested option if the @c index is valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::Option* at(int index) const;

       /*!
        * @brief Returns the index of a specific option.
        *
        * If the option is @c 0 or the @c Option doesn't belong to the @c RadioGroup, @c SelectedIndexNone
        * is returned.
        *
        * @param option The option to get the index of.
        *
        * @return The index of the option, or @c SelectedIndexNone.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int indexOf(bb::cascades::Option* option) const;

        /*!
         * @brief Returns the number of options in the @c RadioGroup.
         *
         * @return The number of options in the @c %RadioGroup.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE int count() const;

    Q_SIGNALS:

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
         * @param selectedOptionSet @c true if the @c RadioGroup currently has a selected option, @c false otherwise.
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
         * @brief Emitted when the @c dividersVisible property has changed.
         *
         * @param dividersVisible @c true if a divider is shown between each option, @c false if
         * dividers are not shown.
         *
         * @since BlackBerry 10.0.0
         */
        void dividersVisibleChanged(bool dividersVisible);

        /*!
        * @brief Emitted when an option has been added to the @c RadioGroup.
        *
        * @param option The option that has been added.
         *
         * @since BlackBerry 10.0.0
        */
        void optionAdded(bb::cascades::Option *option);

       /*!
        * @brief Emitted when an option has been removed from the @c RadioGroup.
        *
        * @param option The option that has been removed, or @c 0 if emitted by @c removeAll().
        *
        * @since BlackBerry 10.0.0
        */
        void optionRemoved(bb::cascades::Option *option);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(RadioGroup)
        Q_DISABLE_COPY(RadioGroup)

        typedef RadioGroup ThisClass;
        typedef Control BaseClass;

        QDeclarativeListProperty<Option> options();
        /*! @endcond */

    public:
        /*!
         * @brief A template builder class for constructing a @c RadioGroup.
         *
         * To retrieve the builder, call @c RadioGroup::create().
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
             * @copydoc bb::cascades::RadioGroup::setDividersVisible(bool)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& dividers(bool dividersVisible)
            {
                this->instance().setDividersVisible(dividersVisible);
                return this->builder();
            }

            /*!
             *
             * @copydoc bb::cascades::RadioGroup::add(bb::cascades::Option*)
             *
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& add(Option* option)
            {
                this->instance().add(option);
                return this->builder();
            }

            /*!
             * @brief Convenience method that creates an option with the specified text and optionally
             * a value and adds it to the group.
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
         * @brief A concrete builder class for constructing a @c RadioGroup.
         *
         * To retrieve the builder, call @c RadioGroup::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, RadioGroup>
        {
        public:
            explicit Builder() : TBuilder<Builder, RadioGroup>(new RadioGroup())
            {
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing a @c RadioGroup.
         *
         * Example using the builder to create a @c %RadioGroup with two options:
         *
         * @snippet tad/examples/controls/radiogroup/src/RadioGroupExamples.cpp radiogroup3
         *
         * @return A builder used for constructing a @c RadioGroup.
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

QML_DECLARE_TYPE(bb::cascades::RadioGroup)

#endif
