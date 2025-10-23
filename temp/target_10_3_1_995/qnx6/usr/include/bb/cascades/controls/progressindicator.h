/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_progressindicator_h
#define cascades_progressindicator_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/progressindicatorstate.h>

namespace bb {
    namespace cascades {

    class ProgressIndicatorPrivate;
    class Container;

    /*!
     *
     * @brief A control that is used to measure the progress of a specified process.
     *
     * @image html progress_indicator.png The progress indicator.
     *
     * A progress indicator showing the progress of a task as a bar. The progress is
     * specified by the @c #value property, which falls within the range specified by the @c #fromValue
     * and #toValue properties. The value of @c fromValue does not have to be lesser than the
     * value of @c toValue.
     *
     * The appearance of the control can be controlled by setting the @c #state,
     * @c #value, @c #fromValue and @c #toValue properties.
     *
     * Here's an example of a progress indicator with values from 100 to 0 and the current value set
     * to 50. This could be used to indicate what percentage of the process has been completed.
     *
     * @snippet tad/examples/controls/progressindicator/assets/main.qml progressindicator1_qml
     *
     * Here's an example of a progress indicator controlled by a slider, in QML:
     *
     * @snippet tad/examples/controls/progressindicator/assets/main.qml progressindicator2_qml
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ProgressIndicator : public Control
    {
    private:
        Q_OBJECT

        /*!
         * @brief The current progress visualized by this progress indicator.
         *
         * The progress is the current value normalized in the range provided by #fromValue and
         * #toValue properties. The value of progress is always in the range [0,1].
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float progress READ progress NOTIFY progressChanged FINAL)

        /*!
         * @brief The current value visualized by this progress indicator.
         *
         * The value must be in the range provided by #fromValue and #toValue properties.
         *
         * The default value is the same as value of #fromValue.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float value READ value WRITE setValue RESET resetValue NOTIFY valueChanged FINAL)

       /*!
        * @brief The low end of the value range.
        *
        * The default value is 0.0. It is permissible that the value of this property is more than the value of @c toValue.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(float fromValue READ fromValue WRITE setFromValue RESET resetFromValue NOTIFY fromValueChanged FINAL)

       /*!
        * @brief The high end of the value range.
        *
        * The default value is 1.0. It is permissible that the value of this property is less than the value of @c fromValue.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(float toValue READ toValue WRITE setToValue RESET resetToValue NOTIFY toValueChanged FINAL)

        /*!
         * @brief The current state of this progress indicator.
         *
         * The default value is @c ProgressIndicatorState::Progress.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ProgressIndicatorState::Type state READ state WRITE setState RESET resetState NOTIFY stateChanged FINAL)

    public:
        /*!
         * @brief Constructs a progress indicator with a parent.
         *
         * If not 0, the ownership of the constructed progress indicator will be transferred to the parent.
         *
         * @param parent The parent container or 0. Optional and will default to 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ProgressIndicator(Container * parent = 0);

        /*!
        * @brief Destructs this progress indicator.
         *
         * @since BlackBerry 10.0.0
        */
        virtual ~ProgressIndicator();

       /*!
        * @brief Returns the low end of the value range.
        *
        * The default value is 0.0.
        *
        * @return The @c fromValue.
        *
        * @since BlackBerry 10.0.0
        */
        float fromValue() const;

       /*!
        * @brief Sets the low end of the value range.
        *
        * @param from The @c fromValue.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setFromValue(float from);

       /*!
        * @brief Resets the low end of the value range to the default value. The default value is 0.0.
        *
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetFromValue();

       /*!
        * @brief Returns the high end of the value range. The default value is 1.0.
        *
        * @return The @c toValue.
        *
        * @since BlackBerry 10.0.0
        */
        float toValue() const;

       /*!
        * @brief Sets the high end of the value range.
        *
        * @param to The @c toValue.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setToValue(float to);

       /*!
        * @brief Resets the high end of the value range to the default value. The default value is 1.0.
        *
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetToValue();

       /*!
        * @brief Sets the value range.
        *
        * The current value is remapped into the specified range.
        *
        * This method will cause #fromValueChanged(), #toValueChanged() and #valueChanged() signals
        * to be emitted if any of the properties change.
        *
        * @param  from  The low end of the value range.
        * @param  to    The high end of the value range.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setRange(float from, float to);

       /*!
        * @brief Resets the value range to the default value.
        * 
        * The default range is from 0.0 to 1.0.
        *
        * This method will cause #fromValueChanged(), #toValueChanged() and #valueChanged() signals
        * to be emitted if any of the properties change.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetRange();

       /*!
        * @brief Returns the current progress of this progress indicator.
        *
        * @return The progress of the progress indicator.
        *
        * @since BlackBerry 10.0.0
        */
        float progress() const;

        /*!
         * @brief Returns the current value of this progress indicator.
         *
         * @return The value of the progress indicator.
         *
         * @since BlackBerry 10.0.0
         */
        float value() const;

        /*!
         * @brief Sets the current value of this progress indicator.
         *
         * The value property is a number in the range provided by #fromValue and #toValue. Values 
         * outside this range will be clamped.
         *
         * Setting value to the value of #toValue does not automatically change 
         * the state of the progress indicator to @c Completed.
         *
         * Changing the value when the control is in @c Completed state may not change the
         * visual representation of the control. In order for progress to be reflected visually
         * the control must be in @c Progress or @c Pause state.
         *
         * @see setState()
         *
         * @param value The new value.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setValue(float value);

        /*!
         * @brief Resets value to the value of #fromValue.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetValue();

        /*!
         * @brief Returns the current state of the progress indicator.
         *
         * @return The state of this progress indicator.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ProgressIndicatorState::Type state() const;

        /*!
         * @brief Sets the current state of this progress indicator.
         *
         * @note Changing the state to @c Complete will not set value to the value of @c toValue
         * property.
         *
         * @param value The new state of this progress indicator.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setState(bb::cascades::ProgressIndicatorState::Type value);

        /*!
         * @brief Resets the state of this progress indicator to @c ProgressIndicatorState::Progress.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetState();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the value changes.
         *
         * @param value The new value.
         *
         * @since BlackBerry 10.0.0
         */
        void valueChanged(float value);

        /*!
         * @brief Emitted when the progress changes.
         *
         * Note that when setting from/to values, the 
         * value is remapped to keep the current progress, meaning this signal will not be emitted.
         *
         * @param progress The new value.
         *
         * @since BlackBerry 10.0.0
         */
        void progressChanged(float progress);

       /*!
        * @brief Emitted when @c toValue changes.
        *
        * @param toValue The @c toValue.
        *
        * @since BlackBerry 10.0.0
        */
        void toValueChanged(float toValue);

       /*!
        * @brief Emitted when the @c fromValue changes.
        *
        * @param fromValue The @c fromValue.
        *
        * @since BlackBerry 10.0.0
        */
        void fromValueChanged(float fromValue);

        /*!
         * @brief Emitted when the current state changes.
         *
        * @note Due to a work around for a Qt Core issue with accessing enums from QML
        * the argument of this signal doesn't follow naming convention for signals in
        * which the signal arguments are typically named to match the associated property's name.
        * Use the object's property to access current property value instead of the signal argument
        * to avoid runtime errors (i.e. use @c state instead of @c newState).
         *
         * @param newState The new state.
         *
         * @since BlackBerry 10.0.0
         */
        void stateChanged(bb::cascades::ProgressIndicatorState::Type newState);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ProgressIndicator)
        Q_DISABLE_COPY(ProgressIndicator)

        typedef ProgressIndicator ThisClass;
        typedef Control BaseClass;
        /*! @endcond */

    public:
        /*!
         * @brief A builder template for constructing a ProgressIndicator.
         * 
         * See ProgressIndicator::create() for getting a concrete Builder for constructing a ProgressIndicator.
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
             * @copydoc bb::cascades::ProgressIndicator::setValue(float)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& value(float value)
            {
                this->instance().setValue(value);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::ProgressIndicator::setToValue(float)
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& to(float to)
            {
                this->instance().setToValue(to);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::ProgressIndicator::setFromValue(float)
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& from(float from)
            {
                this->instance().setFromValue(from);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::ProgressIndicator::setState(bb::cascades::ProgressIndicatorState::Type)
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& state(bb::cascades::ProgressIndicatorState::Type value)
            {
                this->instance().setState(value);
                return this->builder();
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the @c progressChanged(float) signal with the default
             * connection type Qt::AutoConnection.
             *
             * Example:
             * @snippet tad/examples/controls/progressindicator/src/ProgressIndicatorExamples.cpp progressindicator1
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onProgressChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(progressChanged(float)), receiver, method);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a ProgressIndicator.
         *
         * @see ProgressIndicator::create() for getting a concrete Builder for constructing a ProgressIndicator.
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ProgressIndicator>
        {
         public:
            Builder() : TBuilder<Builder, ProgressIndicator>(new ProgressIndicator())
            {
            }
         };

        /*!
         * @brief Creates and returns a Builder for constructing a ProgressIndicator.
         *
         * @return A Builder for constructing a ProgressIndicator.
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

QML_DECLARE_TYPE(bb::cascades::ProgressIndicator)

#endif    // cascades_progressindicator_h

