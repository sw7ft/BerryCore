/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEGENERATOR_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEGENERATOR_HPP

#include <bb/cascades/multimedia/Global>
#include <bb/cascades/multimedia/BarcodeGeneratorError>
#include <bb/cascades/multimedia/BarcodeGeneratorFormat>
#include <bb/ImageData>

#include <QObject>
#include <QtDeclarative>
#include <QUrl>
#include <QScopedPointer>

namespace bb
{

class ImageData; // forward declaration is all that is needed

namespace cascades
{
namespace multimedia
{

class BarcodeGeneratorPrivate;

/*!
 * @headerfile BarcodeGenerator.hpp <bb/cascades/multimedia/BarcodeGenerator>
 *
 * @brief Encodes user-supplied data to a barcode.
 *
 * @details A @c BarcodeGenerator creates barcodes in a variety of formats by encoding user-supplied data.
 * When created, a barcode can be written immediately as a file, or retrieved as @c ImageData and used by other controls.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeGenerator : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Creates an instance of the @c %BarcodeGenerator class.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit BarcodeGenerator(QObject *parent = 0);

    /*!
     * @brief Destroys this @c %BarcodeGenerator.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~BarcodeGenerator();

    /*!
     * @brief Indicates the status of the last barcode generation attempt.
     *
     * @details Call this method after after attempting to generate a barcode.
     *
     * @returns One of @c bb::cascades::multimedia::BarcodeGeneratorError.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::cascades::multimedia::BarcodeGeneratorError::Type error() const;
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the error() method returning the enumerator is availble from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int error() const;
#endif

    /*!
     * @brief Creates a barcode and write it to file.
     *
     * @details The barcode image is written in the location and image format specified in the @c filename parameter. For example, specifying a file name of barcode.png writes in PNG format.
     *
     * @param filename The location and image format for the barcode image.
     * @param format The encoding format for the barcode.  See @c bb::cascades::multimedia::BarcodeGeneratorFormat::Type for more details.
     * @param data The data encoded into the barcode.
     *
     * @returns The fully-qualified path of the written barcode file. If an empty string is returned an error has occurred. Read @c error() to obtain the
     * reason why it failed and see @c bb::cascades::multimedia::BarcodeGeneratorError for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QString generate( const QUrl &filename, bb::cascades::multimedia::BarcodeGeneratorFormat::Type format, const QString &data );

    /*!
     * @brief Creates a scaled barcode and writes it to file.
     *
     * @details The barcode image is written in the location and image format specified in the @c filename paramter. For example, specifying a file name of barcode.png writes in PNG format.
     *
     * @param filename The location and image format for the barcode image.
     * @param format The encoding format for the barcode.  See @c bb::cascades::multimedia::BarcodeGeneratorFormat::Type for more details.
     * @param data The data encoded into the barcode.
     * @param scale The amount of scaling applied to the barcode image.
     *
     * @returns The fully-qualified path of the written barcode file. If an empty string is returned an error has occurred. Read @c error() to obtain the
     * reason why it failed and see @c bb::cascades::multimedia::BarcodeGeneratorError for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QString generate( const QUrl &filename, bb::cascades::multimedia::BarcodeGeneratorFormat::Type format, const QString &data, float scale );

    /*!
     * @brief Creates a barcode and returns it as @c bb::ImageData.
     *
     * @details The resulting @c bb::ImageData is in 32bpp RGBA format and can be used in other Cascades controls such as an @c bb::cascades::ImageView.
     *
     * @param format The encoding format for the barcode.  See @c bb::cascades::multimedia::BarcodeGeneratorFormat::Type for more details.
     * @param data The data encoded into the barcode.
     *
     * @returns The @c bb::ImageData containing the rendered barcode.  If the resulting @c bb::ImageData is not valid, the reason for the failure can be determined by calling @c error().
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::ImageData generate( bb::cascades::multimedia::BarcodeGeneratorFormat::Type format, const QString &data );

    /*!
     * @brief Creates a scaled barcode and returns it as @c bb::ImageData.
     *
     * @details The resulting @c bb::ImageData is in 32bpp RGBA format and can be used in other Cascades controls such as an @c bb::cascades::ImageView.
     *
     * @param format The encoding format for the barcode.  See @c bb::cascades::multimedia::BarcodeGeneratorFormat::Type for more details.
     * @param data The data encoded into the barcode.
     * @param scale The amount of scaling applied to the barcode image.
     *
     * @returns The @c bb::ImageData containing the rendered barcode.  If the resulting @c bb::ImageData is not valid, the reason for the failure can be determined by calling @c error().
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::ImageData generate( bb::cascades::multimedia::BarcodeGeneratorFormat::Type format, const QString &data, float scale );

protected:
    //! @cond PRIVATE
    Q_INVOKABLE QString generate( const QUrl &filename, int format, const QString &data );

    Q_INVOKABLE QString generate( const QUrl &filename, int format, const QString &data, float scale );

    Q_INVOKABLE bb::ImageData generate( int format, const QString &data );

    Q_INVOKABLE bb::ImageData generate( int format, const QString &data, float scale );
    //! @endcond

private:
//! @cond PRIVATE
    Q_DISABLE_COPY(BarcodeGenerator);
    Q_DECLARE_PRIVATE(BarcodeGenerator);
    QScopedPointer<BarcodeGeneratorPrivate> d_ptr;
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::multimedia::BarcodeGenerator);
#endif // BB_CASCADES_MULTIMEDIA_BARCODEGENERATOR_HPP
