/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_IMAGEREADER_HPP
#define BB_UTILITY_IMAGEREADER_HPP

#include <bb/utility/Global>
#include <bb/ImageData>
#include <QScopedPointer>
#include <QUrl>

namespace bb
{
namespace utility
{
class ImageConverterPrivate;

/*!
 * @headerfile ImageConverter.hpp <bb/utility/ImageConverter>
 *
 * @brief Encodes and decodes images to and from different sources in various formats.
 *
 * @details Images may be stored in memory or stored in local files. Images formats
 * are denoted using mime types, such as "image/png", "image/jpeg", and so on,
 * or by the file extension of a given path, such as ".png", ".jpg", and so on.
 *
 * The list of supported formats depends on the codecs that are installed on a
 * device at a particular time. You can use @c img_codec_list(), which is part of
 * the C library, to get a complete list of installed codecs. For more information
 * on C APIs, see http://developer.blackberry.com/native/reference/bb10.
 *
 * Here's how to use the @c %ImageConverter class to decode a PNG image:
 * 
 * @code
 * ImageData image = ImageConverter::decode("foo.png");
 * @endcode
 *
 * In addition to decoding images, this class also contains functionality for encoding
 * images into a specific format (PNG, JPEG, and so on).
 *
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * <library name="bbutility"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_UTILITY_EXPORT ImageConverter
{
public:

    /*!
     * @brief Creates a new instance of the @c %ImageConverter class.
     *
     * @since BlackBerry 10.0.0
     */
    ImageConverter();

    /*!
     * @brief Destroys this @c %ImageConverter instance.
     *
     * @since BlackBerry 10.0.0
     */
    ~ImageConverter();

    /*!
     * @brief Creates an @c ImageData object from an image file.
     *
     * @param fileUrl The location of the image file. Supports "asset:///" and "file:///"
     *        URLs as well as normal file paths.
     * @param format The pixel format of the resultant @c %ImageData. If not specified,
     *        the default pixel format is @c PixelFormat::RGBA_Premultiplied.
     *
     * @return The newly created @c %ImageData. If the image could not be loaded,
     *         @c ImageData::isValid() will return @c false.
     *
     * @since BlackBerry 10.0.0
     */
    static ImageData decode(const QUrl & fileUrl, PixelFormat::Type format = bb::PixelFormat::RGBA_Premultiplied);

    /*!
     * @brief Creates an @c ImageData object from encoded image data.
     *
     * The encoded data can be in any number of formats (PNG, JPEG, and so on).
     *
     * @param encodedData The encoded image data (PNG, JPEG, and so on). The encoded
     *        format is determined by examining the @c encodedData.
     * @param format The pixel format of the resultant @c %ImageData. If not specified,
     *        the default pixel format is @c PixelFormat::RGBA_Premultiplied.
     *
     * @return The newly created @c %ImageData. If the file could not be loaded,
     *         @c ImageData::isValid() will return @c false.
     *
     * @since BlackBerry 10.0.0
     */
    static ImageData decode(const QByteArray & encodedData, PixelFormat::Type format = bb::PixelFormat::RGBA_Premultiplied);

    /*!
     * @brief Converts an image into an encoded format (PNG, JPEG, and so on).
     *
     * @param mimeType The format that the image will be encoded into (for example,
     *        "image/png", "image/jpeg", and so on).
     * @param imageData The image to be encoded.
     * @param quality The quality of the encoding. Valid values are from 0 to 100.
     *        This parameter is used only by codecs that support it. If not specified,
     *        the default quality value is 75.
     *
     * @return The encoded image data. If the image could not be encoded, the returned
     *         @c QByteArray will be empty.
     *
     * @since BlackBerry 10.0.0
     */
    static QByteArray encode(const QString & mimeType, const ImageData & imageData, int quality = 75);

    /*!
     * @brief Converts an image into an encoded format (PNG, JPEG, and so on).
     *
     * @param fileUrl The location to save the image. The image format (PNG, JPEG, and so on)
     *        is determined by file extension. Supports the "asset:///foo.png" and
     *        "file:///path/to/foo.png" formats, standard absolute paths, and relative
     *        paths like "folder/foo.png".
     * @param imageData The image to be encoded.
     * @param quality The quality of the encoding. Valid values are from 0 to 100.
     *        This parameter is used only by codecs that support it. If not specified,
     *        the default quality value is 75.
     *
     * @return @c true if the image was encoded successfully, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    static bool encode(const QUrl & fileUrl, const ImageData & imageData, int quality = 75);

private:
    Q_DISABLE_COPY(ImageConverter)
    Q_DECLARE_PRIVATE(ImageConverter)
    QScopedPointer<ImageConverterPrivate> const d_ptr;
};


}  // namespace
}  // namespace


#endif // _HPP
