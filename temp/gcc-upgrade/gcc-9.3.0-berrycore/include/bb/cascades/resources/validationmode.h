/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_validationmode_h
#define cascades_validationmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief Represents a validation mode.
 *
 * A validation mode is used to define how validation should be triggered.
 *
 * In @c ValidationMode::FocusLost, @c ValidationMode::Delayed, and @c ValidationMode::Immediate modes
 * validation will be triggered automatically but based on different events.
 * In @c %ValidationMode::Immediate mode validation will be triggered immediately (without any delays)
 * after some data has been changed (for example, after every entered symbol in text control).
 *
 * @see bb::cascades::Validator
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BBCASCADES_EXPORT ValidationMode {
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief Validation modes.
     *
     * @since BlackBerry 10.1.0
     */
    enum Type
    {
      /*!
        * @brief Default validation mode. In this mode the validator selects the mode automatically.
       *
       * @since BlackBerry 10.1.0
        */
      Default,
      /*!
        * @brief Automatic validation triggering is disabled. This mode is used for cases
        * when validation should not be executed automatically.
       *
       * @since BlackBerry 10.1.0
        */
      Custom,
      /*!
        * @brief Validation will be executed when @c Control loses focus.
       *
       * @since BlackBerry 10.1.0
        */
      FocusLost,
      /*!
        * @brief Delayed validation mode. Validation will be executed with a default delay.
       *
       * @since BlackBerry 10.1.0
        */
      Delayed,
      /*!
        * @brief Immediate validation mode. Validation will be executed without any delay.
       *
       * @since BlackBerry 10.1.0
        */
      Immediate
    };
};

}
}

#endif // cascades_validationmode_h
