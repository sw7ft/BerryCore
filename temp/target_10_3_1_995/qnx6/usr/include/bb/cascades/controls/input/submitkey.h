/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_SUBMITKEY_H
#define BB_CASCADES_SUBMITKEY_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief A class containing different values used for the Submit key.
 *
 * By using this class with a text input control, you can change the string
 * that appears on the Submit button on the virtual keyboard. The default
 * value is dependant on the type of @c TextFieldInputMode that's used by the
 * text field.
 *
 * @see TextInputProperties
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class SubmitKey {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies different submit key options.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {
        /*! @brief Excludes the submit key from the virtual keyboard.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*! @brief Sets the text of the virtual keyboard submit key to the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Default = 1,

        /*! @brief Sets the text of the virtual keyboard submit key to "Go".
         *
         * @since BlackBerry 10.0.0
         */
        Go = 2,

        /*! @brief Sets the text of the virtual keyboard submit key to "Join".
         *
         * @since BlackBerry 10.0.0
         */
        Join = 3,

        /*! @brief Sets the text of the virtual keyboard submit key to "Next".
         *
         * @since BlackBerry 10.0.0
         */
        Next = 4,

        /*! @brief Sets the text of the virtual keyboard submit key to "Search".
         *
         * @since BlackBerry 10.0.0
         */
        Search = 5,

        /*! @brief Sets the text of the virtual keyboard submit key to "Send".
         *
         * @since BlackBerry 10.0.0
         */
        Send = 6,

        /*! @brief Sets the text of the virtual keyboard submit key to "Submit".
         *
         * @since BlackBerry 10.0.0
         */
        Submit = 7,

        /*! @brief Sets the text of the virtual keyboard submit key to "Done".
         *
         * @since BlackBerry 10.0.0
         */
        Done = 8,

        /*! @brief Sets the text of the virtual keyboard submit key to "Connect".
         *
         * @since BlackBerry 10.0.0
         */
        Connect = 9,
      
        /*! @brief Sets the symbol of the virtual keyboard submit key to the
         *         default Enter symbol. This submit key looks like the 
         *         Enter/Newline key but behaves like a submit key and emits a 
         *         @c submitted() signal when tapped.
         *
         * @since BlackBerry 10.2.0
         */
         EnterKey = 10,

        /*! @brief Sets the text of the virtual keyboard submit key to "Replace".
         *
         * @since BlackBerry 10.2.0
         */
         Replace = 11
    };

private:
    /*! \cond PRIVATE */
    SubmitKey();
    ~SubmitKey();
    /*! \endcond */
};

}
}

#endif // BB_CASCADES_SUBMITKEY_H
