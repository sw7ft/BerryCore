/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_INPUTPROPERTIES_H
#define BB_CASCADES_INPUTPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>

#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/SubmitKey>
#include <bb/cascades/SubmitKeyFocusBehavior>
#include <bb/cascades/TextInputMasking>
#include <bb/cascades/controls/abstracttextcontrol.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/controls/input/keylayout.h>
#include <bb/cascades/controls/input/textinputflag.h>

namespace bb {
namespace cascades {

class TextInputPropertiesPrivate;

/*!
 * @brief Specifies text input properties for text input controls.
 *
 * This is a grouped property that's used to specify input properties for the text field,
 * such as what text is displayed on the Submit button on the keyboard, whether or
 * not spell check should be used to verify the content, or other input-related configuration parameters.
 * The impact and behavior of these flags are dependent on the input handler and are subject to change,
 * and could behave differently on different devices. They should be considered hints.
 *
 * In this example, the word "Connect" is displayed on the virtual keyboard and the @c submitted()
 * signal is captured in order to initiate some sort of task in response. Spell checking is explicitly 
 * enabled and prediction is explicitly disabled for the control.
 *
 * @code
 * TextArea {
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
 * And here's the same example in C++:
 *
 * @code
 * TextArea* pTextArea = new TextArea();
 *
 * pTextArea->input()->setSubmitKey(SubmitKey::Connect);
 * QObject::connect(pTextArea->input(), SIGNAL(submitted()), this, SLOT(onSubmitted()));
 * @endcode
 *
 * @see @c SubmitKey
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextInputProperties : public UIObject
{
    Q_OBJECT

    /*!
     * @brief Specifies which submit key to show on the virtual keyboard.
     *
     * The default value is @c SubmitKey::Default, indicating that the keyboard 
     * should use whatever text is the default.
     *
     * @see @c SubmitKey::Type
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY(bb::cascades::SubmitKey::Type submitKey READ submitKey WRITE setSubmitKey RESET resetSubmitKey NOTIFY submitKeyChanged FINAL)

    /*!
     * @brief Specifies text input feature flags.
     *
     * This is a bit field that you can use to turn on and off input features. The default
     * value is @c TextInputFlag::Default.
     *
     * Here's an example of how to set text input flags:
     *
     * @code
     * TextArea {
     *    input.flags: TextInputFlag.SpellCheck | TextInputFlag.PredictionOff;
     * }
     * @endcode
     *
     * @see @c bb::cascades::TextInputFlag::Types
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::TextInputFlag::Types flags 
             READ flags 
             WRITE setFlags 
             RESET resetFlags 
             NOTIFY flagsChanged 
             FINAL)

    /*!
     * @brief Specifies text input focus behavior.
     *
     * This property controls the focus behavior of the text control. For example, you can use this
     * property to specify if the focus should change to another control when the Enter button is
     * pressed.
     *
     * This property applies only to controls where the #submitKey property has been set. Otherwise,
     * it will be ignored.
     *
     * Here's an example of how to set the text input focus behavior:
     *
     * @code
     * TextField {
     *    input.submitKeyFocusBehavior: SubmitKeyFocusBehavior.Keep;
     * }
     * @endcode
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::SubmitKeyFocusBehavior::Type submitKeyFocusBehavior
             READ submitKeyFocusBehavior
             WRITE setSubmitKeyFocusBehavior
             RESET resetSubmitKeyFocusBehavior
             NOTIFY submitKeyFocusBehaviorChanged
             FINAL)

    /*!
     * @brief Specifies input masking mode.
     *
     * The default value is @c TextInputMasking::Default, indicating that the system will decide
     * if masking is turned on or off.
     *
     * If the masking mode is set to @c TextInputMasking::MaskedNotTogglable or
     * @c TextInputMasking::NotMaskedNotTogglable, the user is not allowed to toggle
     * the masking mode using the text control UI. However, you can still provide your own control
     * in your apps to change the masking model.
     *
     * If the masking mode set to @c TextInputMasking::Masked or @c TextInputMasking::NotMasked,
     * the user can toggle the masking mode by using a toggle box inside the text control.
     *
     * Here's an example of how to set the input masking mode:
     *
     * @code
     * TextField {
     *    inputMode: TextFieldInputMode.Password;
     *    input.masking: TextInputMasking.NotMasked;
     * }
     * @endcode
     *
     * @note This property applies to password or numeric password text fields only.
     *
     * @see TextInputMasking::Type
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY(bb::cascades::TextInputMasking::Type masking
              READ masking
              WRITE setMasking
              RESET resetMasking
              NOTIFY maskingChanged
              FINAL)

    /*!
     * @brief Specifies the key layout.
     *
     * This property controls the layout of the keys on the virtual keyboard, or
     * the interpretation of keys on a physical keyboard.
     *
     * The default value is @c KeyLayout::Default, which means that the key layout is
     * chosen based on the input mode of either the @c TextField or @c TextArea.
     *
     * The following example creates a @c %TextArea with a preferred @c keyLayout of @c KeyLayout.Pin:
     * @code
     * TextArea
     * {
     *     id: pinEditor
     *     input
     *     {
     *         keyLayout: KeyLayout.Pin
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Text"/>
     * @endxmlonly
     *
     * @see @c KeyLayout
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::cascades::KeyLayout::Type keyLayout READ keyLayout
               WRITE setKeyLayout RESET resetKeyLayout NOTIFY keyLayoutChanged REVISION 3 FINAL)

Q_SIGNALS:

    /*!
     * @brief Emitted when the submit key has been pressed.
     *
     * This signal is emitted whenever the submit key is pressed, as long as the key has
     * been set to something other than @c None or @c Default.
     *
     * @param submitter The text control that is the source of the submission.
     *
     * @see @c SubmitKey::Type
     *
     * @since BlackBerry 10.0.0
     */
     void submitted(bb::cascades::AbstractTextControl *submitter);

    /*!
     * @brief Emitted when the submit key has changed.
     *
     * @param submitKey The new submit key.
     *
     * @since BlackBerry 10.0.0
     */
     void submitKeyChanged(const bb::cascades::SubmitKey::Type submitKey);
  
     /*!
     * @brief Emitted when the input flags field has changed.
     *
     * @param newFlags The new flag bit field.
      *
      * @since BlackBerry 10.0.0
     */
     void flagsChanged(bb::cascades::TextInputFlag::Types newFlags);

    /*!
     * @brief Emitted when the focus behavior for the submit key has changed.
     *
     * @param newSubmitKeyFocusBehavior The new behavior.
     *
     * @since BlackBerry 10.0.0
     */
     void submitKeyFocusBehaviorChanged(bb::cascades::SubmitKeyFocusBehavior::Type newSubmitKeyFocusBehavior);

    /*!
     * @brief Emitted when the masking mode has changed.
     *
     * @param newMasking The new masking mode.
     *
     * @since BlackBerry 10.0.0
     */
     void maskingChanged(bb::cascades::TextInputMasking::Type newMasking);

    /*!
     * @brief Emitted when the key layout has changed.
     *
     * @param newKeyLayout The new key layout.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    void keyLayoutChanged(bb::cascades::KeyLayout::Type newKeyLayout);

public:
    virtual ~TextInputProperties();

   /*!
    * @brief Retrieves the current submit key focus behavior.
    *
    * @return The current submit key focus behavior.
    *
    * @since BlackBerry 10.0.0
    */
    bb::cascades::SubmitKeyFocusBehavior::Type submitKeyFocusBehavior();

   /*!
    * @brief Sets the submit key focus behavior to use.
    *
    * @param submitKeyFocusBehavior The submit key focus behavior.
    *
    * @since BlackBerry 10.0.0
    */
    void setSubmitKeyFocusBehavior(bb::cascades::SubmitKeyFocusBehavior::Type submitKeyFocusBehavior);

   /*!
    * @brief Resets the submit key focus behavior to its default value.
    *
    * @since BlackBerry 10.0.0
    */
    Q_SLOT void resetSubmitKeyFocusBehavior();

    /*!
     * @brief Sets which submit key to show on the virtual keyboard.
     *
     * @param submitKey The submit key to show.
     *
     * @since BlackBerry 10.0.0
     */
    void setSubmitKey(bb::cascades::SubmitKey::Type submitKey);

    /*!
     * @brief Resets the submit key to its default value of @c SubmitKey::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetSubmitKey();

    /*!
     * @brief Retrieves the current submit key.
     *
     * @return The current submit key.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::SubmitKey::Type submitKey();

    /*!
     * @brief Sets the input masking mode.
     *
     * @param masking The masking mode.
     *
     * @since BlackBerry 10.0.0
     */
    void setMasking(bb::cascades::TextInputMasking::Type masking);

    /*!
     * @brief Resets the masking mode to its default value of @c TextInputMasking::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetMasking();

    /*!
     * @brief Retrieves the current masking mode.
     *
     * @return The current masking mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::TextInputMasking::Type masking() const;
  
  
    /*!
     * @brief Returns the text input flags.
     *
     * The input flags are a bit field that you can use to turn on and off input features.
     *
     * @return The flags bit field.
     *
     * @see @c TextInputFlag::Types
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::TextInputFlag::Types flags() const;
    
    /*!
     * @brief Sets the text input flags.
     *
     * The input flags are a bit field that you can use to turn on and off input features. This function
     * will emit the @c flagsChanged() signal.
     *
     * Here's an example of how to set text input flags:
     *
     * @code
     * pTextField->input()->setFlags(TextInputFlag::SpellCheck | TextInputFlag::PredictionOff);
     * @endcode
     *
     * @param flags The new text input flags.
     *
     * @see @c TextInputFlag::Types
     *
     * @since BlackBerry 10.0.0
     */
    void setFlags(bb::cascades::TextInputFlag::Types flags);
    
    /*!
     * @brief Resets the input flags to the default state.
     *
     * The default state is @c TextInputFlag::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFlags();

    /*!
     * @brief Gets the current preferred key layout.
     *
     * @return The current key layout.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    bb::cascades::KeyLayout::Type keyLayout() const;

    /*!
     * @brief Sets the current preferred key layout.
     *
     * @param keyLayout The new key layout to be set.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    Q_SLOT void setKeyLayout(bb::cascades::KeyLayout::Type keyLayout);

    /*!
     * @brief Resets the preferred key layout to the default value.
     *
     * The default value for the key layout is @c KeyLayout::Default.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    Q_SLOT void resetKeyLayout();

protected:
    /*! @cond PRIVATE */
    TextInputProperties();
    /*! @endcond */
  
private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(TextInputProperties)
    Q_DISABLE_COPY(TextInputProperties)
    /*! @endcond */
};

}
}

QML_DECLARE_TYPE(bb::cascades::TextInputProperties)

#endif // BB_CASCADES_INPUTPROPERTIES_H
