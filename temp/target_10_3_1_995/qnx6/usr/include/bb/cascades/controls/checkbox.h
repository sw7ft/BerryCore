/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_checkbox_h
#define cascades_checkbox_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstracttogglebutton.h>

namespace bb {
  namespace cascades {

    class CheckBoxPrivate;
    class Container;

   /*!
    * @brief A checkbox control with two states: checked or unchecked. 
    *
    * The checkbox can also have optional text beside it. You can use this text to describe the purpose
    * of the checkbox or the option that it represents.
    *
    * To toggle the state of a checkbox, the user can touch anywhere inside the control, including its text.
    *
    * The visual appearance of the checkbox is predefined and cannot be changed. The optional text is
    * always left-aligned and has predefined font, font size, and color. The checkbox itself is right-aligned.
    *
    * @image html checkbox.png Checkbox in its different layouts and states.
    *
    * Here's how to create a checkbox and set the @c text property in C++:
    *
    * @snippet tad/examples/controls/checkbox/src/CheckBoxExamples.cpp checkbox1
    *
    * Here's how to use the builder pattern to create a checkbox in C++:
    *
    * @snippet tad/examples/controls/checkbox/src/CheckBoxExamples.cpp checkbox2
    *
    * Here's how to create a checkbox in QML:
    * 
    * @snippet tad/examples/controls/checkbox/assets/main.qml checkbox_qml
    *
    * The size of the checkbox behaves as follows:
    * - If there is no text beside the checkbox (the @c text property is @c null), the width is fixed and
    *   the properties @c Control::preferredWidth, @c Control::minWidth, and @c Control::maxWidth are not used.
    * - If there is text beside the checkbox (the @c text property is not @c null), the default behavior
    *   of the width is to fill the width of the parent. The width also has a device-dependent minimum
    *   limit to ensure that at least a small portion of text along with the checkbox is shown when layout
    *   space is limited.
    * - The height is fixed and the properties @c Control::preferredHeight, @c Control::minHeight, and
    *   @c Control::maxHeight are not used.
    * 
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT CheckBox : public AbstractToggleButton
    {
    private:
      Q_OBJECT

      /*!
       * @brief A text string to display next to the checkbox.
       *
       * The default value is @c QString::Null, indicating that no text is set.
       *
       * ADDED as response to comment on how long the text can be in a checkbox
       * If the length of the text exceeds the width available to the checkbox, the text is
       * truncated.
       * /ADDED
       *
       * @since BlackBerry 10.0.0
       */
        Q_PROPERTY(QString text READ text WRITE setText
                  RESET resetText NOTIFY textChanged FINAL)

    public:
      /*!
       * @brief Constructs a @c %CheckBox with the specified parent container.
       *
       * If the specified parent is not @c 0, the ownership of the constructed checkbox
       * is transferred to the parent.
       *
       * @param parent The parent container, or @c 0. This parameter is optional.          
       * The default is 0 if you don't specify a parent.
       *
       * @since BlackBerry 10.0.0
       */
      explicit CheckBox(Container * parent = 0);

      /*!
       * @brief Destructs this @c %CheckBox.
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~CheckBox();

      /*!
       * @brief Returns the text that is displayed beside this @c %CheckBox.
       *
       * @return A string that represents the checkbox text, or @c QString::Null if no
       * text is set.
       *
       * @since BlackBerry 10.0.0
       */
      QString text() const;

      /*!
       * @brief Sets the text to display beside this @c %CheckBox.
       *
       * When the text is set, the @c %CheckBox resizes itself to fill the width of the parent. 
       * The text is left-aligned, and as the checkbox visual is right-aligned this might introduce 
       * empty space between the text and the checkbox visual itself, as it will always fill out as
       * much space at it gets.
       *
       * The width also has a device-dependent minimum limit to ensure that at least a
       * small portion of text along with the checkbox is shown when layout space is limited.
       *
       * @param text A text string to set as the checkbox text, or @c QString::Null to display
       * no text.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setText(const QString & text);

      /*!
       * @brief Resets the text for this @c %CheckBox to @c QString::Null.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetText();

    Q_SIGNALS:
      /*!
       * @brief Emitted when the text beside this @c %CheckBox changes.
       *
       * @param text The new text string for this @c %CheckBox, or @c QString::Null if
       * no text is set.
       *
       * @since BlackBerry 10.0.0
       */
      void textChanged(QString text);

    private:
      Q_DECLARE_PRIVATE(CheckBox)
        Q_DISABLE_COPY(CheckBox)

        /*! @cond PRIVATE */
        typedef CheckBox ThisClass;
        typedef AbstractToggleButton BaseClass;
        /*! @endcond */

    public:
      /*!
       * @brief A builder template for constructing a @c %CheckBox.
       *
       * See @c CheckBox::create() for getting a concrete builder for constructing a @c %CheckBox.
       *
       * @since BlackBerry 10.0.0
       */ 
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
      protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
      public:

          /*!
           * @brief Sets the text for the @c %CheckBox.
           *
           * @param text The text string to set for the checkbox, or @c QString::Null to display
           * no text on the checkbox.
           *
           * @since BlackBerry 10.0.0
           */
          BuilderType& text(const QString &text) {
              this->instance().setText(text);
              return this->builder();
          }

      };

      /*!
       * @brief A concrete builder class for constructing a @c %CheckBox.
       *
       * See @c CheckBox::create() for getting a concrete Builder for constructing a @c %CheckBox.
       *
       * @since BlackBerry 10.0.0
       */ 
      class Builder : public TBuilder<Builder, CheckBox>
      {
      public:
        explicit Builder() : TBuilder<Builder, CheckBox>(new CheckBox()) {}
      };

      /*!
       * @brief Creates and returns a builder for constructing a @c %CheckBox.
       *
       * @snippet tad/examples/controls/checkbox/src/CheckBoxExamples.cpp checkbox2
       *
       * @return A builder for constructing a @c %CheckBox.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create()
      {
        return Builder();
      }

      /*!
       * @brief Creates and returns a builder for constructing a @c %CheckBox with text.
       *
       * Using the builder to create a @c %CheckBox:
       * 
       * @snippet tad/examples/controls/checkbox/src/CheckBoxExamples.cpp checkbox3
       *
       * This builder is a convenience constructor for creating a @c %CheckBox with text. This
       * is equivalent to the following:
       *
       * @snippet tad/examples/controls/checkbox/src/CheckBoxExamples.cpp checkbox2
       *
       * @param text A text string that represents the text to display beside the checkbox,
       * or @c QString::Null to display no text on the checkbox.
       * 
       * @return A Builder used to create a checkbox with text.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create(const QString & text) {
          return Builder().text(text);
      }

    };
  }
}

QML_DECLARE_TYPE(bb::cascades::CheckBox)

#endif
