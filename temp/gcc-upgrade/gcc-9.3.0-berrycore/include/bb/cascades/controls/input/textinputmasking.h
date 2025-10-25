/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_INPUT_MASKING_H
#define BB_CASCADES_INPUT_MASKING_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief A class representing different input masking modes.
 *
 * This class represents different input masking modes. You can use input masking to
 * prevent characters that are typed in a text field from appearing. When input masking
 * is enabled, typed characters appear as asterisks (*).
 *
 * By default, users can toggle input masking on or off by using a toggle box inside the
 * text control. You can prevent this by using either @c MaskedNotTogglable or
 * @c NotMaskedNotTogglable.
 *
 * @see TextInputProperties
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class TextInputMasking {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies different masking modes.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {
       /*!
        * @brief The default masking mode.
        *
        * The system will decide if the masking is turned on or off by default.
        *
        * @since BlackBerry 10.0.0
        */
        Default = 0,

       /*!
        * @brief Indicates that masking is turned on.
        *
        * @since BlackBerry 10.0.0
        */
        Masked = 1,

       /*!
        * @brief Indicates that masking is turned off.
        *
        * @since BlackBerry 10.0.0
        */
        NotMasked = 2,

       /*!
        * @brief Indicates that masking is turned on and that users can't toggle the masking mode.
        *
        * @since BlackBerry 10.0.0
        */
        MaskedNotTogglable = 3,

       /*!
        * @brief Indicates that masking is turned off and that users can't toggle the masking mode.
        *
        * @since BlackBerry 10.0.0
        */
        NotMaskedNotTogglable = 4
    };

private:
    /*! \cond PRIVATE */
    TextInputMasking();
    ~TextInputMasking();
    /*! \endcond */
};

}
}

#endif // BB_CASCADES_INPUT_MASKING_H
