/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstracttextcontrol_h
#define cascades_abstracttextcontrol_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/resources/color.h>
#include <bb/cascades/resources/textstyle.h>
#include <bb/cascades/resources/textstyledefinition.h>
#include <bb/cascades/resources/textalign.h>
#include <bb/cascades/controls/textcontentproperties.h>
#include <bb/cascades/controls/textformat.h>

namespace bb {
    namespace cascades {
    
    class AbstractTextControlPrivate;
    class Container;
    class ActiveTextHandler;

   /*!
    * 
    * @brief Abstract base class for all text controls.
    *
    * Exposes common properties for text controls such as the text
    * that is displayed and the @c TextStyleDefintition, which defines how a text node
    * is rendered.
    *
    * You can set the text for a control by using the @c setText() method. You can listen to changes to text via the
    * @c textChanged() signal.
    *
    * @xmlonly
    * <apigrouping group="User interface/Text"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT AbstractTextControl: public Control
    {
    private:
        Q_OBJECT
        /*!
        * @brief The actual text displayed by the text control.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QString text READ text WRITE setText RESET resetText NOTIFY textChanged FINAL)
                   
       /*!
        * @brief The handler for interacting with the active text in this Control.
        *
        * Setting this handler allows you to listen on events from active text interaction.
        * For example the @c ActiveTextHandler::triggered() signal is emitted when 
        * active text has been triggered, allowing you to intercept the action taken.
        *
        * @see @c AbstractTextControl::triggered()
        *
        * The default value is @c 0, indicating no %ActiveTextHandler is set.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ActiveTextHandler* activeTextHandler READ activeTextHandler WRITE setActiveTextHandler NOTIFY activeTextHandlerChanged FINAL)

       /*!
        * @brief The @c TextStyleDefinition used to render the text.
        *
        * Each text style has a different set of visual characteristics associated with it, such as font weight and 
        * font style. If set, these values override the default characteristic of controls that they are 
        * applied on. For example, setting @c %fontFamily to "helvetica" in a @c %textStyle overrides the default 
        * system font with a font from the Helvetica family for each text control that has the @c %textStyle applied to it. 
        *
        * @xmlonly
        * <qml>
        * <property groupedProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */         
        Q_PROPERTY(bb::cascades::TextStyleDefinition* textStyle READ textStyle FINAL)

        /*!
        * @brief The @c TextContentProperties is used to enable and disable text features e.g. 
        * emoticon substitution and active text support.
        *
        * @snippet tad/examples/controls/abstracttextcontrol/assets/main.qml abstracttextcontrol_qml1
        *
        * @xmlonly
        * <qml>
        * <property groupedProperty="yes"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */         
        Q_PROPERTY(bb::cascades::TextContentProperties* content READ content FINAL);

       /*!
        * @brief The @c TextFormat decides how the provided text data should be interpreted,
        * e.g as plain text or HTML.
        * The default value of the textFormat property is TextFormat.Auto.
        *
        * @snippet tad/examples/controls/abstracttextcontrol/assets/main.qml abstracttextcontrol_qml2
        *
        *
        * @since BlackBerry 10.0.0
        */       
        Q_PROPERTY(bb::cascades::TextFormat::Type textFormat READ textFormat WRITE setTextFormat RESET resetTextFormat NOTIFY textFormatChanged FINAL);
        
    public:
        virtual ~AbstractTextControl();
        
       /*!
        * @brief Returns the current text for the control.
        *
        * @return The current text.
        *
        * @since BlackBerry 10.0.0
        */
        const QString text() const;
        
       /*!
        * @brief Sets the text for the control.
        *
        * @param text The new text.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setText(const QString &text);
        
        
       /*!
        * @brief Resets the text to the default value to the default as a QString::null
        *
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetText();       
        
        /*!
         * @brief Returns the @c bb::cascades::TextStyleDefinition that's used to render the text.
         *
         * This object is used to customize the app text.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextStyleDefinition* textStyle();

        /*!
         * @brief Returns the @c bb::cascades::TextContentProperties used to enable and disable text features e.g. 
         * emoticon substitution and active text support.
         *
         * @returns The content properties for this text node.
         *
         * @since BlackBerry 10.0.0
         */         
        bb::cascades::TextContentProperties* content();
      
        /*!
         * @brief Return the @c bb:cascades::TextFormat used to decide how the provided text is to be
         * interpreted.
         *
         * @returns The current text format for this text control.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextFormat::Type textFormat() const;
      
        /*!
         * @brief Sets the @c bb:cascades::TextFormat for this text control.
         *
         * Changes this text control's way of interpreting the provided text, i.e.
         * if the text should be interpreted as plain text or HTML.
         *
         * @param textFormat The text format that the text control will use to interpret the provided text.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_SLOT void setTextFormat(bb::cascades::TextFormat::Type textFormat);
      
        /*!
         * @brief Resets the @c format property to the default value of @c bb::cascades::TextFormat::Auto.
         *
         *
         * @since BlackBerry 10.0.0
         */    
        Q_SLOT void resetTextFormat();

       /*!
        *
        * @return The @c ActiveTextHandler that was set or @c 0 if no handler was set.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::ActiveTextHandler* activeTextHandler() const;

        /*!
        * @brief Sets the @c ActiveTextHandler for this @c %Control.
        *
        * The control takes ownership of the @c %ActiveTextHandler object. Once completed, 
        * the @c activeTextHandlerChanged() signal is emitted.
        * The replaced active text handler (if one was set) remains owned by the control.
        *
        * @param activeTextHandler The @c %activeTextHandler to set or @c 0 to remove
        * currently set ActiveTextHandler.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void setActiveTextHandler(bb::cascades::ActiveTextHandler* activeTextHandler);

        /*!
        * @brief Resets the @c activeTextHandler property to the default value of @c 0.
        *
        * Removes the @c ActiveTextHandler from this @c control by resetting it to @c 0.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetActiveTextHandler();
    Q_SIGNALS:
        /*!
        * @brief Emitted when the text changes.
        *
        * Typically, this occurs when a user presses return in a single
        * row text control, or when a multi row text control loses focus.
        *
        * @param text The new text.
         *
         * @since BlackBerry 10.0.0
        */
        void textChanged(QString text);
        
       /*!
        * @brief Emitted when a @c %ActiveTextHandler has been set for the Control.
        *        
        * @param activeTextHandler The @c %ActiveTextHandler that has been set, or @c 0 if it was reset.
        *
        * @since BlackBerry 10.0.0
        */
        void activeTextHandlerChanged(bb::cascades::ActiveTextHandler* activeTextHandler);
      
       /*!
        * @brief Emitted when the @c format property is changed.
        *        
        * @param newTextFormat The @c %bb::cascades::TextFormat that has been set.
        *
        * @since BlackBerry 10.0.0
        */      
        void textFormatChanged(bb::cascades::TextFormat::Type newTextFormat);


    protected:
       /*! @cond PRIVATE */

       /*!
        * Constructs an AbstractTextControl and specifies the parent container.
        * The ownership of the AbstractTextControl is transferred to the parent, if specified.
        *
        * @param _d_ptr The private representation of the object.
        * @param parent The parent container or 0. This parameter is optional. The 
        * default is 0 if you don't specify a parent.
        */
        AbstractTextControl(AbstractTextControlPrivate &_d_ptr, Container *parent = 0);
        
    private:
        Q_DECLARE_PRIVATE(AbstractTextControl)
        Q_DISABLE_COPY(AbstractTextControl)
       /*! @endcond */

   public:
       /*! @cond PRIVATE */
        typedef AbstractTextControl ThisClass;
        typedef Control BaseClass;
        /*! @endcond */
        
       /*!         
        * @brief A builder template for constructing an AbstractTextControl.       
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
            * @copydoc AbstractTextControl::setText()
            */
            BuilderType& text(const QString &text)
            {
                this->instance().setText(text);
                return this->builder();
            }            

           /*!
            * @copydoc AbstractTextControl::setActiveTextHandler()
            */
            BuilderType& activeTextHandler(bb::cascades::ActiveTextHandler* activeTextHandler)
            {
                this->instance().setActiveTextHandler(activeTextHandler);
                return this->builder();
            }            

            /*!
             * @brief Sets a base text style for the text.
             *
             * @param textStyle The textstyle to use as a base.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& textStyle(const TextStyle &textStyle)
            {
                this->instance().textStyle()->setBase(textStyle);
                return this->builder();
            }

            /*!
             * @brief Set content flags.
             *
             * @param flags The content flags to set.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& contentFlags(bb::cascades::TextContentFlag::Types flags)
            {
                this->instance().content()->setFlags(flags);
                return this->builder();
            }
          
           /*!
            * @copydoc AbstractTextControl::setTextFormat()
            */          
            BuilderType& format(bb::cascades::TextFormat::Type textFormat)
            {
              this->instance().setTextFormat(textFormat);
              return this->builder();
            }
        };
    };
}
}


QML_DECLARE_TYPE(bb::cascades::AbstractTextControl)


#endif	// cascades_abstracttextcontrol_h

