/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textfieldinputmode_h
#define cascades_textfieldinputmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents a text input mode for the @c TextField.
 *
 * The @c %TextFieldInputMode determines how the @c TextField behaves in relation to its text input.
 * Each input mode has a default set of properties that specify what symbols appear on the keyboard and
 * how the input is displayed in the field. For example, the @c Chat mode contains functionality that
 * allows users to specify emoticons that can be rendered on the screen.
 *
 * You can change the default properties for each mode by turning them on or off using
 * @c TextContentFlag and @c TextInputFlag.
 *
 * If the @c TextFieldInputMode::Custom mode is set, no @c %TextInputFlag values will be available except
 * for @c TextInputFlag::VirtualKeyboard and @c TextInputFlag::VirtualKeyboardOff.
 *
 * For a @c TextArea, you must use @c TextAreaInputMode.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextFieldInputMode {
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief Text input modes for a @c TextField.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*!
       * @brief The default text input mode.
       *
       * @since BlackBerry 10.0.0
       */      
      Default,      
      /*!
       * @brief An input mode for plain text.
       *
       * @since BlackBerry 10.0.0
       */
      Text,
      /*!
       * @brief An input mode for email addresses.
       *
       * @since BlackBerry 10.0.0
       */
      EmailAddress,
      /*!
       * @brief An input mode for passwords.
       *
       * @since BlackBerry 10.0.0
       */
      Password,
      /*!
       * @brief An input mode for chat conversations.
       *
       * @since BlackBerry 10.0.0
       */
      Chat,
      /*!
       * @brief An input mode for URLs.
       *
       * @since BlackBerry 10.0.0
       */
      Url,
      /*!
       * @brief An input mode for phone numbers.
       *
       * @since BlackBerry 10.0.0
       */
      PhoneNumber,
      /*!
       * @brief An input mode for numbers and punctuation.
       *
       * @since BlackBerry 10.0.0
       */
      NumbersAndPunctuation,
      /*!
       * @brief An input mode for numeric passwords.
       *
       * @since BlackBerry 10.0.0
       */
      NumericPassword,
      /*!
       * @brief An input mode for a device PIN.
       * 
       * A PIN is a unique identifier for a device.
       *
       * @since BlackBerry 10.0.0
       */
      Pin,
      /*!
       * @brief An input mode for custom input.
       *
       * Custom input mode will ignore all key input. Key events have to be handled by the application.
       *
       * For text editing, you could use the @ TextEditor class to add text and maintain the cursor position.
       * If the application uses @c TextField::setText(), the cursor position will be reset.
       *
       * When @c %Custom input mode is set, only the @c TextInputFlag::VirtualKeyboard and
       * @c TextInputFlag::VirtualKeyboardOff values are available. The other flags in @c TextInputMode must
       * not be altered from the default state. Spell checking and features from the Input Method Framework,
       * such as word prediction, will be disabled. The application could implement its own integration with
       * the Input Method Framework if such features are required.
       * 
       * When @c %Custom input mode is set, the @c TextField will also not handle submit keys or keyboard
       * shortcuts.
       *
       * @since BlackBerry 10.2.0
       */
      Custom
    };
private:
  /*! @cond PRIVATE */
  TextFieldInputMode();
  ~TextFieldInputMode();
  /*! @endcond */
};

}
}

#endif // cascades_textfieldinputmode_h
