/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textarea_h
#define cascades_textarea_h

#include <bb/cascades/bbcascades_global.h>
#include <QtCore/QString>
#include <bb/cascades/controls/abstracttextcontrol.h>
#include <bb/cascades/resources/textareainputmode.h>
#include <bb/cascades/resources/textareascrollmode.h>
#include <bb/cascades/TextInputProperties>
#include <bb/cascades/TextEditor>

namespace bb {
    namespace cascades {
    
    class TextAreaPrivate;
    class Container;
    class AbstractTextFilter;
    class TextAreaAutoSizeProperties;
    class TextAreaTextFitProperties;

   /*!
    *
    * @brief A multi-line text control for displaying and editing text.
    *
    * @image html textarea_example.png
    *
    * You can specify the @c TextAreaInputMode that defines the behavior of a @c TextArea. 
    * Different modes offer different functionality, such as displaying different character sets 
    * on the virtual keyboard or enabling emoticons in the @c %TextArea when text is being entered.
    * See TextAreaInputMode
    *
    * The following example creates a @c %TextArea with an @c inputMode of @c Chat:
    *
    * @code
    *
    * TextArea {
    *     id: chat
    *     inputMode: TextAreaInputMode.Chat
    * }
    * @endcode
    *
    * The size of the @c %TextArea behaves as follows:
    * - By default, the width of the control is adjusted automatically to fill its parent container.
    * - By default, the height of the control is adjusted automatically to fit all the lines of text.
    * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and @c Control::maxWidth properties.
    * - The height is is adjustable using the @c Control::preferredHeight, @c Control::minHeight and @c Control::maxHeight properties.
    * - The height is never less than is required to fit one line of text.
    *
    * @xmlonly
    * <apigrouping group="User interface/Text"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT TextArea : public AbstractTextControl
    {
    private:
        Q_OBJECT
        
       /*!
        * @brief The mutability of the text.
        *
        * When editable, a @c TextArea has a border 
        * to indicate that the text is editable. A @c %TextArea is editable by default.
        * 
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool editable READ isEditable WRITE setEditable RESET resetEditable NOTIFY editableChanged FINAL)
        
       /*!
        * 
        * @brief The text input mode for the @c TextArea.
        *
        * See TextAreaInputMode
        *
        * The default value is @c Default
        *
        * The following example creates a @c %TextArea with an @c inputMode of @c Chat:
        * @code
        *
        * TextArea {
        *     id: chat
        *     inputMode: TextAreaInputMode.Chat
        * }
        * @endcode
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */         
        Q_PROPERTY(bb::cascades::TextAreaInputMode::Type inputMode READ inputMode WRITE setInputMode
                   RESET resetInputMode NOTIFY inputModeChanged FINAL)

       /*!
        * @brief The hint text for a @c TextArea.
        *
        * The @c %TextArea displays this text when there is no input 
        * in the area. The hint text should suggest 
        * the purpose of the area to the user. For example, if this control is 
        * used as a search box in a contacts management application, the phrase
        * "Search contacts" might be appropriate.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QString hintText READ hintText WRITE setHintText RESET resetHintText NOTIFY hintTextChanged FINAL)

       /*!
        * @brief The visibility of the background.
        *
        * The default value is @c true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible
                   RESET resetBackgroundVisible NOTIFY backgroundVisibleChanged FINAL)

       /*!
        * @brief Indicates whether or not the @c TextArea is highlighted when it has focus.
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
        * Holds properties related to text input.
        *
        * The following example creates one @c TextArea where the submit key on the virtual keyboard 
        * is set to "Connect". A slot is also connected to the @c %submitted signal
        * that is emitted when the submit key is pressed. Spell checking is 
        * explicitly enabled and prediction is explicitly disabled for the control.
        *
        *
        * @code
        * TextArea {
        *     input {
        *         submitKey: SubmitKey.Connect
        *
        *         onSubmitted: {
        *             // Submit key was pressed
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
        * 
        * @brief The scroll mode in the vertical direction for the @c TextArea
        *
        * See TextAreaScrollMode
        *
        * The default value is @c Default
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */         
        Q_PROPERTY(bb::cascades::TextAreaScrollMode::Type scrollMode READ scrollMode WRITE setScrollMode
                   RESET resetScrollMode NOTIFY scrollModeChanged FINAL)

        /*!
         * @brief Specifies maximum length of text.
         *
         * The @c maximumLength is a positive value used to limit the number of
         * characters allowed in a text control.
         *
         * The default @c %maximumLength is INT_MAX, meaning there is no limit set.
         * Although there is no limit set, the actual limit is a large finite value and is device dependent.
         *
         * The following example sets a @c %maximumLength of @c 10 for a @c TextArea:
         *
         * @code
         * TextArea {
         *    maximumLength: 10
         * }
         * @endcode
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(int maximumLength
                   READ maximumLength
                   WRITE setMaximumLength
                   RESET resetMaximumLength
                   NOTIFY maximumLengthChanged
                   FINAL)

      /*!
       * @brief The text filter for the @c TextArea.
       *
       * A filter can be applied to the text in the area to ensure 
       * that all new lines are ignored. 
       * See SingleLineTextFilter
       *
       * The default value of this property is @c 0.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(bb::cascades::AbstractTextFilter* textFilter READ textFilter WRITE setTextFilter RESET resetTextFilter
                 NOTIFY textFilterChanged FINAL);

       /*!
        * @brief Specifies how the control adapts its size to the content.
        *
        * Preferred, min and max sizes (if set) have higher priority than the values set in @c %autoSize.
        *
        * @code
        * TextArea {
        *     autoSize {
        *        maxLineCount: 3
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
        Q_PROPERTY(bb::cascades::TextAreaAutoSizeProperties* autoSize READ autoSize REVISION 2 FINAL);

       /*!
        * @brief @c TextArea text fit related properties.
        *
        * Specifies how the @c TextArea content adapts its size to the @c TextArea size
        *
        * @code
        * TextArea {
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
        Q_PROPERTY(bb::cascades::TextAreaTextFitProperties* textFit READ textFit REVISION 2 FINAL);

    public:
       /*!
        * @brief Constructs a @c TextArea and specifies the parent container.
        *
        * The ownership of the @c %TextArea is transferred to the parent if a parent is specified.
        *
        * @param parent The parent container or @c 0. This parameter is optional.
        * The default is @c 0 if you don't specify a parent.
        *
        * @since BlackBerry 10.0.0
        */
        explicit TextArea(Container* parent = 0);
        
       /*!
        * @brief Indicates whether the @c TextArea is editable.
        *
        * @return @c true if text is editable, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isEditable() const;
        
       /*!
        * @brief Sets whether the @c TextArea is editable.
        *
        * @param editable @c true if text should be editable, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setEditable(bool editable);
        
       /*!
        * @brief Resets the @c editable property to its default value.
        *
        * A @c TextArea is editable by default.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetEditable();
        
        /*!
        * @brief Returns the hint text.
        *
        * @return The hint text, if set.
         *
         * @since BlackBerry 10.0.0
        */
        const QString hintText() const;
        
       /*!
        * @brief Sets the hint text.
        *
        * The default hint text is empty string.
        *
        * @param hintText The new hint text.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setHintText(const QString &hintText);
        
       /*!
        * @brief Resets the hint text to its default value.
        *
        * By default the hint text is set to a localized string, "Enter text" in English.
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
        Q_SLOT void setInputMode(bb::cascades::TextAreaInputMode::Type inputMode);

        /*!
         * @brief Returns the text input mode.
         *
         * @return The text input mode
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextAreaInputMode::Type inputMode() const;

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
        * @brief Sets the visibility of the background.
        *
        * @param backgroundVisible @c true to enable the visibility of the background, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setBackgroundVisible(bool backgroundVisible);
        
       /*!
        * @brief Resets the visibility of the background to its default value.
        *
        * By default, the background is visible.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetBackgroundVisible();

       /*!
        * @brief Returns if the @c TextArea is highlighted when focused.
        *
        * @return @c true if the focus highlight is shown, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isFocusHighlightEnabled() const;
        
       /*!
        * @brief Sets whether to highlight the text when the @c TextArea is focused.
        *
        * @param focusHighlightEnabled @c true if the focus highlight should be shown, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setFocusHighlightEnabled(bool focusHighlightEnabled);
        
       /*!
        * @brief Resets the focus highlight to be shown when the @c TextArea is focused.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetFocusHighlightEnabled();

        /*!
         * @brief Returns the text input properties for this @c TextArea.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextInputProperties* input() const;

        /*!
         * @brief Returns the text editor this @c TextArea.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextEditor* editor() const;

        /*!
         * @brief Set the vertical scroll mode.
         *
         * @param scrollMode The vertical scroll mode to use.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setScrollMode(bb::cascades::TextAreaScrollMode::Type scrollMode);

        /*!
         * @brief Resets the vertical scroll mode to the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetScrollMode();

        /*!
         * @brief Returns the vertical scroll mode.
         *
         * @return The vertical scroll mode
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextAreaScrollMode::Type scrollMode() const;

        /*!
         * @brief Returns the maximum allowed number of characters.
         *
         * @return maximum allowed number of characters.
         *
         *
         * @since BlackBerry 10.0.0
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
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMaximumLength(int maximumLength);

        /*!
         * @brief Resets the @c maximumLength to the default value.
         *
         * The default @c maximumLength is INT_MAX, meaning there is no limit set.
         * Although there is no limit set, the actual limit is a large finite value and is device dependent.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMaximumLength();

        /*!
         * @brief Set the text filter.
         *
         * Ownership will always be transferred to the @c TextArea.
         * If @c %TextArea already has a @c textFilter, the existing @c %textFilter will still be owned by @c %TextArea
         * and destroyed when @c %TextArea is destroyed.
         * If operation was successful, the @c textFilterChanged() signal is emitted.
         *
         * @param textFilter The text filter that should be applied to the text. 
         * Can be @c 0 to remove @c %textFilter (existing content will still be owned by @c %TextArea).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTextFilter(bb::cascades::AbstractTextFilter* textFilter);

        /*!
         * @brief Resets the text filter to the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTextFilter();

        /*!
         * @brief Returns the text filter set on the @c TextArea.
         *
         * @return The text filter set on the @c %TextArea
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::AbstractTextFilter *textFilter() const;

        /*!
         * @brief Returns the @c bb::cascades::TextAreaAutoSizeProperties
         *
         * @since BlackBerry 10.2.0
         */
        bb::cascades::TextAreaAutoSizeProperties* autoSize() const;

        /*!
         * @brief Returns the @c bb::cascades::TextAreaTextFitProperties
         *
         * @since BlackBerry 10.2.0
         */
        bb::cascades::TextAreaTextFitProperties* textFit() const;

    Q_SIGNALS:
       
       /*!
        * @brief Emitted when the user enters a character in a @c TextArea.
        *
        * @param text The string in the @c %TextArea.
        *
        * @since BlackBerry 10.0.0
        */
        void textChanging(const QString text);

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
        * @brief Emitted when the @c editable property changes.
        *
        * @param editable @c true if @c TextArea is editable, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void editableChanged(bool editable);
        
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
        void inputModeChanged(bb::cascades::TextAreaInputMode::Type newInputMode);  

       /*!
        * @brief Emitted when scroll mode changes.
        *
        * @note Due to a work around for a Qt Core issue with accessing enums from QML,
        * the argument of this signal doesn't follow the usual naming convention for signals. 
        * Typically, signal arguments are named to match the associated property's name.
        * In this case, you must use the object's property to access the current 
        * property value instead of the signal argument to avoid runtime errors 
        * (i.e. use @c scrollMode instead of @c newScrollMode).
        *
        * @param newScrollMode The vertical scroll mode.
        *
        * @since BlackBerry 10.0.0
        */
        void scrollModeChanged(bb::cascades::TextAreaScrollMode::Type newScrollMode);

        /*!
         * @brief Emitted when the maximum length has changed.
         *
         * @param maximumLength The new maximum length.
         *
         * @since BlackBerry 10.0.0
         */
        void maximumLengthChanged(int maximumLength);

        /*!
         * @brief Emitted when the text filter changes.
         *
         * @param textFilter The new text filter.
         *
         * @since BlackBerry 10.0.0
         */
        void textFilterChanged(bb::cascades::AbstractTextFilter *textFilter);

    private:
       /*! @cond PRIVATE */
       /*!
        * @brief Constructs a @c TextArea with a optional parent.
        *
        * If not @c 0, the ownership of the constructed @c %TextArea will be transferred to the parent.
        *
        * @param _d_ptr The private representation of the TextArea.
        * @param parent The parent container or 0. Optional and will default to 0 if not specified.
        */
        Q_DECLARE_PRIVATE(TextArea)
        Q_DISABLE_COPY(TextArea)
       /*! @endcond */
        
    public:        
        /*! @cond PRIVATE */
        typedef TextArea ThisClass;
        typedef AbstractTextControl BaseClass;        
        /*! @endcond */
        
       /*!       
        * @brief A builder template for constructing a @c TextArea.
        *
        * @since BlackBerry 10.0.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {}
            
        public:            
           /*!
            * @copydoc bb::cascades::TextArea::setHintText(const QString &)
            */
            BuilderType& hintText(const QString &hintText)
            {
                this->instance().setHintText(hintText);
                return this->builder();
            }
            
           /*!
            * @copydoc bb::cascades::TextArea::setMaximumLength(int)
            */
            BuilderType& maximumLength(int maximumLength)
            {
                this->instance().setMaximumLength(maximumLength);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextArea::setBackgroundVisible(bool)
            */
            BuilderType& backgroundVisible(bool backgroundVisible)
            {
                this->instance().setBackgroundVisible(backgroundVisible);
                return this->builder();
            }
            

           /*!
            * @copydoc bb::cascades::TextArea::setFocusHighlightEnabled(bool)
            */
            BuilderType& focusHighlightEnabled(bool focusHighlightEnabled)
            {
                this->instance().setFocusHighlightEnabled(focusHighlightEnabled);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextArea::setEditable(bool)
            */
            BuilderType& editable(bool editable)
            {
                this->instance().setEditable(editable);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextArea::setInputMode(bb::cascades::TextAreaInputMode::Type)
            */
            BuilderType& inputMode(bb::cascades::TextAreaInputMode::Type inputMode)
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
            * A convenience method for connecting a passed receiver object's slot to
            * the submitted() signal of a @c TextArea with the default connection
            * type of Qt::AutoConnection.
            *
            * If QObject::connect() fails an assert is raised.
            * If receiver parameter is @c 0 this method has no effect.
            *
            * Example of connecting @c %onSubmitted slot in @c pMyObject to the text input
            * properties @c %onSubmitted signal:
            * @code
            * TextArea *pTextArea = TextArea::create()
            *     .onSubmitted(pMyObject, SLOT(onSubmitted()));
            * @endcode
            *
            * @param receiver a non-@c null receiver object
            * @param method a non-null name of the slot in the receiver object to connect to
            *
            * @see TextInputProperties::submitted(bb::cascades::AbstractTextControl*)
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
             *@param flags The input @c flags to set.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& inputFlags(bb::cascades::TextInputFlag::Types flags)
            {
              this->instance().input()->setFlags(flags);
              return this->builder();
            }

           /*!
            * @brief Sets the scroll mode of this @c TextArea.
            *
            * @param scrollMode The scroll mode to set.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& scrollMode(bb::cascades::TextAreaScrollMode::Type scrollMode) {
                this->instance().setScrollMode(scrollMode);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::TextArea::setTextFilter(bb::cascades::AbstractTextFilter*)
            */
            BuilderType& textFilter(bb::cascades::AbstractTextFilter *textFilter) {
                this->instance().setTextFilter(textFilter);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::TextAreaAutoSizeProperties::setMaxLineCount(int)
             */
            BuilderType& maxLineCount(int maxLineCount)
            {
                this->instance().autoSize()->setMaxLineCount(maxLineCount);
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
        * @brief A builder class for constructing a @c TextArea.
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, TextArea>
        {
        public:
            Builder() : TBuilder<Builder, TextArea>(new TextArea())
            {}
        };

       /*!
        * @brief Creates and returns a builder for constructing a @c TextArea.
        *
        * @return A builder for constructing a @c %TextArea.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::TextArea)

#endif // cascades_textarea_h
