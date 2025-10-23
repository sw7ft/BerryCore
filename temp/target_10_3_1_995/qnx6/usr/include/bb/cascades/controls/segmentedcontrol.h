/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_segmentedcontrol_h
#define cascades_segmentedcontrol_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/option.h>

namespace bb {
    namespace cascades {

    class SegmentedControlPrivate;
    class Container;

    /*!
     *
     *
     * @brief A control that displays a horizontal row of selectable options.
     *
     * @c SegmentedControl allows you to create a horizontal row with up to four visible options. A user can 
     * select one of the options, and you can respond to the selection in your app. For example, you can use
     * a @c %SegmentedControl to filter between different types of the content in your app.
     *
     * The @c %SegmentedControl may be placed on all levels of a drill-down hierarchy. It may also be used
     * inside a @c TabbedPane navigation setup, as a way to navigate between sub-sections inside
     * a specific view. 
     *
     * @image html segmentedcontrol.png Example of what the @c %SegmentedControl looks like
     *
     * Defining a @c %SegmentedControl, with some @c Options, in C++, using the builder pattern:
     *
     * @snippet tad/examples/controls/segmentedcontrol/src/SegmentedControlExamples.cpp segmentedcontrol2
     *
     * Defining a @c %SegmentedControl, with some @c Options, in QML:
     *
     * @snippet tad/examples/controls/segmentedcontrol/assets/main.qml segmentedcontrol_qml1
     *
     * @c %SegmentedControl uses the @c Option class to represent the segments in the control. The @c text property
     * of the @c Option class is used for the label on the segment, while the @c selected property is used to
     * determine which segment is selected. Changing the selected property on an option updates the selected
     * index of the @c %SegmentedControl.
     *
     * When the @c %SegmentedControl has no options attached to it, it is not displayed. It's not possible to
     * have a @c %SegmentedControl that is displayed without a selected option.
     *
     * When a user presses an option, the @c %SegmentedControl changes its appearance to reflect the newly
     * selected segment, and the @c selectedIndexChanged() signal is emitted. The newly selected option also emits
     * its @c Option::selectedChanged() signal with a parameter of @c true. The previously selected option emits
     * its @c Option::selectedChanged() signal with a parameter of @c false.
     *
     * Adding an @c Option with @c selected set to @c true sets that segment in @c %SegmentedControl as selected.
     * If multiple options are added with @c selected set to @c true, the last option that was added is selected
     * and the others are not selected.
     *
     * The size of the @c %SegmentedControl behaves as follows:
     * - The width and height of the @c %SegmentedControl are device-dependent, built-in values, so:
     *   - Setting the preferred width or height does not affect the size of the @c %SegmentedControl in any way.
     *   - Setting the minimum width or height does not affect the size of the @c %SegmentedControl in any way.
     *   - Setting the maximum width or height does not affect the size of the @c %SegmentedControl in any way.
     * 
     * @see Option
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */

    class BBCASCADES_EXPORT SegmentedControl : public Control
    {
    private:
        Q_OBJECT

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
         * @brief Indicates whether any option in the @c SegmentedControl is currently selected.
         *
         * This property is set to @c true if any option is selected, and is set to @c false otherwise.
         *
         * This property can be used to determine if any option is currently selected, in addition to
         * examining the @c selectedIndex property (typically from QML). Specifically, if the
         * @c hasSelectedOption property is @c false, the @c selectedIndex property will be set to
         * @c SelectedIndexNone, which is not accessible from QML.
         *
         * @snippet tad/examples/controls/segmentedcontrol/assets/main.qml segmentedcontrol_qml2
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
         * @brief The list of @c Option in the @c SegmentedControl.
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
         * @brief Constructs a @c SegmentedControl with a parent.
         *
         * @param parent The parent container or @c 0. This parameter is optional and will default
         * to @c 0 if not specified. If not @c 0, the ownership of the constructed @c %SegmentedControl
         * is transferred to the parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit SegmentedControl(Container * parent = 0);

        /*!
         * @brief Destructs the @c SegmentedControl.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~SegmentedControl();

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
         * @brief Resets the selected index of the @c SegmentedControl.
         *
         * The selected index is reset to @c 0 if the @c %SegmentedControl has an @c Option selected
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
         * The @c Option must either belong to the @c SegmentedControl or be @c 0. Otherwise it is ignored.
         * Passing @c 0 resets the selected index to @c 0.
         *
         * This function is equivalent to calling @c setSelectedIndex(indexOf(option)) assuming that the @c Option
         * belongs to this @c %SegmentedControl, or is @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the selected option is changed.
         *
         * @param option The option belonging to this @c %SegmentedControl to select, or @c 0 to select the option at index 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSelectedOption(bb::cascades::Option* option);

        /*!
         * @brief Resets the selected option of the @c SegmentedControl.
         *
         * The selected index is reset to @c 0 if the @c %SegmentedControl has an @c Option selected
         * at a non-zero index.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if the index was changed to @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSelectedOption();

        /*!
         * @brief Returns whether the @c SegmentedControl has a selected option.
         *
         * @return @c true if the @c %SegmentedControl has a selected option, @c false otherwise.
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
        * @brief Adds an option to the @c SegmentedControl.
         *
         * The added option is placed last in the @c %SegmentedControl.
         *
         * If the option has already been added to another control, it will be removed from that control and added
         * to this @c %SegmentedControl, which will also assume ownership of the @c Option. Once added, the @c optionAdded()
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
        Q_INVOKABLE void add(bb::cascades::Option* option);

        /*!
         * @brief Inserts the @c Option at the specified @c index.
         *
         * If the @c index is less than @c 0, the option is inserted at index @c 0.
         * If the @c index is equal to or greater than @c count(), the option is appended last.
         *
         * If the option is currently added to another control, it will be removed from that control and added
         * to this @c SegmentedControl, which will also assume ownership of the option. Once added, the @c optionAdded()
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
        Q_INVOKABLE void insert(int index, bb::cascades::Option* option);

        /*!
         * @brief Removes the @c Option from the @c SegmentedControl.
         *
         * This function removes the option from the @c %SegmentedControl if the option belonged to the @c %SegmentedControl.
         *
         * Once the @c Option is removed, the @c %SegmentedControl no longer references it, but it is still 
         * owned by the @c SegmentedControl. It is up to the application to either delete the removed 
         * @c Option, transfer its ownership (by setting its parent) to another object or leave 
         * it as a child of the @c %SegmentedControl (in which case it will be deleted with the @c %SegmentedControl).
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
        Q_INVOKABLE bool remove(bb::cascades::Option* option);

        /*!
         * @brief Removes all options from the @c SegmentedControl and deletes them.
         *
         * The @c optionRemoved() signal is emitted with the @c option parameter as @c 0.
         *
         * The @c selectedIndexChanged(), @c selectedOptionChanged(), and @c selectedValueChanged()
         * signals are emitted, if an option was selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void removeAll();

       /*!
        * @brief Returns an option at a specific index if the index is valid, @c 0 otherwise.
        *
        * The ownership of the returned option is not changed; this @c SegmentedControl will still own the
        * option.
        *
        * @param index The index that specifies the option to return.
        *
        * @return The requested option if @c index is valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::Option* at(int index) const;

       /*!
        * @brief Returns the index of a specific option.
        *
        * If the option is @c 0 or the @c Option doesn't belong to the @c SegmentedControl, @c SelectedIndexNone
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
         * @brief Returns the number of options in the @c SegmentedControl.
         *
         * @return The number of options in the @c %SegmentedControl.
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
         * @param selectedOption The newly selected option, or @c 0 if no option is selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedOptionChanged(bb::cascades::Option* selectedOption);

        /*!
         * @brief Emitted when the @c selectedOptionSet property changes.
         *
         * @param selectedOptionSet @c true if the @c SegmentedControl currently has a selected option, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedOptionSetChanged(bool selectedOptionSet);

        /*!
         * @brief Emitted when the value of the selected option has changed.
         *
         * @param selectedValue The value of the newly selected option, or invalid @c QVariant if none is selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedValueChanged(const QVariant& selectedValue);

        /*!
         * @brief Emitted when an option has been added to the @c SegmentedControl.
         *
         * @param option The option that has been added.
         *
         * @since BlackBerry 10.0.0
         */
        void optionAdded(bb::cascades::Option *option);

        /*!
         * @brief Emitted when an option has been removed from the @c SegmentedControl.
         *        
         * @param option The option that has been removed, @c 0 if emitted by @c removeAll().
         *
         * @since BlackBerry 10.0.0
         */
        void optionRemoved(bb::cascades::Option *option);

    private:
        /*! @cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::Option> options();

        Q_DECLARE_PRIVATE(SegmentedControl)
        Q_DISABLE_COPY(SegmentedControl)

        typedef SegmentedControl ThisClass;
        typedef Control BaseClass;
        /*! @endcond */

    public:
        /*!
         * @brief A builder that constructs a @c SegmentedControl.
         * 
         * To retrieve the builder, call @c SegmentedControl::create().
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
            * 
            * @copydoc bb::cascades::SegmentedControl::add(bb::cascades::Option *)
            * 
            */
            BuilderType& add(bb::cascades::Option* option)
            {
                this->instance().add(option);
                return this->builder();
            }

            /*!
             * @brief Creates an option with the specified text and optional value, and adds it to the
             * @c SegmentedControl.
             * 
             * This is a convenience method that you can use in the following way:
             * 
             * @snippet tad/examples/controls/segmentedcontrol/src/SegmentedControlExamples.cpp segmentedcontrol3
             *
             * This is equivalent to the following:
             *
             * @snippet tad/examples/controls/segmentedcontrol/src/SegmentedControlExamples.cpp segmentedcontrol4
             *
             * @param optionText The text to be used in the option.
             * @param value An optional value parameter for the option.
             * @param selected An optional selected parameter for the option.
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
         * @brief A builder that constructs a @c SegmentedControl.
         * 
         * To retrieve the builder, call @c SegmentedControl::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, SegmentedControl>
        {
        public:
            explicit Builder() : TBuilder<Builder, SegmentedControl>(new SegmentedControl())
            {
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing a @c SegmentedControl.
         *
         * Using the builder to create a @c %SegmentedControl:
         *
         * @snippet tad/examples/controls/segmentedcontrol/src/SegmentedControlExamples.cpp segmentedcontrol1
         *
         * @return A builder used for constructing a @c %SegmentedControl.
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

QML_DECLARE_TYPE(bb::cascades::SegmentedControl)

#endif

