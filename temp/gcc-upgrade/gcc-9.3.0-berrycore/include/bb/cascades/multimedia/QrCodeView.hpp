/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_QRCODEVIEW_HPP
#define BB_CASCADES_MULTIMEDIA_QRCODEVIEW_HPP

#include <bb/cascades/multimedia/QrCodeErrorCorrection>
#include <bb/cascades/multimedia/QrCodeRenderResult>
#include <bb/cascades/CustomControl>
#include <bb/cascades/multimedia/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

class ImageData;

namespace cascades
{
namespace multimedia
{

class QrCodeViewPrivate;

/*!
 * @headerfile QrCodeView.hpp <bb/cascades/multimedia/QrCodeView>
 *
 * @brief Displays a QR code.
 *
 * @details The @c %QrCodeView class represents a Cascades control that displays a QR code
 * (see http://www.denso-wave.com/qrcode/qrstandard-e.html), which is generated from the value
 * of the @c data property.
 *
 * You can control the amount of error correction encoded in the resulting image using the @c
 * errorCorrection property.  Note that more error correction means less room for data.
 *
 * This control only encodes QR codes as Alphanumeric (UTF8).
 *
 * Information on the maximum amount of data that can be encoded can be found at
 * http://www.denso-wave.com/qrcode/qrstandard-e.html.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT QrCodeView : public CustomControl
{
    Q_OBJECT

    /*!
     * @brief The data to display as a QR code.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged FINAL)

    /*!
     * @brief The amount of error correction encoded into the displayed QR code.
     *
     * @details The default error correction is @c QrCodeErrorCorrection::Quality.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::QrCodeErrorCorrection::Type errorCorrection READ errorCorrection WRITE setErrorCorrection NOTIFY errorCorrectionChanged FINAL)

public:
    /*!
     * @brief Creates a new @c %QrCodeView instance.
     *
     * @param parent The parent container or 0. This parameter is optional and will default
     *        to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit QrCodeView(Container *parent = 0);

    /*!
     * @brief Destroys this @c %QrCodeView.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~QrCodeView();

    /*!
     * @brief Gets the data to display as a QR code.
     *
     * @return The data to display as a QR code.
     *
     * @since BlackBerry 10.0.0
     */
    QString data() const;

    /*!
     * @brief Sets the data to display as a QR code.
     *
     * @param data The data to display as a QR code.
     *
     * @since BlackBerry 10.0.0
     */
    void setData(const QString &data);

    /*!
     * @brief Gets the amount of error correction encoded into the displayed QR code.
     *
     * @details The default error correction is @c QrCodeErrorCorrection::Quality.
     *
     * @return The error correction used for the displayed QR code.
     *
     * @since BlackBerry 10.0.0
     */
    QrCodeErrorCorrection::Type errorCorrection() const;

    /*!
     * @brief Sets the amount of error correction encoded into the displayed QR code.
     *
     * @details The default error correction is @c QrCodeErrorCorrection::Quality.
     *
     * @param errorCorrection The error correction used for the displayed QR code.
     *
     * @since BlackBerry 10.0.0
     */
    void setErrorCorrection(QrCodeErrorCorrection::Type errorCorrection);

    /**
     * @brief Renders and returns the QR code in ImageData format at a given size.
     *
     * @details A block size of 1 is minimum and good for transmission due to the resultant small size of the image data.
     * If the image is to be displayed with "nearest-neighbor" scaling, a block size of one can also be used to display the QR code.
     * If the display scaling is "smooth", a larger block size is recommended to avoid a blurred QR code that may be difficult to scan.
     *
     * A margin around the QR code may not be necessary for transmitting QR codes, but may be important
     * for proper scanning when displayed against a dark background.
     *
     * @param blockSize The size, in pixels, of each QR code 'block' or 'square'. Minimum size is 1 (smaller values will be set to 1).
     * @param margin The size, in pixels, of whitespace around the QR code.  Minimum size is 0 (smaller values will be set to 0), but a positive margin is recommended if the QR code may be used against a dark background.
     * @param result If not 0, @c *result is set to a code indicating the result of the operation. See @c bb::cascades::multimedia::QrCodeRenderResult for the list of possible results.
     * @return Returns the QR code in ImageData format.  An empty (invalid) ImageData is returned if an error occurs (ie data string is empty, data string is too large, etc)
     *
     * @since BlackBerry 10.2.0
     */
    bb::ImageData toImageData(int blockSize = 1, int margin = 2, QrCodeRenderResult::Type * result = 0) const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the value of the @c data property changes.
     *
     * @param data The new value of the @c data property.
     *
     * @since BlackBerry 10.0.0
     */
    void dataChanged(const QString &data);

    /*!
     * @brief Emitted when the value of the @c errorCorrection property changes.
     *
     * @param errorCorrection The new value of the @c errorCorrection property.
     *
     * @since BlackBerry 10.0.0
     */
    void errorCorrectionChanged(bb::cascades::multimedia::QrCodeErrorCorrection::Type errorCorrection);

    /*!
     * @brief Emitted after the QR code was rendered.
     *
     * @details This signal is emitted when the QR code is rendered due to changes in @ data, @ errorCorrection, or the size of the control.
     * The signal is not emitted as a result of calls to @c toImageData() (as the render result can be obtained from that function directly).
     *
     * @param result The result of the rendering. See @c bb::cascades::multimedia::QrCodeRenderResult for a list of possible results.
     *
     * @since BlackBerry 10.2.0
     */
    void renderResult(bb::cascades::multimedia::QrCodeRenderResult::Type result);

protected:
    //! @cond PRIVATE
    Q_SIGNAL void errorCorrectionChanged(int errorCorrection);

    Q_SIGNAL void renderResult(int result);
    //! @endcond

private:
    //! @cond PRIVATE
    Q_DISABLE_COPY(QrCodeView);
    Q_DECLARE_PRIVATE(QrCodeView);
    QrCodeViewPrivate * const d_ptr;
    //! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::multimedia::QrCodeView);

#endif /* header guard */
