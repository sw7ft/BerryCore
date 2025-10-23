/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textareainputmode_h
#define cascades_textareainputmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents a text input mode for the @c TextArea.
 *
 * The @c %TextAreaInputMode determines how the @c TextArea behaves in relation to its text input.
 * Each input mode has a default set of properties that specify what symbols appear on the keyboard and
 * how the input is displayed in the field. For example, the @c Chat mode contains functionality that
 * allows users to specify emoticons that can be rendered on the screen.
 * You can change the default properties for each mode by turning them on or off using
 * @c TextContentFlag and @c TextInputFlag.
 *
 * If the @c TextAreaInputMode::Custom mode is set, no @c %TextInputFlag values will be available except
 * for @c TextInputFlag::VirtualKeyboard and @c TextInputFlag::VirtualKeyboardOff.
 *
 * For a @c TextField, you must use @c TextFieldInputMode.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextAreaInputMode {
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief Text input modes for a @c TextArea.
     *
     * @since BlackBerry 10.0.0
     */
    typedef enum {
      /*!
       * @brief The default text input mode for a @c TextArea.
       *
       * @since BlackBerry 10.0.0
       */      
      Default,      
      /*!
       * @brief An input mode for plain text entry.
       *
       * @since BlackBerry 10.0.0
       */
      Text,
      /*!
       * @brief An input mode for chat conversations.
       *
       * @since BlackBerry 10.0.0
       */
      Chat,
      /*!
       * @brief An input mode for email addresses.
       *
       * @since BlackBerry 10.0.0
       */
      EmailAddress,
      /*!
       * @brief An input mode for custom input.
       *
       * Custom input mode will ignore all key input. Key events have to be handled by the application.
       *
       * For text editing, you could use the @ TextEditor class to add text and maintain the cursor position.
       * If the application uses @c TextArea::setText(), the cursor position will be reset.
       *
       * When @c %Custom input mode is set, only the @c TextInputFlag::VirtualKeyboard and
       * @c TextInputFlag::VirtualKeyboardOff values are available. The other flags in @c TextInputMode must
       * not be altered from the default state. Spell checking and features from the Input Method Framework,
       * such as word prediction, will be disabled. The application could implement its own integration with
       * the Input Method Framework if such features are required.
       * 
       * When @c %Custom input mode is set, the @c TextArea will also not handle submit keys or keyboard
       * shortcuts.
       *
       * @since BlackBerry 10.2.0
       */
      Custom
    } Type;
private:
  /*! @cond PRIVATE */
  TextAreaInputMode();
  ~TextAreaInputMode();
  /*! @endcond */
};

}
}

#endif // cascades_textareainputmode_h
