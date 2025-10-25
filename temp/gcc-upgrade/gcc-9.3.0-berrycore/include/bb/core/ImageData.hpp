/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_IMAGEDATA_HPP
#define BB_CORE_IMAGEDATA_HPP

#include <bb/Global>
#include <bb/PixelFormat>

#include <QObject>
#include <QSharedDataPointer>

namespace bb
{

/*!
 * @headerfile ImageData.hpp <bb/ImageData>
 *
 * @brief A class that encapsulates pixels and width, height, format information for images.
 *
 * The @c %ImageData class implements value semantics using copy-on-write, which is also known as "lazy copy" or "lazy evaluation"
 * and by Qt as "implicit data sharing".
 *
 * This means that copies can conceptually be treated as distinct objects, although for performance reasons,
 * they share memory until one of the copies is actually written to, thus becoming distinct from the original.
 * For example:
 *
 * @code
 * bb::ImageData image1(bb::PixelFormat::RGBA_Premultiplied, 400, 300);
 * bb::ImageData image2 = image1;
 * 
 * // image2 is a copy of image1, so holds the same pixel values. In fact, it points to the same memory location:
 * qDebug() << (image1.constPixels() == image2.constPixels()); // true
 * 
 * // but now let's change image2
 * unsigned char * pixels = image2.pixels();
 * 
 * // now image2 is different than image1, so they point to different memory locations
 * qDebug() << (image1.constPixels() == image2.constPixels()); // false
 * @endcode
 *
 * @c %ImageData can easily be used with Qt's @c QImage (if you are linking in the QtGui library):
 * @code
 * bb::ImageData fromQImage(const QImage &qImage)
 * {
 *     bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(), qImage.height());
 *
 *     unsigned char *dstLine = imageData.pixels();
 *     for (int y = 0; y < imageData.height(); y++) {
 *         unsigned char * dst = dstLine;
 *         for (int x = 0; x < imageData.width(); x++) {
 *             QRgb srcPixel = qImage.pixel(x, y);
 *             *dst++ = qRed(srcPixel);
 *             *dst++ = qGreen(srcPixel);
 *             *dst++ = qBlue(srcPixel);
 *             *dst++ = qAlpha(srcPixel);
 *         }
 *         dstLine += imageData.bytesPerLine();
 *     }
 *
 *     return imageData;
 * }
 * @endcode
 * Note that the above example is written for clarity, at the possible expense of performance.
 *
 * @note An invalid @c %ImageData contains undefined data. This means that @c pixels() and @c constPixels()
 * will return invalid pointers in this case. Use the @c isValid() method to check for valid @c ImageData
 * objects.
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT ImageData
{
public:

    /*!
     * @brief Creates an invalid @c %ImageData.
     *
     * @since BlackBerry 10.0.0
     */
    ImageData();

    /*!
     * @brief Creates an @c %ImageData, allocating the necessary memory (for abs(width * height) pixels).
     *
     * @param format The format of the created pixels. See @c PixelFormat for the list of supported formats.
     * @param width The width of the created image buffer.
     * @param height The height of the created image buffer.
     *
     * @since BlackBerry 10.0.0
     */
    ImageData(PixelFormat::Type format, int width, int height);

    /*!
     * @brief Destroys the @c %ImageData object.
     *
     * @since BlackBerry 10.0.0
     */
    ~ImageData();

    /*!
     * @brief Constructs an @c %ImageData as a copy of the given image buffer.
     *
     * The two @c %ImageData objects share a single internal buffer until either attempts to write to the buffer,
     * at which time a full copy is made.
     *
     * @param other The @c %ImageData to copy from.
     *
     * @since BlackBerry 10.0.0
     */
    ImageData(const ImageData & other);

    /*!
     * @brief Assigns the value of other to this @c %ImageData.
     *
     * Like the copy constructor, this does a shallow-copy until a point at which a full copy is necessary.
     *
     * @param other The @c %ImageData to assign.
     *
     * @return The @c %ImageData instance.
     *
     * @since BlackBerry 10.0.0
     */
    ImageData & operator=(const ImageData & other);

    /*!
     * @brief Creates an @c %ImageData from existing memory.
     *
     * The memory is @a copied into a newly allocated buffer that the @c %ImageData owns.
     *
     * @param sourceBuffer  The address of the first pixel to copy from.
     * @param format The format of the created pixels. See @c PixelFormat for the list of supported formats.
     * @param width The width of the created image data.
     * @param height The height of the created image data.
     * @param sourceBytesPerLine The number of bytes per line (stride) in the @c sourceBuffer.
     *
     * @return The newly created @c ImageData.
     *
     * @since BlackBerry 10.0.0
     */
    static ImageData fromPixels(const unsigned char * sourceBuffer, PixelFormat::Type format, int width, int height, int sourceBytesPerLine);

    /*!
     * @brief Whether this @c %ImageData object contains valid image data.
     *
     * @return @c true if this @c %ImageData object contains valid image data, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief The format of the pixels.
     *
     * @return The format of the pixels. @see @c PixelFormat.
     *
     * @since BlackBerry 10.0.0
     */
    PixelFormat::Type format() const;

    /*!
     * @brief The width of the image.
     *
     * @return The width of the image.
     *
     * @since BlackBerry 10.0.0
     */
    int width() const;

    /*!
     * @brief The height of the image.
     *
     * @return The height of the image.
     *
     * @since BlackBerry 10.0.0
     */
    int height() const;

    /*!
     * @brief The bytes per line of the image buffer.
     *
     * The bytes per line is equivalent to "byte address of first pixel on second line - byte address of first pixel on first line".
     *
     * @return The bytes per line of the image buffer.
     *
     * @since BlackBerry 10.0.0
     */
    int bytesPerLine() const;

    /*!
     * @brief Get a read/write pointer to the start of pixel memory.
     *
     * If the internal buffer is currently shared by other instances of @c %ImageData,
     * then a copy of the buffer is made at this point.
     *
     * @return A  read/write pointer to the start of pixel memory.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned char * pixels();

    /*!
     * @brief Get a read-only pointer to the start of pixel memory.
     *
     * @return A read-only pointer to the start of pixel memory.
     *
     * @since BlackBerry 10.0.0
     */
    const unsigned char * pixels() const;

    /*!
     * @brief Get a read-only pointer to the start of pixel memory.
     *
     * @return A read-only pointer to the start of pixel memory.
     *
     * @since BlackBerry 10.0.0
     */
    const unsigned char * constPixels() const;

private:
//!@cond PRIVATE
    class ImageDataPrivate;
    QSharedDataPointer<ImageDataPrivate> d;
//!@endcond
};

//!@cond PRIVATE
BB_CORE_EXPORT QDebug operator<<(QDebug dbg, const ImageData & image);
//!@endcond

}  // namespace


#endif // BB_CORE_IMAGEDATA_HPP
