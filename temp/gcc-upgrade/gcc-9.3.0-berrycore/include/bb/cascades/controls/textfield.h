/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textfield_h
#define cascades_textfield_h

#include <bb/cascades/bbcascades_global.h>
#include <QtCore/QString>
#include <bb/cascades/controls/abstracttextcontrol.h>
#include <bb/cascades/resources/textfieldinputmode.h>
#include <bb/cascades/resources/validationstate.h>
#include <bb/cascades/resources/validationmode.h>
#include <bb/cascades/TextInputProperties>
#include <bb/cascades/TextAutoFit>
#include <bb/cascades/TextEditor>

namespace bb {
    namespace cascades {
    
    class TextFieldPrivate;
    class Container;
    class Validator;
    class TextFieldTextFitProperties;

   /*!
    * 
    * @brief A single-line text control with a button that clears the field.
    *
    * @image html text_field_inactive_active.png Inactive and active text fields
    *
    * A @c TextField may indicate an @c #inputMode that specifies the type of keyboard that is displayed
    * on touch screen devices. For example, the Password input mode enables the masking of characters while
    * the @c %Chat input mode enables the use of emoticons. All the available input modes are defined in 
    * @c TextFieldInputMode.
    *
    * In the following example, one @c %TextField is created for handling an email address
    * and another for a password.
    *
    * @code
    * TextField {
    *     id: email
    *     inputMode: TextFieldInputMode.EmailAddress
    * }
    * TextField {
    *     id: password
    *     inputMode: TextFieldInputMode.Password
    * }
    * @endcode
    *
    * @c %TextField also has an @c #input property, which is a grouped property that's used to
    * specify input properties for the @c %TextField. These properties can determine
    * what text is displayed on the keyboard's 'Submit' button and whether or not spell
    * check should be used to verify the content.
    *
    * Here's an example of how to use @c #input and capture the @c TextInputProperties::submitted() signal,
    * which is emitted when the user presses 'Submit'.
    *
    * @code
    * TextField {
    *     inputMode: TextFieldInputMode.Password
    *     input {
    *         onSubmitted: {
    *             //...Perform action on submission...
    *         }
    *     }
    * }
    * @endcode
    *    
    * The size of the @c %TextField behaves as follows:
    * - By default, the width of the control is adjusted automatically to fill its parent container.
    * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and
    * @c Control::maxWidth properties.
    * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight and
    * @c Control::maxHeight are not used.
    *
    * @xmlonly
    * <apigrouping group="User interface/Text"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT TextField : public AbstractTextControl
    {
    private:
        Q_OBJECT

       /*!
        * @brief The hint text for the @c TextField.
        *
        * The @c %TextField displays this text when there is no input
        * in the field. The hint text should suggest the purpose of the field to the user.
        * For example, if this field were used as a search field in a contacts
        * management application, the phrase "Search contacts" might be appropriate. 
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QString hintText READ hintText WRITE setHintText RESET resetHintText
                   NOTIFY hintTextChanged FINAL)

       /*!
        * 
        * @brief The text input mode for the @c TextField.
        *
        * The example below creates one @c %TextField for entering an email account
        * and another @c %TextField for entering a password.
        * @code
        *
        * TextField {
        *     id: email
        *     inputMode: TextFieldInputMode.EmailAddress
        * }
        * TextField {
        *     id: password
        *     inputMode: TextFieldInputMode.Password
        * }
        * @endcode
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::TextFieldInputMode::Type inputMode READ inputMode WRITE setInputMode
                   RESET resetInputMode NOTIFY inputModeChanged FINAL)

       /*!
        * @brief The visibility of the background.
        *
        * @since BlackBerry 10.0.0
        */         
        Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible
                   RESET resetBackgroundVisible NOTIFY backgroundVisibleChanged FINAL)
                   
       /*!
        * @brief The visibility of the button that clears the @c TextField.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool clearButtonVisible READ isClearButtonVisible WRITE setClearButtonVisible
                   RESET resetClearButtonVisible NOTIFY clearButtonVisibleChanged FINAL)

       /*!
        * @brief Indicates whether or not the @c TextField is highlighted when it has focus.
        *
        * The default value is @c true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool focusHighlightEnabled READ isFocusHighlightEnabled WRITE setFocusHighlightEnabled
                   RESET resetFocusHighlightEnabled NOTIFY focusHighlightEnabledChanged FINAL)

       /*!
        * @brief Text input related properties.
        *
        * This is a grouped property that's used to to specify input properties for the @c TextField,
        * such as what text is displayed on the 'Submit' button on the keyboard and whether 
        * spell check should be used to verify the content.        
        *
        * In this example, the the word "Connect" is displayed on the virtual keyboard and the @c submitted()
        * signal is captured in order to initiate some sort of task in response. Spell checking is explicitly 
        * enabled and prediction is explicitly disabled for the control.
        *
        * @code
        * TextField {
        *     input {
        *         submitKey: SubmitKey.Connect;
        *
        *         onSubmitted: {
        *             // Perform some sort of action
        *         }
        *         
        *         flags: TextInputFlag.SpellCheck | TextInputFlag.PredictionOff
        *     }
        * }
        * @endcode
        *
        * @see TextInputProperties
        *
        * @xmlonly
        * <qml>
        * <property groupedProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::TextInputProperties* input READ input FINAL)

       /*!
        * @brief Editor for selection and text manipulation.
        *
        * Holds properties and operations related to text selection and manipulation.
        *
        * @see TextEditor
        *
        * @xmlonly
        * <qml>
        * <property groupedProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::TextEditor* editor READ editor FINAL)

        /*!
         * @brief The autofit mode.
         *
         * Auto fit mode as defined in @c TextAutoFit.
         *
         * The default value is @c TextAutoFit::Default
         *
         * If @c TextAutoFit::FitToBounds is used together with @c TextFieldTextFitProperties::minFontSizeValue
         * and/or @c TextFieldTextFitProperties::maxFontSizeValue then the text will fit as much
         * as minimum and maximum font size constraints allow it to do.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::TextAutoFit::Type autoFit
                   READ autoFit WRITE setAutoFit NOTIFY autoFitChanged RESET resetAutoFit FINAL)

      /*!
       * @brief The Validator property.
       *
       * Contains a Validator object for the validation of the Control.
       *
       * The default value is Null.
       *
       * @see bb::cascades::Validator
       *
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bb::cascades::Validator* validator
                 READ validator WRITE setValidator NOTIFY validatorChanged RESET resetValidator FINAL)

      /*!
       * @brief Specifies maximum length of text.
       *
       * The @c maximumLength is a positive value used to limit the number of
       * characters allowed in a text control.
       *
       * The default @c %maximumLength is INT_MAX, meaning there is no limit set.
       * Although there is no limit set, the actual limit is a large finite value and is device dependent.
       *
       * The following example sets a @c %maximumLength of @c 10 for a @c TextField:
       *
       * @code
       * TextField {
       *    maximumLength: 10
       * }
       * @endcode
       *
       * @since BlackBerry 10.2.0
       */
      Q_PROPERTY(int maximumLength
                 READ maximumLength
                 WRITE setMaximumLength
                 RESET resetMaximumLength
                 NOTIFY maximumLengthChanged
                 REVISION 2
                 FINAL)

      /*!
       * @brief @c TextField text fit related properties.
       *
       * Specifies how the @c TextField content adapts its size to the @c TextField size
       *
       * @code
       * TextField {
       *     textFit {
       *        minFontSizeValue: 3
       *        maxFontSizeValue: 10
       *     }
       * }
       * @endcode
       *
       * @xmlonly
       * <qml>
       * <property groupedProperty="yes"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.2.0
       */
      Q_PROPERTY(bb::cascades::TextFieldTextFitProperties* textFit READ textFit REVISION 2 FINAL);


    public:
       /*!
        * @brief Constructs a @c TextField and specifies the parent container.
        *
        * The ownership of the button is transferred to the parent if a parent is specified.
        *
        * @param parent The parent container or 0. This parameter is optional. 
        * The default is 0 if you don't specify a parent.
        *
        * @since BlackBerry 10.0.0
        */
        explicit TextField(Container * parent = 0);        
        
       /*!
        * @brief Returns the hint text.
        *
        * @return The hint text.
        *
        * @since BlackBerry 10.0.0
        */
        const QString hintText() const;
        
       /*!
        * @brief Sets the hint text.
        *
        * The default hint text is empty string.
        *
        * @param hintText The text to use as a hint.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setHintText(const QString &hintText);
        
       /*!
        * @brief Resets the hint text to its default value.  
        *
        * By default the hint text is set to a localized string, "Enter text" in english.
        * Note that the string will not be updated until the @c hintTextChanged signal is emitted.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetHintText();

        /*!
         * @brief Set the text input mode.
         *
         * @param inputMode The text input mode to use.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setInputMode(bb::cascades::TextFieldInputMode::Type inputMode);

        /*!
         * @brief Returns the text input mode.
         *
         * @return The text input mode
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextFieldInputMode::Type inputMode() const;

        /*!
         * @brief Resets the text input mode to the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetInputMode();

       /*!
        * @brief Indicates whether the background is visible.
        *
        * @return @c true if background is visible, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isBackgroundVisible() const;
        
       /*!
        * @brief Specifies whether the background should be visible.
        *
        * @param backgroundVisible @c true if the background should be visible, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setBackgroundVisible(bool backgroundVisible);
        
       /*!
        * @brief Resets the visibility of the background visible to the default value.
        *
        * By default, the background is visible.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetBackgroundVisible();

       /*!
        * @brief Indicates whether the button that clears the @c TextField is visible.
        *
        * @return @c true if clear button is visible, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isClearButtonVisible() const;
        
       /*!
        * @brief Specifies the visibility of the button that clears the @c TextField.
        *
        * The button is only visible if the @c %TextField is enabled, there is 
        * input text in the field, and the @c %TextField has focus.
        *
        * @param clearButtonVisible @c true if clear button should be visible, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setClearButtonVisible(bool clearButtonVisible);
        
       /*!
        * @brief Resets the visibility of the button that clears the @c TextField to the default value. 
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetClearButtonVisible();       

       /*!
        * @brief Returns whether the @c TextField is highlighted when focused.
        *
        * @return @c true if the focus highlight is shown, otherwise @c false.
        *
        * @since BlackBerry 10.0.0
        */
        bool isFocusHighlightEnabled() const;
        
       /*!
        * @brief Sets whether to highlight the text when the @c TextField is focused.
        *
        * @param focusHighlightEnabled @c true if the focus highlight should be shown, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setFocusHighlightEnabled(bool focusHighlightEnabled);
        
       /*!
        * @brief Resets the focus highlight to be shown when the @c TextField is focused.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetFocusHighlightEnabled();

        /*!
         * @brief Returns the text input properties for this @c TextField.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextInputProperties* input() const;

        /*!
         * @brief Returns the text editor for this @c TextField.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextEditor* editor() const;

        /*!
         * @brief Sets the text auto fit mode.
         *
         * @param autoFit The auto fit mode.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setAutoFit(bb::cascades::TextAutoFit::Type autoFit);

        /*!
         * @brief Returns the text auto fit mode.
         *
         * @return The auto fit mode if set, otherwise @c TextAutoFit::Default will be returned.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextAutoFit::Type autoFit() const;

        /*!
         * @brief Resets the @c #autoFit property to its default value.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void resetAutoFit();

        /*!
         * @brief Sets the validator property.
         *
         * @param validator The Validator object.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setValidator(bb::cascades::Validator* validator);

        /*!
         * @brief Returns the Validator object.
         *
         * @return The the @c validator object if set, otherwise @c null will be returned.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::Validator* validator() const;

        /*!
         * @brief Resets the @c #validator to its default value.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetValidator();

        /*!
         * @brief Returns the maximum allowed number of characters.
         *
         * @return Maximum allowed number of characters.
         *
         * @since BlackBerry 10.2.0
         */
        int maximumLength() const;

        /*!
         * @brief Sets the maximum allowed number of characters.
         *
         * The @c maximumLength is a positive value used to limit the number
         * of characters allowed in a text control. This function
         * will emit the @c maximumLengthChanged() signal.
         *
         * @param maximumLength The number of allowed characters.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_SLOT void setMaximumLength(int maximumLength);

        /*!
         * @brief Resets the @c maximumLength to the default value.
         *
         * The default @c maximumLength is INT_MAX, meaning there is no limit set.
         * Although there is no limit set, the actual limit is a large finite value and is device dependent.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_SLOT void resetMaximumLength();

        /*!
         * @brief Returns the @c bb::cascades::TextFieldTextFitProperties
         *
         * @since BlackBerry 10.2.0
         */
        bb::cascades::TextFieldTextFitProperties* textFit() const;



    Q_SIGNALS:

       /*!
        * @brief Emitted while the user is entering characters.
        *
        * @param text The text in the field.
        *
        * @since BlackBerry 10.0.0
        */
        void textChanging(const QString text);

       /*!
        * @brief Emitted when the visibility of the button that clears the field changes.
        *
        * @param clearButtonVisible @c true if clear button is visible, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void clearButtonVisibleChanged(bool clearButtonVisible);

       /*!
        * @brief Emitted when the visibility of the background changes.
        *
        * @param backgroundVisible @c true if background is visible, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void backgroundVisibleChanged(bool backgroundVisible);

       /*!
        * @brief Emitted when focus highlight is enabled or disabled.
        *
        * @param focusHighlightEnabled @c true if the focus highlight should be shown, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void focusHighlightEnabledChanged(bool focusHighlightEnabled);

       /*!
        * @brief Emitted when hint text changes.
        *
        * @param hintText The hint text.
        *
        * @since BlackBerry 10.0.0
        */
        void hintTextChanged(const QString hintText);   

       /*!
        * @brief Emitted when text input mode changes.
        *
        * @note Due to a work around for a Qt Core issue with accessing enums from QML,
        * the argument of this signal doesn't follow the usual naming convention for signals. 
        * Typically, signal arguments are named to match the associated property's name.
        * In this case, you must use the object's property to access the current 
        * property value instead of the signal argument to avoid runtime errors 
        * (i.e. use @c inputMode instead of @c newInputMode).
        *
        * @param newInputMode The text input mode.
        *
        * @since BlackBerry 10.0.0
        */
        void inputModeChanged(bb::cascades::TextFieldInputMode::Type newInputMode);

       /*!
        * @brief Emitted when auto fit mode has been changed.
        *
        * @param newAutoFit The new auto-fit mode.
        *
        * @since BlackBerry 10.0.0
        */
        void autoFitChanged(bb::cascades::TextAutoFit::Type newAutoFit);

        /*!
         * @brief Emitted when the Validator object changes.
         *
         * @param validator The new Validator object.
         *
         * @since BlackBerry 10.1.0
         */
        void validatorChanged(bb::cascades::Validator* validator);

        /*!
         * @brief Emitted when the maximum length has changed.
         *
         * @param maximumLength The new maximum length.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        void maximumLengthChanged(int maximumLength);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TextField)
        Q_DISABLE_COPY(TextField)
        /*! @endcond */
       
    public:
        /*! @cond PRIVATE */
        typedef TextField ThisClass;
        typedef AbstractTextControl BaseClass;
        /*! @endcond */
        
       /*!       
        * @brief A builder template for constructing a @c TextField.
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
            * @copydoc bb::cascades::TextField::setHintText(const QString &)
            */
            BuilderType& hintText(const QString &hintText)
            {
                this->instance().setHintText(hintText);
                return this->builder();
            }
            
           /*!
            * @copydoc bb::cascades::TextField::setBackgroundVisible(bool)
            */
            BuilderType& backgroundVisible(bool backgroundVisible)
            {
                this->instance().setBackgroundVisible(backgroundVisible);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextField::setClearButtonVisible(bool)
            */
            BuilderType& clearButtonVisible(bool clearButtonVisible)
            {
                this->instance().setClearButtonVisible(clearButtonVisible);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextField::setFocusHighlightEnabled(bool)
            */
            BuilderType& focusHighlightEnabled(bool focusHighlightEnabled)
            {
                this->instance().setFocusHighlightEnabled(focusHighlightEnabled);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextField::setInputMode(bb::cascades::TextFieldInputMode::Type)
            */
            BuilderType& inputMode(bb::cascades::TextFieldInputMode::Type inputMode)
            {
                this->instance().setInputMode(inputMode);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextInputProperties::setSubmitKey(bb::cascades::SubmitKey::Type)
            */
            BuilderType& submitKey(bb::cascades::SubmitKey::Type submitKey)
            {
                this->instance().input()->setSubmitKey(submitKey);            
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextInputProperties::setSubmitKeyFocusBehavior(bb::cascades::SubmitKeyFocusBehavior::Type)
            */
            BuilderType& submitKeyFocusBehavior(bb::cascades::SubmitKeyFocusBehavior::Type submitKeyFocusBehavior)
            {
                this->instance().input()->setSubmitKeyFocusBehavior(submitKeyFocusBehavior);
                return this->builder();
            }
           /*!
            * @brief A convenience method for connecting passed receiver object's slot to
            * the text input properties submitted() signal of the @c TextField with the default connection
            * type Qt::AutoConnection.
            *
            * If @c QObject::connect() fails an assert is raised.
            * If receiver parameter is @c 0 this method has no effect.
            *
            * Example of connecting @c onSubmitted() slot in pMyObject to the input
            * properties @c onSubmitted() signal:
            * @code
            * TextField *pTextField = TextField::create()
            *     .onSubmitted(pMyObject, SLOT(onSubmitted()));
            * @endcode
            *
            * @param receiver a non-@c null receiver object
            * @param method a non-@c null name of the slot in the receiver object to connect to
            *
            * @see TextInputProperties::Submitted(bb::cascades::AbstractTextControl*)
            * @see QObject::connect(const QObject * sender,
            *                       const char * signal, const char * method,
            *                       Qt::ConnectionType type)
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& onSubmitted(const QObject* receiver, const char *method)
            {
                if (receiver) {
                    bool res = receiver->connect(this->instance().input(), SIGNAL(submitted(bb::cascades::AbstractTextControl*)), method);
                    Q_ASSERT(res);
                    Q_UNUSED(res);
                }
                return this->builder();
            }   
          
            /*!
             * @brief Set input flags.
             *
             *@param flags The input flags to set.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& inputFlags(bb::cascades::TextInputFlag::Types flags)
            {
              this->instance().input()->setFlags(flags);
              return this->builder();
            }
            /*!
             * @copydoc bb::cascades::TextField::setValidator(bb::cascades::Validator*)
             */
             BuilderType& validator(bb::cascades::Validator* validator)
             {
                 this->instance().setValidator(validator);
                 return this->builder();
             }

           /*!
            * @copydoc bb::cascades::TextField::setMaximumLength(int)
            */
            BuilderType& maximumLength(int maximumLength)
            {
                this->instance().setMaximumLength(maximumLength);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextFitProperties::setMinFontSizeValue(float)
            */
            BuilderType& minFontSize(float minFontSizeValue)
            {
                this->instance().textFit()->setMinFontSizeValue(minFontSizeValue);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextFitProperties::setMaxFontSizeValue(float)
            */
            BuilderType& maxFontSize(float maxFontSizeValue)
            {
                this->instance().textFit()->setMaxFontSizeValue(maxFontSizeValue);
                return this->builder();
            }
        };

       /*!      
        * @brief A concrete builder class for constructing a @c TextField.    
        *
        * @since BlackBerry 10.0.0        
        */
        class Builder : public TBuilder<Builder, TextField>
        {
        public:
            explicit Builder(Container *parent = 0) : TBuilder<Builder, TextField>(new TextField(parent))
            {
            }
        };

       /*!
        * Constructs a builder used to construct a @c TextField.
        *
        * @return A builder used to construct a @c %TextField.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create(Container *parent = 0)
        {
            return Builder(parent);
        }
    };
}
}
QML_DECLARE_TYPE(bb::cascades::TextField)

#endif // cascades_textfield_h

