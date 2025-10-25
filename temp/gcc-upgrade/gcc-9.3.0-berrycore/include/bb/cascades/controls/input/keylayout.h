/* Copyright (C) 2014 Research In Motion Limited.  */

#ifndef BB_CASCADES_KEY_LAYOUT_H
#define BB_CASCADES_KEY_LAYOUT_H

#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief This class defines an enumerator that lists all possible keyboard layouts.
 *
 * The keyboard layout affects the layout of keys on the virtual keyboard and the
 * interpretation of key presses on a physical keyboard, depending on the device
 * being used. For example, the @c PhoneNumber enumerated value displays a number-pad
 * on a virtual keyboard, and also removes the need to use the modifier key to
 * enter numbers on a device with a physical keyboard.
 *
 * The keyboard layout depends on @c TextInputProperties::keyLayout property and
 * @c TextArea::inputMode or @c TextField::inputMode.
 * If @c TextInputProperties::keyLayout and @c inputMode define different modes,
 * @c TextInputProperties::keyLayout will take priority for the keyboard layout.
 *
 * @see TextInputProperties
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class KeyLayout
{
    Q_GADGET
    Q_ENUMS(Type)

public:
   /*!
    * @brief Specifies the preferred keyboard layout.
    *
    * @since BlackBerry 10.3.0
    */
    enum Type {
        /*!
         * @brief Sets the preferred keyboard layout to "Default".
         *
         * The keyboard layout depends on input mode of the @c TextField or @c TextArea.
         *
         * @see @c TextArea::inputMode, @c TextField::inputMode
         *
         * @since BlackBerry 10.3.0
         */
        Default = 0,
        /*!
         * @brief Sets the preferred keyboard layout to text.
         *
         * A keyboard layout for entering plain text.
         *
         * @since BlackBerry 10.3.0
         */
        Text = 1,
        /*!
         * @brief Sets the preferred keyboard layout to URL.
         *
         * A keyboard layout for entering URLs.
         *
         * @since BlackBerry 10.3.0
         */
        Url = 2,
        /*!
         * @brief Sets the preferred keyboard layout to email.
         *
         * A keyboard layout for entering email addresses.
         *
         * @since BlackBerry 10.3.0
         */
        EmailAddress = 3,
        /*!
         * @brief Sets the preferred keyboard layout to numbers and punctuation.
         *
         * A keyboard layout for entering numbers and punctuation.
         *
         * @since BlackBerry 10.3.0
         */
        NumbersAndPunctuation = 4,
        /*!
         * @brief Sets the preferred keyboard layout to phone.
         *
         * A keyboard layout for entering phone numbers.
         *
         * @since BlackBerry 10.3.0
         */
        PhoneNumber = 5,
        /*!
         * @brief Sets the preferred keyboard layout to pin.
         *
         * A keyboard layout for entering PINs.
         *
         * @since BlackBerry 10.3.0
         */
        Pin = 6,
        /*!
         * @brief Sets the preferred keyboard layout to alpha numeric.
         *
         * A keyboard layout for entering numbers and letters.
         *
         * @since BlackBerry 10.3.0
         */
        Alphanumeric = 7,
        /*!
         * @brief Sets the preferred keyboard layout to SIM pin.
         *
         * A keyboard layout for entering the PIN of a SIM card.
         *
         * @since BlackBerry 10.3.0
         */
        SimPin = 8,
        /*!
         * @brief Sets the preferred keyboard layout to number.
         *
         * A keyboard layout for entering numbers.
         *
         * @since BlackBerry 10.3.0
         */
        Number = 9,
        /*!
         * @brief Sets the preferred keyboard layout to contact.
         *
         * A keyboard layout for entering contact information.
         * Use Contact instead of EmailAddress when you need the
         * space character easily available on any type of device 
         * keyboard.
         *
         * @since BlackBerry 10.3.0
         */
        Contact = 10
    };

private:
    /*! \cond PRIVATE */
    KeyLayout();
    ~KeyLayout();
    /*! \endcond */
};

} // namespace cascades
} // namespace bb

#endif // BB_CASCADES_KEY_LAYOUT_H
