/* Copyright (C) 2011-2014 Research In Motion Limited.  */

#ifndef cascades_datetimepicker_h
#define cascades_datetimepicker_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/datetimepickermode.h>
#include <bb/cascades/controls/pickerkind.h>

namespace bb {
    namespace cascades {

    class DateTimePickerPrivate;
    class Container;

    /*!
      *
      * @brief A control for selecting a date or time.
      *
      * @image html datetimepicker.png Example of what the DateTimePicker looks like
      *
      * You can specify the type of picker using the @c #kind property.
      * The @c PickerKind::Expandable state displays the picker with a title
      * which can be set using the @c title property.
      * The @c PickerKind::List state displays the picker without a header and always expanded.
      *
      * There are several modes that you can use with @c %DateTimePicker, which are included in the
      * @c DateTimePickerMode class:
      * - Time: Shows two columns with hours and minutes.
      * - Date: Shows three columns with day, month and year. (Default)
      * - DateTime: Shows three columns with day, hours and minutes.
      * - Timer: Shows three columns with hours (in 0 to 23 hour range), minutes and seconds.
      *
      * To select a date and time create a @c QDateTime object with the specific date and time and use 
      * @c DateTimePicker.setValue().
      *
      * In QML the @c %DateTimePicker supports different date and time types when selecting the date and time:
      * - date ("YYYY-MM-DD")
      * - date and time ("YYYY-MM-DDTHH:MM:SS")
      * - JavaScript Date object
      *
      * When using the @c Time mode, a convenience function called @c dateFromTime() can be used to convert the time 
      * value to the correct format.
      *
      * <h3>QML Examples</h3>
      *
      * Here's an example of how to use the @c DateTimePicker in @c Date mode (the default mode):
      *
      * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_qml
      *
      * With @c DateTime mode:
      *
      * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_datetime_qml
      *
      * With @c Time mode, using @c dateFromTime():
      *
      * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_time_qml
      *
      * With @c Timer mode, selecting first row in each column:
      *
      * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_timer_qml
      *
      * Here's how to use a JavaScript @c Date object as the current date and time:
      *
      * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_current_qml
      *
      * <h3>C++ examples</h3>
      *
      * Here's how to use the @c DateTimePicker in @c Date mode (the default mode):
      *
      * @snippet tad/examples/controls/datetimepicker/src/DateTimePickerExamples.cpp datetimepicker
      *
      * With @c DateTime mode, using current date and time as selection:
      *
      * @snippet tad/examples/controls/datetimepicker/src/DateTimePickerExamples.cpp datetimepicker_datetime
      *
      * With @c Time mode, using the convenience function @c dateFromTime() 
      * to set time 11:10 as the selection:
      *
      * @snippet tad/examples/controls/datetimepicker/src/DateTimePickerExamples.cpp datetimepicker_time
      *
      * With @c Timer mode, selecting first row in each column:
      *
      * @snippet tad/examples/controls/datetimepicker/src/DateTimePickerExamples.cpp datetimepicker_timer
      *
      * @xmlonly
      * <apigrouping group="User interface/Core controls"/>
      * @endxmlonly
     *
     * @since BlackBerry 10.0.0
      */
    class BBCASCADES_EXPORT DateTimePicker : public Control
    {
    private:
        Q_OBJECT

       /*!
        * @brief The title of the %DateTimePicker.
        *
        * @note This property has no effect if @c kind is set to @c PickerKind::List.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

       /*!
        * @brief The mode of the %DateTimePicker.
        *
        * This setting determines what type of data is presented in the picker is used, and it can be changed at runtime.
        * The default mode is DateTimePickerMode::Date.
        * @see DateTimePickerMode
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::DateTimePickerMode::Type mode READ mode WRITE setMode RESET resetMode NOTIFY modeChanged FINAL)

       /*!
        * @brief The date and time value that is selected.
        *
        * The default value is the current date and time when the %DateTimePicker is created.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDateTime value READ value WRITE setValue RESET resetValue NOTIFY valueChanged FINAL)

        /*!
        * @brief The minimum date and time value that can be selected.
        *
        * If the selected value is outside of the minimum range the value will be
        * clamped to either the maximum or minimum value.
        *
        * By default the minimum value is not set.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDateTime minimum READ minimum WRITE setMinimum RESET resetMinimum NOTIFY minimumChanged FINAL)

        /*!
        * @brief The maximum date and time value that can be selected.
        *
        * If the selected value is outside of the maximum range the value will be
        * clamped to either the maximum or minimum value.
        *
        * By default the maximum value is not set.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDateTime maximum READ maximum WRITE setMaximum RESET resetMaximum NOTIFY maximumChanged FINAL)

        /*!
        * @brief The increment interval of the minutes.
        * Valid intervals are 1, 5, 10 or 15. Default is 5.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(int minuteInterval READ minuteInterval WRITE setMinuteInterval RESET resetMinuteInterval NOTIFY minuteIntervalChanged FINAL)

       /*!
        * @brief The expanded state as a boolean.
        * The expanded state. True means that the control is expanded, false means that the control
        * is collapsed. The signal is emitted as soon as the %DateTimePicker starts to expand.
        * The DateTimePicker will request focus when it is expanded. However, if it doesn't get focus
        * it will still go to its expanded state.
        *
        * The default value of this property is false, i.e. collapsed.
        *
        * @note This property has no effect if @c kind is set to @c PickerKind::List.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded RESET resetExpanded NOTIFY expandedChanged FINAL)

        /*!
         * @brief The kind of @c DateTimePicker to create.
         *
         * Possible values for this property are @c PickerKind::Default, @c PickerKind::List
         * and @c PickerKind::Expandable.
         * The default value is @c PickerKind::Default, which indicates that
         * system default picker should be used.
         *
         * The @c PickerKind::Expandable state displays the picker with a title
         * that can be set using the @c title property.
         * The @c PickerKind::List state displays the picker without a header and always expanded.
         *
         * @note This property can only be set once during the construction of the @c DateTimePicker.
         *
         * Here's an example of how to create and set up different kinds of date time pickers:
         *
         * QML:
         *
         * @code
         * // List picker
         * DateTimePicker {
         *     id: picker
         *     kind: PickerKind.List;
         * }
         * @endcode
         *
         * C++:
         *
         * @code
         * // Expandable picker
         * picker = DateTimePicker::create(PickerKind::Expandable)
         *            .title("Select")
         *            .expanded(true)
         * @endcode
         *
         *
         * @xmlonly
         * <qml>
         * <property writable="init-only"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bb::cascades::PickerKind::Type kind READ kind WRITE setKind REVISION 4 FINAL)


    public:
       /*!
        * @brief Constructs a %DateTimePicker with a parent and DateTimePickerMode::Date as its initial mode and of the kind @c PickerKind::Default.
        *
        * If not 0, the ownership of the constructed %DateTimePicker will be transferred to the parent.
        *
        * @param parent The parent container or 0. Optional and will default to 0 if not specified.
        * @param mode The mode of the %DateTimePicker. Default mode is DateTimePickerMode::Date
        *
        * @since BlackBerry 10.0.0
        */
        explicit DateTimePicker(Container* parent = 0, bb::cascades::DateTimePickerMode::Type mode = bb::cascades::DateTimePickerMode::Date);

       /*!
        * @brief Constructs a @c Picker with a specified kind and a parent.
        *
        * @param kind The kind of the @c Picker.
        * @param parent The parent container or @c 0. The parent is optional and will default to @c 0 if not specified.
        * @param mode The mode of the %DateTimePicker. Default mode is DateTimePickerMode::Date
        *
        * @since BlackBerry 10.3.1
        */
        Q_REVISION(4)
        explicit DateTimePicker(PickerKind::Type kind, Container* parent = 0, bb::cascades::DateTimePickerMode::Type mode = bb::cascades::DateTimePickerMode::Date);

       /*!
        * @brief Destructs the DateTimePicker.
        *
        * @since BlackBerry 10.0.0
        */
        virtual ~DateTimePicker();

       /*!
        * @brief Returns the @c kind for the @c DateTimnePicker.
        *
        * @return The current kind of picker.
        *
        * @since BlackBerry 10.3.1
        */
        Q_REVISION(4)
        bb::cascades::PickerKind::Type kind() const;

       /*!
        * @brief Returns the current expanded state.
        * @c true means that the state is expanded.
        * @c false means that the state is collapsed.
        *
        * @return the current expanded state
        *
        * @since BlackBerry 10.0.0
        */
        bool isExpanded() const;

       /*!
        * @brief Converts a QTime object to a QDateTime object.
        *
        * This can be used when you want to specify only the time when Time mode is used.
        *
        * Example when used in QML:
        *
        * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_time_qml
        *
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE QDateTime dateFromTime(const QTime& time);

       /*!
        * @brief Sets the title of the %DateTimePicker.
        *
        * The titleChanged() signal will be emitted if operation was successful.
        *
        * @param title The title.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setTitle(const QString& title);

       /*!
        * @brief Returns the title of the %DateTimePicker.
        *
        * @return The title.
        *
        * @since BlackBerry 10.0.0
        */
        QString title() const;

        /*!
         * @brief Resets the title.
         *
         * The titleChanged() signal will be emitted if operation was successful.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTitle();

       /*!
        * @brief Sets the mode of the %DateTimePicker.
        *
        * When the mode is changed, the current selected value is not affected.
        *
        * The modeChanged() signal will be emitted if operation was successful.
        *
        * @param mode The mode of the %DateTimePicker.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setMode(bb::cascades::DateTimePickerMode::Type mode);

       /*!
        * @brief Returns the current mode of the %DateTimePicker.
        *
        * The default mode is DateTimePickerMode::Date.
        *
        * @return The mode of the DateTimePicker.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::DateTimePickerMode::Type mode() const;

       /*!
        * @brief Resets the current mode to the default mode DateTimePickerMode::Date.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetMode();

       /*!
        * @brief Sets the date and time value that is selected in the %DateTimePicker.
        *
        * If the value is outside of the maximum or minimum range the value will be clamped
        * to either the maximum or minimum value.
        *
        * Note: Minute value will be rounded to nearest interval set with setMinuteInterval()
        *       Second will be reset to 0
        *
        * C++ example for selecting current date and time:
        *
        * @snippet tad/examples/controls/datetimepicker/src/DateTimePickerExamples.cpp datetimepicker_current
        *
        * QML example for selecting current date and time:
        *
        * @snippet tad/examples/controls/datetimepicker/assets/main.qml datetimepicker_current_qml
        *
        * The valueChanged() signal will be emitted if operation was successful.
        *
        * @param value The date and time value to select.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setValue(const QDateTime& value);

       /*!
        * @brief Returns the current selected date and time value.
        *
        * @return The value of the selected date and time value.
        *
        * @since BlackBerry 10.0.0
        */
        QDateTime value() const;

       /*!
        * @brief Resets the selected value to the current date and time.
        *
        * If the current date and time is outside of the maximum or minimum range it
        * will be clamped to either the maximum or minimum value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetValue();

       /*!
        * @brief Sets the earliest date and time value that can be selected.
        *
        * By default the minimum value is not set and an empty QDateTime will be returned
        * when minimum() is called.
        *
        * If the minimum value is higher than the maximum value neither maximum nor minimum
        * values will have effect.
        *
        * If the selected value is outside of the minimum range the value will be
        * clamped to either the maximum or minimum value.
        *
        * To remove the minimum value set an empty QDateTime as value or use resetMinimum().
        *
        * The minimumChanged() signal will be emitted if operation was successful.
        *
        * @param value The minimum date and time value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setMinimum(const QDateTime& value);

       /*!
        * @brief Returns the current minimum date and time value.
        *
        *
        * @return The minimum date and time value.
        *         If the minimum value is not set an empty QDateTime is returned.
        *
        * @since BlackBerry 10.0.0
        */
        QDateTime minimum() const;

       /*!
        * @brief Removes the minimum value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetMinimum();

       /*!
        * @brief Sets the latest date and time value that can be selected.
        *
        * By default the maximum value is not set and an empty QDateTime will be returned
        * when maximum() is called.
        *
        * If the maximum value is lower than the minimum value neither minimum nor maximum
        * values will have effect.
        *
        * If the selected value is outside of the maximum range the value will be
        * clamped to either the maximum or minimum value.
        *
        * To remove the maximum value set an empty QDateTime as value or use resetMaximum().
        *
        * The minimumChanged() signal will be emitted if operation was successful.
        *
        * @param value The maximum date and time value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setMaximum(const QDateTime& value);

       /*!
        * @brief Returns the current maximum date and time value.
        *
        * @return The maximum date and time value.
        *         If the maximum value is not set an empty QDateTime is returned.
        *
        * @since BlackBerry 10.0.0
        */
        QDateTime maximum() const;

       /*!
        * @brief Removes the maximum value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetMaximum();

       /*!
        * @brief Sets the interval by which the minutes are incremented.
        *
        * Valid values are 1, 5, 10 or 15. Default is 5. Any non valid values are ignored.
        *
        * The minuteIntervalChanged() signal will be emitted if operation was successful.
        *
        * @param minuteInterval The minute interval value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setMinuteInterval(int minuteInterval);

       /*!
        * @brief Returns the current minute interval value.
        *
        * @return The minute interval value.
        *
        * @since BlackBerry 10.0.0
        */
        int minuteInterval() const;

       /*!
        * @brief Resets the minute interval to the default value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetMinuteInterval();

       /*!
        * @brief Sets the expanded state.
        *
        * In case of successful change #expandedChanged(bool) signal is emitted.
        * @param expanded The new state to set. true means expanded, false means collapsed
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setExpanded(bool expanded);

        /*!
        * @brief Resets the expanded state to @c false, i.e. collapsed.
        * #expandedChanged(bool) signal is emitted.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetExpanded();

    Q_SIGNALS:

       /*!
        * @brief Emitted when the title has changed.
        *
        * @param title The new title.
        *
        * @since BlackBerry 10.0.0
        */
        void titleChanged(QString title);

       /*!
        * @brief Emitted when the mode has changed.
        *
        * @param newMode The new selected mode of the DateTimePicker.
        *
        * @since BlackBerry 10.0.0
        */
        void modeChanged(bb::cascades::DateTimePickerMode::Type newMode);

       /*!
        * @brief Emitted when the value of the date and time has changed.
        *
        * @param value The new value of the date and time.
        *
        * @since BlackBerry 10.0.0
        */
        void valueChanged(QDateTime value);

       /*!
        * @brief Emitted when the minimum value of the date and time has changed.
        *
        * @param value The new minimum value of the date and time.
        *
        * @since BlackBerry 10.0.0
        */
        void minimumChanged(QDateTime value);

       /*!
        * @brief Emitted when the maximum value of the date and time has changed.
        *
        * @param value The new maximum value of the date and time.
        *
        * @since BlackBerry 10.0.0
        */
        void maximumChanged(QDateTime value);

       /*!
        * @brief Emitted when the minute interval value has changed.
        *
        * @param minuteInterval The new minute interval value.
        *
        * @since BlackBerry 10.0.0
        */
        void minuteIntervalChanged(int minuteInterval);

       /*!
        * @brief Emitted when the expanded state has been changed.
        *
        * @param expanded The newly set expanded state
        *
        * @since BlackBerry 10.0.0
         */
        void expandedChanged(bool expanded);

    private:

        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(DateTimePicker)
        Q_DISABLE_COPY(DateTimePicker)

        typedef DateTimePicker ThisClass;
        typedef Control BaseClass;

        Q_REVISION(4)
        void setKind(bb::cascades::PickerKind::Type kind);
        /*! @endcond */

    public:
          /*!
           * @brief A builder template for constructing a %DateTimePicker.
           *
           * To retrieve the builder, call
           * DateTimePicker::create().
           *
           * @since BlackBerry 10.0.0
           */
          template <typename BuilderType, typename BuiltType>
          class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
          {
          protected:
              TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
          public:
             /*!
              * @copydoc bb::cascades::DateTimePicker::setTitle(const QString&)
              */
              BuilderType& title(const QString& title)
              {
                  this->instance().setTitle(title);
                  return this->builder();
              }
             /*!
              * @copydoc bb::cascades::DateTimePicker::setMode(bb::cascades::DateTimePickerMode::Type)
              */
              BuilderType& mode(bb::cascades::DateTimePickerMode::Type mode)
              {
                  this->instance().setMode(mode);
                  return this->builder();
              }
             /*!
              * @copydoc bb::cascades::DateTimePicker::setValue(const QDateTime&)
              */
              BuilderType& value(const QDateTime& value)
              {
                  this->instance().setValue(value);
                  return this->builder();
              }
             /*!
              * @copydoc bb::cascades::DateTimePicker::setMinimum(const QDateTime&)
              */
              BuilderType& minimum(const QDateTime& value)
              {
                  this->instance().setMinimum(value);
                  return this->builder();
              }
             /*!
              * @copydoc bb::cascades::DateTimePicker::setMaximum(const QDateTime&)
              */
              BuilderType& maximum(const QDateTime& value)
              {
                  this->instance().setMaximum(value);
                  return this->builder();
              }
             /*!
              * @copydoc bb::cascades::DateTimePicker::setMinuteInterval(int)
              */
              BuilderType&  minuteInterval(int minuteInterval)
              {
                  this->instance().setMinuteInterval(minuteInterval);
                  return this->builder();
              }

             /*!
              * @copydoc bb::cascades::DateTimePicker::setExpanded(bool)
              */
              BuilderType& expanded(bool expanded)
              {
                  this->instance().setExpanded(expanded);
                  return this->builder();
              }
          };

          /*!
           * @brief A builder for constructing a %DateTimePicker.
           *
           * To retrieve the builder, call
           * DateTimePicker::create().
           *
           * @since BlackBerry 10.0.0
           */
          class Builder : public TBuilder<Builder, DateTimePicker>
          {
          public:
              explicit Builder() : TBuilder<Builder, DateTimePicker>(new DateTimePicker()) {}
             /*!
              * @brief A builder for constructing a %DateTimePicker of a specific kind.
              *
              * To retrieve the builder, call
              * DateTimePicker::create(PickerKind::Type).
              *
              * @since BlackBerry 10.3.1
              */
              explicit Builder(PickerKind::Type kind) : TBuilder<Builder, DateTimePicker>(new DateTimePicker(kind)) {}
          };



          /*!
           * @brief Creates and returns a builder for constructing a %DateTimePicker.
           *
           * Using the builder to create a %DateTimePicker:
           *
           * @snippet tad/examples/controls/datetimepicker/src/DateTimePickerExamples.cpp datetimepicker_datetime
           *
           * @return A builder used for constructing a %DateTimePicker control.
           *
           * @since BlackBerry 10.0.0
           */
          static Builder create()
          {
              return Builder();
          }


          /*!
           * @brief Creates and returns a builder for constructing a %DateTimePicker.
           *
           * @param kind Specifies the kind of this picker
           *
           * The following example uses the builder to create a @c %Picker object:
           *
           * @code
           * DateTimePicker::create(PickerKind::Expandable)
           *     .title("Title");
           * @endcode
           *
           * @return A builder used for constructing a %DateTimePicker object.
           *
           * @since BlackBerry 10.3.1
           */
          static Builder create(PickerKind::Type kind)
          {
              return Builder(kind);
          }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::DateTimePicker)

#endif
