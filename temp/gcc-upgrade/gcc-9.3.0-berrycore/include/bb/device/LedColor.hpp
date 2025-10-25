/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_DEVICE_LEDCOLOR_HPP
#define BB_DEVICE_LEDCOLOR_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile LedColor.hpp <bb/device/LedColor>
 *
 * @brief The @c LedColor class provides a wrapper for the @c LedColor::Type 
 *        enumeration.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT LedColor
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief The @c LedColor class provides a wrapper for the @c LedColor::Type 
     *        enumeration.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief If this color is specified, the LED will not blink.
         *
         * @since BlackBerry 10.0.0
         */
        None    = 0x000000,

        /*!
         * @brief LED will blink red.
         *
         * @since BlackBerry 10.0.0
         */
        Red     = 0xff0000,

        /*!
         * @brief LED will blink green.
         *
         * @since BlackBerry 10.0.0
         */
        Green   = 0x00ff00,

        /*!
         * @brief LED will blink blue.
         *
         * @since BlackBerry 10.0.0
         */
        Blue    = 0x0000ff,

        /*!
         * @brief LED will blink yellow.
         *
         * @since BlackBerry 10.0.0
         */
        Yellow  = Red | Green,

        /*!
         * @brief LED will blink cyan.
         *
         * @since BlackBerry 10.0.0
         */
        Cyan    = Green | Blue,

        /*!
         * @brief LED will blink magenta.
         *
         * @since BlackBerry 10.0.0
         */
        Magenta = Blue | Red,

        /*!
         * @brief LED will blink white.
         *
         * @since BlackBerry 10.0.0
         */
        White   = Red | Green | Blue
    };

    /*!
     * @brief Returns the color corresponding to the use of the colors provided.
     *
     * @param red Whether the result should contain red.
     * @param green Whether the result should contain green.
     * @param blue Whether the result should contain blue.
     *
     * @return Returns the color corresponding to the mix of colors provided, or
     *         @c LedColor::None if no colors are used.
     *
     * @since BlackBerry 10.0.0
     */
    static bb::device::LedColor::Type fromBitset(bool red, bool green, bool blue);

    /*!
     * @brief Returns a string corresponding to the color provided.
     *
     * @param color The color to translate.
     *
     * @return Returns the name of the color as listed in @c LedColor::Type, or the  
     *         null @c QString for @c LedColor::None.
     *
     * @since BlackBerry 10.0.0
     */
    static QString toName(bb::device::LedColor::Type color);
};
} // device
} // bb

QML_DECLARE_TYPE(bb::device::LedColor)
#endif // BB_DEVICE_LEDCOLOR_HPP
