/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_slider_h
#define cascades_slider_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>


namespace bb {
    namespace cascades {
    
    class SliderPrivate;
    class Container;

    /*!
     * 
     * @brief A control that allows for selection of a value from a range of values.
     *
     * @image html slider_regular.png A slider.
     *
     * The input range for the slider is set using the @c #fromValue and @c #toValue properties, the defaults
     * being 0.0 and 1.0. You can listen to changes to the slider value through the @c #value and
     * @c #immediateValue properties. 
     *
     * The size of the slider behaves as follows:
     * - By default, the width of the control has a device-dependent built-in value.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth
     * and @c Control::maxWidth properties.
     * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight
     * and @c Control::maxHeight are not used.
     *
     * Here's an example of how you can create the simple slider in the various ways:
     *
     * @snippet tad/examples/controls/slider/src/SliderExamples.cpp slider
     *
     * Create the slider with an input range ( @c fromValue and @c toValue) and set the value using the builder pattern:
     * @snippet tad/examples/controls/slider/src/SliderExamples.cpp slider_builder
     *
     * Create the slider and set the @c fromValue, @c toValue, and current @c value in CPP and QML:
     * @snippet tad/examples/controls/slider/src/SliderExamples.cpp slider_setvalue
     * @snippet tad/examples/controls/slider/assets/main.qml slider_setvalue_qml
     *
     * Create the slider and set the range and the value:
     * @snippet tad/examples/controls/slider/src/SliderExamples.cpp slider_range
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Slider : public Control {
    private:
        Q_OBJECT
       /*!
        * @brief The low end of the input range.
        *
        * The default value is 0.0.
        * 
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(float fromValue READ fromValue WRITE setFromValue RESET resetFromValue NOTIFY fromValueChanged FINAL)
        
       /*!
        * @brief The high end of the input range.
        *
        * The default value is 1.0.
        * 
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(float toValue READ toValue WRITE setToValue RESET resetToValue NOTIFY toValueChanged FINAL)
        
       /*!
        * @brief The current value of the slider.
        *
        * This value is updated only when the user released the slider. The value is in
        * the range between @c fromValue and @c toValue. When setting a number outside the
        * range, the value is mapped into the range. The valueChanged() signal 
        * is emitted every time this changes.
        *
        * The default value is the same as @c fromValue.
        *
        * @see immediateValue for getting the value while the slider is being dragged.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(float value READ value WRITE setValue RESET resetValue NOTIFY valueChanged FINAL)

       /*!
        * @brief The immediate value of the slider.
        *
        * This value is updated both while the user is dragging the slider and when the 
        * slider is released. This value is also updated everytime Slider::value is updated. 
        * The value is in the range between @c fromValue and @c toValue. 
        * The immediateValueChanged() signal is emitted every time this changes.
        *
        * The default value is the same as @c fromValue.
        *
        * @see value for getting the value only when the slider is released.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(float immediateValue READ immediateValue NOTIFY immediateValueChanged FINAL)

    public:
       /*!
         * @brief Constructs a slider and specifies the parent container.
         *
         * The ownership of the slider is transfered to the parent if a parent is specified.
         *
         * @param parent The parent container or 0. This parameter is optional. 
         * The default is 0 if you don't specify a parent.
        *
        * @since BlackBerry 10.0.0
        */
        explicit Slider(Container *parent = 0);
        virtual ~Slider();

       /*!
        * @brief Returns the low end of the input range.
        *
        * The default value is 0.0.
        *
        * @return The @c fromValue.
        *
        * @since BlackBerry 10.0.0
        */
        float fromValue() const;
        
       /*!
        * @brief Sets the low end of the input range.
        *
        * @param from The @c fromValue.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setFromValue(float from);
        
       /*!
        * @brief Resets the low end of the input range to the default value.
        *
        * The default value is 0.0.
        * 
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetFromValue();

       /*!
        * @brief Returns the high end of the input range.
        *
        * The default value is 1.0.
        *
        * @return The @c toValue.
        *
        * @since BlackBerry 10.0.0
        */
        float toValue() const;
        
       /*!
        * @brief Sets the high end of the input range.
        *
        * @param to The @c toValue.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setToValue(float to);

       /*!
        * @brief Resets the high end of the input range to the default value.
        *
        * The default value is 1.0.
        * 
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetToValue();

       /*!
        * @brief Sets the input range for the slider.
        *
        * The current value is remapped into the specified range.
        * This method will emit the fromValueChanged(), toValueChanged() and valueChanged() signals
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setRange(float from, float to);

       /*!
        * @brief Resets the input range to the default value.
        *
        * The default range is from 0.0 to 1.0.
        *
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetRange();

       /*!
        * @brief Returns the current value of the slider.
        *
        * @since BlackBerry 10.0.0
        */
        float value() const;
        
       /*!
        * @brief Sets the current value of the slider.
        *
        * If you provide a number outside the
        * defined range, the value is clamped to the range.
        *
        * @param value The value of the slider. 
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setValue(float value);
        
       /*!
        * @brief Resets the current value to the default value.
        *
        * The default value is the same as @c fromValue. 
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetValue();

       /*!
        * @brief Returns the immediate value of the slider.
        *
        * @since BlackBerry 10.0.0
        */
        float immediateValue() const;


    Q_SIGNALS:

       /*!
        * @brief Emitted when the value changes.
        *
        * @param value The current slider value.
        *
        * @since BlackBerry 10.0.0
        */
        void valueChanged(float value);

       /*!
        * @brief Emitted when the immediateValue changes.
        *
        * @param immediateValue The immediate slider value.
        *
        * @since BlackBerry 10.0.0
        */
        void immediateValueChanged(float immediateValue);

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
        
    private:
        Q_DECLARE_PRIVATE(Slider)
        Q_DISABLE_COPY(Slider)

   public:
        /*! @cond PRIVATE */
        typedef Slider ThisClass;
        typedef Control BaseClass;
        /*! @endcond */
        
       /*!
        * @brief A builder template for constructing a slider.
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
            * @copydoc bb::cascades::Slider::setValue(float)
            */
            BuilderType& value(float value)
            {
                this->instance().setValue(value);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::Slider::setToValue(float)
            */
            BuilderType& to(float to)
            {
                this->instance().setToValue(to);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::Slider::setFromValue(float)
            */
            BuilderType& from(float from)
            {
                this->instance().setFromValue(from);
                return this->builder();
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the @c valueChanged(float) signal with the default
             * connection type Qt::AutoConnection.
             *
             * Example:
             * @snippet tad/examples/controls/slider/src/SliderExamples.cpp slider_valuechanged
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onValueChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(valueChanged(float)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the @c immediateValue(float) signal with the default
             * connection type Qt::AutoConnection.
             *
             * Example:
             * @snippet tad/examples/controls/slider/src/SliderExamples.cpp slider_immediatevaluechanged
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onImmediateValueChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(immediateValueChanged(float)), receiver, method);
                return this->builder();
            }
        };

        /*!
         * @brief Builder for constructing Slider objects
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, Slider>
        {
        public:
            Builder() : TBuilder<Builder, Slider>(new Slider())
            {
            }
        };
        /*!
         * @brief Creates and returns a builder for constructing a %Slider.
         *
         * @return A builder used for constructing a %Slider.
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

QML_DECLARE_TYPE(bb::cascades::Slider)


#endif	// cascades_slider_h

