/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PIXELFORMAT_HPP
#define BB_CORE_PIXELFORMAT_HPP

#include <bb/Global>
#include <QObject>

namespace bb
{

/*!
 * @headerfile PixelFormat.hpp <bb/PixelFormat>
 *
 * @brief An enumeration of the possible formats for the pixels of an @c ImageData object.
 *
 * @details The @c RGBX 32 bit RGB format is stored in memory as 8 red bits, 8 green bits, 8 blue bits, and 8 ignored bits.
 * For example:
 * @code
 * unsigned char *pPixels;
 * pPixels[0] = 0x60; // red
 * pPixels[1] = 0x30; // green
 * pPixels[2] = 0xE0; // blue
 * pPixels += 4; // skip to next pixel
 * @endcode
 *
 * The @c RGBA_Premultiplied 32 bit RGBA format is stored in memory as 8 pre-multiplied red bits, 8 pre-multiplied green bits,
 * 8 pre-multiplied blue bits, and 8 alpha bits.
 * For example:
 * @code
 * unsigned char *pPixels;
 * pPixels[0] = (0x60*0x80)>>8; // premultiplied red
 * pPixels[1] = (0x30*0x80)>>8; // premultiplied green
 * pPixels[2] = (0xE0*0x80)>>8; // premultiplied blue
 * pPixels[3] = 0x80;           // alpha
 * pPixels += 4; // skip to next pixel
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT PixelFormat
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief An enumeration of the possible formats for the pixels of an @c ImageData object.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief 32 bits per pixel, with Red Green Blue each 0-255 then a skipped byte.
         *
         * @since BlackBerry 10.0.0
         */
        RGBX = 0,

        /*!
         * @brief 32 bits per pixel, with Red Green Blue Alpha each 0-255 where RGB is premultiplied by Alpha.
         *
         * @since BlackBerry 10.0.0
         */
        RGBA_Premultiplied = 1,
    };

private:
//!@cond PRIVATE
    PixelFormat();
    ~PixelFormat();
//!@endcond
};

//!@cond PRIVATE
BB_CORE_EXPORT QDebug operator<<(QDebug dbg, PixelFormat::Type image);
//!@endcond

}  // namespace


#endif // BB_CORE_PIXELFORMAT_HPP
