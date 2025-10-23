/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_label_h
#define cascades_label_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstracttextcontrol.h>
#include <bb/cascades/resources/labeltextfitmode.h>

namespace bb {
    namespace cascades {

    class LabelPrivate;
    class Container;
    class LabelAutoSizeProperties;
    class LabelTextFitProperties;

    /*!
     * 
     * @brief A non interactive label with one line of text.
     *
     * @image html label.png Use a Label to add a short text to your app.
     *
     * You can change the text and the text style (such as color and font) by using properties 
     * in @c AbstractTextControl. You can also use @c LabelTextFitMode and @c LabelTextFitProperties
     * to change the auto-fit behavior of text in a @c Label. The @c %LabelTextFitMode class contains
     * a number of enumerated types for the text auto-fit mode, and @c %LabelTextFitProperties allows you to
     * apply or change the text auto-fit mode for a @c %Label.
     *
     * Creating a label in QML:
     *
     * @code
     * Label {
     *     text: "Label"
     * }
     * @endcode
     *
     * Creating a label in C++:
     *
     * @code
     * QString labelText = "Label";
     * Label *label = new Label();
     * label->setText(labelText);
     * @endcode
     *
     * The size of the label behaves as follows:
     * - By default, the width of the control is adjusted automatically to fit the text.
     * - By default, the height of the control is adjusted automatically to fit one line of text.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth 
     * and @c Control::maxWidth properties.
     * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight
     * and @c Control::maxHeight and properties.
     * - The height is never less than is required to fit a single line of text.
     * - For multiline labels @c autoSize property can be used to limit the number of displayed lines
     *
     * @xmlonly
     * <apigrouping group="User interface/Text"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Label : public AbstractTextControl
    {
    private:
        Q_OBJECT

       /*!
        * @brief Allow multiple lines in label
        *
        * If @c true this label will word wrap and handle line breaks, if @c false this label will 
        * be one single line only and any line breaks will be ignored.
        *
        * For multiline labels use @c autoSize property to configure the maximum number of
        * lines displayed by the label.
        *
        * Default value is @c false. 
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool multiline READ isMultiline WRITE setMultiline RESET resetMultiline NOTIFY multilineChanged FINAL);

       /*!
        * @brief Specifies how the control adapts its size to the content.
        *
        * If preferred min or max sizes are set they override the values set in autoSize. 
        *
        * The @c LabelAutoSizeProperties::maxLineCount property only has effect if
        * @c Label's @c multiline property is set to @c true.
        *
        * @code
        * Label {
        *     // The multiline property needs to be set to true in order to wrap the text
        *     // on multiple lines. 
        *     multiline: true
        *
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
        * @since BlackBerry 10.1.0
        */
        Q_PROPERTY(bb::cascades::LabelAutoSizeProperties* autoSize READ autoSize FINAL);

        /*!
        * @brief @c Label text fit related properties.
        *
        * Specifies how the text in a @c Label adapts its size to the @c Label size.
        *
        * @code
        * Label {
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
        Q_PROPERTY(bb::cascades::LabelTextFitProperties* textFit READ textFit REVISION 2 FINAL);

    public:
        /*!
         * @brief Constructs a non interactive label with a parent.
         * If not 0, the ownership of the constructed label will be transfered to the parent.
         *
         * @param parent The parent container or 0. Optional and will default to 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit Label(Container * parent = 0);

        virtual ~Label();

        /*!
        * @brief Indicates whether the label allows multiple lines of text.
        *
        * Default value is @c false.
        *
        * @return @c true if the label allows multiple lines.
         *
         * @since BlackBerry 10.0.0
        */
        bool isMultiline() const;
        
        /*!
        * @brief Sets whether the label allows multiple lines of text.
        *
        * If @c true, this label will word wrap and handle line breaks, if @c false this label will be one single line only
        * and any line breaks will be ignored.        
        *
        * @param multiline @c true if the label should allow multiple lines, otherwise @c false.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void setMultiline(bool multiline);
        
        /*!
        * @brief Resets @c multiline property to its default value.
        *
        * Default value is @c false.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetMultiline();

       /*!
        * @brief Returns the @c bb::cascades::LabelAutoSizeProperties.
        *
        * @since BlackBerry 10.1.0
        */
        bb::cascades::LabelAutoSizeProperties* autoSize() const;

        /*!
        * @brief Returns the @c bb::cascades::LabelTextFitProperties.
        *
        * @since BlackBerry 10.2.0
        */
        bb::cascades::LabelTextFitProperties* textFit() const;

    Q_SIGNALS:

       /*!
        * @brief Emitted when the @c multiline property changes.
        *
        * @param multiline @c true if label allows multiple lines, otherwise @c false.
        *
        * @since BlackBerry 10.0.0
        */
        void multilineChanged(bool multiline);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(Label)
        Q_DISABLE_COPY(Label)

        typedef Label ThisClass;
        typedef AbstractTextControl BaseClass;
        /*! @endcond */

   public:
      /*!
        * @brief A builder template for constructing a @c Label.
        *
        * See @c Label::create() for getting a concrete Builder for contructing a @c Label.
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
          * @copydoc bb::cascades::Label::setMultiline(bool)
          */
          BuilderType& multiline(bool multiline)
          {
              this->instance().setMultiline(multiline);
              return this->builder();
          }
            
          /*!
           * @copydoc bb::cascades::LabelAutoSizeProperties::setMaxLineCount(int)
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

          /*!
           * @copydoc bb::cascades::LabelTextFitProperties::setMode(bb::cascades::LabelTextFitMode::Type)
           */
          BuilderType& textFitMode(bb::cascades::LabelTextFitMode::Type mode)
          {
            this->instance().textFit()->setMode(mode);
            return this->builder();
          }

        };

      /*!
        * @brief A concrete builder class for constructing a @c Label.
        *
        * See @c Label::create() for getting a concrete Builder for constructing a @c Label.
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Label> 
        {
        public:
            explicit Builder(Container * parent = 0) : TBuilder<Builder, Label>(new Label(parent)) 
            {
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing a @c Label.
         *
         * @return A Builder for constructing a @c Label.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() 
        {
            return Builder();
        }

        /*!
         * @brief Creates and returns a builder for constructing a @c Label with text.
         *
         * @param text A text string.
         * @return A Builder for constructing a @c Label.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(const QString & text) 
        {
            return Builder().text(text);
        }
   };
}
}

QML_DECLARE_TYPE(bb::cascades::Label)

#endif	// cascades_label_h


