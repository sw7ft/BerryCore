/* Copyright (C) 2012-2014 Research In Motion Limited.  */

#ifndef BB_CASCADES_WEBINPUTPROPERTIES_H
#define BB_CASCADES_WEBINPUTPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <bb/cascades/controls/input/textinputflag.h>

namespace bb {
namespace cascades {

class WebInputPropertiesPrivate;
class WebPagePrivate;

/*!
 * @brief Specifies input properties for @c WebView controls or @c WebPage objects.
 *
 * This is a grouped property that's used to specify input properties for the @c WebView or @c WebPage.
 * The impact and behavior of these flags are dependent on the input handler and are subject to change,
 * and could behave differently on different devices. They should be considered hints.
 *
 * In this example, the virtual keyboard is explicitly disabled for the control.
 *
 * @code
 * WebView {
 *     input {
 *         flags: TextInputFlag.VirtualKeyboardOff
 *     }
 * }
 * @endcode
 *
 * And here's the same example in C++:
 *
 * @code
 * WebView* pWebView = ...;
 *
 * pWebView->input()->setFlags(TextInputFlag::VirtualKeyboardOff);
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="User interface/Web"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BBCASCADES_EXPORT WebInputProperties : public QObject
{
    Q_OBJECT

    /*!
     * @brief Specifies text input feature flags.
     *
     * This is a bit field that you can use to turn on and off input features. The default
     * value is @c TextInputFlag::Default.
     *
     * Here's an example of how to set text input flags:
     *
     * @code
     * WebView {
     *    input.flags: TextInputFlag.VirtualKeyboardOff;
     * }
     * @endcode
     *
     * @note Currently, only @c bb::cascades::TextInputFlag::Default, bb::cascades::TextInputFlag::VirtualKeyboard and
     * @c bb::cascades::TextInputFlag::VirtualKeyboardOff are supported with @c WebView or @c WebPage.
     *
     * @see @c bb::cascades::TextInputFlag::Types
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::cascades::TextInputFlag::Types flags 
             READ flags 
             WRITE setFlags 
             RESET resetFlags 
             NOTIFY flagsChanged 
             REVISION 3
             FINAL)

Q_SIGNALS:

     /*!
      * @brief Emitted when the input flags field has changed.
      *
      * @param newFlags The new flag bit field.
      *
      * @since BlackBerry 10.3.0
      */
     Q_REVISION(3)
     void flagsChanged(bb::cascades::TextInputFlag::Types newFlags);

public:
    virtual ~WebInputProperties();

    /*!
     * @brief Returns the text input flags.
     *
     * The input flags are a bit field that you can use to turn on and off input features.
     *
     * @return The flags bit field.
     *
     * @see @c TextInputFlag::Types
     *
     * @since BlackBerry 10.3.0
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
     * pWebView->input()->setFlags(TextInputFlag::VirtualKeyboardOff);
     * @endcode
     *
     * @note Currently, only @c bb::cascades::TextInputFlag::Default, bb::cascades::TextInputFlag::VirtualKeyboard and
     * @c bb::cascades::TextInputFlag::VirtualKeyboardOff are supported with @c WebView or @c WebPage.
     *
     * @param flags The new text input flags.
     *
     * @see @c TextInputFlag::Types
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    Q_SLOT void setFlags(bb::cascades::TextInputFlag::Types flags);

    /*!
     * @brief Resets the input flags to the default state.
     *
     * The default state is @c TextInputFlag::Default.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    Q_SLOT void resetFlags();

private:
    /*! @cond PRIVATE */
    WebInputProperties(WebPagePrivate*);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(WebInputProperties)
    Q_DISABLE_COPY(WebInputProperties)

    WebInputPropertiesPrivate * const d_ptr;
    /*! @endcond */
};

}
}

QML_DECLARE_TYPE(bb::cascades::WebInputProperties)

#endif // BB_CASCADES_WEBINPUTPROPERTIES_H
