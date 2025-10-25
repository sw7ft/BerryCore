/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_validator_h
#define cascades_validator_h

#include <QtCore/QObject>
#include <QtDeclarative>

#include <QtCore/QScopedPointer>

#include <bb/cascades/BaseObject>
#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/validationstate.h>
#include <bb/cascades/resources/validationmode.h>

namespace bb {
    namespace cascades {

    class ValidatorPrivate;

    /*!
     * @brief A default validation class that's used to validate some controls (currently,
     * only @c TextField is supported).
     *
     * @c %Validator includes the following properties:
     *
     * - @c #state: Specifies the current validation state.
     *   This property shows the current @c ValidationState of the control.
     *   Controls can listen to changes to this property to respond to state changes.
     *
     * - @c #mode: Specifies the current validation mode.
     *   This property configures the validator's scheduling logic.
     *
     * - @c #valid: Specifies the current validity of the @c %Control.
     *   This property can be used to set a @c Validator to a @c Valid or @c Invalid state.
     *   Controls can listen to changes to this property to respond to state changes if some
     *   specific actions must be performed when the state changes to a @c Valid or @c Invalid state.
     *   For example, if the @c Control should show an error when the validation state is changed to @c Invalid.
     *   When the @c valid property changes, the @c state property changes also.
     *
     * - @c #errorMessage: Specifies the error message.
     *   This property contains a text representation of the error in an @c Invalid state.
     *
     * The following sample demonstrates how to validate a @c TextField in C++.
     * The code below assumes that @c ValidatePasswordApplication has the @c onValidate() slot.
     *
     * @code
     * ValidatePasswordApplication::ValidatePasswordApplication()
     * {
     *   TextField* passwordField = TextField::create().hintText("Password");
     *   passwordField.setValidator(
     *       Validator::create()
     *         .errorMessage("Incorrect password")
     *         .mode(ValidationMode::FocusLost))
     *         .connect(SIGNAL(validate()), this, SLOT(onValidate()));
     * }
     * @endcode
     *
     * Here's how to validate a @c %TextField in QML:
     *
     * @code
     * TextField {
     *   id: passwordField
     *   validator: Validator {
     *     mode: ValidationMode::FocusLost
     *     errorMessage: "Invalid password"
     *     onValidate: {
     *       // validate a passwordField's text and set appropriate state.
     *     }
     *   }
     * }
     * @endcode
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     *
     * @since BlackBerry 10.1.0
     */
    class BBCASCADES_EXPORT Validator : public BaseObject
    {
        Q_OBJECT

      /*!
       * @brief The validation @c state.
       *
       * Validation state as defined in @c ValidationState.
       *
       * The default value is @c ValidationState::Unknown.
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bb::cascades::ValidationState::Type state
                 READ state WRITE setState NOTIFY stateChanged RESET resetState FINAL)

      /*!
       * @brief The validation @c mode.
       *
       * Validation mode as defined in @c ValidationMode.
       *
       * The default value is @c ValidationMode::Default.
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bb::cascades::ValidationMode::Type mode
                 READ mode WRITE setMode NOTIFY modeChanged RESET resetMode FINAL)

      /*!
       * @brief Represents whether validation was successful or not.
       *
       * Returns @c true if the @c state property is in a @c Valid state or no validation was performed yet,
       * @c false otherwise. This property is bound with the @c state property.
       * If the @c state changes to @c ValidationState::Valid, the @c valid
       * property will be @c true. If the @c state changes to @c ValidationState::Invalid,
       * the @c valid property will be @c false.
       *
       * @note If the @c state property changes to @c ValidationState::Unknown
       * or @c ValidationState::InProgress, then the @c valid property will not
       * change.
       *
       * The default value is @c false.
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bool valid
                 READ isValid WRITE setValid NOTIFY validChanged RESET resetValid FINAL)

      /*!
       * @brief Represents the error message.
       *
       * Contains an error message for the invalid validation state.
       *
       * The default value is @c QString::null.
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(QString errorMessage
                 READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged RESET resetErrorMessage FINAL)

      /*!
       * @brief Represents a delay in milliseconds.
       *
       * The delay, in milliseconds, before the @c validate signal will be emitted.
       * This value is used in the @c requestValidation slot in @c ValidationMode::Delayed mode.
       *
       * The default value is 2000 milliseconds.
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(int delay
                 READ delay WRITE setDelay NOTIFY delayChanged RESET resetDelay FINAL)

      /*!
       * @brief Represents whether validation was requested or not.
       *
       * If this property is set to @c true then @c requestValidation will be called.
       * When the @c validate signal is emitted this property would set back to @c false.
       *
       * @note If the @c mode is set to ValidationMode::Custom, you can
       * listen to this property to find out when validation has been requested.
       * You are responsible for calling @c validate and resetting
       * the @c validationRequested property back to @c false.
       *
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bool validationRequested
                 READ validationRequested WRITE setValidationRequested
                 NOTIFY validationRequestedChanged RESET resetValidationRequested FINAL)

    public:

      /*!
       * @brief Sets the validation @c state.
       *
       * @param state The validation state.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void setState(bb::cascades::ValidationState::Type state);

      /*!
       * @brief Returns the validation state.
       *
       * @return The validation state. @c ValidationState::Unknown by default.
       *
       * @since BlackBerry 10.1.0
       */
      bb::cascades::ValidationState::Type state() const;

      /*!
       * @brief Resets the @c #state to its default value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_INVOKABLE void resetState();

      /*!
       * @brief Sets the validation @c mode.
       *
       * @param mode The validation mode.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void setMode(bb::cascades::ValidationMode::Type mode);

      /*!
       * @brief Returns the validation @c mode.
       *
       * @return The validation mode. @c ValidationMode::Default by default.
       *
       * @since BlackBerry 10.1.0
       */
      bb::cascades::ValidationMode::Type mode() const;

      /*!
       * @brief Resets the @c #mode to its default value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_INVOKABLE void resetMode();

      /*!
       * @brief Sets the @c valid property.
       *
       * @param valid Boolean value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void setValid(bool valid);

      /*!
       * @brief Returns the @c valid value.
       *
       * @return The @c valid value. The default value is @c false.
       *
       * @since BlackBerry 10.1.0
       */
      bool isValid() const;

      /*!
       * @brief Resets @c valid to its default value. Also resets the @c state to its default value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_INVOKABLE void resetValid();

      /*!
       * @brief Sets the error message text.
       *
       * @param errorMessage The error message text.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void setErrorMessage(const QString &errorMessage);

      /*!
       * @brief Returns the @c #errorMessage text.
       *
       * @return The error message text. Returns an empty string if it is not set.
       *
       * @since BlackBerry 10.1.0
       */
      QString errorMessage() const;

      /*!
       * @brief Resets the @c #errorMessage to its default value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_INVOKABLE void resetErrorMessage();

      /*!
       * @brief Sets the @c delay in milliseconds.
       *
       * @param delay The delay in milliseconds.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void setDelay(int delay);

      /*!
       * @brief Returns the @c #delay value.
       *
       * @return The delay in milliseconds.
       *
       * @since BlackBerry 10.1.0
       */
      int delay() const;

      /*!
       * @brief Resets the @c #delay to its default value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_INVOKABLE void resetDelay();

      /*!
       * @brief Shows a toast message with @c errorMessage text.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void showMessage();

      /*!
       * @brief Sets the @c validationRequested property.
       *
       * @param requested Boolean value.
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void setValidationRequested(bool requested);

      /*!
       * @brief Returns the @c validationRequested value.
       *
       * @return The @c %validationRequested value. The default value is @c false.
       *
       * @since BlackBerry 10.1.0
       */
      bool validationRequested() const;

      /*!
       * @brief Resets the @c #validationRequested to its default value of @c false.
       *
       * @since BlackBerry 10.1.0
       */
      Q_INVOKABLE void resetValidationRequested();

      /*!
       * @brief Requests a re-validation of the source according to the @c mode property.
       *
       * The @c validate signal is emitted directly from this slot or with a delay,
       * depending on the @c mode property.
       * If @c mode is set to @c ValidationMode::Custom the @c validate signal is not emitted.
       *
       *
       * @since BlackBerry 10.1.0
       */
      Q_SLOT void requestValidation();

    Q_SIGNALS:

      /*!
       * @brief Emitted when the validation @c state changes.
       *
       * @param newState The new validation state.
       *
       * @since BlackBerry 10.1.0
       */
      void stateChanged(bb::cascades::ValidationState::Type newState);

      /*!
       * @brief Emitted when the validation @c mode changes.
       *
       * @param newMode The new validation mode.
       *
       * @since BlackBerry 10.1.0
       */
      void modeChanged(bb::cascades::ValidationMode::Type newMode);

      /*!
       * @brief Emitted when the @c valid property changes.
       *
       * @param valid The new @c valid property value.
       *
       * @since BlackBerry 10.1.0
       */
      void validChanged(bool valid);

      /*!
       * @brief Emitted when the error message text changes.
       *
       * @param errorMessage The new error message text.
       *
       * @since BlackBerry 10.1.0
       */
      void errorMessageChanged(const QString errorMessage);

      /*!
       * @brief Emitted when the @c delay property changes.
       *
       * @param delay The new delay in milliseconds.
       *
       * @since BlackBerry 10.1.0
       */
      void delayChanged(int delay);

      /*!
       * @brief Emitted when the @c validationRequested property changes.
       *
       * @param requested The new @c %validationRequested property value.
       *
       * @since BlackBerry 10.1.0
       */
      void validationRequestedChanged(bool requested);

      /*!
       * @brief Emitted when validation should be performed by the client.
       *
       *
       * @since BlackBerry 10.1.0
       */
      void validate();
    public:
      /*!
       * @brief Constructs a @c Validator instance
       *
       * @since BlackBerry 10.1.0
       */
      explicit Validator(QObject *parent = 0);
      virtual ~Validator();

    private:
      /*! @cond PRIVATE */
      Q_DECLARE_PRIVATE(Validator)
      Q_DISABLE_COPY(Validator)
      /*! @endcond */

    public:
      typedef BaseObject BaseClass;

      /*!
       * @brief A builder template for constructing a @c Validator.
       *
       * @since BlackBerry 10.1.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
      {
      protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
      public:
        /*!
         * @copydoc bb::cascades::Validator::setState(bb::cascades::ValidationState::Type)
         */
        BuilderType& state(bb::cascades::ValidationState::Type state)
        {
          this->instance().setState(state);
          return this->builder();
        }

        /*!
         * @copydoc bb::cascades::Validator::setMode(bb::cascades::ValidationMode::Type)
         */
        BuilderType& mode(bb::cascades::ValidationMode::Type mode)
        {
          this->instance().setMode(mode);
          return this->builder();
        }

        /*!
         * @copydoc bb::cascades::Validator::setValid(bool)
         */
        BuilderType& valid(bool valid)
        {
          this->instance().setValid(valid);
          return this->builder();
        }

        /*!
         * @copydoc bb::cascades::Validator::setErrorMessage(const QString &)
         */
        BuilderType& errorMessage(const QString &errorMessage)
        {
          this->instance().setErrorMessage(errorMessage);
          return this->builder();
        }

        /*!
         * @copydoc bb::cascades::Validator::setDelay(int)
         */
        BuilderType& delay(int delay)
        {
          this->instance().setDelay(delay);
          return this->builder();
        }

      };

      /*!
       * @brief A builder template for constructing a @c Validator.
       *
       * To retrieve the builder, call @c Validator::create().
       *
       * @since BlackBerry 10.1.0
       */
      class Builder : public TBuilder<Builder, Validator>
      {
      public:
          explicit Builder() : TBuilder<Builder, Validator>(new Validator()) {}
      };

      /*!
       * @brief Creates and returns a builder for constructing a @c %Validator.
       *
       * The following sample uses the builder to create a @c %Validator:
       *
       * @code
       * Validator* validator = Validator::create();
       * @endcode
       *
       * @return A builder used for constructing a @c %Validator.
       *
       * @since BlackBerry 10.1.0
       */
      static Builder create()
      {
          return Builder();
      }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Validator)

#endif // cascades_validator_h

