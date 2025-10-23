/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_textinputactionitem_h
#define cascades_textinputactionitem_h


#include <QtCore/QString>
#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>
#include <bb/cascades/controls/input/textinputproperties.h>
#include <bb/cascades/controls/textformat.h>
#include <bb/cascades/controls/texteditor.h>

namespace bb {
  namespace cascades {

    class TextInputActionItemPrivate;

    /*!
     * @brief The TextInputActionItem is an ActionIitem that provides a text input
     * control on the ActionBar.
     *
     * Many of the properties inherited from @c AbstractActionItem (like title and image) do not make sense
     * for the TextInputActionItem. Changes to these will be ignored by the TextInputActionItem.
     *
     * @see Page
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT TextInputActionItem : public AbstractActionItem
    {
      Q_OBJECT

    private:
      /*!
       * @brief The actual text displayed in the @c TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(QString text READ text WRITE setText RESET resetText NOTIFY textChanged FINAL)

      /*!
       * @brief The hint text for the @c TextInputActionItem.
       *
       * The @c %TextInputActionItem displays this text when no text has been input.
       * The hint text should suggest the purpose of the text input to the user. For example, if this control is
       * used as a search box in a contacts management application, the phrase
       * "Search contacts" might be appropriate.
       *
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(QString hintText READ hintText WRITE setHintText RESET resetHintText NOTIFY hintTextChanged FINAL)
      
      /*!
       * @brief An optional 'status' text for the @c TextInputActionItem.
       *
       * The @c %TextInputActionItem displays this text when there are other actions visible and the text field
       * has enough text inputed to be moved to a separate row above these.
       *
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(QString status READ status WRITE setStatus RESET resetStatus NOTIFY statusChanged FINAL)

      /*!
       * @brief Text input related properties.
       *
       * Holds properties related to text input.
       *
       * The following example creates one @c TextInputActionItem where the submit key on the virtual keyboard
       * is set to "Connect". A slot is also connected to the @c %submitted signal
       * that is emitted when the submit key is pressed. Spell checking is
       * explicitly enabled and prediction is explicitly disabled for the control.
       *
       *
       * @code
       * TextInputActionItem {
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
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(bb::cascades::TextInputProperties* input READ input FINAL)

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
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(bb::cascades::TextContentProperties* content READ content FINAL);

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
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(bb::cascades::TextEditor* editor READ editor FINAL)

      /*!
       * @brief Specifies maximum length of text.
       *
       * The @c maximumLength is a positive value used to limit the number of
       * characters allowed in a text control.
       *
       * The default @c %maximumLength is INT_MAX, meaning there is no limit set.
       * Although there is no limit set, the actual limit is a large finite value and is device dependent.
       *
       * The following example sets a @c %maximumLength of @c 10 for a @c TextInputActionItem:
       *
       * @code
       * TextInputActionItem {
       *    maximumLength: 10
       * }
       * @endcode
       *
       *
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(int maximumLength
                 READ maximumLength
                 WRITE setMaximumLength
                 RESET resetMaximumLength
                 NOTIFY maximumLengthChanged
                 FINAL)

      /*!
       * @brief The @c TextFormat decides how the provided text data should be interpreted,
       * e.g as plain text or HTML.
       * The default value of the textFormat property is TextFormat.Auto.
       *
       * @snippet tad/examples/controls/abstracttextcontrol/assets/main.qml abstracttextcontrol_qml2
       *
       *
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(bb::cascades::TextFormat::Type textFormat READ textFormat WRITE setTextFormat RESET resetTextFormat NOTIFY textFormatChanged FINAL);

    public:
      /*!
       * Constructs a TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      explicit TextInputActionItem();

      /*!
       * The destructor of the TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      virtual ~TextInputActionItem();

      /*!
       * @brief Returns the current text.
       *
       * @return The current text.
       *
       * @since BlackBerry 10.3.0
       */
      QString text() const;

      /*!
       * @brief Sets the text.
       *
       * @param text The new text.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void setText(const QString &text);


      /*!
       * @brief Resets the text to the default value as a QString::null
       *
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void resetText();

      /*!
       * @brief Returns the hint text.
       *
       * @return The hint text, if set.
       *
       * @since BlackBerry 10.3.0
       */
      QString hintText() const;
      
      /*!
       * @brief Returns the status text.
       *
       * @return The status text, if set.
       *
       * @since BlackBerry 10.3.0
       */
      QString status() const;

      /*!
       * @brief Sets the hint text.
       *
       * @param hintText The new hint text.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void setHintText(const QString &hintText);
      
      /*!
       * @brief Sets the status text.
       *
       * @param statusText The new status text.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void setStatus(const QString &statusText);

      /*!
       * @brief Resets the hint text to its default value.
       *
       * By default the hint text is set to a localized string, "Enter text" in English.
       * Note that the string will not be updated until the @c hintTextChanged signal is emitted.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void resetHintText();
      
      /*!
       * @brief Resets the status text to its default value.
       *
       * By default the status text is an empty string string.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void resetStatus();

      /*!
       * @brief Returns the text input properties for the @c TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      bb::cascades::TextInputProperties* input() const;

      /*!
       * @brief Returns the text editor this @c TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      bb::cascades::TextEditor* editor() const;

      /*!
       * @brief Returns the maximum allowed number of characters.
       *
       * @return maximum allowed number of characters.
       *
       *
       * @since BlackBerry 10.3.0
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
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void setMaximumLength(int maximumLength);

      /*!
       * @brief Resets the @c maximumLength to the default value.
       *
       * The default @c maximumLength is INT_MAX, meaning there is no limit set.
       * Although there is no limit set, the actual limit is a large finite value and is device dependent.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void resetMaximumLength();

      /*!
       * @brief Returns the @c bb::cascades::TextContentProperties used to enable and disable text features e.g.
       * emoticon substitution and active text support.
       *
       * @returns The content properties for this text node.
       *
       * @since BlackBerry 10.3.0
       */
      bb::cascades::TextContentProperties* content();

      /*!
       * @brief Return the @c bb:cascades::TextFormat used to decide how the provided text is to be
       * interpreted.
       *
       * @returns The current text format for this text control.
       *
       * @since BlackBerry 10.3.0
       */
      bb::cascades::TextFormat::Type textFormat() const;

      /*!
       * @brief Sets the @c bb:cascades::TextFormat for the text.
       *
       * Changes the text control's way of interpreting the provided text, i.e.
       * if the text should be interpreted as plain text or HTML.
       *
       * @param textFormat The text format that the text control will use to interpret the provided text.
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void setTextFormat(bb::cascades::TextFormat::Type textFormat);

      /*!
       * @brief Resets the @c format property to the default value of @c bb::cascades::TextFormat::Auto.
       *
       *
       * @since BlackBerry 10.3.0
       */
      Q_SLOT void resetTextFormat();

      /*!
      *
      * @brief Request focus to this text input action item.
      *        If possible, the text input action item will receive focuse.
      *
      * @since BlackBerry 10.3.0
      *
      */
      Q_SLOT void requestFocus();

      /*!
      *
      * @brief Called when the text input action item should lose its focus.
      *
      * @since BlackBerry 10.3.0
      *
      */
      Q_SLOT void loseFocus();

    Q_SIGNALS:
      /*!
       * @brief Emitted when the text changes.
       *
       * Typically, this occurs when the text area loses focus.
       *
       * @param text The new text.
       *
       * @since BlackBerry 10.3.0
       */
      void textChanged(const QString& text);

      /*!
       * @brief Emitted when the user enters a character in the @c TextInputActionItem.
       *
       * @param text The string in the @c %TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      void textChanging(const QString& text);

      /*!
       * @brief Emitted when the hint text has been changed.
       *
       * @param hintText The new hint text.
       *
       * @since BlackBerry 10.3.0
       */
      void hintTextChanged(const QString& hintText);
      
      /*!
       * @brief Emitted when the status text has been changed.
       *
       * @param statusText The new status text.
       *
       * @since BlackBerry 10.3.0
       */
      void statusChanged(const QString& statusText);

      /*!
       * @brief Emitted when the @c format property is changed.
       *
       * @param newTextFormat The @c %bb::cascades::TextFormat that has been set.
       *
       * @since BlackBerry 10.3.0
       */
      void textFormatChanged(bb::cascades::TextFormat::Type newTextFormat);

      /*!
       * @brief Emitted when the maximum length has changed.
       *
       * @param maximumLength The new maximum length.
       *
       * @since BlackBerry 10.3.0
       */
      void maximumLengthChanged(int maximumLength);

    private:
      Q_DECLARE_PRIVATE(TextInputActionItem)
      Q_DISABLE_COPY(TextInputActionItem)

      /*! \cond PRIVATE */
      typedef TextInputActionItem ThisClass;
      typedef AbstractActionItem BaseClass;
      /*! \endcond */

    public:

      /*!
       * A builder template for constructing a TextInputActionItem. To retrieve the builder, call
       * TextInputActionItem::create().
       *
       * @since BlackBerry 10.3.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
      {
      protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}

      public:
       /*!
        * @copydoc bb::cascades::TextInputActionItem::setText(const QString &)
        */
        BuilderType& text(const QString &text)
        {
          this->instance().setText(text);
          return this->builder();
        }

       /*!
        * @copydoc bb::cascades::TextInputActionItem::setHintText(const QString &)
        */
        BuilderType& hintText(const QString &hintText)
        {
          this->instance().setHintText(hintText);
          return this->builder();
        }

        /*!
         * @copydoc bb::cascades::TextInputActionItem::setMaximumLength(int)
         */
        BuilderType& maximumLength(int maximumLength)
        {
          this->instance().setMaximumLength(maximumLength);
          return this->builder();
        }

       /*!
        * @brief Set input flags.
        *
        *@param flags The input @c flags to set.
        *
        * @since BlackBerry 10.3.0
        */
        BuilderType& inputFlags(bb::cascades::TextInputFlag::Types flags)
        {
          this->instance().input()->setFlags(flags);
          return this->builder();
        }

       /*!
        * @brief Set content flags.
        *
        * @param flags The content flags to set.
        *
        * @since BlackBerry 10.3.0
        */
        BuilderType& contentFlags(bb::cascades::TextContentFlag::Types flags)
        {
          this->instance().content()->setFlags(flags);
          return this->builder();
        }

       /*!
        * @copydoc bb::cascades::TextInputActionItem::setTextFormat()
        */
        BuilderType& format(bb::cascades::TextFormat::Type textFormat)
        {
          this->instance().setTextFormat(textFormat);
          return this->builder();
        }

       /*!
        * @brief Set the type of submit key.
        *
        * @param submitKey The type of submit key that should be used.
        *
        * @since BlackBerry 10.3.0
        */
        BuilderType& submitKey(bb::cascades::SubmitKey::Type submitKey)
        {
          this->instance().input()->setSubmitKey(submitKey);
          return this->builder();
        }
      };

      /*!
       * A builder template for constructing a TextInputActionItem. To retrieve the builder, call
       * TextInputActionItem::create().
       *
       * @since BlackBerry 10.3.0
       */
      class Builder : public TBuilder<Builder, TextInputActionItem>
      {
      public:
        explicit Builder() : TBuilder<Builder, TextInputActionItem>(new TextInputActionItem()) {}
      };

      /*! Creates and returns a builder for constructing a TextInputActionItem.
       *
       * Using the builder to create a TextInputActionItem:
       * @code
       * TextInputActionItem* actionItem = TextInputActionItem::create();
       * @endcode
       *
       * @return A builder used for constructing a TextInputActionItem.
       *
       * @since BlackBerry 10.3.0
       */
      static Builder create() {
        return Builder();
      }
    };
  } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::TextInputActionItem)


#endif  // cascades_textinputactionitem_h
