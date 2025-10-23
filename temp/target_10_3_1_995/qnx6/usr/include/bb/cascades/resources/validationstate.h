/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_validationstate_h
#define cascades_validationstate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief Represents the validation state of the @c Validator.
 *
 * A validation state is used to describe the validity of user provided data.
 *
 * @xmlonly
 * <apigrouping group="User interface/Core"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BBCASCADES_EXPORT ValidationState {
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief Validation states.
     *
     * @since BlackBerry 10.1.0
     */
    enum Type
    {
      /*!
        * @brief Validation state is unknown. This state is used for cases when the validation
        * process has not been initiated or has been reset.
       *
       * @since BlackBerry 10.1.0
        */
      Unknown = 0,
      /*!
        * @brief Validation is in progress.
       *
       * @since BlackBerry 10.1.0
        */
      InProgress ,
      /*!
        * @brief Validation succeeded.
       *
       * @since BlackBerry 10.1.0
        */
      Valid ,
      /*!
        * @brief Validation failed.
       *
       * @since BlackBerry 10.1.0
        */
      Invalid
    };
};

}
}

#endif // cascades_validationstate_h
